%% run_timing.m — Time SAM2 inference using loadPyTorchExportedProgram + invoke
% This times the MATLAB-interpreted path through the model.
% The C++ codegen path would be faster; this is the floor measurement.

projDir = '/Users/arkadiyturevskiy/Documents/Claude/Coder_Models/Hard/sam2_deploy/matlab_coder';
refDir  = '/Users/arkadiyturevskiy/Documents/Claude/Coder_Models/Hard/sam2_deploy/reference';
statusFile = fullfile(projDir, 'timing_status.txt');

fid = fopen(statusFile, 'w'); fprintf(fid, 'RUNNING\nStarted: %s\n', datetime('now')); fclose(fid);
cd(projDir);

fprintf('=== SAM2 Inference Timing ===\n');

%% ── Load model ───────────────────────────────────────────────────────────────
fprintf('Loading model...\n');
t0 = tic;
model = loadPyTorchExportedProgram( ...
    '/Users/arkadiyturevskiy/Documents/Claude/Coder_Models/Hard/sam2_1200x1800.pt2');
load_t = toc(t0);
fprintf('Model loaded in %.1f s\n', load_t);

%% ── Inputs ───────────────────────────────────────────────────────────────────
fid2 = fopen(fullfile(refDir,'ref_input_image.bin'),  'rb'); img_bytes  = fread(fid2,Inf,'uint8=>uint8');  fclose(fid2);
fid2 = fopen(fullfile(refDir,'ref_input_coords.bin'), 'rb'); co_bytes   = fread(fid2,Inf,'uint8=>uint8');  fclose(fid2);
fid2 = fopen(fullfile(refDir,'ref_input_labels.bin'), 'rb'); lb_bytes   = fread(fid2,Inf,'uint8=>uint8');  fclose(fid2);
fid2 = fopen(fullfile(refDir,'ref_output_1.bin'),     'rb'); iou_bytes  = fread(fid2,Inf,'uint8=>uint8');  fclose(fid2);

ref_image  = reshape(typecast(img_bytes,  'uint8'),  1200, 1800, 3);
ref_coords = reshape(typecast(co_bytes,   'single'), 1, 2);
ref_labels = typecast(lb_bytes, 'int32');  ref_labels = ref_labels(1);
ref_iou    = typecast(iou_bytes,'single');

fprintf('Reference IoU: %.4f  %.4f  %.4f\n', ref_iou(1), ref_iou(2), ref_iou(3));

%% ── Warm-up ──────────────────────────────────────────────────────────────────
fprintf('\nWarm-up run...\n');
t0 = tic;
[masks_w, iou_w] = invoke(model, ref_image, ref_coords, ref_labels);
warm_t = toc(t0)*1000;
fprintf('Warm-up: %.0f ms   IoU: %.4f  %.4f  %.4f\n', warm_t, iou_w(1), iou_w(2), iou_w(3));

%% ── Timed runs ───────────────────────────────────────────────────────────────
N = 3;
times = zeros(1, N);
fprintf('\nTimed runs (%d):\n', N);
for k = 1:N
    t0 = tic;
    [masks_k, iou_k] = invoke(model, ref_image, ref_coords, ref_labels);
    times(k) = toc(t0)*1000;
    fprintf('  Run %d: %.0f ms\n', k, times(k));
end

fprintf('\nMean: %.0f ms   Min: %.0f ms   Max: %.0f ms\n', mean(times), min(times), max(times));

%% ── Accuracy ─────────────────────────────────────────────────────────────────
iou_err = abs(double(iou_k) - double(ref_iou));
fprintf('IoU error vs PyTorch: %.6f  %.6f  %.6f\n', iou_err(1), iou_err(2), iou_err(3));

%% ── Write status ─────────────────────────────────────────────────────────────
fid = fopen(statusFile, 'w');
fprintf(fid, 'SUCCESS\n');
fprintf(fid, 'model_load_s: %.1f\n', load_t);
fprintf(fid, 'warmup_ms: %.0f\n', warm_t);
fprintf(fid, 'mean_ms: %.1f\n', mean(times));
fprintf(fid, 'min_ms: %.1f\n', min(times));
fprintf(fid, 'max_ms: %.1f\n', max(times));
fprintf(fid, 'iou: %.4f  %.4f  %.4f\n', iou_k(1), iou_k(2), iou_k(3));
fprintf(fid, 'iou_err: %.6f  %.6f  %.6f\n', iou_err(1), iou_err(2), iou_err(3));
fprintf(fid, 'times_ms:');
fprintf(fid, ' %.1f', times);
fprintf(fid, '\n');
fclose(fid);

fprintf('\nDone.\n');
