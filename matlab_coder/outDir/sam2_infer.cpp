//
// Prerelease License - for engineering feedback and testing purposes
// only. Not for sale.
// File: sam2_infer.cpp
//
// MATLAB Coder version            : 26.1
// C/C++ source code generated on  : 01-Apr-2026 07:32:45
//

// Include Files
#include "sam2_infer.h"
#include "rt_nonfinite.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function Declarations
static void b_convolution(const float &inputTensor, float &outputTensor, const
  float &weightsTensor, const float &biasTensor);
static void b_convolutionKernel(const float &inputBufferPtr, float
  &outputBufferPtr, const float &weightsBufferPtr, boolean_T
  canInitializeOutputRegistersWithBiasValues, const float &biasBufferPtr);
static void c_convolution(const float &inputTensor, float &outputTensor, const
  float &weightsTensor, const float &biasTensor);
static void c_convolutionKernel(const float &inputBufferPtr, float
  &outputBufferPtr, const float &weightsBufferPtr, boolean_T
  canInitializeOutputRegistersWithBiasValues, const float &biasBufferPtr);
static char *computeFilePathUsingEnvVariable(const char *unresolvedFilePath);
static void convolution(const float &inputTensor, float &outputTensor, const
  float &weightsTensor, const float &biasTensor);
static void convolutionKernel(const float &inputBufferPtr, float
  &outputBufferPtr, const float &weightsBufferPtr, boolean_T
  canInitializeOutputRegistersWithBiasValues, const float &biasBufferPtr);
static void d_convolution(const float &inputTensor, float &outputTensor, const
  float &weightsTensor, const float &biasTensor);
static void d_convolutionKernel(const float &inputBufferPtr, float
  &outputBufferPtr, const float &weightsBufferPtr, boolean_T
  canInitializeOutputRegistersWithBiasValues, const float &biasBufferPtr);
static int div_nde_s32_floor();
static int div_s32_floor(int numerator, int denominator);
static void e_convolution(const float &inputTensor, float &outputTensor, const
  float &weightsTensor, const float &biasTensor);
static void e_convolutionKernel(const float &inputBufferPtr, float
  &outputBufferPtr, const float &weightsBufferPtr, boolean_T
  canInitializeOutputRegistersWithBiasValues, const float &biasBufferPtr);
static void f_convolution(const float &inputTensor, float &outputTensor, const
  float &weightsTensor, const float &biasTensor);
static void f_convolutionKernel(const float &inputBufferPtr, float
  &outputBufferPtr, const float &weightsBufferPtr, boolean_T
  canInitializeOutputRegistersWithBiasValues, const float &biasBufferPtr);
static void g_convolution(const float &inputTensor, float &outputTensor, const
  float &weightsTensor, const float &biasTensor);
static void g_convolutionKernel(const float &inputBufferPtr, float
  &outputBufferPtr, const float &weightsBufferPtr, boolean_T
  canInitializeOutputRegistersWithBiasValues, const float &biasBufferPtr);
static char *getCustomUserDataPathEnvVar(const char *unresolvedFilePath);
static int getPositionOfLastFileSeparator(const char *filePath);
static char *getRelativePathToParentFolder(const char *filePath);
static char *getResolvedFilePath(const char *unresolvedFilePath);
static void macroKernel12417453134711121340(int M, int K, int N, const float *A,
  int LDA, const float *B, int LDB, float *C, int LDC);
static void macroKernel4117173156653932373(int M, int K, int N, const float *A,
  int LDA, const float *B, int LDB, float *C, int LDC);
static void macroKernel4454328187142109130(int M, int K, int N, const float *A,
  int LDA, const float *B, int LDB, float *C, int LDC);
static void macroKernel7373063509845396750(int M, int K, int N, const float *A,
  int LDA, const float *B, int LDB, float *C, int LDC);
static void main_external_interface(const unsigned char in_0[6480000], const
  float in_1[2], int in_2, boolean_T out_0[6480000], float out_1[3]);
static void matrixMultiply12417453134711121340(int M, int K, int N, int
  blockSizeM, int blockSizeK, int blockSizeN, const float *A, const float *B,
  float *C);
static void matrixMultiply4117173156653932373(int M, int K, int N, int
  blockSizeM, int blockSizeK, int blockSizeN, const float *A, const float *B,
  float *C);
static void matrixMultiply4454328187142109130(int M, int K, int N, int
  blockSizeM, int blockSizeK, int blockSizeN, const float *A, const float *B,
  float *C);
static void matrixMultiply7373063509845396750(int M, int K, int N, int
  blockSizeM, int blockSizeK, int blockSizeN, const float *A, const float *B,
  float *C);
static void maxPooling10961364285251527891(const float *inputTensor, float
  *outputTensor);
static void maxPooling13753016621916862475(const float *inputTensor, float
  *outputTensor);
static void maxPooling18144858745303349977(const float *inputTensor, float
  *outputTensor);
static void maxPooling18375657460455750414(const float *inputTensor, float
  *outputTensor);
static void maxPooling2029811058482366664(const float *inputTensor, float
  *outputTensor);
static void maxPooling3996420485521692580(const float *inputTensor, float
  *outputTensor);
static void maxPoolingKernel10961364285251527891(const float *inputBufferPtr,
  float *outputBufferPtr, int poolOutputWidthIdx, int
  startIdxWithPaddingOffsetInputTensor);
static void maxPoolingKernel13753016621916862475(const float *inputBufferPtr,
  float *outputBufferPtr, int poolOutputWidthIdx, int
  startIdxWithPaddingOffsetInputTensor);
static void maxPoolingKernel18144858745303349977(const float *inputBufferPtr,
  float *outputBufferPtr, int poolOutputWidthIdx, int
  startIdxWithPaddingOffsetInputTensor);
static void maxPoolingKernel18375657460455750414(const float *inputBufferPtr,
  float *outputBufferPtr, int poolOutputWidthIdx, int
  startIdxWithPaddingOffsetInputTensor);
static void maxPoolingKernel2029811058482366664(const float *inputBufferPtr,
  float *outputBufferPtr, int poolOutputWidthIdx, int
  startIdxWithPaddingOffsetInputTensor);
static void maxPoolingKernel3996420485521692580(const float *inputBufferPtr,
  float *outputBufferPtr, int poolOutputWidthIdx, int
  startIdxWithPaddingOffsetInputTensor);
static void microKernel10713695924587400261(int K, const float *A, int LDA,
  const float *B, int LDB, float *C, int LDC);
static void microKernel11116153436181717695(int K, const float *A, int LDA,
  const float *B, int LDB, float *C, int LDC);
static void microKernel12338766757609272626(int K, const float *A, int LDA,
  const float *B, int LDB, float *C, int LDC);
static void microKernel12357106081320476066(int K, const float *A, int LDA,
  const float *B, int LDB, float *C, int LDC);
static void microKernel12864598352212304616(int K, const float *A, int LDA,
  const float *B, int LDB, float *C, int LDC);
static void microKernel14141928391000443238(int K, const float *A, int LDA,
  const float *B, int LDB, float *C, int LDC);
static void microKernel16622016978981056782(int K, const float *A, int LDA,
  const float *B, int LDB, float *C, int LDC);
static void microKernel18002655007933138772(int K, const float *A, int LDA,
  const float *B, int LDB, float *C, int LDC);
static void microKernel18193303124806281097(int K, const float *A, int LDA,
  const float *B, int LDB, float *C, int LDC);
static void microKernel6930889964022258822(int K, const float *A, int LDA, const
  float *B, int LDB, float *C, int LDC);
static void microKernel7414168058516034042(int K, const float *A, int LDA, const
  float *B, int LDB, float *C, int LDC);
static void microKernel9975537800498894953(int K, const float *A, int LDA, const
  float *B, int LDB, float *C, int LDC);
static void packA4454328187142109130(int M, int K, const float *srcA, float
  *dstA, int LDA);
static void readDnnConstants_int32_T(int &inputBufferPtr, const char
  *unresolvedFilePath, int numElementsToRead);
static void readDnnConstants_int64_T(long &inputBufferPtr, const char
  *unresolvedFilePath, int numElementsToRead);
static void readDnnConstants_real32_T(float &inputBufferPtr, const char
  *unresolvedFilePath, int numElementsToRead);
static char *resolveBinaryFilePath(const char *unresolvedFilePath);
static float rt_powf_snf(float u0, float u1);
static char *sanitizeFilePathForHSP(const char *unSanitizedFilePath);
static void stringConcat(char *destinationString, const char *sourceString,
  size_t destBufferSize);

// Function Definitions
//
// Arguments    : const float &inputTensor
//                float &outputTensor
//                const float &weightsTensor
//                const float &biasTensor
// Return Type  : void
//
static void b_convolution(const float &inputTensor, float &outputTensor, const
  float &weightsTensor, const float &biasTensor)
{
  static float inputScratchpadBuffer[786432];
  static boolean_T bufferInitialized;
  int fusedInputWidthAndHeightIdx;
  if (!bufferInitialized) {
    std::memset(&inputScratchpadBuffer[0], 0, static_cast<unsigned int>(
      static_cast<int>(sizeof(float)) * 786432));
    bufferInitialized = true;
  }

  for (int fusedInputChannelMiniBlockIdx{0}; fusedInputChannelMiniBlockIdx <
       786432; fusedInputChannelMiniBlockIdx++) {
    fusedInputWidthAndHeightIdx = fusedInputChannelMiniBlockIdx % 1024;
    fusedInputWidthAndHeightIdx = (fusedInputWidthAndHeightIdx % 32 +
      ((fusedInputWidthAndHeightIdx >> 5) << 5)) + (static_cast<int>(
      static_cast<unsigned int>(fusedInputChannelMiniBlockIdx) >> 10) << 10);
    inputScratchpadBuffer[fusedInputWidthAndHeightIdx] = (&inputTensor)
      [fusedInputWidthAndHeightIdx];
  }

  for (int inputChannelBlockIdx{0}; inputChannelBlockIdx < 48;
       inputChannelBlockIdx++) {
    int inputChannelBlockIdxOffset;
    int inputScratchpadBufferBaseIdx;
    inputChannelBlockIdxOffset = inputChannelBlockIdx << 4;
    inputScratchpadBufferBaseIdx = inputChannelBlockIdx << 14;
    for (int fusedOutputWidthAndChannelBlockIdx{0};
         fusedOutputWidthAndChannelBlockIdx < 512;
         fusedOutputWidthAndChannelBlockIdx++) {
      int outputBufferIdx;
      int outputChannelBlockIdx;
      int weightsIdx;
      outputChannelBlockIdx = fusedOutputWidthAndChannelBlockIdx >> 5;
      fusedInputWidthAndHeightIdx = (fusedOutputWidthAndChannelBlockIdx % 32) <<
        5;
      outputBufferIdx = fusedInputWidthAndHeightIdx + (outputChannelBlockIdx <<
        14);
      fusedInputWidthAndHeightIdx += inputScratchpadBufferBaseIdx;
      weightsIdx = outputChannelBlockIdx * 12288 + inputChannelBlockIdxOffset;
      for (int fusedInputChannelMiniBlockIdx{0}; fusedInputChannelMiniBlockIdx <
           16; fusedInputChannelMiniBlockIdx++) {
        b_convolutionKernel(inputScratchpadBuffer[fusedInputWidthAndHeightIdx +
                            (fusedInputChannelMiniBlockIdx << 10)],
                            (&outputTensor)[outputBufferIdx], (&weightsTensor)
                            [weightsIdx + fusedInputChannelMiniBlockIdx],
                            (inputChannelBlockIdx == 0) &&
                            (fusedInputChannelMiniBlockIdx == 0), (&biasTensor)
                            [outputChannelBlockIdx << 4]);
      }
    }
  }
}

//
// Arguments    : const float &inputBufferPtr
//                float &outputBufferPtr
//                const float &weightsBufferPtr
//                boolean_T canInitializeOutputRegistersWithBiasValues
//                const float &biasBufferPtr
// Return Type  : void
//
static void b_convolutionKernel(const float &inputBufferPtr, float
  &outputBufferPtr, const float &weightsBufferPtr, boolean_T
  canInitializeOutputRegistersWithBiasValues, const float &biasBufferPtr)
{
  for (int outputHeightBlockIdx{0}; outputHeightBlockIdx < 32;
       outputHeightBlockIdx++) {
    float b_outputRegister;
    float c_outputRegister;
    float d_outputRegister;
    float e_outputRegister;
    float f_outputRegister;
    float g_outputRegister;
    float h_outputRegister;
    float i_outputRegister;
    float inputRegister0_0;
    float j_outputRegister;
    float k_outputRegister;
    float l_outputRegister;
    float m_outputRegister;
    float n_outputRegister;
    float o_outputRegister;
    float outputRegister;
    float p_outputRegister;
    if (canInitializeOutputRegistersWithBiasValues) {
      outputRegister = (&biasBufferPtr)[0];
      b_outputRegister = (&biasBufferPtr)[1];
      c_outputRegister = (&biasBufferPtr)[2];
      d_outputRegister = (&biasBufferPtr)[3];
      e_outputRegister = (&biasBufferPtr)[4];
      f_outputRegister = (&biasBufferPtr)[5];
      g_outputRegister = (&biasBufferPtr)[6];
      h_outputRegister = (&biasBufferPtr)[7];
      i_outputRegister = (&biasBufferPtr)[8];
      j_outputRegister = (&biasBufferPtr)[9];
      k_outputRegister = (&biasBufferPtr)[10];
      l_outputRegister = (&biasBufferPtr)[11];
      m_outputRegister = (&biasBufferPtr)[12];
      n_outputRegister = (&biasBufferPtr)[13];
      o_outputRegister = (&biasBufferPtr)[14];
      p_outputRegister = (&biasBufferPtr)[15];
    } else {
      outputRegister = (&outputBufferPtr)[outputHeightBlockIdx];
      b_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 1024];
      c_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 2048];
      d_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 3072];
      e_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 4096];
      f_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 5120];
      g_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 6144];
      h_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 7168];
      i_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 8192];
      j_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 9216];
      k_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 10240];
      l_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 11264];
      m_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 12288];
      n_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 13312];
      o_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 14336];
      p_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 15360];
    }

    inputRegister0_0 = (&inputBufferPtr)[outputHeightBlockIdx];
    (&outputBufferPtr)[outputHeightBlockIdx] = outputRegister + inputRegister0_0
      * (&weightsBufferPtr)[0];
    (&outputBufferPtr)[outputHeightBlockIdx + 1024] = b_outputRegister +
      inputRegister0_0 * (&weightsBufferPtr)[768];
    (&outputBufferPtr)[outputHeightBlockIdx + 2048] = c_outputRegister +
      inputRegister0_0 * (&weightsBufferPtr)[1536];
    (&outputBufferPtr)[outputHeightBlockIdx + 3072] = d_outputRegister +
      inputRegister0_0 * (&weightsBufferPtr)[2304];
    e_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[3072];
    f_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[3840];
    g_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[4608];
    h_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[5376];
    i_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[6144];
    j_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[6912];
    k_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[7680];
    l_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[8448];
    m_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[9216];
    n_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[9984];
    o_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[10752];
    p_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[11520];
    (&outputBufferPtr)[outputHeightBlockIdx + 4096] = e_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 5120] = f_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 6144] = g_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 7168] = h_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 8192] = i_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 9216] = j_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 10240] = k_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 11264] = l_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 12288] = m_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 13312] = n_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 14336] = o_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 15360] = p_outputRegister;
  }
}

//
// Arguments    : const float &inputTensor
//                float &outputTensor
//                const float &weightsTensor
//                const float &biasTensor
// Return Type  : void
//
static void c_convolution(const float &inputTensor, float &outputTensor, const
  float &weightsTensor, const float &biasTensor)
{
  static float inputScratchpadBuffer[1572864];
  static boolean_T bufferInitialized;
  int fusedInputWidthAndHeightIdx;
  if (!bufferInitialized) {
    std::memset(&inputScratchpadBuffer[0], 0, static_cast<unsigned int>(
      static_cast<int>(sizeof(float)) * 1572864));
    bufferInitialized = true;
  }

  for (int fusedInputChannelMiniBlockIdx{0}; fusedInputChannelMiniBlockIdx <
       1572864; fusedInputChannelMiniBlockIdx++) {
    fusedInputWidthAndHeightIdx = fusedInputChannelMiniBlockIdx % 4096;
    fusedInputWidthAndHeightIdx = (fusedInputWidthAndHeightIdx % 64 +
      ((fusedInputWidthAndHeightIdx >> 6) << 6)) + (static_cast<int>(
      static_cast<unsigned int>(fusedInputChannelMiniBlockIdx) >> 12) << 12);
    inputScratchpadBuffer[fusedInputWidthAndHeightIdx] = (&inputTensor)
      [fusedInputWidthAndHeightIdx];
  }

  for (int inputChannelBlockIdx{0}; inputChannelBlockIdx < 24;
       inputChannelBlockIdx++) {
    int inputChannelBlockIdxOffset;
    int inputScratchpadBufferBaseIdx;
    inputChannelBlockIdxOffset = inputChannelBlockIdx << 4;
    inputScratchpadBufferBaseIdx = inputChannelBlockIdx << 16;
    for (int fusedOutputWidthAndChannelBlockIdx{0};
         fusedOutputWidthAndChannelBlockIdx < 1024;
         fusedOutputWidthAndChannelBlockIdx++) {
      int outputBufferIdx;
      int outputChannelBlockIdx;
      int weightsIdx;
      outputChannelBlockIdx = fusedOutputWidthAndChannelBlockIdx >> 6;
      fusedInputWidthAndHeightIdx = (fusedOutputWidthAndChannelBlockIdx % 64) <<
        6;
      outputBufferIdx = fusedInputWidthAndHeightIdx + (outputChannelBlockIdx <<
        16);
      fusedInputWidthAndHeightIdx += inputScratchpadBufferBaseIdx;
      weightsIdx = outputChannelBlockIdx * 6144 + inputChannelBlockIdxOffset;
      for (int fusedInputChannelMiniBlockIdx{0}; fusedInputChannelMiniBlockIdx <
           16; fusedInputChannelMiniBlockIdx++) {
        c_convolutionKernel(inputScratchpadBuffer[fusedInputWidthAndHeightIdx +
                            (fusedInputChannelMiniBlockIdx << 12)],
                            (&outputTensor)[outputBufferIdx], (&weightsTensor)
                            [weightsIdx + fusedInputChannelMiniBlockIdx],
                            (inputChannelBlockIdx == 0) &&
                            (fusedInputChannelMiniBlockIdx == 0), (&biasTensor)
                            [outputChannelBlockIdx << 4]);
      }
    }
  }
}

//
// Arguments    : const float &inputBufferPtr
//                float &outputBufferPtr
//                const float &weightsBufferPtr
//                boolean_T canInitializeOutputRegistersWithBiasValues
//                const float &biasBufferPtr
// Return Type  : void
//
static void c_convolutionKernel(const float &inputBufferPtr, float
  &outputBufferPtr, const float &weightsBufferPtr, boolean_T
  canInitializeOutputRegistersWithBiasValues, const float &biasBufferPtr)
{
  for (int outputHeightBlockIdx{0}; outputHeightBlockIdx < 64;
       outputHeightBlockIdx++) {
    float b_outputRegister;
    float c_outputRegister;
    float d_outputRegister;
    float e_outputRegister;
    float f_outputRegister;
    float g_outputRegister;
    float h_outputRegister;
    float i_outputRegister;
    float inputRegister0_0;
    float j_outputRegister;
    float k_outputRegister;
    float l_outputRegister;
    float m_outputRegister;
    float n_outputRegister;
    float o_outputRegister;
    float outputRegister;
    float p_outputRegister;
    if (canInitializeOutputRegistersWithBiasValues) {
      outputRegister = (&biasBufferPtr)[0];
      b_outputRegister = (&biasBufferPtr)[1];
      c_outputRegister = (&biasBufferPtr)[2];
      d_outputRegister = (&biasBufferPtr)[3];
      e_outputRegister = (&biasBufferPtr)[4];
      f_outputRegister = (&biasBufferPtr)[5];
      g_outputRegister = (&biasBufferPtr)[6];
      h_outputRegister = (&biasBufferPtr)[7];
      i_outputRegister = (&biasBufferPtr)[8];
      j_outputRegister = (&biasBufferPtr)[9];
      k_outputRegister = (&biasBufferPtr)[10];
      l_outputRegister = (&biasBufferPtr)[11];
      m_outputRegister = (&biasBufferPtr)[12];
      n_outputRegister = (&biasBufferPtr)[13];
      o_outputRegister = (&biasBufferPtr)[14];
      p_outputRegister = (&biasBufferPtr)[15];
    } else {
      outputRegister = (&outputBufferPtr)[outputHeightBlockIdx];
      b_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 4096];
      c_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 8192];
      d_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 12288];
      e_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 16384];
      f_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 20480];
      g_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 24576];
      h_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 28672];
      i_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 32768];
      j_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 36864];
      k_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 40960];
      l_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 45056];
      m_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 49152];
      n_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 53248];
      o_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 57344];
      p_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 61440];
    }

    inputRegister0_0 = (&inputBufferPtr)[outputHeightBlockIdx];
    (&outputBufferPtr)[outputHeightBlockIdx] = outputRegister + inputRegister0_0
      * (&weightsBufferPtr)[0];
    (&outputBufferPtr)[outputHeightBlockIdx + 4096] = b_outputRegister +
      inputRegister0_0 * (&weightsBufferPtr)[384];
    (&outputBufferPtr)[outputHeightBlockIdx + 8192] = c_outputRegister +
      inputRegister0_0 * (&weightsBufferPtr)[768];
    (&outputBufferPtr)[outputHeightBlockIdx + 12288] = d_outputRegister +
      inputRegister0_0 * (&weightsBufferPtr)[1152];
    e_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[1536];
    f_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[1920];
    g_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[2304];
    h_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[2688];
    i_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[3072];
    j_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[3456];
    k_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[3840];
    l_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[4224];
    m_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[4608];
    n_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[4992];
    o_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[5376];
    p_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[5760];
    (&outputBufferPtr)[outputHeightBlockIdx + 16384] = e_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 20480] = f_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 24576] = g_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 28672] = h_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 32768] = i_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 36864] = j_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 40960] = k_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 45056] = l_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 49152] = m_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 53248] = n_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 57344] = o_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 61440] = p_outputRegister;
  }
}

//
// Arguments    : const char *unresolvedFilePath
// Return Type  : char *
//
static char *computeFilePathUsingEnvVariable(const char *unresolvedFilePath)
{
  char *coderDataPath;
  char *resolvedFilePath;
  char *stringDuplicate;

#if defined(MW_RUNTIME_DL_DATA_PATH)

  extern char* mwGetRuntimeDLDataPath(const char*);
  resolvedFilePath = mwGetRuntimeDLDataPath(unresolvedFilePath);

#elif defined(MW_DL_DATA_PATH)

  resolvedFilePath = resolveBinaryFilePath(unresolvedFilePath);

#else

  coderDataPath = getenv("CODER_DATA_PATH");
  if (coderDataPath != NULL) {
    resolvedFilePath = resolveBinaryFilePath(unresolvedFilePath);
  } else {
    size_t filePathLen;
    size_t sizeOfChar;
    filePathLen = strlen(unresolvedFilePath) + 1;
    sizeOfChar = 1;
    stringDuplicate = static_cast<char *>(calloc(filePathLen, sizeOfChar));
    stringConcat(stringDuplicate, unresolvedFilePath, filePathLen);
    resolvedFilePath = stringDuplicate;
  }

#endif

  return resolvedFilePath;
}

//
// Arguments    : const float &inputTensor
//                float &outputTensor
//                const float &weightsTensor
//                const float &biasTensor
// Return Type  : void
//
static void convolution(const float &inputTensor, float &outputTensor, const
  float &weightsTensor, const float &biasTensor)
{
  static float inputScratchpadBuffer[16875664];
  static boolean_T bufferInitialized;
  int fusedInputWidthAndHeightIdx;
  int inputChannelMiniBlockIdx;
  int inputWidthIdx;
  if (!bufferInitialized) {
    std::memset(&inputScratchpadBuffer[0], 0, static_cast<unsigned int>(
      static_cast<int>(sizeof(float)) * 16875664));
    bufferInitialized = true;
  }

  for (int fusedInputChannelMiniBlockIdx{0}; fusedInputChannelMiniBlockIdx <
       3145728; fusedInputChannelMiniBlockIdx++) {
    inputChannelMiniBlockIdx = static_cast<int>(static_cast<unsigned int>
      (fusedInputChannelMiniBlockIdx) >> 20);
    fusedInputWidthAndHeightIdx = fusedInputChannelMiniBlockIdx % 1048576;
    inputWidthIdx = static_cast<int>(static_cast<unsigned int>
      (fusedInputWidthAndHeightIdx) >> 10);
    fusedInputWidthAndHeightIdx %= 1024;
    inputScratchpadBuffer[((fusedInputWidthAndHeightIdx + inputWidthIdx * 1027)
      + inputChannelMiniBlockIdx * 1054729) + 3084] = (&inputTensor)
      [(fusedInputWidthAndHeightIdx + (inputWidthIdx << 10)) +
      (inputChannelMiniBlockIdx << 20)];
  }

  for (int fusedInputChannelMiniBlockIdx{0}; fusedInputChannelMiniBlockIdx <
       1536; fusedInputChannelMiniBlockIdx++) {
    int outputBufferIdx;
    int weightsIdx;
    inputChannelMiniBlockIdx = fusedInputChannelMiniBlockIdx >> 8;
    fusedInputWidthAndHeightIdx = fusedInputChannelMiniBlockIdx % 256;
    outputBufferIdx = (fusedInputWidthAndHeightIdx << 8) +
      (inputChannelMiniBlockIdx << 20);
    inputWidthIdx = fusedInputWidthAndHeightIdx * 4108;
    weightsIdx = inputChannelMiniBlockIdx * 2352;
    fusedInputWidthAndHeightIdx = inputChannelMiniBlockIdx << 4;
    convolutionKernel(inputScratchpadBuffer[inputWidthIdx], (&outputTensor)
                      [outputBufferIdx], (&weightsTensor)[weightsIdx], true,
                      (&biasTensor)[fusedInputWidthAndHeightIdx]);
    convolutionKernel(inputScratchpadBuffer[inputWidthIdx + 1054729],
                      (&outputTensor)[outputBufferIdx], (&weightsTensor)
                      [weightsIdx + 49], false, (&biasTensor)
                      [fusedInputWidthAndHeightIdx]);
    convolutionKernel(inputScratchpadBuffer[inputWidthIdx + 2109458],
                      (&outputTensor)[outputBufferIdx], (&weightsTensor)
                      [weightsIdx + 98], false, (&biasTensor)
                      [fusedInputWidthAndHeightIdx]);
  }
}

//
// Arguments    : const float &inputBufferPtr
//                float &outputBufferPtr
//                const float &weightsBufferPtr
//                boolean_T canInitializeOutputRegistersWithBiasValues
//                const float &biasBufferPtr
// Return Type  : void
//
static void convolutionKernel(const float &inputBufferPtr, float
  &outputBufferPtr, const float &weightsBufferPtr, boolean_T
  canInitializeOutputRegistersWithBiasValues, const float &biasBufferPtr)
{
  int idxToStrideInputBufferAlongHeight;
  idxToStrideInputBufferAlongHeight = 0;
  for (int outputHeightBlockIdx{0}; outputHeightBlockIdx < 256;
       outputHeightBlockIdx++) {
    float b_outputRegister;
    float c_outputRegister;
    float d_outputRegister;
    float e_outputRegister;
    float f_outputRegister;
    float g_outputRegister;
    float h_outputRegister;
    float i_outputRegister;
    float j_outputRegister;
    float k_outputRegister;
    float l_outputRegister;
    float m_outputRegister;
    float n_outputRegister;
    float o_outputRegister;
    float outputRegister;
    float p_outputRegister;
    int idxToStrideInputBufferAlongWidth;
    if (canInitializeOutputRegistersWithBiasValues) {
      outputRegister = (&biasBufferPtr)[0];
      b_outputRegister = (&biasBufferPtr)[1];
      c_outputRegister = (&biasBufferPtr)[2];
      d_outputRegister = (&biasBufferPtr)[3];
      e_outputRegister = (&biasBufferPtr)[4];
      f_outputRegister = (&biasBufferPtr)[5];
      g_outputRegister = (&biasBufferPtr)[6];
      h_outputRegister = (&biasBufferPtr)[7];
      i_outputRegister = (&biasBufferPtr)[8];
      j_outputRegister = (&biasBufferPtr)[9];
      k_outputRegister = (&biasBufferPtr)[10];
      l_outputRegister = (&biasBufferPtr)[11];
      m_outputRegister = (&biasBufferPtr)[12];
      n_outputRegister = (&biasBufferPtr)[13];
      o_outputRegister = (&biasBufferPtr)[14];
      p_outputRegister = (&biasBufferPtr)[15];
    } else {
      outputRegister = (&outputBufferPtr)[outputHeightBlockIdx];
      b_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 65536];
      c_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 131072];
      d_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 196608];
      e_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 262144];
      f_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 327680];
      g_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 393216];
      h_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 458752];
      i_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 524288];
      j_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 589824];
      k_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 655360];
      l_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 720896];
      m_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 786432];
      n_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 851968];
      o_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 917504];
      p_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 983040];
    }

    idxToStrideInputBufferAlongWidth = idxToStrideInputBufferAlongHeight;
    for (int kernelWidthIdx{0}; kernelWidthIdx < 7; kernelWidthIdx++) {
      for (int kernelHeightIdx{0}; kernelHeightIdx < 7; kernelHeightIdx++) {
        float inputRegister0_0;
        int outputRegister_tmp;
        inputRegister0_0 = (&inputBufferPtr)[idxToStrideInputBufferAlongWidth +
          kernelHeightIdx];
        outputRegister_tmp = kernelWidthIdx * 7 + kernelHeightIdx;
        outputRegister += inputRegister0_0 * (&weightsBufferPtr)
          [outputRegister_tmp];
        b_outputRegister += inputRegister0_0 * (&weightsBufferPtr)
          [outputRegister_tmp + 147];
        c_outputRegister += inputRegister0_0 * (&weightsBufferPtr)
          [outputRegister_tmp + 294];
        d_outputRegister += inputRegister0_0 * (&weightsBufferPtr)
          [outputRegister_tmp + 441];
        e_outputRegister += inputRegister0_0 * (&weightsBufferPtr)
          [outputRegister_tmp + 588];
        f_outputRegister += inputRegister0_0 * (&weightsBufferPtr)
          [outputRegister_tmp + 735];
        g_outputRegister += inputRegister0_0 * (&weightsBufferPtr)
          [outputRegister_tmp + 882];
        h_outputRegister += inputRegister0_0 * (&weightsBufferPtr)
          [outputRegister_tmp + 1029];
        i_outputRegister += inputRegister0_0 * (&weightsBufferPtr)
          [outputRegister_tmp + 1176];
        j_outputRegister += inputRegister0_0 * (&weightsBufferPtr)
          [outputRegister_tmp + 1323];
        k_outputRegister += inputRegister0_0 * (&weightsBufferPtr)
          [outputRegister_tmp + 1470];
        l_outputRegister += inputRegister0_0 * (&weightsBufferPtr)
          [outputRegister_tmp + 1617];
        m_outputRegister += inputRegister0_0 * (&weightsBufferPtr)
          [outputRegister_tmp + 1764];
        n_outputRegister += inputRegister0_0 * (&weightsBufferPtr)
          [outputRegister_tmp + 1911];
        o_outputRegister += inputRegister0_0 * (&weightsBufferPtr)
          [outputRegister_tmp + 2058];
        p_outputRegister += inputRegister0_0 * (&weightsBufferPtr)
          [outputRegister_tmp + 2205];
      }

      idxToStrideInputBufferAlongWidth += 1027;
    }

    (&outputBufferPtr)[outputHeightBlockIdx] = outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 65536] = b_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 131072] = c_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 196608] = d_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 262144] = e_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 327680] = f_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 393216] = g_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 458752] = h_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 524288] = i_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 589824] = j_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 655360] = k_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 720896] = l_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 786432] = m_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 851968] = n_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 917504] = o_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 983040] = p_outputRegister;
    idxToStrideInputBufferAlongHeight += 4;
  }
}

//
// Arguments    : const float &inputTensor
//                float &outputTensor
//                const float &weightsTensor
//                const float &biasTensor
// Return Type  : void
//
static void d_convolution(const float &inputTensor, float &outputTensor, const
  float &weightsTensor, const float &biasTensor)
{
  static float inputScratchpadBuffer[3145728];
  static boolean_T bufferInitialized;
  int fusedInputWidthAndHeightIdx;
  if (!bufferInitialized) {
    std::memset(&inputScratchpadBuffer[0], 0, static_cast<unsigned int>(
      static_cast<int>(sizeof(float)) * 3145728));
    bufferInitialized = true;
  }

  for (int fusedInputChannelMiniBlockIdx{0}; fusedInputChannelMiniBlockIdx <
       3145728; fusedInputChannelMiniBlockIdx++) {
    fusedInputWidthAndHeightIdx = fusedInputChannelMiniBlockIdx % 16384;
    fusedInputWidthAndHeightIdx = (fusedInputWidthAndHeightIdx % 128 +
      ((fusedInputWidthAndHeightIdx >> 7) << 7)) + (static_cast<int>(
      static_cast<unsigned int>(fusedInputChannelMiniBlockIdx) >> 14) << 14);
    inputScratchpadBuffer[fusedInputWidthAndHeightIdx] = (&inputTensor)
      [fusedInputWidthAndHeightIdx];
  }

  for (int inputChannelBlockIdx{0}; inputChannelBlockIdx < 12;
       inputChannelBlockIdx++) {
    int inputChannelBlockIdxOffset;
    int inputScratchpadBufferBaseIdx;
    inputChannelBlockIdxOffset = inputChannelBlockIdx << 4;
    inputScratchpadBufferBaseIdx = inputChannelBlockIdx << 18;
    for (int fusedOutputWidthAndChannelBlockIdx{0};
         fusedOutputWidthAndChannelBlockIdx < 2048;
         fusedOutputWidthAndChannelBlockIdx++) {
      int outputBufferIdx;
      int outputChannelBlockIdx;
      int weightsIdx;
      outputChannelBlockIdx = fusedOutputWidthAndChannelBlockIdx >> 7;
      fusedInputWidthAndHeightIdx = (fusedOutputWidthAndChannelBlockIdx % 128) <<
        7;
      outputBufferIdx = fusedInputWidthAndHeightIdx + (outputChannelBlockIdx <<
        18);
      fusedInputWidthAndHeightIdx += inputScratchpadBufferBaseIdx;
      weightsIdx = outputChannelBlockIdx * 3072 + inputChannelBlockIdxOffset;
      for (int fusedInputChannelMiniBlockIdx{0}; fusedInputChannelMiniBlockIdx <
           16; fusedInputChannelMiniBlockIdx++) {
        d_convolutionKernel(inputScratchpadBuffer[fusedInputWidthAndHeightIdx +
                            (fusedInputChannelMiniBlockIdx << 14)],
                            (&outputTensor)[outputBufferIdx], (&weightsTensor)
                            [weightsIdx + fusedInputChannelMiniBlockIdx],
                            (inputChannelBlockIdx == 0) &&
                            (fusedInputChannelMiniBlockIdx == 0), (&biasTensor)
                            [outputChannelBlockIdx << 4]);
      }
    }
  }
}

//
// Arguments    : const float &inputBufferPtr
//                float &outputBufferPtr
//                const float &weightsBufferPtr
//                boolean_T canInitializeOutputRegistersWithBiasValues
//                const float &biasBufferPtr
// Return Type  : void
//
static void d_convolutionKernel(const float &inputBufferPtr, float
  &outputBufferPtr, const float &weightsBufferPtr, boolean_T
  canInitializeOutputRegistersWithBiasValues, const float &biasBufferPtr)
{
  for (int outputHeightBlockIdx{0}; outputHeightBlockIdx < 128;
       outputHeightBlockIdx++) {
    float b_outputRegister;
    float c_outputRegister;
    float d_outputRegister;
    float e_outputRegister;
    float f_outputRegister;
    float g_outputRegister;
    float h_outputRegister;
    float i_outputRegister;
    float inputRegister0_0;
    float j_outputRegister;
    float k_outputRegister;
    float l_outputRegister;
    float m_outputRegister;
    float n_outputRegister;
    float o_outputRegister;
    float outputRegister;
    float p_outputRegister;
    if (canInitializeOutputRegistersWithBiasValues) {
      outputRegister = (&biasBufferPtr)[0];
      b_outputRegister = (&biasBufferPtr)[1];
      c_outputRegister = (&biasBufferPtr)[2];
      d_outputRegister = (&biasBufferPtr)[3];
      e_outputRegister = (&biasBufferPtr)[4];
      f_outputRegister = (&biasBufferPtr)[5];
      g_outputRegister = (&biasBufferPtr)[6];
      h_outputRegister = (&biasBufferPtr)[7];
      i_outputRegister = (&biasBufferPtr)[8];
      j_outputRegister = (&biasBufferPtr)[9];
      k_outputRegister = (&biasBufferPtr)[10];
      l_outputRegister = (&biasBufferPtr)[11];
      m_outputRegister = (&biasBufferPtr)[12];
      n_outputRegister = (&biasBufferPtr)[13];
      o_outputRegister = (&biasBufferPtr)[14];
      p_outputRegister = (&biasBufferPtr)[15];
    } else {
      outputRegister = (&outputBufferPtr)[outputHeightBlockIdx];
      b_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 16384];
      c_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 32768];
      d_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 49152];
      e_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 65536];
      f_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 81920];
      g_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 98304];
      h_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 114688];
      i_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 131072];
      j_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 147456];
      k_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 163840];
      l_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 180224];
      m_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 196608];
      n_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 212992];
      o_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 229376];
      p_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 245760];
    }

    inputRegister0_0 = (&inputBufferPtr)[outputHeightBlockIdx];
    (&outputBufferPtr)[outputHeightBlockIdx] = outputRegister + inputRegister0_0
      * (&weightsBufferPtr)[0];
    (&outputBufferPtr)[outputHeightBlockIdx + 16384] = b_outputRegister +
      inputRegister0_0 * (&weightsBufferPtr)[192];
    (&outputBufferPtr)[outputHeightBlockIdx + 32768] = c_outputRegister +
      inputRegister0_0 * (&weightsBufferPtr)[384];
    (&outputBufferPtr)[outputHeightBlockIdx + 49152] = d_outputRegister +
      inputRegister0_0 * (&weightsBufferPtr)[576];
    e_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[768];
    f_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[960];
    g_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[1152];
    h_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[1344];
    i_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[1536];
    j_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[1728];
    k_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[1920];
    l_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[2112];
    m_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[2304];
    n_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[2496];
    o_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[2688];
    p_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[2880];
    (&outputBufferPtr)[outputHeightBlockIdx + 65536] = e_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 81920] = f_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 98304] = g_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 114688] = h_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 131072] = i_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 147456] = j_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 163840] = k_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 180224] = l_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 196608] = m_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 212992] = n_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 229376] = o_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 245760] = p_outputRegister;
  }
}

//
// Arguments    : void
// Return Type  : int
//
static int div_nde_s32_floor()
{
  return 18;
}

//
// Arguments    : int numerator
//                int denominator
// Return Type  : int
//
static int div_s32_floor(int numerator, int denominator)
{
  return static_cast<int>(static_cast<unsigned int>(numerator) / static_cast<
    unsigned int>(denominator));
}

//
// Arguments    : const float &inputTensor
//                float &outputTensor
//                const float &weightsTensor
//                const float &biasTensor
// Return Type  : void
//
static void e_convolution(const float &inputTensor, float &outputTensor, const
  float &weightsTensor, const float &biasTensor)
{
  static float inputScratchpadBuffer[6291456];
  static boolean_T bufferInitialized;
  int fusedInputWidthAndHeightIdx;
  if (!bufferInitialized) {
    std::memset(&inputScratchpadBuffer[0], 0, static_cast<unsigned int>(
      static_cast<int>(sizeof(float)) * 6291456));
    bufferInitialized = true;
  }

  for (int fusedInputChannelMiniBlockIdx{0}; fusedInputChannelMiniBlockIdx <
       6291456; fusedInputChannelMiniBlockIdx++) {
    fusedInputWidthAndHeightIdx = fusedInputChannelMiniBlockIdx % 65536;
    fusedInputWidthAndHeightIdx = (fusedInputWidthAndHeightIdx % 256 +
      ((fusedInputWidthAndHeightIdx >> 8) << 8)) + (static_cast<int>(
      static_cast<unsigned int>(fusedInputChannelMiniBlockIdx) >> 16) << 16);
    inputScratchpadBuffer[fusedInputWidthAndHeightIdx] = (&inputTensor)
      [fusedInputWidthAndHeightIdx];
  }

  for (int inputChannelBlockIdx{0}; inputChannelBlockIdx < 6;
       inputChannelBlockIdx++) {
    int inputChannelBlockIdxOffset;
    int inputScratchpadBufferBaseIdx;
    inputChannelBlockIdxOffset = inputChannelBlockIdx << 4;
    inputScratchpadBufferBaseIdx = inputChannelBlockIdx << 20;
    for (int fusedOutputWidthAndChannelBlockIdx{0};
         fusedOutputWidthAndChannelBlockIdx < 4096;
         fusedOutputWidthAndChannelBlockIdx++) {
      int outputBufferIdx;
      int outputChannelBlockIdx;
      int weightsIdx;
      outputChannelBlockIdx = fusedOutputWidthAndChannelBlockIdx >> 8;
      fusedInputWidthAndHeightIdx = (fusedOutputWidthAndChannelBlockIdx % 256) <<
        8;
      outputBufferIdx = fusedInputWidthAndHeightIdx + (outputChannelBlockIdx <<
        20);
      fusedInputWidthAndHeightIdx += inputScratchpadBufferBaseIdx;
      weightsIdx = outputChannelBlockIdx * 1536 + inputChannelBlockIdxOffset;
      for (int fusedInputChannelMiniBlockIdx{0}; fusedInputChannelMiniBlockIdx <
           16; fusedInputChannelMiniBlockIdx++) {
        e_convolutionKernel(inputScratchpadBuffer[fusedInputWidthAndHeightIdx +
                            (fusedInputChannelMiniBlockIdx << 16)],
                            (&outputTensor)[outputBufferIdx], (&weightsTensor)
                            [weightsIdx + fusedInputChannelMiniBlockIdx],
                            (inputChannelBlockIdx == 0) &&
                            (fusedInputChannelMiniBlockIdx == 0), (&biasTensor)
                            [outputChannelBlockIdx << 4]);
      }
    }
  }
}

//
// Arguments    : const float &inputBufferPtr
//                float &outputBufferPtr
//                const float &weightsBufferPtr
//                boolean_T canInitializeOutputRegistersWithBiasValues
//                const float &biasBufferPtr
// Return Type  : void
//
static void e_convolutionKernel(const float &inputBufferPtr, float
  &outputBufferPtr, const float &weightsBufferPtr, boolean_T
  canInitializeOutputRegistersWithBiasValues, const float &biasBufferPtr)
{
  for (int outputHeightBlockIdx{0}; outputHeightBlockIdx < 256;
       outputHeightBlockIdx++) {
    float b_outputRegister;
    float c_outputRegister;
    float d_outputRegister;
    float e_outputRegister;
    float f_outputRegister;
    float g_outputRegister;
    float h_outputRegister;
    float i_outputRegister;
    float inputRegister0_0;
    float j_outputRegister;
    float k_outputRegister;
    float l_outputRegister;
    float m_outputRegister;
    float n_outputRegister;
    float o_outputRegister;
    float outputRegister;
    float p_outputRegister;
    if (canInitializeOutputRegistersWithBiasValues) {
      outputRegister = (&biasBufferPtr)[0];
      b_outputRegister = (&biasBufferPtr)[1];
      c_outputRegister = (&biasBufferPtr)[2];
      d_outputRegister = (&biasBufferPtr)[3];
      e_outputRegister = (&biasBufferPtr)[4];
      f_outputRegister = (&biasBufferPtr)[5];
      g_outputRegister = (&biasBufferPtr)[6];
      h_outputRegister = (&biasBufferPtr)[7];
      i_outputRegister = (&biasBufferPtr)[8];
      j_outputRegister = (&biasBufferPtr)[9];
      k_outputRegister = (&biasBufferPtr)[10];
      l_outputRegister = (&biasBufferPtr)[11];
      m_outputRegister = (&biasBufferPtr)[12];
      n_outputRegister = (&biasBufferPtr)[13];
      o_outputRegister = (&biasBufferPtr)[14];
      p_outputRegister = (&biasBufferPtr)[15];
    } else {
      outputRegister = (&outputBufferPtr)[outputHeightBlockIdx];
      b_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 65536];
      c_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 131072];
      d_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 196608];
      e_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 262144];
      f_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 327680];
      g_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 393216];
      h_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 458752];
      i_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 524288];
      j_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 589824];
      k_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 655360];
      l_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 720896];
      m_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 786432];
      n_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 851968];
      o_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 917504];
      p_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 983040];
    }

    inputRegister0_0 = (&inputBufferPtr)[outputHeightBlockIdx];
    (&outputBufferPtr)[outputHeightBlockIdx] = outputRegister + inputRegister0_0
      * (&weightsBufferPtr)[0];
    (&outputBufferPtr)[outputHeightBlockIdx + 65536] = b_outputRegister +
      inputRegister0_0 * (&weightsBufferPtr)[96];
    (&outputBufferPtr)[outputHeightBlockIdx + 131072] = c_outputRegister +
      inputRegister0_0 * (&weightsBufferPtr)[192];
    (&outputBufferPtr)[outputHeightBlockIdx + 196608] = d_outputRegister +
      inputRegister0_0 * (&weightsBufferPtr)[288];
    e_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[384];
    f_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[480];
    g_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[576];
    h_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[672];
    i_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[768];
    j_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[864];
    k_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[960];
    l_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[1056];
    m_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[1152];
    n_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[1248];
    o_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[1344];
    p_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[1440];
    (&outputBufferPtr)[outputHeightBlockIdx + 262144] = e_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 327680] = f_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 393216] = g_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 458752] = h_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 524288] = i_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 589824] = j_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 655360] = k_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 720896] = l_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 786432] = m_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 851968] = n_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 917504] = o_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 983040] = p_outputRegister;
  }
}

//
// Arguments    : const float &inputTensor
//                float &outputTensor
//                const float &weightsTensor
//                const float &biasTensor
// Return Type  : void
//
static void f_convolution(const float &inputTensor, float &outputTensor, const
  float &weightsTensor, const float &biasTensor)
{
  static float inputScratchpadBuffer[16777216];
  static boolean_T bufferInitialized;
  int fusedInputWidthAndHeightIdx;
  if (!bufferInitialized) {
    std::memset(&inputScratchpadBuffer[0], 0, sizeof(float) << 24);
    bufferInitialized = true;
  }

  for (int fusedInputChannelMiniBlockIdx{0}; fusedInputChannelMiniBlockIdx <
       16777216; fusedInputChannelMiniBlockIdx++) {
    fusedInputWidthAndHeightIdx = fusedInputChannelMiniBlockIdx % 65536;
    fusedInputWidthAndHeightIdx = (fusedInputWidthAndHeightIdx % 256 +
      ((fusedInputWidthAndHeightIdx >> 8) << 8)) + (static_cast<int>(
      static_cast<unsigned int>(fusedInputChannelMiniBlockIdx) >> 16) << 16);
    inputScratchpadBuffer[fusedInputWidthAndHeightIdx] = (&inputTensor)
      [fusedInputWidthAndHeightIdx];
  }

  for (int inputChannelBlockIdx{0}; inputChannelBlockIdx < 16;
       inputChannelBlockIdx++) {
    int inputChannelBlockIdxOffset;
    int inputScratchpadBufferBaseIdx;
    inputChannelBlockIdxOffset = inputChannelBlockIdx << 4;
    inputScratchpadBufferBaseIdx = inputChannelBlockIdx << 20;
    for (int fusedOutputWidthAndChannelBlockIdx{0};
         fusedOutputWidthAndChannelBlockIdx < 512;
         fusedOutputWidthAndChannelBlockIdx++) {
      int outputBufferIdx;
      int outputChannelBlockIdx;
      int weightsIdx;
      outputChannelBlockIdx = fusedOutputWidthAndChannelBlockIdx >> 8;
      fusedInputWidthAndHeightIdx = (fusedOutputWidthAndChannelBlockIdx % 256) <<
        8;
      outputBufferIdx = fusedInputWidthAndHeightIdx + (outputChannelBlockIdx <<
        20);
      fusedInputWidthAndHeightIdx += inputScratchpadBufferBaseIdx;
      weightsIdx = (outputChannelBlockIdx << 12) + inputChannelBlockIdxOffset;
      for (int fusedInputChannelMiniBlockIdx{0}; fusedInputChannelMiniBlockIdx <
           16; fusedInputChannelMiniBlockIdx++) {
        f_convolutionKernel(inputScratchpadBuffer[fusedInputWidthAndHeightIdx +
                            (fusedInputChannelMiniBlockIdx << 16)],
                            (&outputTensor)[outputBufferIdx], (&weightsTensor)
                            [weightsIdx + fusedInputChannelMiniBlockIdx],
                            (inputChannelBlockIdx == 0) &&
                            (fusedInputChannelMiniBlockIdx == 0), (&biasTensor)
                            [outputChannelBlockIdx << 4]);
      }
    }
  }
}

//
// Arguments    : const float &inputBufferPtr
//                float &outputBufferPtr
//                const float &weightsBufferPtr
//                boolean_T canInitializeOutputRegistersWithBiasValues
//                const float &biasBufferPtr
// Return Type  : void
//
static void f_convolutionKernel(const float &inputBufferPtr, float
  &outputBufferPtr, const float &weightsBufferPtr, boolean_T
  canInitializeOutputRegistersWithBiasValues, const float &biasBufferPtr)
{
  for (int outputHeightBlockIdx{0}; outputHeightBlockIdx < 256;
       outputHeightBlockIdx++) {
    float b_outputRegister;
    float c_outputRegister;
    float d_outputRegister;
    float e_outputRegister;
    float f_outputRegister;
    float g_outputRegister;
    float h_outputRegister;
    float i_outputRegister;
    float inputRegister0_0;
    float j_outputRegister;
    float k_outputRegister;
    float l_outputRegister;
    float m_outputRegister;
    float n_outputRegister;
    float o_outputRegister;
    float outputRegister;
    float p_outputRegister;
    if (canInitializeOutputRegistersWithBiasValues) {
      outputRegister = (&biasBufferPtr)[0];
      b_outputRegister = (&biasBufferPtr)[1];
      c_outputRegister = (&biasBufferPtr)[2];
      d_outputRegister = (&biasBufferPtr)[3];
      e_outputRegister = (&biasBufferPtr)[4];
      f_outputRegister = (&biasBufferPtr)[5];
      g_outputRegister = (&biasBufferPtr)[6];
      h_outputRegister = (&biasBufferPtr)[7];
      i_outputRegister = (&biasBufferPtr)[8];
      j_outputRegister = (&biasBufferPtr)[9];
      k_outputRegister = (&biasBufferPtr)[10];
      l_outputRegister = (&biasBufferPtr)[11];
      m_outputRegister = (&biasBufferPtr)[12];
      n_outputRegister = (&biasBufferPtr)[13];
      o_outputRegister = (&biasBufferPtr)[14];
      p_outputRegister = (&biasBufferPtr)[15];
    } else {
      outputRegister = (&outputBufferPtr)[outputHeightBlockIdx];
      b_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 65536];
      c_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 131072];
      d_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 196608];
      e_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 262144];
      f_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 327680];
      g_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 393216];
      h_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 458752];
      i_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 524288];
      j_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 589824];
      k_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 655360];
      l_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 720896];
      m_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 786432];
      n_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 851968];
      o_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 917504];
      p_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 983040];
    }

    inputRegister0_0 = (&inputBufferPtr)[outputHeightBlockIdx];
    (&outputBufferPtr)[outputHeightBlockIdx] = outputRegister + inputRegister0_0
      * (&weightsBufferPtr)[0];
    (&outputBufferPtr)[outputHeightBlockIdx + 65536] = b_outputRegister +
      inputRegister0_0 * (&weightsBufferPtr)[256];
    (&outputBufferPtr)[outputHeightBlockIdx + 131072] = c_outputRegister +
      inputRegister0_0 * (&weightsBufferPtr)[512];
    (&outputBufferPtr)[outputHeightBlockIdx + 196608] = d_outputRegister +
      inputRegister0_0 * (&weightsBufferPtr)[768];
    e_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[1024];
    f_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[1280];
    g_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[1536];
    h_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[1792];
    i_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[2048];
    j_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[2304];
    k_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[2560];
    l_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[2816];
    m_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[3072];
    n_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[3328];
    o_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[3584];
    p_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[3840];
    (&outputBufferPtr)[outputHeightBlockIdx + 262144] = e_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 327680] = f_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 393216] = g_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 458752] = h_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 524288] = i_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 589824] = j_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 655360] = k_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 720896] = l_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 786432] = m_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 851968] = n_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 917504] = o_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 983040] = p_outputRegister;
  }
}

//
// Arguments    : const float &inputTensor
//                float &outputTensor
//                const float &weightsTensor
//                const float &biasTensor
// Return Type  : void
//
static void g_convolution(const float &inputTensor, float &outputTensor, const
  float &weightsTensor, const float &biasTensor)
{
  static float inputScratchpadBuffer[4194304];
  static boolean_T bufferInitialized;
  int fusedInputWidthAndHeightIdx;
  if (!bufferInitialized) {
    std::memset(&inputScratchpadBuffer[0], 0, sizeof(float) << 22);
    bufferInitialized = true;
  }

  for (int fusedInputChannelMiniBlockIdx{0}; fusedInputChannelMiniBlockIdx <
       4194304; fusedInputChannelMiniBlockIdx++) {
    fusedInputWidthAndHeightIdx = fusedInputChannelMiniBlockIdx % 16384;
    fusedInputWidthAndHeightIdx = (fusedInputWidthAndHeightIdx % 128 +
      ((fusedInputWidthAndHeightIdx >> 7) << 7)) + (static_cast<int>(
      static_cast<unsigned int>(fusedInputChannelMiniBlockIdx) >> 14) << 14);
    inputScratchpadBuffer[fusedInputWidthAndHeightIdx] = (&inputTensor)
      [fusedInputWidthAndHeightIdx];
  }

  for (int inputChannelBlockIdx{0}; inputChannelBlockIdx < 16;
       inputChannelBlockIdx++) {
    int inputChannelBlockIdxOffset;
    int inputScratchpadBufferBaseIdx;
    inputChannelBlockIdxOffset = inputChannelBlockIdx << 4;
    inputScratchpadBufferBaseIdx = inputChannelBlockIdx << 18;
    for (int fusedOutputWidthAndChannelBlockIdx{0};
         fusedOutputWidthAndChannelBlockIdx < 512;
         fusedOutputWidthAndChannelBlockIdx++) {
      int outputBufferIdx;
      int outputChannelBlockIdx;
      int weightsIdx;
      outputChannelBlockIdx = fusedOutputWidthAndChannelBlockIdx >> 7;
      fusedInputWidthAndHeightIdx = (fusedOutputWidthAndChannelBlockIdx % 128) <<
        7;
      outputBufferIdx = fusedInputWidthAndHeightIdx + (outputChannelBlockIdx <<
        18);
      fusedInputWidthAndHeightIdx += inputScratchpadBufferBaseIdx;
      weightsIdx = (outputChannelBlockIdx << 12) + inputChannelBlockIdxOffset;
      for (int fusedInputChannelMiniBlockIdx{0}; fusedInputChannelMiniBlockIdx <
           16; fusedInputChannelMiniBlockIdx++) {
        g_convolutionKernel(inputScratchpadBuffer[fusedInputWidthAndHeightIdx +
                            (fusedInputChannelMiniBlockIdx << 14)],
                            (&outputTensor)[outputBufferIdx], (&weightsTensor)
                            [weightsIdx + fusedInputChannelMiniBlockIdx],
                            (inputChannelBlockIdx == 0) &&
                            (fusedInputChannelMiniBlockIdx == 0), (&biasTensor)
                            [outputChannelBlockIdx << 4]);
      }
    }
  }
}

//
// Arguments    : const float &inputBufferPtr
//                float &outputBufferPtr
//                const float &weightsBufferPtr
//                boolean_T canInitializeOutputRegistersWithBiasValues
//                const float &biasBufferPtr
// Return Type  : void
//
static void g_convolutionKernel(const float &inputBufferPtr, float
  &outputBufferPtr, const float &weightsBufferPtr, boolean_T
  canInitializeOutputRegistersWithBiasValues, const float &biasBufferPtr)
{
  for (int outputHeightBlockIdx{0}; outputHeightBlockIdx < 128;
       outputHeightBlockIdx++) {
    float b_outputRegister;
    float c_outputRegister;
    float d_outputRegister;
    float e_outputRegister;
    float f_outputRegister;
    float g_outputRegister;
    float h_outputRegister;
    float i_outputRegister;
    float inputRegister0_0;
    float j_outputRegister;
    float k_outputRegister;
    float l_outputRegister;
    float m_outputRegister;
    float n_outputRegister;
    float o_outputRegister;
    float outputRegister;
    float p_outputRegister;
    if (canInitializeOutputRegistersWithBiasValues) {
      outputRegister = (&biasBufferPtr)[0];
      b_outputRegister = (&biasBufferPtr)[1];
      c_outputRegister = (&biasBufferPtr)[2];
      d_outputRegister = (&biasBufferPtr)[3];
      e_outputRegister = (&biasBufferPtr)[4];
      f_outputRegister = (&biasBufferPtr)[5];
      g_outputRegister = (&biasBufferPtr)[6];
      h_outputRegister = (&biasBufferPtr)[7];
      i_outputRegister = (&biasBufferPtr)[8];
      j_outputRegister = (&biasBufferPtr)[9];
      k_outputRegister = (&biasBufferPtr)[10];
      l_outputRegister = (&biasBufferPtr)[11];
      m_outputRegister = (&biasBufferPtr)[12];
      n_outputRegister = (&biasBufferPtr)[13];
      o_outputRegister = (&biasBufferPtr)[14];
      p_outputRegister = (&biasBufferPtr)[15];
    } else {
      outputRegister = (&outputBufferPtr)[outputHeightBlockIdx];
      b_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 16384];
      c_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 32768];
      d_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 49152];
      e_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 65536];
      f_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 81920];
      g_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 98304];
      h_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 114688];
      i_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 131072];
      j_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 147456];
      k_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 163840];
      l_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 180224];
      m_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 196608];
      n_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 212992];
      o_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 229376];
      p_outputRegister = (&outputBufferPtr)[outputHeightBlockIdx + 245760];
    }

    inputRegister0_0 = (&inputBufferPtr)[outputHeightBlockIdx];
    (&outputBufferPtr)[outputHeightBlockIdx] = outputRegister + inputRegister0_0
      * (&weightsBufferPtr)[0];
    (&outputBufferPtr)[outputHeightBlockIdx + 16384] = b_outputRegister +
      inputRegister0_0 * (&weightsBufferPtr)[256];
    (&outputBufferPtr)[outputHeightBlockIdx + 32768] = c_outputRegister +
      inputRegister0_0 * (&weightsBufferPtr)[512];
    (&outputBufferPtr)[outputHeightBlockIdx + 49152] = d_outputRegister +
      inputRegister0_0 * (&weightsBufferPtr)[768];
    e_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[1024];
    f_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[1280];
    g_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[1536];
    h_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[1792];
    i_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[2048];
    j_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[2304];
    k_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[2560];
    l_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[2816];
    m_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[3072];
    n_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[3328];
    o_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[3584];
    p_outputRegister += inputRegister0_0 * (&weightsBufferPtr)[3840];
    (&outputBufferPtr)[outputHeightBlockIdx + 65536] = e_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 81920] = f_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 98304] = g_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 114688] = h_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 131072] = i_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 147456] = j_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 163840] = k_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 180224] = l_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 196608] = m_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 212992] = n_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 229376] = o_outputRegister;
    (&outputBufferPtr)[outputHeightBlockIdx + 245760] = p_outputRegister;
  }
}

//
// Arguments    : const char *unresolvedFilePath
// Return Type  : char *
//
static char *getCustomUserDataPathEnvVar(const char *unresolvedFilePath)
{
  const char *fileName;
  char *coderDataPath;
  char *resolvedFilePath;
  coderDataPath = getenv("CODER_DATA_PATH");
  if (coderDataPath != NULL) {
    int posOfLastPathSeparator;
    size_t filePathLength;
    size_t sizeOfChar;
    posOfLastPathSeparator = getPositionOfLastFileSeparator(unresolvedFilePath);
    fileName = &unresolvedFilePath[posOfLastPathSeparator];
    filePathLength = (strlen(coderDataPath) + strlen(fileName)) + 1;
    sizeOfChar = 1;
    resolvedFilePath = static_cast<char *>(calloc(filePathLength, sizeOfChar));
    stringConcat(resolvedFilePath, coderDataPath, filePathLength);
    stringConcat(resolvedFilePath, fileName, filePathLength);
  } else {
    resolvedFilePath = NULL;
  }

  return resolvedFilePath;
}

//
// Arguments    : const char *filePath
// Return Type  : int
//
static int getPositionOfLastFileSeparator(const char *filePath)
{
  int lastPathSeparatorUnix;
  int posOfLastPathSeparator;
  const char *ptrToLastPathSeparator;
  lastPathSeparatorUnix = '/';
  ptrToLastPathSeparator = strrchr(filePath, lastPathSeparatorUnix);
  if (ptrToLastPathSeparator != NULL) {
    posOfLastPathSeparator = (int)(ptrToLastPathSeparator - filePath);
  } else {
    int lastPathSeparatorWindows;
    lastPathSeparatorWindows = '\\';
    ptrToLastPathSeparator = strrchr(filePath, lastPathSeparatorWindows);
    if (ptrToLastPathSeparator != NULL) {
      posOfLastPathSeparator = (int)(ptrToLastPathSeparator - filePath);
    } else {
      posOfLastPathSeparator = -1;
    }
  }

  return posOfLastPathSeparator;
}

//
// Arguments    : const char *filePath
// Return Type  : char *
//
static char *getRelativePathToParentFolder(const char *filePath)
{
  int posOfLastPathSeparator;
  const char *fileName;
  const char *parentDir;
  char *resolvedFilePath;
  size_t filePathLength;
  size_t sizeOfChar;
  parentDir = "..";
  posOfLastPathSeparator = getPositionOfLastFileSeparator(filePath);
  fileName = &filePath[posOfLastPathSeparator];
  filePathLength = (strlen(parentDir) + strlen(fileName)) + 1;
  sizeOfChar = 1;
  resolvedFilePath = static_cast<char *>(calloc(filePathLength, sizeOfChar));
  stringConcat(resolvedFilePath, parentDir, filePathLength);
  stringConcat(resolvedFilePath, fileName, filePathLength);
  return resolvedFilePath;
}

//
// Arguments    : const char *unresolvedFilePath
// Return Type  : char *
//
static char *getResolvedFilePath(const char *unresolvedFilePath)
{
  const char *fileOpenMode;
  char *computedPathUsingEnvVars;
  char *pathUsingEnvVarAndSanitizedPath;
  char *relativePathToParent;
  char *resolvedFilePath;
  char *sanitizedFilePath;
  char *stringDuplicate;
  FILE* filePtr;
  resolvedFilePath = NULL;
  fileOpenMode = "rb";
  filePtr = fopen(unresolvedFilePath, fileOpenMode);
  if (filePtr) {
    size_t filePathLen;
    size_t sizeOfChar;
    filePathLen = strlen(unresolvedFilePath) + 1;
    sizeOfChar = 1;
    stringDuplicate = static_cast<char *>(calloc(filePathLen, sizeOfChar));
    stringConcat(stringDuplicate, unresolvedFilePath, filePathLen);
    resolvedFilePath = stringDuplicate;
    fclose(filePtr);
  } else {
    computedPathUsingEnvVars = computeFilePathUsingEnvVariable
      (unresolvedFilePath);
    filePtr = fopen(computedPathUsingEnvVars, fileOpenMode);
    if (filePtr) {
      resolvedFilePath = computedPathUsingEnvVars;
      fclose(filePtr);
    } else {
      free(computedPathUsingEnvVars);
      sanitizedFilePath = sanitizeFilePathForHSP(unresolvedFilePath);
      filePtr = fopen(sanitizedFilePath, fileOpenMode);
      if (filePtr) {
        resolvedFilePath = sanitizedFilePath;
        fclose(filePtr);
      } else {
        relativePathToParent = getRelativePathToParentFolder(unresolvedFilePath);
        filePtr = fopen(relativePathToParent, fileOpenMode);
        if (filePtr) {
          resolvedFilePath = relativePathToParent;
          fclose(filePtr);
        } else {
          free(relativePathToParent);
          pathUsingEnvVarAndSanitizedPath = computeFilePathUsingEnvVariable
            (sanitizedFilePath);
          filePtr = fopen(pathUsingEnvVarAndSanitizedPath, fileOpenMode);
          if (filePtr) {
            resolvedFilePath = pathUsingEnvVarAndSanitizedPath;
            fclose(filePtr);
          } else {
            free(pathUsingEnvVarAndSanitizedPath);
            exit(EXIT_FAILURE);
          }
        }
      }
    }
  }

  return resolvedFilePath;
}

//
// Arguments    : int M
//                int K
//                int N
//                const float *A
//                int LDA
//                const float *B
//                int LDB
//                float *C
//                int LDC
// Return Type  : void
//
static void macroKernel12417453134711121340(int M, int K, int N, const float *A,
  int LDA, const float *B, int LDB, float *C, int LDC)
{
  int i;
  int idxA;
  int idxB;
  int idxC;
  int j;
  j = 0;
  idxB = 0;
  while (j <= N - 4) {
    idxC = LDC * j;
    i = 0;
    idxA = 0;
    while (i <= M - 2) {
      microKernel7414168058516034042(K, &A[idxA], LDA, &B[idxB], LDB, &C[idxC],
        LDC);
      idxA += 2;
      idxC += 2;
      i += 2;
    }

    while (i <= M - 1) {
      microKernel18193303124806281097(K, &A[idxA], LDA, &B[idxB], LDB, &C[idxC],
        LDC);
      idxA++;
      idxC++;
      i++;
    }

    idxB += LDB << 2;
    j += 4;
  }

  while (j <= N - 1) {
    idxC = LDC * j;
    i = 0;
    idxA = 0;
    while (i <= M - 2) {
      microKernel12357106081320476066(K, &A[idxA], LDA, &B[idxB], LDB, &C[idxC],
        LDC);
      idxA += 2;
      idxC += 2;
      i += 2;
    }

    while (i <= M - 1) {
      microKernel14141928391000443238(K, &A[idxA], LDA, &B[idxB], LDB, &C[idxC],
        LDC);
      idxA++;
      idxC++;
      i++;
    }

    idxB += LDB;
    j++;
  }
}

//
// Arguments    : int M
//                int K
//                int N
//                const float *A
//                int LDA
//                const float *B
//                int LDB
//                float *C
//                int LDC
// Return Type  : void
//
static void macroKernel4117173156653932373(int M, int K, int N, const float *A,
  int LDA, const float *B, int LDB, float *C, int LDC)
{
  int idxB;
  int j;
  j = 0;
  idxB = 0;
  while (j < N) {
    int i;
    int idxA;
    int idxC;
    idxC = LDC * j;
    i = 0;
    idxA = 0;
    while (i <= M - 7) {
      microKernel11116153436181717695(K, &A[idxA], LDA, &B[idxB], LDB, &C[idxC],
        LDC);
      idxA += 7;
      idxC += 7;
      i += 7;
    }

    while (i <= M - 1) {
      microKernel6930889964022258822(K, &A[idxA], LDA, &B[idxB], LDB, &C[idxC],
        LDC);
      idxA++;
      idxC++;
      i++;
    }

    idxB += LDB;
    j++;
  }
}

//
// Arguments    : int M
//                int K
//                int N
//                const float *A
//                int LDA
//                const float *B
//                int LDB
//                float *C
//                int LDC
// Return Type  : void
//
static void macroKernel4454328187142109130(int M, int K, int N, const float *A,
  int LDA, const float *B, int LDB, float *C, int LDC)
{
  int i;
  int idxA;
  int idxB;
  int idxC;
  int j;
  j = 0;
  idxB = 0;
  while (j <= N - 4) {
    idxC = LDC * j;
    i = 0;
    idxA = 0;
    while (i <= M - 2) {
      microKernel9975537800498894953(K, &A[idxA], LDA, &B[idxB], LDB, &C[idxC],
        LDC);
      idxA += K << 1;
      idxC += 2;
      i += 2;
    }

    while (i <= M - 1) {
      microKernel10713695924587400261(K, &A[idxA], LDA, &B[idxB], LDB, &C[idxC],
        LDC);
      idxA += K;
      idxC++;
      i++;
    }

    idxB += LDB << 2;
    j += 4;
  }

  while (j <= N - 1) {
    idxC = LDC * j;
    i = 0;
    idxA = 0;
    while (i <= M - 2) {
      microKernel18002655007933138772(K, &A[idxA], LDA, &B[idxB], LDB, &C[idxC],
        LDC);
      idxA += K << 1;
      idxC += 2;
      i += 2;
    }

    while (i <= M - 1) {
      microKernel12338766757609272626(K, &A[idxA], LDA, &B[idxB], LDB, &C[idxC],
        LDC);
      idxA += K;
      idxC++;
      i++;
    }

    idxB += LDB;
    j++;
  }
}

//
// Arguments    : int M
//                int K
//                int N
//                const float *A
//                int LDA
//                const float *B
//                int LDB
//                float *C
//                int LDC
// Return Type  : void
//
static void macroKernel7373063509845396750(int M, int K, int N, const float *A,
  int LDA, const float *B, int LDB, float *C, int LDC)
{
  int idxB;
  int j;
  j = 0;
  idxB = 0;
  while (j < N) {
    int i;
    int idxA;
    int idxC;
    idxC = LDC * j;
    i = 0;
    idxA = 0;
    while (i <= M - 4) {
      microKernel12864598352212304616(K, &A[idxA], LDA, &B[idxB], LDB, &C[idxC],
        LDC);
      idxA += 4;
      idxC += 4;
      i += 4;
    }

    while (i <= M - 1) {
      microKernel16622016978981056782(K, &A[idxA], LDA, &B[idxB], LDB, &C[idxC],
        LDC);
      idxA++;
      idxC++;
      i++;
    }

    idxB += LDB;
    j++;
  }
}

//
// Arguments    : const unsigned char in_0[6480000]
//                const float in_1[2]
//                int in_2
//                boolean_T out_0[6480000]
//                float out_1[3]
// Return Type  : void
//
static void main_external_interface(const unsigned char in_0[6480000], const
  float in_1[2], int in_2, boolean_T out_0[6480000], float out_1[3])
{
  static double dv[6291456];
  static double dv5[3145728];
  static double dv10[1572864];
  static double dv23[1048576];
  static double dv15[786432];
  static double dv1[65536];
  static double dv2[65536];
  static double dv3[65536];
  static double dv4[65536];
  static double dv6[16384];
  static double dv7[16384];
  static double dv8[16384];
  static double dv9[16384];
  static double dv11[4096];
  static double dv12[4096];
  static double dv13[4096];
  static double dv14[4096];
  static double dv20[2048];
  static long __constant_1x1x1x1024x4x1xi64[4096];
  static long __constant_1x1x1024x3x1x1xi64[3072];
  static long __constant_1800xi64[1800];
  static long iv22[1800];
  static long __constant_1200x1xi64[1200];
  static long __constant_1x1x1200x1x1x1xi64[1200];
  static long __constant_1x1x1x1x1024x1xi64[1024];
  static long __constant_256xi64[256];
  static long __constant_1x96x1x1x1xi64[96];
  static long __constant_1x3x1x1x1x1xi64[3];
  static long __constant_1x3x1x1x1xi64[3];
  static long __constant_1x1x2x1xi64[2];
  static long __constant_1x1x2xi64[2];
  static float fv75[301989888];
  static float fv55[150994944];
  static float fv117[103219200];
  static float fv37[75497472];
  static float fv96[67108864];
  static float fv99[67108864];
  static float fv93[51609600];
  static float fv46[37748736];
  static float fv40[25165824];
  static float fv41[25165824];
  static float fv33[18874368];
  static float fv68[18874368];
  static float fv134[16777216];
  static float fv97[16777216];
  static float fv1[14745600];
  static float fv43[12582912];
  static float fv44[12582912];
  static float fv60[12582912];
  static float fv105[11289600];
  static float fv3[9437184];
  static float fv62[9437184];
  static float fv[6480000];
  static float fv183[6480000];
  static float fv184[6480000];
  static float fv185[6480000];
  static float fv13[6291456];
  static float fv14[6291456];
  static float fv15[6291456];
  static float fv16[6291456];
  static float fv17[6291456];
  static float fv18[6291456];
  static float fv19[6291456];
  static float fv20[6291456];
  static float fv21[6291456];
  static float fv22[6291456];
  static float fv23[6291456];
  static float fv24[6291456];
  static float fv25[6291456];
  static float fv26[6291456];
  static float fv27[6291456];
  static float fv28[6291456];
  static float fv29[6291456];
  static float fv30[6291456];
  static float fv42[6291456];
  static float fv6[6291456];
  static float fv66[6291456];
  static float fv78[6291456];
  static float fv84[5644800];
  static float fv95[4718592];
  static float fv171[4260096];
  static float fv172[4227136];
  static float fv133[4194304];
  static float fv34[4194304];
  static float fv36[4194304];
  static float fv86[3841600];
  static float fv90[3841600];
  static float fv106[3763200];
  static float fv109[3763200];
  static float fv2[3686400];
  static float fv103[3145728];
  static float fv121[3145728];
  static float fv4[3145728];
  static float fv45[3145728];
  static float fv47[3145728];
  static float fv5[3145728];
  static float fv61[3145728];
  static float fv125[2822400];
  static float __constant_3072x768xf32[2359296];
  static float __constant_3072x768xf32_186[2359296];
  static float __constant_768x3072xf32[2359296];
  static float __constant_768x3072xf32_185[2359296];
  static float fv135[2097152];
  static float fv48[2097152];
  static float fv52[2097152];
  static float fv110[1920800];
  static float fv114[1920800];
  static float fv81[1881600];
  static float fv82[1881600];
  static float fv83[1881600];
  static float fv85[1881600];
  static float __constant_768x2304xf32[1769472];
  static float fv67[1572864];
  static float fv69[1572864];
  static float fv70[1572864];
  static float fv79[1572864];
  static float fv80[1572864];
  static float fv131[1048576];
  static float fv132[1048576];
  static float fv136[1048576];
  static float fv147[1048576];
  static float fv160[1048576];
  static float fv169[1048576];
  static float fv107[940800];
  static float fv108[940800];
  static float fv126[940800];
  static float __constant_384x2304xf32[884736];
  static float fv104[786432];
  static float fv119[786432];
  static float fv122[786432];
  static float fv123[786432];
  static float __constant_1536x384xf32[589824];
  static float __constant_1536x384xf32_167[589824];
  static float __constant_1536x384xf32_170[589824];
  static float __constant_1536x384xf32_173[589824];
  static float __constant_1536x384xf32_177[589824];
  static float __constant_1536x384xf32_180[589824];
  static float __constant_1536x384xf32_184[589824];
  static float __constant_1x1x768x768xf32[589824];
  static float __constant_1x1x768x768xf32_115[589824];
  static float __constant_384x1536xf32[589824];
  static float __constant_384x1536xf32_166[589824];
  static float __constant_384x1536xf32_169[589824];
  static float __constant_384x1536xf32_172[589824];
  static float __constant_384x1536xf32_176[589824];
  static float __constant_384x1536xf32_179[589824];
  static float __constant_384x1536xf32_183[589824];
  static float __constant_2048x256xf32[524288];
  static float __constant_2048x256xf32_205[524288];
  static float __constant_256x2048xf32[524288];
  static float __constant_256x2048xf32_204[524288];
  static float fv146[524288];
  static float fv162[524288];
  static float fv63[524288];
  static float fv64[524288];
  static float fv127[480200];
  static float fv128[480200];
  static float __constant_384x1152xf32[442368];
  static float __constant_384x1152xf32_168[442368];
  static float __constant_384x1152xf32_171[442368];
  static float __constant_384x1152xf32_174[442368];
  static float __constant_384x1152xf32_178[442368];
  static float __constant_384x1152xf32_181[442368];
  static float fv100[393216];
  static float __constant_384x768xf32[294912];
  static float fv130[262144];
  static float fv179[262144];
  static float fv71[262144];
  static float fv73[262144];
  static float __constant_192x1152xf32[221184];
  static float __constant_196608xf32[196608];
  static float __constant_192x768xf32[147456];
  static float __constant_192x768xf32_164[147456];
  static float __constant_1x1x384x384xf32[147456];
  static float __constant_1x1x384x384xf32_112[147456];
  static float __constant_1x1x384x384xf32_113[147456];
  static float __constant_1x1x384x384xf32_114[147456];
  static float __constant_384x384xf32[147456];
  static float __constant_384x384xf32_175[147456];
  static float __constant_384x384xf32_182[147456];
  static float __constant_768x192xf32[147456];
  static float __constant_768x192xf32_165[147456];
  static float __constant_192x576xf32[110592];
  static float __constant_98304xf32[98304];
  static float __constant_192x384xf32[73728];
  static float __constant_256x256xf32[65536];
  static float __constant_256x256xf32_187[65536];
  static float __constant_256x256xf32_188[65536];
  static float __constant_256x256xf32_189[65536];
  static float __constant_256x256xf32_196[65536];
  static float __constant_256x256xf32_197[65536];
  static float __constant_256x256xf32_198[65536];
  static float __constant_256x256xf32_199[65536];
  static float __constant_256x256xf32_214[65536];
  static float __constant_256x256xf32_215[65536];
  static float __constant_256x256xf32_216[65536];
  static float __constant_256x256xf32_217[65536];
  static float __constant_256x256xf32_219[65536];
  static float __constant_256x256xf32_220[65536];
  static float __constant_256x256xf32_222[65536];
  static float __constant_256x256xf32_223[65536];
  static float __constant_256x256xf32_225[65536];
  static float __constant_256x256xf32_226[65536];
  static float __constant_256x64x2x2xf32[65536];
  static float fv168[65536];
  static float fv31[65536];
  static float fv32[65536];
  static float __constant_96x576xf32[55296];
  static float __constant_49152xf32[49152];
  static float fv88[38416];
  static float __constant_1x1x192x192xf32[36864];
  static float __constant_1x1x192x192xf32_111[36864];
  static float __constant_384x96xf32[36864];
  static float __constant_96x384xf32[36864];
  static float __constant_128x256xf32[32768];
  static float __constant_128x256xf32_195[32768];
  static float __constant_128x256xf32_203[32768];
  static float __constant_128x256xf32_209[32768];
  static float __constant_128x256xf32_213[32768];
  static float __constant_256x128xf32[32768];
  static float __constant_256x128xf32_190[32768];
  static float __constant_256x128xf32_191[32768];
  static float __constant_256x128xf32_192[32768];
  static float __constant_256x128xf32_193[32768];
  static float __constant_256x128xf32_194[32768];
  static float __constant_256x128xf32_200[32768];
  static float __constant_256x128xf32_201[32768];
  static float __constant_256x128xf32_202[32768];
  static float __constant_256x128xf32_206[32768];
  static float __constant_256x128xf32_207[32768];
  static float __constant_256x128xf32_208[32768];
  static float __constant_256x128xf32_210[32768];
  static float __constant_256x128xf32_211[32768];
  static float __constant_256x128xf32_212[32768];
  static float fv163[32768];
  static float fv167[32768];
  static float fv49[32768];
  static float fv51[32768];
  static float fv53[32768];
  static float __constant_96x288xf32[27648];
  static float __constant_24576xf32[24576];
  static float fv101[19600];
  static float fv87[19600];
  static float fv89[19600];
  static float fv91[19600];
  static float fv92[18816];
  static float __constant_96x192xf32[18432];
  static float __constant_16384xf32[16384];
  static float fv102[16384];
  static float fv166[16384];
  static float fv57[16384];
  static float fv58[16384];
  static float fv59[16384];
  static float fv98[16384];
  static float __constant_14112xf32[14112];
  static float fv111[9800];
  static float fv113[9800];
  static float fv115[9800];
  static float fv112[9604];
  static float __constant_1x1x96x96xf32[9216];
  static float __constant_256x32xf32[8192];
  static float __constant_256x32xf32_218[8192];
  static float __constant_256x32xf32_221[8192];
  static float __constant_256x32xf32_224[8192];
  static float __constant_64x32x2x2xf32[8192];
  static float __constant_8192xf32[8192];
  static float fv143[8192];
  static float __constant_1x96x1x8x1x8xf32[6144];
  static float fv38[6144];
  static float fv118[5376];
  static float fv94[5376];
  static float __constant_1x4704x1xf32[4704];
  static float fv116[4704];
  static float __constant_1x1x1x1024x4xf32[4096];
  static float fv144[4096];
  static float fv145[4096];
  static float fv35[4096];
  static float fv77[4096];
  static float __constant_1x1x1024x3x1xf32[3072];
  static float __constant_1x3072xf32[3072];
  static float __constant_1x3072xf32_44[3072];
  static float __constant_1x2304xf32[2304];
  static float __constant_1x2304xf32_42[2304];
  static float __constant_1x2048xf32[2048];
  static float __constant_1x2048xf32_80[2048];
  static float __constant_1x1536xf32[1536];
  static float __constant_1x1536xf32_18[1536];
  static float __constant_1x1536xf32_22[1536];
  static float __constant_1x1536xf32_26[1536];
  static float __constant_1x1536xf32_30[1536];
  static float __constant_1x1536xf32_34[1536];
  static float __constant_1x1536xf32_38[1536];
  static float __constant_1x1152xf32[1152];
  static float __constant_1x1152xf32_16[1152];
  static float __constant_1x1152xf32_20[1152];
  static float __constant_1x1152xf32_24[1152];
  static float __constant_1x1152xf32_28[1152];
  static float __constant_1x1152xf32_32[1152];
  static float __constant_1x1152xf32_36[1152];
  static float __constant_256x4xf32[1024];
  static float __constant_4x256xf32[1024];
  static float __constant_1x1x1x768xf32[768];
  static float __constant_1x1x1x768xf32_43[768];
  static float __constant_1x768x1x1xf32[768];
  static float __constant_1x768x1x1xf32_155[768];
  static float __constant_1x768x1x1xf32_156[768];
  static float __constant_1x768x1x1xf32_157[768];
  static float __constant_1x768x1x1xf32_158[768];
  static float __constant_1x768x1x1xf32_159[768];
  static float __constant_1x768xf32[768];
  static float __constant_1x768xf32_12[768];
  static float __constant_1x768xf32_40[768];
  static float __constant_1x768xf32_41[768];
  static float __constant_1x768xf32_45[768];
  static float __constant_1x576xf32[576];
  static float __constant_1x576xf32_10[576];
  static float __constant_1x1x1x384xf32[384];
  static float __constant_1x1x1x384xf32_17[384];
  static float __constant_1x1x1x384xf32_25[384];
  static float __constant_1x1x1x384xf32_33[384];
  static float __constant_1x384x1x1xf32[384];
  static float __constant_1x384x1x1xf32_128[384];
  static float __constant_1x384x1x1xf32_129[384];
  static float __constant_1x384x1x1xf32_130[384];
  static float __constant_1x384x1x1xf32_131[384];
  static float __constant_1x384x1x1xf32_132[384];
  static float __constant_1x384x1x1xf32_133[384];
  static float __constant_1x384x1x1xf32_134[384];
  static float __constant_1x384x1x1xf32_135[384];
  static float __constant_1x384x1x1xf32_136[384];
  static float __constant_1x384x1x1xf32_137[384];
  static float __constant_1x384x1x1xf32_138[384];
  static float __constant_1x384x1x1xf32_139[384];
  static float __constant_1x384x1x1xf32_140[384];
  static float __constant_1x384x1x1xf32_141[384];
  static float __constant_1x384x1x1xf32_142[384];
  static float __constant_1x384x1x1xf32_143[384];
  static float __constant_1x384x1x1xf32_144[384];
  static float __constant_1x384x1x1xf32_145[384];
  static float __constant_1x384x1x1xf32_146[384];
  static float __constant_1x384x1x1xf32_147[384];
  static float __constant_1x384x1x1xf32_148[384];
  static float __constant_1x384x1x1xf32_149[384];
  static float __constant_1x384x1x1xf32_150[384];
  static float __constant_1x384x1x1xf32_151[384];
  static float __constant_1x384x1x1xf32_152[384];
  static float __constant_1x384x1x1xf32_153[384];
  static float __constant_1x384x1x1xf32_154[384];
  static float __constant_1x384xf32[384];
  static float __constant_1x384xf32_14[384];
  static float __constant_1x384xf32_15[384];
  static float __constant_1x384xf32_19[384];
  static float __constant_1x384xf32_21[384];
  static float __constant_1x384xf32_23[384];
  static float __constant_1x384xf32_27[384];
  static float __constant_1x384xf32_29[384];
  static float __constant_1x384xf32_31[384];
  static float __constant_1x384xf32_35[384];
  static float __constant_1x384xf32_37[384];
  static float __constant_1x384xf32_39[384];
  static float __constant_1x288xf32[288];
  static float __constant_1x1x256xf32[256];
  static float __constant_1x1x256xf32_46[256];
  static float __constant_1x1x256xf32_47[256];
  static float __constant_1x1x256xf32_48[256];
  static float __constant_1x1x256xf32_49[256];
  static float __constant_1x1x256xf32_54[256];
  static float __constant_1x1x256xf32_55[256];
  static float __constant_1x1x256xf32_59[256];
  static float __constant_1x1x256xf32_60[256];
  static float __constant_1x1x256xf32_62[256];
  static float __constant_1x1x256xf32_63[256];
  static float __constant_1x1x256xf32_72[256];
  static float __constant_1x1x256xf32_73[256];
  static float __constant_1x1x256xf32_78[256];
  static float __constant_1x1x256xf32_79[256];
  static float __constant_1x1x256xf32_82[256];
  static float __constant_1x1x256xf32_83[256];
  static float __constant_1x1x256xf32_92[256];
  static float __constant_1x1x256xf32_93[256];
  static float __constant_1x256x1x1xf32[256];
  static float __constant_1x256x1xf32[256];
  static float __constant_1x256x1xf32_160[256];
  static float __constant_1x256x1xf32_161[256];
  static float __constant_1x256x1xf32_162[256];
  static float __constant_1x256x1xf32_163[256];
  static float __constant_1x256xf32[256];
  static float __constant_1x256xf32_0[256];
  static float __constant_1x256xf32_100[256];
  static float __constant_1x256xf32_102[256];
  static float __constant_1x256xf32_103[256];
  static float __constant_1x256xf32_105[256];
  static float __constant_1x256xf32_106[256];
  static float __constant_1x256xf32_50[256];
  static float __constant_1x256xf32_51[256];
  static float __constant_1x256xf32_52[256];
  static float __constant_1x256xf32_53[256];
  static float __constant_1x256xf32_58[256];
  static float __constant_1x256xf32_61[256];
  static float __constant_1x256xf32_67[256];
  static float __constant_1x256xf32_68[256];
  static float __constant_1x256xf32_69[256];
  static float __constant_1x256xf32_70[256];
  static float __constant_1x256xf32_71[256];
  static float __constant_1x256xf32_77[256];
  static float __constant_1x256xf32_81[256];
  static float __constant_1x256xf32_87[256];
  static float __constant_1x256xf32_91[256];
  static float __constant_1x256xf32_94[256];
  static float __constant_1x256xf32_95[256];
  static float __constant_1x256xf32_96[256];
  static float __constant_1x256xf32_97[256];
  static float __constant_1x256xf32_99[256];
  static float __constant_256xf32[256];
  static float __constant_256xf32_3[256];
  static float __constant_256xf32_4[256];
  static float __constant_256xf32_5[256];
  static float __constant_2x128xf32[256];
  static float __constant_1x192x1x1xf32[192];
  static float __constant_1x192x1x1xf32_121[192];
  static float __constant_1x192x1x1xf32_122[192];
  static float __constant_1x192x1x1xf32_123[192];
  static float __constant_1x192x1x1xf32_124[192];
  static float __constant_1x192x1x1xf32_125[192];
  static float __constant_1x192x1x1xf32_126[192];
  static float __constant_1x192x1x1xf32_127[192];
  static float __constant_1x192xf32[192];
  static float __constant_1x192xf32_13[192];
  static float __constant_1x192xf32_9[192];
  static float __constant_1x1x1x192xf32[192];
  static float __constant_1x1x1x192xf32_11[192];
  static float __constant_1x128xf32[128];
  static float __constant_1x128xf32_56[128];
  static float __constant_1x128xf32_57[128];
  static float __constant_1x128xf32_64[128];
  static float __constant_1x128xf32_65[128];
  static float __constant_1x128xf32_66[128];
  static float __constant_1x128xf32_74[128];
  static float __constant_1x128xf32_75[128];
  static float __constant_1x128xf32_76[128];
  static float __constant_1x128xf32_84[128];
  static float __constant_1x128xf32_85[128];
  static float __constant_1x128xf32_86[128];
  static float __constant_1x128xf32_88[128];
  static float __constant_1x128xf32_89[128];
  static float __constant_1x128xf32_90[128];
  static float __constant_1x1x1x96xf32[96];
  static float __constant_1x96x1x1xf32[96];
  static float __constant_1x96x1x1xf32_116[96];
  static float __constant_1x96x1x1xf32_117[96];
  static float __constant_1x96x1x1xf32_118[96];
  static float __constant_1x96x1x1xf32_119[96];
  static float __constant_1x96x1x1xf32_120[96];
  static float __constant_1x96xf32[96];
  static float __constant_96xf32[96];
  static float __constant_1x64x1x1xf32[64];
  static float __constant_1x64x1x1xf32_107[64];
  static float __constant_64xf32[64];
  static float __constant_64xf32_1[64];
  static float __constant_1x32xf32[32];
  static float __constant_1x32xf32_101[32];
  static float __constant_1x32xf32_104[32];
  static float __constant_1x32xf32_98[32];
  static float __constant_32xf32[32];
  static float __constant_32xf32_2[32];
  static float __constant_1x4xf32[4];
  static float __constant_1x3x1x1xf32[3];
  static float __constant_1x3x1x1xf32_110[3];
  static float __constant_1x1x2xf32[2];
  static int iv4[58982400];
  static int iv5[37748736];
  static int iv26[25920000];
  static int iv27[25920000];
  static int iv29[25920000];
  static int iv12[25165824];
  static int iv13[25165824];
  static int iv16[25165824];
  static int iv1[14745600];
  static int iv2[14745600];
  static int iv3[14745600];
  static int iv24[6480000];
  static int iv25[6480000];
  static int iv28[6480000];
  static int iv10[6291456];
  static int iv11[6291456];
  static int iv14[6291456];
  static int iv15[6291456];
  static int iv17[6291456];
  static int __constant_1x2x2x1xi32[4];
  static int __constant_1x2x2x1xi32_6[4];
  static int __constant_1x2x2x1xi32_7[4];
  static int __constant_1x4xi32[4];
  static int __constant_1x4xi32_108[4];
  static int __constant_1x4xi32_109[4];
  static int __constant_1x4xi32_8[4];
  static int __constant_1x3xi32[3];
  static boolean_T bv11[6480000];
  static boolean_T bv[65536];
  static boolean_T bv1[32768];
  static boolean_T bv2[32768];
  static boolean_T bv4[19600];
  static boolean_T bv5[19600];
  static boolean_T bv3[16384];
  static boolean_T bv6[16384];
  static boolean_T bv7[9800];
  static boolean_T bv8[9800];
  static boolean_T bufferInitialized;
  double dv16[1024];
  double dv17[1024];
  double dv18[1024];
  double dv19[1024];
  double dv21[8];
  double dv22[8];
  double d;
  double d1;
  double d2;
  long iv20[1200];
  long iv6[256];
  long iv7[256];
  long iv30[3];
  long d_i;
  float fv129[2401];
  float fv149[2048];
  float fv150[2048];
  float fv151[2048];
  float fv152[2048];
  float fv153[2048];
  float fv154[2048];
  float fv170[2048];
  float fv182[1800];
  float fv148[1536];
  float fv54[1536];
  float fv181[1200];
  float fv120[1024];
  float fv124[1024];
  float fv161[1024];
  float fv50[1024];
  float fv39[768];
  float fv56[768];
  float fv76[768];
  float fv10[512];
  float fv11[512];
  float fv12[512];
  float fv142[512];
  float fv8[512];
  float fv9[512];
  float fv74[384];
  float fv141[256];
  float fv158[256];
  float fv173[256];
  float fv65[256];
  float fv7[256];
  float fv165[128];
  float fv178[128];
  float fv155[64];
  float fv156[64];
  float fv157[64];
  float fv164[64];
  float fv72[64];
  float fv174[32];
  float fv175[32];
  float fv176[32];
  float fv177[32];
  float fv159[8];
  float fv137[4];
  float fv139[4];
  float fv140[4];
  float fv180[4];
  float fv138[2];
  float f;
  float f1;
  float f10;
  float f2;
  float f3;
  float f4;
  float f5;
  float f6;
  float f7;
  float f8;
  float f9;
  float unnamed_idx_0;
  float unnamed_idx_1;
  int iv23[1800];
  int iv21[1200];
  int iv8[256];
  int iv9[256];
  int iv18[12];
  int iv19[4];
  int iv[3];
  int i1;
  int i2;
  int i3;
  int i4;
  int i5;
  int i6;
  int i7;
  signed char iv31[3];
  boolean_T bv10[64];
  boolean_T bv9[64];
  boolean_T b;
  boolean_T b1;
  boolean_T b2;
  if (!bufferInitialized) {
    bufferInitialized = true;
    readDnnConstants_int64_T(__constant_1x3x1x1x1x1xi64[0],
      "./outDir//largeDnnConstants_140407.bin", 3);
    readDnnConstants_int64_T(__constant_1x1x1200x1x1x1xi64[0],
      "./outDir//largeDnnConstants_140391.bin", 1200);
    readDnnConstants_int64_T(__constant_1x1x1x1024x4x1xi64[0],
      "./outDir//largeDnnConstants_140375.bin", 4096);
    readDnnConstants_int32_T(__constant_1x4xi32[0],
      "./outDir//largeDnnConstants_143019.bin", 4);
    readDnnConstants_real32_T(__constant_1x1x1x1024x4xf32[0],
      "./outDir//largeDnnConstants_143212.bin", 4096);
    readDnnConstants_int64_T(__constant_1x1x1024x3x1x1xi64[0],
      "./outDir//largeDnnConstants_140359.bin", 3072);
    readDnnConstants_int64_T(__constant_1x1x1x1x1024x1xi64[0],
      "./outDir//largeDnnConstants_140343.bin", 1024);
    readDnnConstants_int32_T(__constant_1x4xi32_8[0],
      "./outDir//largeDnnConstants_143011.bin", 4);
    readDnnConstants_real32_T(__constant_1x1x1024x3x1xf32[0],
      "./outDir//largeDnnConstants_143226.bin", 3072);
    readDnnConstants_int64_T(__constant_1x1x2x1xi64[0],
      "./outDir//largeDnnConstants_140329.bin", 2);
    readDnnConstants_real32_T(__constant_1x3x1x1xf32[0],
      "./outDir//largeDnnConstants_143117.bin", 3);
    readDnnConstants_real32_T(__constant_1x3x1x1xf32_110[0],
      "./outDir//largeDnnConstants_141907.bin", 3);
    readDnnConstants_real32_T(__constant_14112xf32[0],
      "./outDir//largeDnnConstants_140454.bin", 14112);
    readDnnConstants_real32_T(__constant_96xf32[0],
      "./outDir//largeDnnConstants_143108.bin", 96);
    readDnnConstants_int64_T(__constant_256xi64[0],
      "./outDir//largeDnnConstants_143078.bin", 256);
    readDnnConstants_int64_T(__constant_1x96x1x1x1xi64[0],
      "./outDir//largeDnnConstants_140316.bin", 96);
    readDnnConstants_int32_T(__constant_1x4xi32_108[0],
      "./outDir//largeDnnConstants_141933.bin", 4);
    readDnnConstants_real32_T(__constant_1x4704x1xf32[0],
      "./outDir//largeDnnConstants_141942.bin", 4704);
    readDnnConstants_real32_T(__constant_1x96x1x8x1x8xf32[0],
      "./outDir//largeDnnConstants_141979.bin", 6144);
    readDnnConstants_real32_T(__constant_1x96x1x1xf32[0],
      "./outDir//largeDnnConstants_141787.bin", 96);
    readDnnConstants_real32_T(__constant_1x96x1x1xf32_116[0],
      "./outDir//largeDnnConstants_141775.bin", 96);
    readDnnConstants_real32_T(__constant_96x288xf32[0],
      "./outDir//largeDnnConstants_141173.bin", 27648);
    readDnnConstants_real32_T(__constant_1x288xf32[0],
      "./outDir//largeDnnConstants_143003.bin", 288);
    readDnnConstants_real32_T(__constant_1x1x96x96xf32[0],
      "./outDir//largeDnnConstants_141895.bin", 9216);
    readDnnConstants_real32_T(__constant_1x1x1x96xf32[0],
      "./outDir//largeDnnConstants_142993.bin", 96);
    readDnnConstants_real32_T(__constant_1x96x1x1xf32_117[0],
      "./outDir//largeDnnConstants_141763.bin", 96);
    readDnnConstants_real32_T(__constant_1x96x1x1xf32_118[0],
      "./outDir//largeDnnConstants_141751.bin", 96);
    readDnnConstants_real32_T(__constant_96x384xf32[0],
      "./outDir//largeDnnConstants_141165.bin", 36864);
    readDnnConstants_real32_T(__constant_1x384xf32[0],
      "./outDir//largeDnnConstants_142983.bin", 384);
    readDnnConstants_real32_T(__constant_384x96xf32[0],
      "./outDir//largeDnnConstants_141157.bin", 36864);
    readDnnConstants_real32_T(__constant_1x96xf32[0],
      "./outDir//largeDnnConstants_142975.bin", 96);
    readDnnConstants_real32_T(__constant_1x96x1x1xf32_119[0],
      "./outDir//largeDnnConstants_141739.bin", 96);
    readDnnConstants_real32_T(__constant_1x96x1x1xf32_120[0],
      "./outDir//largeDnnConstants_141727.bin", 96);
    readDnnConstants_real32_T(__constant_96x192xf32[0],
      "./outDir//largeDnnConstants_141149.bin", 18432);
    readDnnConstants_real32_T(__constant_1x192xf32[0],
      "./outDir//largeDnnConstants_142967.bin", 192);
    readDnnConstants_real32_T(__constant_96x576xf32[0],
      "./outDir//largeDnnConstants_141141.bin", 55296);
    readDnnConstants_real32_T(__constant_1x576xf32[0],
      "./outDir//largeDnnConstants_142959.bin", 576);
    readDnnConstants_real32_T(__constant_1x1x192x192xf32[0],
      "./outDir//largeDnnConstants_141883.bin", 36864);
    readDnnConstants_real32_T(__constant_1x1x1x192xf32[0],
      "./outDir//largeDnnConstants_142949.bin", 192);
    readDnnConstants_real32_T(__constant_1x192x1x1xf32[0],
      "./outDir//largeDnnConstants_141715.bin", 192);
    readDnnConstants_real32_T(__constant_1x192x1x1xf32_121[0],
      "./outDir//largeDnnConstants_141703.bin", 192);
    readDnnConstants_real32_T(__constant_192x768xf32[0],
      "./outDir//largeDnnConstants_141133.bin", 147456);
    readDnnConstants_real32_T(__constant_1x768xf32[0],
      "./outDir//largeDnnConstants_142939.bin", 768);
    readDnnConstants_real32_T(__constant_768x192xf32[0],
      "./outDir//largeDnnConstants_141125.bin", 147456);
    readDnnConstants_real32_T(__constant_1x192xf32_9[0],
      "./outDir//largeDnnConstants_142931.bin", 192);
    readDnnConstants_real32_T(__constant_1x192x1x1xf32_122[0],
      "./outDir//largeDnnConstants_141691.bin", 192);
    readDnnConstants_real32_T(__constant_1x192x1x1xf32_123[0],
      "./outDir//largeDnnConstants_141679.bin", 192);
    readDnnConstants_real32_T(__constant_192x576xf32[0],
      "./outDir//largeDnnConstants_141117.bin", 110592);
    readDnnConstants_real32_T(__constant_1x576xf32_10[0],
      "./outDir//largeDnnConstants_142923.bin", 576);
    readDnnConstants_real32_T(__constant_1x1x192x192xf32_111[0],
      "./outDir//largeDnnConstants_141871.bin", 36864);
    readDnnConstants_real32_T(__constant_1x1x1x192xf32_11[0],
      "./outDir//largeDnnConstants_142913.bin", 192);
    readDnnConstants_real32_T(__constant_1x192x1x1xf32_124[0],
      "./outDir//largeDnnConstants_141667.bin", 192);
    readDnnConstants_real32_T(__constant_1x192x1x1xf32_125[0],
      "./outDir//largeDnnConstants_141655.bin", 192);
    readDnnConstants_real32_T(__constant_192x768xf32_164[0],
      "./outDir//largeDnnConstants_141109.bin", 147456);
    readDnnConstants_real32_T(__constant_1x768xf32_12[0],
      "./outDir//largeDnnConstants_142903.bin", 768);
    readDnnConstants_real32_T(__constant_768x192xf32_165[0],
      "./outDir//largeDnnConstants_141101.bin", 147456);
    readDnnConstants_real32_T(__constant_1x192xf32_13[0],
      "./outDir//largeDnnConstants_142895.bin", 192);
    readDnnConstants_real32_T(__constant_1x192x1x1xf32_126[0],
      "./outDir//largeDnnConstants_141643.bin", 192);
    readDnnConstants_real32_T(__constant_1x192x1x1xf32_127[0],
      "./outDir//largeDnnConstants_141631.bin", 192);
    readDnnConstants_real32_T(__constant_192x384xf32[0],
      "./outDir//largeDnnConstants_141093.bin", 73728);
    readDnnConstants_real32_T(__constant_1x384xf32_14[0],
      "./outDir//largeDnnConstants_142887.bin", 384);
    readDnnConstants_real32_T(__constant_192x1152xf32[0],
      "./outDir//largeDnnConstants_141085.bin", 221184);
    readDnnConstants_real32_T(__constant_1x1152xf32[0],
      "./outDir//largeDnnConstants_142879.bin", 1152);
    readDnnConstants_real32_T(__constant_1x1x384x384xf32[0],
      "./outDir//largeDnnConstants_141859.bin", 147456);
    readDnnConstants_real32_T(__constant_1x1x1x384xf32[0],
      "./outDir//largeDnnConstants_142869.bin", 384);
    readDnnConstants_real32_T(__constant_1x384x1x1xf32[0],
      "./outDir//largeDnnConstants_141619.bin", 384);
    readDnnConstants_real32_T(__constant_1x384x1x1xf32_128[0],
      "./outDir//largeDnnConstants_141607.bin", 384);
    readDnnConstants_real32_T(__constant_384x1536xf32[0],
      "./outDir//largeDnnConstants_141077.bin", 589824);
    readDnnConstants_real32_T(__constant_1x1536xf32[0],
      "./outDir//largeDnnConstants_142859.bin", 1536);
    readDnnConstants_real32_T(__constant_1536x384xf32[0],
      "./outDir//largeDnnConstants_141069.bin", 589824);
    readDnnConstants_real32_T(__constant_1x384xf32_15[0],
      "./outDir//largeDnnConstants_142851.bin", 384);
    readDnnConstants_real32_T(__constant_1x384x1x1xf32_129[0],
      "./outDir//largeDnnConstants_141595.bin", 384);
    readDnnConstants_real32_T(__constant_1x384x1x1xf32_130[0],
      "./outDir//largeDnnConstants_141583.bin", 384);
    readDnnConstants_real32_T(__constant_384x1152xf32[0],
      "./outDir//largeDnnConstants_141061.bin", 442368);
    readDnnConstants_real32_T(__constant_1x1152xf32_16[0],
      "./outDir//largeDnnConstants_142843.bin", 1152);
    readDnnConstants_real32_T(__constant_1x1x384x384xf32_112[0],
      "./outDir//largeDnnConstants_141847.bin", 147456);
    readDnnConstants_real32_T(__constant_1x1x1x384xf32_17[0],
      "./outDir//largeDnnConstants_142833.bin", 384);
    readDnnConstants_real32_T(__constant_1x384x1x1xf32_131[0],
      "./outDir//largeDnnConstants_141571.bin", 384);
    readDnnConstants_real32_T(__constant_1x384x1x1xf32_132[0],
      "./outDir//largeDnnConstants_141559.bin", 384);
    readDnnConstants_real32_T(__constant_384x1536xf32_166[0],
      "./outDir//largeDnnConstants_141053.bin", 589824);
    readDnnConstants_real32_T(__constant_1x1536xf32_18[0],
      "./outDir//largeDnnConstants_142823.bin", 1536);
    readDnnConstants_real32_T(__constant_1536x384xf32_167[0],
      "./outDir//largeDnnConstants_141045.bin", 589824);
    readDnnConstants_real32_T(__constant_1x384xf32_19[0],
      "./outDir//largeDnnConstants_142815.bin", 384);
    readDnnConstants_real32_T(__constant_1x384x1x1xf32_133[0],
      "./outDir//largeDnnConstants_141547.bin", 384);
    readDnnConstants_real32_T(__constant_1x384x1x1xf32_134[0],
      "./outDir//largeDnnConstants_141535.bin", 384);
    readDnnConstants_real32_T(__constant_384x1152xf32_168[0],
      "./outDir//largeDnnConstants_141037.bin", 442368);
    readDnnConstants_real32_T(__constant_1x1152xf32_20[0],
      "./outDir//largeDnnConstants_142807.bin", 1152);
    readDnnConstants_real32_T(__constant_384x384xf32[0],
      "./outDir//largeDnnConstants_141029.bin", 147456);
    readDnnConstants_real32_T(__constant_1x384xf32_21[0],
      "./outDir//largeDnnConstants_142799.bin", 384);
    readDnnConstants_real32_T(__constant_1x384x1x1xf32_135[0],
      "./outDir//largeDnnConstants_141523.bin", 384);
    readDnnConstants_real32_T(__constant_1x384x1x1xf32_136[0],
      "./outDir//largeDnnConstants_141511.bin", 384);
    readDnnConstants_real32_T(__constant_384x1536xf32_169[0],
      "./outDir//largeDnnConstants_141021.bin", 589824);
    readDnnConstants_real32_T(__constant_1x1536xf32_22[0],
      "./outDir//largeDnnConstants_142791.bin", 1536);
    readDnnConstants_real32_T(__constant_1536x384xf32_170[0],
      "./outDir//largeDnnConstants_141013.bin", 589824);
    readDnnConstants_real32_T(__constant_1x384xf32_23[0],
      "./outDir//largeDnnConstants_142783.bin", 384);
    readDnnConstants_real32_T(__constant_1x384x1x1xf32_137[0],
      "./outDir//largeDnnConstants_141499.bin", 384);
    readDnnConstants_real32_T(__constant_1x384x1x1xf32_138[0],
      "./outDir//largeDnnConstants_141487.bin", 384);
    readDnnConstants_real32_T(__constant_384x1152xf32_171[0],
      "./outDir//largeDnnConstants_141005.bin", 442368);
    readDnnConstants_real32_T(__constant_1x1152xf32_24[0],
      "./outDir//largeDnnConstants_142775.bin", 1152);
    readDnnConstants_real32_T(__constant_1x1x384x384xf32_113[0],
      "./outDir//largeDnnConstants_141835.bin", 147456);
    readDnnConstants_real32_T(__constant_1x1x1x384xf32_25[0],
      "./outDir//largeDnnConstants_142765.bin", 384);
    readDnnConstants_real32_T(__constant_1x384x1x1xf32_139[0],
      "./outDir//largeDnnConstants_141475.bin", 384);
    readDnnConstants_real32_T(__constant_1x384x1x1xf32_140[0],
      "./outDir//largeDnnConstants_141463.bin", 384);
    readDnnConstants_real32_T(__constant_384x1536xf32_172[0],
      "./outDir//largeDnnConstants_140997.bin", 589824);
    readDnnConstants_real32_T(__constant_1x1536xf32_26[0],
      "./outDir//largeDnnConstants_142755.bin", 1536);
    readDnnConstants_real32_T(__constant_1536x384xf32_173[0],
      "./outDir//largeDnnConstants_140989.bin", 589824);
    readDnnConstants_real32_T(__constant_1x384xf32_27[0],
      "./outDir//largeDnnConstants_142747.bin", 384);
    readDnnConstants_real32_T(__constant_1x384x1x1xf32_141[0],
      "./outDir//largeDnnConstants_141451.bin", 384);
    readDnnConstants_real32_T(__constant_1x384x1x1xf32_142[0],
      "./outDir//largeDnnConstants_141439.bin", 384);
    readDnnConstants_real32_T(__constant_384x1152xf32_174[0],
      "./outDir//largeDnnConstants_140981.bin", 442368);
    readDnnConstants_real32_T(__constant_1x1152xf32_28[0],
      "./outDir//largeDnnConstants_142739.bin", 1152);
    readDnnConstants_real32_T(__constant_384x384xf32_175[0],
      "./outDir//largeDnnConstants_140973.bin", 147456);
    readDnnConstants_real32_T(__constant_1x384xf32_29[0],
      "./outDir//largeDnnConstants_142731.bin", 384);
    readDnnConstants_real32_T(__constant_1x384x1x1xf32_143[0],
      "./outDir//largeDnnConstants_141427.bin", 384);
    readDnnConstants_real32_T(__constant_1x384x1x1xf32_144[0],
      "./outDir//largeDnnConstants_141415.bin", 384);
    readDnnConstants_real32_T(__constant_384x1536xf32_176[0],
      "./outDir//largeDnnConstants_140965.bin", 589824);
    readDnnConstants_real32_T(__constant_1x1536xf32_30[0],
      "./outDir//largeDnnConstants_142723.bin", 1536);
    readDnnConstants_real32_T(__constant_1536x384xf32_177[0],
      "./outDir//largeDnnConstants_140957.bin", 589824);
    readDnnConstants_real32_T(__constant_1x384xf32_31[0],
      "./outDir//largeDnnConstants_142715.bin", 384);
    readDnnConstants_real32_T(__constant_1x384x1x1xf32_145[0],
      "./outDir//largeDnnConstants_141403.bin", 384);
    readDnnConstants_real32_T(__constant_1x384x1x1xf32_146[0],
      "./outDir//largeDnnConstants_141391.bin", 384);
    readDnnConstants_real32_T(__constant_384x1152xf32_178[0],
      "./outDir//largeDnnConstants_140949.bin", 442368);
    readDnnConstants_real32_T(__constant_1x1152xf32_32[0],
      "./outDir//largeDnnConstants_142707.bin", 1152);
    readDnnConstants_real32_T(__constant_1x1x384x384xf32_114[0],
      "./outDir//largeDnnConstants_141823.bin", 147456);
    readDnnConstants_real32_T(__constant_1x1x1x384xf32_33[0],
      "./outDir//largeDnnConstants_142697.bin", 384);
    readDnnConstants_real32_T(__constant_1x384x1x1xf32_147[0],
      "./outDir//largeDnnConstants_141379.bin", 384);
    readDnnConstants_real32_T(__constant_1x384x1x1xf32_148[0],
      "./outDir//largeDnnConstants_141367.bin", 384);
    readDnnConstants_real32_T(__constant_384x1536xf32_179[0],
      "./outDir//largeDnnConstants_140941.bin", 589824);
    readDnnConstants_real32_T(__constant_1x1536xf32_34[0],
      "./outDir//largeDnnConstants_142687.bin", 1536);
    readDnnConstants_real32_T(__constant_1536x384xf32_180[0],
      "./outDir//largeDnnConstants_140933.bin", 589824);
    readDnnConstants_real32_T(__constant_1x384xf32_35[0],
      "./outDir//largeDnnConstants_142679.bin", 384);
    readDnnConstants_real32_T(__constant_1x384x1x1xf32_149[0],
      "./outDir//largeDnnConstants_141355.bin", 384);
    readDnnConstants_real32_T(__constant_1x384x1x1xf32_150[0],
      "./outDir//largeDnnConstants_141343.bin", 384);
    readDnnConstants_real32_T(__constant_384x1152xf32_181[0],
      "./outDir//largeDnnConstants_140925.bin", 442368);
    readDnnConstants_real32_T(__constant_1x1152xf32_36[0],
      "./outDir//largeDnnConstants_142671.bin", 1152);
    readDnnConstants_real32_T(__constant_384x384xf32_182[0],
      "./outDir//largeDnnConstants_140917.bin", 147456);
    readDnnConstants_real32_T(__constant_1x384xf32_37[0],
      "./outDir//largeDnnConstants_142663.bin", 384);
    readDnnConstants_real32_T(__constant_1x384x1x1xf32_151[0],
      "./outDir//largeDnnConstants_141331.bin", 384);
    readDnnConstants_real32_T(__constant_1x384x1x1xf32_152[0],
      "./outDir//largeDnnConstants_141319.bin", 384);
    readDnnConstants_real32_T(__constant_384x1536xf32_183[0],
      "./outDir//largeDnnConstants_140909.bin", 589824);
    readDnnConstants_real32_T(__constant_1x1536xf32_38[0],
      "./outDir//largeDnnConstants_142655.bin", 1536);
    readDnnConstants_real32_T(__constant_1536x384xf32_184[0],
      "./outDir//largeDnnConstants_140901.bin", 589824);
    readDnnConstants_real32_T(__constant_1x384xf32_39[0],
      "./outDir//largeDnnConstants_142647.bin", 384);
    readDnnConstants_real32_T(__constant_1x384x1x1xf32_153[0],
      "./outDir//largeDnnConstants_141307.bin", 384);
    readDnnConstants_real32_T(__constant_1x384x1x1xf32_154[0],
      "./outDir//largeDnnConstants_141295.bin", 384);
    readDnnConstants_real32_T(__constant_384x768xf32[0],
      "./outDir//largeDnnConstants_140893.bin", 294912);
    readDnnConstants_real32_T(__constant_1x768xf32_40[0],
      "./outDir//largeDnnConstants_142639.bin", 768);
    readDnnConstants_real32_T(__constant_384x2304xf32[0],
      "./outDir//largeDnnConstants_140885.bin", 884736);
    readDnnConstants_real32_T(__constant_1x2304xf32[0],
      "./outDir//largeDnnConstants_142631.bin", 2304);
    readDnnConstants_real32_T(__constant_1x1x768x768xf32[0],
      "./outDir//largeDnnConstants_141811.bin", 589824);
    readDnnConstants_real32_T(__constant_1x1x1x768xf32[0],
      "./outDir//largeDnnConstants_142621.bin", 768);
    readDnnConstants_real32_T(__constant_1x768x1x1xf32[0],
      "./outDir//largeDnnConstants_141283.bin", 768);
    readDnnConstants_real32_T(__constant_1x768x1x1xf32_155[0],
      "./outDir//largeDnnConstants_141271.bin", 768);
    readDnnConstants_real32_T(__constant_768x3072xf32[0],
      "./outDir//largeDnnConstants_140877.bin", 2359296);
    readDnnConstants_real32_T(__constant_1x3072xf32[0],
      "./outDir//largeDnnConstants_142611.bin", 3072);
    readDnnConstants_real32_T(__constant_3072x768xf32[0],
      "./outDir//largeDnnConstants_140869.bin", 2359296);
    readDnnConstants_real32_T(__constant_1x768xf32_41[0],
      "./outDir//largeDnnConstants_142603.bin", 768);
    readDnnConstants_real32_T(__constant_1x768x1x1xf32_156[0],
      "./outDir//largeDnnConstants_141259.bin", 768);
    readDnnConstants_real32_T(__constant_1x768x1x1xf32_157[0],
      "./outDir//largeDnnConstants_141247.bin", 768);
    readDnnConstants_real32_T(__constant_768x2304xf32[0],
      "./outDir//largeDnnConstants_140861.bin", 1769472);
    readDnnConstants_real32_T(__constant_1x2304xf32_42[0],
      "./outDir//largeDnnConstants_142595.bin", 2304);
    readDnnConstants_real32_T(__constant_1x1x768x768xf32_115[0],
      "./outDir//largeDnnConstants_141799.bin", 589824);
    readDnnConstants_real32_T(__constant_1x1x1x768xf32_43[0],
      "./outDir//largeDnnConstants_142585.bin", 768);
    readDnnConstants_real32_T(__constant_1x768x1x1xf32_158[0],
      "./outDir//largeDnnConstants_141235.bin", 768);
    readDnnConstants_real32_T(__constant_1x768x1x1xf32_159[0],
      "./outDir//largeDnnConstants_141223.bin", 768);
    readDnnConstants_real32_T(__constant_768x3072xf32_185[0],
      "./outDir//largeDnnConstants_140853.bin", 2359296);
    readDnnConstants_real32_T(__constant_1x3072xf32_44[0],
      "./outDir//largeDnnConstants_142575.bin", 3072);
    readDnnConstants_real32_T(__constant_3072x768xf32_186[0],
      "./outDir//largeDnnConstants_140845.bin", 2359296);
    readDnnConstants_real32_T(__constant_1x768xf32_45[0],
      "./outDir//largeDnnConstants_142567.bin", 768);
    readDnnConstants_real32_T(__constant_196608xf32[0],
      "./outDir//largeDnnConstants_140448.bin", 196608);
    readDnnConstants_real32_T(__constant_256xf32[0],
      "./outDir//largeDnnConstants_143102.bin", 256);
    readDnnConstants_real32_T(__constant_98304xf32[0],
      "./outDir//largeDnnConstants_140442.bin", 98304);
    readDnnConstants_real32_T(__constant_256xf32_3[0],
      "./outDir//largeDnnConstants_143096.bin", 256);
    readDnnConstants_real32_T(__constant_49152xf32[0],
      "./outDir//largeDnnConstants_140436.bin", 49152);
    readDnnConstants_real32_T(__constant_256xf32_4[0],
      "./outDir//largeDnnConstants_143090.bin", 256);
    readDnnConstants_real32_T(__constant_24576xf32[0],
      "./outDir//largeDnnConstants_140430.bin", 24576);
    readDnnConstants_real32_T(__constant_256xf32_5[0],
      "./outDir//largeDnnConstants_143084.bin", 256);
    readDnnConstants_real32_T(__constant_8192xf32[0],
      "./outDir//largeDnnConstants_140424.bin", 8192);
    readDnnConstants_real32_T(__constant_32xf32_2[0],
      "./outDir//largeDnnConstants_143126.bin", 32);
    readDnnConstants_real32_T(__constant_16384xf32[0],
      "./outDir//largeDnnConstants_140418.bin", 16384);
    readDnnConstants_real32_T(__constant_64xf32_1[0],
      "./outDir//largeDnnConstants_143132.bin", 64);
    readDnnConstants_real32_T(__constant_1x256x1xf32[0],
      "./outDir//largeDnnConstants_143140.bin", 256);
    readDnnConstants_real32_T(__constant_1x1x2xf32[0],
      "./outDir//largeDnnConstants_143070.bin", 2);
    readDnnConstants_int64_T(__constant_1x1x2xi64[0],
      "./outDir//largeDnnConstants_142558.bin", 2);
    readDnnConstants_int32_T(__constant_1x2x2x1xi32[0],
      "./outDir//largeDnnConstants_143059.bin", 4);
    readDnnConstants_int32_T(__constant_1x2x2x1xi32_7[0],
      "./outDir//largeDnnConstants_143035.bin", 4);
    readDnnConstants_int32_T(__constant_1x2x2x1xi32_6[0],
      "./outDir//largeDnnConstants_143047.bin", 4);
    readDnnConstants_int32_T(__constant_1x3xi32[0],
      "./outDir//largeDnnConstants_141925.bin", 3);
    readDnnConstants_real32_T(__constant_2x128xf32[0],
      "./outDir//largeDnnConstants_140837.bin", 256);
    readDnnConstants_real32_T(__constant_1x1x256xf32[0],
      "./outDir//largeDnnConstants_142548.bin", 256);
    readDnnConstants_real32_T(__constant_1x1x256xf32_46[0],
      "./outDir//largeDnnConstants_142538.bin", 256);
    readDnnConstants_real32_T(__constant_1x1x256xf32_47[0],
      "./outDir//largeDnnConstants_142528.bin", 256);
    readDnnConstants_real32_T(__constant_1x1x256xf32_48[0],
      "./outDir//largeDnnConstants_142518.bin", 256);
    readDnnConstants_real32_T(__constant_1x1x256xf32_49[0],
      "./outDir//largeDnnConstants_142508.bin", 256);
    readDnnConstants_real32_T(__constant_1x256xf32_0[0],
      "./outDir//largeDnnConstants_143149.bin", 256);
    readDnnConstants_real32_T(__constant_1x256xf32[0],
      "./outDir//largeDnnConstants_143157.bin", 256);
    readDnnConstants_real32_T(__constant_4x256xf32[0],
      "./outDir//largeDnnConstants_143165.bin", 1024);
    readDnnConstants_real32_T(__constant_1x256x1x1xf32[0],
      "./outDir//largeDnnConstants_143239.bin", 256);
    readDnnConstants_real32_T(__constant_256x256xf32[0],
      "./outDir//largeDnnConstants_140829.bin", 65536);
    readDnnConstants_real32_T(__constant_1x256xf32_50[0],
      "./outDir//largeDnnConstants_142499.bin", 256);
    readDnnConstants_real32_T(__constant_256x256xf32_187[0],
      "./outDir//largeDnnConstants_140821.bin", 65536);
    readDnnConstants_real32_T(__constant_1x256xf32_51[0],
      "./outDir//largeDnnConstants_142491.bin", 256);
    readDnnConstants_real32_T(__constant_256x256xf32_188[0],
      "./outDir//largeDnnConstants_140813.bin", 65536);
    readDnnConstants_real32_T(__constant_1x256xf32_52[0],
      "./outDir//largeDnnConstants_142483.bin", 256);
    readDnnConstants_real32_T(__constant_256x256xf32_189[0],
      "./outDir//largeDnnConstants_140805.bin", 65536);
    readDnnConstants_real32_T(__constant_1x256xf32_53[0],
      "./outDir//largeDnnConstants_142475.bin", 256);
    readDnnConstants_real32_T(__constant_1x1x256xf32_54[0],
      "./outDir//largeDnnConstants_142466.bin", 256);
    readDnnConstants_real32_T(__constant_1x1x256xf32_55[0],
      "./outDir//largeDnnConstants_142456.bin", 256);
    readDnnConstants_real32_T(__constant_256x128xf32[0],
      "./outDir//largeDnnConstants_140797.bin", 32768);
    readDnnConstants_real32_T(__constant_1x128xf32[0],
      "./outDir//largeDnnConstants_142447.bin", 128);
    readDnnConstants_real32_T(__constant_256x128xf32_190[0],
      "./outDir//largeDnnConstants_140789.bin", 32768);
    readDnnConstants_real32_T(__constant_1x128xf32_56[0],
      "./outDir//largeDnnConstants_142439.bin", 128);
    readDnnConstants_real32_T(__constant_256x128xf32_191[0],
      "./outDir//largeDnnConstants_140781.bin", 32768);
    readDnnConstants_real32_T(__constant_1x128xf32_57[0],
      "./outDir//largeDnnConstants_142431.bin", 128);
    readDnnConstants_real32_T(__constant_128x256xf32[0],
      "./outDir//largeDnnConstants_140773.bin", 32768);
    readDnnConstants_real32_T(__constant_1x256xf32_58[0],
      "./outDir//largeDnnConstants_142423.bin", 256);
    readDnnConstants_real32_T(__constant_1x1x256xf32_59[0],
      "./outDir//largeDnnConstants_142414.bin", 256);
    readDnnConstants_real32_T(__constant_1x1x256xf32_60[0],
      "./outDir//largeDnnConstants_142404.bin", 256);
    readDnnConstants_real32_T(__constant_256x2048xf32[0],
      "./outDir//largeDnnConstants_140765.bin", 524288);
    readDnnConstants_real32_T(__constant_1x2048xf32[0],
      "./outDir//largeDnnConstants_142395.bin", 2048);
    readDnnConstants_real32_T(__constant_2048x256xf32[0],
      "./outDir//largeDnnConstants_140757.bin", 524288);
    readDnnConstants_real32_T(__constant_1x256xf32_61[0],
      "./outDir//largeDnnConstants_142387.bin", 256);
    readDnnConstants_real32_T(__constant_1x1x256xf32_62[0],
      "./outDir//largeDnnConstants_142378.bin", 256);
    readDnnConstants_real32_T(__constant_1x1x256xf32_63[0],
      "./outDir//largeDnnConstants_142368.bin", 256);
    readDnnConstants_real32_T(__constant_256x128xf32_192[0],
      "./outDir//largeDnnConstants_140749.bin", 32768);
    readDnnConstants_real32_T(__constant_1x128xf32_64[0],
      "./outDir//largeDnnConstants_142359.bin", 128);
    readDnnConstants_real32_T(__constant_256x128xf32_193[0],
      "./outDir//largeDnnConstants_140741.bin", 32768);
    readDnnConstants_real32_T(__constant_1x128xf32_65[0],
      "./outDir//largeDnnConstants_142351.bin", 128);
    readDnnConstants_real32_T(__constant_256x128xf32_194[0],
      "./outDir//largeDnnConstants_140733.bin", 32768);
    readDnnConstants_real32_T(__constant_1x128xf32_66[0],
      "./outDir//largeDnnConstants_142343.bin", 128);
    readDnnConstants_real32_T(__constant_128x256xf32_195[0],
      "./outDir//largeDnnConstants_140725.bin", 32768);
    readDnnConstants_real32_T(__constant_1x256xf32_67[0],
      "./outDir//largeDnnConstants_142335.bin", 256);
    readDnnConstants_real32_T(__constant_1x256x1xf32_160[0],
      "./outDir//largeDnnConstants_141212.bin", 256);
    readDnnConstants_real32_T(__constant_1x256x1xf32_161[0],
      "./outDir//largeDnnConstants_141202.bin", 256);
    readDnnConstants_real32_T(__constant_256x256xf32_196[0],
      "./outDir//largeDnnConstants_140717.bin", 65536);
    readDnnConstants_real32_T(__constant_1x256xf32_68[0],
      "./outDir//largeDnnConstants_142327.bin", 256);
    readDnnConstants_real32_T(__constant_256x256xf32_197[0],
      "./outDir//largeDnnConstants_140709.bin", 65536);
    readDnnConstants_real32_T(__constant_1x256xf32_69[0],
      "./outDir//largeDnnConstants_142319.bin", 256);
    readDnnConstants_real32_T(__constant_256x256xf32_198[0],
      "./outDir//largeDnnConstants_140701.bin", 65536);
    readDnnConstants_real32_T(__constant_1x256xf32_70[0],
      "./outDir//largeDnnConstants_142311.bin", 256);
    readDnnConstants_real32_T(__constant_256x256xf32_199[0],
      "./outDir//largeDnnConstants_140693.bin", 65536);
    readDnnConstants_real32_T(__constant_1x256xf32_71[0],
      "./outDir//largeDnnConstants_142303.bin", 256);
    readDnnConstants_real32_T(__constant_1x1x256xf32_72[0],
      "./outDir//largeDnnConstants_142294.bin", 256);
    readDnnConstants_real32_T(__constant_1x1x256xf32_73[0],
      "./outDir//largeDnnConstants_142284.bin", 256);
    readDnnConstants_real32_T(__constant_256x128xf32_200[0],
      "./outDir//largeDnnConstants_140685.bin", 32768);
    readDnnConstants_real32_T(__constant_1x128xf32_74[0],
      "./outDir//largeDnnConstants_142275.bin", 128);
    readDnnConstants_real32_T(__constant_256x128xf32_201[0],
      "./outDir//largeDnnConstants_140677.bin", 32768);
    readDnnConstants_real32_T(__constant_1x128xf32_75[0],
      "./outDir//largeDnnConstants_142267.bin", 128);
    readDnnConstants_real32_T(__constant_256x128xf32_202[0],
      "./outDir//largeDnnConstants_140669.bin", 32768);
    readDnnConstants_real32_T(__constant_1x128xf32_76[0],
      "./outDir//largeDnnConstants_142259.bin", 128);
    readDnnConstants_real32_T(__constant_128x256xf32_203[0],
      "./outDir//largeDnnConstants_140661.bin", 32768);
    readDnnConstants_real32_T(__constant_1x256xf32_77[0],
      "./outDir//largeDnnConstants_142251.bin", 256);
    readDnnConstants_real32_T(__constant_1x1x256xf32_78[0],
      "./outDir//largeDnnConstants_142242.bin", 256);
    readDnnConstants_real32_T(__constant_1x1x256xf32_79[0],
      "./outDir//largeDnnConstants_142232.bin", 256);
    readDnnConstants_real32_T(__constant_256x2048xf32_204[0],
      "./outDir//largeDnnConstants_140653.bin", 524288);
    readDnnConstants_real32_T(__constant_1x2048xf32_80[0],
      "./outDir//largeDnnConstants_142223.bin", 2048);
    readDnnConstants_real32_T(__constant_2048x256xf32_205[0],
      "./outDir//largeDnnConstants_140645.bin", 524288);
    readDnnConstants_real32_T(__constant_1x256xf32_81[0],
      "./outDir//largeDnnConstants_142215.bin", 256);
    readDnnConstants_real32_T(__constant_1x1x256xf32_82[0],
      "./outDir//largeDnnConstants_142206.bin", 256);
    readDnnConstants_real32_T(__constant_1x1x256xf32_83[0],
      "./outDir//largeDnnConstants_142196.bin", 256);
    readDnnConstants_real32_T(__constant_256x128xf32_206[0],
      "./outDir//largeDnnConstants_140637.bin", 32768);
    readDnnConstants_real32_T(__constant_1x128xf32_84[0],
      "./outDir//largeDnnConstants_142187.bin", 128);
    readDnnConstants_real32_T(__constant_256x128xf32_207[0],
      "./outDir//largeDnnConstants_140629.bin", 32768);
    readDnnConstants_real32_T(__constant_1x128xf32_85[0],
      "./outDir//largeDnnConstants_142179.bin", 128);
    readDnnConstants_real32_T(__constant_256x128xf32_208[0],
      "./outDir//largeDnnConstants_140621.bin", 32768);
    readDnnConstants_real32_T(__constant_1x128xf32_86[0],
      "./outDir//largeDnnConstants_142171.bin", 128);
    readDnnConstants_real32_T(__constant_128x256xf32_209[0],
      "./outDir//largeDnnConstants_140613.bin", 32768);
    readDnnConstants_real32_T(__constant_1x256xf32_87[0],
      "./outDir//largeDnnConstants_142163.bin", 256);
    readDnnConstants_real32_T(__constant_1x256x1xf32_162[0],
      "./outDir//largeDnnConstants_141192.bin", 256);
    readDnnConstants_real32_T(__constant_1x256x1xf32_163[0],
      "./outDir//largeDnnConstants_141182.bin", 256);
    readDnnConstants_real32_T(__constant_256x128xf32_210[0],
      "./outDir//largeDnnConstants_140605.bin", 32768);
    readDnnConstants_real32_T(__constant_1x128xf32_88[0],
      "./outDir//largeDnnConstants_142155.bin", 128);
    readDnnConstants_real32_T(__constant_256x128xf32_211[0],
      "./outDir//largeDnnConstants_140597.bin", 32768);
    readDnnConstants_real32_T(__constant_1x128xf32_89[0],
      "./outDir//largeDnnConstants_142147.bin", 128);
    readDnnConstants_real32_T(__constant_256x128xf32_212[0],
      "./outDir//largeDnnConstants_140589.bin", 32768);
    readDnnConstants_real32_T(__constant_1x128xf32_90[0],
      "./outDir//largeDnnConstants_142139.bin", 128);
    readDnnConstants_real32_T(__constant_128x256xf32_213[0],
      "./outDir//largeDnnConstants_140581.bin", 32768);
    readDnnConstants_real32_T(__constant_1x256xf32_91[0],
      "./outDir//largeDnnConstants_142131.bin", 256);
    readDnnConstants_real32_T(__constant_1x1x256xf32_92[0],
      "./outDir//largeDnnConstants_142122.bin", 256);
    readDnnConstants_real32_T(__constant_1x1x256xf32_93[0],
      "./outDir//largeDnnConstants_142112.bin", 256);
    readDnnConstants_real32_T(__constant_256x64x2x2xf32[0],
      "./outDir//largeDnnConstants_143175.bin", 65536);
    readDnnConstants_real32_T(__constant_64xf32[0],
      "./outDir//largeDnnConstants_143184.bin", 64);
    readDnnConstants_real32_T(__constant_1x64x1x1xf32[0],
      "./outDir//largeDnnConstants_141965.bin", 64);
    readDnnConstants_real32_T(__constant_1x64x1x1xf32_107[0],
      "./outDir//largeDnnConstants_141953.bin", 64);
    readDnnConstants_real32_T(__constant_64x32x2x2xf32[0],
      "./outDir//largeDnnConstants_143193.bin", 8192);
    readDnnConstants_real32_T(__constant_32xf32[0],
      "./outDir//largeDnnConstants_143202.bin", 32);
    readDnnConstants_real32_T(__constant_256x256xf32_214[0],
      "./outDir//largeDnnConstants_140573.bin", 65536);
    readDnnConstants_real32_T(__constant_1x256xf32_94[0],
      "./outDir//largeDnnConstants_142103.bin", 256);
    readDnnConstants_real32_T(__constant_256x256xf32_215[0],
      "./outDir//largeDnnConstants_140565.bin", 65536);
    readDnnConstants_real32_T(__constant_1x256xf32_95[0],
      "./outDir//largeDnnConstants_142095.bin", 256);
    readDnnConstants_real32_T(__constant_256x32xf32[0],
      "./outDir//largeDnnConstants_140557.bin", 8192);
    readDnnConstants_real32_T(__constant_1x32xf32[0],
      "./outDir//largeDnnConstants_142087.bin", 32);
    readDnnConstants_real32_T(__constant_256x256xf32_216[0],
      "./outDir//largeDnnConstants_140549.bin", 65536);
    readDnnConstants_real32_T(__constant_1x256xf32_96[0],
      "./outDir//largeDnnConstants_142079.bin", 256);
    readDnnConstants_real32_T(__constant_256x256xf32_217[0],
      "./outDir//largeDnnConstants_140541.bin", 65536);
    readDnnConstants_real32_T(__constant_1x256xf32_97[0],
      "./outDir//largeDnnConstants_142071.bin", 256);
    readDnnConstants_real32_T(__constant_256x32xf32_218[0],
      "./outDir//largeDnnConstants_140533.bin", 8192);
    readDnnConstants_real32_T(__constant_1x32xf32_98[0],
      "./outDir//largeDnnConstants_142063.bin", 32);
    readDnnConstants_real32_T(__constant_256x256xf32_219[0],
      "./outDir//largeDnnConstants_140525.bin", 65536);
    readDnnConstants_real32_T(__constant_1x256xf32_99[0],
      "./outDir//largeDnnConstants_142055.bin", 256);
    readDnnConstants_real32_T(__constant_256x256xf32_220[0],
      "./outDir//largeDnnConstants_140517.bin", 65536);
    readDnnConstants_real32_T(__constant_1x256xf32_100[0],
      "./outDir//largeDnnConstants_142047.bin", 256);
    readDnnConstants_real32_T(__constant_256x32xf32_221[0],
      "./outDir//largeDnnConstants_140509.bin", 8192);
    readDnnConstants_real32_T(__constant_1x32xf32_101[0],
      "./outDir//largeDnnConstants_142039.bin", 32);
    readDnnConstants_real32_T(__constant_256x256xf32_222[0],
      "./outDir//largeDnnConstants_140501.bin", 65536);
    readDnnConstants_real32_T(__constant_1x256xf32_102[0],
      "./outDir//largeDnnConstants_142031.bin", 256);
    readDnnConstants_real32_T(__constant_256x256xf32_223[0],
      "./outDir//largeDnnConstants_140493.bin", 65536);
    readDnnConstants_real32_T(__constant_1x256xf32_103[0],
      "./outDir//largeDnnConstants_142023.bin", 256);
    readDnnConstants_real32_T(__constant_256x32xf32_224[0],
      "./outDir//largeDnnConstants_140485.bin", 8192);
    readDnnConstants_real32_T(__constant_1x32xf32_104[0],
      "./outDir//largeDnnConstants_142015.bin", 32);
    readDnnConstants_real32_T(__constant_256x256xf32_225[0],
      "./outDir//largeDnnConstants_140477.bin", 65536);
    readDnnConstants_real32_T(__constant_1x256xf32_105[0],
      "./outDir//largeDnnConstants_142007.bin", 256);
    readDnnConstants_real32_T(__constant_256x256xf32_226[0],
      "./outDir//largeDnnConstants_140469.bin", 65536);
    readDnnConstants_real32_T(__constant_1x256xf32_106[0],
      "./outDir//largeDnnConstants_141999.bin", 256);
    readDnnConstants_real32_T(__constant_256x4xf32[0],
      "./outDir//largeDnnConstants_140461.bin", 1024);
    readDnnConstants_real32_T(__constant_1x4xf32[0],
      "./outDir//largeDnnConstants_141991.bin", 4);
    readDnnConstants_int64_T(__constant_1200x1xi64[0],
      "./outDir//largeDnnConstants_140305.bin", 1200);
    readDnnConstants_int64_T(__constant_1800xi64[0],
      "./outDir//largeDnnConstants_143026.bin", 1800);
    readDnnConstants_int64_T(__constant_1x3x1x1x1xi64[0],
      "./outDir//largeDnnConstants_140294.bin", 3);
    readDnnConstants_int32_T(__constant_1x4xi32_109[0],
      "./outDir//largeDnnConstants_141917.bin", 4);
  }

  bufferInitialized = true;
  for (int i{0}; i < 3; i++) {
    for (int b_i{0}; b_i < 1200; b_i++) {
      for (int c_i{0}; c_i < 1800; c_i++) {
        fv[(2160000 * i + 1800 * b_i) + c_i] = static_cast<float>(static_cast<
          unsigned char>(((signed char *)&in_0[0])[(5400 * b_i + 3 * c_i) + i]))
          * 0.003921569F;
      }
    }

    d_i = __constant_1x3x1x1x1x1xi64[i];
    if (static_cast<int>(d_i) < 0) {
      iv[i] = static_cast<int>(d_i) + 3;
    } else {
      iv[i] = static_cast<int>(d_i);
    }

    i2 = iv[i];
    for (int c_i{0}; c_i < 1200; c_i++) {
      d_i = __constant_1x1x1200x1x1x1xi64[c_i];
      for (int b_i{0}; b_i < 1024; b_i++) {
        i1 = (4915200 * i + (c_i << 12)) + (b_i << 2);
        iv1[i1] = i2;
        if (static_cast<int>(d_i) < 0) {
          iv2[i1] = static_cast<int>(d_i) + 1200;
        } else {
          iv2[i1] = static_cast<int>(d_i);
        }

        iv1[i1 + 1] = i2;
        if (static_cast<int>(d_i) < 0) {
          iv2[i1 + 1] = static_cast<int>(d_i) + 1200;
        } else {
          iv2[i1 + 1] = static_cast<int>(d_i);
        }

        iv1[i1 + 2] = i2;
        if (static_cast<int>(d_i) < 0) {
          iv2[i1 + 2] = static_cast<int>(d_i) + 1200;
        } else {
          iv2[i1 + 2] = static_cast<int>(d_i);
        }

        iv1[i1 + 3] = i2;
        if (static_cast<int>(d_i) < 0) {
          iv2[i1 + 3] = static_cast<int>(d_i) + 1200;
        } else {
          iv2[i1 + 3] = static_cast<int>(d_i);
        }
      }

      for (int b_i{0}; b_i < 4096; b_i++) {
        d_i = __constant_1x1x1x1024x4x1xi64[b_i];
        if (static_cast<int>(d_i) < 0) {
          iv3[(b_i + i * 4915200) + (c_i << 12)] = static_cast<int>(d_i) + 1800;
        } else {
          iv3[(b_i + i * 4915200) + (c_i << 12)] = static_cast<int>(d_i);
        }
      }

      for (int b_i{0}; b_i < 1024; b_i++) {
        i1 = (19660800 * i + (c_i << 14)) + (b_i << 4);
        iv4[i1] = 0;
        i3 = (4915200 * i + (c_i << 12)) + (b_i << 2);
        iv4[i1 + 1] = iv1[i3];
        iv4[i1 + 2] = iv2[i3];
        iv4[i1 + 4] = 0;
        iv4[i1 + 5] = iv1[i3 + 1];
        iv4[i1 + 6] = iv2[i3 + 1];
        iv4[i1 + 8] = 0;
        iv4[i1 + 9] = iv1[i3 + 2];
        iv4[i1 + 10] = iv2[i3 + 2];
        iv4[i1 + 12] = 0;
        iv4[i1 + 13] = iv1[i3 + 3];
        iv4[i1 + 14] = iv2[i3 + 3];
      }
    }
  }

  for (int b_i{0}; b_i < 3; b_i++) {
    for (int c_i{0}; c_i < 1200; c_i++) {
      for (int i{0}; i < 1024; i++) {
        i3 = (4915200 * b_i + (c_i << 12)) + (i << 2);
        i2 = (19660800 * b_i + (c_i << 14)) + (i << 4);
        iv4[i2 + 3] = iv3[i3];
        iv4[i2 + 7] = iv3[i3 + 1];
        iv4[i2 + 11] = iv3[i3 + 2];
        iv4[i2 + 15] = iv3[i3 + 3];
      }
    }
  }

  i1 = __constant_1x4xi32[3];
  i2 = __constant_1x4xi32[2];
  i3 = __constant_1x4xi32[1];
  i4 = __constant_1x4xi32[0];
  for (int b_i{0}; b_i < 14745600; b_i++) {
    i5 = b_i << 2;
    fv1[b_i] = fv[((iv4[i5 + 3] * i1 + iv4[i5 + 2] * i2) + iv4[i5 + 1] * i3) +
      iv4[i5] * i4];
  }

  std::memset(&fv2[0], 0, 3686400U * sizeof(float));
  for (int e_i{0}; e_i < 3; e_i++) {
    for (int b_i{0}; b_i < 1200; b_i++) {
      for (int c_i{0}; c_i < 1024; c_i++) {
        i1 = (1228800 * e_i + (b_i << 10)) + c_i;
        i2 = c_i << 2;
        i3 = (4915200 * e_i + (b_i << 12)) + i2;
        fv2[i1] = fv1[i3 + 3] * __constant_1x1x1x1024x4xf32[i2 + 3] + (fv1[i3 +
          2] * __constant_1x1x1x1024x4xf32[i2 + 2] + (fv1[i3 + 1] *
          __constant_1x1x1x1024x4xf32[i2 + 1] + (fv1[i3] *
          __constant_1x1x1x1024x4xf32[i2] + fv2[i1])));
      }
    }

    i1 = iv[e_i];
    for (int c_i{0}; c_i < 1024; c_i++) {
      for (int i{0}; i < 3; i++) {
        d_i = __constant_1x1x1024x3x1x1xi64[3 * c_i + i];
        if (static_cast<int>(d_i) < 0) {
          i2 = static_cast<int>(d_i) + 1200;
        } else {
          i2 = static_cast<int>(d_i);
        }

        for (int f_i{0}; f_i < 1024; f_i++) {
          d_i = __constant_1x1x1x1x1024x1xi64[f_i];
          if (static_cast<int>(d_i) < 0) {
            i3 = static_cast<int>(d_i) + 1024;
          } else {
            i3 = static_cast<int>(d_i);
          }

          i4 = ((12582912 * e_i + 12288 * c_i) + (i << 12)) + (f_i << 2);
          iv5[i4] = 0;
          iv5[i4 + 1] = i1;
          iv5[i4 + 2] = i2;
          iv5[i4 + 3] = i3;
        }
      }
    }
  }

  i1 = __constant_1x4xi32_8[3];
  i2 = __constant_1x4xi32_8[2];
  i3 = __constant_1x4xi32_8[1];
  i4 = __constant_1x4xi32_8[0];
  for (int b_i{0}; b_i < 9437184; b_i++) {
    i5 = b_i << 2;
    fv3[b_i] = fv2[((iv5[i5 + 3] * i1 + iv5[i5 + 2] * i2) + iv5[i5 + 1] * i3) +
      iv5[i5] * i4];
  }

  std::memset(&fv4[0], 0, 3145728U * sizeof(float));
  for (int b_i{0}; b_i < 3; b_i++) {
    for (int c_i{0}; c_i < 1024; c_i++) {
      for (int f_i{0}; f_i < 3; f_i++) {
        f = __constant_1x1x1024x3x1xf32[3 * c_i + f_i];
        for (int i{0}; i < 1024; i++) {
          i1 = ((b_i << 20) + (c_i << 10)) + i;
          fv4[i1] += fv3[((3145728 * b_i + 3072 * c_i) + (f_i << 10)) + i] * f;
        }
      }
    }
  }

  if (__constant_1x1x2x1xi64[0] == 0L) {
    unnamed_idx_0 = in_1[0] * 0.00055555557F * 1024.0F;
  } else {
    unnamed_idx_0 = in_1[0];
  }

  if (__constant_1x1x2x1xi64[1] == 0L) {
    unnamed_idx_1 = in_1[0] * 0.00055555557F * 1024.0F;
  } else {
    unnamed_idx_1 = in_1[1];
  }

  for (int b_i{0}; b_i < 3; b_i++) {
    f = __constant_1x3x1x1xf32[b_i];
    f1 = __constant_1x3x1x1xf32_110[b_i];
    i1 = b_i << 20;
    for (int c_i{0}; c_i < 1024; c_i++) {
      for (int i{0}; i < 1024; i++) {
        fv5[(i1 + (c_i << 10)) + i] = (fv4[(i1 + (i << 10)) + c_i] - f) * f1;
      }
    }
  }

  convolution(fv5[0], fv6[0], __constant_14112xf32[0], __constant_96xf32[0]);
  for (int b_i{0}; b_i < 256; b_i++) {
    f = (static_cast<float>(__constant_256xi64[b_i]) + 0.5F) * 0.02734375F -
      0.5F;
    f1 = std::floor(f);
    f -= f1;
    if (!(f < 1.0F)) {
      f = 1.0F;
    }

    if (!(f > 0.0F)) {
      f = 0.0F;
    }

    fv7[b_i] = f;
    iv6[b_i] = static_cast<long>(f1);
    iv7[b_i] = static_cast<long>(f1);
    iv8[b_i] = static_cast<int>(static_cast<long>(f1));
    iv9[b_i] = static_cast<int>(static_cast<long>(f1));
    fv10[b_i] = f;
    fv10[b_i + 256] = 1.0F - f;
    fv9[b_i] = f + 1.0F;
    fv9[b_i + 256] = 2.0F - f;
  }

  for (int b_i{0}; b_i < 512; b_i++) {
    f = fv9[b_i];
    fv8[b_i] = ((f * -0.75F - -3.75F) * f - 6.0F) * f - -3.0F;
    f = fv10[b_i];
    fv9[b_i] = (f * 1.25F - 2.25F) * f * f + 1.0F;
  }

  for (int b_i{0}; b_i < 256; b_i++) {
    f = fv7[b_i];
    fv11[b_i] = f;
    fv11[b_i + 256] = 1.0F - f;
    fv12[b_i] = f + 1.0F;
    fv12[b_i + 256] = 2.0F - f;
  }

  for (int b_i{0}; b_i < 512; b_i++) {
    f = fv12[b_i];
    fv10[b_i] = ((f * -0.75F - -3.75F) * f - 6.0F) * f - -3.0F;
    f = fv11[b_i];
    fv12[b_i] = (f * 1.25F - 2.25F) * f * f + 1.0F;
  }

  for (int c_i{0}; c_i < 96; c_i++) {
    d_i = __constant_1x96x1x1x1xi64[c_i];
    if (static_cast<int>(d_i) < 0) {
      i3 = static_cast<int>(d_i) + 96;
    } else {
      i3 = static_cast<int>(d_i);
    }

    i4 = c_i << 18;
    for (int i{0}; i < 256; i++) {
      if (iv8[i] - 1 > 0) {
        d_i = iv8[i] - 1;
      } else {
        d_i = 0L;
      }

      if (static_cast<int>(d_i) < 6) {
        i5 = static_cast<int>(d_i);
      } else {
        i5 = 6;
      }

      if (i5 < 0) {
        i5 += 7;
      }

      i2 = i << 10;
      for (int f_i{0}; f_i < 256; f_i++) {
        if (iv9[f_i] - 1 > 0) {
          d_i = iv9[f_i] - 1;
        } else {
          d_i = 0L;
        }

        if (static_cast<int>(d_i) < 6) {
          i6 = static_cast<int>(d_i);
        } else {
          i6 = 6;
        }

        if (i6 < 0) {
          i6 += 7;
        }

        iv11[((c_i << 16) + (i << 8)) + f_i] = i6;
        i1 = f_i << 2;
        i7 = (i4 + i2) + i1;
        iv16[i7] = 0;
        iv16[i7 + 1] = i3;
        i1 = (i1 + i2) + i4;
        iv12[i1] = 0;
        iv12[i1 + 1] = i3;
        iv12[i1 + 3] = iv16[i1 + 3];
        iv12[i7 + 2] = i5;
        iv13[i1] = 0;
        iv13[i1 + 1] = i3;
        iv13[i1 + 2] = i5;
        iv13[i7 + 3] = i6;
      }
    }
  }

  i1 = __constant_1x4xi32_108[3];
  i2 = __constant_1x4xi32_108[2];
  i3 = __constant_1x4xi32_108[1];
  i4 = __constant_1x4xi32_108[0];
  for (int b_i{0}; b_i < 6291456; b_i++) {
    iv10[b_i] = 0;
    i5 = b_i << 2;
    fv13[b_i] = __constant_1x4704x1xf32[((iv13[i5 + 3] * i1 + iv13[i5 + 2] * i2)
      + iv13[i5 + 1] * i3) + iv13[i5] * i4];
  }

  for (int c_i{0}; c_i < 96; c_i++) {
    i1 = c_i << 18;
    for (int i{0}; i < 256; i++) {
      i3 = i << 10;
      for (int f_i{0}; f_i < 256; f_i++) {
        if (iv6[f_i] > 0L) {
          d_i = iv6[f_i];
        } else {
          d_i = 0L;
        }

        if (d_i < 6L) {
          i4 = static_cast<int>(d_i);
        } else {
          i4 = 6;
        }

        if (i4 < 0) {
          i4 += 7;
        }

        iv14[((c_i << 16) + (i << 8)) + f_i] = i4;
        i5 = f_i << 2;
        i2 = (i5 + i3) + i1;
        iv13[i2] = iv12[i2];
        iv13[i2 + 1] = iv12[i2 + 1];
        iv13[i2 + 2] = iv12[i2 + 2];
        iv13[((i1 + i3) + i5) + 3] = i4;
      }
    }
  }

  i1 = __constant_1x4xi32_108[3];
  i2 = __constant_1x4xi32_108[2];
  i3 = __constant_1x4xi32_108[1];
  i4 = __constant_1x4xi32_108[0];
  for (int c_i{0}; c_i < 6291456; c_i++) {
    i5 = c_i << 2;
    fv14[c_i] = __constant_1x4704x1xf32[((iv13[i5 + 3] * i1 + iv13[i5 + 2] * i2)
      + iv13[i5 + 1] * i3) + iv13[i5] * i4];
  }

  for (int c_i{0}; c_i < 96; c_i++) {
    i1 = c_i << 18;
    for (int i{0}; i < 256; i++) {
      i3 = i << 10;
      for (int f_i{0}; f_i < 256; f_i++) {
        if (iv9[f_i] + 1 > 0) {
          d_i = iv9[f_i] + 1;
        } else {
          d_i = 0L;
        }

        if (static_cast<int>(d_i) < 6) {
          i4 = static_cast<int>(d_i);
        } else {
          i4 = 6;
        }

        if (i4 < 0) {
          i4 += 7;
        }

        iv15[((c_i << 16) + (i << 8)) + f_i] = i4;
        i5 = f_i << 2;
        i2 = (i5 + i3) + i1;
        iv13[i2] = iv12[i2];
        iv13[i2 + 1] = iv12[i2 + 1];
        iv13[i2 + 2] = iv12[i2 + 2];
        iv13[((i1 + i3) + i5) + 3] = i4;
      }
    }
  }

  i1 = __constant_1x4xi32_108[3];
  i2 = __constant_1x4xi32_108[2];
  i3 = __constant_1x4xi32_108[1];
  i4 = __constant_1x4xi32_108[0];
  for (int i{0}; i < 6291456; i++) {
    i5 = i << 2;
    fv15[i] = __constant_1x4704x1xf32[((iv13[i5 + 3] * i1 + iv13[i5 + 2] * i2) +
      iv13[i5 + 1] * i3) + iv13[i5] * i4];
  }

  for (int b_i{0}; b_i < 96; b_i++) {
    for (int c_i{0}; c_i < 256; c_i++) {
      for (int i{0}; i < 256; i++) {
        if (iv9[i] + 2 > 0) {
          d_i = iv9[i] + 2;
        } else {
          d_i = 0L;
        }

        if (static_cast<int>(d_i) < 6) {
          i1 = static_cast<int>(d_i);
        } else {
          i1 = 6;
        }

        if (i1 < 0) {
          i1 += 7;
        }

        iv17[((b_i << 16) + (c_i << 8)) + i] = i1;
        iv12[(((b_i << 18) + (c_i << 10)) + (i << 2)) + 3] = i1;
      }
    }
  }

  i1 = __constant_1x4xi32_108[3];
  i2 = __constant_1x4xi32_108[2];
  i3 = __constant_1x4xi32_108[1];
  i4 = __constant_1x4xi32_108[0];
  for (int f_i{0}; f_i < 6291456; f_i++) {
    i5 = f_i << 2;
    fv16[f_i] = __constant_1x4704x1xf32[((iv12[i5 + 3] * i1 + iv12[i5 + 2] * i2)
      + iv12[i5 + 1] * i3) + iv12[i5] * i4];
  }

  for (int c_i{0}; c_i < 96; c_i++) {
    i3 = c_i << 18;
    for (int i{0}; i < 256; i++) {
      if (iv7[i] > 0L) {
        d_i = iv7[i];
      } else {
        d_i = 0L;
      }

      if (d_i < 6L) {
        i4 = static_cast<int>(d_i);
      } else {
        i4 = 6;
      }

      if (i4 < 0) {
        i4 += 7;
      }

      i5 = i << 10;
      for (int f_i{0}; f_i < 256; f_i++) {
        i1 = f_i << 2;
        i2 = (i1 + i5) + i3;
        i6 = iv16[i2];
        iv12[i2] = i6;
        i7 = iv16[i2 + 1];
        iv12[i2 + 1] = i7;
        iv12[i2 + 3] = iv16[i2 + 3];
        i1 += i3 + i5;
        iv12[i1 + 2] = i4;
        iv13[i2] = i6;
        iv13[i2 + 1] = i7;
        iv13[i2 + 2] = i4;
        iv13[i1 + 3] = iv11[((c_i << 16) + (i << 8)) + f_i];
      }
    }
  }

  i1 = __constant_1x4xi32_108[3];
  i2 = __constant_1x4xi32_108[2];
  i3 = __constant_1x4xi32_108[1];
  i4 = __constant_1x4xi32_108[0];
  for (int e_i{0}; e_i < 6291456; e_i++) {
    i5 = e_i << 2;
    fv17[e_i] = __constant_1x4704x1xf32[((iv13[i5 + 3] * i1 + iv13[i5 + 2] * i2)
      + iv13[i5 + 1] * i3) + iv13[i5] * i4];
  }

  for (int c_i{0}; c_i < 96; c_i++) {
    i1 = c_i << 18;
    for (int i{0}; i < 256; i++) {
      i2 = i << 10;
      for (int f_i{0}; f_i < 256; f_i++) {
        i3 = f_i << 2;
        i4 = (i3 + i2) + i1;
        iv13[i4] = iv12[i4];
        iv13[i4 + 1] = iv12[i4 + 1];
        iv13[i4 + 2] = iv12[i4 + 2];
        iv13[((i1 + i2) + i3) + 3] = iv14[((c_i << 16) + (i << 8)) + f_i];
      }
    }
  }

  i1 = __constant_1x4xi32_108[3];
  i2 = __constant_1x4xi32_108[2];
  i3 = __constant_1x4xi32_108[1];
  i4 = __constant_1x4xi32_108[0];
  for (int b_i{0}; b_i < 6291456; b_i++) {
    i5 = b_i << 2;
    fv18[b_i] = __constant_1x4704x1xf32[((iv13[i5 + 3] * i1 + iv13[i5 + 2] * i2)
      + iv13[i5 + 1] * i3) + iv13[i5] * i4];
  }

  for (int c_i{0}; c_i < 96; c_i++) {
    i1 = c_i << 18;
    for (int i{0}; i < 256; i++) {
      i2 = i << 10;
      for (int f_i{0}; f_i < 256; f_i++) {
        i3 = f_i << 2;
        i4 = (i3 + i2) + i1;
        iv13[i4] = iv12[i4];
        iv13[i4 + 1] = iv12[i4 + 1];
        iv13[i4 + 2] = iv12[i4 + 2];
        iv13[((i1 + i2) + i3) + 3] = iv15[((c_i << 16) + (i << 8)) + f_i];
      }
    }
  }

  i1 = __constant_1x4xi32_108[3];
  i2 = __constant_1x4xi32_108[2];
  i3 = __constant_1x4xi32_108[1];
  i4 = __constant_1x4xi32_108[0];
  for (int c_i{0}; c_i < 6291456; c_i++) {
    i5 = c_i << 2;
    fv19[c_i] = __constant_1x4704x1xf32[((iv13[i5 + 3] * i1 + iv13[i5 + 2] * i2)
      + iv13[i5 + 1] * i3) + iv13[i5] * i4];
  }

  for (int b_i{0}; b_i < 96; b_i++) {
    for (int c_i{0}; c_i < 256; c_i++) {
      for (int i{0}; i < 256; i++) {
        iv12[(((b_i << 18) + (c_i << 10)) + (i << 2)) + 3] = iv17[((b_i << 16) +
          (c_i << 8)) + i];
      }
    }
  }

  i1 = __constant_1x4xi32_108[3];
  i2 = __constant_1x4xi32_108[2];
  i3 = __constant_1x4xi32_108[1];
  i4 = __constant_1x4xi32_108[0];
  for (int c_i{0}; c_i < 6291456; c_i++) {
    i5 = c_i << 2;
    fv20[c_i] = __constant_1x4704x1xf32[((iv12[i5 + 3] * i1 + iv12[i5 + 2] * i2)
      + iv12[i5 + 1] * i3) + iv12[i5] * i4];
  }

  for (int c_i{0}; c_i < 96; c_i++) {
    i3 = c_i << 18;
    for (int i{0}; i < 256; i++) {
      if (iv8[i] + 1 > 0) {
        d_i = iv8[i] + 1;
      } else {
        d_i = 0L;
      }

      if (static_cast<int>(d_i) < 6) {
        i4 = static_cast<int>(d_i);
      } else {
        i4 = 6;
      }

      if (i4 < 0) {
        i4 += 7;
      }

      i5 = i << 10;
      for (int f_i{0}; f_i < 256; f_i++) {
        i1 = f_i << 2;
        i2 = (i1 + i5) + i3;
        i6 = iv16[i2];
        iv12[i2] = i6;
        i7 = iv16[i2 + 1];
        iv12[i2 + 1] = i7;
        iv12[i2 + 3] = iv16[i2 + 3];
        i1 += i3 + i5;
        iv12[i1 + 2] = i4;
        iv13[i2] = i6;
        iv13[i2 + 1] = i7;
        iv13[i2 + 2] = i4;
        iv13[i1 + 3] = iv11[((c_i << 16) + (i << 8)) + f_i];
      }
    }
  }

  i1 = __constant_1x4xi32_108[3];
  i2 = __constant_1x4xi32_108[2];
  i3 = __constant_1x4xi32_108[1];
  i4 = __constant_1x4xi32_108[0];
  for (int c_i{0}; c_i < 6291456; c_i++) {
    i5 = c_i << 2;
    fv21[c_i] = __constant_1x4704x1xf32[((iv13[i5 + 3] * i1 + iv13[i5 + 2] * i2)
      + iv13[i5 + 1] * i3) + iv13[i5] * i4];
  }

  for (int c_i{0}; c_i < 96; c_i++) {
    i1 = c_i << 18;
    for (int i{0}; i < 256; i++) {
      i2 = i << 10;
      for (int f_i{0}; f_i < 256; f_i++) {
        i3 = f_i << 2;
        i4 = (i3 + i2) + i1;
        iv13[i4] = iv12[i4];
        iv13[i4 + 1] = iv12[i4 + 1];
        iv13[i4 + 2] = iv12[i4 + 2];
        iv13[((i1 + i2) + i3) + 3] = iv14[((c_i << 16) + (i << 8)) + f_i];
      }
    }
  }

  i1 = __constant_1x4xi32_108[3];
  i2 = __constant_1x4xi32_108[2];
  i3 = __constant_1x4xi32_108[1];
  i4 = __constant_1x4xi32_108[0];
  for (int c_i{0}; c_i < 6291456; c_i++) {
    i5 = c_i << 2;
    fv22[c_i] = __constant_1x4704x1xf32[((iv13[i5 + 3] * i1 + iv13[i5 + 2] * i2)
      + iv13[i5 + 1] * i3) + iv13[i5] * i4];
  }

  for (int c_i{0}; c_i < 96; c_i++) {
    i1 = c_i << 18;
    for (int i{0}; i < 256; i++) {
      i2 = i << 10;
      for (int f_i{0}; f_i < 256; f_i++) {
        i3 = f_i << 2;
        i4 = (i3 + i2) + i1;
        iv13[i4] = iv12[i4];
        iv13[i4 + 1] = iv12[i4 + 1];
        iv13[i4 + 2] = iv12[i4 + 2];
        iv13[((i1 + i2) + i3) + 3] = iv15[((c_i << 16) + (i << 8)) + f_i];
      }
    }
  }

  i1 = __constant_1x4xi32_108[3];
  i2 = __constant_1x4xi32_108[2];
  i3 = __constant_1x4xi32_108[1];
  i4 = __constant_1x4xi32_108[0];
  for (int c_i{0}; c_i < 6291456; c_i++) {
    i5 = c_i << 2;
    fv23[c_i] = __constant_1x4704x1xf32[((iv13[i5 + 3] * i1 + iv13[i5 + 2] * i2)
      + iv13[i5 + 1] * i3) + iv13[i5] * i4];
  }

  for (int b_i{0}; b_i < 96; b_i++) {
    for (int c_i{0}; c_i < 256; c_i++) {
      for (int i{0}; i < 256; i++) {
        iv12[(((b_i << 18) + (c_i << 10)) + (i << 2)) + 3] = iv17[((b_i << 16) +
          (c_i << 8)) + i];
      }
    }
  }

  i1 = __constant_1x4xi32_108[3];
  i2 = __constant_1x4xi32_108[2];
  i3 = __constant_1x4xi32_108[1];
  i4 = __constant_1x4xi32_108[0];
  for (int c_i{0}; c_i < 6291456; c_i++) {
    i5 = c_i << 2;
    fv24[c_i] = __constant_1x4704x1xf32[((iv12[i5 + 3] * i1 + iv12[i5 + 2] * i2)
      + iv12[i5 + 1] * i3) + iv12[i5] * i4];
  }

  for (int c_i{0}; c_i < 96; c_i++) {
    i3 = c_i << 18;
    for (int i{0}; i < 256; i++) {
      if (iv8[i] + 2 > 0) {
        d_i = iv8[i] + 2;
      } else {
        d_i = 0L;
      }

      if (static_cast<int>(d_i) < 6) {
        i4 = static_cast<int>(d_i);
      } else {
        i4 = 6;
      }

      if (i4 < 0) {
        i4 += 7;
      }

      i5 = i << 10;
      for (int f_i{0}; f_i < 256; f_i++) {
        i1 = f_i << 2;
        i2 = (i3 + i5) + i1;
        iv16[i2 + 2] = i4;
        i1 = (i1 + i5) + i3;
        iv13[i1] = iv16[i1];
        iv13[i1 + 1] = iv16[i1 + 1];
        iv13[i1 + 2] = i4;
        iv13[i2 + 3] = iv11[((c_i << 16) + (i << 8)) + f_i];
      }
    }
  }

  i1 = __constant_1x4xi32_108[3];
  i2 = __constant_1x4xi32_108[2];
  i3 = __constant_1x4xi32_108[1];
  i4 = __constant_1x4xi32_108[0];
  for (int c_i{0}; c_i < 6291456; c_i++) {
    i5 = c_i << 2;
    fv25[c_i] = __constant_1x4704x1xf32[((iv13[i5 + 3] * i1 + iv13[i5 + 2] * i2)
      + iv13[i5 + 1] * i3) + iv13[i5] * i4];
  }

  for (int c_i{0}; c_i < 96; c_i++) {
    i1 = c_i << 18;
    for (int i{0}; i < 256; i++) {
      i2 = i << 10;
      for (int f_i{0}; f_i < 256; f_i++) {
        i3 = f_i << 2;
        i4 = (i3 + i2) + i1;
        iv13[i4] = iv16[i4];
        iv13[i4 + 1] = iv16[i4 + 1];
        iv13[i4 + 2] = iv16[i4 + 2];
        iv13[((i1 + i2) + i3) + 3] = iv14[((c_i << 16) + (i << 8)) + f_i];
      }
    }
  }

  i1 = __constant_1x4xi32_108[3];
  i2 = __constant_1x4xi32_108[2];
  i3 = __constant_1x4xi32_108[1];
  i4 = __constant_1x4xi32_108[0];
  for (int c_i{0}; c_i < 6291456; c_i++) {
    i5 = c_i << 2;
    fv26[c_i] = __constant_1x4704x1xf32[((iv13[i5 + 3] * i1 + iv13[i5 + 2] * i2)
      + iv13[i5 + 1] * i3) + iv13[i5] * i4];
  }

  for (int c_i{0}; c_i < 96; c_i++) {
    i1 = c_i << 18;
    for (int i{0}; i < 256; i++) {
      i2 = i << 10;
      for (int f_i{0}; f_i < 256; f_i++) {
        i3 = f_i << 2;
        i4 = (i3 + i2) + i1;
        iv13[i4] = iv16[i4];
        iv13[i4 + 1] = iv16[i4 + 1];
        iv13[i4 + 2] = iv16[i4 + 2];
        iv13[((i1 + i2) + i3) + 3] = iv15[((c_i << 16) + (i << 8)) + f_i];
      }
    }
  }

  i1 = __constant_1x4xi32_108[3];
  i2 = __constant_1x4xi32_108[2];
  i3 = __constant_1x4xi32_108[1];
  i4 = __constant_1x4xi32_108[0];
  for (int c_i{0}; c_i < 6291456; c_i++) {
    i5 = c_i << 2;
    fv27[c_i] = __constant_1x4704x1xf32[((iv13[i5 + 3] * i1 + iv13[i5 + 2] * i2)
      + iv13[i5 + 1] * i3) + iv13[i5] * i4];
  }

  for (int b_i{0}; b_i < 96; b_i++) {
    for (int c_i{0}; c_i < 256; c_i++) {
      for (int i{0}; i < 256; i++) {
        iv16[(((b_i << 18) + (c_i << 10)) + (i << 2)) + 3] = iv17[((b_i << 16) +
          (c_i << 8)) + i];
      }
    }
  }

  i2 = __constant_1x4xi32_108[3];
  i3 = __constant_1x4xi32_108[2];
  i4 = __constant_1x4xi32_108[1];
  i5 = __constant_1x4xi32_108[0];
  for (int c_i{0}; c_i < 6291456; c_i++) {
    i1 = c_i << 2;
    i1 = (((iv16[i1 + 3] * i2 + iv16[i1 + 2] * i3) + iv16[i1 + 1] * i4) +
          iv16[i1] * i5) + iv10[c_i];
    iv10[c_i] = i1;
    fv28[c_i] = __constant_1x4704x1xf32[i1];
  }

  for (int b_i{0}; b_i < 96; b_i++) {
    for (int c_i{0}; c_i < 32; c_i++) {
      for (int i{0}; i < 8; i++) {
        for (int f_i{0}; f_i < 32; f_i++) {
          for (int e_i{0}; e_i < 8; e_i++) {
            fv29[((((b_i << 16) + (c_i << 11)) + (i << 8)) + (f_i << 3)) + e_i] =
              __constant_1x96x1x8x1x8xf32[((b_i << 6) + (i << 3)) + e_i];
          }
        }
      }
    }
  }

  for (int c_i{0}; c_i < 96; c_i++) {
    i1 = c_i << 16;
    for (int i{0}; i < 256; i++) {
      f = fv8[i];
      f1 = fv8[i + 256];
      f2 = fv9[i];
      f3 = fv9[i + 256];
      for (int f_i{0}; f_i < 256; f_i++) {
        i2 = (i1 + (f_i << 8)) + i;
        i3 = (i1 + (i << 8)) + f_i;
        fv30[i3] = fv6[i3] + (((((((fv13[i2] * f + fv14[i2] * f2) + fv15[i2] *
          f3) + fv16[i2] * f1) * fv10[f_i] + (((fv17[i2] * f + fv18[i2] * f2) +
          fv19[i2] * f3) + fv20[i2] * f1) * fv12[f_i]) + (((fv21[i2] * f +
          fv22[i2] * f2) + fv23[i2] * f3) + fv24[i2] * f1) * fv12[f_i + 256]) +
          (((fv25[i2] * f + fv26[i2] * f2) + fv27[i2] * f3) + fv28[i2] * f1) *
          fv10[f_i + 256]) + fv29[i2]);
      }
    }
  }

  for (int b_i{0}; b_i < 256; b_i++) {
    for (int c_i{0}; c_i < 256; c_i++) {
      for (int i{0}; i < 96; i++) {
        fv6[(24576 * b_i + 96 * c_i) + i] = fv30[((i << 16) + (c_i << 8)) + b_i];
      }
    }
  }

  for (int b_i{0}; b_i < 6291456; b_i++) {
    dv[b_i] = fv6[b_i];
  }

  std::memset(&dv1[0], 0, 65536U * sizeof(double));
  std::memset(&dv2[0], 0, 65536U * sizeof(double));
  std::memset(&dv3[0], 0, 65536U * sizeof(double));
  for (int c_i{0}; c_i < 256; c_i++) {
    for (int i{0}; i < 256; i++) {
      i1 = (c_i << 8) + i;
      d = dv3[i1];
      for (int b_i{0}; b_i < 96; b_i++) {
        d += dv[(24576 * c_i + 96 * i) + b_i];
      }

      dv3[i1] = d;
      d1 = 0.0;
      for (int b_i{0}; b_i < 96; b_i++) {
        d2 = dv[(24576 * c_i + 96 * i) + b_i] - d * 0.010416666666666666;
        d1 += d2 * d2;
      }

      dv4[i1] = d1;
    }
  }

  std::memset(&fv31[0], 0, 65536U * sizeof(float));
  std::memset(&fv32[0], 0, 65536U * sizeof(float));
  for (int c_i{0}; c_i < 256; c_i++) {
    for (int i{0}; i < 256; i++) {
      i1 = (c_i << 8) + i;
      f = fv32[i1];
      for (int b_i{0}; b_i < 96; b_i++) {
        f += fv6[(24576 * c_i + 96 * i) + b_i];
      }

      fv32[i1] = f;
      d = dv4[i1];
      for (int b_i{0}; b_i < 96; b_i++) {
        fv6[(24576 * c_i + 96 * i) + b_i] = (fv30[((b_i << 16) + (i << 8)) + c_i]
          - f * 0.010416667F) * (1.0F / std::sqrt(static_cast<float>(d *
          0.010416666666666666) + 1.0E-6F)) * __constant_1x96x1x1xf32[b_i] +
          __constant_1x96x1x1xf32_116[b_i];
      }
    }
  }

  for (int b_i{0}; b_i < 32; b_i++) {
    for (int c_i{0}; c_i < 32; c_i++) {
      for (int i{0}; i < 8; i++) {
        for (int f_i{0}; f_i < 8; f_i++) {
          std::copy(&fv6[((b_i * 196608 + c_i * 768) + i * 24576) + f_i * 96],
                    &fv6[static_cast<int>(static_cast<unsigned int>(((b_i *
            196608 + c_i * 768) + i * 24576) + f_i * 96) + 96U)], &fv13[((b_i *
                      196608 + c_i * 6144) + i * 768) + f_i * 96]);
        }
      }
    }
  }

  matrixMultiply12417453134711121340(288, 96, 65536, 128, 128, 128,
    &__constant_96x288xf32[0], &fv13[0], &fv33[0]);
  for (int b_i{0}; b_i < 65536; b_i++) {
    for (int c_i{0}; c_i < 288; c_i++) {
      i1 = 288 * b_i + c_i;
      fv33[i1] += __constant_1x288xf32[c_i];
    }
  }

  for (int i{0}; i < 1024; i++) {
    for (int b_i{0}; b_i < 64; b_i++) {
      for (int c_i{0}; c_i < 96; c_i++) {
        fv6[(6144 * i + 96 * b_i) + c_i] = fv33[(18432 * i + 288 * b_i) + c_i] *
          0.31947154F;
      }
    }

    for (int b_i{0}; b_i < 96; b_i++) {
      for (int c_i{0}; c_i < 64; c_i++) {
        fv13[(6144 * i + (b_i << 6)) + c_i] = fv33[((18432 * i + 288 * c_i) +
          b_i) + 96] * 0.31947154F;
      }
    }
  }

  for (int b_i{0}; b_i < 1024; b_i++) {
    matrixMultiply12417453134711121340(64, 96, 64, 128, 128, 128, &fv13[b_i *
      6144], &fv6[b_i * 6144], &fv35[0]);
    std::copy(&fv35[0], &fv35[4096], &fv34[b_i * 4096]);
  }

  for (int b_i{0}; b_i < 65536; b_i++) {
    fv32[b_i] = -3.402823466E+38F;
  }

  for (int c_i{0}; c_i < 1024; c_i++) {
    for (int i{0}; i < 64; i++) {
      i1 = (c_i << 6) + i;
      f = fv32[i1];
      for (int b_i{0}; b_i < 64; b_i++) {
        f1 = fv34[((c_i << 12) + (i << 6)) + b_i];
        if (!(f != f) && ((f1 != f1) || (f1 > f))) {
          f = f1;
        }
      }

      fv32[i1] = f;
      for (int b_i{0}; b_i < 64; b_i++) {
        i1 = ((c_i << 12) + (i << 6)) + b_i;
        fv36[i1] = std::exp(fv34[i1] - f);
      }
    }
  }

  std::memset(&fv32[0], 0, 65536U * sizeof(float));
  for (int b_i{0}; b_i < 1024; b_i++) {
    for (int c_i{0}; c_i < 64; c_i++) {
      i1 = (b_i << 6) + c_i;
      f = fv32[i1];
      for (int i{0}; i < 64; i++) {
        f += fv36[((b_i << 12) + (c_i << 6)) + i];
      }

      fv32[i1] = f;
    }
  }

  std::memset(&bv[0], 0, 65536U * sizeof(boolean_T));
  for (int c_i{0}; c_i < 1024; c_i++) {
    for (int i{0}; i < 64; i++) {
      i2 = (c_i << 6) + i;
      b = bv[i2];
      for (int b_i{0}; b_i < 64; b_i++) {
        b = (!(fv34[((c_i << 12) + (i << 6)) + b_i] == rtMinusInfF) || b);
      }

      bv[i2] = b;
      for (int b_i{0}; b_i < 64; b_i++) {
        if (b) {
          i1 = ((c_i << 12) + (i << 6)) + b_i;
          fv36[i1] *= 1.0F / fv32[i2];
        } else {
          fv36[((c_i << 12) + (i << 6)) + b_i] = 0.0F;
        }
      }
    }
  }

  for (int b_i{0}; b_i < 1024; b_i++) {
    float (*r)[6144];
    i1 = b_i * 18432 + 192;
    r = (float (*)[6144])std::malloc(static_cast<unsigned int>(6144 * sizeof
      (float)));
    for (int c_i{0}; c_i < 64; c_i++) {
      std::copy(&fv33[c_i * 288 + i1], &fv33[static_cast<int>(static_cast<
                 unsigned int>(c_i * 288 + i1) + 96U)], &(*r)[c_i * 96]);
    }

    matrixMultiply12417453134711121340(96, 64, 64, 128, 128, 128, &(*r)[0],
      &fv36[b_i << 12], &fv38[0]);
    std::free(r);
    std::copy(&fv38[0], &fv38[6144], &fv6[b_i * 6144]);
  }

  for (int b_i{0}; b_i < 1024; b_i++) {
    for (int c_i{0}; c_i < 8; c_i++) {
      std::copy(&__constant_1x1x96x96xf32[0], &__constant_1x1x96x96xf32[9216],
                &fv37[b_i * 73728 + c_i * 9216]);
    }
  }

  for (int b_i{0}; b_i < 8192; b_i++) {
    matrixMultiply12417453134711121340(96, 96, 8, 128, 128, 128, &fv37[b_i *
      9216], &fv6[b_i * 768], &fv39[0]);
    std::copy(&fv39[0], &fv39[768], &fv13[b_i * 768]);
  }

  for (int b_i{0}; b_i < 1024; b_i++) {
    for (int c_i{0}; c_i < 8; c_i++) {
      for (int i{0}; i < 8; i++) {
        for (int f_i{0}; f_i < 96; f_i++) {
          i1 = ((6144 * b_i + 768 * c_i) + 96 * i) + f_i;
          fv6[i1] = fv13[i1] + __constant_1x1x1x96xf32[f_i];
        }
      }
    }
  }

  for (int c_i{0}; c_i < 96; c_i++) {
    for (int i{0}; i < 32; i++) {
      for (int f_i{0}; f_i < 8; f_i++) {
        for (int e_i{0}; e_i < 32; e_i++) {
          for (int b_i{0}; b_i < 8; b_i++) {
            i1 = ((((c_i << 16) + (i << 11)) + (f_i << 8)) + (e_i << 3)) + b_i;
            fv13[i1] = fv30[i1] + fv6[(((196608 * e_i + 6144 * i) + 768 * b_i) +
              96 * f_i) + c_i];
          }
        }
      }
    }
  }

  for (int b_i{0}; b_i < 256; b_i++) {
    for (int c_i{0}; c_i < 256; c_i++) {
      for (int i{0}; i < 96; i++) {
        fv6[(24576 * b_i + 96 * c_i) + i] = fv13[((i << 16) + (c_i << 8)) + b_i];
      }
    }
  }

  for (int b_i{0}; b_i < 6291456; b_i++) {
    dv[b_i] = fv6[b_i];
  }

  std::memset(&dv3[0], 0, 65536U * sizeof(double));
  for (int c_i{0}; c_i < 256; c_i++) {
    for (int i{0}; i < 256; i++) {
      i1 = (c_i << 8) + i;
      d = dv3[i1];
      for (int b_i{0}; b_i < 96; b_i++) {
        d += dv[(24576 * c_i + 96 * i) + b_i];
      }

      dv3[i1] = d;
      d1 = 0.0;
      f = 0.0F;
      for (int b_i{0}; b_i < 96; b_i++) {
        i1 = (24576 * c_i + 96 * i) + b_i;
        d2 = dv[i1] - d * 0.010416666666666666;
        d1 += d2 * d2;
        f += fv6[i1];
      }

      for (int b_i{0}; b_i < 96; b_i++) {
        fv6[(24576 * c_i + 96 * i) + b_i] = (fv13[((b_i << 16) + (i << 8)) + c_i]
          - f * 0.010416667F) * (1.0F / std::sqrt(static_cast<float>(d1 *
          0.010416666666666666) + 1.0E-6F)) * __constant_1x96x1x1xf32_117[b_i] +
          __constant_1x96x1x1xf32_118[b_i];
      }
    }
  }

  matrixMultiply12417453134711121340(384, 96, 65536, 128, 128, 128,
    &__constant_96x384xf32[0], &fv6[0], &fv40[0]);
  for (int b_i{0}; b_i < 65536; b_i++) {
    for (int c_i{0}; c_i < 384; c_i++) {
      i1 = 384 * b_i + c_i;
      fv40[i1] += __constant_1x384xf32[c_i];
    }
  }

  for (int b_i{0}; b_i < 25165824; b_i++) {
    f4 = fv40[b_i];
    f = f4 * 0.70710677F;
    b = (f < 0.0F);
    if (b) {
      f = -f;
    }

    b1 = (f < 0.8F);
    b2 = (f < 2.0F);
    if ((f != f) || (f < 3.75F)) {
      if (b2) {
        if (b1) {
          f1 = 0.02581468F;
          f2 = 0.20974171F;
          f3 = -0.52301854F;
          f5 = 1.1283791F;
        } else {
          f1 = 0.037064552F;
          f2 = 0.1184074F;
          f3 = -0.36472142F;
          f5 = 1.1275069F;
        }

        f6 = 0.0F;
        if (b1) {
          f7 = 0.073979646F;
          f8 = -0.13180897F;
          f9 = 0.5192301F;
          f10 = -0.46351382F;
        } else {
          f7 = 0.05724428F;
          f8 = -0.088346265F;
          f9 = 0.4483691F;
          f10 = -0.327607F;
        }
      } else {
        f1 = -1.7104803E-5F;
        f2 = 0.0002534471F;
        f3 = -0.0014137363F;
        f5 = 0.0035196193F;
        f6 = -0.0033009306F;
        f7 = 0.08219089F;
        f8 = -0.5833899F;
        f9 = 1.6270593F;
        f10 = -2.0606916F;
      }

      f = static_cast<float>(!b2) + (f * (f * (f * (f * f1 + f2) + f3) + f5) +
        f6) / (f * (f * (f * (f * f7 + f8) + f9) + f10) + 1.0F);
    } else {
      f = 1.0F;
    }

    if (b) {
      f = -f;
    }

    fv41[b_i] = f4 * ((f + 1.0F) * 0.5F);
  }

  matrixMultiply12417453134711121340(96, 384, 65536, 128, 128, 128,
    &__constant_384x96xf32[0], &fv41[0], &fv42[0]);
  for (int b_i{0}; b_i < 65536; b_i++) {
    for (int c_i{0}; c_i < 96; c_i++) {
      i1 = 96 * b_i + c_i;
      fv42[i1] += __constant_1x96xf32[c_i];
    }
  }

  for (int b_i{0}; b_i < 96; b_i++) {
    for (int c_i{0}; c_i < 256; c_i++) {
      for (int i{0}; i < 256; i++) {
        i1 = ((b_i << 16) + (c_i << 8)) + i;
        fv30[i1] = fv13[i1] + fv42[(24576 * i + 96 * c_i) + b_i];
      }
    }
  }

  for (int b_i{0}; b_i < 256; b_i++) {
    for (int c_i{0}; c_i < 256; c_i++) {
      for (int i{0}; i < 96; i++) {
        fv6[(24576 * b_i + 96 * c_i) + i] = fv30[((i << 16) + (c_i << 8)) + b_i];
      }
    }
  }

  for (int b_i{0}; b_i < 6291456; b_i++) {
    dv[b_i] = fv6[b_i];
  }

  for (int c_i{0}; c_i < 256; c_i++) {
    for (int i{0}; i < 256; i++) {
      i2 = (c_i << 8) + i;
      d = dv2[i2];
      for (int b_i{0}; b_i < 96; b_i++) {
        d += dv[(24576 * c_i + 96 * i) + b_i];
      }

      dv2[i2] = d;
      d1 = dv1[i2];
      f = fv31[i2];
      for (int b_i{0}; b_i < 96; b_i++) {
        i1 = (24576 * c_i + 96 * i) + b_i;
        d2 = dv[i1] - d * 0.010416666666666666;
        d1 += d2 * d2;
        f += fv6[i1];
      }

      fv31[i2] = f;
      dv1[i2] = d1;
      for (int b_i{0}; b_i < 96; b_i++) {
        fv6[(24576 * c_i + 96 * i) + b_i] = (fv30[((b_i << 16) + (i << 8)) + c_i]
          - f * 0.010416667F) * (1.0F / std::sqrt(static_cast<float>(d1 *
          0.010416666666666666) + 1.0E-6F)) * __constant_1x96x1x1xf32_119[b_i] +
          __constant_1x96x1x1xf32_120[b_i];
      }
    }
  }

  matrixMultiply12417453134711121340(192, 96, 65536, 128, 128, 128,
    &__constant_96x192xf32[0], &fv6[0], &fv43[0]);
  for (int b_i{0}; b_i < 65536; b_i++) {
    for (int c_i{0}; c_i < 192; c_i++) {
      i1 = 192 * b_i + c_i;
      fv43[i1] += __constant_1x192xf32[c_i];
    }
  }

  for (int b_i{0}; b_i < 192; b_i++) {
    for (int c_i{0}; c_i < 256; c_i++) {
      for (int i{0}; i < 256; i++) {
        fv44[((b_i << 16) + (c_i << 8)) + i] = fv43[(49152 * i + 192 * c_i) +
          b_i];
      }
    }
  }

  maxPooling10961364285251527891(&fv44[0], &fv45[0]);
  for (int b_i{0}; b_i < 32; b_i++) {
    for (int c_i{0}; c_i < 32; c_i++) {
      for (int i{0}; i < 8; i++) {
        for (int f_i{0}; f_i < 8; f_i++) {
          std::copy(&fv6[((b_i * 196608 + c_i * 768) + i * 24576) + f_i * 96],
                    &fv6[static_cast<int>(static_cast<unsigned int>(((b_i *
            196608 + c_i * 768) + i * 24576) + f_i * 96) + 96U)], &fv13[((b_i *
                      196608 + c_i * 6144) + i * 768) + f_i * 96]);
        }
      }
    }
  }

  matrixMultiply4454328187142109130(576, 96, 65536, 128, 128, 128,
    &__constant_96x576xf32[0], &fv13[0], &fv46[0]);
  for (int b_i{0}; b_i < 65536; b_i++) {
    for (int c_i{0}; c_i < 576; c_i++) {
      i1 = 576 * b_i + c_i;
      fv46[i1] += __constant_1x576xf32[c_i];
    }
  }

  for (int b_i{0}; b_i < 1024; b_i++) {
    for (int c_i{0}; c_i < 192; c_i++) {
      for (int i{0}; i < 8; i++) {
        for (int f_i{0}; f_i < 8; f_i++) {
          fv43[((12288 * b_i + (c_i << 6)) + (i << 3)) + f_i] = fv46[((36864 *
            b_i + 4608 * f_i) + 576 * i) + c_i];
        }
      }
    }
  }

  maxPooling3996420485521692580(&fv43[0], &fv47[0]);
  for (int e_i{0}; e_i < 1024; e_i++) {
    for (int i8{0}; i8 < 2; i8++) {
      for (int b_i{0}; b_i < 64; b_i++) {
        std::copy(&fv46[((e_i * 36864 + i8 * 96) + b_i * 576) + 384], &fv46
                  [((e_i * 36864 + i8 * 96) + b_i * 576) + 480], &fv43[(e_i *
                   12288 + i8 * 6144) + b_i * 96]);
      }

      i1 = 3072 * e_i + 1536 * i8;
      for (int c_i{0}; c_i < 4; c_i++) {
        for (int i{0}; i < 4; i++) {
          for (int f_i{0}; f_i < 96; f_i++) {
            fv4[((i1 + 384 * c_i) + 96 * i) + f_i] = fv47[((i1 + (f_i << 4)) +
              (i << 2)) + c_i] * 0.31947154F;
          }
        }
      }

      for (int b_i{0}; b_i < 96; b_i++) {
        for (int c_i{0}; c_i < 64; c_i++) {
          fv44[((12288 * e_i + 6144 * i8) + (b_i << 6)) + c_i] = fv46[(((36864 *
            e_i + 576 * c_i) + 96 * i8) + b_i) + 192] * 0.31947154F;
        }
      }
    }
  }

  for (int b_i{0}; b_i < 2048; b_i++) {
    matrixMultiply12417453134711121340(64, 96, 16, 128, 128, 128, &fv44[b_i *
      6144], &fv4[b_i * 1536], &fv50[0]);
    std::copy(&fv50[0], &fv50[1024], &fv48[b_i * 1024]);
  }

  for (int b_i{0}; b_i < 32768; b_i++) {
    fv49[b_i] = -3.402823466E+38F;
    fv51[b_i] = -3.402823466E+38F;
  }

  for (int c_i{0}; c_i < 1024; c_i++) {
    for (int i{0}; i < 2; i++) {
      for (int f_i{0}; f_i < 16; f_i++) {
        i1 = ((c_i << 5) + (i << 4)) + f_i;
        f = fv51[i1];
        for (int b_i{0}; b_i < 64; b_i++) {
          f1 = fv48[(((c_i << 11) + (i << 10)) + (f_i << 6)) + b_i];
          if (!(f != f) && ((f1 != f1) || (f1 > f))) {
            f = f1;
          }
        }

        fv51[i1] = f;
        for (int b_i{0}; b_i < 64; b_i++) {
          i1 = (((c_i << 11) + (i << 10)) + (f_i << 6)) + b_i;
          fv52[i1] = std::exp(fv48[i1] - f);
        }
      }
    }
  }

  std::memset(&fv51[0], 0, 32768U * sizeof(float));
  std::memset(&fv53[0], 0, 32768U * sizeof(float));
  for (int b_i{0}; b_i < 1024; b_i++) {
    for (int c_i{0}; c_i < 2; c_i++) {
      for (int i{0}; i < 16; i++) {
        i1 = ((b_i << 5) + (c_i << 4)) + i;
        f = fv53[i1];
        for (int f_i{0}; f_i < 64; f_i++) {
          f += fv52[(((b_i << 11) + (c_i << 10)) + (i << 6)) + f_i];
        }

        fv53[i1] = f;
      }
    }
  }

  std::memset(&bv1[0], 0, 32768U * sizeof(boolean_T));
  std::memset(&bv2[0], 0, 32768U * sizeof(boolean_T));
  for (int i{0}; i < 1024; i++) {
    for (int f_i{0}; f_i < 2; f_i++) {
      for (int e_i{0}; e_i < 16; e_i++) {
        i2 = ((i << 5) + (f_i << 4)) + e_i;
        b = bv2[i2];
        for (int b_i{0}; b_i < 64; b_i++) {
          b = (!(fv48[(((i << 11) + (f_i << 10)) + (e_i << 6)) + b_i] ==
                 rtMinusInfF) || b);
        }

        bv2[i2] = b;
        for (int c_i{0}; c_i < 64; c_i++) {
          if (b) {
            i1 = (((i << 11) + (f_i << 10)) + (e_i << 6)) + c_i;
            fv52[i1] *= 1.0F / fv53[i2];
          } else {
            fv52[(((i << 11) + (f_i << 10)) + (e_i << 6)) + c_i] = 0.0F;
          }
        }
      }
    }
  }

  for (int b_i{0}; b_i < 2048; b_i++) {
    matrixMultiply12417453134711121340(96, 64, 16, 128, 128, 128, &fv43[b_i *
      6144], &fv52[b_i << 10], &fv54[0]);
    std::copy(&fv54[0], &fv54[1536], &fv4[b_i * 1536]);
  }

  for (int b_i{0}; b_i < 1024; b_i++) {
    for (int c_i{0}; c_i < 4; c_i++) {
      for (int i{0}; i < 4; i++) {
        for (int f_i{0}; f_i < 2; f_i++) {
          std::copy(&fv4[((b_i * 3072 + c_i * 384) + i * 96) + f_i * 1536],
                    &fv4[static_cast<int>(static_cast<unsigned int>(((b_i * 3072
            + c_i * 384) + i * 96) + f_i * 1536) + 96U)], &fv5[((b_i * 3072 +
                      c_i * 768) + i * 192) + f_i * 96]);
        }
      }

      std::copy(&__constant_1x1x192x192xf32[0], &__constant_1x1x192x192xf32
                [36864], &fv55[b_i * 147456 + c_i * 36864]);
    }
  }

  for (int b_i{0}; b_i < 4096; b_i++) {
    matrixMultiply12417453134711121340(192, 192, 4, 128, 128, 128, &fv55[b_i *
      36864], &fv5[b_i * 768], &fv56[0]);
    std::copy(&fv56[0], &fv56[768], &fv4[b_i * 768]);
  }

  for (int b_i{0}; b_i < 1024; b_i++) {
    for (int c_i{0}; c_i < 4; c_i++) {
      for (int i{0}; i < 4; i++) {
        for (int f_i{0}; f_i < 192; f_i++) {
          i1 = ((3072 * b_i + 768 * c_i) + 192 * i) + f_i;
          fv5[i1] = fv4[i1] + __constant_1x1x1x192xf32[f_i];
        }
      }
    }
  }

  for (int c_i{0}; c_i < 192; c_i++) {
    for (int i{0}; i < 32; i++) {
      for (int f_i{0}; f_i < 4; f_i++) {
        for (int e_i{0}; e_i < 32; e_i++) {
          i1 = (((c_i << 14) + (i << 9)) + (f_i << 7)) + (e_i << 2);
          i2 = ((98304 * e_i + 3072 * i) + 192 * f_i) + c_i;
          fv4[i1] = fv45[i1] + fv5[i2];
          fv4[i1 + 1] = fv45[i1 + 1] + fv5[i2 + 768];
          fv4[i1 + 2] = fv45[i1 + 2] + fv5[i2 + 1536];
          fv4[i1 + 3] = fv45[i1 + 3] + fv5[i2 + 2304];
        }
      }
    }
  }

  for (int b_i{0}; b_i < 128; b_i++) {
    for (int c_i{0}; c_i < 128; c_i++) {
      for (int i{0}; i < 192; i++) {
        fv5[(24576 * b_i + 192 * c_i) + i] = fv4[((i << 14) + (c_i << 7)) + b_i];
      }
    }
  }

  for (int b_i{0}; b_i < 3145728; b_i++) {
    dv5[b_i] = fv5[b_i];
  }

  std::memset(&dv6[0], 0, 16384U * sizeof(double));
  std::memset(&dv7[0], 0, 16384U * sizeof(double));
  std::memset(&dv8[0], 0, 16384U * sizeof(double));
  for (int c_i{0}; c_i < 128; c_i++) {
    for (int i{0}; i < 128; i++) {
      i1 = (c_i << 7) + i;
      d = dv8[i1];
      for (int b_i{0}; b_i < 192; b_i++) {
        d += dv5[(24576 * c_i + 192 * i) + b_i];
      }

      dv8[i1] = d;
      d1 = 0.0;
      for (int b_i{0}; b_i < 192; b_i++) {
        d2 = dv5[(24576 * c_i + 192 * i) + b_i] - d * 0.005208333333333333;
        d1 += d2 * d2;
      }

      dv9[i1] = d1;
    }
  }

  std::memset(&fv57[0], 0, 16384U * sizeof(float));
  std::memset(&fv58[0], 0, 16384U * sizeof(float));
  std::memset(&fv59[0], 0, 16384U * sizeof(float));
  for (int c_i{0}; c_i < 128; c_i++) {
    for (int i{0}; i < 128; i++) {
      i1 = (c_i << 7) + i;
      f = fv59[i1];
      for (int b_i{0}; b_i < 192; b_i++) {
        f += fv5[(24576 * c_i + 192 * i) + b_i];
      }

      fv59[i1] = f;
      d = dv9[i1];
      for (int b_i{0}; b_i < 192; b_i++) {
        fv5[(24576 * c_i + 192 * i) + b_i] = (fv4[((b_i << 14) + (i << 7)) + c_i]
          - f * 0.0052083335F) * (1.0F / std::sqrt(static_cast<float>(d *
          0.005208333333333333) + 1.0E-6F)) * __constant_1x192x1x1xf32[b_i] +
          __constant_1x192x1x1xf32_121[b_i];
      }
    }
  }

  matrixMultiply4454328187142109130(768, 192, 16384, 128, 128, 128,
    &__constant_192x768xf32[0], &fv5[0], &fv60[0]);
  for (int b_i{0}; b_i < 16384; b_i++) {
    for (int c_i{0}; c_i < 768; c_i++) {
      i1 = 768 * b_i + c_i;
      fv60[i1] += __constant_1x768xf32[c_i];
    }
  }

  for (int b_i{0}; b_i < 12582912; b_i++) {
    f4 = fv60[b_i];
    f = f4 * 0.70710677F;
    b = (f < 0.0F);
    if (b) {
      f = -f;
    }

    b1 = (f < 0.8F);
    b2 = (f < 2.0F);
    if ((f != f) || (f < 3.75F)) {
      if (b2) {
        if (b1) {
          f1 = 0.02581468F;
          f2 = 0.20974171F;
          f3 = -0.52301854F;
          f5 = 1.1283791F;
        } else {
          f1 = 0.037064552F;
          f2 = 0.1184074F;
          f3 = -0.36472142F;
          f5 = 1.1275069F;
        }

        f6 = 0.0F;
        if (b1) {
          f7 = 0.073979646F;
          f8 = -0.13180897F;
          f9 = 0.5192301F;
          f10 = -0.46351382F;
        } else {
          f7 = 0.05724428F;
          f8 = -0.088346265F;
          f9 = 0.4483691F;
          f10 = -0.327607F;
        }
      } else {
        f1 = -1.7104803E-5F;
        f2 = 0.0002534471F;
        f3 = -0.0014137363F;
        f5 = 0.0035196193F;
        f6 = -0.0033009306F;
        f7 = 0.08219089F;
        f8 = -0.5833899F;
        f9 = 1.6270593F;
        f10 = -2.0606916F;
      }

      f = static_cast<float>(!b2) + (f * (f * (f * (f * f1 + f2) + f3) + f5) +
        f6) / (f * (f * (f * (f * f7 + f8) + f9) + f10) + 1.0F);
    } else {
      f = 1.0F;
    }

    if (b) {
      f = -f;
    }

    fv43[b_i] = f4 * ((f + 1.0F) * 0.5F);
  }

  matrixMultiply12417453134711121340(192, 768, 16384, 128, 128, 128,
    &__constant_768x192xf32[0], &fv43[0], &fv61[0]);
  for (int b_i{0}; b_i < 16384; b_i++) {
    for (int c_i{0}; c_i < 192; c_i++) {
      i1 = 192 * b_i + c_i;
      fv61[i1] += __constant_1x192xf32_9[c_i];
    }
  }

  for (int b_i{0}; b_i < 192; b_i++) {
    for (int c_i{0}; c_i < 128; c_i++) {
      for (int i{0}; i < 128; i++) {
        i1 = ((b_i << 14) + (c_i << 7)) + i;
        fv45[i1] = fv4[i1] + fv61[(24576 * i + 192 * c_i) + b_i];
      }
    }
  }

  for (int b_i{0}; b_i < 128; b_i++) {
    for (int c_i{0}; c_i < 128; c_i++) {
      for (int i{0}; i < 192; i++) {
        fv5[(24576 * b_i + 192 * c_i) + i] = fv45[((i << 14) + (c_i << 7)) + b_i];
      }
    }
  }

  for (int b_i{0}; b_i < 3145728; b_i++) {
    dv5[b_i] = fv5[b_i];
  }

  std::memset(&dv8[0], 0, 16384U * sizeof(double));
  for (int c_i{0}; c_i < 128; c_i++) {
    for (int i{0}; i < 128; i++) {
      i1 = (c_i << 7) + i;
      d = dv8[i1];
      for (int b_i{0}; b_i < 192; b_i++) {
        d += dv5[(24576 * c_i + 192 * i) + b_i];
      }

      dv8[i1] = d;
      d1 = 0.0;
      f = 0.0F;
      for (int b_i{0}; b_i < 192; b_i++) {
        i1 = (24576 * c_i + 192 * i) + b_i;
        d2 = dv5[i1] - d * 0.005208333333333333;
        d1 += d2 * d2;
        f += fv5[i1];
      }

      for (int b_i{0}; b_i < 192; b_i++) {
        fv5[(24576 * c_i + 192 * i) + b_i] = (fv45[((b_i << 14) + (i << 7)) +
          c_i] - f * 0.0052083335F) * (1.0F / std::sqrt(static_cast<float>(d1 *
          0.005208333333333333) + 1.0E-6F)) * __constant_1x192x1x1xf32_122[b_i]
          + __constant_1x192x1x1xf32_123[b_i];
      }
    }
  }

  for (int b_i{0}; b_i < 32; b_i++) {
    for (int c_i{0}; c_i < 32; c_i++) {
      for (int i{0}; i < 4; i++) {
        for (int f_i{0}; f_i < 4; f_i++) {
          std::copy(&fv5[((b_i * 98304 + c_i * 768) + i * 24576) + f_i * 192],
                    &fv5[static_cast<int>(static_cast<unsigned int>(((b_i *
            98304 + c_i * 768) + i * 24576) + f_i * 192) + 192U)], &fv4[((b_i *
                      98304 + c_i * 3072) + i * 768) + f_i * 192]);
        }
      }
    }
  }

  matrixMultiply4454328187142109130(576, 192, 16384, 128, 128, 128,
    &__constant_192x576xf32[0], &fv4[0], &fv62[0]);
  for (int b_i{0}; b_i < 16384; b_i++) {
    for (int c_i{0}; c_i < 576; c_i++) {
      i1 = 576 * b_i + c_i;
      fv62[i1] += __constant_1x576xf32_10[c_i];
    }
  }

  for (int f_i{0}; f_i < 1024; f_i++) {
    for (int e_i{0}; e_i < 2; e_i++) {
      for (int c_i{0}; c_i < 16; c_i++) {
        for (int i{0}; i < 96; i++) {
          i1 = ((9216 * f_i + 576 * c_i) + 96 * e_i) + i;
          i2 = ((3072 * f_i + 1536 * e_i) + 96 * c_i) + i;
          fv5[i2] = fv62[i1 + 384];
          fv4[i2] = fv62[i1] * 0.31947154F;
        }
      }

      for (int b_i{0}; b_i < 96; b_i++) {
        for (int c_i{0}; c_i < 16; c_i++) {
          fv47[((3072 * f_i + 1536 * e_i) + (b_i << 4)) + c_i] = fv62[(((9216 *
            f_i + 576 * c_i) + 96 * e_i) + b_i) + 192] * 0.31947154F;
        }
      }
    }
  }

  for (int b_i{0}; b_i < 2048; b_i++) {
    matrixMultiply12417453134711121340(16, 96, 16, 128, 128, 128, &fv47[b_i *
      1536], &fv4[b_i * 1536], &fv65[0]);
    std::copy(&fv65[0], &fv65[256], &fv63[b_i * 256]);
  }

  for (int i{0}; i < 1024; i++) {
    for (int f_i{0}; f_i < 2; f_i++) {
      for (int e_i{0}; e_i < 16; e_i++) {
        i3 = ((i << 5) + (f_i << 4)) + e_i;
        f3 = fv49[i3];
        for (int b_i{0}; b_i < 16; b_i++) {
          f = fv63[(((i << 9) + (f_i << 8)) + (e_i << 4)) + b_i];
          if (!(f3 != f3) && ((f != f) || (f > f3))) {
            f3 = f;
          }
        }

        fv49[i3] = f3;
        f = fv51[i3];
        b = bv1[i3];
        for (int c_i{0}; c_i < 16; c_i++) {
          i1 = (((i << 9) + (f_i << 8)) + (e_i << 4)) + c_i;
          f1 = fv63[i1];
          f2 = std::exp(f1 - f3);
          fv64[i1] = f2;
          f += f2;
          b = (!(f1 == rtMinusInfF) || b);
        }

        bv1[i3] = b;
        fv51[i3] = f;
        for (int c_i{0}; c_i < 16; c_i++) {
          if (b) {
            i1 = (((i << 9) + (f_i << 8)) + (e_i << 4)) + c_i;
            fv64[i1] *= 1.0F / fv51[i3];
          } else {
            fv64[(((i << 9) + (f_i << 8)) + (e_i << 4)) + c_i] = 0.0F;
          }
        }
      }
    }
  }

  for (int b_i{0}; b_i < 2048; b_i++) {
    matrixMultiply12417453134711121340(96, 16, 16, 128, 128, 128, &fv5[b_i *
      1536], &fv64[b_i << 8], &fv54[0]);
    std::copy(&fv54[0], &fv54[1536], &fv4[b_i * 1536]);
  }

  for (int b_i{0}; b_i < 1024; b_i++) {
    for (int c_i{0}; c_i < 4; c_i++) {
      for (int i{0}; i < 4; i++) {
        for (int f_i{0}; f_i < 2; f_i++) {
          std::copy(&fv4[((b_i * 3072 + c_i * 384) + i * 96) + f_i * 1536],
                    &fv4[static_cast<int>(static_cast<unsigned int>(((b_i * 3072
            + c_i * 384) + i * 96) + f_i * 1536) + 96U)], &fv5[((b_i * 3072 +
                      c_i * 768) + i * 192) + f_i * 96]);
        }
      }

      std::copy(&__constant_1x1x192x192xf32_111[0],
                &__constant_1x1x192x192xf32_111[36864], &fv55[b_i * 147456 + c_i
                * 36864]);
    }
  }

  for (int b_i{0}; b_i < 4096; b_i++) {
    matrixMultiply12417453134711121340(192, 192, 4, 128, 128, 128, &fv55[b_i *
      36864], &fv5[b_i * 768], &fv56[0]);
    std::copy(&fv56[0], &fv56[768], &fv4[b_i * 768]);
  }

  for (int b_i{0}; b_i < 1024; b_i++) {
    for (int c_i{0}; c_i < 4; c_i++) {
      for (int i{0}; i < 4; i++) {
        for (int f_i{0}; f_i < 192; f_i++) {
          i1 = ((3072 * b_i + 768 * c_i) + 192 * i) + f_i;
          fv5[i1] = fv4[i1] + __constant_1x1x1x192xf32_11[f_i];
        }
      }
    }
  }

  for (int c_i{0}; c_i < 192; c_i++) {
    for (int i{0}; i < 32; i++) {
      for (int f_i{0}; f_i < 4; f_i++) {
        for (int e_i{0}; e_i < 32; e_i++) {
          i1 = (((c_i << 14) + (i << 9)) + (f_i << 7)) + (e_i << 2);
          i2 = ((98304 * e_i + 3072 * i) + 192 * f_i) + c_i;
          fv4[i1] = fv45[i1] + fv5[i2];
          fv4[i1 + 1] = fv45[i1 + 1] + fv5[i2 + 768];
          fv4[i1 + 2] = fv45[i1 + 2] + fv5[i2 + 1536];
          fv4[i1 + 3] = fv45[i1 + 3] + fv5[i2 + 2304];
        }
      }
    }
  }

  for (int b_i{0}; b_i < 128; b_i++) {
    for (int c_i{0}; c_i < 128; c_i++) {
      for (int i{0}; i < 192; i++) {
        fv5[(24576 * b_i + 192 * c_i) + i] = fv4[((i << 14) + (c_i << 7)) + b_i];
      }
    }
  }

  for (int b_i{0}; b_i < 3145728; b_i++) {
    dv5[b_i] = fv5[b_i];
  }

  std::memset(&dv8[0], 0, 16384U * sizeof(double));
  for (int c_i{0}; c_i < 128; c_i++) {
    for (int i{0}; i < 128; i++) {
      i1 = (c_i << 7) + i;
      d = dv8[i1];
      for (int b_i{0}; b_i < 192; b_i++) {
        d += dv5[(24576 * c_i + 192 * i) + b_i];
      }

      dv8[i1] = d;
      d1 = 0.0;
      f = 0.0F;
      for (int b_i{0}; b_i < 192; b_i++) {
        i1 = (24576 * c_i + 192 * i) + b_i;
        d2 = dv5[i1] - d * 0.005208333333333333;
        d1 += d2 * d2;
        f += fv5[i1];
      }

      for (int b_i{0}; b_i < 192; b_i++) {
        fv5[(24576 * c_i + 192 * i) + b_i] = (fv4[((b_i << 14) + (i << 7)) + c_i]
          - f * 0.0052083335F) * (1.0F / std::sqrt(static_cast<float>(d1 *
          0.005208333333333333) + 1.0E-6F)) * __constant_1x192x1x1xf32_124[b_i]
          + __constant_1x192x1x1xf32_125[b_i];
      }
    }
  }

  matrixMultiply4454328187142109130(768, 192, 16384, 128, 128, 128,
    &__constant_192x768xf32_164[0], &fv5[0], &fv60[0]);
  for (int b_i{0}; b_i < 16384; b_i++) {
    for (int c_i{0}; c_i < 768; c_i++) {
      i1 = 768 * b_i + c_i;
      fv60[i1] += __constant_1x768xf32_12[c_i];
    }
  }

  for (int b_i{0}; b_i < 12582912; b_i++) {
    f4 = fv60[b_i];
    f = f4 * 0.70710677F;
    b = (f < 0.0F);
    if (b) {
      f = -f;
    }

    b1 = (f < 0.8F);
    b2 = (f < 2.0F);
    if ((f != f) || (f < 3.75F)) {
      if (b2) {
        if (b1) {
          f1 = 0.02581468F;
          f2 = 0.20974171F;
          f3 = -0.52301854F;
          f5 = 1.1283791F;
        } else {
          f1 = 0.037064552F;
          f2 = 0.1184074F;
          f3 = -0.36472142F;
          f5 = 1.1275069F;
        }

        f6 = 0.0F;
        if (b1) {
          f7 = 0.073979646F;
          f8 = -0.13180897F;
          f9 = 0.5192301F;
          f10 = -0.46351382F;
        } else {
          f7 = 0.05724428F;
          f8 = -0.088346265F;
          f9 = 0.4483691F;
          f10 = -0.327607F;
        }
      } else {
        f1 = -1.7104803E-5F;
        f2 = 0.0002534471F;
        f3 = -0.0014137363F;
        f5 = 0.0035196193F;
        f6 = -0.0033009306F;
        f7 = 0.08219089F;
        f8 = -0.5833899F;
        f9 = 1.6270593F;
        f10 = -2.0606916F;
      }

      f = static_cast<float>(!b2) + (f * (f * (f * (f * f1 + f2) + f3) + f5) +
        f6) / (f * (f * (f * (f * f7 + f8) + f9) + f10) + 1.0F);
    } else {
      f = 1.0F;
    }

    if (b) {
      f = -f;
    }

    fv43[b_i] = f4 * ((f + 1.0F) * 0.5F);
  }

  matrixMultiply12417453134711121340(192, 768, 16384, 128, 128, 128,
    &__constant_768x192xf32_165[0], &fv43[0], &fv61[0]);
  for (int b_i{0}; b_i < 16384; b_i++) {
    for (int c_i{0}; c_i < 192; c_i++) {
      i1 = 192 * b_i + c_i;
      fv61[i1] += __constant_1x192xf32_13[c_i];
    }
  }

  for (int b_i{0}; b_i < 192; b_i++) {
    for (int c_i{0}; c_i < 128; c_i++) {
      for (int i{0}; i < 128; i++) {
        i1 = ((b_i << 14) + (c_i << 7)) + i;
        fv45[i1] = fv4[i1] + fv61[(24576 * i + 192 * c_i) + b_i];
      }
    }
  }

  for (int b_i{0}; b_i < 128; b_i++) {
    for (int c_i{0}; c_i < 128; c_i++) {
      for (int i{0}; i < 192; i++) {
        fv5[(24576 * b_i + 192 * c_i) + i] = fv45[((i << 14) + (c_i << 7)) + b_i];
      }
    }
  }

  for (int b_i{0}; b_i < 3145728; b_i++) {
    dv5[b_i] = fv5[b_i];
  }

  for (int c_i{0}; c_i < 128; c_i++) {
    for (int i{0}; i < 128; i++) {
      i2 = (c_i << 7) + i;
      d = dv7[i2];
      for (int b_i{0}; b_i < 192; b_i++) {
        d += dv5[(24576 * c_i + 192 * i) + b_i];
      }

      dv7[i2] = d;
      d1 = dv6[i2];
      f = fv58[i2];
      for (int b_i{0}; b_i < 192; b_i++) {
        i1 = (24576 * c_i + 192 * i) + b_i;
        d2 = dv5[i1] - d * 0.005208333333333333;
        d1 += d2 * d2;
        f += fv5[i1];
      }

      fv58[i2] = f;
      dv6[i2] = d1;
      for (int b_i{0}; b_i < 192; b_i++) {
        fv5[(24576 * c_i + 192 * i) + b_i] = (fv45[((b_i << 14) + (i << 7)) +
          c_i] - f * 0.0052083335F) * (1.0F / std::sqrt(static_cast<float>(d1 *
          0.005208333333333333) + 1.0E-6F)) * __constant_1x192x1x1xf32_126[b_i]
          + __constant_1x192x1x1xf32_127[b_i];
      }
    }
  }

  matrixMultiply12417453134711121340(384, 192, 16384, 128, 128, 128,
    &__constant_192x384xf32[0], &fv5[0], &fv66[0]);
  for (int b_i{0}; b_i < 16384; b_i++) {
    for (int c_i{0}; c_i < 384; c_i++) {
      i1 = 384 * b_i + c_i;
      fv66[i1] += __constant_1x384xf32_14[c_i];
    }
  }

  for (int b_i{0}; b_i < 384; b_i++) {
    for (int c_i{0}; c_i < 128; c_i++) {
      for (int i{0}; i < 128; i++) {
        fv6[((b_i << 14) + (c_i << 7)) + i] = fv66[(49152 * i + 384 * c_i) + b_i];
      }
    }
  }

  maxPooling18375657460455750414(&fv6[0], &fv67[0]);
  for (int b_i{0}; b_i < 32; b_i++) {
    for (int c_i{0}; c_i < 32; c_i++) {
      for (int i{0}; i < 4; i++) {
        for (int f_i{0}; f_i < 4; f_i++) {
          std::copy(&fv5[((b_i * 98304 + c_i * 768) + i * 24576) + f_i * 192],
                    &fv5[static_cast<int>(static_cast<unsigned int>(((b_i *
            98304 + c_i * 768) + i * 24576) + f_i * 192) + 192U)], &fv4[((b_i *
                      98304 + c_i * 3072) + i * 768) + f_i * 192]);
        }
      }
    }
  }

  matrixMultiply4454328187142109130(1152, 192, 16384, 128, 128, 128,
    &__constant_192x1152xf32[0], &fv4[0], &fv68[0]);
  for (int b_i{0}; b_i < 16384; b_i++) {
    for (int c_i{0}; c_i < 1152; c_i++) {
      i1 = 1152 * b_i + c_i;
      fv68[i1] += __constant_1x1152xf32[c_i];
    }
  }

  for (int b_i{0}; b_i < 1024; b_i++) {
    for (int c_i{0}; c_i < 384; c_i++) {
      for (int i{0}; i < 4; i++) {
        i1 = (18432 * b_i + 1152 * i) + c_i;
        i3 = (6144 * b_i + (c_i << 4)) + (i << 2);
        fv6[i3] = fv68[i1];
        fv6[i3 + 1] = fv68[i1 + 4608];
        fv6[i3 + 2] = fv68[i1 + 9216];
        fv6[i3 + 3] = fv68[i1 + 13824];
      }
    }
  }

  maxPooling2029811058482366664(&fv6[0], &fv69[0]);
  for (int e_i{0}; e_i < 1024; e_i++) {
    for (int i8{0}; i8 < 4; i8++) {
      for (int b_i{0}; b_i < 16; b_i++) {
        std::copy(&fv68[((e_i * 18432 + i8 * 96) + b_i * 1152) + 768], &fv68
                  [((e_i * 18432 + i8 * 96) + b_i * 1152) + 864], &fv6[(e_i *
                   6144 + i8 * 1536) + b_i * 96]);
      }

      i1 = 1536 * e_i + 384 * i8;
      for (int c_i{0}; c_i < 2; c_i++) {
        for (int i{0}; i < 2; i++) {
          for (int f_i{0}; f_i < 96; f_i++) {
            fv70[((i1 + 192 * c_i) + 96 * i) + f_i] = fv69[((i1 + (f_i << 2)) +
              (i << 1)) + c_i] * 0.31947154F;
          }
        }
      }

      for (int b_i{0}; b_i < 96; b_i++) {
        for (int c_i{0}; c_i < 16; c_i++) {
          fv13[((6144 * e_i + 1536 * i8) + (b_i << 4)) + c_i] = fv68[(((18432 *
            e_i + 1152 * c_i) + 96 * i8) + b_i) + 384] * 0.31947154F;
        }
      }
    }
  }

  for (int b_i{0}; b_i < 4096; b_i++) {
    matrixMultiply12417453134711121340(16, 96, 4, 128, 128, 128, &fv13[b_i *
      1536], &fv70[b_i * 384], &fv72[0]);
    std::copy(&fv72[0], &fv72[64], &fv71[b_i * 64]);
  }

  for (int b_i{0}; b_i < 16384; b_i++) {
    fv58[b_i] = -3.402823466E+38F;
  }

  for (int c_i{0}; c_i < 1024; c_i++) {
    for (int i{0}; i < 4; i++) {
      for (int f_i{0}; f_i < 4; f_i++) {
        i1 = ((c_i << 4) + (i << 2)) + f_i;
        f = fv58[i1];
        for (int b_i{0}; b_i < 16; b_i++) {
          f1 = fv71[(((c_i << 8) + (i << 6)) + (f_i << 4)) + b_i];
          if (!(f != f) && ((f1 != f1) || (f1 > f))) {
            f = f1;
          }
        }

        fv58[i1] = f;
        for (int b_i{0}; b_i < 16; b_i++) {
          i1 = (((c_i << 8) + (i << 6)) + (f_i << 4)) + b_i;
          fv73[i1] = std::exp(fv71[i1] - f);
        }
      }
    }
  }

  std::memset(&fv58[0], 0, 16384U * sizeof(float));
  for (int b_i{0}; b_i < 1024; b_i++) {
    for (int c_i{0}; c_i < 4; c_i++) {
      for (int i{0}; i < 4; i++) {
        i1 = ((b_i << 4) + (c_i << 2)) + i;
        f = fv58[i1];
        for (int f_i{0}; f_i < 16; f_i++) {
          f += fv73[(((b_i << 8) + (c_i << 6)) + (i << 4)) + f_i];
        }

        fv58[i1] = f;
      }
    }
  }

  std::memset(&bv3[0], 0, 16384U * sizeof(boolean_T));
  for (int i{0}; i < 1024; i++) {
    for (int f_i{0}; f_i < 4; f_i++) {
      for (int e_i{0}; e_i < 4; e_i++) {
        i2 = ((i << 4) + (f_i << 2)) + e_i;
        b = bv3[i2];
        for (int b_i{0}; b_i < 16; b_i++) {
          b = (!(fv71[(((i << 8) + (f_i << 6)) + (e_i << 4)) + b_i] ==
                 rtMinusInfF) || b);
        }

        bv3[i2] = b;
        for (int c_i{0}; c_i < 16; c_i++) {
          if (b) {
            i1 = (((i << 8) + (f_i << 6)) + (e_i << 4)) + c_i;
            fv73[i1] *= 1.0F / fv58[i2];
          } else {
            fv73[(((i << 8) + (f_i << 6)) + (e_i << 4)) + c_i] = 0.0F;
          }
        }
      }
    }
  }

  for (int b_i{0}; b_i < 4096; b_i++) {
    matrixMultiply12417453134711121340(96, 16, 4, 128, 128, 128, &fv6[b_i * 1536],
      &fv73[b_i << 6], &fv74[0]);
    std::copy(&fv74[0], &fv74[384], &fv69[b_i * 384]);
  }

  for (int b_i{0}; b_i < 1024; b_i++) {
    for (int c_i{0}; c_i < 2; c_i++) {
      for (int i{0}; i < 2; i++) {
        for (int f_i{0}; f_i < 4; f_i++) {
          std::copy(&fv69[((b_i * 1536 + c_i * 192) + i * 96) + f_i * 384],
                    &fv69[static_cast<int>(static_cast<unsigned int>(((b_i *
            1536 + c_i * 192) + i * 96) + f_i * 384) + 96U)], &fv70[((b_i * 1536
                      + c_i * 768) + i * 384) + f_i * 96]);
        }
      }

      std::copy(&__constant_1x1x384x384xf32[0], &__constant_1x1x384x384xf32
                [147456], &fv75[b_i * 294912 + c_i * 147456]);
    }
  }

  for (int b_i{0}; b_i < 2048; b_i++) {
    matrixMultiply12417453134711121340(384, 384, 2, 128, 128, 128, &fv75[b_i *
      147456], &fv70[b_i * 768], &fv76[0]);
    std::copy(&fv76[0], &fv76[768], &fv69[b_i * 768]);
  }

  for (int b_i{0}; b_i < 1024; b_i++) {
    for (int c_i{0}; c_i < 2; c_i++) {
      for (int i{0}; i < 2; i++) {
        for (int f_i{0}; f_i < 384; f_i++) {
          i1 = ((1536 * b_i + 768 * c_i) + 384 * i) + f_i;
          fv70[i1] = fv69[i1] + __constant_1x1x1x384xf32[f_i];
        }
      }
    }
  }

  for (int c_i{0}; c_i < 384; c_i++) {
    for (int i{0}; i < 32; i++) {
      for (int f_i{0}; f_i < 2; f_i++) {
        for (int e_i{0}; e_i < 32; e_i++) {
          i1 = (((c_i << 12) + (i << 7)) + (f_i << 6)) + (e_i << 1);
          i2 = ((49152 * e_i + 1536 * i) + 384 * f_i) + c_i;
          fv69[i1] = fv67[i1] + fv70[i2];
          fv69[i1 + 1] = fv67[i1 + 1] + fv70[i2 + 768];
        }
      }
    }
  }

  for (int b_i{0}; b_i < 64; b_i++) {
    for (int c_i{0}; c_i < 64; c_i++) {
      for (int i{0}; i < 384; i++) {
        fv70[(24576 * b_i + 384 * c_i) + i] = fv69[((i << 12) + (c_i << 6)) +
          b_i];
      }
    }
  }

  for (int b_i{0}; b_i < 1572864; b_i++) {
    dv10[b_i] = fv70[b_i];
  }

  std::memset(&dv11[0], 0, 4096U * sizeof(double));
  std::memset(&dv12[0], 0, 4096U * sizeof(double));
  std::memset(&dv13[0], 0, 4096U * sizeof(double));
  for (int c_i{0}; c_i < 64; c_i++) {
    for (int i{0}; i < 64; i++) {
      i1 = (c_i << 6) + i;
      d = dv13[i1];
      for (int b_i{0}; b_i < 384; b_i++) {
        d += dv10[(24576 * c_i + 384 * i) + b_i];
      }

      dv13[i1] = d;
      d1 = 0.0;
      for (int b_i{0}; b_i < 384; b_i++) {
        d2 = dv10[(24576 * c_i + 384 * i) + b_i] - d * 0.0026041666666666665;
        d1 += d2 * d2;
      }

      dv14[i1] = d1;
    }
  }

  std::memset(&fv35[0], 0, 4096U * sizeof(float));
  std::memset(&fv77[0], 0, 4096U * sizeof(float));
  for (int c_i{0}; c_i < 64; c_i++) {
    for (int i{0}; i < 64; i++) {
      i1 = (c_i << 6) + i;
      f = fv77[i1];
      for (int b_i{0}; b_i < 384; b_i++) {
        f += fv70[(24576 * c_i + 384 * i) + b_i];
      }

      fv77[i1] = f;
      d = dv14[i1];
      for (int b_i{0}; b_i < 384; b_i++) {
        fv70[(24576 * c_i + 384 * i) + b_i] = (fv69[((b_i << 12) + (i << 6)) +
          c_i] - f * 0.0026041667F) * (1.0F / std::sqrt(static_cast<float>(d *
          0.0026041666666666665) + 1.0E-6F)) * __constant_1x384x1x1xf32[b_i] +
          __constant_1x384x1x1xf32_128[b_i];
      }
    }
  }

  matrixMultiply4454328187142109130(1536, 384, 4096, 128, 128, 128,
    &__constant_384x1536xf32[0], &fv70[0], &fv78[0]);
  for (int b_i{0}; b_i < 4096; b_i++) {
    for (int c_i{0}; c_i < 1536; c_i++) {
      i1 = 1536 * b_i + c_i;
      fv78[i1] += __constant_1x1536xf32[c_i];
    }
  }

  for (int b_i{0}; b_i < 6291456; b_i++) {
    f4 = fv78[b_i];
    f = f4 * 0.70710677F;
    b = (f < 0.0F);
    if (b) {
      f = -f;
    }

    b1 = (f < 0.8F);
    b2 = (f < 2.0F);
    if ((f != f) || (f < 3.75F)) {
      if (b2) {
        if (b1) {
          f1 = 0.02581468F;
          f2 = 0.20974171F;
          f3 = -0.52301854F;
          f5 = 1.1283791F;
        } else {
          f1 = 0.037064552F;
          f2 = 0.1184074F;
          f3 = -0.36472142F;
          f5 = 1.1275069F;
        }

        f6 = 0.0F;
        if (b1) {
          f7 = 0.073979646F;
          f8 = -0.13180897F;
          f9 = 0.5192301F;
          f10 = -0.46351382F;
        } else {
          f7 = 0.05724428F;
          f8 = -0.088346265F;
          f9 = 0.4483691F;
          f10 = -0.327607F;
        }
      } else {
        f1 = -1.7104803E-5F;
        f2 = 0.0002534471F;
        f3 = -0.0014137363F;
        f5 = 0.0035196193F;
        f6 = -0.0033009306F;
        f7 = 0.08219089F;
        f8 = -0.5833899F;
        f9 = 1.6270593F;
        f10 = -2.0606916F;
      }

      f = static_cast<float>(!b2) + (f * (f * (f * (f * f1 + f2) + f3) + f5) +
        f6) / (f * (f * (f * (f * f7 + f8) + f9) + f10) + 1.0F);
    } else {
      f = 1.0F;
    }

    if (b) {
      f = -f;
    }

    fv6[b_i] = f4 * ((f + 1.0F) * 0.5F);
  }

  matrixMultiply12417453134711121340(384, 1536, 4096, 128, 128, 128,
    &__constant_1536x384xf32[0], &fv6[0], &fv79[0]);
  for (int b_i{0}; b_i < 4096; b_i++) {
    for (int c_i{0}; c_i < 384; c_i++) {
      i1 = 384 * b_i + c_i;
      fv79[i1] += __constant_1x384xf32_15[c_i];
    }
  }

  for (int b_i{0}; b_i < 384; b_i++) {
    for (int c_i{0}; c_i < 64; c_i++) {
      for (int i{0}; i < 64; i++) {
        i1 = ((b_i << 12) + (c_i << 6)) + i;
        fv80[i1] = fv69[i1] + fv79[(24576 * i + 384 * c_i) + b_i];
      }
    }
  }

  for (int b_i{0}; b_i < 64; b_i++) {
    for (int c_i{0}; c_i < 64; c_i++) {
      for (int i{0}; i < 384; i++) {
        fv70[(24576 * b_i + 384 * c_i) + i] = fv80[((i << 12) + (c_i << 6)) +
          b_i];
      }
    }
  }

  for (int b_i{0}; b_i < 1572864; b_i++) {
    dv10[b_i] = fv70[b_i];
  }

  std::memset(&dv13[0], 0, 4096U * sizeof(double));
  for (int c_i{0}; c_i < 64; c_i++) {
    for (int i{0}; i < 64; i++) {
      i2 = (c_i << 6) + i;
      d = dv13[i2];
      for (int b_i{0}; b_i < 384; b_i++) {
        d += dv10[(24576 * c_i + 384 * i) + b_i];
      }

      dv13[i2] = d;
      d1 = 0.0;
      f = 0.0F;
      for (int b_i{0}; b_i < 384; b_i++) {
        i1 = (24576 * c_i + 384 * i) + b_i;
        d2 = dv10[i1] - d * 0.0026041666666666665;
        d1 += d2 * d2;
        f += fv70[i1];
      }

      dv14[i2] = d1;
      fv77[i2] = f;
    }
  }

  for (int b_i{0}; b_i < 384; b_i++) {
    f = __constant_1x384x1x1xf32_129[b_i];
    f1 = __constant_1x384x1x1xf32_130[b_i];
    for (int c_i{0}; c_i < 64; c_i++) {
      for (int i{0}; i < 64; i++) {
        i1 = (i << 6) + c_i;
        i3 = ((b_i << 12) + (c_i << 6)) + i;
        fv67[i3] = (fv80[i3] - fv77[i1] * 0.0026041667F) * (1.0F / std::sqrt(
          static_cast<float>(dv14[i1] * 0.0026041666666666665) + 1.0E-6F)) * f +
          f1;
      }
    }
  }

  std::memset(&fv81[0], 0, 1881600U * sizeof(float));
  for (int b_i{0}; b_i < 384; b_i++) {
    std::memset(&fv82[b_i * 4900], 0, 4900U * sizeof(float));
    for (int c_i{0}; c_i < 64; c_i++) {
      std::copy(&fv67[b_i * 4096 + c_i * 64], &fv67[static_cast<int>(
                 static_cast<unsigned int>(b_i * 4096 + c_i * 64) + 64U)],
                &fv82[b_i * 4900 + c_i * 70]);
    }
  }

  for (int b_i{0}; b_i < 5; b_i++) {
    for (int c_i{0}; c_i < 5; c_i++) {
      for (int i{0}; i < 14; i++) {
        for (int f_i{0}; f_i < 14; f_i++) {
          for (int e_i{0}; e_i < 384; e_i++) {
            fv83[(((376320 * b_i + 75264 * c_i) + 5376 * i) + 384 * f_i) + e_i] =
              fv82[(((4900 * e_i + 980 * c_i) + 70 * f_i) + 14 * b_i) + i];
          }
        }
      }
    }
  }

  matrixMultiply4454328187142109130(1152, 384, 4900, 128, 128, 128,
    &__constant_384x1152xf32[0], &fv83[0], &fv84[0]);
  for (int b_i{0}; b_i < 4900; b_i++) {
    for (int c_i{0}; c_i < 1152; c_i++) {
      i1 = 1152 * b_i + c_i;
      fv84[i1] += __constant_1x1152xf32_16[c_i];
    }
  }

  for (int f_i{0}; f_i < 25; f_i++) {
    for (int e_i{0}; e_i < 4; e_i++) {
      for (int c_i{0}; c_i < 196; c_i++) {
        for (int i{0}; i < 96; i++) {
          i1 = ((225792 * f_i + 1152 * c_i) + 96 * e_i) + i;
          i2 = ((75264 * f_i + 18816 * e_i) + 96 * c_i) + i;
          fv82[i2] = fv84[i1 + 768];
          fv83[i2] = fv84[i1] * 0.31947154F;
        }
      }

      for (int b_i{0}; b_i < 96; b_i++) {
        for (int c_i{0}; c_i < 196; c_i++) {
          fv85[((75264 * f_i + 18816 * e_i) + 196 * b_i) + c_i] = fv84[(((225792
            * f_i + 1152 * c_i) + 96 * e_i) + b_i) + 384] * 0.31947154F;
        }
      }
    }
  }

  for (int b_i{0}; b_i < 100; b_i++) {
    matrixMultiply12417453134711121340(196, 96, 196, 128, 128, 128, &fv85[b_i *
      18816], &fv83[b_i * 18816], &fv88[0]);
    std::copy(&fv88[0], &fv88[38416], &fv86[b_i * 38416]);
  }

  for (int b_i{0}; b_i < 19600; b_i++) {
    fv87[b_i] = -3.402823466E+38F;
    fv89[b_i] = -3.402823466E+38F;
  }

  for (int c_i{0}; c_i < 25; c_i++) {
    for (int i{0}; i < 4; i++) {
      for (int f_i{0}; f_i < 196; f_i++) {
        i1 = (784 * c_i + 196 * i) + f_i;
        f = fv89[i1];
        for (int b_i{0}; b_i < 196; b_i++) {
          f1 = fv86[((153664 * c_i + 38416 * i) + 196 * f_i) + b_i];
          if (!(f != f) && ((f1 != f1) || (f1 > f))) {
            f = f1;
          }
        }

        fv89[i1] = f;
        for (int b_i{0}; b_i < 196; b_i++) {
          i1 = ((153664 * c_i + 38416 * i) + 196 * f_i) + b_i;
          fv90[i1] = std::exp(fv86[i1] - f);
        }
      }
    }
  }

  std::memset(&fv89[0], 0, 19600U * sizeof(float));
  std::memset(&fv91[0], 0, 19600U * sizeof(float));
  for (int b_i{0}; b_i < 25; b_i++) {
    for (int c_i{0}; c_i < 4; c_i++) {
      for (int i{0}; i < 196; i++) {
        i1 = (784 * b_i + 196 * c_i) + i;
        f = fv91[i1];
        for (int f_i{0}; f_i < 196; f_i++) {
          f += fv90[((153664 * b_i + 38416 * c_i) + 196 * i) + f_i];
        }

        fv91[i1] = f;
      }
    }
  }

  std::memset(&bv4[0], 0, 19600U * sizeof(boolean_T));
  std::memset(&bv5[0], 0, 19600U * sizeof(boolean_T));
  for (int i{0}; i < 25; i++) {
    for (int f_i{0}; f_i < 4; f_i++) {
      for (int e_i{0}; e_i < 196; e_i++) {
        i2 = (784 * i + 196 * f_i) + e_i;
        b = bv5[i2];
        for (int b_i{0}; b_i < 196; b_i++) {
          b = (!(fv86[((153664 * i + 38416 * f_i) + 196 * e_i) + b_i] ==
                 rtMinusInfF) || b);
        }

        bv5[i2] = b;
        for (int c_i{0}; c_i < 196; c_i++) {
          if (b) {
            i1 = ((153664 * i + 38416 * f_i) + 196 * e_i) + c_i;
            fv90[i1] *= 1.0F / fv91[i2];
          } else {
            fv90[((153664 * i + 38416 * f_i) + 196 * e_i) + c_i] = 0.0F;
          }
        }
      }
    }
  }

  for (int b_i{0}; b_i < 100; b_i++) {
    matrixMultiply12417453134711121340(96, 196, 196, 128, 128, 128, &fv82[b_i *
      18816], &fv90[b_i * 38416], &fv92[0]);
    std::copy(&fv92[0], &fv92[18816], &fv83[b_i * 18816]);
  }

  for (int b_i{0}; b_i < 25; b_i++) {
    for (int c_i{0}; c_i < 14; c_i++) {
      for (int i{0}; i < 14; i++) {
        for (int f_i{0}; f_i < 4; f_i++) {
          std::copy(&fv83[((b_i * 75264 + c_i * 1344) + i * 96) + f_i * 18816],
                    &fv83[static_cast<int>(static_cast<unsigned int>(((b_i *
            75264 + c_i * 1344) + i * 96) + f_i * 18816) + 96U)], &fv82[((b_i *
                      75264 + c_i * 5376) + i * 384) + f_i * 96]);
        }
      }

      std::copy(&__constant_1x1x384x384xf32_112[0],
                &__constant_1x1x384x384xf32_112[147456], &fv93[b_i * 2064384 +
                c_i * 147456]);
    }
  }

  for (int b_i{0}; b_i < 350; b_i++) {
    matrixMultiply12417453134711121340(384, 384, 14, 128, 128, 128, &fv93[b_i *
      147456], &fv82[b_i * 5376], &fv94[0]);
    std::copy(&fv94[0], &fv94[5376], &fv83[b_i * 5376]);
  }

  for (int b_i{0}; b_i < 25; b_i++) {
    for (int c_i{0}; c_i < 14; c_i++) {
      for (int i{0}; i < 14; i++) {
        for (int f_i{0}; f_i < 384; f_i++) {
          i1 = ((75264 * b_i + 5376 * c_i) + 384 * i) + f_i;
          fv82[i1] = fv83[i1] + __constant_1x1x1x384xf32_17[f_i];
        }
      }
    }
  }

  for (int b_i{0}; b_i < 5; b_i++) {
    for (int c_i{0}; c_i < 14; c_i++) {
      for (int i{0}; i < 5; i++) {
        for (int f_i{0}; f_i < 14; f_i++) {
          std::copy(&fv82[((b_i * 376320 + c_i * 5376) + i * 75264) + f_i * 384],
                    &fv82[static_cast<int>(static_cast<unsigned int>(((b_i *
            376320 + c_i * 5376) + i * 75264) + f_i * 384) + 384U)], &fv83[((b_i
                      * 376320 + c_i * 26880) + i * 5376) + f_i * 384]);
        }
      }
    }
  }

  for (int b_i{0}; b_i < 384; b_i++) {
    for (int c_i{0}; c_i < 64; c_i++) {
      for (int i{0}; i < 64; i++) {
        i1 = ((b_i << 12) + (c_i << 6)) + i;
        fv67[i1] = fv80[i1] + fv83[(26880 * i + 384 * c_i) + b_i];
      }
    }
  }

  for (int b_i{0}; b_i < 64; b_i++) {
    for (int c_i{0}; c_i < 64; c_i++) {
      for (int i{0}; i < 384; i++) {
        fv70[(24576 * b_i + 384 * c_i) + i] = fv67[((i << 12) + (c_i << 6)) +
          b_i];
      }
    }
  }

  for (int b_i{0}; b_i < 1572864; b_i++) {
    dv10[b_i] = fv70[b_i];
  }

  std::memset(&dv13[0], 0, 4096U * sizeof(double));
  for (int c_i{0}; c_i < 64; c_i++) {
    for (int i{0}; i < 64; i++) {
      i1 = (c_i << 6) + i;
      d = dv13[i1];
      for (int b_i{0}; b_i < 384; b_i++) {
        d += dv10[(24576 * c_i + 384 * i) + b_i];
      }

      dv13[i1] = d;
      d1 = 0.0;
      f = 0.0F;
      for (int b_i{0}; b_i < 384; b_i++) {
        i1 = (24576 * c_i + 384 * i) + b_i;
        d2 = dv10[i1] - d * 0.0026041666666666665;
        d1 += d2 * d2;
        f += fv70[i1];
      }

      for (int b_i{0}; b_i < 384; b_i++) {
        fv70[(24576 * c_i + 384 * i) + b_i] = (fv67[((b_i << 12) + (i << 6)) +
          c_i] - f * 0.0026041667F) * (1.0F / std::sqrt(static_cast<float>(d1 *
          0.0026041666666666665) + 1.0E-6F)) * __constant_1x384x1x1xf32_131[b_i]
          + __constant_1x384x1x1xf32_132[b_i];
      }
    }
  }

  matrixMultiply4454328187142109130(1536, 384, 4096, 128, 128, 128,
    &__constant_384x1536xf32_166[0], &fv70[0], &fv78[0]);
  for (int b_i{0}; b_i < 4096; b_i++) {
    for (int c_i{0}; c_i < 1536; c_i++) {
      i1 = 1536 * b_i + c_i;
      fv78[i1] += __constant_1x1536xf32_18[c_i];
    }
  }

  for (int b_i{0}; b_i < 6291456; b_i++) {
    f4 = fv78[b_i];
    f = f4 * 0.70710677F;
    b = (f < 0.0F);
    if (b) {
      f = -f;
    }

    b1 = (f < 0.8F);
    b2 = (f < 2.0F);
    if ((f != f) || (f < 3.75F)) {
      if (b2) {
        if (b1) {
          f1 = 0.02581468F;
          f2 = 0.20974171F;
          f3 = -0.52301854F;
          f5 = 1.1283791F;
        } else {
          f1 = 0.037064552F;
          f2 = 0.1184074F;
          f3 = -0.36472142F;
          f5 = 1.1275069F;
        }

        f6 = 0.0F;
        if (b1) {
          f7 = 0.073979646F;
          f8 = -0.13180897F;
          f9 = 0.5192301F;
          f10 = -0.46351382F;
        } else {
          f7 = 0.05724428F;
          f8 = -0.088346265F;
          f9 = 0.4483691F;
          f10 = -0.327607F;
        }
      } else {
        f1 = -1.7104803E-5F;
        f2 = 0.0002534471F;
        f3 = -0.0014137363F;
        f5 = 0.0035196193F;
        f6 = -0.0033009306F;
        f7 = 0.08219089F;
        f8 = -0.5833899F;
        f9 = 1.6270593F;
        f10 = -2.0606916F;
      }

      f = static_cast<float>(!b2) + (f * (f * (f * (f * f1 + f2) + f3) + f5) +
        f6) / (f * (f * (f * (f * f7 + f8) + f9) + f10) + 1.0F);
    } else {
      f = 1.0F;
    }

    if (b) {
      f = -f;
    }

    fv6[b_i] = f4 * ((f + 1.0F) * 0.5F);
  }

  matrixMultiply12417453134711121340(384, 1536, 4096, 128, 128, 128,
    &__constant_1536x384xf32_167[0], &fv6[0], &fv79[0]);
  for (int b_i{0}; b_i < 4096; b_i++) {
    for (int c_i{0}; c_i < 384; c_i++) {
      i1 = 384 * b_i + c_i;
      fv79[i1] += __constant_1x384xf32_19[c_i];
    }
  }

  for (int b_i{0}; b_i < 384; b_i++) {
    for (int c_i{0}; c_i < 64; c_i++) {
      for (int i{0}; i < 64; i++) {
        i1 = ((b_i << 12) + (c_i << 6)) + i;
        fv67[i1] += fv79[(24576 * i + 384 * c_i) + b_i];
      }
    }
  }

  for (int b_i{0}; b_i < 64; b_i++) {
    for (int c_i{0}; c_i < 64; c_i++) {
      for (int i{0}; i < 384; i++) {
        fv70[(24576 * b_i + 384 * c_i) + i] = fv67[((i << 12) + (c_i << 6)) +
          b_i];
      }
    }
  }

  for (int b_i{0}; b_i < 1572864; b_i++) {
    dv10[b_i] = fv70[b_i];
  }

  std::memset(&dv13[0], 0, 4096U * sizeof(double));
  for (int c_i{0}; c_i < 64; c_i++) {
    for (int i{0}; i < 64; i++) {
      i1 = (c_i << 6) + i;
      d = dv13[i1];
      for (int b_i{0}; b_i < 384; b_i++) {
        d += dv10[(24576 * c_i + 384 * i) + b_i];
      }

      dv13[i1] = d;
      d1 = 0.0;
      f = 0.0F;
      for (int b_i{0}; b_i < 384; b_i++) {
        i1 = (24576 * c_i + 384 * i) + b_i;
        d2 = dv10[i1] - d * 0.0026041666666666665;
        d1 += d2 * d2;
        f += fv70[i1];
      }

      for (int b_i{0}; b_i < 384; b_i++) {
        fv70[(24576 * c_i + 384 * i) + b_i] = (fv67[((b_i << 12) + (i << 6)) +
          c_i] - f * 0.0026041667F) * (1.0F / std::sqrt(static_cast<float>(d1 *
          0.0026041666666666665) + 1.0E-6F)) * __constant_1x384x1x1xf32_133[b_i]
          + __constant_1x384x1x1xf32_134[b_i];
      }
    }
  }

  matrixMultiply4454328187142109130(1152, 384, 4096, 128, 128, 128,
    &__constant_384x1152xf32_168[0], &fv70[0], &fv95[0]);
  for (int b_i{0}; b_i < 4096; b_i++) {
    for (int c_i{0}; c_i < 1152; c_i++) {
      i1 = 1152 * b_i + c_i;
      fv95[i1] += __constant_1x1152xf32_20[c_i];
    }
  }

  for (int i{0}; i < 4; i++) {
    for (int b_i{0}; b_i < 4096; b_i++) {
      for (int c_i{0}; c_i < 96; c_i++) {
        i1 = (1152 * b_i + 96 * i) + c_i;
        i3 = (393216 * i + 96 * b_i) + c_i;
        fv69[i3] = fv95[i1 + 768];
        fv70[i3] = fv95[i1] * 0.31947154F;
      }
    }

    for (int b_i{0}; b_i < 96; b_i++) {
      for (int c_i{0}; c_i < 4096; c_i++) {
        fv80[(393216 * i + (b_i << 12)) + c_i] = fv95[((1152 * c_i + 96 * i) +
          b_i) + 384] * 0.31947154F;
      }
    }
  }

  for (int b_i{0}; b_i < 4; b_i++) {
    matrixMultiply4454328187142109130(4096, 96, 4096, 128, 128, 128, &fv80[b_i *
      393216], &fv70[b_i * 393216], &fv97[0]);
    std::copy(&fv97[0], &fv97[16777216], &fv96[b_i * 16777216]);
  }

  for (int b_i{0}; b_i < 16384; b_i++) {
    fv58[b_i] = -3.402823466E+38F;
    fv98[b_i] = -3.402823466E+38F;
  }

  for (int c_i{0}; c_i < 4; c_i++) {
    for (int i{0}; i < 4096; i++) {
      i1 = (c_i << 12) + i;
      f = fv98[i1];
      for (int b_i{0}; b_i < 4096; b_i++) {
        f1 = fv96[((c_i << 24) + (i << 12)) + b_i];
        if (!(f != f) && ((f1 != f1) || (f1 > f))) {
          f = f1;
        }
      }

      fv98[i1] = f;
      for (int b_i{0}; b_i < 4096; b_i++) {
        i1 = ((c_i << 24) + (i << 12)) + b_i;
        fv99[i1] = std::exp(fv96[i1] - f);
      }
    }
  }

  std::memset(&fv59[0], 0, 16384U * sizeof(float));
  std::memset(&fv98[0], 0, 16384U * sizeof(float));
  for (int b_i{0}; b_i < 4; b_i++) {
    for (int c_i{0}; c_i < 4096; c_i++) {
      i1 = (b_i << 12) + c_i;
      f = fv98[i1];
      for (int i{0}; i < 4096; i++) {
        f += fv99[((b_i << 24) + (c_i << 12)) + i];
      }

      fv98[i1] = f;
    }
  }

  std::memset(&bv3[0], 0, 16384U * sizeof(boolean_T));
  std::memset(&bv6[0], 0, 16384U * sizeof(boolean_T));
  for (int c_i{0}; c_i < 4; c_i++) {
    for (int i{0}; i < 4096; i++) {
      i2 = (c_i << 12) + i;
      b = bv6[i2];
      for (int b_i{0}; b_i < 4096; b_i++) {
        b = (!(fv96[((c_i << 24) + (i << 12)) + b_i] == rtMinusInfF) || b);
      }

      bv6[i2] = b;
      for (int b_i{0}; b_i < 4096; b_i++) {
        if (b) {
          i1 = ((c_i << 24) + (i << 12)) + b_i;
          fv99[i1] *= 1.0F / fv98[i2];
        } else {
          fv99[((c_i << 24) + (i << 12)) + b_i] = 0.0F;
        }
      }
    }
  }

  for (int b_i{0}; b_i < 4; b_i++) {
    matrixMultiply12417453134711121340(96, 4096, 4096, 128, 128, 128, &fv69[b_i *
      393216], &fv99[b_i << 24], &fv100[0]);
    std::copy(&fv100[0], &fv100[393216], &fv70[b_i * 393216]);
  }

  for (int b_i{0}; b_i < 4096; b_i++) {
    for (int c_i{0}; c_i < 4; c_i++) {
      std::copy(&fv70[b_i * 96 + c_i * 393216], &fv70[static_cast<int>(
                 static_cast<unsigned int>(b_i * 96 + c_i * 393216) + 96U)],
                &fv69[b_i * 384 + c_i * 96]);
    }
  }

  matrixMultiply12417453134711121340(384, 384, 4096, 128, 128, 128,
    &__constant_384x384xf32[0], &fv69[0], &fv79[0]);
  for (int b_i{0}; b_i < 4096; b_i++) {
    for (int c_i{0}; c_i < 384; c_i++) {
      i1 = 384 * b_i + c_i;
      fv79[i1] += __constant_1x384xf32_21[c_i];
    }
  }

  for (int b_i{0}; b_i < 384; b_i++) {
    for (int c_i{0}; c_i < 64; c_i++) {
      for (int i{0}; i < 64; i++) {
        i1 = ((b_i << 12) + (c_i << 6)) + i;
        fv67[i1] += fv79[(24576 * i + 384 * c_i) + b_i];
      }
    }
  }

  for (int b_i{0}; b_i < 64; b_i++) {
    for (int c_i{0}; c_i < 64; c_i++) {
      for (int i{0}; i < 384; i++) {
        fv70[(24576 * b_i + 384 * c_i) + i] = fv67[((i << 12) + (c_i << 6)) +
          b_i];
      }
    }
  }

  for (int b_i{0}; b_i < 1572864; b_i++) {
    dv10[b_i] = fv70[b_i];
  }

  std::memset(&dv13[0], 0, 4096U * sizeof(double));
  for (int c_i{0}; c_i < 64; c_i++) {
    for (int i{0}; i < 64; i++) {
      i1 = (c_i << 6) + i;
      d = dv13[i1];
      for (int b_i{0}; b_i < 384; b_i++) {
        d += dv10[(24576 * c_i + 384 * i) + b_i];
      }

      dv13[i1] = d;
      d1 = 0.0;
      f = 0.0F;
      for (int b_i{0}; b_i < 384; b_i++) {
        i1 = (24576 * c_i + 384 * i) + b_i;
        d2 = dv10[i1] - d * 0.0026041666666666665;
        d1 += d2 * d2;
        f += fv70[i1];
      }

      for (int b_i{0}; b_i < 384; b_i++) {
        fv70[(24576 * c_i + 384 * i) + b_i] = (fv67[((b_i << 12) + (i << 6)) +
          c_i] - f * 0.0026041667F) * (1.0F / std::sqrt(static_cast<float>(d1 *
          0.0026041666666666665) + 1.0E-6F)) * __constant_1x384x1x1xf32_135[b_i]
          + __constant_1x384x1x1xf32_136[b_i];
      }
    }
  }

  matrixMultiply4454328187142109130(1536, 384, 4096, 128, 128, 128,
    &__constant_384x1536xf32_169[0], &fv70[0], &fv78[0]);
  for (int b_i{0}; b_i < 4096; b_i++) {
    for (int c_i{0}; c_i < 1536; c_i++) {
      i1 = 1536 * b_i + c_i;
      fv78[i1] += __constant_1x1536xf32_22[c_i];
    }
  }

  for (int b_i{0}; b_i < 6291456; b_i++) {
    f4 = fv78[b_i];
    f = f4 * 0.70710677F;
    b = (f < 0.0F);
    if (b) {
      f = -f;
    }

    b1 = (f < 0.8F);
    b2 = (f < 2.0F);
    if ((f != f) || (f < 3.75F)) {
      if (b2) {
        if (b1) {
          f1 = 0.02581468F;
          f2 = 0.20974171F;
          f3 = -0.52301854F;
          f5 = 1.1283791F;
        } else {
          f1 = 0.037064552F;
          f2 = 0.1184074F;
          f3 = -0.36472142F;
          f5 = 1.1275069F;
        }

        f6 = 0.0F;
        if (b1) {
          f7 = 0.073979646F;
          f8 = -0.13180897F;
          f9 = 0.5192301F;
          f10 = -0.46351382F;
        } else {
          f7 = 0.05724428F;
          f8 = -0.088346265F;
          f9 = 0.4483691F;
          f10 = -0.327607F;
        }
      } else {
        f1 = -1.7104803E-5F;
        f2 = 0.0002534471F;
        f3 = -0.0014137363F;
        f5 = 0.0035196193F;
        f6 = -0.0033009306F;
        f7 = 0.08219089F;
        f8 = -0.5833899F;
        f9 = 1.6270593F;
        f10 = -2.0606916F;
      }

      f = static_cast<float>(!b2) + (f * (f * (f * (f * f1 + f2) + f3) + f5) +
        f6) / (f * (f * (f * (f * f7 + f8) + f9) + f10) + 1.0F);
    } else {
      f = 1.0F;
    }

    if (b) {
      f = -f;
    }

    fv6[b_i] = f4 * ((f + 1.0F) * 0.5F);
  }

  matrixMultiply12417453134711121340(384, 1536, 4096, 128, 128, 128,
    &__constant_1536x384xf32_170[0], &fv6[0], &fv79[0]);
  for (int b_i{0}; b_i < 4096; b_i++) {
    for (int c_i{0}; c_i < 384; c_i++) {
      i1 = 384 * b_i + c_i;
      fv79[i1] += __constant_1x384xf32_23[c_i];
    }
  }

  for (int b_i{0}; b_i < 384; b_i++) {
    for (int c_i{0}; c_i < 64; c_i++) {
      for (int i{0}; i < 64; i++) {
        i1 = ((b_i << 12) + (c_i << 6)) + i;
        fv67[i1] += fv79[(24576 * i + 384 * c_i) + b_i];
      }
    }
  }

  for (int b_i{0}; b_i < 64; b_i++) {
    for (int c_i{0}; c_i < 64; c_i++) {
      for (int i{0}; i < 384; i++) {
        fv70[(24576 * b_i + 384 * c_i) + i] = fv67[((i << 12) + (c_i << 6)) +
          b_i];
      }
    }
  }

  for (int b_i{0}; b_i < 1572864; b_i++) {
    dv10[b_i] = fv70[b_i];
  }

  std::memset(&dv13[0], 0, 4096U * sizeof(double));
  for (int c_i{0}; c_i < 64; c_i++) {
    for (int i{0}; i < 64; i++) {
      i2 = (c_i << 6) + i;
      d = dv13[i2];
      for (int b_i{0}; b_i < 384; b_i++) {
        d += dv10[(24576 * c_i + 384 * i) + b_i];
      }

      dv13[i2] = d;
      d1 = 0.0;
      f = 0.0F;
      for (int b_i{0}; b_i < 384; b_i++) {
        i1 = (24576 * c_i + 384 * i) + b_i;
        d2 = dv10[i1] - d * 0.0026041666666666665;
        d1 += d2 * d2;
        f += fv70[i1];
      }

      dv14[i2] = d1;
      fv77[i2] = f;
    }
  }

  for (int i{0}; i < 384; i++) {
    f = __constant_1x384x1x1xf32_137[i];
    f1 = __constant_1x384x1x1xf32_138[i];
    for (int b_i{0}; b_i < 64; b_i++) {
      for (int c_i{0}; c_i < 64; c_i++) {
        i1 = (c_i << 6) + b_i;
        fv81[(4900 * i + 70 * b_i) + c_i] = (fv67[((i << 12) + (b_i << 6)) + c_i]
          - fv77[i1] * 0.0026041667F) * (1.0F / std::sqrt(static_cast<float>
          (dv14[i1] * 0.0026041666666666665) + 1.0E-6F)) * f + f1;
      }
    }

    std::copy(&fv81[i * 4900], &fv81[static_cast<int>(static_cast<unsigned int>
               (i * 4900) + 4900U)], &fv82[i * 4900]);
    for (int b_i{0}; b_i < 64; b_i++) {
      std::copy(&fv81[i * 4900 + b_i * 70], &fv81[static_cast<int>(static_cast<
                 unsigned int>(i * 4900 + b_i * 70) + 64U)], &fv82[i * 4900 +
                b_i * 70]);
    }
  }

  for (int b_i{0}; b_i < 5; b_i++) {
    for (int c_i{0}; c_i < 5; c_i++) {
      for (int i{0}; i < 14; i++) {
        for (int f_i{0}; f_i < 14; f_i++) {
          for (int e_i{0}; e_i < 384; e_i++) {
            fv83[(((376320 * b_i + 75264 * c_i) + 5376 * i) + 384 * f_i) + e_i] =
              fv82[(((4900 * e_i + 980 * c_i) + 70 * f_i) + 14 * b_i) + i];
          }
        }
      }
    }
  }

  matrixMultiply4454328187142109130(1152, 384, 4900, 128, 128, 128,
    &__constant_384x1152xf32_171[0], &fv83[0], &fv84[0]);
  for (int b_i{0}; b_i < 4900; b_i++) {
    for (int c_i{0}; c_i < 1152; c_i++) {
      i1 = 1152 * b_i + c_i;
      fv84[i1] += __constant_1x1152xf32_24[c_i];
    }
  }

  for (int f_i{0}; f_i < 25; f_i++) {
    for (int e_i{0}; e_i < 4; e_i++) {
      for (int c_i{0}; c_i < 196; c_i++) {
        for (int i{0}; i < 96; i++) {
          i1 = ((225792 * f_i + 1152 * c_i) + 96 * e_i) + i;
          i2 = ((75264 * f_i + 18816 * e_i) + 96 * c_i) + i;
          fv82[i2] = fv84[i1 + 768];
          fv83[i2] = fv84[i1] * 0.31947154F;
        }
      }

      for (int b_i{0}; b_i < 96; b_i++) {
        for (int c_i{0}; c_i < 196; c_i++) {
          fv85[((75264 * f_i + 18816 * e_i) + 196 * b_i) + c_i] = fv84[(((225792
            * f_i + 1152 * c_i) + 96 * e_i) + b_i) + 384] * 0.31947154F;
        }
      }
    }
  }

  for (int b_i{0}; b_i < 100; b_i++) {
    matrixMultiply12417453134711121340(196, 96, 196, 128, 128, 128, &fv85[b_i *
      18816], &fv83[b_i * 18816], &fv88[0]);
    std::copy(&fv88[0], &fv88[38416], &fv86[b_i * 38416]);
  }

  for (int b_i{0}; b_i < 19600; b_i++) {
    fv91[b_i] = -3.402823466E+38F;
  }

  for (int i{0}; i < 25; i++) {
    for (int f_i{0}; f_i < 4; f_i++) {
      for (int e_i{0}; e_i < 196; e_i++) {
        i2 = (784 * i + 196 * f_i) + e_i;
        f2 = fv91[i2];
        for (int b_i{0}; b_i < 196; b_i++) {
          f = fv86[((153664 * i + 38416 * f_i) + 196 * e_i) + b_i];
          if (!(f2 != f2) && ((f != f) || (f > f2))) {
            f2 = f;
          }
        }

        fv91[i2] = f2;
        f = 0.0F;
        for (int c_i{0}; c_i < 196; c_i++) {
          i1 = ((153664 * i + 38416 * f_i) + 196 * e_i) + c_i;
          f1 = std::exp(fv86[i1] - f2);
          fv90[i1] = f1;
          f += f1;
        }

        fv101[i2] = f;
        bv5[(e_i + 196 * f_i) + 784 * i] = false;
      }
    }
  }

  for (int i{0}; i < 25; i++) {
    for (int f_i{0}; f_i < 4; f_i++) {
      for (int e_i{0}; e_i < 196; e_i++) {
        i2 = (784 * i + 196 * f_i) + e_i;
        b = bv5[i2];
        for (int b_i{0}; b_i < 196; b_i++) {
          b = (!(fv86[((153664 * i + 38416 * f_i) + 196 * e_i) + b_i] ==
                 rtMinusInfF) || b);
        }

        bv5[i2] = b;
        for (int c_i{0}; c_i < 196; c_i++) {
          if (b) {
            i1 = ((153664 * i + 38416 * f_i) + 196 * e_i) + c_i;
            fv90[i1] *= 1.0F / fv101[i2];
          } else {
            fv90[((153664 * i + 38416 * f_i) + 196 * e_i) + c_i] = 0.0F;
          }
        }
      }
    }
  }

  for (int b_i{0}; b_i < 100; b_i++) {
    matrixMultiply12417453134711121340(96, 196, 196, 128, 128, 128, &fv82[b_i *
      18816], &fv90[b_i * 38416], &fv92[0]);
    std::copy(&fv92[0], &fv92[18816], &fv83[b_i * 18816]);
  }

  for (int b_i{0}; b_i < 25; b_i++) {
    for (int c_i{0}; c_i < 14; c_i++) {
      for (int i{0}; i < 14; i++) {
        for (int f_i{0}; f_i < 4; f_i++) {
          std::copy(&fv83[((b_i * 75264 + c_i * 1344) + i * 96) + f_i * 18816],
                    &fv83[static_cast<int>(static_cast<unsigned int>(((b_i *
            75264 + c_i * 1344) + i * 96) + f_i * 18816) + 96U)], &fv82[((b_i *
                      75264 + c_i * 5376) + i * 384) + f_i * 96]);
        }
      }

      std::copy(&__constant_1x1x384x384xf32_113[0],
                &__constant_1x1x384x384xf32_113[147456], &fv93[b_i * 2064384 +
                c_i * 147456]);
    }
  }

  for (int b_i{0}; b_i < 350; b_i++) {
    matrixMultiply12417453134711121340(384, 384, 14, 128, 128, 128, &fv93[b_i *
      147456], &fv82[b_i * 5376], &fv94[0]);
    std::copy(&fv94[0], &fv94[5376], &fv83[b_i * 5376]);
  }

  for (int b_i{0}; b_i < 25; b_i++) {
    for (int c_i{0}; c_i < 14; c_i++) {
      for (int i{0}; i < 14; i++) {
        for (int f_i{0}; f_i < 384; f_i++) {
          i1 = ((75264 * b_i + 5376 * c_i) + 384 * i) + f_i;
          fv82[i1] = fv83[i1] + __constant_1x1x1x384xf32_25[f_i];
        }
      }
    }
  }

  for (int b_i{0}; b_i < 5; b_i++) {
    for (int c_i{0}; c_i < 14; c_i++) {
      for (int i{0}; i < 5; i++) {
        for (int f_i{0}; f_i < 14; f_i++) {
          std::copy(&fv82[((b_i * 376320 + c_i * 5376) + i * 75264) + f_i * 384],
                    &fv82[static_cast<int>(static_cast<unsigned int>(((b_i *
            376320 + c_i * 5376) + i * 75264) + f_i * 384) + 384U)], &fv83[((b_i
                      * 376320 + c_i * 26880) + i * 5376) + f_i * 384]);
        }
      }
    }
  }

  for (int b_i{0}; b_i < 384; b_i++) {
    for (int c_i{0}; c_i < 64; c_i++) {
      for (int i{0}; i < 64; i++) {
        i1 = ((b_i << 12) + (c_i << 6)) + i;
        fv67[i1] += fv83[(26880 * i + 384 * c_i) + b_i];
      }
    }
  }

  for (int b_i{0}; b_i < 64; b_i++) {
    for (int c_i{0}; c_i < 64; c_i++) {
      for (int i{0}; i < 384; i++) {
        fv70[(24576 * b_i + 384 * c_i) + i] = fv67[((i << 12) + (c_i << 6)) +
          b_i];
      }
    }
  }

  for (int b_i{0}; b_i < 1572864; b_i++) {
    dv10[b_i] = fv70[b_i];
  }

  std::memset(&dv13[0], 0, 4096U * sizeof(double));
  for (int c_i{0}; c_i < 64; c_i++) {
    for (int i{0}; i < 64; i++) {
      i1 = (c_i << 6) + i;
      d = dv13[i1];
      for (int b_i{0}; b_i < 384; b_i++) {
        d += dv10[(24576 * c_i + 384 * i) + b_i];
      }

      dv13[i1] = d;
      d1 = 0.0;
      f = 0.0F;
      for (int b_i{0}; b_i < 384; b_i++) {
        i1 = (24576 * c_i + 384 * i) + b_i;
        d2 = dv10[i1] - d * 0.0026041666666666665;
        d1 += d2 * d2;
        f += fv70[i1];
      }

      for (int b_i{0}; b_i < 384; b_i++) {
        fv70[(24576 * c_i + 384 * i) + b_i] = (fv67[((b_i << 12) + (i << 6)) +
          c_i] - f * 0.0026041667F) * (1.0F / std::sqrt(static_cast<float>(d1 *
          0.0026041666666666665) + 1.0E-6F)) * __constant_1x384x1x1xf32_139[b_i]
          + __constant_1x384x1x1xf32_140[b_i];
      }
    }
  }

  matrixMultiply4454328187142109130(1536, 384, 4096, 128, 128, 128,
    &__constant_384x1536xf32_172[0], &fv70[0], &fv78[0]);
  for (int b_i{0}; b_i < 4096; b_i++) {
    for (int c_i{0}; c_i < 1536; c_i++) {
      i1 = 1536 * b_i + c_i;
      fv78[i1] += __constant_1x1536xf32_26[c_i];
    }
  }

  for (int b_i{0}; b_i < 6291456; b_i++) {
    f4 = fv78[b_i];
    f = f4 * 0.70710677F;
    b = (f < 0.0F);
    if (b) {
      f = -f;
    }

    b1 = (f < 0.8F);
    b2 = (f < 2.0F);
    if ((f != f) || (f < 3.75F)) {
      if (b2) {
        if (b1) {
          f1 = 0.02581468F;
          f2 = 0.20974171F;
          f3 = -0.52301854F;
          f5 = 1.1283791F;
        } else {
          f1 = 0.037064552F;
          f2 = 0.1184074F;
          f3 = -0.36472142F;
          f5 = 1.1275069F;
        }

        f6 = 0.0F;
        if (b1) {
          f7 = 0.073979646F;
          f8 = -0.13180897F;
          f9 = 0.5192301F;
          f10 = -0.46351382F;
        } else {
          f7 = 0.05724428F;
          f8 = -0.088346265F;
          f9 = 0.4483691F;
          f10 = -0.327607F;
        }
      } else {
        f1 = -1.7104803E-5F;
        f2 = 0.0002534471F;
        f3 = -0.0014137363F;
        f5 = 0.0035196193F;
        f6 = -0.0033009306F;
        f7 = 0.08219089F;
        f8 = -0.5833899F;
        f9 = 1.6270593F;
        f10 = -2.0606916F;
      }

      f = static_cast<float>(!b2) + (f * (f * (f * (f * f1 + f2) + f3) + f5) +
        f6) / (f * (f * (f * (f * f7 + f8) + f9) + f10) + 1.0F);
    } else {
      f = 1.0F;
    }

    if (b) {
      f = -f;
    }

    fv6[b_i] = f4 * ((f + 1.0F) * 0.5F);
  }

  matrixMultiply12417453134711121340(384, 1536, 4096, 128, 128, 128,
    &__constant_1536x384xf32_173[0], &fv6[0], &fv79[0]);
  for (int b_i{0}; b_i < 4096; b_i++) {
    for (int c_i{0}; c_i < 384; c_i++) {
      i1 = 384 * b_i + c_i;
      fv79[i1] += __constant_1x384xf32_27[c_i];
    }
  }

  for (int b_i{0}; b_i < 384; b_i++) {
    for (int c_i{0}; c_i < 64; c_i++) {
      for (int i{0}; i < 64; i++) {
        i1 = ((b_i << 12) + (c_i << 6)) + i;
        fv67[i1] += fv79[(24576 * i + 384 * c_i) + b_i];
      }
    }
  }

  for (int b_i{0}; b_i < 64; b_i++) {
    for (int c_i{0}; c_i < 64; c_i++) {
      for (int i{0}; i < 384; i++) {
        fv70[(24576 * b_i + 384 * c_i) + i] = fv67[((i << 12) + (c_i << 6)) +
          b_i];
      }
    }
  }

  for (int b_i{0}; b_i < 1572864; b_i++) {
    dv10[b_i] = fv70[b_i];
  }

  std::memset(&dv13[0], 0, 4096U * sizeof(double));
  for (int c_i{0}; c_i < 64; c_i++) {
    for (int i{0}; i < 64; i++) {
      i1 = (c_i << 6) + i;
      d = dv13[i1];
      for (int b_i{0}; b_i < 384; b_i++) {
        d += dv10[(24576 * c_i + 384 * i) + b_i];
      }

      dv13[i1] = d;
      d1 = 0.0;
      f = 0.0F;
      for (int b_i{0}; b_i < 384; b_i++) {
        i1 = (24576 * c_i + 384 * i) + b_i;
        d2 = dv10[i1] - d * 0.0026041666666666665;
        d1 += d2 * d2;
        f += fv70[i1];
      }

      for (int b_i{0}; b_i < 384; b_i++) {
        fv70[(24576 * c_i + 384 * i) + b_i] = (fv67[((b_i << 12) + (i << 6)) +
          c_i] - f * 0.0026041667F) * (1.0F / std::sqrt(static_cast<float>(d1 *
          0.0026041666666666665) + 1.0E-6F)) * __constant_1x384x1x1xf32_141[b_i]
          + __constant_1x384x1x1xf32_142[b_i];
      }
    }
  }

  matrixMultiply4454328187142109130(1152, 384, 4096, 128, 128, 128,
    &__constant_384x1152xf32_174[0], &fv70[0], &fv95[0]);
  for (int b_i{0}; b_i < 4096; b_i++) {
    for (int c_i{0}; c_i < 1152; c_i++) {
      i1 = 1152 * b_i + c_i;
      fv95[i1] += __constant_1x1152xf32_28[c_i];
    }
  }

  for (int i{0}; i < 4; i++) {
    for (int b_i{0}; b_i < 4096; b_i++) {
      for (int c_i{0}; c_i < 96; c_i++) {
        i1 = (1152 * b_i + 96 * i) + c_i;
        i3 = (393216 * i + 96 * b_i) + c_i;
        fv69[i3] = fv95[i1 + 768];
        fv70[i3] = fv95[i1] * 0.31947154F;
      }
    }

    for (int b_i{0}; b_i < 96; b_i++) {
      for (int c_i{0}; c_i < 4096; c_i++) {
        fv80[(393216 * i + (b_i << 12)) + c_i] = fv95[((1152 * c_i + 96 * i) +
          b_i) + 384] * 0.31947154F;
      }
    }
  }

  for (int b_i{0}; b_i < 4; b_i++) {
    matrixMultiply4454328187142109130(4096, 96, 4096, 128, 128, 128, &fv80[b_i *
      393216], &fv70[b_i * 393216], &fv97[0]);
    std::copy(&fv97[0], &fv97[16777216], &fv96[b_i * 16777216]);
  }

  for (int b_i{0}; b_i < 16384; b_i++) {
    fv98[b_i] = -3.402823466E+38F;
  }

  for (int c_i{0}; c_i < 4; c_i++) {
    for (int i{0}; i < 4096; i++) {
      i2 = (c_i << 12) + i;
      f2 = fv98[i2];
      for (int b_i{0}; b_i < 4096; b_i++) {
        f = fv96[((c_i << 24) + (i << 12)) + b_i];
        if (!(f2 != f2) && ((f != f) || (f > f2))) {
          f2 = f;
        }
      }

      fv98[i2] = f2;
      f = 0.0F;
      for (int b_i{0}; b_i < 4096; b_i++) {
        i1 = ((c_i << 24) + (i << 12)) + b_i;
        f1 = std::exp(fv96[i1] - f2);
        fv99[i1] = f1;
        f += f1;
      }

      fv102[i2] = f;
      bv6[i2] = false;
    }
  }

  for (int c_i{0}; c_i < 4; c_i++) {
    for (int i{0}; i < 4096; i++) {
      i2 = (c_i << 12) + i;
      b = bv6[i2];
      for (int b_i{0}; b_i < 4096; b_i++) {
        b = (!(fv96[((c_i << 24) + (i << 12)) + b_i] == rtMinusInfF) || b);
      }

      bv6[i2] = b;
      for (int b_i{0}; b_i < 4096; b_i++) {
        if (b) {
          i1 = ((c_i << 24) + (i << 12)) + b_i;
          fv99[i1] *= 1.0F / fv102[i2];
        } else {
          fv99[((c_i << 24) + (i << 12)) + b_i] = 0.0F;
        }
      }
    }
  }

  for (int b_i{0}; b_i < 4; b_i++) {
    matrixMultiply12417453134711121340(96, 4096, 4096, 128, 128, 128, &fv69[b_i *
      393216], &fv99[b_i << 24], &fv100[0]);
    std::copy(&fv100[0], &fv100[393216], &fv70[b_i * 393216]);
  }

  for (int b_i{0}; b_i < 4096; b_i++) {
    for (int c_i{0}; c_i < 4; c_i++) {
      std::copy(&fv70[b_i * 96 + c_i * 393216], &fv70[static_cast<int>(
                 static_cast<unsigned int>(b_i * 96 + c_i * 393216) + 96U)],
                &fv69[b_i * 384 + c_i * 96]);
    }
  }

  matrixMultiply12417453134711121340(384, 384, 4096, 128, 128, 128,
    &__constant_384x384xf32_175[0], &fv69[0], &fv79[0]);
  for (int b_i{0}; b_i < 4096; b_i++) {
    for (int c_i{0}; c_i < 384; c_i++) {
      i1 = 384 * b_i + c_i;
      fv79[i1] += __constant_1x384xf32_29[c_i];
    }
  }

  for (int b_i{0}; b_i < 384; b_i++) {
    for (int c_i{0}; c_i < 64; c_i++) {
      for (int i{0}; i < 64; i++) {
        i1 = ((b_i << 12) + (c_i << 6)) + i;
        fv67[i1] += fv79[(24576 * i + 384 * c_i) + b_i];
      }
    }
  }

  for (int b_i{0}; b_i < 64; b_i++) {
    for (int c_i{0}; c_i < 64; c_i++) {
      for (int i{0}; i < 384; i++) {
        fv70[(24576 * b_i + 384 * c_i) + i] = fv67[((i << 12) + (c_i << 6)) +
          b_i];
      }
    }
  }

  for (int b_i{0}; b_i < 1572864; b_i++) {
    dv10[b_i] = fv70[b_i];
  }

  std::memset(&dv13[0], 0, 4096U * sizeof(double));
  for (int c_i{0}; c_i < 64; c_i++) {
    for (int i{0}; i < 64; i++) {
      i1 = (c_i << 6) + i;
      d = dv13[i1];
      for (int b_i{0}; b_i < 384; b_i++) {
        d += dv10[(24576 * c_i + 384 * i) + b_i];
      }

      dv13[i1] = d;
      d1 = 0.0;
      f = 0.0F;
      for (int b_i{0}; b_i < 384; b_i++) {
        i1 = (24576 * c_i + 384 * i) + b_i;
        d2 = dv10[i1] - d * 0.0026041666666666665;
        d1 += d2 * d2;
        f += fv70[i1];
      }

      for (int b_i{0}; b_i < 384; b_i++) {
        fv70[(24576 * c_i + 384 * i) + b_i] = (fv67[((b_i << 12) + (i << 6)) +
          c_i] - f * 0.0026041667F) * (1.0F / std::sqrt(static_cast<float>(d1 *
          0.0026041666666666665) + 1.0E-6F)) * __constant_1x384x1x1xf32_143[b_i]
          + __constant_1x384x1x1xf32_144[b_i];
      }
    }
  }

  matrixMultiply4454328187142109130(1536, 384, 4096, 128, 128, 128,
    &__constant_384x1536xf32_176[0], &fv70[0], &fv78[0]);
  for (int b_i{0}; b_i < 4096; b_i++) {
    for (int c_i{0}; c_i < 1536; c_i++) {
      i1 = 1536 * b_i + c_i;
      fv78[i1] += __constant_1x1536xf32_30[c_i];
    }
  }

  for (int b_i{0}; b_i < 6291456; b_i++) {
    f4 = fv78[b_i];
    f = f4 * 0.70710677F;
    b = (f < 0.0F);
    if (b) {
      f = -f;
    }

    b1 = (f < 0.8F);
    b2 = (f < 2.0F);
    if ((f != f) || (f < 3.75F)) {
      if (b2) {
        if (b1) {
          f1 = 0.02581468F;
          f2 = 0.20974171F;
          f3 = -0.52301854F;
          f5 = 1.1283791F;
        } else {
          f1 = 0.037064552F;
          f2 = 0.1184074F;
          f3 = -0.36472142F;
          f5 = 1.1275069F;
        }

        f6 = 0.0F;
        if (b1) {
          f7 = 0.073979646F;
          f8 = -0.13180897F;
          f9 = 0.5192301F;
          f10 = -0.46351382F;
        } else {
          f7 = 0.05724428F;
          f8 = -0.088346265F;
          f9 = 0.4483691F;
          f10 = -0.327607F;
        }
      } else {
        f1 = -1.7104803E-5F;
        f2 = 0.0002534471F;
        f3 = -0.0014137363F;
        f5 = 0.0035196193F;
        f6 = -0.0033009306F;
        f7 = 0.08219089F;
        f8 = -0.5833899F;
        f9 = 1.6270593F;
        f10 = -2.0606916F;
      }

      f = static_cast<float>(!b2) + (f * (f * (f * (f * f1 + f2) + f3) + f5) +
        f6) / (f * (f * (f * (f * f7 + f8) + f9) + f10) + 1.0F);
    } else {
      f = 1.0F;
    }

    if (b) {
      f = -f;
    }

    fv6[b_i] = f4 * ((f + 1.0F) * 0.5F);
  }

  matrixMultiply12417453134711121340(384, 1536, 4096, 128, 128, 128,
    &__constant_1536x384xf32_177[0], &fv6[0], &fv79[0]);
  for (int b_i{0}; b_i < 4096; b_i++) {
    for (int c_i{0}; c_i < 384; c_i++) {
      i1 = 384 * b_i + c_i;
      fv79[i1] += __constant_1x384xf32_31[c_i];
    }
  }

  for (int b_i{0}; b_i < 384; b_i++) {
    for (int c_i{0}; c_i < 64; c_i++) {
      for (int i{0}; i < 64; i++) {
        i1 = ((b_i << 12) + (c_i << 6)) + i;
        fv67[i1] += fv79[(24576 * i + 384 * c_i) + b_i];
      }
    }
  }

  for (int b_i{0}; b_i < 64; b_i++) {
    for (int c_i{0}; c_i < 64; c_i++) {
      for (int i{0}; i < 384; i++) {
        fv70[(24576 * b_i + 384 * c_i) + i] = fv67[((i << 12) + (c_i << 6)) +
          b_i];
      }
    }
  }

  for (int b_i{0}; b_i < 1572864; b_i++) {
    dv10[b_i] = fv70[b_i];
  }

  std::memset(&dv13[0], 0, 4096U * sizeof(double));
  for (int c_i{0}; c_i < 64; c_i++) {
    for (int i{0}; i < 64; i++) {
      i2 = (c_i << 6) + i;
      d = dv13[i2];
      for (int b_i{0}; b_i < 384; b_i++) {
        d += dv10[(24576 * c_i + 384 * i) + b_i];
      }

      dv13[i2] = d;
      d1 = 0.0;
      f = 0.0F;
      for (int b_i{0}; b_i < 384; b_i++) {
        i1 = (24576 * c_i + 384 * i) + b_i;
        d2 = dv10[i1] - d * 0.0026041666666666665;
        d1 += d2 * d2;
        f += fv70[i1];
      }

      dv14[i2] = d1;
      fv77[i2] = f;
    }
  }

  for (int i{0}; i < 384; i++) {
    f = __constant_1x384x1x1xf32_145[i];
    f1 = __constant_1x384x1x1xf32_146[i];
    for (int b_i{0}; b_i < 64; b_i++) {
      for (int c_i{0}; c_i < 64; c_i++) {
        i1 = (c_i << 6) + b_i;
        fv81[(4900 * i + 70 * b_i) + c_i] = (fv67[((i << 12) + (b_i << 6)) + c_i]
          - fv77[i1] * 0.0026041667F) * (1.0F / std::sqrt(static_cast<float>
          (dv14[i1] * 0.0026041666666666665) + 1.0E-6F)) * f + f1;
      }
    }

    std::copy(&fv81[i * 4900], &fv81[static_cast<int>(static_cast<unsigned int>
               (i * 4900) + 4900U)], &fv82[i * 4900]);
    for (int b_i{0}; b_i < 64; b_i++) {
      std::copy(&fv81[i * 4900 + b_i * 70], &fv81[static_cast<int>(static_cast<
                 unsigned int>(i * 4900 + b_i * 70) + 64U)], &fv82[i * 4900 +
                b_i * 70]);
    }
  }

  for (int b_i{0}; b_i < 5; b_i++) {
    for (int c_i{0}; c_i < 5; c_i++) {
      for (int i{0}; i < 14; i++) {
        for (int f_i{0}; f_i < 14; f_i++) {
          for (int e_i{0}; e_i < 384; e_i++) {
            fv83[(((376320 * b_i + 75264 * c_i) + 5376 * i) + 384 * f_i) + e_i] =
              fv82[(((4900 * e_i + 980 * c_i) + 70 * f_i) + 14 * b_i) + i];
          }
        }
      }
    }
  }

  matrixMultiply4454328187142109130(1152, 384, 4900, 128, 128, 128,
    &__constant_384x1152xf32_178[0], &fv83[0], &fv84[0]);
  for (int b_i{0}; b_i < 4900; b_i++) {
    for (int c_i{0}; c_i < 1152; c_i++) {
      i1 = 1152 * b_i + c_i;
      fv84[i1] += __constant_1x1152xf32_32[c_i];
    }
  }

  for (int f_i{0}; f_i < 25; f_i++) {
    for (int e_i{0}; e_i < 4; e_i++) {
      for (int c_i{0}; c_i < 196; c_i++) {
        for (int i{0}; i < 96; i++) {
          i1 = ((225792 * f_i + 1152 * c_i) + 96 * e_i) + i;
          i2 = ((75264 * f_i + 18816 * e_i) + 96 * c_i) + i;
          fv82[i2] = fv84[i1 + 768];
          fv83[i2] = fv84[i1] * 0.31947154F;
        }
      }

      for (int b_i{0}; b_i < 96; b_i++) {
        for (int c_i{0}; c_i < 196; c_i++) {
          fv85[((75264 * f_i + 18816 * e_i) + 196 * b_i) + c_i] = fv84[(((225792
            * f_i + 1152 * c_i) + 96 * e_i) + b_i) + 384] * 0.31947154F;
        }
      }
    }
  }

  for (int b_i{0}; b_i < 100; b_i++) {
    matrixMultiply12417453134711121340(196, 96, 196, 128, 128, 128, &fv85[b_i *
      18816], &fv83[b_i * 18816], &fv88[0]);
    std::copy(&fv88[0], &fv88[38416], &fv86[b_i * 38416]);
  }

  for (int i{0}; i < 25; i++) {
    for (int f_i{0}; f_i < 4; f_i++) {
      for (int e_i{0}; e_i < 196; e_i++) {
        i3 = (784 * i + 196 * f_i) + e_i;
        f3 = fv87[i3];
        for (int b_i{0}; b_i < 196; b_i++) {
          f = fv86[((153664 * i + 38416 * f_i) + 196 * e_i) + b_i];
          if (!(f3 != f3) && ((f != f) || (f > f3))) {
            f3 = f;
          }
        }

        fv87[i3] = f3;
        f = fv89[i3];
        b = bv4[i3];
        for (int c_i{0}; c_i < 196; c_i++) {
          i1 = ((153664 * i + 38416 * f_i) + 196 * e_i) + c_i;
          f1 = fv86[i1];
          f2 = std::exp(f1 - f3);
          fv90[i1] = f2;
          f += f2;
          b = (!(f1 == rtMinusInfF) || b);
        }

        bv4[i3] = b;
        fv89[i3] = f;
        for (int c_i{0}; c_i < 196; c_i++) {
          if (b) {
            i1 = ((153664 * i + 38416 * f_i) + 196 * e_i) + c_i;
            fv90[i1] *= 1.0F / fv89[i3];
          } else {
            fv90[((153664 * i + 38416 * f_i) + 196 * e_i) + c_i] = 0.0F;
          }
        }
      }
    }
  }

  for (int b_i{0}; b_i < 100; b_i++) {
    matrixMultiply12417453134711121340(96, 196, 196, 128, 128, 128, &fv82[b_i *
      18816], &fv90[b_i * 38416], &fv92[0]);
    std::copy(&fv92[0], &fv92[18816], &fv83[b_i * 18816]);
  }

  for (int b_i{0}; b_i < 25; b_i++) {
    for (int c_i{0}; c_i < 14; c_i++) {
      for (int i{0}; i < 14; i++) {
        for (int f_i{0}; f_i < 4; f_i++) {
          std::copy(&fv83[((b_i * 75264 + c_i * 1344) + i * 96) + f_i * 18816],
                    &fv83[static_cast<int>(static_cast<unsigned int>(((b_i *
            75264 + c_i * 1344) + i * 96) + f_i * 18816) + 96U)], &fv82[((b_i *
                      75264 + c_i * 5376) + i * 384) + f_i * 96]);
        }
      }

      std::copy(&__constant_1x1x384x384xf32_114[0],
                &__constant_1x1x384x384xf32_114[147456], &fv93[b_i * 2064384 +
                c_i * 147456]);
    }
  }

  for (int b_i{0}; b_i < 350; b_i++) {
    matrixMultiply12417453134711121340(384, 384, 14, 128, 128, 128, &fv93[b_i *
      147456], &fv82[b_i * 5376], &fv94[0]);
    std::copy(&fv94[0], &fv94[5376], &fv83[b_i * 5376]);
  }

  for (int b_i{0}; b_i < 25; b_i++) {
    for (int c_i{0}; c_i < 14; c_i++) {
      for (int i{0}; i < 14; i++) {
        for (int f_i{0}; f_i < 384; f_i++) {
          i1 = ((75264 * b_i + 5376 * c_i) + 384 * i) + f_i;
          fv82[i1] = fv83[i1] + __constant_1x1x1x384xf32_33[f_i];
        }
      }
    }
  }

  for (int b_i{0}; b_i < 5; b_i++) {
    for (int c_i{0}; c_i < 14; c_i++) {
      for (int i{0}; i < 5; i++) {
        for (int f_i{0}; f_i < 14; f_i++) {
          std::copy(&fv82[((b_i * 376320 + c_i * 5376) + i * 75264) + f_i * 384],
                    &fv82[static_cast<int>(static_cast<unsigned int>(((b_i *
            376320 + c_i * 5376) + i * 75264) + f_i * 384) + 384U)], &fv83[((b_i
                      * 376320 + c_i * 26880) + i * 5376) + f_i * 384]);
        }
      }
    }
  }

  for (int b_i{0}; b_i < 384; b_i++) {
    for (int c_i{0}; c_i < 64; c_i++) {
      for (int i{0}; i < 64; i++) {
        i1 = ((b_i << 12) + (c_i << 6)) + i;
        fv67[i1] += fv83[(26880 * i + 384 * c_i) + b_i];
      }
    }
  }

  for (int b_i{0}; b_i < 64; b_i++) {
    for (int c_i{0}; c_i < 64; c_i++) {
      for (int i{0}; i < 384; i++) {
        fv70[(24576 * b_i + 384 * c_i) + i] = fv67[((i << 12) + (c_i << 6)) +
          b_i];
      }
    }
  }

  for (int b_i{0}; b_i < 1572864; b_i++) {
    dv10[b_i] = fv70[b_i];
  }

  std::memset(&dv13[0], 0, 4096U * sizeof(double));
  for (int c_i{0}; c_i < 64; c_i++) {
    for (int i{0}; i < 64; i++) {
      i1 = (c_i << 6) + i;
      d = dv13[i1];
      for (int b_i{0}; b_i < 384; b_i++) {
        d += dv10[(24576 * c_i + 384 * i) + b_i];
      }

      dv13[i1] = d;
      d1 = 0.0;
      f = 0.0F;
      for (int b_i{0}; b_i < 384; b_i++) {
        i1 = (24576 * c_i + 384 * i) + b_i;
        d2 = dv10[i1] - d * 0.0026041666666666665;
        d1 += d2 * d2;
        f += fv70[i1];
      }

      for (int b_i{0}; b_i < 384; b_i++) {
        fv70[(24576 * c_i + 384 * i) + b_i] = (fv67[((b_i << 12) + (i << 6)) +
          c_i] - f * 0.0026041667F) * (1.0F / std::sqrt(static_cast<float>(d1 *
          0.0026041666666666665) + 1.0E-6F)) * __constant_1x384x1x1xf32_147[b_i]
          + __constant_1x384x1x1xf32_148[b_i];
      }
    }
  }

  matrixMultiply4454328187142109130(1536, 384, 4096, 128, 128, 128,
    &__constant_384x1536xf32_179[0], &fv70[0], &fv78[0]);
  for (int b_i{0}; b_i < 4096; b_i++) {
    for (int c_i{0}; c_i < 1536; c_i++) {
      i1 = 1536 * b_i + c_i;
      fv78[i1] += __constant_1x1536xf32_34[c_i];
    }
  }

  for (int b_i{0}; b_i < 6291456; b_i++) {
    f4 = fv78[b_i];
    f = f4 * 0.70710677F;
    b = (f < 0.0F);
    if (b) {
      f = -f;
    }

    b1 = (f < 0.8F);
    b2 = (f < 2.0F);
    if ((f != f) || (f < 3.75F)) {
      if (b2) {
        if (b1) {
          f1 = 0.02581468F;
          f2 = 0.20974171F;
          f3 = -0.52301854F;
          f5 = 1.1283791F;
        } else {
          f1 = 0.037064552F;
          f2 = 0.1184074F;
          f3 = -0.36472142F;
          f5 = 1.1275069F;
        }

        f6 = 0.0F;
        if (b1) {
          f7 = 0.073979646F;
          f8 = -0.13180897F;
          f9 = 0.5192301F;
          f10 = -0.46351382F;
        } else {
          f7 = 0.05724428F;
          f8 = -0.088346265F;
          f9 = 0.4483691F;
          f10 = -0.327607F;
        }
      } else {
        f1 = -1.7104803E-5F;
        f2 = 0.0002534471F;
        f3 = -0.0014137363F;
        f5 = 0.0035196193F;
        f6 = -0.0033009306F;
        f7 = 0.08219089F;
        f8 = -0.5833899F;
        f9 = 1.6270593F;
        f10 = -2.0606916F;
      }

      f = static_cast<float>(!b2) + (f * (f * (f * (f * f1 + f2) + f3) + f5) +
        f6) / (f * (f * (f * (f * f7 + f8) + f9) + f10) + 1.0F);
    } else {
      f = 1.0F;
    }

    if (b) {
      f = -f;
    }

    fv6[b_i] = f4 * ((f + 1.0F) * 0.5F);
  }

  matrixMultiply12417453134711121340(384, 1536, 4096, 128, 128, 128,
    &__constant_1536x384xf32_180[0], &fv6[0], &fv79[0]);
  for (int b_i{0}; b_i < 4096; b_i++) {
    for (int c_i{0}; c_i < 384; c_i++) {
      i1 = 384 * b_i + c_i;
      fv79[i1] += __constant_1x384xf32_35[c_i];
    }
  }

  for (int b_i{0}; b_i < 384; b_i++) {
    for (int c_i{0}; c_i < 64; c_i++) {
      for (int i{0}; i < 64; i++) {
        i1 = ((b_i << 12) + (c_i << 6)) + i;
        fv67[i1] += fv79[(24576 * i + 384 * c_i) + b_i];
      }
    }
  }

  for (int b_i{0}; b_i < 64; b_i++) {
    for (int c_i{0}; c_i < 64; c_i++) {
      for (int i{0}; i < 384; i++) {
        fv70[(24576 * b_i + 384 * c_i) + i] = fv67[((i << 12) + (c_i << 6)) +
          b_i];
      }
    }
  }

  for (int b_i{0}; b_i < 1572864; b_i++) {
    dv10[b_i] = fv70[b_i];
  }

  std::memset(&dv13[0], 0, 4096U * sizeof(double));
  for (int c_i{0}; c_i < 64; c_i++) {
    for (int i{0}; i < 64; i++) {
      i1 = (c_i << 6) + i;
      d = dv13[i1];
      for (int b_i{0}; b_i < 384; b_i++) {
        d += dv10[(24576 * c_i + 384 * i) + b_i];
      }

      dv13[i1] = d;
      d1 = 0.0;
      f = 0.0F;
      for (int b_i{0}; b_i < 384; b_i++) {
        i1 = (24576 * c_i + 384 * i) + b_i;
        d2 = dv10[i1] - d * 0.0026041666666666665;
        d1 += d2 * d2;
        f += fv70[i1];
      }

      for (int b_i{0}; b_i < 384; b_i++) {
        fv70[(24576 * c_i + 384 * i) + b_i] = (fv67[((b_i << 12) + (i << 6)) +
          c_i] - f * 0.0026041667F) * (1.0F / std::sqrt(static_cast<float>(d1 *
          0.0026041666666666665) + 1.0E-6F)) * __constant_1x384x1x1xf32_149[b_i]
          + __constant_1x384x1x1xf32_150[b_i];
      }
    }
  }

  matrixMultiply4454328187142109130(1152, 384, 4096, 128, 128, 128,
    &__constant_384x1152xf32_181[0], &fv70[0], &fv95[0]);
  for (int b_i{0}; b_i < 4096; b_i++) {
    for (int c_i{0}; c_i < 1152; c_i++) {
      i1 = 1152 * b_i + c_i;
      fv95[i1] += __constant_1x1152xf32_36[c_i];
    }
  }

  for (int i{0}; i < 4; i++) {
    for (int b_i{0}; b_i < 4096; b_i++) {
      for (int c_i{0}; c_i < 96; c_i++) {
        i1 = (1152 * b_i + 96 * i) + c_i;
        i3 = (393216 * i + 96 * b_i) + c_i;
        fv69[i3] = fv95[i1 + 768];
        fv70[i3] = fv95[i1] * 0.31947154F;
      }
    }

    for (int b_i{0}; b_i < 96; b_i++) {
      for (int c_i{0}; c_i < 4096; c_i++) {
        fv80[(393216 * i + (b_i << 12)) + c_i] = fv95[((1152 * c_i + 96 * i) +
          b_i) + 384] * 0.31947154F;
      }
    }
  }

  for (int b_i{0}; b_i < 4; b_i++) {
    matrixMultiply4454328187142109130(4096, 96, 4096, 128, 128, 128, &fv80[b_i *
      393216], &fv70[b_i * 393216], &fv97[0]);
    std::copy(&fv97[0], &fv97[16777216], &fv96[b_i * 16777216]);
  }

  for (int c_i{0}; c_i < 4; c_i++) {
    for (int i{0}; i < 4096; i++) {
      i2 = (c_i << 12) + i;
      f3 = fv58[i2];
      for (int b_i{0}; b_i < 4096; b_i++) {
        f = fv96[((c_i << 24) + (i << 12)) + b_i];
        if (!(f3 != f3) && ((f != f) || (f > f3))) {
          f3 = f;
        }
      }

      fv58[i2] = f3;
      f = fv59[i2];
      b = bv3[i2];
      for (int b_i{0}; b_i < 4096; b_i++) {
        i1 = ((c_i << 24) + (i << 12)) + b_i;
        f1 = fv96[i1];
        f2 = std::exp(f1 - f3);
        fv99[i1] = f2;
        f += f2;
        b = (!(f1 == rtMinusInfF) || b);
      }

      bv3[i2] = b;
      fv59[i2] = f;
      for (int b_i{0}; b_i < 4096; b_i++) {
        if (b) {
          i1 = ((c_i << 24) + (i << 12)) + b_i;
          fv99[i1] *= 1.0F / fv59[i2];
        } else {
          fv99[((c_i << 24) + (i << 12)) + b_i] = 0.0F;
        }
      }
    }
  }

  for (int b_i{0}; b_i < 4; b_i++) {
    matrixMultiply12417453134711121340(96, 4096, 4096, 128, 128, 128, &fv69[b_i *
      393216], &fv99[b_i << 24], &fv100[0]);
    std::copy(&fv100[0], &fv100[393216], &fv70[b_i * 393216]);
  }

  for (int b_i{0}; b_i < 4096; b_i++) {
    for (int c_i{0}; c_i < 4; c_i++) {
      std::copy(&fv70[b_i * 96 + c_i * 393216], &fv70[static_cast<int>(
                 static_cast<unsigned int>(b_i * 96 + c_i * 393216) + 96U)],
                &fv69[b_i * 384 + c_i * 96]);
    }
  }

  matrixMultiply12417453134711121340(384, 384, 4096, 128, 128, 128,
    &__constant_384x384xf32_182[0], &fv69[0], &fv79[0]);
  for (int b_i{0}; b_i < 4096; b_i++) {
    for (int c_i{0}; c_i < 384; c_i++) {
      i1 = 384 * b_i + c_i;
      fv79[i1] += __constant_1x384xf32_37[c_i];
    }
  }

  for (int b_i{0}; b_i < 384; b_i++) {
    for (int c_i{0}; c_i < 64; c_i++) {
      for (int i{0}; i < 64; i++) {
        i1 = ((b_i << 12) + (c_i << 6)) + i;
        fv67[i1] += fv79[(24576 * i + 384 * c_i) + b_i];
      }
    }
  }

  for (int b_i{0}; b_i < 64; b_i++) {
    for (int c_i{0}; c_i < 64; c_i++) {
      for (int i{0}; i < 384; i++) {
        fv70[(24576 * b_i + 384 * c_i) + i] = fv67[((i << 12) + (c_i << 6)) +
          b_i];
      }
    }
  }

  for (int b_i{0}; b_i < 1572864; b_i++) {
    dv10[b_i] = fv70[b_i];
  }

  std::memset(&dv13[0], 0, 4096U * sizeof(double));
  for (int c_i{0}; c_i < 64; c_i++) {
    for (int i{0}; i < 64; i++) {
      i1 = (c_i << 6) + i;
      d = dv13[i1];
      for (int b_i{0}; b_i < 384; b_i++) {
        d += dv10[(24576 * c_i + 384 * i) + b_i];
      }

      dv13[i1] = d;
      d1 = 0.0;
      f = 0.0F;
      for (int b_i{0}; b_i < 384; b_i++) {
        i1 = (24576 * c_i + 384 * i) + b_i;
        d2 = dv10[i1] - d * 0.0026041666666666665;
        d1 += d2 * d2;
        f += fv70[i1];
      }

      for (int b_i{0}; b_i < 384; b_i++) {
        fv70[(24576 * c_i + 384 * i) + b_i] = (fv67[((b_i << 12) + (i << 6)) +
          c_i] - f * 0.0026041667F) * (1.0F / std::sqrt(static_cast<float>(d1 *
          0.0026041666666666665) + 1.0E-6F)) * __constant_1x384x1x1xf32_151[b_i]
          + __constant_1x384x1x1xf32_152[b_i];
      }
    }
  }

  matrixMultiply4454328187142109130(1536, 384, 4096, 128, 128, 128,
    &__constant_384x1536xf32_183[0], &fv70[0], &fv78[0]);
  for (int b_i{0}; b_i < 4096; b_i++) {
    for (int c_i{0}; c_i < 1536; c_i++) {
      i1 = 1536 * b_i + c_i;
      fv78[i1] += __constant_1x1536xf32_38[c_i];
    }
  }

  for (int b_i{0}; b_i < 6291456; b_i++) {
    f4 = fv78[b_i];
    f = f4 * 0.70710677F;
    b = (f < 0.0F);
    if (b) {
      f = -f;
    }

    b1 = (f < 0.8F);
    b2 = (f < 2.0F);
    if ((f != f) || (f < 3.75F)) {
      if (b2) {
        if (b1) {
          f1 = 0.02581468F;
          f2 = 0.20974171F;
          f3 = -0.52301854F;
          f5 = 1.1283791F;
        } else {
          f1 = 0.037064552F;
          f2 = 0.1184074F;
          f3 = -0.36472142F;
          f5 = 1.1275069F;
        }

        f6 = 0.0F;
        if (b1) {
          f7 = 0.073979646F;
          f8 = -0.13180897F;
          f9 = 0.5192301F;
          f10 = -0.46351382F;
        } else {
          f7 = 0.05724428F;
          f8 = -0.088346265F;
          f9 = 0.4483691F;
          f10 = -0.327607F;
        }
      } else {
        f1 = -1.7104803E-5F;
        f2 = 0.0002534471F;
        f3 = -0.0014137363F;
        f5 = 0.0035196193F;
        f6 = -0.0033009306F;
        f7 = 0.08219089F;
        f8 = -0.5833899F;
        f9 = 1.6270593F;
        f10 = -2.0606916F;
      }

      f = static_cast<float>(!b2) + (f * (f * (f * (f * f1 + f2) + f3) + f5) +
        f6) / (f * (f * (f * (f * f7 + f8) + f9) + f10) + 1.0F);
    } else {
      f = 1.0F;
    }

    if (b) {
      f = -f;
    }

    fv6[b_i] = f4 * ((f + 1.0F) * 0.5F);
  }

  matrixMultiply12417453134711121340(384, 1536, 4096, 128, 128, 128,
    &__constant_1536x384xf32_184[0], &fv6[0], &fv79[0]);
  for (int b_i{0}; b_i < 4096; b_i++) {
    for (int c_i{0}; c_i < 384; c_i++) {
      i1 = 384 * b_i + c_i;
      fv79[i1] += __constant_1x384xf32_39[c_i];
    }
  }

  for (int b_i{0}; b_i < 384; b_i++) {
    for (int c_i{0}; c_i < 64; c_i++) {
      for (int i{0}; i < 64; i++) {
        i1 = ((b_i << 12) + (c_i << 6)) + i;
        fv67[i1] += fv79[(24576 * i + 384 * c_i) + b_i];
      }
    }
  }

  for (int b_i{0}; b_i < 64; b_i++) {
    for (int c_i{0}; c_i < 64; c_i++) {
      for (int i{0}; i < 384; i++) {
        fv70[(24576 * b_i + 384 * c_i) + i] = fv67[((i << 12) + (c_i << 6)) +
          b_i];
      }
    }
  }

  for (int b_i{0}; b_i < 1572864; b_i++) {
    dv10[b_i] = fv70[b_i];
  }

  for (int c_i{0}; c_i < 64; c_i++) {
    for (int i{0}; i < 64; i++) {
      i2 = (c_i << 6) + i;
      d = dv12[i2];
      for (int b_i{0}; b_i < 384; b_i++) {
        d += dv10[(24576 * c_i + 384 * i) + b_i];
      }

      dv12[i2] = d;
      d1 = dv11[i2];
      f = fv35[i2];
      for (int b_i{0}; b_i < 384; b_i++) {
        i1 = (24576 * c_i + 384 * i) + b_i;
        d2 = dv10[i1] - d * 0.0026041666666666665;
        d1 += d2 * d2;
        f += fv70[i1];
      }

      fv35[i2] = f;
      dv11[i2] = d1;
    }
  }

  for (int b_i{0}; b_i < 384; b_i++) {
    f = __constant_1x384x1x1xf32_153[b_i];
    f1 = __constant_1x384x1x1xf32_154[b_i];
    for (int c_i{0}; c_i < 64; c_i++) {
      for (int i{0}; i < 64; i++) {
        i1 = (i << 6) + c_i;
        fv81[(4900 * b_i + 70 * c_i) + i] = (fv67[((b_i << 12) + (c_i << 6)) + i]
          - fv35[i1] * 0.0026041667F) * (1.0F / std::sqrt(static_cast<float>
          (dv11[i1] * 0.0026041666666666665) + 1.0E-6F)) * f + f1;
      }
    }
  }

  for (int b_i{0}; b_i < 64; b_i++) {
    for (int c_i{0}; c_i < 64; c_i++) {
      for (int i{0}; i < 384; i++) {
        fv70[(24576 * b_i + 384 * c_i) + i] = fv81[(4900 * i + 70 * c_i) + b_i];
      }
    }
  }

  matrixMultiply4454328187142109130(768, 384, 4096, 128, 128, 128,
    &__constant_384x768xf32[0], &fv70[0], &fv103[0]);
  for (int b_i{0}; b_i < 4096; b_i++) {
    for (int c_i{0}; c_i < 768; c_i++) {
      i1 = 768 * b_i + c_i;
      fv103[i1] += __constant_1x768xf32_40[c_i];
    }
  }

  for (int b_i{0}; b_i < 768; b_i++) {
    for (int c_i{0}; c_i < 64; c_i++) {
      for (int i{0}; i < 64; i++) {
        fv4[((b_i << 12) + (c_i << 6)) + i] = fv103[(49152 * i + 768 * c_i) +
          b_i];
      }
    }
  }

  maxPooling13753016621916862475(&fv4[0], &fv104[0]);
  for (int b_i{0}; b_i < 5; b_i++) {
    for (int c_i{0}; c_i < 5; c_i++) {
      for (int i{0}; i < 14; i++) {
        for (int f_i{0}; f_i < 14; f_i++) {
          for (int e_i{0}; e_i < 384; e_i++) {
            fv83[(((376320 * b_i + 75264 * c_i) + 5376 * i) + 384 * f_i) + e_i] =
              fv81[(((4900 * e_i + 980 * c_i) + 70 * f_i) + 14 * b_i) + i];
          }
        }
      }
    }
  }

  matrixMultiply4454328187142109130(2304, 384, 4900, 128, 128, 128,
    &__constant_384x2304xf32[0], &fv83[0], &fv105[0]);
  for (int b_i{0}; b_i < 4900; b_i++) {
    for (int c_i{0}; c_i < 2304; c_i++) {
      i1 = 2304 * b_i + c_i;
      fv105[i1] += __constant_1x2304xf32[c_i];
    }
  }

  for (int b_i{0}; b_i < 25; b_i++) {
    for (int c_i{0}; c_i < 768; c_i++) {
      for (int i{0}; i < 14; i++) {
        for (int f_i{0}; f_i < 14; f_i++) {
          fv106[((150528 * b_i + 196 * c_i) + 14 * i) + f_i] = fv105[((451584 *
            b_i + 32256 * f_i) + 2304 * i) + c_i];
        }
      }
    }
  }

  maxPooling18144858745303349977(&fv106[0], &fv107[0]);
  for (int e_i{0}; e_i < 25; e_i++) {
    for (int i8{0}; i8 < 8; i8++) {
      for (int b_i{0}; b_i < 196; b_i++) {
        std::copy(&fv105[((e_i * 451584 + i8 * 96) + b_i * 2304) + 1536],
                  &fv105[((e_i * 451584 + i8 * 96) + b_i * 2304) + 1632],
                  &fv106[(e_i * 150528 + i8 * 18816) + b_i * 96]);
      }

      i1 = 37632 * e_i + 4704 * i8;
      for (int c_i{0}; c_i < 7; c_i++) {
        for (int i{0}; i < 7; i++) {
          for (int f_i{0}; f_i < 96; f_i++) {
            fv108[((i1 + 672 * c_i) + 96 * i) + f_i] = fv107[((i1 + 49 * f_i) +
              7 * i) + c_i] * 0.31947154F;
          }
        }
      }

      for (int b_i{0}; b_i < 96; b_i++) {
        for (int c_i{0}; c_i < 196; c_i++) {
          fv109[((150528 * e_i + 18816 * i8) + 196 * b_i) + c_i] = fv105
            [(((451584 * e_i + 2304 * c_i) + 96 * i8) + b_i) + 768] *
            0.31947154F;
        }
      }
    }
  }

  for (int b_i{0}; b_i < 200; b_i++) {
    matrixMultiply12417453134711121340(196, 96, 49, 128, 128, 128, &fv109[b_i *
      18816], &fv108[b_i * 4704], &fv112[0]);
    std::copy(&fv112[0], &fv112[9604], &fv110[b_i * 9604]);
  }

  for (int b_i{0}; b_i < 9800; b_i++) {
    fv111[b_i] = -3.402823466E+38F;
    fv113[b_i] = -3.402823466E+38F;
  }

  for (int c_i{0}; c_i < 25; c_i++) {
    for (int i{0}; i < 8; i++) {
      for (int f_i{0}; f_i < 49; f_i++) {
        i1 = (392 * c_i + 49 * i) + f_i;
        f = fv113[i1];
        for (int b_i{0}; b_i < 196; b_i++) {
          f1 = fv110[((76832 * c_i + 9604 * i) + 196 * f_i) + b_i];
          if (!(f != f) && ((f1 != f1) || (f1 > f))) {
            f = f1;
          }
        }

        fv113[i1] = f;
        for (int b_i{0}; b_i < 196; b_i++) {
          i1 = ((76832 * c_i + 9604 * i) + 196 * f_i) + b_i;
          fv114[i1] = std::exp(fv110[i1] - f);
        }
      }
    }
  }

  std::memset(&fv113[0], 0, 9800U * sizeof(float));
  std::memset(&fv115[0], 0, 9800U * sizeof(float));
  for (int b_i{0}; b_i < 25; b_i++) {
    for (int c_i{0}; c_i < 8; c_i++) {
      for (int i{0}; i < 49; i++) {
        i1 = (392 * b_i + 49 * c_i) + i;
        f = fv115[i1];
        for (int f_i{0}; f_i < 196; f_i++) {
          f += fv114[((76832 * b_i + 9604 * c_i) + 196 * i) + f_i];
        }

        fv115[i1] = f;
      }
    }
  }

  std::memset(&bv7[0], 0, 9800U * sizeof(boolean_T));
  std::memset(&bv8[0], 0, 9800U * sizeof(boolean_T));
  for (int i{0}; i < 25; i++) {
    for (int f_i{0}; f_i < 8; f_i++) {
      for (int e_i{0}; e_i < 49; e_i++) {
        i2 = (392 * i + 49 * f_i) + e_i;
        b = bv8[i2];
        for (int b_i{0}; b_i < 196; b_i++) {
          b = (!(fv110[((76832 * i + 9604 * f_i) + 196 * e_i) + b_i] ==
                 rtMinusInfF) || b);
        }

        bv8[i2] = b;
        for (int c_i{0}; c_i < 196; c_i++) {
          if (b) {
            i1 = ((76832 * i + 9604 * f_i) + 196 * e_i) + c_i;
            fv114[i1] *= 1.0F / fv115[i2];
          } else {
            fv114[((76832 * i + 9604 * f_i) + 196 * e_i) + c_i] = 0.0F;
          }
        }
      }
    }
  }

  for (int b_i{0}; b_i < 200; b_i++) {
    matrixMultiply12417453134711121340(96, 196, 49, 128, 128, 128, &fv106[b_i *
      18816], &fv114[b_i * 9604], &fv116[0]);
    std::copy(&fv116[0], &fv116[4704], &fv107[b_i * 4704]);
  }

  for (int b_i{0}; b_i < 25; b_i++) {
    for (int c_i{0}; c_i < 7; c_i++) {
      for (int i{0}; i < 7; i++) {
        for (int f_i{0}; f_i < 8; f_i++) {
          std::copy(&fv107[((b_i * 37632 + c_i * 672) + i * 96) + f_i * 4704],
                    &fv107[static_cast<int>(static_cast<unsigned int>(((b_i *
            37632 + c_i * 672) + i * 96) + f_i * 4704) + 96U)], &fv108[((b_i *
                      37632 + c_i * 5376) + i * 768) + f_i * 96]);
        }
      }

      std::copy(&__constant_1x1x768x768xf32[0], &__constant_1x1x768x768xf32
                [589824], &fv117[b_i * 4128768 + c_i * 589824]);
    }
  }

  for (int b_i{0}; b_i < 175; b_i++) {
    matrixMultiply4454328187142109130(768, 768, 7, 128, 128, 128, &fv117[b_i *
      589824], &fv108[b_i * 5376], &fv118[0]);
    std::copy(&fv118[0], &fv118[5376], &fv107[b_i * 5376]);
  }

  for (int b_i{0}; b_i < 25; b_i++) {
    for (int c_i{0}; c_i < 7; c_i++) {
      for (int i{0}; i < 7; i++) {
        for (int f_i{0}; f_i < 768; f_i++) {
          i1 = ((37632 * b_i + 5376 * c_i) + 768 * i) + f_i;
          fv108[i1] = fv107[i1] + __constant_1x1x1x768xf32[f_i];
        }
      }
    }
  }

  for (int b_i{0}; b_i < 5; b_i++) {
    for (int c_i{0}; c_i < 7; c_i++) {
      for (int i{0}; i < 5; i++) {
        for (int f_i{0}; f_i < 7; f_i++) {
          std::copy(&fv108[((b_i * 188160 + c_i * 5376) + i * 37632) + f_i * 768],
                    &fv108[static_cast<int>(static_cast<unsigned int>(((b_i *
            188160 + c_i * 5376) + i * 37632) + f_i * 768) + 768U)], &fv107
                    [((b_i * 188160 + c_i * 26880) + i * 5376) + f_i * 768]);
        }
      }
    }
  }

  for (int b_i{0}; b_i < 768; b_i++) {
    for (int c_i{0}; c_i < 32; c_i++) {
      for (int i{0}; i < 32; i++) {
        i1 = ((b_i << 10) + (c_i << 5)) + i;
        fv104[i1] += fv107[(26880 * i + 768 * c_i) + b_i];
      }
    }
  }

  for (int b_i{0}; b_i < 32; b_i++) {
    for (int c_i{0}; c_i < 32; c_i++) {
      for (int i{0}; i < 768; i++) {
        fv119[(24576 * b_i + 768 * c_i) + i] = fv104[((i << 10) + (c_i << 5)) +
          b_i];
      }
    }
  }

  for (int b_i{0}; b_i < 786432; b_i++) {
    dv15[b_i] = fv119[b_i];
  }

  std::memset(&dv16[0], 0, 1024U * sizeof(double));
  std::memset(&dv17[0], 0, 1024U * sizeof(double));
  std::memset(&dv18[0], 0, 1024U * sizeof(double));
  for (int c_i{0}; c_i < 32; c_i++) {
    for (int i{0}; i < 32; i++) {
      i1 = (c_i << 5) + i;
      d = dv18[i1];
      for (int b_i{0}; b_i < 768; b_i++) {
        d += dv15[(24576 * c_i + 768 * i) + b_i];
      }

      dv18[i1] = d;
      d1 = 0.0;
      for (int b_i{0}; b_i < 768; b_i++) {
        d2 = dv15[(24576 * c_i + 768 * i) + b_i] - d * 0.0013020833333333333;
        d1 += d2 * d2;
      }

      dv19[i1] = d1;
    }
  }

  std::memset(&fv50[0], 0, 1024U * sizeof(float));
  std::memset(&fv120[0], 0, 1024U * sizeof(float));
  for (int c_i{0}; c_i < 32; c_i++) {
    for (int i{0}; i < 32; i++) {
      i1 = (c_i << 5) + i;
      f = fv120[i1];
      for (int b_i{0}; b_i < 768; b_i++) {
        f += fv119[(24576 * c_i + 768 * i) + b_i];
      }

      fv120[i1] = f;
      d = dv19[i1];
      for (int b_i{0}; b_i < 768; b_i++) {
        fv119[(24576 * c_i + 768 * i) + b_i] = (fv104[((b_i << 10) + (i << 5)) +
          c_i] - f * 0.0013020834F) * (1.0F / std::sqrt(static_cast<float>(d *
          0.0013020833333333333) + 1.0E-6F)) * __constant_1x768x1x1xf32[b_i] +
          __constant_1x768x1x1xf32_155[b_i];
      }
    }
  }

  matrixMultiply4454328187142109130(3072, 768, 1024, 128, 128, 128,
    &__constant_768x3072xf32[0], &fv119[0], &fv121[0]);
  for (int b_i{0}; b_i < 1024; b_i++) {
    for (int c_i{0}; c_i < 3072; c_i++) {
      i1 = 3072 * b_i + c_i;
      fv121[i1] += __constant_1x3072xf32[c_i];
    }
  }

  for (int b_i{0}; b_i < 3145728; b_i++) {
    f4 = fv121[b_i];
    f = f4 * 0.70710677F;
    b = (f < 0.0F);
    if (b) {
      f = -f;
    }

    b1 = (f < 0.8F);
    b2 = (f < 2.0F);
    if ((f != f) || (f < 3.75F)) {
      if (b2) {
        if (b1) {
          f1 = 0.02581468F;
          f2 = 0.20974171F;
          f3 = -0.52301854F;
          f5 = 1.1283791F;
        } else {
          f1 = 0.037064552F;
          f2 = 0.1184074F;
          f3 = -0.36472142F;
          f5 = 1.1275069F;
        }

        f6 = 0.0F;
        if (b1) {
          f7 = 0.073979646F;
          f8 = -0.13180897F;
          f9 = 0.5192301F;
          f10 = -0.46351382F;
        } else {
          f7 = 0.05724428F;
          f8 = -0.088346265F;
          f9 = 0.4483691F;
          f10 = -0.327607F;
        }
      } else {
        f1 = -1.7104803E-5F;
        f2 = 0.0002534471F;
        f3 = -0.0014137363F;
        f5 = 0.0035196193F;
        f6 = -0.0033009306F;
        f7 = 0.08219089F;
        f8 = -0.5833899F;
        f9 = 1.6270593F;
        f10 = -2.0606916F;
      }

      f = static_cast<float>(!b2) + (f * (f * (f * (f * f1 + f2) + f3) + f5) +
        f6) / (f * (f * (f * (f * f7 + f8) + f9) + f10) + 1.0F);
    } else {
      f = 1.0F;
    }

    if (b) {
      f = -f;
    }

    fv4[b_i] = f4 * ((f + 1.0F) * 0.5F);
  }

  matrixMultiply4454328187142109130(768, 3072, 1024, 128, 128, 128,
    &__constant_3072x768xf32[0], &fv4[0], &fv122[0]);
  for (int b_i{0}; b_i < 1024; b_i++) {
    for (int c_i{0}; c_i < 768; c_i++) {
      i1 = 768 * b_i + c_i;
      fv122[i1] += __constant_1x768xf32_41[c_i];
    }
  }

  for (int b_i{0}; b_i < 768; b_i++) {
    for (int c_i{0}; c_i < 32; c_i++) {
      for (int i{0}; i < 32; i++) {
        i1 = ((b_i << 10) + (c_i << 5)) + i;
        fv123[i1] = fv104[i1] + fv122[(24576 * i + 768 * c_i) + b_i];
      }
    }
  }

  for (int b_i{0}; b_i < 32; b_i++) {
    for (int c_i{0}; c_i < 32; c_i++) {
      for (int i{0}; i < 768; i++) {
        fv119[(24576 * b_i + 768 * c_i) + i] = fv123[((i << 10) + (c_i << 5)) +
          b_i];
      }
    }
  }

  for (int b_i{0}; b_i < 786432; b_i++) {
    dv15[b_i] = fv119[b_i];
  }

  std::memset(&dv18[0], 0, 1024U * sizeof(double));
  for (int c_i{0}; c_i < 32; c_i++) {
    for (int i{0}; i < 32; i++) {
      i2 = (c_i << 5) + i;
      d = dv18[i2];
      for (int b_i{0}; b_i < 768; b_i++) {
        d += dv15[(24576 * c_i + 768 * i) + b_i];
      }

      dv18[i2] = d;
      d1 = 0.0;
      f = 0.0F;
      for (int b_i{0}; b_i < 768; b_i++) {
        i1 = (24576 * c_i + 768 * i) + b_i;
        d2 = dv15[i1] - d * 0.0013020833333333333;
        d1 += d2 * d2;
        f += fv119[i1];
      }

      dv19[i2] = d1;
      fv124[i2] = f;
    }
  }

  for (int b_i{0}; b_i < 768; b_i++) {
    f = __constant_1x768x1x1xf32_156[b_i];
    f1 = __constant_1x768x1x1xf32_157[b_i];
    for (int c_i{0}; c_i < 32; c_i++) {
      for (int i{0}; i < 32; i++) {
        i1 = (i << 5) + c_i;
        i3 = ((b_i << 10) + (c_i << 5)) + i;
        fv104[i3] = (fv123[i3] - fv124[i1] * 0.0013020834F) * (1.0F / std::sqrt(
          static_cast<float>(dv19[i1] * 0.0013020833333333333) + 1.0E-6F)) * f +
          f1;
      }
    }
  }

  std::memset(&fv107[0], 0, 940800U * sizeof(float));
  for (int b_i{0}; b_i < 768; b_i++) {
    for (int c_i{0}; c_i < 32; c_i++) {
      std::copy(&fv104[b_i * 1024 + c_i * 32], &fv104[static_cast<int>(
                 static_cast<unsigned int>(b_i * 1024 + c_i * 32) + 32U)],
                &fv107[b_i * 1225 + c_i * 35]);
    }
  }

  for (int b_i{0}; b_i < 5; b_i++) {
    for (int c_i{0}; c_i < 5; c_i++) {
      for (int i{0}; i < 7; i++) {
        for (int f_i{0}; f_i < 7; f_i++) {
          for (int e_i{0}; e_i < 768; e_i++) {
            fv108[(((188160 * b_i + 37632 * c_i) + 5376 * i) + 768 * f_i) + e_i]
              = fv107[(((1225 * e_i + 245 * c_i) + 35 * f_i) + 7 * b_i) + i];
          }
        }
      }
    }
  }

  matrixMultiply4454328187142109130(2304, 768, 1225, 128, 128, 128,
    &__constant_768x2304xf32[0], &fv108[0], &fv125[0]);
  for (int b_i{0}; b_i < 1225; b_i++) {
    for (int c_i{0}; c_i < 2304; c_i++) {
      i1 = 2304 * b_i + c_i;
      fv125[i1] += __constant_1x2304xf32_42[c_i];
    }
  }

  for (int f_i{0}; f_i < 25; f_i++) {
    for (int e_i{0}; e_i < 8; e_i++) {
      for (int c_i{0}; c_i < 49; c_i++) {
        for (int i{0}; i < 96; i++) {
          i1 = ((112896 * f_i + 2304 * c_i) + 96 * e_i) + i;
          i2 = ((37632 * f_i + 4704 * e_i) + 96 * c_i) + i;
          fv108[i2] = fv125[i1 + 1536];
          fv107[i2] = fv125[i1] * 0.31947154F;
        }
      }

      for (int b_i{0}; b_i < 96; b_i++) {
        for (int c_i{0}; c_i < 49; c_i++) {
          fv126[((37632 * f_i + 4704 * e_i) + 49 * b_i) + c_i] = fv125[(((112896
            * f_i + 2304 * c_i) + 96 * e_i) + b_i) + 768] * 0.31947154F;
        }
      }
    }
  }

  for (int b_i{0}; b_i < 200; b_i++) {
    matrixMultiply12417453134711121340(49, 96, 49, 128, 128, 128, &fv126[b_i *
      4704], &fv107[b_i * 4704], &fv129[0]);
    std::copy(&fv129[0], &fv129[2401], &fv127[b_i * 2401]);
  }

  for (int i{0}; i < 25; i++) {
    for (int f_i{0}; f_i < 8; f_i++) {
      for (int e_i{0}; e_i < 49; e_i++) {
        i3 = (392 * i + 49 * f_i) + e_i;
        f3 = fv111[i3];
        for (int b_i{0}; b_i < 49; b_i++) {
          f = fv127[((19208 * i + 2401 * f_i) + 49 * e_i) + b_i];
          if (!(f3 != f3) && ((f != f) || (f > f3))) {
            f3 = f;
          }
        }

        fv111[i3] = f3;
        f = fv113[i3];
        b = bv7[i3];
        for (int c_i{0}; c_i < 49; c_i++) {
          i1 = ((19208 * i + 2401 * f_i) + 49 * e_i) + c_i;
          f1 = fv127[i1];
          f2 = std::exp(f1 - f3);
          fv128[i1] = f2;
          f += f2;
          b = (!(f1 == rtMinusInfF) || b);
        }

        bv7[i3] = b;
        fv113[i3] = f;
        for (int c_i{0}; c_i < 49; c_i++) {
          if (b) {
            i1 = ((19208 * i + 2401 * f_i) + 49 * e_i) + c_i;
            fv128[i1] *= 1.0F / fv113[i3];
          } else {
            fv128[((19208 * i + 2401 * f_i) + 49 * e_i) + c_i] = 0.0F;
          }
        }
      }
    }
  }

  for (int b_i{0}; b_i < 200; b_i++) {
    matrixMultiply12417453134711121340(96, 49, 49, 128, 128, 128, &fv108[b_i *
      4704], &fv128[b_i * 2401], &fv116[0]);
    std::copy(&fv116[0], &fv116[4704], &fv107[b_i * 4704]);
  }

  for (int b_i{0}; b_i < 25; b_i++) {
    for (int c_i{0}; c_i < 7; c_i++) {
      for (int i{0}; i < 7; i++) {
        for (int f_i{0}; f_i < 8; f_i++) {
          std::copy(&fv107[((b_i * 37632 + c_i * 672) + i * 96) + f_i * 4704],
                    &fv107[static_cast<int>(static_cast<unsigned int>(((b_i *
            37632 + c_i * 672) + i * 96) + f_i * 4704) + 96U)], &fv108[((b_i *
                      37632 + c_i * 5376) + i * 768) + f_i * 96]);
        }
      }

      std::copy(&__constant_1x1x768x768xf32_115[0],
                &__constant_1x1x768x768xf32_115[589824], &fv117[b_i * 4128768 +
                c_i * 589824]);
    }
  }

  for (int b_i{0}; b_i < 175; b_i++) {
    matrixMultiply4454328187142109130(768, 768, 7, 128, 128, 128, &fv117[b_i *
      589824], &fv108[b_i * 5376], &fv118[0]);
    std::copy(&fv118[0], &fv118[5376], &fv107[b_i * 5376]);
  }

  for (int b_i{0}; b_i < 25; b_i++) {
    for (int c_i{0}; c_i < 7; c_i++) {
      for (int i{0}; i < 7; i++) {
        for (int f_i{0}; f_i < 768; f_i++) {
          i1 = ((37632 * b_i + 5376 * c_i) + 768 * i) + f_i;
          fv108[i1] = fv107[i1] + __constant_1x1x1x768xf32_43[f_i];
        }
      }
    }
  }

  for (int b_i{0}; b_i < 5; b_i++) {
    for (int c_i{0}; c_i < 7; c_i++) {
      for (int i{0}; i < 5; i++) {
        for (int f_i{0}; f_i < 7; f_i++) {
          std::copy(&fv108[((b_i * 188160 + c_i * 5376) + i * 37632) + f_i * 768],
                    &fv108[static_cast<int>(static_cast<unsigned int>(((b_i *
            188160 + c_i * 5376) + i * 37632) + f_i * 768) + 768U)], &fv107
                    [((b_i * 188160 + c_i * 26880) + i * 5376) + f_i * 768]);
        }
      }
    }
  }

  for (int b_i{0}; b_i < 768; b_i++) {
    for (int c_i{0}; c_i < 32; c_i++) {
      for (int i{0}; i < 32; i++) {
        i1 = ((b_i << 10) + (c_i << 5)) + i;
        fv104[i1] = fv123[i1] + fv107[(26880 * i + 768 * c_i) + b_i];
      }
    }
  }

  for (int b_i{0}; b_i < 32; b_i++) {
    for (int c_i{0}; c_i < 32; c_i++) {
      for (int i{0}; i < 768; i++) {
        fv119[(24576 * b_i + 768 * c_i) + i] = fv104[((i << 10) + (c_i << 5)) +
          b_i];
      }
    }
  }

  for (int b_i{0}; b_i < 786432; b_i++) {
    dv15[b_i] = fv119[b_i];
  }

  for (int c_i{0}; c_i < 32; c_i++) {
    for (int i{0}; i < 32; i++) {
      i2 = (c_i << 5) + i;
      d = dv17[i2];
      for (int b_i{0}; b_i < 768; b_i++) {
        d += dv15[(24576 * c_i + 768 * i) + b_i];
      }

      dv17[i2] = d;
      d1 = dv16[i2];
      f = fv50[i2];
      for (int b_i{0}; b_i < 768; b_i++) {
        i1 = (24576 * c_i + 768 * i) + b_i;
        d2 = dv15[i1] - d * 0.0013020833333333333;
        d1 += d2 * d2;
        f += fv119[i1];
      }

      fv50[i2] = f;
      dv16[i2] = d1;
      for (int b_i{0}; b_i < 768; b_i++) {
        fv119[(24576 * c_i + 768 * i) + b_i] = (fv104[((b_i << 10) + (i << 5)) +
          c_i] - f * 0.0013020834F) * (1.0F / std::sqrt(static_cast<float>(d1 *
          0.0013020833333333333) + 1.0E-6F)) * __constant_1x768x1x1xf32_158[b_i]
          + __constant_1x768x1x1xf32_159[b_i];
      }
    }
  }

  matrixMultiply4454328187142109130(3072, 768, 1024, 128, 128, 128,
    &__constant_768x3072xf32_185[0], &fv119[0], &fv121[0]);
  for (int b_i{0}; b_i < 1024; b_i++) {
    for (int c_i{0}; c_i < 3072; c_i++) {
      i1 = 3072 * b_i + c_i;
      fv121[i1] += __constant_1x3072xf32_44[c_i];
    }
  }

  for (int b_i{0}; b_i < 3145728; b_i++) {
    f4 = fv121[b_i];
    f = f4 * 0.70710677F;
    b = (f < 0.0F);
    if (b) {
      f = -f;
    }

    b1 = (f < 0.8F);
    b2 = (f < 2.0F);
    if ((f != f) || (f < 3.75F)) {
      if (b2) {
        if (b1) {
          f1 = 0.02581468F;
          f2 = 0.20974171F;
          f3 = -0.52301854F;
          f5 = 1.1283791F;
        } else {
          f1 = 0.037064552F;
          f2 = 0.1184074F;
          f3 = -0.36472142F;
          f5 = 1.1275069F;
        }

        f6 = 0.0F;
        if (b1) {
          f7 = 0.073979646F;
          f8 = -0.13180897F;
          f9 = 0.5192301F;
          f10 = -0.46351382F;
        } else {
          f7 = 0.05724428F;
          f8 = -0.088346265F;
          f9 = 0.4483691F;
          f10 = -0.327607F;
        }
      } else {
        f1 = -1.7104803E-5F;
        f2 = 0.0002534471F;
        f3 = -0.0014137363F;
        f5 = 0.0035196193F;
        f6 = -0.0033009306F;
        f7 = 0.08219089F;
        f8 = -0.5833899F;
        f9 = 1.6270593F;
        f10 = -2.0606916F;
      }

      f = static_cast<float>(!b2) + (f * (f * (f * (f * f1 + f2) + f3) + f5) +
        f6) / (f * (f * (f * (f * f7 + f8) + f9) + f10) + 1.0F);
    } else {
      f = 1.0F;
    }

    if (b) {
      f = -f;
    }

    fv4[b_i] = f4 * ((f + 1.0F) * 0.5F);
  }

  matrixMultiply4454328187142109130(768, 3072, 1024, 128, 128, 128,
    &__constant_3072x768xf32_186[0], &fv4[0], &fv122[0]);
  for (int b_i{0}; b_i < 1024; b_i++) {
    for (int c_i{0}; c_i < 768; c_i++) {
      i1 = 768 * b_i + c_i;
      fv122[i1] += __constant_1x768xf32_45[c_i];
    }
  }

  for (int b_i{0}; b_i < 768; b_i++) {
    for (int c_i{0}; c_i < 32; c_i++) {
      for (int i{0}; i < 32; i++) {
        i1 = ((b_i << 10) + (c_i << 5)) + i;
        fv104[i1] += fv122[(24576 * i + 768 * c_i) + b_i];
      }
    }
  }

  b_convolution(fv104[0], fv130[0], __constant_196608xf32[0],
                __constant_256xf32[0]);
  for (int b_i{0}; b_i < 256; b_i++) {
    i1 = b_i << 10;
    for (int c_i{0}; c_i < 32; c_i++) {
      for (int i{0}; i < 32; i++) {
        fv71[(i1 + (c_i << 5)) + i] = fv130[(i1 + (i << 5)) + c_i];
      }
    }
  }

  c_convolution(fv67[0], fv131[0], __constant_98304xf32[0],
                __constant_256xf32_3[0]);
  for (int b_i{0}; b_i < 256; b_i++) {
    i1 = b_i << 12;
    for (int c_i{0}; c_i < 64; c_i++) {
      d_i = static_cast<long>(std::floor(static_cast<float>(c_i) / 2.0F));
      for (int i{0}; i < 64; i++) {
        fv132[(i1 + (c_i << 6)) + i] = fv131[(i1 + (i << 6)) + c_i] + fv71[((b_i
          << 10) + (static_cast<int>(d_i) << 5)) + static_cast<int>(std::floor(
          static_cast<float>(i) / 2.0F))];
      }
    }
  }

  d_convolution(fv45[0], fv133[0], __constant_49152xf32[0],
                __constant_256xf32_4[0]);
  e_convolution(fv30[0], fv134[0], __constant_24576xf32[0],
                __constant_256xf32_5[0]);
  f_convolution(fv134[0], fv135[0], __constant_8192xf32[0], __constant_32xf32_2
                [0]);
  g_convolution(fv133[0], fv131[0], __constant_16384xf32[0],
                __constant_64xf32_1[0]);
  for (int b_i{0}; b_i < 256; b_i++) {
    f = __constant_1x256x1xf32[b_i];
    for (int c_i{0}; c_i < 4096; c_i++) {
      i1 = (b_i << 12) + c_i;
      fv136[i1] = fv132[i1] + f;
    }
  }

  if (__constant_1x1x2x1xi64[0] == 1L) {
    unnamed_idx_0 = unnamed_idx_1 * 0.00083333335F * 1024.0F;
  }

  fv137[0] = unnamed_idx_0 + 0.5F;
  fv137[2] = __constant_1x1x2xf32[0];
  if (__constant_1x1x2x1xi64[1] == 1L) {
    unnamed_idx_0 = unnamed_idx_1 * 0.00083333335F * 1024.0F;
  } else {
    unnamed_idx_0 = unnamed_idx_1;
  }

  fv137[1] = unnamed_idx_0 + 0.5F;
  fv137[3] = __constant_1x1x2xf32[1];
  fv138[0] = static_cast<float>(in_2);
  fv138[1] = -1.0F;
  f = fv137[0] * 0.0009765625F;
  if (__constant_1x1x2xi64[0] == 0L) {
    fv139[0] = f;
  } else {
    fv139[0] = fv137[0];
  }

  iv18[0] = __constant_1x2x2x1xi32[0];
  iv18[1] = __constant_1x2x2x1xi32_7[0];
  iv18[2] = __constant_1x2x2x1xi32_6[0];
  if (__constant_1x1x2xi64[1] == 0L) {
    fv139[1] = f;
  } else {
    fv139[1] = unnamed_idx_0 + 0.5F;
  }

  iv18[3] = __constant_1x2x2x1xi32[1];
  iv18[4] = __constant_1x2x2x1xi32_7[1];
  iv18[5] = __constant_1x2x2x1xi32_6[1];
  f = __constant_1x1x2xf32[0] * 0.0009765625F;
  if (__constant_1x1x2xi64[0] == 0L) {
    fv139[2] = f;
  } else {
    fv139[2] = __constant_1x1x2xf32[0];
  }

  iv18[6] = __constant_1x2x2x1xi32[2];
  iv18[7] = __constant_1x2x2x1xi32_7[2];
  iv18[8] = __constant_1x2x2x1xi32_6[2];
  if (__constant_1x1x2xi64[1] == 0L) {
    fv139[3] = f;
  } else {
    fv139[3] = __constant_1x1x2xf32[1];
  }

  iv18[9] = __constant_1x2x2x1xi32[3];
  iv18[10] = __constant_1x2x2x1xi32_7[3];
  iv18[11] = __constant_1x2x2x1xi32_6[3];
  i1 = __constant_1x3xi32[2];
  i3 = __constant_1x3xi32[1];
  i2 = __constant_1x3xi32[0];
  for (int b_i{0}; b_i < 4; b_i++) {
    iv19[b_i] = (iv18[3 * b_i + 2] * i1 + iv18[3 * b_i + 1] * i3) + iv18[3 * b_i]
      * i2;
    fv140[b_i] = fv137[b_i];
  }

  fv140[iv19[0]] = fv139[0];
  fv140[iv19[1]] = fv139[1];
  fv140[iv19[2]] = fv139[2];
  fv140[iv19[3]] = fv139[3];
  fv137[iv19[0]] = fv140[0];
  fv137[iv19[1]] = fv140[1];
  fv137[iv19[2]] = fv140[2];
  fv137[iv19[3]] = fv140[3];
  f = fv137[1] * 0.0009765625F;
  if (__constant_1x1x2xi64[0] == 1L) {
    fv139[0] = f;
  } else {
    fv139[0] = fv137[0];
  }

  if (__constant_1x1x2xi64[1] == 1L) {
    fv139[1] = f;
  } else {
    fv139[1] = fv137[1];
  }

  f = fv137[3] * 0.0009765625F;
  if (__constant_1x1x2xi64[0] == 1L) {
    fv139[2] = f;
  } else {
    fv139[2] = fv137[2];
  }

  if (__constant_1x1x2xi64[1] == 1L) {
    fv139[3] = f;
  } else {
    fv139[3] = fv137[3];
  }

  fv140[0] = fv137[0];
  fv140[1] = fv137[1];
  fv140[2] = fv137[2];
  fv140[3] = fv137[3];
  fv140[iv19[0]] = fv139[0];
  fv140[iv19[1]] = fv139[1];
  fv140[iv19[2]] = fv139[2];
  fv140[iv19[3]] = fv139[3];
  fv137[iv19[0]] = fv140[0];
  fv137[iv19[1]] = fv140[1];
  fv137[iv19[2]] = fv140[2];
  fv137[iv19[3]] = fv140[3];
  fv139[0] = fv137[0] * 2.0F - 1.0F;
  fv139[1] = fv137[1] * 2.0F - 1.0F;
  fv139[2] = fv137[2] * 2.0F - 1.0F;
  fv139[3] = fv137[3] * 2.0F - 1.0F;
  matrixMultiply12417453134711121340(128, 2, 2, 128, 128, 128,
    &__constant_2x128xf32[0], &fv139[0], &fv141[0]);
  for (int b_i{0}; b_i < 256; b_i++) {
    f = fv141[b_i] * 6.2831855F;
    fv65[b_i] = std::sin(f);
    f = std::cos(f);
    fv7[b_i] = f;
  }

  for (int b_i{0}; b_i < 2; b_i++) {
    std::copy(&fv65[b_i * 128], &fv65[static_cast<int>(static_cast<unsigned int>
               (b_i * 128) + 128U)], &fv142[b_i * 256]);
    std::copy(&fv7[b_i * 128], &fv7[static_cast<int>(static_cast<unsigned int>
               (b_i * 128) + 128U)], &fv142[b_i * 256 + 128]);
    f = fv138[b_i];
    for (int c_i{0}; c_i < 256; c_i++) {
      if (f == -1.0F) {
        f1 = __constant_1x1x256xf32[c_i];
      } else {
        f1 = fv142[(b_i << 8) + c_i];
      }

      if (f == 0.0F) {
        f1 += __constant_1x1x256xf32_46[c_i];
      }

      if (f == 1.0F) {
        f1 += __constant_1x1x256xf32_47[c_i];
      }

      if (f == 2.0F) {
        f1 += __constant_1x1x256xf32_48[c_i];
      }

      if (f == 3.0F) {
        fv142[(b_i << 8) + c_i] = f1 + __constant_1x1x256xf32_49[c_i];
      } else {
        fv142[(b_i << 8) + c_i] = f1;
      }
    }
  }

  for (int b_i{0}; b_i < 64; b_i++) {
    b = (b_i == 0);
    for (int c_i{0}; c_i < 64; c_i++) {
      if (b) {
        fv144[(b_i << 6) + c_i] = 1.0F;
      } else {
        fv144[(b_i << 6) + c_i] = fv144[((b_i - 1) << 6) + c_i] + 1.0F;
      }

      if (c_i == 0) {
        fv145[b_i << 6] = 1.0F;
      } else {
        i1 = (b_i << 6) + c_i;
        fv145[i1] = fv145[i1 - 1] + 1.0F;
      }
    }
  }

  for (int b_i{0}; b_i < 4096; b_i++) {
    fv35[b_i] = (fv144[b_i] - 0.5F) * 0.015625F;
    fv77[b_i] = (fv145[b_i] - 0.5F) * 0.015625F;
  }

  for (int b_i{0}; b_i < 64; b_i++) {
    for (int c_i{0}; c_i < 64; c_i++) {
      i1 = (b_i << 6) + c_i;
      i3 = (b_i << 7) + (c_i << 1);
      fv143[i3] = fv77[i1];
      fv143[i3 + 1] = fv35[i1];
    }
  }

  for (int b_i{0}; b_i < 8192; b_i++) {
    fv143[b_i] = fv143[b_i] * 2.0F - 1.0F;
  }

  matrixMultiply12417453134711121340(128, 2, 4096, 128, 128, 128,
    &__constant_2x128xf32[0], &fv143[0], &fv146[0]);
  for (int b_i{0}; b_i < 524288; b_i++) {
    f = fv146[b_i] * 6.2831855F;
    fv64[b_i] = std::sin(f);
    f = std::cos(f);
    fv63[b_i] = f;
  }

  for (int b_i{0}; b_i < 64; b_i++) {
    for (int c_i{0}; c_i < 64; c_i++) {
      std::copy(&fv64[b_i * 8192 + c_i * 128], &fv64[static_cast<int>(
                 static_cast<unsigned int>(b_i * 8192 + c_i * 128) + 128U)],
                &fv147[b_i * 16384 + c_i * 256]);
      std::copy(&fv63[b_i * 8192 + c_i * 128], &fv63[static_cast<int>(
                 static_cast<unsigned int>(b_i * 8192 + c_i * 128) + 128U)],
                &fv147[(b_i * 16384 + c_i * 256) + 128]);
    }
  }

  for (int b_i{0}; b_i < 256; b_i++) {
    for (int c_i{0}; c_i < 64; c_i++) {
      for (int i{0}; i < 64; i++) {
        fv132[((b_i << 12) + (c_i << 6)) + i] = fv147[((c_i << 14) + (i << 8)) +
          b_i];
      }
    }

    fv148[b_i] = __constant_1x256xf32_0[b_i];
    fv148[b_i + 256] = __constant_1x256xf32[b_i];
  }

  std::copy(&__constant_4x256xf32[0], &__constant_4x256xf32[1024], &fv148[512]);
  std::copy(&fv148[0], &fv148[1536], &fv149[0]);
  std::copy(&fv142[0], &fv142[512], &fv149[1536]);
  for (int b_i{0}; b_i < 256; b_i++) {
    f = __constant_1x256x1x1xf32[b_i];
    for (int c_i{0}; c_i < 64; c_i++) {
      for (int i{0}; i < 64; i++) {
        i1 = ((b_i << 12) + (c_i << 6)) + i;
        fv147[i1] = fv136[i1] + f;
      }
    }
  }

  for (int b_i{0}; b_i < 4096; b_i++) {
    for (int c_i{0}; c_i < 256; c_i++) {
      fv136[(b_i << 8) + c_i] = fv147[(c_i << 12) + b_i];
    }
  }

  matrixMultiply12417453134711121340(256, 256, 8, 128, 128, 128,
    &__constant_256x256xf32[0], &fv149[0], &fv150[0]);
  for (int b_i{0}; b_i < 8; b_i++) {
    for (int c_i{0}; c_i < 256; c_i++) {
      i1 = (b_i << 8) + c_i;
      fv151[i1] = fv150[i1] + __constant_1x256xf32_50[c_i];
    }
  }

  matrixMultiply12417453134711121340(256, 256, 8, 128, 128, 128,
    &__constant_256x256xf32_187[0], &fv149[0], &fv150[0]);
  for (int b_i{0}; b_i < 8; b_i++) {
    for (int c_i{0}; c_i < 256; c_i++) {
      i1 = (b_i << 8) + c_i;
      fv152[i1] = fv150[i1] + __constant_1x256xf32_51[c_i];
    }
  }

  matrixMultiply12417453134711121340(256, 256, 8, 128, 128, 128,
    &__constant_256x256xf32_188[0], &fv149[0], &fv150[0]);
  for (int b_i{0}; b_i < 8; b_i++) {
    for (int c_i{0}; c_i < 256; c_i++) {
      i1 = (b_i << 8) + c_i;
      fv150[i1] += __constant_1x256xf32_52[c_i];
    }
  }

  for (int b_i{0}; b_i < 8; b_i++) {
    for (int c_i{0}; c_i < 8; c_i++) {
      for (int i{0}; i < 32; i++) {
        i1 = ((c_i << 8) + (b_i << 5)) + i;
        i3 = ((b_i << 8) + (c_i << 5)) + i;
        fv153[i3] = fv150[i1];
        fv154[i3] = fv151[i1] * 0.4204482F;
      }
    }
  }

  for (int b_i{0}; b_i < 8; b_i++) {
    for (int c_i{0}; c_i < 32; c_i++) {
      for (int i{0}; i < 8; i++) {
        fv151[((b_i << 8) + (c_i << 3)) + i] = fv152[((i << 8) + (b_i << 5)) +
          c_i] * 0.4204482F;
      }
    }
  }

  for (int b_i{0}; b_i < 8; b_i++) {
    i1 = b_i << 8;
    matrixMultiply12417453134711121340(8, 32, 8, 128, 128, 128, &fv151[i1],
      &fv154[i1], &fv156[0]);
    std::copy(&fv156[0], &fv156[64], &fv10[b_i * 64]);
  }

  for (int b_i{0}; b_i < 64; b_i++) {
    fv72[b_i] = -3.402823466E+38F;
    fv155[b_i] = -3.402823466E+38F;
  }

  for (int c_i{0}; c_i < 8; c_i++) {
    for (int i{0}; i < 8; i++) {
      i1 = (c_i << 3) + i;
      f = fv155[i1];
      for (int b_i{0}; b_i < 8; b_i++) {
        f1 = fv10[((c_i << 6) + (i << 3)) + b_i];
        if (!(f != f) && ((f1 != f1) || (f1 > f))) {
          f = f1;
        }
      }

      fv155[i1] = f;
      for (int b_i{0}; b_i < 8; b_i++) {
        i1 = ((c_i << 6) + (i << 3)) + b_i;
        fv9[i1] = std::exp(fv10[i1] - f);
      }
    }
  }

  std::memset(&fv155[0], 0, 64U * sizeof(float));
  std::memset(&fv157[0], 0, 64U * sizeof(float));
  for (int b_i{0}; b_i < 8; b_i++) {
    for (int c_i{0}; c_i < 8; c_i++) {
      i1 = (b_i << 3) + c_i;
      f = fv157[i1];
      for (int i{0}; i < 8; i++) {
        f += fv9[((b_i << 6) + (c_i << 3)) + i];
      }

      fv157[i1] = f;
    }
  }

  std::memset(&bv9[0], 0, 64U * sizeof(boolean_T));
  std::memset(&bv10[0], 0, 64U * sizeof(boolean_T));
  for (int c_i{0}; c_i < 8; c_i++) {
    for (int i{0}; i < 8; i++) {
      i2 = (c_i << 3) + i;
      b = bv10[i2];
      for (int b_i{0}; b_i < 8; b_i++) {
        b = (!(fv10[((c_i << 6) + (i << 3)) + b_i] == rtMinusInfF) || b);
      }

      bv10[i2] = b;
      for (int b_i{0}; b_i < 8; b_i++) {
        if (b) {
          i1 = ((c_i << 6) + (i << 3)) + b_i;
          fv9[i1] *= 1.0F / fv157[i2];
        } else {
          fv9[((c_i << 6) + (i << 3)) + b_i] = 0.0F;
        }
      }
    }
  }

  for (int b_i{0}; b_i < 8; b_i++) {
    i1 = b_i << 8;
    matrixMultiply12417453134711121340(32, 8, 8, 128, 128, 128, &fv153[i1],
      &fv9[b_i << 6], &fv158[0]);
    std::copy(&fv158[0], &fv158[256], &fv151[i1]);
  }

  for (int b_i{0}; b_i < 8; b_i++) {
    for (int c_i{0}; c_i < 8; c_i++) {
      std::copy(&fv151[b_i * 32 + c_i * 256], &fv151[static_cast<int>(
                 static_cast<unsigned int>(b_i * 32 + c_i * 256) + 32U)],
                &fv154[b_i * 256 + c_i * 32]);
    }
  }

  matrixMultiply12417453134711121340(256, 256, 8, 128, 128, 128,
    &__constant_256x256xf32_189[0], &fv154[0], &fv150[0]);
  for (int b_i{0}; b_i < 8; b_i++) {
    for (int c_i{0}; c_i < 256; c_i++) {
      i1 = (b_i << 8) + c_i;
      fv150[i1] += __constant_1x256xf32_53[c_i];
    }
  }

  for (int b_i{0}; b_i < 2048; b_i++) {
    dv20[b_i] = fv150[b_i];
  }

  for (int c_i{0}; c_i < 8; c_i++) {
    dv21[c_i] = 0.0;
    dv22[c_i] = 0.0;
    d = 0.0;
    for (int b_i{0}; b_i < 256; b_i++) {
      d += dv20[(c_i << 8) + b_i];
    }

    fv159[c_i] = 0.0F;
    d1 = 0.0;
    f = 0.0F;
    for (int b_i{0}; b_i < 256; b_i++) {
      i1 = (c_i << 8) + b_i;
      d2 = dv20[i1] - d * 0.00390625;
      d1 += d2 * d2;
      f += fv150[i1];
    }

    for (int b_i{0}; b_i < 256; b_i++) {
      i1 = (c_i << 8) + b_i;
      fv151[i1] = (fv150[i1] - f * 0.00390625F) * (1.0F / std::sqrt(static_cast<
        float>(d1 * 0.00390625) + 1.0E-5F)) * __constant_1x1x256xf32_54[b_i] +
        __constant_1x1x256xf32_55[b_i];
    }
  }

  for (int b_i{0}; b_i < 2048; b_i++) {
    fv152[b_i] = fv151[b_i] + fv149[b_i];
  }

  for (int b_i{0}; b_i < 4096; b_i++) {
    for (int c_i{0}; c_i < 256; c_i++) {
      i1 = (c_i << 12) + b_i;
      fv160[(b_i << 8) + c_i] = fv147[i1] + fv132[i1];
    }
  }

  matrixMultiply12417453134711121340(128, 256, 8, 128, 128, 128,
    &__constant_256x128xf32[0], &fv152[0], &fv161[0]);
  for (int b_i{0}; b_i < 8; b_i++) {
    for (int c_i{0}; c_i < 128; c_i++) {
      i1 = (b_i << 7) + c_i;
      fv161[i1] += __constant_1x128xf32[c_i];
    }
  }

  matrixMultiply12417453134711121340(128, 256, 4096, 128, 128, 128,
    &__constant_256x128xf32_190[0], &fv160[0], &fv146[0]);
  for (int b_i{0}; b_i < 4096; b_i++) {
    for (int c_i{0}; c_i < 128; c_i++) {
      i1 = (b_i << 7) + c_i;
      fv63[i1] = fv146[i1] + __constant_1x128xf32_56[c_i];
    }
  }

  matrixMultiply12417453134711121340(128, 256, 4096, 128, 128, 128,
    &__constant_256x128xf32_191[0], &fv136[0], &fv146[0]);
  for (int b_i{0}; b_i < 4096; b_i++) {
    for (int c_i{0}; c_i < 128; c_i++) {
      i1 = (b_i << 7) + c_i;
      fv146[i1] += __constant_1x128xf32_57[c_i];
    }
  }

  for (int i{0}; i < 8; i++) {
    for (int b_i{0}; b_i < 4096; b_i++) {
      std::copy(&fv146[i * 16 + b_i * 128], &fv146[static_cast<int>(static_cast<
                 unsigned int>(i * 16 + b_i * 128) + 16U)], &fv64[i * 65536 +
                b_i * 16]);
    }

    for (int b_i{0}; b_i < 8; b_i++) {
      for (int c_i{0}; c_i < 16; c_i++) {
        fv50[((i << 7) + (b_i << 4)) + c_i] = fv161[((b_i << 7) + (i << 4)) +
          c_i] * 0.5F;
      }
    }

    for (int b_i{0}; b_i < 16; b_i++) {
      for (int c_i{0}; c_i < 4096; c_i++) {
        fv162[((i << 16) + (b_i << 12)) + c_i] = fv63[((c_i << 7) + (i << 4)) +
          b_i] * 0.5F;
      }
    }
  }

  for (int b_i{0}; b_i < 8; b_i++) {
    matrixMultiply4454328187142109130(4096, 16, 8, 128, 128, 128, &fv162[b_i <<
      16], &fv50[b_i << 7], &fv163[0]);
    std::copy(&fv163[0], &fv163[32768], &fv71[b_i * 32768]);
  }

  for (int b_i{0}; b_i < 64; b_i++) {
    fv157[b_i] = -3.402823466E+38F;
  }

  for (int c_i{0}; c_i < 8; c_i++) {
    for (int i{0}; i < 8; i++) {
      i2 = (c_i << 3) + i;
      f2 = fv157[i2];
      for (int b_i{0}; b_i < 4096; b_i++) {
        f = fv71[((c_i << 15) + (i << 12)) + b_i];
        if (!(f2 != f2) && ((f != f) || (f > f2))) {
          f2 = f;
        }
      }

      fv157[i2] = f2;
      f = 0.0F;
      for (int b_i{0}; b_i < 4096; b_i++) {
        i1 = ((c_i << 15) + (i << 12)) + b_i;
        f1 = std::exp(fv71[i1] - f2);
        fv73[i1] = f1;
        f += f1;
      }

      fv164[i2] = f;
      bv10[i2] = false;
    }
  }

  for (int c_i{0}; c_i < 8; c_i++) {
    for (int i{0}; i < 8; i++) {
      i2 = (c_i << 3) + i;
      b = bv10[i2];
      for (int b_i{0}; b_i < 4096; b_i++) {
        b = (!(fv71[((c_i << 15) + (i << 12)) + b_i] == rtMinusInfF) || b);
      }

      bv10[i2] = b;
      for (int b_i{0}; b_i < 4096; b_i++) {
        if (b) {
          i1 = ((c_i << 15) + (i << 12)) + b_i;
          fv73[i1] *= 1.0F / fv164[i2];
        } else {
          fv73[((c_i << 15) + (i << 12)) + b_i] = 0.0F;
        }
      }
    }
  }

  for (int b_i{0}; b_i < 8; b_i++) {
    matrixMultiply12417453134711121340(16, 4096, 8, 128, 128, 128, &fv64[b_i <<
      16], &fv73[b_i << 15], &fv165[0]);
    std::copy(&fv165[0], &fv165[128], &fv120[b_i * 128]);
  }

  for (int b_i{0}; b_i < 8; b_i++) {
    for (int c_i{0}; c_i < 8; c_i++) {
      std::copy(&fv120[b_i * 16 + c_i * 128], &fv120[static_cast<int>(
                 static_cast<unsigned int>(b_i * 16 + c_i * 128) + 16U)],
                &fv50[b_i * 128 + c_i * 16]);
    }
  }

  matrixMultiply12417453134711121340(256, 128, 8, 128, 128, 128,
    &__constant_128x256xf32[0], &fv50[0], &fv150[0]);
  for (int b_i{0}; b_i < 8; b_i++) {
    for (int c_i{0}; c_i < 256; c_i++) {
      i1 = (b_i << 8) + c_i;
      fv150[i1] += __constant_1x256xf32_58[c_i];
    }
  }

  for (int b_i{0}; b_i < 2048; b_i++) {
    f = fv151[b_i] + fv150[b_i];
    fv152[b_i] = f;
    dv20[b_i] = f;
  }

  for (int c_i{0}; c_i < 8; c_i++) {
    d = 0.0;
    for (int b_i{0}; b_i < 256; b_i++) {
      d += dv20[(c_i << 8) + b_i];
    }

    d1 = 0.0;
    f = 0.0F;
    for (int b_i{0}; b_i < 256; b_i++) {
      i1 = (c_i << 8) + b_i;
      d2 = dv20[i1] - d * 0.00390625;
      d1 += d2 * d2;
      f += fv152[i1];
    }

    for (int b_i{0}; b_i < 256; b_i++) {
      i1 = (c_i << 8) + b_i;
      fv152[i1] = (fv152[i1] - f * 0.00390625F) * (1.0F / std::sqrt(static_cast<
        float>(d1 * 0.00390625) + 1.0E-5F)) * __constant_1x1x256xf32_59[b_i] +
        __constant_1x1x256xf32_60[b_i];
    }
  }

  matrixMultiply4454328187142109130(2048, 256, 8, 128, 128, 128,
    &__constant_256x2048xf32[0], &fv152[0], &fv166[0]);
  for (int b_i{0}; b_i < 8; b_i++) {
    for (int c_i{0}; c_i < 2048; c_i++) {
      i1 = (b_i << 11) + c_i;
      fv166[i1] += __constant_1x2048xf32[c_i];
    }
  }

  for (int b_i{0}; b_i < 16384; b_i++) {
    if ((fv166[b_i] != fv166[b_i]) || (fv166[b_i] < 3.402823466E+38F)) {
      f = fv166[b_i];
    } else {
      f = 3.402823466E+38F;
    }

    if ((f != f) || (f > 0.0F)) {
      fv58[b_i] = f;
    } else {
      fv58[b_i] = 0.0F;
    }
  }

  matrixMultiply12417453134711121340(256, 2048, 8, 128, 128, 128,
    &__constant_2048x256xf32[0], &fv58[0], &fv150[0]);
  for (int b_i{0}; b_i < 8; b_i++) {
    for (int c_i{0}; c_i < 256; c_i++) {
      i1 = (b_i << 8) + c_i;
      fv150[i1] += __constant_1x256xf32_61[c_i];
    }
  }

  for (int b_i{0}; b_i < 2048; b_i++) {
    f = fv152[b_i] + fv150[b_i];
    fv152[b_i] = f;
    dv20[b_i] = f;
  }

  for (int c_i{0}; c_i < 8; c_i++) {
    d = 0.0;
    for (int b_i{0}; b_i < 256; b_i++) {
      d += dv20[(c_i << 8) + b_i];
    }

    d1 = 0.0;
    f = 0.0F;
    for (int b_i{0}; b_i < 256; b_i++) {
      i1 = (c_i << 8) + b_i;
      d2 = dv20[i1] - d * 0.00390625;
      d1 += d2 * d2;
      f += fv152[i1];
    }

    for (int b_i{0}; b_i < 256; b_i++) {
      i1 = (c_i << 8) + b_i;
      fv153[i1] = (fv152[i1] - f * 0.00390625F) * (1.0F / std::sqrt(static_cast<
        float>(d1 * 0.00390625) + 1.0E-5F)) * __constant_1x1x256xf32_62[b_i] +
        __constant_1x1x256xf32_63[b_i];
    }
  }

  for (int b_i{0}; b_i < 2048; b_i++) {
    fv152[b_i] = fv153[b_i] + fv149[b_i];
  }

  matrixMultiply12417453134711121340(128, 256, 4096, 128, 128, 128,
    &__constant_256x128xf32_192[0], &fv160[0], &fv146[0]);
  for (int b_i{0}; b_i < 4096; b_i++) {
    for (int c_i{0}; c_i < 128; c_i++) {
      i1 = (b_i << 7) + c_i;
      fv146[i1] += __constant_1x128xf32_64[c_i];
    }
  }

  matrixMultiply12417453134711121340(128, 256, 8, 128, 128, 128,
    &__constant_256x128xf32_193[0], &fv152[0], &fv161[0]);
  for (int b_i{0}; b_i < 8; b_i++) {
    for (int c_i{0}; c_i < 128; c_i++) {
      i1 = (b_i << 7) + c_i;
      fv120[i1] = fv161[i1] + __constant_1x128xf32_65[c_i];
    }
  }

  matrixMultiply12417453134711121340(128, 256, 8, 128, 128, 128,
    &__constant_256x128xf32_194[0], &fv153[0], &fv161[0]);
  for (int b_i{0}; b_i < 8; b_i++) {
    for (int c_i{0}; c_i < 128; c_i++) {
      i1 = (b_i << 7) + c_i;
      fv161[i1] += __constant_1x128xf32_66[c_i];
    }
  }

  for (int i{0}; i < 8; i++) {
    for (int b_i{0}; b_i < 8; b_i++) {
      std::copy(&fv161[i * 16 + b_i * 128], &fv161[static_cast<int>(static_cast<
                 unsigned int>(i * 16 + b_i * 128) + 16U)], &fv50[i * 128 + b_i *
                16]);
    }

    for (int b_i{0}; b_i < 4096; b_i++) {
      for (int c_i{0}; c_i < 16; c_i++) {
        fv64[((i << 16) + (b_i << 4)) + c_i] = fv146[((b_i << 7) + (i << 4)) +
          c_i] * 0.5F;
      }
    }

    for (int b_i{0}; b_i < 16; b_i++) {
      for (int c_i{0}; c_i < 8; c_i++) {
        fv124[((i << 7) + (b_i << 3)) + c_i] = fv120[((c_i << 7) + (i << 4)) +
          b_i] * 0.5F;
      }
    }
  }

  for (int b_i{0}; b_i < 8; b_i++) {
    matrixMultiply12417453134711121340(8, 16, 4096, 128, 128, 128, &fv124[b_i <<
      7], &fv64[b_i << 16], &fv167[0]);
    std::copy(&fv167[0], &fv167[32768], &fv71[b_i * 32768]);
  }

  for (int b_i{0}; b_i < 32768; b_i++) {
    fv49[b_i] = -3.402823466E+38F;
    fv53[b_i] = -3.402823466E+38F;
  }

  for (int c_i{0}; c_i < 8; c_i++) {
    for (int i{0}; i < 4096; i++) {
      i1 = (c_i << 12) + i;
      f = fv53[i1];
      for (int b_i{0}; b_i < 8; b_i++) {
        f1 = fv71[((c_i << 15) + (i << 3)) + b_i];
        if (!(f != f) && ((f1 != f1) || (f1 > f))) {
          f = f1;
        }
      }

      fv53[i1] = f;
      for (int b_i{0}; b_i < 8; b_i++) {
        i1 = ((c_i << 15) + (i << 3)) + b_i;
        fv73[i1] = std::exp(fv71[i1] - f);
      }
    }
  }

  std::memset(&fv51[0], 0, 32768U * sizeof(float));
  std::memset(&fv53[0], 0, 32768U * sizeof(float));
  for (int b_i{0}; b_i < 8; b_i++) {
    for (int c_i{0}; c_i < 4096; c_i++) {
      i1 = (b_i << 12) + c_i;
      f = fv53[i1];
      for (int i{0}; i < 8; i++) {
        f += fv73[((b_i << 15) + (c_i << 3)) + i];
      }

      fv53[i1] = f;
    }
  }

  std::memset(&bv1[0], 0, 32768U * sizeof(boolean_T));
  std::memset(&bv2[0], 0, 32768U * sizeof(boolean_T));
  for (int c_i{0}; c_i < 8; c_i++) {
    for (int i{0}; i < 4096; i++) {
      i2 = (c_i << 12) + i;
      b = bv2[i2];
      for (int b_i{0}; b_i < 8; b_i++) {
        b = (!(fv71[((c_i << 15) + (i << 3)) + b_i] == rtMinusInfF) || b);
      }

      bv2[i2] = b;
      for (int b_i{0}; b_i < 8; b_i++) {
        if (b) {
          i1 = ((c_i << 15) + (i << 3)) + b_i;
          fv73[i1] *= 1.0F / fv53[i2];
        } else {
          fv73[((c_i << 15) + (i << 3)) + b_i] = 0.0F;
        }
      }
    }
  }

  for (int b_i{0}; b_i < 8; b_i++) {
    matrixMultiply12417453134711121340(16, 8, 4096, 128, 128, 128, &fv50[b_i <<
      7], &fv73[b_i << 15], &fv168[0]);
    std::copy(&fv168[0], &fv168[65536], &fv63[b_i * 65536]);
  }

  for (int b_i{0}; b_i < 4096; b_i++) {
    for (int c_i{0}; c_i < 8; c_i++) {
      std::copy(&fv63[b_i * 16 + c_i * 65536], &fv63[static_cast<int>(
                 static_cast<unsigned int>(b_i * 16 + c_i * 65536) + 16U)],
                &fv64[b_i * 128 + c_i * 16]);
    }
  }

  matrixMultiply12417453134711121340(256, 128, 4096, 128, 128, 128,
    &__constant_128x256xf32_195[0], &fv64[0], &fv169[0]);
  for (int b_i{0}; b_i < 4096; b_i++) {
    for (int c_i{0}; c_i < 256; c_i++) {
      i1 = (b_i << 8) + c_i;
      fv169[i1] += __constant_1x256xf32_67[c_i];
    }
  }

  for (int b_i{0}; b_i < 256; b_i++) {
    for (int c_i{0}; c_i < 4096; c_i++) {
      i1 = (b_i << 12) + c_i;
      fv136[i1] = fv147[i1] + fv169[(c_i << 8) + b_i];
    }
  }

  for (int b_i{0}; b_i < 4096; b_i++) {
    for (int c_i{0}; c_i < 256; c_i++) {
      fv160[(b_i << 8) + c_i] = fv136[(c_i << 12) + b_i];
    }
  }

  for (int b_i{0}; b_i < 1048576; b_i++) {
    dv23[b_i] = fv160[b_i];
  }

  for (int c_i{0}; c_i < 4096; c_i++) {
    dv11[c_i] = 0.0;
    dv13[c_i] = 0.0;
    d = 0.0;
    for (int b_i{0}; b_i < 256; b_i++) {
      d += dv23[(c_i << 8) + b_i];
    }

    fv35[c_i] = 0.0F;
    d1 = 0.0;
    f = 0.0F;
    for (int b_i{0}; b_i < 256; b_i++) {
      i1 = (c_i << 8) + b_i;
      d2 = dv23[i1] - d * 0.00390625;
      d1 += d2 * d2;
      f += fv160[i1];
    }

    fv77[c_i] = f;
    dv14[c_i] = d1;
  }

  for (int b_i{0}; b_i < 256; b_i++) {
    f = __constant_1x256x1xf32_160[b_i];
    f1 = __constant_1x256x1xf32_161[b_i];
    for (int c_i{0}; c_i < 4096; c_i++) {
      i1 = (b_i << 12) + c_i;
      fv136[i1] = (fv136[i1] - fv77[c_i] * 0.00390625F) * (1.0F / std::sqrt(
        static_cast<float>(dv14[c_i] * 0.00390625) + 1.0E-5F)) * f + f1;
    }
  }

  for (int b_i{0}; b_i < 4096; b_i++) {
    for (int c_i{0}; c_i < 256; c_i++) {
      fv147[(b_i << 8) + c_i] = fv136[(c_i << 12) + b_i];
    }
  }

  matrixMultiply12417453134711121340(256, 256, 8, 128, 128, 128,
    &__constant_256x256xf32_196[0], &fv152[0], &fv150[0]);
  for (int b_i{0}; b_i < 8; b_i++) {
    for (int c_i{0}; c_i < 256; c_i++) {
      i1 = (b_i << 8) + c_i;
      fv151[i1] = fv150[i1] + __constant_1x256xf32_68[c_i];
    }
  }

  matrixMultiply12417453134711121340(256, 256, 8, 128, 128, 128,
    &__constant_256x256xf32_197[0], &fv152[0], &fv150[0]);
  for (int b_i{0}; b_i < 8; b_i++) {
    for (int c_i{0}; c_i < 256; c_i++) {
      i1 = (b_i << 8) + c_i;
      fv152[i1] = fv150[i1] + __constant_1x256xf32_69[c_i];
    }
  }

  matrixMultiply12417453134711121340(256, 256, 8, 128, 128, 128,
    &__constant_256x256xf32_198[0], &fv153[0], &fv150[0]);
  for (int b_i{0}; b_i < 8; b_i++) {
    for (int c_i{0}; c_i < 256; c_i++) {
      i1 = (b_i << 8) + c_i;
      fv150[i1] += __constant_1x256xf32_70[c_i];
    }
  }

  for (int b_i{0}; b_i < 8; b_i++) {
    for (int c_i{0}; c_i < 8; c_i++) {
      for (int i{0}; i < 32; i++) {
        i1 = ((c_i << 8) + (b_i << 5)) + i;
        i3 = ((b_i << 8) + (c_i << 5)) + i;
        fv170[i3] = fv150[i1];
        fv154[i3] = fv151[i1] * 0.4204482F;
      }
    }
  }

  for (int b_i{0}; b_i < 8; b_i++) {
    for (int c_i{0}; c_i < 32; c_i++) {
      for (int i{0}; i < 8; i++) {
        fv151[((b_i << 8) + (c_i << 3)) + i] = fv152[((i << 8) + (b_i << 5)) +
          c_i] * 0.4204482F;
      }
    }
  }

  for (int b_i{0}; b_i < 8; b_i++) {
    i1 = b_i << 8;
    matrixMultiply12417453134711121340(8, 32, 8, 128, 128, 128, &fv151[i1],
      &fv154[i1], &fv156[0]);
    std::copy(&fv156[0], &fv156[64], &fv10[b_i * 64]);
  }

  for (int b_i{0}; b_i < 64; b_i++) {
    fv157[b_i] = -3.402823466E+38F;
  }

  for (int c_i{0}; c_i < 8; c_i++) {
    for (int i{0}; i < 8; i++) {
      i2 = (c_i << 3) + i;
      f2 = fv157[i2];
      for (int b_i{0}; b_i < 8; b_i++) {
        f = fv10[((c_i << 6) + (i << 3)) + b_i];
        if (!(f2 != f2) && ((f != f) || (f > f2))) {
          f2 = f;
        }
      }

      fv157[i2] = f2;
      f = 0.0F;
      for (int b_i{0}; b_i < 8; b_i++) {
        i1 = ((c_i << 6) + (i << 3)) + b_i;
        f1 = std::exp(fv10[i1] - f2);
        fv9[i1] = f1;
        f += f1;
      }

      fv164[i2] = f;
      bv10[i2] = false;
    }
  }

  for (int c_i{0}; c_i < 8; c_i++) {
    for (int i{0}; i < 8; i++) {
      i2 = (c_i << 3) + i;
      b = bv10[i2];
      for (int b_i{0}; b_i < 8; b_i++) {
        b = (!(fv10[((c_i << 6) + (i << 3)) + b_i] == rtMinusInfF) || b);
      }

      bv10[i2] = b;
      for (int b_i{0}; b_i < 8; b_i++) {
        if (b) {
          i1 = ((c_i << 6) + (i << 3)) + b_i;
          fv9[i1] *= 1.0F / fv164[i2];
        } else {
          fv9[((c_i << 6) + (i << 3)) + b_i] = 0.0F;
        }
      }
    }
  }

  for (int b_i{0}; b_i < 8; b_i++) {
    i1 = b_i << 8;
    matrixMultiply12417453134711121340(32, 8, 8, 128, 128, 128, &fv170[i1],
      &fv9[b_i << 6], &fv158[0]);
    std::copy(&fv158[0], &fv158[256], &fv151[i1]);
  }

  for (int b_i{0}; b_i < 8; b_i++) {
    for (int c_i{0}; c_i < 8; c_i++) {
      std::copy(&fv151[b_i * 32 + c_i * 256], &fv151[static_cast<int>(
                 static_cast<unsigned int>(b_i * 32 + c_i * 256) + 32U)],
                &fv154[b_i * 256 + c_i * 32]);
    }
  }

  matrixMultiply12417453134711121340(256, 256, 8, 128, 128, 128,
    &__constant_256x256xf32_199[0], &fv154[0], &fv150[0]);
  for (int b_i{0}; b_i < 8; b_i++) {
    for (int c_i{0}; c_i < 256; c_i++) {
      i1 = (b_i << 8) + c_i;
      fv150[i1] += __constant_1x256xf32_71[c_i];
    }
  }

  for (int b_i{0}; b_i < 2048; b_i++) {
    f = fv153[b_i] + fv150[b_i];
    fv152[b_i] = f;
    dv20[b_i] = f;
  }

  for (int c_i{0}; c_i < 8; c_i++) {
    d = 0.0;
    for (int b_i{0}; b_i < 256; b_i++) {
      d += dv20[(c_i << 8) + b_i];
    }

    d1 = 0.0;
    f = 0.0F;
    for (int b_i{0}; b_i < 256; b_i++) {
      i1 = (c_i << 8) + b_i;
      d2 = dv20[i1] - d * 0.00390625;
      d1 += d2 * d2;
      f += fv152[i1];
    }

    for (int b_i{0}; b_i < 256; b_i++) {
      i1 = (c_i << 8) + b_i;
      fv151[i1] = (fv152[i1] - f * 0.00390625F) * (1.0F / std::sqrt(static_cast<
        float>(d1 * 0.00390625) + 1.0E-5F)) * __constant_1x1x256xf32_72[b_i] +
        __constant_1x1x256xf32_73[b_i];
    }
  }

  for (int b_i{0}; b_i < 2048; b_i++) {
    fv152[b_i] = fv151[b_i] + fv149[b_i];
  }

  for (int b_i{0}; b_i < 4096; b_i++) {
    for (int c_i{0}; c_i < 256; c_i++) {
      i1 = (c_i << 12) + b_i;
      fv160[(b_i << 8) + c_i] = fv136[i1] + fv132[i1];
    }
  }

  matrixMultiply12417453134711121340(128, 256, 8, 128, 128, 128,
    &__constant_256x128xf32_200[0], &fv152[0], &fv161[0]);
  for (int b_i{0}; b_i < 8; b_i++) {
    for (int c_i{0}; c_i < 128; c_i++) {
      i1 = (b_i << 7) + c_i;
      fv161[i1] += __constant_1x128xf32_74[c_i];
    }
  }

  matrixMultiply12417453134711121340(128, 256, 4096, 128, 128, 128,
    &__constant_256x128xf32_201[0], &fv160[0], &fv146[0]);
  for (int b_i{0}; b_i < 4096; b_i++) {
    for (int c_i{0}; c_i < 128; c_i++) {
      i1 = (b_i << 7) + c_i;
      fv63[i1] = fv146[i1] + __constant_1x128xf32_75[c_i];
    }
  }

  matrixMultiply12417453134711121340(128, 256, 4096, 128, 128, 128,
    &__constant_256x128xf32_202[0], &fv147[0], &fv146[0]);
  for (int b_i{0}; b_i < 4096; b_i++) {
    for (int c_i{0}; c_i < 128; c_i++) {
      i1 = (b_i << 7) + c_i;
      fv146[i1] += __constant_1x128xf32_76[c_i];
    }
  }

  for (int i{0}; i < 8; i++) {
    for (int b_i{0}; b_i < 4096; b_i++) {
      std::copy(&fv146[i * 16 + b_i * 128], &fv146[static_cast<int>(static_cast<
                 unsigned int>(i * 16 + b_i * 128) + 16U)], &fv64[i * 65536 +
                b_i * 16]);
    }

    for (int b_i{0}; b_i < 8; b_i++) {
      for (int c_i{0}; c_i < 16; c_i++) {
        fv50[((i << 7) + (b_i << 4)) + c_i] = fv161[((b_i << 7) + (i << 4)) +
          c_i] * 0.5F;
      }
    }

    for (int b_i{0}; b_i < 16; b_i++) {
      for (int c_i{0}; c_i < 4096; c_i++) {
        fv162[((i << 16) + (b_i << 12)) + c_i] = fv63[((c_i << 7) + (i << 4)) +
          b_i] * 0.5F;
      }
    }
  }

  for (int b_i{0}; b_i < 8; b_i++) {
    matrixMultiply4454328187142109130(4096, 16, 8, 128, 128, 128, &fv162[b_i <<
      16], &fv50[b_i << 7], &fv163[0]);
    std::copy(&fv163[0], &fv163[32768], &fv71[b_i * 32768]);
  }

  for (int b_i{0}; b_i < 64; b_i++) {
    fv157[b_i] = -3.402823466E+38F;
  }

  for (int c_i{0}; c_i < 8; c_i++) {
    for (int i{0}; i < 8; i++) {
      i2 = (c_i << 3) + i;
      f2 = fv157[i2];
      for (int b_i{0}; b_i < 4096; b_i++) {
        f = fv71[((c_i << 15) + (i << 12)) + b_i];
        if (!(f2 != f2) && ((f != f) || (f > f2))) {
          f2 = f;
        }
      }

      fv157[i2] = f2;
      f = 0.0F;
      for (int b_i{0}; b_i < 4096; b_i++) {
        i1 = ((c_i << 15) + (i << 12)) + b_i;
        f1 = std::exp(fv71[i1] - f2);
        fv73[i1] = f1;
        f += f1;
      }

      fv164[i2] = f;
      bv10[i2] = false;
    }
  }

  for (int c_i{0}; c_i < 8; c_i++) {
    for (int i{0}; i < 8; i++) {
      i2 = (c_i << 3) + i;
      b = bv10[i2];
      for (int b_i{0}; b_i < 4096; b_i++) {
        b = (!(fv71[((c_i << 15) + (i << 12)) + b_i] == rtMinusInfF) || b);
      }

      bv10[i2] = b;
      for (int b_i{0}; b_i < 4096; b_i++) {
        if (b) {
          i1 = ((c_i << 15) + (i << 12)) + b_i;
          fv73[i1] *= 1.0F / fv164[i2];
        } else {
          fv73[((c_i << 15) + (i << 12)) + b_i] = 0.0F;
        }
      }
    }
  }

  for (int b_i{0}; b_i < 8; b_i++) {
    matrixMultiply12417453134711121340(16, 4096, 8, 128, 128, 128, &fv64[b_i <<
      16], &fv73[b_i << 15], &fv165[0]);
    std::copy(&fv165[0], &fv165[128], &fv120[b_i * 128]);
  }

  for (int b_i{0}; b_i < 8; b_i++) {
    for (int c_i{0}; c_i < 8; c_i++) {
      std::copy(&fv120[b_i * 16 + c_i * 128], &fv120[static_cast<int>(
                 static_cast<unsigned int>(b_i * 16 + c_i * 128) + 16U)],
                &fv50[b_i * 128 + c_i * 16]);
    }
  }

  matrixMultiply12417453134711121340(256, 128, 8, 128, 128, 128,
    &__constant_128x256xf32_203[0], &fv50[0], &fv150[0]);
  for (int b_i{0}; b_i < 8; b_i++) {
    for (int c_i{0}; c_i < 256; c_i++) {
      i1 = (b_i << 8) + c_i;
      fv150[i1] += __constant_1x256xf32_77[c_i];
    }
  }

  for (int b_i{0}; b_i < 2048; b_i++) {
    f = fv151[b_i] + fv150[b_i];
    fv152[b_i] = f;
    dv20[b_i] = f;
  }

  for (int c_i{0}; c_i < 8; c_i++) {
    d = 0.0;
    for (int b_i{0}; b_i < 256; b_i++) {
      d += dv20[(c_i << 8) + b_i];
    }

    d1 = 0.0;
    f = 0.0F;
    for (int b_i{0}; b_i < 256; b_i++) {
      i1 = (c_i << 8) + b_i;
      d2 = dv20[i1] - d * 0.00390625;
      d1 += d2 * d2;
      f += fv152[i1];
    }

    for (int b_i{0}; b_i < 256; b_i++) {
      i1 = (c_i << 8) + b_i;
      fv152[i1] = (fv152[i1] - f * 0.00390625F) * (1.0F / std::sqrt(static_cast<
        float>(d1 * 0.00390625) + 1.0E-5F)) * __constant_1x1x256xf32_78[b_i] +
        __constant_1x1x256xf32_79[b_i];
    }
  }

  matrixMultiply4454328187142109130(2048, 256, 8, 128, 128, 128,
    &__constant_256x2048xf32_204[0], &fv152[0], &fv166[0]);
  for (int b_i{0}; b_i < 8; b_i++) {
    for (int c_i{0}; c_i < 2048; c_i++) {
      i1 = (b_i << 11) + c_i;
      fv166[i1] += __constant_1x2048xf32_80[c_i];
    }
  }

  for (int b_i{0}; b_i < 16384; b_i++) {
    if ((fv166[b_i] != fv166[b_i]) || (fv166[b_i] < 3.402823466E+38F)) {
      f = fv166[b_i];
    } else {
      f = 3.402823466E+38F;
    }

    if ((f != f) || (f > 0.0F)) {
      fv58[b_i] = f;
    } else {
      fv58[b_i] = 0.0F;
    }
  }

  matrixMultiply12417453134711121340(256, 2048, 8, 128, 128, 128,
    &__constant_2048x256xf32_205[0], &fv58[0], &fv150[0]);
  for (int b_i{0}; b_i < 8; b_i++) {
    for (int c_i{0}; c_i < 256; c_i++) {
      i1 = (b_i << 8) + c_i;
      fv150[i1] += __constant_1x256xf32_81[c_i];
    }
  }

  for (int b_i{0}; b_i < 2048; b_i++) {
    f = fv152[b_i] + fv150[b_i];
    fv152[b_i] = f;
    dv20[b_i] = f;
  }

  for (int c_i{0}; c_i < 8; c_i++) {
    d = 0.0;
    for (int b_i{0}; b_i < 256; b_i++) {
      d += dv20[(c_i << 8) + b_i];
    }

    d1 = 0.0;
    f = 0.0F;
    for (int b_i{0}; b_i < 256; b_i++) {
      i1 = (c_i << 8) + b_i;
      d2 = dv20[i1] - d * 0.00390625;
      d1 += d2 * d2;
      f += fv152[i1];
    }

    for (int b_i{0}; b_i < 256; b_i++) {
      i1 = (c_i << 8) + b_i;
      fv151[i1] = (fv152[i1] - f * 0.00390625F) * (1.0F / std::sqrt(static_cast<
        float>(d1 * 0.00390625) + 1.0E-5F)) * __constant_1x1x256xf32_82[b_i] +
        __constant_1x1x256xf32_83[b_i];
    }
  }

  for (int b_i{0}; b_i < 2048; b_i++) {
    fv152[b_i] = fv151[b_i] + fv149[b_i];
  }

  matrixMultiply12417453134711121340(128, 256, 4096, 128, 128, 128,
    &__constant_256x128xf32_206[0], &fv160[0], &fv146[0]);
  for (int b_i{0}; b_i < 4096; b_i++) {
    for (int c_i{0}; c_i < 128; c_i++) {
      i1 = (b_i << 7) + c_i;
      fv146[i1] += __constant_1x128xf32_84[c_i];
    }
  }

  matrixMultiply12417453134711121340(128, 256, 8, 128, 128, 128,
    &__constant_256x128xf32_207[0], &fv152[0], &fv161[0]);
  for (int b_i{0}; b_i < 8; b_i++) {
    for (int c_i{0}; c_i < 128; c_i++) {
      i1 = (b_i << 7) + c_i;
      fv120[i1] = fv161[i1] + __constant_1x128xf32_85[c_i];
    }
  }

  matrixMultiply12417453134711121340(128, 256, 8, 128, 128, 128,
    &__constant_256x128xf32_208[0], &fv151[0], &fv161[0]);
  for (int b_i{0}; b_i < 8; b_i++) {
    for (int c_i{0}; c_i < 128; c_i++) {
      i1 = (b_i << 7) + c_i;
      fv161[i1] += __constant_1x128xf32_86[c_i];
    }
  }

  for (int i{0}; i < 8; i++) {
    for (int b_i{0}; b_i < 8; b_i++) {
      std::copy(&fv161[i * 16 + b_i * 128], &fv161[static_cast<int>(static_cast<
                 unsigned int>(i * 16 + b_i * 128) + 16U)], &fv50[i * 128 + b_i *
                16]);
    }

    for (int b_i{0}; b_i < 4096; b_i++) {
      for (int c_i{0}; c_i < 16; c_i++) {
        fv64[((i << 16) + (b_i << 4)) + c_i] = fv146[((b_i << 7) + (i << 4)) +
          c_i] * 0.5F;
      }
    }

    for (int b_i{0}; b_i < 16; b_i++) {
      for (int c_i{0}; c_i < 8; c_i++) {
        fv124[((i << 7) + (b_i << 3)) + c_i] = fv120[((c_i << 7) + (i << 4)) +
          b_i] * 0.5F;
      }
    }
  }

  for (int b_i{0}; b_i < 8; b_i++) {
    matrixMultiply12417453134711121340(8, 16, 4096, 128, 128, 128, &fv124[b_i <<
      7], &fv64[b_i << 16], &fv167[0]);
    std::copy(&fv167[0], &fv167[32768], &fv71[b_i * 32768]);
  }

  for (int c_i{0}; c_i < 8; c_i++) {
    for (int i{0}; i < 4096; i++) {
      i2 = (c_i << 12) + i;
      f3 = fv49[i2];
      for (int b_i{0}; b_i < 8; b_i++) {
        f = fv71[((c_i << 15) + (i << 3)) + b_i];
        if (!(f3 != f3) && ((f != f) || (f > f3))) {
          f3 = f;
        }
      }

      fv49[i2] = f3;
      f = fv51[i2];
      b = bv1[i2];
      for (int b_i{0}; b_i < 8; b_i++) {
        i1 = ((c_i << 15) + (i << 3)) + b_i;
        f1 = fv71[i1];
        f2 = std::exp(f1 - f3);
        fv73[i1] = f2;
        f += f2;
        b = (!(f1 == rtMinusInfF) || b);
      }

      bv1[i2] = b;
      fv51[i2] = f;
      for (int b_i{0}; b_i < 8; b_i++) {
        if (b) {
          i1 = ((c_i << 15) + (i << 3)) + b_i;
          fv73[i1] *= 1.0F / fv51[i2];
        } else {
          fv73[((c_i << 15) + (i << 3)) + b_i] = 0.0F;
        }
      }
    }
  }

  for (int b_i{0}; b_i < 8; b_i++) {
    matrixMultiply12417453134711121340(16, 8, 4096, 128, 128, 128, &fv50[b_i <<
      7], &fv73[b_i << 15], &fv168[0]);
    std::copy(&fv168[0], &fv168[65536], &fv63[b_i * 65536]);
  }

  for (int b_i{0}; b_i < 4096; b_i++) {
    for (int c_i{0}; c_i < 8; c_i++) {
      std::copy(&fv63[b_i * 16 + c_i * 65536], &fv63[static_cast<int>(
                 static_cast<unsigned int>(b_i * 16 + c_i * 65536) + 16U)],
                &fv64[b_i * 128 + c_i * 16]);
    }
  }

  matrixMultiply12417453134711121340(256, 128, 4096, 128, 128, 128,
    &__constant_128x256xf32_209[0], &fv64[0], &fv169[0]);
  for (int b_i{0}; b_i < 4096; b_i++) {
    for (int c_i{0}; c_i < 256; c_i++) {
      i1 = (b_i << 8) + c_i;
      fv169[i1] += __constant_1x256xf32_87[c_i];
    }
  }

  for (int b_i{0}; b_i < 256; b_i++) {
    for (int c_i{0}; c_i < 4096; c_i++) {
      i1 = (b_i << 12) + c_i;
      fv136[i1] += fv169[(c_i << 8) + b_i];
    }
  }

  for (int b_i{0}; b_i < 4096; b_i++) {
    for (int c_i{0}; c_i < 256; c_i++) {
      fv160[(b_i << 8) + c_i] = fv136[(c_i << 12) + b_i];
    }
  }

  for (int b_i{0}; b_i < 1048576; b_i++) {
    dv23[b_i] = fv160[b_i];
  }

  for (int c_i{0}; c_i < 4096; c_i++) {
    d = dv13[c_i];
    for (int b_i{0}; b_i < 256; b_i++) {
      d += dv23[(c_i << 8) + b_i];
    }

    dv13[c_i] = d;
    d1 = dv11[c_i];
    f = fv35[c_i];
    for (int b_i{0}; b_i < 256; b_i++) {
      i1 = (c_i << 8) + b_i;
      d2 = dv23[i1] - d * 0.00390625;
      d1 += d2 * d2;
      f += fv160[i1];
    }

    fv35[c_i] = f;
    dv11[c_i] = d1;
  }

  for (int b_i{0}; b_i < 256; b_i++) {
    f = __constant_1x256x1xf32_162[b_i];
    f1 = __constant_1x256x1xf32_163[b_i];
    for (int c_i{0}; c_i < 4096; c_i++) {
      i1 = (b_i << 12) + c_i;
      fv136[i1] = (fv136[i1] - fv35[c_i] * 0.00390625F) * (1.0F / std::sqrt(
        static_cast<float>(dv11[c_i] * 0.00390625) + 1.0E-5F)) * f + f1;
    }
  }

  for (int b_i{0}; b_i < 4096; b_i++) {
    for (int c_i{0}; c_i < 256; c_i++) {
      i1 = (c_i << 12) + b_i;
      f = fv136[i1];
      i3 = (b_i << 8) + c_i;
      fv147[i3] = f;
      fv160[i3] = f + fv132[i1];
    }
  }

  matrixMultiply12417453134711121340(128, 256, 8, 128, 128, 128,
    &__constant_256x128xf32_210[0], &fv152[0], &fv161[0]);
  for (int b_i{0}; b_i < 8; b_i++) {
    for (int c_i{0}; c_i < 128; c_i++) {
      i1 = (b_i << 7) + c_i;
      fv161[i1] += __constant_1x128xf32_88[c_i];
    }
  }

  matrixMultiply12417453134711121340(128, 256, 4096, 128, 128, 128,
    &__constant_256x128xf32_211[0], &fv160[0], &fv146[0]);
  for (int b_i{0}; b_i < 4096; b_i++) {
    for (int c_i{0}; c_i < 128; c_i++) {
      i1 = (b_i << 7) + c_i;
      fv63[i1] = fv146[i1] + __constant_1x128xf32_89[c_i];
    }
  }

  matrixMultiply12417453134711121340(128, 256, 4096, 128, 128, 128,
    &__constant_256x128xf32_212[0], &fv147[0], &fv146[0]);
  for (int b_i{0}; b_i < 4096; b_i++) {
    for (int c_i{0}; c_i < 128; c_i++) {
      i1 = (b_i << 7) + c_i;
      fv146[i1] += __constant_1x128xf32_90[c_i];
    }
  }

  for (int i{0}; i < 8; i++) {
    for (int b_i{0}; b_i < 4096; b_i++) {
      std::copy(&fv146[i * 16 + b_i * 128], &fv146[static_cast<int>(static_cast<
                 unsigned int>(i * 16 + b_i * 128) + 16U)], &fv64[i * 65536 +
                b_i * 16]);
    }

    for (int b_i{0}; b_i < 8; b_i++) {
      for (int c_i{0}; c_i < 16; c_i++) {
        fv50[((i << 7) + (b_i << 4)) + c_i] = fv161[((b_i << 7) + (i << 4)) +
          c_i] * 0.5F;
      }
    }

    for (int b_i{0}; b_i < 16; b_i++) {
      for (int c_i{0}; c_i < 4096; c_i++) {
        fv162[((i << 16) + (b_i << 12)) + c_i] = fv63[((c_i << 7) + (i << 4)) +
          b_i] * 0.5F;
      }
    }
  }

  for (int b_i{0}; b_i < 8; b_i++) {
    matrixMultiply4454328187142109130(4096, 16, 8, 128, 128, 128, &fv162[b_i <<
      16], &fv50[b_i << 7], &fv163[0]);
    std::copy(&fv163[0], &fv163[32768], &fv71[b_i * 32768]);
  }

  for (int c_i{0}; c_i < 8; c_i++) {
    for (int i{0}; i < 8; i++) {
      i2 = (c_i << 3) + i;
      f3 = fv72[i2];
      for (int b_i{0}; b_i < 4096; b_i++) {
        f = fv71[((c_i << 15) + (i << 12)) + b_i];
        if (!(f3 != f3) && ((f != f) || (f > f3))) {
          f3 = f;
        }
      }

      fv72[i2] = f3;
      f = fv155[i2];
      b = bv9[i2];
      for (int b_i{0}; b_i < 4096; b_i++) {
        i1 = ((c_i << 15) + (i << 12)) + b_i;
        f1 = fv71[i1];
        f2 = std::exp(f1 - f3);
        fv73[i1] = f2;
        f += f2;
        b = (!(f1 == rtMinusInfF) || b);
      }

      bv9[i2] = b;
      fv155[i2] = f;
      for (int b_i{0}; b_i < 4096; b_i++) {
        if (b) {
          i1 = ((c_i << 15) + (i << 12)) + b_i;
          fv73[i1] *= 1.0F / fv155[i2];
        } else {
          fv73[((c_i << 15) + (i << 12)) + b_i] = 0.0F;
        }
      }
    }
  }

  for (int b_i{0}; b_i < 8; b_i++) {
    matrixMultiply12417453134711121340(16, 4096, 8, 128, 128, 128, &fv64[b_i <<
      16], &fv73[b_i << 15], &fv165[0]);
    std::copy(&fv165[0], &fv165[128], &fv120[b_i * 128]);
  }

  for (int b_i{0}; b_i < 8; b_i++) {
    for (int c_i{0}; c_i < 8; c_i++) {
      std::copy(&fv120[b_i * 16 + c_i * 128], &fv120[static_cast<int>(
                 static_cast<unsigned int>(b_i * 16 + c_i * 128) + 16U)],
                &fv50[b_i * 128 + c_i * 16]);
    }
  }

  matrixMultiply12417453134711121340(256, 128, 8, 128, 128, 128,
    &__constant_128x256xf32_213[0], &fv50[0], &fv150[0]);
  for (int b_i{0}; b_i < 8; b_i++) {
    for (int c_i{0}; c_i < 256; c_i++) {
      i1 = (b_i << 8) + c_i;
      fv150[i1] += __constant_1x256xf32_91[c_i];
    }
  }

  for (int b_i{0}; b_i < 2048; b_i++) {
    f = fv151[b_i] + fv150[b_i];
    fv152[b_i] = f;
    dv20[b_i] = f;
  }

  for (int c_i{0}; c_i < 8; c_i++) {
    d = dv22[c_i];
    for (int b_i{0}; b_i < 256; b_i++) {
      d += dv20[(c_i << 8) + b_i];
    }

    dv22[c_i] = d;
    d1 = dv21[c_i];
    f = fv159[c_i];
    for (int b_i{0}; b_i < 256; b_i++) {
      i1 = (c_i << 8) + b_i;
      d2 = dv20[i1] - d * 0.00390625;
      d1 += d2 * d2;
      f += fv152[i1];
    }

    fv159[c_i] = f;
    dv21[c_i] = d1;
    for (int b_i{0}; b_i < 256; b_i++) {
      i1 = (c_i << 8) + b_i;
      fv152[i1] = (fv152[i1] - f * 0.00390625F) * (1.0F / std::sqrt(static_cast<
        float>(d1 * 0.00390625) + 1.0E-5F)) * __constant_1x1x256xf32_92[b_i] +
        __constant_1x1x256xf32_93[b_i];
    }
  }

  for (int b_i{0}; b_i < 64; b_i++) {
    for (int c_i{0}; c_i < 256; c_i++) {
      i1 = (c_i << 8) + (b_i << 2);
      i3 = (b_i << 10) + (c_i << 2);
      fv31[i3] = __constant_256x64x2x2xf32[i1 + 3];
      fv31[i3 + 1] = __constant_256x64x2x2xf32[i1 + 2];
      fv31[i3 + 2] = __constant_256x64x2x2xf32[i1 + 1];
      fv31[i3 + 3] = __constant_256x64x2x2xf32[i1];
    }
  }

  std::memset(&fv171[0], 0, 4260096U * sizeof(float));
  for (int b_i{0}; b_i < 256; b_i++) {
    for (int c_i{0}; c_i < 64; c_i++) {
      for (int i{0}; i < 64; i++) {
        fv171[((16641 * b_i + 258 * c_i) + (i << 1)) + 130] = fv136[((b_i << 12)
          + (c_i << 6)) + i];
      }
    }
  }

  for (int b_i{0}; b_i < 64; b_i++) {
    for (int c_i{0}; c_i < 128; c_i++) {
      for (int i{0}; i < 128; i++) {
        fv132[((b_i << 14) + (c_i << 7)) + i] = __constant_64xf32[b_i];
      }
    }
  }

  for (int c_i{0}; c_i < 64; c_i++) {
    for (int i{0}; i < 128; i++) {
      for (int f_i{0}; f_i < 128; f_i++) {
        i1 = ((c_i << 14) + (i << 7)) + f_i;
        for (int e_i{0}; e_i < 256; e_i++) {
          i2 = (16641 * e_i + 129 * i) + f_i;
          i3 = (c_i << 10) + (e_i << 2);
          i4 = (16641 * e_i + 129 * (i + 1)) + f_i;
          fv132[i1] = (((fv132[i1] + fv171[i2] * fv31[i3]) + fv171[i2 + 1] *
                        fv31[i3 + 1]) + fv171[i4] * fv31[i3 + 2]) + fv171[i4 + 1]
            * fv31[i3 + 3];
        }
      }
    }
  }

  for (int b_i{0}; b_i < 64; b_i++) {
    i1 = b_i << 14;
    for (int c_i{0}; c_i < 128; c_i++) {
      for (int i{0}; i < 128; i++) {
        i3 = (i1 + (c_i << 7)) + i;
        fv132[i3] += fv131[(i1 + (i << 7)) + c_i];
      }
    }
  }

  std::memset(&fv98[0], 0, 16384U * sizeof(float));
  for (int b_i{0}; b_i < 64; b_i++) {
    for (int c_i{0}; c_i < 16384; c_i++) {
      fv98[c_i] += fv132[c_i + (b_i << 14)];
    }
  }

  for (int b_i{0}; b_i < 64; b_i++) {
    for (int c_i{0}; c_i < 16384; c_i++) {
      i1 = c_i + (b_i << 14);
      f = fv132[i1] - fv98[c_i] * 0.015625F;
      fv132[i1] = f;
      fv57[c_i] += rt_powf_snf(f, 2.0F);
    }
  }

  for (int b_i{0}; b_i < 64; b_i++) {
    f4 = __constant_1x64x1x1xf32[b_i];
    unnamed_idx_1 = __constant_1x64x1x1xf32_107[b_i];
    for (int c_i{0}; c_i < 128; c_i++) {
      i1 = c_i << 7;
      for (int i{0}; i < 128; i++) {
        i3 = ((b_i << 14) + i1) + i;
        unnamed_idx_0 = fv132[i3] * (1.0F / rt_powf_snf(fv57[i1 + i] * 0.015625F
          + 1.0E-6F, 0.5F)) * f4 + unnamed_idx_1;
        f = unnamed_idx_0 * 0.70710677F;
        b = (f < 0.0F);
        if (b) {
          f = -f;
        }

        b1 = (f < 0.8F);
        b2 = (f < 2.0F);
        if ((f != f) || (f < 3.75F)) {
          if (b2) {
            if (b1) {
              f1 = 0.02581468F;
              f2 = 0.20974171F;
              f3 = -0.52301854F;
              f5 = 1.1283791F;
            } else {
              f1 = 0.037064552F;
              f2 = 0.1184074F;
              f3 = -0.36472142F;
              f5 = 1.1275069F;
            }

            f6 = 0.0F;
            if (b1) {
              f7 = 0.073979646F;
              f8 = -0.13180897F;
              f9 = 0.5192301F;
              f10 = -0.46351382F;
            } else {
              f7 = 0.05724428F;
              f8 = -0.088346265F;
              f9 = 0.4483691F;
              f10 = -0.327607F;
            }
          } else {
            f1 = -1.7104803E-5F;
            f2 = 0.0002534471F;
            f3 = -0.0014137363F;
            f5 = 0.0035196193F;
            f6 = -0.0033009306F;
            f7 = 0.08219089F;
            f8 = -0.5833899F;
            f9 = 1.6270593F;
            f10 = -2.0606916F;
          }

          f = static_cast<float>(!b2) + (f * (f * (f * (f * f1 + f2) + f3) + f5)
            + f6) / (f * (f * (f * (f * f7 + f8) + f9) + f10) + 1.0F);
        } else {
          f = 1.0F;
        }

        if (b) {
          f = -f;
        }

        fv132[i3] = unnamed_idx_0 * ((f + 1.0F) * 0.5F);
      }
    }
  }

  for (int b_i{0}; b_i < 32; b_i++) {
    for (int c_i{0}; c_i < 64; c_i++) {
      i1 = (c_i << 7) + (b_i << 2);
      i3 = (b_i << 8) + (c_i << 2);
      fv143[i3] = __constant_64x32x2x2xf32[i1 + 3];
      fv143[i3 + 1] = __constant_64x32x2x2xf32[i1 + 2];
      fv143[i3 + 2] = __constant_64x32x2x2xf32[i1 + 1];
      fv143[i3 + 3] = __constant_64x32x2x2xf32[i1];
    }
  }

  std::memset(&fv172[0], 0, 4227136U * sizeof(float));
  for (int b_i{0}; b_i < 64; b_i++) {
    for (int c_i{0}; c_i < 128; c_i++) {
      for (int i{0}; i < 128; i++) {
        fv172[((66049 * b_i + 514 * c_i) + (i << 1)) + 258] = fv132[((b_i << 14)
          + (c_i << 7)) + i];
      }
    }
  }

  for (int b_i{0}; b_i < 32; b_i++) {
    for (int c_i{0}; c_i < 256; c_i++) {
      for (int i{0}; i < 256; i++) {
        fv48[((b_i << 16) + (c_i << 8)) + i] = __constant_32xf32[b_i];
      }
    }
  }

  for (int c_i{0}; c_i < 32; c_i++) {
    for (int i{0}; i < 256; i++) {
      for (int f_i{0}; f_i < 256; f_i++) {
        i1 = ((c_i << 16) + (i << 8)) + f_i;
        for (int e_i{0}; e_i < 64; e_i++) {
          i2 = (66049 * e_i + 257 * i) + f_i;
          i3 = (c_i << 8) + (e_i << 2);
          i4 = (66049 * e_i + 257 * (i + 1)) + f_i;
          fv48[i1] = (((fv48[i1] + fv172[i2] * fv143[i3]) + fv172[i2 + 1] *
                       fv143[i3 + 1]) + fv172[i4] * fv143[i3 + 2]) + fv172[i4 +
            1] * fv143[i3 + 3];
        }
      }
    }
  }

  for (int b_i{0}; b_i < 32; b_i++) {
    i1 = b_i << 16;
    for (int c_i{0}; c_i < 256; c_i++) {
      for (int i{0}; i < 256; i++) {
        i3 = (i1 + (c_i << 8)) + i;
        f4 = fv48[i3] + fv135[(i1 + (i << 8)) + c_i];
        f = f4 * 0.70710677F;
        b = (f < 0.0F);
        if (b) {
          f = -f;
        }

        b1 = (f < 0.8F);
        b2 = (f < 2.0F);
        if ((f != f) || (f < 3.75F)) {
          if (b2) {
            if (b1) {
              f1 = 0.02581468F;
              f2 = 0.20974171F;
              f3 = -0.52301854F;
              f5 = 1.1283791F;
            } else {
              f1 = 0.037064552F;
              f2 = 0.1184074F;
              f3 = -0.36472142F;
              f5 = 1.1275069F;
            }

            f6 = 0.0F;
            if (b1) {
              f7 = 0.073979646F;
              f8 = -0.13180897F;
              f9 = 0.5192301F;
              f10 = -0.46351382F;
            } else {
              f7 = 0.05724428F;
              f8 = -0.088346265F;
              f9 = 0.4483691F;
              f10 = -0.327607F;
            }
          } else {
            f1 = -1.7104803E-5F;
            f2 = 0.0002534471F;
            f3 = -0.0014137363F;
            f5 = 0.0035196193F;
            f6 = -0.0033009306F;
            f7 = 0.08219089F;
            f8 = -0.5833899F;
            f9 = 1.6270593F;
            f10 = -2.0606916F;
          }

          f = static_cast<float>(!b2) + (f * (f * (f * (f * f1 + f2) + f3) + f5)
            + f6) / (f * (f * (f * (f * f7 + f8) + f9) + f10) + 1.0F);
        } else {
          f = 1.0F;
        }

        if (b) {
          f = -f;
        }

        fv48[i3] = f4 * ((f + 1.0F) * 0.5F);
      }
    }
  }

  matrixMultiply4117173156653932373(256, 256, 1, 128, 128, 128,
    &__constant_256x256xf32_214[0], &fv152[512], &fv173[0]);
  for (int b_i{0}; b_i < 256; b_i++) {
    f = fv173[b_i] + __constant_1x256xf32_94[b_i];
    if (!(f != f) && !(f < 3.402823466E+38F)) {
      f = 3.402823466E+38F;
    }

    if ((f != f) || (f > 0.0F)) {
      fv7[b_i] = f;
    } else {
      fv7[b_i] = 0.0F;
    }
  }

  matrixMultiply4117173156653932373(256, 256, 1, 128, 128, 128,
    &__constant_256x256xf32_215[0], &fv7[0], &fv173[0]);
  for (int b_i{0}; b_i < 256; b_i++) {
    f = fv173[b_i] + __constant_1x256xf32_95[b_i];
    if (!(f != f) && !(f < 3.402823466E+38F)) {
      f = 3.402823466E+38F;
    }

    if ((f != f) || (f > 0.0F)) {
      fv173[b_i] = f;
    } else {
      fv173[b_i] = 0.0F;
    }
  }

  matrixMultiply4117173156653932373(32, 256, 1, 128, 128, 128,
    &__constant_256x32xf32[0], &fv173[0], &fv174[0]);
  for (int b_i{0}; b_i < 32; b_i++) {
    fv175[b_i] = fv174[b_i] + __constant_1x32xf32[b_i];
  }

  matrixMultiply4117173156653932373(256, 256, 1, 128, 128, 128,
    &__constant_256x256xf32_216[0], &fv152[768], &fv173[0]);
  for (int b_i{0}; b_i < 256; b_i++) {
    f = fv173[b_i] + __constant_1x256xf32_96[b_i];
    if (!(f != f) && !(f < 3.402823466E+38F)) {
      f = 3.402823466E+38F;
    }

    if ((f != f) || (f > 0.0F)) {
      fv7[b_i] = f;
    } else {
      fv7[b_i] = 0.0F;
    }
  }

  matrixMultiply4117173156653932373(256, 256, 1, 128, 128, 128,
    &__constant_256x256xf32_217[0], &fv7[0], &fv173[0]);
  for (int b_i{0}; b_i < 256; b_i++) {
    f = fv173[b_i] + __constant_1x256xf32_97[b_i];
    if (!(f != f) && !(f < 3.402823466E+38F)) {
      f = 3.402823466E+38F;
    }

    if ((f != f) || (f > 0.0F)) {
      fv173[b_i] = f;
    } else {
      fv173[b_i] = 0.0F;
    }
  }

  matrixMultiply4117173156653932373(32, 256, 1, 128, 128, 128,
    &__constant_256x32xf32_218[0], &fv173[0], &fv174[0]);
  for (int b_i{0}; b_i < 32; b_i++) {
    fv176[b_i] = fv174[b_i] + __constant_1x32xf32_98[b_i];
  }

  matrixMultiply4117173156653932373(256, 256, 1, 128, 128, 128,
    &__constant_256x256xf32_219[0], &fv152[1024], &fv173[0]);
  for (int b_i{0}; b_i < 256; b_i++) {
    f = fv173[b_i] + __constant_1x256xf32_99[b_i];
    if (!(f != f) && !(f < 3.402823466E+38F)) {
      f = 3.402823466E+38F;
    }

    if ((f != f) || (f > 0.0F)) {
      fv7[b_i] = f;
    } else {
      fv7[b_i] = 0.0F;
    }
  }

  matrixMultiply4117173156653932373(256, 256, 1, 128, 128, 128,
    &__constant_256x256xf32_220[0], &fv7[0], &fv173[0]);
  for (int b_i{0}; b_i < 256; b_i++) {
    f = fv173[b_i] + __constant_1x256xf32_100[b_i];
    if (!(f != f) && !(f < 3.402823466E+38F)) {
      f = 3.402823466E+38F;
    }

    if ((f != f) || (f > 0.0F)) {
      fv173[b_i] = f;
    } else {
      fv173[b_i] = 0.0F;
    }
  }

  matrixMultiply4117173156653932373(32, 256, 1, 128, 128, 128,
    &__constant_256x32xf32_221[0], &fv173[0], &fv174[0]);
  for (int b_i{0}; b_i < 32; b_i++) {
    fv177[b_i] = fv174[b_i] + __constant_1x32xf32_101[b_i];
  }

  matrixMultiply4117173156653932373(256, 256, 1, 128, 128, 128,
    &__constant_256x256xf32_222[0], &fv152[1280], &fv173[0]);
  for (int b_i{0}; b_i < 256; b_i++) {
    f = fv173[b_i] + __constant_1x256xf32_102[b_i];
    if (!(f != f) && !(f < 3.402823466E+38F)) {
      f = 3.402823466E+38F;
    }

    if ((f != f) || (f > 0.0F)) {
      fv7[b_i] = f;
    } else {
      fv7[b_i] = 0.0F;
    }
  }

  matrixMultiply4117173156653932373(256, 256, 1, 128, 128, 128,
    &__constant_256x256xf32_223[0], &fv7[0], &fv173[0]);
  for (int b_i{0}; b_i < 256; b_i++) {
    f = fv173[b_i] + __constant_1x256xf32_103[b_i];
    if (!(f != f) && !(f < 3.402823466E+38F)) {
      f = 3.402823466E+38F;
    }

    if ((f != f) || (f > 0.0F)) {
      fv173[b_i] = f;
    } else {
      fv173[b_i] = 0.0F;
    }
  }

  matrixMultiply4117173156653932373(32, 256, 1, 128, 128, 128,
    &__constant_256x32xf32_224[0], &fv173[0], &fv174[0]);
  for (int b_i{0}; b_i < 32; b_i++) {
    f = fv174[b_i] + __constant_1x32xf32_104[b_i];
    fv174[b_i] = f;
    fv178[b_i] = fv175[b_i];
    fv178[b_i + 32] = fv176[b_i];
    fv178[b_i + 64] = fv177[b_i];
    fv178[b_i + 96] = f;
  }

  matrixMultiply4454328187142109130(65536, 32, 4, 128, 128, 128, &fv48[0],
    &fv178[0], &fv179[0]);
  matrixMultiply4117173156653932373(256, 256, 1, 128, 128, 128,
    &__constant_256x256xf32_225[0], &fv152[256], &fv173[0]);
  for (int b_i{0}; b_i < 256; b_i++) {
    f = fv173[b_i] + __constant_1x256xf32_105[b_i];
    if (!(f != f) && !(f < 3.402823466E+38F)) {
      f = 3.402823466E+38F;
    }

    if ((f != f) || (f > 0.0F)) {
      fv7[b_i] = f;
    } else {
      fv7[b_i] = 0.0F;
    }
  }

  matrixMultiply4117173156653932373(256, 256, 1, 128, 128, 128,
    &__constant_256x256xf32_226[0], &fv7[0], &fv173[0]);
  for (int b_i{0}; b_i < 256; b_i++) {
    f = fv173[b_i] + __constant_1x256xf32_106[b_i];
    if (!(f != f) && !(f < 3.402823466E+38F)) {
      f = 3.402823466E+38F;
    }

    if ((f != f) || (f > 0.0F)) {
      fv173[b_i] = f;
    } else {
      fv173[b_i] = 0.0F;
    }
  }

  matrixMultiply7373063509845396750(4, 256, 1, 128, 128, 128,
    &__constant_256x4xf32[0], &fv173[0], &fv180[0]);
  fv180[0] = 1.0F / (std::exp(-(fv180[0] + __constant_1x4xf32[0])) + 1.0F);
  fv180[1] = 1.0F / (std::exp(-(fv180[1] + __constant_1x4xf32[1])) + 1.0F);
  fv180[2] = 1.0F / (std::exp(-(fv180[2] + __constant_1x4xf32[2])) + 1.0F);
  fv180[3] = 1.0F / (std::exp(-(fv180[3] + __constant_1x4xf32[3])) + 1.0F);
  for (int b_i{0}; b_i < 1200; b_i++) {
    f = (static_cast<float>(__constant_1200x1xi64[b_i]) + 0.5F) * 0.21333334F -
      0.5F;
    if (!(f > 0.0F)) {
      f = 0.0F;
    }

    fv181[b_i] = f;
    if (f < 0.0F) {
      f = std::ceil(f);
    } else {
      f = std::floor(f);
    }

    iv20[b_i] = static_cast<long>(f);
    iv21[b_i] = static_cast<int>(static_cast<long>(f));
  }

  for (int b_i{0}; b_i < 1800; b_i++) {
    f = (static_cast<float>(__constant_1800xi64[b_i]) + 0.5F) * 0.14222223F -
      0.5F;
    if (!(f > 0.0F)) {
      f = 0.0F;
    }

    fv182[b_i] = f;
    if (f < 0.0F) {
      f = std::ceil(f);
    } else {
      f = std::floor(f);
    }

    iv22[b_i] = static_cast<long>(f);
    iv23[b_i] = static_cast<int>(static_cast<long>(f));
  }

  for (int c_i{0}; c_i < 3; c_i++) {
    d_i = __constant_1x3x1x1x1xi64[c_i];
    if (static_cast<int>(d_i) < 0) {
      i3 = static_cast<int>(d_i) + 3;
    } else {
      i3 = static_cast<int>(d_i);
    }

    for (int i{0}; i < 1200; i++) {
      if (iv21[i] < 0) {
        i4 = iv21[i] + 256;
      } else {
        i4 = iv21[i];
      }

      for (int f_i{0}; f_i < 1800; f_i++) {
        if (iv23[f_i] < 0) {
          i5 = iv23[f_i] + 256;
        } else {
          i5 = iv23[f_i];
        }

        iv25[(2160000 * c_i + 1800 * i) + f_i] = i5;
        i1 = f_i << 2;
        i2 = (8640000 * c_i + 7200 * i) + i1;
        iv29[i2] = 0;
        iv29[i2 + 1] = i3;
        i1 = (i1 + 7200 * i) + 8640000 * c_i;
        iv26[i1] = 0;
        iv26[i1 + 1] = i3;
        iv26[i1 + 3] = iv29[i1 + 3];
        iv26[i2 + 2] = i4;
        iv27[i1] = 0;
        iv27[i1 + 1] = i3;
        iv27[i1 + 2] = i4;
        iv27[i2 + 3] = i5;
      }
    }
  }

  i1 = __constant_1x4xi32_109[3];
  i2 = __constant_1x4xi32_109[2];
  i3 = __constant_1x4xi32_109[1];
  i4 = __constant_1x4xi32_109[0];
  for (int c_i{0}; c_i < 6480000; c_i++) {
    iv24[c_i] = 0;
    i5 = c_i << 2;
    fv[c_i] = fv179[(((iv27[i5 + 3] * i1 + iv27[i5 + 2] * i2) + iv27[i5 + 1] *
                      i3) + iv27[i5] * i4) + 65536];
  }

  for (int b_i{0}; b_i < 3; b_i++) {
    for (int c_i{0}; c_i < 1200; c_i++) {
      for (int i{0}; i < 1800; i++) {
        if (iv23[i] + 1 < 255) {
          i1 = iv23[i] + 1;
        } else {
          i1 = 255;
        }

        if (i1 < 0) {
          i1 += 256;
        }

        iv28[(2160000 * b_i + 1800 * c_i) + i] = i1;
        iv26[((8640000 * b_i + 7200 * c_i) + (i << 2)) + 3] = i1;
      }
    }
  }

  i1 = __constant_1x4xi32_109[3];
  i2 = __constant_1x4xi32_109[2];
  i3 = __constant_1x4xi32_109[1];
  i4 = __constant_1x4xi32_109[0];
  for (int c_i{0}; c_i < 6480000; c_i++) {
    i5 = c_i << 2;
    fv183[c_i] = fv179[(((iv26[i5 + 3] * i1 + iv26[i5 + 2] * i2) + iv26[i5 + 1] *
                         i3) + iv26[i5] * i4) + 65536];
  }

  for (int c_i{0}; c_i < 3; c_i++) {
    for (int i{0}; i < 1200; i++) {
      if (iv21[i] + 1 < 255) {
        i2 = iv21[i] + 1;
      } else {
        i2 = 255;
      }

      if (i2 < 0) {
        i2 += 256;
      }

      for (int f_i{0}; f_i < 1800; f_i++) {
        i1 = f_i << 2;
        i3 = (8640000 * c_i + 7200 * i) + i1;
        iv29[i3 + 2] = i2;
        i1 = (i1 + 7200 * i) + 8640000 * c_i;
        iv26[i1] = iv29[i1];
        iv26[i1 + 1] = iv29[i1 + 1];
        iv26[i1 + 2] = i2;
        iv26[i3 + 3] = iv25[(2160000 * c_i + 1800 * i) + f_i];
      }
    }
  }

  i1 = __constant_1x4xi32_109[3];
  i2 = __constant_1x4xi32_109[2];
  i3 = __constant_1x4xi32_109[1];
  i4 = __constant_1x4xi32_109[0];
  for (int c_i{0}; c_i < 6480000; c_i++) {
    i5 = c_i << 2;
    fv184[c_i] = fv179[(((iv26[i5 + 3] * i1 + iv26[i5 + 2] * i2) + iv26[i5 + 1] *
                         i3) + iv26[i5] * i4) + 65536];
  }

  for (int b_i{0}; b_i < 3; b_i++) {
    for (int c_i{0}; c_i < 1200; c_i++) {
      for (int i{0}; i < 1800; i++) {
        iv29[((8640000 * b_i + 7200 * c_i) + (i << 2)) + 3] = iv28[(2160000 *
          b_i + 1800 * c_i) + i];
      }
    }
  }

  i2 = __constant_1x4xi32_109[3];
  i3 = __constant_1x4xi32_109[2];
  i4 = __constant_1x4xi32_109[1];
  i5 = __constant_1x4xi32_109[0];
  for (int c_i{0}; c_i < 6480000; c_i++) {
    i1 = c_i << 2;
    i1 = (((iv29[i1 + 3] * i2 + iv29[i1 + 2] * i3) + iv29[i1 + 1] * i4) +
          iv29[i1] * i5) + iv24[c_i];
    iv24[c_i] = i1;
    fv185[c_i] = fv179[i1 + 65536];
  }

  for (int b_i{0}; b_i < 3; b_i++) {
    for (int c_i{0}; c_i < 1200; c_i++) {
      f2 = fv181[c_i] - static_cast<float>(iv20[c_i]);
      if (!(f2 < 1.0F)) {
        f2 = 1.0F;
      }

      for (int i{0}; i < 1800; i++) {
        i1 = (2160000 * b_i + 1800 * c_i) + i;
        f = fv[i1];
        f3 = fv184[i1];
        f5 = fv182[i] - static_cast<float>(iv22[i]);
        if (!(f5 < 1.0F)) {
          f5 = 1.0F;
        }

        if (!(f5 > 0.0F)) {
          f5 = 0.0F;
        }

        f += (fv183[i1] - f) * f5;
        if (f2 > 0.0F) {
          f1 = f2;
        } else {
          f1 = 0.0F;
        }

        bv11[i1] = (f + ((f3 + (fv185[i1] - f3) * f5) - f) * f1 > 0.0F);
      }
    }

    iv30[b_i] = b_i;
    out_1[b_i] = fv180[b_i + 1];
  }

  f = out_1[0];
  f1 = out_1[1];
  f2 = out_1[2];
  for (int b_i{0}; b_i < 3; b_i++) {
    f3 = f;
    d_i = iv30[0];
    if (!(f >= f1)) {
      f = f1;
      f1 = f3;
      iv30[0] = iv30[1];
      iv30[1] = d_i;
    }

    f3 = f1;
    d_i = iv30[1];
    if (!(f1 >= f2)) {
      f1 = f2;
      f2 = f3;
      iv30[1] = iv30[2];
      iv30[2] = d_i;
    }
  }

  for (int b_i{0}; b_i < 3; b_i++) {
    signed char i9;
    d_i = iv30[b_i];
    iv31[b_i] = static_cast<signed char>(d_i);
    out_1[b_i] = fv180[static_cast<int>(d_i) + 1];
    i9 = iv31[b_i];
    for (int c_i{0}; c_i < 1200; c_i++) {
      i1 = c_i * 1800;
      std::copy(&bv11[i9 * 2160000 + i1], &bv11[static_cast<int>(static_cast<
                 unsigned int>(i9 * 2160000 + i1) + 1800U)], &out_0[b_i *
                2160000 + c_i * 1800]);
    }
  }
}

//
// Arguments    : int M
//                int K
//                int N
//                int blockSizeM
//                int blockSizeK
//                int blockSizeN
//                const float *A
//                const float *B
//                float *C
// Return Type  : void
//
static void matrixMultiply12417453134711121340(int M, int K, int N, int
  blockSizeM, int blockSizeK, int blockSizeN, const float *A, const float *B,
  float *C)
{
  int i0_ub;
  int k0_ub;
  std::memset(C, 0, static_cast<unsigned int>(M * N * static_cast<int>(sizeof
    (float))));
  if (blockSizeM >= M) {
    blockSizeM = M;
  } else {
    blockSizeM = (blockSizeM >> 1) << 1;
    if (blockSizeM <= 0) {
      blockSizeM = 1;
    }
  }

  if (blockSizeN >= N) {
    blockSizeN = N;
  } else {
    blockSizeN = (blockSizeN >> 2) << 2;
    if (blockSizeN <= 0) {
      blockSizeN = 1;
    }
  }

  i0_ub = div_s32_floor(M - 1, blockSizeM) + 1;
  k0_ub = div_s32_floor(K - 1, blockSizeK) + 1;
  for (int b_j1{0}; b_j1 < N; b_j1 += blockSizeN) {
    int N2;
    if (b_j1 > N - blockSizeN) {
      N2 = N - b_j1;
    } else {
      N2 = blockSizeN;
    }

    for (int k0{1}; k0 <= k0_ub; k0++) {
      int K2;
      int k;
      k = (k0 - 1) * blockSizeK;
      if (k > K - blockSizeK) {
        K2 = K - k;
      } else {
        K2 = blockSizeK;
      }

      for (int i0{1}; i0 <= i0_ub; i0++) {
        int b_i;
        int i;
        i = (i0 - 1) * blockSizeM;
        if (i > M - blockSizeM) {
          b_i = M - i;
        } else {
          b_i = blockSizeM;
        }

        macroKernel12417453134711121340(b_i, K2, N2, &A[i + M * k], M, &B[k + K *
          b_j1], K, &C[i + M * b_j1], M);
      }
    }
  }
}

//
// Arguments    : int M
//                int K
//                int N
//                int blockSizeM
//                int blockSizeK
//                int blockSizeN
//                const float *A
//                const float *B
//                float *C
// Return Type  : void
//
static void matrixMultiply4117173156653932373(int M, int K, int N, int
  blockSizeM, int blockSizeK, int blockSizeN, const float *A, const float *B,
  float *C)
{
  int i0_ub;
  int k0_ub;
  std::memset(C, 0, static_cast<unsigned int>(M * N * static_cast<int>(sizeof
    (float))));
  if (blockSizeM >= M) {
    blockSizeM = M;
  } else {
    blockSizeM = div_nde_s32_floor() * 7;
    if (blockSizeM <= 0) {
      blockSizeM = 1;
    }
  }

  if (blockSizeN >= N) {
    blockSizeN = N;
  } else if (blockSizeN <= 0) {
    blockSizeN = 1;
  }

  i0_ub = div_s32_floor(M - 1, blockSizeM) + 1;
  k0_ub = div_s32_floor(K - 1, blockSizeK) + 1;
  for (int b_j1{0}; b_j1 < N; b_j1 += blockSizeN) {
    int N2;
    if (b_j1 > N - blockSizeN) {
      N2 = N - b_j1;
    } else {
      N2 = blockSizeN;
    }

    for (int k0{1}; k0 <= k0_ub; k0++) {
      int K2;
      int k;
      k = (k0 - 1) * blockSizeK;
      if (k > K - blockSizeK) {
        K2 = K - k;
      } else {
        K2 = blockSizeK;
      }

      for (int i0{1}; i0 <= i0_ub; i0++) {
        int b_i;
        int i;
        i = (i0 - 1) * blockSizeM;
        if (i > M - blockSizeM) {
          b_i = M - i;
        } else {
          b_i = blockSizeM;
        }

        macroKernel4117173156653932373(b_i, K2, N2, &A[i + M * k], M, &B[k + K *
          b_j1], K, &C[i + M * b_j1], M);
      }
    }
  }
}

//
// Arguments    : int M
//                int K
//                int N
//                int blockSizeM
//                int blockSizeK
//                int blockSizeN
//                const float *A
//                const float *B
//                float *C
// Return Type  : void
//
static void matrixMultiply4454328187142109130(int M, int K, int N, int
  blockSizeM, int blockSizeK, int blockSizeN, const float *A, const float *B,
  float *C)
{
  float *bufferA;
  int i0_ub;
  int k0_ub;
  std::memset(C, 0, static_cast<unsigned int>(M * N * static_cast<int>(sizeof
    (float))));
  if (blockSizeM >= M) {
    blockSizeM = M;
  } else {
    blockSizeM = (blockSizeM >> 1) << 1;
    if (blockSizeM <= 0) {
      blockSizeM = 1;
    }
  }

  if (blockSizeN >= N) {
    blockSizeN = N;
  } else {
    blockSizeN = (blockSizeN >> 2) << 2;
    if (blockSizeN <= 0) {
      blockSizeN = 1;
    }
  }

  i0_ub = div_s32_floor(M - 1, blockSizeM) + 1;
  k0_ub = div_s32_floor(K - 1, blockSizeK) + 1;
  bufferA = static_cast<float *>(std::malloc(static_cast<unsigned int>
    (blockSizeM * blockSizeK * static_cast<int>(sizeof(float)))));
  for (int b_j1{0}; b_j1 < N; b_j1 += blockSizeN) {
    int N2;
    if (b_j1 > N - blockSizeN) {
      N2 = N - b_j1;
    } else {
      N2 = blockSizeN;
    }

    for (int k0{1}; k0 <= k0_ub; k0++) {
      int K2;
      int k;
      k = (k0 - 1) * blockSizeK;
      if (k > K - blockSizeK) {
        K2 = K - k;
      } else {
        K2 = blockSizeK;
      }

      for (int i0{1}; i0 <= i0_ub; i0++) {
        int M2;
        int i;
        i = (i0 - 1) * blockSizeM;
        if (i > M - blockSizeM) {
          M2 = M - i;
        } else {
          M2 = blockSizeM;
        }

        packA4454328187142109130(M2, K2, &A[i + M * k], &bufferA[0], M);
        macroKernel4454328187142109130(M2, K2, N2, &bufferA[0], M, &B[k + K *
          b_j1], K, &C[i + M * b_j1], M);
      }
    }
  }

  std::free(bufferA);
}

//
// Arguments    : int M
//                int K
//                int N
//                int blockSizeM
//                int blockSizeK
//                int blockSizeN
//                const float *A
//                const float *B
//                float *C
// Return Type  : void
//
static void matrixMultiply7373063509845396750(int M, int K, int N, int
  blockSizeM, int blockSizeK, int blockSizeN, const float *A, const float *B,
  float *C)
{
  int i0_ub;
  int k0_ub;
  std::memset(C, 0, static_cast<unsigned int>(M * N * static_cast<int>(sizeof
    (float))));
  if (blockSizeM >= M) {
    blockSizeM = M;
  } else {
    blockSizeM = (blockSizeM >> 2) << 2;
    if (blockSizeM <= 0) {
      blockSizeM = 1;
    }
  }

  if (blockSizeN >= N) {
    blockSizeN = N;
  } else if (blockSizeN <= 0) {
    blockSizeN = 1;
  }

  i0_ub = div_s32_floor(M - 1, blockSizeM) + 1;
  k0_ub = div_s32_floor(K - 1, blockSizeK) + 1;
  for (int b_j1{0}; b_j1 < N; b_j1 += blockSizeN) {
    int N2;
    if (b_j1 > N - blockSizeN) {
      N2 = N - b_j1;
    } else {
      N2 = blockSizeN;
    }

    for (int k0{1}; k0 <= k0_ub; k0++) {
      int K2;
      int k;
      k = (k0 - 1) * blockSizeK;
      if (k > K - blockSizeK) {
        K2 = K - k;
      } else {
        K2 = blockSizeK;
      }

      for (int i0{1}; i0 <= i0_ub; i0++) {
        int b_i;
        int i;
        i = (i0 - 1) * blockSizeM;
        if (i > M - blockSizeM) {
          b_i = M - i;
        } else {
          b_i = blockSizeM;
        }

        macroKernel7373063509845396750(b_i, K2, N2, &A[i + M * k], M, &B[k + K *
          b_j1], K, &C[i + M * b_j1], M);
      }
    }
  }
}

//
// Arguments    : const float *inputTensor
//                float *outputTensor
// Return Type  : void
//
static void maxPooling10961364285251527891(const float *inputTensor, float
  *outputTensor)
{
  for (int fusedOutputWidthAndChannelBlockIdx{0};
       fusedOutputWidthAndChannelBlockIdx < 24576;
       fusedOutputWidthAndChannelBlockIdx++) {
    int outputChannelBlockIdx;
    int outputWidthIdx;
    outputChannelBlockIdx = fusedOutputWidthAndChannelBlockIdx >> 7;
    outputWidthIdx = fusedOutputWidthAndChannelBlockIdx % 128;
    maxPoolingKernel10961364285251527891(&inputTensor[outputChannelBlockIdx <<
      16], &outputTensor[(outputWidthIdx << 7) + (outputChannelBlockIdx << 14)],
      outputWidthIdx, outputWidthIdx << 9);
  }
}

//
// Arguments    : const float *inputTensor
//                float *outputTensor
// Return Type  : void
//
static void maxPooling13753016621916862475(const float *inputTensor, float
  *outputTensor)
{
  for (int fusedOutputWidthAndChannelBlockIdx{0};
       fusedOutputWidthAndChannelBlockIdx < 24576;
       fusedOutputWidthAndChannelBlockIdx++) {
    int outputChannelBlockIdx;
    int outputWidthIdx;
    outputChannelBlockIdx = fusedOutputWidthAndChannelBlockIdx >> 5;
    outputWidthIdx = fusedOutputWidthAndChannelBlockIdx % 32;
    maxPoolingKernel13753016621916862475(&inputTensor[outputChannelBlockIdx <<
      12], &outputTensor[(outputWidthIdx << 5) + (outputChannelBlockIdx << 10)],
      outputWidthIdx, outputWidthIdx << 7);
  }
}

//
// Arguments    : const float *inputTensor
//                float *outputTensor
// Return Type  : void
//
static void maxPooling18144858745303349977(const float *inputTensor, float
  *outputTensor)
{
  for (int imageIdx{0}; imageIdx < 25; imageIdx++) {
    for (int fusedOutputWidthAndChannelBlockIdx{0};
         fusedOutputWidthAndChannelBlockIdx < 5376;
         fusedOutputWidthAndChannelBlockIdx++) {
      int outputChannelBlockIdx;
      int outputWidthIdx;
      outputChannelBlockIdx = static_cast<int>(static_cast<unsigned int>
        (fusedOutputWidthAndChannelBlockIdx) / 7U);
      outputWidthIdx = fusedOutputWidthAndChannelBlockIdx % 7;
      maxPoolingKernel18144858745303349977(&inputTensor[outputChannelBlockIdx *
        196 + imageIdx * 150528], &outputTensor[(outputWidthIdx * 7 +
        outputChannelBlockIdx * 49) + imageIdx * 37632], outputWidthIdx,
        (outputWidthIdx << 1) * 14);
    }
  }
}

//
// Arguments    : const float *inputTensor
//                float *outputTensor
// Return Type  : void
//
static void maxPooling18375657460455750414(const float *inputTensor, float
  *outputTensor)
{
  for (int fusedOutputWidthAndChannelBlockIdx{0};
       fusedOutputWidthAndChannelBlockIdx < 24576;
       fusedOutputWidthAndChannelBlockIdx++) {
    int outputChannelBlockIdx;
    int outputWidthIdx;
    outputChannelBlockIdx = fusedOutputWidthAndChannelBlockIdx >> 6;
    outputWidthIdx = fusedOutputWidthAndChannelBlockIdx % 64;
    maxPoolingKernel18375657460455750414(&inputTensor[outputChannelBlockIdx <<
      14], &outputTensor[(outputWidthIdx << 6) + (outputChannelBlockIdx << 12)],
      outputWidthIdx, outputWidthIdx << 8);
  }
}

//
// Arguments    : const float *inputTensor
//                float *outputTensor
// Return Type  : void
//
static void maxPooling2029811058482366664(const float *inputTensor, float
  *outputTensor)
{
  for (int imageIdx{0}; imageIdx < 1024; imageIdx++) {
    for (int fusedOutputWidthAndChannelBlockIdx{0};
         fusedOutputWidthAndChannelBlockIdx < 768;
         fusedOutputWidthAndChannelBlockIdx++) {
      int i;
      int outputChannelBlockIdx;
      int outputWidthIdx;
      outputChannelBlockIdx = fusedOutputWidthAndChannelBlockIdx >> 1;
      outputWidthIdx = fusedOutputWidthAndChannelBlockIdx % 2;
      i = outputWidthIdx << 1;
      maxPoolingKernel2029811058482366664(&inputTensor[(outputChannelBlockIdx <<
        4) + imageIdx * 6144], &outputTensor[(i + (outputChannelBlockIdx << 2))
        + imageIdx * 1536], outputWidthIdx, i << 2);
    }
  }
}

//
// Arguments    : const float *inputTensor
//                float *outputTensor
// Return Type  : void
//
static void maxPooling3996420485521692580(const float *inputTensor, float
  *outputTensor)
{
  for (int imageIdx{0}; imageIdx < 1024; imageIdx++) {
    for (int fusedOutputWidthAndChannelBlockIdx{0};
         fusedOutputWidthAndChannelBlockIdx < 768;
         fusedOutputWidthAndChannelBlockIdx++) {
      int outputChannelBlockIdx;
      int outputWidthIdx;
      outputChannelBlockIdx = fusedOutputWidthAndChannelBlockIdx >> 2;
      outputWidthIdx = fusedOutputWidthAndChannelBlockIdx % 4;
      maxPoolingKernel3996420485521692580(&inputTensor[(outputChannelBlockIdx <<
        6) + imageIdx * 12288], &outputTensor[((outputWidthIdx << 2) +
        (outputChannelBlockIdx << 4)) + imageIdx * 3072], outputWidthIdx,
        outputWidthIdx << 4);
    }
  }
}

//
// Arguments    : const float *inputBufferPtr
//                float *outputBufferPtr
//                int poolOutputWidthIdx
//                int startIdxWithPaddingOffsetInputTensor
// Return Type  : void
//
static void maxPoolingKernel10961364285251527891(const float *inputBufferPtr,
  float *outputBufferPtr, int, int startIdxWithPaddingOffsetInputTensor)
{
  int idxToStrideInputBufferAlongHeight;
  idxToStrideInputBufferAlongHeight = startIdxWithPaddingOffsetInputTensor;
  for (int outputHeightBlockIdx{0}; outputHeightBlockIdx < 128;
       outputHeightBlockIdx++) {
    outputBufferPtr[outputHeightBlockIdx] = std::fmax
      (inputBufferPtr[idxToStrideInputBufferAlongHeight + 257], std::fmax
       (inputBufferPtr[idxToStrideInputBufferAlongHeight + 256], std::fmax
        (inputBufferPtr[idxToStrideInputBufferAlongHeight + 1],
         inputBufferPtr[idxToStrideInputBufferAlongHeight])));
    idxToStrideInputBufferAlongHeight += 2;
  }
}

//
// Arguments    : const float *inputBufferPtr
//                float *outputBufferPtr
//                int poolOutputWidthIdx
//                int startIdxWithPaddingOffsetInputTensor
// Return Type  : void
//
static void maxPoolingKernel13753016621916862475(const float *inputBufferPtr,
  float *outputBufferPtr, int, int startIdxWithPaddingOffsetInputTensor)
{
  int idxToStrideInputBufferAlongHeight;
  idxToStrideInputBufferAlongHeight = startIdxWithPaddingOffsetInputTensor;
  for (int outputHeightBlockIdx{0}; outputHeightBlockIdx < 32;
       outputHeightBlockIdx++) {
    outputBufferPtr[outputHeightBlockIdx] = std::fmax
      (inputBufferPtr[idxToStrideInputBufferAlongHeight + 65], std::fmax
       (inputBufferPtr[idxToStrideInputBufferAlongHeight + 64], std::fmax
        (inputBufferPtr[idxToStrideInputBufferAlongHeight + 1],
         inputBufferPtr[idxToStrideInputBufferAlongHeight])));
    idxToStrideInputBufferAlongHeight += 2;
  }
}

//
// Arguments    : const float *inputBufferPtr
//                float *outputBufferPtr
//                int poolOutputWidthIdx
//                int startIdxWithPaddingOffsetInputTensor
// Return Type  : void
//
static void maxPoolingKernel18144858745303349977(const float *inputBufferPtr,
  float *outputBufferPtr, int, int startIdxWithPaddingOffsetInputTensor)
{
  int idxToStrideInputBufferAlongHeight;
  idxToStrideInputBufferAlongHeight = startIdxWithPaddingOffsetInputTensor;
  for (int outputHeightBlockIdx{0}; outputHeightBlockIdx < 7;
       outputHeightBlockIdx++) {
    outputBufferPtr[outputHeightBlockIdx] = std::fmax
      (inputBufferPtr[idxToStrideInputBufferAlongHeight + 15], std::fmax
       (inputBufferPtr[idxToStrideInputBufferAlongHeight + 14], std::fmax
        (inputBufferPtr[idxToStrideInputBufferAlongHeight + 1],
         inputBufferPtr[idxToStrideInputBufferAlongHeight])));
    idxToStrideInputBufferAlongHeight += 2;
  }
}

//
// Arguments    : const float *inputBufferPtr
//                float *outputBufferPtr
//                int poolOutputWidthIdx
//                int startIdxWithPaddingOffsetInputTensor
// Return Type  : void
//
static void maxPoolingKernel18375657460455750414(const float *inputBufferPtr,
  float *outputBufferPtr, int, int startIdxWithPaddingOffsetInputTensor)
{
  int idxToStrideInputBufferAlongHeight;
  idxToStrideInputBufferAlongHeight = startIdxWithPaddingOffsetInputTensor;
  for (int outputHeightBlockIdx{0}; outputHeightBlockIdx < 64;
       outputHeightBlockIdx++) {
    outputBufferPtr[outputHeightBlockIdx] = std::fmax
      (inputBufferPtr[idxToStrideInputBufferAlongHeight + 129], std::fmax
       (inputBufferPtr[idxToStrideInputBufferAlongHeight + 128], std::fmax
        (inputBufferPtr[idxToStrideInputBufferAlongHeight + 1],
         inputBufferPtr[idxToStrideInputBufferAlongHeight])));
    idxToStrideInputBufferAlongHeight += 2;
  }
}

//
// Arguments    : const float *inputBufferPtr
//                float *outputBufferPtr
//                int poolOutputWidthIdx
//                int startIdxWithPaddingOffsetInputTensor
// Return Type  : void
//
static void maxPoolingKernel2029811058482366664(const float *inputBufferPtr,
  float *outputBufferPtr, int, int startIdxWithPaddingOffsetInputTensor)
{
  int idxToStrideInputBufferAlongHeight;
  idxToStrideInputBufferAlongHeight = startIdxWithPaddingOffsetInputTensor;
  for (int outputHeightBlockIdx{0}; outputHeightBlockIdx < 2;
       outputHeightBlockIdx++) {
    outputBufferPtr[outputHeightBlockIdx] = std::fmax
      (inputBufferPtr[idxToStrideInputBufferAlongHeight + 5], std::fmax
       (inputBufferPtr[idxToStrideInputBufferAlongHeight + 4], std::fmax
        (inputBufferPtr[idxToStrideInputBufferAlongHeight + 1],
         inputBufferPtr[idxToStrideInputBufferAlongHeight])));
    idxToStrideInputBufferAlongHeight += 2;
  }
}

//
// Arguments    : const float *inputBufferPtr
//                float *outputBufferPtr
//                int poolOutputWidthIdx
//                int startIdxWithPaddingOffsetInputTensor
// Return Type  : void
//
static void maxPoolingKernel3996420485521692580(const float *inputBufferPtr,
  float *outputBufferPtr, int, int startIdxWithPaddingOffsetInputTensor)
{
  int idxToStrideInputBufferAlongHeight;
  idxToStrideInputBufferAlongHeight = startIdxWithPaddingOffsetInputTensor;
  for (int outputHeightBlockIdx{0}; outputHeightBlockIdx < 4;
       outputHeightBlockIdx++) {
    outputBufferPtr[outputHeightBlockIdx] = std::fmax
      (inputBufferPtr[idxToStrideInputBufferAlongHeight + 9], std::fmax
       (inputBufferPtr[idxToStrideInputBufferAlongHeight + 8], std::fmax
        (inputBufferPtr[idxToStrideInputBufferAlongHeight + 1],
         inputBufferPtr[idxToStrideInputBufferAlongHeight])));
    idxToStrideInputBufferAlongHeight += 2;
  }
}

//
// Arguments    : int K
//                const float *A
//                int LDA
//                const float *B
//                int LDB
//                float *C
//                int LDC
// Return Type  : void
//
static void microKernel10713695924587400261(int K, const float *A, int, const
  float *B, int LDB, float *C, int LDC)
{
  float b_c;
  float c;
  float c_c;
  float d_c;
  int c_tmp;
  int idxA;
  int idxB;
  idxA = 0;
  idxB = 0;
  c = C[0];
  b_c = C[LDC];
  c_tmp = LDC << 1;
  c_c = C[c_tmp];
  d_c = C[LDC * 3];
  for (int k{0}; k < K; k++) {
    float a;
    a = A[idxA];
    idxA++;
    c += a * B[idxB];
    b_c += a * B[idxB + LDB];
    c_c += a * B[idxB + (LDB << 1)];
    d_c += a * B[idxB + LDB * 3];
    idxB++;
  }

  C[0] = c;
  C[LDC] = b_c;
  C[c_tmp] = c_c;
  C[LDC * 3] = d_c;
}

//
// Arguments    : int K
//                const float *A
//                int LDA
//                const float *B
//                int LDB
//                float *C
//                int LDC
// Return Type  : void
//
static void microKernel11116153436181717695(int K, const float *A, int LDA,
  const float *B, int, float *C, int)
{
  float b_c;
  float c;
  float c_c;
  float d_c;
  float e_c;
  float f_c;
  float g_c;
  int idxA;
  int idxB;
  idxA = 0;
  idxB = 0;
  c = C[0];
  b_c = C[1];
  c_c = C[2];
  d_c = C[3];
  e_c = C[4];
  f_c = C[5];
  g_c = C[6];
  for (int k{0}; k < K; k++) {
    float b;
    b = B[idxB];
    c += A[idxA] * b;
    b_c += A[idxA + 1] * b;
    c_c += A[idxA + 2] * b;
    d_c += A[idxA + 3] * b;
    e_c += A[idxA + 4] * b;
    f_c += A[idxA + 5] * b;
    g_c += A[idxA + 6] * b;
    idxA += LDA;
    idxB++;
  }

  C[0] = c;
  C[1] = b_c;
  C[2] = c_c;
  C[3] = d_c;
  C[4] = e_c;
  C[5] = f_c;
  C[6] = g_c;
}

//
// Arguments    : int K
//                const float *A
//                int LDA
//                const float *B
//                int LDB
//                float *C
//                int LDC
// Return Type  : void
//
static void microKernel12338766757609272626(int K, const float *A, int, const
  float *B, int, float *C, int)
{
  float c;
  int idxA;
  int idxB;
  idxA = 0;
  idxB = 0;
  c = C[0];
  for (int k{0}; k < K; k++) {
    float aFloat;
    aFloat = A[idxA];
    idxA++;
    c += aFloat * B[idxB];
    idxB++;
  }

  C[0] = c;
}

//
// Arguments    : int K
//                const float *A
//                int LDA
//                const float *B
//                int LDB
//                float *C
//                int LDC
// Return Type  : void
//
static void microKernel12357106081320476066(int K, const float *A, int LDA,
  const float *B, int, float *C, int)
{
  float b_c;
  float c;
  int idxA;
  int idxB;
  idxA = 0;
  idxB = 0;
  c = C[0];
  b_c = C[1];
  for (int k{0}; k < K; k++) {
    float aFloat;
    float b;
    float b_aFloat;
    aFloat = A[idxA];
    b_aFloat = A[idxA + 1];
    b = B[idxB];
    c += aFloat * b;
    b_c += b_aFloat * b;
    idxA += LDA;
    idxB++;
  }

  C[0] = c;
  C[1] = b_c;
}

//
// Arguments    : int K
//                const float *A
//                int LDA
//                const float *B
//                int LDB
//                float *C
//                int LDC
// Return Type  : void
//
static void microKernel12864598352212304616(int K, const float *A, int LDA,
  const float *B, int, float *C, int)
{
  float b_c;
  float c;
  float c_c;
  float d_c;
  int idxA;
  int idxB;
  idxA = 0;
  idxB = 0;
  c = C[0];
  b_c = C[1];
  c_c = C[2];
  d_c = C[3];
  for (int k{0}; k < K; k++) {
    float b;
    b = B[idxB];
    c += A[idxA] * b;
    b_c += A[idxA + 1] * b;
    c_c += A[idxA + 2] * b;
    d_c += A[idxA + 3] * b;
    idxA += LDA;
    idxB++;
  }

  C[0] = c;
  C[1] = b_c;
  C[2] = c_c;
  C[3] = d_c;
}

//
// Arguments    : int K
//                const float *A
//                int LDA
//                const float *B
//                int LDB
//                float *C
//                int LDC
// Return Type  : void
//
static void microKernel14141928391000443238(int K, const float *A, int LDA,
  const float *B, int, float *C, int)
{
  float c;
  int idxA;
  int idxB;
  idxA = 0;
  idxB = 0;
  c = C[0];
  for (int k{0}; k < K; k++) {
    float aFloat;
    float b;
    aFloat = A[idxA];
    b = B[idxB];
    c += aFloat * b;
    idxA += LDA;
    idxB++;
  }

  C[0] = c;
}

//
// Arguments    : int K
//                const float *A
//                int LDA
//                const float *B
//                int LDB
//                float *C
//                int LDC
// Return Type  : void
//
static void microKernel16622016978981056782(int K, const float *A, int LDA,
  const float *B, int, float *C, int)
{
  float c;
  int idxA;
  int idxB;
  idxA = 0;
  idxB = 0;
  c = C[0];
  for (int k{0}; k < K; k++) {
    c += A[idxA] * B[idxB];
    idxA += LDA;
    idxB++;
  }

  C[0] = c;
}

//
// Arguments    : int K
//                const float *A
//                int LDA
//                const float *B
//                int LDB
//                float *C
//                int LDC
// Return Type  : void
//
static void microKernel18002655007933138772(int K, const float *A, int, const
  float *B, int, float *C, int)
{
  float b_c;
  float c;
  int idxA;
  int idxB;
  idxA = 0;
  idxB = 0;
  c = C[0];
  b_c = C[1];
  for (int k{0}; k < K; k++) {
    float aFloat;
    float b;
    aFloat = A[idxA];
    idxA += 2;
    b = B[idxB];
    c += aFloat * b;
    b_c += A[idxA - 1] * b;
    idxB++;
  }

  C[0] = c;
  C[1] = b_c;
}

//
// Arguments    : int K
//                const float *A
//                int LDA
//                const float *B
//                int LDB
//                float *C
//                int LDC
// Return Type  : void
//
static void microKernel18193303124806281097(int K, const float *A, int LDA,
  const float *B, int LDB, float *C, int LDC)
{
  float b_c;
  float c;
  float c_c;
  float d_c;
  int c_tmp;
  int idxA;
  int idxB;
  idxA = 0;
  idxB = 0;
  c = C[0];
  b_c = C[LDC];
  c_tmp = LDC << 1;
  c_c = C[c_tmp];
  d_c = C[LDC * 3];
  for (int k{0}; k < K; k++) {
    float a;
    float b;
    float b_b;
    float c_b;
    float d_b;
    a = A[idxA];
    b = B[idxB];
    b_b = B[idxB + LDB];
    c_b = B[idxB + (LDB << 1)];
    d_b = B[idxB + LDB * 3];
    c += a * b;
    b_c += a * b_b;
    c_c += a * c_b;
    d_c += a * d_b;
    idxA += LDA;
    idxB++;
  }

  C[0] = c;
  C[LDC] = b_c;
  C[c_tmp] = c_c;
  C[LDC * 3] = d_c;
}

//
// Arguments    : int K
//                const float *A
//                int LDA
//                const float *B
//                int LDB
//                float *C
//                int LDC
// Return Type  : void
//
static void microKernel6930889964022258822(int K, const float *A, int LDA, const
  float *B, int, float *C, int)
{
  float c;
  int idxA;
  int idxB;
  idxA = 0;
  idxB = 0;
  c = C[0];
  for (int k{0}; k < K; k++) {
    float b;
    b = B[idxB];
    c += A[idxA] * b;
    idxA += LDA;
    idxB++;
  }

  C[0] = c;
}

//
// Arguments    : int K
//                const float *A
//                int LDA
//                const float *B
//                int LDB
//                float *C
//                int LDC
// Return Type  : void
//
static void microKernel7414168058516034042(int K, const float *A, int LDA, const
  float *B, int LDB, float *C, int LDC)
{
  float b_c;
  float c;
  float c_c;
  float d_c;
  float e_c;
  float f_c;
  float g_c;
  float h_c;
  int b_c_tmp;
  int c_tmp;
  int idxA;
  int idxB;
  idxA = 0;
  idxB = 0;
  c = C[0];
  b_c = C[1];
  c_c = C[LDC];
  d_c = C[LDC + 1];
  c_tmp = LDC << 1;
  e_c = C[c_tmp];
  f_c = C[c_tmp + 1];
  g_c = C[LDC * 3];
  b_c_tmp = LDC * 3 + 1;
  h_c = C[b_c_tmp];
  for (int k{0}; k < K; k++) {
    float a;
    float b;
    float b_a;
    float b_b;
    float c_b;
    float d_b;
    a = A[idxA];
    b_a = A[idxA + 1];
    b = B[idxB];
    b_b = B[idxB + LDB];
    c_b = B[idxB + (LDB << 1)];
    d_b = B[idxB + LDB * 3];
    c += a * b;
    b_c += b_a * b;
    c_c += a * b_b;
    d_c += b_a * b_b;
    e_c += a * c_b;
    f_c += b_a * c_b;
    g_c += a * d_b;
    h_c += b_a * d_b;
    idxA += LDA;
    idxB++;
  }

  C[0] = c;
  C[1] = b_c;
  C[LDC] = c_c;
  C[LDC + 1] = d_c;
  C[c_tmp] = e_c;
  C[c_tmp + 1] = f_c;
  C[LDC * 3] = g_c;
  C[b_c_tmp] = h_c;
}

//
// Arguments    : int K
//                const float *A
//                int LDA
//                const float *B
//                int LDB
//                float *C
//                int LDC
// Return Type  : void
//
static void microKernel9975537800498894953(int K, const float *A, int, const
  float *B, int LDB, float *C, int LDC)
{
  float b_c;
  float c;
  float c_c;
  float d_c;
  float e_c;
  float f_c;
  float g_c;
  float h_c;
  int b_c_tmp;
  int c_tmp;
  int idxA;
  int idxB;
  idxA = 0;
  idxB = 0;
  c = C[0];
  b_c = C[1];
  c_c = C[LDC];
  d_c = C[LDC + 1];
  c_tmp = LDC << 1;
  e_c = C[c_tmp];
  f_c = C[c_tmp + 1];
  g_c = C[LDC * 3];
  b_c_tmp = LDC * 3 + 1;
  h_c = C[b_c_tmp];
  for (int k{0}; k < K; k++) {
    float a;
    float b;
    float b_a;
    float b_b;
    float c_b;
    float d_b;
    a = A[idxA];
    idxA += 2;
    b_a = A[idxA - 1];
    b = B[idxB];
    b_b = B[idxB + LDB];
    c_b = B[idxB + (LDB << 1)];
    d_b = B[idxB + LDB * 3];
    c += a * b;
    b_c += b_a * b;
    c_c += a * b_b;
    d_c += b_a * b_b;
    e_c += a * c_b;
    f_c += b_a * c_b;
    g_c += a * d_b;
    h_c += b_a * d_b;
    idxB++;
  }

  C[0] = c;
  C[1] = b_c;
  C[LDC] = c_c;
  C[LDC + 1] = d_c;
  C[c_tmp] = e_c;
  C[c_tmp + 1] = f_c;
  C[LDC * 3] = g_c;
  C[b_c_tmp] = h_c;
}

//
// Arguments    : int M
//                int K
//                const float *srcA
//                float *dstA
//                int LDA
// Return Type  : void
//
static void packA4454328187142109130(int M, int K, const float *srcA, float
  *dstA, int LDA)
{
  int srcA_idx1;
  srcA_idx1 = 0;
  while (M != 0) {
    int height;
    int srcA_idx2;
    if (M >= 2) {
      height = 2;
    } else {
      height = 1;
    }

    srcA_idx2 = srcA_idx1;
    for (int k{0}; k < K; k++) {
      for (int i{0}; i < height; i++) {
        *dstA = srcA[i + srcA_idx2];
        dstA++;
      }

      srcA_idx2 += LDA;
    }

    srcA_idx1 += height;
    M -= height;
  }
}

//
// Arguments    : int &inputBufferPtr
//                const char *unresolvedFilePath
//                int numElementsToRead
// Return Type  : void
//
static void readDnnConstants_int32_T(int &inputBufferPtr, const char
  *unresolvedFilePath, int numElementsToRead)
{
  int elementSizeInBytes;
  const char *fileOpenMode;
  char *resolvedFilePath;
  FILE* filePtr;
  void *dataBufferPtr;
  resolvedFilePath = getResolvedFilePath(unresolvedFilePath);
  fileOpenMode = "rb";
  filePtr = fopen(resolvedFilePath, fileOpenMode);
  dataBufferPtr = &(&inputBufferPtr)[0];
  elementSizeInBytes = 4;
  fread(dataBufferPtr, elementSizeInBytes, numElementsToRead, filePtr);
  fclose(filePtr);
  free(resolvedFilePath);
}

//
// Arguments    : long &inputBufferPtr
//                const char *unresolvedFilePath
//                int numElementsToRead
// Return Type  : void
//
static void readDnnConstants_int64_T(long &inputBufferPtr, const char
  *unresolvedFilePath, int numElementsToRead)
{
  int elementSizeInBytes;
  const char *fileOpenMode;
  char *resolvedFilePath;
  FILE* filePtr;
  void *dataBufferPtr;
  resolvedFilePath = getResolvedFilePath(unresolvedFilePath);
  fileOpenMode = "rb";
  filePtr = fopen(resolvedFilePath, fileOpenMode);
  dataBufferPtr = &(&inputBufferPtr)[0];
  elementSizeInBytes = 8;
  fread(dataBufferPtr, elementSizeInBytes, numElementsToRead, filePtr);
  fclose(filePtr);
  free(resolvedFilePath);
}

//
// Arguments    : float &inputBufferPtr
//                const char *unresolvedFilePath
//                int numElementsToRead
// Return Type  : void
//
static void readDnnConstants_real32_T(float &inputBufferPtr, const char
  *unresolvedFilePath, int numElementsToRead)
{
  int elementSizeInBytes;
  const char *fileOpenMode;
  char *resolvedFilePath;
  FILE* filePtr;
  void *dataBufferPtr;
  resolvedFilePath = getResolvedFilePath(unresolvedFilePath);
  fileOpenMode = "rb";
  filePtr = fopen(resolvedFilePath, fileOpenMode);
  dataBufferPtr = &(&inputBufferPtr)[0];
  elementSizeInBytes = 4;
  fread(dataBufferPtr, elementSizeInBytes, numElementsToRead, filePtr);
  fclose(filePtr);
  free(resolvedFilePath);
}

//
// Arguments    : const char *unresolvedFilePath
// Return Type  : char *
//
static char *resolveBinaryFilePath(const char *unresolvedFilePath)
{
  const char *filePathAfterSlicingRelativePathOp;
  const char *lastDirName;
  const char *lastPathSeparator;
  const char *leadingPathSeparatorUnixAndWindows;
  const char *mwDLDataPath;
  char *codegenDir;
  char *coderDataPath;
  char *resolvedFilePath;
  char *updatedStartDir;
  size_t sizeOfChar;

#define XSTR(x)                        #x
#define STR(x)                         XSTR(x)

  coderDataPath = getenv("CODER_DATA_PATH");
  sizeOfChar = 1;
  if (coderDataPath != NULL) {
    resolvedFilePath = getCustomUserDataPathEnvVar(unresolvedFilePath);
  } else {
    int lastPathSeparatorWindows;
    size_t codegenDirLength;
    size_t posOfCodegenDir;
    size_t posOfLeadingPathSeparator;
    mwDLDataPath = STR(MW_DL_DATA_PATH);
    filePathAfterSlicingRelativePathOp = &unresolvedFilePath[2];
    leadingPathSeparatorUnixAndWindows = "/\\";
    posOfLeadingPathSeparator = strcspn(filePathAfterSlicingRelativePathOp,
      leadingPathSeparatorUnixAndWindows);
    codegenDirLength = posOfLeadingPathSeparator + 1;
    codegenDir = static_cast<char *>(calloc(codegenDirLength, sizeOfChar));
    strncpy(codegenDir, filePathAfterSlicingRelativePathOp,
            posOfLeadingPathSeparator);
    lastPathSeparatorWindows = '\\';
    lastPathSeparator = strrchr(mwDLDataPath, lastPathSeparatorWindows);
    if (lastPathSeparator == NULL) {
      int lastPathSeparatorUnix;
      lastPathSeparatorUnix = '/';
      lastPathSeparator = strrchr(mwDLDataPath, lastPathSeparatorUnix);
    }

    if (lastPathSeparator == NULL) {
      lastDirName = mwDLDataPath;
    } else {
      lastDirName = lastPathSeparator + 1;
    }

    if (strcmp(lastDirName, codegenDir) == 0) {
      posOfCodegenDir = lastDirName - mwDLDataPath;
    } else {
      posOfCodegenDir = strlen(mwDLDataPath);
    }

    if (posOfCodegenDir == strlen(mwDLDataPath)) {
      size_t filePathLen_a;
      filePathAfterSlicingRelativePathOp = &unresolvedFilePath[1];
      filePathLen_a = (strlen(mwDLDataPath) + strlen
                       (filePathAfterSlicingRelativePathOp)) + 1;
      resolvedFilePath = static_cast<char *>(calloc(filePathLen_a, sizeOfChar));
      stringConcat(resolvedFilePath, mwDLDataPath, filePathLen_a);
      stringConcat(resolvedFilePath, filePathAfterSlicingRelativePathOp,
                   filePathLen_a);
    } else {
      size_t filePathLen_b;
      filePathLen_b = posOfCodegenDir + 1;
      updatedStartDir = static_cast<char *>(calloc(filePathLen_b, sizeOfChar));
      strncpy(updatedStartDir, mwDLDataPath, posOfCodegenDir);
      filePathLen_b = (strlen(updatedStartDir) + strlen
                       (filePathAfterSlicingRelativePathOp)) + 1;
      resolvedFilePath = static_cast<char *>(calloc(filePathLen_b, sizeOfChar));
      stringConcat(resolvedFilePath, updatedStartDir, filePathLen_b);
      stringConcat(resolvedFilePath, filePathAfterSlicingRelativePathOp,
                   filePathLen_b);
      free(updatedStartDir);
    }

    free(codegenDir);
  }

#undef XSTR
#undef STR

  return resolvedFilePath;
}

//
// Arguments    : float u0
//                float u1
// Return Type  : float
//
static float rt_powf_snf(float u0, float u1)
{
  float y;
  if (std::isnan(u0) || std::isnan(u1)) {
    y = rtNaNF;
  } else {
    float f;
    y = std::abs(u0);
    f = std::abs(u1);
    if (std::isinf(u1)) {
      if (y == 1.0F) {
        y = 1.0F;
      } else if (y > 1.0F) {
        if (u1 > 0.0F) {
          y = rtInfF;
        } else {
          y = 0.0F;
        }
      } else if (u1 > 0.0F) {
        y = 0.0F;
      } else {
        y = rtInfF;
      }
    } else if (f == 0.0F) {
      y = 1.0F;
    } else if (f == 1.0F) {
      if (u1 > 0.0F) {
        y = u0;
      } else {
        y = 1.0F / u0;
      }
    } else if (u1 == 2.0F) {
      y = u0 * u0;
    } else if ((u1 == 0.5F) && (u0 >= 0.0F)) {
      y = std::sqrt(u0);
    } else if ((u0 < 0.0F) && (u1 > std::floor(u1))) {
      y = rtNaNF;
    } else {
      y = std::pow(u0, u1);
    }
  }

  return y;
}

//
// Arguments    : const char *unSanitizedFilePath
// Return Type  : char *
//
static char *sanitizeFilePathForHSP(const char *unSanitizedFilePath)
{
  char *sanitizedFilePath;
  char *stringDuplicate;
  size_t filePathLen;
  size_t sizeOfChar;
  filePathLen = strlen(unSanitizedFilePath) + 1;
  sizeOfChar = 1;
  stringDuplicate = static_cast<char *>(calloc(filePathLen, sizeOfChar));
  stringConcat(stringDuplicate, unSanitizedFilePath, filePathLen);
  sanitizedFilePath = stringDuplicate;
  for (size_t charIdx = 0; charIdx < strlen(unSanitizedFilePath); charIdx++) {
    char charToCheckFor;
    charToCheckFor = unSanitizedFilePath[charIdx];
    if (isspace(charToCheckFor)) {
      sanitizedFilePath[charIdx] = '_';
    }
  }

  return sanitizedFilePath;
}

//
// Arguments    : char *destinationString
//                const char *sourceString
//                size_t destBufferSize
// Return Type  : void
//
static void stringConcat(char *destinationString, const char *sourceString,
  size_t destBufferSize)
{
  size_t dstStringLen;
  size_t srcBuffIdx;
  dstStringLen = strlen(destinationString);
  srcBuffIdx = 0;
  while ((sourceString[srcBuffIdx] != '\x00') && (dstStringLen < destBufferSize
          - 1)) {
    destinationString[dstStringLen] = sourceString[srcBuffIdx];
    dstStringLen++;
    srcBuffIdx++;
  }

  destinationString[dstStringLen] = '\x00';
}

//
// Arguments    : const char *filePath
// Return Type  : char *
//
char *extractCodegenFolderName(const char *filePath)
{
  int posOfLastPathSeparator;
  char *codegenFolderName;
  size_t filePathLen;
  size_t sizeOfChar;

  // this function allocates dynamic memory
  filePathLen = strlen(filePath) + 1;
  sizeOfChar = 1;
  codegenFolderName = static_cast<char *>(calloc(filePathLen, sizeOfChar));
  posOfLastPathSeparator = getPositionOfLastFileSeparator(filePath);
  if (posOfLastPathSeparator != -1) {
    strncpy(codegenFolderName, filePath, posOfLastPathSeparator);
    codegenFolderName[posOfLastPathSeparator] = '\x00';
  } else {
    codegenFolderName[0] = '.';
    codegenFolderName[1] = '\x00';
  }

  return codegenFolderName;
}

//
// SAM2_INFER  Run SAM2 inference via MATLAB Coder Support Package for PyTorch.
//    Inputs:
//      image_hwc_u8  : uint8  [1200, 1800, 3]  raw image pixels (HWC)
//      point_coords  : single [1, 2]            (x, y) in image coords
//      point_labels  : int32  [1]               1=foreground, 0=background
//    Outputs:
//      masks         : logical [3, 1200, 1800]  binary segmentation masks
//      iou_scores    : single  [3]              per-mask IoU predictions
//
//    loadPyTorchExportedProgram loads the .pt2 directly — no importNetworkFromPyTorch.
//    MATLAB Coder generates C++ via the MLIR/TOSA lowering path.
//    invoke() with multiple LHS variables unpacks multi-output models —
//    brace indexing ({}) is not supported by MATLAB Coder for this return type.
//
// Arguments    : const unsigned char image_hwc_u8[6480000]
//                const float point_coords[2]
//                int point_labels
//                boolean_T masks[6480000]
//                float iou_scores[3]
// Return Type  : void
//
void sam2_infer(const unsigned char image_hwc_u8[6480000], const float
                point_coords[2], int point_labels, boolean_T masks[6480000],
                float iou_scores[3])
{
  static unsigned char uv[6480000];
  static boolean_T bv[6480000];

  //  Multi-output invoke: unpack directly into named variables.
  //  MLIR signature: (ui8[1200x1800x3], f32[1x2], i32[1]) -> (i1[3x1200x1800], f32[3])
  for (int i{0}; i < 3; i++) {
    for (int i1{0}; i1 < 1800; i1++) {
      for (int i2{0}; i2 < 1200; i2++) {
        uv[(i + 3 * i1) + 5400 * i2] = image_hwc_u8[(i2 + 1200 * i1) + 2160000 *
          i];
      }
    }
  }

  main_external_interface(uv, point_coords, point_labels, bv, iou_scores);
  for (int i{0}; i < 3; i++) {
    for (int i1{0}; i1 < 1200; i1++) {
      for (int i2{0}; i2 < 1800; i2++) {
        masks[(i + 3 * i1) + 3600 * i2] = bv[(i2 + 1800 * i1) + 2160000 * i];
      }
    }
  }
}

//
// File trailer for sam2_infer.cpp
//
// [EOF]
//
