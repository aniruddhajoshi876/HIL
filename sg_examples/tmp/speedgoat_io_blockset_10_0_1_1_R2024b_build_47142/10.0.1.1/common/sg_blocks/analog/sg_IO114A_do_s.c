// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL        (0x678+460-0x842)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME         sg_IO114A_do_s
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
#define za9d8fb6bcf             ssGetSFcnParam(S, (0x165f+1229-0x1b2c))
#define zabe1e0cd2c          ssGetSFcnParam(S, (0xc0f+2496-0x15ce))
#define z702a26a5e9                ssGetSFcnParam(S, (0x1596+3883-0x24bf))
#define zc8bbaa6115               ssGetSFcnParam(S, (0x113+5382-0x1616))
#define zf80b27df71                ssGetSFcnParam(S, (0x1739+1755-0x1e10))
#define ze13f49a01f           ssGetSFcnParam(S, (0x1fe1+1559-0x25f3))
#define zdf24515981                           ((0x14e2+176-0x158c))
#define zc5ce4cb81a              ((0x135b+2909-0x1eb8))
#define z2e6483d505              ((0x80f+6495-0x216e))
#define z0194338df7         ((0x7b4+3503-0x1563))
#define z2b17e2ee3b              ((0x13bd+541-0x15d9))
static char_T msg[(0x249+7829-0x1fde)];
#define VENDORID    (0x1d68+3167-0x157d)
#define DEVICEID    25096
#define SUBVENDORID 5194
#define SUBDEVICEID 25096
#define DEVNAME     "\x53\x70\x65\x65\x64\x67\x6f\x61\x74\x20\x49\x4f\x31\x31\x34\x41"  
static void mdlInitializeSizes(SimStruct*S){uint16_T i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x1898+2601-0x22c1));ssSetNumDiscStates(S,(0x12c3+5051-0x267e));ssSetNumInputPorts(S,(int_T)mxGetN(za9d8fb6bcf));for(i=(0x133+4768-0x13d3);i<mxGetN(za9d8fb6bcf);i++){ssSetInputPortWidth(S,i,(0x1e55+1580-0x2480));ssSetInputPortDirectFeedThrough(S,i,(0x6d4+440-0x88b));}ssSetNumOutputPorts(S,(0x1838+2422-0x21ae));ssSetNumSampleTimes(S,(0x9fb+911-0xd89));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x92f+978-0xd01));ssSetNumNonsampledZCs(S,(0xf15+3281-0x1be6));for(i=(0x140+1494-0x716);i<zdf24515981;i++){ssSetSFcnParamNotTunable(S,i);}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(zabe1e0cd2c)[(0x3db+5474-0x193d)]==-1.0){ssSetSampleTime(S,(0x15f1+3583-0x23f0),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0xbff+3306-0x18e9),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x245+8423-0x232c),mxGetPr(zabe1e0cd2c)[(0x19a+7967-0x20b9)]);ssSetOffsetTime(S,(0x1e21+958-0x21df),0.0);}}
#define MDL_START
static void mdlStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
sg_PCIDevice zeccbadd9b3;int_T bus,slot;uint32_T za0d38ae598;uintptr_t za42cf7dd4a;if(mxGetN(z702a26a5e9)==(0x1a93+2106-0x22cc)){bus=(0x89b+7228-0x24d7);slot=(int_T)mxGetPr(z702a26a5e9)[(0x742+7331-0x23e5)];}else{bus=(int_T)mxGetPr(z702a26a5e9)[(0x11b2+1182-0x1650)];slot=(int_T)mxGetPr(z702a26a5e9)[(0x8d4+4777-0x1b7c)];}za0d38ae598=(int_T)mxGetPr(ze13f49a01f)[(0x4a3+793-0x7bc)];if(sg_findPciDevice(&zeccbadd9b3,DEVNAME,VENDORID,DEVICEID,SUBVENDORID,SUBDEVICEID,za0d38ae598,bus,slot)!=(0x656+7571-0x23e9)){ssSetErrorStatus(S,pSgErrorStr);return;}za42cf7dd4a=(uintptr_t)sg_mapIo(&zeccbadd9b3,(0x15ba+4138-0x25e2));ssSetPWorkValue(S,z0194338df7,(uint32_T*)za42cf7dd4a);
#endif
}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){
#ifndef MATLAB_MEX_FILE
uintptr_t za42cf7dd4a=(uintptr_t)ssGetPWorkValue(S,z0194338df7);uint32_T zf91d71c6d9=(uint32_T)mxGetN(za9d8fb6bcf);uint32_T i;real_T output;int_T channel;InputRealPtrsType z142f9c10a3;uint16_T zcb341ffb0e=(0x10a+492-0x2f6);for(i=(0x533+5379-0x1a36);i<zf91d71c6d9;i++){channel=(int_T)mxGetPr(za9d8fb6bcf)[i]-(0x6e4+7092-0x2297);z142f9c10a3=ssGetInputPortRealSignalPtrs(S,i);output=*z142f9c10a3[(0x4b8+313-0x5f1)];if(output>0.5){zcb341ffb0e|=((0x1e8+2246-0xaad)<<channel);}}sg_outpW(za42cf7dd4a+(0x1663+2484-0x1fd7),zcb341ffb0e);
#endif
}static void mdlTerminate(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uintptr_t za42cf7dd4a=(uintptr_t)ssGetPWorkValue(S,z0194338df7);uint32_T zf91d71c6d9=(uint32_T)mxGetN(za9d8fb6bcf);uint32_T i;real_T output;int_T channel;uint16_T zcb341ffb0e;zcb341ffb0e=sg_inpW(za42cf7dd4a+(0x6fd+2558-0x10bb));for(i=(0x620+3718-0x14a6);i<zf91d71c6d9;i++){channel=(uint32_T)mxGetPr(za9d8fb6bcf)[i]-(0xb6c+1530-0x1165);if(sg_isModelInit()||(mxGetPr(zc8bbaa6115)[i]==(0x77d+5338-0x1c56))){output=mxGetPr(zf80b27df71)[i];if(output>0.5){zcb341ffb0e|=((0x751+2222-0xffe)<<channel);}else{zcb341ffb0e&=~((0x4b6+5897-0x1bbe)<<channel);}}}sg_outpW(za42cf7dd4a+(0x38f+8904-0x2617),zcb341ffb0e);
#endif
}
#include "sg_sfcn_glue.h"   

