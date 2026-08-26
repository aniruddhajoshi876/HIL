// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL    (0xc8a+2375-0x15cf)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO102_di_s_v2
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
#define zdf24515981          ((0x8c0+2965-0x1451))
#define ze13f49a01f           ssGetSFcnParam(S,(0x1178+5127-0x257f))
#define za9d8fb6bcf             ssGetSFcnParam(S,(0x1388+691-0x163a))
#define z3832b85a32           ssGetSFcnParam(S,(0xcc0+3927-0x1c15))
#define z702a26a5e9                ssGetSFcnParam(S,(0x215+7075-0x1db5))
#define z2e6483d505              ((0xcf8+4263-0x1d9f))
#define zc5ce4cb81a              ((0xab0+991-0xe8f))
#define z2b17e2ee3b              ((0x2113+665-0x23ac))
static char_T msg[(0x726+3961-0x159f)];static void mdlInitializeSizes(SimStruct*S){uint16_T i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0xd7+9347-0x255a));ssSetNumDiscStates(S,(0x7ba+7767-0x2611));if(!ssSetNumInputPorts(S,(0x1ff+5955-0x1942)))return;if(!ssSetNumOutputPorts(S,(uint16_T)mxGetN(za9d8fb6bcf)))return;for(i=(0x23f6+674-0x2698);i<(uint16_T)mxGetN(za9d8fb6bcf);i++){ssSetOutputPortWidth(S,i,(0x1a23+1004-0x1e0e));}ssSetNumSampleTimes(S,(0xbdf+4430-0x1d2c));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0xd11+3466-0x1a9b));ssSetNumNonsampledZCs(S,(0x716+2390-0x106c));for(i=(0x16f6+834-0x1a38);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x6e8+5025-0x1a89));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x10cf+2286-0x19bd)]==-1.0){ssSetSampleTime(S,(0x9c3+3870-0x18e1),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x39b+2934-0xf11),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x7e4+3707-0x165f),mxGetPr(z3832b85a32)[(0x1320+1895-0x1a87)]);ssSetOffsetTime(S,(0x1444+345-0x159d),0.0);}}
#ifndef MATLAB_MEX_FILE
static void sg_ModelLoad(SimStruct*S){}static void sg_ModelStart(SimStruct*S){}static void sg_ModelStep(SimStruct*S){uint32_T i,channel,z0c3eef007f;real_T*y;uint32_T za0d38ae598=((int_T)mxGetPr(ze13f49a01f)[(0x4a0+126-0x51e)]);zcdb36f3262*zae10e3f17f=(zcdb36f3262*)sg_module_get_custom_data(z12ba1d7c25,za0d38ae598);if(!zae10e3f17f){sprintf(msg,"\x49\x4f\x25\x64\x20\x28\x49\x44\x20\x25\x64\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x69\x6e\x20\x44\x49\x20\x4d\x6f\x64\x65\x6c\x53\x74\x65\x70" "\n",z12ba1d7c25,za0d38ae598);ssSetErrorStatus(S,msg);return;}z0c3eef007f=mxGetN(za9d8fb6bcf);for(i=(0x2194+67-0x21d7);i<z0c3eef007f;i++){channel=(int_T)mxGetPr(za9d8fb6bcf)[i]-(0x1849+3039-0x2427);y=ssGetOutputPortSignal(S,i);*y=((zae10e3f17f->z3fad3d9764[(0xeb+7038-0x1c60)]&65535)>>channel)&(0xf0d+92-0xf68);}}static void sg_ModelStop(SimStruct*S){}
#endif 
#include "sg_sfcn_glue.h" 

