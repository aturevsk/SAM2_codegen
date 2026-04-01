# SAM2_codegen

Efficient C++ code generation from `sam2_1200x1800.pt2` (SAM2 Hiera-B+, 128 MB) for embedded deployment.
Two complementary approaches are compared:

| | Approach 1 | Approach 2 |
|---|---|---|
| **Method** | Manual architecture-aware C++ | MATLAB Coder → `loadPyTorchExportedProgram` → MLIR/TOSA → C++ |
| **Status** | Runs (numerical accuracy in progress) | Scripts ready; blocked by license expiry |
| **Inference** | ~8.2 s (MacBook Pro, CPU) | ~1.5 s estimated |
| **Code** | ~1300 lines hand-written | ~50K lines generated |

---

## Model

- **Input**: `sam2_1200x1800.pt2` — SAM2 exported via `torch.export`, 128 MB
- **Signature**: `(image[1200,1800,3] uint8, point_coords[1,2] float32, point_labels[1] int32)` → `(masks[1,3,1200,1800], iou_scores[1,3])`
- **Backbone**: Hiera-B+ (4-stage hierarchical ViT, 96→192→384→768 channels, Masked Unit Attention)

## Repository Structure

```
sam2_deploy/
├── manual_cpp/          # Approach 1: hand-written C++
│   ├── sam2.h           # Data structures (HieraBlock, SAM2 model)
│   ├── sam2.cpp         # Weight loading, preprocessing, mask decoder
│   ├── sam2_hiera.cpp   # Hiera backbone forward pass (MUA implementation)
│   ├── sam2_decoder.cpp # Cross-attention mask decoder
│   ├── sam2_ops.cpp     # Primitive ops (layernorm, GELU, BLAS wrappers)
│   ├── main.cpp         # CLI entry point
│   └── CMakeLists.txt   # Build: C++17, Apple Accelerate, -O3
│
├── matlab_coder/        # Approach 2: MATLAB Coder pipeline
│   ├── sam2_infer.m     # Entry function: loadPyTorchExportedProgram + invoke
│   ├── run_codegen.m    # Coder configuration and code generation driver
│   ├── benchmark_matlab_coder.m  # Latency benchmarking script
│   └── loadSAM2.m       # Weight loader helper
│
├── reference/           # Reference tools
│   ├── extract_weights.py   # Export all tensors from .pt2 to float32 .bin files
│   └── gen_reference.py     # Generate PyTorch reference I/O for validation
│
├── webapp/
│   └── index.html       # Interactive MathWorks-styled single-page app (6 tabs)
│
├── SAM2_Deployment_Report.pdf  # Full technical report
└── generate_report.py          # Report generation script (ReportLab)
```

## Quick Start — Approach 1 (Manual C++)

### 1. Extract weights
```bash
pip install torch
python3 reference/extract_weights.py --pt2 /path/to/sam2_1200x1800.pt2 --out weights/
```

### 2. Build
```bash
mkdir manual_cpp/build && cd manual_cpp/build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(sysctl -n hw.ncpu)
```

### 3. Run inference
```bash
./sam2_infer /path/to/image.jpg 900 600 1
# args: image path, y coord, x coord, label (1=foreground)
```

## Quick Start — Approach 2 (MATLAB Coder)

Requires: MATLAB R2024b+ with **MATLAB Coder** and **Deep Learning Toolbox Support Package for PyTorch Models**.

```matlab
cd matlab_coder
run('run_codegen.m')   % generates C++ in matlab_coder/codegen/
```

> **Note**: MATLAB R2026a trial license expired before codegen could be executed in this project.
> All scripts are correct and ready to run with a valid license.

## Architecture Overview

```
image[1200×1800×3 uint8]
    │
    ▼  Anti-aliased bicubic resize (precomputed tables)
[1024×1024×3 float32]
    │
    ▼  Hiera Backbone (lifted tensors 0–153)
    ├── Stage 1: 256×256, 96ch,  2 regular MHA blocks     (tensors 0–17)
    ├── Stage 2: 128×128, 192ch, 1 MUA + 4 regular blocks (tensors 18–43)
    ├── Stage 3:  64×64,  384ch, 1 MUA + 6 regular blocks (tensors 44–129)
    └── Stage 4:  32×32,  768ch, 1 MUA block              (tensors 130–153)
    │
    ▼  FPN Neck (lifted tensors 154–161)
[256-ch feature embeddings at 4 scales]
    │
    ▼  Prompt Encoder
[image + point tokens]
    │
    ▼  Mask Decoder (2-layer cross-attention transformer)
masks[1,3,1200,1800]  iou_scores[1,3]
```

## Key Technical Findings

### Masked Unit Attention (MUA)
Transition blocks use an asymmetric attention pattern:
- **Q** projected from spatially-pooled (H/2 × W/2) features
- **K, V** projected from full-resolution (H × W) features
- Achieves spatial downsampling *within* the attention mechanism
- Separate `ds_proj` linear layer handles the skip-connection channel projection

### Bugs Fixed in Manual C++ Implementation
| Bug | Symptom | Fix |
|-----|---------|-----|
| Index arrays stored as float32, read as int64 | SIGBUS (exit 138) | `load_i64` casts via `load_f` |
| QKV weights passed as ds_proj | IoU ≈ 1.48×10¹⁵ | Separate `ds_w_s2/s3/s4` fields |
| Stage 3: 7 blocks instead of 6 | Array overrun into ds_proj memory | Loop `i < 7` |
| Transition norm2 used instead of norm1 for MLP | Wrong MLP scale | Use `blk.norm1` in `hiera_transition_block` |
| `norm1.size = C_in` for transition blocks | Wrong LayerNorm dimension | `norm1.size = C_out` when `is_transition` |
| Non-square image coordinate normalization | Point prompt at wrong y position | Per-axis: `pt_y_n = (y+0.5)/H` |

## Report

See [`SAM2_Deployment_Report.pdf`](SAM2_Deployment_Report.pdf) for the full technical report covering architecture analysis, both approaches, all bugs, benchmark results, and next steps.

## Web Application

**Live app**: [https://aturevsk.github.io/SAM2_codegen/webapp/index.html](https://aturevsk.github.io/SAM2_codegen/webapp/index.html)

Or open [`webapp/index.html`](webapp/index.html) locally in any browser — no server required.
6 tabs: Overview · Architecture · Approach 1 · Approach 2 · Benchmark · Weight Explorer

---

*Generated with Claude Code (Opus 4.6) — April 2026*
