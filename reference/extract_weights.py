"""
Extract all weights from sam2_1200x1800.pt2 to binary files.
Also traces the graph to map lifted_tensor indices to their usage context,
so the manual C++ implementation can load them by architecture position.
"""

import os
import struct
import torch
import numpy as np
from collections import defaultdict

PT2_PATH = "/Users/arkadiyturevskiy/Documents/Claude/Coder_Models/Hard/sam2_1200x1800.pt2"
OUT_DIR  = "/Users/arkadiyturevskiy/Documents/Claude/Coder_Models/Hard/sam2_deploy/weights"
os.makedirs(OUT_DIR, exist_ok=True)

print("Loading model...")
ep = torch.export.load(PT2_PATH)
gm = ep.graph_module

# ── 1. Dump all placeholders (params + buffers + constants) ─────────────────
print("\n=== Extracting tensors ===")
tensors_saved = {}

for node in gm.graph.nodes:
    if node.op != "placeholder":
        continue
    if "val" not in node.meta:
        continue
    val = node.meta["val"]
    if not isinstance(val, torch.Tensor):
        continue

    name = node.name   # e.g. p_sam2_mask_decoder_iou_token_weight
    shape = list(val.shape)
    dtype = val.dtype

    # Retrieve actual data from state_dict or constants
    data = None
    # Check state_dict (params + buffers)
    sd = ep.state_dict
    if isinstance(sd, dict):
        # Parameter/buffer names use dots (from graph_signature targets)
        for spec in ep.graph_signature.input_specs:
            if spec.arg.name == name and hasattr(spec, "target") and spec.target:
                key = spec.target
                if key in sd:
                    data = sd[key]
                    break

    # Check constants dict
    if data is None:
        consts = ep.constants
        if isinstance(consts, dict):
            for spec in ep.graph_signature.input_specs:
                if spec.arg.name == name and hasattr(spec, "target") and spec.target:
                    key = spec.target
                    if key in consts:
                        data = consts[key]
                        break

    if data is None:
        print(f"  WARN: could not find data for {name} {shape}")
        continue

    # Save as float32 binary
    arr = data.detach().float().cpu().numpy()
    fname = name + ".bin"
    fpath = os.path.join(OUT_DIR, fname)
    arr.tofile(fpath)
    tensors_saved[name] = {"shape": shape, "dtype": str(dtype), "file": fname}

print(f"Saved {len(tensors_saved)} tensors.")

# ── 2. Write a manifest JSON for use by C++ loader ───────────────────────────
import json
manifest_path = os.path.join(OUT_DIR, "manifest.json")
with open(manifest_path, "w") as f:
    json.dump(tensors_saved, f, indent=2)
print(f"Manifest written to {manifest_path}")

# ── 3. Trace graph: map lifted_tensor_N to first call_function that uses it ──
print("\n=== Tracing lifted_tensor usage ===")
node_map = {n.name: n for n in gm.graph.nodes}
lifted_usage = {}

for node in gm.graph.nodes:
    if node.op == "placeholder" and node.name.startswith("c_sam2_lifted_tensor_"):
        idx = int(node.name.split("_")[-1])
        # Find first downstream call_function
        for user in node.users:
            if user.op == "call_function":
                lifted_usage[idx] = {
                    "name": node.name,
                    "shape": list(node.meta["val"].shape) if "val" in node.meta else [],
                    "first_use_op": str(user.target),
                    "first_use_name": user.name,
                }
                break

usage_path = os.path.join(OUT_DIR, "lifted_tensor_usage.json")
with open(usage_path, "w") as f:
    json.dump(lifted_usage, f, indent=2)
print(f"Lifted tensor usage written ({len(lifted_usage)} tensors) to {usage_path}")

# ── 4. Generate reference outputs for validation ─────────────────────────────
print("\n=== Generating reference output ===")
torch.manual_seed(42)

# Use a synthetic image
img = torch.randint(0, 256, (1200, 1800, 3), dtype=torch.uint8)
pt_coords = torch.tensor([[600.0, 900.0]], dtype=torch.float32)
pt_labels = torch.tensor([1], dtype=torch.int32)

# Build input dict matching signature
inputs = {}
for node in gm.graph.nodes:
    if node.op == "placeholder" and "val" in node.meta:
        val = node.meta["val"]
        if not isinstance(val, torch.Tensor):
            continue
        name = node.name
        kind_str = ""
        for spec in ep.graph_signature.input_specs:
            if spec.arg.name == name:
                kind_str = str(spec.kind)
                break
        if "USER_INPUT" in kind_str:
            if name == "image_hwc_u8":
                inputs[name] = img
            elif name == "point_coords":
                inputs[name] = pt_coords
            elif name == "point_labels":
                inputs[name] = pt_labels

print(f"Running inference with inputs: { {k: v.shape for k,v in inputs.items()} }")
try:
    with torch.no_grad():
        out = ep.module()(**inputs)
    ref_dir = "/Users/arkadiyturevskiy/Documents/Claude/Coder_Models/Hard/sam2_deploy/reference"
    for i, o in enumerate(out if isinstance(out, (list, tuple)) else [out]):
        arr = o.float().cpu().numpy()
        fpath = os.path.join(ref_dir, f"ref_output_{i}.bin")
        arr.tofile(fpath)
        print(f"  Output {i}: shape={arr.shape}, dtype={arr.dtype} → {fpath}")
    # Save input too
    img.numpy().tofile(os.path.join(ref_dir, "ref_input_image.bin"))
    pt_coords.numpy().tofile(os.path.join(ref_dir, "ref_input_coords.bin"))
    pt_labels.numpy().tofile(os.path.join(ref_dir, "ref_input_labels.bin"))
    print("Reference outputs saved.")
except Exception as e:
    print(f"Inference failed: {e}")

print("\nExtraction complete.")
