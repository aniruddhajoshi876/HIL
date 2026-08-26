// Copyright 2006-2026 Speedgoat GmbH

#define     S_FUNCTION_LEVEL    (0x154+8317-0x21cf)
#undef      S_FUNCTION_NAME
#define     S_FUNCTION_NAME     sg_IO101_da_s
#include    <stddef.h>
#include    <stdlib.h>
#include    <stdbool.h>
#include    "simstruc.h"
#ifdef      MATLAB_MEX_FILE
#include    "mex.h"
#endif
#ifndef         MATLAB_MEX_FILE
#include        "sg_common.h"
#endif
#include "include/sg_io101_regs.h"
#include "sg_callback_legacy.h"
#include "sg_printf.h"
#define DEVNAME "\x53\x70\x65\x65\x64\x67\x6f\x61\x74\x20\x49\x4f\x31\x30\x31"
#define VENDORID (0x1840+1857-0x8ac)
#define DEVICEID 17495
#define zdf24515981          ((0x19e8+1524-0x1fd6))
#define za9d8fb6bcf             ssGetSFcnParam(S,(0x1101+900-0x1485))
#define zc8bbaa6115               ssGetSFcnParam(S,(0x378+1222-0x83d))
#define zae7f89439f                ssGetSFcnParam(S,(0x7ca+2241-0x1089))
#define z3832b85a32           ssGetSFcnParam(S,(0xf06+2557-0x1900))
#define z702a26a5e9                ssGetSFcnParam(S,(0x16af+1872-0x1dfb))
#define ze13f49a01f           ssGetSFcnParam(S,(0x1fa+5937-0x1926))
#define z2e6483d505              ((0x5+7750-0x1e4a))
#define z7e2eeaa57c          ((0x22f3+779-0x25fe))
#define zc5ce4cb81a              ((0x1ebb+1249-0x238c))
#define z2b17e2ee3b              ((0x4e9+6719-0x1f27))
#define z0194338df7         ((0xd41+4942-0x208f))
static char_T msg[(0x2bb+1238-0x691)];
#ifndef MATLAB_MEX_FILE
static void z14abefc6ac(volatile uint32_T*za42cf7dd4a,SimStruct*S){int i;for(i=(0x2b9+1933-0xa46);!(za42cf7dd4a[ze4eca519da]&(0xc9b+370-0xe0c));i++){if(i>100000){sprintf(msg,"\x25\x73\x20\x63\x61\x6c\x69\x62\x72\x61\x74\x69\x6f\x6e\x20\x64\x61\x74\x61\x20\x72\x65\x74\x72\x69\x65\x76\x61\x6c\x20\x74\x69\x6d\x65\x64\x20\x6f\x75\x74",DEVNAME);ssSetErrorStatus(S,msg);return;}sg_wait_ns((0x232a+1798-0x2648));}}static void ze60f8e9903(uint32_T channel,real_T*zd3add15c40,real_T*zbd0243c03e,volatile uint32_T*za42cf7dd4a,SimStruct*S){uint32_T z7be9105675,z548bd6fb7c;int16_T offset,z0754dd67cc;z548bd6fb7c=channel*(0x1206+1116-0x165e)+(0x17a9+1925-0x1f2d);za42cf7dd4a[z16268937aa]=((0x2a5+9235-0x26b7)<<(0x29+990-0x3f8))|(z548bd6fb7c<<(0xc70+5282-0x210a));z14abefc6ac(za42cf7dd4a,S);z7be9105675=(za42cf7dd4a[ze4eca519da]>>(0x1c1b+1990-0x23d9))&(0x1fed+710-0x21b4);sg_wait_s(0.001);z548bd6fb7c=channel*(0x16db+2101-0x1f0c)+(0x1496+2164-0x1d0a);za42cf7dd4a[z16268937aa]=((0xa9c+2514-0x146d)<<(0xbab+1794-0x129e))|(z548bd6fb7c<<(0x24d+5399-0x175c));z14abefc6ac(za42cf7dd4a,S);z7be9105675=(za42cf7dd4a[ze4eca519da]&65280)|z7be9105675;offset=(int16_T)z7be9105675;sg_wait_s(0.001);z548bd6fb7c=channel*(0x7da+741-0xabb)+(0x131+4093-0x112b);za42cf7dd4a[z16268937aa]=((0x889+2924-0x13f4)<<(0x135a+2264-0x1c23))|(z548bd6fb7c<<(0xea7+2785-0x1980));z14abefc6ac(za42cf7dd4a,S);z7be9105675=(za42cf7dd4a[ze4eca519da]>>(0x934+1694-0xfca))&(0x1c54+2973-0x26f2);sg_wait_s(0.001);z548bd6fb7c=channel*(0x1b4+1115-0x60b)+(0x8bb+1068-0xce5);za42cf7dd4a[z16268937aa]=((0x136a+3479-0x2100)<<(0x1eda+12-0x1ed7))|(z548bd6fb7c<<(0xcef+6499-0x264a));z14abefc6ac(za42cf7dd4a,S);z7be9105675=(za42cf7dd4a[ze4eca519da]&65280)|z7be9105675;z0754dd67cc=(int16_T)z7be9105675;sg_wait_s(0.001);*zd3add15c40=((z0754dd67cc/1.0e6)+(0x1a57+3188-0x26ca))*3276.75;*zbd0243c03e=offset/100.0;}
#endif
static void mdlInitializeSizes(SimStruct*S){uint32_T i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x1f00+1244-0x23dc));ssSetNumDiscStates(S,(0x229+5219-0x168c));ssSetNumOutputPorts(S,(0x2170+1372-0x26cc));ssSetNumInputPorts(S,(int)mxGetN(za9d8fb6bcf));for(i=(0xbd6+6332-0x2492);i<(int)mxGetN(za9d8fb6bcf);i++){ssSetInputPortWidth(S,i,(0x1bd8+1826-0x22f9));ssSetInputPortDirectFeedThrough(S,i,(0x1a4+3006-0xd61));ssSetInputPortRequiredContiguous(S,i,(0xf9+1666-0x77a));}ssSetNumSampleTimes(S,(0x1204+426-0x13ad));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x596+6785-0x2017));ssSetNumNonsampledZCs(S,(0x1cd4+322-0x1e16));for(i=(0x923+3317-0x1618);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x62d+466-0x7ff));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x18e5+1031-0x1cec)]==-1.0){ssSetSampleTime(S,(0x798+4010-0x1742),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0xf3b+3405-0x1c88),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x6cb+4610-0x18cd),mxGetPr(z3832b85a32)[(0x494+1987-0xc57)]);ssSetOffsetTime(S,(0x21fb+651-0x2486),0.0);}}
#define MDL_START
static void mdlStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
sg_PCIDevice zeccbadd9b3;volatile uint32_T*za42cf7dd4a;uint16_T zf91d71c6d9=(uint16_T)mxGetN(za9d8fb6bcf);int moduleId=(int)mxGetScalar(ze13f49a01f);if((int_T)mxGetPr(z702a26a5e9)[(0x242d+504-0x2625)]<(0x1a6b+2792-0x2553)){if(sg_findPciDevice(&zeccbadd9b3,DEVNAME,VENDORID,DEVICEID,SG_NO_SUB,SG_NO_SUB,moduleId,SG_NO_BUS_SLOT,SG_NO_BUS_SLOT)){ssSetErrorStatus(S,pSgErrorStr);return;}}else{uint16_T bus,slot;if(mxGetN(z702a26a5e9)==(0x722+6954-0x224b)){bus=(0x172b+2212-0x1fcf);slot=(uint16_T)mxGetPr(z702a26a5e9)[(0x2f7+3829-0x11ec)];}else{bus=(uint16_T)mxGetPr(z702a26a5e9)[(0x3f0+663-0x687)];slot=(uint16_T)mxGetPr(z702a26a5e9)[(0xb71+3579-0x196b)];}if(sg_findPciDevice(&zeccbadd9b3,DEVNAME,VENDORID,DEVICEID,SG_NO_SUB,SG_NO_SUB,moduleId,bus,slot)){ssSetErrorStatus(S,pSgErrorStr);return;}}za42cf7dd4a=(volatile uint32_T*)sg_mapMemory(&zeccbadd9b3,(0x844+4765-0x1ae1));ssSetPWorkValue(S,z0194338df7,(void*)za42cf7dd4a);ssSetIWorkValue(S,z7e2eeaa57c,zf91d71c6d9);{uint32_T i;real_T zd3add15c40,zbd0243c03e;for(i=(0x3b6+8955-0x26b1);i<(0x7f8+6132-0x1fe4);i++){ze60f8e9903(i,&zd3add15c40,&zbd0243c03e,za42cf7dd4a,S);ssSetRWorkValue(S,i*(0x101d+5790-0x26b9),zd3add15c40);ssSetRWorkValue(S,i*(0x1757+66-0x1797)+(0x140a+3829-0x22fe),zbd0243c03e);}}
#endif
}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){
#ifndef MATLAB_MEX_FILE
volatile uint32_T*za42cf7dd4a=ssGetPWorkValue(S,z0194338df7);uint16_T zf91d71c6d9=ssGetIWorkValue(S,z7e2eeaa57c);uint16_T i;real_T*zc7fdaf6331;int32_T out;uint16_T channel;real_T zd3add15c40,zbd0243c03e;uint16_T first;first=(0x26f+9186-0x2650);for(i=(0x119d+554-0x13c7);i<zf91d71c6d9;i++){if(first){first=(0xdef+1996-0x15bb);}else{za42cf7dd4a[z0a43a53ea7]=(uint32_T)out;}channel=(uint16_T)mxGetPr(za9d8fb6bcf)[i]-(0x954+2789-0x1438);zd3add15c40=ssGetRWorkValue(S,channel*(0x3a7+8667-0x2580));zbd0243c03e=ssGetRWorkValue(S,channel*(0xa7+918-0x43b)+(0x114d+2832-0x1c5c));zc7fdaf6331=(real_T*)ssGetInputPortRealSignal(S,i);out=(int32_T)(((zc7fdaf6331[(0xdf0+5936-0x2520)]+10.0)*zd3add15c40)-zbd0243c03e);if(out>65535){out=65535;}if(out<(0x1284+3927-0x21db)){out=(0x77+1321-0x5a0);}out=out|(channel<<(0x2d5+7935-0x21c4));}out=out|((0x1e3+6874-0x1cbc)<<(0x105+3413-0xe47));za42cf7dd4a[z0a43a53ea7]=(uint32_T)out;za42cf7dd4a[z5eec49dc7c]=(0x19aa+168-0x1a51);
#endif
}static void mdlTerminate(SimStruct*S){
#ifndef MATLAB_MEX_FILE
volatile uint32_T*za42cf7dd4a=ssGetPWorkValue(S,z0194338df7);uint16_T zf91d71c6d9=ssGetIWorkValue(S,z7e2eeaa57c);uint16_T i;int32_T out;uint16_T channel;real_T zd3add15c40,zbd0243c03e;uint16_T first;if(sg_isModelInit()){za42cf7dd4a[z216a802cff]=(0x226+2318-0xb14);first=(0x3e3+4370-0x14f4);for(channel=(0x1238+1377-0x1799);channel<(0x1067+4259-0x2102);channel++){if(first){first=(0x6d1+7588-0x2475);}else{za42cf7dd4a[z0a43a53ea7]=(uint32_T)out;}zd3add15c40=ssGetRWorkValue(S,channel*(0x5e5+7207-0x220a));zbd0243c03e=ssGetRWorkValue(S,channel*(0xfff+3326-0x1cfb)+(0x7b7+6021-0x1f3b));out=(int32_T)((10.0*zd3add15c40)-zbd0243c03e);if(out>65535){out=65535;}if(out<(0x11e4+1255-0x16cb)){out=(0x12b+4522-0x12d5);}out=out|(channel<<(0x745+7917-0x2622));}out=out|((0x123a+204-0x1305)<<(0x11c7+353-0x1315));za42cf7dd4a[z0a43a53ea7]=(uint32_T)out;za42cf7dd4a[z216a802cff]=(0x1df+5289-0x1687);za42cf7dd4a[z5eec49dc7c]=(0xbea+336-0xd39);}sg_wait_s(0.0001);first=(0xa79+6419-0x238b);for(i=(0xcf+4242-0x1161);i<zf91d71c6d9;i++){if(sg_isModelInit()||(int)mxGetPr(zc8bbaa6115)[i]){if(first){first=(0x5a3+7570-0x2335);}else{za42cf7dd4a[z0a43a53ea7]=(uint32_T)out;}channel=(uint16_T)mxGetPr(za9d8fb6bcf)[i]-(0xc15+6491-0x256f);zd3add15c40=ssGetRWorkValue(S,channel*(0x1679+3657-0x24c0));zbd0243c03e=ssGetRWorkValue(S,channel*(0x804+2244-0x10c6)+(0x80c+2516-0x11df));out=(int32_T)((((real_T)mxGetPr(zae7f89439f)[i]+10.0)*zd3add15c40)-zbd0243c03e);if(out>65535){out=65535;}if(out<(0x1ad3+2131-0x2326)){out=(0x1ca5+1428-0x2239);}out=out|(channel<<(0x211b+685-0x23b8));}}out=out|((0x1bab+1941-0x233f)<<(0x75d+1437-0xce7));za42cf7dd4a[z0a43a53ea7]=(uint32_T)out;za42cf7dd4a[z5eec49dc7c]=(0xe85+1863-0x15cb);
#endif
}
#include "sg_sfcn_glue.h"   

