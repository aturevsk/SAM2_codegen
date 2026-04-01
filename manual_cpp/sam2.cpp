// SAM2 model — weight loading and full forward pass
#include "sam2.h"
#include <iostream>
#include <cstring>

// Forward declarations
void run_hiera(const SAM2& model, const float* img_nchw,
               Tensor& feat0, Tensor& feat1, Tensor& feat2, Tensor& feat3);
void run_mask_decoder(const SAM2& model,
                      const float* img_embed, int iH, int iW,
                      const float* feat_s1, const float* feat_s0,
                      const float* point_tokens, int num_pts,
                      std::vector<float>& low_res_masks,
                      std::vector<float>& iou_preds, float& obj_score);

// ─────────────────────────────────────────────────────────────────
// Weight-loading helpers
// ─────────────────────────────────────────────────────────────────

static std::vector<float> load_f(const std::string& dir, const std::string& name) {
    std::string path = dir + "/" + name + ".bin";
    std::ifstream f(path, std::ios::binary);
    if (!f) throw std::runtime_error("Missing weight: " + path);
    f.seekg(0, std::ios::end);
    size_t bytes = f.tellg();
    f.seekg(0);
    std::vector<float> buf(bytes / sizeof(float));
    f.read(reinterpret_cast<char*>(buf.data()), bytes);
    return buf;
}

// Index buffers are extracted as float32 (extract_weights.py converts everything to float).
// Load as float then cast to int64.
static std::vector<int64_t> load_i64(const std::string& dir, const std::string& name) {
    auto floats = load_f(dir, name);
    std::vector<int64_t> result(floats.size());
    for (size_t i = 0; i < floats.size(); i++) result[i] = (int64_t)floats[i];
    return result;
}

static LinearW load_linear(const std::string& dir, const std::string& w_name,
                            const std::string& b_name, int out_f, int in_f) {
    LinearW lw;
    lw.in_f = in_f; lw.out_f = out_f;
    lw.w = load_f(dir, w_name);
    lw.b = load_f(dir, b_name);
    return lw;
}

static NormW load_norm(const std::string& dir, const std::string& prefix, int size) {
    NormW nw;
    nw.size = size;
    nw.w = load_f(dir, prefix + "weight");
    nw.b = load_f(dir, prefix + "bias");
    return nw;
}

// Load a Hiera block given the lifted_tensor indices for the block's weights.
// Each block needs: qkv_w[idx], qkv_b[idx+1], out_w[idx+2], out_b[idx+3],
//                  norm1_w[idx+4], norm1_b[idx+5], fc1_w[idx+6], fc1_b[idx+7],
//                  fc2_w[idx+8], fc2_b[idx+9], norm2_w[idx+10], norm2_b[idx+11]
static HieraBlock load_hiera_block(const std::string& dir,
                                   int lifted_start,
                                   int C_in, int C_out, int heads,
                                   int win_h, int win_w,
                                   bool is_transition)
{
    HieraBlock blk;
    blk.C_in = C_in; blk.C_out = C_out;
    blk.heads = heads;
    blk.win_h = win_h; blk.win_w = win_w;
    blk.is_transition = is_transition;

    auto lt = [&](int i) { return "c_sam2_lifted_tensor_" + std::to_string(lifted_start + i); };

    int qkv_out = is_transition ? 3*C_out : 3*C_out;

    blk.qkv.w = load_f(dir, lt(0));
    blk.qkv.b = load_f(dir, lt(1));
    blk.qkv.in_f  = C_in;
    blk.qkv.out_f = qkv_out;

    blk.out_proj.w = load_f(dir, lt(2));
    blk.out_proj.b = load_f(dir, lt(3));
    blk.out_proj.in_f  = C_out;
    blk.out_proj.out_f = C_out;

    blk.norm1.w = load_f(dir, lt(4));
    blk.norm1.b = load_f(dir, lt(5));
    // For regular blocks norm1 operates on C_in (pre-attention norm).
    // For transition blocks the attention has no pre-norm; norm1 (at offset 4-5)
    // is the post-add, pre-MLP norm operating on C_out features.
    blk.norm1.size = is_transition ? C_out : C_in;

    blk.fc1.w = load_f(dir, lt(6));
    blk.fc1.b = load_f(dir, lt(7));
    blk.fc1.in_f = C_out;
    blk.fc1.out_f = 4*C_out;

    blk.fc2.w = load_f(dir, lt(8));
    blk.fc2.b = load_f(dir, lt(9));
    blk.fc2.in_f = 4*C_out;
    blk.fc2.out_f = C_out;

    blk.norm2.w = load_f(dir, lt(10));
    blk.norm2.b = load_f(dir, lt(11));
    blk.norm2.size = C_out;

    return blk;
}

// ─────────────────────────────────────────────────────────────────
// SAM2::load — load all weights from binary directory
// ─────────────────────────────────────────────────────────────────
void SAM2::load(const std::string& dir) {
    std::cout << "Loading SAM2 weights from: " << dir << "\n";

    // ── Preprocessing buffers ────────────────────────────────────
    pixel_mean = load_f(dir, "b_pixel_mean");    // [1,3,1,1] = 3 values
    pixel_std  = load_f(dir, "b_pixel_std");
    aa_idx_w = load_i64(dir, "b_aa_idx_w");      // [1024, 4]
    aa_wt_w  = load_f(dir, "b_aa_wt_w");
    aa_idx_h = load_i64(dir, "b_aa_idx_h");      // [1024, 3]
    aa_wt_h  = load_f(dir, "b_aa_wt_h");

    // ── Patch embed ──────────────────────────────────────────────
    pe_conv_w   = load_f(dir, "c_sam2_lifted_tensor_0");
    pe_conv_b   = load_f(dir, "c_sam2_lifted_tensor_1");
    pe_pos_7x7  = load_f(dir, "c_sam2_lifted_tensor_2");
    pe_pos_8x8  = load_f(dir, "c_sam2_lifted_tensor_3");
    pe_norm.w   = load_f(dir, "c_sam2_lifted_tensor_4");
    pe_norm.b   = load_f(dir, "c_sam2_lifted_tensor_5");
    pe_norm.size = 96;

    // ── Stage 1: 1 block, 96ch, window=8x8, 1 head ──────────────
    // Tensors 6-17 (12 tensors)
    s1_blocks[0] = load_hiera_block(dir, 6,  96, 96, 1, 8, 8, false);

    // Pre-stage-2 norm (applied in transition block for skip connection)
    // Tensors 10-11 are norm1 of s1_blocks[0] (applied before attention)
    // s1_out_norm is the separate norm before downsampling projection
    // Looking at graph: layer_norm_2 uses lifted_tensor_16,17 → that's norm2 of block0
    // The downsampling proj norm (before linear_4) uses a fresh layer_norm.
    // In our weight file, s1_out_norm corresponds to lifting the norm at the
    // "output" of stage 1 (before PatchMerge). From the graph: layer_norm_2
    // is norm2 of block 0 at tensors 16,17.
    // The actual stage-end norm for PatchMerge uses tensors right before linear_4.
    // In the graph trace: node 70 = layer_norm_2 uses tensors 16,17 (norm2 of s1_blk0)
    // Node 71 = linear_4 uses tensor 18 for projection 96→192.
    // So s1_out_norm = s1_blocks[0].norm2 (they share the same weights).
    s1_out_norm = s1_blocks[0].norm2;

    // ── Stage 2: transition (96→192) + 1 regular block ──────────
    // Transition block (MUA): tensors 18-29
    //   18: ds_proj_w [192,96], 19: ds_proj_b [192]
    //   20-29: qkv,out,norm1,fc1,fc2,norm2 for the MUA attention
    // Wait - in stage 2 transition:
    //   Tensor 18: [192,96] = downsampling projection (ds_w)
    //   Tensor 19: [192]    = ds_b
    //   Tensor 20: [576,96] = qkv_w for MUA block (from stage1 windows)
    //   Tensor 21: [576]
    //   Tensor 22: [192,192] = out_proj_w
    //   Tensor 23: [192]
    //   Tensor 24: [192] = norm_attn_w (but this is for MLP norm_out)
    //   Actually re-reading graph: after MUA attn, skip+residual → layer_norm_3
    //   layer_norm_3 uses tensors 24,25 → norm of the output of MUA block
    //   Then linear_7 [768,192] = fc1 of MLP (tensors 26,27)
    //   linear_8 [192,768] = fc2 (tensors 28,29)
    //   norm2 of this block = 30,31
    // Hmm that would be tensors 24-31 for norm1+mlp+norm2 = 8 tensors
    // And tensors 20-23 for qkv+out = 4 tensors
    // But the block also needs attention norm (norm1) before qkv
    // Let me re-check: in hiera_transition_block, I apply ds_norm before the skip,
    // and norm2 before the MLP. The attention itself doesn't have a pre-norm
    // because in Hiera the transition block normalises differently.
    // For simplicity, I'll use norm1 as a dummy (identity) for the transition block's
    // attention norm (since the graph shows no explicit norm before the MUA qkv).
    // The MUA block output adds directly to the pooled skip.

    // For the transition block, I store ds_w/b in qkv (re-used as pointers passed to
    // hiera_transition_block). Let me load them separately:
    // We'll put ds_w in a separate field by reusing C++ struct slots.
    // Actually let me re-examine the transition block weights more carefully.
    // From the graph:
    //   node 70: layer_norm_2 [tensors 16,17] → applied to s1 output NHWC [1,256,256,96]
    //   node 71: linear_4 [tensor 18: [192,96], tensor 19: [192]] → [1,256,256,192]
    //   node 72-73: permute + max_pool2d → skip [1,128,128,192]
    //   node 75-78: window x (256,256,96) → linear_5 [tensor 20: [576,96]] → MUA qkv
    //   ...
    //   node 95: linear_6 [tensor 22: [192,192]] → out_proj
    //   node 99: add → residual (attn output + skip)
    //   node 100: layer_norm_3 [tensors 24,25] → MLP norm
    //   node 101: linear_7 [tensors 26,27] → fc1
    //   node 103: linear_8 [tensors 28,29] → fc2
    //   node 104: add → MLP residual

    // So transition block layout (tensors from 20):
    //   20-21: qkv_w, qkv_b  [576,96], [576]
    //   22-23: out_proj_w, out_proj_b  [192,192], [192]
    //   24-25: norm1_w, norm1_b  [192] (actually this is post-add norm before MLP)
    //   26-27: fc1_w, fc1_b  [768,192], [768]
    //   28-29: fc2_w, fc2_b  [192,768], [192]
    //   30-31: norm2_w, norm2_b  [192]
    // And ds proj uses 18-19.

    // Downsampling projection for stage 1→2 skip path (tensors 18-19)
    ds_w_s2 = load_f(dir, "c_sam2_lifted_tensor_18");  // [192, 96]
    ds_b_s2 = load_f(dir, "c_sam2_lifted_tensor_19");  // [192]

    // Stage 2 MUA transition block: qkv from tensor 20 (NOT 18!)
    // Tensors 20-31: qkv,out_proj,norm1(pre-MLP),fc1,fc2,norm2
    s2_blocks[0] = load_hiera_block(dir, 20,  96, 192, 2, 8, 8, true);

    // Stage 2 regular block: tensors 32-43
    s2_blocks[1] = load_hiera_block(dir, 32,  192, 192, 2, 4, 4, false);

    // s2_out_norm = norm applied to s2 output before downsampling projection.
    // Graph: layer_norm_6 [tensors 36,37] = norm1 of s2_blocks[1].
    s2_out_norm = s2_blocks[1].norm1;

    // ── Stage 3: transition (192→384) + 6 regular blocks ────────
    // Tensors 44-45: ds_proj for stage 2→3 skip path
    ds_w_s3 = load_f(dir, "c_sam2_lifted_tensor_44");  // [384, 192]
    ds_b_s3 = load_f(dir, "c_sam2_lifted_tensor_45");  // [384]

    // Stage 3 MUA transition: tensors 46-57
    s3_blocks[0] = load_hiera_block(dir, 46,  192, 384, 4, 4, 4, true);

    // 6 regular 384ch blocks: tensors 58..58+6*12-1 = 58..129
    for (int i = 1; i < 7; i++) {
        s3_blocks[i] = load_hiera_block(dir, 58 + (i-1)*12,  384, 384, 4, 4, 4, false);
    }
    // s3_out_norm: norm1 of s3_blocks[6] (last regular, start=118), tensors 122-123
    s3_out_norm = s3_blocks[6].norm1;

    // ── Stage 4: transition (384→768) + 1 regular block ─────────
    // Tensors 130-131: ds_proj for stage 3→4 skip path
    ds_w_s4 = load_f(dir, "c_sam2_lifted_tensor_130");  // [768, 384]
    ds_b_s4 = load_f(dir, "c_sam2_lifted_tensor_131");  // [768]

    // Stage 4 MUA transition: tensors 132-143
    s4_blocks[0] = load_hiera_block(dir, 132,  384, 768, 8, 4, 4, true);

    // Stage 4 regular block: tensors 144-155
    s4_blocks[1] = load_hiera_block(dir, 144,  768, 768, 8, 4, 4, false);

    // ── FPN Neck ─────────────────────────────────────────────────
    // Tensors 154-161: (but 154 = after s4 regular block's tensors end at 155)
    // Wait, s4_blocks[1] uses 144-155 (12 tensors). Next = 156.
    // From our trace: 154=[256,768,1,1], 155=[256], 156=[256,384,1,1], ...
    // So neck starts at 154 - but s4_blocks[1] ends at 155.
    // Let me re-check: s4_blocks[1] start=144, 12 tensors → indices 144-155.
    // And tensor 154 = [256,768,1,1] is the first neck conv.
    // These OVERLAP! Tensor 154 can't be in both.
    // Re-examining: s4 transition = 132-143 (12 tensors), s4 regular = 144-155 (12 tensors).
    // But tensor 154=[256,768,1,1] is in range of s4_regular (which ends at 155).
    // Contradiction unless the MLP has different size.
    // Let me re-read: for 768ch block: fc1=[3072,768], fc2=[768,3072], norm=[768,768]
    //   144: qkv_w [2304,768] (8 heads, 3*768=2304 but wait: 3*8*96=2304 ✓)
    //   145: qkv_b [2304]
    //   146: out_proj_w [768,768]
    //   147: out_proj_b [768]
    //   148-149: norm1 [768]
    //   150-151: fc1 [3072,768], fc1_b (4*768=3072)
    //   152-153: fc2 [768,3072], fc2_b
    //   (norm2 would be 154-155 but tensor 154=[256,768,1,1] is neck conv!)
    // So the 768ch regular block only has 12 tensors starting at 144:
    //   144-145: qkv
    //   146-147: out_proj
    //   148-149: norm1
    //   150-151: fc1
    //   152-153: fc2
    //   154-155: norm2? But 154=[256,768,1,1] is the neck!
    // This means the regular block at stage 4 only has 10 parameter tensors
    // (no norm2 since the MLP norm is the final output norm, or there's no post-MLP norm).
    // OR the 768ch stage has no MLP (only attention + linear)?
    // Looking at graph nodes around linear_49-50 (fc2 of s4_regular):
    //   node ~151: linear_50 [152,153] → [1,32,32,768]
    //   (then immediately: neck projections using 154,155,156,...,161)
    // So s4_blocks[1] MLP has no post-norm (or norm is fused differently).

    // Fix: load s4_blocks[1] with only 10 tensors (no norm2)
    // For simplicity in the forward pass, we'll use identity norm for norm2.
    {
        auto lt = [&](int i) { return "c_sam2_lifted_tensor_" + std::to_string(144 + i); };
        HieraBlock& blk = s4_blocks[1];
        blk.C_in = 768; blk.C_out = 768;
        blk.heads = 8; blk.win_h = 4; blk.win_w = 4;
        blk.is_transition = false;
        blk.qkv.w = load_f(dir, lt(0)); blk.qkv.b = load_f(dir, lt(1));
        blk.qkv.in_f = 768; blk.qkv.out_f = 3*768;
        blk.out_proj.w = load_f(dir, lt(2)); blk.out_proj.b = load_f(dir, lt(3));
        blk.out_proj.in_f = blk.out_proj.out_f = 768;
        blk.norm1.w = load_f(dir, lt(4)); blk.norm1.b = load_f(dir, lt(5)); blk.norm1.size=768;
        blk.fc1.w = load_f(dir, lt(6)); blk.fc1.b = load_f(dir, lt(7));
        blk.fc1.in_f = 768; blk.fc1.out_f = 4*768;
        blk.fc2.w = load_f(dir, lt(8)); blk.fc2.b = load_f(dir, lt(9));
        blk.fc2.in_f = 4*768; blk.fc2.out_f = 768;
        // No norm2 – use trivial (identity)
        blk.norm2.w.assign(768, 1.f);
        blk.norm2.b.assign(768, 0.f);
        blk.norm2.size = 768;
    }

    // FPN: tensors 154-161
    neck.w[0] = load_f(dir, "c_sam2_lifted_tensor_154");
    neck.b[0] = load_f(dir, "c_sam2_lifted_tensor_155");
    neck.w[1] = load_f(dir, "c_sam2_lifted_tensor_156");
    neck.b[1] = load_f(dir, "c_sam2_lifted_tensor_157");
    neck.w[2] = load_f(dir, "c_sam2_lifted_tensor_158");
    neck.b[2] = load_f(dir, "c_sam2_lifted_tensor_159");
    neck.w[3] = load_f(dir, "c_sam2_lifted_tensor_160");
    neck.b[3] = load_f(dir, "c_sam2_lifted_tensor_161");

    // ── Prompt Encoder ───────────────────────────────────────────
    for (int i = 0; i < 4; i++)
        prompt_enc.point_embed[i] = load_f(dir,
            "p_sam2_prompt_encoder_point_embeddings_" + std::to_string(i) + "_weight");
    // flatten [1,256] → [256]
    prompt_enc.not_a_point = load_f(dir, "p_sam2_prompt_encoder_not_a_point_embed_weight");
    prompt_enc.gauss_matrix = load_f(dir, "b_sam2_prompt_encoder_pe_layer_positional_encoding_gaussian_matrix");

    // ── Mask Decoder ─────────────────────────────────────────────
    mask_dec.no_mem_embed   = load_f(dir, "p_sam2_no_mem_embed");
    mask_dec.iou_token      = load_f(dir, "p_sam2_mask_decoder_iou_token_weight");
    mask_dec.obj_score_token= load_f(dir, "p_sam2_mask_decoder_obj_score_token_weight");
    for (int i = 0; i < 4; i++)
        mask_dec.mask_tokens[i] = load_f(dir,
            "p_sam2_mask_decoder_mask_tokens_weight");  // loaded as [4,256], we'll split
    // Actually mask_tokens is stored as [4,256]; load once, split
    {
        auto all = load_f(dir, "p_sam2_mask_decoder_mask_tokens_weight");
        for (int i = 0; i < 4; i++) {
            mask_dec.mask_tokens[i].assign(all.begin() + i*256, all.begin() + (i+1)*256);
        }
    }

    auto load_tf_layer = [&](MaskDecoderW::TfLayer& L, const std::string& pfx) {
        // Self-attn
        L.sa_qkv[0] = load_linear(dir,
            pfx+"self_attn_q_proj_weight", pfx+"self_attn_q_proj_bias", 256, 256);
        L.sa_qkv[1] = load_linear(dir,
            pfx+"self_attn_k_proj_weight", pfx+"self_attn_k_proj_bias", 256, 256);
        L.sa_qkv[2] = load_linear(dir,
            pfx+"self_attn_v_proj_weight", pfx+"self_attn_v_proj_bias", 256, 256);
        L.sa_out = load_linear(dir,
            pfx+"self_attn_out_proj_weight", pfx+"self_attn_out_proj_bias", 256, 256);
        L.norm1 = load_norm(dir, pfx+"norm1_", 256);
        // Cross-attn token→image (internal_dim=128)
        L.t2i_q = load_linear(dir,
            pfx+"cross_attn_token_to_image_q_proj_weight",
            pfx+"cross_attn_token_to_image_q_proj_bias", 128, 256);
        L.t2i_k = load_linear(dir,
            pfx+"cross_attn_token_to_image_k_proj_weight",
            pfx+"cross_attn_token_to_image_k_proj_bias", 128, 256);
        L.t2i_v = load_linear(dir,
            pfx+"cross_attn_token_to_image_v_proj_weight",
            pfx+"cross_attn_token_to_image_v_proj_bias", 128, 256);
        L.t2i_out = load_linear(dir,
            pfx+"cross_attn_token_to_image_out_proj_weight",
            pfx+"cross_attn_token_to_image_out_proj_bias", 256, 128);
        L.norm2 = load_norm(dir, pfx+"norm2_", 256);
        // MLP 256→2048→256
        L.mlp_fc1 = load_linear(dir,
            pfx+"mlp_layers_0_weight", pfx+"mlp_layers_0_bias", 2048, 256);
        L.mlp_fc2 = load_linear(dir,
            pfx+"mlp_layers_1_weight", pfx+"mlp_layers_1_bias", 256, 2048);
        L.norm3 = load_norm(dir, pfx+"norm3_", 256);
        // Cross-attn image→token
        L.i2t_q = load_linear(dir,
            pfx+"cross_attn_image_to_token_q_proj_weight",
            pfx+"cross_attn_image_to_token_q_proj_bias", 128, 256);
        L.i2t_k = load_linear(dir,
            pfx+"cross_attn_image_to_token_k_proj_weight",
            pfx+"cross_attn_image_to_token_k_proj_bias", 128, 256);
        L.i2t_v = load_linear(dir,
            pfx+"cross_attn_image_to_token_v_proj_weight",
            pfx+"cross_attn_image_to_token_v_proj_bias", 128, 256);
        L.i2t_out = load_linear(dir,
            pfx+"cross_attn_image_to_token_out_proj_weight",
            pfx+"cross_attn_image_to_token_out_proj_bias", 256, 128);
        L.norm4 = load_norm(dir, pfx+"norm4_", 256);
    };

    load_tf_layer(mask_dec.layers[0],
        "p_sam2_mask_decoder_transformer_layers_0_");
    load_tf_layer(mask_dec.layers[1],
        "p_sam2_mask_decoder_transformer_layers_1_");

    // Final attn
    mask_dec.final_q = load_linear(dir,
        "p_sam2_mask_decoder_transformer_final_attn_token_to_image_q_proj_weight",
        "p_sam2_mask_decoder_transformer_final_attn_token_to_image_q_proj_bias", 128, 256);
    mask_dec.final_k = load_linear(dir,
        "p_sam2_mask_decoder_transformer_final_attn_token_to_image_k_proj_weight",
        "p_sam2_mask_decoder_transformer_final_attn_token_to_image_k_proj_bias", 128, 256);
    mask_dec.final_v = load_linear(dir,
        "p_sam2_mask_decoder_transformer_final_attn_token_to_image_v_proj_weight",
        "p_sam2_mask_decoder_transformer_final_attn_token_to_image_v_proj_bias", 128, 256);
    mask_dec.final_out = load_linear(dir,
        "p_sam2_mask_decoder_transformer_final_attn_token_to_image_out_proj_weight",
        "p_sam2_mask_decoder_transformer_final_attn_token_to_image_out_proj_bias", 256, 128);
    mask_dec.norm_final = load_norm(dir, "p_sam2_mask_decoder_transformer_norm_final_attn_", 256);

    // Output upscaling
    mask_dec.upscale.w0 = load_f(dir, "p_sam2_mask_decoder_output_upscaling_0_weight");
    mask_dec.upscale.b0 = load_f(dir, "p_sam2_mask_decoder_output_upscaling_0_bias");
    mask_dec.upscale.ln.w = load_f(dir, "p_sam2_mask_decoder_output_upscaling_1_weight");
    mask_dec.upscale.ln.b = load_f(dir, "p_sam2_mask_decoder_output_upscaling_1_bias");
    mask_dec.upscale.ln.size = 64;
    mask_dec.upscale.w3 = load_f(dir, "p_sam2_mask_decoder_output_upscaling_3_weight");
    mask_dec.upscale.b3 = load_f(dir, "p_sam2_mask_decoder_output_upscaling_3_bias");

    // FPN s0, s1 conv
    mask_dec.conv_s0_w = load_f(dir, "p_sam2_mask_decoder_conv_s0_weight");
    mask_dec.conv_s0_b = load_f(dir, "p_sam2_mask_decoder_conv_s0_bias");
    mask_dec.conv_s1_w = load_f(dir, "p_sam2_mask_decoder_conv_s1_weight");
    mask_dec.conv_s1_b = load_f(dir, "p_sam2_mask_decoder_conv_s1_bias");

    // Hypernetwork MLPs
    for (int i = 0; i < 4; i++) {
        std::string p = "p_sam2_mask_decoder_output_hypernetworks_mlps_" + std::to_string(i) + "_layers_";
        mask_dec.hyper[i].l0 = load_linear(dir, p+"0_weight", p+"0_bias", 256, 256);
        mask_dec.hyper[i].l1 = load_linear(dir, p+"1_weight", p+"1_bias", 256, 256);
        mask_dec.hyper[i].l2 = load_linear(dir, p+"2_weight", p+"2_bias", 32, 256);
    }

    // IoU prediction head
    mask_dec.iou_l0 = load_linear(dir,
        "p_sam2_mask_decoder_iou_prediction_head_layers_0_weight",
        "p_sam2_mask_decoder_iou_prediction_head_layers_0_bias", 256, 256);
    mask_dec.iou_l1 = load_linear(dir,
        "p_sam2_mask_decoder_iou_prediction_head_layers_1_weight",
        "p_sam2_mask_decoder_iou_prediction_head_layers_1_bias", 256, 256);
    mask_dec.iou_l2 = load_linear(dir,
        "p_sam2_mask_decoder_iou_prediction_head_layers_2_weight",
        "p_sam2_mask_decoder_iou_prediction_head_layers_2_bias", 4, 256);

    // Obj score head
    mask_dec.obj_l0 = load_linear(dir,
        "p_sam2_mask_decoder_pred_obj_score_head_layers_0_weight",
        "p_sam2_mask_decoder_pred_obj_score_head_layers_0_bias", 256, 256);
    mask_dec.obj_l1 = load_linear(dir,
        "p_sam2_mask_decoder_pred_obj_score_head_layers_1_weight",
        "p_sam2_mask_decoder_pred_obj_score_head_layers_1_bias", 256, 256);
    mask_dec.obj_l2 = load_linear(dir,
        "p_sam2_mask_decoder_pred_obj_score_head_layers_2_weight",
        "p_sam2_mask_decoder_pred_obj_score_head_layers_2_bias", 1, 256);

    std::cout << "Weights loaded.\n";
}

// ─────────────────────────────────────────────────────────────────
// SAM2::forward
// ─────────────────────────────────────────────────────────────────
void SAM2::forward(const uint8_t* img_hwc, int H, int W,
                   float pt_x, float pt_y, int label,
                   std::vector<float>& masks_out,
                   std::vector<float>& iou_out)
{
    // 1. Preprocess: uint8 → float → /255 → aa-resize → normalise → NCHW
    std::vector<float> img_f((size_t)H*W*3);
    for (size_t i = 0; i < (size_t)H*W*3; i++) img_f[i] = img_hwc[i] / 255.f;

    // Extract pixel_mean/std from [1,3,1,1] stored as 4 floats per channel
    float pm[3], ps[3];
    for (int c = 0; c < 3; c++) {
        pm[c] = pixel_mean[c];
        ps[c] = pixel_std[c];
    }

    Tensor img_nchw = aa_resize_1024(img_f.data(),
                                     aa_idx_w.data(), aa_wt_w.data(), 1024,
                                     aa_idx_h.data(), aa_wt_h.data(), 1024,
                                     pm, ps);

    // 2. Hiera encoder → 4-scale FPN features
    Tensor feat0, feat1, feat2, feat3;
    run_hiera(*this, img_nchw.ptr(), feat0, feat1, feat2, feat3);

    // 3. Prompt encoder: encode point
    // The exported model normalizes point coords by the original image dimensions.
    // SAM2 prompt encoder: coords_norm = (coords + 0.5) / image_size (H or W).
    // The aa_resize stretches each axis independently (no aspect ratio preservation),
    // so normalization must be done per-axis using original H and W.
    float pt_x_n = (pt_x + 0.5f) / W;   // = 600.5 / 1800 ≈ 0.334
    float pt_y_n = (pt_y + 0.5f) / H;   // = 900.5 / 1200 ≈ 0.750

    // Point tokens + padding: 2 tokens [2, 256]
    float point_tokens[2 * 256];
    // Re-use encode_points from decoder translation unit
    extern void encode_point_tokens(const PromptEncoderW&, float, float, int, float*);

    // Inline the encoding here:
    {
        const PromptEncoderW& pe = prompt_enc;
        // Token 0: actual point
        float coord[2] = { pt_x_n, pt_y_n };
        float pe_feat[256];
        // Gaussian PE
        for (int d = 0; d < 128; d++) {
            float proj = (float)(2.0 * M_PI) *
                (coord[0] * pe.gauss_matrix[d] + coord[1] * pe.gauss_matrix[128+d]);
            pe_feat[d]     = std::sin(proj);
            pe_feat[128+d] = std::cos(proj);
        }
        const float* type_embed = pe.point_embed[label].data();
        for (int d = 0; d < 256; d++) point_tokens[d] = pe_feat[d] + type_embed[d];

        // Token 1: not-a-point padding
        float zero_coord[2] = {0.f, 0.f};
        for (int d = 0; d < 128; d++) {
            float proj = (float)(2.0 * M_PI) *
                (zero_coord[0] * pe.gauss_matrix[d] + zero_coord[1] * pe.gauss_matrix[128+d]);
            pe_feat[d]     = std::sin(proj);
            pe_feat[128+d] = std::cos(proj);
        }
        for (int d = 0; d < 256; d++)
            point_tokens[256+d] = pe_feat[d] + pe.not_a_point[d];
    }

    // 4. Mask decoder
    // Use feat2 (64×64) as the primary image embedding for the decoder
    std::vector<float> low_res_masks;
    std::vector<float> iou_preds;
    float obj_score;

    run_mask_decoder(*this,
                     feat2.ptr(), 64, 64,
                     feat1.ptr(),   // 128×128
                     feat0.ptr(),   // 256×256
                     point_tokens, 2,
                     low_res_masks, iou_preds, obj_score);

    // 5. Select best 3 masks (indices 0,1,2 of the 4) and upsample to H×W
    // low_res_masks: [4, 256, 256]
    int LH = 256, LW = 256;
    masks_out.resize(3 * H * W);
    for (int i = 0; i < 3; i++) {
        const float* lm = low_res_masks.data() + i * LH * LW;
        float* mo = masks_out.data() + i * H * W;
        // Bilinear upsample [1, 1, LH, LW] → [1, 1, H, W]
        upsample_bilinear_nchw(lm, mo, 1, 1, LH, LW, H, W);
    }

    iou_out.resize(3);
    for (int i = 0; i < 3; i++) iou_out[i] = iou_preds[i];
}
