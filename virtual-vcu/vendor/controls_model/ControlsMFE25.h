/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: ControlsMFE25.h
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

#ifndef ControlsMFE25_h_
#define ControlsMFE25_h_
#ifndef ControlsMFE25_COMMON_INCLUDES_
#define ControlsMFE25_COMMON_INCLUDES_
#include <stdlib.h>
#include <stdio.h>
#include "rtwtypes.h"
#include "rt_nonfinite.h"
#include "math.h"
#include "coder_posix_time.h"
#endif                                 /* ControlsMFE25_COMMON_INCLUDES_ */

#include "ControlsMFE25_types.h"
#include "rtGetInf.h"
#include "rtGetNaN.h"
#include <stddef.h>
#include <string.h>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Block signals (default storage) */
typedef struct {
  real_T Probe[2];                     /* '<S307>/Probe' */
} B_ControlsMFE25_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T Integrator_DSTATE;            /* '<S313>/Integrator' */
  real_T Delay4_DSTATE;                /* '<S15>/Delay4' */
  real_T Delay3_DSTATE[2];             /* '<S15>/Delay3' */
  real_T Delay2_DSTATE[3];             /* '<S15>/Delay2' */
  real_T Delay1_DSTATE[4];             /* '<S15>/Delay1' */
  real_T Filter_DSTATE;                /* '<S115>/Filter' */
  real_T Integrator_DSTATE_k;          /* '<S120>/Integrator' */
  real_T Filter_DSTATE_k;              /* '<S171>/Filter' */
  real_T Integrator_DSTATE_p;          /* '<S176>/Integrator' */
  real_T Filter_DSTATE_f;              /* '<S227>/Filter' */
  real_T Integrator_DSTATE_kg;         /* '<S232>/Integrator' */
  real_T Filter_DSTATE_d;              /* '<S283>/Filter' */
  real_T Integrator_DSTATE_o;          /* '<S288>/Integrator' */
  real_T Filter_DSTATE_c;              /* '<S53>/Filter' */
  real_T Integrator_DSTATE_a;          /* '<S58>/Integrator' */
  real_T DelayOneStep_DSTATE[4];       /* '<S7>/Delay One Step' */
  real_T Delay_DSTATE[4];              /* '<S9>/Delay' */
  real_T Delay1_DSTATE_p;              /* '<S317>/Delay1' */
  real_T Delay3_DSTATE_c;              /* '<S317>/Delay3' */
  real_T Delay2_DSTATE_e;              /* '<S317>/Delay2' */
  real_T x_pred[2];                    /* '<S15>/MATLAB Function2' */
  real_T P_pred[4];                    /* '<S15>/MATLAB Function2' */
  real_T freq;                      /* '<S7>/Torque Allocation QP Normalized' */
  uint32_T m_bpIndex;                  /* '<S10>/1-D Lookup Table' */
  uint32_T m_bpIndex_d;                /* '<S10>/1-D Lookup Table1' */
  uint32_T m_bpIndex_h;                /* '<S10>/1-D Lookup Table2' */
  uint32_T m_bpIndex_i;                /* '<S10>/1-D Lookup Table3' */
  uint32_T m_bpIndex_p;                /* '<S78>/kp' */
  uint32_T m_bpIndex_c;                /* '<S78>/kd' */
  uint32_T m_bpIndex_ie;               /* '<S78>/ki' */
  uint32_T m_bpIndex_e;                /* '<S20>/kp' */
  uint32_T m_bpIndex_im;               /* '<S20>/kd' */
  uint32_T m_bpIndex_o;                /* '<S20>/ki' */
  uint32_T m_bpIndex_g;                /* '<S8>/Pedal Mapping w//o Regen' */
  uint32_T m_bpIndex_m;                /* '<S8>/Pedal Mapping w//Regen' */
  int8_T Integrator_PrevResetState;    /* '<S313>/Integrator' */
  int8_T Filter_PrevResetState;        /* '<S115>/Filter' */
  int8_T Integrator_PrevResetState_n;  /* '<S120>/Integrator' */
  int8_T Filter_PrevResetState_a;      /* '<S171>/Filter' */
  int8_T Integrator_PrevResetState_e;  /* '<S176>/Integrator' */
  int8_T Filter_PrevResetState_k;      /* '<S227>/Filter' */
  int8_T Integrator_PrevResetState_f;  /* '<S232>/Integrator' */
  int8_T Filter_PrevResetState_p;      /* '<S283>/Filter' */
  int8_T Integrator_PrevResetState_m;  /* '<S288>/Integrator' */
  int8_T Filter_PrevResetState_ag;     /* '<S53>/Filter' */
  int8_T Integrator_PrevResetState_nn; /* '<S58>/Integrator' */
  uint8_T Integrator_IC_LOADING;       /* '<S313>/Integrator' */
  boolean_T icLoad;                    /* '<S9>/Delay' */
  boolean_T is_initialized_not_empty;  /* '<S15>/MATLAB Function2' */
  boolean_T freq_not_empty;         /* '<S7>/Torque Allocation QP Normalized' */
  boolean_T savedTime_not_empty;    /* '<S7>/Torque Allocation QP Normalized' */
} DW_ControlsMFE25_T;

/* Invariant block signals (default storage) */
typedef struct {
  const real_T Gain;                   /* '<S2>/Gain' */
  const real_T Gain_n;                 /* '<S1>/Gain' */
  const real_T Gain_m;                 /* '<S8>/Gain' */
  const boolean_T Compare;             /* '<S310>/Compare' */
} ConstB_ControlsMFE25_T;

/* Constant parameters (default storage) */
typedef struct {
  /* Expression: [-1 -1 0 0 1 1]
   * Referenced by: '<S8>/Pedal Mapping w//Regen'
   */
  real_T PedalMappingwRegen_tableData[6];

  /* Expression: [-1 0 0.08 0.1 1 2]
   * Referenced by: '<S8>/Pedal Mapping w//Regen'
   */
  real_T PedalMappingwRegen_bp01Data[6];

  /* Expression: [0 0 1 1]
   * Referenced by: '<S8>/Pedal Mapping w//o Regen'
   */
  real_T PedalMappingwoRegen_tableData[4];

  /* Expression: [-1 0 1 2]
   * Referenced by: '<S8>/Pedal Mapping w//o Regen'
   */
  real_T PedalMappingwoRegen_bp01Data[4];

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by:
   *   '<Root>/Constant'
   *   '<Root>/Constant6'
   */
  real_T pooled2[3];

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by:
   *   '<Root>/Constant1'
   *   '<Root>/Constant2'
   */
  real_T pooled3[3];

  /* Expression: CyalphaLookUp
   * Referenced by: '<Root>/Constant23'
   */
  real_T Constant23_Value[589];

  /* Expression: pid_kd_long
   * Referenced by: '<Root>/Constant3'
   */
  real_T Constant3_Value[3];

  /* Expression: y_ref
   * Referenced by: '<Root>/Constant4'
   */
  real_T Constant4_Value[200];

  /* Expression: Fz_curve
   * Referenced by: '<Root>/Constant5'
   */
  real_T Constant5_Value[200];

  /* Expression: pid_kp_lat
   * Referenced by: '<Root>/Constant7'
   */
  real_T Constant7_Value[3];

  /* Expression: pid_ki_lat
   * Referenced by: '<Root>/Constant8'
   */
  real_T Constant8_Value[3];

  /* Expression: pid_kd_lat
   * Referenced by: '<Root>/Constant9'
   */
  real_T Constant9_Value[3];

  /* Expression: diag([0.1, 0.1])
   * Referenced by: '<S17>/Q'
   */
  real_T Q_Value[4];

  /* Pooled Parameter (Expression: )
   * Referenced by:
   *   '<S14>/2-D Lookup Table'
   *   '<S14>/2-D Lookup Table1'
   *   '<S14>/2-D Lookup Table2'
   *   '<S14>/2-D Lookup Table3'
   */
  real_T pooled16[19];

  /* Pooled Parameter (Expression: [225:50:1125])
   * Referenced by:
   *   '<S14>/2-D Lookup Table'
   *   '<S14>/2-D Lookup Table1'
   *   '<S14>/2-D Lookup Table2'
   *   '<S14>/2-D Lookup Table3'
   */
  real_T pooled17[31];

  /* Pooled Parameter (Expression: [-15:1:15])
   * Referenced by:
   *   '<S14>/2-D Lookup Table'
   *   '<S14>/2-D Lookup Table1'
   *   '<S14>/2-D Lookup Table2'
   *   '<S14>/2-D Lookup Table3'
   */
  uint32_T pooled18[2];
} ConstP_ControlsMFE25_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T ResetSignal;                  /* '<Root>/ResetSignal' */
  real_T vehicle_speed;                /* '<Root>/vehicle_speed' */
  real_T min_speed;                    /* '<Root>/min_speed' */
  real_T P_max;                        /* '<Root>/P_max' */
  real_T lamda1;                       /* '<Root>/lamda1' */
  real_T lamda2;                       /* '<Root>/lamda2' */
  real_T lamda3;                       /* '<Root>/lamda3' */
  real_T om_fl;                        /* '<Root>/om_fl' */
  real_T om_fr;                        /* '<Root>/om_fr' */
  real_T om_rl;                        /* '<Root>/om_rl' */
  real_T om_rr;                        /* '<Root>/om_rr' */
  real_T efficiency;                   /* '<Root>/efficiency' */
  real_T N_long;                       /* '<Root>/N_long' */
  real_T ax;                           /* '<Root>/ax' */
  real_T SWA;                          /* '<Root>/SWA' */
  real_T vy;                           /* '<Root>/vy' */
  real_T yaw_rate;                     /* '<Root>/yaw_rate' */
  real_T rThrottlePedal;               /* '<Root>/rThrottlePedal' */
  real_T BRegenEnabledButton;          /* '<Root>/BRegenEnabledButton' */
  real_T T_i_max;                      /* '<Root>/T_i_max' */
  real_T R_max;                        /* '<Root>/R_max' */
  real_T yrr_scaling;                  /* '<Root>/yrr_scaling' */
  real_T Fz_gain;                      /* '<Root>/Fz_gain' */
  real_T ay;                           /* '<Root>/ay' */
  real_T use_imu_vel_x;                /* '<Root>/use_imu_vel_x' */
  real_T use_imu_vel_y;                /* '<Root>/use_imu_vel_y' */
  real_T use_pushrod_loadcells;        /* '<Root>/use_pushrod_loadcells' */
  real_T fz_fl;                        /* '<Root>/fz_fl' */
  real_T fz_fr;                        /* '<Root>/fz_fr' */
  real_T fz_rl;                        /* '<Root>/fz_rl' */
  real_T fz_rr;                        /* '<Root>/fz_rr' */
  real_T slip_ref_scaling;             /* '<Root>/slip_ref_scaling' */
} ExtU_ControlsMFE25_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T tau1;                         /* '<Root>/tau1' */
  real_T tau2;                         /* '<Root>/tau2' */
  real_T tau3;                         /* '<Root>/tau3' */
  real_T tau4;                         /* '<Root>/tau4' */
  real_T wheelA_filtered;              /* '<Root>/wheelA_filtered' */
  real_T wheelA;                       /* '<Root>/wheelA' */
  real_T kalman_vx;                    /* '<Root>/kalman_vx' */
  real_T kalman_vy;                    /* '<Root>/kalman_vy' */
  real_T yaw_rate_ref;                 /* '<Root>/yaw_rate_ref' */
  real_T Mz_FF;                        /* '<Root>/Mz_FF' */
  real_T Mz_PID;                       /* '<Root>/Mz_PID' */
  real_T Mz_Target;                    /* '<Root>/Mz_Target' */
  real_T Pmech;                        /* '<Root>/Pmech' */
  real_T Pelect_estimated;             /* '<Root>/Pelect_estimated' */
  real_T fz_calc_fl;                   /* '<Root>/fz_calc_fl' */
  real_T fz_calc_fr;                   /* '<Root>/fz_calc_fr' */
  real_T fz_calc_rl;                   /* '<Root>/fz_calc_rl' */
  real_T fz_calc_rr;                   /* '<Root>/fz_calc_rr' */
  real_T msr_ref_fl;                   /* '<Root>/msr_ref_fl' */
  real_T msr_ref_fr;                   /* '<Root>/msr_ref_fr' */
  real_T msr_ref_rl;                   /* '<Root>/msr_ref_rl' */
  real_T msr_ref_rr;                   /* '<Root>/msr_ref_rr' */
  real_T msr_actual_fl;                /* '<Root>/msr_actual_fl' */
  real_T msr_actual_fr;                /* '<Root>/msr_actual_fr' */
  real_T msr_actual_rl;                /* '<Root>/msr_actual_rl' */
  real_T msr_actual_rr;                /* '<Root>/msr_actual_rr' */
  real_T Long_FF_fl;                   /* '<Root>/Long_FF_fl' */
  real_T Long_FF_fr;                   /* '<Root>/Long_FF_fr' */
  real_T Long_FF_rl;                   /* '<Root>/Long_FF_rl' */
  real_T Long_FF_rr;                   /* '<Root>/Long_FF_rr' */
  real_T Long_PID_fl;                  /* '<Root>/Long_PID_fl' */
  real_T Long_PID_fr;                  /* '<Root>/Long_PID_fr' */
  real_T Long_PID_rl;                  /* '<Root>/Long_PID_rl' */
  real_T Long_PID_rr;                  /* '<Root>/Long_PID_rr' */
} ExtY_ControlsMFE25_T;

/* Real-time Model Data Structure */
struct tag_RTM_ControlsMFE25_T {
  const char_T * volatile errorStatus;
  B_ControlsMFE25_T *blockIO;
  ExtU_ControlsMFE25_T *inputs;
  ExtY_ControlsMFE25_T *outputs;
  DW_ControlsMFE25_T *dwork;
};

/* External data declarations for dependent source files */
extern const char_T *RT_MEMORY_ALLOCATION_ERROR;
extern const ConstB_ControlsMFE25_T ControlsMFE25_ConstB;/* constant block i/o */

/* Constant parameters (default storage) */
extern const ConstP_ControlsMFE25_T ControlsMFE25_ConstP;

/* Model entry point functions */
extern RT_MODEL_ControlsMFE25_T *ControlsMFE25(void);
extern void ControlsMFE25_initialize(RT_MODEL_ControlsMFE25_T *const
  ControlsMFE25_M);
extern void ControlsMFE25_step(RT_MODEL_ControlsMFE25_T *const ControlsMFE25_M);
extern void ControlsMFE25_terminate(RT_MODEL_ControlsMFE25_T * ControlsMFE25_M);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<Root>/Constant14' : Unused code path elimination
 * Block '<S66>/Data Type Duplicate' : Unused code path elimination
 * Block '<S66>/Data Type Propagation' : Unused code path elimination
 * Block '<S128>/Data Type Duplicate' : Unused code path elimination
 * Block '<S128>/Data Type Propagation' : Unused code path elimination
 * Block '<S184>/Data Type Duplicate' : Unused code path elimination
 * Block '<S184>/Data Type Propagation' : Unused code path elimination
 * Block '<S240>/Data Type Duplicate' : Unused code path elimination
 * Block '<S240>/Data Type Propagation' : Unused code path elimination
 * Block '<S296>/Data Type Duplicate' : Unused code path elimination
 * Block '<S296>/Data Type Propagation' : Unused code path elimination
 * Block '<S9>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S315>/Data Type Duplicate' : Unused code path elimination
 * Block '<S315>/Data Type Propagation' : Unused code path elimination
 * Block '<S12>/Data Type Duplicate' : Unused code path elimination
 * Block '<S12>/Data Type Propagation' : Unused code path elimination
 * Block '<S13>/Data Type Duplicate' : Unused code path elimination
 * Block '<S13>/Data Type Propagation' : Unused code path elimination
 * Block '<S320>/Gain' : Unused code path elimination
 * Block '<S318>/Saturation' : Unused code path elimination
 * Block '<S18>/Constant' : Unused code path elimination
 * Block '<S1>/Gain1' : Eliminated nontunable gain of 1
 * Block '<S1>/Gain2' : Eliminated nontunable gain of 1
 * Block '<S313>/Saturation' : Eliminated Saturate block
 * Block '<S4>/K' : Eliminated nontunable gain of 1
 * Block '<S9>/Zero-Order Hold' : Eliminated since input and output rates are identical
 * Block '<S15>/Delay' : Eliminated Zero Delay block after compile
 * Block '<S16>/Add' : Unused code path elimination
 * Block '<S16>/Add1' : Unused code path elimination
 * Block '<S16>/Constant' : Unused code path elimination
 * Block '<S16>/Gain' : Unused code path elimination
 * Block '<S16>/Gain1' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'ControlsMFE25'
 * '<S1>'   : 'ControlsMFE25/Subsystem Reference'
 * '<S2>'   : 'ControlsMFE25/Subsystem Reference/Feedback Lat'
 * '<S3>'   : 'ControlsMFE25/Subsystem Reference/Feedback Long'
 * '<S4>'   : 'ControlsMFE25/Subsystem Reference/Low-Pass Filter (Discrete or Continuous)'
 * '<S5>'   : 'ControlsMFE25/Subsystem Reference/MATLAB Function2'
 * '<S6>'   : 'ControlsMFE25/Subsystem Reference/MATLAB Function3'
 * '<S7>'   : 'ControlsMFE25/Subsystem Reference/MOLLS'
 * '<S8>'   : 'ControlsMFE25/Subsystem Reference/Pedal Mapping'
 * '<S9>'   : 'ControlsMFE25/Subsystem Reference/Rate Limiter Dynamic'
 * '<S10>'  : 'ControlsMFE25/Subsystem Reference/Reference Generator and FeedForward Long'
 * '<S11>'  : 'ControlsMFE25/Subsystem Reference/Reference and FF Lat'
 * '<S12>'  : 'ControlsMFE25/Subsystem Reference/Saturation Dynamic'
 * '<S13>'  : 'ControlsMFE25/Subsystem Reference/Saturation Dynamic4'
 * '<S14>'  : 'ControlsMFE25/Subsystem Reference/Subsystem'
 * '<S15>'  : 'ControlsMFE25/Subsystem Reference/Subsystem Reference'
 * '<S16>'  : 'ControlsMFE25/Subsystem Reference/Subsystem1'
 * '<S17>'  : 'ControlsMFE25/Subsystem Reference/Tuned Kalman Filter Values'
 * '<S18>'  : 'ControlsMFE25/Subsystem Reference/fz safety check'
 * '<S19>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1'
 * '<S20>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/Subsystem'
 * '<S21>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/Anti-windup'
 * '<S22>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/D Gain'
 * '<S23>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/External Derivative'
 * '<S24>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/Filter'
 * '<S25>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/Filter ICs'
 * '<S26>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/I Gain'
 * '<S27>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/Ideal P Gain'
 * '<S28>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/Ideal P Gain Fdbk'
 * '<S29>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/Integrator'
 * '<S30>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/Integrator ICs'
 * '<S31>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/N Copy'
 * '<S32>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/N Gain'
 * '<S33>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/P Copy'
 * '<S34>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/Parallel P Gain'
 * '<S35>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/Reset Signal'
 * '<S36>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/Saturation'
 * '<S37>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/Saturation Fdbk'
 * '<S38>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/Sum'
 * '<S39>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/Sum Fdbk'
 * '<S40>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/Tracking Mode'
 * '<S41>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/Tracking Mode Sum'
 * '<S42>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/Tsamp - Integral'
 * '<S43>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/Tsamp - Ngain'
 * '<S44>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/postSat Signal'
 * '<S45>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/preInt Signal'
 * '<S46>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/preSat Signal'
 * '<S47>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/Anti-windup/Disc. Clamping Parallel'
 * '<S48>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S49>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/Anti-windup/Disc. Clamping Parallel/Dead Zone/External'
 * '<S50>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/Anti-windup/Disc. Clamping Parallel/Dead Zone/External/Dead Zone Dynamic'
 * '<S51>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/D Gain/External Parameters'
 * '<S52>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/External Derivative/Error'
 * '<S53>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/Filter/Disc. Forward Euler Filter'
 * '<S54>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/Filter ICs/Internal IC - Filter'
 * '<S55>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/I Gain/External Parameters'
 * '<S56>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/Ideal P Gain/Passthrough'
 * '<S57>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/Ideal P Gain Fdbk/Passthrough'
 * '<S58>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/Integrator/Discrete'
 * '<S59>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/Integrator ICs/Internal IC'
 * '<S60>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/N Copy/Disabled'
 * '<S61>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/N Gain/External Parameters'
 * '<S62>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/P Copy/Disabled'
 * '<S63>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/Parallel P Gain/External Parameters'
 * '<S64>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/Reset Signal/External Reset'
 * '<S65>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/Saturation/External'
 * '<S66>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/Saturation/External/Saturation Dynamic'
 * '<S67>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/Saturation Fdbk/Passthrough'
 * '<S68>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/Sum/Sum_PID'
 * '<S69>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/Sum Fdbk/Enabled'
 * '<S70>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/Tracking Mode/Disabled'
 * '<S71>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/Tracking Mode Sum/Passthrough'
 * '<S72>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/Tsamp - Integral/TsSignalSpecification'
 * '<S73>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/Tsamp - Ngain/Passthrough'
 * '<S74>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/postSat Signal/Feedback_Path'
 * '<S75>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/preInt Signal/Internal PreInt'
 * '<S76>'  : 'ControlsMFE25/Subsystem Reference/Feedback Lat/PID 1/preSat Signal/Feedback_Path'
 * '<S77>'  : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID'
 * '<S78>'  : 'ControlsMFE25/Subsystem Reference/Feedback Long/Subsystem'
 * '<S79>'  : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1'
 * '<S80>'  : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2'
 * '<S81>'  : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3'
 * '<S82>'  : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4'
 * '<S83>'  : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/Anti-windup'
 * '<S84>'  : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/D Gain'
 * '<S85>'  : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/External Derivative'
 * '<S86>'  : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/Filter'
 * '<S87>'  : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/Filter ICs'
 * '<S88>'  : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/I Gain'
 * '<S89>'  : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/Ideal P Gain'
 * '<S90>'  : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/Ideal P Gain Fdbk'
 * '<S91>'  : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/Integrator'
 * '<S92>'  : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/Integrator ICs'
 * '<S93>'  : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/N Copy'
 * '<S94>'  : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/N Gain'
 * '<S95>'  : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/P Copy'
 * '<S96>'  : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/Parallel P Gain'
 * '<S97>'  : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/Reset Signal'
 * '<S98>'  : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/Saturation'
 * '<S99>'  : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/Saturation Fdbk'
 * '<S100>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/Sum'
 * '<S101>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/Sum Fdbk'
 * '<S102>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/Tracking Mode'
 * '<S103>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/Tracking Mode Sum'
 * '<S104>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/Tsamp - Integral'
 * '<S105>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/Tsamp - Ngain'
 * '<S106>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/postSat Signal'
 * '<S107>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/preInt Signal'
 * '<S108>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/preSat Signal'
 * '<S109>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/Anti-windup/Disc. Clamping Parallel'
 * '<S110>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S111>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/Anti-windup/Disc. Clamping Parallel/Dead Zone/External'
 * '<S112>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/Anti-windup/Disc. Clamping Parallel/Dead Zone/External/Dead Zone Dynamic'
 * '<S113>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/D Gain/External Parameters'
 * '<S114>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/External Derivative/Error'
 * '<S115>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/Filter/Disc. Forward Euler Filter'
 * '<S116>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/Filter ICs/Internal IC - Filter'
 * '<S117>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/I Gain/External Parameters'
 * '<S118>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/Ideal P Gain/Passthrough'
 * '<S119>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/Ideal P Gain Fdbk/Passthrough'
 * '<S120>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/Integrator/Discrete'
 * '<S121>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/Integrator ICs/Internal IC'
 * '<S122>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/N Copy/Disabled'
 * '<S123>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/N Gain/External Parameters'
 * '<S124>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/P Copy/Disabled'
 * '<S125>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/Parallel P Gain/External Parameters'
 * '<S126>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/Reset Signal/External Reset'
 * '<S127>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/Saturation/External'
 * '<S128>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/Saturation/External/Saturation Dynamic'
 * '<S129>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/Saturation Fdbk/Passthrough'
 * '<S130>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/Sum/Sum_PID'
 * '<S131>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/Sum Fdbk/Enabled'
 * '<S132>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/Tracking Mode/Disabled'
 * '<S133>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/Tracking Mode Sum/Passthrough'
 * '<S134>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/Tsamp - Integral/TsSignalSpecification'
 * '<S135>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/Tsamp - Ngain/Passthrough'
 * '<S136>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/postSat Signal/Feedback_Path'
 * '<S137>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/preInt Signal/Internal PreInt'
 * '<S138>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 1/preSat Signal/Feedback_Path'
 * '<S139>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/Anti-windup'
 * '<S140>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/D Gain'
 * '<S141>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/External Derivative'
 * '<S142>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/Filter'
 * '<S143>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/Filter ICs'
 * '<S144>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/I Gain'
 * '<S145>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/Ideal P Gain'
 * '<S146>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/Ideal P Gain Fdbk'
 * '<S147>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/Integrator'
 * '<S148>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/Integrator ICs'
 * '<S149>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/N Copy'
 * '<S150>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/N Gain'
 * '<S151>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/P Copy'
 * '<S152>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/Parallel P Gain'
 * '<S153>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/Reset Signal'
 * '<S154>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/Saturation'
 * '<S155>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/Saturation Fdbk'
 * '<S156>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/Sum'
 * '<S157>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/Sum Fdbk'
 * '<S158>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/Tracking Mode'
 * '<S159>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/Tracking Mode Sum'
 * '<S160>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/Tsamp - Integral'
 * '<S161>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/Tsamp - Ngain'
 * '<S162>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/postSat Signal'
 * '<S163>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/preInt Signal'
 * '<S164>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/preSat Signal'
 * '<S165>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/Anti-windup/Disc. Clamping Parallel'
 * '<S166>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S167>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/Anti-windup/Disc. Clamping Parallel/Dead Zone/External'
 * '<S168>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/Anti-windup/Disc. Clamping Parallel/Dead Zone/External/Dead Zone Dynamic'
 * '<S169>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/D Gain/External Parameters'
 * '<S170>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/External Derivative/Error'
 * '<S171>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/Filter/Disc. Forward Euler Filter'
 * '<S172>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/Filter ICs/Internal IC - Filter'
 * '<S173>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/I Gain/External Parameters'
 * '<S174>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/Ideal P Gain/Passthrough'
 * '<S175>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/Ideal P Gain Fdbk/Passthrough'
 * '<S176>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/Integrator/Discrete'
 * '<S177>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/Integrator ICs/Internal IC'
 * '<S178>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/N Copy/Disabled'
 * '<S179>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/N Gain/External Parameters'
 * '<S180>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/P Copy/Disabled'
 * '<S181>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/Parallel P Gain/External Parameters'
 * '<S182>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/Reset Signal/External Reset'
 * '<S183>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/Saturation/External'
 * '<S184>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/Saturation/External/Saturation Dynamic'
 * '<S185>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/Saturation Fdbk/Passthrough'
 * '<S186>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/Sum/Sum_PID'
 * '<S187>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/Sum Fdbk/Enabled'
 * '<S188>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/Tracking Mode/Disabled'
 * '<S189>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/Tracking Mode Sum/Passthrough'
 * '<S190>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/Tsamp - Integral/TsSignalSpecification'
 * '<S191>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/Tsamp - Ngain/Passthrough'
 * '<S192>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/postSat Signal/Feedback_Path'
 * '<S193>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/preInt Signal/Internal PreInt'
 * '<S194>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 2/preSat Signal/Feedback_Path'
 * '<S195>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/Anti-windup'
 * '<S196>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/D Gain'
 * '<S197>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/External Derivative'
 * '<S198>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/Filter'
 * '<S199>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/Filter ICs'
 * '<S200>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/I Gain'
 * '<S201>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/Ideal P Gain'
 * '<S202>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/Ideal P Gain Fdbk'
 * '<S203>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/Integrator'
 * '<S204>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/Integrator ICs'
 * '<S205>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/N Copy'
 * '<S206>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/N Gain'
 * '<S207>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/P Copy'
 * '<S208>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/Parallel P Gain'
 * '<S209>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/Reset Signal'
 * '<S210>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/Saturation'
 * '<S211>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/Saturation Fdbk'
 * '<S212>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/Sum'
 * '<S213>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/Sum Fdbk'
 * '<S214>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/Tracking Mode'
 * '<S215>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/Tracking Mode Sum'
 * '<S216>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/Tsamp - Integral'
 * '<S217>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/Tsamp - Ngain'
 * '<S218>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/postSat Signal'
 * '<S219>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/preInt Signal'
 * '<S220>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/preSat Signal'
 * '<S221>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/Anti-windup/Disc. Clamping Parallel'
 * '<S222>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S223>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/Anti-windup/Disc. Clamping Parallel/Dead Zone/External'
 * '<S224>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/Anti-windup/Disc. Clamping Parallel/Dead Zone/External/Dead Zone Dynamic'
 * '<S225>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/D Gain/External Parameters'
 * '<S226>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/External Derivative/Error'
 * '<S227>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/Filter/Disc. Forward Euler Filter'
 * '<S228>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/Filter ICs/Internal IC - Filter'
 * '<S229>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/I Gain/External Parameters'
 * '<S230>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/Ideal P Gain/Passthrough'
 * '<S231>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/Ideal P Gain Fdbk/Passthrough'
 * '<S232>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/Integrator/Discrete'
 * '<S233>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/Integrator ICs/Internal IC'
 * '<S234>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/N Copy/Disabled'
 * '<S235>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/N Gain/External Parameters'
 * '<S236>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/P Copy/Disabled'
 * '<S237>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/Parallel P Gain/External Parameters'
 * '<S238>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/Reset Signal/External Reset'
 * '<S239>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/Saturation/External'
 * '<S240>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/Saturation/External/Saturation Dynamic'
 * '<S241>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/Saturation Fdbk/Passthrough'
 * '<S242>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/Sum/Sum_PID'
 * '<S243>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/Sum Fdbk/Enabled'
 * '<S244>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/Tracking Mode/Disabled'
 * '<S245>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/Tracking Mode Sum/Passthrough'
 * '<S246>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/Tsamp - Integral/TsSignalSpecification'
 * '<S247>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/Tsamp - Ngain/Passthrough'
 * '<S248>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/postSat Signal/Feedback_Path'
 * '<S249>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/preInt Signal/Internal PreInt'
 * '<S250>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 3/preSat Signal/Feedback_Path'
 * '<S251>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/Anti-windup'
 * '<S252>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/D Gain'
 * '<S253>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/External Derivative'
 * '<S254>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/Filter'
 * '<S255>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/Filter ICs'
 * '<S256>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/I Gain'
 * '<S257>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/Ideal P Gain'
 * '<S258>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/Ideal P Gain Fdbk'
 * '<S259>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/Integrator'
 * '<S260>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/Integrator ICs'
 * '<S261>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/N Copy'
 * '<S262>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/N Gain'
 * '<S263>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/P Copy'
 * '<S264>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/Parallel P Gain'
 * '<S265>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/Reset Signal'
 * '<S266>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/Saturation'
 * '<S267>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/Saturation Fdbk'
 * '<S268>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/Sum'
 * '<S269>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/Sum Fdbk'
 * '<S270>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/Tracking Mode'
 * '<S271>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/Tracking Mode Sum'
 * '<S272>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/Tsamp - Integral'
 * '<S273>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/Tsamp - Ngain'
 * '<S274>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/postSat Signal'
 * '<S275>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/preInt Signal'
 * '<S276>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/preSat Signal'
 * '<S277>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/Anti-windup/Disc. Clamping Parallel'
 * '<S278>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S279>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/Anti-windup/Disc. Clamping Parallel/Dead Zone/External'
 * '<S280>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/Anti-windup/Disc. Clamping Parallel/Dead Zone/External/Dead Zone Dynamic'
 * '<S281>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/D Gain/External Parameters'
 * '<S282>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/External Derivative/Error'
 * '<S283>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/Filter/Disc. Forward Euler Filter'
 * '<S284>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/Filter ICs/Internal IC - Filter'
 * '<S285>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/I Gain/External Parameters'
 * '<S286>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/Ideal P Gain/Passthrough'
 * '<S287>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/Ideal P Gain Fdbk/Passthrough'
 * '<S288>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/Integrator/Discrete'
 * '<S289>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/Integrator ICs/Internal IC'
 * '<S290>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/N Copy/Disabled'
 * '<S291>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/N Gain/External Parameters'
 * '<S292>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/P Copy/Disabled'
 * '<S293>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/Parallel P Gain/External Parameters'
 * '<S294>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/Reset Signal/External Reset'
 * '<S295>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/Saturation/External'
 * '<S296>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/Saturation/External/Saturation Dynamic'
 * '<S297>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/Saturation Fdbk/Passthrough'
 * '<S298>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/Sum/Sum_PID'
 * '<S299>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/Sum Fdbk/Enabled'
 * '<S300>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/Tracking Mode/Disabled'
 * '<S301>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/Tracking Mode Sum/Passthrough'
 * '<S302>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/Tsamp - Integral/TsSignalSpecification'
 * '<S303>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/Tsamp - Ngain/Passthrough'
 * '<S304>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/postSat Signal/Feedback_Path'
 * '<S305>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/preInt Signal/Internal PreInt'
 * '<S306>' : 'ControlsMFE25/Subsystem Reference/Feedback Long/PID/PID 4/preSat Signal/Feedback_Path'
 * '<S307>' : 'ControlsMFE25/Subsystem Reference/Low-Pass Filter (Discrete or Continuous)/Enable//disable time constant'
 * '<S308>' : 'ControlsMFE25/Subsystem Reference/Low-Pass Filter (Discrete or Continuous)/Initialization'
 * '<S309>' : 'ControlsMFE25/Subsystem Reference/Low-Pass Filter (Discrete or Continuous)/Integrator (Discrete or Continuous)'
 * '<S310>' : 'ControlsMFE25/Subsystem Reference/Low-Pass Filter (Discrete or Continuous)/Enable//disable time constant/Compare To Constant'
 * '<S311>' : 'ControlsMFE25/Subsystem Reference/Low-Pass Filter (Discrete or Continuous)/Enable//disable time constant/Compare To Zero'
 * '<S312>' : 'ControlsMFE25/Subsystem Reference/Low-Pass Filter (Discrete or Continuous)/Initialization/Init_u'
 * '<S313>' : 'ControlsMFE25/Subsystem Reference/Low-Pass Filter (Discrete or Continuous)/Integrator (Discrete or Continuous)/Discrete'
 * '<S314>' : 'ControlsMFE25/Subsystem Reference/MOLLS/Torque Allocation QP Normalized'
 * '<S315>' : 'ControlsMFE25/Subsystem Reference/Rate Limiter Dynamic/Saturation Dynamic'
 * '<S316>' : 'ControlsMFE25/Subsystem Reference/Reference and FF Lat/MATLAB Function'
 * '<S317>' : 'ControlsMFE25/Subsystem Reference/Reference and FF Lat/Subsystem'
 * '<S318>' : 'ControlsMFE25/Subsystem Reference/Subsystem/slip angles'
 * '<S319>' : 'ControlsMFE25/Subsystem Reference/Subsystem/slip angles/MATLAB Function'
 * '<S320>' : 'ControlsMFE25/Subsystem Reference/Subsystem/slip angles/Radians to Degrees'
 * '<S321>' : 'ControlsMFE25/Subsystem Reference/Subsystem Reference/MATLAB Function1'
 * '<S322>' : 'ControlsMFE25/Subsystem Reference/Subsystem Reference/MATLAB Function2'
 */
#endif                                 /* ControlsMFE25_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
