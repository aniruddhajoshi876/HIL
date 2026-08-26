/** @file platform.h 
 *
 * @brief
 * Platform specific macro-definitions
 *
 * @details
 * This file is specific for the hardware target platform. It contains the definitions of macros used to convert generic numeric types
 *
 * @copyright
 * Copyright 2014-2099 JPEmbedded.
 * This software is protected Intellectual Property and may only be used
 * according to the licence agreement.
 *
 * @author Jan Mazan
 */

#if !defined(_PLATFORM__INCLUDED_)
#define _PLATFORM__INCLUDED_

#include "hal_types.h"
#include <string.h>

/** This macro is used to retrieve a 16 bit number form a protocol frame */
#define NTOH16(p_Dest)	        (((p_Dest)[0] << 8) | ((p_Dest)[1]))
#define HTON16(p_Dest, v)	    {(p_Dest)[0] = ((v) >> 8); (p_Dest)[1] = ((v) & 0xFF);}

/** This macro is used to retrieve a 24 bit number form a protocol frame */
#define NTOH24(p_Dest)	        (((p_Dest)[0] << 16) | ((p_Dest)[1] << 8) | ((p_Dest)[2]))
#define HTON24(p_Dest, v)	    {(p_Dest)[0] = ((v) >> 16); (p_Dest)[1] = ((v) >> 8); (p_Dest)[2] = ((v) & 0xFF);}

/** This macro is used to retrieve a 32 bit number form a protocol frame */
#define NTOH32(p_Dest)	        (((p_Dest)[0] << 24) | ((p_Dest)[1] << 16) | ((p_Dest)[2] << 8) | ((p_Dest)[3]))
#define HTON32(p_Dest, v)	    {(p_Dest)[0] = ((v) >> 24); (p_Dest)[1] = ((v) >> 16); (p_Dest)[2] = ((v) >> 8); (p_Dest)[3] = ((v) & 0xFF);}

/** This macro is used to retrieve a 64 bit number form a protocol frame */
#define NTOH64(p_Dest)	        ((((int64)(p_Dest)[0]) << 56) | (((int64)(p_Dest)[1]) << 48) | (((int64)(p_Dest)[2]) << 40) | (((int64)(p_Dest)[3]) << 32) | (((int64)(p_Dest)[4]) << 24) | (((int64)(p_Dest)[5])<< 16) | (((int64)(p_Dest)[6])<< 8) | (((int64)(p_Dest)[7])))
#define HTON64(p_Dest, v)	    {(p_Dest)[0] = ((v) >> 56); (p_Dest)[1] = ((v) >> 48); (p_Dest)[2] = ((v) >> 40); (p_Dest)[3] = ((v) >> 32); (p_Dest)[4] = ((v) >> 24); (p_Dest)[5] = ((v) >> 16); (p_Dest)[6] = ((v) >> 8); (p_Dest)[7] = ((v) & 0xFF);}

#define BE32(p)                 (int32u)(((p)[0] << 24) | ((p)[1] << 16) | ((p)[2] << 8) | ((p)[3]))
#define LE32(p)                 (int32u)(((p)[3] << 24) | ((p)[2] << 16) | ((p)[1] << 8) | ((p)[0]))
#define SWAP32(v)               ((((v) >> 24) & 0xFF) | (((v) >> 8) & 0xFF00) | (((v) << 8) & 0xFF0000) | (((v) << 24) & 0xFF000000)) 

#ifdef __cplusplus
#define PTR_TO_UINT(p)        reinterpret_cast<uintptr_t>((p))
#else
#define PTR_TO_UINT(p)        (uintptr_t)(p)
#endif

#ifdef __cplusplus
#define PTR_TO_INT(p)         reinterpret_cast<intptr_t>((p))
#else
#define PTR_TO_INT(p)         (intptr_t)(p)
#endif

#define BITSTR_SIZE             10
typedef struct { int32u bits[BITSTR_SIZE]; }  BIT_STRING_T;

#define BITSTR_SET(s1, s2)      { for (int i = 0; i < BITSTR_SIZE; i++) (s1).bits[i] = (s2).bits[i]; }
#define BITSTR_ADD(s1, s2)      { for (int i = 0; i < BITSTR_SIZE; i++) (s1).bits[i] |= (s2).bits[i]; }
#define BITSTR_OFF(s1, s2)      { for (int i = 0; i < BITSTR_SIZE; i++) (s1).bits[i] &= ~((s2).bits[i]); }
#define BITSTR_SETBIT(s, b)     { if ((b) < (32 * BITSTR_SIZE)) (s).bits[(b)/32] |= (1 << ((b) % 32)); }
#define BITSTR_GETBIT(s, b)     ( ((b) < (32 * BITSTR_SIZE)) ? ((s).bits[(b)/32] & (1 << ((b) % 32))) : 0 )
#define BITSTR_CLRBIT(s, b)     { if ((b) < (32 * BITSTR_SIZE)) (s).bits[(b)/32] &= ~((int32u)(1 << ((b) % 32))); }
#define BITSTR_ZERO(s)          { for (int i = 0; i < BITSTR_SIZE; i++) (s).bits[i] = 0; }
#define BITSTR_SETALL(s)        { for (int i = 0; i < BITSTR_SIZE; i++) (s).bits[i] = 0xFFFFFFFF; }
#define BITSTR_VPTR(s)          (int32u*)((s).bits)
inline bool BITSTR_AND(BIT_STRING_T &s1, BIT_STRING_T &s2) {
  for (int i = 0; i < BITSTR_SIZE; i++) {
    if ((s1).bits[i] & (s2).bits[i]) return true;
  }
  return false;
}

#endif // !defined(_PLATFORM__INCLUDED_)
