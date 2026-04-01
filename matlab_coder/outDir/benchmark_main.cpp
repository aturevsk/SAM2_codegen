// benchmark_main.cpp — Time the MATLAB Coder-generated SAM2 C++ library
// Compile: see build_benchmark.sh
#include <cstdio>
#include <cstring>
#include <chrono>
#include <cstdlib>
#include "sam2_infer.h"
#include "sam2_infer_initialize.h"
#include "sam2_infer_terminate.h"
#include "rt_nonfinite.h"

int main(int argc, char** argv)
{
    const char* refDir = "/Users/arkadiyturevskiy/Documents/Claude/Coder_Models/Hard/sam2_deploy/reference";

    printf("=== SAM2 Generated C++ Benchmark ===\n");

    // Initialize runtime
    sam2_infer_initialize();

    // Allocate I/O buffers
    static unsigned char img[1200*1800*3];
    static float coords[2];
    static int   label;
    static boolean_T masks[3*1200*1800];
    static float iou[3];

    // Load reference inputs
    char path[512];
    snprintf(path, sizeof(path), "%s/ref_input_image.bin", refDir);
    FILE* f = fopen(path, "rb");
    if (!f) { printf("Cannot open %s\n", path); return 1; }
    fread(img, 1, sizeof(img), f); fclose(f);

    snprintf(path, sizeof(path), "%s/ref_input_coords.bin", refDir);
    f = fopen(path, "rb"); fread(coords, 4, 2, f); fclose(f);

    snprintf(path, sizeof(path), "%s/ref_input_labels.bin", refDir);
    f = fopen(path, "rb"); fread(&label, 4, 1, f); fclose(f);

    // Read reference IoU
    float ref_iou[3] = {0};
    snprintf(path, sizeof(path), "%s/ref_output_1.bin", refDir);
    f = fopen(path, "rb"); fread(ref_iou, 4, 3, f); fclose(f);
    printf("Reference IoU: %.4f  %.4f  %.4f\n", ref_iou[0], ref_iou[1], ref_iou[2]);

    // Warm-up
    printf("\nWarm-up run...\n");
    auto t0 = std::chrono::high_resolution_clock::now();
    sam2_infer(img, coords, label, masks, iou);
    auto t1 = std::chrono::high_resolution_clock::now();
    double warmup_ms = std::chrono::duration<double,std::milli>(t1-t0).count();
    printf("Warm-up: %.0f ms   IoU: %.4f  %.4f  %.4f\n", warmup_ms, iou[0], iou[1], iou[2]);

    // Timed runs
    const int N = 3;
    double times[N];
    printf("\nTimed runs:\n");
    for (int k = 0; k < N; k++) {
        auto ta = std::chrono::high_resolution_clock::now();
        sam2_infer(img, coords, label, masks, iou);
        auto tb = std::chrono::high_resolution_clock::now();
        times[k] = std::chrono::duration<double,std::milli>(tb-ta).count();
        printf("  Run %d: %.0f ms\n", k+1, times[k]);
    }

    double mean_t = 0;
    double min_t = times[0], max_t = times[0];
    for (int k = 0; k < N; k++) {
        mean_t += times[k];
        if (times[k] < min_t) min_t = times[k];
        if (times[k] > max_t) max_t = times[k];
    }
    mean_t /= N;

    printf("\nLatency: mean=%.0f  min=%.0f  max=%.0f ms\n", mean_t, min_t, max_t);
    printf("Final IoU: %.4f  %.4f  %.4f\n", iou[0], iou[1], iou[2]);
    printf("IoU error: %.6f  %.6f  %.6f\n",
           fabs(iou[0]-ref_iou[0]), fabs(iou[1]-ref_iou[1]), fabs(iou[2]-ref_iou[2]));

    // Write results to file
    FILE* out = fopen("/Users/arkadiyturevskiy/Documents/Claude/Coder_Models/Hard/sam2_deploy/matlab_coder/cpp_bench_results.txt", "w");
    fprintf(out, "mean_ms: %.1f\n", mean_t);
    fprintf(out, "min_ms: %.1f\n", min_t);
    fprintf(out, "max_ms: %.1f\n", max_t);
    fprintf(out, "iou: %.4f  %.4f  %.4f\n", iou[0], iou[1], iou[2]);
    fprintf(out, "ref_iou: %.4f  %.4f  %.4f\n", ref_iou[0], ref_iou[1], ref_iou[2]);
    fclose(out);

    sam2_infer_terminate();
    printf("Done.\n");
    return 0;
}
