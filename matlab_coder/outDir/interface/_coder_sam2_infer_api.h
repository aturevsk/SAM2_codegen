//
// Prerelease License - for engineering feedback and testing purposes
// only. Not for sale.
// File: _coder_sam2_infer_api.h
//
// MATLAB Coder version            : 26.1
// C/C++ source code generated on  : 01-Apr-2026 07:32:45
//

#ifndef _CODER_SAM2_INFER_API_H
#define _CODER_SAM2_INFER_API_H

// Include Files
#include "emlrt.h"
#include "mex.h"
#include "tmwtypes.h"
#include <algorithm>
#include <cstring>

// Variable Declarations
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

// Function Declarations
void sam2_infer(const uint8_T image_hwc_u8[6480000],
                const real32_T point_coords[2], int32_T point_labels,
                boolean_T masks[6480000], real32_T iou_scores[3]);

void sam2_infer_api(const mxArray *const prhs[3], int32_T nlhs,
                    const mxArray *plhs[2]);

void sam2_infer_atexit();

void sam2_infer_initialize();

void sam2_infer_terminate();

void sam2_infer_xil_shutdown();

void sam2_infer_xil_terminate();

#endif
//
// File trailer for _coder_sam2_infer_api.h
//
// [EOF]
//
