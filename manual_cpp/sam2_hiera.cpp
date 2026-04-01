// SAM2 Hiera backbone implementation
// Architecture: 4-stage hierarchical ViT with masked unit attention
// Stage dims: 96 (256²) → 192 (128²) → 384 (64²) → 768 (32²)
#include "sam2.h"
#include <cstring>

// ─────────────────────────────────────────────────────────────────
// Helpers: NHWC window partition / unpartition
// x:   [N, H, W, C]  → windows: [N*nW*nH, wH, wW, C]
// ─────────────────────────────────────────────────────────────────
static void window_partition(const float* x, float* win,
                             int N, int H, int W, int C,
                             int wH, int wW)
{
    // win: [(N * (H/wH) * (W/wW)), wH, wW, C]
    int nH = H / wH, nW = W / wW;
    for (int n = 0; n < N; n++) {
        for (int ph = 0; ph < nH; ph++) {
            for (int pw = 0; pw < nW; pw++) {
                for (int wh = 0; wh < wH; wh++) {
                    for (int ww = 0; ww < wW; ww++) {
                        int src_h = ph*wH + wh;
                        int src_w = pw*wW + ww;
                        const float* s = x + ((n*H + src_h)*W + src_w)*C;
                        float* d = win + ((((n*nH + ph)*nW + pw)*wH + wh)*wW + ww)*C;
                        std::memcpy(d, s, C*sizeof(float));
                    }
                }
            }
        }
    }
}

static void window_unpartition(const float* win, float* x,
                               int N, int H, int W, int C,
                               int wH, int wW)
{
    int nH = H / wH, nW = W / wW;
    for (int n = 0; n < N; n++) {
        for (int ph = 0; ph < nH; ph++) {
            for (int pw = 0; pw < nW; pw++) {
                for (int wh = 0; wh < wH; wh++) {
                    for (int ww = 0; ww < wW; ww++) {
                        int dst_h = ph*wH + wh;
                        int dst_w = pw*wW + ww;
                        const float* s = win + ((((n*nH+ph)*nW+pw)*wH+wh)*wW+ww)*C;
                        float* d = x + ((n*H + dst_h)*W + dst_w)*C;
                        std::memcpy(d, s, C*sizeof(float));
                    }
                }
            }
        }
    }
}

// ─────────────────────────────────────────────────────────────────
// Pool NHWC spatially by 2x2 max  [B,H,W,C] → [B,H/2,W/2,C]
// ─────────────────────────────────────────────────────────────────
static void maxpool2d_nhwc(const float* in, float* out,
                           int B, int H, int W, int C)
{
    int oH = H/2, oW = W/2;
    for (int b = 0; b < B; b++) {
        for (int oh = 0; oh < oH; oh++) {
            for (int ow = 0; ow < oW; ow++) {
                for (int c = 0; c < C; c++) {
                    float mx = -1e38f;
                    for (int kh = 0; kh < 2; kh++) {
                        for (int kw = 0; kw < 2; kw++) {
                            float v = in[((b*H + oh*2+kh)*W + ow*2+kw)*C + c];
                            if (v > mx) mx = v;
                        }
                    }
                    out[((b*oH + oh)*oW + ow)*C + c] = mx;
                }
            }
        }
    }
}

// ─────────────────────────────────────────────────────────────────
// Standard window attention block (no spatial downsampling)
// x: [N, H, W, C] NHWC, modified in-place (after attention+MLP)
// ─────────────────────────────────────────────────────────────────
static void hiera_regular_block(float* x, int N, int H, int W, int C,
                                const HieraBlock& blk,
                                std::vector<float>& tmp_buf)
{
    int wH = blk.win_h, wW = blk.win_w;
    int nW = (H/wH) * (W/wW) * N;  // number of windows
    int T  = wH * wW;                // tokens per window
    int head_dim = C / blk.heads;

    // scratch
    size_t sz_win = (size_t)nW * T * C;
    size_t sz_qkv = (size_t)nW * T * (3*C);
    size_t sz_attn = (size_t)nW * blk.heads * T * T;
    tmp_buf.resize(sz_win + sz_qkv + sz_attn + (size_t)nW*T*C*2);
    float* win_x  = tmp_buf.data();                          // [nW, T, C]
    float* qkv    = win_x + sz_win;                          // [nW, T, 3C]
    float* attn_s = qkv + sz_qkv;                            // [nW, H, T, T]
    float* out_a  = attn_s + sz_attn;                        // [nW, T, C]
    float* ln_tmp = out_a + (size_t)nW*T*C;                  // reuse

    // ── Attention sub-block ────────────────────────────────────
    // Save residual
    std::vector<float> residual(x, x + (size_t)N*H*W*C);

    // LayerNorm1 (normalise last dim C, in-place)
    layer_norm(x, blk.norm1.w.data(), blk.norm1.b.data(), N*H*W*C, C);

    // Window partition
    window_partition(x, win_x, N, H, W, C, wH, wW);

    // QKV projection: [nW, T, C] → [nW, T, 3C]
    linear(win_x, blk.qkv.w.data(), blk.qkv.b.data(), qkv, nW*T, 3*C, C);

    // Reshape to [nW, T, 3, heads, head_dim] then split
    // q/k/v each [nW, heads, T, head_dim]
    int C3H = 3 * C;
    std::vector<float> q_buf((size_t)nW * blk.heads * T * head_dim);
    std::vector<float> k_buf((size_t)nW * blk.heads * T * head_dim);
    std::vector<float> v_buf((size_t)nW * blk.heads * T * head_dim);

    for (int w = 0; w < nW; w++) {
        for (int t = 0; t < T; t++) {
            const float* qkv_t = qkv + (w*T+t)*C3H;
            for (int h = 0; h < blk.heads; h++) {
                for (int d = 0; d < head_dim; d++) {
                    q_buf[((size_t)w*blk.heads+h)*T*head_dim + t*head_dim + d] =
                        qkv_t[0*C + h*head_dim + d];
                    k_buf[((size_t)w*blk.heads+h)*T*head_dim + t*head_dim + d] =
                        qkv_t[1*C + h*head_dim + d];
                    v_buf[((size_t)w*blk.heads+h)*T*head_dim + t*head_dim + d] =
                        qkv_t[2*C + h*head_dim + d];
                }
            }
        }
    }

    // Attention: [nW, heads, T, head_dim]
    std::vector<float> attn_out((size_t)nW * blk.heads * T * head_dim);
    sdpa(q_buf.data(), k_buf.data(), v_buf.data(),
         attn_out.data(), attn_s,
         nW * blk.heads, 1, T, T, head_dim);

    // Reassemble [nW, T, C]
    for (int w = 0; w < nW; w++) {
        for (int t = 0; t < T; t++) {
            for (int h = 0; h < blk.heads; h++) {
                for (int d = 0; d < head_dim; d++) {
                    out_a[(w*T+t)*C + h*head_dim + d] =
                        attn_out[((size_t)w*blk.heads+h)*T*head_dim + t*head_dim + d];
                }
            }
        }
    }

    // Out projection: [nW, T, C] → [nW, T, C]
    std::vector<float> out_proj((size_t)nW * T * C);
    linear(out_a, blk.out_proj.w.data(), blk.out_proj.b.data(),
           out_proj.data(), nW*T, C, C);

    // Unpartition back to [N, H, W, C]
    window_unpartition(out_proj.data(), x, N, H, W, C, wH, wW);

    // Add residual
    add_inplace(x, residual.data(), N*H*W*C);

    // ── MLP sub-block ──────────────────────────────────────────
    std::copy(x, x + (size_t)N*H*W*C, residual.begin());

    // LayerNorm2
    layer_norm(x, blk.norm2.w.data(), blk.norm2.b.data(), N*H*W*C, C);

    // FC1: [N*H*W, 4C]
    int M = N*H*W;
    std::vector<float> fc1_out((size_t)M * blk.fc1.out_f);
    linear(x, blk.fc1.w.data(), blk.fc1.b.data(),
           fc1_out.data(), M, blk.fc1.out_f, C);
    gelu_inplace(fc1_out.data(), M * blk.fc1.out_f);

    // FC2: [N*H*W, C]
    linear(fc1_out.data(), blk.fc2.w.data(), blk.fc2.b.data(),
           x, M, C, blk.fc1.out_f);

    // Add residual
    add_inplace(x, residual.data(), N*H*W*C);
}

// ─────────────────────────────────────────────────────────────────
// Masked Unit Attention (MUA) transition block
// Input:  x [N, H, W, C_in] NHWC
// Output: out [N, H/2, W/2, C_out] NHWC
//
// In the graph, this block:
//   1. Windows x at (wH,wW) = 8x8 for stage1→2 or 4x4 for stage2→3
//   2. Projects [nW, T, C_in] → [nW, T, 3*heads*head_dim]
//      where Q is spatially pooled 2x (nW,T/4,heads,head_dim)
//            K/V remain at full resolution (nW,T,heads,head_dim)
//   3. Attention Q[T/4] × K[T] produces [T/4] output tokens per window
//   4. Out-proj, reshape to [N, H/2, W/2, C_out]
//   5. Then a SEPARATE downsampling projection applies to x before adding residual:
//      norm(x) → linear(C_in → C_out) → permute → maxpool2d → permute  =  skip_conn
//   6. Add residual skip_conn
//   7. LayerNorm + MLP
// ─────────────────────────────────────────────────────────────────
static void hiera_transition_block(
    const float* x, float* y,        // x: input, y: output (pre-allocated)
    int N, int H, int W,
    const HieraBlock& blk,
    // downsampling projection for residual (tensors 18-19 style)
    const float* ds_w, const float* ds_b, // [C_out, C_in]
    // pre-ds norm
    const float* ds_norm_w, const float* ds_norm_b,
    std::vector<float>& tmp_buf)
{
    int C_in  = blk.C_in;
    int C_out = blk.C_out;
    int wH    = blk.win_h, wW = blk.win_w;
    int nH_wins = H / wH, nW_wins = W / wW;
    int nW   = N * nH_wins * nW_wins;   // total windows
    int T    = wH * wW;                  // tokens per window (full)
    int T_q  = T / 4;                    // query tokens (2x spatial pool)
    int heads = blk.heads;
    int head_dim = C_out / heads;        // head dim in output space

    // ── Build skip connection: norm(x) → linear(C_out) → pool ──
    std::vector<float> skip_inp(x, x + (size_t)N*H*W*C_in);
    layer_norm(skip_inp.data(), ds_norm_w, ds_norm_b, N*H*W*C_in, C_in);
    // Project: [N*H*W, C_out]
    std::vector<float> skip_proj((size_t)N*H*W*C_out);
    linear(skip_inp.data(), ds_w, ds_b, skip_proj.data(), N*H*W, C_out, C_in);
    // Permute to NCHW: [N, C_out, H, W]
    std::vector<float> skip_nchw((size_t)N*C_out*H*W);
    for (int n = 0; n < N; n++)
        for (int h = 0; h < H; h++)
            for (int w = 0; w < W; w++)
                for (int c = 0; c < C_out; c++)
                    skip_nchw[((n*C_out+c)*H+h)*W+w] = skip_proj[(n*H+h)*W*C_out + w*C_out + c];
    // MaxPool 2x2: [N, C_out, H/2, W/2]
    int oH = H/2, oW = W/2;
    std::vector<float> skip_pooled((size_t)N*C_out*oH*oW);
    maxpool2d_nchw(skip_nchw.data(), skip_pooled.data(), N, C_out, H, W, 2,2,2,2);
    // Back to NHWC: [N, H/2, W/2, C_out]
    std::vector<float> skip((size_t)N*oH*oW*C_out);
    for (int n = 0; n < N; n++)
        for (int oh = 0; oh < oH; oh++)
            for (int ow = 0; ow < oW; ow++)
                for (int c = 0; c < C_out; c++)
                    skip[(n*oH+oh)*oW*C_out + ow*C_out + c] =
                        skip_pooled[((n*C_out+c)*oH+oh)*oW+ow];

    // ── Attention on original x ─────────────────────────────────
    // Window partition of x: [nW, T, C_in]
    std::vector<float> win_x((size_t)nW * T * C_in);
    window_partition(x, win_x.data(), N, H, W, C_in, wH, wW);

    // QKV projection: [nW, T, 3*C_out]
    // qkv.w: [3*C_out, C_in]  (C_out = heads * head_dim)
    std::vector<float> qkv_all((size_t)nW * T * (3*C_out));
    linear(win_x.data(), blk.qkv.w.data(), blk.qkv.b.data(),
           qkv_all.data(), nW*T, 3*C_out, C_in);

    // Split Q/K/V: each [nW, T, C_out]
    // Then pool Q spatially: Q_win [wH,wW,heads,head_dim] → pool → [wH/2,wW/2,heads,head_dim]
    // Resulting: Q [nW, T_q, heads, head_dim], K/V [nW, T, heads, head_dim]

    std::vector<float> q_flat((size_t)nW * T_q * C_out);
    std::vector<float> k_flat((size_t)nW * T   * C_out);
    std::vector<float> v_flat((size_t)nW * T   * C_out);

    // For K/V, just copy the last 2*C_out from qkv_all
    for (int i = 0; i < nW*T; i++) {
        const float* src = qkv_all.data() + i*(3*C_out);
        std::memcpy(k_flat.data() + i*C_out, src + C_out,   C_out*sizeof(float));
        std::memcpy(v_flat.data() + i*C_out, src + 2*C_out, C_out*sizeof(float));
    }

    // Pool Q spatially: for each window, pool 2x2
    // Q_raw: [nW, wH, wW, C_out] → pool → [nW, wH/2, wW/2, C_out]
    std::vector<float> q_raw_win((size_t)nW * T * C_out);
    for (int i = 0; i < nW*T; i++) {
        const float* src = qkv_all.data() + i*(3*C_out);
        std::memcpy(q_raw_win.data() + i*C_out, src, C_out*sizeof(float));
    }
    // q_raw_win: [nW, wH, wW, C_out] → pool to [nW, wH/2, wW/2, C_out]
    int qH = wH/2, qW = wW/2;
    for (int w = 0; w < nW; w++) {
        for (int qh = 0; qh < qH; qh++) {
            for (int qw = 0; qw < qW; qw++) {
                for (int c = 0; c < C_out; c++) {
                    float mx = -1e38f;
                    for (int kh = 0; kh < 2; kh++) {
                        for (int kw = 0; kw < 2; kw++) {
                            int idx_tok = (qh*2+kh)*wW + qw*2+kw;
                            float v = q_raw_win[(w*T+idx_tok)*C_out + c];
                            if (v > mx) mx = v;
                        }
                    }
                    q_flat[(w*T_q + qh*qW+qw)*C_out + c] = mx;
                }
            }
        }
    }

    // Reformat to [nW, heads, T_q/T, head_dim] for sdpa
    auto reformat = [&](const std::vector<float>& src, int tokens) {
        std::vector<float> dst((size_t)nW * heads * tokens * head_dim);
        for (int w = 0; w < nW; w++) {
            for (int t = 0; t < tokens; t++) {
                for (int h = 0; h < heads; h++) {
                    for (int d = 0; d < head_dim; d++) {
                        dst[((w*heads+h)*tokens + t)*head_dim + d] =
                            src[(w*tokens+t)*C_out + h*head_dim + d];
                    }
                }
            }
        }
        return dst;
    };
    auto q_heads = reformat(q_flat, T_q);
    auto k_heads = reformat(k_flat, T);
    auto v_heads = reformat(v_flat, T);

    // SDPA: Q[T_q] attends to K/V[T]
    std::vector<float> attn_out((size_t)nW * heads * T_q * head_dim);
    std::vector<float> attn_buf((size_t)nW * heads * T_q * T);
    sdpa(q_heads.data(), k_heads.data(), v_heads.data(),
         attn_out.data(), attn_buf.data(),
         nW * heads, 1, T_q, T, head_dim);

    // Reassemble [nW, T_q, C_out]
    std::vector<float> attn_reassembled((size_t)nW * T_q * C_out);
    for (int w = 0; w < nW; w++) {
        for (int t = 0; t < T_q; t++) {
            for (int h = 0; h < heads; h++) {
                for (int d = 0; d < head_dim; d++) {
                    attn_reassembled[(w*T_q+t)*C_out + h*head_dim + d] =
                        attn_out[((w*heads+h)*T_q + t)*head_dim + d];
                }
            }
        }
    }

    // Out proj: [nW*T_q, C_out] → [nW*T_q, C_out]
    std::vector<float> attn_proj((size_t)nW * T_q * C_out);
    linear(attn_reassembled.data(), blk.out_proj.w.data(), blk.out_proj.b.data(),
           attn_proj.data(), nW*T_q, C_out, C_out);

    // Unpartition pooled windows back to [N, H/2, W/2, C_out]
    // Each window contributes qH×qW = T_q tokens
    window_unpartition(attn_proj.data(), y, N, oH, oW, C_out, qH, qW);

    // Add skip residual
    add_inplace(y, skip.data(), (size_t)N*oH*oW*C_out);

    // ── MLP sub-block ──────────────────────────────────────────
    std::vector<float> y_res(y, y + (size_t)N*oH*oW*C_out);
    int M = N*oH*oW;

    // For transition blocks: norm1 (offset 4-5 in block) is the pre-MLP norm
    // (same tensor offset as pre-attn norm in regular blocks, but here applied
    // post-attention-add since MUA has no pre-attention norm).
    layer_norm(y, blk.norm1.w.data(), blk.norm1.b.data(), M*C_out, C_out);

    std::vector<float> fc1_out((size_t)M * blk.fc1.out_f);
    linear(y, blk.fc1.w.data(), blk.fc1.b.data(), fc1_out.data(), M, blk.fc1.out_f, C_out);
    gelu_inplace(fc1_out.data(), M * blk.fc1.out_f);

    linear(fc1_out.data(), blk.fc2.w.data(), blk.fc2.b.data(), y, M, C_out, blk.fc1.out_f);

    add_inplace(y, y_res.data(), (size_t)N*oH*oW*C_out);
}

// ─────────────────────────────────────────────────────────────────
// Run Hiera encoder
// Input: img_nchw [1, 3, 1024, 1024]
// Outputs: feats at 4 scales in NCHW, projected to 256ch
// ─────────────────────────────────────────────────────────────────
void run_hiera(const SAM2& model, const float* img_nchw,
               // Output FPN features (256ch, NCHW)
               Tensor& feat0,  // [1, 256, 256, 256]  (scale0, stride 4)
               Tensor& feat1,  // [1, 256, 128, 128]  (scale1)
               Tensor& feat2,  // [1, 256, 64, 64]    (scale2)
               Tensor& feat3)  // [1, 256, 32, 32]    (scale3)
{
    const int N = 1;
    std::vector<float> tmp;

    // ── Patch embed: [1,3,1024,1024] → [1,96,256,256] ──────────
    Tensor pe_nchw({1, 96, 256, 256});
    conv2d_nchw(img_nchw, pe_nchw.ptr(),
                model.pe_conv_w.data(), model.pe_conv_b.data(),
                1, 3, 1024, 1024, 96, 7, 7, 4, 4, 3, 3);

    // Position embed: bicubic(7x7→256x256) + tile(8x8,32x32) + add  → [1,96,256,256]
    Tensor pos_up({1, 96, 256, 256});
    upsample_bicubic_nchw(model.pe_pos_7x7.data(), pos_up.ptr(), 1, 96, 7, 7, 256, 256);

    // tile(1,96,8,8) to (1,96,256,256): repeat 32x in H and W
    Tensor pos_tile({1, 96, 256, 256});
    const float* tile_src = model.pe_pos_8x8.data();
    for (int c = 0; c < 96; c++) {
        for (int h = 0; h < 256; h++) {
            for (int w = 0; w < 256; w++) {
                pos_tile.ptr()[(c*256+h)*256+w] = tile_src[(c*8 + h%8)*8 + w%8];
            }
        }
    }
    // Add pos embeds to patch embed (both NCHW → add)
    add_inplace(pe_nchw.ptr(), pos_up.ptr(), 1*96*256*256);
    add_inplace(pe_nchw.ptr(), pos_tile.ptr(), 1*96*256*256);

    // Permute to NHWC: [1, 256, 256, 96]
    std::vector<float> s1_nhwc((size_t)1*256*256*96);
    for (int c = 0; c < 96; c++)
        for (int h = 0; h < 256; h++)
            for (int w = 0; w < 256; w++)
                s1_nhwc[(h*256+w)*96 + c] = pe_nchw.ptr()[(c*256+h)*256+w];

    // LayerNorm on patch embed
    layer_norm(s1_nhwc.data(), model.pe_norm.w.data(), model.pe_norm.b.data(),
               1*256*256*96, 96);

    // ── Stage 1: 1 regular block, 96ch ──────────────────────────
    hiera_regular_block(s1_nhwc.data(), 1, 256, 256, 96,
                        model.s1_blocks[0], tmp);
    // Stage 1 FPN output (used for feat0)
    std::vector<float> s1_out = s1_nhwc;  // save NHWC [1,256,256,96]

    // ── Stage 2: transition (96→192) + 1 regular block ──────────
    // Transition: s1_nhwc → s2_nhwc [1,128,128,192]
    std::vector<float> s2_nhwc((size_t)1*128*128*192);

    // Stage 1→2 transition: ds_norm = s1_out_norm, ds_proj = tensors 18-19
    hiera_transition_block(
        s1_nhwc.data(), s2_nhwc.data(),
        1, 256, 256,
        model.s2_blocks[0],
        model.ds_w_s2.data(),
        model.ds_b_s2.data(),
        model.s1_out_norm.w.data(),
        model.s1_out_norm.b.data(),
        tmp);

    // Regular block 1 (192ch)
    hiera_regular_block(s2_nhwc.data(), 1, 128, 128, 192,
                        model.s2_blocks[1], tmp);
    std::vector<float> s2_out = s2_nhwc;

    // ── Stage 3: transition (192→384) + 7 regular blocks ────────
    std::vector<float> s3_nhwc((size_t)1*64*64*384);

    // Stage 2→3 transition: ds_norm = s2_out_norm, ds_proj = tensors 44-45
    hiera_transition_block(
        s2_nhwc.data(), s3_nhwc.data(),
        1, 128, 128,
        model.s3_blocks[0],
        model.ds_w_s3.data(),
        model.ds_b_s3.data(),
        model.s2_out_norm.w.data(),
        model.s2_out_norm.b.data(),
        tmp);

    for (int i = 1; i < 7; i++) {
        hiera_regular_block(s3_nhwc.data(), 1, 64, 64, 384,
                            model.s3_blocks[i], tmp);
    }
    std::vector<float> s3_out = s3_nhwc;

    // ── Stage 4: transition (384→768) + 1 regular block ─────────
    std::vector<float> s4_nhwc((size_t)1*32*32*768);

    // Stage 3→4 transition: ds_norm = s3_out_norm, ds_proj = tensors 130-131
    hiera_transition_block(
        s3_nhwc.data(), s4_nhwc.data(),
        1, 64, 64,
        model.s4_blocks[0],
        model.ds_w_s4.data(),
        model.ds_b_s4.data(),
        model.s3_out_norm.w.data(),
        model.s3_out_norm.b.data(),
        tmp);

    hiera_regular_block(s4_nhwc.data(), 1, 32, 32, 768,
                        model.s4_blocks[1], tmp);

    // ── FPN Neck: project each scale to 256ch, NCHW ─────────────
    // Stage 4 → feat3 [1,256,32,32]
    auto nhwc_to_nchw = [](const float* nhwc, float* nchw, int N, int H, int W, int C) {
        for (int n = 0; n < N; n++)
            for (int h = 0; h < H; h++)
                for (int w = 0; w < W; w++)
                    for (int c = 0; c < C; c++)
                        nchw[((n*C+c)*H+h)*W+w] = nhwc[(n*H+h)*W*C + w*C + c];
    };

    auto apply_neck_conv = [&](const std::vector<float>& nhwc,
                                float* out_nchw,
                                int H, int W, int C_in,
                                const std::vector<float>& nw,
                                const std::vector<float>& nb) {
        // Convert NHWC → NCHW
        std::vector<float> nchw_in((size_t)H*W*C_in);
        nhwc_to_nchw(nhwc.data(), nchw_in.data(), 1, H, W, C_in);
        // 1x1 conv: [1, 256, H, W]
        conv2d_nchw(nchw_in.data(), out_nchw,
                    nw.data(), nb.data(),
                    1, C_in, H, W, 256, 1, 1, 1, 1, 0, 0);
    };

    feat3 = Tensor({1, 256, 32, 32});
    apply_neck_conv(std::vector<float>(s4_nhwc),
                    feat3.ptr(), 32, 32, 768,
                    model.neck.w[0], model.neck.b[0]);

    feat2 = Tensor({1, 256, 64, 64});
    apply_neck_conv(std::vector<float>(s3_out),
                    feat2.ptr(), 64, 64, 384,
                    model.neck.w[1], model.neck.b[1]);

    feat1 = Tensor({1, 256, 128, 128});
    apply_neck_conv(std::vector<float>(s2_out),
                    feat1.ptr(), 128, 128, 192,
                    model.neck.w[2], model.neck.b[2]);

    feat0 = Tensor({1, 256, 256, 256});
    apply_neck_conv(std::vector<float>(s1_out),
                    feat0.ptr(), 256, 256, 96,
                    model.neck.w[3], model.neck.b[3]);
}
