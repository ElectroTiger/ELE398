/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: ntrp23.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 05-May-2016 18:41:45
 */

#ifndef __NTRP23_H__
#define __NTRP23_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "calculate_drift_types.h"

/* Function Declarations */
extern void ntrp23(double t, double t0, const double b_y0[6], double h, const
                   double f[24], double y[6]);

#endif

/*
 * File trailer for ntrp23.h
 *
 * [EOF]
 */
