//
// Prerelease License - for engineering feedback and testing purposes
// only. Not for sale.
// File: main.cpp
//
// MATLAB Coder version            : 26.1
// C/C++ source code generated on  : 01-Apr-2026 07:32:45
//

/*************************************************************************/
/* This automatically generated example C++ main file shows how to call  */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/

// Include Files
#include "main.h"
#include "rt_nonfinite.h"
#include "sam2_infer.h"
#include "sam2_infer_initialize.h"
#include "sam2_infer_terminate.h"

// Function Declarations
static void argInit_1200x1800x3_uint8_T(unsigned char result[6480000]);

static void argInit_1x2_real32_T(float result[2]);

static int argInit_int32_T();

static float argInit_real32_T();

static unsigned char argInit_uint8_T();

// Function Definitions
//
// Arguments    : unsigned char result[6480000]
// Return Type  : void
//
static void argInit_1200x1800x3_uint8_T(unsigned char result[6480000])
{
  // Loop over the array to initialize each element.
  for (int idx0{0}; idx0 < 1200; idx0++) {
    for (int idx1{0}; idx1 < 1800; idx1++) {
      for (int idx2{0}; idx2 < 3; idx2++) {
        // Set the value of the array element.
        // Change this value to the value that the application requires.
        result[(idx0 + 1200 * idx1) + 2160000 * idx2] = argInit_uint8_T();
      }
    }
  }
}

//
// Arguments    : float result[2]
// Return Type  : void
//
static void argInit_1x2_real32_T(float result[2])
{
  // Loop over the array to initialize each element.
  for (int idx1{0}; idx1 < 2; idx1++) {
    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result[idx1] = argInit_real32_T();
  }
}

//
// Arguments    : void
// Return Type  : int
//
static int argInit_int32_T()
{
  return 0;
}

//
// Arguments    : void
// Return Type  : float
//
static float argInit_real32_T()
{
  return 0.0F;
}

//
// Arguments    : void
// Return Type  : unsigned char
//
static unsigned char argInit_uint8_T()
{
  return 0U;
}

//
// Arguments    : int argc
//                char **argv
// Return Type  : int
//
int main(int, char **)
{
  // Initialize the application.
  // You do not need to do this more than one time.
  sam2_infer_initialize();
  // Invoke the entry-point functions.
  // You can call entry-point functions multiple times.
  main_sam2_infer();
  // Terminate the application.
  // You do not need to do this more than one time.
  sam2_infer_terminate();
  return 0;
}

//
// Arguments    : void
// Return Type  : void
//
void main_sam2_infer()
{
  static unsigned char uv[6480000];
  static boolean_T masks[6480000];
  float iou_scores[3];
  float fv[2];
  // Initialize function 'sam2_infer' input arguments.
  // Initialize function input argument 'image_hwc_u8'.
  // Initialize function input argument 'point_coords'.
  // Call the entry-point 'sam2_infer'.
  argInit_1200x1800x3_uint8_T(uv);
  argInit_1x2_real32_T(fv);
  sam2_infer(uv, fv, argInit_int32_T(), masks, iou_scores);
}

//
// File trailer for main.cpp
//
// [EOF]
//
