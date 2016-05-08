/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: callODEFunctionNSM.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 05-May-2016 18:41:45
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "calculate_drift.h"
#include "callODEFunctionNSM.h"

/* Function Definitions */

/*
 * Arguments    : const double y[6]
 *                const double varargin_1[3]
 *                double varargin_3
 *                double yp[6]
 * Return Type  : void
 */
void callODEFunctionNSM(const double y[6], const double varargin_1[3], double
  varargin_3, double yp[6])
{
  double b_y;
  double scale;
  int k;
  double absxk;
  double t;
  static const double dv1[3] = { 0.0, 0.0, 9.801 };

  /*  State-space calculation has first three rows of the state vector as the  */
  /*  position, and the second three rows as the velocity.  */
  /* Gravitational acceleration in m/s. */
  /*  Initial declaration of the shape of the function.  */
  b_y = 0.0;
  scale = 2.2250738585072014E-308;
  for (k = 0; k < 3; k++) {
    yp[k] = y[k + 3];
    absxk = fabs(y[3 + k] - varargin_1[k]);
    if (absxk > scale) {
      t = scale / absxk;
      b_y = 1.0 + b_y * t * t;
      scale = absxk;
    } else {
      t = absxk / scale;
      b_y += t * t;
    }
  }

  b_y = scale * sqrt(b_y);
  b_y *= -varargin_3;
  for (k = 0; k < 3; k++) {
    yp[3 + k] = b_y * (y[3 + k] - varargin_1[k]) - dv1[k];
  }
}

/*
 * File trailer for callODEFunctionNSM.c
 *
 * [EOF]
 */
