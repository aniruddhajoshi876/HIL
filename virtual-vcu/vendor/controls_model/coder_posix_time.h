/* Timing API emitted by MATLAB Coder for the ControlsMFE25 tic/toc calls.
 * The .c is a deliberate no-op stub: the generated model discards the toc
 * return and nothing else reads the timekeeper state -- see coder_posix_time.c
 * and docs/controls_branch_sync.md item 5. */

#ifndef CODER_POSIX_TIME_H
#define CODER_POSIX_TIME_H

#include "rtwtypes.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  real_T tv_sec;
  real_T tv_nsec;
} coderTimespec;

void coderInitTimeFunctions(real_T *freq);
void coderTimeClockGettimeMonotonic(coderTimespec *timespec, real_T freq);

#ifdef __cplusplus
}
#endif

#endif
