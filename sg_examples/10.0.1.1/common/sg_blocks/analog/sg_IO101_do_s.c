// Copyright 2006-2026 Speedgoat GmbH

#define         S_FUNCTION_LEVEL        (0x621+4254-0x16bd)
#undef          S_FUNCTION_NAME
#define         S_FUNCTION_NAME         sg_IO101_do_s
#include        <stddef.h>
#include        <stdlib.h>
#include        <stdbool.h>
#include        "simstruc.h"
#ifdef          MATLAB_MEX_FILE
#include        "mex.h"
#endif
#ifndef         MATLAB_MEX_FILE
#include        "sg_common.h"
#endif
#include "include/sg_io101_regs.h"
#include "sg_callback_legacy.h"
#include "sg_printf.h"
#define DEVNAME "\x53\x70\x65\x65\x64\x67\x6f\x61\x74\x20\x49\x4f\x31\x30\x31"
#define VENDORID (0x18f5+1120-0x680)
#define DEVICEID 17495
#define zdf24515981          ((0x154+568-0x382))
#define z942d41a49c        ssGetSFcnParam(S,(0x182c+3238-0x24d2))
#define z0cf2e207bc        ssGetSFcnParam(S,(0x40f+6245-0x1c73))
#define z7bf3bce264        ssGetSFcnParam(S,(0x675+1052-0xa8f))
#define z871352ca17          ssGetSFcnParam(S,(0x595+4884-0x18a6))
#define zb34d68df21          ssGetSFcnParam(S,(0x812+6587-0x21c9))
#define z4464f2b915           ssGetSFcnParam(S,(0x286+6176-0x1aa1))
#define zfd0a35e5cb           ssGetSFcnParam(S,(0xec+1736-0x7ae))
#define z3832b85a32           ssGetSFcnParam(S,(0x1985+543-0x1b9d))
#define z702a26a5e9                ssGetSFcnParam(S,(0x1853+1612-0x1e97))
#define ze13f49a01f           ssGetSFcnParam(S,(0xc35+2577-0x163d))
#define z2e6483d505              ((0x69d+622-0x90b))
#define zc5ce4cb81a              ((0x952+7468-0x267e))
#define z2b17e2ee3b              ((0x1a14+239-0x1b02))
#define z0194338df7         ((0xac4+2235-0x137f))
#define THRESHOLD               0.5
static char_T msg[(0x85d+3863-0x1674)];static void mdlInitializeSizes(SimStruct*S){uint32_T i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x1132+3676-0x1f8e));ssSetNumDiscStates(S,(0xbff+5524-0x2193));if((uint32_T)mxGetPr(z942d41a49c)[(0xdb3+661-0x1048)]==(0x14ca+2927-0x2038)){ssSetNumInputPorts(S,mxGetN(z0cf2e207bc));for(i=(0x15fc+3689-0x2465);i<mxGetN(z0cf2e207bc);i++){ssSetInputPortWidth(S,i,(0x8d+1517-0x679));ssSetInputPortDirectFeedThrough(S,i,(0x15c+3225-0xdf4));ssSetInputPortDataType(S,i,SS_DOUBLE);ssSetInputPortRequiredContiguous(S,i,(0x914+2147-0x1176));}}else{ssSetNumInputPorts(S,mxGetN(z7bf3bce264));for(i=(0x1fb6+328-0x20fe);i<mxGetN(z7bf3bce264);i++){ssSetInputPortWidth(S,i,(0xe2a+2003-0x15fc));ssSetInputPortDirectFeedThrough(S,i,(0x9af+4240-0x1a3e));ssSetInputPortDataType(S,i,SS_DOUBLE);ssSetInputPortRequiredContiguous(S,i,(0x1b2+6272-0x1a31));}}ssSetNumOutputPorts(S,(0x1fb3+1770-0x269d));ssSetNumSampleTimes(S,(0xacb+6271-0x2349));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x1d9b+1562-0x23b5));ssSetNumNonsampledZCs(S,(0xfaa+5959-0x26f1));for(i=(0x1bf0+773-0x1ef5);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x4ca+1269-0x9bf));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0xa8b+3855-0x199a)]==-1.0){ssSetSampleTime(S,(0xac4+2254-0x1392),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x144+6607-0x1b13),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x2120+96-0x2180),mxGetPr(z3832b85a32)[(0x1b4f+909-0x1edc)]);ssSetOffsetTime(S,(0xa42+5117-0x1e3f),0.0);}}
#define MDL_START
static void mdlStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
sg_PCIDevice zeccbadd9b3;volatile uint32_T*za42cf7dd4a;int moduleId=(int)mxGetScalar(ze13f49a01f);if((int_T)mxGetPr(z702a26a5e9)[(0x786+1297-0xc97)]<(0xd81+6076-0x253d)){if(sg_findPciDevice(&zeccbadd9b3,DEVNAME,VENDORID,DEVICEID,SG_NO_SUB,SG_NO_SUB,moduleId,SG_NO_BUS_SLOT,SG_NO_BUS_SLOT)){ssSetErrorStatus(S,pSgErrorStr);return;}}else{int_T bus,slot;if(mxGetN(z702a26a5e9)==(0x60d+1447-0xbb3)){bus=(0x270+7685-0x2075);slot=(int_T)mxGetPr(z702a26a5e9)[(0x1a41+723-0x1d14)];}else{bus=(int_T)mxGetPr(z702a26a5e9)[(0x1f80+1653-0x25f5)];slot=(int_T)mxGetPr(z702a26a5e9)[(0x1c46+2514-0x2617)];}if(sg_findPciDevice(&zeccbadd9b3,DEVNAME,VENDORID,DEVICEID,SG_NO_SUB,SG_NO_SUB,moduleId,bus,slot)){ssSetErrorStatus(S,pSgErrorStr);return;}}za42cf7dd4a=(volatile uint32_T*)sg_mapMemory(&zeccbadd9b3,(0xc75+6141-0x2472));ssSetPWorkValue(S,z0194338df7,(void*)za42cf7dd4a);
#endif
}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){
#ifndef MATLAB_MEX_FILE
volatile uint32_T*za42cf7dd4a=ssGetPWorkValue(S,z0194338df7);uint32_T i;uint_T z718c4c15f4,channel;uint32_T data;real_T*zc7fdaf6331;data=za42cf7dd4a[z1c7b619405];if((uint32_T)mxGetPr(z942d41a49c)[(0x1d3+2314-0xadd)]==(0xf64+2567-0x196a)){data&=4294967040;z718c4c15f4=(0x62a+4120-0x1642);for(i=(0x1a7+5709-0x17f4);i<mxGetN(z0cf2e207bc);i++){channel=(uchar_T)mxGetPr(z0cf2e207bc)[i]-(0x46d+2102-0xca2);zc7fdaf6331=(real_T*)ssGetInputPortRealSignal(S,i);if(zc7fdaf6331[(0x225+2374-0xb6b)]>=THRESHOLD){z718c4c15f4|=(0x1bab+59-0x1be5)<<channel;}}za42cf7dd4a[z1c7b619405]=data|z718c4c15f4;}else{data&=4294902015;z718c4c15f4=(0xc83+5428-0x21b7);for(i=(0x188+1678-0x816);i<mxGetN(z7bf3bce264);i++){channel=(uchar_T)mxGetPr(z7bf3bce264)[i]-(0x79c+55-0x7d2);zc7fdaf6331=(real_T*)ssGetInputPortRealSignal(S,i);if(zc7fdaf6331[(0xaf7+3933-0x1a54)]>=THRESHOLD){z718c4c15f4|=(0x6e4+5544-0x1c8b)<<channel;}}za42cf7dd4a[z1c7b619405]=data|(z718c4c15f4<<(0x1b5d+1910-0x22cb));}
#endif
}static void mdlTerminate(SimStruct*S){
#ifndef MATLAB_MEX_FILE
volatile uint32_T*za42cf7dd4a=ssGetPWorkValue(S,z0194338df7);uint16_T i;real_T out;uint32_T channel;uint32_T z718c4c15f4,data;z718c4c15f4=(0x3ad+2730-0xe57);data=za42cf7dd4a[z1c7b619405];if((uint32_T)mxGetPr(z942d41a49c)[(0x1360+4343-0x2457)]==(0x52f+7254-0x2184)){data&=4294967040;for(i=(0x18d0+886-0x1c46);i<mxGetN(z0cf2e207bc);i++){if(sg_isModelInit()||(int)mxGetPr(z871352ca17)[i]){channel=(uint32_T)mxGetPr(z0cf2e207bc)[i]-(0x90c+5413-0x1e30);out=(real_T)mxGetPr(z4464f2b915)[i];if(out>=THRESHOLD){z718c4c15f4|=(0xdaa+1659-0x1424)<<channel;}}}za42cf7dd4a[z1c7b619405]=data|z718c4c15f4;}else{data&=4294902015;for(i=(0xfc+8486-0x2222);i<mxGetN(z7bf3bce264);i++){if(sg_isModelInit()||(int)mxGetPr(zb34d68df21)[i]){channel=(uint32_T)mxGetPr(z7bf3bce264)[i]-(0x5bd+1928-0xd44);out=(real_T)mxGetPr(zfd0a35e5cb)[i];if(out>=THRESHOLD){z718c4c15f4|=(0xd8f+27-0xda9)<<channel;}}}za42cf7dd4a[z1c7b619405]=data|(z718c4c15f4<<(0x1227+4963-0x2582));}
#endif
}
#include "sg_sfcn_glue.h"   

