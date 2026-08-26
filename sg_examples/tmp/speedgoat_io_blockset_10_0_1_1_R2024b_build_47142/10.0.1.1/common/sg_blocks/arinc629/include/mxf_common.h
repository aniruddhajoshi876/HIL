/*****************************************************************************
//
//       Copyright (c) MAX Technologies Inc. 1988-2015, All Rights Reserved.
//             CONFIDENTIAL AND PROPRIETARY INFORMATION WHICH IS THE
//                         PROPERTY OF MAX TECHNOLOGIES INC.
//
*****************************************************************************/

/*****************************************************************************
//       You may define the following constants
//       - MAXT_DEFNOINCLUDES       Prevents all includes
//       - MAXT_DEFNOEXPORTED       Prevents EXPORTED redefinitions
//       - MAXT_DEFTYPESNOTYPE      Prevents all types redefinitions
//       - MAXT_DEFTYPESNOFIXED     Prevents fixed type redefinition
//       - MAXT_DEFTYPESNOPVOID     Prevents "pvoid" redefinition
//       - MAXT_DEFTYPESNOPCHAR     Prevents "char*" redefinition
//       - MAXT_DEFTYPESNOPINT      Prevents "pint" redefinition
*****************************************************************************/

#ifndef MXF_MXCOMMON_H_CONST
#define MXF_MXCOMMON_H_CONST

#ifndef BITS_PER_LONG
   #define BITS_PER_LONG 32
#endif

#if defined(__APPLE__) && defined(__MACH__)
   #ifndef _osx
      #define _osx
   #endif
   #ifndef _linux
      #define _linux
   #endif
#endif

#if (BITS_PER_LONG == 64) || defined(_WIN64) || defined(__LP64__) //linux, windows, OSX
   #define MXF_64
#else
   #define MXF_32
#endif

#if defined(_MSC_VER)
   #if _MSC_VER < 1300
      #define MAXT_VS6
   #endif
   #if _MSC_VER >= 1600 && !defined(KMDF_MAJOR_VERSION)  
      #define MAXT_VS2010
   #endif
#endif

#if !defined(__STDC_VERSION__) 
   #define __STDC_VERSION__ 0
#endif

#if __STDC_VERSION__ >= 199901L || defined(MAXT_VS2010)
   #define C99
#endif

#ifndef MAXT_DEFNOINCLUDES
   #if defined(WIN32) && !defined(_CRT_SECURE_NO_WARNINGS)
      //eliminate the warnings for sprinf, strcpy, etc. in visual studio 2005 +
      #define _CRT_SECURE_NO_WARNINGS
   #endif
   #if defined(WIN32)
      #pragma warning (disable:4201) //nameless union
      #pragma warning (disable:4055) //function pointer

      //Remove windows headers warnings
      #pragma warning (push)
      #pragma warning (disable:4668) //is not defined as a preprocessor macro
      #pragma warning (disable:4574) //preprocessor macro is defined to be '0'
      #pragma warning (disable:4820) //bytes padding
      #pragma warning (disable:4255) //No function prototype
   #endif

   #include <stdio.h>
   #include <stdlib.h>
   #include <string.h>
   #include <math.h>

   #ifdef C99
      #include <stdint.h>
   #endif

   #if defined(WIN32)
      #pragma warning (pop)
   #endif

#endif

#ifndef FALSE
   #define FALSE  0
#endif

#ifndef TRUE
   #define TRUE   1
#endif

#ifndef max
   #define max(a,b)              (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
   #define min(a,b)              (((a) < (b)) ? (a) : (b))
#endif

#if defined(_WIN32) && !defined(__MXFIRMWARE) && !defined(__MX_EMBEDDED)
   #define MXWINDOWS
   #ifdef __BORLANDC__
      #define MXPASCAL      pascal
   #else
      #define MXPASCAL      __stdcall
   #endif
#else
   #define MXPASCAL
#endif

#ifndef MAXT_DEFTYPESNOTYPE

   #ifndef MAXT_DEFTYPESNOPVOID
      typedef void *pvoid;
   #endif /* MAXT_DEFTYPESNOPVOID */

   #ifndef MAXT_DEFTYPESNOPCHAR
      typedef char *pchar;
   #endif /* MAXT_DEFTYPESNOPCHAR */

   #ifndef MAXT_DEFTYPESNOPINT
      typedef int *pint;
      #if !defined(_irix) && !defined(_linux)  && !defined(linux)
         typedef unsigned int uint;
      #endif
      typedef unsigned int *puint;
   #endif /* MAXT_DEFTYPESNOPINT */

   #ifndef MAXT_DEFTYPESNOFIXED
      #ifdef C99
         typedef int8_t          int8;
         typedef uint8_t         uint8;

         typedef int16_t         int16;
         typedef uint16_t        uint16;

         typedef int32_t         int32;
         typedef uint32_t        uint32;

         #if !defined(int64)
            typedef int64_t          int64;
            typedef int64_t*         pint64;
         #endif

         #if !defined(uint64)
            typedef uint64_t         uint64;
            typedef uint64_t*        puint64;
         #endif

         typedef int8_t          *pint8;
         typedef uint8_t         *puint8;

         typedef int16_t         *pint16;
         typedef uint16_t        *puint16;

         typedef int32_t         *pint32;
         typedef uint32_t        *puint32;
      #else
         //No C99
         typedef char            int8;
         typedef unsigned char   uint8;

         typedef short           int16;
         typedef unsigned short  uint16;

         typedef int            int32;
         typedef unsigned int   uint32;

         #if !defined(int64)
            #if defined(__BORLANDC__) || defined(_WIN32)
               typedef __int64            int64;
               typedef __int64*           pint64;
               typedef unsigned __int64   uint64;
               typedef unsigned __int64*  puint64;
            #else
               typedef long long             int64;
               typedef long long*            pint64;
            #endif
         #endif

         #if !defined(uint64)
            #if defined(__BORLANDC__) || defined(_WIN32)
            #else
               typedef unsigned long long    uint64;
               typedef unsigned long long*   puint64;
            #endif
         #endif

         typedef char            *pint8;
         typedef unsigned char   *puint8;

         typedef short           *pint16;
         typedef unsigned short  *puint16;

         typedef int            *pint32;
         typedef unsigned int   *puint32;
      #endif
   #endif /* MAXT_DEFTYPESNOFIXED */
   
   #ifndef BITS_PER_LONG
      #define BITS_PER_LONG 32
   #endif

#endif /* MAXT_DEFTYPESNOTYPE */

#ifndef MAXT_I64_CONST
   #ifdef __BORLANDC__
      #define MAXT_I64_CONST(CONST)  CONST
      #define MAXT_UI64_CONST(CONST) CONST
   #else
      #ifdef _WIN32
         #define MAXT_I64_CONST(CONST)  CONST##i64
         #define MAXT_UI64_CONST(CONST) CONST##ui64
      #else
         #define MAXT_I64_CONST(CONST)  CONST##LL
         #define MAXT_UI64_CONST(CONST) CONST##ULL
      #endif
   #endif
#endif

#ifndef EXPORTED
   #if defined(MAXT_DEFNOEXPORTED) || defined(_VXWORKS)
      #define EXPORTED
   #else
      #ifdef __BORLANDC__
         #define EXPORTED MXPASCAL _export
      #else
         #if defined (MONTAVISTA) || defined (linux)
            #define EXPORTED
         #else
            #define EXPORTED MXPASCAL
         #endif
      #endif
   #endif
#endif

#ifdef MX3_EXPORTED_ENABLE
   #define MX_EXPORTED     EXPORTED
#else
   #define MX_EXPORTED
#endif

#ifdef MXFCT_EXPORTED_ONLY
   #define MXF_EXPORTED
#else
   #define MXF_EXPORTED       EXPORTED
#endif

#define MXFCT_EXPORTED     EXPORTED

typedef void*    MXHINSTANCE;

typedef uint32 (*MXFUNCTION)(uint32, void*);

typedef uint64    HMXF_HANDLE;
typedef uint64    HMXF_NETWORK_HANDLE;

#ifdef MXF_64 
   typedef uint64 HMX_HANDLE;
#else
   typedef uint32 HMX_HANDLE;
#endif

#define NOT_USED(p) ((void)(p));

#endif
