/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ControlsMFE25_types.h
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

#ifndef ControlsMFE25_types_h_
#define ControlsMFE25_types_h_
#include "rtwtypes.h"

/* Custom Type definition for MATLAB Function: '<S7>/Torque Allocation QP Normalized' */
#ifndef struct_tag_sdAmwXbnJnEmimT0NaJRtAD
#define struct_tag_sdAmwXbnJnEmimT0NaJRtAD

struct tag_sdAmwXbnJnEmimT0NaJRtAD
{
  real_T tv_sec;
  real_T tv_nsec;
};

#endif                                 /* struct_tag_sdAmwXbnJnEmimT0NaJRtAD */

#ifndef typedef_sdAmwXbnJnEmimT0NaJRtAD_Contr_T
#define typedef_sdAmwXbnJnEmimT0NaJRtAD_Contr_T

typedef struct tag_sdAmwXbnJnEmimT0NaJRtAD sdAmwXbnJnEmimT0NaJRtAD_Contr_T;

#endif                             /* typedef_sdAmwXbnJnEmimT0NaJRtAD_Contr_T */

#ifndef struct_tag_sF7ecKzAoqUt0jrk31NyRZH
#define struct_tag_sF7ecKzAoqUt0jrk31NyRZH

struct tag_sF7ecKzAoqUt0jrk31NyRZH
{
  real_T xstar[5];
  real_T fstar;
  real_T firstorderopt;
  real_T lambda[10];
  int32_T state;
  real_T maxConstr;
  int32_T iterations;
  real_T searchDir[5];
};

#endif                                 /* struct_tag_sF7ecKzAoqUt0jrk31NyRZH */

#ifndef typedef_sF7ecKzAoqUt0jrk31NyRZH_Contr_T
#define typedef_sF7ecKzAoqUt0jrk31NyRZH_Contr_T

typedef struct tag_sF7ecKzAoqUt0jrk31NyRZH sF7ecKzAoqUt0jrk31NyRZH_Contr_T;

#endif                             /* typedef_sF7ecKzAoqUt0jrk31NyRZH_Contr_T */

#ifndef struct_tag_szdozZxcClCeUpd1TsA9nJF
#define struct_tag_szdozZxcClCeUpd1TsA9nJF

struct tag_szdozZxcClCeUpd1TsA9nJF
{
  real_T grad[5];
  real_T Hx[4];
  boolean_T hasLinear;
  int32_T nvar;
  int32_T maxVar;
  real_T beta;
  real_T rho;
  int32_T objtype;
  int32_T prev_objtype;
  int32_T prev_nvar;
  boolean_T prev_hasLinear;
  real_T gammaScalar;
};

#endif                                 /* struct_tag_szdozZxcClCeUpd1TsA9nJF */

#ifndef typedef_szdozZxcClCeUpd1TsA9nJF_Contr_T
#define typedef_szdozZxcClCeUpd1TsA9nJF_Contr_T

typedef struct tag_szdozZxcClCeUpd1TsA9nJF szdozZxcClCeUpd1TsA9nJF_Contr_T;

#endif                             /* typedef_szdozZxcClCeUpd1TsA9nJF_Contr_T */

#ifndef struct_tag_sY034dY3cx1IgSIMa0jtlQE
#define struct_tag_sY034dY3cx1IgSIMa0jtlQE

struct tag_sY034dY3cx1IgSIMa0jtlQE
{
  real_T FMat[25];
  int32_T ldm;
  int32_T ndims;
  int32_T info;
  real_T scaleFactor;
  boolean_T ConvexCheck;
  real_T regTol_;
  real_T workspace_[240];
  real_T workspace2_[240];
};

#endif                                 /* struct_tag_sY034dY3cx1IgSIMa0jtlQE */

#ifndef typedef_sY034dY3cx1IgSIMa0jtlQE_Contr_T
#define typedef_sY034dY3cx1IgSIMa0jtlQE_Contr_T

typedef struct tag_sY034dY3cx1IgSIMa0jtlQE sY034dY3cx1IgSIMa0jtlQE_Contr_T;

#endif                             /* typedef_sY034dY3cx1IgSIMa0jtlQE_Contr_T */

#ifndef struct_tag_sIOJhD9KwAkF5sEguPjYquC
#define struct_tag_sIOJhD9KwAkF5sEguPjYquC

struct tag_sIOJhD9KwAkF5sEguPjYquC
{
  boolean_T RemainFeasible;
  int32_T MaxIterations;
  real_T ConstrRelTolFactor;
  real_T ProbRelTolFactor;
};

#endif                                 /* struct_tag_sIOJhD9KwAkF5sEguPjYquC */

#ifndef typedef_sIOJhD9KwAkF5sEguPjYquC_Contr_T
#define typedef_sIOJhD9KwAkF5sEguPjYquC_Contr_T

typedef struct tag_sIOJhD9KwAkF5sEguPjYquC sIOJhD9KwAkF5sEguPjYquC_Contr_T;

#endif                             /* typedef_sIOJhD9KwAkF5sEguPjYquC_Contr_T */

#ifndef struct_tag_sisnsZ1AM9QRiMKnwqarOXF
#define struct_tag_sisnsZ1AM9QRiMKnwqarOXF

struct tag_sisnsZ1AM9QRiMKnwqarOXF
{
  int32_T ldq;
  real_T QR[50];
  real_T Q[25];
  int32_T jpvt[10];
  int32_T mrows;
  int32_T ncols;
  real_T tau[5];
  int32_T minRowCol;
  boolean_T usedPivoting;
};

#endif                                 /* struct_tag_sisnsZ1AM9QRiMKnwqarOXF */

#ifndef typedef_sisnsZ1AM9QRiMKnwqarOXF_Contr_T
#define typedef_sisnsZ1AM9QRiMKnwqarOXF_Contr_T

typedef struct tag_sisnsZ1AM9QRiMKnwqarOXF sisnsZ1AM9QRiMKnwqarOXF_Contr_T;

#endif                             /* typedef_sisnsZ1AM9QRiMKnwqarOXF_Contr_T */

#ifndef struct_tag_su0bqVilpnfgpuAQ6xEtFDC
#define struct_tag_su0bqVilpnfgpuAQ6xEtFDC

struct tag_su0bqVilpnfgpuAQ6xEtFDC
{
  real_T workspace_float[50];
  int32_T workspace_int[10];
  int32_T workspace_sort[10];
};

#endif                                 /* struct_tag_su0bqVilpnfgpuAQ6xEtFDC */

#ifndef typedef_su0bqVilpnfgpuAQ6xEtFDC_Contr_T
#define typedef_su0bqVilpnfgpuAQ6xEtFDC_Contr_T

typedef struct tag_su0bqVilpnfgpuAQ6xEtFDC su0bqVilpnfgpuAQ6xEtFDC_Contr_T;

#endif                             /* typedef_su0bqVilpnfgpuAQ6xEtFDC_Contr_T */

#ifndef struct_tag_s18w5MCz6685sBFJwJZKJdG
#define struct_tag_s18w5MCz6685sBFJwJZKJdG

struct tag_s18w5MCz6685sBFJwJZKJdG
{
  int32_T mConstr;
  int32_T mConstrOrig;
  int32_T mConstrMax;
  int32_T nVar;
  int32_T nVarOrig;
  int32_T nVarMax;
  int32_T ldA;
  real_T Aineq[5];
  real_T bineq;
  real_T lb[5];
  real_T ub[5];
  int32_T indexLB[5];
  int32_T indexUB[5];
  int32_T indexFixed[5];
  int32_T mEqRemoved;
  real_T ATwset[50];
  real_T bwset[10];
  int32_T nActiveConstr;
  real_T maxConstrWorkspace[10];
  int32_T sizes[5];
  int32_T sizesNormal[5];
  int32_T sizesPhaseOne[5];
  int32_T sizesRegularized[5];
  int32_T sizesRegPhaseOne[5];
  int32_T isActiveIdx[6];
  int32_T isActiveIdxNormal[6];
  int32_T isActiveIdxPhaseOne[6];
  int32_T isActiveIdxRegularized[6];
  int32_T isActiveIdxRegPhaseOne[6];
  boolean_T isActiveConstr[10];
  int32_T Wid[10];
  int32_T Wlocalidx[10];
  int32_T nWConstr[5];
  int32_T probType;
  real_T SLACK0;
};

#endif                                 /* struct_tag_s18w5MCz6685sBFJwJZKJdG */

#ifndef typedef_s18w5MCz6685sBFJwJZKJdG_Contr_T
#define typedef_s18w5MCz6685sBFJwJZKJdG_Contr_T

typedef struct tag_s18w5MCz6685sBFJwJZKJdG s18w5MCz6685sBFJwJZKJdG_Contr_T;

#endif                             /* typedef_s18w5MCz6685sBFJwJZKJdG_Contr_T */

/* Forward declaration for rtModel */
typedef struct tag_RTM_ControlsMFE25_T RT_MODEL_ControlsMFE25_T;

#endif                                 /* ControlsMFE25_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
