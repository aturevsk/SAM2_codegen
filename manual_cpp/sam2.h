#pragma once
// SAM2 Manual C++ Inference — 1200×1800 → 3 masks
// Hiera backbone (96→192→384→768) + Prompt Encoder + Mask Decoder
// Uses Accelerate/BLAS for GEMM; no other external dependencies.

#include <cstdint>
#include <cstddef>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <cassert>
#include <chrono>
#include <numeric>

#ifdef __APPLE__
  #include <Accelerate/Accelerate.h>
  #define HAS_BLAS 1
#endif

// ─────────────────────────────────────────────────────────────────
// Tensor: contiguous float32, row-major, up to 5-D
// ─────────────────────────────────────────────────────────────────
struct Tensor {
    std::vector<float> data;
    std::vector<int>   dims;

    Tensor() = default;
    Tensor(std::initializer_list<int> d) : dims(d) {
        data.assign(numel(), 0.f);
    }
    explicit Tensor(const std::vector<int>& d) : dims(d) {
        data.assign(numel(), 0.f);
    }

    size_t numel() const {
        size_t n = 1;
        for (int d : dims) n *= (size_t)d;
        return n;
    }
    int ndim() const { return (int)dims.size(); }
    float* ptr() { return data.data(); }
    const float* ptr() const { return data.data(); }

    // Load raw float32 binary
    static Tensor from_bin(const std::string& path, std::vector<int> d) {
        Tensor t(d);
        std::ifstream f(path, std::ios::binary);
        if (!f) throw std::runtime_error("Cannot open: " + path);
        f.read(reinterpret_cast<char*>(t.data.data()), t.numel()*sizeof(float));
        if (!f) throw std::runtime_error("Read failed: " + path);
        return t;
    }
    static Tensor from_bin_u8(const std::string& path, std::vector<int> d) {
        // uint8 binary → float32
        size_t n = 1;
        for (int x : d) n *= x;
        std::vector<uint8_t> raw(n);
        std::ifstream f(path, std::ios::binary);
        if (!f) throw std::runtime_error("Cannot open: " + path);
        f.read(reinterpret_cast<char*>(raw.data()), n);
        Tensor t(d);
        for (size_t i = 0; i < n; i++) t.data[i] = (float)raw[i];
        return t;
    }
    static Tensor from_bin_i32(const std::string& path, std::vector<int> d) {
        size_t n = 1;
        for (int x : d) n *= x;
        std::vector<int32_t> raw(n);
        std::ifstream f(path, std::ios::binary);
        if (!f) throw std::runtime_error("Cannot open: " + path);
        f.read(reinterpret_cast<char*>(raw.data()), n*4);
        Tensor t(d);
        for (size_t i = 0; i < n; i++) t.data[i] = (float)raw[i];
        return t;
    }
};

// ─────────────────────────────────────────────────────────────────
// Primitive ops
// ─────────────────────────────────────────────────────────────────

// sgemm wrapper: C = alpha*A*B^T + beta*C
// A: [M,K], B: [N,K] (row-major), C: [M,N]
inline void gemm_nt(const float* A, const float* B, float* C,
                    int M, int N, int K,
                    float alpha = 1.f, float beta = 0.f) {
#ifdef HAS_BLAS
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasTrans,
                M, N, K, alpha, A, K, B, K, beta, C, N);
#else
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            float s = 0.f;
            for (int k = 0; k < K; k++) s += A[i*K+k] * B[j*K+k];
            C[i*N+j] = alpha*s + beta*C[i*N+j];
        }
    }
#endif
}

// Linear: x[M,K] → out[M,N]  (w: [N,K], b: [N])
inline void linear(const float* x, const float* w, const float* b,
                   float* out, int M, int N, int K) {
    gemm_nt(x, w, out, M, N, K);
    if (b) {
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
                out[i*N+j] += b[j];
    }
}

// LayerNorm: normalise last dimension of shape [..., norm_size]
inline void layer_norm(float* x, const float* w, const float* b,
                       int total, int norm_size, float eps = 1e-6f) {
    int rows = total / norm_size;
    for (int r = 0; r < rows; r++) {
        float* row = x + (size_t)r * norm_size;
        float mean = 0.f, var = 0.f;
        for (int i = 0; i < norm_size; i++) mean += row[i];
        mean /= norm_size;
        for (int i = 0; i < norm_size; i++) { float d = row[i]-mean; var += d*d; }
        var /= norm_size;
        float inv_std = 1.f / std::sqrt(var + eps);
        if (w && b) {
            for (int i = 0; i < norm_size; i++)
                row[i] = (row[i]-mean)*inv_std * w[i] + b[i];
        } else {
            for (int i = 0; i < norm_size; i++)
                row[i] = (row[i]-mean)*inv_std;
        }
    }
}

// In-place activations
inline void gelu_inplace(float* x, int n) {
    for (int i = 0; i < n; i++) {
        float v = x[i];
        x[i] = 0.5f * v * (1.f + std::tanh(0.7978845608f*(v + 0.044715f*v*v*v)));
    }
}
inline void relu_inplace(float* x, int n) {
    for (int i = 0; i < n; i++) if (x[i] < 0.f) x[i] = 0.f;
}
inline void sigmoid_inplace(float* x, int n) {
    for (int i = 0; i < n; i++) x[i] = 1.f / (1.f + std::exp(-x[i]));
}
inline void add_inplace(float* a, const float* b, int n) {
    for (int i = 0; i < n; i++) a[i] += b[i];
}
inline void mul_inplace(float* a, const float* b, int n) {
    for (int i = 0; i < n; i++) a[i] *= b[i];
}

// Softmax over last dim: x[rows, cols]
inline void softmax_rows(float* x, int rows, int cols) {
    for (int r = 0; r < rows; r++) {
        float* row = x + (size_t)r * cols;
        float mx = *std::max_element(row, row+cols);
        float s = 0.f;
        for (int i = 0; i < cols; i++) { row[i] = std::exp(row[i]-mx); s += row[i]; }
        float inv = 1.f / s;
        for (int i = 0; i < cols; i++) row[i] *= inv;
    }
}

// Scaled dot-product attention (causal=false)
// q: [B,H,Sq,D]  k: [B,H,Skv,D]  v: [B,H,Skv,D]  out: [B,H,Sq,D]
void sdpa(const float* q, const float* k, const float* v,
          float* out_buf, float* attn_buf,
          int B, int H, int Sq, int Skv, int D);

// Conv2d (NCHW): out[N,Oc,Oh,Ow]
void conv2d_nchw(const float* in, float* out,
                 const float* w, const float* b,
                 int N, int C, int H, int W,
                 int Oc, int kH, int kW,
                 int strH, int strW, int padH, int padW,
                 int groups = 1);

// ConvTranspose2d (NCHW): upsample path
void conv_transpose2d_nchw(const float* in, float* out,
                           const float* w, const float* b,
                           int N, int C, int H, int W,
                           int Oc, int kH, int kW,
                           int strH, int strW, int padH, int padW,
                           int out_padH, int out_padW);

// MaxPool2d (NCHW)
void maxpool2d_nchw(const float* in, float* out,
                    int N, int C, int H, int W,
                    int kH, int kW, int strH, int strW);

// Bilinear upsample (NCHW)
void upsample_bilinear_nchw(const float* in, float* out,
                            int N, int C, int iH, int iW,
                            int oH, int oW);

// Bicubic upsample (NCHW)
void upsample_bicubic_nchw(const float* in, float* out,
                           int N, int C, int iH, int iW,
                           int oH, int oW);

// Nearest upsample (NCHW)
void upsample_nearest_nchw(const float* in, float* out,
                           int N, int C, int iH, int iW,
                           int oH, int oW);

// Anti-aliased resize using precomputed index/weight tables
// img: [H_in, W_in, 3] float (NHWC after /255), returns [1, 3, 1024, 1024]
Tensor aa_resize_1024(const float* img_hwc,
                      const int64_t* idx_w, const float* wt_w, int n_idx_w, // [1024,4]
                      const int64_t* idx_h, const float* wt_h, int n_idx_h, // [1024,3]
                      const float* pixel_mean, const float* pixel_std);

// ─────────────────────────────────────────────────────────────────
// Weight structs
// ─────────────────────────────────────────────────────────────────

struct LinearW { std::vector<float> w, b; int in_f, out_f; };
struct NormW   { std::vector<float> w, b; int size; };

struct HieraBlock {
    // Attention
    LinearW qkv;   // [3*C_out, C_in]  (may differ if transition block)
    LinearW out_proj; // [C_out, C_out]
    NormW   norm1;
    // MLP
    LinearW fc1;   // [4*C, C]
    LinearW fc2;   // [C, 4*C]
    NormW   norm2;
    // Block config
    int C_in, C_out, heads;
    int win_h, win_w;
    bool is_transition; // MUA block: Q is pooled 2x spatially
};

struct HieraNeck {
    // 1x1 conv for each scale: 768→256, 384→256, 192→256, 96→256
    std::vector<float> w[4], b[4]; // indexed 0=scale3(768ch), 1=scale2(384ch), 2=scale1(192ch), 3=scale0(96ch)
};

struct PromptEncoderW {
    // Point embeddings: 4 embeddings [1,256] + not_a_point [1,256]
    std::vector<float> point_embed[4];   // each [256]
    std::vector<float> not_a_point;      // [256]
    // Gaussian matrix for pos encoding: [2,128]
    std::vector<float> gauss_matrix;     // [2,128] = 256 floats
    // Mask downscaling (not used in single-click mode but kept for completeness)
    // (omitted – unused in no-mask-input path)
};

struct MaskDecoderW {
    // Special tokens: iou_token [1,256], mask_tokens [4,256], obj_score_token [1,256]
    std::vector<float> iou_token;           // [256]
    std::vector<float> mask_tokens[4];      // [4][256]
    std::vector<float> obj_score_token;     // [256]
    std::vector<float> no_mem_embed;        // [1,1,256] = [256]

    // Transformer: 2 layers
    struct TfLayer {
        // Self-attn: Q/K/V all [256,256], out [256,256]
        LinearW sa_qkv[3];   // q_proj, k_proj, v_proj  each [256,256]
        LinearW sa_out;
        NormW   norm1;
        // Cross-attn token-to-image: q,k,v [128,256] (internal_dim=128), out [256,128]
        LinearW t2i_q, t2i_k, t2i_v, t2i_out;
        NormW   norm2;
        // MLP: 256→2048→256
        LinearW mlp_fc1, mlp_fc2;
        NormW   norm3;
        // Cross-attn image-to-token (same dims)
        LinearW i2t_q, i2t_k, i2t_v, i2t_out;
        NormW   norm4;
    } layers[2];

    // Final attn token-to-image
    LinearW final_q, final_k, final_v, final_out;
    NormW   norm_final;

    // Output upscaling: ConvTranspose 256→64 (2x2,s2) + LayerNorm(64) + ConvTranspose 64→32 (2x2,s2)
    struct {
        std::vector<float> w0,b0;  // ConvTranspose [256,64,2,2]
        NormW ln;
        std::vector<float> w3,b3;  // ConvTranspose [64,32,2,2] (index 3 because LayerNorm is idx 1)
    } upscale;

    // Hypernetwork MLPs: 4 mask output heads, each 256→256→256→32
    struct HyperMLP {
        LinearW l0, l1, l2;  // [256,256],[256,256],[32,256]
    } hyper[4];

    // IoU prediction head: 256→256→256→4
    LinearW iou_l0, iou_l1, iou_l2;

    // Obj score head: 256→256→256→1
    LinearW obj_l0, obj_l1, obj_l2;

    // FPN conv s0,s1: [32,256,1,1], [64,256,1,1]
    std::vector<float> conv_s0_w, conv_s0_b;  // [32,256]
    std::vector<float> conv_s1_w, conv_s1_b;  // [64,256]
};

// ─────────────────────────────────────────────────────────────────
// SAM2 model
// ─────────────────────────────────────────────────────────────────
struct SAM2 {
    // Preprocessing buffers (from model's buffers)
    std::vector<float>   pixel_mean, pixel_std;  // [1,3,1,1]
    std::vector<int64_t> aa_idx_w, aa_idx_h;     // [1024,4] and [1024,3]
    std::vector<float>   aa_wt_w,  aa_wt_h;      // same shape

    // Hiera backbone weights
    // Patch embed
    std::vector<float> pe_conv_w, pe_conv_b;   // [96,3,7,7], [96]
    std::vector<float> pe_pos_7x7, pe_pos_8x8; // [1,96,7,7], [1,96,8,8]
    NormW pe_norm;

    // Blocks (in graph order)
    // Stage 1: 1 regular block (96ch)
    HieraBlock s1_blocks[1];
    // Stage 2: 1 transition block (96→192ch) + 1 regular block (192ch)
    HieraBlock s2_blocks[2];
    // Stage 3: 1 transition block (192→384ch) + 6 regular blocks (384ch)
    HieraBlock s3_blocks[7];
    // Stage 4: 1 transition block (384→768ch) + 1 regular block (768ch)
    HieraBlock s4_blocks[2];
    // Stage output norms (applied before FPN) — used as ds_norm in skip path
    NormW s1_out_norm, s2_out_norm, s3_out_norm;  // pre-pool norms
    // Downsampling projection weights for each transition (separate from block qkv)
    std::vector<float> ds_w_s2, ds_b_s2;  // [192, 96], [192]   tensors 18-19
    std::vector<float> ds_w_s3, ds_b_s3;  // [384, 192], [384]  tensors 44-45
    std::vector<float> ds_w_s4, ds_b_s4;  // [768, 384], [768]  tensors 130-131

    HieraNeck neck;

    PromptEncoderW prompt_enc;
    MaskDecoderW   mask_dec;

    // ──── API ────────────────────────────────────────────────────
    void load(const std::string& weight_dir);

    // Run full inference.
    // img: [H,W,3] uint8 raw pixels
    // pt_x, pt_y: point coordinate in original image (float)
    // label: 1=foreground, 0=background
    // masks_out: [3, H, W] float (low-res logits, bilinear-upsampled)
    // iou_out:   [3] float
    void forward(const uint8_t* img_hwc, int H, int W,
                 float pt_x, float pt_y, int label,
                 std::vector<float>& masks_out,
                 std::vector<float>& iou_out);
};
