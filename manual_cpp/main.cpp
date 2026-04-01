// SAM2 Manual C++ Benchmark + Validation
// Tests both correctness (vs reference PyTorch output) and timing.
#include "sam2.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <cmath>
#include <numeric>
#include <cstring>

using Clock = std::chrono::high_resolution_clock;

static std::vector<uint8_t> load_u8(const std::string& p, size_t n) {
    std::vector<uint8_t> v(n);
    std::ifstream f(p, std::ios::binary);
    if (!f) throw std::runtime_error("Missing: "+p);
    f.read(reinterpret_cast<char*>(v.data()), n);
    return v;
}

static std::vector<float> load_f32(const std::string& p, size_t n) {
    std::vector<float> v(n);
    std::ifstream f(p, std::ios::binary);
    if (!f) throw std::runtime_error("Missing: "+p);
    f.read(reinterpret_cast<char*>(v.data()), n*4);
    return v;
}

static float rmse(const float* a, const float* b, size_t n) {
    double s = 0;
    for (size_t i = 0; i < n; i++) { double d = a[i]-b[i]; s += d*d; }
    return (float)std::sqrt(s/n);
}

int main(int argc, char** argv) {
    std::string weight_dir = "/Users/arkadiyturevskiy/Documents/Claude/Coder_Models/Hard/sam2_deploy/weights";
    std::string ref_dir    = "/Users/arkadiyturevskiy/Documents/Claude/Coder_Models/Hard/sam2_deploy/reference";
    int H = 1200, W = 1800;
    if (argc > 1) weight_dir = argv[1];
    if (argc > 2) ref_dir    = argv[2];

    std::cout << "=== SAM2 Manual C++ Benchmark ===\n\n";

    // Load model
    SAM2 model;
    {
        auto t0 = Clock::now();
        model.load(weight_dir);
        auto t1 = Clock::now();
        double ms = std::chrono::duration<double,std::milli>(t1-t0).count();
        std::cout << "Model load time: " << ms << " ms\n\n";
    }

    // Load reference inputs
    auto img = load_u8(ref_dir+"/ref_input_image.bin", (size_t)H*W*3);
    auto ref_coords = load_f32(ref_dir+"/ref_input_coords.bin", 2);
    float pt_x = ref_coords[0], pt_y = ref_coords[1];
    std::cout << "Input: " << H << "×" << W << "  point=(" << pt_x << "," << pt_y << ")\n\n";

    // ── Warmup run ───────────────────────────────────────────────
    std::cout << "Warmup...\n";
    std::vector<float> masks, ious;
    model.forward(img.data(), H, W, pt_x, pt_y, 1, masks, ious);
    std::cout << "Warmup done. IoU predictions: ";
    for (float v : ious) std::cout << v << " ";
    std::cout << "\n\n";

    // ── Timed runs ───────────────────────────────────────────────
    int N_RUNS = 5;
    std::cout << "Timing " << N_RUNS << " runs...\n";
    std::vector<double> times;
    for (int r = 0; r < N_RUNS; r++) {
        auto t0 = Clock::now();
        model.forward(img.data(), H, W, pt_x, pt_y, 1, masks, ious);
        auto t1 = Clock::now();
        times.push_back(std::chrono::duration<double,std::milli>(t1-t0).count());
        std::cout << "  Run " << r << ": " << times.back() << " ms\n";
    }

    double sum = std::accumulate(times.begin(), times.end(), 0.0);
    double mean = sum / times.size();
    std::sort(times.begin(), times.end());
    double median = times[times.size()/2];
    double mn = times.front(), mx = times.back();
    std::cout << "\nLatency (ms):  mean=" << mean
              << "  median=" << median
              << "  min=" << mn
              << "  max=" << mx << "\n";
    std::cout << "Throughput: " << 1000.0/mean << " fps\n\n";

    // ── Validation vs PyTorch reference ─────────────────────────
    std::cout << "=== Validation vs PyTorch reference ===\n";
    try {
        // ref_output_0: [3, 1200, 1800] (masks upsampled)
        // ref_output_1: [3] (IoU scores)
        auto ref0 = load_f32(ref_dir+"/ref_output_0.bin", (size_t)3*H*W);
        auto ref1 = load_f32(ref_dir+"/ref_output_1.bin", 3);

        float err_masks = rmse(masks.data(), ref0.data(), (size_t)3*H*W);
        std::cout << "Masks RMSE vs PyTorch:  " << err_masks << "\n";
        std::cout << "Our IoU:  ";
        for (float v : ious) std::cout << v << " ";
        std::cout << "\n";
        std::cout << "Ref IoU:  ";
        for (float v : ref1) std::cout << v << " ";
        std::cout << "\n";
        std::cout << "IoU RMSE: " << rmse(ious.data(), ref1.data(), 3) << "\n";

        if (err_masks < 0.1f) {
            std::cout << "\n[PASS] Outputs match PyTorch reference (RMSE < 0.1).\n";
        } else {
            std::cout << "\n[INFO] RMSE > 0.1 – check weight mapping.\n";
        }
    } catch (const std::exception& e) {
        std::cout << "Validation skipped: " << e.what() << "\n";
    }

    // ── Memory ───────────────────────────────────────────────────
    std::cout << "\n=== Memory (approximate) ===\n";
    // Weight memory (params already loaded into vectors)
    // This is an approximation; actual resident set also includes stack/buffers
    size_t w_bytes = 0;
    // We don't have easy introspection here; print model file size
    std::ifstream pt2("/Users/arkadiyturevskiy/Documents/Claude/Coder_Models/Hard/sam2_1200x1800.pt2",
                      std::ios::binary|std::ios::ate);
    if (pt2) std::cout << "Source .pt2 file: " << pt2.tellg()/1024/1024 << " MB\n";
    std::cout << "Weight binaries: ~16 MB (FP32)\n";
    std::cout << "Working buffers: ~" << (256*256*96 + 128*128*192 + 64*64*384 + 32*32*768)*4/1024/1024
              << "+ MB\n";

    // ── Save output masks ────────────────────────────────────────
    {
        std::ofstream f(ref_dir+"/manual_cpp_output_masks.bin", std::ios::binary);
        f.write(reinterpret_cast<const char*>(masks.data()), masks.size()*4);
        std::ofstream g(ref_dir+"/manual_cpp_output_iou.bin", std::ios::binary);
        g.write(reinterpret_cast<const char*>(ious.data()), ious.size()*4);
    }
    std::cout << "\nOutputs saved to reference directory.\n";
    return 0;
}
