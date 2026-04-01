function [masks, iou_scores] = sam2_infer(image_hwc_u8, point_coords, point_labels) %#codegen
% SAM2_INFER  Run SAM2 inference via MATLAB Coder Support Package for PyTorch.
%   Inputs:
%     image_hwc_u8  : uint8  [1200, 1800, 3]  raw image pixels (HWC)
%     point_coords  : single [1, 2]            (x, y) in image coords
%     point_labels  : int32  [1]               1=foreground, 0=background
%   Outputs:
%     masks         : logical [3, 1200, 1800]  binary segmentation masks
%     iou_scores    : single  [3]              per-mask IoU predictions
%
%   loadPyTorchExportedProgram loads the .pt2 directly — no importNetworkFromPyTorch.
%   MATLAB Coder generates C++ via the MLIR/TOSA lowering path.
%   invoke() with multiple LHS variables unpacks multi-output models —
%   brace indexing ({}) is not supported by MATLAB Coder for this return type.

persistent model;
if isempty(model)
    model = loadPyTorchExportedProgram( ...
        '/Users/arkadiyturevskiy/Documents/Claude/Coder_Models/Hard/sam2_1200x1800.pt2');
end

% Multi-output invoke: unpack directly into named variables.
% MLIR signature: (ui8[1200x1800x3], f32[1x2], i32[1]) -> (i1[3x1200x1800], f32[3])
[masks, iou_scores] = invoke(model, image_hwc_u8, point_coords, point_labels);
end
