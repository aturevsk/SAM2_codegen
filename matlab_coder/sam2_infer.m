function [masks, iou_scores] = sam2_infer(image_hwc_u8, point_coords, point_labels) %#codegen
% SAM2_INFER  Run SAM2 inference via MATLAB Coder Support Package for PyTorch.
%   Inputs:
%     image_hwc_u8  : uint8  [1200, 1800, 3]  raw image pixels (HWC)
%     point_coords  : single [1, 2]            (x, y) in image coords
%     point_labels  : int32  [1]               1=foreground, 0=background
%   Outputs:
%     masks         : single [3, 1200, 1800]   mask logits at full resolution
%     iou_scores    : single [3]               per-mask IoU predictions
%
%   loadPyTorchExportedProgram loads the .pt2 directly — no importNetworkFromPyTorch.
%   MATLAB Coder generates C++ via the MLIR/TOSA lowering path.

persistent model;
if isempty(model)
    model = loadPyTorchExportedProgram( ...
        '/Users/arkadiyturevskiy/Documents/Claude/Coder_Models/Hard/sam2_1200x1800.pt2');
end

outputs    = invoke(model, image_hwc_u8, point_coords, point_labels);
masks      = outputs{1};
iou_scores = outputs{2};
end
