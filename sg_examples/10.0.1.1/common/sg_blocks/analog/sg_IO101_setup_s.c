// Copyright 2006-2026 Speedgoat GmbH

#define     S_FUNCTION_LEVEL    (0x69b+2555-0x1094)
#undef      S_FUNCTION_NAME
#define     S_FUNCTION_NAME     sg_IO101_setup_s
#include    <stddef.h>
#include    <stdlib.h>
#include    <stdbool.h>
#include    "simstruc.h"
#ifdef      MATLAB_MEX_FILE
#include    "mex.h"
#else
#include    "sg_common.h"
#endif
#include "include/sg_io101_regs.h"
#include "sg_callback_legacy.h"
#include "sg_printf.h"
#define DEVNAME "\x53\x70\x65\x65\x64\x67\x6f\x61\x74\x20\x49\x4f\x31\x30\x31"
#define VENDORID (0x177d+826-0x3e2)
#define DEVICEID 17495
#define zdf24515981          ((0x1b81+1136-0x1fed))
#define z702a26a5e9                ssGetSFcnParam(S,(0xbe0+1081-0x1019))
#define z726c6b0744        ssGetSFcnParam(S,(0x607+8242-0x2638))
#define zf59d07c647        ssGetSFcnParam(S,(0x1850+1926-0x1fd4))
#define ze13f49a01f           ssGetSFcnParam(S,(0x613+5857-0x1cf1))
#define z2e6483d505              ((0x597+869-0x8fc))
#define zc5ce4cb81a              ((0xcc5+4062-0x1ca3))
#define z2b17e2ee3b              ((0xb10+1842-0x1242))
static char_T msg[(0x4fb+7425-0x20fc)];static void mdlInitializeSizes(SimStruct*S){uint32_T i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x219f+889-0x2518));ssSetNumDiscStates(S,(0x3d+1829-0x762));ssSetNumInputPorts(S,(0x41c+8615-0x25c3));ssSetNumOutputPorts(S,(0x8c7+797-0xbe4));ssSetNumSampleTimes(S,(0x1669+3892-0x259c));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0xda2+4222-0x1e20));ssSetNumNonsampledZCs(S,(0x5+761-0x2fe));for(i=(0xafb+5982-0x2259);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x12d2+707-0x1595));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE|SS_OPTION_PLACE_ASAP);}static void mdlInitializeSampleTimes(SimStruct*S){ssSetSampleTime(S,(0x527+1072-0x957),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x1cc4+781-0x1fd1),FIXED_IN_MINOR_STEP_OFFSET);}
#define MDL_START
static void mdlStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
sg_PCIDevice zeccbadd9b3;volatile uint32_T*za42cf7dd4a;uint32_T z9d16154d3f,z88b41962cc;int moduleId=(int)mxGetScalar(ze13f49a01f);if((int_T)mxGetPr(z702a26a5e9)[(0x1f71+1047-0x2388)]<(0x1108+4325-0x21ed)){if(sg_findPciDevice(&zeccbadd9b3,DEVNAME,VENDORID,DEVICEID,SG_NO_SUB,SG_NO_SUB,moduleId,SG_NO_BUS_SLOT,SG_NO_BUS_SLOT)){ssSetErrorStatus(S,pSgErrorStr);return;}}else{int_T bus,slot;if(mxGetN(z702a26a5e9)==(0x3b5+2239-0xc73)){bus=(0x21a+14-0x228);slot=(int_T)mxGetPr(z702a26a5e9)[(0x1482+3572-0x2276)];}else{bus=(int_T)mxGetPr(z702a26a5e9)[(0x6b9+2290-0xfab)];slot=(int_T)mxGetPr(z702a26a5e9)[(0x192d+2941-0x24a9)];}if(sg_findPciDevice(&zeccbadd9b3,DEVNAME,VENDORID,DEVICEID,SG_NO_SUB,SG_NO_SUB,moduleId,bus,slot)){ssSetErrorStatus(S,pSgErrorStr);return;}}za42cf7dd4a=(volatile uint32_T*)sg_mapMemory(&zeccbadd9b3,(0x1416+1915-0x1b91));z9d16154d3f=(uint32_T)mxGetPr(z726c6b0744)[(0x327+10-0x331)]-(0x1062+5665-0x2682);z88b41962cc=(uint32_T)mxGetPr(zf59d07c647)[(0x8e7+5281-0x1d88)]-(0x4c1+7564-0x224c);za42cf7dd4a[ze2be7d0ea8]=z9d16154d3f+(z88b41962cc<<(0xd1+5618-0x16c2));
#endif
}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){}static void mdlTerminate(SimStruct*S){}
#include "sg_sfcn_glue.h"   

