/** @file dnp3_endian.h
 *
 * @brief
 * Endian handling header file
 *
 * @details
 * Contains macro definitions for converting DNP3 frame bytes to base types
 *
 * @copyright
 * Copyright 2019-2020 JPEmbedded.
 * This software is protected Intellectual Property and may only be used
 * according to the licence agreement.
 *
 * @author Michal Lewicki
 */

#ifndef STACK_INCLUDE_DNP3_ENDIAN_H_
#define STACK_INCLUDE_DNP3_ENDIAN_H_

#include "Basetypes.h"

/** This macro is used to retrieve a 16 bit number from a dnp3 protocol frame */
#define DNP_NTOH16(p_in)          (((p_in)[1] << 8) | ((p_in)[0]))
/** This macro is used to put a 16 bit number into a dnp3 protocol frame */
#define DNP_HTON16(p_Dest, v)     {(p_Dest)[1] = ((v) >> 8); (p_Dest)[0] = ((v) & 0xFF);}

/** This macro is used to retrieve a 32 bit number from a dnp3 protocol frame */
#define DNP_NTOH32(p_in)          (((p_in)[3] << 24) | ((p_in)[2] << 16) | ((p_in)[1] << 8) | ((p_in)[0]))
/** This macro is used to put a 32 bit number into a dnp3 protocol frame */
#define DNP_HTON32(p_Dest, v)     {(p_Dest)[3] = ((v) >> 24); (p_Dest)[2] = ((v) >> 16); (p_Dest)[1] = ((v) >> 8); (p_Dest)[0] = ((v) & 0xFF);}

/** This macro is used to retrieve a 48 bit number from a dnp3 protocol frame */
#define DNP_NTOH48(p_in)          ((int64u((p_in)[5]) << 40) | (int64u((p_in)[4]) << 32) | \
                                   (int64u((p_in)[3]) << 24) | (int64u((p_in)[2]) << 16) | (int64u((p_in)[1]) << 8) | ((p_in)[0]))

/** This macro is used to put a 48 bit number into a dnp3 protocol frame */
#define DNP_HTON48(p_Dest, v)     {(p_Dest)[5] = ((v) >> 40); (p_Dest)[4] = ((v) >> 32); (p_Dest)[3] = ((v) >> 24); (p_Dest)[2] = ((v) >> 16); (p_Dest)[1] = ((v) >> 8); (p_Dest)[0] = ((v) & 0xFF);}

/** This macro is used to retrieve a 64 bit number from a dnp3 protocol frame */
#define DNP_NTOH64(p_in)          _net2double(p_in)
                                   
/** This macro is used to put a 64 bit number into a dnp3 protocol frame */
#define DNP_HTON64(p_Dest, v)     _double2hex(v, p_Dest)

#if 1
static inline double64 _net2double(int8u *p)  {
  double64  d;
  memcpy(&d, p, sizeof(double64));
  return d;
}

static inline void _double2hex(double64 d, int8u *p)  {
  memcpy(p, &d, sizeof(double64));
}

static inline float32 _net2float(int8u *p)  {
  float32  f;
  memcpy(&f, p, sizeof(float32));
  return f;
}

static inline void _float2hex(float32 f, int8u *p)  {
  memcpy(p, &f, sizeof(float32));
}
#else
static inline double64 _net2double(int8u *p)  {
  double64  d;
  double64  *p_d = &d;
  
  for (int8u i = 0; i < sizeof(double64); i++) {
    p_d[i] = p[sizeof(double64) - 1 - i];
  }
  return d;
}

static inline void _double2hex(double64 d, int8u *p)  {
  double64  *p_d = &d;
  
  for (int8u i = 0; i < sizeof(double64); i++) {
    p[i] = p_d[sizeof(double64) - 1 - i];
  }
}

static inline float32 _net2float(int8u *p)  {
  float32   f;
  float32  *p_f = &f;
  
  for (int8u i = 0; i < sizeof(float32); i++) {
    p_f[i] = p[sizeof(float32) - 1 - i];
  }
  return f;
}

static inline void _float2hex(float32 f, int8u *p)  {
  float32  *p_f = &f;
  
  for (int8u i = 0; i < sizeof(float32); i++) {
    p[i] = p_f[sizeof(float32) - 1 - i];
  }
}
#endif

#endif /* STACK_INCLUDE_DNP3_ENDIAN_H_ */
