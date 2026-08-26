// Copyright 2006-2026 Speedgoat GmbH

#ifndef z1fca830782
#define z1fca830782
#define z41c10a4f5f
#define z8d6ea808ad (0x4c2+7354-0x217b)
#define RAW (0x963+2011-0x113c)
#define z19832ebff1 (0xc71+927-0x100d)
#define CAN (0x571+2469-0xf15)
#define CANFD (0xcda+112-0xd48)
#define z7371dee8d9 (0x61c+3756-0x14c8)
#define z93b0b0dad8 (0x847+5535-0x1de5)
#define z33a7e132e9 (0xa35+2316-0x1340)
#define za1fb0b66a0 (0x14fd+3384-0x2233) 
#define z8daf43954d (0x32a+6732-0x1d73)
#define z029d5a18e9 (0xcbd+2121-0x1506)
#define z03e859192c (0x107c+125-0x10f8)
#define z7752b55472 (0x1dc2+1929-0x2549)
#define z41e529036d (0x65d+5935-0x1d8c)
#define zc715a7c5e8(Module, Id, zf67982ee78, z0bdbf8b480, z5f7f100032, z84eb0d0e41) \
    sg_mod_info *mod_info = sg_module_get_single(Module, Id); \
    if (!mod_info) \
    { \
        sprintf(z41efa4f0cd, "\x54\x79\x70\x65\x20\x25\x64\x2c\x20\x49\x44\x20\x25\x64\x20\x25\x73\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79", Module, Id, z0bdbf8b480); \
        ssSetErrorStatus(S, z41efa4f0cd); \
        return; \
    } \
    \
    z5f7f100032 = reinterpret_cast<ESD_Module *>(sg_module_get_custom_data(Module, Id)); \
    \
    \
    z84eb0d0e41 = sg_block_register_with_uid(mod_info, zf67982ee78, (uintptr_t)S); \
    if (!z84eb0d0e41) \
    { \
        sprintf(z41efa4f0cd, "\x54\x79\x70\x65\x20\x25\x73\x20\x25\x73\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x67\x69\x73\x74\x65\x72\x20\x62\x6c\x6f\x63\x6b\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x28\x6d\x6f\x64\x75\x6c\x65\x20\x74\x79\x70\x65\x20\x25\x64\x2c\x20\x49\x44\x20\x25\x64\x29" "\n", #zf67982ee78, z0bdbf8b480, Module, Id); \
        ssSetErrorStatus(S, z41efa4f0cd); \
        return; \
    }
#define zb13ee7f728(Module, Id, zf67982ee78, z0bdbf8b480, z84eb0d0e41) \
    sg_mod_info *mod_info = sg_module_get_single(Module, Id);\
    if (!mod_info)\
    {\
        sprintf(z41efa4f0cd, "\x54\x79\x70\x65\x20\x25\x64\x2c\x20\x49\x44\x20\x25\x64\x20\x73\x67\x5f\x4d\x6f\x64\x65\x6c\x53\x74\x65\x70\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79", Module, Id);\
        ssSetErrorStatus(S, z41efa4f0cd);\
        return;\
    }\
    \
    z05264739a1 = sg_block_get_by_uid(mod_info, zf67982ee78, (uintptr_t)S);\
    if (!z05264739a1)\
    {\
        sprintf(z41efa4f0cd, "\x54\x79\x70\x65\x20\x25\x73\x20\x25\x73\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x62\x6c\x6f\x63\x6b\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x28\x6d\x6f\x64\x75\x6c\x65\x20\x74\x79\x70\x65\x20\x25\x64\x2c\x20\x49\x44\x20\x25\x64\x29" "\n", #zf67982ee78, z0bdbf8b480, Module, Id);\
        ssSetErrorStatus(S, z41efa4f0cd);\
        return;\
    }
enum ze6cef91778{zee3e1cecfe,z76c6d18be6,z93889c3854,CAN_STATUS,z1ebeafa0bc,z8ab33b6fd7,zb102eea5ee,DO};
#undef WIN32
#undef z6cadf57691
#undef _WIN32
#include "simstruc.h"
#include "ESD_OfA_datatypes.h"
#include "CANFD_Message_Definition.h"
#include "CAN_Message_Definition.h"
#include "sg_blocks/common/libsg/sg_param.h"
typedef struct{int boardType;int moduleId;int sampleTime;SgParam_DoubleVec*z633f10f226;int z312de21d54;int z7bf9e09a7a;int z3d68200d9c;}z5b80e69c07;typedef struct{int boardType;int moduleId;int sampleTime;SgParam_DoubleVec*z7cf8cde3ca;int z3e398bddf3;int z3eee1086a8;}z969c25e079;
#ifndef MATLAB_MEX_FILE
#include "sg_printf.h"
#if !defined(NTLIN_H_) && !defined(_NTLIN_H_)
#include "../lib/include/ntlin.h"
#endif
#if !defined(NTCAN_H_) && !defined(_NTCAN_H_)
#include "../lib/include/ntcan.h"
#endif
class ESD_Module;class z5bb7e7233c;class zde6535072f;class zc9fa8a75f5;
#include "sg_time.h"
#include "IoModuleRegistry.h"
typedef struct zf199a43644{ESD_Module*module;EVMSG*evmsg;zb529d466d7*zdf046c2413;zd441a5253a*z91db17dcc6;int z56e11564f5;}zee381ecad1;typedef struct zbc65a2f03d{double*z955edc215f;double*z05c7d453bd;CMSG_X*zb1fa780a09;NTCAN_HANDLE zd52824a365;}z2b853047a8;typedef struct zd75c2e8bf8{uint32_t*z51398271a0;}z29838dbece;typedef struct ze5f49a2df2{CMSG_X*cmsg;NTCAN_FORMATEVENT_PARAMS*para;NTCAN_BAUDRATE_X*baud;double*z955edc215f;double*z05c7d453bd;NTCAN_HANDLE handle;NTCAN_HANDLE z83a8aa870b;double z5d1dc1a1ee;}z7bc6dcf575;typedef struct zd64df4bd2f{double*z955edc215f;double*z05c7d453bd;}z42182ae588;typedef struct zf88651bb08{z969c25e079*params;zb529d466d7*zdf046c2413;EVMSG*evmsg;NTCAN_HANDLE handle;}zbf49808d68;typedef struct z563d62c541{z5b80e69c07*params;zb529d466d7*zdf046c2413;EVMSG*evmsg;NTCAN_HANDLE handle;}z51dacf88d5;extern uint64_t z0253a90535;extern int z11b6e53507;sg_mod_info*ze1aeb1562e(int module,int id,int zcab18afec3,int Bus,int Slot,SimStruct*S);sg_mod_info*z83f9d86feb(int module,int id);void zebaa5a2f8b(int module,int id);void z9cecc65016(z9427b84bed*ze2ce73de92);void z08a1f62323(z9427b84bed*zf333e5328e,CMSG_X*zb1fa780a09);void z34c0874290(CMSG_X*zb1fa780a09,CANMsg*z4ca265854f,double*z955edc215f,double*z05c7d453bd,SimStruct*S);void zed717ac691(CANMsg*z204ecb8842,CMSG_X*zb1fa780a09);void z7b233bcfd4(CMSG_X*zb1fa780a09,CanFdMessage*z4ca265854f,double*z955edc215f,double*z05c7d453bd,SimStruct*S);void z5d536a09bb(CanFdMessage*z204ecb8842,CMSG_X*zb1fa780a09);void za35219a4b6(const zb772849ce5*z40c568487d,int*out);void zf10d2a0b5c(const double*array,double N,zd441a5253a*z91db17dcc6);
#ifdef __linux__
int zb3227ff971(int bus,int slot,int z0add1d1c25,int*z4c08138eac);
#endif
#endif 
#define z9fe96ce105(x) (mxGetPr(ssGetSFcnParam(S, x)))
#define z09263dafad(x) (mxGetN(ssGetSFcnParam(S, x)))
#define z4c1a02abaf(x) (mxGetM(ssGetSFcnParam(S, x)))
#endif 

