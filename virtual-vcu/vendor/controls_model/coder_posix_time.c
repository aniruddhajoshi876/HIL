/*
 * Timing adapter for the generated ControlsMFE25 tic/toc calls.
 *
 * The controls-branch copy of this file is backed by an STM32 TIM2 peripheral
 * and cannot compile for a Windows MEX file or a Speedgoat (Simulink Real-Time
 * / QNX) target. It is the only platform substitution in the vendored model.
 *
 * DELIBERATE STUB (virtual-vcu controls-sync item 5):
 * The generated ControlsMFE25.c calls ControlsMFE25_tic() once and
 * ControlsMFE25_toc() once per allocator step ("Torque Allocation QP
 * Normalized"). The single toc() call site (ControlsMFE25.c:6806 at controls
 * commit bcd6352) DISCARDS the returned elapsed-time value -- it is not
 * assigned, stored, or fed to any block. The only state these timing
 * functions touch (savedTime on the stack, and DW->freq / DW->freq_not_empty /
 * DW->savedTime_not_empty) is written and read exclusively by the timing
 * functions themselves; nothing in the allocator, the QP driver, or any
 * Outport consumes it. Therefore returning constant zeros here cannot change
 * allocator outputs (tau1..tau4) or state evolution.
 *
 * On a Simulink Real-Time (QNX) target a real monotonic-clock syscall every
 * 5 ms step is pure overhead and a portability risk for a value that is
 * thrown away, so this stub performs no syscall at all.
 *
 * TO RESTORE A REAL TIMER (only needed if a future allocator revision starts
 * consuming the toc() return -- e.g. an adaptive-iteration QP): replace the
 * body of coderTimeClockGettimeMonotonic() with clock_gettime(CLOCK_MONOTONIC,
 * ...) on QNX / a clock() fallback on the host, and set *freq to the tick
 * frequency in coderInitTimeFunctions(). The previous clock()-based
 * implementation is preserved in git history for this file.
 */

#include "coder_posix_time.h"

const char_T *RT_MEMORY_ALLOCATION_ERROR = "memory allocation error";

void coderInitTimeFunctions(real_T *freq)
{
  /* Non-zero so ControlsMFE25_toc()'s internal divide-by-freq stays defined
   * even though its result is discarded. */
  *freq = 1.0;
}

void coderTimeClockGettimeMonotonic(coderTimespec *timespec, real_T freq)
{
  (void)freq;
  timespec->tv_sec = 0.0;
  timespec->tv_nsec = 0.0;
}
