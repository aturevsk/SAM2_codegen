//
// Prerelease License - for engineering feedback and testing purposes
// only. Not for sale.
// File: _coder_sam2_infer_api.cpp
//
// MATLAB Coder version            : 26.1
// C/C++ source code generated on  : 01-Apr-2026 07:32:45
//

// Include Files
#include "_coder_sam2_infer_api.h"
#include "_coder_sam2_infer_mex.h"

// Variable Definitions
emlrtCTX emlrtRootTLSGlobal{nullptr};

emlrtContext emlrtContextGlobal{
    true,                                                 // bFirstTime
    false,                                                // bInitialized
    131690U,                                              // fVersionInfo
    nullptr,                                              // fErrorFunction
    "sam2_infer",                                         // fFunctionName
    nullptr,                                              // fRTCallStack
    false,                                                // bDebugMode
    {2045744189U, 2170104910U, 2743257031U, 4284093946U}, // fSigWrd
    nullptr                                               // fSigMem
};

// Function Declarations
static real32_T (*b_emlrt_marshallIn(const emlrtStack &sp,
                                     const mxArray *b_nullptr,
                                     const char_T *identifier))[2];

static real32_T (*b_emlrt_marshallIn(const emlrtStack &sp, const mxArray *u,
                                     const emlrtMsgIdentifier *parentId))[2];

static const mxArray *b_emlrt_marshallOut(real32_T u[3]);

static int32_T c_emlrt_marshallIn(const emlrtStack &sp,
                                  const mxArray *b_nullptr,
                                  const char_T *identifier);

static int32_T c_emlrt_marshallIn(const emlrtStack &sp, const mxArray *u,
                                  const emlrtMsgIdentifier *parentId);

static uint8_T (*d_emlrt_marshallIn(const emlrtStack &sp, const mxArray *src,
                                    const emlrtMsgIdentifier *msgId))[6480000];

static real32_T (*e_emlrt_marshallIn(const emlrtStack &sp, const mxArray *src,
                                     const emlrtMsgIdentifier *msgId))[2];

static void emlrtExitTimeCleanupDtorFcn(const void *r);

static uint8_T (*emlrt_marshallIn(const emlrtStack &sp,
                                  const mxArray *b_nullptr,
                                  const char_T *identifier))[6480000];

static uint8_T (*emlrt_marshallIn(const emlrtStack &sp, const mxArray *u,
                                  const emlrtMsgIdentifier *parentId))[6480000];

static const mxArray *emlrt_marshallOut(boolean_T u[6480000]);

static int32_T f_emlrt_marshallIn(const emlrtStack &sp, const mxArray *src,
                                  const emlrtMsgIdentifier *msgId);

// Function Definitions
//
// Arguments    : const emlrtStack &sp
//                const mxArray *b_nullptr
//                const char_T *identifier
// Return Type  : real32_T (*)[2]
//
static real32_T (*b_emlrt_marshallIn(const emlrtStack &sp,
                                     const mxArray *b_nullptr,
                                     const char_T *identifier))[2]
{
  emlrtMsgIdentifier thisId;
  real32_T(*y)[2];
  thisId.fIdentifier = const_cast<const char_T *>(identifier);
  thisId.fParent = nullptr;
  thisId.bParentIsCell = false;
  y = b_emlrt_marshallIn(sp, emlrtAlias(b_nullptr), &thisId);
  emlrtDestroyArray(&b_nullptr);
  return y;
}

//
// Arguments    : const emlrtStack &sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
// Return Type  : real32_T (*)[2]
//
static real32_T (*b_emlrt_marshallIn(const emlrtStack &sp, const mxArray *u,
                                     const emlrtMsgIdentifier *parentId))[2]
{
  real32_T(*y)[2];
  y = e_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

//
// Arguments    : real32_T u[3]
// Return Type  : const mxArray *
//
static const mxArray *b_emlrt_marshallOut(real32_T u[3])
{
  static const int32_T iv[2]{0, 0};
  static const int32_T iv1[2]{1, 3};
  const mxArray *m;
  const mxArray *y;
  void *existingData;
  y = nullptr;
  m = emlrtCreateNumericArray(2, (const void *)&iv[0], mxSINGLE_CLASS, mxREAL);
  existingData = emlrtMxGetData((mxArray *)m);
  if (existingData != (void *)&u[0]) {
    emlrtFreeMex(existingData);
  }
  emlrtMxSetData((mxArray *)m, &u[0]);
  emlrtSetDimensions((mxArray *)m, &iv1[0], 2);
  emlrtAssign(&y, m);
  return y;
}

//
// Arguments    : const emlrtStack &sp
//                const mxArray *b_nullptr
//                const char_T *identifier
// Return Type  : int32_T
//
static int32_T c_emlrt_marshallIn(const emlrtStack &sp,
                                  const mxArray *b_nullptr,
                                  const char_T *identifier)
{
  emlrtMsgIdentifier thisId;
  int32_T y;
  thisId.fIdentifier = const_cast<const char_T *>(identifier);
  thisId.fParent = nullptr;
  thisId.bParentIsCell = false;
  y = c_emlrt_marshallIn(sp, emlrtAlias(b_nullptr), &thisId);
  emlrtDestroyArray(&b_nullptr);
  return y;
}

//
// Arguments    : const emlrtStack &sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
// Return Type  : int32_T
//
static int32_T c_emlrt_marshallIn(const emlrtStack &sp, const mxArray *u,
                                  const emlrtMsgIdentifier *parentId)
{
  int32_T y;
  y = f_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

//
// Arguments    : const emlrtStack &sp
//                const mxArray *src
//                const emlrtMsgIdentifier *msgId
// Return Type  : uint8_T (*)[6480000]
//
static uint8_T (*d_emlrt_marshallIn(const emlrtStack &sp, const mxArray *src,
                                    const emlrtMsgIdentifier *msgId))[6480000]
{
  static const int32_T dims[3]{1200, 1800, 3};
  int32_T iv[3];
  uint8_T(*ret)[6480000];
  boolean_T bv[3]{false, false, false};
  emlrtCheckVsBuiltInR2012b((emlrtConstCTX)&sp, msgId, src, "uint8", false, 3U,
                            (const void *)&dims[0], &bv[0], &iv[0]);
  ret = (uint8_T(*)[6480000])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

//
// Arguments    : const emlrtStack &sp
//                const mxArray *src
//                const emlrtMsgIdentifier *msgId
// Return Type  : real32_T (*)[2]
//
static real32_T (*e_emlrt_marshallIn(const emlrtStack &sp, const mxArray *src,
                                     const emlrtMsgIdentifier *msgId))[2]
{
  static const int32_T dims[2]{1, 2};
  int32_T iv[2];
  real32_T(*ret)[2];
  boolean_T bv[2]{false, false};
  emlrtCheckVsBuiltInR2012b((emlrtConstCTX)&sp, msgId, src, "single", false, 2U,
                            (const void *)&dims[0], &bv[0], &iv[0]);
  ret = (real32_T(*)[2])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

//
// Arguments    : const void *r
// Return Type  : void
//
static void emlrtExitTimeCleanupDtorFcn(const void *r)
{
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

//
// Arguments    : const emlrtStack &sp
//                const mxArray *b_nullptr
//                const char_T *identifier
// Return Type  : uint8_T (*)[6480000]
//
static uint8_T (*emlrt_marshallIn(const emlrtStack &sp,
                                  const mxArray *b_nullptr,
                                  const char_T *identifier))[6480000]
{
  emlrtMsgIdentifier thisId;
  uint8_T(*y)[6480000];
  thisId.fIdentifier = const_cast<const char_T *>(identifier);
  thisId.fParent = nullptr;
  thisId.bParentIsCell = false;
  y = emlrt_marshallIn(sp, emlrtAlias(b_nullptr), &thisId);
  emlrtDestroyArray(&b_nullptr);
  return y;
}

//
// Arguments    : const emlrtStack &sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
// Return Type  : uint8_T (*)[6480000]
//
static uint8_T (*emlrt_marshallIn(const emlrtStack &sp, const mxArray *u,
                                  const emlrtMsgIdentifier *parentId))[6480000]
{
  uint8_T(*y)[6480000];
  y = d_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

//
// Arguments    : boolean_T u[6480000]
// Return Type  : const mxArray *
//
static const mxArray *emlrt_marshallOut(boolean_T u[6480000])
{
  static const int32_T iv[3]{0, 0, 0};
  static const int32_T iv1[3]{3, 1200, 1800};
  const mxArray *m;
  const mxArray *y;
  void *existingData;
  y = nullptr;
  m = emlrtCreateLogicalArray(3, &iv[0]);
  existingData = emlrtMxGetData((mxArray *)m);
  if (existingData != (void *)&u[0]) {
    emlrtFreeMex(existingData);
  }
  emlrtMxSetData((mxArray *)m, &u[0]);
  emlrtSetDimensions((mxArray *)m, &iv1[0], 3);
  emlrtAssign(&y, m);
  return y;
}

//
// Arguments    : const emlrtStack &sp
//                const mxArray *src
//                const emlrtMsgIdentifier *msgId
// Return Type  : int32_T
//
static int32_T f_emlrt_marshallIn(const emlrtStack &sp, const mxArray *src,
                                  const emlrtMsgIdentifier *msgId)
{
  static const int32_T dims{0};
  int32_T ret;
  emlrtCheckBuiltInR2012b((emlrtConstCTX)&sp, msgId, src, "int32", false, 0U,
                          (const void *)&dims);
  ret = *static_cast<int32_T *>(emlrtMxGetData(src));
  emlrtDestroyArray(&src);
  return ret;
}

//
// Arguments    : const mxArray * const prhs[3]
//                int32_T nlhs
//                const mxArray *plhs[2]
// Return Type  : void
//
void sam2_infer_api(const mxArray *const prhs[3], int32_T nlhs,
                    const mxArray *plhs[2])
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  int32_T point_labels;
  real32_T(*iou_scores)[3];
  real32_T(*point_coords)[2];
  uint8_T(*image_hwc_u8)[6480000];
  boolean_T(*masks)[6480000];
  st.tls = emlrtRootTLSGlobal;
  masks = (boolean_T(*)[6480000])mxMalloc(sizeof(boolean_T[6480000]));
  iou_scores = (real32_T(*)[3])mxMalloc(sizeof(real32_T[3]));
  // Marshall function inputs
  image_hwc_u8 = emlrt_marshallIn(st, emlrtAlias(prhs[0]), "image_hwc_u8");
  point_coords = b_emlrt_marshallIn(st, emlrtAlias(prhs[1]), "point_coords");
  point_labels = c_emlrt_marshallIn(st, emlrtAliasP(prhs[2]), "point_labels");
  // Invoke the target function
  sam2_infer(*image_hwc_u8, *point_coords, point_labels, *masks, *iou_scores);
  // Marshall function outputs
  plhs[0] = emlrt_marshallOut(*masks);
  if (nlhs > 1) {
    plhs[1] = b_emlrt_marshallOut(*iou_scores);
  }
}

//
// Arguments    : void
// Return Type  : void
//
void sam2_infer_atexit()
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtPushHeapReferenceStackR2021a(&st, false, nullptr,
                                    (void *)&emlrtExitTimeCleanupDtorFcn,
                                    nullptr, nullptr, nullptr);
  emlrtEnterRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  sam2_infer_xil_terminate();
  sam2_infer_xil_shutdown();
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

//
// Arguments    : void
// Return Type  : void
//
void sam2_infer_initialize()
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, nullptr);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

//
// Arguments    : void
// Return Type  : void
//
void sam2_infer_terminate()
{
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

//
// File trailer for _coder_sam2_infer_api.cpp
//
// [EOF]
//
