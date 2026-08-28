/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ControlsMFE25.c
 *
 * Code generated for Simulink model 'ControlsMFE25'.
 *
 * Model version                  : 1.9
 * Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
 * C/C++ source code generated on : Sat Aug 15 00:32:33 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "ControlsMFE25.h"
#include "ControlsMFE25_types.h"
#include "rtwtypes.h"
#include <math.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "ControlsMFE25_private.h"
#include "coder_posix_time.h"
#include "rt_defines.h"

/* Forward declaration for local functions */
static void ControlsMFE25_timeKeeper(real_T newTime_tv_sec, real_T
  newTime_tv_nsec, sdAmwXbnJnEmimT0NaJRtAD_Contr_T *savedTime,
  DW_ControlsMFE25_T *ControlsMFE25_DW);
static void ControlsMFE25_tic(sdAmwXbnJnEmimT0NaJRtAD_Contr_T *savedTime,
  DW_ControlsMFE25_T *ControlsMFE25_DW);
static void ControlsMFE25_timeKeeper_n(sdAmwXbnJnEmimT0NaJRtAD_Contr_T
  *savedTime, real_T *outTime_tv_sec, real_T *outTime_tv_nsec,
  DW_ControlsMFE25_T *ControlsMFE25_DW);
static real_T ControlsMFE25_toc(sdAmwXbnJnEmimT0NaJRtAD_Contr_T *savedTime,
  DW_ControlsMFE25_T *ControlsMFE25_DW);
static void Control_modifyOverheadPhaseOne_(s18w5MCz6685sBFJwJZKJdG_Contr_T *obj);
static void ControlsMFE25_setProblemType(s18w5MCz6685sBFJwJZKJdG_Contr_T *obj,
  int32_T PROBLEM_TYPE);
static real_T ControlsMFE25_xnrm2(int32_T n, const real_T x[50], int32_T ix0);
static real_T ControlsMFE25_xzlarfg(int32_T n, real_T *alpha1, real_T x[50],
  int32_T ix0);
static void ControlsMFE25_xzlarf(int32_T m, int32_T n, int32_T iv0, real_T tau,
  real_T C[50], int32_T ic0, real_T work[10]);
static void ControlsMFE25_qrf(real_T A[50], int32_T m, int32_T n, int32_T nfxd,
  real_T tau[5]);
static void ControlsMFE25_xgeqp3(real_T A[50], int32_T m, int32_T n, int32_T
  jpvt[10], real_T tau[5]);
static void ControlsMFE25_countsort(int32_T x[10], int32_T xLen, int32_T
  workspace[10], int32_T xMin, int32_T xMax);
static void ControlsMFE25_removeConstr(s18w5MCz6685sBFJwJZKJdG_Contr_T *obj,
  int32_T idx_global);
static void ControlsMF_RemoveDependentIneq_(s18w5MCz6685sBFJwJZKJdG_Contr_T
  *workingset, sisnsZ1AM9QRiMKnwqarOXF_Contr_T *qrmanager,
  su0bqVilpnfgpuAQ6xEtFDC_Contr_T *memspace, real_T tolfactor);
static void ControlsMFE25_computeQ_(sisnsZ1AM9QRiMKnwqarOXF_Contr_T *obj,
  int32_T nrows);
static int32_T ControlsMFE25_rank(const real_T qrmanager_QR[50], int32_T
  qrmanager_mrows, int32_T qrmanager_ncols);
static real_T Controls_maxConstraintViolation(s18w5MCz6685sBFJwJZKJdG_Contr_T
  *obj, const real_T x[50]);
static boolean_T Control_feasibleX0ForWorkingSet(real_T workspace[50], real_T
  xCurrent[5], s18w5MCz6685sBFJwJZKJdG_Contr_T *workingset,
  sisnsZ1AM9QRiMKnwqarOXF_Contr_T *qrmanager);
static int32_T Controls_ComputeNumDependentEq_(sisnsZ1AM9QRiMKnwqarOXF_Contr_T
  *qrmanager, const real_T beqf[10], int32_T mConstr, int32_T nVar);
static real_T Contro_maxConstraintViolation_m(s18w5MCz6685sBFJwJZKJdG_Contr_T
  *obj, const real_T x[5]);
static void ControlsMFE_IndexOfDependentEq_(int32_T depIdx[10], int32_T mFixed,
  int32_T nDep, sisnsZ1AM9QRiMKnwqarOXF_Contr_T *qrmanager, int32_T mRows,
  int32_T nCols);
static void ControlsMFE25_removeEqConstr(const s18w5MCz6685sBFJwJZKJdG_Contr_T
  *obj, int32_T idx_global);
static void ControlsMFE2_PresolveWorkingSet(sF7ecKzAoqUt0jrk31NyRZH_Contr_T
  *solution, su0bqVilpnfgpuAQ6xEtFDC_Contr_T *memspace,
  s18w5MCz6685sBFJwJZKJdG_Contr_T *workingset, sisnsZ1AM9QRiMKnwqarOXF_Contr_T
  *qrmanager);
static void ControlsMFE25_xgemv(int32_T m, int32_T n, const real_T A[16],
  int32_T lda, const real_T x[5], real_T y[4]);
static void ControlsMFE_computeGrad_StoreHx(szdozZxcClCeUpd1TsA9nJF_Contr_T *obj,
  const real_T H[16], const real_T f[4], const real_T x[5]);
static real_T ControlsMFE_computeFval_ReuseHx(const
  szdozZxcClCeUpd1TsA9nJF_Contr_T *obj, real_T workspace[50], const real_T f[4],
  const real_T x[5]);
static void ControlsMFE25_factorQR(sisnsZ1AM9QRiMKnwqarOXF_Contr_T *obj, const
  real_T A[50], int32_T mrows, int32_T ncols);
static void ControlsMFE25_xrotg(real_T *a, real_T *b, real_T *c, real_T *s);
static void ControlsMFE25_squareQ_appendCol(sisnsZ1AM9QRiMKnwqarOXF_Contr_T *obj,
  const real_T vec[50], int32_T iv0);
static void ControlsMFE25_deleteColMoveEnd(sisnsZ1AM9QRiMKnwqarOXF_Contr_T *obj,
  int32_T idx);
static void ControlsMFE25_xgemv_o(int32_T m, int32_T n, const real_T A[25],
  int32_T ia0, const real_T x[50], real_T y[5]);
static void ControlsMFE25_fullColLDL2_(sY034dY3cx1IgSIMa0jtlQE_Contr_T *obj,
  int32_T NColsRemain, real_T REG_PRIMAL);
static void ControlsMFE25_compute_deltax(const real_T H[16],
  sF7ecKzAoqUt0jrk31NyRZH_Contr_T *solution, su0bqVilpnfgpuAQ6xEtFDC_Contr_T
  *memspace, const sisnsZ1AM9QRiMKnwqarOXF_Contr_T *qrmanager,
  sY034dY3cx1IgSIMa0jtlQE_Contr_T *cholmanager, const
  szdozZxcClCeUpd1TsA9nJF_Contr_T *objective);
static void ControlsMFE25_compute_lambda(real_T workspace[50],
  sF7ecKzAoqUt0jrk31NyRZH_Contr_T *solution, const
  szdozZxcClCeUpd1TsA9nJF_Contr_T *objective, const
  sisnsZ1AM9QRiMKnwqarOXF_Contr_T *qrmanager);
static real_T ControlsMFE25_xnrm2_d(int32_T n, const real_T x[5]);
static void ControlsMFE25_ratiotest(const real_T solution_xstar[5], const real_T
  solution_searchDir[5], real_T workspace[50], int32_T workingset_nVar, const
  real_T workingset_Aineq[5], real_T workingset_bineq, const real_T
  workingset_lb[5], const real_T workingset_ub[5], const int32_T
  workingset_indexLB[5], const int32_T workingset_indexUB[5], const int32_T
  workingset_sizes[5], const int32_T workingset_isActiveIdx[6], const boolean_T
  workingset_isActiveConstr[10], const int32_T workingset_nWConstr[5], real_T
  *toldelta, real_T *alpha, boolean_T *newBlocking, int32_T *constrType, int32_T
  *constrIdx);
static void ControlsMFE25_feasibleratiotest(const real_T solution_xstar[5],
  const real_T solution_searchDir[5], real_T workspace[50], int32_T
  workingset_nVar, const real_T workingset_Aineq[5], real_T workingset_bineq,
  const real_T workingset_lb[5], const real_T workingset_ub[5], const int32_T
  workingset_indexLB[5], const int32_T workingset_indexUB[5], const int32_T
  workingset_sizes[5], const int32_T workingset_isActiveIdx[6], const boolean_T
  workingset_isActiveConstr[10], const int32_T workingset_nWConstr[5], boolean_T
  isPhaseOne, real_T *alpha, boolean_T *newBlocking, int32_T *constrType,
  int32_T *constrIdx);
static void Cont_addBoundToActiveSetMatrix_(s18w5MCz6685sBFJwJZKJdG_Contr_T *obj,
  int32_T TYPE, int32_T idx_local);
static void ControlsMFE25_addAineqConstr(s18w5MCz6685sBFJwJZKJdG_Contr_T *obj,
  int32_T idx_local);
static void ControlsMFE25_iterate_e(const real_T H[16], const real_T f[4],
  sF7ecKzAoqUt0jrk31NyRZH_Contr_T *solution, su0bqVilpnfgpuAQ6xEtFDC_Contr_T
  *memspace, s18w5MCz6685sBFJwJZKJdG_Contr_T *workingset,
  sisnsZ1AM9QRiMKnwqarOXF_Contr_T *qrmanager, sY034dY3cx1IgSIMa0jtlQE_Contr_T
  *cholmanager, szdozZxcClCeUpd1TsA9nJF_Contr_T *objective, boolean_T
  runTimeOptions_RemainFeasible, int32_T runTimeOptions_MaxIterations, real_T
  runTimeOptions_ConstrRelTolFact, real_T runTimeOptions_ProbRelTolFactor);
static void ControlsMF_computeFirstOrderOpt(sF7ecKzAoqUt0jrk31NyRZH_Contr_T
  *solution, const szdozZxcClCeUpd1TsA9nJF_Contr_T *objective, int32_T
  workingset_nVar, const real_T workingset_ATwset[50], int32_T
  workingset_nActiveConstr, real_T workspace[50]);
static int32_T ControlsMFE2_RemoveDependentEq_(su0bqVilpnfgpuAQ6xEtFDC_Contr_T
  *memspace, const s18w5MCz6685sBFJwJZKJdG_Contr_T *workingset,
  sisnsZ1AM9QRiMKnwqarOXF_Contr_T *qrmanager);
static void ControlsMFE25_phaseone(const real_T H[16], const real_T f[4],
  sF7ecKzAoqUt0jrk31NyRZH_Contr_T *solution, su0bqVilpnfgpuAQ6xEtFDC_Contr_T
  *memspace, s18w5MCz6685sBFJwJZKJdG_Contr_T *workingset,
  sisnsZ1AM9QRiMKnwqarOXF_Contr_T *qrmanager, sY034dY3cx1IgSIMa0jtlQE_Contr_T
  *cholmanager, szdozZxcClCeUpd1TsA9nJF_Contr_T *objective, const
  sIOJhD9KwAkF5sEguPjYquC_Contr_T *runTimeOptions);
static void ControlsMFE25_iterate(const real_T H[16], const real_T f[4],
  sF7ecKzAoqUt0jrk31NyRZH_Contr_T *solution, su0bqVilpnfgpuAQ6xEtFDC_Contr_T
  *memspace, s18w5MCz6685sBFJwJZKJdG_Contr_T *workingset,
  sisnsZ1AM9QRiMKnwqarOXF_Contr_T *qrmanager, sY034dY3cx1IgSIMa0jtlQE_Contr_T
  *cholmanager, szdozZxcClCeUpd1TsA9nJF_Contr_T *objective, real_T
  options_ObjectiveLimit, int32_T runTimeOptions_MaxIterations, real_T
  runTimeOptions_ConstrRelTolFact, real_T runTimeOptions_ProbRelTolFactor);
static void ControlsMFE25_driver(const real_T H[16], const real_T f[4],
  sF7ecKzAoqUt0jrk31NyRZH_Contr_T *solution, su0bqVilpnfgpuAQ6xEtFDC_Contr_T
  *memspace, s18w5MCz6685sBFJwJZKJdG_Contr_T *workingset,
  sY034dY3cx1IgSIMa0jtlQE_Contr_T *cholmanager, sIOJhD9KwAkF5sEguPjYquC_Contr_T
  runTimeOptions, sisnsZ1AM9QRiMKnwqarOXF_Contr_T *qrmanager,
  szdozZxcClCeUpd1TsA9nJF_Contr_T *objective);
real_T look1_pbinlcapw(real_T u0, const real_T bp0[], const real_T table[],
  uint32_T prevIndex[], uint32_T maxIndex)
{
  real_T frac;
  real_T y;
  uint32_T bpIdx;

  /* Column-major Lookup 1-D
     Search method: 'binary'
     Use previous index: 'on'
     Interpolation method: 'Linear point-slope'
     Extrapolation method: 'Clip'
     Use last breakpoint for index at or above upper limit: 'on'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Clip'
     Use previous index: 'on'
     Use last breakpoint for index at or above upper limit: 'on'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0U]) {
    bpIdx = 0U;
    frac = 0.0;
  } else if (u0 < bp0[maxIndex]) {
    uint32_T found;
    uint32_T iLeft;
    uint32_T iRght;

    /* Binary Search using Previous Index */
    bpIdx = prevIndex[0U];
    iLeft = 0U;
    iRght = maxIndex;
    found = 0U;
    while (found == 0U) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx - 1U;
        bpIdx = ((bpIdx + iLeft) - 1U) >> 1U;
      } else if (u0 < bp0[bpIdx + 1U]) {
        found = 1U;
      } else {
        iLeft = bpIdx + 1U;
        bpIdx = ((bpIdx + iRght) + 1U) >> 1U;
      }
    }

    frac = (u0 - bp0[bpIdx]) / (bp0[bpIdx + 1U] - bp0[bpIdx]);
  } else {
    bpIdx = maxIndex;
    frac = 0.0;
  }

  prevIndex[0U] = bpIdx;

  /* Column-major Interpolation 1-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'on'
     Overflow mode: 'portable wrapping'
   */
  if (bpIdx == maxIndex) {
    y = table[bpIdx];
  } else {
    real_T yL_0d0;
    yL_0d0 = table[bpIdx];
    y = (table[bpIdx + 1U] - yL_0d0) * frac + yL_0d0;
  }

  return y;
}

real_T look2_binlxpw(real_T u0, real_T u1, const real_T bp0[], const real_T bp1[],
                     const real_T table[], const uint32_T maxIndex[], uint32_T
                     stride)
{
  real_T fractions[2];
  real_T frac;
  real_T yL_0d0;
  real_T yL_0d1;
  uint32_T bpIndices[2];
  uint32_T bpIdx;
  uint32_T iLeft;
  uint32_T iRght;

  /* Column-major Lookup 2-D
     Search method: 'binary'
     Use previous index: 'off'
     Interpolation method: 'Linear point-slope'
     Extrapolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Linear'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0U]) {
    iLeft = 0U;
    frac = (u0 - bp0[0U]) / (bp0[1U] - bp0[0U]);
  } else if (u0 < bp0[maxIndex[0U]]) {
    /* Binary Search */
    bpIdx = maxIndex[0U] >> 1U;
    iLeft = 0U;
    iRght = maxIndex[0U];
    while (iRght - iLeft > 1U) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1U;
    }

    frac = (u0 - bp0[iLeft]) / (bp0[iLeft + 1U] - bp0[iLeft]);
  } else {
    iLeft = maxIndex[0U] - 1U;
    frac = (u0 - bp0[maxIndex[0U] - 1U]) / (bp0[maxIndex[0U]] - bp0[maxIndex[0U]
      - 1U]);
  }

  fractions[0U] = frac;
  bpIndices[0U] = iLeft;

  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Linear'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u1 <= bp1[0U]) {
    iLeft = 0U;
    frac = (u1 - bp1[0U]) / (bp1[1U] - bp1[0U]);
  } else if (u1 < bp1[maxIndex[1U]]) {
    /* Binary Search */
    bpIdx = maxIndex[1U] >> 1U;
    iLeft = 0U;
    iRght = maxIndex[1U];
    while (iRght - iLeft > 1U) {
      if (u1 < bp1[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1U;
    }

    frac = (u1 - bp1[iLeft]) / (bp1[iLeft + 1U] - bp1[iLeft]);
  } else {
    iLeft = maxIndex[1U] - 1U;
    frac = (u1 - bp1[maxIndex[1U] - 1U]) / (bp1[maxIndex[1U]] - bp1[maxIndex[1U]
      - 1U]);
  }

  /* Column-major Interpolation 2-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'portable wrapping'
   */
  bpIdx = iLeft * stride + bpIndices[0U];
  yL_0d0 = table[bpIdx];
  yL_0d0 += (table[bpIdx + 1U] - yL_0d0) * fractions[0U];
  bpIdx += stride;
  yL_0d1 = table[bpIdx];
  return (((table[bpIdx + 1U] - yL_0d1) * fractions[0U] + yL_0d1) - yL_0d0) *
    frac + yL_0d0;
}

int32_T div_nde_s32_floor(int32_T numerator, int32_T denominator)
{
  return (((numerator < 0) != (denominator < 0)) && (numerator % denominator !=
           0) ? -1 : 0) + numerator / denominator;
}

real_T rt_atan2d_snf(real_T u0, real_T u1)
{
  real_T y;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    int32_T tmp;
    int32_T tmp_0;
    if (u0 > 0.0) {
      tmp = 1;
    } else {
      tmp = -1;
    }

    if (u1 > 0.0) {
      tmp_0 = 1;
    } else {
      tmp_0 = -1;
    }

    y = atan2(tmp, tmp_0);
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = atan2(u0, u1);
  }

  return y;
}

/* Function for MATLAB Function: '<S7>/Torque Allocation QP Normalized' */
static void ControlsMFE25_timeKeeper(real_T newTime_tv_sec, real_T
  newTime_tv_nsec, sdAmwXbnJnEmimT0NaJRtAD_Contr_T *savedTime,
  DW_ControlsMFE25_T *ControlsMFE25_DW)
{
  coderTimespec origTimespec;
  if (!ControlsMFE25_DW->savedTime_not_empty) {
    if (!ControlsMFE25_DW->freq_not_empty) {
      ControlsMFE25_DW->freq_not_empty = true;
      coderInitTimeFunctions(&ControlsMFE25_DW->freq);
    }

    coderTimeClockGettimeMonotonic(&origTimespec, ControlsMFE25_DW->freq);
    ControlsMFE25_DW->savedTime_not_empty = true;
  }

  savedTime->tv_sec = newTime_tv_sec;
  savedTime->tv_nsec = newTime_tv_nsec;
}

/* Function for MATLAB Function: '<S7>/Torque Allocation QP Normalized' */
static void ControlsMFE25_tic(sdAmwXbnJnEmimT0NaJRtAD_Contr_T *savedTime,
  DW_ControlsMFE25_T *ControlsMFE25_DW)
{
  coderTimespec origTimespec;
  if (!ControlsMFE25_DW->freq_not_empty) {
    ControlsMFE25_DW->freq_not_empty = true;
    coderInitTimeFunctions(&ControlsMFE25_DW->freq);
  }

  coderTimeClockGettimeMonotonic(&origTimespec, ControlsMFE25_DW->freq);
  ControlsMFE25_timeKeeper(origTimespec.tv_sec, origTimespec.tv_nsec, savedTime,
    ControlsMFE25_DW);
}

/* Function for MATLAB Function: '<S7>/Torque Allocation QP Normalized' */
static void ControlsMFE25_timeKeeper_n(sdAmwXbnJnEmimT0NaJRtAD_Contr_T
  *savedTime, real_T *outTime_tv_sec, real_T *outTime_tv_nsec,
  DW_ControlsMFE25_T *ControlsMFE25_DW)
{
  coderTimespec origTimespec;
  if (!ControlsMFE25_DW->savedTime_not_empty) {
    if (!ControlsMFE25_DW->freq_not_empty) {
      ControlsMFE25_DW->freq_not_empty = true;
      coderInitTimeFunctions(&ControlsMFE25_DW->freq);
    }

    coderTimeClockGettimeMonotonic(&origTimespec, ControlsMFE25_DW->freq);
    savedTime->tv_sec = origTimespec.tv_sec;
    savedTime->tv_nsec = origTimespec.tv_nsec;
  }

  *outTime_tv_sec = savedTime->tv_sec;
  *outTime_tv_nsec = savedTime->tv_nsec;
}

/* Function for MATLAB Function: '<S7>/Torque Allocation QP Normalized' */
static real_T ControlsMFE25_toc(sdAmwXbnJnEmimT0NaJRtAD_Contr_T *savedTime,
  DW_ControlsMFE25_T *ControlsMFE25_DW)
{
  coderTimespec origTimespec;
  real_T t;
  real_T tstart_tv_nsec;
  real_T tstart_tv_sec;
  ControlsMFE25_timeKeeper_n(savedTime, &tstart_tv_sec, &tstart_tv_nsec,
    ControlsMFE25_DW);
  if (!ControlsMFE25_DW->freq_not_empty) {
    ControlsMFE25_DW->freq_not_empty = true;
    coderInitTimeFunctions(&ControlsMFE25_DW->freq);
  }

  coderTimeClockGettimeMonotonic(&origTimespec, ControlsMFE25_DW->freq);
  t = (origTimespec.tv_nsec - tstart_tv_nsec) / 1.0E+9 + (origTimespec.tv_sec -
    tstart_tv_sec);
  return t;
}

/* Function for MATLAB Function: '<S7>/Torque Allocation QP Normalized' */
static void Control_modifyOverheadPhaseOne_(s18w5MCz6685sBFJwJZKJdG_Contr_T *obj)
{
  int32_T c;
  int32_T idx;
  int32_T idxStartIneq;
  int32_T idx_0;
  idxStartIneq = (uint8_T)obj->sizes[0];
  idx_0 = 0;
  for (idx = 0; idx < idxStartIneq; idx++) {
    obj->ATwset[idx_0 + 4] = 0.0;
    idx_0 += 5;
  }

  obj->Aineq[4] = -1.0;
  obj->indexLB[obj->sizes[3] - 1] = 5;
  obj->lb[4] = obj->SLACK0;
  idxStartIneq = obj->isActiveIdx[2];
  c = obj->nActiveConstr;
  idx_0 = 5 * obj->isActiveIdx[2];
  for (idx = idxStartIneq; idx <= c; idx++) {
    obj->ATwset[idx_0 - 1] = -1.0;
    idx_0 += 5;
  }

  idxStartIneq = obj->isActiveIdx[4] - 1;
  if (obj->nWConstr[4] > 0) {
    c = obj->sizesNormal[4];
    for (idx = c; idx >= 1; idx--) {
      idx_0 = idxStartIneq + idx;
      obj->isActiveConstr[idx_0] = obj->isActiveConstr[idx_0 - 1];
    }
  } else {
    obj->isActiveConstr[(obj->isActiveIdx[4] + obj->sizesNormal[4]) - 1] = false;
  }

  obj->isActiveConstr[obj->isActiveIdx[4] - 1] = false;
}

/* Function for MATLAB Function: '<S7>/Torque Allocation QP Normalized' */
static void ControlsMFE25_setProblemType(s18w5MCz6685sBFJwJZKJdG_Contr_T *obj,
  int32_T PROBLEM_TYPE)
{
  int32_T b;
  int32_T colOffsetATw;
  int32_T i;
  int32_T idx;
  int32_T idxUpperExisting;
  switch (PROBLEM_TYPE) {
   case 3:
    obj->nVar = 4;
    obj->mConstr = obj->mConstrOrig;
    if (obj->nWConstr[4] > 0) {
      idxUpperExisting = obj->isActiveIdx[4] - 1;
      b = (uint8_T)obj->sizesNormal[4];
      for (idx = 0; idx < b; idx++) {
        colOffsetATw = idxUpperExisting + idx;
        obj->isActiveConstr[(obj->isActiveIdxNormal[4] + idx) - 1] =
          obj->isActiveConstr[colOffsetATw];
        obj->isActiveConstr[colOffsetATw] = false;
      }
    }

    for (colOffsetATw = 0; colOffsetATw < 5; colOffsetATw++) {
      obj->sizes[colOffsetATw] = obj->sizesNormal[colOffsetATw];
    }

    for (colOffsetATw = 0; colOffsetATw < 6; colOffsetATw++) {
      obj->isActiveIdx[colOffsetATw] = obj->isActiveIdxNormal[colOffsetATw];
    }
    break;

   case 1:
    obj->nVar = 5;
    obj->mConstr = obj->mConstrOrig + 1;
    for (colOffsetATw = 0; colOffsetATw < 5; colOffsetATw++) {
      obj->sizes[colOffsetATw] = obj->sizesPhaseOne[colOffsetATw];
    }

    Control_modifyOverheadPhaseOne_(obj);
    for (colOffsetATw = 0; colOffsetATw < 6; colOffsetATw++) {
      obj->isActiveIdx[colOffsetATw] = obj->isActiveIdxPhaseOne[colOffsetATw];
    }
    break;

   case 2:
    obj->nVar = 4;
    obj->mConstr = 9;
    for (colOffsetATw = 0; colOffsetATw < 5; colOffsetATw++) {
      obj->sizes[colOffsetATw] = obj->sizesRegularized[colOffsetATw];
    }

    if (obj->probType != 4) {
      obj->Aineq[4] = -1.0;
      idxUpperExisting = 4;
      b = obj->sizesNormal[3] + 1;
      colOffsetATw = obj->sizesRegularized[3];
      for (idx = b; idx <= colOffsetATw; idx++) {
        idxUpperExisting++;
        obj->indexLB[idx - 1] = idxUpperExisting;
      }

      if (obj->nWConstr[4] > 0) {
        idxUpperExisting = (uint8_T)obj->sizesRegularized[4];
        for (idx = 0; idx < idxUpperExisting; idx++) {
          obj->isActiveConstr[obj->isActiveIdxRegularized[4] + idx] =
            obj->isActiveConstr[(obj->isActiveIdx[4] + idx) - 1];
        }
      }

      idxUpperExisting = obj->isActiveIdx[4];
      b = obj->isActiveIdxRegularized[4];
      if (idxUpperExisting <= b - 1) {
        memset(&obj->isActiveConstr[idxUpperExisting + -1], 0, (uint32_T)(b -
                idxUpperExisting) * sizeof(boolean_T));
      }

      obj->lb[4] = 0.0;
      idxUpperExisting = obj->isActiveIdx[2];
      b = obj->nActiveConstr;
      for (idx = idxUpperExisting; idx <= b; idx++) {
        colOffsetATw = (idx - 1) * 5 - 1;
        if (obj->Wid[idx - 1] == 3) {
          i = obj->Wlocalidx[idx - 1] + 3;
          if (i >= 5) {
            memset(&obj->ATwset[colOffsetATw + 5], 0, (uint32_T)(i - 4) * sizeof
                   (real_T));
          }

          obj->ATwset[(obj->Wlocalidx[idx - 1] + colOffsetATw) + 4] = -1.0;
          i = obj->Wlocalidx[idx - 1] + 5;
          if (i <= 4) {
            memset(&obj->ATwset[i + colOffsetATw], 0, (uint32_T)(((colOffsetATw
                      - i) - colOffsetATw) + 5) * sizeof(real_T));
          }
        }
      }
    }

    for (colOffsetATw = 0; colOffsetATw < 6; colOffsetATw++) {
      obj->isActiveIdx[colOffsetATw] = obj->isActiveIdxRegularized[colOffsetATw];
    }
    break;

   default:
    obj->nVar = 5;
    obj->mConstr = 10;
    for (colOffsetATw = 0; colOffsetATw < 5; colOffsetATw++) {
      obj->sizes[colOffsetATw] = obj->sizesRegPhaseOne[colOffsetATw];
    }

    Control_modifyOverheadPhaseOne_(obj);
    for (colOffsetATw = 0; colOffsetATw < 6; colOffsetATw++) {
      obj->isActiveIdx[colOffsetATw] = obj->isActiveIdxRegPhaseOne[colOffsetATw];
    }
    break;
  }

  obj->probType = PROBLEM_TYPE;
}

/* Function for MATLAB Function: '<S7>/Torque Allocation QP Normalized' */
static real_T ControlsMFE25_xnrm2(int32_T n, const real_T x[50], int32_T ix0)
{
  real_T y;
  int32_T k;
  y = 0.0;
  if (n >= 1) {
    if (n == 1) {
      y = fabs(x[ix0 - 1]);
    } else {
      real_T scale;
      int32_T kend;
      scale = 3.3121686421112381E-170;
      kend = (ix0 + n) - 1;
      for (k = ix0; k <= kend; k++) {
        real_T absxk;
        absxk = fabs(x[k - 1]);
        if (absxk > scale) {
          real_T t;
          t = scale / absxk;
          y = y * t * t + 1.0;
          scale = absxk;
        } else {
          real_T t;
          t = absxk / scale;
          y += t * t;
        }
      }

      y = scale * sqrt(y);
      if (rtIsNaN(y)) {
        k = ix0;
        int32_T exitg1;
        do {
          exitg1 = 0;
          if (k <= kend) {
            if (rtIsNaN(x[k - 1])) {
              exitg1 = 1;
            } else {
              k++;
            }
          } else {
            y = (rtInf);
            exitg1 = 1;
          }
        } while (exitg1 == 0);
      }
    }
  }

  return y;
}

real_T rt_hypotd_snf(real_T u0, real_T u1)
{
  real_T a;
  real_T b;
  real_T y;
  a = fabs(u0);
  b = fabs(u1);
  if (a < b) {
    a /= b;
    y = sqrt(a * a + 1.0) * b;
  } else if (a > b) {
    b /= a;
    y = sqrt(b * b + 1.0) * a;
  } else if (rtIsNaN(b)) {
    y = (rtNaN);
  } else {
    y = a * 1.4142135623730951;
  }

  return y;
}

/* Function for MATLAB Function: '<S7>/Torque Allocation QP Normalized' */
static real_T ControlsMFE25_xzlarfg(int32_T n, real_T *alpha1, real_T x[50],
  int32_T ix0)
{
  real_T a;
  real_T tau;
  real_T xnorm;
  int32_T c;
  int32_T d;
  int32_T knt;
  tau = 0.0;
  if (n > 0) {
    xnorm = ControlsMFE25_xnrm2(n - 1, x, ix0);
    if (xnorm != 0.0) {
      xnorm = rt_hypotd_snf(*alpha1, xnorm);
      if (*alpha1 >= 0.0) {
        xnorm = -xnorm;
      }

      if (fabs(xnorm) < 1.0020841800044864E-292) {
        knt = 0;
        d = (ix0 + n) - 2;
        do {
          knt++;
          for (c = ix0; c <= d; c++) {
            x[c - 1] *= 9.9792015476736E+291;
          }

          xnorm *= 9.9792015476736E+291;
          *alpha1 *= 9.9792015476736E+291;
        } while ((fabs(xnorm) < 1.0020841800044864E-292) && (knt < 20));

        xnorm = rt_hypotd_snf(*alpha1, ControlsMFE25_xnrm2(n - 1, x, ix0));
        if (*alpha1 >= 0.0) {
          xnorm = -xnorm;
        }

        tau = (xnorm - *alpha1) / xnorm;
        a = 1.0 / (*alpha1 - xnorm);
        for (c = ix0; c <= d; c++) {
          x[c - 1] *= a;
        }

        for (c = 0; c < knt; c++) {
          xnorm *= 1.0020841800044864E-292;
        }

        *alpha1 = xnorm;
      } else {
        tau = (xnorm - *alpha1) / xnorm;
        a = 1.0 / (*alpha1 - xnorm);
        c = (ix0 + n) - 2;
        for (knt = ix0; knt <= c; knt++) {
          x[knt - 1] *= a;
        }

        *alpha1 = xnorm;
      }
    }
  }

  return tau;
}

/* Function for MATLAB Function: '<S7>/Torque Allocation QP Normalized' */
static void ControlsMFE25_xzlarf(int32_T m, int32_T n, int32_T iv0, real_T tau,
  real_T C[50], int32_T ic0, real_T work[10])
{
  int32_T b_ia;
  int32_T coltop;
  int32_T lastc;
  int32_T lastv;
  if (tau != 0.0) {
    boolean_T exitg2;
    lastv = m;
    lastc = iv0 + m;
    while ((lastv > 0) && (C[lastc - 2] == 0.0)) {
      lastv--;
      lastc--;
    }

    lastc = n - 1;
    exitg2 = false;
    while ((!exitg2) && (lastc + 1 > 0)) {
      int32_T exitg1;
      coltop = lastc * 5 + ic0;
      b_ia = coltop;
      do {
        exitg1 = 0;
        if (b_ia <= (coltop + lastv) - 1) {
          if (C[b_ia - 1] != 0.0) {
            exitg1 = 1;
          } else {
            b_ia++;
          }
        } else {
          lastc--;
          exitg1 = 2;
        }
      } while (exitg1 == 0);

      if (exitg1 == 1) {
        exitg2 = true;
      }
    }
  } else {
    lastv = 0;
    lastc = -1;
  }

  if (lastv > 0) {
    real_T c;
    int32_T d;
    int32_T jy;
    if (lastc + 1 != 0) {
      if (lastc >= 0) {
        memset(&work[0], 0, (uint32_T)(lastc + 1) * sizeof(real_T));
      }

      jy = 5 * lastc + ic0;
      for (coltop = ic0; coltop <= jy; coltop += 5) {
        c = 0.0;
        d = coltop + lastv;
        for (b_ia = coltop; b_ia < d; b_ia++) {
          c += C[((iv0 + b_ia) - coltop) - 1] * C[b_ia - 1];
        }

        b_ia = div_nde_s32_floor(coltop - ic0, 5);
        work[b_ia] += c;
      }
    }

    if (!(-tau == 0.0)) {
      jy = ic0;
      for (coltop = 0; coltop <= lastc; coltop++) {
        c = work[coltop];
        if (c != 0.0) {
          c *= -tau;
          d = lastv + jy;
          for (b_ia = jy; b_ia < d; b_ia++) {
            C[b_ia - 1] += C[((iv0 + b_ia) - jy) - 1] * c;
          }
        }

        jy += 5;
      }
    }
  }
}

/* Function for MATLAB Function: '<S7>/Torque Allocation QP Normalized' */
static void ControlsMFE25_qrf(real_T A[50], int32_T m, int32_T n, int32_T nfxd,
  real_T tau[5])
{
  real_T work[10];
  real_T b_atmp;
  real_T tau_0;
  int32_T b;
  int32_T i;
  int32_T ii;
  int32_T mmi;
  memset(&work[0], 0, 10U * sizeof(real_T));
  b = (uint8_T)nfxd;
  for (i = 0; i < b; i++) {
    ii = i * 5 + i;
    mmi = m - i;
    if (i + 1 < m) {
      b_atmp = A[ii];
      tau_0 = ControlsMFE25_xzlarfg(mmi, &b_atmp, A, ii + 2);
      tau[i] = tau_0;
      A[ii] = b_atmp;
    } else {
      tau_0 = 0.0;
      tau[i] = 0.0;
    }

    if (i + 1 < n) {
      b_atmp = A[ii];
      A[ii] = 1.0;
      ControlsMFE25_xzlarf(mmi, (n - i) - 1, ii + 1, tau_0, A, ii + 6, work);
      A[ii] = b_atmp;
    }
  }
}

/* Function for MATLAB Function: '<S7>/Torque Allocation QP Normalized' */
static void ControlsMFE25_xgeqp3(real_T A[50], int32_T m, int32_T n, int32_T
  jpvt[10], real_T tau[5])
{
  real_T vn1[10];
  real_T vn2[10];
  real_T work[10];
  real_T s;
  real_T temp;
  real_T vn1_0;
  int32_T b_ix;
  int32_T i;
  int32_T itemp;
  int32_T ix;
  int32_T ix_tmp;
  int32_T iy;
  int32_T minmn;
  int32_T mmi;
  int32_T nfxd;
  int32_T pvt;
  int32_T temp_tmp;
  int32_T tmp;
  if (m <= n) {
    minmn = m;
  } else {
    minmn = n;
  }

  for (i = 0; i < 5; i++) {
    tau[i] = 0.0;
  }

  if (minmn < 1) {
    for (minmn = 0; minmn < n; minmn++) {
      jpvt[minmn] = minmn + 1;
    }
  } else {
    nfxd = -1;
    for (i = 0; i < n; i++) {
      if (jpvt[i] != 0) {
        nfxd++;
        if (i + 1 != nfxd + 1) {
          ix = i * 5;
          iy = nfxd * 5;
          for (mmi = 0; mmi < m; mmi++) {
            temp_tmp = ix + mmi;
            temp = A[temp_tmp];
            tmp = iy + mmi;
            A[temp_tmp] = A[tmp];
            A[tmp] = temp;
          }

          jpvt[i] = jpvt[nfxd];
          jpvt[nfxd] = i + 1;
        } else {
          jpvt[i] = i + 1;
        }
      } else {
        jpvt[i] = i + 1;
      }
    }

    if (nfxd + 1 <= minmn) {
      nfxd++;
    } else {
      nfxd = minmn;
    }

    for (i = 0; i < 5; i++) {
      tau[i] = 0.0;
    }

    ControlsMFE25_qrf(A, m, n, nfxd, tau);
    if (nfxd < minmn) {
      memset(&work[0], 0, 10U * sizeof(real_T));
      memset(&vn1[0], 0, 10U * sizeof(real_T));
      memset(&vn2[0], 0, 10U * sizeof(real_T));
      for (i = nfxd + 1; i <= n; i++) {
        vn1_0 = ControlsMFE25_xnrm2(m - nfxd, A, ((i - 1) * 5 + nfxd) + 1);
        vn1[i - 1] = vn1_0;
        vn2[i - 1] = vn1_0;
      }

      for (i = nfxd + 1; i <= minmn; i++) {
        ix_tmp = (i - 1) * 5;
        ix = (ix_tmp + i) - 1;
        iy = (n - i) + 1;
        mmi = m - i;
        if (iy < 1) {
          pvt = -2;
        } else {
          pvt = -1;
          if (iy > 1) {
            temp = fabs(vn1[i - 1]);
            for (itemp = 2; itemp <= iy; itemp++) {
              s = fabs(vn1[(i + itemp) - 2]);
              if (s > temp) {
                pvt = itemp - 2;
                temp = s;
              }
            }
          }
        }

        pvt += i;
        if (pvt + 1 != i) {
          b_ix = pvt * 5;
          for (itemp = 0; itemp < m; itemp++) {
            temp_tmp = b_ix + itemp;
            temp = A[temp_tmp];
            tmp = ix_tmp + itemp;
            A[temp_tmp] = A[tmp];
            A[tmp] = temp;
          }

          itemp = jpvt[pvt];
          jpvt[pvt] = jpvt[i - 1];
          jpvt[i - 1] = itemp;
          vn1[pvt] = vn1[i - 1];
          vn2[pvt] = vn2[i - 1];
        }

        if (i < m) {
          temp = A[ix];
          vn1_0 = ControlsMFE25_xzlarfg(mmi + 1, &temp, A, ix + 2);
          tau[i - 1] = vn1_0;
          A[ix] = temp;
        } else {
          vn1_0 = 0.0;
          tau[i - 1] = 0.0;
        }

        if (i < n) {
          temp = A[ix];
          A[ix] = 1.0;
          ControlsMFE25_xzlarf(mmi + 1, iy - 1, ix + 1, vn1_0, A, ix + 6, work);
          A[ix] = temp;
        }

        for (ix = i + 1; ix <= n; ix++) {
          iy = (ix - 1) * 5 + i;
          vn1_0 = vn1[ix - 1];
          if (vn1_0 != 0.0) {
            temp = fabs(A[iy - 1]) / vn1_0;
            temp = 1.0 - temp * temp;
            if (temp < 0.0) {
              temp = 0.0;
            }

            s = vn1_0 / vn2[ix - 1];
            s = s * s * temp;
            if (s <= 1.4901161193847656E-8) {
              if (i < m) {
                vn1_0 = ControlsMFE25_xnrm2(mmi, A, iy + 1);
                vn1[ix - 1] = vn1_0;
                vn2[ix - 1] = vn1_0;
              } else {
                vn1[ix - 1] = 0.0;
                vn2[ix - 1] = 0.0;
              }
            } else {
              vn1[ix - 1] = vn1_0 * sqrt(temp);
            }
          }
        }
      }
    }
  }
}

/* Function for MATLAB Function: '<S7>/Torque Allocation QP Normalized' */
static void ControlsMFE25_countsort(int32_T x[10], int32_T xLen, int32_T
  workspace[10], int32_T xMin, int32_T xMax)
{
  int32_T b;
  int32_T idxFill;
  int32_T maxOffset;
  if ((xLen > 1) && (xMax > xMin)) {
    int32_T idxEnd;
    int32_T idxStart;
    b = xMax - xMin;
    if (b >= 0) {
      memset(&workspace[0], 0, (uint32_T)(b + 1) * sizeof(int32_T));
    }

    maxOffset = b - 1;
    for (b = 0; b < xLen; b++) {
      idxFill = x[b] - xMin;
      workspace[idxFill]++;
    }

    for (b = 2; b <= maxOffset + 2; b++) {
      workspace[b - 1] += workspace[b - 2];
    }

    idxStart = 1;
    idxEnd = workspace[0];
    for (b = 0; b <= maxOffset; b++) {
      for (idxFill = idxStart; idxFill <= idxEnd; idxFill++) {
        x[idxFill - 1] = b + xMin;
      }

      idxStart = workspace[b] + 1;
      idxEnd = workspace[b + 1];
    }

    for (maxOffset = idxStart; maxOffset <= idxEnd; maxOffset++) {
      x[maxOffset - 1] = xMax;
    }
  }
}

/* Function for MATLAB Function: '<S7>/Torque Allocation QP Normalized' */
static void ControlsMFE25_removeConstr(s18w5MCz6685sBFJwJZKJdG_Contr_T *obj,
  int32_T idx_global)
{
  int32_T TYPE;
  int32_T idx;
  TYPE = obj->Wid[idx_global - 1] - 1;
  obj->isActiveConstr[(obj->isActiveIdx[obj->Wid[idx_global - 1] - 1] +
                       obj->Wlocalidx[idx_global - 1]) - 2] = false;
  if (idx_global < obj->nActiveConstr) {
    int32_T b;
    obj->Wid[idx_global - 1] = obj->Wid[obj->nActiveConstr - 1];
    obj->Wlocalidx[idx_global - 1] = obj->Wlocalidx[obj->nActiveConstr - 1];
    b = (uint8_T)obj->nVar;
    for (idx = 0; idx < b; idx++) {
      obj->ATwset[idx + 5 * (idx_global - 1)] = obj->ATwset[(obj->nActiveConstr
        - 1) * 5 + idx];
    }

    obj->bwset[idx_global - 1] = obj->bwset[obj->nActiveConstr - 1];
  }

  obj->nActiveConstr--;
  obj->nWConstr[TYPE]--;
}

/* Function for MATLAB Function: '<S7>/Torque Allocation QP Normalized' */
static void ControlsMF_RemoveDependentIneq_(s18w5MCz6685sBFJwJZKJdG_Contr_T
  *workingset, sisnsZ1AM9QRiMKnwqarOXF_Contr_T *qrmanager,
  su0bqVilpnfgpuAQ6xEtFDC_Contr_T *memspace, real_T tolfactor)
{
  real_T maxDiag;
  real_T tol;
  int32_T b;
  int32_T d;
  int32_T ix0;
  int32_T iy0;
  int32_T nActiveConstr;
  int32_T nDepIneq;
  int32_T nFixedConstr;
  int32_T nVar;
  nFixedConstr = workingset->nWConstr[0] + workingset->nWConstr[1];
  nVar = workingset->nVar;
  if ((workingset->nWConstr[2] + workingset->nWConstr[3]) + workingset->
      nWConstr[4] > 0) {
    if (workingset->nVar >= workingset->nActiveConstr) {
      nDepIneq = workingset->nVar;
    } else {
      nDepIneq = workingset->nActiveConstr;
    }

    tol = fmin(1.4901161193847656E-8, 2.2204460492503131E-15 * (real_T)nDepIneq)
      * tolfactor;
    for (nDepIneq = 0; nDepIneq < nFixedConstr; nDepIneq++) {
      qrmanager->jpvt[nDepIneq] = 1;
    }

    if (nFixedConstr + 1 <= workingset->nActiveConstr) {
      memset(&qrmanager->jpvt[nFixedConstr], 0, (uint32_T)
             (workingset->nActiveConstr - nFixedConstr) * sizeof(int32_T));
    }

    b = workingset->nActiveConstr;
    for (nDepIneq = 0; nDepIneq < b; nDepIneq++) {
      iy0 = 5 * nDepIneq;
      ix0 = 5 * nDepIneq;
      d = (uint8_T)nVar;
      for (nActiveConstr = 0; nActiveConstr < d; nActiveConstr++) {
        qrmanager->QR[iy0 + nActiveConstr] = workingset->ATwset[ix0 +
          nActiveConstr];
      }
    }

    if (workingset->nVar * workingset->nActiveConstr == 0) {
      qrmanager->mrows = workingset->nVar;
      qrmanager->ncols = workingset->nActiveConstr;
      qrmanager->minRowCol = 0;
    } else {
      qrmanager->usedPivoting = true;
      qrmanager->mrows = workingset->nVar;
      qrmanager->ncols = workingset->nActiveConstr;
      if (workingset->nVar <= workingset->nActiveConstr) {
        qrmanager->minRowCol = workingset->nVar;
      } else {
        qrmanager->minRowCol = workingset->nActiveConstr;
      }

      ControlsMFE25_xgeqp3(qrmanager->QR, workingset->nVar,
                           workingset->nActiveConstr, qrmanager->jpvt,
                           qrmanager->tau);
    }

    nDepIneq = 0;
    for (nActiveConstr = workingset->nActiveConstr - 1; nActiveConstr + 1 > nVar;
         nActiveConstr--) {
      nDepIneq++;
      memspace->workspace_int[nDepIneq - 1] = qrmanager->jpvt[nActiveConstr];
    }

    maxDiag = fabs(qrmanager->QR[0]);
    b = 0;
    for (nVar = 0; nVar < nActiveConstr; nVar++) {
      maxDiag = fmax(maxDiag, fabs(qrmanager->QR[b + 6]));
      b += 6;
    }

    if (nActiveConstr + 1 <= workingset->nVar) {
      nVar = 5 * nActiveConstr + nActiveConstr;
      while ((nActiveConstr + 1 > nFixedConstr) && (fabs(qrmanager->QR[nVar]) <
              tol * maxDiag)) {
        nDepIneq++;
        memspace->workspace_int[nDepIneq - 1] = qrmanager->jpvt[nActiveConstr];
        nActiveConstr--;
        nVar -= 6;
      }
    }

    ControlsMFE25_countsort(memspace->workspace_int, nDepIneq,
      memspace->workspace_sort, nFixedConstr + 1, workingset->nActiveConstr);
    for (nFixedConstr = nDepIneq; nFixedConstr >= 1; nFixedConstr--) {
      ControlsMFE25_removeConstr(workingset, memspace->
        workspace_int[nFixedConstr - 1]);
    }
  }
}

/* Function for MATLAB Function: '<S7>/Torque Allocation QP Normalized' */
static void ControlsMFE25_computeQ_(sisnsZ1AM9QRiMKnwqarOXF_Contr_T *obj,
  int32_T nrows)
{
  real_T work[5];
  int32_T c_ia;
  int32_T coltop;
  int32_T i;
  int32_T iQR0;
  int32_T ia;
  int32_T idx;
  int32_T itau;
  i = obj->minRowCol;
  for (idx = 0; idx < i; idx++) {
    iQR0 = 5 * idx + idx;
    ia = obj->mrows - idx;
    if (ia - 2 >= 0) {
      memcpy(&obj->Q[iQR0 + 1], &obj->QR[iQR0 + 1], (uint32_T)(ia - 1) * sizeof
             (real_T));
    }
  }

  idx = obj->mrows;
  iQR0 = obj->minRowCol;
  if (nrows >= 1) {
    for (itau = iQR0; itau < nrows; itau++) {
      ia = itau * 5;
      memset(&obj->Q[ia], 0, (uint32_T)idx * sizeof(real_T));
      obj->Q[ia + itau] = 1.0;
    }

    itau = obj->minRowCol - 1;
    for (i = 0; i < 5; i++) {
      work[i] = 0.0;
    }

    for (i = obj->minRowCol; i >= 1; i--) {
      int32_T lastc;
      iQR0 = ((i - 1) * 5 + i) - 1;
      if (i < nrows) {
        obj->Q[iQR0] = 1.0;
        ia = idx - i;
        if (obj->tau[itau] != 0.0) {
          boolean_T exitg2;
          lastc = iQR0 + ia;
          while ((ia + 1 > 0) && (obj->Q[lastc] == 0.0)) {
            ia--;
            lastc--;
          }

          lastc = (nrows - i) - 1;
          exitg2 = false;
          while ((!exitg2) && (lastc + 1 > 0)) {
            int32_T exitg1;
            coltop = (lastc * 5 + iQR0) + 6;
            c_ia = coltop;
            do {
              exitg1 = 0;
              if (c_ia <= coltop + ia) {
                if (obj->Q[c_ia - 1] != 0.0) {
                  exitg1 = 1;
                } else {
                  c_ia++;
                }
              } else {
                lastc--;
                exitg1 = 2;
              }
            } while (exitg1 == 0);

            if (exitg1 == 1) {
              exitg2 = true;
            }
          }
        } else {
          ia = -1;
          lastc = -1;
        }

        if (ia + 1 > 0) {
          real_T b_c;
          int32_T f;
          int32_T jy;
          if (lastc + 1 != 0) {
            if (lastc >= 0) {
              memset(&work[0], 0, (uint32_T)(lastc + 1) * sizeof(real_T));
            }

            jy = (5 * lastc + iQR0) + 6;
            for (coltop = iQR0 + 6; coltop <= jy; coltop += 5) {
              b_c = 0.0;
              f = coltop + ia;
              for (c_ia = coltop; c_ia <= f; c_ia++) {
                b_c += obj->Q[(iQR0 + c_ia) - coltop] * obj->Q[c_ia - 1];
              }

              c_ia = div_nde_s32_floor((coltop - iQR0) - 6, 5);
              work[c_ia] += b_c;
            }
          }

          if (!(-obj->tau[itau] == 0.0)) {
            jy = iQR0 + 6;
            for (coltop = 0; coltop <= lastc; coltop++) {
              b_c = work[coltop];
              if (b_c != 0.0) {
                b_c *= -obj->tau[itau];
                f = ia + jy;
                for (c_ia = jy; c_ia <= f; c_ia++) {
                  obj->Q[c_ia - 1] += obj->Q[(iQR0 + c_ia) - jy] * b_c;
                }
              }

              jy += 5;
            }
          }
        }
      }

      if (i < idx) {
        lastc = ((iQR0 + idx) - i) + 1;
        for (ia = iQR0 + 2; ia <= lastc; ia++) {
          obj->Q[ia - 1] *= -obj->tau[itau];
        }
      }

      obj->Q[iQR0] = 1.0 - obj->tau[itau];
      lastc = (uint8_T)(i - 1);
      for (ia = 0; ia < lastc; ia++) {
        obj->Q[(iQR0 - ia) - 1] = 0.0;
      }

      itau--;
    }
  }
}

/* Function for MATLAB Function: '<S7>/Torque Allocation QP Normalized' */
static int32_T ControlsMFE25_rank(const real_T qrmanager_QR[50], int32_T
  qrmanager_mrows, int32_T qrmanager_ncols)
{
  int32_T minmn;
  int32_T r;
  r = 0;
  if (qrmanager_mrows < qrmanager_ncols) {
    minmn = 4;
  } else {
    minmn = qrmanager_ncols;
  }

  if (minmn > 0) {
    real_T tol;
    int32_T tmp;
    if (qrmanager_mrows >= qrmanager_ncols) {
      tmp = qrmanager_mrows;
    } else {
      tmp = qrmanager_ncols;
    }

    tol = fmin(1.4901161193847656E-8, 2.2204460492503131E-15 * (real_T)tmp) *
      fabs(qrmanager_QR[0]);
    while ((r < minmn) && (!(fabs(qrmanager_QR[5 * r + r]) <= tol))) {
      r++;
    }
  }

  return r;
}

/* Function for MATLAB Function: '<S7>/Torque Allocation QP Normalized' */
static real_T Controls_maxConstraintViolation(s18w5MCz6685sBFJwJZKJdG_Contr_T
  *obj, const real_T x[50])
{
  real_T v;
  int32_T e;
  int32_T ia;
  if (obj->probType == 2) {
    obj->maxConstrWorkspace[0] = obj->bineq;
    obj->maxConstrWorkspace[0] = -obj->maxConstrWorkspace[0];
    obj->maxConstrWorkspace[0] += ((obj->Aineq[0] * x[10] + obj->Aineq[1] * x[11])
      + obj->Aineq[2] * x[12]) + obj->Aineq[3] * x[13];
    obj->maxConstrWorkspace[0] -= x[14];
    v = fmax(0.0, obj->maxConstrWorkspace[0]);
  } else {
    real_T b_c;
    obj->maxConstrWorkspace[0] = obj->bineq;
    obj->maxConstrWorkspace[0] = -obj->maxConstrWorkspace[0];
    b_c = 0.0;
    e = obj->nVar;
    for (ia = 1; ia <= e; ia++) {
      b_c += obj->Aineq[ia - 1] * x[ia + 9];
    }

    obj->maxConstrWorkspace[0] += b_c;
    v = fmax(0.0, obj->maxConstrWorkspace[0]);
  }

  if (obj->sizes[3] > 0) {
    ia = (uint8_T)obj->sizes[3];
    for (e = 0; e < ia; e++) {
      v = fmax(v, -x[obj->indexLB[e] + 9] - obj->lb[obj->indexLB[e] - 1]);
    }
  }

  if (obj->sizes[4] > 0) {
    ia = (uint8_T)obj->sizes[4];
    for (e = 0; e < ia; e++) {
      v = fmax(v, x[obj->indexUB[e] + 9] - obj->ub[obj->indexUB[e] - 1]);
    }
  }

  if (obj->sizes[0] > 0) {
    ia = (uint8_T)obj->sizes[0];
    for (e = 0; e < ia; e++) {
      v = fmax(v, fabs(x[obj->indexFixed[e] + 9] - obj->ub[obj->indexFixed[e] -
                       1]));
    }
  }

  return v;
}

/* Function for MATLAB Function: '<S7>/Torque Allocation QP Normalized' */
static boolean_T Control_feasibleX0ForWorkingSet(real_T workspace[50], real_T
  xCurrent[5], s18w5MCz6685sBFJwJZKJdG_Contr_T *workingset,
  sisnsZ1AM9QRiMKnwqarOXF_Contr_T *qrmanager)
{
  real_T B[50];
  real_T c_c;
  real_T temp;
  int32_T c_ix;
  int32_T exitg1;
  int32_T h_k;
  int32_T iAcol;
  int32_T ia;
  int32_T ix;
  int32_T iy;
  int32_T mWConstr;
  int32_T nVar;
  int32_T rankQR;
  int32_T tmp;
  boolean_T guard1;
  boolean_T nonDegenerateWset;
  mWConstr = workingset->nActiveConstr;
  nVar = workingset->nVar;
  nonDegenerateWset = true;
  if (workingset->nActiveConstr != 0) {
    if (workingset->nActiveConstr >= workingset->nVar) {
      c_ix = (uint8_T)workingset->nVar;
      for (rankQR = 0; rankQR < c_ix; rankQR++) {
        ix = 5 * rankQR;
        for (h_k = 0; h_k < mWConstr; h_k++) {
          qrmanager->QR[h_k + ix] = workingset->ATwset[5 * h_k + rankQR];
        }
      }

      memset(&qrmanager->jpvt[0], 0, (uint8_T)workingset->nVar * sizeof(int32_T));
      if (workingset->nActiveConstr * workingset->nVar == 0) {
        qrmanager->mrows = workingset->nActiveConstr;
        qrmanager->ncols = workingset->nVar;
        qrmanager->minRowCol = 0;
      } else {
        qrmanager->usedPivoting = true;
        qrmanager->mrows = workingset->nActiveConstr;
        qrmanager->ncols = workingset->nVar;
        if (workingset->nActiveConstr <= workingset->nVar) {
          qrmanager->minRowCol = workingset->nActiveConstr;
        } else {
          qrmanager->minRowCol = workingset->nVar;
        }

        ControlsMFE25_xgeqp3(qrmanager->QR, workingset->nActiveConstr,
                             workingset->nVar, qrmanager->jpvt, qrmanager->tau);
      }

      ControlsMFE25_computeQ_(qrmanager, qrmanager->mrows);
      rankQR = ControlsMFE25_rank(qrmanager->QR, qrmanager->mrows,
        qrmanager->ncols);
      for (h_k = 0; h_k < mWConstr; h_k++) {
        workspace[h_k] = workingset->bwset[h_k];
        workspace[h_k + 10] = workingset->bwset[h_k];
      }

      iy = (workingset->nActiveConstr - 1) * 5 + 1;
      for (h_k = 1; h_k <= iy; h_k += 5) {
        temp = 0.0;
        ia = h_k + nVar;
        for (c_ix = h_k; c_ix < ia; c_ix++) {
          temp += workingset->ATwset[c_ix - 1] * xCurrent[c_ix - h_k];
        }

        ia = div_nde_s32_floor(h_k - 1, 5);
        workspace[ia] -= temp;
      }

      memcpy(&B[0], &workspace[0], 50U * sizeof(real_T));
      for (h_k = 0; h_k <= 10; h_k += 10) {
        ix = h_k + nVar;
        for (c_ix = h_k + 1; c_ix <= ix; c_ix++) {
          workspace[c_ix - 1] = 0.0;
        }
      }

      iy = -1;
      for (h_k = 0; h_k <= 10; h_k += 10) {
        iAcol = -1;
        ia = h_k + nVar;
        for (c_ix = h_k + 1; c_ix <= ia; c_ix++) {
          temp = 0.0;
          for (ix = 0; ix < mWConstr; ix++) {
            temp += qrmanager->Q[(ix + iAcol) + 1] * B[(ix + iy) + 1];
          }

          workspace[c_ix - 1] += temp;
          iAcol += 5;
        }

        iy += 10;
      }

      for (mWConstr = 0; mWConstr < 2; mWConstr++) {
        ix = 10 * mWConstr - 1;
        for (h_k = rankQR; h_k >= 1; h_k--) {
          iy = (h_k - 1) * 5;
          ia = h_k + ix;
          temp = workspace[ia];
          if (temp != 0.0) {
            workspace[ia] = temp / qrmanager->QR[(h_k + iy) - 1];
            iAcol = (uint8_T)(h_k - 1);
            for (c_ix = 0; c_ix < iAcol; c_ix++) {
              tmp = (c_ix + ix) + 1;
              workspace[tmp] -= qrmanager->QR[c_ix + iy] * workspace[ia];
            }
          }
        }
      }

      for (mWConstr = rankQR + 1; mWConstr <= nVar; mWConstr++) {
        workspace[mWConstr - 1] = 0.0;
        workspace[mWConstr + 9] = 0.0;
      }

      mWConstr = (uint8_T)workingset->nVar;
      for (rankQR = 0; rankQR < mWConstr; rankQR++) {
        workspace[qrmanager->jpvt[rankQR] + 19] = workspace[rankQR];
      }

      mWConstr = (uint8_T)workingset->nVar;
      for (rankQR = 0; rankQR < mWConstr; rankQR++) {
        workspace[rankQR] = workspace[rankQR + 20];
      }

      mWConstr = (uint8_T)workingset->nVar;
      for (rankQR = 0; rankQR < mWConstr; rankQR++) {
        workspace[qrmanager->jpvt[rankQR] + 19] = workspace[rankQR + 10];
      }

      mWConstr = (uint8_T)workingset->nVar;
      for (rankQR = 0; rankQR < mWConstr; rankQR++) {
        workspace[rankQR + 10] = workspace[rankQR + 20];
      }
    } else {
      if (workingset->nActiveConstr - 1 >= 0) {
        memset(&qrmanager->jpvt[0], 0, (uint32_T)workingset->nActiveConstr *
               sizeof(int32_T));
      }

      guard1 = false;
      if (workingset->nVar * workingset->nActiveConstr > 0) {
        for (rankQR = 0; rankQR < mWConstr; rankQR++) {
          c_ix = 5 * rankQR;
          ix = 5 * rankQR;
          iy = (uint8_T)nVar;
          for (h_k = 0; h_k < iy; h_k++) {
            qrmanager->QR[ix + h_k] = workingset->ATwset[c_ix + h_k];
          }
        }

        guard1 = true;
      } else if (workingset->nVar * workingset->nActiveConstr == 0) {
        qrmanager->mrows = workingset->nVar;
        qrmanager->ncols = workingset->nActiveConstr;
        qrmanager->minRowCol = 0;
      } else {
        guard1 = true;
      }

      if (guard1) {
        qrmanager->usedPivoting = true;
        qrmanager->mrows = workingset->nVar;
        qrmanager->ncols = workingset->nActiveConstr;
        if (workingset->nVar <= workingset->nActiveConstr) {
          qrmanager->minRowCol = workingset->nVar;
        } else {
          qrmanager->minRowCol = workingset->nActiveConstr;
        }

        ControlsMFE25_xgeqp3(qrmanager->QR, workingset->nVar,
                             workingset->nActiveConstr, qrmanager->jpvt,
                             qrmanager->tau);
      }

      ControlsMFE25_computeQ_(qrmanager, qrmanager->minRowCol);
      rankQR = ControlsMFE25_rank(qrmanager->QR, qrmanager->mrows,
        qrmanager->ncols);
      for (h_k = 0; h_k < mWConstr; h_k++) {
        ix = (qrmanager->jpvt[h_k] - 1) * 5;
        temp = 0.0;
        iAcol = (uint8_T)nVar;
        for (c_ix = 0; c_ix < iAcol; c_ix++) {
          temp += workingset->ATwset[ix + c_ix] * xCurrent[c_ix];
        }

        workspace[h_k] = workingset->bwset[qrmanager->jpvt[h_k] - 1] - temp;
        workspace[h_k + 10] = workingset->bwset[qrmanager->jpvt[h_k] - 1];
      }

      iy = (uint8_T)rankQR;
      for (mWConstr = 0; mWConstr < 2; mWConstr++) {
        ix = 10 * mWConstr;
        for (h_k = 0; h_k < iy; h_k++) {
          iAcol = 5 * h_k;
          ia = h_k + ix;
          temp = workspace[ia];
          for (c_ix = 0; c_ix < h_k; c_ix++) {
            temp -= qrmanager->QR[c_ix + iAcol] * workspace[c_ix + ix];
          }

          workspace[ia] = temp / qrmanager->QR[h_k + iAcol];
        }
      }

      memcpy(&B[0], &workspace[0], 50U * sizeof(real_T));
      for (mWConstr = 0; mWConstr <= 10; mWConstr += 10) {
        c_ix = mWConstr + nVar;
        for (h_k = mWConstr + 1; h_k <= c_ix; h_k++) {
          workspace[h_k - 1] = 0.0;
        }
      }

      ix = 1;
      for (mWConstr = 0; mWConstr <= 10; mWConstr += 10) {
        iy = -1;
        iAcol = ix + rankQR;
        for (h_k = ix; h_k < iAcol; h_k++) {
          ia = mWConstr + nVar;
          for (c_ix = mWConstr + 1; c_ix <= ia; c_ix++) {
            workspace[c_ix - 1] += qrmanager->Q[(iy + c_ix) - mWConstr] * B[h_k
              - 1];
          }

          iy += 5;
        }

        ix += 10;
      }
    }

    rankQR = 0;
    do {
      exitg1 = 0;
      if (rankQR <= (uint8_T)nVar - 1) {
        if (rtIsInf(workspace[rankQR]) || rtIsNaN(workspace[rankQR])) {
          nonDegenerateWset = false;
          exitg1 = 1;
        } else if (rtIsInf(workspace[rankQR + 10]) || rtIsNaN(workspace[rankQR +
                    10])) {
          nonDegenerateWset = false;
          exitg1 = 1;
        } else {
          rankQR++;
        }
      } else {
        for (rankQR = 0; rankQR < nVar; rankQR++) {
          workspace[rankQR] += xCurrent[rankQR];
        }

        if (workingset->probType == 2) {
          workingset->maxConstrWorkspace[0] = workingset->bineq;
          workingset->maxConstrWorkspace[0] = -workingset->maxConstrWorkspace[0];
          workingset->maxConstrWorkspace[0] += ((workingset->Aineq[0] *
            workspace[0] + workingset->Aineq[1] * workspace[1]) +
            workingset->Aineq[2] * workspace[2]) + workingset->Aineq[3] *
            workspace[3];
          workingset->maxConstrWorkspace[0] -= workspace[4];
          temp = fmax(0.0, workingset->maxConstrWorkspace[0]);
        } else {
          workingset->maxConstrWorkspace[0] = workingset->bineq;
          workingset->maxConstrWorkspace[0] = -workingset->maxConstrWorkspace[0];
          c_c = 0.0;
          ix = workingset->nVar;
          for (mWConstr = 1; mWConstr <= ix; mWConstr++) {
            c_c += workingset->Aineq[mWConstr - 1] * workspace[mWConstr - 1];
          }

          workingset->maxConstrWorkspace[0] += c_c;
          temp = fmax(0.0, workingset->maxConstrWorkspace[0]);
        }

        if (workingset->sizes[3] > 0) {
          mWConstr = (uint8_T)workingset->sizes[3];
          for (rankQR = 0; rankQR < mWConstr; rankQR++) {
            temp = fmax(temp, -workspace[workingset->indexLB[rankQR] - 1] -
                        workingset->lb[workingset->indexLB[rankQR] - 1]);
          }
        }

        if (workingset->sizes[4] > 0) {
          mWConstr = (uint8_T)workingset->sizes[4];
          for (rankQR = 0; rankQR < mWConstr; rankQR++) {
            temp = fmax(temp, workspace[workingset->indexUB[rankQR] - 1] -
                        workingset->ub[workingset->indexUB[rankQR] - 1]);
          }
        }

        if (workingset->sizes[0] > 0) {
          mWConstr = (uint8_T)workingset->sizes[0];
          for (rankQR = 0; rankQR < mWConstr; rankQR++) {
            temp = fmax(temp, fabs(workspace[workingset->indexFixed[rankQR] - 1]
              - workingset->ub[workingset->indexFixed[rankQR] - 1]));
          }
        }

        c_c = Controls_maxConstraintViolation(workingset, workspace);
        if ((temp <= 2.2204460492503131E-16) || (temp < c_c)) {
          memcpy(&xCurrent[0], &workspace[0], (uint8_T)nVar * sizeof(real_T));
        } else {
          memcpy(&xCurrent[0], &workspace[10], (uint8_T)nVar * sizeof(real_T));
        }

        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  return nonDegenerateWset;
}

/* Function for MATLAB Function: '<S7>/Torque Allocation QP Normalized' */
static int32_T Controls_ComputeNumDependentEq_(sisnsZ1AM9QRiMKnwqarOXF_Contr_T
  *qrmanager, const real_T beqf[10], int32_T mConstr, int32_T nVar)
{
  real_T qtb;
  real_T tol;
  int32_T b;
  int32_T ix;
  int32_T numDependent;
  int32_T totalRank;
  boolean_T exitg1;
  numDependent = mConstr - nVar;
  if (numDependent <= 0) {
    numDependent = 0;
  }

  memset(&qrmanager->jpvt[0], 0, (uint8_T)nVar * sizeof(int32_T));
  if (mConstr * nVar == 0) {
    qrmanager->mrows = mConstr;
    qrmanager->ncols = nVar;
    qrmanager->minRowCol = 0;
  } else {
    qrmanager->usedPivoting = true;
    qrmanager->mrows = mConstr;
    qrmanager->ncols = nVar;
    if (mConstr <= nVar) {
      qrmanager->minRowCol = mConstr;
    } else {
      qrmanager->minRowCol = nVar;
    }

    ControlsMFE25_xgeqp3(qrmanager->QR, mConstr, nVar, qrmanager->jpvt,
                         qrmanager->tau);
  }

  if (mConstr >= nVar) {
    totalRank = mConstr;
  } else {
    totalRank = nVar;
  }

  tol = fmin(1.4901161193847656E-8, 2.2204460492503131E-15 * (real_T)totalRank);
  if (nVar <= mConstr) {
    totalRank = nVar;
  } else {
    totalRank = mConstr;
  }

  totalRank += (totalRank - 1) * 5;
  while ((totalRank > 0) && (fabs(qrmanager->QR[totalRank - 1]) <= tol * fabs
          (qrmanager->QR[0]))) {
    totalRank -= 6;
    numDependent++;
  }

  if (numDependent > 0) {
    ControlsMFE25_computeQ_(qrmanager, qrmanager->mrows);
    b = 0;
    exitg1 = false;
    while ((!exitg1) && (b <= numDependent - 1)) {
      ix = ((mConstr - b) - 1) * 5;
      qtb = 0.0;
      for (totalRank = 0; totalRank < mConstr; totalRank++) {
        qtb += qrmanager->Q[ix + totalRank] * beqf[totalRank];
      }

      if (fabs(qtb) >= tol) {
        numDependent = -1;
        exitg1 = true;
      } else {
        b++;
      }
    }
  }

  return numDependent;
}

/* Function for MATLAB Function: '<S7>/Torque Allocation QP Normalized' */
static real_T Contro_maxConstraintViolation_m(s18w5MCz6685sBFJwJZKJdG_Contr_T
  *obj, const real_T x[5])
{
  real_T v;
  int32_T e;
  int32_T ia;
  if (obj->probType == 2) {
    obj->maxConstrWorkspace[0] = obj->bineq;
    obj->maxConstrWorkspace[0] = -obj->maxConstrWorkspace[0];
    obj->maxConstrWorkspace[0] += ((obj->Aineq[0] * x[0] + obj->Aineq[1] * x[1])
      + obj->Aineq[2] * x[2]) + obj->Aineq[3] * x[3];
    obj->maxConstrWorkspace[0] -= x[4];
    v = fmax(0.0, obj->maxConstrWorkspace[0]);
  } else {
    real_T b_c;
    obj->maxConstrWorkspace[0] = obj->bineq;
    obj->maxConstrWorkspace[0] = -obj->maxConstrWorkspace[0];
    b_c = 0.0;
    e = obj->nVar;
    for (ia = 1; ia <= e; ia++) {
      b_c += obj->Aineq[ia - 1] * x[ia - 1];
    }

    obj->maxConstrWorkspace[0] += b_c;
    v = fmax(0.0, obj->maxConstrWorkspace[0]);
  }

  if (obj->sizes[3] > 0) {
    ia = (uint8_T)obj->sizes[3];
    for (e = 0; e < ia; e++) {
      v = fmax(v, -x[obj->indexLB[e] - 1] - obj->lb[obj->indexLB[e] - 1]);
    }
  }

  if (obj->sizes[4] > 0) {
    ia = (uint8_T)obj->sizes[4];
    for (e = 0; e < ia; e++) {
      v = fmax(v, x[obj->indexUB[e] - 1] - obj->ub[obj->indexUB[e] - 1]);
    }
  }

  if (obj->sizes[0] > 0) {
    ia = (uint8_T)obj->sizes[0];
    for (e = 0; e < ia; e++) {
      v = fmax(v, fabs(x[obj->indexFixed[e] - 1] - obj->ub[obj->indexFixed[e] -
                       1]));
    }
  }

  return v;
}

/* Function for MATLAB Function: '<S7>/Torque Allocation QP Normalized' */
static void ControlsMFE_IndexOfDependentEq_(int32_T depIdx[10], int32_T mFixed,
  int32_T nDep, sisnsZ1AM9QRiMKnwqarOXF_Contr_T *qrmanager, int32_T mRows,
  int32_T nCols)
{
  int32_T idx;
  for (idx = 0; idx < mFixed; idx++) {
    qrmanager->jpvt[idx] = 1;
  }

  if (mFixed + 1 <= nCols) {
    memset(&qrmanager->jpvt[mFixed], 0, (uint32_T)(nCols - mFixed) * sizeof
           (int32_T));
  }

  if (mRows * nCols == 0) {
    qrmanager->mrows = mRows;
    qrmanager->ncols = nCols;
    qrmanager->minRowCol = 0;
  } else {
    qrmanager->usedPivoting = true;
    qrmanager->mrows = mRows;
    qrmanager->ncols = nCols;
    if (mRows <= nCols) {
      qrmanager->minRowCol = mRows;
    } else {
      qrmanager->minRowCol = nCols;
    }

    ControlsMFE25_xgeqp3(qrmanager->QR, mRows, nCols, qrmanager->jpvt,
                         qrmanager->tau);
  }

  for (idx = 0; idx < nDep; idx++) {
    depIdx[idx] = qrmanager->jpvt[(nCols - nDep) + idx];
  }
}

/* Function for MATLAB Function: '<S7>/Torque Allocation QP Normalized' */
static void ControlsMFE25_removeEqConstr(const s18w5MCz6685sBFJwJZKJdG_Contr_T
  *obj, int32_T idx_global)
{
  int32_T totalEq;
  totalEq = obj->nWConstr[0] + obj->nWConstr[1];
  if ((totalEq != 0) && (idx_global <= totalEq)) {
    /* Check node always fails. would cause program termination and was eliminated */
  }
}

/* Function for MATLAB Function: '<S7>/Torque Allocation QP Normalized' */
static void ControlsMFE2_PresolveWorkingSet(sF7ecKzAoqUt0jrk31NyRZH_Contr_T
  *solution, su0bqVilpnfgpuAQ6xEtFDC_Contr_T *memspace,
  s18w5MCz6685sBFJwJZKJdG_Contr_T *workingset, sisnsZ1AM9QRiMKnwqarOXF_Contr_T
  *qrmanager)
{
  real_T constrViolation;
  int32_T c;
  int32_T i;
  int32_T idxEndIneq;
  int32_T idxEndIneq_0;
  int32_T idxStartIneq;
  int32_T ix0;
  int32_T nVar;
  boolean_T guard1;
  boolean_T okWorkingSet;
  solution->state = 82;
  qrmanager->ldq = 5;
  memset(&qrmanager->QR[0], 0, 50U * sizeof(real_T));
  memset(&qrmanager->Q[0], 0, 25U * sizeof(real_T));
  for (i = 0; i < 10; i++) {
    qrmanager->jpvt[i] = 0;
  }

  qrmanager->mrows = 0;
  qrmanager->ncols = 0;
  for (i = 0; i < 5; i++) {
    qrmanager->tau[i] = 0.0;
  }

  qrmanager->minRowCol = 0;
  qrmanager->usedPivoting = false;
  c = 0;
  if (workingset->nWConstr[0] > 0) {
    c = (uint8_T)workingset->nWConstr[0];
    nVar = (uint8_T)workingset->nVar;
    idxStartIneq = 0;
    for (i = 0; i < c; i++) {
      idxEndIneq_0 = 0;
      for (idxEndIneq = 0; idxEndIneq < nVar; idxEndIneq++) {
        qrmanager->QR[idxEndIneq_0 + i] = workingset->ATwset[idxEndIneq +
          idxStartIneq];
        idxEndIneq_0 += 5;
      }

      idxStartIneq += 5;
    }

    c = Controls_ComputeNumDependentEq_(qrmanager, workingset->bwset,
      workingset->nWConstr[0], workingset->nVar);
    if (c > 0) {
      idxStartIneq = (uint8_T)workingset->nWConstr[0];
      for (i = 0; i < idxStartIneq; i++) {
        idxEndIneq_0 = 5 * i;
        ix0 = 5 * i;
        for (idxEndIneq = 0; idxEndIneq < nVar; idxEndIneq++) {
          qrmanager->QR[idxEndIneq_0 + idxEndIneq] = workingset->ATwset[ix0 +
            idxEndIneq];
        }
      }

      ControlsMFE_IndexOfDependentEq_(memspace->workspace_int,
        workingset->nWConstr[0], c, qrmanager, workingset->nVar,
        workingset->nWConstr[0]);
      ControlsMFE25_countsort(memspace->workspace_int, c,
        memspace->workspace_sort, 1, workingset->nWConstr[0]);
      for (nVar = c; nVar >= 1; nVar--) {
        ControlsMFE25_removeEqConstr(workingset, memspace->workspace_int[nVar -
          1]);
      }
    }
  }

  if ((c != -1) && (workingset->nActiveConstr <= 5)) {
    ControlsMF_RemoveDependentIneq_(workingset, qrmanager, memspace, 1.0);
    okWorkingSet = Control_feasibleX0ForWorkingSet(memspace->workspace_float,
      solution->xstar, workingset, qrmanager);
    guard1 = false;
    if (!okWorkingSet) {
      ControlsMF_RemoveDependentIneq_(workingset, qrmanager, memspace, 10.0);
      okWorkingSet = Control_feasibleX0ForWorkingSet(memspace->workspace_float,
        solution->xstar, workingset, qrmanager);
      if (!okWorkingSet) {
        solution->state = -7;
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }

    if (guard1) {
      if (workingset->nWConstr[0] + workingset->nWConstr[1] == workingset->nVar)
      {
        constrViolation = Contro_maxConstraintViolation_m(workingset,
          solution->xstar);
        if (constrViolation > 1.0E-8) {
          solution->state = -2;
        }
      }
    }
  } else {
    solution->state = -3;
    i = (workingset->nWConstr[0] + workingset->nWConstr[1]) + 1;
    idxEndIneq = workingset->nActiveConstr;
    for (nVar = i; nVar <= idxEndIneq; nVar++) {
      workingset->isActiveConstr[(workingset->isActiveIdx[workingset->Wid[nVar -
        1] - 1] + workingset->Wlocalidx[nVar - 1]) - 2] = false;
    }

    workingset->nWConstr[2] = 0;
    workingset->nWConstr[3] = 0;
    workingset->nWConstr[4] = 0;
    workingset->nActiveConstr = workingset->nWConstr[0] + workingset->nWConstr[1];
  }
}

/* Function for MATLAB Function: '<S7>/Torque Allocation QP Normalized' */
static void ControlsMFE25_xgemv(int32_T m, int32_T n, const real_T A[16],
  int32_T lda, const real_T x[5], real_T y[4])
{
  int32_T b_iy;
  int32_T ia;
  if ((m != 0) && (n != 0)) {
    int32_T b;
    int32_T ix;
    if (m - 1 >= 0) {
      memset(&y[0], 0, (uint32_T)m * sizeof(real_T));
    }

    ix = 0;
    b = (n - 1) * lda + 1;
    for (b_iy = 1; lda < 0 ? b_iy >= b : b_iy <= b; b_iy += lda) {
      int32_T c;
      c = b_iy + m;
      for (ia = b_iy; ia < c; ia++) {
        int32_T tmp;
        tmp = ia - b_iy;
        y[tmp] += A[ia - 1] * x[ix];
      }

      ix++;
    }
  }
}

/* Function for MATLAB Function: '<S7>/Torque Allocation QP Normalized' */
static void ControlsMFE_computeGrad_StoreHx(szdozZxcClCeUpd1TsA9nJF_Contr_T *obj,
  const real_T H[16], const real_T f[4], const real_T x[5])
{
  int32_T b_ixlast;
  int32_T idx;
  switch (obj->objtype) {
   case 5:
    if (obj->nvar - 2 >= 0) {
      memset(&obj->grad[0], 0, (uint32_T)(obj->nvar - 1) * sizeof(real_T));
    }

    obj->grad[obj->nvar - 1] = obj->gammaScalar;
    break;

   case 3:
    ControlsMFE25_xgemv(obj->nvar, obj->nvar, H, obj->nvar, x, obj->Hx);
    if (obj->nvar - 1 >= 0) {
      memcpy(&obj->grad[0], &obj->Hx[0], (uint32_T)obj->nvar * sizeof(real_T));
    }

    if (obj->hasLinear && (obj->nvar >= 1)) {
      b_ixlast = obj->nvar;
      for (idx = 0; idx < b_ixlast; idx++) {
        obj->grad[idx] += f[idx];
      }
    }
    break;

   default:
    ControlsMFE25_xgemv(obj->nvar, obj->nvar, H, obj->nvar, x, obj->Hx);
    b_ixlast = obj->nvar + 1;
    for (idx = b_ixlast; idx < 5; idx++) {
      obj->Hx[idx - 1] = x[idx - 1] * 0.0;
    }

    obj->grad[0] = obj->Hx[0];
    obj->grad[1] = obj->Hx[1];
    obj->grad[2] = obj->Hx[2];
    obj->grad[3] = obj->Hx[3];
    if (obj->hasLinear && (obj->nvar >= 1)) {
      b_ixlast = obj->nvar;
      for (idx = 0; idx < b_ixlast; idx++) {
        obj->grad[idx] += f[idx];
      }
    }
    break;
  }
}

/* Function for MATLAB Function: '<S7>/Torque Allocation QP Normalized' */
static real_T ControlsMFE_computeFval_ReuseHx(const
  szdozZxcClCeUpd1TsA9nJF_Contr_T *obj, real_T workspace[50], const real_T f[4],
  const real_T x[5])
{
  real_T val;
  int32_T k;
  switch (obj->objtype) {
   case 5:
    val = x[obj->nvar - 1] * obj->gammaScalar;
    break;

   case 3:
    {
      if (obj->hasLinear) {
        int32_T ixlast;
        ixlast = obj->nvar;
        for (k = 0; k < ixlast; k++) {
          workspace[k] = 0.5 * obj->Hx[k] + f[k];
        }

        val = 0.0;
        if (obj->nvar >= 1) {
          ixlast = obj->nvar;
          for (k = 0; k < ixlast; k++) {
            val += x[k] * workspace[k];
          }
        }
      } else {
        val = 0.0;
        if (obj->nvar >= 1) {
          int32_T ixlast;
          ixlast = obj->nvar;
          for (k = 0; k < ixlast; k++) {
            val += x[k] * obj->Hx[k];
          }
        }

        val *= 0.5;
      }
    }
    break;

   default:
    {
      if (obj->hasLinear) {
        int32_T ixlast;
        if (obj->nvar - 1 >= 0) {
          memcpy(&workspace[0], &f[0], (uint32_T)obj->nvar * sizeof(real_T));
        }

        ixlast = 4 - obj->nvar;
        for (k = 0; k < ixlast; k++) {
          workspace[obj->nvar + k] = 0.0;
        }

        workspace[0] += 0.5 * obj->Hx[0];
        workspace[1] += 0.5 * obj->Hx[1];
        workspace[2] += 0.5 * obj->Hx[2];
        workspace[3] += 0.5 * obj->Hx[3];
        val = ((x[0] * workspace[0] + x[1] * workspace[1]) + x[2] * workspace[2])
          + x[3] * workspace[3];
      } else {
        int32_T ixlast;
        val = (((x[0] * obj->Hx[0] + x[1] * obj->Hx[1]) + x[2] * obj->Hx[2]) +
               x[3] * obj->Hx[3]) * 0.5;
        ixlast = obj->nvar + 1;
        for (k = ixlast; k < 5; k++) {
          val += x[k - 1] * 0.0;
        }
      }
    }
    break;
  }

  return val;
}

/* Function for MATLAB Function: '<S7>/Torque Allocation QP Normalized' */
static void ControlsMFE25_factorQR(sisnsZ1AM9QRiMKnwqarOXF_Contr_T *obj, const
  real_T A[50], int32_T mrows, int32_T ncols)
{
  int32_T b;
  int32_T i;
  int32_T idx;
  int32_T ix0;
  int32_T iy0;
  boolean_T guard1;
  idx = mrows * ncols;
  guard1 = false;
  if (idx > 0) {
    for (idx = 0; idx < ncols; idx++) {
      ix0 = 5 * idx;
      iy0 = 5 * idx;
      b = (uint8_T)mrows;
      for (i = 0; i < b; i++) {
        obj->QR[iy0 + i] = A[ix0 + i];
      }
    }

    guard1 = true;
  } else if (idx == 0) {
    obj->mrows = mrows;
    obj->ncols = ncols;
    obj->minRowCol = 0;
  } else {
    guard1 = true;
  }

  if (guard1) {
    obj->usedPivoting = false;
    obj->mrows = mrows;
    obj->ncols = ncols;
    for (idx = 0; idx < ncols; idx++) {
      obj->jpvt[idx] = idx + 1;
    }

    if (mrows <= ncols) {
      idx = mrows;
    } else {
      idx = ncols;
    }

    obj->minRowCol = idx;
    for (i = 0; i < 5; i++) {
      obj->tau[i] = 0.0;
    }

    if (idx >= 1) {
      for (i = 0; i < 5; i++) {
        obj->tau[i] = 0.0;
      }

      ControlsMFE25_qrf(obj->QR, mrows, ncols, idx, obj->tau);
    }
  }
}

/* Function for MATLAB Function: '<S7>/Torque Allocation QP Normalized' */
static void ControlsMFE25_xrotg(real_T *a, real_T *b, real_T *c, real_T *s)
{
  real_T absa;
  real_T absb;
  real_T roe;
  real_T scale;
  roe = *b;
  absa = fabs(*a);
  absb = fabs(*b);
  if (absa > absb) {
    roe = *a;
  }

  scale = absa + absb;
  if (scale == 0.0) {
    *s = 0.0;
    *c = 1.0;
    *a = 0.0;
    *b = 0.0;
  } else {
    real_T ads;
    real_T bds;
    ads = absa / scale;
    bds = absb / scale;
    scale *= sqrt(ads * ads + bds * bds);
    if (roe < 0.0) {
      scale = -scale;
    }

    *c = *a / scale;
    *s = *b / scale;
    if (absa > absb) {
      *b = *s;
    } else if (*c != 0.0) {
      *b = 1.0 / *c;
    } else {
      *b = 1.0;
    }

    *a = scale;
  }
}

/* Function for MATLAB Function: '<S7>/Torque Allocation QP Normalized' */
static void ControlsMFE25_squareQ_appendCol(sisnsZ1AM9QRiMKnwqarOXF_Contr_T *obj,
  const real_T vec[50], int32_T iv0)
{
  real_T b_c;
  real_T s;
  real_T temp;
  real_T temp_tmp;
  int32_T b_iy;
  int32_T d;
  int32_T e;
  int32_T idxRotGCol;
  int32_T iyend;
  if (obj->mrows <= obj->ncols + 1) {
    obj->minRowCol = obj->mrows;
  } else {
    obj->minRowCol = obj->ncols + 1;
  }

  b_iy = 5 * obj->ncols;
  if (obj->mrows != 0) {
    iyend = b_iy + obj->mrows;
    if (b_iy + 1 <= iyend) {
      memset(&obj->QR[b_iy], 0, (uint32_T)(iyend - b_iy) * sizeof(real_T));
    }

    d = (obj->mrows - 1) * 5 + 1;
    for (idxRotGCol = 1; idxRotGCol <= d; idxRotGCol += 5) {
      b_c = 0.0;
      e = idxRotGCol + obj->mrows;
      for (iyend = idxRotGCol; iyend < e; iyend++) {
        b_c += vec[((iv0 + iyend) - idxRotGCol) - 1] * obj->Q[iyend - 1];
      }

      iyend = div_nde_s32_floor(idxRotGCol - 1, 5) + b_iy;
      obj->QR[iyend] += b_c;
    }
  }

  obj->ncols++;
  obj->jpvt[obj->ncols - 1] = obj->ncols;
  for (b_iy = obj->mrows - 2; b_iy + 2 > obj->ncols; b_iy--) {
    e = (obj->ncols - 1) * 5 + b_iy;
    temp = obj->QR[e + 1];
    ControlsMFE25_xrotg(&obj->QR[e], &temp, &b_c, &s);
    obj->QR[e + 1] = temp;
    iyend = 5 * b_iy;
    d = obj->mrows;
    if (obj->mrows >= 1) {
      for (idxRotGCol = 0; idxRotGCol < d; idxRotGCol++) {
        e = iyend + idxRotGCol;
        temp = obj->Q[e + 5];
        temp_tmp = obj->Q[e];
        obj->Q[e + 5] = temp * b_c - temp_tmp * s;
        obj->Q[e] = temp * s + temp_tmp * b_c;
      }
    }
  }
}

/* Function for MATLAB Function: '<S7>/Torque Allocation QP Normalized' */
static void ControlsMFE25_deleteColMoveEnd(sisnsZ1AM9QRiMKnwqarOXF_Contr_T *obj,
  int32_T idx)
{
  real_T b_s;
  real_T b_temp;
  real_T c_c;
  int32_T QRk0;
  int32_T b_ix;
  int32_T b_n;
  int32_T b_temp_tmp;
  int32_T i;
  int32_T idxRotGCol;
  int32_T idxRotGCol_tmp;
  int32_T k;
  if (obj->usedPivoting) {
    i = 1;
    while ((i <= obj->ncols) && (obj->jpvt[i - 1] != idx)) {
      i++;
    }

    idx = i;
  }

  if (idx >= obj->ncols) {
    obj->ncols--;
  } else {
    obj->jpvt[idx - 1] = obj->jpvt[obj->ncols - 1];
    idxRotGCol = obj->minRowCol;
    for (i = 0; i < idxRotGCol; i++) {
      obj->QR[i + 5 * (idx - 1)] = obj->QR[(obj->ncols - 1) * 5 + i];
    }

    obj->ncols--;
    if (obj->mrows <= obj->ncols) {
      obj->minRowCol = obj->mrows;
    } else {
      obj->minRowCol = obj->ncols;
    }

    if (idx < obj->mrows) {
      if (obj->mrows - 1 <= obj->ncols) {
        i = obj->mrows - 1;
      } else {
        i = obj->ncols;
      }

      k = i;
      idxRotGCol = (idx - 1) * 5;
      while (k >= idx) {
        b_temp_tmp = k + idxRotGCol;
        b_temp = obj->QR[b_temp_tmp];
        ControlsMFE25_xrotg(&obj->QR[b_temp_tmp - 1], &b_temp, &c_c, &b_s);
        obj->QR[b_temp_tmp] = b_temp;
        idxRotGCol_tmp = (k - 1) * 5;
        obj->QR[k + idxRotGCol_tmp] = 0.0;
        QRk0 = 5 * idx + k;
        b_ix = obj->ncols - idx;
        if (b_ix >= 1) {
          for (b_n = 0; b_n < b_ix; b_n++) {
            b_temp_tmp = b_n * 5 + QRk0;
            b_temp = obj->QR[b_temp_tmp - 1] * c_c + obj->QR[b_temp_tmp] * b_s;
            obj->QR[b_temp_tmp] = obj->QR[b_temp_tmp] * c_c - obj->QR[b_temp_tmp
              - 1] * b_s;
            obj->QR[b_temp_tmp - 1] = b_temp;
          }
        }

        b_ix = obj->mrows;
        if (obj->mrows >= 1) {
          for (b_n = 0; b_n < b_ix; b_n++) {
            b_temp_tmp = idxRotGCol_tmp + b_n;
            b_temp = obj->Q[b_temp_tmp + 5] * b_s + obj->Q[b_temp_tmp] * c_c;
            obj->Q[b_temp_tmp + 5] = obj->Q[b_temp_tmp + 5] * c_c - obj->
              Q[b_temp_tmp] * b_s;
            obj->Q[b_temp_tmp] = b_temp;
          }
        }

        k--;
      }

      for (k = idx + 1; k <= i; k++) {
        idxRotGCol_tmp = (k - 1) * 5;
        b_temp_tmp = k + idxRotGCol_tmp;
        b_temp = obj->QR[b_temp_tmp];
        ControlsMFE25_xrotg(&obj->QR[b_temp_tmp - 1], &b_temp, &c_c, &b_s);
        obj->QR[b_temp_tmp] = b_temp;
        QRk0 = k * 6;
        b_n = obj->ncols - k;
        if (b_n >= 1) {
          for (idxRotGCol = 0; idxRotGCol < b_n; idxRotGCol++) {
            b_temp_tmp = idxRotGCol * 5 + QRk0;
            b_temp = obj->QR[b_temp_tmp - 1] * c_c + obj->QR[b_temp_tmp] * b_s;
            obj->QR[b_temp_tmp] = obj->QR[b_temp_tmp] * c_c - obj->QR[b_temp_tmp
              - 1] * b_s;
            obj->QR[b_temp_tmp - 1] = b_temp;
          }
        }

        b_n = obj->mrows;
        if (obj->mrows >= 1) {
          for (idxRotGCol = 0; idxRotGCol < b_n; idxRotGCol++) {
            b_temp_tmp = idxRotGCol_tmp + idxRotGCol;
            b_temp = obj->Q[b_temp_tmp + 5] * b_s + obj->Q[b_temp_tmp] * c_c;
            obj->Q[b_temp_tmp + 5] = obj->Q[b_temp_tmp + 5] * c_c - obj->
              Q[b_temp_tmp] * b_s;
            obj->Q[b_temp_tmp] = b_temp;
          }
        }
      }
    }
  }
}

/* Function for MATLAB Function: '<S7>/Torque Allocation QP Normalized' */
static void ControlsMFE25_xgemv_o(int32_T m, int32_T n, const real_T A[25],
  int32_T ia0, const real_T x[50], real_T y[5])
{
  int32_T b_iy;
  int32_T ia;
  if (m != 0) {
    int32_T b;
    int32_T ix;
    memset(&y[0], 0, (uint32_T)m * sizeof(real_T));
    ix = 0;
    b = (n - 1) * 5 + ia0;
    for (b_iy = ia0; b_iy <= b; b_iy += 5) {
      int32_T c;
      c = b_iy + m;
      for (ia = b_iy; ia < c; ia++) {
        int32_T tmp;
        tmp = ia - b_iy;
        y[tmp] += A[ia - 1] * x[ix];
      }

      ix++;
    }
  }
}

/* Function for MATLAB Function: '<S7>/Torque Allocation QP Normalized' */
static void ControlsMFE25_fullColLDL2_(sY034dY3cx1IgSIMa0jtlQE_Contr_T *obj,
  int32_T NColsRemain, real_T REG_PRIMAL)
{
  int32_T b_k;
  int32_T ijA;
  int32_T lastDiag;
  int32_T subMatrixDim;
  for (lastDiag = 0; lastDiag < NColsRemain; lastDiag++) {
    real_T obj_FMat;
    int32_T LD_diagOffset;
    LD_diagOffset = 6 * lastDiag;
    obj_FMat = obj->FMat[LD_diagOffset];
    if (fabs(obj_FMat) <= obj->regTol_) {
      obj_FMat += REG_PRIMAL;
      obj->FMat[LD_diagOffset] = obj_FMat;
    }

    obj_FMat = -1.0 / obj_FMat;
    subMatrixDim = (NColsRemain - lastDiag) - 2;
    for (b_k = 0; b_k <= subMatrixDim; b_k++) {
      obj->workspace_[b_k] = obj->FMat[(LD_diagOffset + b_k) + 1];
    }

    if (!(obj_FMat == 0.0)) {
      int32_T jA;
      jA = LD_diagOffset + 7;
      for (b_k = 0; b_k <= subMatrixDim; b_k++) {
        real_T temp;
        temp = obj->workspace_[b_k];
        if (temp != 0.0) {
          int32_T b;
          temp *= obj_FMat;
          b = subMatrixDim + jA;
          for (ijA = jA; ijA <= b; ijA++) {
            obj->FMat[ijA - 1] += obj->workspace_[ijA - jA] * temp;
          }
        }

        jA += 5;
      }
    }

    obj_FMat = 1.0 / obj->FMat[LD_diagOffset];
    b_k = LD_diagOffset + subMatrixDim;
    for (subMatrixDim = LD_diagOffset + 2; subMatrixDim <= b_k + 2; subMatrixDim
         ++) {
      obj->FMat[subMatrixDim - 1] *= obj_FMat;
    }
  }

  lastDiag = (NColsRemain - 1) * 6;
  if (fabs(obj->FMat[lastDiag]) <= obj->regTol_) {
    obj->FMat[lastDiag] += REG_PRIMAL;
  }
}

/* Function for MATLAB Function: '<S7>/Torque Allocation QP Normalized' */
static void ControlsMFE25_compute_deltax(const real_T H[16],
  sF7ecKzAoqUt0jrk31NyRZH_Contr_T *solution, su0bqVilpnfgpuAQ6xEtFDC_Contr_T
  *memspace, const sisnsZ1AM9QRiMKnwqarOXF_Contr_T *qrmanager,
  sY034dY3cx1IgSIMa0jtlQE_Contr_T *cholmanager, const
  szdozZxcClCeUpd1TsA9nJF_Contr_T *objective)
{
  real_T s;
  real_T smax;
  real_T temp;
  int32_T ar;
  int32_T b_jjA;
  int32_T br;
  int32_T exitg1;
  int32_T g;
  int32_T h;
  int32_T i;
  int32_T ix;
  int32_T lastColC;
  int32_T mNull;
  int32_T nVar;
  int32_T nVars;
  int32_T nullStartIdx;
  int32_T nullStartIdx_tmp;
  nVar = qrmanager->mrows - 1;
  mNull = qrmanager->mrows - qrmanager->ncols;
  if (mNull <= 0) {
    if (qrmanager->mrows - 1 >= 0) {
      memset(&solution->searchDir[0], 0, (uint32_T)((qrmanager->mrows - 1) + 1) *
             sizeof(real_T));
    }
  } else {
    for (nullStartIdx = 0; nullStartIdx <= nVar; nullStartIdx++) {
      solution->searchDir[nullStartIdx] = -objective->grad[nullStartIdx];
    }

    if (qrmanager->ncols <= 0) {
      if (objective->objtype == 3) {
        temp = 1.4901161193847656E-8 * cholmanager->scaleFactor * (real_T)
          qrmanager->mrows;
        cholmanager->ndims = qrmanager->mrows;
        for (mNull = 0; mNull <= nVar; mNull++) {
          nVars = (nVar + 1) * mNull;
          lastColC = 5 * mNull;
          for (nullStartIdx = 0; nullStartIdx <= nVar; nullStartIdx++) {
            cholmanager->FMat[lastColC + nullStartIdx] = H[nullStartIdx + nVars];
          }
        }

        if (qrmanager->mrows < 1) {
          nullStartIdx = -1;
        } else {
          nullStartIdx = 0;
          if (qrmanager->mrows > 1) {
            smax = fabs(cholmanager->FMat[0]);
            for (mNull = 2; mNull <= nVar + 1; mNull++) {
              s = fabs(cholmanager->FMat[(mNull - 1) * 6]);
              if (s > smax) {
                nullStartIdx = mNull - 1;
                smax = s;
              }
            }
          }
        }

        cholmanager->regTol_ = fmax(fabs(cholmanager->FMat[5 * nullStartIdx +
          nullStartIdx]) * 2.2204460492503131E-16, fabs(temp));
        ControlsMFE25_fullColLDL2_(cholmanager, qrmanager->mrows, temp);
        if (cholmanager->ConvexCheck) {
          mNull = 0;
          do {
            exitg1 = 0;
            if (mNull <= nVar) {
              if (cholmanager->FMat[5 * mNull + mNull] <= 0.0) {
                cholmanager->info = -mNull - 1;
                exitg1 = 1;
              } else {
                mNull++;
              }
            } else {
              cholmanager->ConvexCheck = false;
              exitg1 = 1;
            }
          } while (exitg1 == 0);
        }

        if (cholmanager->info != 0) {
          solution->state = -6;
        } else {
          nVar = cholmanager->ndims;
          if (cholmanager->ndims != 0) {
            for (mNull = 0; mNull < nVar; mNull++) {
              lastColC = mNull * 5 + mNull;
              b_jjA = (nVar - mNull) - 2;
              for (nullStartIdx = 0; nullStartIdx <= b_jjA; nullStartIdx++) {
                ix = (nullStartIdx + mNull) + 1;
                solution->searchDir[ix] -= cholmanager->FMat[(nullStartIdx +
                  lastColC) + 1] * solution->searchDir[mNull];
              }
            }
          }

          nullStartIdx = 0;
          for (mNull = 0; mNull < nVar; mNull++) {
            solution->searchDir[mNull] /= cholmanager->FMat[nullStartIdx];
            nullStartIdx += 6;
          }

          nVar = cholmanager->ndims;
          if (cholmanager->ndims != 0) {
            for (mNull = nVar; mNull >= 1; mNull--) {
              nVars = (mNull - 1) * 5;
              temp = solution->searchDir[mNull - 1];
              for (nullStartIdx = nVar; nullStartIdx >= mNull + 1; nullStartIdx
                   --) {
                temp -= cholmanager->FMat[(nVars + nullStartIdx) - 1] *
                  solution->searchDir[nullStartIdx - 1];
              }

              solution->searchDir[mNull - 1] = temp;
            }
          }
        }
      }
    } else {
      nullStartIdx_tmp = 5 * qrmanager->ncols;
      nullStartIdx = nullStartIdx_tmp + 1;
      if (objective->objtype == 5) {
        for (nVars = 0; nVars < mNull; nVars++) {
          memspace->workspace_float[nVars] = -qrmanager->Q[(qrmanager->ncols +
            nVars) * 5 + nVar];
        }

        ControlsMFE25_xgemv_o(qrmanager->mrows, mNull, qrmanager->Q,
                              nullStartIdx_tmp + 1, memspace->workspace_float,
                              solution->searchDir);
      } else {
        if (objective->objtype == 3) {
          nVars = qrmanager->mrows;
          if ((qrmanager->mrows != 0) && (mNull != 0)) {
            br = nullStartIdx_tmp;
            lastColC = (mNull - 1) * 10;
            for (b_jjA = 0; b_jjA <= lastColC; b_jjA += 10) {
              g = b_jjA + nVars;
              for (ix = b_jjA + 1; ix <= g; ix++) {
                memspace->workspace_float[ix - 1] = 0.0;
              }
            }

            for (b_jjA = 0; b_jjA <= lastColC; b_jjA += 10) {
              ar = -1;
              h = br + nVars;
              for (ix = br + 1; ix <= h; ix++) {
                i = b_jjA + nVars;
                for (g = b_jjA + 1; g <= i; g++) {
                  memspace->workspace_float[g - 1] += H[(ar + g) - b_jjA] *
                    qrmanager->Q[ix - 1];
                }

                ar += nVars;
              }

              br += 5;
            }
          }

          if (mNull != 0) {
            br = (mNull - 1) * 5;
            for (b_jjA = 0; b_jjA <= br; b_jjA += 5) {
              g = b_jjA + mNull;
              for (ix = b_jjA + 1; ix <= g; ix++) {
                cholmanager->FMat[ix - 1] = 0.0;
              }
            }

            lastColC = -1;
            for (b_jjA = 0; b_jjA <= br; b_jjA += 5) {
              ar = nullStartIdx_tmp;
              h = b_jjA + mNull;
              for (ix = b_jjA + 1; ix <= h; ix++) {
                temp = 0.0;
                for (g = 0; g < nVars; g++) {
                  temp += memspace->workspace_float[(g + lastColC) + 1] *
                    qrmanager->Q[g + ar];
                }

                cholmanager->FMat[ix - 1] += temp;
                ar += 5;
              }

              lastColC += 10;
            }
          }
        }

        temp = 1.4901161193847656E-8 * cholmanager->scaleFactor * (real_T)mNull;
        cholmanager->ndims = mNull;
        lastColC = 0;
        if (mNull > 1) {
          smax = fabs(cholmanager->FMat[0]);
          for (nVars = 2; nVars <= mNull; nVars++) {
            s = fabs(cholmanager->FMat[(nVars - 1) * 6]);
            if (s > smax) {
              lastColC = nVars - 1;
              smax = s;
            }
          }
        }

        cholmanager->regTol_ = fmax(fabs(cholmanager->FMat[5 * lastColC +
          lastColC]) * 2.2204460492503131E-16, fabs(temp));
        ControlsMFE25_fullColLDL2_(cholmanager, mNull, temp);
        if (cholmanager->ConvexCheck) {
          nVars = 0;
          do {
            exitg1 = 0;
            if (nVars <= mNull - 1) {
              if (cholmanager->FMat[5 * nVars + nVars] <= 0.0) {
                cholmanager->info = -nVars - 1;
                exitg1 = 1;
              } else {
                nVars++;
              }
            } else {
              cholmanager->ConvexCheck = false;
              exitg1 = 1;
            }
          } while (exitg1 == 0);
        }

        if (cholmanager->info != 0) {
          solution->state = -6;
        } else {
          if (qrmanager->mrows != 0) {
            memset(&memspace->workspace_float[0], 0, (uint32_T)mNull * sizeof
                   (real_T));
            b_jjA = ((mNull - 1) * 5 + nullStartIdx_tmp) + 1;
            for (nVars = nullStartIdx; nVars <= b_jjA; nVars += 5) {
              temp = 0.0;
              g = nVars + nVar;
              for (lastColC = nVars; lastColC <= g; lastColC++) {
                temp += qrmanager->Q[lastColC - 1] * objective->grad[lastColC -
                  nVars];
              }

              ix = div_nde_s32_floor((nVars - nullStartIdx_tmp) - 1, 5);
              memspace->workspace_float[ix] -= temp;
            }
          }

          lastColC = cholmanager->ndims;
          if (cholmanager->ndims != 0) {
            for (nVar = 0; nVar < lastColC; nVar++) {
              b_jjA = nVar * 5 + nVar;
              ix = (lastColC - nVar) - 2;
              for (nVars = 0; nVars <= ix; nVars++) {
                br = (nVars + nVar) + 1;
                memspace->workspace_float[br] -= cholmanager->FMat[(nVars +
                  b_jjA) + 1] * memspace->workspace_float[nVar];
              }
            }
          }

          nullStartIdx = 0;
          for (nVar = 0; nVar < lastColC; nVar++) {
            memspace->workspace_float[nVar] /= cholmanager->FMat[nullStartIdx];
            nullStartIdx += 6;
          }

          lastColC = cholmanager->ndims;
          if (cholmanager->ndims != 0) {
            for (nVar = lastColC; nVar >= 1; nVar--) {
              b_jjA = (nVar - 1) * 5;
              temp = memspace->workspace_float[nVar - 1];
              for (nVars = lastColC; nVars >= nVar + 1; nVars--) {
                temp -= cholmanager->FMat[(b_jjA + nVars) - 1] *
                  memspace->workspace_float[nVars - 1];
              }

              memspace->workspace_float[nVar - 1] = temp;
            }
          }

          ControlsMFE25_xgemv_o(qrmanager->mrows, mNull, qrmanager->Q,
                                nullStartIdx_tmp + 1, memspace->workspace_float,
                                solution->searchDir);
        }
      }
    }
  }
}

/* Function for MATLAB Function: '<S7>/Torque Allocation QP Normalized' */
static void ControlsMFE25_compute_lambda(real_T workspace[50],
  sF7ecKzAoqUt0jrk31NyRZH_Contr_T *solution, const
  szdozZxcClCeUpd1TsA9nJF_Contr_T *objective, const
  sisnsZ1AM9QRiMKnwqarOXF_Contr_T *qrmanager)
{
  int32_T b_idx;
  int32_T idxQR;
  int32_T nActiveConstr;
  nActiveConstr = qrmanager->ncols;
  if (qrmanager->ncols > 0) {
    real_T c;
    boolean_T guard1;
    guard1 = false;
    if (objective->objtype != 4) {
      boolean_T nonDegenerate;
      if (qrmanager->mrows >= qrmanager->ncols) {
        idxQR = qrmanager->mrows;
      } else {
        idxQR = qrmanager->ncols;
      }

      c = fmin(1.4901161193847656E-8, 2.2204460492503131E-15 * (real_T)idxQR);
      nonDegenerate = ((qrmanager->mrows > 0) && (qrmanager->ncols > 0));
      if (nonDegenerate) {
        boolean_T guard2;
        b_idx = qrmanager->ncols;
        guard2 = false;
        if (qrmanager->mrows < qrmanager->ncols) {
          idxQR = (qrmanager->ncols - 1) * 5 + qrmanager->mrows;
          while ((b_idx > qrmanager->mrows) && (fabs(qrmanager->QR[idxQR - 1]) >=
                  c)) {
            b_idx--;
            idxQR -= 5;
          }

          nonDegenerate = (b_idx == qrmanager->mrows);
          if (!nonDegenerate) {
          } else {
            guard2 = true;
          }
        } else {
          guard2 = true;
        }

        if (guard2) {
          idxQR = (b_idx - 1) * 5 + b_idx;
          while ((b_idx >= 1) && (fabs(qrmanager->QR[idxQR - 1]) >= c)) {
            b_idx--;
            idxQR -= 6;
          }

          nonDegenerate = (b_idx == 0);
        }
      }

      if (!nonDegenerate) {
        solution->state = -7;
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }

    if (guard1) {
      int32_T ix;
      int32_T jjA;
      if (qrmanager->mrows != 0) {
        memset(&workspace[0], 0, (uint32_T)qrmanager->ncols * sizeof(real_T));
        jjA = (qrmanager->ncols - 1) * 5 + 1;
        for (b_idx = 1; b_idx <= jjA; b_idx += 5) {
          c = 0.0;
          ix = b_idx + qrmanager->mrows;
          for (idxQR = b_idx; idxQR < ix; idxQR++) {
            c += qrmanager->Q[idxQR - 1] * objective->grad[idxQR - b_idx];
          }

          idxQR = div_nde_s32_floor(b_idx - 1, 5);
          workspace[idxQR] += c;
        }
      }

      for (b_idx = nActiveConstr; b_idx >= 1; b_idx--) {
        jjA = ((b_idx - 1) * 5 + b_idx) - 2;
        workspace[b_idx - 1] /= qrmanager->QR[jjA + 1];
        for (idxQR = 0; idxQR <= b_idx - 2; idxQR++) {
          ix = (b_idx - idxQR) - 2;
          workspace[ix] -= workspace[b_idx - 1] * qrmanager->QR[jjA - idxQR];
        }
      }

      for (b_idx = 0; b_idx < nActiveConstr; b_idx++) {
        solution->lambda[b_idx] = -workspace[b_idx];
      }
    }
  }
}

/* Function for MATLAB Function: '<S7>/Torque Allocation QP Normalized' */
static real_T ControlsMFE25_xnrm2_d(int32_T n, const real_T x[5])
{
  real_T y;
  int32_T kend;
  y = 0.0;
  if (n >= 1) {
    if (n == 1) {
      y = fabs(x[0]);
    } else {
      real_T scale;
      scale = 3.3121686421112381E-170;
      for (kend = 0; kend < n; kend++) {
        real_T absxk;
        absxk = fabs(x[kend]);
        if (absxk > scale) {
          real_T t;
          t = scale / absxk;
          y = y * t * t + 1.0;
          scale = absxk;
        } else {
          real_T t;
          t = absxk / scale;
          y += t * t;
        }
      }

      y = scale * sqrt(y);
      if (rtIsNaN(y)) {
        kend = 0;
        int32_T exitg1;
        do {
          exitg1 = 0;
          if (kend <= n - 1) {
            if (rtIsNaN(x[kend])) {
              exitg1 = 1;
            } else {
              kend++;
            }
          } else {
            y = (rtInf);
            exitg1 = 1;
          }
        } while (exitg1 == 0);
      }
    }
  }

  return y;
}

/* Function for MATLAB Function: '<S7>/Torque Allocation QP Normalized' */
static void ControlsMFE25_ratiotest(const real_T solution_xstar[5], const real_T
  solution_searchDir[5], real_T workspace[50], int32_T workingset_nVar, const
  real_T workingset_Aineq[5], real_T workingset_bineq, const real_T
  workingset_lb[5], const real_T workingset_ub[5], const int32_T
  workingset_indexLB[5], const int32_T workingset_indexUB[5], const int32_T
  workingset_sizes[5], const int32_T workingset_isActiveIdx[6], const boolean_T
  workingset_isActiveConstr[10], const int32_T workingset_nWConstr[5], real_T
  *toldelta, real_T *alpha, boolean_T *newBlocking, int32_T *constrType, int32_T
  *constrIdx)
{
  real_T alphaTemp;
  real_T alphaTemp_tmp;
  real_T b_c;
  real_T denomTol;
  real_T p_max;
  real_T phaseOneCorrectionP;
  real_T pk_corrected;
  int32_T ia;
  int32_T k;
  int32_T workingset_indexLB_0;
  *alpha = 1.0E+30;
  *newBlocking = false;
  *constrType = 0;
  *constrIdx = 0;
  p_max = 0.0;
  denomTol = 2.2204460492503131E-13 * ControlsMFE25_xnrm2_d(workingset_nVar,
    solution_searchDir);
  if (workingset_nWConstr[2] < 1) {
    workspace[0] = workingset_bineq;
    workspace[0] = -workspace[0];
    b_c = 0.0;
    for (ia = 1; ia <= workingset_nVar; ia++) {
      b_c += workingset_Aineq[ia - 1] * solution_xstar[ia - 1];
    }

    workspace[0] += b_c;
    workspace[10] = 0.0;
    b_c = 0.0;
    for (ia = 1; ia <= workingset_nVar; ia++) {
      b_c += workingset_Aineq[ia - 1] * solution_searchDir[ia - 1];
    }

    workspace[10] += b_c;
    if ((workspace[10] > denomTol) &&
        (!workingset_isActiveConstr[workingset_isActiveIdx[2] - 1])) {
      alphaTemp = fmin(fabs(workspace[0] - *toldelta), (1.0E-8 - workspace[0]) +
                       *toldelta) / workspace[10];
      if ((alphaTemp <= 1.0E+30) && (fabs(workspace[10]) > 0.0)) {
        *alpha = alphaTemp;
        *constrType = 3;
        *constrIdx = 1;
        *newBlocking = true;
      }

      alphaTemp = fmin(fabs(workspace[0]), 1.0E-8 - workspace[0]) / workspace[10];
      if (alphaTemp < *alpha) {
        *alpha = alphaTemp;
        *constrType = 3;
        *constrIdx = 1;
        *newBlocking = true;
        p_max = fabs(workspace[10]);
      }
    }
  }

  if (workingset_nWConstr[3] < workingset_sizes[3]) {
    b_c = solution_xstar[workingset_nVar - 1] * 0.0;
    phaseOneCorrectionP = solution_searchDir[workingset_nVar - 1] * 0.0;
    ia = workingset_sizes[3];
    for (k = 0; k <= ia - 2; k++) {
      workingset_indexLB_0 = workingset_indexLB[k];
      pk_corrected = -solution_searchDir[workingset_indexLB_0 - 1] -
        phaseOneCorrectionP;
      if ((pk_corrected > denomTol) && (!workingset_isActiveConstr
           [(workingset_isActiveIdx[3] + k) - 1])) {
        alphaTemp_tmp = -solution_xstar[workingset_indexLB_0 - 1] -
          workingset_lb[workingset_indexLB_0 - 1];
        alphaTemp = (alphaTemp_tmp - *toldelta) - b_c;
        alphaTemp = fmin(fabs(alphaTemp), 1.0E-8 - alphaTemp) / pk_corrected;
        if ((alphaTemp <= *alpha) && (fabs(pk_corrected) > p_max)) {
          *alpha = alphaTemp;
          *constrType = 4;
          *constrIdx = k + 1;
          *newBlocking = true;
        }

        alphaTemp = alphaTemp_tmp - b_c;
        alphaTemp = fmin(fabs(alphaTemp), 1.0E-8 - alphaTemp) / pk_corrected;
        if (alphaTemp < *alpha) {
          *alpha = alphaTemp;
          *constrType = 4;
          *constrIdx = k + 1;
          *newBlocking = true;
          p_max = fabs(pk_corrected);
        }
      }
    }

    ia = workingset_indexLB[workingset_sizes[3] - 1] - 1;
    b_c = solution_searchDir[ia];
    if ((-b_c > denomTol) && (!workingset_isActiveConstr
         [(workingset_isActiveIdx[3] + workingset_sizes[3]) - 2])) {
      alphaTemp_tmp = -solution_xstar[ia] - workingset_lb[ia];
      alphaTemp = alphaTemp_tmp - *toldelta;
      alphaTemp = fmin(fabs(alphaTemp), 1.0E-8 - alphaTemp) / -b_c;
      if ((alphaTemp <= *alpha) && (fabs(b_c) > p_max)) {
        *alpha = alphaTemp;
        *constrType = 4;
        *constrIdx = workingset_sizes[3];
        *newBlocking = true;
      }

      alphaTemp = fmin(fabs(alphaTemp_tmp), 1.0E-8 - alphaTemp_tmp) / -b_c;
      if (alphaTemp < *alpha) {
        *alpha = alphaTemp;
        *constrType = 4;
        *constrIdx = workingset_sizes[3];
        *newBlocking = true;
        p_max = fabs(b_c);
      }
    }
  }

  if (workingset_nWConstr[4] < workingset_sizes[4]) {
    b_c = solution_xstar[workingset_nVar - 1] * 0.0;
    phaseOneCorrectionP = solution_searchDir[workingset_nVar - 1] * 0.0;
    ia = (uint8_T)workingset_sizes[4];
    for (k = 0; k < ia; k++) {
      workingset_indexLB_0 = workingset_indexUB[k];
      pk_corrected = solution_searchDir[workingset_indexLB_0 - 1] -
        phaseOneCorrectionP;
      if ((pk_corrected > denomTol) && (!workingset_isActiveConstr
           [(workingset_isActiveIdx[4] + k) - 1])) {
        alphaTemp_tmp = solution_xstar[workingset_indexLB_0 - 1] -
          workingset_ub[workingset_indexLB_0 - 1];
        alphaTemp = (alphaTemp_tmp - *toldelta) - b_c;
        alphaTemp = fmin(fabs(alphaTemp), 1.0E-8 - alphaTemp) / pk_corrected;
        if ((alphaTemp <= *alpha) && (fabs(pk_corrected) > p_max)) {
          *alpha = alphaTemp;
          *constrType = 5;
          *constrIdx = k + 1;
          *newBlocking = true;
        }

        alphaTemp = alphaTemp_tmp - b_c;
        alphaTemp = fmin(fabs(alphaTemp), 1.0E-8 - alphaTemp) / pk_corrected;
        if (alphaTemp < *alpha) {
          *alpha = alphaTemp;
          *constrType = 5;
          *constrIdx = k + 1;
          *newBlocking = true;
          p_max = fabs(pk_corrected);
        }
      }
    }
  }

  *toldelta += 6.608625846508183E-7;
  if (p_max > 0.0) {
    *alpha = fmax(*alpha, 6.608625846508183E-7 / p_max);
  }

  *newBlocking = (((!*newBlocking) || (!(*alpha > 1.0))) && (*newBlocking));
  *alpha = fmin(*alpha, 1.0);
}

/* Function for MATLAB Function: '<S7>/Torque Allocation QP Normalized' */
static void ControlsMFE25_feasibleratiotest(const real_T solution_xstar[5],
  const real_T solution_searchDir[5], real_T workspace[50], int32_T
  workingset_nVar, const real_T workingset_Aineq[5], real_T workingset_bineq,
  const real_T workingset_lb[5], const real_T workingset_ub[5], const int32_T
  workingset_indexLB[5], const int32_T workingset_indexUB[5], const int32_T
  workingset_sizes[5], const int32_T workingset_isActiveIdx[6], const boolean_T
  workingset_isActiveConstr[10], const int32_T workingset_nWConstr[5], boolean_T
  isPhaseOne, real_T *alpha, boolean_T *newBlocking, int32_T *constrType,
  int32_T *constrIdx)
{
  real_T alphaTemp;
  real_T b_c;
  real_T denomTol;
  real_T phaseOneCorrectionP;
  real_T ratio;
  int32_T ia;
  int32_T k;
  int32_T workingset_indexLB_0;
  *alpha = 1.0E+30;
  *newBlocking = false;
  *constrType = 0;
  *constrIdx = 0;
  denomTol = 2.2204460492503131E-13 * ControlsMFE25_xnrm2_d(workingset_nVar,
    solution_searchDir);
  if (workingset_nWConstr[2] < 1) {
    workspace[0] = workingset_bineq;
    workspace[0] = -workspace[0];
    b_c = 0.0;
    for (ia = 1; ia <= workingset_nVar; ia++) {
      b_c += workingset_Aineq[ia - 1] * solution_xstar[ia - 1];
    }

    workspace[0] += b_c;
    workspace[10] = 0.0;
    b_c = 0.0;
    for (ia = 1; ia <= workingset_nVar; ia++) {
      b_c += workingset_Aineq[ia - 1] * solution_searchDir[ia - 1];
    }

    workspace[10] += b_c;
    if ((workspace[10] > denomTol) &&
        (!workingset_isActiveConstr[workingset_isActiveIdx[2] - 1])) {
      alphaTemp = fmin(fabs(workspace[0]), 1.0E-8 - workspace[0]) / workspace[10];
      if (alphaTemp < 1.0E+30) {
        *alpha = alphaTemp;
        *constrType = 3;
        *constrIdx = 1;
        *newBlocking = true;
      }
    }
  }

  if (workingset_nWConstr[3] < workingset_sizes[3]) {
    b_c = solution_xstar[workingset_nVar - 1] * (real_T)isPhaseOne;
    phaseOneCorrectionP = solution_searchDir[workingset_nVar - 1] * (real_T)
      isPhaseOne;
    ia = workingset_sizes[3];
    for (k = 0; k <= ia - 2; k++) {
      workingset_indexLB_0 = workingset_indexLB[k];
      alphaTemp = -solution_searchDir[workingset_indexLB_0 - 1] -
        phaseOneCorrectionP;
      if ((alphaTemp > denomTol) && (!workingset_isActiveConstr
           [(workingset_isActiveIdx[3] + k) - 1])) {
        ratio = (-solution_xstar[workingset_indexLB_0 - 1] -
                 workingset_lb[workingset_indexLB_0 - 1]) - b_c;
        alphaTemp = fmin(fabs(ratio), 1.0E-8 - ratio) / alphaTemp;
        if (alphaTemp < *alpha) {
          *alpha = alphaTemp;
          *constrType = 4;
          *constrIdx = k + 1;
          *newBlocking = true;
        }
      }
    }

    ia = workingset_indexLB[workingset_sizes[3] - 1] - 1;
    b_c = -solution_searchDir[ia];
    if ((b_c > denomTol) && (!workingset_isActiveConstr[(workingset_isActiveIdx
          [3] + workingset_sizes[3]) - 2])) {
      ratio = -solution_xstar[ia] - workingset_lb[ia];
      alphaTemp = fmin(fabs(ratio), 1.0E-8 - ratio) / b_c;
      if (alphaTemp < *alpha) {
        *alpha = alphaTemp;
        *constrType = 4;
        *constrIdx = workingset_sizes[3];
        *newBlocking = true;
      }
    }
  }

  if (workingset_nWConstr[4] < workingset_sizes[4]) {
    b_c = solution_xstar[workingset_nVar - 1] * (real_T)isPhaseOne;
    phaseOneCorrectionP = solution_searchDir[workingset_nVar - 1] * (real_T)
      isPhaseOne;
    ia = (uint8_T)workingset_sizes[4];
    for (k = 0; k < ia; k++) {
      workingset_indexLB_0 = workingset_indexUB[k];
      alphaTemp = solution_searchDir[workingset_indexLB_0 - 1] -
        phaseOneCorrectionP;
      if ((alphaTemp > denomTol) && (!workingset_isActiveConstr
           [(workingset_isActiveIdx[4] + k) - 1])) {
        ratio = (solution_xstar[workingset_indexLB_0 - 1] -
                 workingset_ub[workingset_indexLB_0 - 1]) - b_c;
        alphaTemp = fmin(fabs(ratio), 1.0E-8 - ratio) / alphaTemp;
        if (alphaTemp < *alpha) {
          *alpha = alphaTemp;
          *constrType = 5;
          *constrIdx = k + 1;
          *newBlocking = true;
        }
      }
    }
  }

  if (!isPhaseOne) {
    *newBlocking = (((!*newBlocking) || (!(*alpha > 1.0))) && (*newBlocking));
    *alpha = fmin(*alpha, 1.0);
  }
}

/* Function for MATLAB Function: '<S7>/Torque Allocation QP Normalized' */
static void Cont_addBoundToActiveSetMatrix_(s18w5MCz6685sBFJwJZKJdG_Contr_T *obj,
  int32_T TYPE, int32_T idx_local)
{
  int32_T colOffset;
  int32_T idx_bnd_local;
  obj->nWConstr[TYPE - 1]++;
  obj->isActiveConstr[(obj->isActiveIdx[TYPE - 1] + idx_local) - 2] = true;
  obj->nActiveConstr++;
  obj->Wid[obj->nActiveConstr - 1] = TYPE;
  obj->Wlocalidx[obj->nActiveConstr - 1] = idx_local;
  colOffset = (obj->nActiveConstr - 1) * 5 - 1;
  if (TYPE == 5) {
    idx_bnd_local = obj->indexUB[idx_local - 1];
    obj->bwset[obj->nActiveConstr - 1] = obj->ub[obj->indexUB[idx_local - 1] - 1];
  } else {
    idx_bnd_local = obj->indexLB[idx_local - 1];
    obj->bwset[obj->nActiveConstr - 1] = obj->lb[obj->indexLB[idx_local - 1] - 1];
  }

  if ((uint8_T)(idx_bnd_local - 1) - 1 >= 0) {
    memset(&obj->ATwset[colOffset + 1], 0, (uint8_T)(idx_bnd_local - 1) * sizeof
           (real_T));
  }

  obj->ATwset[idx_bnd_local + colOffset] = (real_T)(TYPE == 5) * 2.0 - 1.0;
  if (idx_bnd_local + 1 <= obj->nVar) {
    memset(&obj->ATwset[(idx_bnd_local + colOffset) + 1], 0, (uint32_T)
           (((obj->nVar + colOffset) - idx_bnd_local) - colOffset) * sizeof
           (real_T));
  }

  switch (obj->probType) {
   case 3:
   case 2:
    break;

   default:
    obj->ATwset[obj->nVar + colOffset] = -1.0;
    break;
  }
}

/* Function for MATLAB Function: '<S7>/Torque Allocation QP Normalized' */
static void ControlsMFE25_addAineqConstr(s18w5MCz6685sBFJwJZKJdG_Contr_T *obj,
  int32_T idx_local)
{
  int32_T b;
  int32_T iAineq0;
  int32_T iAw0;
  int32_T idx;
  obj->nWConstr[2]++;
  obj->isActiveConstr[(obj->isActiveIdx[2] + idx_local) - 2] = true;
  obj->nActiveConstr++;
  obj->Wid[obj->nActiveConstr - 1] = 3;
  obj->Wlocalidx[obj->nActiveConstr - 1] = idx_local;
  iAineq0 = (idx_local - 1) * 5;
  iAw0 = (obj->nActiveConstr - 1) * 5;
  b = obj->nVar;
  for (idx = 0; idx < b; idx++) {
    obj->ATwset[iAw0 + idx] = obj->Aineq[iAineq0 + idx];
  }

  obj->bwset[obj->nActiveConstr - 1] = obj->bineq;
}

/* Function for MATLAB Function: '<S7>/Torque Allocation QP Normalized' */
static void ControlsMFE25_iterate_e(const real_T H[16], const real_T f[4],
  sF7ecKzAoqUt0jrk31NyRZH_Contr_T *solution, su0bqVilpnfgpuAQ6xEtFDC_Contr_T
  *memspace, s18w5MCz6685sBFJwJZKJdG_Contr_T *workingset,
  sisnsZ1AM9QRiMKnwqarOXF_Contr_T *qrmanager, sY034dY3cx1IgSIMa0jtlQE_Contr_T
  *cholmanager, szdozZxcClCeUpd1TsA9nJF_Contr_T *objective, boolean_T
  runTimeOptions_RemainFeasible, int32_T runTimeOptions_MaxIterations, real_T
  runTimeOptions_ConstrRelTolFact, real_T runTimeOptions_ProbRelTolFactor)
{
  real_T normDelta;
  real_T solution_lambda;
  real_T tolDelta;
  int32_T TYPE;
  int32_T activeConstrChangedType;
  int32_T activeSetChangeID;
  int32_T c;
  int32_T d;
  int32_T exitg1;
  int32_T globalActiveConstrIdx;
  int32_T localActiveConstrIdx;
  int32_T nVar;
  boolean_T guard1;
  boolean_T newBlocking;
  boolean_T subProblemChanged;
  boolean_T updateFval;
  subProblemChanged = true;
  updateFval = true;
  activeSetChangeID = 0;
  TYPE = objective->objtype;
  tolDelta = 6.7434957617430445E-7;
  nVar = workingset->nVar;
  globalActiveConstrIdx = 0;
  ControlsMFE_computeGrad_StoreHx(objective, H, f, solution->xstar);
  solution->fstar = ControlsMFE_computeFval_ReuseHx(objective,
    memspace->workspace_float, f, solution->xstar);
  if (solution->iterations < runTimeOptions_MaxIterations) {
    solution->state = -5;
  } else {
    solution->state = 0;
  }

  memset(&solution->lambda[0], 0, 10U * sizeof(real_T));
  do {
    exitg1 = 0;
    if (solution->state == -5) {
      guard1 = false;
      if (subProblemChanged) {
        switch (activeSetChangeID) {
         case 1:
          ControlsMFE25_squareQ_appendCol(qrmanager, workingset->ATwset, 5 *
            (workingset->nActiveConstr - 1) + 1);
          break;

         case -1:
          ControlsMFE25_deleteColMoveEnd(qrmanager, globalActiveConstrIdx);
          break;

         default:
          ControlsMFE25_factorQR(qrmanager, workingset->ATwset, nVar,
            workingset->nActiveConstr);
          ControlsMFE25_computeQ_(qrmanager, qrmanager->mrows);
          break;
        }

        ControlsMFE25_compute_deltax(H, solution, memspace, qrmanager,
          cholmanager, objective);
        if (solution->state != -5) {
          exitg1 = 1;
        } else {
          normDelta = ControlsMFE25_xnrm2_d(nVar, solution->searchDir);
          guard1 = true;
        }
      } else {
        localActiveConstrIdx = (uint8_T)nVar;
        memset(&solution->searchDir[0], 0, (uint8_T)nVar * sizeof(real_T));
        normDelta = 0.0;
        guard1 = true;
      }

      if (guard1) {
        if ((!subProblemChanged) || (normDelta < 1.0E-8) ||
            (workingset->nActiveConstr >= nVar)) {
          ControlsMFE25_compute_lambda(memspace->workspace_float, solution,
            objective, qrmanager);
          if ((solution->state != -7) || (workingset->nActiveConstr > nVar)) {
            localActiveConstrIdx = 0;
            normDelta = 0.0 * runTimeOptions_ProbRelTolFactor * (real_T)(TYPE !=
              5);
            c = (workingset->nWConstr[0] + workingset->nWConstr[1]) + 1;
            d = workingset->nActiveConstr;
            for (activeConstrChangedType = c; activeConstrChangedType <= d;
                 activeConstrChangedType++) {
              solution_lambda = solution->lambda[activeConstrChangedType - 1];
              if (solution_lambda < normDelta) {
                normDelta = solution_lambda;
                localActiveConstrIdx = activeConstrChangedType;
              }
            }

            if (localActiveConstrIdx == 0) {
              solution->state = 1;
            } else {
              activeSetChangeID = -1;
              globalActiveConstrIdx = localActiveConstrIdx;
              subProblemChanged = true;
              ControlsMFE25_removeConstr(workingset, localActiveConstrIdx);
              if (localActiveConstrIdx < workingset->nActiveConstr + 1) {
                solution->lambda[localActiveConstrIdx - 1] = solution->
                  lambda[workingset->nActiveConstr];
              }

              solution->lambda[workingset->nActiveConstr] = 0.0;
            }
          } else {
            localActiveConstrIdx = workingset->nActiveConstr;
            activeSetChangeID = 0;
            globalActiveConstrIdx = workingset->nActiveConstr;
            subProblemChanged = true;
            ControlsMFE25_removeConstr(workingset, workingset->nActiveConstr);
            solution->lambda[localActiveConstrIdx - 1] = 0.0;
          }

          updateFval = false;
        } else {
          updateFval = (TYPE == 5);
          if (updateFval || runTimeOptions_RemainFeasible) {
            ControlsMFE25_feasibleratiotest(solution->xstar, solution->searchDir,
              memspace->workspace_float, workingset->nVar, workingset->Aineq,
              workingset->bineq, workingset->lb, workingset->ub,
              workingset->indexLB, workingset->indexUB, workingset->sizes,
              workingset->isActiveIdx, workingset->isActiveConstr,
              workingset->nWConstr, updateFval, &normDelta, &newBlocking,
              &activeConstrChangedType, &localActiveConstrIdx);
          } else {
            ControlsMFE25_ratiotest(solution->xstar, solution->searchDir,
              memspace->workspace_float, workingset->nVar, workingset->Aineq,
              workingset->bineq, workingset->lb, workingset->ub,
              workingset->indexLB, workingset->indexUB, workingset->sizes,
              workingset->isActiveIdx, workingset->isActiveConstr,
              workingset->nWConstr, &tolDelta, &normDelta, &newBlocking,
              &activeConstrChangedType, &localActiveConstrIdx);
          }

          if (newBlocking) {
            switch (activeConstrChangedType) {
             case 3:
              ControlsMFE25_addAineqConstr(workingset, localActiveConstrIdx);
              break;

             case 4:
              Cont_addBoundToActiveSetMatrix_(workingset, 4,
                localActiveConstrIdx);
              break;

             default:
              Cont_addBoundToActiveSetMatrix_(workingset, 5,
                localActiveConstrIdx);
              break;
            }

            activeSetChangeID = 1;
          } else {
            if (objective->objtype == 5) {
              if (ControlsMFE25_xnrm2_d(objective->nvar, solution->searchDir) >
                  100.0 * (real_T)objective->nvar * 1.4901161193847656E-8) {
                solution->state = 3;
              } else {
                solution->state = 4;
              }
            }

            subProblemChanged = false;
            if (workingset->nActiveConstr == 0) {
              solution->state = 1;
            }
          }

          if (!(normDelta == 0.0)) {
            for (activeConstrChangedType = 0; activeConstrChangedType < nVar;
                 activeConstrChangedType++) {
              solution->xstar[activeConstrChangedType] += normDelta *
                solution->searchDir[activeConstrChangedType];
            }
          }

          ControlsMFE_computeGrad_StoreHx(objective, H, f, solution->xstar);
          updateFval = true;
        }

        solution->iterations++;
        activeConstrChangedType = objective->nvar;
        if ((solution->iterations >= runTimeOptions_MaxIterations) &&
            ((solution->state != 1) || (objective->objtype == 5))) {
          solution->state = 0;
        }

        if (solution->iterations - solution->iterations / 50 * 50 == 0) {
          solution->maxConstr = Contro_maxConstraintViolation_m(workingset,
            solution->xstar);
          normDelta = solution->maxConstr;
          if (objective->objtype == 5) {
            normDelta = solution->maxConstr - solution->xstar[objective->nvar -
              1];
          }

          if (normDelta > 1.0E-8 * runTimeOptions_ConstrRelTolFact) {
            if (objective->nvar - 1 >= 0) {
              memcpy(&solution->searchDir[0], &solution->xstar[0], (uint32_T)
                     objective->nvar * sizeof(real_T));
            }

            newBlocking = Control_feasibleX0ForWorkingSet
              (memspace->workspace_float, solution->searchDir, workingset,
               qrmanager);
            if ((!newBlocking) && (solution->state != 0)) {
              solution->state = -2;
            }

            activeSetChangeID = 0;
            normDelta = Contro_maxConstraintViolation_m(workingset,
              solution->searchDir);
            if (normDelta < solution->maxConstr) {
              localActiveConstrIdx = (uint8_T)objective->nvar;
              if ((uint8_T)objective->nvar - 1 >= 0) {
                memcpy(&solution->xstar[0], &solution->searchDir[0], (uint8_T)
                       objective->nvar * sizeof(real_T));
              }

              solution->maxConstr = normDelta;
            }
          }
        }

        if (updateFval) {
          solution->fstar = ControlsMFE_computeFval_ReuseHx(objective,
            memspace->workspace_float, f, solution->xstar);
          if ((solution->fstar < -1.0E+20) && ((solution->state != 0) ||
               (objective->objtype != 5))) {
            solution->state = 2;
          }
        }
      }
    } else {
      if (!updateFval) {
        solution->fstar = ControlsMFE_computeFval_ReuseHx(objective,
          memspace->workspace_float, f, solution->xstar);
      }

      exitg1 = 1;
    }
  } while (exitg1 == 0);
}

/* Function for MATLAB Function: '<S7>/Torque Allocation QP Normalized' */
static void ControlsMF_computeFirstOrderOpt(sF7ecKzAoqUt0jrk31NyRZH_Contr_T
  *solution, const szdozZxcClCeUpd1TsA9nJF_Contr_T *objective, int32_T
  workingset_nVar, const real_T workingset_ATwset[50], int32_T
  workingset_nActiveConstr, real_T workspace[50])
{
  real_T infNorm;
  int32_T b;
  int32_T k;
  boolean_T exitg1;
  memcpy(&workspace[0], &objective->grad[0], (uint8_T)workingset_nVar * sizeof
         (real_T));
  if (workingset_nActiveConstr != 0) {
    int32_T c;
    int32_T ix;
    ix = 0;
    c = (workingset_nActiveConstr - 1) * 5 + 1;
    for (k = 1; k <= c; k += 5) {
      int32_T d;
      d = k + workingset_nVar;
      for (b = k; b < d; b++) {
        int32_T tmp;
        tmp = b - k;
        workspace[tmp] += workingset_ATwset[b - 1] * solution->lambda[ix];
      }

      ix++;
    }
  }

  infNorm = 0.0;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k <= (uint8_T)workingset_nVar - 1)) {
    real_T abs_workspace_i;
    abs_workspace_i = fabs(workspace[k]);
    if (rtIsNaN(abs_workspace_i)) {
      infNorm = (rtNaN);
      exitg1 = true;
    } else {
      infNorm = fmax(infNorm, abs_workspace_i);
      k++;
    }
  }

  solution->firstorderopt = infNorm;
}

/* Function for MATLAB Function: '<S7>/Torque Allocation QP Normalized' */
static int32_T ControlsMFE2_RemoveDependentEq_(su0bqVilpnfgpuAQ6xEtFDC_Contr_T
  *memspace, const s18w5MCz6685sBFJwJZKJdG_Contr_T *workingset,
  sisnsZ1AM9QRiMKnwqarOXF_Contr_T *qrmanager)
{
  int32_T b;
  int32_T idx_col;
  int32_T idx_col_0;
  int32_T idx_row;
  int32_T mTotalWorkingEq;
  int32_T nDepInd;
  int32_T nVar;
  mTotalWorkingEq = workingset->nWConstr[0] + workingset->nWConstr[1];
  nDepInd = 0;
  if (mTotalWorkingEq > 0) {
    b = (uint8_T)workingset->nVar;
    idx_row = 0;
    for (nVar = 0; nVar < mTotalWorkingEq; nVar++) {
      idx_col_0 = 0;
      for (idx_col = 0; idx_col < b; idx_col++) {
        qrmanager->QR[idx_col_0 + nVar] = workingset->ATwset[idx_col + idx_row];
        idx_col_0 += 5;
      }

      idx_row += 5;
    }

    nDepInd = Controls_ComputeNumDependentEq_(qrmanager, workingset->bwset,
      mTotalWorkingEq, workingset->nVar);
    if (nDepInd > 0) {
      idx_row = (uint8_T)workingset->nVar;
      for (nVar = 0; nVar < mTotalWorkingEq; nVar++) {
        b = 5 * nVar;
        idx_col_0 = 5 * nVar;
        for (idx_col = 0; idx_col < idx_row; idx_col++) {
          qrmanager->QR[b + idx_col] = workingset->ATwset[idx_col_0 + idx_col];
        }
      }

      ControlsMFE_IndexOfDependentEq_(memspace->workspace_int,
        workingset->nWConstr[0], nDepInd, qrmanager, workingset->nVar,
        mTotalWorkingEq);
      ControlsMFE25_countsort(memspace->workspace_int, nDepInd,
        memspace->workspace_sort, 1, mTotalWorkingEq);
      for (nVar = nDepInd; nVar >= 1; nVar--) {
        ControlsMFE25_removeEqConstr(workingset, memspace->workspace_int[nVar -
          1]);
      }
    }
  }

  return nDepInd;
}

/* Function for MATLAB Function: '<S7>/Torque Allocation QP Normalized' */
static void ControlsMFE25_phaseone(const real_T H[16], const real_T f[4],
  sF7ecKzAoqUt0jrk31NyRZH_Contr_T *solution, su0bqVilpnfgpuAQ6xEtFDC_Contr_T
  *memspace, s18w5MCz6685sBFJwJZKJdG_Contr_T *workingset,
  sisnsZ1AM9QRiMKnwqarOXF_Contr_T *qrmanager, sY034dY3cx1IgSIMa0jtlQE_Contr_T
  *cholmanager, szdozZxcClCeUpd1TsA9nJF_Contr_T *objective, const
  sIOJhD9KwAkF5sEguPjYquC_Contr_T *runTimeOptions)
{
  real_T b_options_ObjectiveLimit;
  real_T normDelta;
  real_T solution_lambda;
  int32_T PROBTYPE_ORIG;
  int32_T b_nVar;
  int32_T e;
  int32_T exitg1;
  int32_T g;
  int32_T idxEndIneq;
  int32_T idxMinLambda;
  int32_T idxStartIneq;
  int32_T k;
  int32_T nVar;
  boolean_T exitg2;
  boolean_T guard1;
  boolean_T nonDegenerateWset;
  boolean_T subProblemChanged;
  boolean_T updateFval;
  PROBTYPE_ORIG = workingset->probType;
  nVar = workingset->nVar;
  solution->xstar[4] = solution->maxConstr + 1.0;
  if (workingset->probType == 3) {
    idxEndIneq = 1;
  } else {
    idxEndIneq = 4;
  }

  ControlsMFE25_setProblemType(workingset, idxEndIneq);
  idxStartIneq = (workingset->nWConstr[0] + workingset->nWConstr[1]) + 1;
  idxEndIneq = workingset->nActiveConstr;
  for (b_nVar = idxStartIneq; b_nVar <= idxEndIneq; b_nVar++) {
    workingset->isActiveConstr[(workingset->isActiveIdx[workingset->Wid[b_nVar -
      1] - 1] + workingset->Wlocalidx[b_nVar - 1]) - 2] = false;
  }

  workingset->nWConstr[2] = 0;
  workingset->nWConstr[3] = 0;
  workingset->nWConstr[4] = 0;
  workingset->nActiveConstr = workingset->nWConstr[0] + workingset->nWConstr[1];
  objective->prev_objtype = objective->objtype;
  objective->prev_nvar = objective->nvar;
  objective->prev_hasLinear = objective->hasLinear;
  objective->objtype = 5;
  objective->nvar = 5;
  objective->gammaScalar = 1.0;
  objective->hasLinear = true;
  b_options_ObjectiveLimit = 1.0E-8 * runTimeOptions->ConstrRelTolFactor;
  subProblemChanged = true;
  updateFval = true;
  idxEndIneq = 0;
  b_nVar = workingset->nVar;
  idxStartIneq = 0;
  ControlsMFE_computeGrad_StoreHx(objective, H, f, solution->xstar);
  solution->fstar = ControlsMFE_computeFval_ReuseHx(objective,
    memspace->workspace_float, f, solution->xstar);
  if (solution->iterations < runTimeOptions->MaxIterations) {
    solution->state = -5;
  } else {
    solution->state = 0;
  }

  memset(&solution->lambda[0], 0, 10U * sizeof(real_T));
  do {
    exitg1 = 0;
    if (solution->state == -5) {
      guard1 = false;
      if (subProblemChanged) {
        switch (idxEndIneq) {
         case 1:
          ControlsMFE25_squareQ_appendCol(qrmanager, workingset->ATwset, 5 *
            (workingset->nActiveConstr - 1) + 1);
          break;

         case -1:
          ControlsMFE25_deleteColMoveEnd(qrmanager, idxStartIneq);
          break;

         default:
          ControlsMFE25_factorQR(qrmanager, workingset->ATwset, b_nVar,
            workingset->nActiveConstr);
          ControlsMFE25_computeQ_(qrmanager, qrmanager->mrows);
          break;
        }

        ControlsMFE25_compute_deltax(H, solution, memspace, qrmanager,
          cholmanager, objective);
        if (solution->state != -5) {
          exitg1 = 1;
        } else {
          normDelta = ControlsMFE25_xnrm2_d(b_nVar, solution->searchDir);
          guard1 = true;
        }
      } else {
        idxMinLambda = (uint8_T)b_nVar;
        memset(&solution->searchDir[0], 0, (uint8_T)b_nVar * sizeof(real_T));
        normDelta = 0.0;
        guard1 = true;
      }

      if (guard1) {
        if ((!subProblemChanged) || (normDelta < 1.4901161193847657E-10) ||
            (workingset->nActiveConstr >= b_nVar)) {
          ControlsMFE25_compute_lambda(memspace->workspace_float, solution,
            objective, qrmanager);
          if ((solution->state != -7) || (workingset->nActiveConstr > b_nVar)) {
            idxMinLambda = 0;
            normDelta = 0.0 * runTimeOptions->ProbRelTolFactor * 0.0;
            e = (workingset->nWConstr[0] + workingset->nWConstr[1]) + 1;
            g = workingset->nActiveConstr;
            for (k = e; k <= g; k++) {
              solution_lambda = solution->lambda[k - 1];
              if (solution_lambda < normDelta) {
                normDelta = solution_lambda;
                idxMinLambda = k;
              }
            }

            if (idxMinLambda == 0) {
              solution->state = 1;
            } else {
              idxEndIneq = -1;
              idxStartIneq = idxMinLambda;
              subProblemChanged = true;
              ControlsMFE25_removeConstr(workingset, idxMinLambda);
              if (idxMinLambda < workingset->nActiveConstr + 1) {
                solution->lambda[idxMinLambda - 1] = solution->lambda
                  [workingset->nActiveConstr];
              }

              solution->lambda[workingset->nActiveConstr] = 0.0;
            }
          } else {
            idxMinLambda = workingset->nActiveConstr;
            idxEndIneq = 0;
            idxStartIneq = workingset->nActiveConstr;
            subProblemChanged = true;
            ControlsMFE25_removeConstr(workingset, workingset->nActiveConstr);
            solution->lambda[idxMinLambda - 1] = 0.0;
          }

          updateFval = false;
        } else {
          ControlsMFE25_feasibleratiotest(solution->xstar, solution->searchDir,
            memspace->workspace_float, workingset->nVar, workingset->Aineq,
            workingset->bineq, workingset->lb, workingset->ub,
            workingset->indexLB, workingset->indexUB, workingset->sizes,
            workingset->isActiveIdx, workingset->isActiveConstr,
            workingset->nWConstr, true, &normDelta, &updateFval, &k,
            &idxMinLambda);
          if (updateFval) {
            switch (k) {
             case 3:
              ControlsMFE25_addAineqConstr(workingset, idxMinLambda);
              break;

             case 4:
              Cont_addBoundToActiveSetMatrix_(workingset, 4, idxMinLambda);
              break;

             default:
              Cont_addBoundToActiveSetMatrix_(workingset, 5, idxMinLambda);
              break;
            }

            idxEndIneq = 1;
          } else {
            if (objective->objtype == 5) {
              if (ControlsMFE25_xnrm2_d(objective->nvar, solution->searchDir) >
                  100.0 * (real_T)objective->nvar * 1.4901161193847656E-8) {
                solution->state = 3;
              } else {
                solution->state = 4;
              }
            }

            subProblemChanged = false;
            if (workingset->nActiveConstr == 0) {
              solution->state = 1;
            }
          }

          if (!(normDelta == 0.0)) {
            for (k = 0; k < b_nVar; k++) {
              solution->xstar[k] += normDelta * solution->searchDir[k];
            }
          }

          ControlsMFE_computeGrad_StoreHx(objective, H, f, solution->xstar);
          updateFval = true;
        }

        solution->iterations++;
        idxMinLambda = objective->nvar;
        if ((solution->iterations >= runTimeOptions->MaxIterations) &&
            ((solution->state != 1) || (objective->objtype == 5))) {
          solution->state = 0;
        }

        if (solution->iterations - solution->iterations / 50 * 50 == 0) {
          solution->maxConstr = Contro_maxConstraintViolation_m(workingset,
            solution->xstar);
          normDelta = solution->maxConstr;
          if (objective->objtype == 5) {
            normDelta = solution->maxConstr - solution->xstar[objective->nvar -
              1];
          }

          if (normDelta > b_options_ObjectiveLimit) {
            if (objective->nvar - 1 >= 0) {
              memcpy(&solution->searchDir[0], &solution->xstar[0], (uint32_T)
                     objective->nvar * sizeof(real_T));
            }

            nonDegenerateWset = Control_feasibleX0ForWorkingSet
              (memspace->workspace_float, solution->searchDir, workingset,
               qrmanager);
            if ((!nonDegenerateWset) && (solution->state != 0)) {
              solution->state = -2;
            }

            idxEndIneq = 0;
            normDelta = Contro_maxConstraintViolation_m(workingset,
              solution->searchDir);
            if ((normDelta < solution->maxConstr) && (objective->nvar - 1 >= 0))
            {
              memcpy(&solution->xstar[0], &solution->searchDir[0], (uint32_T)
                     objective->nvar * sizeof(real_T));
            }
          }
        }

        if (updateFval) {
          solution->fstar = ControlsMFE_computeFval_ReuseHx(objective,
            memspace->workspace_float, f, solution->xstar);
          if ((solution->fstar < b_options_ObjectiveLimit) && ((solution->state
                != 0) || (objective->objtype != 5))) {
            solution->state = 2;
          }
        }
      }
    } else {
      if (!updateFval) {
        solution->fstar = ControlsMFE_computeFval_ReuseHx(objective,
          memspace->workspace_float, f, solution->xstar);
      }

      exitg1 = 1;
    }
  } while (exitg1 == 0);

  if (workingset->isActiveConstr[(workingset->isActiveIdx[3] + workingset->
       sizes[3]) - 2]) {
    b_nVar = workingset->sizes[0];
    exitg2 = false;
    while ((!exitg2) && (b_nVar + 1 <= workingset->nActiveConstr)) {
      if ((workingset->Wid[b_nVar] == 4) && (workingset->Wlocalidx[b_nVar] ==
           workingset->sizes[3])) {
        ControlsMFE25_removeConstr(workingset, b_nVar + 1);
        exitg2 = true;
      } else {
        b_nVar++;
      }
    }
  }

  b_nVar = workingset->nActiveConstr;
  while ((b_nVar > workingset->sizes[0]) && (b_nVar > nVar)) {
    ControlsMFE25_removeConstr(workingset, b_nVar);
    b_nVar--;
  }

  solution->maxConstr = solution->xstar[4];
  ControlsMFE25_setProblemType(workingset, PROBTYPE_ORIG);
  objective->objtype = objective->prev_objtype;
  objective->nvar = objective->prev_nvar;
  objective->hasLinear = objective->prev_hasLinear;
}

/* Function for MATLAB Function: '<S7>/Torque Allocation QP Normalized' */
static void ControlsMFE25_iterate(const real_T H[16], const real_T f[4],
  sF7ecKzAoqUt0jrk31NyRZH_Contr_T *solution, su0bqVilpnfgpuAQ6xEtFDC_Contr_T
  *memspace, s18w5MCz6685sBFJwJZKJdG_Contr_T *workingset,
  sisnsZ1AM9QRiMKnwqarOXF_Contr_T *qrmanager, sY034dY3cx1IgSIMa0jtlQE_Contr_T
  *cholmanager, szdozZxcClCeUpd1TsA9nJF_Contr_T *objective, real_T
  options_ObjectiveLimit, int32_T runTimeOptions_MaxIterations, real_T
  runTimeOptions_ConstrRelTolFact, real_T runTimeOptions_ProbRelTolFactor)
{
  real_T b_c;
  real_T denomTol;
  real_T normDelta;
  real_T ratio;
  int32_T activeSetChangeID;
  int32_T b_nVar;
  int32_T e_k;
  int32_T exitg1;
  int32_T globalActiveConstrIdx;
  int32_T ia;
  int32_T idxMinLambda;
  int32_T idx_local;
  int32_T nVar;
  boolean_T guard1;
  boolean_T nonDegenerateWset;
  boolean_T subProblemChanged;
  boolean_T updateFval;
  subProblemChanged = true;
  updateFval = true;
  activeSetChangeID = 0;
  nVar = workingset->nVar;
  globalActiveConstrIdx = 0;
  ControlsMFE_computeGrad_StoreHx(objective, H, f, solution->xstar);
  solution->fstar = ControlsMFE_computeFval_ReuseHx(objective,
    memspace->workspace_float, f, solution->xstar);
  solution->state = -5;
  memset(&solution->lambda[0], 0, 10U * sizeof(real_T));
  do {
    exitg1 = 0;
    if (solution->state == -5) {
      guard1 = false;
      if (subProblemChanged) {
        switch (activeSetChangeID) {
         case 1:
          ControlsMFE25_squareQ_appendCol(qrmanager, workingset->ATwset, 5 *
            (workingset->nActiveConstr - 1) + 1);
          break;

         case -1:
          ControlsMFE25_deleteColMoveEnd(qrmanager, globalActiveConstrIdx);
          break;

         default:
          ControlsMFE25_factorQR(qrmanager, workingset->ATwset, nVar,
            workingset->nActiveConstr);
          ControlsMFE25_computeQ_(qrmanager, qrmanager->mrows);
          break;
        }

        ControlsMFE25_compute_deltax(H, solution, memspace, qrmanager,
          cholmanager, objective);
        if (solution->state != -5) {
          exitg1 = 1;
        } else {
          normDelta = ControlsMFE25_xnrm2_d(nVar, solution->searchDir);
          guard1 = true;
        }
      } else {
        memset(&solution->searchDir[0], 0, (uint8_T)nVar * sizeof(real_T));
        normDelta = 0.0;
        guard1 = true;
      }

      if (guard1) {
        if ((!subProblemChanged) || (normDelta < 1.4901161193847657E-10) ||
            (workingset->nActiveConstr >= nVar)) {
          ControlsMFE25_compute_lambda(memspace->workspace_float, solution,
            objective, qrmanager);
          if ((solution->state != -7) || (workingset->nActiveConstr > nVar)) {
            idxMinLambda = 0;
            normDelta = 0.0 * runTimeOptions_ProbRelTolFactor * 0.0;
            idx_local = (workingset->nWConstr[0] + workingset->nWConstr[1]) + 1;
            e_k = workingset->nActiveConstr;
            for (b_nVar = idx_local; b_nVar <= e_k; b_nVar++) {
              denomTol = solution->lambda[b_nVar - 1];
              if (denomTol < normDelta) {
                normDelta = denomTol;
                idxMinLambda = b_nVar;
              }
            }

            if (idxMinLambda == 0) {
              solution->state = 1;
            } else {
              activeSetChangeID = -1;
              globalActiveConstrIdx = idxMinLambda;
              subProblemChanged = true;
              ControlsMFE25_removeConstr(workingset, idxMinLambda);
              if (idxMinLambda < workingset->nActiveConstr + 1) {
                solution->lambda[idxMinLambda - 1] = solution->lambda
                  [workingset->nActiveConstr];
              }

              solution->lambda[workingset->nActiveConstr] = 0.0;
            }
          } else {
            idxMinLambda = workingset->nActiveConstr;
            activeSetChangeID = 0;
            globalActiveConstrIdx = workingset->nActiveConstr;
            subProblemChanged = true;
            ControlsMFE25_removeConstr(workingset, workingset->nActiveConstr);
            solution->lambda[idxMinLambda - 1] = 0.0;
          }

          updateFval = false;
        } else {
          b_nVar = workingset->nVar - 1;
          normDelta = 1.0E+30;
          updateFval = false;
          idxMinLambda = 0;
          idx_local = 0;
          denomTol = 2.2204460492503131E-13 * ControlsMFE25_xnrm2_d
            (workingset->nVar, solution->searchDir);
          if (workingset->nWConstr[2] < 1) {
            memspace->workspace_float[0] = workingset->bineq;
            memspace->workspace_float[0] = -memspace->workspace_float[0];
            b_c = 0.0;
            for (ia = 1; ia <= b_nVar + 1; ia++) {
              b_c += workingset->Aineq[ia - 1] * solution->xstar[ia - 1];
            }

            memspace->workspace_float[0] += b_c;
            memspace->workspace_float[10] = 0.0;
            b_c = 0.0;
            for (ia = 1; ia <= b_nVar + 1; ia++) {
              b_c += workingset->Aineq[ia - 1] * solution->searchDir[ia - 1];
            }

            memspace->workspace_float[10] += b_c;
            if ((memspace->workspace_float[10] > denomTol) &&
                (!workingset->isActiveConstr[workingset->isActiveIdx[2] - 1])) {
              b_c = fmin(fabs(memspace->workspace_float[0]), 1.0E-8 -
                         memspace->workspace_float[0]) /
                memspace->workspace_float[10];
              if (b_c < 1.0E+30) {
                normDelta = b_c;
                idxMinLambda = 3;
                idx_local = 1;
                updateFval = true;
              }
            }
          }

          if (workingset->nWConstr[3] < workingset->sizes[3]) {
            ia = workingset->sizes[3];
            for (e_k = 0; e_k <= ia - 2; e_k++) {
              b_c = -solution->searchDir[workingset->indexLB[e_k] - 1] -
                solution->searchDir[b_nVar];
              if ((b_c > denomTol) && (!workingset->isActiveConstr
                   [(workingset->isActiveIdx[3] + e_k) - 1])) {
                ratio = (-solution->xstar[workingset->indexLB[e_k] - 1] -
                         workingset->lb[workingset->indexLB[e_k] - 1]) -
                  solution->xstar[b_nVar];
                b_c = fmin(fabs(ratio), 1.0E-8 - ratio) / b_c;
                if (b_c < normDelta) {
                  normDelta = b_c;
                  idxMinLambda = 4;
                  idx_local = e_k + 1;
                  updateFval = true;
                }
              }
            }

            if ((-solution->searchDir[workingset->indexLB[workingset->sizes[3] -
                 1] - 1] > denomTol) && (!workingset->isActiveConstr
                 [(workingset->isActiveIdx[3] + workingset->sizes[3]) - 2])) {
              ratio = -solution->xstar[workingset->indexLB[workingset->sizes[3]
                - 1] - 1] - workingset->lb[workingset->indexLB[workingset->
                sizes[3] - 1] - 1];
              b_c = fmin(fabs(ratio), 1.0E-8 - ratio) / -solution->
                searchDir[workingset->indexLB[workingset->sizes[3] - 1] - 1];
              if (b_c < normDelta) {
                normDelta = b_c;
                idxMinLambda = 4;
                idx_local = workingset->sizes[3];
                updateFval = true;
              }
            }
          }

          if (workingset->nWConstr[4] < workingset->sizes[4]) {
            ia = (uint8_T)workingset->sizes[4];
            for (e_k = 0; e_k < ia; e_k++) {
              b_c = solution->searchDir[workingset->indexUB[e_k] - 1] -
                solution->searchDir[b_nVar];
              if ((b_c > denomTol) && (!workingset->isActiveConstr
                   [(workingset->isActiveIdx[4] + e_k) - 1])) {
                ratio = (solution->xstar[workingset->indexUB[e_k] - 1] -
                         workingset->ub[workingset->indexUB[e_k] - 1]) -
                  solution->xstar[b_nVar];
                b_c = fmin(fabs(ratio), 1.0E-8 - ratio) / b_c;
                if (b_c < normDelta) {
                  normDelta = b_c;
                  idxMinLambda = 5;
                  idx_local = e_k + 1;
                  updateFval = true;
                }
              }
            }
          }

          if (updateFval) {
            switch (idxMinLambda) {
             case 3:
              ControlsMFE25_addAineqConstr(workingset, idx_local);
              break;

             case 4:
              Cont_addBoundToActiveSetMatrix_(workingset, 4, idx_local);
              break;

             default:
              Cont_addBoundToActiveSetMatrix_(workingset, 5, idx_local);
              break;
            }

            activeSetChangeID = 1;
          } else {
            if (objective->objtype == 5) {
              if (ControlsMFE25_xnrm2_d(objective->nvar, solution->searchDir) >
                  100.0 * (real_T)objective->nvar * 1.4901161193847656E-8) {
                solution->state = 3;
              } else {
                solution->state = 4;
              }
            }

            subProblemChanged = false;
            if (workingset->nActiveConstr == 0) {
              solution->state = 1;
            }
          }

          if (!(normDelta == 0.0)) {
            for (b_nVar = 0; b_nVar < nVar; b_nVar++) {
              solution->xstar[b_nVar] += normDelta * solution->searchDir[b_nVar];
            }
          }

          ControlsMFE_computeGrad_StoreHx(objective, H, f, solution->xstar);
          updateFval = true;
        }

        solution->iterations++;
        if (solution->iterations >= runTimeOptions_MaxIterations) {
          solution->state = 0;
        }

        if (solution->iterations - solution->iterations / 50 * 50 == 0) {
          solution->maxConstr = Contro_maxConstraintViolation_m(workingset,
            solution->xstar);
          if (solution->maxConstr - solution->xstar[4] > 1.0E-8 *
              runTimeOptions_ConstrRelTolFact) {
            for (activeSetChangeID = 0; activeSetChangeID < 5; activeSetChangeID
                 ++) {
              solution->searchDir[activeSetChangeID] = solution->
                xstar[activeSetChangeID];
            }

            nonDegenerateWset = Control_feasibleX0ForWorkingSet
              (memspace->workspace_float, solution->searchDir, workingset,
               qrmanager);
            if ((!nonDegenerateWset) && (solution->state != 0)) {
              solution->state = -2;
            }

            activeSetChangeID = 0;
            normDelta = Contro_maxConstraintViolation_m(workingset,
              solution->searchDir);
            if (normDelta < solution->maxConstr) {
              for (b_nVar = 0; b_nVar < 5; b_nVar++) {
                solution->xstar[b_nVar] = solution->searchDir[b_nVar];
              }

              solution->maxConstr = normDelta;
            }
          }
        }

        if (updateFval) {
          solution->fstar = ControlsMFE_computeFval_ReuseHx(objective,
            memspace->workspace_float, f, solution->xstar);
          if ((solution->fstar < options_ObjectiveLimit) && (solution->state !=
               0)) {
            solution->state = 2;
          }
        }
      }
    } else {
      if (!updateFval) {
        solution->fstar = ControlsMFE_computeFval_ReuseHx(objective,
          memspace->workspace_float, f, solution->xstar);
      }

      exitg1 = 1;
    }
  } while (exitg1 == 0);
}

/* Function for MATLAB Function: '<S7>/Torque Allocation QP Normalized' */
static void ControlsMFE25_driver(const real_T H[16], const real_T f[4],
  sF7ecKzAoqUt0jrk31NyRZH_Contr_T *solution, su0bqVilpnfgpuAQ6xEtFDC_Contr_T
  *memspace, s18w5MCz6685sBFJwJZKJdG_Contr_T *workingset,
  sY034dY3cx1IgSIMa0jtlQE_Contr_T *cholmanager, sIOJhD9KwAkF5sEguPjYquC_Contr_T
  runTimeOptions, sisnsZ1AM9QRiMKnwqarOXF_Contr_T *qrmanager,
  szdozZxcClCeUpd1TsA9nJF_Contr_T *objective)
{
  s18w5MCz6685sBFJwJZKJdG_Contr_T b_workingset;
  real_T b_c;
  real_T tmp;
  int32_T i;
  int32_T idxEndIneq;
  int32_T idxStartIneq;
  int32_T mConstr;
  boolean_T exitg1;
  boolean_T guard1;
  boolean_T guard2;
  boolean_T okWorkingSet;
  for (i = 0; i < 5; i++) {
    objective->grad[i] = 0.0;
  }

  objective->Hx[0] = 0.0;
  objective->Hx[1] = 0.0;
  objective->Hx[2] = 0.0;
  objective->Hx[3] = 0.0;
  objective->hasLinear = true;
  objective->nvar = 4;
  objective->maxVar = 5;
  objective->beta = 0.0;
  objective->rho = 0.0;
  objective->objtype = 3;
  objective->prev_objtype = 3;
  objective->prev_nvar = 0;
  objective->prev_hasLinear = false;
  objective->gammaScalar = 0.0;
  solution->iterations = 0;
  i = workingset->nVar;
  idxStartIneq = (uint8_T)workingset->sizes[0];
  for (mConstr = 0; mConstr < idxStartIneq; mConstr++) {
    solution->xstar[workingset->indexFixed[mConstr] - 1] = workingset->
      ub[workingset->indexFixed[mConstr] - 1];
  }

  idxStartIneq = (uint8_T)workingset->sizes[3];
  for (mConstr = 0; mConstr < idxStartIneq; mConstr++) {
    if (workingset->isActiveConstr[(workingset->isActiveIdx[3] + mConstr) - 1])
    {
      solution->xstar[workingset->indexLB[mConstr] - 1] = -workingset->
        lb[workingset->indexLB[mConstr] - 1];
    }
  }

  idxStartIneq = (uint8_T)workingset->sizes[4];
  for (mConstr = 0; mConstr < idxStartIneq; mConstr++) {
    if (workingset->isActiveConstr[(workingset->isActiveIdx[4] + mConstr) - 1])
    {
      solution->xstar[workingset->indexUB[mConstr] - 1] = workingset->
        ub[workingset->indexUB[mConstr] - 1];
    }
  }

  ControlsMFE2_PresolveWorkingSet(solution, memspace, workingset, qrmanager);
  if (solution->state >= 0) {
    solution->iterations = 0;
    solution->maxConstr = Contro_maxConstraintViolation_m(workingset,
      solution->xstar);
    tmp = 1.0E-8 * runTimeOptions.ConstrRelTolFactor;
    guard1 = false;
    if (solution->maxConstr > tmp) {
      solution->xstar[4] = solution->maxConstr + 1.0;
      b_workingset = *workingset;
      ControlsMFE25_setProblemType(&b_workingset, 1);
      idxStartIneq = (b_workingset.nWConstr[0] + b_workingset.nWConstr[1]) + 1;
      idxEndIneq = b_workingset.nActiveConstr;
      for (mConstr = idxStartIneq; mConstr <= idxEndIneq; mConstr++) {
        b_workingset.isActiveConstr
          [(b_workingset.isActiveIdx[b_workingset.Wid[mConstr - 1] - 1] +
            b_workingset.Wlocalidx[mConstr - 1]) - 2] = false;
      }

      b_workingset.nWConstr[2] = 0;
      b_workingset.nWConstr[3] = 0;
      b_workingset.nWConstr[4] = 0;
      b_workingset.nActiveConstr = b_workingset.nWConstr[0] +
        b_workingset.nWConstr[1];
      objective->prev_objtype = 3;
      objective->prev_nvar = 4;
      objective->prev_hasLinear = true;
      objective->objtype = 5;
      objective->nvar = 5;
      objective->gammaScalar = 1.0;
      objective->hasLinear = true;
      solution->fstar = solution->xstar[4];
      solution->state = 5;
      ControlsMFE25_iterate(H, f, solution, memspace, &b_workingset, qrmanager,
                            cholmanager, objective, tmp,
                            runTimeOptions.MaxIterations,
                            runTimeOptions.ConstrRelTolFactor,
                            runTimeOptions.ProbRelTolFactor);
      if (b_workingset.isActiveConstr[(b_workingset.isActiveIdx[3] +
           b_workingset.sizes[3]) - 2]) {
        mConstr = b_workingset.sizes[0];
        exitg1 = false;
        while ((!exitg1) && (mConstr + 1 <= b_workingset.nActiveConstr)) {
          if ((b_workingset.Wid[mConstr] == 4) &&
              (b_workingset.Wlocalidx[mConstr] == b_workingset.sizes[3])) {
            ControlsMFE25_removeConstr(&b_workingset, mConstr + 1);
            exitg1 = true;
          } else {
            mConstr++;
          }
        }
      }

      mConstr = b_workingset.nActiveConstr;
      while ((mConstr > b_workingset.sizes[0]) && (mConstr > workingset->nVar))
      {
        ControlsMFE25_removeConstr(&b_workingset, mConstr);
        mConstr--;
      }

      solution->maxConstr = solution->xstar[4];
      ControlsMFE25_setProblemType(&b_workingset, 3);
      objective->objtype = objective->prev_objtype;
      objective->nvar = objective->prev_nvar;
      objective->hasLinear = objective->prev_hasLinear;
      *workingset = b_workingset;
      if (solution->state == 0) {
      } else {
        solution->maxConstr = Contro_maxConstraintViolation_m(&b_workingset,
          solution->xstar);
        *workingset = b_workingset;
        if (solution->maxConstr > tmp) {
          memset(&solution->lambda[0], 0, 10U * sizeof(real_T));
          memspace->workspace_float[0] = f[0];
          memspace->workspace_float[1] = f[1];
          memspace->workspace_float[2] = f[2];
          memspace->workspace_float[3] = f[3];
          for (i = 0; i <= 12; i += 4) {
            b_c = solution->xstar[i >> 2] * 0.5;
            for (mConstr = i + 1; mConstr <= i + 4; mConstr++) {
              idxStartIneq = (mConstr - i) - 1;
              memspace->workspace_float[idxStartIneq] += H[mConstr - 1] * b_c;
            }
          }

          solution->fstar = ((solution->xstar[0] * memspace->workspace_float[0]
                              + solution->xstar[1] * memspace->workspace_float[1])
                             + solution->xstar[2] * memspace->workspace_float[2])
            + solution->xstar[3] * memspace->workspace_float[3];
          solution->state = -2;
        } else {
          if (solution->maxConstr > 0.0) {
            if (i - 1 >= 0) {
              memcpy(&solution->searchDir[0], &solution->xstar[0], (uint32_T)i *
                     sizeof(real_T));
            }

            solution->state = 82;
            mConstr = ControlsMFE2_RemoveDependentEq_(memspace, &b_workingset,
              qrmanager);
            if ((mConstr != -1) && (b_workingset.nActiveConstr <= 5)) {
              ControlsMF_RemoveDependentIneq_(&b_workingset, qrmanager, memspace,
                1.0);
              okWorkingSet = Control_feasibleX0ForWorkingSet
                (memspace->workspace_float, solution->xstar, &b_workingset,
                 qrmanager);
              guard2 = false;
              if (!okWorkingSet) {
                ControlsMF_RemoveDependentIneq_(&b_workingset, qrmanager,
                  memspace, 10.0);
                okWorkingSet = Control_feasibleX0ForWorkingSet
                  (memspace->workspace_float, solution->xstar, &b_workingset,
                   qrmanager);
                if (!okWorkingSet) {
                  solution->state = -7;
                } else {
                  guard2 = true;
                }
              } else {
                guard2 = true;
              }

              if (guard2) {
                if (b_workingset.nWConstr[0] + b_workingset.nWConstr[1] ==
                    b_workingset.nVar) {
                  b_c = Contro_maxConstraintViolation_m(&b_workingset,
                    solution->xstar);
                  if (b_c > 1.0E-8) {
                    solution->state = -2;
                  }
                }
              }
            } else {
              solution->state = -3;
              idxStartIneq = (b_workingset.nWConstr[0] + b_workingset.nWConstr[1])
                + 1;
              idxEndIneq = b_workingset.nActiveConstr;
              for (mConstr = idxStartIneq; mConstr <= idxEndIneq; mConstr++) {
                b_workingset.isActiveConstr
                  [(b_workingset.isActiveIdx[b_workingset.Wid[mConstr - 1] - 1]
                    + b_workingset.Wlocalidx[mConstr - 1]) - 2] = false;
              }

              b_workingset.nWConstr[2] = 0;
              b_workingset.nWConstr[3] = 0;
              b_workingset.nWConstr[4] = 0;
              b_workingset.nActiveConstr = b_workingset.nWConstr[0] +
                b_workingset.nWConstr[1];
            }

            *workingset = b_workingset;
            b_c = Contro_maxConstraintViolation_m(workingset, solution->xstar);
            if (b_c >= solution->maxConstr) {
              solution->maxConstr = b_c;
              if (i - 1 >= 0) {
                memcpy(&solution->xstar[0], &solution->searchDir[0], (uint32_T)i
                       * sizeof(real_T));
              }
            }
          }

          guard1 = true;
        }
      }
    } else {
      guard1 = true;
    }

    if (guard1) {
      ControlsMFE25_iterate_e(H, f, solution, memspace, workingset, qrmanager,
        cholmanager, objective, true, runTimeOptions.MaxIterations,
        runTimeOptions.ConstrRelTolFactor, runTimeOptions.ProbRelTolFactor);
      if (solution->state != -6) {
        solution->maxConstr = Contro_maxConstraintViolation_m(workingset,
          solution->xstar);
        ControlsMF_computeFirstOrderOpt(solution, objective, workingset->nVar,
          workingset->ATwset, workingset->nActiveConstr,
          memspace->workspace_float);
        runTimeOptions.RemainFeasible = false;
        while ((solution->iterations < runTimeOptions.MaxIterations) &&
               ((solution->state == -7) || ((solution->state == 1) &&
                 ((solution->maxConstr > tmp) || (solution->firstorderopt >
                   1.0E-8 * runTimeOptions.ProbRelTolFactor))))) {
          Control_feasibleX0ForWorkingSet(memspace->workspace_float,
            solution->xstar, workingset, qrmanager);
          solution->state = 82;
          i = ControlsMFE2_RemoveDependentEq_(memspace, workingset, qrmanager);
          if ((i != -1) && (workingset->nActiveConstr <= 5)) {
            ControlsMF_RemoveDependentIneq_(workingset, qrmanager, memspace, 1.0);
            okWorkingSet = Control_feasibleX0ForWorkingSet
              (memspace->workspace_float, solution->xstar, workingset, qrmanager);
            guard2 = false;
            if (!okWorkingSet) {
              ControlsMF_RemoveDependentIneq_(workingset, qrmanager, memspace,
                10.0);
              okWorkingSet = Control_feasibleX0ForWorkingSet
                (memspace->workspace_float, solution->xstar, workingset,
                 qrmanager);
              if (!okWorkingSet) {
                solution->state = -7;
              } else {
                guard2 = true;
              }
            } else {
              guard2 = true;
            }

            if (guard2) {
              if (workingset->nWConstr[0] + workingset->nWConstr[1] ==
                  workingset->nVar) {
                b_c = Contro_maxConstraintViolation_m(workingset,
                  solution->xstar);
                if (b_c > 1.0E-8) {
                  solution->state = -2;
                }
              }
            }
          } else {
            solution->state = -3;
            mConstr = (workingset->nWConstr[0] + workingset->nWConstr[1]) + 1;
            idxStartIneq = workingset->nActiveConstr;
            for (i = mConstr; i <= idxStartIneq; i++) {
              workingset->isActiveConstr[(workingset->isActiveIdx
                [workingset->Wid[i - 1] - 1] + workingset->Wlocalidx[i - 1]) - 2]
                = false;
            }

            workingset->nWConstr[2] = 0;
            workingset->nWConstr[3] = 0;
            workingset->nWConstr[4] = 0;
            workingset->nActiveConstr = workingset->nWConstr[0] +
              workingset->nWConstr[1];
          }

          ControlsMFE25_phaseone(H, f, solution, memspace, workingset, qrmanager,
            cholmanager, objective, &runTimeOptions);
          ControlsMFE25_iterate_e(H, f, solution, memspace, workingset,
            qrmanager, cholmanager, objective, false,
            runTimeOptions.MaxIterations, runTimeOptions.ConstrRelTolFactor,
            runTimeOptions.ProbRelTolFactor);
          solution->maxConstr = Contro_maxConstraintViolation_m(workingset,
            solution->xstar);
          ControlsMF_computeFirstOrderOpt(solution, objective, workingset->nVar,
            workingset->ATwset, workingset->nActiveConstr,
            memspace->workspace_float);
        }
      }
    }
  }
}

/* Model step function */
void ControlsMFE25_step(RT_MODEL_ControlsMFE25_T *const ControlsMFE25_M)
{
  B_ControlsMFE25_T *ControlsMFE25_B = ControlsMFE25_M->blockIO;
  DW_ControlsMFE25_T *ControlsMFE25_DW = ControlsMFE25_M->dwork;
  ExtU_ControlsMFE25_T *ControlsMFE25_U = (ExtU_ControlsMFE25_T *)
    ControlsMFE25_M->inputs;
  ExtY_ControlsMFE25_T *ControlsMFE25_Y = (ExtY_ControlsMFE25_T *)
    ControlsMFE25_M->outputs;
  s18w5MCz6685sBFJwJZKJdG_Contr_T WorkingSet;
  sF7ecKzAoqUt0jrk31NyRZH_Contr_T solution;
  sIOJhD9KwAkF5sEguPjYquC_Contr_T expl_temp;
  sY034dY3cx1IgSIMa0jtlQE_Contr_T CholRegManager;
  sdAmwXbnJnEmimT0NaJRtAD_Contr_T savedTime;
  sisnsZ1AM9QRiMKnwqarOXF_Contr_T QRManager;
  su0bqVilpnfgpuAQ6xEtFDC_Contr_T memspace;
  szdozZxcClCeUpd1TsA9nJF_Contr_T QPObjective;
  real_T rtb_Product5_i[200];
  real_T A[49];
  real_T R[49];
  real_T A_0[16];
  real_T A_1[16];
  real_T H_tmp[16];
  real_T A_tmp_1[14];
  real_T X[14];
  real_T rtb_TmpSignalConversionAtSFunct[7];
  real_T v[7];
  real_T d[4];
  real_T f[4];
  real_T lb[4];
  real_T rtb_Switch2[4];
  real_T x0[4];
  real_T rtb_vx_est[2];
  real_T B0;
  real_T B1;
  real_T Integrator;
  real_T Integrator_h;
  real_T Integrator_h_tmp;
  real_T Integrator_n;
  real_T Integrator_n2;
  real_T Integrator_n_tmp;
  real_T Integrator_tmp;
  real_T K_ratio;
  real_T Sign;
  real_T Switch2;
  real_T Switch3;
  real_T lty;
  real_T rtb_CyAlphaF;
  real_T rtb_Filter_p;
  real_T rtb_IProdOut;
  real_T rtb_Integrator;
  real_T rtb_NProdOut_e;
  real_T rtb_NProdOut_h;
  real_T rtb_Product1_c;
  real_T rtb_Product_j;
  real_T rtb_Saturation_idx_0;
  real_T rtb_Saturation_idx_1;
  real_T rtb_Saturation_idx_2;
  real_T rtb_Saturation_idx_3;
  real_T rtb_SumFdbk_hw;
  real_T rtb_Switch;
  real_T rtb_Switch1;
  real_T rtb_Switch2_g;
  real_T rtb_Switch2_nz;
  real_T rtb_Switch2_p2_idx_0;
  real_T rtb_Switch2_p2_idx_0_0;
  real_T rtb_Switch2_p2_idx_1;
  real_T rtb_Switch2_p2_idx_1_0;
  real_T rtb_Switch2_p2_idx_2;
  real_T rtb_Switch2_p2_idx_2_0;
  real_T rtb_Switch2_p2_idx_3;
  real_T rtb_Switch2_p2_idx_3_0;
  real_T rtb_TmpSignalConversionAtDotP_0;
  real_T rtb_TmpSignalConversionAtDotP_1;
  real_T rtb_TmpSignalConversionAtDotP_2;
  real_T rtb_TmpSignalConversionAtDotP_3;
  real_T rtb_msr_idx_0;
  real_T rtb_msr_idx_1;
  real_T rtb_msr_idx_2;
  real_T rtb_msr_idx_3;
  real_T rtb_reference_idx_0;
  real_T rtb_reference_idx_1;
  real_T rtb_reference_idx_2;
  real_T rtb_reference_idx_3;
  real_T s;
  real_T slip_idx_0;
  real_T slip_idx_1;
  real_T slip_idx_2;
  real_T slip_idx_3;
  real_T smax;
  real_T w_n;
  real_T wheelbase_tmp;
  int32_T b_ix;
  int32_T ix;
  int32_T iy;
  int32_T jA;
  int32_T jj;
  int32_T jp;
  int32_T k;
  int8_T A_tmp[14];
  int8_T A_tmp_0[14];
  int8_T ipiv[7];
  int8_T ipiv_0;
  int8_T tmp;
  boolean_T x[4];
  boolean_T rtb_LogicalOperator;
  boolean_T rtb_LowerRelop1_nk_idx_0;
  boolean_T rtb_LowerRelop1_nk_idx_1;
  boolean_T rtb_LowerRelop1_nk_idx_2;
  boolean_T rtb_LowerRelop1_nk_idx_3;
  boolean_T rtb_RelationalOperator;
  boolean_T rtb_fixforDTpropagationissue;
  static const int8_T d_0[14] = { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1 };

  static const int8_T b_a[14] = { 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1 };

  static const int8_T c_b[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1
  };

  boolean_T exitg1;
  boolean_T guard1;

  /* SignalConversion generated from: '<S1>/Dot Product' */
  rtb_TmpSignalConversionAtDotP_0 = ControlsMFE25_U->om_fl;
  rtb_TmpSignalConversionAtDotP_1 = ControlsMFE25_U->om_fr;
  rtb_TmpSignalConversionAtDotP_2 = ControlsMFE25_U->om_rl;
  rtb_TmpSignalConversionAtDotP_3 = ControlsMFE25_U->om_rr;

  /* MATLAB Function: '<S1>/MATLAB Function2' */
  rtb_Product_j = ControlsMFE25_U->yaw_rate;
  if (fabs(ControlsMFE25_U->yaw_rate) < 0.05) {
    rtb_Product_j = 0.0;
  }

  /* Logic: '<S307>/Logical Operator' incorporates:
   *  Constant: '<S307>/Time constant'
   *  Constant: '<S311>/Constant'
   *  RelationalOperator: '<S311>/Compare'
   *  Sum: '<S307>/Sum1'
   */
  rtb_LogicalOperator = ((0.1 - ControlsMFE25_B->Probe[0] <= 0.0) &&
    ControlsMFE25_ConstB.Compare);

  /* Outport: '<Root>/wheelA' incorporates:
   *  Constant: '<Root>/Constant21'
   *  Product: '<S1>/Product1'
   */
  ControlsMFE25_Y->wheelA = 0.225 * ControlsMFE25_U->SWA;

  /* DiscreteIntegrator: '<S313>/Integrator' */
  if (ControlsMFE25_DW->Integrator_IC_LOADING != 0) {
    ControlsMFE25_DW->Integrator_DSTATE = ControlsMFE25_Y->wheelA;
  }

  if (rtb_LogicalOperator || (ControlsMFE25_DW->Integrator_PrevResetState != 0))
  {
    ControlsMFE25_DW->Integrator_DSTATE = ControlsMFE25_Y->wheelA;
  }

  rtb_Integrator = ControlsMFE25_DW->Integrator_DSTATE;

  /* MATLAB Function: '<S15>/MATLAB Function1' */
  smax = fmax(ControlsMFE25_U->vehicle_speed, 0.5);

  /* SignalConversion generated from: '<S322>/ SFunction ' incorporates:
   *  DiscreteIntegrator: '<S313>/Integrator'
   *  Gain: '<S15>/Gain'
   *  MATLAB Function: '<S15>/MATLAB Function1'
   *  MATLAB Function: '<S15>/MATLAB Function2'
   *  MATLAB Function: '<S1>/MATLAB Function2'
   */
  rtb_TmpSignalConversionAtSFunct[0] = 0.1975 * ControlsMFE25_U->om_fl;
  rtb_TmpSignalConversionAtSFunct[1] = 0.1975 * ControlsMFE25_U->om_fr;
  rtb_TmpSignalConversionAtSFunct[2] = 0.1975 * ControlsMFE25_U->om_rl;
  rtb_TmpSignalConversionAtSFunct[3] = 0.1975 * ControlsMFE25_U->om_rr;
  rtb_TmpSignalConversionAtSFunct[4] = ControlsMFE25_U->vehicle_speed;
  rtb_TmpSignalConversionAtSFunct[5] = ControlsMFE25_U->vy;
  rtb_TmpSignalConversionAtSFunct[6] = ((80000.0 *
    ControlsMFE25_DW->Integrator_DSTATE * smax - -8000.0 * rtb_Product_j) -
    ControlsMFE25_U->ay * 270.0 * smax) / 160000.0;

  /* MATLAB Function: '<S15>/MATLAB Function2' incorporates:
   *  Constant: '<S17>/r0'
   *  Constant: '<S17>/r1'
   */
  if (!ControlsMFE25_DW->is_initialized_not_empty) {
    ControlsMFE25_DW->x_pred[0] = ControlsMFE25_U->vehicle_speed;
    ControlsMFE25_DW->x_pred[1] = ControlsMFE25_U->vy;
    ControlsMFE25_DW->is_initialized_not_empty = true;
  }

  v[0] = fabs(rtb_TmpSignalConversionAtSFunct[0] - ControlsMFE25_DW->x_pred[0]) *
    2.0 + 0.1;
  v[1] = fabs(rtb_TmpSignalConversionAtSFunct[1] - ControlsMFE25_DW->x_pred[0]) *
    2.0 + 0.1;
  v[2] = fabs(rtb_TmpSignalConversionAtSFunct[2] - ControlsMFE25_DW->x_pred[0]) *
    2.0 + 0.1;
  v[3] = fabs(rtb_TmpSignalConversionAtSFunct[3] - ControlsMFE25_DW->x_pred[0]) *
    2.0 + 0.1;

  /* Switch: '<S15>/Switch' incorporates:
   *  Constant: '<S17>/change_threshold'
   *  Delay: '<S15>/Delay1'
   *  Delay: '<S15>/Delay2'
   *  Delay: '<S15>/Delay3'
   *  Delay: '<S15>/Delay4'
   *  MinMax: '<S15>/Max'
   *  MinMax: '<S15>/Min'
   *  RelationalOperator: '<S15>/Relational Operator'
   *  Sum: '<S15>/Subtract'
   */
  if (fmax(fmax(fmax(fmax(ControlsMFE25_DW->Delay4_DSTATE,
                          ControlsMFE25_DW->Delay3_DSTATE[0U]),
                     ControlsMFE25_DW->Delay2_DSTATE[0U]),
                ControlsMFE25_DW->Delay1_DSTATE[0U]),
           ControlsMFE25_U->vehicle_speed) - fmin(fmin(fmin(fmin
         (ControlsMFE25_DW->Delay4_DSTATE, ControlsMFE25_DW->Delay3_DSTATE[0U]),
         ControlsMFE25_DW->Delay2_DSTATE[0U]), ControlsMFE25_DW->Delay1_DSTATE
        [0U]), ControlsMFE25_U->vehicle_speed) <= 0.05) {
    /* MATLAB Function: '<S15>/MATLAB Function2' incorporates:
     *  Constant: '<S17>/r_imu_frozen'
     */
    v[4] = 1.0E+6;
  } else {
    /* MATLAB Function: '<S15>/MATLAB Function2' incorporates:
     *  Constant: '<S17>/r_imu_normal'
     */
    v[4] = 0.05;
  }

  /* End of Switch: '<S15>/Switch' */

  /* MATLAB Function: '<S15>/MATLAB Function2' incorporates:
   *  Constant: '<S15>/Constant8'
   *  Constant: '<S17>/Q'
   *  Delay: '<S15>/Delay1'
   *  Delay: '<S15>/Delay2'
   *  Delay: '<S15>/Delay3'
   *  MinMax: '<S15>/Max'
   *  MinMax: '<S15>/Min'
   */
  v[5] = fabs(ControlsMFE25_U->vy - rtb_TmpSignalConversionAtSFunct[6]) * 0.01;
  v[6] = 0.01;
  memset(&R[0], 0, 49U * sizeof(real_T));
  jj = 0;
  for (k = 0; k < 7; k++) {
    R[jj] = v[k];
    jj += 8;
  }

  for (iy = 0; iy < 14; iy++) {
    A_tmp[iy] = d_0[iy];
    A_tmp_0[iy] = b_a[iy];
  }

  for (iy = 0; iy < 2; iy++) {
    for (k = 0; k < 7; k++) {
      A_tmp_1[k + 7 * iy] = 0.0;
    }

    for (k = 0; k < 2; k++) {
      B1 = ControlsMFE25_DW->P_pred[(iy << 1) + k];
      for (jj = 0; jj < 7; jj++) {
        jp = 7 * iy + jj;
        A_tmp_1[jp] += (real_T)A_tmp_0[7 * k + jj] * B1;
      }
    }
  }

  iy = 0;
  for (k = 0; k < 7; k++) {
    smax = A_tmp_1[k + 7];
    rtb_Saturation_idx_0 = A_tmp_1[k];
    jj = 0;
    b_ix = 0;
    for (jp = 0; jp < 7; jp++) {
      ix = jj + k;
      A[ix] = ((real_T)A_tmp[b_ix + 1] * smax + (real_T)A_tmp[b_ix] *
               rtb_Saturation_idx_0) + R[ix];
      jj += 7;
      b_ix += 2;
    }

    jj = A_tmp[iy];
    smax = ControlsMFE25_DW->P_pred[0] * (real_T)jj;
    rtb_Saturation_idx_0 = ControlsMFE25_DW->P_pred[1] * (real_T)jj;
    jj = A_tmp[iy + 1];
    X[iy] = ControlsMFE25_DW->P_pred[2] * (real_T)jj + smax;
    X[iy + 1] = ControlsMFE25_DW->P_pred[3] * (real_T)jj + rtb_Saturation_idx_0;
    ipiv[k] = (int8_T)(k + 1);
    iy += 2;
  }

  for (k = 0; k < 6; k++) {
    jj = k << 3;
    iy = 8 - k;
    b_ix = 0;
    ix = jj;
    smax = fabs(A[jj]);
    for (jp = 2; jp < iy; jp++) {
      ix++;
      s = fabs(A[ix]);
      if (s > smax) {
        b_ix = jp - 1;
        smax = s;
      }
    }

    if (A[jj + b_ix] != 0.0) {
      if (b_ix != 0) {
        iy = k + b_ix;
        ipiv[k] = (int8_T)(iy + 1);
        for (jp = 0; jp < 7; jp++) {
          b_ix = jp * 7 + k;
          smax = A[b_ix];
          A[b_ix] = A[iy];
          A[iy] = smax;
          iy += 7;
        }
      }

      iy = (jj - k) + 7;
      for (jp = jj + 2; jp <= iy; jp++) {
        A[jp - 1] /= A[jj];
      }
    }

    ix = 5 - k;
    jA = jj + 9;
    for (jp = 0; jp <= ix; jp++) {
      B1 = A[(jp * 7 + jj) + 7];
      if (B1 != 0.0) {
        iy = (jA - k) + 5;
        for (b_ix = jA; b_ix <= iy; b_ix++) {
          A[b_ix - 1] += A[((jj + b_ix) - jA) + 1] * -B1;
        }
      }

      jA += 7;
    }
  }

  for (k = 0; k < 7; k++) {
    jj = k << 1;
    iy = 7 * k;
    for (jp = 0; jp < k; jp++) {
      ix = jp << 1;
      B1 = A[jp + iy];
      if (B1 != 0.0) {
        X[jj] -= B1 * X[ix];
        X[jj + 1] -= X[ix + 1] * B1;
      }
    }

    smax = 1.0 / A[k + iy];
    X[jj] *= smax;
    X[jj + 1] *= smax;
  }

  for (k = 6; k >= 0; k--) {
    iy = k << 1;
    b_ix = 7 * k - 1;
    for (jj = k + 2; jj < 8; jj++) {
      ix = (jj - 1) << 1;
      B1 = A[jj + b_ix];
      if (B1 != 0.0) {
        X[iy] -= B1 * X[ix];
        X[iy + 1] -= X[ix + 1] * B1;
      }
    }
  }

  for (k = 5; k >= 0; k--) {
    ipiv_0 = ipiv[k];
    if (k + 1 != ipiv_0) {
      b_ix = k << 1;
      smax = X[b_ix];
      jj = (ipiv_0 - 1) << 1;
      X[b_ix] = X[jj];
      X[jj] = smax;
      smax = X[b_ix + 1];
      X[b_ix + 1] = X[jj + 1];
      X[jj + 1] = smax;
    }
  }

  smax = ControlsMFE25_DW->x_pred[1];
  rtb_Saturation_idx_0 = ControlsMFE25_DW->x_pred[0];
  for (iy = 0; iy < 7; iy++) {
    v[iy] = rtb_TmpSignalConversionAtSFunct[iy] - ((real_T)A_tmp_0[iy + 7] *
      smax + (real_T)A_tmp_0[iy] * rtb_Saturation_idx_0);
  }

  for (iy = 0; iy < 2; iy++) {
    B1 = 0.0;
    for (k = 0; k < 7; k++) {
      B1 += X[(k << 1) + iy] * v[k];
    }

    rtb_vx_est[iy] = ControlsMFE25_DW->x_pred[iy] + B1;
    for (k = 0; k < 2; k++) {
      B1 = 0.0;
      for (jj = 0; jj < 7; jj++) {
        B1 += X[(jj << 1) + iy] * (real_T)A_tmp_0[7 * k + jj];
      }

      lb[iy + (k << 1)] = 1.0 - B1;
    }

    B1 = lb[iy + 2];
    smax = lb[iy];
    d[iy] = (B1 * ControlsMFE25_DW->P_pred[1] + smax * ControlsMFE25_DW->P_pred
             [0]) + ControlsMFE25_ConstP.Q_Value[iy];
    d[iy + 2] = (B1 * ControlsMFE25_DW->P_pred[3] + smax *
                 ControlsMFE25_DW->P_pred[2]) + ControlsMFE25_ConstP.Q_Value[iy
      + 2];
  }

  ControlsMFE25_DW->x_pred[0] = ControlsMFE25_U->ax * 0.005 + rtb_vx_est[0];
  ControlsMFE25_DW->x_pred[1] = ControlsMFE25_U->ay * 0.005 + rtb_vx_est[1];
  ControlsMFE25_DW->P_pred[0] = d[0];
  ControlsMFE25_DW->P_pred[1] = d[1];
  ControlsMFE25_DW->P_pred[2] = d[2];
  ControlsMFE25_DW->P_pred[3] = d[3];

  /* Switch: '<S1>/Switch' */
  if (ControlsMFE25_U->use_imu_vel_x > 0.0) {
    rtb_Switch = ControlsMFE25_U->vehicle_speed;
  } else {
    rtb_Switch = rtb_vx_est[0];
  }

  /* End of Switch: '<S1>/Switch' */

  /* Switch: '<S8>/Switch' incorporates:
   *  Product: '<S8>/Product3'
   *  Switch: '<S8>/Switch1'
   */
  if ((real_T)(rtb_Switch > 5.0) * ControlsMFE25_U->BRegenEnabledButton > 0.0) {
    /* Lookup_n-D: '<S8>/Pedal Mapping w//Regen' */
    s = look1_pbinlcapw(ControlsMFE25_U->rThrottlePedal,
                        ControlsMFE25_ConstP.PedalMappingwRegen_bp01Data,
                        ControlsMFE25_ConstP.PedalMappingwRegen_tableData,
                        &ControlsMFE25_DW->m_bpIndex_m, 5U);
  } else {
    /* Lookup_n-D: '<S8>/Pedal Mapping w//o Regen' */
    s = look1_pbinlcapw(ControlsMFE25_U->rThrottlePedal,
                        ControlsMFE25_ConstP.PedalMappingwoRegen_bp01Data,
                        ControlsMFE25_ConstP.PedalMappingwoRegen_tableData,
                        &ControlsMFE25_DW->m_bpIndex_g, 3U);
  }

  /* End of Switch: '<S8>/Switch' */

  /* Product: '<S8>/Product' */
  rtb_Product1_c = ControlsMFE25_U->T_i_max * s;

  /* Signum: '<S8>/Sign' */
  if (rtIsNaN(s)) {
    /* Signum: '<S8>/Sign' */
    Sign = (rtNaN);

    /* Switch: '<S8>/Switch3' */
    Switch3 = ControlsMFE25_ConstB.Gain_m;
  } else if (s < 0.0) {
    /* Signum: '<S8>/Sign' */
    Sign = -1.0;

    /* Switch: '<S8>/Switch3' */
    Switch3 = ControlsMFE25_ConstB.Gain_m;
  } else {
    /* Signum: '<S8>/Sign' */
    Sign = (s > 0.0);

    /* Switch: '<S8>/Switch3' */
    Switch3 = rtb_Product1_c;
  }

  /* End of Signum: '<S8>/Sign' */

  /* MATLAB Function: '<S1>/MATLAB Function3' incorporates:
   *  MATLAB Function: '<S11>/MATLAB Function'
   */
  B0 = rtb_Switch * rtb_Switch;
  smax = B0 * 2.7499584000000006;
  s = 250.0 * ControlsMFE25_U->ax * 0.25 / 1.56 / 2.0;
  rtb_Saturation_idx_3 = 250.0 * ControlsMFE25_U->ay * 0.25 / 1.1 / 2.0;
  slip_idx_0 = smax * 0.42 / 2.0;
  slip_idx_1 = 0.101 * ControlsMFE25_U->SWA;
  rtb_Saturation_idx_0 = (((576.3375 - s) - rtb_Saturation_idx_3) + slip_idx_0)
    - slip_idx_1;

  /* Saturate: '<S18>/Saturation' */
  if (rtb_Saturation_idx_0 <= 1.0) {
    rtb_Saturation_idx_0 = 1.0;
  }

  /* MATLAB Function: '<S1>/MATLAB Function3' */
  rtb_Saturation_idx_1 = (((576.3375 - s) + rtb_Saturation_idx_3) + slip_idx_0)
    + slip_idx_1;

  /* Saturate: '<S18>/Saturation' */
  if (rtb_Saturation_idx_1 <= 1.0) {
    rtb_Saturation_idx_1 = 1.0;
  }

  /* MATLAB Function: '<S1>/MATLAB Function3' */
  slip_idx_0 = smax * 0.58000000000000007 / 2.0;
  slip_idx_1 = 0.117 * ControlsMFE25_U->SWA;
  rtb_Saturation_idx_2 = (((s + 649.9125) - rtb_Saturation_idx_3) + slip_idx_0)
    + slip_idx_1;

  /* Saturate: '<S18>/Saturation' */
  if (rtb_Saturation_idx_2 <= 1.0) {
    rtb_Saturation_idx_2 = 1.0;
  }

  /* MATLAB Function: '<S1>/MATLAB Function3' */
  rtb_Saturation_idx_3 = (((s + 649.9125) + rtb_Saturation_idx_3) + slip_idx_0)
    - slip_idx_1;

  /* Saturate: '<S18>/Saturation' */
  if (rtb_Saturation_idx_3 <= 1.0) {
    rtb_Saturation_idx_3 = 1.0;
  }

  /* Switch: '<S1>/Switch2' */
  if (ControlsMFE25_U->use_pushrod_loadcells > 0.0) {
    rtb_Switch2[0] = ControlsMFE25_U->fz_fl;
    rtb_Switch2[1] = ControlsMFE25_U->fz_fr;
    rtb_Switch2[2] = ControlsMFE25_U->fz_rl;
    rtb_Switch2[3] = ControlsMFE25_U->fz_rr;
  } else {
    rtb_Switch2[0] = rtb_Saturation_idx_0;
    rtb_Switch2[1] = rtb_Saturation_idx_1;
    rtb_Switch2[2] = rtb_Saturation_idx_2;
    rtb_Switch2[3] = rtb_Saturation_idx_3;
  }

  /* End of Switch: '<S1>/Switch2' */

  /* Product: '<S1>/Product3' */
  slip_idx_0 = ControlsMFE25_U->Fz_gain * rtb_Switch2[0];
  slip_idx_1 = ControlsMFE25_U->Fz_gain * rtb_Switch2[1];
  slip_idx_2 = ControlsMFE25_U->Fz_gain * rtb_Switch2[2];
  slip_idx_3 = ControlsMFE25_U->Fz_gain * rtb_Switch2[3];

  /* Product: '<S1>/Product5' incorporates:
   *  Constant: '<Root>/Constant4'
   */
  for (jj = 0; jj < 200; jj++) {
    rtb_Product5_i[jj] = ControlsMFE25_ConstP.Constant4_Value[jj] *
      ControlsMFE25_U->slip_ref_scaling;
  }

  /* End of Product: '<S1>/Product5' */

  /* SignalConversion generated from: '<S10>/Transpose1' incorporates:
   *  Constant: '<Root>/Constant5'
   *  Lookup_n-D: '<S10>/1-D Lookup Table'
   */
  rtb_reference_idx_0 = look1_pbinlcapw(slip_idx_0,
    ControlsMFE25_ConstP.Constant5_Value, rtb_Product5_i,
    &ControlsMFE25_DW->m_bpIndex, 199U);

  /* Lookup_n-D: '<S10>/1-D Lookup Table1' incorporates:
   *  Constant: '<Root>/Constant5'
   */
  lty = look1_pbinlcapw(slip_idx_1, ControlsMFE25_ConstP.Constant5_Value,
                        rtb_Product5_i, &ControlsMFE25_DW->m_bpIndex_d, 199U);

  /* Lookup_n-D: '<S10>/1-D Lookup Table2' incorporates:
   *  Constant: '<Root>/Constant5'
   */
  rtb_IProdOut = look1_pbinlcapw(slip_idx_2,
    ControlsMFE25_ConstP.Constant5_Value, rtb_Product5_i,
    &ControlsMFE25_DW->m_bpIndex_h, 199U);

  /* Lookup_n-D: '<S10>/1-D Lookup Table3' incorporates:
   *  Constant: '<Root>/Constant5'
   */
  rtb_Filter_p = look1_pbinlcapw(slip_idx_3,
    ControlsMFE25_ConstP.Constant5_Value, rtb_Product5_i,
    &ControlsMFE25_DW->m_bpIndex_i, 199U);

  /* MinMax: '<S10>/Max' */
  s = fmax(rtb_Switch, ControlsMFE25_U->min_speed);

  /* Product: '<S10>/Product' */
  rtb_reference_idx_3 = rtb_reference_idx_0 * s * Sign;
  rtb_reference_idx_0 = rtb_reference_idx_3;

  /* Product: '<S10>/Divide' incorporates:
   *  Bias: '<S10>/Add Constant4'
   *  Constant: '<Root>/Constant17'
   *  Constant: '<Root>/Constant18'
   *  Constant: '<Root>/Constant19'
   *  Gain: '<S10>/mu4'
   *  Product: '<S10>/Divide1'
   *  Product: '<S10>/Product'
   *  Product: '<S10>/Product1'
   *  Product: '<S10>/Product3'
   *  Product: '<S10>/Product4'
   *  Sum: '<S10>/Add4'
   */
  slip_idx_0 = ((rtb_reference_idx_3 / s + 1.0) * ControlsMFE25_U->ax * 0.45 /
                0.2032 + 1.2 * slip_idx_0 * 0.2032) * Sign / 13.39;

  /* Sum: '<S1>/Sum' incorporates:
   *  Constant: '<Root>/Constant17'
   *  Product: '<S1>/Product'
   */
  rtb_msr_idx_3 = 0.2032 * ControlsMFE25_U->om_fl - rtb_Switch;
  rtb_msr_idx_0 = rtb_msr_idx_3;

  /* Sum: '<S3>/Sum1' incorporates:
   *  Product: '<S10>/Product'
   *  Sum: '<S1>/Sum'
   *  Switch: '<S315>/Switch2'
   */
  rtb_Switch2_p2_idx_0 = rtb_reference_idx_3 - rtb_msr_idx_3;

  /* Product: '<S10>/Product' incorporates:
   *  SignalConversion generated from: '<S10>/Transpose1'
   */
  rtb_reference_idx_3 = lty * s * Sign;
  rtb_reference_idx_1 = rtb_reference_idx_3;

  /* Product: '<S10>/Divide' incorporates:
   *  Bias: '<S10>/Add Constant4'
   *  Constant: '<Root>/Constant17'
   *  Constant: '<Root>/Constant18'
   *  Constant: '<Root>/Constant19'
   *  Gain: '<S10>/mu4'
   *  Product: '<S10>/Divide1'
   *  Product: '<S10>/Product'
   *  Product: '<S10>/Product1'
   *  Product: '<S10>/Product3'
   *  Product: '<S10>/Product4'
   *  Sum: '<S10>/Add4'
   */
  slip_idx_1 = ((rtb_reference_idx_3 / s + 1.0) * ControlsMFE25_U->ax * 0.45 /
                0.2032 + 1.2 * slip_idx_1 * 0.2032) * Sign / 13.39;

  /* Sum: '<S1>/Sum' incorporates:
   *  Constant: '<Root>/Constant17'
   *  Product: '<S1>/Product'
   */
  rtb_msr_idx_3 = 0.2032 * ControlsMFE25_U->om_fr - rtb_Switch;
  rtb_msr_idx_1 = rtb_msr_idx_3;

  /* Sum: '<S3>/Sum1' incorporates:
   *  Product: '<S10>/Product'
   *  Sum: '<S1>/Sum'
   *  Switch: '<S315>/Switch2'
   */
  rtb_Switch2_p2_idx_1 = rtb_reference_idx_3 - rtb_msr_idx_3;

  /* Product: '<S10>/Product' incorporates:
   *  SignalConversion generated from: '<S10>/Transpose1'
   */
  rtb_reference_idx_3 = rtb_IProdOut * s * Sign;
  rtb_reference_idx_2 = rtb_reference_idx_3;

  /* Product: '<S10>/Divide' incorporates:
   *  Bias: '<S10>/Add Constant4'
   *  Constant: '<Root>/Constant17'
   *  Constant: '<Root>/Constant18'
   *  Constant: '<Root>/Constant19'
   *  Gain: '<S10>/mu4'
   *  Product: '<S10>/Divide1'
   *  Product: '<S10>/Product'
   *  Product: '<S10>/Product1'
   *  Product: '<S10>/Product3'
   *  Product: '<S10>/Product4'
   *  Sum: '<S10>/Add4'
   */
  slip_idx_2 = ((rtb_reference_idx_3 / s + 1.0) * ControlsMFE25_U->ax * 0.45 /
                0.2032 + 1.2 * slip_idx_2 * 0.2032) * Sign / 13.39;

  /* Sum: '<S1>/Sum' incorporates:
   *  Constant: '<Root>/Constant17'
   *  Product: '<S1>/Product'
   */
  rtb_msr_idx_3 = 0.2032 * ControlsMFE25_U->om_rl - rtb_Switch;
  rtb_msr_idx_2 = rtb_msr_idx_3;

  /* Sum: '<S3>/Sum1' incorporates:
   *  Product: '<S10>/Product'
   *  Sum: '<S1>/Sum'
   *  Switch: '<S315>/Switch2'
   */
  rtb_Switch2_p2_idx_2 = rtb_reference_idx_3 - rtb_msr_idx_3;

  /* Product: '<S10>/Product' incorporates:
   *  SignalConversion generated from: '<S10>/Transpose1'
   */
  rtb_reference_idx_3 = rtb_Filter_p * s * Sign;

  /* Product: '<S10>/Divide' incorporates:
   *  Bias: '<S10>/Add Constant4'
   *  Constant: '<Root>/Constant17'
   *  Constant: '<Root>/Constant18'
   *  Constant: '<Root>/Constant19'
   *  Gain: '<S10>/mu4'
   *  Product: '<S10>/Divide1'
   *  Product: '<S10>/Product'
   *  Product: '<S10>/Product1'
   *  Product: '<S10>/Product3'
   *  Product: '<S10>/Product4'
   *  Sum: '<S10>/Add4'
   */
  slip_idx_3 = ((rtb_reference_idx_3 / s + 1.0) * ControlsMFE25_U->ax * 0.45 /
                0.2032 + 1.2 * slip_idx_3 * 0.2032) * Sign / 13.39;

  /* Sum: '<S1>/Sum' incorporates:
   *  Constant: '<Root>/Constant17'
   *  Product: '<S1>/Product'
   */
  rtb_msr_idx_3 = 0.2032 * ControlsMFE25_U->om_rr - rtb_Switch;

  /* Sum: '<S3>/Sum1' incorporates:
   *  Product: '<S10>/Product'
   *  Sum: '<S1>/Sum'
   *  Switch: '<S315>/Switch2'
   */
  rtb_Switch2_p2_idx_3 = rtb_reference_idx_3 - rtb_msr_idx_3;

  /* Lookup_n-D: '<S78>/kp' incorporates:
   *  Constant: '<Root>/Constant'
   *  Constant: '<Root>/Constant1'
   *  Switch: '<S1>/Switch'
   */
  s = look1_pbinlcapw(rtb_Switch, ControlsMFE25_ConstP.pooled2,
                      ControlsMFE25_ConstP.pooled3,
                      &ControlsMFE25_DW->m_bpIndex_p, 2U);

  /* Product: '<S125>/PProd Out' */
  lty = rtb_Switch2_p2_idx_0 * s;

  /* Lookup_n-D: '<S78>/kd' incorporates:
   *  Constant: '<Root>/Constant'
   *  Constant: '<Root>/Constant3'
   *  Switch: '<S1>/Switch'
   */
  rtb_IProdOut = look1_pbinlcapw(rtb_Switch, ControlsMFE25_ConstP.pooled2,
    ControlsMFE25_ConstP.Constant3_Value, &ControlsMFE25_DW->m_bpIndex_c, 2U);

  /* DiscreteIntegrator: '<S115>/Filter' */
  if (((ControlsMFE25_U->ResetSignal > 0.0) &&
       (ControlsMFE25_DW->Filter_PrevResetState <= 0)) ||
      ((ControlsMFE25_U->ResetSignal <= 0.0) &&
       (ControlsMFE25_DW->Filter_PrevResetState == 1))) {
    ControlsMFE25_DW->Filter_DSTATE = 0.0;
  }

  /* Product: '<S123>/NProd Out' incorporates:
   *  DiscreteIntegrator: '<S115>/Filter'
   *  Product: '<S113>/DProd Out'
   *  Sum: '<S115>/SumD'
   */
  smax = (rtb_Switch2_p2_idx_0 * rtb_IProdOut - ControlsMFE25_DW->Filter_DSTATE)
    * ControlsMFE25_U->N_long;

  /* Sum: '<S131>/Sum Fdbk' */
  rtb_Filter_p = (lty + ControlsMFE25_DW->Integrator_DSTATE_k) + smax;

  /* Switch: '<S8>/Switch2' */
  if (Sign >= 0.0) {
    /* Switch: '<S8>/Switch2' incorporates:
     *  Constant: '<S8>/lower torque limit'
     */
    Switch2 = -5.0;
  } else {
    /* Switch: '<S8>/Switch2' */
    Switch2 = rtb_Product1_c;
  }

  /* End of Switch: '<S8>/Switch2' */

  /* Switch: '<S112>/Switch' incorporates:
   *  RelationalOperator: '<S112>/u_GTE_up'
   *  RelationalOperator: '<S112>/u_GT_lo'
   *  Switch: '<S112>/Switch1'
   */
  if (rtb_Filter_p >= Switch3) {
    B1 = Switch3;
  } else if (rtb_Filter_p > Switch2) {
    /* Switch: '<S112>/Switch1' */
    B1 = rtb_Filter_p;
  } else {
    B1 = Switch2;
  }

  /* Sum: '<S112>/Diff' incorporates:
   *  Switch: '<S112>/Switch'
   */
  rtb_Product1_c = rtb_Filter_p - B1;

  /* RelationalOperator: '<S109>/Relational Operator' incorporates:
   *  Constant: '<S109>/Clamping_zero'
   */
  rtb_RelationalOperator = (rtb_Product1_c != 0.0);

  /* RelationalOperator: '<S109>/fix for DT propagation issue' incorporates:
   *  Constant: '<S109>/Clamping_zero'
   */
  rtb_fixforDTpropagationissue = (rtb_Product1_c > 0.0);

  /* Lookup_n-D: '<S78>/ki' incorporates:
   *  Constant: '<Root>/Constant'
   *  Constant: '<Root>/Constant2'
   *  Switch: '<S1>/Switch'
   */
  rtb_Product1_c = look1_pbinlcapw(rtb_Switch, ControlsMFE25_ConstP.pooled2,
    ControlsMFE25_ConstP.pooled3, &ControlsMFE25_DW->m_bpIndex_ie, 2U);

  /* Product: '<S117>/IProd Out' */
  rtb_Filter_p = rtb_Switch2_p2_idx_0 * rtb_Product1_c;

  /* Switch: '<S109>/Switch1' incorporates:
   *  Constant: '<S109>/Constant'
   *  Constant: '<S109>/Constant2'
   */
  if (rtb_fixforDTpropagationissue) {
    ipiv_0 = 1;
  } else {
    ipiv_0 = -1;
  }

  /* Switch: '<S109>/Switch2' incorporates:
   *  Constant: '<S109>/Clamping_zero'
   *  Constant: '<S109>/Constant3'
   *  Constant: '<S109>/Constant4'
   *  RelationalOperator: '<S109>/fix for DT propagation issue1'
   */
  if (rtb_Filter_p > 0.0) {
    tmp = 1;
  } else {
    tmp = -1;
  }

  /* Switch: '<S109>/Switch' incorporates:
   *  Constant: '<S109>/Constant1'
   *  Logic: '<S109>/AND3'
   *  RelationalOperator: '<S109>/Equal1'
   *  Switch: '<S109>/Switch1'
   *  Switch: '<S109>/Switch2'
   */
  if (rtb_RelationalOperator && (ipiv_0 == tmp)) {
    rtb_Filter_p = 0.0;
  }

  /* End of Switch: '<S109>/Switch' */

  /* DiscreteIntegrator: '<S120>/Integrator' */
  if (((ControlsMFE25_U->ResetSignal > 0.0) &&
       (ControlsMFE25_DW->Integrator_PrevResetState_n <= 0)) ||
      ((ControlsMFE25_U->ResetSignal <= 0.0) &&
       (ControlsMFE25_DW->Integrator_PrevResetState_n == 1))) {
    ControlsMFE25_DW->Integrator_DSTATE_k = 0.0;
  }

  Integrator_tmp = 0.5 * rtb_Filter_p;

  /* DiscreteIntegrator: '<S120>/Integrator' */
  Integrator = Integrator_tmp + ControlsMFE25_DW->Integrator_DSTATE_k;

  /* Sum: '<S130>/Sum' */
  lty = (lty + Integrator) + smax;

  /* Switch: '<S128>/Switch2' incorporates:
   *  RelationalOperator: '<S128>/LowerRelop1'
   *  RelationalOperator: '<S128>/UpperRelop'
   *  Switch: '<S128>/Switch'
   */
  if (lty > Switch3) {
    lty = Switch3;
  } else if (lty < Switch2) {
    /* Switch: '<S128>/Switch' */
    lty = Switch2;
  }

  /* End of Switch: '<S128>/Switch2' */

  /* Product: '<S181>/PProd Out' */
  rtb_Filter_p = rtb_Switch2_p2_idx_1 * s;

  /* DiscreteIntegrator: '<S171>/Filter' */
  if (((ControlsMFE25_U->ResetSignal > 0.0) &&
       (ControlsMFE25_DW->Filter_PrevResetState_a <= 0)) ||
      ((ControlsMFE25_U->ResetSignal <= 0.0) &&
       (ControlsMFE25_DW->Filter_PrevResetState_a == 1))) {
    ControlsMFE25_DW->Filter_DSTATE_k = 0.0;
  }

  /* Product: '<S179>/NProd Out' incorporates:
   *  DiscreteIntegrator: '<S171>/Filter'
   *  Product: '<S169>/DProd Out'
   *  Sum: '<S171>/SumD'
   */
  rtb_NProdOut_h = (rtb_Switch2_p2_idx_1 * rtb_IProdOut -
                    ControlsMFE25_DW->Filter_DSTATE_k) * ControlsMFE25_U->N_long;

  /* Sum: '<S187>/Sum Fdbk' */
  rtb_Switch2_g = (rtb_Filter_p + ControlsMFE25_DW->Integrator_DSTATE_p) +
    rtb_NProdOut_h;

  /* Switch: '<S168>/Switch' incorporates:
   *  RelationalOperator: '<S168>/u_GTE_up'
   *  RelationalOperator: '<S168>/u_GT_lo'
   *  Switch: '<S168>/Switch1'
   */
  if (rtb_Switch2_g >= Switch3) {
    B1 = Switch3;
  } else if (rtb_Switch2_g > Switch2) {
    /* Switch: '<S168>/Switch1' */
    B1 = rtb_Switch2_g;
  } else {
    B1 = Switch2;
  }

  /* Sum: '<S168>/Diff' incorporates:
   *  Switch: '<S168>/Switch'
   */
  rtb_Switch2_g -= B1;

  /* RelationalOperator: '<S165>/Relational Operator' incorporates:
   *  Constant: '<S165>/Clamping_zero'
   */
  rtb_RelationalOperator = (rtb_Switch2_g != 0.0);

  /* RelationalOperator: '<S165>/fix for DT propagation issue' incorporates:
   *  Constant: '<S165>/Clamping_zero'
   */
  rtb_fixforDTpropagationissue = (rtb_Switch2_g > 0.0);

  /* Product: '<S173>/IProd Out' */
  rtb_Switch2_g = rtb_Switch2_p2_idx_1 * rtb_Product1_c;

  /* Switch: '<S165>/Switch1' incorporates:
   *  Constant: '<S165>/Constant'
   *  Constant: '<S165>/Constant2'
   */
  if (rtb_fixforDTpropagationissue) {
    ipiv_0 = 1;
  } else {
    ipiv_0 = -1;
  }

  /* Switch: '<S165>/Switch2' incorporates:
   *  Constant: '<S165>/Clamping_zero'
   *  Constant: '<S165>/Constant3'
   *  Constant: '<S165>/Constant4'
   *  RelationalOperator: '<S165>/fix for DT propagation issue1'
   */
  if (rtb_Switch2_g > 0.0) {
    tmp = 1;
  } else {
    tmp = -1;
  }

  /* Switch: '<S165>/Switch' incorporates:
   *  Constant: '<S165>/Constant1'
   *  Logic: '<S165>/AND3'
   *  RelationalOperator: '<S165>/Equal1'
   *  Switch: '<S165>/Switch1'
   *  Switch: '<S165>/Switch2'
   */
  if (rtb_RelationalOperator && (ipiv_0 == tmp)) {
    rtb_Switch2_g = 0.0;
  }

  /* End of Switch: '<S165>/Switch' */

  /* DiscreteIntegrator: '<S176>/Integrator' */
  if (((ControlsMFE25_U->ResetSignal > 0.0) &&
       (ControlsMFE25_DW->Integrator_PrevResetState_e <= 0)) ||
      ((ControlsMFE25_U->ResetSignal <= 0.0) &&
       (ControlsMFE25_DW->Integrator_PrevResetState_e == 1))) {
    ControlsMFE25_DW->Integrator_DSTATE_p = 0.0;
  }

  Integrator_n_tmp = 0.5 * rtb_Switch2_g;

  /* DiscreteIntegrator: '<S176>/Integrator' */
  Integrator_n = Integrator_n_tmp + ControlsMFE25_DW->Integrator_DSTATE_p;

  /* Sum: '<S186>/Sum' */
  rtb_Switch2_g = (rtb_Filter_p + Integrator_n) + rtb_NProdOut_h;

  /* Switch: '<S184>/Switch2' incorporates:
   *  RelationalOperator: '<S184>/LowerRelop1'
   *  RelationalOperator: '<S184>/UpperRelop'
   *  Switch: '<S184>/Switch'
   */
  if (rtb_Switch2_g > Switch3) {
    rtb_Switch2_g = Switch3;
  } else if (rtb_Switch2_g < Switch2) {
    /* Switch: '<S184>/Switch' */
    rtb_Switch2_g = Switch2;
  }

  /* End of Switch: '<S184>/Switch2' */

  /* Product: '<S237>/PProd Out' */
  rtb_Filter_p = rtb_Switch2_p2_idx_2 * s;

  /* DiscreteIntegrator: '<S227>/Filter' */
  if (((ControlsMFE25_U->ResetSignal > 0.0) &&
       (ControlsMFE25_DW->Filter_PrevResetState_k <= 0)) ||
      ((ControlsMFE25_U->ResetSignal <= 0.0) &&
       (ControlsMFE25_DW->Filter_PrevResetState_k == 1))) {
    ControlsMFE25_DW->Filter_DSTATE_f = 0.0;
  }

  /* Product: '<S235>/NProd Out' incorporates:
   *  DiscreteIntegrator: '<S227>/Filter'
   *  Product: '<S225>/DProd Out'
   *  Sum: '<S227>/SumD'
   */
  rtb_NProdOut_e = (rtb_Switch2_p2_idx_2 * rtb_IProdOut -
                    ControlsMFE25_DW->Filter_DSTATE_f) * ControlsMFE25_U->N_long;

  /* Sum: '<S243>/Sum Fdbk' */
  rtb_Switch2_nz = (rtb_Filter_p + ControlsMFE25_DW->Integrator_DSTATE_kg) +
    rtb_NProdOut_e;

  /* Switch: '<S224>/Switch' incorporates:
   *  RelationalOperator: '<S224>/u_GTE_up'
   *  RelationalOperator: '<S224>/u_GT_lo'
   *  Switch: '<S224>/Switch1'
   */
  if (rtb_Switch2_nz >= Switch3) {
    B1 = Switch3;
  } else if (rtb_Switch2_nz > Switch2) {
    /* Switch: '<S224>/Switch1' */
    B1 = rtb_Switch2_nz;
  } else {
    B1 = Switch2;
  }

  /* Sum: '<S224>/Diff' incorporates:
   *  Switch: '<S224>/Switch'
   */
  rtb_Switch2_nz -= B1;

  /* RelationalOperator: '<S221>/Relational Operator' incorporates:
   *  Constant: '<S221>/Clamping_zero'
   */
  rtb_RelationalOperator = (rtb_Switch2_nz != 0.0);

  /* RelationalOperator: '<S221>/fix for DT propagation issue' incorporates:
   *  Constant: '<S221>/Clamping_zero'
   */
  rtb_fixforDTpropagationissue = (rtb_Switch2_nz > 0.0);

  /* Product: '<S229>/IProd Out' */
  rtb_Switch2_nz = rtb_Switch2_p2_idx_2 * rtb_Product1_c;

  /* Switch: '<S221>/Switch1' incorporates:
   *  Constant: '<S221>/Constant'
   *  Constant: '<S221>/Constant2'
   */
  if (rtb_fixforDTpropagationissue) {
    ipiv_0 = 1;
  } else {
    ipiv_0 = -1;
  }

  /* Switch: '<S221>/Switch2' incorporates:
   *  Constant: '<S221>/Clamping_zero'
   *  Constant: '<S221>/Constant3'
   *  Constant: '<S221>/Constant4'
   *  RelationalOperator: '<S221>/fix for DT propagation issue1'
   */
  if (rtb_Switch2_nz > 0.0) {
    tmp = 1;
  } else {
    tmp = -1;
  }

  /* Switch: '<S221>/Switch' incorporates:
   *  Constant: '<S221>/Constant1'
   *  Logic: '<S221>/AND3'
   *  RelationalOperator: '<S221>/Equal1'
   *  Switch: '<S221>/Switch1'
   *  Switch: '<S221>/Switch2'
   */
  if (rtb_RelationalOperator && (ipiv_0 == tmp)) {
    rtb_Switch2_nz = 0.0;
  }

  /* End of Switch: '<S221>/Switch' */

  /* DiscreteIntegrator: '<S232>/Integrator' */
  if (((ControlsMFE25_U->ResetSignal > 0.0) &&
       (ControlsMFE25_DW->Integrator_PrevResetState_f <= 0)) ||
      ((ControlsMFE25_U->ResetSignal <= 0.0) &&
       (ControlsMFE25_DW->Integrator_PrevResetState_f == 1))) {
    ControlsMFE25_DW->Integrator_DSTATE_kg = 0.0;
  }

  Integrator_h_tmp = 0.5 * rtb_Switch2_nz;

  /* DiscreteIntegrator: '<S232>/Integrator' */
  Integrator_h = Integrator_h_tmp + ControlsMFE25_DW->Integrator_DSTATE_kg;

  /* Sum: '<S242>/Sum' */
  rtb_Switch2_nz = (rtb_Filter_p + Integrator_h) + rtb_NProdOut_e;

  /* Switch: '<S240>/Switch2' incorporates:
   *  RelationalOperator: '<S240>/LowerRelop1'
   *  RelationalOperator: '<S240>/UpperRelop'
   *  Switch: '<S240>/Switch'
   */
  if (rtb_Switch2_nz > Switch3) {
    rtb_Switch2_nz = Switch3;
  } else if (rtb_Switch2_nz < Switch2) {
    /* Switch: '<S240>/Switch' */
    rtb_Switch2_nz = Switch2;
  }

  /* End of Switch: '<S240>/Switch2' */

  /* Product: '<S293>/PProd Out' */
  s *= rtb_Switch2_p2_idx_3;

  /* Product: '<S281>/DProd Out' */
  rtb_IProdOut *= rtb_Switch2_p2_idx_3;

  /* DiscreteIntegrator: '<S283>/Filter' */
  if (((ControlsMFE25_U->ResetSignal > 0.0) &&
       (ControlsMFE25_DW->Filter_PrevResetState_p <= 0)) ||
      ((ControlsMFE25_U->ResetSignal <= 0.0) &&
       (ControlsMFE25_DW->Filter_PrevResetState_p == 1))) {
    ControlsMFE25_DW->Filter_DSTATE_d = 0.0;
  }

  /* Product: '<S291>/NProd Out' incorporates:
   *  DiscreteIntegrator: '<S283>/Filter'
   *  Sum: '<S283>/SumD'
   */
  rtb_Filter_p = (rtb_IProdOut - ControlsMFE25_DW->Filter_DSTATE_d) *
    ControlsMFE25_U->N_long;

  /* Sum: '<S299>/Sum Fdbk' */
  rtb_SumFdbk_hw = (s + ControlsMFE25_DW->Integrator_DSTATE_o) + rtb_Filter_p;

  /* Switch: '<S280>/Switch' incorporates:
   *  RelationalOperator: '<S280>/u_GTE_up'
   *  RelationalOperator: '<S280>/u_GT_lo'
   *  Switch: '<S280>/Switch1'
   */
  if (rtb_SumFdbk_hw >= Switch3) {
    B1 = Switch3;
  } else if (rtb_SumFdbk_hw > Switch2) {
    /* Switch: '<S280>/Switch1' */
    B1 = rtb_SumFdbk_hw;
  } else {
    B1 = Switch2;
  }

  /* Sum: '<S280>/Diff' incorporates:
   *  Switch: '<S280>/Switch'
   */
  rtb_IProdOut = rtb_SumFdbk_hw - B1;

  /* Product: '<S285>/IProd Out' */
  rtb_Product1_c *= rtb_Switch2_p2_idx_3;

  /* Switch: '<S277>/Switch1' incorporates:
   *  Constant: '<S277>/Clamping_zero'
   *  Constant: '<S277>/Constant'
   *  Constant: '<S277>/Constant2'
   *  RelationalOperator: '<S277>/fix for DT propagation issue'
   */
  if (rtb_IProdOut > 0.0) {
    ipiv_0 = 1;
  } else {
    ipiv_0 = -1;
  }

  /* Switch: '<S277>/Switch2' incorporates:
   *  Constant: '<S277>/Clamping_zero'
   *  Constant: '<S277>/Constant3'
   *  Constant: '<S277>/Constant4'
   *  RelationalOperator: '<S277>/fix for DT propagation issue1'
   */
  if (rtb_Product1_c > 0.0) {
    tmp = 1;
  } else {
    tmp = -1;
  }

  /* Switch: '<S277>/Switch' incorporates:
   *  Constant: '<S277>/Clamping_zero'
   *  Constant: '<S277>/Constant1'
   *  Logic: '<S277>/AND3'
   *  RelationalOperator: '<S277>/Equal1'
   *  RelationalOperator: '<S277>/Relational Operator'
   *  Switch: '<S277>/Switch1'
   *  Switch: '<S277>/Switch2'
   */
  if ((rtb_IProdOut != 0.0) && (ipiv_0 == tmp)) {
    rtb_SumFdbk_hw = 0.0;
  } else {
    rtb_SumFdbk_hw = rtb_Product1_c;
  }

  /* End of Switch: '<S277>/Switch' */

  /* DiscreteIntegrator: '<S288>/Integrator' */
  if (((ControlsMFE25_U->ResetSignal > 0.0) &&
       (ControlsMFE25_DW->Integrator_PrevResetState_m <= 0)) ||
      ((ControlsMFE25_U->ResetSignal <= 0.0) &&
       (ControlsMFE25_DW->Integrator_PrevResetState_m == 1))) {
    ControlsMFE25_DW->Integrator_DSTATE_o = 0.0;
  }

  rtb_SumFdbk_hw *= 0.5;

  /* DiscreteIntegrator: '<S288>/Integrator' */
  Integrator_n2 = rtb_SumFdbk_hw + ControlsMFE25_DW->Integrator_DSTATE_o;

  /* Sum: '<S298>/Sum' */
  s = (s + Integrator_n2) + rtb_Filter_p;

  /* Switch: '<S296>/Switch2' incorporates:
   *  RelationalOperator: '<S296>/LowerRelop1'
   *  RelationalOperator: '<S296>/UpperRelop'
   *  Switch: '<S296>/Switch'
   */
  if (s > Switch3) {
    s = Switch3;
  } else if (s < Switch2) {
    /* Switch: '<S296>/Switch' */
    s = Switch2;
  }

  /* End of Switch: '<S296>/Switch2' */

  /* Sum: '<S1>/Sum1' incorporates:
   *  Product: '<S10>/Divide'
   *  Switch: '<S315>/Switch2'
   */
  rtb_Switch2_p2_idx_0 = slip_idx_0 + lty;
  rtb_Switch2_p2_idx_1 = slip_idx_1 + rtb_Switch2_g;
  rtb_Switch2_p2_idx_2 = slip_idx_2 + rtb_Switch2_nz;
  rtb_Switch2_p2_idx_3 = slip_idx_3 + s;

  /* RelationalOperator: '<S13>/LowerRelop1' incorporates:
   *  Switch: '<S315>/Switch2'
   */
  rtb_LowerRelop1_nk_idx_0 = (rtb_Switch2_p2_idx_0 > Switch3);

  /* Switch: '<S13>/Switch' incorporates:
   *  RelationalOperator: '<S13>/LowerRelop1'
   *  RelationalOperator: '<S13>/UpperRelop'
   *  Switch: '<S315>/Switch2'
   */
  if (rtb_Switch2_p2_idx_0 < Switch2) {
    rtb_Switch2_p2_idx_0_0 = Switch2;
  } else {
    rtb_Switch2_p2_idx_0_0 = rtb_Switch2_p2_idx_0;
  }

  /* RelationalOperator: '<S13>/LowerRelop1' incorporates:
   *  Switch: '<S315>/Switch2'
   */
  rtb_LowerRelop1_nk_idx_1 = (rtb_Switch2_p2_idx_1 > Switch3);

  /* Switch: '<S13>/Switch' incorporates:
   *  RelationalOperator: '<S13>/LowerRelop1'
   *  RelationalOperator: '<S13>/UpperRelop'
   *  Switch: '<S315>/Switch2'
   */
  if (rtb_Switch2_p2_idx_1 < Switch2) {
    rtb_Switch2_p2_idx_1_0 = Switch2;
  } else {
    rtb_Switch2_p2_idx_1_0 = rtb_Switch2_p2_idx_1;
  }

  /* RelationalOperator: '<S13>/LowerRelop1' incorporates:
   *  Switch: '<S315>/Switch2'
   */
  rtb_LowerRelop1_nk_idx_2 = (rtb_Switch2_p2_idx_2 > Switch3);

  /* Switch: '<S13>/Switch' incorporates:
   *  RelationalOperator: '<S13>/LowerRelop1'
   *  RelationalOperator: '<S13>/UpperRelop'
   *  Switch: '<S315>/Switch2'
   */
  if (rtb_Switch2_p2_idx_2 < Switch2) {
    rtb_Switch2_p2_idx_2_0 = Switch2;
  } else {
    rtb_Switch2_p2_idx_2_0 = rtb_Switch2_p2_idx_2;
  }

  /* RelationalOperator: '<S13>/LowerRelop1' incorporates:
   *  Switch: '<S315>/Switch2'
   */
  rtb_LowerRelop1_nk_idx_3 = (rtb_Switch2_p2_idx_3 > Switch3);

  /* Switch: '<S13>/Switch' incorporates:
   *  RelationalOperator: '<S13>/LowerRelop1'
   *  RelationalOperator: '<S13>/UpperRelop'
   *  Switch: '<S315>/Switch2'
   */
  if (rtb_Switch2_p2_idx_3 < Switch2) {
    rtb_Switch2_p2_idx_3_0 = Switch2;
  } else {
    rtb_Switch2_p2_idx_3_0 = rtb_Switch2_p2_idx_3;
  }

  /* Saturate: '<S14>/Saturation' */
  if (rtb_Switch2[0] > 1500.0) {
    B1 = 1500.0;
  } else if (rtb_Switch2[0] < 100.0) {
    B1 = 100.0;
  } else {
    B1 = rtb_Switch2[0];
  }

  /* Lookup_n-D: '<S14>/2-D Lookup Table' incorporates:
   *  Constant: '<Root>/Constant23'
   *  Constant: '<S14>/Constant'
   *  Saturate: '<S14>/Saturation'
   */
  rtb_Product1_c = look2_binlxpw(B1, 0.0, ControlsMFE25_ConstP.pooled16,
    ControlsMFE25_ConstP.pooled17, ControlsMFE25_ConstP.Constant23_Value,
    ControlsMFE25_ConstP.pooled18, 19U);

  /* Saturate: '<S14>/Saturation' */
  if (rtb_Switch2[1] > 1500.0) {
    B1 = 1500.0;
  } else if (rtb_Switch2[1] < 100.0) {
    B1 = 100.0;
  } else {
    B1 = rtb_Switch2[1];
  }

  /* Lookup_n-D: '<S14>/2-D Lookup Table1' incorporates:
   *  Constant: '<Root>/Constant23'
   *  Constant: '<S14>/Constant'
   *  Saturate: '<S14>/Saturation'
   */
  rtb_IProdOut = look2_binlxpw(B1, 0.0, ControlsMFE25_ConstP.pooled16,
    ControlsMFE25_ConstP.pooled17, ControlsMFE25_ConstP.Constant23_Value,
    ControlsMFE25_ConstP.pooled18, 19U);

  /* Gain: '<S14>/Gain' incorporates:
   *  Sum: '<S14>/Add'
   */
  rtb_CyAlphaF = (rtb_Product1_c + rtb_IProdOut) * 0.5;

  /* Saturate: '<S14>/Saturation' */
  if (rtb_Switch2[2] > 1500.0) {
    B1 = 1500.0;
  } else if (rtb_Switch2[2] < 100.0) {
    B1 = 100.0;
  } else {
    B1 = rtb_Switch2[2];
  }

  /* Lookup_n-D: '<S14>/2-D Lookup Table2' incorporates:
   *  Constant: '<Root>/Constant23'
   *  Constant: '<S14>/Constant'
   *  Saturate: '<S14>/Saturation'
   */
  rtb_Product1_c = look2_binlxpw(B1, 0.0, ControlsMFE25_ConstP.pooled16,
    ControlsMFE25_ConstP.pooled17, ControlsMFE25_ConstP.Constant23_Value,
    ControlsMFE25_ConstP.pooled18, 19U);

  /* Saturate: '<S14>/Saturation' */
  if (rtb_Switch2[3] > 1500.0) {
    B1 = 1500.0;
  } else if (rtb_Switch2[3] < 100.0) {
    B1 = 100.0;
  } else {
    B1 = rtb_Switch2[3];
  }

  /* Lookup_n-D: '<S14>/2-D Lookup Table3' incorporates:
   *  Constant: '<Root>/Constant23'
   *  Constant: '<S14>/Constant'
   *  Saturate: '<S14>/Saturation'
   */
  rtb_IProdOut = look2_binlxpw(B1, 0.0, ControlsMFE25_ConstP.pooled16,
    ControlsMFE25_ConstP.pooled17, ControlsMFE25_ConstP.Constant23_Value,
    ControlsMFE25_ConstP.pooled18, 19U);

  /* Gain: '<S14>/Gain1' incorporates:
   *  Sum: '<S14>/Add1'
   */
  rtb_Product1_c = (rtb_Product1_c + rtb_IProdOut) * 0.5;

  /* Switch: '<S1>/Switch1' */
  if (ControlsMFE25_U->use_imu_vel_y > 0.0) {
    rtb_Switch1 = ControlsMFE25_U->vy;
  } else {
    rtb_Switch1 = rtb_vx_est[1];
  }

  /* End of Switch: '<S1>/Switch1' */

  /* MATLAB Function: '<S11>/MATLAB Function' incorporates:
   *  Constant: '<Root>/Constant10'
   *  Constant: '<Root>/Constant11'
   *  Constant: '<Root>/Constant12'
   *  Constant: '<Root>/Constant13'
   */
  rtb_IProdOut = sqrt(rtb_Switch1 * rtb_Switch1 + B0);
  B0 = rtb_CyAlphaF * rtb_Product1_c;
  K_ratio = fmax(1.0E-8, (0.854 * rtb_CyAlphaF - 0.67099999999999993 *
    rtb_Product1_c) * -58.693899489384584 / B0 * rtb_IProdOut + 1.0);
  B1 = sqrt(rtb_IProdOut);
  w_n = sqrt(B0 / 16380.0) * (3.05 / B1) * sqrt(K_ratio);
  rtb_Switch2_p2_idx_1 = 1.5 * w_n;
  rtb_Switch2_p2_idx_0 = B1 / 1.525 / K_ratio;
  rtb_Switch2_p2_idx_3 = rtb_Switch2_p2_idx_1 * rtb_Switch2_p2_idx_1;
  rtb_IProdOut = 1.0 / rtb_Switch2_p2_idx_3;
  B0 = rtb_Switch2_p2_idx_0 / rtb_IProdOut;
  B1 = 233.142 * B1 / (3.05 * rtb_Product1_c) * rtb_Switch2_p2_idx_0 /
    rtb_IProdOut;
  rtb_Switch2_p2_idx_0 = 1.0 / rtb_IProdOut;
  rtb_Product1_c = ((0.729316 * rtb_CyAlphaF + 0.45024099999999989 *
                     rtb_Product1_c) * 273.0 + (rtb_CyAlphaF + rtb_Product1_c) *
                    60.0) / (sqrt(16380.0 * rtb_CyAlphaF * rtb_Product1_c *
    K_ratio) * 3.05) * 2.0 / rtb_Switch2_p2_idx_1 / rtb_IProdOut;
  rtb_IProdOut /= rtb_IProdOut;
  K_ratio = rtb_IProdOut * 160000.0;
  rtb_Switch2_p2_idx_1 = rtb_Product1_c * 400.0;
  rtb_Switch2_p2_idx_2 = (K_ratio + rtb_Switch2_p2_idx_1) + rtb_Switch2_p2_idx_0;
  wheelbase_tmp = B1 * 400.0;

  /* Outputs for Atomic SubSystem: '<S11>/Subsystem' */
  /* Sum: '<S317>/Sum1' incorporates:
   *  DiscreteIntegrator: '<S313>/Integrator'
   *  MATLAB Function: '<S11>/MATLAB Function'
   *  Product: '<S317>/Product1'
   *  UnitDelay: '<S317>/Delay1'
   */
  B1 = (wheelbase_tmp + B0) / rtb_Switch2_p2_idx_2 *
    ControlsMFE25_DW->Integrator_DSTATE + ControlsMFE25_DW->Delay1_DSTATE_p;

  /* Switch: '<S317>/Switch' incorporates:
   *  RelationalOperator: '<S317>/IsNaN'
   *  UnitDelay: '<S317>/Delay3'
   */
  if (rtIsNaN(B1)) {
    rtb_Product1_c = ControlsMFE25_DW->Delay3_DSTATE_c;
  } else {
    rtb_Product1_c = B1;
  }

  /* End of Switch: '<S317>/Switch' */

  /* Update for UnitDelay: '<S317>/Delay1' incorporates:
   *  DiscreteIntegrator: '<S313>/Integrator'
   *  MATLAB Function: '<S11>/MATLAB Function'
   *  Product: '<S317>/Product2'
   *  Product: '<S317>/Product3'
   *  Sum: '<S317>/Sum2'
   *  UnitDelay: '<S317>/Delay2'
   */
  ControlsMFE25_DW->Delay1_DSTATE_p = (2.0 * B0 / rtb_Switch2_p2_idx_2 *
    ControlsMFE25_DW->Integrator_DSTATE + ControlsMFE25_DW->Delay2_DSTATE_e) - (
    -2.0 * rtb_IProdOut * 160000.0 + 2.0 * rtb_Switch2_p2_idx_0) /
    rtb_Switch2_p2_idx_2 * rtb_Product1_c;

  /* Update for UnitDelay: '<S317>/Delay3' */
  ControlsMFE25_DW->Delay3_DSTATE_c = rtb_Product1_c;

  /* Update for UnitDelay: '<S317>/Delay2' incorporates:
   *  DiscreteIntegrator: '<S313>/Integrator'
   *  MATLAB Function: '<S11>/MATLAB Function'
   *  Product: '<S317>/Product4'
   *  Product: '<S317>/Product5'
   *  Sum: '<S317>/Sum3'
   */
  ControlsMFE25_DW->Delay2_DSTATE_e = (B0 - wheelbase_tmp) /
    rtb_Switch2_p2_idx_2 * ControlsMFE25_DW->Integrator_DSTATE - ((K_ratio -
    rtb_Switch2_p2_idx_1) + rtb_Switch2_p2_idx_0) / rtb_Switch2_p2_idx_2 *
    rtb_Product1_c;

  /* End of Outputs for SubSystem: '<S11>/Subsystem' */

  /* Product: '<S11>/Product1' */
  rtb_Product1_c *= ControlsMFE25_U->yrr_scaling;

  /* Sum: '<S2>/Sum1' incorporates:
   *  MATLAB Function: '<S1>/MATLAB Function2'
   */
  rtb_IProdOut = rtb_Product1_c - rtb_Product_j;

  /* Lookup_n-D: '<S20>/kp' incorporates:
   *  Constant: '<Root>/Constant6'
   *  Constant: '<Root>/Constant7'
   *  Switch: '<S1>/Switch'
   */
  rtb_Product_j = look1_pbinlcapw(rtb_Switch, ControlsMFE25_ConstP.pooled2,
    ControlsMFE25_ConstP.Constant7_Value, &ControlsMFE25_DW->m_bpIndex_e, 2U);

  /* Product: '<S63>/PProd Out' */
  rtb_Product_j *= rtb_IProdOut;

  /* Lookup_n-D: '<S20>/kd' incorporates:
   *  Constant: '<Root>/Constant6'
   *  Constant: '<Root>/Constant9'
   *  Switch: '<S1>/Switch'
   */
  B1 = look1_pbinlcapw(rtb_Switch, ControlsMFE25_ConstP.pooled2,
                       ControlsMFE25_ConstP.Constant9_Value,
                       &ControlsMFE25_DW->m_bpIndex_im, 2U);

  /* DiscreteIntegrator: '<S53>/Filter' */
  if (((ControlsMFE25_U->ResetSignal > 0.0) &&
       (ControlsMFE25_DW->Filter_PrevResetState_ag <= 0)) ||
      ((ControlsMFE25_U->ResetSignal <= 0.0) &&
       (ControlsMFE25_DW->Filter_PrevResetState_ag == 1))) {
    ControlsMFE25_DW->Filter_DSTATE_c = 0.0;
  }

  /* Product: '<S61>/NProd Out' incorporates:
   *  DiscreteIntegrator: '<S53>/Filter'
   *  Product: '<S51>/DProd Out'
   *  Sum: '<S53>/SumD'
   */
  K_ratio = rtb_IProdOut * B1 - ControlsMFE25_DW->Filter_DSTATE_c;

  /* Sum: '<S69>/Sum Fdbk' */
  B0 = (rtb_Product_j + ControlsMFE25_DW->Integrator_DSTATE_a) + K_ratio;

  /* Switch: '<S50>/Switch' incorporates:
   *  Constant: '<Root>/Constant16'
   *  RelationalOperator: '<S50>/u_GTE_up'
   *  RelationalOperator: '<S50>/u_GT_lo'
   *  Switch: '<S50>/Switch1'
   */
  if (B0 >= 5000.0) {
    B1 = 5000.0;
  } else if (B0 > ControlsMFE25_ConstB.Gain) {
    /* Switch: '<S50>/Switch1' */
    B1 = B0;
  } else {
    B1 = ControlsMFE25_ConstB.Gain;
  }

  /* Sum: '<S50>/Diff' incorporates:
   *  Switch: '<S50>/Switch'
   */
  B1 = B0 - B1;

  /* RelationalOperator: '<S47>/Relational Operator' incorporates:
   *  Constant: '<S47>/Clamping_zero'
   */
  rtb_RelationalOperator = (B1 != 0.0);

  /* RelationalOperator: '<S47>/fix for DT propagation issue' incorporates:
   *  Constant: '<S47>/Clamping_zero'
   */
  rtb_fixforDTpropagationissue = (B1 > 0.0);

  /* Lookup_n-D: '<S20>/ki' incorporates:
   *  Constant: '<Root>/Constant6'
   *  Constant: '<Root>/Constant8'
   *  Switch: '<S1>/Switch'
   */
  B1 = look1_pbinlcapw(rtb_Switch, ControlsMFE25_ConstP.pooled2,
                       ControlsMFE25_ConstP.Constant8_Value,
                       &ControlsMFE25_DW->m_bpIndex_o, 2U);

  /* Product: '<S55>/IProd Out' */
  rtb_IProdOut *= B1;

  /* Switch: '<S47>/Switch1' incorporates:
   *  Constant: '<S47>/Constant'
   *  Constant: '<S47>/Constant2'
   */
  if (rtb_fixforDTpropagationissue) {
    ipiv_0 = 1;
  } else {
    ipiv_0 = -1;
  }

  /* Switch: '<S47>/Switch2' incorporates:
   *  Constant: '<S47>/Clamping_zero'
   *  Constant: '<S47>/Constant3'
   *  Constant: '<S47>/Constant4'
   *  RelationalOperator: '<S47>/fix for DT propagation issue1'
   */
  if (rtb_IProdOut > 0.0) {
    tmp = 1;
  } else {
    tmp = -1;
  }

  /* Switch: '<S47>/Switch' incorporates:
   *  Constant: '<S47>/Constant1'
   *  Logic: '<S47>/AND3'
   *  RelationalOperator: '<S47>/Equal1'
   *  Switch: '<S47>/Switch1'
   *  Switch: '<S47>/Switch2'
   */
  if (rtb_RelationalOperator && (ipiv_0 == tmp)) {
    rtb_IProdOut = 0.0;
  }

  /* End of Switch: '<S47>/Switch' */

  /* DiscreteIntegrator: '<S58>/Integrator' */
  if (((ControlsMFE25_U->ResetSignal > 0.0) &&
       (ControlsMFE25_DW->Integrator_PrevResetState_nn <= 0)) ||
      ((ControlsMFE25_U->ResetSignal <= 0.0) &&
       (ControlsMFE25_DW->Integrator_PrevResetState_nn == 1))) {
    ControlsMFE25_DW->Integrator_DSTATE_a = 0.0;
  }

  rtb_IProdOut *= 0.5;

  /* DiscreteIntegrator: '<S58>/Integrator' */
  B0 = rtb_IProdOut + ControlsMFE25_DW->Integrator_DSTATE_a;

  /* Sum: '<S68>/Sum' */
  rtb_Product_j = (rtb_Product_j + B0) + K_ratio;

  /* Switch: '<S66>/Switch2' incorporates:
   *  Constant: '<Root>/Constant16'
   *  RelationalOperator: '<S66>/LowerRelop1'
   *  RelationalOperator: '<S66>/UpperRelop'
   *  Switch: '<S66>/Switch'
   */
  if (rtb_Product_j > 5000.0) {
    B1 = 5000.0;
  } else if (rtb_Product_j < ControlsMFE25_ConstB.Gain) {
    /* Switch: '<S66>/Switch' */
    B1 = ControlsMFE25_ConstB.Gain;
  } else {
    B1 = rtb_Product_j;
  }

  /* End of Switch: '<S66>/Switch2' */

  /* Product: '<S11>/Product' incorporates:
   *  Constant: '<Root>/Constant11'
   *  DiscreteIntegrator: '<S313>/Integrator'
   *  MATLAB Function: '<S11>/MATLAB Function'
   */
  rtb_Product_j = (rtb_Switch2_p2_idx_3 / (w_n * w_n) - 1.0) * (1.708 *
    rtb_CyAlphaF) * ControlsMFE25_DW->Integrator_DSTATE;

  /* Sum: '<S1>/Sum2' */
  rtb_CyAlphaF = B1 + rtb_Product_j;

  /* Switch: '<S12>/Switch2' incorporates:
   *  Constant: '<Root>/Constant16'
   *  RelationalOperator: '<S12>/LowerRelop1'
   *  RelationalOperator: '<S12>/UpperRelop'
   *  Switch: '<S12>/Switch'
   */
  if (rtb_CyAlphaF > 5000.0) {
    /* Outport: '<Root>/Mz_Target' */
    ControlsMFE25_Y->Mz_Target = 5000.0;
  } else if (rtb_CyAlphaF < ControlsMFE25_ConstB.Gain_n) {
    /* Switch: '<S12>/Switch' incorporates:
     *  Outport: '<Root>/Mz_Target'
     */
    ControlsMFE25_Y->Mz_Target = ControlsMFE25_ConstB.Gain_n;
  } else {
    /* Outport: '<Root>/Mz_Target' incorporates:
     *  Switch: '<S12>/Switch'
     */
    ControlsMFE25_Y->Mz_Target = rtb_CyAlphaF;
  }

  /* End of Switch: '<S12>/Switch2' */

  /* Product: '<S1>/Divide' incorporates:
   *  Sum: '<S1>/Sum'
   */
  rtb_Switch2_p2_idx_3 = rtb_msr_idx_0 / rtb_Switch;
  rtb_Switch2_p2_idx_0 = rtb_Switch2_p2_idx_3;

  /* MATLAB Function: '<S7>/Torque Allocation QP Normalized' incorporates:
   *  Product: '<S1>/Divide'
   */
  x[0] = rtIsInf(rtb_Switch2_p2_idx_3);

  /* Product: '<S1>/Divide' incorporates:
   *  Sum: '<S1>/Sum'
   */
  rtb_Switch2_p2_idx_3 = rtb_msr_idx_1 / rtb_Switch;
  rtb_Switch2_p2_idx_1 = rtb_Switch2_p2_idx_3;

  /* MATLAB Function: '<S7>/Torque Allocation QP Normalized' incorporates:
   *  Product: '<S1>/Divide'
   */
  x[1] = rtIsInf(rtb_Switch2_p2_idx_3);

  /* Product: '<S1>/Divide' incorporates:
   *  Sum: '<S1>/Sum'
   */
  rtb_Switch2_p2_idx_3 = rtb_msr_idx_2 / rtb_Switch;
  rtb_Switch2_p2_idx_2 = rtb_Switch2_p2_idx_3;

  /* MATLAB Function: '<S7>/Torque Allocation QP Normalized' incorporates:
   *  Product: '<S1>/Divide'
   */
  x[2] = rtIsInf(rtb_Switch2_p2_idx_3);

  /* Product: '<S1>/Divide' incorporates:
   *  Sum: '<S1>/Sum'
   */
  rtb_Switch2_p2_idx_3 = rtb_msr_idx_3 / rtb_Switch;

  /* MATLAB Function: '<S7>/Torque Allocation QP Normalized' incorporates:
   *  Product: '<S1>/Divide'
   */
  x[3] = rtIsInf(rtb_Switch2_p2_idx_3);

  /* Trigonometry: '<S1>/Atan2' */
  rtb_Switch = rt_atan2d_snf(rtb_Switch1, rtb_Switch);

  /* MATLAB Function: '<S7>/Torque Allocation QP Normalized' incorporates:
   *  Constant: '<Root>/Constant11'
   *  Constant: '<Root>/Constant17'
   *  Constant: '<Root>/Constant18'
   *  Constant: '<Root>/Constant20'
   *  Delay: '<S7>/Delay One Step'
   *  Product: '<S7>/Product'
   *  Product: '<S7>/Product1'
   *  Switch: '<S16>/Switch'
   */
  rtb_Switch1 = ControlsMFE25_Y->Mz_Target;
  rtb_RelationalOperator = true;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 4)) {
    if (!x[k]) {
      rtb_RelationalOperator = false;
      exitg1 = true;
    } else {
      k++;
    }
  }

  if (rtb_RelationalOperator) {
    rtb_Switch2_p2_idx_0 = 0.0;
    rtb_Switch2_p2_idx_1 = 0.0;
    rtb_Switch2_p2_idx_2 = 0.0;
    rtb_Switch2_p2_idx_3 = 0.0;
  }

  rtb_CyAlphaF = ((rtb_Switch2[0] + rtb_Switch2[1]) + rtb_Switch2[2]) +
    rtb_Switch2[3];
  w_n = rtb_Switch2[0];
  if (rtb_Switch2[0] < 0.0) {
    w_n = 1.0;
  }

  rtb_Switch2[0] = sqrt(w_n / rtb_CyAlphaF);
  w_n = rtb_Switch2[1];
  if (rtb_Switch2[1] < 0.0) {
    w_n = 1.0;
  }

  rtb_Switch2[1] = sqrt(w_n / rtb_CyAlphaF);
  w_n = rtb_Switch2[2];
  if (rtb_Switch2[2] < 0.0) {
    w_n = 1.0;
  }

  rtb_Switch2[2] = sqrt(w_n / rtb_CyAlphaF);
  w_n = rtb_Switch2[3];
  if (rtb_Switch2[3] < 0.0) {
    w_n = 1.0;
  }

  memset(&A_0[0], 0, sizeof(real_T) << 4U);
  A_0[0] = rtb_Switch2[0];
  A_0[5] = rtb_Switch2[1];
  A_0[10] = rtb_Switch2[2];
  A_0[15] = sqrt(w_n / rtb_CyAlphaF);
  if (rtIsNaN(ControlsMFE25_Y->Mz_Target)) {
    rtb_Switch1 = 0.0;
  }

  rtb_CyAlphaF = Switch3 / 21.0;
  w_n = Switch2 / 21.0;
  rtb_Switch1 = rtb_Switch1 / 75.780019685039377 / 21.0;
  Switch2 = cos(ControlsMFE25_Y->wheelA);
  x0[0] = ControlsMFE25_DW->DelayOneStep_DSTATE[0] / 21.0;
  wheelbase_tmp = sin(ControlsMFE25_Y->wheelA) * 0.854;
  d[0] = (-Switch2 * 1.15 / 2.0 + wheelbase_tmp) * 65.895669291338592 * fmax(0.0,
    1.0 - rtb_Switch2_p2_idx_0) / 75.780019685039377;
  rtb_Switch2_p2_idx_0 = ControlsMFE25_U->om_fl * 13.39;
  x0[1] = ControlsMFE25_DW->DelayOneStep_DSTATE[1] / 21.0;
  d[1] = (Switch2 * 1.15 / 2.0 + wheelbase_tmp) * 65.895669291338592 * fmax(0.0,
    1.0 - rtb_Switch2_p2_idx_1) / 75.780019685039377;
  rtb_Switch2_p2_idx_1 = ControlsMFE25_U->om_fr * 13.39;
  x0[2] = ControlsMFE25_DW->DelayOneStep_DSTATE[2] / 21.0;
  d[2] = fmax(0.0, 1.0 - rtb_Switch2_p2_idx_2) * -37.890009842519689 /
    75.780019685039377;
  rtb_Switch2_p2_idx_2 = ControlsMFE25_U->om_rl * 13.39;
  x0[3] = ControlsMFE25_DW->DelayOneStep_DSTATE[3] / 21.0;
  d[3] = fmax(0.0, 1.0 - rtb_Switch2_p2_idx_3) * 37.890009842519689 /
    75.780019685039377;
  rtb_Switch2_p2_idx_3 = ControlsMFE25_U->om_rr * 13.39;
  Switch2 = 0.0;
  if (Sign == 1.0) {
    Switch2 = ControlsMFE25_U->P_max * ControlsMFE25_U->efficiency;
    rtb_Switch2_p2_idx_0 *= 21.0;
    rtb_Switch2_p2_idx_1 *= 21.0;
    rtb_Switch2_p2_idx_2 *= 21.0;
    rtb_Switch2_p2_idx_3 *= 21.0;
  } else if (Sign == 0.0) {
    rtb_Switch2_p2_idx_0 *= 21.0;
    rtb_Switch2_p2_idx_1 *= 21.0;
    rtb_Switch2_p2_idx_2 *= 21.0;
    rtb_Switch2_p2_idx_3 *= 21.0;
  } else if (Sign == -1.0) {
    Switch2 = ControlsMFE25_U->efficiency * ControlsMFE25_U->R_max;
    rtb_Switch2_p2_idx_0 = -ControlsMFE25_U->om_fl * 13.39 * 21.0;
    rtb_Switch2_p2_idx_1 = -ControlsMFE25_U->om_fr * 13.39 * 21.0;
    rtb_Switch2_p2_idx_2 = -ControlsMFE25_U->om_rl * 13.39 * 21.0;
    rtb_Switch2_p2_idx_3 = -ControlsMFE25_U->om_rr * 13.39 * 21.0;
  }

  Sign = rtb_Switch * rtb_Switch * ControlsMFE25_U->lamda2;
  jj = 0;
  for (jp = 0; jp < 4; jp++) {
    rtb_Switch2[jp] = rtb_CyAlphaF;
    lb[jp] = w_n;
    iy = 0;
    for (k = 0; k < 4; k++) {
      A_1[k + jj] = ((A_0[iy + 1] * A_0[jj + 1] + A_0[iy] * A_0[jj]) + A_0[iy +
                     2] * A_0[jj + 2]) + A_0[iy + 3] * A_0[jj + 3];
      iy += 4;
    }

    jj += 4;
  }

  for (iy = 0; iy < 16; iy++) {
    H_tmp[iy] = ControlsMFE25_U->lamda1 * A_1[iy];
  }

  iy = 0;
  for (k = 0; k < 4; k++) {
    A_1[iy] = d[0] * d[k];
    A_1[iy + 1] = d[1] * d[k];
    A_1[iy + 2] = d[2] * d[k];
    A_1[iy + 3] = d[3] * d[k];
    iy += 4;
  }

  for (iy = 0; iy < 16; iy++) {
    A_0[iy] = ((Sign * A_1[iy] + H_tmp[iy]) + ControlsMFE25_U->lamda3 * (real_T)
               c_b[iy]) * 2.0;
  }

  Sign *= rtb_Switch1;

  /* Switch: '<S13>/Switch2' incorporates:
   *  RelationalOperator: '<S13>/LowerRelop1'
   */
  if (rtb_LowerRelop1_nk_idx_0) {
    rtb_Switch2_p2_idx_0_0 = Switch3;
  }

  /* MATLAB Function: '<S7>/Torque Allocation QP Normalized' incorporates:
   *  Switch: '<S13>/Switch2'
   */
  rtb_Switch = rtb_Switch2_p2_idx_0_0 / 21.0;

  /* Switch: '<S13>/Switch2' incorporates:
   *  RelationalOperator: '<S13>/LowerRelop1'
   */
  if (rtb_LowerRelop1_nk_idx_1) {
    rtb_Switch2_p2_idx_1_0 = Switch3;
  }

  /* MATLAB Function: '<S7>/Torque Allocation QP Normalized' incorporates:
   *  Switch: '<S13>/Switch2'
   */
  rtb_Switch2_p2_idx_1_0 /= 21.0;

  /* Switch: '<S13>/Switch2' incorporates:
   *  RelationalOperator: '<S13>/LowerRelop1'
   */
  if (rtb_LowerRelop1_nk_idx_2) {
    rtb_Switch2_p2_idx_2_0 = Switch3;
  }

  /* MATLAB Function: '<S7>/Torque Allocation QP Normalized' incorporates:
   *  Switch: '<S13>/Switch2'
   */
  rtb_Switch2_p2_idx_2_0 /= 21.0;

  /* Switch: '<S13>/Switch2' incorporates:
   *  RelationalOperator: '<S13>/LowerRelop1'
   */
  if (rtb_LowerRelop1_nk_idx_3) {
    rtb_Switch2_p2_idx_3_0 = Switch3;
  }

  /* MATLAB Function: '<S7>/Torque Allocation QP Normalized' incorporates:
   *  Switch: '<S13>/Switch2'
   */
  Switch3 = rtb_Switch2_p2_idx_3_0 / 21.0;
  for (iy = 0; iy < 4; iy++) {
    f[iy] = (((((H_tmp[iy + 4] * rtb_Switch2_p2_idx_1_0 + H_tmp[iy] * rtb_Switch)
                + H_tmp[iy + 8] * rtb_Switch2_p2_idx_2_0) + H_tmp[iy + 12] *
               Switch3) + Sign * d[iy]) + ControlsMFE25_U->lamda3 * x0[iy]) *
      -2.0;
  }

  ControlsMFE25_tic(&savedTime, ControlsMFE25_DW);
  Switch3 = (rtInf);
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 4)) {
    if (lb[k] > rtb_Switch2[k]) {
      Switch3 = -2.0;
      exitg1 = true;
    } else {
      k++;
    }
  }

  if (Switch3 == -2.0) {
    rtb_Switch2_p2_idx_0 = x0[0];
    rtb_Switch2_p2_idx_1 = x0[1];
    rtb_Switch2_p2_idx_2 = x0[2];
    rtb_Switch2_p2_idx_3 = x0[3];
  } else {
    solution.fstar = 0.0;
    solution.firstorderopt = 0.0;
    memset(&solution.lambda[0], 0, 10U * sizeof(real_T));
    solution.state = 0;
    solution.maxConstr = 0.0;
    solution.iterations = 0;
    solution.xstar[0] = x0[0];
    solution.xstar[1] = x0[1];
    solution.xstar[2] = x0[2];
    solution.xstar[3] = x0[3];
    CholRegManager.ndims = 0;
    CholRegManager.info = 0;
    CholRegManager.ConvexCheck = true;
    CholRegManager.regTol_ = 0.0;
    WorkingSet.nVar = 4;
    WorkingSet.nVarOrig = 4;
    WorkingSet.nVarMax = 5;
    WorkingSet.ldA = 5;
    for (jj = 0; jj < 5; jj++) {
      solution.searchDir[jj] = 0.0;
      WorkingSet.Aineq[jj] = 0.0;
      WorkingSet.lb[jj] = 0.0;
      WorkingSet.ub[jj] = 0.0;
    }

    WorkingSet.mEqRemoved = 0;
    memset(&WorkingSet.ATwset[0], 0, 50U * sizeof(real_T));
    WorkingSet.nActiveConstr = 0;
    memset(&WorkingSet.bwset[0], 0, 10U * sizeof(real_T));
    memset(&WorkingSet.maxConstrWorkspace[0], 0, 10U * sizeof(real_T));
    for (jj = 0; jj < 10; jj++) {
      WorkingSet.isActiveConstr[jj] = false;
      WorkingSet.Wid[jj] = 0;
      WorkingSet.Wlocalidx[jj] = 0;
    }

    WorkingSet.probType = 3;
    WorkingSet.SLACK0 = 1.0E-5;
    for (jj = 0; jj < 5; jj++) {
      WorkingSet.nWConstr[jj] = 0;
      WorkingSet.indexLB[jj] = 0;
      WorkingSet.indexUB[jj] = 0;
      WorkingSet.indexFixed[jj] = 0;
    }

    k = 1;
    jj = 0;
    jp = 0;
    for (iy = 0; iy < 4; iy++) {
      Sign = lb[iy];
      guard1 = false;
      if ((!rtIsInf(Sign)) && (!rtIsNaN(Sign))) {
        if (fabs(Sign - rtb_Switch2[iy]) < 1.0E-8) {
          jp++;
          WorkingSet.indexFixed[jp - 1] = iy + 1;
        } else {
          k++;
          WorkingSet.indexLB[k - 2] = iy + 1;
          guard1 = true;
        }
      } else {
        guard1 = true;
      }

      if (guard1) {
        w_n = rtb_Switch2[iy];
        if ((!rtIsInf(w_n)) && (!rtIsNaN(w_n))) {
          jj++;
          WorkingSet.indexUB[jj - 1] = iy + 1;
        }
      }
    }

    WorkingSet.bineq = Switch2;
    iy = (k + jj) + jp;
    WorkingSet.mConstr = iy;
    WorkingSet.mConstrOrig = iy;
    WorkingSet.mConstrMax = 10;
    WorkingSet.sizesPhaseOne[0] = jp;
    WorkingSet.sizesPhaseOne[1] = 0;
    WorkingSet.sizesPhaseOne[2] = 1;
    WorkingSet.sizesPhaseOne[3] = k - 1;
    WorkingSet.sizesPhaseOne[4] = jj;
    for (iy = 0; iy < 5; iy++) {
      WorkingSet.sizes[iy] = WorkingSet.sizesPhaseOne[iy];
      WorkingSet.sizesNormal[iy] = WorkingSet.sizesPhaseOne[iy];
    }

    WorkingSet.sizesPhaseOne[0] = jp;
    WorkingSet.sizesPhaseOne[1] = 0;
    WorkingSet.sizesPhaseOne[2] = 1;
    WorkingSet.sizesPhaseOne[3] = k;
    WorkingSet.sizesPhaseOne[4] = jj;
    for (iy = 0; iy < 5; iy++) {
      WorkingSet.sizesRegularized[iy] = WorkingSet.sizesPhaseOne[iy];
    }

    WorkingSet.sizesRegPhaseOne[0] = jp;
    WorkingSet.sizesRegPhaseOne[1] = 0;
    WorkingSet.sizesRegPhaseOne[2] = 1;
    WorkingSet.sizesRegPhaseOne[3] = k + 1;
    WorkingSet.sizesRegPhaseOne[4] = jj;
    WorkingSet.isActiveIdxRegularized[0] = 1;
    WorkingSet.isActiveIdxRegularized[1] = jp;
    WorkingSet.isActiveIdxRegularized[2] = 0;
    WorkingSet.isActiveIdxRegularized[3] = 1;
    WorkingSet.isActiveIdxRegularized[4] = k - 1;
    WorkingSet.isActiveIdxRegularized[5] = jj;
    for (iy = 0; iy < 6; iy++) {
      WorkingSet.isActiveIdxRegPhaseOne[iy] =
        WorkingSet.isActiveIdxRegularized[iy];
    }

    for (iy = 0; iy < 5; iy++) {
      WorkingSet.isActiveIdxRegPhaseOne[iy + 1] +=
        WorkingSet.isActiveIdxRegPhaseOne[iy];
    }

    for (iy = 0; iy < 6; iy++) {
      WorkingSet.isActiveIdx[iy] = WorkingSet.isActiveIdxRegPhaseOne[iy];
    }

    for (iy = 0; iy < 5; iy++) {
      WorkingSet.isActiveIdxRegularized[iy + 1] +=
        WorkingSet.isActiveIdxRegularized[iy];
    }

    for (iy = 0; iy < 6; iy++) {
      WorkingSet.isActiveIdxNormal[iy] = WorkingSet.isActiveIdxRegularized[iy];
    }

    WorkingSet.isActiveIdxRegularized[0] = 1;
    WorkingSet.isActiveIdxRegularized[1] = jp;
    WorkingSet.isActiveIdxRegularized[2] = 0;
    WorkingSet.isActiveIdxRegularized[3] = 1;
    WorkingSet.isActiveIdxRegularized[4] = k;
    WorkingSet.isActiveIdxRegularized[5] = jj;
    for (iy = 0; iy < 6; iy++) {
      WorkingSet.isActiveIdxRegPhaseOne[iy] =
        WorkingSet.isActiveIdxRegularized[iy];
    }

    for (iy = 0; iy < 5; iy++) {
      WorkingSet.isActiveIdxRegPhaseOne[iy + 1] +=
        WorkingSet.isActiveIdxRegPhaseOne[iy];
    }

    for (iy = 0; iy < 6; iy++) {
      WorkingSet.isActiveIdxPhaseOne[iy] = WorkingSet.isActiveIdxRegPhaseOne[iy];
    }

    WorkingSet.isActiveIdxRegPhaseOne[0] = 1;
    WorkingSet.isActiveIdxRegPhaseOne[1] = jp;
    WorkingSet.isActiveIdxRegPhaseOne[2] = 0;
    WorkingSet.isActiveIdxRegPhaseOne[3] = 1;
    WorkingSet.isActiveIdxRegPhaseOne[4] = k + 1;
    WorkingSet.isActiveIdxRegPhaseOne[5] = jj;
    for (iy = 0; iy < 5; iy++) {
      WorkingSet.isActiveIdxRegularized[iy + 1] +=
        WorkingSet.isActiveIdxRegularized[iy];
      WorkingSet.isActiveIdxRegPhaseOne[iy + 1] +=
        WorkingSet.isActiveIdxRegPhaseOne[iy];
    }

    WorkingSet.Aineq[0] = rtb_Switch2_p2_idx_0;
    WorkingSet.lb[0] = -lb[0];
    WorkingSet.ub[0] = rtb_Switch2[0];
    WorkingSet.Aineq[1] = rtb_Switch2_p2_idx_1;
    WorkingSet.lb[1] = -lb[1];
    WorkingSet.ub[1] = rtb_Switch2[1];
    WorkingSet.Aineq[2] = rtb_Switch2_p2_idx_2;
    WorkingSet.lb[2] = -lb[2];
    WorkingSet.ub[2] = rtb_Switch2[2];
    WorkingSet.Aineq[3] = rtb_Switch2_p2_idx_3;
    WorkingSet.lb[3] = -lb[3];
    WorkingSet.ub[3] = rtb_Switch2[3];
    ControlsMFE25_setProblemType(&WorkingSet, 3);
    b_ix = WorkingSet.isActiveIdx[2];
    for (iy = b_ix; iy < 11; iy++) {
      WorkingSet.isActiveConstr[iy - 1] = false;
    }

    WorkingSet.nWConstr[0] = WorkingSet.sizes[0];
    WorkingSet.nWConstr[1] = 0;
    WorkingSet.nWConstr[2] = 0;
    WorkingSet.nWConstr[3] = 0;
    WorkingSet.nWConstr[4] = 0;
    WorkingSet.nActiveConstr = WorkingSet.nWConstr[0];
    iy = (uint8_T)WorkingSet.sizes[0];
    for (ix = 0; ix < iy; ix++) {
      WorkingSet.Wid[ix] = 1;
      WorkingSet.Wlocalidx[ix] = ix + 1;
      WorkingSet.isActiveConstr[ix] = true;
      jA = 5 * ix;
      b_ix = WorkingSet.indexFixed[ix];
      if (b_ix - 2 >= 0) {
        memset(&WorkingSet.ATwset[jA], 0, (uint32_T)(b_ix - 1) * sizeof(real_T));
      }

      WorkingSet.ATwset[(WorkingSet.indexFixed[ix] + jA) - 1] = 1.0;
      b_ix = WorkingSet.indexFixed[ix] + 1;
      if (b_ix <= WorkingSet.nVar) {
        memset(&WorkingSet.ATwset[(b_ix + jA) + -1], 0, (uint32_T)
               ((((WorkingSet.nVar + jA) - b_ix) - jA) + 1) * sizeof(real_T));
      }

      WorkingSet.bwset[ix] = WorkingSet.ub[WorkingSet.indexFixed[ix] - 1];
    }

    WorkingSet.SLACK0 = 0.0;
    Switch3 = fmax(1.0, ((fabs(WorkingSet.Aineq[0]) + fabs(WorkingSet.Aineq[1]))
                         + fabs(WorkingSet.Aineq[2])) + fabs(WorkingSet.Aineq[3]));
    Sign = 0.0;
    Switch2 = 0.0;
    b_ix = 0;
    for (iy = 0; iy < 4; iy++) {
      Sign = fmax(Sign, ((fabs(A_0[b_ix + 1]) + fabs(A_0[b_ix])) + fabs(A_0[b_ix
        + 2])) + fabs(A_0[b_ix + 3]));
      Switch2 = fmax(Switch2, fabs(f[iy]));
      b_ix += 4;
    }

    Sign = fmax(fmax(Switch3, Switch2), Sign);
    CholRegManager.scaleFactor = Sign;
    expl_temp.ProbRelTolFactor = Sign;
    expl_temp.ConstrRelTolFactor = Switch3;
    expl_temp.MaxIterations = (((jp + k) + jj) + 4) * 10;
    expl_temp.RemainFeasible = false;
    ControlsMFE25_driver(A_0, f, &solution, &memspace, &WorkingSet,
                         &CholRegManager, expl_temp, &QRManager, &QPObjective);
    rtb_Switch2_p2_idx_0 = solution.xstar[0];
    rtb_Switch2_p2_idx_1 = solution.xstar[1];
    rtb_Switch2_p2_idx_2 = solution.xstar[2];
    rtb_Switch2_p2_idx_3 = solution.xstar[3];
  }

  rtb_Switch2_p2_idx_0_0 = rtb_Switch2_p2_idx_0 * 21.0;
  rtb_Switch2_p2_idx_1_0 = rtb_Switch2_p2_idx_1 * 21.0;
  rtb_Switch2_p2_idx_2_0 = rtb_Switch2_p2_idx_2 * 21.0;
  rtb_Switch2_p2_idx_3 *= 21.0;
  ControlsMFE25_toc(&savedTime, ControlsMFE25_DW);

  /* Delay: '<S9>/Delay' incorporates:
   *  MATLAB Function: '<S7>/Torque Allocation QP Normalized'
   */
  if (ControlsMFE25_DW->icLoad) {
    ControlsMFE25_DW->Delay_DSTATE[0] = rtb_Switch2_p2_idx_0_0;
    ControlsMFE25_DW->Delay_DSTATE[1] = rtb_Switch2_p2_idx_1_0;
    ControlsMFE25_DW->Delay_DSTATE[2] = rtb_Switch2_p2_idx_2_0;
    ControlsMFE25_DW->Delay_DSTATE[3] = rtb_Switch2_p2_idx_3;
  }

  /* Outport: '<Root>/wheelA_filtered' */
  ControlsMFE25_Y->wheelA_filtered = rtb_Integrator;

  /* Outport: '<Root>/kalman_vx' */
  ControlsMFE25_Y->kalman_vx = rtb_vx_est[0];

  /* Outport: '<Root>/kalman_vy' */
  ControlsMFE25_Y->kalman_vy = rtb_vx_est[1];

  /* Outport: '<Root>/yaw_rate_ref' */
  ControlsMFE25_Y->yaw_rate_ref = rtb_Product1_c;

  /* Outport: '<Root>/Mz_FF' */
  ControlsMFE25_Y->Mz_FF = rtb_Product_j;

  /* Outport: '<Root>/Mz_PID' */
  ControlsMFE25_Y->Mz_PID = B1;

  /* Sum: '<S9>/Difference Inputs2' incorporates:
   *  Delay: '<S9>/Delay'
   *  MATLAB Function: '<S7>/Torque Allocation QP Normalized'
   *  RelationalOperator: '<S315>/LowerRelop1'
   *  Sum: '<S9>/Difference Inputs1'
   *
   * Block description for '<S9>/Difference Inputs2':
   *
   *  Add in CPU
   *
   * Block description for '<S9>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rtb_Product_j = (rtb_Switch2_p2_idx_0_0 - ControlsMFE25_DW->Delay_DSTATE[0]) +
    ControlsMFE25_DW->Delay_DSTATE[0];
  rtb_Switch2_p2_idx_0 = rtb_Product_j;

  /* DotProduct: '<S1>/Dot Product' incorporates:
   *  SignalConversion generated from: '<S1>/Dot Product'
   */
  rtb_TmpSignalConversionAtDotP_0 *= rtb_Product_j;

  /* Sum: '<S9>/Difference Inputs2' incorporates:
   *  Delay: '<S9>/Delay'
   *  MATLAB Function: '<S7>/Torque Allocation QP Normalized'
   *  RelationalOperator: '<S315>/LowerRelop1'
   *  Sum: '<S9>/Difference Inputs1'
   *
   * Block description for '<S9>/Difference Inputs2':
   *
   *  Add in CPU
   *
   * Block description for '<S9>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rtb_Product_j = (rtb_Switch2_p2_idx_1_0 - ControlsMFE25_DW->Delay_DSTATE[1]) +
    ControlsMFE25_DW->Delay_DSTATE[1];
  rtb_Switch2_p2_idx_1 = rtb_Product_j;

  /* DotProduct: '<S1>/Dot Product' incorporates:
   *  SignalConversion generated from: '<S1>/Dot Product'
   */
  rtb_TmpSignalConversionAtDotP_0 += rtb_Product_j *
    rtb_TmpSignalConversionAtDotP_1;

  /* Sum: '<S9>/Difference Inputs2' incorporates:
   *  Delay: '<S9>/Delay'
   *  MATLAB Function: '<S7>/Torque Allocation QP Normalized'
   *  RelationalOperator: '<S315>/LowerRelop1'
   *  Sum: '<S9>/Difference Inputs1'
   *
   * Block description for '<S9>/Difference Inputs2':
   *
   *  Add in CPU
   *
   * Block description for '<S9>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rtb_Product_j = (rtb_Switch2_p2_idx_2_0 - ControlsMFE25_DW->Delay_DSTATE[2]) +
    ControlsMFE25_DW->Delay_DSTATE[2];
  rtb_Switch2_p2_idx_2 = rtb_Product_j;

  /* DotProduct: '<S1>/Dot Product' incorporates:
   *  SignalConversion generated from: '<S1>/Dot Product'
   */
  rtb_TmpSignalConversionAtDotP_0 += rtb_Product_j *
    rtb_TmpSignalConversionAtDotP_2;

  /* Sum: '<S9>/Difference Inputs2' incorporates:
   *  Delay: '<S9>/Delay'
   *  MATLAB Function: '<S7>/Torque Allocation QP Normalized'
   *  RelationalOperator: '<S315>/LowerRelop1'
   *  Sum: '<S9>/Difference Inputs1'
   *
   * Block description for '<S9>/Difference Inputs2':
   *
   *  Add in CPU
   *
   * Block description for '<S9>/Difference Inputs1':
   *
   *  Add in CPU
   */
  rtb_Product_j = (rtb_Switch2_p2_idx_3 - ControlsMFE25_DW->Delay_DSTATE[3]) +
    ControlsMFE25_DW->Delay_DSTATE[3];

  /* Outport: '<Root>/tau1' */
  ControlsMFE25_Y->tau1 = rtb_Switch2_p2_idx_0;

  /* Outport: '<Root>/tau2' */
  ControlsMFE25_Y->tau2 = rtb_Switch2_p2_idx_1;

  /* Outport: '<Root>/tau3' */
  ControlsMFE25_Y->tau3 = rtb_Switch2_p2_idx_2;

  /* Outport: '<Root>/tau4' incorporates:
   *  Sum: '<S9>/Difference Inputs2'
   *
   * Block description for '<S9>/Difference Inputs2':
   *
   *  Add in CPU
   */
  ControlsMFE25_Y->tau4 = rtb_Product_j;

  /* Product: '<S1>/Product2' incorporates:
   *  Constant: '<Root>/Constant18'
   *  DotProduct: '<S1>/Dot Product'
   *  SignalConversion generated from: '<S1>/Dot Product'
   */
  B1 = (rtb_Product_j * rtb_TmpSignalConversionAtDotP_3 +
        rtb_TmpSignalConversionAtDotP_0) * 13.39;

  /* Outport: '<Root>/Pmech' */
  ControlsMFE25_Y->Pmech = B1;

  /* Outport: '<Root>/Pelect_estimated' incorporates:
   *  Product: '<S1>/Product4'
   */
  ControlsMFE25_Y->Pelect_estimated = B1 * ControlsMFE25_U->efficiency;

  /* Outport: '<Root>/fz_calc_fl' */
  ControlsMFE25_Y->fz_calc_fl = rtb_Saturation_idx_0;

  /* Outport: '<Root>/fz_calc_fr' */
  ControlsMFE25_Y->fz_calc_fr = rtb_Saturation_idx_1;

  /* Outport: '<Root>/fz_calc_rl' */
  ControlsMFE25_Y->fz_calc_rl = rtb_Saturation_idx_2;

  /* Outport: '<Root>/fz_calc_rr' */
  ControlsMFE25_Y->fz_calc_rr = rtb_Saturation_idx_3;

  /* Outport: '<Root>/msr_ref_fl' */
  ControlsMFE25_Y->msr_ref_fl = rtb_reference_idx_0;

  /* Outport: '<Root>/msr_ref_fr' */
  ControlsMFE25_Y->msr_ref_fr = rtb_reference_idx_1;

  /* Outport: '<Root>/msr_ref_rl' */
  ControlsMFE25_Y->msr_ref_rl = rtb_reference_idx_2;

  /* Outport: '<Root>/msr_ref_rr' */
  ControlsMFE25_Y->msr_ref_rr = rtb_reference_idx_3;

  /* Outport: '<Root>/msr_actual_fl' */
  ControlsMFE25_Y->msr_actual_fl = rtb_msr_idx_0;

  /* Outport: '<Root>/msr_actual_fr' */
  ControlsMFE25_Y->msr_actual_fr = rtb_msr_idx_1;

  /* Outport: '<Root>/msr_actual_rl' */
  ControlsMFE25_Y->msr_actual_rl = rtb_msr_idx_2;

  /* Outport: '<Root>/msr_actual_rr' */
  ControlsMFE25_Y->msr_actual_rr = rtb_msr_idx_3;

  /* Outport: '<Root>/Long_FF_fl' */
  ControlsMFE25_Y->Long_FF_fl = slip_idx_0;

  /* Outport: '<Root>/Long_FF_fr' */
  ControlsMFE25_Y->Long_FF_fr = slip_idx_1;

  /* Outport: '<Root>/Long_FF_rl' */
  ControlsMFE25_Y->Long_FF_rl = slip_idx_2;

  /* Outport: '<Root>/Long_FF_rr' */
  ControlsMFE25_Y->Long_FF_rr = slip_idx_3;

  /* Outport: '<Root>/Long_PID_fl' */
  ControlsMFE25_Y->Long_PID_fl = lty;

  /* Outport: '<Root>/Long_PID_fr' */
  ControlsMFE25_Y->Long_PID_fr = rtb_Switch2_g;

  /* Outport: '<Root>/Long_PID_rl' */
  ControlsMFE25_Y->Long_PID_rl = rtb_Switch2_nz;

  /* Outport: '<Root>/Long_PID_rr' */
  ControlsMFE25_Y->Long_PID_rr = s;

  /* Update for DiscreteIntegrator: '<S313>/Integrator' incorporates:
   *  Constant: '<S307>/Time constant'
   *  MinMax: '<S307>/Max'
   *  Product: '<S4>/1//T'
   *  Sum: '<S4>/Sum1'
   */
  ControlsMFE25_DW->Integrator_IC_LOADING = 0U;
  ControlsMFE25_DW->Integrator_DSTATE += 1.0 / fmax(ControlsMFE25_B->Probe[0],
    0.1) * (ControlsMFE25_Y->wheelA - rtb_Integrator) * 0.005;
  ControlsMFE25_DW->Integrator_PrevResetState = (int8_T)rtb_LogicalOperator;

  /* Update for Delay: '<S15>/Delay4' */
  ControlsMFE25_DW->Delay4_DSTATE = ControlsMFE25_U->vehicle_speed;

  /* Update for Delay: '<S15>/Delay3' */
  ControlsMFE25_DW->Delay3_DSTATE[0] = ControlsMFE25_DW->Delay3_DSTATE[1];
  ControlsMFE25_DW->Delay3_DSTATE[1] = ControlsMFE25_U->vehicle_speed;

  /* Update for Delay: '<S15>/Delay2' */
  ControlsMFE25_DW->Delay2_DSTATE[0] = ControlsMFE25_DW->Delay2_DSTATE[1];
  ControlsMFE25_DW->Delay2_DSTATE[1] = ControlsMFE25_DW->Delay2_DSTATE[2];
  ControlsMFE25_DW->Delay2_DSTATE[2] = ControlsMFE25_U->vehicle_speed;

  /* Update for Delay: '<S15>/Delay1' */
  ControlsMFE25_DW->Delay1_DSTATE[0] = ControlsMFE25_DW->Delay1_DSTATE[1];
  ControlsMFE25_DW->Delay1_DSTATE[1] = ControlsMFE25_DW->Delay1_DSTATE[2];
  ControlsMFE25_DW->Delay1_DSTATE[2] = ControlsMFE25_DW->Delay1_DSTATE[3];
  ControlsMFE25_DW->Delay1_DSTATE[3] = ControlsMFE25_U->vehicle_speed;

  /* Update for DiscreteIntegrator: '<S115>/Filter' incorporates:
   *  DiscreteIntegrator: '<S120>/Integrator'
   *  DiscreteIntegrator: '<S171>/Filter'
   *  DiscreteIntegrator: '<S176>/Integrator'
   *  DiscreteIntegrator: '<S227>/Filter'
   *  DiscreteIntegrator: '<S232>/Integrator'
   *  DiscreteIntegrator: '<S283>/Filter'
   *  DiscreteIntegrator: '<S288>/Integrator'
   *  DiscreteIntegrator: '<S53>/Filter'
   *  DiscreteIntegrator: '<S58>/Integrator'
   */
  ControlsMFE25_DW->Filter_DSTATE += 0.005 * smax;
  if (ControlsMFE25_U->ResetSignal > 0.0) {
    ControlsMFE25_DW->Filter_PrevResetState = 1;
    ControlsMFE25_DW->Integrator_PrevResetState_n = 1;
    ControlsMFE25_DW->Filter_PrevResetState_a = 1;
    ControlsMFE25_DW->Integrator_PrevResetState_e = 1;
    ControlsMFE25_DW->Filter_PrevResetState_k = 1;
    ControlsMFE25_DW->Integrator_PrevResetState_f = 1;
    ControlsMFE25_DW->Filter_PrevResetState_p = 1;
    ControlsMFE25_DW->Integrator_PrevResetState_m = 1;
    ControlsMFE25_DW->Filter_PrevResetState_ag = 1;
    ControlsMFE25_DW->Integrator_PrevResetState_nn = 1;
  } else if (ControlsMFE25_U->ResetSignal < 0.0) {
    ControlsMFE25_DW->Filter_PrevResetState = -1;
    ControlsMFE25_DW->Integrator_PrevResetState_n = -1;
    ControlsMFE25_DW->Filter_PrevResetState_a = -1;
    ControlsMFE25_DW->Integrator_PrevResetState_e = -1;
    ControlsMFE25_DW->Filter_PrevResetState_k = -1;
    ControlsMFE25_DW->Integrator_PrevResetState_f = -1;
    ControlsMFE25_DW->Filter_PrevResetState_p = -1;
    ControlsMFE25_DW->Integrator_PrevResetState_m = -1;
    ControlsMFE25_DW->Filter_PrevResetState_ag = -1;
    ControlsMFE25_DW->Integrator_PrevResetState_nn = -1;
  } else if (ControlsMFE25_U->ResetSignal == 0.0) {
    ControlsMFE25_DW->Filter_PrevResetState = 0;
    ControlsMFE25_DW->Integrator_PrevResetState_n = 0;
    ControlsMFE25_DW->Filter_PrevResetState_a = 0;
    ControlsMFE25_DW->Integrator_PrevResetState_e = 0;
    ControlsMFE25_DW->Filter_PrevResetState_k = 0;
    ControlsMFE25_DW->Integrator_PrevResetState_f = 0;
    ControlsMFE25_DW->Filter_PrevResetState_p = 0;
    ControlsMFE25_DW->Integrator_PrevResetState_m = 0;
    ControlsMFE25_DW->Filter_PrevResetState_ag = 0;
    ControlsMFE25_DW->Integrator_PrevResetState_nn = 0;
  } else {
    ControlsMFE25_DW->Filter_PrevResetState = 2;
    ControlsMFE25_DW->Integrator_PrevResetState_n = 2;
    ControlsMFE25_DW->Filter_PrevResetState_a = 2;
    ControlsMFE25_DW->Integrator_PrevResetState_e = 2;
    ControlsMFE25_DW->Filter_PrevResetState_k = 2;
    ControlsMFE25_DW->Integrator_PrevResetState_f = 2;
    ControlsMFE25_DW->Filter_PrevResetState_p = 2;
    ControlsMFE25_DW->Integrator_PrevResetState_m = 2;
    ControlsMFE25_DW->Filter_PrevResetState_ag = 2;
    ControlsMFE25_DW->Integrator_PrevResetState_nn = 2;
  }

  /* End of Update for DiscreteIntegrator: '<S115>/Filter' */

  /* Update for DiscreteIntegrator: '<S120>/Integrator' */
  ControlsMFE25_DW->Integrator_DSTATE_k = Integrator_tmp + Integrator;

  /* Update for DiscreteIntegrator: '<S171>/Filter' */
  ControlsMFE25_DW->Filter_DSTATE_k += 0.005 * rtb_NProdOut_h;

  /* Update for DiscreteIntegrator: '<S176>/Integrator' */
  ControlsMFE25_DW->Integrator_DSTATE_p = Integrator_n_tmp + Integrator_n;

  /* Update for DiscreteIntegrator: '<S227>/Filter' */
  ControlsMFE25_DW->Filter_DSTATE_f += 0.005 * rtb_NProdOut_e;

  /* Update for DiscreteIntegrator: '<S232>/Integrator' */
  ControlsMFE25_DW->Integrator_DSTATE_kg = Integrator_h_tmp + Integrator_h;

  /* Update for DiscreteIntegrator: '<S283>/Filter' */
  ControlsMFE25_DW->Filter_DSTATE_d += 0.005 * rtb_Filter_p;

  /* Update for DiscreteIntegrator: '<S288>/Integrator' */
  ControlsMFE25_DW->Integrator_DSTATE_o = rtb_SumFdbk_hw + Integrator_n2;

  /* Update for DiscreteIntegrator: '<S53>/Filter' */
  ControlsMFE25_DW->Filter_DSTATE_c += 0.005 * K_ratio;

  /* Update for DiscreteIntegrator: '<S58>/Integrator' */
  ControlsMFE25_DW->Integrator_DSTATE_a = rtb_IProdOut + B0;

  /* Update for Delay: '<S9>/Delay' */
  ControlsMFE25_DW->icLoad = false;

  /* Update for Delay: '<S7>/Delay One Step' incorporates:
   *  MATLAB Function: '<S7>/Torque Allocation QP Normalized'
   */
  ControlsMFE25_DW->DelayOneStep_DSTATE[0] = rtb_Switch2_p2_idx_0_0;

  /* Update for Delay: '<S9>/Delay' */
  ControlsMFE25_DW->Delay_DSTATE[0] = rtb_Switch2_p2_idx_0;

  /* Update for Delay: '<S7>/Delay One Step' incorporates:
   *  MATLAB Function: '<S7>/Torque Allocation QP Normalized'
   */
  ControlsMFE25_DW->DelayOneStep_DSTATE[1] = rtb_Switch2_p2_idx_1_0;

  /* Update for Delay: '<S9>/Delay' */
  ControlsMFE25_DW->Delay_DSTATE[1] = rtb_Switch2_p2_idx_1;

  /* Update for Delay: '<S7>/Delay One Step' incorporates:
   *  MATLAB Function: '<S7>/Torque Allocation QP Normalized'
   */
  ControlsMFE25_DW->DelayOneStep_DSTATE[2] = rtb_Switch2_p2_idx_2_0;

  /* Update for Delay: '<S9>/Delay' */
  ControlsMFE25_DW->Delay_DSTATE[2] = rtb_Switch2_p2_idx_2;

  /* Update for Delay: '<S7>/Delay One Step' incorporates:
   *  MATLAB Function: '<S7>/Torque Allocation QP Normalized'
   */
  ControlsMFE25_DW->DelayOneStep_DSTATE[3] = rtb_Switch2_p2_idx_3;

  /* Update for Delay: '<S9>/Delay' incorporates:
   *  Sum: '<S9>/Difference Inputs2'
   *
   * Block description for '<S9>/Difference Inputs2':
   *
   *  Add in CPU
   */
  ControlsMFE25_DW->Delay_DSTATE[3] = rtb_Product_j;
}

/* Model initialize function */
void ControlsMFE25_initialize(RT_MODEL_ControlsMFE25_T *const ControlsMFE25_M)
{
  B_ControlsMFE25_T *ControlsMFE25_B = ControlsMFE25_M->blockIO;
  DW_ControlsMFE25_T *ControlsMFE25_DW = ControlsMFE25_M->dwork;

  /* Start for Probe: '<S307>/Probe' */
  ControlsMFE25_B->Probe[0] = 0.005;
  ControlsMFE25_B->Probe[1] = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S313>/Integrator' */
  ControlsMFE25_DW->Integrator_PrevResetState = 0;
  ControlsMFE25_DW->Integrator_IC_LOADING = 1U;

  /* InitializeConditions for DiscreteIntegrator: '<S115>/Filter' */
  ControlsMFE25_DW->Filter_PrevResetState = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S120>/Integrator' */
  ControlsMFE25_DW->Integrator_DSTATE_k = 0.0;
  ControlsMFE25_DW->Integrator_PrevResetState_n = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S171>/Filter' */
  ControlsMFE25_DW->Filter_PrevResetState_a = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S176>/Integrator' */
  ControlsMFE25_DW->Integrator_DSTATE_p = 0.0;
  ControlsMFE25_DW->Integrator_PrevResetState_e = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S227>/Filter' */
  ControlsMFE25_DW->Filter_PrevResetState_k = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S232>/Integrator' */
  ControlsMFE25_DW->Integrator_DSTATE_kg = 0.0;
  ControlsMFE25_DW->Integrator_PrevResetState_f = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S283>/Filter' */
  ControlsMFE25_DW->Filter_PrevResetState_p = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S288>/Integrator' */
  ControlsMFE25_DW->Integrator_DSTATE_o = 0.0;
  ControlsMFE25_DW->Integrator_PrevResetState_m = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S53>/Filter' */
  ControlsMFE25_DW->Filter_PrevResetState_ag = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S58>/Integrator' */
  ControlsMFE25_DW->Integrator_DSTATE_a = 0.0;
  ControlsMFE25_DW->Integrator_PrevResetState_nn = 2;

  /* InitializeConditions for Delay: '<S9>/Delay' */
  ControlsMFE25_DW->icLoad = true;

  /* SystemInitialize for MATLAB Function: '<S15>/MATLAB Function2' */
  ControlsMFE25_DW->is_initialized_not_empty = false;

  /* InitializeConditions for Delay: '<S7>/Delay One Step' */
  ControlsMFE25_DW->DelayOneStep_DSTATE[0] = 0.5;
  ControlsMFE25_DW->DelayOneStep_DSTATE[1] = 0.5;

  /* SystemInitialize for MATLAB Function: '<S15>/MATLAB Function2' */
  ControlsMFE25_DW->P_pred[1] = 0.0;

  /* InitializeConditions for Delay: '<S7>/Delay One Step' */
  ControlsMFE25_DW->DelayOneStep_DSTATE[2] = 0.5;

  /* SystemInitialize for MATLAB Function: '<S15>/MATLAB Function2' */
  ControlsMFE25_DW->P_pred[2] = 0.0;

  /* InitializeConditions for Delay: '<S7>/Delay One Step' */
  ControlsMFE25_DW->DelayOneStep_DSTATE[3] = 0.5;

  /* SystemInitialize for MATLAB Function: '<S15>/MATLAB Function2' */
  ControlsMFE25_DW->P_pred[0] = 0.01;
  ControlsMFE25_DW->P_pred[3] = 0.01;

  /* SystemInitialize for MATLAB Function: '<S7>/Torque Allocation QP Normalized' */
  ControlsMFE25_DW->freq_not_empty = false;
  ControlsMFE25_DW->savedTime_not_empty = false;
}

/* Model terminate function */
void ControlsMFE25_terminate(RT_MODEL_ControlsMFE25_T * ControlsMFE25_M)
{
  /* model code */
  rt_FREE(ControlsMFE25_M->blockIO);
  rt_FREE(ControlsMFE25_M->inputs);
  rt_FREE(ControlsMFE25_M->outputs);
  rt_FREE(ControlsMFE25_M->dwork);
  rt_FREE(ControlsMFE25_M);
}

/* Model data allocation function */
RT_MODEL_ControlsMFE25_T *ControlsMFE25(void)
{
  RT_MODEL_ControlsMFE25_T *ControlsMFE25_M;
  ControlsMFE25_M = (RT_MODEL_ControlsMFE25_T *) malloc(sizeof
    (RT_MODEL_ControlsMFE25_T));
  if (ControlsMFE25_M == (NULL)) {
    return (NULL);
  }

  (void) memset((char *)ControlsMFE25_M, 0,
                sizeof(RT_MODEL_ControlsMFE25_T));

  /* block I/O */
  {
    B_ControlsMFE25_T *b = (B_ControlsMFE25_T *) malloc(sizeof(B_ControlsMFE25_T));
    rt_VALIDATE_MEMORY(ControlsMFE25_M,b);
    ControlsMFE25_M->blockIO = (b);
  }

  /* states (dwork) */
  {
    DW_ControlsMFE25_T *dwork = (DW_ControlsMFE25_T *) malloc(sizeof
      (DW_ControlsMFE25_T));
    rt_VALIDATE_MEMORY(ControlsMFE25_M,dwork);
    ControlsMFE25_M->dwork = (dwork);
  }

  /* external inputs */
  {
    ExtU_ControlsMFE25_T *ControlsMFE25_U = (ExtU_ControlsMFE25_T *) malloc
      (sizeof(ExtU_ControlsMFE25_T));
    rt_VALIDATE_MEMORY(ControlsMFE25_M,ControlsMFE25_U);
    ControlsMFE25_M->inputs = (((ExtU_ControlsMFE25_T *) ControlsMFE25_U));
  }

  /* external outputs */
  {
    ExtY_ControlsMFE25_T *ControlsMFE25_Y = (ExtY_ControlsMFE25_T *) malloc
      (sizeof(ExtY_ControlsMFE25_T));
    rt_VALIDATE_MEMORY(ControlsMFE25_M,ControlsMFE25_Y);
    ControlsMFE25_M->outputs = (ControlsMFE25_Y);
  }

  {
    B_ControlsMFE25_T *ControlsMFE25_B = ControlsMFE25_M->blockIO;
    DW_ControlsMFE25_T *ControlsMFE25_DW = ControlsMFE25_M->dwork;
    ExtU_ControlsMFE25_T *ControlsMFE25_U = (ExtU_ControlsMFE25_T *)
      ControlsMFE25_M->inputs;
    ExtY_ControlsMFE25_T *ControlsMFE25_Y = (ExtY_ControlsMFE25_T *)
      ControlsMFE25_M->outputs;

    /* block I/O */
    (void) memset(((void *) ControlsMFE25_B), 0,
                  sizeof(B_ControlsMFE25_T));

    /* states (dwork) */
    (void) memset((void *)ControlsMFE25_DW, 0,
                  sizeof(DW_ControlsMFE25_T));

    /* external inputs */
    (void)memset(ControlsMFE25_U, 0, sizeof(ExtU_ControlsMFE25_T));

    /* external outputs */
    (void)memset(ControlsMFE25_Y, 0, sizeof(ExtY_ControlsMFE25_T));
  }

  return ControlsMFE25_M;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
