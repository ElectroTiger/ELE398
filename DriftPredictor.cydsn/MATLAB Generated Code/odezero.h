/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: odezero.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 05-May-2016 18:41:45
 */

#ifndef __ODEZERO_H__
#define __ODEZERO_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "calculate_drift_types.h"

/* Function Declarations */
extern void odezero(double v, double t, const double y[6], double tnew, const
                    double ynew[6], double h, const double f[24], int *nout,
                    emxArray_real_T *tout, emxArray_real_T *yout,
                    emxArray_int32_T *iout, double *vnew, boolean_T *stop);

#endif

/*
 * File trailer for odezero.h
 *
 * [EOF]
 */
