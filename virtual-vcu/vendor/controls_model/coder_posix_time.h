/* Portable implementation of the timing API emitted by MATLAB Coder. */

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
