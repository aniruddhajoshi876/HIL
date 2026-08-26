// Copyright 2006-2026 Speedgoat GmbH

#pragma once
#ifndef NTCAN_H_
#define NTCAN_H_
#if defined(_MSC_VER) && (_MSC_VER >= (0x196c+3628-0x2220)) && !defined(__BUILDMACHINE__)
# include <intrin.h>
#endif
#ifdef __cplusplus
extern"C"{
#endif
#if defined(_WIN32)
# include <windows.h>
#define NTCAN_BOOL  BOOL
# if defined(__LABVIEW__)
#  include <visa.h>
#  include <ansi_c.h>
#  include <utility.h>
#  undef TRUE   
#  undef FALSE
#  define TRUE  (0x2c5+6649-0x1cbe)
#  define FALSE -(0xc50+4225-0x1cd0)
# endif 
# if defined(__MINGW32__) || (defined(_MSC_VER) && (_MSC_VER >= (0x101f+909-0xca4)))
#  include <stdint.h>      
# endif
# if !defined(EXPORT)
#  define EXPORT __declspec (dllexport)    
# endif
# if !defined(CALLTYPE)
#  define CALLTYPE __cdecl
# endif
# if defined(_MSC_VER) && !defined(NTCAN_NO_AUTOLINK)
#  if defined(UNDER_RTSS)
#   pragma comment(lib,"ntcan_rtss.lib")  /* Import LIB as COFF (32-/64-bit) */
#  elif defined(RTOS32)
#  elif defined(z7f7e6325b2)
#   pragma comment(lib,"ntcan.lib")  /* Import LIB as COFF (32-/64-bit) */
#  else
#   pragma comment(lib,"ntcan.lib")       /* Import LIB as COFF (32-/64-bit) */
#  endif
# elif defined(__BORLANDC__) && !defined(NTCAN_NO_AUTOLINK)
#  if defined(__BORLANDC__) && defined(__clang__)
#   pragma comment(lib,"ntcan")           /* Import LIB as OMF (32-bit) or ELF (64-bit) */
#  else
#   pragma comment(lib,"ntcan.lib")       /* Import LIB as OMF (32-bit) */
#  endif
# endif 
# if !defined(UNDER_RTSS) && !defined(RTOS32) && !defined(__LABVIEW__) && !defined(z7f7e6325b2)
#  if (__GNUC__ >= (0x146a+2906-0x1fbd))   
#   define NTCAN_DLSYM(hnd, name)    (void *)GetProcAddress(hnd, name)
#  else
#   define NTCAN_DLSYM(hnd, name)    GetProcAddress(hnd, name)
#  endif
#  define NTCAN_MAX_TX_QUEUESIZE          16383
#  define NTCAN_MAX_RX_QUEUESIZE          16383
# endif
#elif defined (__QNX__) || defined(__linux__)
# include <errno.h>
# include <stdint.h>
# include <dlfcn.h>
# define NTCAN_BOOL int32_t
# define NTCAN_DLSYM(hnd, name)     dlsym(hnd, name)
#elif defined(__Lynx__)
# include <errno.h>
# include <stdint.h>
#elif defined(__VXWORKS__)
# include <vxWorks.h>
# include <errno.h>
# if defined(_WRS_VXWORKS_MAJOR) && ((_WRS_VXWORKS_MAJOR == (0x8f7+7615-0x26b0)) && (_WRS_VXWORKS_MINOR > (0x731+6988-0x2275)))
#  include <stdint.h>
# endif
# if defined(_WRS_VXWORKS_MAJOR) && (_WRS_VXWORKS_MAJOR > (0xebc+4661-0x20ec))
#  define NTCAN_CLEAN_NAMESPACE
# endif
#elif defined(__FreeBSD__)
# include <stdint.h>
# include <errno.h>
#elif defined (z815d5956d2)
# include <stdint.h>
# include <errno.h>
#else
# error "Unsupported NTCAN platform"
#endif 
#ifndef EXPORT
# define EXPORT
#endif
#ifndef CALLTYPE
# define CALLTYPE
#endif
#if defined(_MSC_VER) && _MSC_VER >= (0x1d11+1863-0x1f44)
# if _MSC_FULL_VER >= 140050320
#  define _NTCAN_DEPRECATE_TEXT(_Text) __declspec(deprecated(_Text))
# else
#  define _NTCAN_DEPRECATE_TEXT(_Text) __declspec(deprecated)
# endif
# ifndef _NTCAN_OBSOLETE
#  define _NTCAN_OBSOLETE(_NewItem) \
         _NTCAN_DEPRECATE_TEXT("\x54\x68\x69\x73\x20\x66\x75\x6e\x63\x74\x69\x6f\x6e\x20\x68\x61\x73\x20\x62\x65\x65\x6e\x20\x73\x75\x70\x65\x72\x63\x65\x64\x65\x64\x20\x62\x79\x20\x6e\x65\x77\x65\x72" \
                               "\x6c\x69\x62\x72\x61\x72\x79\x20\x66\x75\x6e\x63\x74\x69\x6f\x6e\x61\x6c\x69\x74\x79\x2e\x20\x43\x6f\x6e\x73\x69\x64\x65\x72\x20\x75\x73\x69\x6e\x67\x20"     \
                               #_NewItem "\x20\x69\x6e\x73\x74\x65\x61\x64\x2e\x20\x53\x65\x65\x20\x41\x50\x49\x20\x6d\x61\x6e\x75\x61\x6c\x20\x66\x6f\x72\x20\x64\x65\x74\x61\x69\x6c\x73\x2e")
# endif 
#endif 
#if ((__GNUC__ > (0x4e7+4466-0x1657)) || (__GNUC__ > (0x693+748-0x97d)) && (__GNUC_MINOR__ >= (0x19b+1258-0x684)))
# define _NTCAN_GCCATTR_DEPRECATED __attribute__((deprecated))
#endif
#ifdef __clang__
# define _NTCAN_GCCATTR_DEPRECATED __attribute__((deprecated))
#endif
#ifdef _NTCAN_OBSOLETE_NO_WARNINGS
# undef _NTCAN_OBSOLETE
# undef _NTCAN_GCCATTR_DEPRECATED
#endif
#ifndef _NTCAN_OBSOLETE
# define _NTCAN_OBSOLETE(_NewItem)
#endif
#ifndef _NTCAN_GCCATTR_DEPRECATED
# define _NTCAN_GCCATTR_DEPRECATED
#endif
#if defined(_MSC_VER)
# define NTCAN_INLINE static __inline      
#elif defined (__GNUC__)
# define NTCAN_INLINE static __inline__    
#else
# define NTCAN_INLINE
#endif
#define NTCAN_EV_BASE                   1073741824
#define NTCAN_EV_USER                   1073741952
#define NTCAN_EV_LAST                   1073742079
#define NTCAN_EV_CAN_ERROR              (NTCAN_EV_BASE + (0x15b2+244-0x16a6))
#define NTCAN_EV_BAUD_CHANGE            (NTCAN_EV_BASE + (0x16f5+1537-0x1cf5))
#define NTCAN_EV_CAN_ERROR_EXT          (NTCAN_EV_BASE + (0x932+6211-0x2173))
#define NTCAN_EV_BUSLOAD                (NTCAN_EV_BASE + (0x694+6746-0x20eb))
#define NTCAN_EV_GPIO_SET_DIR           (NTCAN_EV_USER + (0x986+4286-0x19e3))
#define NTCAN_EV_GPIO_SET_DO            (NTCAN_EV_USER + (0x69a+530-0x84a))
#define NTCAN_EV_GPIO_GET_DI            (NTCAN_EV_USER + (0xdb8+4639-0x1f74))
#define NTCAN_EV_GPIO_GET_DO            (NTCAN_EV_USER + (0xad5+5453-0x1fbe))
#define NTCAN_MODE_NO_RTR               (0x1a2+3549-0xf6f)  
#define NTCAN_MODE_NO_DATA              (0x176c+139-0x17d7)  
#define NTCAN_MODE_NO_INTERACTION       (0xddd+2518-0x16b3)  
#define NTCAN_MODE_MARK_INTERACTION     (0x5bc+8343-0x2453)  
#define NTCAN_MODE_LOCAL_ECHO           (0x2344+640-0x21c4)  
#define NTCAN_MODE_TIMESTAMPED_TX       131072  
#define NTCAN_MODE_FD                   262144  
#define NTCAN_MODE_LIN                  134217728  
#define NTCAN_MODE_OBJECT               268435456  
#define NTCAN_MODE_OVERLAPPED           536870912  
#ifndef NTCAN_MAX_TX_QUEUESIZE
# define NTCAN_MAX_TX_QUEUESIZE          16384
#endif
#ifndef NTCAN_MAX_RX_QUEUESIZE
# define NTCAN_MAX_RX_QUEUESIZE          16384
#endif
#define NTCAN_NO_QUEUE                  -(0x2188+828-0x24c3)
#define NTCAN_MAX_NETS                  (0x6ca+2007-0xda2)
#define NTCAN_20B_BASE                  536870912
#define NTCAN_RTR                       (0x1f7+5597-0x17c4)   
#define NTCAN_NO_BRS                    (0x15c9+1525-0x1bae)   
#define NTCAN_NO_DATA                   (0xc25+5934-0x2333)   
#define NTCAN_INTERACTION               (0x65f+6448-0x1f6f)   
#define NTCAN_DAR                       (0x13d2+1177-0x184b)   
#define NTCAN_FD                        (0x18bc+1618-0x1e8e)   
#define NTCAN_ESI_FD_ERROR_PASSIVE      (0x120+5504-0x15a1)     
#define NTCAN_USER_BAUDRATE             0x80000000U 
#define NTCAN_LISTEN_ONLY_MODE          0x40000000U 
#define NTCAN_USER_BAUDRATE_NUM         0x20000000U 
#define NTCAN_SELF_TEST_MODE            0x10000000U 
#define NTCAN_AUTOBAUD                  0x00FFFFFEU 
#define NTCAN_BAUD_FD                   0x00FFFFFDU 
#define NTCAN_NO_BAUDRATE               0x7FFFFFFFU 
#define z1106777ad5                0xFFFFFFFFU 
#define NTCAN_BAUD_1000                (0x459+3596-0x1265)
#define NTCAN_BAUD_800                 (0x19c3+2007-0x218c)
#define NTCAN_BAUD_500                 (0x286+6330-0x1b3e)
#define NTCAN_BAUD_250                 (0x1cf7+541-0x1f10)
#define NTCAN_BAUD_125                 (0x1b17+362-0x1c7b)
#define NTCAN_BAUD_100                 (0x937+1583-0xf5f)
#define NTCAN_BAUD_50                  (0x6b0+7712-0x24c7)
#define NTCAN_BAUD_20                  (0x1408+3663-0x224c)
#define NTCAN_BAUD_10                  (0xeb6+2087-0x16d0)
#define NTCAN_BAUD_10000               (0xd99+2329-0x169d)
#define NTCAN_BAUD_8000                (0xabc+360-0xc10)
#define NTCAN_BAUD_5000                (0x1d52+605-0x1f9c)
#define NTCAN_BAUD_4000                (0x247a+351-0x25c7)
#define NTCAN_BAUD_2000                (0x1a8+6309-0x1a3c)
#define NTCAN_BSTATUS_OK                (0x1680+2736-0x2130)
#define NTCAN_BSTATUS_NEED_FW_UPDATE    (0xcf3+3000-0x18aa)
#define NTCAN_BSTATUS_HW_ERROR          (0x1738+619-0x19a1)
#define NTCAN_SCHED_FLAG_EN            (0x1a7f+974-0x1e4d) 
#define NTCAN_SCHED_FLAG_DIS           (0x3f4+2183-0xc79) 
#define NTCAN_SCHED_FLAG_REL           (0x2e9+2308-0xbed) 
#define NTCAN_SCHED_FLAG_ABS           (0x298+7380-0x1f6b) 
#define NTCAN_SCHED_FLAG_INC8          (0x9fa+724-0xbce) 
#define NTCAN_SCHED_FLAG_INC16         (0x17f1+3990-0x2587) 
#define NTCAN_SCHED_FLAG_INC32         (0x1253+3886-0x1e81) 
#define NTCAN_SCHED_FLAG_DEC8          (0x1b6b+2974-0x2309) 
#define NTCAN_SCHED_FLAG_DEC16         (0x10a1+3597-0x19ae) 
#define NTCAN_SCHED_FLAG_DEC32         (0x11e5+460-0xdb1) 
#define NTCAN_SCHED_FLAG_OFS0          (0x19c+3000-0xd54) 
#define NTCAN_SCHED_FLAG_OFS1          (0x17d5+2628-0x1219) 
#define NTCAN_SCHED_FLAG_OFS2          (0x25dc+2440-0xf64) 
#define NTCAN_SCHED_FLAG_OFS3          12288 
#define NTCAN_SCHED_FLAG_OFS4          16384 
#define NTCAN_SCHED_FLAG_OFS5          20480 
#define NTCAN_SCHED_FLAG_OFS6          24576 
#define NTCAN_SCHED_FLAG_OFS7          28672 
#define NTCAN_CANCTL_SJA1000     (0x195d+272-0x1a6d)  
#define NTCAN_CANCTL_I82527      (0x71a+5716-0x1d6d)  
#define NTCAN_CANCTL_FUJI        (0x255+769-0x554)  
#define NTCAN_CANCTL_LPC         (0xc0+5653-0x16d2)  
#define NTCAN_CANCTL_MSCAN       (0x2e3+4440-0x1437)  
#define NTCAN_CANCTL_ATSAM       (0xad5+2326-0x13e6)  
#define NTCAN_CANCTL_ESDACC      (0xcb4+5327-0x217d)  
#define NTCAN_CANCTL_STM32       (0xdf0+3076-0x19ed)  
#define NTCAN_CANCTL_CC770       (0x56d+1653-0xbda)  
#define NTCAN_CANCTL_SPEAR       (0x727+4407-0x1855)  
#define NTCAN_CANCTL_FLEXCAN     (0x178+2419-0xae1)  
#define NTCAN_CANCTL_SITARA      (0x113b+3205-0x1db5)  
#define NTCAN_CANCTL_MCP2515     (0x17c7+1706-0x1e65)  
#define NTCAN_CANCTL_MCAN        (0x2010+816-0x2333)  
#define NTCAN_CANCTL_CAST        (0x1fb2+1496-0x257c)  
#define NTCAN_CANCTL_KCANXL      (0x20a+7484-0x1f37)  
#define NTCAN_CANCTL_ESDLIN      (0x9fd+1093-0xe32)  
#define NTCAN_CANCTL_MSAM        (0x1c9+2082-0x9da)  
#define zfac28925a9      (0x1572+3559-0x2347)  
#define NTCAN_CANCTL_CTUCAN      (0x359+8061-0x22c3)  
#define NTCAN_TRX_PCA82C251      (0xa86+2449-0x1417)  
#define NTCAN_TRX_SN65HVD251     (0x628+2910-0x1185)  
#define NTCAN_TRX_SN65HVD265     (0x37d+223-0x45a)  
#define NTCAN_TRX_MCP2561FD      (0x5d4+890-0x94b)  
#define NTCAN_TRX_TCAN1051G      (0x14a+1281-0x647)  
#define NTCAN_TRX_SN65HVD230     (0x6c5+6764-0x212c)  
#define NTCAN_TRX_TJA1462        (0x1883+2504-0x2245)  
#define z946b457247       (0x49b+7448-0x21ac)  
#define zc214bd87bf    (0x1c92+798-0x1eb1)  
#define NTCAN_BITRATE_FLAG_SAM     ((0x11d0+3722-0x2059) << (0x15a6+1331-0x1ad9))        
#define zeb926efc46     NTCAN_BITRATE_FLAG_SAM
#define z3463d46123     ((0x1b11+3059-0x2703) << (0x866+6240-0x20c5))        
#define NTCAN_TDC_MODE_AUTO        (0xa4a+717-0xd17)
#define NTCAN_TDC_MODE_MANUAL      (0x1ee6+1537-0x24e6)
#define NTCAN_TDC_MODE_RESERVED    (0x73+2843-0xb8c)
#define NTCAN_TDC_MODE_OFF         (0xfdc+5544-0x2581)
#define NTCAN_TDC_FLAG_TDCEXT      ((0xcf8+2989-0x18a4) <<  (0x1102+3290-0x1dd5))    
#define NTCAN_TDC_FLAG_TDCI        ((0x11a7+1161-0x162f) << (0x9cd+3849-0x18c7))    
#define NTCAN_ECC_CLASS_BIT_ERROR           (0xe38+1309-0x1355)    
#define NTCAN_ECC_CLASS_FORM_ERROR          (0x98a+2565-0x134f)    
#define NTCAN_ECC_CLASS_STUFF_ERROR         (0x40f+987-0x76a)    
#define NTCAN_ECC_CLASS_OTHER_ERROR         (0x10a8+4270-0x2096)    
#define NTCAN_ECC_DIR_RX                    (0x12ff+1222-0x17a5)    
#define NTCAN_ECC_DIR_TX                    (0x143f+2448-0x1dcf)    
#define NTCAN_ECC_DETAIL_SOF                (0x19d5+3130-0x260c)
#define NTCAN_ECC_DETAIL_ID28_TO_ID21       (0xdd4+5695-0x2411)
#define NTCAN_ECC_DETAIL_SRTR               (0x11c+7855-0x1fc7)
#define NTCAN_ECC_DETAIL_IDE                (0x135a+3758-0x2203)
#define NTCAN_ECC_DETAIL_ID20_TO_ID18       (0x8e2+7361-0x259d)
#define NTCAN_ECC_DETAIL_ID17_TO_ID13       (0x895+6712-0x22c6)
#define NTCAN_ECC_DETAIL_CRC                (0xe09+3783-0x1cc8)
#define NTCAN_ECC_DETAIL_RES0               (0x721+6659-0x211b)
#define NTCAN_ECC_DETAIL_DATA               (0x759+5702-0x1d95)
#define NTCAN_ECC_DETAIL_DLC                (0x569+1808-0xc6e)
#define NTCAN_ECC_DETAIL_RTR                (0xd4+955-0x483)
#define NTCAN_ECC_DETAIL_RES1               (0xad0+7013-0x2628)
#define NTCAN_ECC_DETAIL_ID4_TO_ID0         (0x1bbd+857-0x1f08)
#define NTCAN_ECC_DETAIL_ID12_TO_ID5        (0x1af1+1614-0x2130)
#define NTCAN_ECC_DETAIL_ACTIVE_ERR_FLAG    (0x1a38+295-0x1b4e)
#define NTCAN_ECC_DETAIL_INTERMISSION       (0x1406+396-0x1580)
#define NTCAN_ECC_DETAIL_TOLERATE_DOM_BITS  (0x1b7c+2603-0x2594)
#define NTCAN_ECC_DETAIL_FD_STUFF_COUNT     (0x243+1317-0x754)
#define NTCAN_ECC_DETAIL_PASSIVE_ERR_FLAG   (0x1ffd+357-0x214c)
#define NTCAN_ECC_DETAIL_ERROR_DELIM        (0x1dea+2138-0x262d)
#define NTCAN_ECC_DETAIL_CRC_DELIM          (0x12cb+828-0x15ef)
#define NTCAN_ECC_DETAIL_ACK_SLOT           (0x2175+320-0x229c)
#define NTCAN_ECC_DETAIL_EOF                (0x10af+855-0x13ec)
#define NTCAN_ECC_DETAIL_ACK_DELIM          (0x97b+7471-0x268f)
#define NTCAN_ECC_DETAIL_OVERLOAD           (0x1bd+3665-0xff2)
#define NTCAN_ECC_DETAIL_FD_RES0            (0x1699+3787-0x2547)
#define NTCAN_ECC_DETAIL_FD_BRS             (0xc47+3316-0x191d)
#define NTCAN_ECC_DETAIL_FD_ESI             (0x6bb+7083-0x2247)
#define NTCAN_GPIO_CFG_DIR                (1U << (0x171+1070-0x59f)) 
#define NTCAN_GPIO_CFG_VOLTAGE            (1U << (0x86a+325-0x9ae)) 
#define NTCAN_GPIO_CFG_PULL               (1U << (0x3ab+1871-0xaf8)) 
#define NTCAN_GPIO_CFG_IRQ                (1U << (0xc84+6629-0x2666)) 
#define NTCAN_GPIO_CFG_FILTER             (1U << (0xeb1+1461-0x1462)) 
#define NTCAN_GPIO_CFG_DIR_IN             0U    
#define NTCAN_GPIO_CFG_DIR_OUT            1U    
#define NTCAN_GPIO_CFG_DIR_OUT_LS         2U    
#define NTCAN_GPIO_CFG_DIR_OUT_HS         3U    
#define NTCAN_GPIO_CFG_VOLTAGE_3V3       33U    
#define NTCAN_GPIO_CFG_VOLTAGE_5V        50U    
#define NTCAN_GPIO_CFG_PULL_NONE          0U    
#define NTCAN_GPIO_CFG_PULL_UP            1U    
#define NTCAN_GPIO_CFG_PULL_DOWN          2U    
#define NTCAN_GPIO_CFG_IRQ_NONE           0U    
#define NTCAN_GPIO_CFG_IRQ_RISING_EDGE    1U    
#define NTCAN_GPIO_CFG_IRQ_FALLING_EDGE   2U    
#define NTCAN_GPIO_CFG_IRQ_BOTH_EDGES     3U    
#define NTCAN_TERM_DISABLE                (0x1067+655-0x12f6)             
#define NTCAN_TERM_ENABLE                 4294967295    
#if defined(_WIN32)
# define NTCAN_ERRNO_BASE               3758096384
# define NTCAN_SUCCESS                  ERROR_SUCCESS
# define NTCAN_INVALID_PARAMETER        ERROR_INVALID_PARAMETER
# define NTCAN_INVALID_HANDLE           ERROR_INVALID_HANDLE
# define NTCAN_IO_INCOMPLETE            ERROR_IO_INCOMPLETE
# define NTCAN_IO_PENDING               ERROR_IO_PENDING
# define NTCAN_NET_NOT_FOUND            ERROR_FILE_NOT_FOUND
# define NTCAN_INSUFFICIENT_RESOURCES   ERROR_NO_SYSTEM_RESOURCES
# define NTCAN_OPERATION_ABORTED        ERROR_OPERATION_ABORTED
# define NTCAN_WRONG_DEVICE_STATE       ERROR_NOT_READY
# define NTCAN_HANDLE_FORCED_CLOSE      ERROR_HANDLE_EOF
# define NTCAN_NOT_IMPLEMENTED          ERROR_INVALID_FUNCTION
# define NTCAN_NOT_SUPPORTED            ERROR_NOT_SUPPORTED
#elif defined (__LABVIEW__)
# define NTCAN_ERRNO_BASE               16777216
# define NTCAN_SUCCESS                  VI_SUCCCESS
#define NTCAN_INVALID_PARAMETER         VI_ERROR_INV_PARAMETER
#define NTCAN_INVALID_HANDLE            VI_ERROR_INV_HNDLR_REF
#define NTCAN_IO_INCOMPLETE             VI_ERROR_IO
#define NTCAN_IO_PENDING                VI_ERROR_IO
#define NTCAN_NET_NOT_FOUND             VI_ERROR_FILE_ACCESS
#define NTCAN_INSUFFICIENT_RESOURCES    VI_ERROR_RSRC_NFOUND
#define NTCAN_OPERATION_ABORTED         VI_ERROR_TMO
#define NTCAN_HANDLE_FORCED_CLOSE       VI_ERROR_HNDLR_NINSTALLED
#define NTCAN_NOT_IMPLEMENTED           VI_ERROR_NIMPL_OPER
#define NTCAN_NOT_SUPPORTED             VI_ERROR_NSUP_OPER
#elif defined (__QNX__)
# define NTCAN_ERRNO_BASE               (0x1c9c+2435-0x251f)
# define NTCAN_SUCCESS                  (0x1ded+180-0x1ea1)
# define NTCAN_INVALID_PARAMETER        EINVAL
# define NTCAN_INVALID_HANDLE           EBADF
# define NTCAN_NET_NOT_FOUND            ENOENT
# define NTCAN_INSUFFICIENT_RESOURCES   ENOMEM
# define NTCAN_OPERATION_ABORTED        EINTR
# define NTCAN_NOT_IMPLEMENTED          ENOTTY 
# define NTCAN_NOT_SUPPORTED            ENOTSUP
#elif defined (__linux__)
# define NTCAN_ERRNO_BASE               (0x1194+2403-0x19f7)
# define NTCAN_SUCCESS                  (0xccc+251-0xdc7)
# define NTCAN_INVALID_PARAMETER        EINVAL
# define NTCAN_INVALID_HANDLE           EBADFD
# define NTCAN_NET_NOT_FOUND            ENODEV
# define NTCAN_INSUFFICIENT_RESOURCES   ENOMEM
# define NTCAN_OPERATION_ABORTED        EINTR
# define NTCAN_NOT_IMPLEMENTED          ENOSYS
#elif defined(__Lynx__)
# define NTCAN_ERRNO_BASE               0x000001000
# define NTCAN_SUCCESS                  (0x152a+1297-0x1a3b)
# define NTCAN_INVALID_PARAMETER        EINVAL
# define NTCAN_INVALID_HANDLE           EBADF
# define NTCAN_NET_NOT_FOUND            ENOENT
# define NTCAN_INSUFFICIENT_RESOURCES   ENOMEM
# define NTCAN_OPERATION_ABORTED        EINTR
# define NTCAN_WRONG_DEVICE_STATE       EPIPE
# define NTCAN_HANDLE_FORCED_CLOSE      ENOSPC
# define NTCAN_NOT_IMPLEMENTED          ENOTTY
# define NTCAN_NOT_SUPPORTED            ENOSYS
#elif defined(__VXWORKS__)
# define NTCAN_ERRNO_BASE               (0x1be4+52-0xc18)
# define NTCAN_SUCCESS                  (0x5ca+7358-0x2288)
# define NTCAN_INVALID_PARAMETER        EINVAL
# define NTCAN_INVALID_HANDLE           EBADF
# define NTCAN_NET_NOT_FOUND            ENODEV
# define NTCAN_INSUFFICIENT_RESOURCES   ENOMEM
# define NTCAN_OPERATION_ABORTED        ECANCELED
# define NTCAN_NOT_IMPLEMENTED          ENOSYS
# define NTCAN_NOT_SUPPORTED            ENOTSUP
#elif defined z815d5956d2
# define NTCAN_ERRNO_BASE               0x000001000
# define NTCAN_INVALID_PARAMETER        EINVAL
# define NTCAN_INVALID_HANDLE           EBADF
# define NTCAN_NET_NOT_FOUND            ENODEV
# define NTCAN_INSUFFICIENT_RESOURCES   ENOMEM
# define NTCAN_OPERATION_ABORTED        EINTR
# define NTCAN_NOT_IMPLEMENTED          ENOSYS
# define NTCAN_SUCCESS                  (0xd44+556-0xf70)
#elif defined (__FreeBSD__)
# define NTCAN_ERRNO_BASE               (0x1a6b+1132-0x1dd7)
# define NTCAN_SUCCESS                  (0x4c7+3168-0x1127)
# define NTCAN_INVALID_PARAMETER        EINVAL
# define NTCAN_INVALID_HANDLE           EBADF
# define NTCAN_NET_NOT_FOUND            ENOENT
# define NTCAN_INSUFFICIENT_RESOURCES   ENOMEM
# define NTCAN_OPERATION_ABORTED        EINTR
# define NTCAN_NOT_IMPLEMENTED          ENOSYS
#endif 
#define NTCAN_RX_TIMEOUT                (NTCAN_ERRNO_BASE + (0x1a1f+3020-0x25ea))
#define NTCAN_TX_TIMEOUT                (NTCAN_ERRNO_BASE + (0x8c6+4904-0x1bec))
#define NTCAN_TX_ERROR                  (NTCAN_ERRNO_BASE + (0x7f1+353-0x94e))
#define NTCAN_CONTR_OFF_BUS             (NTCAN_ERRNO_BASE + (0xb66+3854-0x1a6f))
#define NTCAN_CONTR_BUSY                (NTCAN_ERRNO_BASE + (0xb2f+6247-0x2390))
#define NTCAN_CONTR_WARN                (NTCAN_ERRNO_BASE + (0x254+5184-0x168d))
#define NTCAN_NO_ID_ENABLED             (NTCAN_ERRNO_BASE + (0xca3+1646-0x1308))
#define NTCAN_ID_ALREADY_ENABLED        (NTCAN_ERRNO_BASE + (0xac5+2702-0x1549))
#define NTCAN_ID_NOT_ENABLED            (NTCAN_ERRNO_BASE + (0x54f+4141-0x1571))
#define NTCAN_INVALID_FIRMWARE          (NTCAN_ERRNO_BASE + (0x85f+1529-0xe4b))
#define NTCAN_MESSAGE_LOST              (NTCAN_ERRNO_BASE + (0x11f7+3654-0x202f))
#define NTCAN_INVALID_HARDWARE          (NTCAN_ERRNO_BASE + (0x6fb+401-0x87d))
#define NTCAN_PENDING_WRITE             (NTCAN_ERRNO_BASE + (0x60c+3317-0x12f1))
#define NTCAN_PENDING_READ              (NTCAN_ERRNO_BASE + (0x11d4+2308-0x1ac7))
#define NTCAN_INVALID_DRIVER            (NTCAN_ERRNO_BASE + (0x1cfd+2253-0x25b8))
#ifndef NTCAN_WRONG_DEVICE_STATE
# define NTCAN_WRONG_DEVICE_STATE       (NTCAN_ERRNO_BASE + (0x29c+5361-0x177a))
#endif
#ifndef NTCAN_HANDLE_FORCED_CLOSE
# define NTCAN_HANDLE_FORCED_CLOSE      (NTCAN_ERRNO_BASE + (0xba4+1058-0xfb2))
#endif
#ifndef NTCAN_NOT_SUPPORTED
# define NTCAN_NOT_SUPPORTED            (NTCAN_ERRNO_BASE + (0x1489+1927-0x1bfb))
#endif
#define NTCAN_CONTR_ERR_PASSIVE         (NTCAN_ERRNO_BASE + (0x1491+3776-0x233b))
#define NTCAN_ERROR_NO_BAUDRATE         (NTCAN_ERRNO_BASE + (0x4a2+2856-0xfb3))
#define NTCAN_ERROR_LOM                 (NTCAN_ERRNO_BASE + (0xc41+6668-0x2635))
#define NTCAN_NO_CAN_CAPABILITY         (NTCAN_ERRNO_BASE + (0x8c4+2936-0x1423))
#define NTCAN_NO_LIN_CAPABILITY         (NTCAN_ERRNO_BASE + (0x23b+2073-0xa3a))
#define NTCAN_SOCK_CONN_TIMEOUT         (NTCAN_ERRNO_BASE + (0xc2f+3965-0x1b2c))
#define NTCAN_SOCK_CMD_TIMEOUT          (NTCAN_ERRNO_BASE + (0x160+2507-0xaaa))
#define NTCAN_SOCK_HOST_NOT_FOUND       (NTCAN_ERRNO_BASE + (0x13e4+3586-0x2164))
#define zd110924dfd   (NTCAN_ERRNO_BASE + (0x74a+2503-0x108e))
#define z19a50a4073          (NTCAN_ERRNO_BASE + (0x111c+863-0x13f7))
#define NTCAN_GET_CTRL_TYPE(boardstatus)     (((boardstatus) >> (0x36f+527-0x566)) & (0x1a32+1905-0x20a4))
#define NTCAN_GET_BOARD_STATUS(boardstatus)  ((boardstatus) & 65535)
#define NTCAN_DLC(len)               ((len) & (0x355+7752-0x218e))
#define NTCAN_DLC_AND_TYPE(len)      ((len) & ((0xf46+5786-0x25d1) | NTCAN_RTR))
#define NTCAN_IS_RTR(len)            (((len) & (NTCAN_FD | NTCAN_RTR)) == NTCAN_RTR)
#define NTCAN_IS_INTERACTION(len)    ((len) & NTCAN_INTERACTION)
#define NTCAN_IS_FD(len)             ((len) & NTCAN_FD)
#define NTCAN_IS_FD_WITHOUT_BRS(len) (((len) & (NTCAN_FD | NTCAN_NO_BRS)) == \
                                               (NTCAN_FD | NTCAN_NO_BRS))
#define NTCAN_LEN_TO_DATASIZE(len)    _canLenToDataSize((uint8_t)(len))
#define NTCAN_DATASIZE_TO_DLC(dataSize) _canDataSizeToDLC((dataSize))
#define NTCAN_ID(id)                 ((id) & 536870911)
#define NTCAN_IS_EFF(id)             ((id) & NTCAN_20B_BASE)
#define NTCAN_IS_EVENT(id)           ((id) & NTCAN_EV_BASE)
#define NTCAN_GET_TDC_MODE(val)     (((val) >> (0x1223+4807-0x24cc)) & (0x212+275-0x322))       
#define NTCAN_GET_TDC_SSPO(val)     (((val) >> (0x13ad+3790-0x2264)) & (0x19ac+2569-0x2336))      
#define NTCAN_GET_TDC_SSPS(val)     z63d906cfcc((val))   
#define NTCAN_GET_TDC_FILTER(val)   (((val) >>  (0xfdc+1367-0x152b)) & (0x20ed+617-0x22d7))      
#define NTCAN_GET_TDC_TD(val)       ((val) & (((val) & NTCAN_TDC_FLAG_TDCEXT) ?     \
                                             (0x523+4239-0x1533) : (0x576+6931-0x204a)))      
#define NTCAN_GET_TDC_VALUE(arg)    NTCAN_GET_TDC_TD((arg))    
#define NTCAN_GET_TDC_OFFSET(arg)   NTCAN_GET_TDC_SSPS((arg))  
#define NTCAN_SET_TDC(mode, shift) ((((mode) & (0x1cf+7055-0x1d5b)) << (0xb36+4962-0x1e7a)) | \
                                    (((shift) & (0x3a2+4286-0x13e1)) << (0xf30+3843-0x1e23)))
#define NTCAN_SET_TDC_F(mode, shift, filter) ((((mode) & (0x3d7+5251-0x1857)) << (0xdd4+4222-0x1e34))   | \
                                              (((shift) & (0xdf1+6498-0x26d4)) << (0x1354+3029-0x1f19)) | \
                                              (((filter) & (0x1853+3889-0x2705)) << (0x117+8248-0x2147)))
#define NTCAN_ECC_ERROR_CODE(ecc)           ((ecc) & (0x192f+2294-0x2165))
#define NTCAN_ECC_ERROR_DIRECTION(ecc)      ((ecc) & (0x1ead+335-0x1fdc))
#define NTCAN_ECC_ERROR_DETAIL(ecc)         ((ecc) & (0xc2b+826-0xf46))
#define NTCAN_SET_ECCEXT(ecc, zb8349cb4a6, flags)      \
            (((ecc) & (0x1401+3442-0x2094)) | (((zb8349cb4a6) & (0x177a+266-0x1875)) << (0x43b+2708-0xebf)) | ((flags) << (0x21+5295-0x14c8)))
#if ! defined(_STDINT_H ) && ! defined(_STDINT_H_INCLUDED) && ! defined(_STDINT) && ! defined(__INCstdinth) && ! defined(__INCvxTypesh) && !defined _SYS_STDINT_H_
# ifndef _WIN64
typedef unsigned char uint8_t;typedef signed char int8_t;typedef unsigned short uint16_t;typedef signed short int16_t;typedef unsigned int uint32_t;typedef signed int int32_t;
# else
typedef unsigned __int8 uint8_t;typedef signed __int8 int8_t;typedef unsigned __int16 uint16_t;typedef signed __int16 int16_t;typedef unsigned __int32 uint32_t;typedef signed __int32 int32_t;
# endif 
typedef unsigned __int64 uint64_t;typedef signed __int64 int64_t;
#endif 
#if defined(__VXWORKS__)
# if !defined(_WRS_VXWORKS_MAJOR) && !defined(_WRS_VXWORKS_5_X)
#  if !defined (UINT64_MAX)
#   define UINT64_MAX  18446744073709551615ULL
#   if !defined (INT64_MAX)
#    define INT64_MAX  9223372036854775807LL
#   endif
typedef long long int64_t;typedef unsigned long long uint64_t;
#  endif 
# endif 
#endif 
#if defined(_WIN32)
typedef DWORD NTCAN_RESULT;typedef HANDLE NTCAN_HANDLE;
#define NTCAN_NO_HANDLE   ((NTCAN_HANDLE)INVALID_HANDLE_VALUE)
#else
typedef void OVERLAPPED;typedef int32_t NTCAN_RESULT;typedef int32_t NTCAN_HANDLE;
#define NTCAN_NO_HANDLE   ((NTCAN_HANDLE)-(0x1704+145-0x1794))
#endif
#if !defined(_WIN32) && !defined(NTCAN_CLEAN_NAMESPACE)
typedef int32_t HANDLE _NTCAN_GCCATTR_DEPRECATED;
#endif
#pragma pack(1)
typedef struct{int32_t id;uint8_t len;uint8_t msg_lost;uint8_t reserved[(0xb77+1874-0x12c8)];uint8_t esi;uint8_t data[(0x211+5935-0x1938)];}CMSG;typedef struct{int32_t id;uint8_t len;uint8_t msg_lost;uint8_t reserved[(0x822+6125-0x200e)];uint8_t esi;uint8_t data[(0x1be9+83-0x1c34)];uint64_t timestamp;}CMSG_T;typedef struct{int32_t id;uint8_t len;uint8_t msg_lost;uint8_t reserved[(0x575+36-0x598)];uint8_t esi;uint8_t data[(0x11a5+2663-0x1bcc)];uint64_t timestamp;}CMSG_X;typedef struct{uint8_t reserved1;uint8_t can_status;uint8_t dma_stall;uint8_t ctrl_overrun;uint8_t reserved3;uint8_t fifo_overrun;}EV_CAN_ERROR;typedef struct{uint32_t baud;uint32_t num_baud;}EV_CAN_BAUD_CHANGE;typedef union{struct{uint8_t status;uint8_t ecc;uint8_t rec;uint8_t tec;}sja1000;struct{uint8_t status;uint8_t z4be4f9e6bc;uint8_t rec;uint8_t tec;}z2c47f965bf;struct{uint8_t status;uint8_t ecc;uint8_t rec;uint8_t tec;uint8_t txstatus;}esdacc;}EV_CAN_ERROR_EXT;typedef struct{uint32_t value;uint32_t mask;}zb529d466d7;typedef struct{int32_t evid;uint8_t len;uint8_t reserved[(0x17e9+2698-0x2270)];union{uint8_t c[(0x1442+612-0x169e)];uint16_t s[(0x18aa+3048-0x248e)];uint32_t l[(0x1ec3+1255-0x23a8)];uint64_t zc25b82582e;EV_CAN_ERROR error;EV_CAN_BAUD_CHANGE baud_change;EV_CAN_ERROR_EXT error_ext;zb529d466d7 z50d14bfd8f;}evdata;}EVMSG;typedef struct{int32_t evid;uint8_t len;uint8_t reserved[(0x69+7943-0x1f6d)];union{uint8_t c[(0x942+2264-0x1212)];uint16_t s[(0x947+7490-0x2685)];uint32_t l[(0xc41+5247-0x20be)];uint64_t zc25b82582e;EV_CAN_ERROR error;EV_CAN_BAUD_CHANGE baud_change;EV_CAN_ERROR_EXT error_ext;zb529d466d7 z50d14bfd8f;}evdata;uint64_t timestamp;}EVMSG_T;typedef struct{int32_t evid;uint8_t len;uint8_t reserved[(0x150a+3618-0x2329)];union{uint8_t c[(0x19e7+2312-0x22af)];uint16_t s[(0xa8d+5569-0x202e)];uint32_t l[(0xf38+1137-0x1399)];uint64_t zc25b82582e[(0xc2+8267-0x2105)];EV_CAN_ERROR error;EV_CAN_BAUD_CHANGE baud_change;EV_CAN_ERROR_EXT error_ext;zb529d466d7 z50d14bfd8f;}evdata;uint64_t timestamp;}EVMSG_X;typedef struct{uint16_t hardware;uint16_t firmware;uint16_t driver;uint16_t dll;uint32_t boardstatus;uint8_t boardid[(0x1784+1509-0x1d5b)];uint16_t features;}CAN_IF_STATUS;typedef struct{uint16_t hardware;uint16_t firmware;uint16_t driver;uint16_t dll;uint32_t features;uint32_t serial;uint64_t timestamp_freq;uint32_t ctrl_clock;uint8_t ctrl_type;uint8_t base_net;uint8_t ports;uint8_t transceiver;uint16_t boardstatus;uint16_t firmware2;char boardid[(0xd8b+1618-0x13bd)];char serial_string[(0x2079+1298-0x257b)];char drv_build_info[(0xe16+5890-0x24d8)];char lib_build_info[(0x776+4352-0x1836)];uint16_t open_handle;uint8_t z5da94b4c24;uint8_t reserved;uint64_t z5a79dcb7b6;char zb2adc6865f[(0xfc6+5915-0x26d5)];uint16_t z5c748e332d;uint16_t z0920462606;uint8_t z0e9c9c30da;uint8_t reserved2[(0x88f+2504-0x1248)];}NTCAN_INFO;typedef struct{uint32_t std_data;uint32_t std_rtr;uint32_t ext_data;uint32_t ext_rtr;}NTCAN_FRAME_COUNT;typedef struct{uint64_t timestamp;NTCAN_FRAME_COUNT rcv_count;NTCAN_FRAME_COUNT xmit_count;uint32_t ctrl_ovr;uint32_t fifo_ovr;uint32_t err_frames;uint32_t rcv_byte_count;uint32_t xmit_byte_count;uint32_t aborted_frames;uint32_t rcv_count_fd;uint32_t xmit_count_fd;uint64_t bit_count;}NTCAN_BUS_STATISTIC;typedef struct{uint8_t rcv_err_counter;uint8_t xmit_err_counter;uint8_t status;uint8_t type;}NTCAN_CTRL_STATE;typedef struct{uint32_t baud;uint32_t valid;uint32_t rate;uint32_t clock;uint8_t ctrl_type;uint8_t tq_pre_sp;uint8_t tq_post_sp;uint8_t sjw;uint32_t error;uint32_t flags;uint32_t rate_d;uint8_t tq_pre_sp_d;uint8_t tq_post_sp_d;uint8_t sjw_d;uint8_t mode;uint32_t reserved[(0x1a8d+424-0x1c34)];}NTCAN_BITRATE;typedef struct{uint32_t acr;uint32_t amr;uint32_t idArea;}NTCAN_FILTER_MASK;
#define NTCAN_IDS_REGION_20A    (0x454+4998-0x17da)       
#define NTCAN_IDS_REGION_20B    (0xb0b+4756-0x1d9e)       
#define NTCAN_IDS_REGION_EV     (0x561+4370-0x1671)       
typedef struct{int32_t id;int32_t flags;uint64_t time_start;uint64_t time_interval;uint32_t count_start;uint32_t count_stop;}CSCHED;typedef struct{uint64_t timestamp;uint64_t timestamp_freq;uint32_t num_baudrate;uint32_t flags;uint64_t busload_oldts;uint64_t busload_oldbits;uint8_t ctrl_type;uint8_t reserved[(0x142a+252-0x151f)];uint32_t reserved2[(0x24+5314-0x14e2)];}NTCAN_FORMATEVENT_PARAMS;typedef struct{union{uint32_t idx;uint32_t rate;uint32_t btr_ctrl;struct{uint16_t brp;uint16_t tseg1;uint16_t tseg2;uint16_t sjw;}btr;}u;}NTCAN_BAUDRATE_CFG;typedef struct{uint8_t z8a7dfcd8c7;uint8_t za0331e6d51;int8_t z05160c457d;uint8_t z08214aa9f2;}NTCAN_TDC_CFG;
#define NTCAN_BAUDRATE_MODE_DISABLE          (0x21f5+1137-0x2666)      
#define NTCAN_BAUDRATE_MODE_INDEX            (0xa4b+4173-0x1a97)      
#define NTCAN_BAUDRATE_MODE_BTR_CTRL         (0x134d+2455-0x1ce2)      
#define NTCAN_BAUDRATE_MODE_BTR_CANONICAL    (0x178f+2226-0x203e)      
#define NTCAN_BAUDRATE_MODE_NUM              (0x1103+2086-0x1925)      
#define NTCAN_BAUDRATE_MODE_AUTOBAUD         (0x1793+3248-0x243e)      
#define NTCAN_BAUDRATE_FLAG_FD     (0x1e2+3527-0xfa8)        
#define NTCAN_BAUDRATE_FLAG_LOM    (0x303+6237-0x1b5e)        
#define NTCAN_BAUDRATE_FLAG_STM    (0x295+683-0x53c)        
#define NTCAN_BAUDRATE_FLAG_TRS    (0x7b1+5475-0x1d0c)        
#define NTCAN_BAUDRATE_FLAG_TXP    (0x2334+80-0x2374)        
#define NTCAN_BAUDRATE_FLAG_TDC    (0xc9c+844-0xfc8)        
#define NTCAN_BAUDRATE_FLAG_DAR    (0x10b9+2720-0x1b19)        
typedef struct{uint16_t mode;uint16_t flags;NTCAN_TDC_CFG tdc;NTCAN_BAUDRATE_CFG arb;NTCAN_BAUDRATE_CFG data;}NTCAN_BAUDRATE_X;
#pragma pack()
#define NTCAN_FEATURE_FULL_CAN         ((0xb53+4940-0x1e9e)<<(0x11d9+4844-0x24c5))  
#define NTCAN_FEATURE_CAN_20B          ((0x10aa+3792-0x1f79)<<(0x895+6044-0x2030))  
#define NTCAN_FEATURE_DEVICE_NET       ((0x474+6085-0x1c38)<<(0x9e9+2202-0x1281))  
#define NTCAN_FEATURE_CYCLIC_TX        ((0x794+1802-0xe9d)<<(0xa1f+4468-0x1b90))  
#define NTCAN_FEATURE_TIMESTAMPED_TX   ((0x6cd+6341-0x1f91)<<(0x1a3+490-0x38a))  
#define NTCAN_FEATURE_RX_OBJECT_MODE   ((0x17f4+91-0x184e)<<(0x16f2+651-0x1979))  
#define NTCAN_FEATURE_TIMESTAMP        ((0x16a0+2610-0x20d1)<<(0x5c5+8115-0x2573))  
#define NTCAN_FEATURE_LISTEN_ONLY_MODE ((0x2032+600-0x2289)<<(0x11a+1421-0x6a1))  
#define NTCAN_FEATURE_SMART_DISCONNECT ((0x48a+918-0x81f)<<(0x1d66+727-0x2036))  
#define NTCAN_FEATURE_LOCAL_ECHO       ((0x574+6074-0x1d2d)<<(0xcf5+548-0xf11))  
#define NTCAN_FEATURE_SMART_ID_FILTER  ((0x12e2+2215-0x1b88)<<(0x152c+2194-0x1db5))  
#define NTCAN_FEATURE_SCHEDULING       ((0x6ff+2580-0x1112)<<(0xddd+5862-0x24b9)) 
#define NTCAN_FEATURE_DIAGNOSTIC       ((0xdb7+1262-0x12a4)<<(0xc11+427-0xdb1)) 
#define NTCAN_FEATURE_ERROR_INJECTION  ((0x13f2+1249-0x18d2)<<(0x207b+42-0x2099)) 
#define NTCAN_FEATURE_IRIGB            ((0x12a5+3696-0x2114)<<(0xa99+1828-0x11b0)) 
#define NTCAN_FEATURE_PXI              ((0x1142+1843-0x1874)<<(0x395+7786-0x21f1)) 
#define NTCAN_FEATURE_CAN_FD           ((0x12d+5077-0x1501)<<(0x1497+3257-0x2141)) 
#define NTCAN_FEATURE_SELF_TEST        ((0x17bf+551-0x19e5)<<(0xe9b+5269-0x2320)) 
#define NTCAN_FEATURE_TRIPLE_SAMPLING  ((0x333+3267-0xff5)<<(0x3fd+7857-0x229d)) 
#define NTCAN_FEATURE_TX_PAUSE         ((0xac2+2413-0x142e)<<(0x1273+1720-0x1919)) 
#define NTCAN_FEATURE_DAR              ((0x4ec+2279-0xdd2)<<(0x13ba+3744-0x2247)) 
#define NTCAN_FEATURE_DAR_FRAME        ((0x57+1143-0x4cd)<<(0x5b+7762-0x1e99)) 
#define NTCAN_FEATURE_LIN              ((0x685+6682-0x209e)<<(0xdf+9485-0x25d1)) 
#define NTCAN_FEATURE_PROG_TERM        ((0xa59+726-0xd2e)<<(0x454+5065-0x1801)) 
#define NTCAN_FEATURE_GPIO             ((0x31+4220-0x10ac)<<(0xd6+3950-0x1027)) 
#define NTCAN_BUSSTATE_OK           (0x137+3515-0xef2)
#define NTCAN_BUSSTATE_WARN         (0x158+9511-0x263f)
#define NTCAN_BUSSTATE_ERRPASSIVE   (0x71a+6821-0x213f)
#define NTCAN_BUSSTATE_BUSOFF       (0x1d7+2443-0xaa2)
#define NTCAN_IOCTL_FLUSH_RX_FIFO         (0x918+901-0xc9c)   
#define NTCAN_IOCTL_GET_RX_MSG_COUNT      (0xd92+4921-0x20c9)   
#define NTCAN_IOCTL_GET_RX_TIMEOUT        (0x738+6844-0x21f1)   
#define NTCAN_IOCTL_GET_TX_TIMEOUT        (0x12d3+590-0x151d)   
#define NTCAN_IOCTL_SET_20B_HND_FILTER    (0x1762+725-0x1a32)   
#define NTCAN_IOCTL_GET_SERIAL            (0x958+3366-0x1678)   
#define NTCAN_IOCTL_GET_TIMESTAMP_FREQ    (0xa86+2545-0x1470)   
#define NTCAN_IOCTL_GET_TIMESTAMP         (0xf03+4733-0x2178)   
#define NTCAN_IOCTL_ABORT_RX              (0x264+5591-0x1832)   
#define NTCAN_IOCTL_ABORT_TX              (0xb01+4600-0x1cef)   
#define NTCAN_IOCTL_SET_RX_TIMEOUT        (0xf08+287-0x101c)   
#define NTCAN_IOCTL_SET_TX_TIMEOUT        (0x11a7+4852-0x248f)   
#define NTCAN_IOCTL_TX_OBJ_CREATE         (0x535+4415-0x1667)   
#define NTCAN_IOCTL_TX_OBJ_AUTOANSWER_ON  (0x11b6+5165-0x25d5)   
#define NTCAN_IOCTL_TX_OBJ_AUTOANSWER_OFF (0xee1+4676-0x2116)   
#define NTCAN_IOCTL_TX_OBJ_UPDATE         (0x3a2+7092-0x1f46)   
#define NTCAN_IOCTL_TX_OBJ_DESTROY        (0xf12+4989-0x227e)   
#if defined (__linux__) || defined(__Lynx__)
#else
#define NTCAN_IOCTL_TX_OBJ_DESTROY_X      (0xfd1+5848-0x2697)   
#endif
#define NTCAN_IOCTL_TX_OBJ_SCHEDULE_START (0x1032+4397-0x214c)   
#define NTCAN_IOCTL_TX_OBJ_SCHEDULE_STOP  (0x55a+6307-0x1de9)   
#define NTCAN_IOCTL_TX_OBJ_SCHEDULE       (0xa9c+7171-0x268a)   
#define NTCAN_IOCTL_SET_BUSLOAD_INTERVAL  (0x274+4929-0x159f)   
#define NTCAN_IOCTL_GET_BUSLOAD_INTERVAL  (0x19a9+1430-0x1f28)   
#define NTCAN_IOCTL_GET_BUS_STATISTIC     (0x1431+2060-0x1c25)   
#define NTCAN_IOCTL_GET_CTRL_STATUS       (0x1144+3110-0x1d51)   
#define NTCAN_IOCTL_GET_BITRATE_DETAILS   (0x10a3+3179-0x1cf4)   
#define NTCAN_IOCTL_GET_NATIVE_HANDLE     (0x669+2413-0xfbb)   
#define NTCAN_IOCTL_SET_HND_FILTER        (0x11d1+2684-0x1c31)   
#define NTCAN_IOCTL_GET_INFO              (0x1e7c+996-0x2243)   
#define NTCAN_IOCTL_TX_OBJ_CREATE_X       (0x1ebd+1120-0x22ff)   
#define NTCAN_IOCTL_TX_OBJ_UPDATE_X       (0x1179+372-0x12ce)   
#define NTCAN_IOCTL_EEI_CREATE            (0x3b5+4681-0x15de)   
#define NTCAN_IOCTL_EEI_DESTROY           (0xd43+856-0x107a)   
#define NTCAN_IOCTL_EEI_STATUS            (0xe81+5638-0x2465)   
#define NTCAN_IOCTL_EEI_CONFIGURE         (0x11f0+4729-0x2446)   
#define NTCAN_IOCTL_EEI_START             (0x19c7+1430-0x1f39)   
#define NTCAN_IOCTL_EEI_STOP              (0x486+7650-0x2243)   
#define NTCAN_IOCTL_EEI_TRIGGER_NOW       (0x988+2803-0x1455)   
#define NTCAN_IOCTL_SET_TX_TS_WIN         (0xb81+2885-0x1696)   
#define NTCAN_IOCTL_GET_TX_TS_WIN         (0x111+9278-0x251e)   
#define NTCAN_IOCTL_SET_TX_TS_TIMEOUT     (0xb31+2717-0x159c)   
#define NTCAN_IOCTL_GET_TX_TS_TIMEOUT     (0x8a7+3638-0x16aa)   
#define NTCAN_IOCTL_GET_TX_MSG_COUNT      (0x387+5834-0x1a1d)   
#if defined (__linux__) || defined(__Lynx__)
#define NTCAN_IOCTL_TX_OBJ_DESTROY_X      (0x1e28+459-0x1fb4)   
#else
#define NTCAN_IOCTL_LXX_RESERVED          (0x15ba+1421-0x1b08)   
#endif
#define NTCAN_IOCTL_RESET_CTRL_EC         32795   
#define NTCAN_IOCTL_GET_FD_TDC            (0x1a64+743-0x1d0b)   
#define NTCAN_IOCTL_SET_FD_TDC            (0x12e1+2288-0x1b90)   
#define NTCAN_IOCTL_LIN_MASTER_SEL        (0x1461+465-0x15f0)  
#define NTCAN_IOCTL_TX_OBJ_AUTOANSWER_ONCE (0x139+6222-0x1944) 
#define NTCAN_IOCTL_GET_DAR_MODE          (0x134+2551-0xae7)   
#define NTCAN_IOCTL_SET_DAR_MODE          (0x8f7+639-0xb31)   
#define NTCAN_DAR_DISABLE_ON_ARB_LOST     (0x1401+85-0x1455)    
#define NTCAN_DAR_DISABLE_ON_TX_ERROR     (0x7d9+1181-0xc74)    
#define NTCAN_IOCTL_GET_TERM_CFG          (0xb4c+1252-0xfea)   
#define NTCAN_IOCTL_SET_TERM_CFG          (0x5a7+4625-0x1771)   
#define NTCAN_IOCTL_GET_GPIO_CFG          (0x10f3+5598-0x2689)   
#define NTCAN_IOCTL_SET_GPIO_CFG          (0x1587+3359-0x225d)   
#define zb0792c0506         (0x86+9787-0x2677)   
#define z3f77a602dc       (0x1013+1536-0x15c8)   
#define NTCAN_ERROR_FORMAT_LONG           (0x1b0f+377-0x1c88)   
#define NTCAN_ERROR_FORMAT_SHORT          (0xd2c+429-0xed8)   
#define NTCAN_FORMATEVENT_SHORT           (0xc72+1680-0x1301)   
#define EEI_STATUS_OFF              (0x40+1756-0x71c)
#define EEI_STATUS_WAIT_TRIGGER     (0x1217+1952-0x19b6)
#define EEI_STATUS_SENDING          (0xcbd+1260-0x11a7)
#define EEI_STATUS_FINISHED         (0x167+5466-0x16be)
#define EEI_TRIGGER_MATCH           (0x1a6+42-0x1d0)
#define EEI_TRIGGER_ARBITRATION     (0x26f+3271-0xf35)
#define EEI_TRIGGER_TIMESTAMP       (0xf44+4194-0x1fa4)
#define EEI_TRIGGER_FIELD_POSITION  (0x1869+1437-0x1e03)
#define EEI_TRIGGER_EXTERNAL_INPUT  (0x16c0+14-0x16ca)
#define EEI_TRIGGER_ARBITRATION_OPTION_ABORT_ON_ERROR   (0xd91+3497-0x1b39) 
#define EEI_TRIGGER_MATCH_OPTION_DESTUFFED              (0x4b2+679-0x758) 
#define EEI_TRIGGER_TIMESTAMP_OPTION_BUSFREE            (0x212b+519-0x2331) 
#define EEI_MODE_REPEAT_ENABLE                (0x619+4417-0x1759)
#define EEI_MODE_REPEAT_USE_NUMBER_OF_REPEAT  (0x923+4512-0x1ac1)
#define EEI_TRIGGERDELAY_NONE       (0x15d+8289-0x21be) 
#define EEI_TRIGGERDELAY_BITTIMES   (0x12f1+4503-0x2487) 
#define NTCAN_MAX_CAN_FRAME_BITS_CC     (0x1260+264-0x12c8)
typedef union{uint8_t c[NTCAN_MAX_CAN_FRAME_BITS_CC>>(0x10df+2111-0x191b)];uint16_t s[NTCAN_MAX_CAN_FRAME_BITS_CC>>(0xd72+94-0xdcc)];uint32_t l[NTCAN_MAX_CAN_FRAME_BITS_CC>>(0x66b+4425-0x17af)];}CAN_FRAME_STREAM;
#define NTCAN_MAX_CAN_FRAME_BITS_FD     (0x1795+2628-0x1ed9)
typedef union{uint8_t c[NTCAN_MAX_CAN_FRAME_BITS_FD>>(0x1abc+2423-0x2430)];uint16_t s[NTCAN_MAX_CAN_FRAME_BITS_FD>>(0x2356+391-0x24d9)];uint32_t l[NTCAN_MAX_CAN_FRAME_BITS_FD>>(0xb68+4994-0x1ee5)];}zce6a574ab6;typedef struct _NTCAN_EEI_UNIT{uint32_t handle;uint8_t mode_trigger;uint8_t mode_trigger_option;uint8_t mode_triggerarm_delay;uint8_t mode_triggeraction_delay;uint8_t mode_repeat;uint8_t mode_trigger_now;uint8_t mode_ext_trigger_option;uint8_t mode_send_async;uint8_t reserved1[(0x888+4059-0x185f)];uint64_t timestamp_send;CAN_FRAME_STREAM trigger_pattern;CAN_FRAME_STREAM trigger_mask;uint8_t trigger_ecc;uint8_t reserved2[(0x5ac+753-0x89a)];uint32_t external_trigger_mask;uint32_t reserved3[(0xb73+1319-0x108a)];CAN_FRAME_STREAM tx_pattern;uint32_t tx_pattern_len;uint32_t triggerarm_delay;uint32_t triggeraction_delay;uint32_t number_of_repeat;uint32_t reserved4;CAN_FRAME_STREAM tx_pattern_recessive;uint32_t reserved5[(0x9e9+3986-0x1972)];}NTCAN_EEI_UNIT;typedef struct _NTCAN_EEI_STATUS{uint32_t handle;uint8_t status;uint8_t unit_index;uint8_t units_total;uint8_t units_free;uint64_t trigger_timestamp;uint16_t trigger_cnt;uint16_t reserved0;uint32_t reserved1[(0xfe7+964-0x1390)];}NTCAN_EEI_STATUS;typedef struct _CMSG_FRAME{CAN_FRAME_STREAM can_frame;CAN_FRAME_STREAM stuff_bits;uint16_t crc;uint8_t length;uint8_t pos_id11;uint8_t pos_id18;uint8_t pos_rtr;uint8_t pos_crtl;uint8_t pos_dlc;uint8_t pos_data[(0x1e68+1534-0x245e)];uint8_t pos_crc;uint8_t pos_crc_del;uint8_t pos_ack;uint8_t pos_eof;uint8_t pos_ifs;uint8_t z1bcd329f83;uint8_t reserved[(0x1817+2225-0x20c6)];}CMSG_FRAME;typedef struct zda9d633407{zce6a574ab6 can_frame;zce6a574ab6 stuff_bits;uint32_t crc;uint16_t length;uint16_t bit_count[(0x1096+2859-0x1bbf)];uint16_t z1bcd329f83[(0xa27+384-0xba5)];uint16_t pos_id11;uint16_t pos_id18;uint16_t pos_rtr;uint16_t z99fba11744;uint16_t z7eccbcc875;uint16_t z02b5995c58;uint16_t pos_dlc;uint16_t pos_data[(0xac1+534-0xc97)];uint16_t z677836e352;uint16_t pos_crc;uint16_t pos_crc_del;uint16_t pos_ack;uint16_t pos_eof;uint16_t pos_ifs;uint16_t reserved[(0x33f+6379-0x1c1e)];}z0e25307e87;typedef struct _NTCAN_GPIO_CFG{uint8_t channel;uint8_t reserved;uint16_t properties;uint8_t direction;uint8_t voltage;uint8_t pull;uint8_t irq_mode;uint32_t input_filter;uint8_t reserved2[(0xe14+5322-0x22d2)];}NTCAN_GPIO_CFG;
#if (defined(_MSC_VER) && (_MSC_VER >= (0x13e4+5260-0x22f8))) ||               \
    (defined(__BORLANDC__) && (__BORLANDC__ >= (0xb16+5651-0x19f9)))
uint8_t _rotl8(uint8_t value,uint8_t shift);
# pragma intrinsic(_rotl8)
#define _ntcan_rotl8(value, shift)   _rotl8(value, shift)
#else
NTCAN_INLINE uint8_t _ntcan_rotl8(uint8_t value,uint8_t shift){return(uint8_t)((value<<shift)|(value>>((0x338+2611-0xd63)-shift)));}
#endif 
NTCAN_INLINE uint8_t _canLenToDataSize(uint8_t len){static const uint8_t ucLenNtcan[]={(0x1ed3+1574-0x24f9),(0x163c+1175-0x1ad3),(0x104c+95-0x10aa),(0x182+7979-0x20ac),(0x1c58+543-0x1e75),(0x1342+262-0x1446),(0xf5f+4443-0x20b7),(0x15+5218-0x1474),(0x193f+2832-0x244b),(0x1ca1+1149-0x211a),(0x9b3+4100-0x19b2),(0x1398+2922-0x1efd),(0x1030+1359-0x1579),(0xba7+6968-0x26d9),(0x1447+1792-0x1b40),(0xd8b+4260-0x1e28),(0x2072+1288-0x2572),(0xadd+2121-0x131e),(0x10ed+166-0x118b),(0x3d1+975-0x794),(0x86c+7583-0x2603),(0x1f51+141-0x1fce),(0x1282+2264-0x1b52),(0x11bb+2672-0x1c17),(0x11ea+1211-0x169d),(0xbb3+3763-0x1a4e),(0xbd4+683-0xe77),(0x186+2371-0xaa9),(0x6bd+1309-0xbd2),(0x4a4+6435-0x1d97),(0xa83+6286-0x2309),(0x539+5119-0x18f8),(0x11af+717-0x147c),(0x16f4+4060-0x26d0),(0x53a+7334-0x21e0),(0x68b+331-0x7d5),(0xaef+5695-0x212e),(0x2d4+972-0x69e),(0xa34+2813-0x1531),(0x6cb+3448-0x1440),(0x11aa+4309-0x227f),(0x190+6019-0x190f),(0x9cf+780-0xcdb),(0xa41+4299-0x1b07),(0x53a+2484-0xeee),(0x1087+186-0x113b),(0xd48+4841-0x2031),(0x145d+3520-0x2216),(0x14b9+2305-0x1dba),(0xd7b+6012-0x24ef),(0x1bea+446-0x1da8),(0x1184+4373-0x228d),(0x17d+6132-0x1971),(0x3cb+3543-0x1192),(0x9f3+5510-0x1f79),(0x158a+2901-0x20cb),(0x1938+2564-0x233c),(0x1433+4136-0x2443),(0x320+6336-0x1be0),(0x69b+772-0x97f),(0x6e9+353-0x84a),(0x11eb+2146-0x1a1d),(0xb20+1090-0xf62),(0x1b11+1097-0x1f1a)};return(ucLenNtcan[_ntcan_rotl8(len,(0x570+6041-0x1d08))&(0x218c+1428-0x26e1)]);}NTCAN_INLINE uint8_t _canDataSizeToDLC(uint8_t dataSize){static const uint8_t ucLenNtcan[]={(0xc67+5690-0x22a1),(0xaef+3628-0x191a),(0x1515+4339-0x2606),(0x1053+2317-0x195d),(0x6a3+7478-0x23d5),(0xbf0+1066-0x1015),(0xa37+2128-0x1281),(0x3f5+6254-0x1c5c),(0x10a+7956-0x2016),(0x320+1115-0x772),(0x148a+2794-0x1f6b),(0xff5+5868-0x26d8),(0xb04+4975-0x1e6a),(0x17e1+315-0x1912),(0x2395+376-0x2503),(0x9d8+1833-0x10f7),(0x184d+2690-0x22c5),(0xcc6+6587-0x2676),(0xa9+4834-0x1380),(0x8c0+4194-0x1917),(0x7ba+2606-0x11dd),(0x122+1157-0x59b),(0x3e7+4098-0x13dd),(0x1404+4628-0x260c),(0xf1d+3600-0x1d21),(0x1340+1335-0x186a),(0xa4+3907-0xfda),(0x2d1+1433-0x85d),(0x1fa+3524-0xfb1),(0x22c+1524-0x813),(0x140c+3636-0x2233),(0x828+4447-0x197a),(0x908+1497-0xed4),(0xcd2+1179-0x115f),(0xe41+1200-0x12e3),(0x686+2973-0x1215),(0x10d3+5238-0x253b),(0x833+696-0xadd),(0xa17+3057-0x15fa),(0x16e6+3699-0x254b),(0xa9b+2098-0x12bf),(0xcf1+4804-0x1fa7),(0x2ef+4578-0x14c3),(0x5e8+471-0x7b1),(0x1c3+685-0x462),(0xc44+350-0xd94),(0x1678+3244-0x2316),(0x7b1+4299-0x186e),(0x5ec+3192-0x1256),(0xc46+1787-0x1332),(0x1644+484-0x1819),(0x1c3a+948-0x1fdf),(0xe5+7613-0x1e93),(0x7a5+892-0xb12),(0x2530+243-0x2614),(0x3d3+5840-0x1a94),(0xec1+4616-0x20ba),(0x7b9+7202-0x23cc),(0x1425+1009-0x1807),(0x6b5+4995-0x1a29),(0x1c84+2137-0x24ce),(0x14d+2936-0xcb6),(0x1eb2+827-0x21de),(0x172+9533-0x26a0),(0x1244+1220-0x16f9)};if(dataSize>(0xe51+1220-0x12d5)){dataSize=(0x3da+4437-0x14ef);}return(ucLenNtcan[dataSize]);}NTCAN_INLINE int8_t z63d906cfcc(uint32_t arg){if(NTCAN_TDC_MODE_AUTO==NTCAN_GET_TDC_MODE(arg)){if(arg&NTCAN_TDC_FLAG_TDCEXT){struct{signed int value:(0x45d+2315-0xd61);}_ssps;_ssps.value=(signed)(((arg)>>(0x533+7316-0x21b7))&(0x584+6447-0x1e34));return((int8_t)_ssps.value);}else{struct{signed int value:(0x222+5467-0x1777);}_ssps;_ssps.value=(signed)(((arg)>>(0xdb9+3790-0x1c77))&(0x3cd+2617-0xdc7));return((int8_t)_ssps.value);}}return((((arg)>>(0x1523+3738-0x23ad))&(0x984+1629-0xf62)));}EXPORT NTCAN_RESULT CALLTYPE canSetBaudrate(NTCAN_HANDLE handle,uint32_t baud);EXPORT NTCAN_RESULT CALLTYPE canGetBaudrate(NTCAN_HANDLE handle,uint32_t*baud);EXPORT NTCAN_RESULT CALLTYPE canOpen(int net,uint32_t flags,int32_t txqueuesize,int32_t rxqueuesize,int32_t txtimeout,int32_t rxtimeout,NTCAN_HANDLE*handle);EXPORT NTCAN_RESULT CALLTYPE canClose(NTCAN_HANDLE handle);EXPORT NTCAN_RESULT CALLTYPE canSetBaudrateX(NTCAN_HANDLE handle,NTCAN_BAUDRATE_X*baud);EXPORT NTCAN_RESULT CALLTYPE canGetBaudrateX(NTCAN_HANDLE handle,NTCAN_BAUDRATE_X*baud);EXPORT NTCAN_RESULT CALLTYPE canIdAdd(NTCAN_HANDLE handle,int32_t id);EXPORT NTCAN_RESULT CALLTYPE canIdRegionAdd(NTCAN_HANDLE 
handle,int32_t idStart,int32_t*idCnt);EXPORT NTCAN_RESULT CALLTYPE canIdDelete(NTCAN_HANDLE handle,int32_t id);EXPORT NTCAN_RESULT CALLTYPE canIdRegionDelete(NTCAN_HANDLE handle,int32_t idStart,int32_t*idCnt);EXPORT NTCAN_RESULT CALLTYPE canTake(NTCAN_HANDLE handle,CMSG*cmsg,int32_t*len);EXPORT NTCAN_RESULT CALLTYPE canRead(NTCAN_HANDLE handle,CMSG*cmsg,int32_t*len,OVERLAPPED*ovrlppd);EXPORT NTCAN_RESULT CALLTYPE canSend(NTCAN_HANDLE handle,CMSG*cmsg,int32_t*len);EXPORT NTCAN_RESULT CALLTYPE canWrite(NTCAN_HANDLE handle,CMSG*cmsg,int32_t*len,OVERLAPPED*ovrlppd);_NTCAN_OBSOLETE(canRead)EXPORT NTCAN_RESULT CALLTYPE canReadEvent(NTCAN_HANDLE handle,EVMSG*evmsg,OVERLAPPED*ovrlppd)_NTCAN_GCCATTR_DEPRECATED;_NTCAN_OBSOLETE(canSend)EXPORT NTCAN_RESULT CALLTYPE canSendEvent(NTCAN_HANDLE handle,EVMSG*evmsg)_NTCAN_GCCATTR_DEPRECATED;EXPORT NTCAN_RESULT CALLTYPE canStatus(NTCAN_HANDLE handle,CAN_IF_STATUS*cstat);EXPORT NTCAN_RESULT CALLTYPE canIoctl(NTCAN_HANDLE handle,uint32_t ulCmd,void*pArg);EXPORT NTCAN_RESULT CALLTYPE canTakeT(NTCAN_HANDLE handle,CMSG_T*cmsg_t,int32_t*len);EXPORT NTCAN_RESULT CALLTYPE canReadT(NTCAN_HANDLE handle,CMSG_T*cmsg_t,int32_t*len,OVERLAPPED*ovrlppd);EXPORT NTCAN_RESULT CALLTYPE canSendT(NTCAN_HANDLE handle,CMSG_T*cmsg_t,int32_t*len);EXPORT NTCAN_RESULT CALLTYPE canWriteT(NTCAN_HANDLE handle,CMSG_T*cmsg_t,int32_t*len,OVERLAPPED*ovrlppd);EXPORT NTCAN_RESULT CALLTYPE canTakeX(NTCAN_HANDLE handle,CMSG_X*cmsg_x,int32_t*len);EXPORT NTCAN_RESULT CALLTYPE canReadX(NTCAN_HANDLE handle,CMSG_X*cmsg_x,int32_t*len,OVERLAPPED*ovrlppd);EXPORT NTCAN_RESULT CALLTYPE canSendX(NTCAN_HANDLE handle,CMSG_X*cmsg_x,int32_t*len);EXPORT NTCAN_RESULT CALLTYPE canWriteX(NTCAN_HANDLE handle,CMSG_X*cmsg_x,int32_t*len,OVERLAPPED*ovrlppd);EXPORT NTCAN_RESULT CALLTYPE canFormatError(NTCAN_RESULT error,uint32_t type,char*pBuf,uint32_t bufsize);EXPORT NTCAN_RESULT CALLTYPE canFormatEvent(EVMSG*event,NTCAN_FORMATEVENT_PARAMS*para,char*pBuf,uint32_t bufsize);EXPORT NTCAN_RESULT CALLTYPE canFormatFrame(CMSG*msg,CMSG_FRAME*frame,uint32_t eccExt);EXPORT NTCAN_RESULT CALLTYPE z5d72838d9a(CMSG_X*msg,z0e25307e87*frame,uint32_t eccExt);
#if (defined(_WIN32) || defined(__linux__)) && !defined(UNDER_RTSS) && !defined(RTOS32) && !defined(z7f7e6325b2)
EXPORT NTCAN_RESULT CALLTYPE canGetOverlappedResult(NTCAN_HANDLE handle,OVERLAPPED*ovrlppd,int32_t*len,NTCAN_BOOL bWait);EXPORT NTCAN_RESULT CALLTYPE canGetOverlappedResultT(NTCAN_HANDLE handle,OVERLAPPED*ovrlppd,int32_t*len,NTCAN_BOOL bWait);EXPORT NTCAN_RESULT CALLTYPE canGetOverlappedResultX(NTCAN_HANDLE handle,OVERLAPPED*ovrlppd,int32_t*len,NTCAN_BOOL bWait);
#else
# define canGetOverlappedResult(hnd, ovr, len, bWait)    NTCAN_NOT_IMPLEMENTED
# define canGetOverlappedResultT(hnd, ovr, len, bWait)   NTCAN_NOT_IMPLEMENTED
# define canGetOverlappedResultX(hnd, ovr, len, bWait)   NTCAN_NOT_IMPLEMENTED
#endif 
#if defined(NTCAN_DLSYM)
typedef NTCAN_RESULT(CALLTYPE*PFN_CAN_SET_BAUDRATE)(NTCAN_HANDLE handle,uint32_t baud);typedef NTCAN_RESULT(CALLTYPE*PFN_CAN_GET_BAUDRATE)(NTCAN_HANDLE handle,uint32_t*baud);typedef NTCAN_RESULT(CALLTYPE*PFN_CAN_OPEN)(int net,uint32_t flags,int32_t txqueuesize,int32_t rxqueuesize,int32_t txtimeout,int32_t rxtimeout,NTCAN_HANDLE*handle);typedef NTCAN_RESULT(CALLTYPE*PFN_CAN_SET_BAUDRATE_X)(NTCAN_HANDLE handle,NTCAN_BAUDRATE_X*baud);typedef NTCAN_RESULT(CALLTYPE*PFN_CAN_GET_BAUDRATE_X)(NTCAN_HANDLE handle,NTCAN_BAUDRATE_X*baud);typedef NTCAN_RESULT(CALLTYPE*PFN_CAN_CLOSE)(NTCAN_HANDLE handle);typedef NTCAN_RESULT(CALLTYPE*PFN_CAN_ID_ADD)(NTCAN_HANDLE handle,int32_t id);typedef NTCAN_RESULT(CALLTYPE*PFN_CAN_ID_DELETE)(NTCAN_HANDLE handle,int32_t id);typedef NTCAN_RESULT(CALLTYPE*PFN_CAN_SEND)(NTCAN_HANDLE handle,CMSG*cmsg,int32_t*len);typedef NTCAN_RESULT(CALLTYPE*PFN_CAN_WRITE)(NTCAN_HANDLE handle,CMSG*cmsg,int32_t*len,OVERLAPPED*ovrlppd);typedef NTCAN_RESULT(CALLTYPE*PFN_CAN_TAKE)(NTCAN_HANDLE handle,CMSG*cmsg,int32_t*len);typedef NTCAN_RESULT(CALLTYPE*PFN_CAN_READ)(NTCAN_HANDLE handle,CMSG*cmsg,int32_t*len,OVERLAPPED*ovrlppd);typedef NTCAN_RESULT(CALLTYPE*PFN_CAN_READ_EVENT)(NTCAN_HANDLE handle,EVMSG*cmsg,OVERLAPPED*ovrlppd);typedef NTCAN_RESULT(CALLTYPE*PFN_CAN_SEND_EVENT)(NTCAN_HANDLE handle,EVMSG*cmsg);typedef NTCAN_RESULT(CALLTYPE*PFN_CAN_STATUS)(NTCAN_HANDLE handle,CAN_IF_STATUS*cstat);typedef NTCAN_RESULT(CALLTYPE*PFN_CAN_IOCTL)(NTCAN_HANDLE handle,uint32_t ulCmd,void*pArg);typedef NTCAN_RESULT(CALLTYPE*PFN_CAN_TAKE_T)(NTCAN_HANDLE handle,CMSG_T*cmsg_t,int32_t*len);typedef NTCAN_RESULT(CALLTYPE*PFN_CAN_READ_T)(NTCAN_HANDLE handle,CMSG_T*cmsg_t,int32_t*len,OVERLAPPED*ovrlppd);typedef NTCAN_RESULT(CALLTYPE*PFN_CAN_SEND_T)(NTCAN_HANDLE handle,CMSG_T*cmsg_t,int32_t*len);typedef NTCAN_RESULT(CALLTYPE*PFN_CAN_WRITE_T)(NTCAN_HANDLE handle,CMSG_T*cmsg_t,int32_t*len,OVERLAPPED*ovrlppd);typedef NTCAN_RESULT(CALLTYPE*PFN_CAN_TAKE_X)(NTCAN_HANDLE handle,CMSG_X*cmsg_x,int32_t*len);typedef NTCAN_RESULT(CALLTYPE*PFN_CAN_READ_X)(NTCAN_HANDLE handle,CMSG_X*cmsg_x,int32_t*len,OVERLAPPED*ovrlppd);typedef NTCAN_RESULT(CALLTYPE*PFN_CAN_SEND_X)(NTCAN_HANDLE handle,CMSG_X*cmsg_x,int32_t*len);typedef NTCAN_RESULT(CALLTYPE*PFN_CAN_WRITE_X)(NTCAN_HANDLE handle,CMSG_X*cmsg_x,int32_t*len,OVERLAPPED*ovrlppd);typedef NTCAN_RESULT(CALLTYPE*PFN_CAN_FORMAT_ERROR)(NTCAN_RESULT error,uint32_t type,char*pBuf,uint32_t bufsize);typedef NTCAN_RESULT(CALLTYPE*PFN_CAN_FORMAT_EVENT)(EVMSG*event,NTCAN_FORMATEVENT_PARAMS*para,char*pBuf,uint32_t bufsize);typedef NTCAN_RESULT(CALLTYPE*PFN_CAN_FORMAT_FRAME)(CMSG*msg,CMSG_FRAME*frame,uint32_t eccExt);typedef NTCAN_RESULT(CALLTYPE*ze3ed87847f)(CMSG_X*msg,z0e25307e87*frame,uint32_t eccExt);
#if (defined(_WIN32) || defined(__linux__)) && !defined(UNDER_RTSS) && !defined(RTOS32) && !defined(z7f7e6325b2)
typedef NTCAN_RESULT(CALLTYPE*PFN_CAN_GET_OVERLAPPED_RESULT)(NTCAN_HANDLE handle,OVERLAPPED*ovrlppd,int32_t*len,NTCAN_BOOL bWait);typedef NTCAN_RESULT(CALLTYPE*PFN_CAN_GET_OVERLAPPED_RESULT_T)(NTCAN_HANDLE handle,OVERLAPPED*ovrlppd,int32_t*len,NTCAN_BOOL bWait);typedef NTCAN_RESULT(CALLTYPE*PFN_CAN_GET_OVERLAPPED_RESULT_X)(NTCAN_HANDLE handle,OVERLAPPED*ovrlppd,int32_t*len,NTCAN_BOOL bWait);
#else
typedef NTCAN_RESULT(CALLTYPE*PFN_CAN_GET_OVERLAPPED_RESULT)(NTCAN_HANDLE handle,OVERLAPPED*ovrlppd,int32_t*len,int bWait);typedef NTCAN_RESULT(CALLTYPE*PFN_CAN_GET_OVERLAPPED_RESULT_T)(NTCAN_HANDLE handle,OVERLAPPED*ovrlppd,int32_t*len,int bWait);typedef NTCAN_RESULT(CALLTYPE*PFN_CAN_GET_OVERLAPPED_RESULT_X)(NTCAN_HANDLE handle,OVERLAPPED*ovrlppd,int32_t*len,int bWait);
#endif 
#define FUNCPTR_CAN_SET_BAUDRATE(hnd) \
    (PFN_CAN_SET_BAUDRATE)NTCAN_DLSYM(hnd, "\x63\x61\x6e\x53\x65\x74\x42\x61\x75\x64\x72\x61\x74\x65")
#define FUNCPTR_CAN_GET_BAUDRATE(hnd) \
    (PFN_CAN_GET_BAUDRATE)NTCAN_DLSYM(hnd, "\x63\x61\x6e\x47\x65\x74\x42\x61\x75\x64\x72\x61\x74\x65")
#define FUNCPTR_CAN_OPEN(hnd) \
    (PFN_CAN_OPEN)NTCAN_DLSYM(hnd, "\x63\x61\x6e\x4f\x70\x65\x6e")
#define FUNCPTR_CAN_CLOSE(hnd) \
    (PFN_CAN_CLOSE)NTCAN_DLSYM(hnd, "\x63\x61\x6e\x43\x6c\x6f\x73\x65")
#define FUNCPTR_CAN_SET_BAUDRATE_X(hnd) \
    (PFN_CAN_SET_BAUDRATE_X)NTCAN_DLSYM(hnd, "\x63\x61\x6e\x53\x65\x74\x42\x61\x75\x64\x72\x61\x74\x65\x58")
#define FUNCPTR_CAN_GET_BAUDRATE_X(hnd) \
    (PFN_CAN_GET_BAUDRATE_X)NTCAN_DLSYM(hnd, "\x63\x61\x6e\x47\x65\x74\x42\x61\x75\x64\x72\x61\x74\x65\x58")
#define FUNCPTR_CAN_ID_ADD(hnd) \
    (PFN_CAN_ID_ADD)NTCAN_DLSYM(hnd, "\x63\x61\x6e\x49\x64\x41\x64\x64")
#define FUNCPTR_CAN_ID_DELETE(hnd) \
    (PFN_CAN_ID_DELETE)NTCAN_DLSYM(hnd, "\x63\x61\x6e\x49\x64\x44\x65\x6c\x65\x74\x65")
#define FUNCPTR_CAN_SEND(hnd) \
    (PFN_CAN_SEND)NTCAN_DLSYM(hnd, "\x63\x61\x6e\x53\x65\x6e\x64")
#define FUNCPTR_CAN_WRITE(hnd) \
    (PFN_CAN_WRITE)NTCAN_DLSYM(hnd, "\x63\x61\x6e\x57\x72\x69\x74\x65")
#define FUNCPTR_CAN_TAKE(hnd) \
    (PFN_CAN_TAKE)NTCAN_DLSYM(hnd, "\x63\x61\x6e\x54\x61\x6b\x65")
#define FUNCPTR_CAN_READ(hnd) \
    (PFN_CAN_READ)NTCAN_DLSYM(hnd, "\x63\x61\x6e\x52\x65\x61\x64")
#define FUNCPTR_CAN_SEND_EVENT(hnd) \
    (PFN_CAN_SEND_EVENT)NTCAN_DLSYM(hnd, "\x63\x61\x6e\x53\x65\x6e\x64\x45\x76\x65\x6e\x74")
#define FUNCPTR_CAN_READ_EVENT(hnd) \
    (PFN_CAN_READ_EVENT)NTCAN_DLSYM(hnd, "\x63\x61\x6e\x52\x65\x61\x64\x45\x76\x65\x6e\x74")
#define FUNCPTR_CAN_STATUS(hnd) \
    (PFN_CAN_STATUS)NTCAN_DLSYM(hnd, "\x63\x61\x6e\x53\x74\x61\x74\x75\x73")
#define FUNCPTR_CAN_IOCTL(hnd) \
    (PFN_CAN_IOCTL)NTCAN_DLSYM(hnd, "\x63\x61\x6e\x49\x6f\x63\x74\x6c")
#define FUNCPTR_CAN_SEND_T(hnd) \
    (PFN_CAN_SEND_T)NTCAN_DLSYM(hnd, "\x63\x61\x6e\x53\x65\x6e\x64\x54")
#define FUNCPTR_CAN_WRITE_T(hnd) \
    (PFN_CAN_WRITE_T)NTCAN_DLSYM(hnd, "\x63\x61\x6e\x57\x72\x69\x74\x65\x54")
#define FUNCPTR_CAN_TAKE_T(hnd) \
    (PFN_CAN_TAKE_T)NTCAN_DLSYM(hnd, "\x63\x61\x6e\x54\x61\x6b\x65\x54")
#define FUNCPTR_CAN_READ_T(hnd) \
    (PFN_CAN_READ_T)NTCAN_DLSYM(hnd, "\x63\x61\x6e\x52\x65\x61\x64\x54")
#define FUNCPTR_CAN_SEND_X(hnd) \
    (PFN_CAN_SEND_X)NTCAN_DLSYM(hnd, "\x63\x61\x6e\x53\x65\x6e\x64\x58")
#define FUNCPTR_CAN_WRITE_X(hnd) \
    (PFN_CAN_WRITE_X)NTCAN_DLSYM(hnd, "\x63\x61\x6e\x57\x72\x69\x74\x65\x58")
#define FUNCPTR_CAN_TAKE_X(hnd) \
    (PFN_CAN_TAKE_X)NTCAN_DLSYM(hnd, "\x63\x61\x6e\x54\x61\x6b\x65\x58")
#define FUNCPTR_CAN_READ_X(hnd) \
    (PFN_CAN_READ_X)NTCAN_DLSYM(hnd, "\x63\x61\x6e\x52\x65\x61\x64\x58")
#define FUNCPTR_CAN_FORMAT_ERROR(hnd) \
    (PFN_CAN_FORMAT_ERROR)NTCAN_DLSYM(hnd, "\x63\x61\x6e\x46\x6f\x72\x6d\x61\x74\x45\x72\x72\x6f\x72")
#define FUNCPTR_CAN_FORMAT_EVENT(hnd) \
    (PFN_CAN_FORMAT_EVENT)NTCAN_DLSYM(hnd, "\x63\x61\x6e\x46\x6f\x72\x6d\x61\x74\x45\x76\x65\x6e\x74")
#define FUNCPTR_CAN_FORMAT_FRAME(hnd) \
    (PFN_CAN_FORMAT_FRAME)NTCAN_DLSYM(hnd, "\x63\x61\x6e\x46\x6f\x72\x6d\x61\x74\x46\x72\x61\x6d\x65")
#define z17c27ba395(hnd) \
    (ze3ed87847f)NTCAN_DLSYM(hnd, "\x63\x61\x6e\x46\x6f\x72\x6d\x61\x74\x46\x72\x61\x6d\x65\x58")
#if (defined(_WIN32) || defined(__linux__)) && !defined(UNDER_RTSS) && !defined(RTOS32) && !defined(z7f7e6325b2)
# define FUNCPTR_CAN_GET_OVERLAPPED_RESULT(hnd) \
    (PFN_CAN_GET_OVERLAPPED_RESULT)NTCAN_DLSYM(hnd, "\x63\x61\x6e\x47\x65\x74\x4f\x76\x65\x72\x6c\x61\x70\x70\x65\x64\x52\x65\x73\x75\x6c\x74")
# define FUNCPTR_CAN_GET_OVERLAPPED_RESULT_T(hnd) \
    (PFN_CAN_GET_OVERLAPPED_RESULT_T)NTCAN_DLSYM(hnd, "\x63\x61\x6e\x47\x65\x74\x4f\x76\x65\x72\x6c\x61\x70\x70\x65\x64\x52\x65\x73\x75\x6c\x74\x54")
# define FUNCPTR_CAN_GET_OVERLAPPED_RESULT_X(hnd) \
    (PFN_CAN_GET_OVERLAPPED_RESULT_T)NTCAN_DLSYM(hnd, "\x63\x61\x6e\x47\x65\x74\x4f\x76\x65\x72\x6c\x61\x70\x70\x65\x64\x52\x65\x73\x75\x6c\x74\x58")
#else
# define FUNCPTR_CAN_GET_OVERLAPPED_RESULT(hnd)         NULL
# define FUNCPTR_CAN_GET_OVERLAPPED_RESULT_T(hnd)       NULL
# define FUNCPTR_CAN_GET_OVERLAPPED_RESULT_X(hnd)       NULL
#endif 
#endif 
#ifdef __cplusplus
}
#endif
#endif 

