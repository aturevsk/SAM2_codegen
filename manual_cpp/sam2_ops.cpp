// SAM2 primitive ops implementation
#include "sam2.h"
#include <cstring>
#include <climits>

// ─────────────────────────────────────────────────────────────────
// Scaled dot-product attention
// q: [B,H,Sq,D]  k: [B,H,Skv,D]  v: [B,H,Skv,D]  out: [B,H,Sq,D]
// attn_buf: scratch [B,H,Sq,Skv]
// ─────────────────────────────────────────────────────────────────
void sdpa(const float* q, const float* k, const float* v,
          float* out_buf, float* attn_buf,
          int B, int H, int Sq, int Skv, int D)
{
    float scale = 1.f / std::sqrt((float)D);
    // For each (b,h) pair: attn[Sq,Skv] = softmax(q[Sq,D] * k[Skv,D]^T * scale)
    //                      out[Sq,D]    = attn[Sq,Skv] * v[Skv,D]
    for (int b = 0; b < B; b++) {
        for (int h = 0; h < H; h++) {
            const float* Qbh = q + ((size_t)b*H + h) * Sq  * D;
            const float* Kbh = k + ((size_t)b*H + h) * Skv * D;
            const float* Vbh = v + ((size_t)b*H + h) * Skv * D;
            float*       Obh = out_buf + ((size_t)b*H + h) * Sq  * D;
            float*       Abh = attn_buf + ((size_t)b*H + h) * Sq * Skv;

            // Attn scores: Q * K^T  [Sq, Skv]
            gemm_nt(Qbh, Kbh, Abh, Sq, Skv, D, scale, 0.f);
            // Softmax row-wise
            softmax_rows(Abh, Sq, Skv);
            // Output: Attn * V  [Sq, D]
            // Attn[Sq,Skv] * V[Skv,D] → Out[Sq,D]  (normal mm, not transposed)
#ifdef HAS_BLAS
            cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                        Sq, D, Skv, 1.f, Abh, Skv, Vbh, D, 0.f, Obh, D);
#else
            for (int i = 0; i < Sq; i++) {
                for (int d = 0; d < D; d++) {
                    float s = 0.f;
                    for (int j = 0; j < Skv; j++) s += Abh[i*Skv+j] * Vbh[j*D+d];
                    Obh[i*D+d] = s;
                }
            }
#endif
        }
    }
}

// ─────────────────────────────────────────────────────────────────
// Conv2d NCHW
// ─────────────────────────────────────────────────────────────────
void conv2d_nchw(const float* in, float* out,
                 const float* w, const float* b,
                 int N, int C, int H, int W,
                 int Oc, int kH, int kW,
                 int strH, int strW, int padH, int padW,
                 int groups)
{
    int oH = (H + 2*padH - kH) / strH + 1;
    int oW = (W + 2*padW - kW) / strW + 1;
    int Cg = C / groups;      // in-channels per group
    int Ocg = Oc / groups;    // out-channels per group

    for (int n = 0; n < N; n++) {
        for (int g = 0; g < groups; g++) {
            for (int oc = 0; oc < Ocg; oc++) {
                int oc_abs = g * Ocg + oc;
                float bias_val = b ? b[oc_abs] : 0.f;
                for (int oh = 0; oh < oH; oh++) {
                    for (int ow = 0; ow < oW; ow++) {
                        float sum = bias_val;
                        for (int ic = 0; ic < Cg; ic++) {
                            int ic_abs = g * Cg + ic;
                            for (int kh = 0; kh < kH; kh++) {
                                int ih = oh*strH - padH + kh;
                                if (ih < 0 || ih >= H) continue;
                                for (int kw = 0; kw < kW; kw++) {
                                    int iw = ow*strW - padW + kw;
                                    if (iw < 0 || iw >= W) continue;
                                    float x = in[((n*C + ic_abs)*H + ih)*W + iw];
                                    float fw = w[((oc_abs*(C/groups) + ic)*kH + kh)*kW + kw];
                                    sum += x * fw;
                                }
                            }
                        }
                        out[((n*Oc + oc_abs)*oH + oh)*oW + ow] = sum;
                    }
                }
            }
        }
    }
}

// ─────────────────────────────────────────────────────────────────
// ConvTranspose2d NCHW
// ─────────────────────────────────────────────────────────────────
void conv_transpose2d_nchw(const float* in, float* out,
                           const float* w, const float* b,
                           int N, int C, int H, int W,
                           int Oc, int kH, int kW,
                           int strH, int strW, int padH, int padW,
                           int out_padH, int out_padW)
{
    int oH = (H-1)*strH - 2*padH + kH + out_padH;
    int oW = (W-1)*strW - 2*padW + kW + out_padW;
    size_t out_size = (size_t)N*Oc*oH*oW;
    std::fill(out, out+out_size, 0.f);
    if (b) {
        for (int n = 0; n < N; n++)
            for (int oc = 0; oc < Oc; oc++)
                for (int i = 0; i < oH*oW; i++)
                    out[((n*Oc+oc)*oH)*oW + i] = b[oc]; // filled below
        // re-zero and set bias properly
        for (int n = 0; n < N; n++)
            for (int oc = 0; oc < Oc; oc++) {
                float bv = b[oc];
                float* o = out + (n*Oc+oc)*(size_t)oH*oW;
                for (int i = 0; i < oH*oW; i++) o[i] = bv;
            }
    } else {
        std::fill(out, out+out_size, 0.f);
    }
    // w: [C, Oc, kH, kW]
    for (int n = 0; n < N; n++) {
        for (int c = 0; c < C; c++) {
            for (int ih = 0; ih < H; ih++) {
                for (int iw = 0; iw < W; iw++) {
                    float val = in[((n*C+c)*H+ih)*W+iw];
                    for (int oc = 0; oc < Oc; oc++) {
                        for (int kh = 0; kh < kH; kh++) {
                            int oh = ih*strH - padH + kh;
                            if (oh < 0 || oh >= oH) continue;
                            for (int kw = 0; kw < kW; kw++) {
                                int ow = iw*strW - padW + kw;
                                if (ow < 0 || ow >= oW) continue;
                                out[((n*Oc+oc)*oH+oh)*oW+ow] +=
                                    val * w[((c*Oc+oc)*kH+kh)*kW+kw];
                            }
                        }
                    }
                }
            }
        }
    }
}

// ─────────────────────────────────────────────────────────────────
// MaxPool2d NCHW
// ─────────────────────────────────────────────────────────────────
void maxpool2d_nchw(const float* in, float* out,
                    int N, int C, int H, int W,
                    int kH, int kW, int strH, int strW)
{
    int oH = (H - kH) / strH + 1;
    int oW = (W - kW) / strW + 1;
    for (int n = 0; n < N; n++) {
        for (int c = 0; c < C; c++) {
            for (int oh = 0; oh < oH; oh++) {
                for (int ow = 0; ow < oW; ow++) {
                    float mx = -1e38f;
                    for (int kh = 0; kh < kH; kh++) {
                        for (int kw = 0; kw < kW; kw++) {
                            float v = in[((n*C+c)*H + oh*strH+kh)*W + ow*strW+kw];
                            if (v > mx) mx = v;
                        }
                    }
                    out[((n*C+c)*oH+oh)*oW+ow] = mx;
                }
            }
        }
    }
}

// ─────────────────────────────────────────────────────────────────
// Bilinear upsample NCHW
// ─────────────────────────────────────────────────────────────────
void upsample_bilinear_nchw(const float* in, float* out,
                            int N, int C, int iH, int iW,
                            int oH, int oW)
{
    float scH = (float)iH / oH;
    float scW = (float)iW / oW;
    for (int n = 0; n < N; n++) {
        for (int c = 0; c < C; c++) {
            const float* src = in + (n*C+c)*(size_t)iH*iW;
            float*       dst = out + (n*C+c)*(size_t)oH*oW;
            for (int oh = 0; oh < oH; oh++) {
                float fy = (oh + 0.5f)*scH - 0.5f;
                int y0 = std::max(0, (int)fy);
                int y1 = std::min(iH-1, y0+1);
                float dy = fy - y0; if (dy < 0) dy = 0;
                for (int ow = 0; ow < oW; ow++) {
                    float fx = (ow + 0.5f)*scW - 0.5f;
                    int x0 = std::max(0, (int)fx);
                    int x1 = std::min(iW-1, x0+1);
                    float dx = fx - x0; if (dx < 0) dx = 0;
                    float v = src[y0*iW+x0]*(1-dy)*(1-dx)
                            + src[y0*iW+x1]*(1-dy)*dx
                            + src[y1*iW+x0]*dy*(1-dx)
                            + src[y1*iW+x1]*dy*dx;
                    dst[oh*oW+ow] = v;
                }
            }
        }
    }
}

// ─────────────────────────────────────────────────────────────────
// Bicubic upsample NCHW
// ─────────────────────────────────────────────────────────────────
static float cubic_weight(float t) {
    // Mitchell-Netravali (a=-0.75 as PyTorch default)
    float at = std::abs(t);
    if (at < 1.f) return 1.5f*at*at*at - 2.5f*at*at + 1.f;
    if (at < 2.f) return -0.5f*at*at*at + 2.5f*at*at - 4.f*at + 2.f;
    return 0.f;
}
void upsample_bicubic_nchw(const float* in, float* out,
                           int N, int C, int iH, int iW,
                           int oH, int oW)
{
    float scH = (float)iH / oH;
    float scW = (float)iW / oW;
    for (int n = 0; n < N; n++) {
        for (int c = 0; c < C; c++) {
            const float* src = in + (n*C+c)*(size_t)iH*iW;
            float*       dst = out + (n*C+c)*(size_t)oH*oW;
            for (int oh = 0; oh < oH; oh++) {
                float fy = (oh + 0.5f)*scH - 0.5f;
                int y_ctr = (int)std::floor(fy);
                for (int ow = 0; ow < oW; ow++) {
                    float fx = (ow + 0.5f)*scW - 0.5f;
                    int x_ctr = (int)std::floor(fx);
                    float s = 0.f, wsum = 0.f;
                    for (int dy = -1; dy <= 2; dy++) {
                        int iy = std::max(0, std::min(iH-1, y_ctr+dy));
                        float wy = cubic_weight(fy - (y_ctr+dy));
                        for (int dx = -1; dx <= 2; dx++) {
                            int ix = std::max(0, std::min(iW-1, x_ctr+dx));
                            float wx = cubic_weight(fx - (x_ctr+dx));
                            s    += src[iy*iW+ix] * wy * wx;
                            wsum += wy * wx;
                        }
                    }
                    dst[oh*oW+ow] = s / (wsum + 1e-8f);
                }
            }
        }
    }
}

// ─────────────────────────────────────────────────────────────────
// Nearest upsample NCHW
// ─────────────────────────────────────────────────────────────────
void upsample_nearest_nchw(const float* in, float* out,
                           int N, int C, int iH, int iW,
                           int oH, int oW)
{
    for (int n = 0; n < N; n++) {
        for (int c = 0; c < C; c++) {
            const float* src = in + (n*C+c)*(size_t)iH*iW;
            float*       dst = out + (n*C+c)*(size_t)oH*oW;
            for (int oh = 0; oh < oH; oh++) {
                int iy = (int)std::floor((float)oh / oH * iH);
                iy = std::max(0, std::min(iH-1, iy));
                for (int ow = 0; ow < oW; ow++) {
                    int ix = (int)std::floor((float)ow / oW * iW);
                    ix = std::max(0, std::min(iW-1, ix));
                    dst[oh*oW+ow] = src[iy*iW+ix];
                }
            }
        }
    }
}

// ─────────────────────────────────────────────────────────────────
// Anti-aliased resize to 1024x1024 using precomputed tables
// img_hwc: [H_in, W_in, 3] float  (after /255)
// idx_w: [1024, 4]  (int64 indices into width axis)
// wt_w:  [1024, 4]  (weights)
// idx_h: [1024, 3]  (int64 indices into height axis)
// wt_h:  [1024, 3]  (weights)
// Returns: [1, 3, 1024, 1024] normalised NCHW
// ─────────────────────────────────────────────────────────────────
Tensor aa_resize_1024(const float* img_hwc,
                      const int64_t* idx_w, const float* wt_w, int /*n_idx_w*/,
                      const int64_t* idx_h, const float* wt_h, int /*n_idx_h*/,
                      const float* pixel_mean, const float* pixel_std)
{
    // Step 1: horizontal pass  [H_in, 1024, 3]
    // We don't know H_in here directly, but the caller provides idx/wt derived from a
    // specific H,W.  We'll do both passes in one shot via intermediate buffer.
    // idx_w has shape [1024, 4], covering 1800-wide input.
    // idx_h has shape [1024, 3], covering 1200-high input.

    const int OUT = 1024;
    const int IW_SRC = 1800;  // width of the aa_resize source
    const int IH_SRC = 1200;  // height
    const int C3 = 3;

    // Intermediate: [IH_SRC, OUT, 3] – horizontal resampling
    std::vector<float> tmp((size_t)IH_SRC * OUT * C3);
    for (int h = 0; h < IH_SRC; h++) {
        for (int ow = 0; ow < OUT; ow++) {
            for (int c = 0; c < C3; c++) {
                float s = 0.f;
                // n_w = 4 weights
                for (int k = 0; k < 4; k++) {
                    int64_t ix = idx_w[ow*4 + k];
                    float   wt = wt_w[ow*4 + k];
                    s += img_hwc[(h*IW_SRC + ix)*C3 + c] * wt;
                }
                tmp[(h*OUT + ow)*C3 + c] = s;
            }
        }
    }

    // Output: [1, 3, OUT, OUT] NCHW
    Tensor out({1, C3, OUT, OUT});
    float* dst = out.ptr();

    for (int oh = 0; oh < OUT; oh++) {
        for (int ow = 0; ow < OUT; ow++) {
            for (int c = 0; c < C3; c++) {
                float s = 0.f;
                // n_h = 3 weights
                for (int k = 0; k < 3; k++) {
                    int64_t iy = idx_h[oh*3 + k];
                    float   wt = wt_h[oh*3 + k];
                    s += tmp[(iy*OUT + ow)*C3 + c] * wt;
                }
                // Normalise: (x - mean) / std
                float mean_c = pixel_mean[c];
                float std_c  = pixel_std[c];
                dst[(c*OUT + oh)*OUT + ow] = (s - mean_c) / std_c;
            }
        }
    }
    return out;
}
