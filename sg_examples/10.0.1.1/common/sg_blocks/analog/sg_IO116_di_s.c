// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL    (0xcac+3696-0x1b1a)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO116_di_s
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
#define za9d8fb6bcf             ssGetSFcnParam(S, (0x10c4+2035-0x18b7))
#define z39cbd24432         ssGetSFcnParam(S, (0x1511+89-0x1569))
#define z702a26a5e9                ssGetSFcnParam(S, (0x292+6023-0x1a17))
#define ze13f49a01f           ssGetSFcnParam(S, (0xff0+5055-0x23ac))
#define zdf24515981          ((0x788+6603-0x214f))
#define z2e6483d505              ((0xcb4+2254-0x1582))
#define zc5ce4cb81a              ((0x138+8165-0x211d))
#define z2b17e2ee3b              ((0x38c+6358-0x1c62))
static char msg[(0x860+5449-0x1ca9)];static void mdlInitializeSizes(SimStruct*S){uint32_T i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x1544+2514-0x1f16));ssSetNumDiscStates(S,(0x1e17+881-0x2188));ssSetNumSampleTimes(S,(0x1caa+68-0x1ced));ssSetNumModes(S,(0xa31+5806-0x20df));ssSetNumNonsampledZCs(S,(0x423+1769-0xb0c));for(i=(0x773+1541-0xd78);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,SS_PRM_NOT_TUNABLE);}if(!ssSetNumOutputPorts(S,(uint16_T)mxGetN(za9d8fb6bcf)))return;for(i=(0xeca+3254-0x1b80);i<(uint16_T)mxGetN(za9d8fb6bcf);i++){ssSetOutputPortWidth(S,i,(0x576+8405-0x264a));}ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z39cbd24432)[(0x1165+3876-0x2089)]==-1.0){ssSetSampleTime(S,(0x4f5+7735-0x232c),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x1537+671-0x17d6),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x366+4655-0x1595),mxGetPr(z39cbd24432)[(0xc1b+433-0xdcc)]);ssSetOffsetTime(S,(0x415+1157-0x89a),0.0);}}
#ifndef MATLAB_MEX_FILE
static void sg_ModelLoad(SimStruct*S){}static void sg_ModelStart(SimStruct*S){}static void sg_ModelStep(SimStruct*S){uint32_T i;uint32_T z979d8f17a3=(0xf03+4895-0x2222);uint32_T z577e20787b=(0xb6c+1823-0x128b);uint32_T zb0004dfabf;real_T*y;uint32_T za0d38ae598=((uint32_T)mxGetPr(ze13f49a01f)[(0xa90+6966-0x25c6)]);z08779af635*zae10e3f17f=(z08779af635*)sg_module_get_custom_data(z12ba1d7c25,za0d38ae598);if(!zae10e3f17f){sprintf(msg,"\x49\x4f\x25\x64\x20\x28\x49\x44\x20\x25\x64\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x69\x6e\x20\x44\x49\x20\x4d\x6f\x64\x65\x6c\x53\x74\x65\x70" "\n",z12ba1d7c25,za0d38ae598);ssSetErrorStatus(S,msg);return;}z979d8f17a3=mxGetN(za9d8fb6bcf);zb0004dfabf=zae10e3f17f->z3fad3d9764->zfb3b6a8e3f&(0x18a+1122-0x4ed);for(i=(0xbf8+5699-0x223b);i<z979d8f17a3;i++){z577e20787b=(int_T)mxGetPr(za9d8fb6bcf)[i]-(0x2f8+8095-0x2296);y=ssGetOutputPortSignal(S,i);*y=(zb0004dfabf>>z577e20787b)&(0x9f9+2435-0x137b);}}static void sg_ModelStop(SimStruct*S){}
#endif 
#include "sg_sfcn_glue.h"   

