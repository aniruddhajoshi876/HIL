// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL    (0x847+1492-0xe19)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO116_do_s
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sg_io116.h"
#include "simstruc.h" 
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#else
#include "sg_common.h"
#include "sg_printf.h"
#include "sg_module_registry.h"
#include "sg_module_types.h"
#endif
#define SG_EARLY_INIT
#include "sg_callback.h"
#define za9d8fb6bcf             ssGetSFcnParam(S, (0x10d0+1179-0x156b))
#define z39cbd24432         ssGetSFcnParam(S, (0x1985+340-0x1ad8))
#define z702a26a5e9                ssGetSFcnParam(S, (0x12c2+2314-0x1bca))
#define ze13f49a01f           ssGetSFcnParam(S, (0xe60+554-0x1087))
#define zdf24515981          ((0x789+82-0x7d7))
#define z2e6483d505              ((0xd4+7901-0x1fb1))
#define zc5ce4cb81a              ((0x214f+297-0x2278))
#define z2b17e2ee3b              ((0x762+1662-0xde0))
static char msg[(0x18cd+243-0x18c0)];static void mdlInitializeSizes(SimStruct*S){uint32_T i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0xee1+5383-0x23e8));ssSetNumDiscStates(S,(0x101d+3424-0x1d7d));ssSetNumSampleTimes(S,(0x16cf+4067-0x26b1));ssSetNumModes(S,(0x67+5539-0x160a));ssSetNumNonsampledZCs(S,(0xae3+3387-0x181e));for(i=(0x11a2+1068-0x15ce);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,SS_PRM_NOT_TUNABLE);}if(!ssSetNumInputPorts(S,(int)mxGetN(za9d8fb6bcf)))return;for(i=(0x1f22+1614-0x2570);i<(int)mxGetN(za9d8fb6bcf);i++){ssSetInputPortWidth(S,i,(0xfd1+2434-0x1952));ssSetInputPortDirectFeedThrough(S,i,(0xf16+5490-0x2487));ssSetInputPortRequiredContiguous(S,i,(0x5c0+354-0x721));}ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z39cbd24432)[(0x1274+612-0x14d8)]==-1.0){ssSetSampleTime(S,(0xc2+4441-0x121b),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x804+412-0x9a0),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x10cd+1744-0x179d),mxGetPr(z39cbd24432)[(0x1c24+2043-0x241f)]);ssSetOffsetTime(S,(0x1266+4730-0x24e0),0.0);}}
#ifndef MATLAB_MEX_FILE
static void sg_ModelLoad(SimStruct*S){}static void sg_ModelStart(SimStruct*S){}static void sg_ModelStep(SimStruct*S){uint32_T i;uint32_T z6ebde3830d=(0x1462+4164-0x24a6);uint32_T channel;real_T*z8b5ae3b99c;uint32_T za0d38ae598=((uint32_T)mxGetPr(ze13f49a01f)[(0x1571+2301-0x1e6e)]);z08779af635*zae10e3f17f=(z08779af635*)sg_module_get_custom_data(z12ba1d7c25,za0d38ae598);if(!zae10e3f17f){sprintf(msg,"\x49\x4f\x25\x64\x20\x28\x49\x44\x20\x25\x64\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x69\x6e\x20\x44\x4f\x20\x4d\x6f\x64\x65\x6c\x53\x74\x65\x70" "\n",z12ba1d7c25,za0d38ae598);ssSetErrorStatus(S,msg);return;}z6ebde3830d=(0x1f3c+41-0x1f65);for(i=(0x2e5+248-0x3dd);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_T)mxGetPr(za9d8fb6bcf)[i]-(0x3c7+6003-0x1b39);z8b5ae3b99c=(real_T*)ssGetInputPortRealSignal(S,i);if(*z8b5ae3b99c==(0x1fa4+1132-0x240f)){z6ebde3830d=z6ebde3830d|((0xf68+355-0x10ca)<<channel);}}zae10e3f17f->z3fad3d9764->zfb3b6a8e3f=z9ffbe855ce|(z6ebde3830d<<(0x3b8+4282-0x146a));}static void sg_ModelStop(SimStruct*S){}
#endif 
#include "sg_sfcn_glue.h"   

