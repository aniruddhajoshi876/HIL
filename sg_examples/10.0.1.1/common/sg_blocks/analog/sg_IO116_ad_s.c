// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL    (0xc57+1795-0x1358)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO116_ad_s
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
#define za9d8fb6bcf             ssGetSFcnParam(S, (0x1d47+2412-0x26b3))
#define z39cbd24432         ssGetSFcnParam(S, (0x1849+1567-0x1e67))
#define z702a26a5e9                ssGetSFcnParam(S, (0x1017+4755-0x22a8))
#define zda964b0978                ssGetSFcnParam(S, (0x6cb+6899-0x21bb))
#define ze342ab7eba         ssGetSFcnParam(S, (0x5c1+3642-0x13f7))
#define ze13f49a01f           ssGetSFcnParam(S, (0x1d6+9234-0x25e3))
#define zdf24515981          ((0x1f2f+1679-0x25b8))
#define z2e6483d505              ((0x5e2+236-0x6ce))
#define zc5ce4cb81a              ((0x58c+6195-0x1dbf))
#define z2b17e2ee3b              ((0x42d+487-0x614))
static char msg[(0x143b+900-0x16bf)];static void mdlInitializeSizes(SimStruct*S){uint32_T i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x14bc+580-0x1700));ssSetNumDiscStates(S,(0x5e9+5514-0x1b73));ssSetNumSampleTimes(S,(0x1df+1755-0x8b9));ssSetNumModes(S,(0xc2a+6565-0x25cf));ssSetNumNonsampledZCs(S,(0xec9+2259-0x179c));for(i=(0x61c+7156-0x2210);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,SS_PRM_NOT_TUNABLE);}if(!ssSetNumOutputPorts(S,(uint16_T)mxGetN(za9d8fb6bcf)))return;for(i=(0x59d+4884-0x18b1);i<(uint16_T)mxGetN(za9d8fb6bcf);i++){ssSetOutputPortWidth(S,i,(0x8b6+6880-0x2395));}ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z39cbd24432)[(0x1ab4+1632-0x2114)]==-1.0){ssSetSampleTime(S,(0x242a+471-0x2601),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x1822+2368-0x2162),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x833+7892-0x2707),mxGetPr(z39cbd24432)[(0x1e7+4825-0x14c0)]);ssSetOffsetTime(S,(0x12ef+3591-0x20f6),0.0);}}
#ifndef MATLAB_MEX_FILE
static void sg_ModelLoad(SimStruct*S){}static void sg_ModelStart(SimStruct*S){}static void sg_ModelStep(SimStruct*S){uint32_T za0d38ae598=((uint32_T)mxGetPr(ze13f49a01f)[(0x2399+177-0x244a)]);uint32_T i=(0x18ba+2927-0x2429);uint32_T z31f3f2b868=(0x3f4+6113-0x1bd5);uint32_T zf91d71c6d9=(uint32_T)mxGetN(za9d8fb6bcf);real_T z64002f2ffb=(0x180a+2012-0x1fe6);real_T z0754dd67cc=(real_T)mxGetPr(zda964b0978)[(0x2c3+8420-0x23a7)];real_T*y;z08779af635*zae10e3f17f=(z08779af635*)sg_module_get_custom_data(z12ba1d7c25,za0d38ae598);if(!zae10e3f17f){sprintf(msg,"\x49\x4f\x25\x64\x20\x28\x49\x44\x20\x25\x64\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x69\x6e\x20\x41\x44\x20\x4d\x6f\x64\x65\x6c\x53\x74\x65\x70" "\n",z12ba1d7c25,za0d38ae598);ssSetErrorStatus(S,msg);return;}zae10e3f17f->z3fad3d9764->z14bc320aa4|=zf95e657598;while(zae10e3f17f->z3fad3d9764->z14bc320aa4&zf95e657598){}for(i=(0x2f3+2936-0xe6b);i<zf91d71c6d9;i++){y=ssGetOutputPortSignal(S,i);z31f3f2b868=zae10e3f17f->z3fad3d9764->z690d720321&65535;if((uint32_T)mxGetPr(ze342ab7eba)[i]==(0x1376+3353-0x208e)){z64002f2ffb=z0754dd67cc;}else{z64002f2ffb=65535/20e-3;}*y=(real_T)z31f3f2b868/z64002f2ffb;}}static void sg_ModelStop(SimStruct*S){}
#endif 
#include "sg_sfcn_glue.h"   

