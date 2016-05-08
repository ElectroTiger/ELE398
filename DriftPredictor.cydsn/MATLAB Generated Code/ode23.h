/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: ode23.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 05-May-2016 18:41:45
 */

#ifndef __ODE23_H__
#define __ODE23_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "calculate_drift_types.h"

/* Function Declarations */
extern void ode23(const double b_y0[6], const double varargin_1[3], double
                  varargin_3, emxArray_real_T *varargout_1, emxArray_real_T
                  *varargout_2, emxArray_real_T *varargout_3, emxArray_real_T
                  *varargout_4, emxArray_real_T *varargout_5);

#endif

/*
 * File trailer for ode23.h
 *
 * [EOF]
 */
