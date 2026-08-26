// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL        (0x10e9+4036-0x20ab)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME         sg_IO114A_di_s
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include "simstruc.h"
#include "sg_callback_legacy.h"
#include "sg_printf.h"
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#else
#include "sg_common.h"
#endif
#define za9d8fb6bcf             ssGetSFcnParam(S, (0x210c+496-0x22fc))
#define zabe1e0cd2c          ssGetSFcnParam(S, (0x866+6585-0x221e))
#define z702a26a5e9                ssGetSFcnParam(S, (0x2d1+8332-0x235b))
#define ze13f49a01f           ssGetSFcnParam(S, (0xd36+1347-0x1276))
#define zdf24515981                           ((0x66+1796-0x766))
#define zc5ce4cb81a              ((0x1874+2032-0x2064))
#define z2e6483d505              ((0x1ddc+575-0x201b))
#define z0194338df7         ((0x9f0+3157-0x1645))
#define z2b17e2ee3b              ((0xb5+947-0x467))
static char_T msg[(0x682+5956-0x1cc6)];
#define VENDORID    (0x15f9+5884-0x18ab)
#define DEVICEID    25096
#define SUBVENDORID 5194
#define SUBDEVICEID 25096
#define DEVNAME     "\x53\x70\x65\x65\x64\x67\x6f\x61\x74\x20\x49\x4f\x31\x31\x34\x41"  
static void mdlInitializeSizes(SimStruct*S){uint16_T i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x78+3340-0xd84));ssSetNumDiscStates(S,(0xafd+500-0xcf1));ssSetNumInputPorts(S,(0xdd+6677-0x1af2));ssSetNumOutputPorts(S,(int_T)mxGetN(za9d8fb6bcf));for(i=(0x1e30+1491-0x2403);i<(int)mxGetN(za9d8fb6bcf);i++){ssSetOutputPortWidth(S,i,(0x15f+863-0x4bd));}ssSetNumSampleTimes(S,(0xb5d+2974-0x16fa));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0xd91+4334-0x1e7f));ssSetNumNonsampledZCs(S,(0x7ad+5447-0x1cf4));for(i=(0xeb7+3135-0x1af6);i<zdf24515981;i++){ssSetSFcnParamNotTunable(S,i);}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(zabe1e0cd2c)[(0x1d41+2349-0x266e)]==-1.0){ssSetSampleTime(S,(0x135b+4837-0x2640),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0xe48+3370-0x1b72),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x2445+593-0x2696),mxGetPr(zabe1e0cd2c)[(0x1bc9+2813-0x26c6)]);ssSetOffsetTime(S,(0x1a1+7118-0x1d6f),0.0);}}
#define MDL_START
static void mdlStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
sg_PCIDevice zeccbadd9b3;int_T bus,slot;uint32_T za0d38ae598;uintptr_t za42cf7dd4a;if(mxGetN(z702a26a5e9)==(0xe0+6464-0x1a1f)){bus=(0x88c+14-0x89a);slot=(int_T)mxGetPr(z702a26a5e9)[(0x1941+305-0x1a72)];}else{bus=(int_T)mxGetPr(z702a26a5e9)[(0x1050+2490-0x1a0a)];slot=(int_T)mxGetPr(z702a26a5e9)[(0x325+7510-0x207a)];}za0d38ae598=(int_T)mxGetPr(ze13f49a01f)[(0x18d9+2082-0x20fb)];if(sg_findPciDevice(&zeccbadd9b3,DEVNAME,VENDORID,DEVICEID,SUBVENDORID,SUBDEVICEID,za0d38ae598,bus,slot)!=(0x1ed1+552-0x20f9)){ssSetErrorStatus(S,pSgErrorStr);return;}za42cf7dd4a=(uintptr_t)sg_mapIo(&zeccbadd9b3,(0x14af+681-0x1756));ssSetPWorkValue(S,z0194338df7,(uint32_T*)za42cf7dd4a);
#endif
}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){
#ifndef MATLAB_MEX_FILE
uintptr_t za42cf7dd4a=(uintptr_t)ssGetPWorkValue(S,z0194338df7);uint32_T zf91d71c6d9=(uint32_T)mxGetN(za9d8fb6bcf);uint32_T i;int_T channel;real_T*y;uint16_T zf67144ac88;zf67144ac88=sg_inpW(za42cf7dd4a+(0xb49+1855-0x1248))>>(0x338+5986-0x1a96);for(i=(0xb9a+4980-0x1f0e);i<zf91d71c6d9;i++){y=ssGetOutputPortSignal(S,i);channel=(int_T)mxGetPr(za9d8fb6bcf)[i]-(0xea0+240-0xf8f);if(zf67144ac88&((0x6a3+1942-0xe38)<<channel)){y[(0x18fb+1483-0x1ec6)]=(0x739+2993-0x12e9);}else{y[(0x137f+2036-0x1b73)]=(0x1fb8+522-0x21c2);}}
#endif
}static void mdlTerminate(SimStruct*S){}
#include "sg_sfcn_glue.h"   

