//
// Prerelease License - for engineering feedback and testing purposes
// only. Not for sale.
// File: _coder_sam2_infer_mex.h
//
// MATLAB Coder version            : 26.1
// C/C++ source code generated on  : 01-Apr-2026 07:32:45
//

#ifndef _CODER_SAM2_INFER_MEX_H
#define _CODER_SAM2_INFER_MEX_H

// Include Files
#include "emlrt.h"
#include "mex.h"
#include "tmwtypes.h"

// Function Declarations
MEXFUNCTION_LINKAGE void mexFunction(int32_T nlhs, mxArray *plhs[],
                                     int32_T nrhs, const mxArray *prhs[]);

emlrtCTX mexFunctionCreateRootTLS();

void unsafe_sam2_infer_mexFunction(int32_T nlhs, mxArray *plhs[2], int32_T nrhs,
                                   const mxArray *prhs[3]);

#endif
//
// File trailer for _coder_sam2_infer_mex.h
//
// [EOF]
//
