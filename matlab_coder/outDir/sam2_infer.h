//
// Prerelease License - for engineering feedback and testing purposes
// only. Not for sale.
// File: sam2_infer.h
//
// MATLAB Coder version            : 26.1
// C/C++ source code generated on  : 01-Apr-2026 07:32:45
//

#ifndef SAM2_INFER_H
#define SAM2_INFER_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
char *extractCodegenFolderName(const char *filePath);

extern void sam2_infer(const unsigned char image_hwc_u8[6480000],
                       const float point_coords[2], int point_labels,
                       boolean_T masks[6480000], float iou_scores[3]);

#endif
//
// File trailer for sam2_infer.h
//
// [EOF]
//
