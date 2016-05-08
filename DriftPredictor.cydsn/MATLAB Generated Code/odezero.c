/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: odezero.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 05-May-2016 18:41:45
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "calculate_drift.h"
#include "odezero.h"
#include "calculate_drift_emxutil.h"
#include "ntrp23.h"

/* Function Declarations */
static void nfindcrossing(double vL, double vR, int *idx, int *nidx);

/* Function Definitions */

/*
 * Arguments    : double vL
 *                double vR
 *                int *idx
 *                int *nidx
 * Return Type  : void
 */
static void nfindcrossing(double vL, double vR, int *idx, int *nidx)
{
  double b_vL;
  double b_vR;
  *idx = 0;
  *nidx = 0;
  if (vL < 0.0) {
    b_vL = -1.0;
  } else if (vL > 0.0) {
    b_vL = 1.0;
  } else if (vL == 0.0) {
    b_vL = 0.0;
  } else {
    b_vL = vL;
  }

  if (vR < 0.0) {
    b_vR = -1.0;
  } else if (vR > 0.0) {
    b_vR = 1.0;
  } else if (vR == 0.0) {
    b_vR = 0.0;
  } else {
    b_vR = vR;
  }

  if ((b_vL != b_vR) && (-(vR - vL) >= 0.0)) {
    *nidx = 1;
    *idx = 1;
  }
}

/*
 * Arguments    : double v
 *                double t
 *                const double y[6]
 *                double tnew
 *                const double ynew[6]
 *                double h
 *                const double f[24]
 *                int *nout
 *                emxArray_real_T *tout
 *                emxArray_real_T *yout
 *                emxArray_int32_T *iout
 *                double *vnew
 *                boolean_T *stop
 * Return Type  : void
 */
void odezero(double v, double t, const double y[6], double tnew, const double
             ynew[6], double h, const double f[24], int *nout, emxArray_real_T
             *tout, emxArray_real_T *yout, emxArray_int32_T *iout, double *vnew,
             boolean_T *stop)
{
  int i1;
  double absxk;
  double ttry;
  int exponent;
  int b_exponent;
  double tol;
  double tdir;
  double tL;
  double vL;
  double tR;
  double yR[6];
  double vR;
  double vswap;
  char lastmoved;
  int exitg1;
  double delta;
  boolean_T lzrnz;
  boolean_T exitg2;
  double change;
  double ytry[6];
  *nout = 0;
  i1 = tout->size[0] * tout->size[1];
  tout->size[0] = 1;
  tout->size[1] = 0;
  emxEnsureCapacity((emxArray__common *)tout, i1, (int)sizeof(double));
  i1 = yout->size[0] * yout->size[1];
  yout->size[0] = 6;
  yout->size[1] = 0;
  emxEnsureCapacity((emxArray__common *)yout, i1, (int)sizeof(double));
  i1 = iout->size[0] * iout->size[1];
  iout->size[0] = 1;
  iout->size[1] = 0;
  emxEnsureCapacity((emxArray__common *)iout, i1, (int)sizeof(int));
  absxk = fabs(t);
  if ((!rtIsInf(absxk)) && (!rtIsNaN(absxk))) {
    if (absxk <= 2.2250738585072014E-308) {
      ttry = 4.94065645841247E-324;
    } else {
      frexp(absxk, &exponent);
      ttry = ldexp(1.0, exponent - 53);
    }
  } else {
    ttry = rtNaN;
  }

  absxk = fabs(tnew);
  if ((!rtIsInf(absxk)) && (!rtIsNaN(absxk))) {
    if (absxk <= 2.2250738585072014E-308) {
      absxk = 4.94065645841247E-324;
    } else {
      frexp(absxk, &b_exponent);
      absxk = ldexp(1.0, b_exponent - 53);
    }
  } else {
    absxk = rtNaN;
  }

  tol = fmin(128.0 * fmax(ttry, absxk), fabs(tnew - t));
  absxk = tnew - t;
  if (absxk < 0.0) {
    tdir = -1.0;
  } else if (absxk > 0.0) {
    tdir = 1.0;
  } else if (absxk == 0.0) {
    tdir = 0.0;
  } else {
    tdir = absxk;
  }

  *stop = false;
  tL = t;
  vL = v;

  /*  Event function which causes the ODE to terminate execution upon */
  /*  the drift particle hiting the ground. */
  /*  Event triggers when y(3) == 0; */
  /*  Event terminates solution procedure */
  /*  Only account for when y(3) goes positive to negative. */
  *vnew = ynew[2];
  tR = tnew;
  for (exponent = 0; exponent < 6; exponent++) {
    yR[exponent] = ynew[exponent];
  }

  vR = ynew[2];
  vswap = 0.0;
  ttry = tnew;
  lastmoved = 'N';
  do {
    exitg1 = 0;
    nfindcrossing(vL, vR, &b_exponent, &exponent);
    if (exponent < 1) {
      exitg1 = 1;
    } else {
      delta = tR - tL;
      if (fabs(delta) <= tol) {
        i1 = tout->size[0] * tout->size[1];
        tout->size[0] = 1;
        tout->size[1] = 1;
        emxEnsureCapacity((emxArray__common *)tout, i1, (int)sizeof(double));
        tout->data[0] = 0.0;
        i1 = yout->size[0] * yout->size[1];
        yout->size[0] = 6;
        yout->size[1] = 1;
        emxEnsureCapacity((emxArray__common *)yout, i1, (int)sizeof(double));
        for (i1 = 0; i1 < 6; i1++) {
          yout->data[i1] = 0.0;
        }

        i1 = iout->size[0] * iout->size[1];
        iout->size[0] = 1;
        iout->size[1] = 1;
        emxEnsureCapacity((emxArray__common *)iout, i1, (int)sizeof(int));
        iout->data[0] = 0;
        tout->data[0] = tR;
        iout->data[0] = b_exponent;
        for (i1 = 0; i1 < 6; i1++) {
          yout->data[i1] = yR[i1];
        }

        *nout = 1;
        if (tL != 0.0) {
          *stop = true;
        }

        exitg1 = 1;
      } else {
        lzrnz = (tL == t);
        if (lzrnz) {
          lzrnz = false;
          exponent = 1;
          exitg2 = false;
          while ((!exitg2) && (exponent <= 1)) {
            if ((vL == 0.0) && (vR != 0.0)) {
              lzrnz = true;
              exitg2 = true;
            } else {
              exponent = 2;
            }
          }
        }

        if (lzrnz) {
          ttry = tL + tdir * 0.5 * tol;
        } else {
          change = 1.0;
          if (vL == 0.0) {
            if ((tdir * ttry > tdir * tR) && (vswap != vR)) {
              ttry = vR * (ttry - tR);
              absxk = (vswap - vR) * delta;
              vswap = ttry / absxk;
              absxk = 1.0 - ttry / absxk;
              if ((1.0 - vswap < 0.0) || (1.0 - vswap > 1.0)) {
                absxk = 0.5;
              }
            } else {
              absxk = 0.5;
            }
          } else if (vR == 0.0) {
            if ((tdir * ttry < tdir * tL) && (vswap != vL)) {
              absxk = vL * (tL - ttry) / ((vswap - vL) * delta);
              if ((absxk < 0.0) || (absxk > 1.0)) {
                absxk = 0.5;
              }
            } else {
              absxk = 0.5;
            }
          } else {
            absxk = -vL / (vR - vL);
          }

          if (absxk < 1.0) {
            change = absxk;
          }

          change *= fabs(delta);
          ttry = tL + tdir * fmax(0.5 * tol, fmin(change, fabs(delta) - 0.5 *
            tol));
        }

        ntrp23(ttry, t, y, h, f, ytry);

        /*  Event function which causes the ODE to terminate execution upon */
        /*  the drift particle hiting the ground. */
        /*  Event triggers when y(3) == 0; */
        /*  Event terminates solution procedure */
        /*  Only account for when y(3) goes positive to negative. */
        nfindcrossing(vL, ytry[2], &b_exponent, &exponent);
        if (exponent > 0) {
          absxk = tR;
          tR = ttry;
          ttry = absxk;
          for (exponent = 0; exponent < 6; exponent++) {
            yR[exponent] = ytry[exponent];
          }

          vswap = vR;
          vR = ytry[2];
          if (lastmoved == 'R') {
            absxk = 0.5 * vL;
            if (fabs(absxk) >= 2.2250738585072014E-308) {
              vL = absxk;
            }
          }

          lastmoved = 'R';
        } else {
          absxk = tL;
          tL = ttry;
          ttry = absxk;
          vswap = vL;
          vL = ytry[2];
          if (lastmoved == 'L') {
            absxk = 0.5 * vR;
            if (fabs(absxk) >= 2.2250738585072014E-308) {
              vR = absxk;
            }
          }

          lastmoved = 'L';
        }
      }
    }
  } while (exitg1 == 0);
}

/*
 * File trailer for odezero.c
 *
 * [EOF]
 */
