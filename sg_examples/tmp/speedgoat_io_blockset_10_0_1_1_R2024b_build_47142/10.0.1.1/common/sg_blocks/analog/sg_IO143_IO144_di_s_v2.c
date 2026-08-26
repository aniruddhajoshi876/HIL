// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL    (0x2d7+4598-0x14cb)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO143_IO144_di_s_v2
#include "sg_IO143_IO144_v2.h"
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
#define z533b11d03f           ssGetSFcnParam(S,  (0x10f1+1513-0x16da)) 
#define za00184cdc1            ssGetSFcnParam(S,  (0x173d+3298-0x241e)) 
#define z702a26a5e9                ssGetSFcnParam(S,  (0x1431+4530-0x25e1)) 
#define zabe1e0cd2c          ssGetSFcnParam(S,  (0x5e0+2987-0x1188)) 
#define z82143b8d5e         ssGetSFcnParam(S,  (0x750+4202-0x17b6)) 
#define zdf24515981                        (    (0x370+7794-0x21dd))
#define z2e6483d505              ((0x249+3627-0x1074))
#define zc5ce4cb81a              ((0x1869+2840-0x2381))
#define z2b17e2ee3b              ((0x15f3+1764-0x1cd7))
static char msg[(0x11e8+3068-0x1ce4)];static int zdc01648b54;static void mdlInitializeSizes(SimStruct*S){uint_T i;zdc01648b54=sprintf(msg,"\x49\x6e\x20\x49\x4f\x25\x64\x2c\x20\x44\x69\x67\x69\x74\x61\x6c\x20\x69\x6e\x70\x75\x74\x20\x62\x6c\x6f\x63\x6b\x2c\x20\x49\x44\x20\x25\x64\x3a\x20",(int)mxGetPr(z533b11d03f)[(0x4cb+4660-0x16ff)],(int)mxGetPr(za00184cdc1)[(0x27f+4459-0x13ea)]);ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf((msg+zdc01648b54),"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n""\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64\x2e" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x8b+7055-0x1c1a));ssSetNumDiscStates(S,(0x1906+3024-0x24d6));if(!ssSetNumInputPorts(S,(0xc19+791-0xf30)))return;if(!ssSetNumOutputPorts(S,(int)mxGetN(z82143b8d5e)))return;for(i=(0x55a+7790-0x23c8);i<(uint_T)mxGetN(z82143b8d5e);i++){ssSetOutputPortWidth(S,i,(0x1623+390-0x17a8));}ssSetNumSampleTimes(S,(0x58b+15-0x599));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x15ff+394-0x1789));ssSetNumNonsampledZCs(S,(0x14f2+688-0x17a2));for(i=(0x14db+3217-0x216c);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,SS_PRM_NOT_TUNABLE);}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(zabe1e0cd2c)[(0xdfa+1458-0x13ac)]==-1.0){ssSetSampleTime(S,(0xa95+5062-0x1e5b),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x6b5+3066-0x12af),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0xca0+5950-0x23de),mxGetPr(zabe1e0cd2c)[(0xe98+2581-0x18ad)]);ssSetOffsetTime(S,(0xf59+4366-0x2067),0.0);}}
#ifndef MATLAB_MEX_FILE
static void sg_ModelLoad(SimStruct*S){}static void sg_ModelStart(SimStruct*S){}static void sg_ModelStep(SimStruct*S){uint32_T z85c496e7c0;real_T*y;uint_T i;int boardType=(int)mxGetPr(z533b11d03f)[(0x3eb+6750-0x1e49)];int za0d38ae598=(int)mxGetPr(za00184cdc1)[(0x671+323-0x7b4)];uint32_T zf91d71c6d9=(uint32_T)mxGetN(z82143b8d5e);zc8ee45929d*zae10e3f17f=(zc8ee45929d*)sg_module_get_custom_data(boardType,za0d38ae598);if(!zae10e3f17f){sprintf(msg,"\x49\x4f\x25\x64\x20\x28\x49\x44\x20\x25\x64\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x69\x6e\x20\x44\x49\x20\x4d\x6f\x64\x65\x6c\x53\x74\x65\x70" "\n",boardType,za0d38ae598);ssSetErrorStatus(S,msg);return;}uint32_T ze1cc2f3e4a=zae10e3f17f->z3fad3d9764->zde659008d9;SG_PRINTF(TRACE,"\x44\x49\x20\x64\x61\x74\x61\x3a\x20\x25\x58" "\n",ze1cc2f3e4a);for(i=(0x103+5541-0x16a8);i<zf91d71c6d9;i++){z85c496e7c0=(uint32_T)mxGetPr(z82143b8d5e)[i]-(0x1c27+2055-0x242d);y=ssGetOutputPortRealSignal(S,i);if(ze1cc2f3e4a&((0x7d4+5293-0x1c80)<<z85c496e7c0)){*y=1.0;}else{*y=0.0;}}}static void sg_ModelStop(SimStruct*S){}
#endif 
#include "sg_sfcn_glue.h"   

