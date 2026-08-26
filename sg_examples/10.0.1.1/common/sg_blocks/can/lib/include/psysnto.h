// Copyright 2006-2026 Speedgoat GmbH

#ifndef z6b7f6894b7
#define z6b7f6894b7
#ifndef _PSYS_H_
# error "Header must be included from PSYS header"
#endif
#ifndef __QNXNTO__
# error "Wrong system header for target platform"
#endif
#include <sys/neutrino.h>
#include <sys/netmgr.h>
#include <sys/stat.h>
#include <sys/syspage.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <malloc.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <inttypes.h>
#include <stdarg.h>
#include <syslog.h>
#include <ctype.h>
#include <dirent.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#ifndef NDEBUG
# define z074151ccaa (0xd2d+1279-0x122b)
#endif
#ifdef __LITTLEENDIAN__
#define PSYS_BYTE_ORDER PSYS_ENDIAN_LITTLE
#endif
#ifdef __BIGENDIAN__
#define PSYS_BYTE_ORDER PSYS_ENDIAN_BIG
#endif
#define PSYS_REG_SIZE (0x18d7+3058-0x24a9)
typedef int8_t INT8;typedef uint8_t UINT8;typedef int16_t INT16;typedef uint16_t UINT16;typedef int32_t INT32;typedef uint32_t UINT32;typedef int64_t INT64;typedef uint64_t UINT64;typedef intptr_t zf1af836f20;typedef uintptr_t UINTPTR;typedef int z479f693849;typedef pthread_t THREAD;typedef pthread_mutex_t MUTEX;typedef pthread_cond_t COND;
#endif 

