/*
 * Portable timing adapter for the generated ControlsMFE25 tic/toc calls.
 *
 * The controls-branch copy is backed by an STM32 TIM2 peripheral and cannot
 * compile for a Windows MEX file or a Speedgoat target. The generated model
 * discards the value returned by toc, so replacing only this platform adapter
 * cannot change allocator outputs or state evolution.
 */

#include "coder_posix_time.h"
#include <time.h>

const char_T *RT_MEMORY_ALLOCATION_ERROR = "memory allocation error";

void coderInitTimeFunctions(real_T *freq)
{
  *freq = (real_T)CLOCKS_PER_SEC;
}

void coderTimeClockGettimeMonotonic(coderTimespec *timespec, real_T freq)
{
  const clock_t ticks = clock();
  const real_T ticksPerSecond = (freq > 0.0) ? freq : (real_T)CLOCKS_PER_SEC;
  const real_T seconds = (real_T)ticks / ticksPerSecond;
  const real_T wholeSeconds = (real_T)((long)seconds);

  timespec->tv_sec = wholeSeconds;
  timespec->tv_nsec = (seconds - wholeSeconds) * 1.0E+9;
}
