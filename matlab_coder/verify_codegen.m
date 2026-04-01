%% verify_codegen.m — Validate and benchmark MATLAB Coder-generated SAM2
% Run after run_codegen_bg.m succeeds.
% Calls the generated MEX (for MATLAB-side timing) and compares vs. PyTorch reference.

projDir = '/Users/arkadiyturevskiy/Documents/Claude/Coder_Models/Hard/sam2_deploy/matlab_coder';
refDir  = '/Users/arkadiyturevskiy/Documents/Claude/Coder_Models/Hard/sam2_deploy/reference';
cd(projDir);

fprintf('=== SAM2 Codegen Verification & Benchmark ===\n\n');

%% ─── 1. Load reference I/O from PyTorch ─────────────────────────────────────
ref_image  = reshape(typecast(fileread_bytes(fullfile(refDir,'ref_input_image.bin')),  'uint8'),  [1200, 1800, 3]);
ref_coords = reshape(typecast(fileread_bytes(fullfile(refDir,'ref_input_coords.bin')), 'single'), [1, 2]);
ref_labels = reshape(typecast(fileread_bytes(fullfile(refDir,'ref_input_labels.bin')), 'int32'),  [1]);
ref_masks  = reshape(typecast(fileread_bytes(fullfile(refDir,'ref_output_0.bin')),     'single'), [3, 1200, 1800]);
ref_iou    = reshape(typecast(fileread_bytes(fullfile(refDir,'ref_output_1.bin')),     'single'), [3]);

fprintf('Reference IoU (PyTorch): %.4f  %.4f  %.4f\n', ref_iou(1), ref_iou(2), ref_iou(3));

%% ─── 2. Build MEX from generated code ───────────────────────────────────────
outDir = fullfile(projDir, 'codegen');
fprintf('\nBuilding MEX from generated C++...\n');
mex_src = fullfile(outDir, 'sam2_infer.cpp');
if ~isfile(mex_src)
    error('Codegen output not found: %s\nRun run_codegen_bg.m first.', mex_src);
end

% Add codegen output to path
addpath(outDir);

%% ─── 3. Warm-up run ─────────────────────────────────────────────────────────
fprintf('Warm-up inference...\n');
[masks_out, iou_out] = sam2_infer(ref_image, ref_coords, ref_labels);
fprintf('Warm-up IoU: %.4f  %.4f  %.4f\n', iou_out(1), iou_out(2), iou_out(3));

%% ─── 4. Timed runs ──────────────────────────────────────────────────────────
N = 5;
fprintf('\nTiming %d inference runs...\n', N);
times = zeros(1, N);
for k = 1:N
    t0 = tic;
    [masks_k, iou_k] = sam2_infer(ref_image, ref_coords, ref_labels);
    times(k) = toc(t0) * 1000; % ms
    fprintf('  Run %d: %.1f ms\n', k, times(k));
end

fprintf('\nLatency: mean=%.1f  median=%.1f  min=%.1f  max=%.1f ms\n', ...
    mean(times), median(times), min(times), max(times));

%% ─── 5. Numerical comparison vs. PyTorch ────────────────────────────────────
fprintf('\n=== Numerical Comparison vs. PyTorch Reference ===\n');
iou_err = abs(double(iou_out) - double(ref_iou));
fprintf('IoU absolute error: %.6f  %.6f  %.6f\n', iou_err(1), iou_err(2), iou_err(3));

% Mask agreement (boolean vs. sign of logit)
mask_logit_sign = ref_masks > 0;  % PyTorch positive logit → foreground
mask_agree = double(masks_out) == double(mask_logit_sign);
for m = 1:3
    pct = 100 * mean(mask_agree(m,:,:), 'all');
    fprintf('Mask %d pixel agreement: %.2f%%\n', m, pct);
end

%% ─── 6. Save results ────────────────────────────────────────────────────────
results.times_ms      = times;
results.mean_ms       = mean(times);
results.median_ms     = median(times);
results.iou_out       = iou_out;
results.iou_ref       = ref_iou;
results.iou_err       = iou_err;
results.mask_agree_pct = 100 * squeeze(mean(mask_agree, [2,3]));

save(fullfile(projDir, 'verify_results.mat'), 'results');
fprintf('\nResults saved to verify_results.mat\n');
fprintf('Done.\n');

%% ─── Helper ──────────────────────────────────────────────────────────────────
function bytes = fileread_bytes(path)
    fid = fopen(path, 'rb');
    bytes = fread(fid, Inf, 'uint8=>uint8');
    fclose(fid);
end
