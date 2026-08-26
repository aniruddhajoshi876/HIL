// Copyright 2006-2026 Speedgoat GmbH

#ifndef _PSYS_H_
#define _PSYS_H_
#if defined(_WIN32) && !defined(z01c5d30060)
#    include <psyswin.h>
#elif defined(__linux__)
#    include <psyslinux.h>
#elif defined(__QNXNTO__)
#    include <psysnto.h>
#elif defined(z5f9752c2bf)
#    include <psysvx.h>
#elif defined(zf6552658fe) || defined(z3b7a5cc490)
#    include <psysrtos.h>
#elif defined(zcea8ac9fd3)
#    include <psysrmos.h>
#elif defined(z01c5d30060)
#    include <psyslabview.h>
#else
#    error "Operating system undefined"
#endif
#ifndef PSYS_BYTE_ORDER
#    error !!! Host byteorder undefined !!!!
#endif
#ifndef PSYS_REG_SIZE
#    error !!! Host register size in bits undefined !!!!
#endif
#define PSYS_MSGSIZE                    16100
#define PSYS_ENDIAN_LITTLE              (0xd51+4064-0x1d31)
#define PSYS_ENDIAN_BIG                 (0x2da+2852-0xdfd)
#define PSYS_PRIO_INHERIT               -(0xcca+2557-0x16c6) 
#define PSYS_PRIO_MIN                   (0x6f6+767-0x9f5)
#define PSYS_PRIO_MAX                   (0x1594+364-0x16e1)
#define PSYS_THREAD_NOFLOAT             (1U << (0xcd5+3576-0x1abd))
#define PSYS_THREAD_FLOAT               (0U << (0x662+1592-0xc8a))
#define PSYS_THREAD_NATIVE_PRIO         (1U << (0x1a61+1804-0x2151))
#define PSYS_THREAD_ENFORCE_STACKSIZE   (1U << (0xa68+7361-0x270c))
#define PSYS_THREAD_ENFORCE_PRIO        (1U << (0x812+2195-0x1087))
#define PSYS_THREAD_NAME                (1U << (0x3ab+8937-0x2675))
#define PSYS_THREADNAME_LENGTH          (0x1f6a+99-0x1f8d)
#define PSYS_TIME_ABS                   (0xc2+5859-0x17a4)
#define PSYS_TIME_REL                   (0x86a+7110-0x2430)
#define PSYS_VERIFY_READ                ((0x10e0+429-0x128c) << (0x4b7+2600-0xedf))
#define PSYS_VERIFY_WRITE               ((0x213+6942-0x1d30) << (0x7e9+3672-0x1640))
#define PSYS_VERIFY_STRING              ((0xd45+3741-0x1be1) << (0xec2+3239-0x1b67))
#define PSYS_MUTEX_PLATFORM_DEFAULT     (0x342+9149-0x26ff)
#define PSYS_MUTEX_RECURSIVE            (0x667+3339-0x1371)
#define PSYS_MUTEX_ERRORCHECK           (0x266+3994-0x11fe)
#define PSYS_LOG_TYPE_FILE              1U
#define PSYS_LOG_TYPE_CONSOLE           2U
#define PSYS_LOG_TYPE_SYSLOG            3U
#define PSYS_FEATURE_NATIVE_THREAD_PRIO 0x0001U 
#define N2USEC                          (UINT64)(1000L)
#define N2MSEC                          ((0x1925+210-0x160f) * N2USEC)
#define N2SEC                           ((0x86d+3950-0x13f3) * N2MSEC)
#define N2MIN                           ((0x146a+3803-0x2309) * N2SEC)
#define N2HOUR                          ((0xbd2+5754-0x2210) * N2MIN)
#define N2DAY                           ((0x6f7+385-0x860) * N2HOUR)
#ifndef PSYS_CALLTYPE
#    define PSYS_CALLTYPE
#endif
#ifndef EXPORT
#    define EXPORT
#endif
#ifndef IMPORT
#    define IMPORT extern
#endif
#if !defined(NULLHANDLE) || (NULLHANDLE != (0xd7c+5264-0x220c))
#    define NULLHANDLE (0x1a3c+1952-0x21dc)
#endif
#define _PSYS_UNUSED __attribute__((unused))
#define _PSYS_PACKED __attribute__((packed))
#ifndef __GNUC__
#    define __attribute__(x) 
#endif
#if defined(__GNUC__)
#    define PSYS_INLINE     __inline__
#    define PSYS_DEPRECATED __attribute__((deprecated))
#elif defined(_MSC_VER)
#    define PSYS_INLINE _inline
#    if (_MSC_VER >= (0x1762+356-0x13b2))
#        define PSYS_DEPRECATED __declspec(deprecated)
#    endif
#endif
#if !defined(PSYS_UNREFERENCED_PARAMETER)
#    define PSYS_UNREFERENCED_PARAMETER(arg) ((void)(arg))
#endif
#if !defined(PSYS_DEPRECATED)
#    define PSYS_DEPRECATED
#endif
#if !defined(PSYS_MEM_TRACE_ENABLE)
#    define PSYS_MEM_TRACE_ENABLE
#endif
#define PSYS_OK    (0xca5+3067-0x18a0)
#define PSYS_ERROR -(0xdbc+54-0xdf1)
#ifndef PSYS_NO_POSIX_ERROR
#    include <errno.h>
#    define PSYS_EPERM           EPERM     
#    define PSYS_ENOENT          ENOENT    
#    define PSYS_ESRCH           ESRCH     
#    define PSYS_EINTR           EINTR     
#    define PSYS_EIO             EIO       
#    define PSYS_ENXIO           ENXIO     
#    define PSYS_E2BIG           E2BIG     
#    define PSYS_ENOEXEC         ENOEXEC   
#    define PSYS_EBADF           EBADF     
#    define PSYS_ECHILD          ECHILD    
#    define PSYS_EAGAIN          EAGAIN    
#    define PSYS_ENOMEM          ENOMEM    
#    define PSYS_EACCES          EACCES    
#    define PSYS_EFAULT          EFAULT    
#    define PSYS_ENOTBLK         ENOTBLK   
#    define PSYS_EBUSY           EBUSY     
#    define PSYS_EEXIST          EEXIST    
#    define PSYS_EXDEV           EXDEV     
#    define PSYS_ENODEV          ENODEV    
#    define PSYS_ENOTDIR         ENOTDIR   
#    define PSYS_EISDIR          EISDIR    
#    define PSYS_EINVAL          EINVAL    
#    define PSYS_ENFILE          ENFILE    
#    define PSYS_EMFILE          EMFILE    
#    define PSYS_ENOTTY          ENOTTY    
#    define PSYS_ETXTBSY         ETXTBSY   
#    define PSYS_EFBIG           EFBIG     
#    define PSYS_ENOSPC          ENOSPC    
#    define PSYS_ESPIPE          ESPIPE    
#    define PSYS_EROFS           EROFS     
#    define PSYS_EMLINK          EMLINK    
#    define PSYS_EPIPE           EPIPE     
#    define PSYS_EDOM            EDOM      
#    define PSYS_ERANGE          ERANGE    
#    define PSYS_ENOMSG          ENOMSG    
#    define PSYS_EIDRM           EIDRM     
#    define PSYS_ECHRNG          ECHRNG    
#    define PSYS_EL2NSYNC        EL2NSYNC  
#    define PSYS_EL3HLT          EL3HLT    
#    define PSYS_EL3RST          EL3RST    
#    define PSYS_ELNRNG          ELNRNG    
#    define PSYS_EUNATCH         EUNATCH   
#    define PSYS_ENOCSI          ENOCSI    
#    define PSYS_EL2HLT          EL2HLT    
#    define PSYS_EDEADLK         EDEADLK   
#    define PSYS_ENOLCK          ENOLCK    
#    define PSYS_ECANCELED       ECANCELED 
#    define PSYS_ENOTSUP         ENOTSUP   
#    define PSYS_EDQUOT          EDQUOT 
#    define PSYS_EBADE           EBADE     
#    define PSYS_EBADR           EBADR     
#    define PSYS_EXFULL          EXFULL    
#    define PSYS_ENOANO          ENOANO    
#    define PSYS_EBADRQC         EBADRQC   
#    define PSYS_EBADSLT         EBADSLT   
#    define PSYS_EDEADLOCK       EDEADLOCK 
#    define PSYS_EBFONT          EBFONT 
#    define PSYS_ENOSTR          ENOSTR  
#    define PSYS_ENODATA         ENODATA 
#    define PSYS_ETIME           ETIME   
#    define PSYS_ENOSR           ENOSR   
#    define PSYS_ENONET          ENONET  
#    define PSYS_ENOPKG          ENOPKG  
#    define PSYS_EREMOTE         EREMOTE 
#    define PSYS_ENOLINK         ENOLINK 
#    define PSYS_EADV            EADV    
#    define PSYS_ESRMNT          ESRMNT  
#    define PSYS_ECOMM           ECOMM        
#    define PSYS_EPROTO          EPROTO       
#    define PSYS_EMULTIHOP       EMULTIHOP    
#    define PSYS_EBADMSG         EBADMSG      
#    define PSYS_ENAMETOOLONG    ENAMETOOLONG 
#    define PSYS_EOVERFLOW       EOVERFLOW    
#    define PSYS_ENOTUNIQ        ENOTUNIQ     
#    define PSYS_EBADFD          EBADFD       
#    define PSYS_EREMCHG         EREMCHG      
#    define PSYS_ELIBACC         ELIBACC  
#    define PSYS_ELIBBAD         ELIBBAD  
#    define PSYS_ELIBSCN         ELIBSCN  
#    define PSYS_ELIBMAX         ELIBMAX  
#    define PSYS_ELIBEXEC        ELIBEXEC 
#    define PSYS_EILSEQ          EILSEQ   
#    define PSYS_ENOSYS          ENOSYS    
#    define PSYS_ELOOP           ELOOP     
#    define PSYS_ERESTART        ERESTART  
#    define PSYS_ESTRPIPE        ESTRPIPE  
#    define PSYS_ENOTEMPTY       ENOTEMPTY 
#    define PSYS_EUSERS          EUSERS    
#    define PSYS_EOPNOTSUPP      EOPNOTSUPP 
#    define PSYS_ESTALE          ESTALE 
#    define PSYS_EWOULDBLOCK     EWOULDBLOCK 
#    define PSYS_EINPROGRESS     EINPROGRESS 
#    define PSYS_EALREADY        EALREADY    
#    define PSYS_ENOTSOCK        ENOTSOCK        
#    define PSYS_EDESTADDRREQ    EDESTADDRREQ    
#    define PSYS_EMSGSIZE        EMSGSIZE        
#    define PSYS_EPROTOTYPE      EPROTOTYPE      
#    define PSYS_ENOPROTOOPT     ENOPROTOOPT     
#    define PSYS_EPROTONOSUPPORT EPROTONOSUPPORT 
#    define PSYS_ESOCKTNOSUPPORT ESOCKTNOSUPPORT 
#    define PSYS_EPFNOSUPPORT    EPFNOSUPPORT    
#    define PSYS_EAFNOSUPPORT    EAFNOSUPPORT    
#    define PSYS_EADDRINUSE      EADDRINUSE      
#    define PSYS_EADDRNOTAVAIL   EADDRNOTAVAIL   
#    define PSYS_ENETDOWN        ENETDOWN     
#    define PSYS_ENETUNREACH     ENETUNREACH  
#    define PSYS_ENETRESET       ENETRESET    
#    define PSYS_ECONNABORTED    ECONNABORTED 
#    define PSYS_ECONNRESET      ECONNRESET   
#    define PSYS_ENOBUFS         ENOBUFS      
#    define PSYS_EISCONN         EISCONN      
#    define PSYS_ENOTCONN        ENOTCONN     
#    define PSYS_ESHUTDOWN       ESHUTDOWN    
#    define PSYS_ETOOMANYREFS    ETOOMANYREFS 
#    define PSYS_ETIMEDOUT       ETIMEDOUT    
#    define PSYS_ECONNREFUSED    ECONNREFUSED 
#    define PSYS_EHOSTDOWN       EHOSTDOWN    
#    define PSYS_EHOSTUNREACH    EHOSTUNREACH 
#    define PSYS_EBADRPC         EBADRPC       
#    define PSYS_ERPCMISMATCH    ERPCMISMATCH  
#    define PSYS_EPROGUNAVAIL    EPROGUNAVAIL  
#    define PSYS_EPROGMISMATCH   EPROGMISMATCH 
#    define PSYS_EPROCUNAVAIL    EPROCUNAVAIL  
#    define PSYS_E_MLC_BASE      (0x16d7+4307-0x1eaa)
#    define PSYS_E_CAN_BASE      (0x17a1+4883-0x1ab4)
#endif 
#ifndef INT
#    define INT signed int
#endif
#ifndef UINT
#    define UINT unsigned int
#endif
#ifndef VOID
#    define VOID void
#endif
#ifndef CHAR
#    define CHAR char
#endif
#ifdef __cplusplus
extern"C"{
#endif
typedef union{UINT64 z20b5f1e053;struct{
#if PSYS_BYTE_ORDER == PSYS_ENDIAN_LITTLE
UINT32 z4cf39d0f23;UINT32 z3da7c0a836;
#endif
#if PSYS_BYTE_ORDER == PSYS_ENDIAN_BIG
UINT32 z3da7c0a836;UINT32 z4cf39d0f23;
#endif
}l;}PSYS_TIME;typedef struct{PSYS_TIME value;PSYS_TIME interval;}zca72610612;typedef struct{INT32 zf6f1c5aa7c;INT32 z854c891df8;UINT32 flags;CHAR*name;}z7cac15e91f;typedef struct{INT32 zc036e2eb73;INT32 z7a84b20a68;INT32 zfc82be0351;INT32 zb81f696860;INT32 zf6f1c5aa7c;}z481eda6272;typedef struct{UINT16 version;UINT16 features;UINT8 z5891588585[(0x97f+923-0xd0e)];CHAR z12c819a117[(0x6b1+4798-0x192f)];}z167d8ec214;
#ifndef _PSYS_PLATFORM_SPECIFIC_EVENTS
typedef struct{UINT32 mask;COND zb640727420;MUTEX mutex;}zc35f553e12;
#endif 
#ifndef PSYS_NO_POSIX_ERROR
#    define z1eba5f44f6()    errno
#    define z6f9253a1d4(z0fcae3df66) errno = z0fcae3df66
#endif
#define PSYS_SLEEP_USEC(zfbe71f6739)        \
    {                              \
        PSYS_TIME z03019a17d9;          \
        z03019a17d9.z20b5f1e053 = (zfbe71f6739)*N2USEC; \
        psysSleep(&z03019a17d9);        \
    }
#define PSYS_SLEEP_MSEC(zb5b0733e2f)        \
    {                              \
        PSYS_TIME z03019a17d9;          \
        z03019a17d9.z20b5f1e053 = (zb5b0733e2f)*N2MSEC; \
        psysSleep(&z03019a17d9);        \
    }
#define PSYS_SLEEP_SEC(s)        \
    {                            \
        PSYS_TIME z03019a17d9;        \
        z03019a17d9.z20b5f1e053 = (s)*N2SEC; \
        psysSleep(&z03019a17d9);      \
    }
EXPORT INT PSYS_CALLTYPE psysMutexInitX(MUTEX*mutex,INT flags);EXPORT INT PSYS_CALLTYPE psysMutexInit(MUTEX*mutex);EXPORT INT PSYS_CALLTYPE psysMutexDestroy(MUTEX*mutex);EXPORT INT PSYS_CALLTYPE psysMutexLock(MUTEX*mutex);EXPORT INT PSYS_CALLTYPE psysMutexUnlock(MUTEX*mutex);EXPORT INT PSYS_CALLTYPE psysCondInit(COND*zb640727420);EXPORT INT PSYS_CALLTYPE psysCondDestroy(COND*zb640727420);EXPORT INT PSYS_CALLTYPE psysCondWait(COND*zb640727420,MUTEX*mutex);EXPORT INT PSYS_CALLTYPE psysCondSignal(COND*zb640727420);EXPORT INT PSYS_CALLTYPE psysEventInit(zc35f553e12*event);EXPORT INT PSYS_CALLTYPE psysEventDestroy(zc35f553e12*event);EXPORT INT PSYS_CALLTYPE psysEventWait(zc35f553e12*event,UINT32*mask);EXPORT INT PSYS_CALLTYPE psysEventSignal(zc35f553e12*event,UINT32 mask);EXPORT INT PSYS_CALLTYPE psysSleep(PSYS_TIME*time);EXPORT INT PSYS_CALLTYPE psysThreadCreate(THREAD*thread,z7cac15e91f*zf880517e09,int(PSYS_CALLTYPE*zebb6e914cb)(void*),VOID*arg);EXPORT INT PSYS_CALLTYPE psysValidatePriority(INT zf6f1c5aa7c);EXPORT INT PSYS_CALLTYPE psysTimeGet(PSYS_TIME*time);EXPORT INT PSYS_CALLTYPE psysChannelCreate(const CHAR*name,UINT32 flags);EXPORT INT PSYS_CALLTYPE psysChannelDestroy(INT zafb130db1b);EXPORT INT PSYS_CALLTYPE psysMsgReceive(INT zafb130db1b,VOID*data,INT len,z481eda6272*zcb2f2f6021);EXPORT INT PSYS_CALLTYPE psysMsgReply(INT zd3d5cecdf3,INT status,const VOID*data,INT len);EXPORT INT PSYS_CALLTYPE psysConnectAttach(const CHAR*name);EXPORT INT PSYS_CALLTYPE psysConnectDetach(INT zce67a57ca1);EXPORT INT PSYS_CALLTYPE psysMsgSend(INT zce67a57ca1,const VOID*za31003659f,INT z503c791e13,VOID*zbf8309dca9,INT zcf1ba30ff2);EXPORT INT PSYS_CALLTYPE psysInfo(z167d8ec214*info,INT len);EXPORT INT PSYS_CALLTYPE psysTimerInit(INT id,z7cac15e91f*zf880517e09);EXPORT INT PSYS_CALLTYPE psysTimerCreate(VOID(PSYS_CALLTYPE*zebb6e914cb)(INT,VOID*),VOID*arg);EXPORT INT PSYS_CALLTYPE psysTimerDelete(INT id);EXPORT INT PSYS_CALLTYPE psysTimerSet(INT id,INT32 flags,const zca72610612*z71a7adfe4c,zca72610612*z2ec0941f6d);EXPORT INT PSYS_CALLTYPE psysTimerGet(INT id,zca72610612*z71a7adfe4c);EXPORT INT PSYS_CALLTYPE psysObjectCopy(const CHAR*z0f2d183aba,CHAR*dest,const CHAR*zffe01d25fb,INT z84f07a7a0f);EXPORT VOID PSYS_CALLTYPE psysLog(UINT32 mask,const CHAR*format,...);EXPORT VOID PSYS_CALLTYPE psysLogMaskSet(UINT32 mask);EXPORT INT PSYS_CALLTYPE psysLogConfig(UINT32 type,const CHAR*zf0f8ffbaae);EXPORT VOID*PSYS_CALLTYPE psysMalloc(UINT size);EXPORT VOID*PSYS_CALLTYPE psysCalloc(UINT z4becf47bd7,UINT size);EXPORT VOID*PSYS_CALLTYPE psysRealloc(VOID*ptr,UINT size);EXPORT VOID PSYS_CALLTYPE psysFree(VOID*ptr);EXPORT INT PSYS_CALLTYPE psysMemProbe(UINT8*addr,INT32 flags,UINT size,UINT align);EXPORT INT PSYS_CALLTYPE psysTimezoneSet(const CHAR*z3744a6a4fc);
#ifdef __cplusplus
}
#endif
#endif 

