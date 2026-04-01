// SAM2 Prompt Encoder + Mask Decoder implementation
#include "sam2.h"
#include <cstring>

// ─────────────────────────────────────────────────────────────────
// Positional encoding: Gaussian random Fourier features
// coords: [N, 2] normalised to [0,1]
// Returns: [N, 256]  (128 sin + 128 cos features)
// ─────────────────────────────────────────────────────────────────
static void gaussian_pos_encoding(const float* coords, int N,
                                  const float* gauss_mat,  // [2, 128]
                                  float* out)              // [N, 256]
{
    for (int i = 0; i < N; i++) {
        float x = coords[i*2 + 0] * 2.f - 1.f;   // scale to [-1,1] then ×2π
        float y = coords[i*2 + 1] * 2.f - 1.f;
        // proj = coords @ gauss_mat  → [128]
        for (int d = 0; d < 128; d++) {
            float proj = (float)(2.0 * M_PI) *
                         (x * gauss_mat[0*128+d] + y * gauss_mat[1*128+d]);
            out[i*256 + d]       = std::sin(proj);
            out[i*256 + 128 + d] = std::cos(proj);
        }
    }
}

// ─────────────────────────────────────────────────────────────────
// Encode point prompts
// Returns tokens: [1, 1+1, 256]  (one point + one padding)
// ─────────────────────────────────────────────────────────────────
static void encode_points(const PromptEncoderW& pe,
                           float pt_x_norm, float pt_y_norm,
                           int label,    // 1=fg, 0=bg
                           float* out)  // [2, 256]  (point embed + not-a-point pad)
{
    // Point positional encoding [1, 256]
    float coord[2] = { pt_x_norm, pt_y_norm };
    float pe_feat[256];
    gaussian_pos_encoding(coord, 1, pe.gauss_matrix.data(), pe_feat);

    // Add point type embedding (label 0 or 1 → index 0 or 1)
    // point_embed[0] = background, point_embed[1] = foreground
    const float* type_embed = pe.point_embed[label].data();
    for (int d = 0; d < 256; d++) out[d] = pe_feat[d] + type_embed[d];

    // Padding token: not_a_point embed (at zero position)
    float zero_coord[2] = { 0.f, 0.f };
    float zero_pe[256];
    gaussian_pos_encoding(zero_coord, 1, pe.gauss_matrix.data(), zero_pe);
    for (int d = 0; d < 256; d++)
        out[256 + d] = zero_pe[d] + pe.not_a_point[d];
}

// ─────────────────────────────────────────────────────────────────
// Multi-head attention helper (used in mask decoder transformer)
// q: [N, Sq, C]  k: [N, Skv, C]  v: [N, Skv, C]
// qw[C,C] or different dims for cross-attn (internal_dim=128)
// ─────────────────────────────────────────────────────────────────
static void mha(const float* q, const float* k, const float* v,
                const LinearW& Wq, const LinearW& Wk, const LinearW& Wv,
                const LinearW& Wout,
                float* out,
                int N, int Sq, int Skv, int C_in_q, int C_in_kv, int C_out,
                int num_heads, int internal_dim)  // C_out = embed_dim
{
    int head_dim = internal_dim / num_heads;
    int M_q  = N * Sq;
    int M_kv = N * Skv;

    std::vector<float> Qq(M_q  * internal_dim);
    std::vector<float> Kk(M_kv * internal_dim);
    std::vector<float> Vv(M_kv * internal_dim);

    linear(q, Wq.w.data(), Wq.b.data(), Qq.data(), M_q,  internal_dim, C_in_q);
    linear(k, Wk.w.data(), Wk.b.data(), Kk.data(), M_kv, internal_dim, C_in_kv);
    linear(v, Wv.w.data(), Wv.b.data(), Vv.data(), M_kv, internal_dim, C_in_kv);

    // Reshape to [N, num_heads, S, head_dim]
    auto to_heads = [&](const std::vector<float>& src, int S) {
        std::vector<float> dst(N * num_heads * S * head_dim);
        for (int n = 0; n < N; n++)
            for (int s = 0; s < S; s++)
                for (int h = 0; h < num_heads; h++)
                    for (int d = 0; d < head_dim; d++)
                        dst[((n*num_heads+h)*S+s)*head_dim+d] =
                            src[(n*S+s)*internal_dim + h*head_dim + d];
        return dst;
    };

    auto Qh = to_heads(Qq, Sq);
    auto Kh = to_heads(Kk, Skv);
    auto Vh = to_heads(Vv, Skv);

    std::vector<float> attn_out(N * num_heads * Sq * head_dim);
    std::vector<float> attn_buf(N * num_heads * Sq * Skv);
    sdpa(Qh.data(), Kh.data(), Vh.data(),
         attn_out.data(), attn_buf.data(),
         N * num_heads, 1, Sq, Skv, head_dim);

    // Reassemble [N, Sq, internal_dim]
    std::vector<float> reassembled(M_q * internal_dim);
    for (int n = 0; n < N; n++)
        for (int s = 0; s < Sq; s++)
            for (int h = 0; h < num_heads; h++)
                for (int d = 0; d < head_dim; d++)
                    reassembled[(n*Sq+s)*internal_dim + h*head_dim + d] =
                        attn_out[((n*num_heads+h)*Sq+s)*head_dim+d];

    // Out projection: [N*Sq, C_out]
    linear(reassembled.data(), Wout.w.data(), Wout.b.data(),
           out, M_q, C_out, internal_dim);
}

// ─────────────────────────────────────────────────────────────────
// Mask Decoder forward
// img_embed: [1, 256, H_img, W_img] (from Hiera FPN, e.g. 64×64)
// feat0,1: [1,256,H,W] lower-resolution for upscaling
// point_tokens: [1, num_pts, 256]   (prompt tokens)
// Returns masks [4, H_img*4, W_img*4] and IoU [4] and obj_score
// ─────────────────────────────────────────────────────────────────
void run_mask_decoder(
    const SAM2& model,
    const float* img_embed,    int iH, int iW,   // 64x64
    const float* feat_s1,                        // 128x128 [1,256,128,128]
    const float* feat_s0,                        // 256x256 [1,256,256,256]
    const float* point_tokens, int num_pts,      // [1, num_pts, 256]
    // Output
    std::vector<float>& low_res_masks,   // [4, iH*4, iW*4]
    std::vector<float>& iou_preds,       // [4]
    float& obj_score)
{
    const MaskDecoderW& md = model.mask_dec;
    const int C = 256;
    const int embed_dim = 256;
    const int internal_dim = 128;  // cross-attn dim
    const int num_heads = 8;

    // ── Assemble output tokens: [iou, mask×4, obj_score] = 6 tokens ──
    // Concat with no_mem_embed → but here we just use the 6 output tokens
    // In the original: tokens = [iou_token, mask_tokens[0..3], obj_score_token]
    // Shape: [1, 6, 256]
    int n_out_tokens = 6;
    std::vector<float> out_tokens((size_t)n_out_tokens * C);
    // Copy iou_token
    std::memcpy(out_tokens.data() + 0*C, md.iou_token.data(), C*sizeof(float));
    // Copy mask_tokens 0..3
    for (int i = 0; i < 4; i++)
        std::memcpy(out_tokens.data() + (1+i)*C, md.mask_tokens[i].data(), C*sizeof(float));
    // Copy obj_score_token
    std::memcpy(out_tokens.data() + 5*C, md.obj_score_token.data(), C*sizeof(float));

    // Total query tokens: out_tokens + point_tokens
    int n_q = n_out_tokens + num_pts;
    std::vector<float> tokens((size_t)n_q * C);
    std::memcpy(tokens.data(), out_tokens.data(), n_out_tokens*C*sizeof(float));
    std::memcpy(tokens.data() + n_out_tokens*C, point_tokens, (size_t)num_pts*C*sizeof(float));

    // Image tokens: flatten img_embed [1,256,iH,iW] → [1, iH*iW, 256] NHWC
    int S_img = iH * iW;
    std::vector<float> img_tokens((size_t)S_img * C);
    for (int h = 0; h < iH; h++)
        for (int w = 0; w < iW; w++)
            for (int c = 0; c < C; c++)
                img_tokens[(h*iW+w)*C + c] = img_embed[(c*iH+h)*iW+w];

    // Also add positional encoding to img_tokens (use Gaussian PE on grid)
    {
        std::vector<float> grid_coords((size_t)S_img * 2);
        for (int h = 0; h < iH; h++)
            for (int w = 0; w < iW; w++) {
                grid_coords[(h*iW+w)*2+0] = (w + 0.5f) / iW;
                grid_coords[(h*iW+w)*2+1] = (h + 0.5f) / iH;
            }
        std::vector<float> img_pe((size_t)S_img * 256);
        gaussian_pos_encoding(grid_coords.data(), S_img,
                              model.prompt_enc.gauss_matrix.data(), img_pe.data());
        add_inplace(img_tokens.data(), img_pe.data(), S_img*C);
    }

    // ── 2-layer transformer ────────────────────────────────────────
    for (int layer = 0; layer < 2; layer++) {
        const auto& L = md.layers[layer];

        // 1. Self-attention on tokens [1, n_q, 256]
        {
            std::vector<float> tok_res(tokens);
            layer_norm(tokens.data(), L.norm1.w.data(), L.norm1.b.data(), n_q*C, C);

            // SA: q=k=v = tokens; [1, n_q, 256] × [256,256]
            // Use 8 heads, all projections [256,256], internal_dim=256
            std::vector<float> sa_out(n_q * C);
            mha(tokens.data(), tokens.data(), tokens.data(),
                L.sa_qkv[0], L.sa_qkv[1], L.sa_qkv[2], L.sa_out,
                sa_out.data(),
                1, n_q, n_q, C, C, C, num_heads, C);
            for (int i = 0; i < n_q*C; i++) tokens[i] = sa_out[i] + tok_res[i];
        }

        // 2. Cross-attention: tokens → image (token queries, image keys/values)
        //    dim: Q=[n_q,256], K/V=[S_img,256], internal=128
        {
            std::vector<float> tok_res(tokens);
            layer_norm(tokens.data(), L.norm2.w.data(), L.norm2.b.data(), n_q*C, C);

            std::vector<float> ca_out(n_q * C);
            mha(tokens.data(), img_tokens.data(), img_tokens.data(),
                L.t2i_q, L.t2i_k, L.t2i_v, L.t2i_out,
                ca_out.data(),
                1, n_q, S_img, C, C, C, num_heads, internal_dim);
            for (int i = 0; i < n_q*C; i++) tokens[i] = ca_out[i] + tok_res[i];
        }

        // 3. MLP on tokens
        {
            std::vector<float> tok_res(tokens);
            layer_norm(tokens.data(), L.norm3.w.data(), L.norm3.b.data(), n_q*C, C);

            std::vector<float> mlp1(n_q * 2048);
            linear(tokens.data(), L.mlp_fc1.w.data(), L.mlp_fc1.b.data(),
                   mlp1.data(), n_q, 2048, C);
            relu_inplace(mlp1.data(), n_q*2048);
            linear(mlp1.data(), L.mlp_fc2.w.data(), L.mlp_fc2.b.data(),
                   tokens.data(), n_q, C, 2048);
            for (int i = 0; i < n_q*C; i++) tokens[i] += tok_res[i];
        }

        // 4. Cross-attention: image → tokens (image queries, token keys/values)
        {
            // Update img_tokens (only for layer 0; both layers update independently)
            std::vector<float> img_res(img_tokens);
            // layer_norm on img_tokens
            std::vector<float> img_ln(img_tokens);
            layer_norm(img_ln.data(), L.norm4.w.data(), L.norm4.b.data(), S_img*C, C);

            std::vector<float> img_out(S_img * C);
            mha(img_ln.data(), tokens.data(), tokens.data(),
                L.i2t_q, L.i2t_k, L.i2t_v, L.i2t_out,
                img_out.data(),
                1, S_img, n_q, C, C, C, num_heads, internal_dim);
            for (int i = 0; i < S_img*C; i++) img_tokens[i] = img_out[i] + img_res[i];
        }
    }

    // Final cross-attention: tokens → image
    {
        std::vector<float> tok_res(tokens);
        // Apply final norm to tokens
        std::vector<float> tok_ln(tokens);
        layer_norm(tok_ln.data(), md.norm_final.w.data(), md.norm_final.b.data(), n_q*C, C);

        std::vector<float> fa_out(n_q * C);
        mha(tok_ln.data(), img_tokens.data(), img_tokens.data(),
            md.final_q, md.final_k, md.final_v, md.final_out,
            fa_out.data(),
            1, n_q, S_img, C, C, C, num_heads, internal_dim);
        for (int i = 0; i < n_q*C; i++) tokens[i] = fa_out[i] + tok_res[i];
    }

    // Extract output tokens: [1+4] mask tokens at indices 0..4
    // tokens[0]     = iou_token output
    // tokens[1..4]  = mask token outputs
    // tokens[5]     = obj_score token output

    // ── Output upscaling: img_embed [1,256,iH,iW] → [1,32,iH*4,iW*4] ──
    // ConvTranspose2d [256→64, kernel 2x2, stride 2] + LayerNorm + GELU
    // ConvTranspose2d [64→32, kernel 2x2, stride 2]
    // (s0,s1 FPN features also contribute via 1x1 convs)

    // First upsample: [1,256,64,64] → [1,64,128,128]
    Tensor up1({1, 64, iH*2, iW*2});
    conv_transpose2d_nchw(img_embed, up1.ptr(),
                          md.upscale.w0.data(), md.upscale.b0.data(),
                          1, 256, iH, iW, 64, 2, 2, 2, 2, 0, 0, 0, 0);

    // Add FPN feat_s1 projection [1,256,128,128] → [1,64,128,128]
    {
        std::vector<float> s1_proj((size_t)64*(iH*2)*(iW*2));
        conv2d_nchw(feat_s1, s1_proj.data(),
                    md.conv_s1_w.data(), md.conv_s1_b.data(),
                    1, 256, iH*2, iW*2, 64, 1, 1, 1, 1, 0, 0);
        add_inplace(up1.ptr(), s1_proj.data(), (size_t)64*(iH*2)*(iW*2));
    }

    // LayerNorm on channels (applied per-pixel: reshape [1,64,H,W] → [H*W, 64])
    {
        // Convert to NHWC, apply LN, convert back
        int M = iH*2, W2 = iW*2;
        std::vector<float> tmp_nhwc((size_t)M*W2*64);
        for (int c = 0; c < 64; c++)
            for (int h = 0; h < M; h++)
                for (int w = 0; w < W2; w++)
                    tmp_nhwc[(h*W2+w)*64+c] = up1.ptr()[(c*M+h)*W2+w];
        layer_norm(tmp_nhwc.data(), md.upscale.ln.w.data(), md.upscale.ln.b.data(),
                   M*W2*64, 64);
        gelu_inplace(tmp_nhwc.data(), M*W2*64);
        for (int c = 0; c < 64; c++)
            for (int h = 0; h < M; h++)
                for (int w = 0; w < W2; w++)
                    up1.ptr()[(c*M+h)*W2+w] = tmp_nhwc[(h*W2+w)*64+c];
    }

    // Second upsample: [1,64,128,128] → [1,32,256,256]
    Tensor up2({1, 32, iH*4, iW*4});
    conv_transpose2d_nchw(up1.ptr(), up2.ptr(),
                          md.upscale.w3.data(), md.upscale.b3.data(),
                          1, 64, iH*2, iW*2, 32, 2, 2, 2, 2, 0, 0, 0, 0);

    // Add FPN feat_s0 projection [1,256,256,256] → [1,32,256,256]
    {
        std::vector<float> s0_proj((size_t)32*(iH*4)*(iW*4));
        conv2d_nchw(feat_s0, s0_proj.data(),
                    md.conv_s0_w.data(), md.conv_s0_b.data(),
                    1, 256, iH*4, iW*4, 32, 1, 1, 1, 1, 0, 0);
        add_inplace(up2.ptr(), s0_proj.data(), (size_t)32*(iH*4)*(iW*4));
    }
    gelu_inplace(up2.ptr(), up2.numel());

    // up2: [1, 32, 256, 256]  (upscaled image feature)

    // ── Hypernetwork: produce mask outputs ──────────────────────
    // For each mask i: hyper_out[i] = MLP(mask_token[i])  → [32]
    // mask[i] = inner_product(hyper_out[i], up2.pixel) → [256, 256]
    low_res_masks.resize(4 * iH*4 * iW*4);
    for (int i = 0; i < 4; i++) {
        const float* tok_i = tokens.data() + (1+i)*C;
        // 3-layer MLP: 256→256→256→32 with ReLU
        std::vector<float> h0(256), h1(256), h2(32);
        linear(tok_i, md.hyper[i].l0.w.data(), md.hyper[i].l0.b.data(), h0.data(), 1, 256, 256);
        relu_inplace(h0.data(), 256);
        linear(h0.data(), md.hyper[i].l1.w.data(), md.hyper[i].l1.b.data(), h1.data(), 1, 256, 256);
        relu_inplace(h1.data(), 256);
        linear(h1.data(), md.hyper[i].l2.w.data(), md.hyper[i].l2.b.data(), h2.data(), 1, 32, 256);
        // Dot product with upscaled feature [32, H, W]
        int HW = iH*4 * iW*4;
        float* mask_out = low_res_masks.data() + i*HW;
        for (int p = 0; p < HW; p++) {
            float s = 0.f;
            for (int d = 0; d < 32; d++) {
                s += h2[d] * up2.ptr()[d*HW + p];
            }
            mask_out[p] = s;
        }
    }

    // ── IoU predictions ────────────────────────────────────────
    iou_preds.resize(4);
    // iou_token_out at index 0
    const float* iou_tok = tokens.data() + 0*C;
    std::vector<float> i0(256), i1(256), i2(4);
    linear(iou_tok, md.iou_l0.w.data(), md.iou_l0.b.data(), i0.data(), 1, 256, 256);
    relu_inplace(i0.data(), 256);
    linear(i0.data(), md.iou_l1.w.data(), md.iou_l1.b.data(), i1.data(), 1, 256, 256);
    relu_inplace(i1.data(), 256);
    linear(i1.data(), md.iou_l2.w.data(), md.iou_l2.b.data(), i2.data(), 1, 4, 256);
    for (int i = 0; i < 4; i++) iou_preds[i] = i2[i];

    // ── Obj score ──────────────────────────────────────────────
    const float* obj_tok = tokens.data() + 5*C;
    std::vector<float> o0(256), o1(256), o2(1);
    linear(obj_tok, md.obj_l0.w.data(), md.obj_l0.b.data(), o0.data(), 1, 256, 256);
    relu_inplace(o0.data(), 256);
    linear(o0.data(), md.obj_l1.w.data(), md.obj_l1.b.data(), o1.data(), 1, 256, 256);
    relu_inplace(o1.data(), 256);
    linear(o1.data(), md.obj_l2.w.data(), md.obj_l2.b.data(), o2.data(), 1, 1, 256);
    obj_score = o2[0];
}
