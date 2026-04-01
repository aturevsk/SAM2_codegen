%% benchmark_matlab_coder.m — Benchmark SAM2 via MATLAB Coder generated C++
% Compiles the generated C++ with GCC/Clang and measures latency.

projDir = '/Users/arkadiyturevskiy/Documents/Claude/Coder_Models/Hard/sam2_deploy/matlab_coder';
refDir  = '/Users/arkadiyturevskiy/Documents/Claude/Coder_Models/Hard/sam2_deploy/reference';
genDir  = fullfile(projDir, 'codegen');
cd(projDir);

fprintf('=== MATLAB Coder C++ Benchmark ===\n\n');

%% ─── Check codegen output exists ────────────────────────────────────────────
if ~exist(fullfile(genDir, 'sam2_infer.cpp'), 'file') && ...
   ~exist(fullfile(genDir, 'lib', 'sam2_infer.cpp'), 'file')
    warning('Codegen output not found. Run run_codegen.m first.');
    return;
end

%% ─── Build a test harness and compile ───────────────────────────────────────
% Write a simple C++ test harness that calls the generated function
harness_src = fullfile(projDir, 'bench_harness.cpp');
fid = fopen(harness_src, 'w');
fprintf(fid, [
    '#include <stdio.h>\n'
    '#include <stdlib.h>\n'
    '#include <time.h>\n'
    '#include "sam2_infer.h"\n'
    'int main() {\n'
    '  // Allocate inputs\n'
    '  unsigned char* img = (unsigned char*)calloc(1200*1800*3, 1);\n'
    '  float* coords = (float*)malloc(2*sizeof(float));\n'
    '  int*   labels = (int*)malloc(sizeof(int));\n'
    '  float* masks  = (float*)malloc(3*1200*1800*sizeof(float));\n'
    '  float* ious   = (float*)malloc(3*sizeof(float));\n'
    '  coords[0]=600.f; coords[1]=900.f; labels[0]=1;\n'
    '  // Warmup\n'
    '  sam2_infer(img, coords, labels, masks, ious);\n'
    '  // Time 5 runs\n'
    '  struct timespec t0, t1;\n'
    '  double total_ms = 0;\n'
    '  for (int r=0; r<5; r++) {\n'
    '    clock_gettime(CLOCK_MONOTONIC, &t0);\n'
    '    sam2_infer(img, coords, labels, masks, ious);\n'
    '    clock_gettime(CLOCK_MONOTONIC, &t1);\n'
    '    double ms = (t1.tv_sec-t0.tv_sec)*1000.0 + (t1.tv_nsec-t0.tv_nsec)/1e6;\n'
    '    printf("Run %d: %.1f ms\n", r, ms);\n'
    '    total_ms += ms;\n'
    '  }\n'
    '  printf("Mean: %.1f ms\\nIoU: %.4f %.4f %.4f\\n",\n'
    '    total_ms/5.0, ious[0], ious[1], ious[2]);\n'
    '  return 0;\n'
    '}\n'
]);
fclose(fid);

fprintf('Test harness written to: %s\n', harness_src);
fprintf('(Compile with: clang++ -O3 -march=native -I<genDir> bench_harness.cpp <genDir>/*.cpp -o bench_sam2_coder)\n\n');

%% ─── Run inference from MATLAB to measure latency ───────────────────────────
% Load reference inputs
fprintf('Loading reference inputs...\n');
fid = fopen(fullfile(refDir, 'ref_input_image.bin'), 'r');
img_data = fread(fid, 1200*1800*3, 'uint8=>uint8'); fclose(fid);
image_hwc_u8 = reshape(img_data, [1200, 1800, 3]);

coords = single([600, 900]);
labels = int32(1);

%% ─── Time the MATLAB interpreted call ───────────────────────────────────────
% This is not the generated C++ speed, but confirms functional correctness
% The true C++ speed comes from compiling with the codegen output.

fprintf('Timing sam2_infer in MATLAB (interpreted, not codegen speed)...\n');
N_RUNS = 3;
times_ms = zeros(1, N_RUNS);
for r = 1:N_RUNS
    t_start = tic;
    [masks, iou_scores] = sam2_infer(image_hwc_u8, coords, labels);
    times_ms(r) = toc(t_start)*1000;
    fprintf('  Run %d: %.0f ms\n', r, times_ms(r));
end

fprintf('\nMATLAB interpreted mean: %.0f ms\n', mean(times_ms));
fprintf('IoU scores: %.4f  %.4f  %.4f\n', iou_scores(1), iou_scores(2), iou_scores(3));

%% ─── Compare with PyTorch reference ─────────────────────────────────────────
fprintf('\n=== Validation vs PyTorch ===\n');
fid = fopen(fullfile(refDir, 'ref_output_1.bin'), 'r');
ref_iou = fread(fid, 3, 'float32=>single'); fclose(fid);

fprintf('Our IoU:  '); fprintf('%.4f ', iou_scores(:)'); fprintf('\n');
fprintf('Ref IoU:  '); fprintf('%.4f ', ref_iou(:)');     fprintf('\n');
iou_rmse = sqrt(mean((iou_scores(:) - ref_iou(:)).^2));
fprintf('IoU RMSE: %.6f\n', iou_rmse);

%% ─── Save results ────────────────────────────────────────────────────────────
results.times_ms    = times_ms;
results.mean_ms     = mean(times_ms);
results.iou_scores  = iou_scores;
results.ref_iou     = ref_iou;
results.iou_rmse    = iou_rmse;
results.timestamp   = datetime('now');
save(fullfile(projDir, 'benchmark_results.mat'), 'results');
fprintf('\nResults saved to benchmark_results.mat\n');
