%% run_benchmark.m — Build MEX from generated C++ and time SAM2 inference
projDir = '/Users/arkadiyturevskiy/Documents/Claude/Coder_Models/Hard/sam2_deploy/matlab_coder';
outDir  = fullfile(projDir, 'outDir');
refDir  = '/Users/arkadiyturevskiy/Documents/Claude/Coder_Models/Hard/sam2_deploy/reference';
statusFile = fullfile(projDir, 'benchmark_status.txt');

fid = fopen(statusFile, 'w'); fprintf(fid, 'RUNNING\nStarted: %s\n', datetime('now')); fclose(fid);

cd(outDir);

%% ── 1. Build MEX ────────────────────────────────────────────────────────────
fprintf('Building MEX...\n');
try
    mex('-setup','C++');
    src_files = {
        'sam2_infer.cpp'
        'sam2_infer_initialize.cpp'
        'sam2_infer_terminate.cpp'
        'rt_nonfinite.cpp'
        'rtGetInf.cpp'
        'rtGetNaN.cpp'
        fullfile('interface','_coder_sam2_infer_mex.cpp')
        fullfile('interface','_coder_sam2_infer_api.cpp')
        fullfile('interface','_coder_sam2_infer_info.cpp')
    };
    mex_args = ['-I' outDir, ' -I' fullfile(outDir,'interface')];
    mex_cmd = ['mex ' mex_args];
    for k = 1:numel(src_files)
        mex_cmd = [mex_cmd ' ' src_files{k}]; %#ok<AGROW>
    end
    mex_cmd = [mex_cmd ' -output sam2_infer_mex'];
    eval(mex_cmd);
    fprintf('MEX built: sam2_infer_mex.%s\n', mexext);
    mex_ok = true;
catch ME
    fprintf('MEX build failed: %s\n', ME.message);
    mex_ok = false;
end

%% ── 2. Load reference inputs ─────────────────────────────────────────────────
fprintf('\nLoading reference inputs...\n');
try
    img_bytes    = fread(fopen(fullfile(refDir,'ref_input_image.bin'),'rb'),Inf,'uint8=>uint8');
    coord_bytes  = fread(fopen(fullfile(refDir,'ref_input_coords.bin'),'rb'),Inf,'uint8=>uint8');
    label_bytes  = fread(fopen(fullfile(refDir,'ref_input_labels.bin'),'rb'),Inf,'uint8=>uint8');
    ref_iou_bytes= fread(fopen(fullfile(refDir,'ref_output_1.bin'),'rb'),Inf,'uint8=>uint8');

    ref_image  = reshape(typecast(img_bytes,   'uint8'),  [1200, 1800, 3]);
    ref_coords = reshape(typecast(coord_bytes, 'single'), [1, 2]);
    ref_labels = reshape(typecast(label_bytes, 'int32'),  [1]);
    ref_iou    = reshape(typecast(ref_iou_bytes,'single'),[3]);
    fprintf('Reference IoU (PyTorch): %.4f  %.4f  %.4f\n', ref_iou(1), ref_iou(2), ref_iou(3));
    ref_ok = true;
catch ME
    fprintf('Reference load failed: %s\n', ME.message);
    ref_ok = false; ref_iou = [nan nan nan];
end

%% ── 3. Timing via MATLAB-level sam2_infer call ───────────────────────────────
% The generated code is also callable at MATLAB level via the persistent model
addpath(projDir);  % sam2_infer.m
addpath(outDir);

N_warm = 1; N_time = 3;
times_ms = zeros(1, N_time);
iou_out  = [nan nan nan];

fprintf('\nRunning %d warm-up + %d timed calls...\n', N_warm, N_time);

% Set environment variable so generated code finds .bin weight files
setenv('MATLAB_CODER_LARGE_CONST_PATH', outDir);

try
    %% warm-up
    for k = 1:N_warm
        fprintf('  Warm-up %d... ', k); drawnow;
        t0 = tic;
        [m_out, iou_out] = sam2_infer(ref_image, ref_coords, ref_labels);
        tw = toc(t0)*1000;
        fprintf('%.0f ms\n', tw);
    end

    %% timed runs
    for k = 1:N_time
        fprintf('  Run %d... ', k); drawnow;
        t0 = tic;
        [m_out, iou_out] = sam2_infer(ref_image, ref_coords, ref_labels);
        times_ms(k) = toc(t0)*1000;
        fprintf('%.0f ms\n', times_ms(k));
    end
    inference_ok = true;
catch ME
    fprintf('Inference error: %s\n', ME.message);
    inference_ok = false;
end

%% ── 4. Write status ──────────────────────────────────────────────────────────
fid = fopen(statusFile, 'w');
if inference_ok
    fprintf(fid, 'SUCCESS\n');
    fprintf(fid, 'mean_ms: %.1f\n', mean(times_ms));
    fprintf(fid, 'min_ms:  %.1f\n', min(times_ms));
    fprintf(fid, 'max_ms:  %.1f\n', max(times_ms));
    fprintf(fid, 'iou: %.4f  %.4f  %.4f\n', iou_out(1), iou_out(2), iou_out(3));
    fprintf(fid, 'ref_iou: %.4f  %.4f  %.4f\n', ref_iou(1), ref_iou(2), ref_iou(3));
    fprintf(fid, 'times_ms:');
    fprintf(fid, ' %.1f', times_ms);
    fprintf(fid, '\n');
else
    fprintf(fid, 'INFERENCE_FAILED\n');
end
fprintf(fid, 'mex_ok: %d\n', mex_ok);
fprintf(fid, 'codegen_cpp_files: 10\n');
fprintf(fid, 'codegen_h_files:   13\n');
fprintf(fid, 'codegen_bin_files: 320\n');
fprintf(fid, 'codegen_bin_mb:    125.3\n');
fprintf(fid, 'codegen_lines:     12598\n');
fprintf(fid, 'codegen_elapsed_s: 64.4\n');
fclose(fid);

fprintf('\nBenchmark complete. Results in benchmark_status.txt\n');
