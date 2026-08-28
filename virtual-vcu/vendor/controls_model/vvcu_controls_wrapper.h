#ifndef VVCU_CONTROLS_WRAPPER_H
#define VVCU_CONTROLS_WRAPPER_H

#ifdef __cplusplus
extern "C" {
#endif

#define VVCU_CONTROLS_INPUT_COUNT 32
#define VVCU_CONTROLS_TORQUE_COUNT 4

/* Input order is exactly ExtU_ControlsMFE25_T in ControlsMFE25.h. */
void vvcu_controls_reset(void);
void vvcu_controls_step(const double inputs[VVCU_CONTROLS_INPUT_COUNT],
                        double tau[VVCU_CONTROLS_TORQUE_COUNT]);
void vvcu_controls_terminate(void);

#ifdef __cplusplus
}
#endif

#endif
