function net = loadSAM2()
% LOADSAM2  Load SAM2 exported program for MATLAB Coder code generation.
% Uses loadPyTorchExportedProgram (direct .pt2 → no Deep Learning Toolbox import).
net = loadPyTorchExportedProgram( ...
    '/Users/arkadiyturevskiy/Documents/Claude/Coder_Models/Hard/sam2_1200x1800.pt2');
end
