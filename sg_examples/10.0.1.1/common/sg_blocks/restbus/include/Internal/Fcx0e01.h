// Copyright 2006-2026 Speedgoat GmbH

#ifndef z44f02195d0
#define z44f02195d0
#ifdef _WIN32
#ifndef zf337073605
#define zf337073605 __stdcall
#endif
#ifdef z545ff2a924
#define zd8669200f7 extern "C" __declspec(dllexport)
#else
#if defined(__cplusplus)
#define zd8669200f7 extern "C" __declspec(dllimport)
#else
#define zd8669200f7 __declspec(dllimport)
#endif
#endif
#else
#ifndef zf337073605
#define zf337073605
#endif
#ifdef z545ff2a924
#define zd8669200f7 extern "C" __attribute__((z08edd5ea13("\x64\x65\x66\x61\x75\x6c\x74")))
#else
#if defined(__cplusplus)
#define zd8669200f7 extern "C"
#else
#define zd8669200f7
#endif
#endif
#endif
#if _WIN32 || _WIN64
#if _WIN64
#define z9dab14899b
#else
#define zfbe727c5d0
#endif
#endif
#if __GNUC__
#if __x86_64__ || __ppc64__
#define z9dab14899b
#else
#define zfbe727c5d0
#endif
#endif
typedef enum z6c3a8b10f7{z0f3e60e63e,}z6c3a8b10f7;typedef enum z36edeb1e74{z6c022daac3,z04e7d1f02a,z73a03c04b7,}z36edeb1e74;typedef void*z6b0de95b9a;typedef unsigned char zf127cebf70;typedef unsigned char z661d5ab3fe;typedef unsigned short z93cb5c7721;typedef unsigned int zbf3274f471;typedef unsigned long long z8066bee665;
#pragma pack(push, r1, 8)
typedef struct z458e0b78f7{zbf3274f471 Major;zbf3274f471 Minor;zbf3274f471 Update;zbf3274f471 Release;}z458e0b78f7;typedef struct zc0e1768950{z8066bee665 z280cd21842;z36edeb1e74 Type;z8066bee665 zffae39c454;z458e0b78f7 z8332f29f27;z458e0b78f7 zcb87cb3c4b;z458e0b78f7 zd92041529d;struct zc0e1768950*z213404fc00;}zc0e1768950;
#pragma pack(pop, r1)
typedef enum zb344436e56{z9b970565ba=(0x4f7+2946-0x1079),z45fcbfeea6=(0x10f3+2677-0x1b67),zc73f6249dd=(0xa6a+6622-0x2446),}zb344436e56;typedef enum z99dd7da85e{NONE=(0x1797+3367-0x24be),z24c39e97c5=(0xcff+5122-0x2100),z7f43ce65c9,z9287624a21,ze9e5186abc,z7a608b698a,ze395ce5988,z4969131979,}z99dd7da85e;zd8669200f7 z99dd7da85e zf337073605 fcxGetDevices(zc0e1768950**z5f83503df4,int moduleId);zd8669200f7 z99dd7da85e zf337073605 fcxOpen(z6b0de95b9a*z898d3603c5,z8066bee665 zf528bd284e);zd8669200f7 z99dd7da85e zf337073605 fcxClose(z6b0de95b9a handle);zd8669200f7 z99dd7da85e zf337073605 fcxTunnelWrite(z6b0de95b9a handle,const z661d5ab3fe*z71f4cd9753,zbf3274f471 z7a5bff3fe2,zbf3274f471*z0de52af43c,zbf3274f471 zc84e1bb7af,zbf3274f471 zddfead20c0);zd8669200f7 z99dd7da85e zf337073605 fcxTunnelRead(z6b0de95b9a handle,z661d5ab3fe*byte,zbf3274f471 bufferLength,zbf3274f471*zcb35c6a930,zbf3274f471*zc84e1bb7af,zbf3274f471*zddfead20c0);zd8669200f7 z99dd7da85e zf337073605 fcxTunnelReset(z6b0de95b9a handle);zd8669200f7 z99dd7da85e zf337073605 fcxHpsReset(z6b0de95b9a handle);zd8669200f7 z99dd7da85e zf337073605 z5a6f39e9e3(const z6c3a8b10f7,void*p);zd8669200f7 z99dd7da85e zf337073605 zbafd278626(z6b0de95b9a handle,z661d5ab3fe*byte,zbf3274f471 bufferLength,zbf3274f471*zcb35c6a930,bool zbcf0c35b49);
#endif 

