// Copyright 2006-2026 Speedgoat GmbH

#ifndef za6058e64de
#define za6058e64de
#include <stdbool.h>
#include "simstruc.h"
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#else
#include "sg_common.h"
#endif
#include <stdint.h>
#include "sg_error.h"
#include "sg_param.h"
static const char*const DEVNAME[]={"\x53\x70\x65\x65\x64\x67\x6f\x61\x74\x20\x49\x4f\x32\x39\x31\x2d\x48\x53","\x53\x70\x65\x65\x64\x67\x6f\x61\x74\x20\x49\x4f\x32\x39\x31\x2d\x4c\x53","\x53\x70\x65\x65\x64\x67\x6f\x61\x74\x20\x49\x4f\x32\x39\x30"};static const int VENDORID=18767;static const int SUBVENDORID=18767;static const int DEVICEID[]={(0xb24+3244-0x16bf),(0x5b4+6410-0x1dac),(0xb0c+4937-0x1d54)};static const int SUBDEVICEID[]={(0x5f9+747-0x7d3),(0x13b3+1072-0x16d1),(0x1cb+7349-0x1d80)};
#define z28d8d3124b         ((0x484+1648-0xaf4))
#define z8a371741a5     ((0x5cc+7224-0x2203))
#define ze358b1d836        ((0x66c+4493-0x17e9))
#define zd138e6a92f         ((0x1ce4+652-0x1f5f))
#define z48eba9dc8f         ((0x9ea+6670-0x23d0))
#define z3b46633574          ((0x1c6a+2563-0x2644))
#define z6b7e9ee97c   ((0x189+6687-0x1ba8))
#define z27f0654ef7  ((0x43b+8141-0x2407))
#define z1102d3b44a  "\x49\x4f\x32\x39\x31\x2d\x48\x53"
#define z0e5df46beb  "\x49\x4f\x32\x39\x31\x2d\x4c\x53"
#define zdf5cf40b05	"\x49\x4f\x32\x39\x30"
typedef struct{int z2e605bbf33;SgParam_IntVec*zfba97307b4;int moduleId;SgParam_IntVec*zba026642cf;int z914cf542a7;}zfb6915538d;typedef struct{int z2e605bbf33;int moduleId;int sampleTime;SgParam_IntVec*zfba97307b4;SgParam_IntVec*zba026642cf;SgParam_DoubleVec*zaad20b7839;SgParam_BoolVec*zd2fdf499e5;int z914cf542a7;}ze826deae6f;typedef struct{int z2e605bbf33;int moduleId;int sampleTime;SgParam_IntVec*zfba97307b4;SgParam_IntVec*ze78fe53602;SgParam_DoubleVec*zbc9f76727a;SgParam_BoolVec*z2b20820faa;int z914cf542a7;}zd12c486dc7;typedef struct{int z2e605bbf33;int moduleId;int sampleTime;SgParam_IntVec*zfba97307b4;SgParam_IntVec*z0dcf9b37c9;int z914cf542a7;}zf6056b30e2;typedef struct{int z2e605bbf33;int moduleId;int sampleTime;SgParam_IntVec*zfba97307b4;SgParam_IntVec*z21a0c6aad6;int z914cf542a7;}z6beb14870a;typedef struct{const char*z9a1876ef4c;int moduleId;uint16_t zc10e8d2264;SgError*error;zfb6915538d*z7a48f1e12c;ze826deae6f*za3308a91b2;zd12c486dc7*zd477607148;zf6056b30e2*z9b320392db;z6beb14870a*z47dd4fd31b;}zac36a3c7c4;typedef struct{int z2e605bbf33;int moduleId;const SgParam_IntVec*zfba97307b4;int z914cf542a7;}zc4fb565021;extern zac36a3c7c4*za2e2f109d9(void);extern void z5b012c1c56(zac36a3c7c4*zae10e3f17f);extern int z6058695f7b(zac36a3c7c4*zae10e3f17f,const zc4fb565021*args);extern void zb1e7d711fd(zac36a3c7c4*zae10e3f17f);extern uint8_t zd2d58e2e2c(zac36a3c7c4*zae10e3f17f,uint16_t zcc15bcc791);extern void z7b8313fc2d(zac36a3c7c4*zae10e3f17f,uint16_t zcc15bcc791,uint8_t value);extern void zae1f544514(ze826deae6f*params);extern void z6766f2c4e7(zd12c486dc7*params);extern void z9ecd4d10c4(zf6056b30e2*params);extern void z4323bd91b2(z6beb14870a*params);
#endif  

