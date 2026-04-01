%% run_codegen.m — Generate C++ from sam2_1200x1800.pt2 via MATLAB Coder
% Approach 2: loadPyTorchExportedProgram → direct .pt2 → C++ (MLIR/TOSA path)
% Mirrors the pattern used in the Easy/repvit_predict.m project.

projDir = '/Users/arkadiyturevskiy/Documents/Claude/Coder_Models/Hard/sam2_deploy/matlab_coder';
outDir  = fullfile(projDir, 'codegen');
cd(projDir);

fprintf('=== SAM2 MATLAB Coder Code Generation ===\n');
fprintf('Source:  sam2_1200x1800.pt2  (128 MB)\n');
fprintf('Entry:   sam2_infer.m\n');
fprintf('Backend: loadPyTorchExportedProgram → MLIR/TOSA → C++\n\n');

%% ─── Coder configuration ─────────────────────────────────────────────────────
cfg = coder.config('lib', 'ecoder', true);
cfg.TargetLang         = 'C++';
cfg.GenerateReport     = true;
cfg.GenCodeOnly        = true;
cfg.EnableOpenMP       = false;   % keep off — training job owns the cores
cfg.SupportNonFinite   = true;    % SAM2 attention uses -Inf masking
cfg.BuildConfiguration = 'Faster Runs';
cfg.LargeConstantThreshold = 0;   % weights go to .bin sidecar files
cfg.EnableMemcpy       = true;
cfg.MemcpyThreshold    = 64;

%% ─── Deep learning config: no external runtime ───────────────────────────────
dlcfg = coder.DeepLearningConfig('none');
cfg.DeepLearningConfig = dlcfg;

%% ─── Input types (must match pt2 signature exactly) ─────────────────────────
% Confirmed from graph signature:
%   image_hwc_u8 : [1200, 1800, 3]  uint8   (fixed)
%   point_coords : [1, 2]           single  (fixed)
%   point_labels : [1]              int32   (fixed)
img_type    = coder.typeof(uint8(0),   [1200, 1800, 3], [false false false]);
coords_type = coder.typeof(single(0),  [1, 2],          [false false]);
labels_type = coder.typeof(int32(0),   [1],             [false]);

%% ─── Codegen ─────────────────────────────────────────────────────────────────
fprintf('Starting code generation (may take 5-15 minutes for 128 MB model)...\n');
t0 = tic;
try
    codegen -config cfg sam2_infer ...
            -args {img_type, coords_type, labels_type} ...
            -d outDir -report
    elapsed = toc(t0);
    fprintf('\n[SUCCESS] Code generation completed in %.1f seconds.\n', elapsed);
    fprintf('Output: %s\n', outDir);

    %% Summarise
    cpp_files = dir(fullfile(outDir, '*.cpp'));
    h_files   = dir(fullfile(outDir, '*.h'));
    bin_files = dir(fullfile(outDir, '*.bin'));
    fprintf('\nGenerated files:\n');
    fprintf('  C++ sources: %d\n', numel(cpp_files));
    fprintf('  Headers:     %d\n', numel(h_files));
    fprintf('  Weight .bin: %d  (%.1f MB total)\n', numel(bin_files), ...
        sum([bin_files.bytes])/1e6);

    total_lines = 0;
    for k = 1:numel(cpp_files)
        fid = fopen(fullfile(outDir, cpp_files(k).name), 'r');
        c = textscan(fid, '%s', 'Delimiter', '\n'); fclose(fid);
        total_lines = total_lines + numel(c{1});
    end
    fprintf('  Total C++ lines: %d\n', total_lines);

    summary.elapsed_s       = elapsed;
    summary.n_cpp           = numel(cpp_files);
    summary.n_h             = numel(h_files);
    summary.total_lines     = total_lines;
    summary.total_bin_bytes = sum([bin_files.bytes]);
    save(fullfile(projDir, 'codegen_summary.mat'), 'summary');

catch ME
    elapsed = toc(t0);
    fprintf('\n[FAILED] after %.1f s  —  %s\n', elapsed, ME.message);
    errInfo.id = ME.identifier; errInfo.message = ME.message;
    errInfo.stack = ME.stack;   errInfo.elapsed = elapsed;
    save(fullfile(projDir, 'codegen_error.mat'), 'errInfo');
    fprintf('Error saved to codegen_error.mat\n');
end
