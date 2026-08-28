#include "vvcu_controls_wrapper.h"
#include "ControlsMFE25.h"

#include <stddef.h>

static RT_MODEL_ControlsMFE25_T *vvcu_model;

static void copy_inputs(ExtU_ControlsMFE25_T *u, const double x[32])
{
  u->ResetSignal = x[0];
  u->vehicle_speed = x[1];
  u->min_speed = x[2];
  u->P_max = x[3];
  u->lamda1 = x[4];
  u->lamda2 = x[5];
  u->lamda3 = x[6];
  u->om_fl = x[7];
  u->om_fr = x[8];
  u->om_rl = x[9];
  u->om_rr = x[10];
  u->efficiency = x[11];
  u->N_long = x[12];
  u->ax = x[13];
  u->SWA = x[14];
  u->vy = x[15];
  u->yaw_rate = x[16];
  u->rThrottlePedal = x[17];
  u->BRegenEnabledButton = x[18];
  u->T_i_max = x[19];
  u->R_max = x[20];
  u->yrr_scaling = x[21];
  u->Fz_gain = x[22];
  u->ay = x[23];
  u->use_imu_vel_x = x[24];
  u->use_imu_vel_y = x[25];
  u->use_pushrod_loadcells = x[26];
  u->fz_fl = x[27];
  u->fz_fr = x[28];
  u->fz_rl = x[29];
  u->fz_rr = x[30];
  u->slip_ref_scaling = x[31];
}

static void default_inputs(double x[32])
{
  size_t i;
  for (i = 0; i < 32; ++i) {
    x[i] = 0.0;
  }
  x[2] = 0.5;
  x[3] = 80000.0;
  x[4] = 1.0;
  x[5] = 1.0;
  x[6] = 0.1;
  x[11] = 0.99;
  x[12] = 100.0;
  x[19] = 15.0;
  x[21] = 1.0;
  x[22] = 1.0;
  x[31] = 1.0;
}

void vvcu_controls_terminate(void)
{
  if (vvcu_model != NULL) {
    ControlsMFE25_terminate(vvcu_model);
    vvcu_model = NULL;
  }
}

void vvcu_controls_reset(void)
{
  double x[32];
  ExtU_ControlsMFE25_T *u;

  vvcu_controls_terminate();
  vvcu_model = ControlsMFE25();
  if (vvcu_model == NULL) {
    return;
  }

  ControlsMFE25_initialize(vvcu_model);
  default_inputs(x);
  x[0] = 1.0;
  u = (ExtU_ControlsMFE25_T *)vvcu_model->inputs;
  copy_inputs(u, x);
  ControlsMFE25_step(vvcu_model);
  u->ResetSignal = 0.0;
}

void vvcu_controls_step(const double inputs[32], double tau[4])
{
  ExtU_ControlsMFE25_T *u;
  ExtY_ControlsMFE25_T *y;

  if (vvcu_model == NULL) {
    vvcu_controls_reset();
  }
  if (vvcu_model == NULL) {
    tau[0] = 0.0;
    tau[1] = 0.0;
    tau[2] = 0.0;
    tau[3] = 0.0;
    return;
  }

  u = (ExtU_ControlsMFE25_T *)vvcu_model->inputs;
  copy_inputs(u, inputs);
  ControlsMFE25_step(vvcu_model);
  y = (ExtY_ControlsMFE25_T *)vvcu_model->outputs;
  tau[0] = y->tau1;
  tau[1] = y->tau2;
  tau[2] = y->tau3;
  tau[3] = y->tau4;
}
