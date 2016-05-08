/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: calculate_drift.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 05-May-2016 18:41:45
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "calculate_drift.h"
#include "calculate_drift_emxutil.h"
#include "ode23.h"

/* Function Definitions */

/*
 * Specify the initial condition vector for the differential equation.
 * Arguments    : const double x0Vec[3]
 *                const double w0Vec[3]
 *                const double v0Vec[3]
 *                double alpha
 *                double *tf
 *                double *x
 *                double *y
 * Return Type  : void
 */
void calculate_drift(const double x0Vec[3], const double w0Vec[3], const double
                     v0Vec[3], double alpha, double *tf, double *x, double *y)
{
  double b_x0Vec[6];
  int i0;
  emxArray_real_T *unusedU0;
  emxArray_real_T *unusedU1;
  emxArray_real_T *TE;
  emxArray_real_T *XE;
  emxArray_real_T *unusedU2;

  /*  Create an event where the calculation terminates upon the particle */
  /*  hitting the ground (Condition where height is zero.  */
  /*  Use ODE23 to solve the differential equation. Time step is set to 300 */
  /*  (5 minutes) for safety, but the event causes the calculation to terminate */
  /*  long beforethen.  */
  /*  We don't-care some options because we only care about the final time and */
  /*  the final position.  */
  for (i0 = 0; i0 < 3; i0++) {
    b_x0Vec[i0] = x0Vec[i0];
    b_x0Vec[i0 + 3] = v0Vec[i0];
  }

  emxInit_real_T(&unusedU0, 1);
  emxInit_real_T1(&unusedU1, 2);
  emxInit_real_T(&TE, 1);
  emxInit_real_T1(&XE, 2);
  emxInit_real_T(&unusedU2, 1);
  ode23(b_x0Vec, w0Vec, alpha, unusedU0, unusedU1, TE, XE, unusedU2);
  *x = XE->data[0];
  *y = XE->data[1];
  *tf = TE->data[0];
  emxFree_real_T(&unusedU2);
  emxFree_real_T(&XE);
  emxFree_real_T(&TE);
  emxFree_real_T(&unusedU1);
  emxFree_real_T(&unusedU0);
}

/*
 * File trailer for calculate_drift.c
 *
 * [EOF]
 */
