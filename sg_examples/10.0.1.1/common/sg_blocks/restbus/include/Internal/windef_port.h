// Copyright 2006-2026 Speedgoat GmbH

#ifndef ze16130fbfc
#define ze16130fbfc
#if !defined(__linux__)
#define __linux__	
#endif
#ifdef __linux__
#include <stdint.h>
#include <string>
#include <iostream>
#include <string.h> 
#include "sg_common.h"
#ifndef VOID
#define VOID void
typedef char CHAR;typedef short SHORT;typedef unsigned int DWORD;typedef unsigned long LONG;typedef unsigned long ULONG;typedef unsigned long*PULONG;typedef int BOOL;typedef unsigned char BYTE;typedef unsigned char UCHAR;typedef unsigned short WORD;typedef float FLOAT;typedef FLOAT*PFLOAT;typedef BOOL*zc786d18372;typedef BOOL*LPBOOL;typedef BYTE*PBYTE;typedef BYTE*LPBYTE;typedef int*PINT;typedef int*LPINT;typedef WORD*PWORD;typedef WORD*LPWORD;typedef long*LPLONG;typedef long z7c2791ac2c;typedef DWORD*PDWORD;typedef DWORD*LPDWORD;typedef void*LPVOID;typedef const void*LPCVOID;typedef size_t SIZE_T;typedef void*z096008ef80;typedef const CHAR*LPCSTR,*PCSTR;typedef void*z2e9610b357;typedef void*z76650a8649;typedef void*z5733c31b0e;typedef uint32_t*z704d0b38a0;typedef UCHAR*PUCHAR;typedef unsigned short USHORT;typedef uint32_t zf1c7b8e60b;typedef uint64_t z09de8108ef;typedef uint64_t*z69296b6d73;typedef char TCHAR;typedef int64_t z59df57438e;typedef void*LPSECURITY_ATTRIBUTES;typedef long int*LPOVERLAPPED;typedef union{struct{uint32_t LowPart;uint32_t HighPart;};uint64_t QuadPart;}LARGE_INTEGER;
#define z2743b2bace(x) (-x * (0x2c6+240-0x3ac))
#define zff5fa55460(x) (-x * (0x48a+2911-0xfdf) * (0x8dc+7078-0x209a))
typedef int INT;typedef unsigned int UINT;typedef unsigned int UINT32;typedef unsigned int*PUINT;typedef unsigned int*zfb1aed6559;typedef unsigned long long UINT64;typedef void*HANDLE;typedef void*HMODULE;typedef void*PVOID;typedef struct _SYSTEMTIME{WORD wYear;WORD wMonth;WORD wDayOfWeek;WORD wDay;WORD wHour;WORD wMinute;WORD wSecond;WORD wMilliseconds;}SYSTEMTIME,*z8f2a2d6762,*LPSYSTEMTIME;typedef void*z2b3ef74253;typedef uintptr_t zb3836ca6af;
#if defined(z9dab14899b)
typedef uint64_t z89cc47ad22;
#else
typedef unsigned long z89cc47ad22;
#endif
typedef void*z4affb1c7bd;
#define PAGE_SIZE (0x788+7068-0x2320) * 1024
#define z735d87d64a
typedef union{struct{uint32_t LowPart;uint32_t HighPart;};uint64_t QuadPart;}za1115a0b47;typedef struct zffee640834{LONG zfdd1bc92c7;LONG z8fea68eeff;pthread_mutex_t z84f17c487c;unsigned int zdfdfb3d659;unsigned int z18fdf10b07;}SHARED,*z80f2c590d8;typedef UCHAR BOOLEAN;typedef BOOLEAN*PBOOLEAN;
#endif
#define zf104417d39(x) sg_wait_ns(x*(0x953+2761-0x1034))
#define ze82d5b06bf(z51df7fd927, z9219142cc8, Interval) (sg_wait_ns(abs((int64_t)(*Interval.QuadPart)*(0xb6f+2051-0xf8a)) / (0x1eb1+97-0x1f08)))
#define z767cf50e81 1000000000L
#define TRUE (0x1d1+7172-0x1dd4)
#define FALSE (0xb7d+6288-0x240d)
#define INVALID_HANDLE_VALUE (0xdec+5892-0x24f0)
#define DEVICE_TYPE DWORD
#define zccdefa5e89 (0xa16+1407-0xf94)
#define zacd8a83ed4 (0x134f+2750-0x1e0b)
#define zc95fdb542a (0x1e77+826-0x21ae)
#define z6ce55bfe30 (0x565+2918-0x10c7)
#define z0cd7798a2c (0x532+155-0x5c8)
#define z5d5842aa94 (0xab0+2496-0x146a)
#define z8c6dd0c582 (0x102a+2413-0x1990)
#define zb547ec1d6b (0x965+2232-0x1215)
#define z36bbbd2891 (0x267+620-0x4ca)
#define z5bf75d856e (0x5f7+232-0x6d5)
#define zcbd64306a5 (0x10f4+4722-0x235b)
#define z4376adcd71 (0xf4+620-0x354)
#define z6cf6aebf90 (0x247+2186-0xac4)
#define za3799854eb (0x5b+2672-0xabd)
#define z60151f8131 (0x14c1+2995-0x2065)
#define z3d50fe04f0 (0x555+8271-0x2594)
#define za97d75e6fc (0x527+1744-0xbe6)
#define z4e73d46263 (0x1474+3882-0x238c)
#define z6955599125 (0x3ac+8826-0x2613)
#define z313cd1d9ec (0x2a5+3853-0x119e)
#define zc04077b15a (0x1166+3562-0x1f3b)
#define z31dd1b96bb (0x11e9+3613-0x1ff0)
#define z39e6e89985 (0xec4+3501-0x1c5a)
#define z3c1e725ce9 (0x148+8110-0x20de)
#define zd5d614e85e (0x1fec+199-0x209a)
#define zfa059ae3ff (0xff5+5702-0x2621)
#define za8e95db853 (0x64c+8326-0x26b7)
#define zb7180c3dfc (0x93d+5032-0x1cc9)
#define zc1d64e871e (0x1aea+878-0x1e3b)
#define ze4fbb53d60 (0x1b7+8794-0x23f3)
#define z9d1eeee544 (0x567+8353-0x25e9)
#define z2149a905ff (0x987+6556-0x2303)
#define zbd7fed0dc1 (0x415+2199-0xc8b)
#define z8ada55170e (0x16d1+3718-0x2535)
#define z41edd00c3e (0x6b1+6263-0x1f05)
#define zacc1242000 (0x5a7+2111-0xdc2)
#define z19a682446a (0x70f+7010-0x224c)
#define zf5ee4c97e8 (0x9cf+1387-0xf14)
#define z7e83fbd266 (0x13c8+1058-0x17c3)
#define z2c5ecd7693 (0x5df+7693-0x23c4)
#define za457af9779 (0x1249+629-0x1495)
#define z0d5c8038cd (0x11bf+4930-0x24d7)
#define zeac0ba45a4 (0x16f0+3174-0x232b)
#define zdfc2b7162f (0x131a+1897-0x1a57)
#define z3fd01fbefb (0x98b+7521-0x26bf)
#define z6f25d6604a (0x1210+4067-0x21c5)
#define z78787ed58a (0xb6a+1913-0x12b4)
#define z4fb0763e65 (0xbbc+2260-0x1460)
#define z6441429ec5 (0x1785+3109-0x2379)
#define zeac59f9bb7 (0x233+7635-0x1fd4)
#define zda5f06aa66 (0x1904+3574-0x26c7)
#define zcc97bb35bd (0x1743+2505-0x20d8)
#define z1519926a55 (0x270+3048-0xe23)
#define z62bb2552d7 (0x118f+122-0x11d3)
#define z45db24dcf5 (0xf96+245-0x1054)
#define zbdfb261dca (0x1bfd+1756-0x22a1)
#define z4f93dd8d7b (0x315+8197-0x22e1)
#define z96ccffb4fe (0x811+3374-0x1505)
#define z59f7577788 (0x187a+3558-0x2625)
#define z9be0ee6f08(z5262770c37, Function, Method, Access) ((DWORD)(((z5262770c37) << (0x1019+2325-0x191e)) | ((Access) << (0x1afd+1992-0x22b7)) | ((Function) << (0x99d+1459-0xf4e)) | (Method)))
#define zd5ce026830(zb1a67a85ad) (((DWORD)(zb1a67a85ad & 4294901760)) >> (0x18b8+2779-0x2383))
#define z445ab1a879(zb1a67a85ad) (((ULONG)(zb1a67a85ad & 16380)) >> (0x4c5+4201-0x152c))
#define z037ec4ca2d(zb1a67a85ad) (((ULONG)(zb1a67a85ad & 786432)) >> (0x89+4673-0x12bc))
#define z3febaf364d(zb1a67a85ad) (((ULONG)(zb1a67a85ad & (0xf36+2736-0x19e3))))
#define METHOD_BUFFERED (0x1c0d+2122-0x2457)
#define METHOD_IN_DIRECT (0x426+2151-0xc8c)
#define METHOD_OUT_DIRECT (0x9c5+4384-0x1ae3)
#define METHOD_NEITHER (0x1ef3+816-0x2220)
#define ze3deebe8d6 METHOD_OUT_DIRECT
#define zacbed06ba8 METHOD_IN_DIRECT
#define FILE_ANY_ACCESS (0xbb9+1928-0x1341)
#define z0b999d28ae (FILE_ANY_ACCESS)
#define FILE_READ_ACCESS ((0x190d+2875-0x2447))  
#define FILE_WRITE_ACCESS ((0x8cd+3619-0x16ee)) 
#define GENERIC_READ (0x80000000L)
#define GENERIC_WRITE (0x40000000L)
#define GENERIC_EXECUTE (0x20000000L)
#define GENERIC_ALL
#define CREATE_NEW (0xc78+1142-0x10ed)
#define CREATE_ALWAYS (0x1e70+928-0x220e)
#define OPEN_EXISTING (0x1526+3372-0x224f)
#define OPEN_ALWAYS (0x6ab+2205-0xf44)
#define TRUNCATE_EXISTING (0x6fb+2498-0x10b8)
#define FILE_SHARE_READ (0x52f+600-0x786)
#define FILE_SHARE_WRITE (0x1c6b+1861-0x23ae)
#define zca94ada7ae (0x346+6095-0x1b11)
#define FILE_ATTRIBUTE_READONLY (0xad7+6142-0x22d4)
#define FILE_ATTRIBUTE_HIDDEN (0x94+8400-0x2162)
#define FILE_ATTRIBUTE_SYSTEM (0x1687+1531-0x1c7e)
#define FILE_ATTRIBUTE_DIRECTORY (0x1752+1401-0x1cbb)
#define FILE_ATTRIBUTE_ARCHIVE (0x4e8+5702-0x1b0e)
#define z4e3f9a2ca1 (0x12f4+4380-0x23d0)
#define FILE_ATTRIBUTE_NORMAL (0xb79+5073-0x1eca)
#define FILE_ATTRIBUTE_TEMPORARY (0x1c3b+808-0x1e63)
#define z4edc2572f9 (0x13a5+4981-0x251a)
#define z947056e1af (0xf6b+2587-0x1586)
#define FILE_ATTRIBUTE_COMPRESSED (0xf96+7341-0x2443)
#define zd185c86fa1 (0x148b+7475-0x21be)
#define z9545ab5d18 (0x25ec+2115-0xe2f)
#define z9de9febf72 16384
#define FILE_NOTIFY_CHANGE_FILE_NAME (0x7e8+7272-0x244f)
#define FILE_NOTIFY_CHANGE_DIR_NAME (0x226c+39-0x2291)
#define FILE_NOTIFY_CHANGE_ATTRIBUTES (0x344+4129-0x1361)
#define FILE_NOTIFY_CHANGE_SIZE (0x1f1+3532-0xfb5)
#define FILE_NOTIFY_CHANGE_LAST_WRITE (0xcb3+4905-0x1fcc)
#define zc4c143a9b1 (0x34f+1535-0x92e)
#define z1291f4b498 (0x2249+981-0x25de)
#define FILE_NOTIFY_CHANGE_SECURITY (0x132d+2471-0x1bd4)
#define z27f8a8d405 (0x3c5+8327-0x244b)
#define z76c6e5c1af (0x416+5005-0x17a1)
#define z2e8d61c9e1 (0xa21+2878-0x155c)
#define z04018755c0 (0x403+123-0x47a)
#define z958c52582b (0x2d2+7540-0x2041)
#define MAILSLOT_NO_MESSAGE ((DWORD)-(0x6a6+5258-0x1b2f))
#define MAILSLOT_WAIT_FOREVER ((DWORD)-(0xf7a+5509-0x24fe))
#define z030fbfd29d (0x7db+3228-0x1476)
#define z9db2106a27 (0x1466+483-0x1647)
#define ze03e49d04f (0x7f9+4136-0x181d)
#define z8128e9a98f (0x15cb+3458-0x2345)
#define zf941f1c564 (0x1d72+2038-0x2558)
#define z37da56012f (0x1dd+4178-0x120f)
#define z7402db57ec (0x8cd+2570-0x1297)
#define z552a2a485a (0x13c6+335-0x1495)
#define zb9cd1c536b (0x1965+68-0x18a9)
#define z8d367ea13d 32768
#define z853ac47838 65536
#define z1c86e1ab5c 131072
#define z53b1714cd2 262144
#define z3a52f43a6a 524288
#define z826276c683 ((z7c2791ac2c)0x00000000L) 
#define z4bbb803d81 ((z7c2791ac2c)0xC0000002L)
#define zc423bd1b2a ((z7c2791ac2c)0xC000000DL)
#define STATUS_NO_MEMORY ((z7c2791ac2c)0xC0000017L)              
#define z74e0152754 ((z7c2791ac2c)0xC000009AL) 
#define z10a96a3528 ((z7c2791ac2c)0xC0000185L)
#define zaadea55ed8 ((z7c2791ac2c)0xC00000E8L)
#define za056fa1f96 ((z7c2791ac2c)0xC00000BBL)
#define STATUS_TIMEOUT ((z7c2791ac2c)(0x12d2+1503-0x17af))
#define z4a3c19962f ((z7c2791ac2c)3221225792)
#define z239f32dbb3 ((z7c2791ac2c)0xC0000182L)
#define IN
#define z938f9bb1df
#define OUT
HANDLE CreateFile(const char*z28c33e17a3,DWORD z8a9f55ef26,DWORD ze3738b3e1c,LPVOID z4ec7936099,DWORD zcf87f8241c,DWORD z0b0c9fbf45,HANDLE zd6d0b07084);BOOL CloseHandle(HANDLE z181a2f20e2);BOOL DeviceIoControl(HANDLE z181a2f20e2,DWORD z23ba06758d,LPVOID z0b2cef16eb,DWORD ze39b56d4b3,LPVOID z67fa4142ff,DWORD zd9a6438281,LPDWORD zaf23b07101,long*zc2a60f4e2a);extern DWORD z3d11ad4645;DWORD GetLastError(void);VOID zcb86b4f976(ULONG z0a85a6f1aa,ULONG z66f8156cb2,const char*z7d478506ba,...);
#if !defined(zc75f957d65)
#define zc75f957d65 (0x80b+4902-0x1b31)
#define z2bfc907fb7 (0x11a+3682-0xf7b)
#define ze4e58d4a24 (0x123a+4444-0x2395)
#define z69006351d4 (0xac8+1684-0x115a)
#define z54202e149b (0x43a+530-0x649)
#define z5e0bc118dc (0x21b1+1025-0x25ae)
#define zaf1e9e3318 (0x22+7353-0x1cd6)
#define z3b52bbf9d2 (0x8+1789-0x6ff)
#define zda7a5851ea (0x78b+2003-0xf57)
#define z87a4e2ae76 (0x659+4081-0x1642)
#define z419c9224cb (0x1163+3110-0x1d80)
#define zb22c3e395e (0xd05+2650-0x175e)
#define z01bc922099 (0x1f4+293-0x317)
#define zab281776b7 (0x3f9+2716-0xe91)
#define z800d5f67b1 (0x4ed+429-0x692)
#define z787ac248a8 (0x989+2556-0x1375)
#define z64a0ae1cf1 (0xd07+3158-0x193d)
#define zdd5578ed92 (0x1ebd+1637-0x24e2)
#define z88066fc207 (0x12d+264-0x1b5)
#endif
#define zdeca580b3f (0x796+2522-0x116d)
#define z50f7eb4283 \
    extern "C"         \
    {
#define z92325276bf }
#define __forceinline inline
#define za3489e46ce
#define z5a9b5147a2(x) (x)
#define z86d309d631(zd9e0a279fe, z32c51772d3, z32bb54c52c) malloc(z32c51772d3)
#define z31fadae0db(buffer, z32bb54c52c) free(buffer)
#define zb98e638aa5(args...) vsnprintf(args)
#define zc27478c2b9(args...) z47d3405bcc(), printf(args)
#define ze2d51ebf8f(x) ((x) >= (0xc13+2574-0x1621))
#define zb50faa0ee5 "\x46\x63\x78\x30\x64\x30\x31"
#define z66b49d31a8 std::string
#define z417567a448 vsnprintf
#define z1274a0a689(x) x
#define z5080a06de6(x) x
#define UNREFERENCED_PARAMETER(x) (x)
#define zf3a40112a2 3221225990
extern void z47d3405bcc(void);extern void z63a0821367(volatile UCHAR*Register,PUCHAR Buffer,ULONG Count);extern void z084083eca6(volatile UCHAR*Register,PUCHAR Buffer,ULONG Count);extern void zd5a11a4049(volatile z09de8108ef*Register,z69296b6d73 Buffer,ULONG Count);extern void z42eb1008df(volatile z09de8108ef*Register,z69296b6d73 Buffer,ULONG Count);extern void z59c30d7c15(volatile z09de8108ef*Register,PULONG Buffer,ULONG Count);extern void z65e4369e22(volatile z09de8108ef*Register,PULONG Buffer,ULONG Count);PVOID z126b1e69e4(z938f9bb1df za3489e46ce volatile PVOID ze5fbc5bb10,unsigned int offset);ULONG ze165fa04bb(z938f9bb1df za3489e46ce volatile PVOID ze5fbc5bb10,unsigned int offset);VOID zcdfa906161(z938f9bb1df za3489e46ce volatile PVOID ze5fbc5bb10,unsigned int offset,ULONG value);unsigned int Align(unsigned int value,unsigned int alignment);unsigned int z82870eb658(unsigned int value);unsigned int z8279913d76(unsigned int value);unsigned int z299d0e58c3(unsigned int value);unsigned int z116129441f(unsigned int dlc);typedef void*ACCESS_MASK;typedef int zfae727582e;typedef void*zbad3f66b5c;typedef void*za9150e3b66;
#define SYNCHRONIZE nullptr
extern int*z2a171abb13;
#define zbbddbdc737 nullptr
#define RtlZeroMemory(ptr, size) memset(ptr, (0x804+1639-0xe6b), size)
#define z12be324674(destination, source, length) memcpy(destination, source, length)
#define RtlCopyMemory(destination, source, length) memcpy(destination, source, length)
inline void z578fbb9a52(pthread_mutex_t*z89c0bccefa,int*Timeout){zcb86b4f976(z5e0bc118dc,zab281776b7,"%s mutex:%p\n",__FUNCTION__,(void*)z89c0bccefa);int ret=pthread_mutex_lock(z89c0bccefa);if(ret!=(0x4d6+847-0x825)){std::cerr<<"\x70\x74\x68\x72\x65\x61\x64\x5f\x6d\x75\x74\x65\x78\x5f\x6c\x6f\x63\x6b\x20\x66\x61\x69\x6c\x65\x64\x3a\x20"<<ret<<"\x2c\x20"<<strerror(ret)<<std::endl;zcb86b4f976(z69006351d4,zab281776b7,"\x70\x74\x68\x72\x65\x61\x64\x5f\x6d\x75\x74\x65\x78\x5f\x6c\x6f\x63\x6b\x20\x66\x61\x69\x6c\x65\x64\x3a\x20\x25\x69\x2c\x20\x25\x73" "\n",ret,strerror(ret));}zcb86b4f976(z5e0bc118dc,zab281776b7,"\x25\x73\x20\x6c\x6f\x63\x6b\x20\x61\x63\x71\x75\x69\x72\x65\x64" "\n",__FUNCTION__);}inline void z3c28d7b037(pthread_mutex_t*z89c0bccefa){int ret=pthread_mutex_unlock(z89c0bccefa);if(ret!=(0xacd+5192-0x1f15)){std::cerr<<"\x70\x74\x68\x72\x65\x61\x64\x5f\x6d\x75\x74\x65\x78\x5f\x75\x6e\x6c\x6f\x63\x6b\x20\x66\x61\x69\x6c\x65\x64\x3a\x20"<<ret<<"\x2c\x20"<<strerror(ret)<<std::endl;zcb86b4f976(z69006351d4,zab281776b7,"\x70\x74\x68\x72\x65\x61\x64\x5f\x6d\x75\x74\x65\x78\x5f\x75\x6e\x6c\x6f\x63\x6b\x20\x66\x61\x69\x6c\x65\x64\x3a\x20\x25\x69\x2c\x20\x25\x73" "\n",ret,strerror(ret));}zcb86b4f976(z5e0bc118dc,zab281776b7,"\x25\x73\x20\x72\x65\x6c\x65\x61\x73\x65\x64" "\n",__FUNCTION__);}z7c2791ac2c z57dd804163(HANDLE Handle,ACCESS_MASK DesiredAccess,zfae727582e z0d5820bc89,zbad3f66b5c zcb27c3c527,PVOID*Object,za9150e3b66 zbe27c3c91d);inline void z9e32894255(unsigned int zc5e10e1b11){timespec zd93a2bc15a,z70be47cfda;z70be47cfda.tv_nsec=(0x858+1929-0xfe1);z70be47cfda.tv_sec=(0x466+3814-0x134c);zd93a2bc15a.tv_nsec=zc5e10e1b11*(0x15fd+5008-0x25a5);zd93a2bc15a.tv_sec=zd93a2bc15a.tv_nsec/1000000000;zd93a2bc15a.tv_nsec=zd93a2bc15a.tv_nsec%1000000000;while((nanosleep(&zd93a2bc15a,&z70be47cfda)==-(0x170b+3908-0x264e))&&(errno==EINTR)){if(z70be47cfda.tv_nsec!=(0xc45+3472-0x19d5)||z70be47cfda.tv_sec!=(0x1081+4142-0x20af)){zd93a2bc15a=z70be47cfda;continue;}}}
#endif 
#endif 

