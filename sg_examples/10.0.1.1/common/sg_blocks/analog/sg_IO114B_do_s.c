// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL        (0x70a+753-0x9f9)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME         sg_IO114B_do_s
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
#define za9d8fb6bcf             ssGetSFcnParam(S, (0x20bc+5-0x20c1))
#define zabe1e0cd2c          ssGetSFcnParam(S, (0x4a+2150-0x8af))
#define z702a26a5e9                ssGetSFcnParam(S, (0xe1f+2716-0x18b9))
#define zc8bbaa6115               ssGetSFcnParam(S, (0x153d+1116-0x1996))
#define zf80b27df71                ssGetSFcnParam(S, (0x15e8+1202-0x1a96))
#define ze13f49a01f           ssGetSFcnParam(S, (0xe00+2317-0x1708))
#define zdf24515981                           ((0x1012+852-0x1360))
#define zc5ce4cb81a              ((0x1509+3513-0x22c2))
#define z2e6483d505              ((0xa0c+4655-0x1c3b))
#define z0194338df7         ((0x4e0+1685-0xb75))
#define z2b17e2ee3b              ((0x167+5717-0x17bb))
static char_T msg[(0x13a3+2002-0x1a75)];
#define VENDORID    5194
#define DEVICEID    25352
#define SUBVENDORID (0x1bcc+5605-0x1d67)
#define SUBDEVICEID 25512
#define DEVNAME     "\x53\x70\x65\x65\x64\x67\x6f\x61\x74\x20\x49\x4f\x31\x31\x34\x42"
static void mdlInitializeSizes(SimStruct*S){uint16_T i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x1d8+316-0x314));ssSetNumDiscStates(S,(0x59+4301-0x1126));ssSetNumInputPorts(S,(int_T)mxGetN(za9d8fb6bcf));for(i=(0x6d2+4626-0x18e4);i<mxGetN(za9d8fb6bcf);i++){ssSetInputPortWidth(S,i,(0xb55+4787-0x1e07));ssSetInputPortDirectFeedThrough(S,i,(0xbdf+3923-0x1b31));}ssSetNumOutputPorts(S,(0xbb0+3316-0x18a4));ssSetNumSampleTimes(S,(0x1c19+1226-0x20e2));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x1677+2507-0x2042));ssSetNumNonsampledZCs(S,(0xbd8+2323-0x14eb));for(i=(0xe0a+5113-0x2203);i<zdf24515981;i++){ssSetSFcnParamNotTunable(S,i);}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(zabe1e0cd2c)[(0x848+3550-0x1626)]==-1.0){ssSetSampleTime(S,(0x12f+4016-0x10df),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x1549+1718-0x1bff),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x702+4750-0x1990),mxGetPr(zabe1e0cd2c)[(0xbc2+2230-0x1478)]);ssSetOffsetTime(S,(0x10bd+2741-0x1b72),0.0);}}
#define MDL_START
static void mdlStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
sg_PCIDevice zeccbadd9b3;int_T bus,slot;uint32_T za0d38ae598;uintptr_t za42cf7dd4a;if(mxGetN(z702a26a5e9)==(0x22f8+1041-0x2708)){bus=(0x1e11+1524-0x2405);slot=(int_T)mxGetPr(z702a26a5e9)[(0x511+408-0x6a9)];}else{bus=(int_T)mxGetPr(z702a26a5e9)[(0x1090+1999-0x185f)];slot=(int_T)mxGetPr(z702a26a5e9)[(0x25b2+0-0x25b1)];}za0d38ae598=(int_T)mxGetPr(ze13f49a01f)[(0x1ee6+943-0x2295)];if(sg_findPciDevice(&zeccbadd9b3,DEVNAME,VENDORID,DEVICEID,SUBVENDORID,SUBDEVICEID,za0d38ae598,bus,slot)!=(0x774+4603-0x196f)){ssSetErrorStatus(S,pSgErrorStr);return;}za42cf7dd4a=(uintptr_t)sg_mapIo(&zeccbadd9b3,(0x1175+2283-0x1a5e));ssSetPWorkValue(S,z0194338df7,(uint32_T*)za42cf7dd4a);
#endif
}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){
#ifndef MATLAB_MEX_FILE
uintptr_t za42cf7dd4a=(uintptr_t)ssGetPWorkValue(S,z0194338df7);uint32_T zf91d71c6d9=(uint32_T)mxGetN(za9d8fb6bcf);uint32_T i;real_T output;int_T channel;InputRealPtrsType z142f9c10a3;uint16_T zcb341ffb0e=(0x529+1705-0xbd2);for(i=(0x12bb+1633-0x191c);i<zf91d71c6d9;i++){channel=(int_T)mxGetPr(za9d8fb6bcf)[i]-(0x24b+7533-0x1fb7);z142f9c10a3=ssGetInputPortRealSignalPtrs(S,i);output=*z142f9c10a3[(0x1501+4397-0x262e)];if(output>0.5){zcb341ffb0e|=((0x4da+2273-0xdba)<<channel);}}sg_outpW(za42cf7dd4a+(0x1871+3636-0x2665),(zcb341ffb0e<<(0x546+6505-0x1eab)));
#endif
}static void mdlTerminate(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uintptr_t za42cf7dd4a=(uintptr_t)ssGetPWorkValue(S,z0194338df7);uint32_T zf91d71c6d9=(uint32_T)mxGetN(za9d8fb6bcf);uint32_T i;real_T output;int_T channel;uint16_T zcb341ffb0e;zcb341ffb0e=sg_inpW(za42cf7dd4a+(0x19b0+1364-0x1ec4));for(i=(0x426+1389-0x993);i<zf91d71c6d9;i++){channel=(uint32_T)mxGetPr(za9d8fb6bcf)[i]-(0x1264+427-0x140e);if(sg_isModelInit()||(mxGetPr(zc8bbaa6115)[i]==(0x132+5205-0x1586))){output=mxGetPr(zf80b27df71)[i];if(output>0.5){zcb341ffb0e|=((0xc8d+4924-0x1fc8)<<channel);}else{zcb341ffb0e&=~((0xa01+6933-0x2515)<<channel);}}}sg_outpW(za42cf7dd4a+(0x78b+5684-0x1d7f),(zcb341ffb0e<<(0x1b4a+1293-0x2053)));
#endif
}
#include "sg_sfcn_glue.h"   

