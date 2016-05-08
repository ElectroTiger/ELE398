/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: ode23.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 05-May-2016 18:41:45
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "calculate_drift.h"
#include "ode23.h"
#include "callODEFunctionNSM.h"
#include "calculate_drift_emxutil.h"
#include "odezero.h"

/* Function Declarations */
static double rt_powd_snf(double u0, double u1);

/* Function Definitions */

/*
 * Arguments    : double u0
 *                double u1
 * Return Type  : double
 */
static double rt_powd_snf(double u0, double u1)
{
  double y;
  double d0;
  double d1;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else {
    d0 = fabs(u0);
    d1 = fabs(u1);
    if (rtIsInf(u1)) {
      if (d0 == 1.0) {
        y = rtNaN;
      } else if (d0 > 1.0) {
        if (u1 > 0.0) {
          y = rtInf;
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = rtInf;
      }
    } else if (d1 == 0.0) {
      y = 1.0;
    } else if (d1 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > floor(u1))) {
      y = rtNaN;
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

/*
 * Arguments    : const double b_y0[6]
 *                const double varargin_1[3]
 *                double varargin_3
 *                emxArray_real_T *varargout_1
 *                emxArray_real_T *varargout_2
 *                emxArray_real_T *varargout_3
 *                emxArray_real_T *varargout_4
 *                emxArray_real_T *varargout_5
 * Return Type  : void
 */
void ode23(const double b_y0[6], const double varargin_1[3], double varargin_3,
           emxArray_real_T *varargout_1, emxArray_real_T *varargout_2,
           emxArray_real_T *varargout_3, emxArray_real_T *varargout_4,
           emxArray_real_T *varargout_5)
{
  emxArray_real_T *teout;
  emxArray_real_T *yeout;
  emxArray_int32_T *ieout;
  emxArray_real_T *tout;
  double f0[6];
  double valt;
  int ia;
  emxArray_real_T *yout;
  int nout;
  double absh;
  double ynew[6];
  int k;
  double err;
  boolean_T exitg4;
  double absx;
  double t;
  double y[6];
  static double f[24];
  boolean_T MinStepExit;
  boolean_T Done;
  emxArray_real_T *te;
  emxArray_real_T *ye;
  emxArray_int32_T *ie;
  emxArray_real_T *b_yeout;
  emxArray_real_T *b_yout;
  int exitg1;
  int exponent;
  double hmin;
  double h;
  boolean_T NoFailedAttempts;
  int exitg2;
  int Bcolidx;
  int j;
  int ix;
  int c;
  static const double x[6] = { 0.5, 0.0, 0.75, 0.22222222222222221,
    0.33333333333333331, 0.44444444444444442 };

  int iy;
  double tnew;
  double z[6];
  static const double b[4] = { -0.069444444444444448, 0.083333333333333329,
    0.1111111111111111, -0.125 };

  boolean_T exitg3;
  boolean_T b0;
  double taux[3];
  static const double b_b[4] = { -2.6666666666666665, 2.0, 2.6666666666666665,
    -2.0 };

  static const double c_b[4] = { 1.6666666666666667, -2.0, -2.6666666666666665,
    3.0 };

  static double dv0[18];
  emxInit_real_T1(&teout, 2);
  emxInit_real_T1(&yeout, 2);
  emxInit_int32_T(&ieout, 2);
  emxInit_real_T1(&tout, 2);
  callODEFunctionNSM(b_y0, varargin_1, varargin_3, f0);

  /*  Event function which causes the ODE to terminate execution upon */
  /*  the drift particle hiting the ground. */
  valt = b_y0[2];

  /*  Event triggers when y(3) == 0; */
  /*  Event terminates solution procedure */
  /*  Only account for when y(3) goes positive to negative. */
  ia = teout->size[0] * teout->size[1];
  teout->size[0] = 1;
  teout->size[1] = 0;
  emxEnsureCapacity((emxArray__common *)teout, ia, (int)sizeof(double));
  ia = yeout->size[0] * yeout->size[1];
  yeout->size[0] = 6;
  yeout->size[1] = 0;
  emxEnsureCapacity((emxArray__common *)yeout, ia, (int)sizeof(double));
  ia = ieout->size[0] * ieout->size[1];
  ieout->size[0] = 1;
  ieout->size[1] = 0;
  emxEnsureCapacity((emxArray__common *)ieout, ia, (int)sizeof(int));
  ia = tout->size[0] * tout->size[1];
  tout->size[0] = 1;
  tout->size[1] = 100;
  emxEnsureCapacity((emxArray__common *)tout, ia, (int)sizeof(double));
  for (ia = 0; ia < 100; ia++) {
    tout->data[ia] = 0.0;
  }

  emxInit_real_T1(&yout, 2);
  ia = yout->size[0] * yout->size[1];
  yout->size[0] = 6;
  yout->size[1] = 100;
  emxEnsureCapacity((emxArray__common *)yout, ia, (int)sizeof(double));
  for (ia = 0; ia < 600; ia++) {
    yout->data[ia] = 0.0;
  }

  nout = 0;
  tout->data[0] = 0.0;
  for (ia = 0; ia < 6; ia++) {
    yout->data[ia] = b_y0[ia];
  }

  absh = 30.0;
  for (k = 0; k < 6; k++) {
    ynew[k] = f0[k] / fmax(fabs(b_y0[k]), 0.001);
  }

  err = 0.0;
  k = 0;
  exitg4 = false;
  while ((!exitg4) && (k < 6)) {
    absx = fabs(ynew[k]);
    if (rtIsNaN(absx)) {
      err = rtNaN;
      exitg4 = true;
    } else {
      if (absx > err) {
        err = absx;
      }

      k++;
    }
  }

  absx = err / 0.080000000000000016;
  if (30.0 * absx > 1.0) {
    absh = 1.0 / absx;
  }

  absh = fmax(absh, 7.90505033345994E-323);
  t = 0.0;
  for (ia = 0; ia < 6; ia++) {
    y[ia] = b_y0[ia];
  }

  memset(&f[0], 0, 24U * sizeof(double));
  for (ia = 0; ia < 6; ia++) {
    f[ia] = f0[ia];
  }

  MinStepExit = false;
  Done = false;
  emxInit_real_T1(&te, 2);
  emxInit_real_T1(&ye, 2);
  emxInit_int32_T(&ie, 2);
  emxInit_real_T1(&b_yeout, 2);
  emxInit_real_T1(&b_yout, 2);
  do {
    exitg1 = 0;
    absx = fabs(t);
    if ((!rtIsInf(absx)) && (!rtIsNaN(absx))) {
      if (absx <= 2.2250738585072014E-308) {
        absx = 4.94065645841247E-324;
      } else {
        frexp(absx, &exponent);
        absx = ldexp(1.0, exponent - 53);
      }
    } else {
      absx = rtNaN;
    }

    hmin = 16.0 * absx;
    absh = fmin(30.0, fmax(hmin, absh));
    h = absh;
    if (1.1 * absh >= fabs(300.0 - t)) {
      h = 300.0 - t;
      absh = fabs(300.0 - t);
      Done = true;
    }

    NoFailedAttempts = true;
    do {
      exitg2 = 0;
      Bcolidx = 3;
      for (j = 0; j < 2; j++) {
        Bcolidx += j;
        for (k = 0; k < 6; k++) {
          f0[k] = y[k];
        }

        if (h == 0.0) {
        } else {
          ix = Bcolidx;
          c = 6 * j;
          for (k = 1; k <= c + 1; k += 6) {
            absx = h * x[ix - 3];
            iy = 0;
            for (ia = k; ia <= k + 5; ia++) {
              f0[iy] += f[ia - 1] * absx;
              iy++;
            }

            ix++;
          }
        }

        callODEFunctionNSM(f0, varargin_1, varargin_3, *(double (*)[6])&f[6 * (j
          + 1)]);
      }

      tnew = t + h;
      if (Done) {
        tnew = 300.0;
      }

      for (k = 0; k < 6; k++) {
        ynew[k] = y[k];
      }

      if (h == 0.0) {
      } else {
        for (k = 0; k <= 13; k += 6) {
          absx = h * x[Bcolidx - 1];
          iy = 0;
          for (ia = k; ia + 1 <= k + 6; ia++) {
            ynew[iy] += f[ia] * absx;
            iy++;
          }

          Bcolidx++;
        }
      }

      callODEFunctionNSM(ynew, varargin_1, varargin_3, *(double (*)[6])&f[18]);
      h = tnew - t;
      for (k = 0; k < 6; k++) {
        err = fabs(y[k]);
        absx = fabs(ynew[k]);
        if ((err > absx) || rtIsNaN(absx)) {
          err = fmax(err, 0.001);
        } else {
          err = fmax(absx, 0.001);
        }

        f0[k] = err;
        absx = 0.0;
        for (ia = 0; ia < 4; ia++) {
          absx += f[k + 6 * ia] * b[ia];
        }

        z[k] = absx / f0[k];
      }

      err = 0.0;
      k = 0;
      exitg3 = false;
      while ((!exitg3) && (k < 6)) {
        absx = fabs(z[k]);
        if (rtIsNaN(absx)) {
          err = rtNaN;
          exitg3 = true;
        } else {
          if (absx > err) {
            err = absx;
          }

          k++;
        }
      }

      err *= absh;
      if (err > 0.001) {
        if (absh <= hmin) {
          MinStepExit = true;
          exitg2 = 1;
        } else {
          if (NoFailedAttempts) {
            NoFailedAttempts = false;
            absh = fmax(hmin, absh * fmax(0.5, 0.8 * rt_powd_snf(0.001 / err,
              0.33333333333333331)));
          } else {
            absh = fmax(hmin, 0.5 * absh);
          }

          h = absh;
          Done = false;
        }
      } else {
        exitg2 = 1;
      }
    } while (exitg2 == 0);

    if (MinStepExit) {
      exitg1 = 1;
    } else {
      odezero(valt, t, y, tnew, ynew, h, f, &k, te, ye, ie, &valt, &b0);
      if (k > 0) {
        k = teout->size[1];
        iy = te->size[1];
        ia = teout->size[0] * teout->size[1];
        teout->size[1] = k + iy;
        emxEnsureCapacity((emxArray__common *)teout, ia, (int)sizeof(double));
        for (ia = 0; ia < iy; ia++) {
          teout->data[k + ia] = te->data[ia];
        }

        ia = b_yeout->size[0] * b_yeout->size[1];
        b_yeout->size[0] = 6;
        b_yeout->size[1] = yeout->size[1] + ye->size[1];
        emxEnsureCapacity((emxArray__common *)b_yeout, ia, (int)sizeof(double));
        k = yeout->size[1];
        for (ia = 0; ia < k; ia++) {
          for (iy = 0; iy < 6; iy++) {
            b_yeout->data[iy + b_yeout->size[0] * ia] = yeout->data[iy +
              yeout->size[0] * ia];
          }
        }

        k = ye->size[1];
        for (ia = 0; ia < k; ia++) {
          for (iy = 0; iy < 6; iy++) {
            b_yeout->data[iy + b_yeout->size[0] * (ia + yeout->size[1])] =
              ye->data[iy + ye->size[0] * ia];
          }
        }

        ia = yeout->size[0] * yeout->size[1];
        yeout->size[0] = 6;
        yeout->size[1] = b_yeout->size[1];
        emxEnsureCapacity((emxArray__common *)yeout, ia, (int)sizeof(double));
        k = b_yeout->size[1];
        for (ia = 0; ia < k; ia++) {
          for (iy = 0; iy < 6; iy++) {
            yeout->data[iy + yeout->size[0] * ia] = b_yeout->data[iy +
              b_yeout->size[0] * ia];
          }
        }

        k = ieout->size[1];
        iy = ie->size[1];
        ia = ieout->size[0] * ieout->size[1];
        ieout->size[1] = k + iy;
        emxEnsureCapacity((emxArray__common *)ieout, ia, (int)sizeof(int));
        for (ia = 0; ia < iy; ia++) {
          ieout->data[k + ia] = ie->data[ia];
        }

        if (b0) {
          absx = te->data[te->size[1] - 1] - t;
          for (ia = 0; ia < 3; ia++) {
            taux[ia] = t + absx * (0.5 + 0.25 * (double)ia);
          }

          for (ia = 0; ia < 6; ia++) {
            f0[ia] = 0.0;
            ynew[ia] = 0.0;
            for (iy = 0; iy < 4; iy++) {
              f0[ia] += f[ia + 6 * iy] * b_b[iy];
              ynew[ia] += f[ia + 6 * iy] * c_b[iy];
            }
          }

          for (j = 0; j < 3; j++) {
            absx = (taux[j] - t) / h;
            for (k = 0; k < 6; k++) {
              dv0[k + 6 * j] = (ynew[k] * absx + f0[k]) * absx + f[k];
              f[k + 6 * (1 + j)] = dv0[k + 6 * j];
            }
          }

          tnew = te->data[te->size[1] - 1];
          k = ye->size[1];
          for (ia = 0; ia < 6; ia++) {
            ynew[ia] = ye->data[ia + ye->size[0] * (k - 1)];
          }

          Done = true;
        }
      }

      nout++;
      if (nout + 1 > tout->size[1]) {
        k = tout->size[1];
        ia = tout->size[0] * tout->size[1];
        tout->size[1] = k + 100;
        emxEnsureCapacity((emxArray__common *)tout, ia, (int)sizeof(double));
        for (ia = 0; ia < 100; ia++) {
          tout->data[k + ia] = 0.0;
        }

        ia = b_yout->size[0] * b_yout->size[1];
        b_yout->size[0] = 6;
        b_yout->size[1] = yout->size[1] + 100;
        emxEnsureCapacity((emxArray__common *)b_yout, ia, (int)sizeof(double));
        k = yout->size[1];
        for (ia = 0; ia < k; ia++) {
          for (iy = 0; iy < 6; iy++) {
            b_yout->data[iy + b_yout->size[0] * ia] = yout->data[iy + yout->
              size[0] * ia];
          }
        }

        for (ia = 0; ia < 100; ia++) {
          for (iy = 0; iy < 6; iy++) {
            b_yout->data[iy + b_yout->size[0] * (ia + yout->size[1])] = 0.0;
          }
        }

        ia = yout->size[0] * yout->size[1];
        yout->size[0] = 6;
        yout->size[1] = b_yout->size[1];
        emxEnsureCapacity((emxArray__common *)yout, ia, (int)sizeof(double));
        k = b_yout->size[1];
        for (ia = 0; ia < k; ia++) {
          for (iy = 0; iy < 6; iy++) {
            yout->data[iy + yout->size[0] * ia] = b_yout->data[iy + b_yout->
              size[0] * ia];
          }
        }
      }

      tout->data[nout] = tnew;
      for (j = 0; j < 6; j++) {
        yout->data[j + yout->size[0] * nout] = ynew[j];
      }

      if (Done) {
        exitg1 = 1;
      } else {
        if (NoFailedAttempts) {
          absx = 1.25 * rt_powd_snf(err / 0.001, 0.33333333333333331);
          if (absx > 0.2) {
            absh /= absx;
          } else {
            absh *= 5.0;
          }
        }

        t = tnew;
        for (k = 0; k < 6; k++) {
          y[k] = ynew[k];
          f[k] = f[18 + k];
        }
      }
    }
  } while (exitg1 == 0);

  emxFree_real_T(&b_yout);
  emxFree_real_T(&b_yeout);
  emxFree_int32_T(&ie);
  emxFree_real_T(&ye);
  emxFree_real_T(&te);
  ia = varargout_1->size[0];
  varargout_1->size[0] = nout + 1;
  emxEnsureCapacity((emxArray__common *)varargout_1, ia, (int)sizeof(double));
  for (ia = 0; ia <= nout; ia++) {
    varargout_1->data[ia] = tout->data[ia];
  }

  emxFree_real_T(&tout);
  ia = varargout_2->size[0] * varargout_2->size[1];
  varargout_2->size[0] = nout + 1;
  varargout_2->size[1] = 6;
  emxEnsureCapacity((emxArray__common *)varargout_2, ia, (int)sizeof(double));
  for (ia = 0; ia < 6; ia++) {
    for (iy = 0; iy <= nout; iy++) {
      varargout_2->data[iy + varargout_2->size[0] * ia] = yout->data[ia +
        yout->size[0] * iy];
    }
  }

  emxFree_real_T(&yout);
  ia = varargout_3->size[0];
  varargout_3->size[0] = teout->size[1];
  emxEnsureCapacity((emxArray__common *)varargout_3, ia, (int)sizeof(double));
  k = teout->size[1];
  for (ia = 0; ia < k; ia++) {
    varargout_3->data[ia] = teout->data[teout->size[0] * ia];
  }

  emxFree_real_T(&teout);
  ia = varargout_4->size[0] * varargout_4->size[1];
  varargout_4->size[0] = yeout->size[1];
  varargout_4->size[1] = 6;
  emxEnsureCapacity((emxArray__common *)varargout_4, ia, (int)sizeof(double));
  for (ia = 0; ia < 6; ia++) {
    k = yeout->size[1];
    for (iy = 0; iy < k; iy++) {
      varargout_4->data[iy + varargout_4->size[0] * ia] = yeout->data[ia +
        yeout->size[0] * iy];
    }
  }

  emxFree_real_T(&yeout);
  ia = varargout_5->size[0];
  varargout_5->size[0] = ieout->size[1];
  emxEnsureCapacity((emxArray__common *)varargout_5, ia, (int)sizeof(double));
  k = ieout->size[1];
  for (ia = 0; ia < k; ia++) {
    varargout_5->data[ia] = ieout->data[ieout->size[0] * ia];
  }

  emxFree_int32_T(&ieout);
}

/*
 * File trailer for ode23.c
 *
 * [EOF]
 */
