/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: ntrp23.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 05-May-2016 18:41:45
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "calculate_drift.h"
#include "ntrp23.h"

/* Function Definitions */

/*
 * Arguments    : double t
 *                double t0
 *                const double b_y0[6]
 *                double h
 *                const double f[24]
 *                double y[6]
 * Return Type  : void
 */
void ntrp23(double t, double t0, const double b_y0[6], double h, const double f
            [24], double y[6])
{
  double s;
  double fhBI1[6];
  int k;
  double fhBI2[6];
  double fhBI3[6];
  int i2;
  static const double b[4] = { -1.3333333333333333, 1.0, 1.3333333333333333,
    -1.0 };

  static const double b_b[4] = { 0.55555555555555558, -0.66666666666666663,
    -0.88888888888888884, 1.0 };

  s = (t - t0) / h;
  for (k = 0; k < 6; k++) {
    fhBI1[k] = f[k] * h;
    fhBI2[k] = 0.0;
    fhBI3[k] = 0.0;
    for (i2 = 0; i2 < 4; i2++) {
      fhBI2[k] += f[k + 6 * i2] * (h * b[i2]);
      fhBI3[k] += f[k + 6 * i2] * (h * b_b[i2]);
    }

    y[k] = ((fhBI3[k] * s + fhBI2[k]) * s + fhBI1[k]) * s + b_y0[k];
  }
}

/*
 * File trailer for ntrp23.c
 *
 * [EOF]
 */
