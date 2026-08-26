// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL    (0x228d+625-0x24fc)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO102_do_s_v2
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sg_io102.h"
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
#define zdf24515981          ((0x625+6256-0x1e91))
#define ze13f49a01f           ssGetSFcnParam(S,(0xf72+3216-0x1c02))
#define za9d8fb6bcf             ssGetSFcnParam(S,(0x940+6433-0x2260))
#define z3832b85a32           ssGetSFcnParam(S,(0x140b+4032-0x23c9))
#define z702a26a5e9                ssGetSFcnParam(S,(0x2e1+6783-0x1d5d))
#define z2e6483d505              ((0xf36+4883-0x2248))
#define z7e2eeaa57c          ((0x284+1978-0xa3e))
#define zc5ce4cb81a              ((0x112f+4828-0x240b))
#define z2b17e2ee3b              ((0x428+2590-0xe45))
#define z0194338df7         ((0x19c7+2290-0x22b9))
#define THRESHOLD               0.5
static char_T msg[(0x37c+2195-0xb0f)];static void mdlInitializeSizes(SimStruct*S){uint32_T i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0xa8+8326-0x212e));ssSetNumDiscStates(S,(0x18ac+3155-0x24ff));if(!ssSetNumOutputPorts(S,(0x1df5+1440-0x2395)))return;if(!ssSetNumInputPorts(S,(int)mxGetN(za9d8fb6bcf)))return;for(i=(0x1041+3377-0x1d72);i<(int)mxGetN(za9d8fb6bcf);i++){ssSetInputPortWidth(S,i,(0x1bbc+396-0x1d47));ssSetInputPortDirectFeedThrough(S,i,(0x194c+2341-0x2270));ssSetInputPortRequiredContiguous(S,i,(0x19c4+1603-0x2006));}ssSetNumSampleTimes(S,(0x15a3+2060-0x1dae));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0xa34+4107-0x1a3f));ssSetNumNonsampledZCs(S,(0xed6+3608-0x1cee));for(i=(0xa02+5305-0x1ebb);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x6+5942-0x173c));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x4b3+8013-0x2400)]==-1.0){ssSetSampleTime(S,(0x613+3646-0x1451),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x1950+334-0x1a9e),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0xcb6+6036-0x244a),mxGetPr(z3832b85a32)[(0x1777+527-0x1986)]);ssSetOffsetTime(S,(0x270+731-0x54b),0.0);}}
#ifndef MATLAB_MEX_FILE
static void sg_ModelLoad(SimStruct*S){}static void sg_ModelStart(SimStruct*S){}static void sg_ModelStep(SimStruct*S){uint16_T z0c3eef007f=(uint16_T)mxGetN(za9d8fb6bcf);uint16_T i;uint32_T z718c4c15f4,channel;real_T*zc7fdaf6331;uint32_T za0d38ae598=((int_T)mxGetPr(ze13f49a01f)[(0x11b+8723-0x232e)]);zcdb36f3262*zae10e3f17f=(zcdb36f3262*)sg_module_get_custom_data(z12ba1d7c25,za0d38ae598);if(!zae10e3f17f){sprintf(msg,"\x49\x4f\x25\x64\x20\x28\x49\x44\x20\x25\x64\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x69\x6e\x20\x44\x4f\x20\x4d\x6f\x64\x65\x6c\x53\x74\x65\x70" "\n",z12ba1d7c25,za0d38ae598);ssSetErrorStatus(S,msg);return;}z718c4c15f4=zae10e3f17f->z3fad3d9764[(0xddc+6059-0x257e)];for(i=(0xc49+4242-0x1cdb);i<z0c3eef007f;i++){channel=(uint32_T)mxGetPr(za9d8fb6bcf)[i]-(0x717+8056-0x268e);zc7fdaf6331=(real_T*)ssGetInputPortRealSignal(S,i);if(*zc7fdaf6331>=THRESHOLD){z718c4c15f4|=((0x72d+3345-0x143d)<<channel);}else{z718c4c15f4&=~((0x533+7453-0x224f)<<channel);}}zae10e3f17f->z3fad3d9764[(0x3b7+4532-0x1562)]=z718c4c15f4;}static void sg_ModelStop(SimStruct*S){}
#endif 
#include "sg_sfcn_glue.h" 

