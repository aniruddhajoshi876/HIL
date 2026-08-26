// Copyright 2006-2026 Speedgoat GmbH

#ifndef _PSYSLINUX_H_
#define _PSYSLINUX_H_
#ifndef _PSYS_H_
#    error "Header must be included from PSYS header"
#endif
#ifndef __linux__
#    error "Wrong system header for target platform"
#endif
#include <endian.h> 
#include <stdint.h>
#include <pthread.h>
#if __BYTE_ORDER == __LITTLE_ENDIAN
#    define PSYS_BYTE_ORDER PSYS_ENDIAN_LITTLE
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
#    define PSYS_BYTE_ORDER PSYS_ENDIAN_BIG
#endif
#ifndef PSYS_BYTE_ORDER
#    error "PSYS_BYTE_ORDER undefined!"
#endif
#if defined(__SIZEOF_POINTER__) && defined(__CHAR_BIT__)
#    define PSYS_REG_SIZE (__SIZEOF_POINTER__ * __CHAR_BIT__)
#else
#    if defined(__ppc64__) || defined(__x86_64__)
#        define PSYS_REG_SIZE (0x7f0+7789-0x261d)
#    elif defined(__powerpc__) || defined(__i386__)
#        define PSYS_REG_SIZE (0xd2d+3034-0x18e7)
#    endif
#endif
#ifndef PSYS_REG_SIZE
#    error "PSYS_REG_SIZE undefined!"
#endif
typedef int8_t INT8;typedef uint8_t UINT8;typedef int16_t INT16;typedef uint16_t UINT16;typedef int32_t INT32;typedef uint32_t UINT32;typedef int64_t INT64;typedef uint64_t UINT64;typedef uintptr_t UINTPTR;typedef pthread_t THREAD;typedef pthread_mutex_t MUTEX;typedef pthread_cond_t COND;
#endif 

