"""Generate reference inputs/outputs from sam2_1200x1800.pt2."""
import os, torch, numpy as np

PT2  = "/Users/arkadiyturevskiy/Documents/Claude/Coder_Models/Hard/sam2_1200x1800.pt2"
REF  = "/Users/arkadiyturevskiy/Documents/Claude/Coder_Models/Hard/sam2_deploy/reference"
os.makedirs(REF, exist_ok=True)

print("Loading model...")
ep = torch.export.load(PT2)

# Fixed synthetic inputs
torch.manual_seed(42)
img        = torch.randint(0, 256, (1200, 1800, 3), dtype=torch.uint8)
pt_coords  = torch.tensor([[600.0, 900.0]], dtype=torch.float32)
pt_labels  = torch.tensor([1], dtype=torch.int32)

print("Running inference (positional args)...")
with torch.no_grad():
    out = ep.module()(img, pt_coords, pt_labels)

outs = out if isinstance(out, (list, tuple)) else [out]
for i, o in enumerate(outs):
    arr = o.float().cpu().numpy()
    arr.tofile(f"{REF}/ref_output_{i}.bin")
    print(f"  out[{i}]: shape={arr.shape} dtype={arr.dtype}")

# Save inputs
img.numpy().tofile(f"{REF}/ref_input_image.bin")
pt_coords.numpy().tofile(f"{REF}/ref_input_coords.bin")
pt_labels.numpy().tofile(f"{REF}/ref_input_labels.bin")
print("Saved inputs + outputs.")

# Also save output shapes/dtypes for C++ validation
import json
meta = {
    "inputs": {
        "image_hwc_u8":  {"shape": [1200,1800,3], "dtype": "uint8"},
        "point_coords":  {"shape": [1,2],          "dtype": "float32"},
        "point_labels":  {"shape": [1],             "dtype": "int32"},
    },
    "outputs": [
        {"shape": list(o.float().cpu().numpy().shape), "dtype": "float32"}
        for o in outs
    ]
}
with open(f"{REF}/io_meta.json","w") as f:
    json.dump(meta, f, indent=2)
print("Metadata saved.")
