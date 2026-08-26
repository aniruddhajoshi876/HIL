// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL        (0x1c16+2520-0x25ec)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME         sg_IO114B_di_s
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
#define za9d8fb6bcf             ssGetSFcnParam(S, (0xd2f+4230-0x1db5))
#define zabe1e0cd2c          ssGetSFcnParam(S, (0x10a9+259-0x11ab))
#define z702a26a5e9                ssGetSFcnParam(S, (0xdc+4931-0x141d))
#define ze13f49a01f           ssGetSFcnParam(S, (0xb+9552-0x2558))
#define zdf24515981                           ((0x5e4+6720-0x2020))
#define zc5ce4cb81a              ((0xcd6+2171-0x1551))
#define z2e6483d505              ((0x17a4+2676-0x2218))
#define z0194338df7         ((0x50+1864-0x798))
#define z2b17e2ee3b              ((0x149+8505-0x2281))
static char_T msg[(0x30c+8218-0x2226)];
#define VENDORID    (0x1478+4456-0x1196)
#define DEVICEID    25352
#define SUBVENDORID 5194
#define SUBDEVICEID 25512
#define DEVNAME     "\x53\x70\x65\x65\x64\x67\x6f\x61\x74\x20\x49\x4f\x31\x31\x34\x42"
static void mdlInitializeSizes(SimStruct*S){uint16_T i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x11a5+4957-0x2502));ssSetNumDiscStates(S,(0xbba+2328-0x14d2));ssSetNumInputPorts(S,(0xc8f+3198-0x190d));ssSetNumOutputPorts(S,(int_T)mxGetN(za9d8fb6bcf));for(i=(0x1138+4854-0x242e);i<(int)mxGetN(za9d8fb6bcf);i++){ssSetOutputPortWidth(S,i,(0x125b+390-0x13e0));}ssSetNumSampleTimes(S,(0xc27+5873-0x2317));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x223d+193-0x22fe));ssSetNumNonsampledZCs(S,(0x1dea+1085-0x2227));for(i=(0x4b7+478-0x695);i<zdf24515981;i++){ssSetSFcnParamNotTunable(S,i);}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(zabe1e0cd2c)[(0xe56+3125-0x1a8b)]==-1.0){ssSetSampleTime(S,(0xfd0+4497-0x2161),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x1c84+100-0x1ce8),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x1943+2650-0x239d),mxGetPr(zabe1e0cd2c)[(0x834+4933-0x1b79)]);ssSetOffsetTime(S,(0x1a8b+3125-0x26c0),0.0);}}
#define MDL_START
static void mdlStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
sg_PCIDevice zeccbadd9b3;int_T bus,slot;uint32_T za0d38ae598;uintptr_t za42cf7dd4a;if(mxGetN(z702a26a5e9)==(0xcbd+2878-0x17fa)){bus=(0x1ec8+1940-0x265c);slot=(int_T)mxGetPr(z702a26a5e9)[(0xb1c+5307-0x1fd7)];}else{bus=(int_T)mxGetPr(z702a26a5e9)[(0x8bb+3645-0x16f8)];slot=(int_T)mxGetPr(z702a26a5e9)[(0x6e6+5171-0x1b18)];}za0d38ae598=(int_T)mxGetPr(ze13f49a01f)[(0x1cf+1171-0x662)];if(sg_findPciDevice(&zeccbadd9b3,DEVNAME,VENDORID,DEVICEID,SUBVENDORID,SUBDEVICEID,za0d38ae598,bus,slot)!=(0x11a2+4994-0x2524)){ssSetErrorStatus(S,pSgErrorStr);return;}za42cf7dd4a=(uintptr_t)sg_mapIo(&zeccbadd9b3,(0x1301+3476-0x2093));ssSetPWorkValue(S,z0194338df7,(uint32_T*)za42cf7dd4a);
#endif
}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){
#ifndef MATLAB_MEX_FILE
uintptr_t za42cf7dd4a=(uintptr_t)ssGetPWorkValue(S,z0194338df7);uint32_T zf91d71c6d9=(uint32_T)mxGetN(za9d8fb6bcf);uint32_T i;int_T channel;real_T*y;uint16_T zf67144ac88;zf67144ac88=(sg_inpW(za42cf7dd4a+(0x538+3804-0x13d4))>>(0x340+1904-0xaac))&(0x7d9+6675-0x21dd);for(i=(0x1f39+190-0x1ff7);i<zf91d71c6d9;i++){y=ssGetOutputPortSignal(S,i);channel=(int_T)mxGetPr(za9d8fb6bcf)[i]-(0x5af+2424-0xf26);if(zf67144ac88&((0x891+3341-0x159d)<<channel)){y[(0xde5+4081-0x1dd6)]=(0xfd5+1111-0x142b);}else{y[(0xe7f+2464-0x181f)]=(0xc13+118-0xc89);}}
#endif
}static void mdlTerminate(SimStruct*S){}
#include "sg_sfcn_glue.h"   

