%% run_codegen_bg.m — SAM2 codegen, writes status files for polling
% Run via: matlab -nodisplay -r "run('/path/to/run_codegen_bg.m'); exit"

projDir = '/Users/arkadiyturevskiy/Documents/Claude/Coder_Models/Hard/sam2_deploy/matlab_coder';
outDir  = fullfile(projDir, 'codegen');
statusFile  = fullfile(projDir, 'codegen_status.txt');
summaryFile = fullfile(projDir, 'codegen_summary.mat');
errorFile   = fullfile(projDir, 'codegen_error.mat');

% Clean previous results
if isfile(statusFile),  delete(statusFile);  end
if isfile(summaryFile), delete(summaryFile); end
if isfile(errorFile),   delete(errorFile);   end

fid = fopen(statusFile, 'w');
fprintf(fid, 'RUNNING\nStarted: %s\n', datetime('now'));
fclose(fid);

cd(projDir);
fprintf('=== SAM2 MATLAB Coder Background Codegen ===\n');
fprintf('CWD: %s\n', pwd);

%% Config
cfg = coder.config('lib', 'ecoder', true);
cfg.TargetLang             = 'C++';
cfg.GenerateReport         = true;
cfg.GenCodeOnly            = true;
cfg.EnableOpenMP           = false;
cfg.SupportNonFinite       = true;   % SAM2 attention uses -Inf masking
cfg.BuildConfiguration     = 'Faster Runs';
cfg.LargeConstantThreshold = 0;
cfg.EnableMemcpy           = true;
cfg.MemcpyThreshold        = 64;

dlcfg = coder.DeepLearningConfig('none');
cfg.DeepLearningConfig = dlcfg;

%% Input types
img_type    = coder.typeof(uint8(0),  [1200, 1800, 3], [false false false]);
coords_type = coder.typeof(single(0), [1, 2],          [false false]);
labels_type = coder.typeof(int32(0),  [1],             [false]);

%% Run
t0 = tic;
try
    codegen -config cfg sam2_infer ...
            -args {img_type, coords_type, labels_type} ...
            -d outDir -report

    elapsed = toc(t0);
    fprintf('\n[SUCCESS] %.1f s\n', elapsed);

    cpp_files = dir(fullfile(outDir, '*.cpp'));
    h_files   = dir(fullfile(outDir, '*.h'));
    bin_files = dir(fullfile(outDir, '*.bin'));
    total_lines = 0;
    for k = 1:numel(cpp_files)
        fid2 = fopen(fullfile(outDir, cpp_files(k).name), 'r');
        c = textscan(fid2, '%s', 'Delimiter', '\n'); fclose(fid2);
        total_lines = total_lines + numel(c{1});
    end

    summary.elapsed_s       = elapsed;
    summary.n_cpp           = numel(cpp_files);
    summary.n_h             = numel(h_files);
    summary.n_bin           = numel(bin_files);
    summary.total_lines     = total_lines;
    summary.total_bin_bytes = sum([bin_files.bytes]);
    save(summaryFile, 'summary');

    fid = fopen(statusFile, 'w');
    fprintf(fid, 'SUCCESS\nElapsed: %.1f s\nC++ files: %d\nHeaders: %d\nBin files: %d (%.1f MB)\nTotal lines: %d\n', ...
        elapsed, numel(cpp_files), numel(h_files), numel(bin_files), ...
        sum([bin_files.bytes])/1e6, total_lines);
    fclose(fid);

catch ME
    elapsed = toc(t0);
    fprintf('\n[FAILED] %.1f s — %s\n', elapsed, ME.message);
    errInfo.id = ME.identifier; errInfo.message = ME.message;
    errInfo.stack = ME.stack;   errInfo.elapsed = elapsed;
    save(errorFile, 'errInfo');

    fid = fopen(statusFile, 'w');
    fprintf(fid, 'FAILED\nElapsed: %.1f s\nError: %s\nID: %s\n', ...
        elapsed, ME.message, ME.identifier);
    fclose(fid);
end
