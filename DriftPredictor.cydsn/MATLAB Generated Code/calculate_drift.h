/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: calculate_drift.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 05-May-2016 18:41:45
 */

#ifndef __CALCULATE_DRIFT_H__
#define __CALCULATE_DRIFT_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "calculate_drift_types.h"

/* Function Declarations */
extern void calculate_drift(const double x0Vec[3], const double w0Vec[3], const
  double v0Vec[3], double alpha, double *tf, double *x, double *y);

#endif

/*
 * File trailer for calculate_drift.h
 *
 * [EOF]
 */
