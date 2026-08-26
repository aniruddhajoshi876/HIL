// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL   (0x101d+1889-0x177c)
#undef  S_FUNCTION_NAME
#define S_FUNCTION_NAME    sg_getcputemp_s
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "simstruc.h"
#ifndef MATLAB_MEX_FILE
#include "sg_common.h"
#include "sg_target.h" 
#include "sg_callback_legacy.h"
#else
#include "mex.h"
#endif
#define z39cbd24432         ssGetSFcnParam(S,(0xb38+2443-0x14c3))
#define zdf24515981          ((0x8db+2142-0x1138))
static void mdlInitializeSizes(SimStruct*S){ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){return;}ssSetNumContStates(S,(0x1e4a+2073-0x2663));ssSetNumDiscStates(S,(0x1f3d+290-0x205f));if(!ssSetNumInputPorts(S,(0x14d8+709-0x179d)))return;if(!ssSetNumOutputPorts(S,(0xf26+5121-0x2326)))return;ssSetOutputPortWidth(S,(0x9b+570-0x2d5),(0x1491+2012-0x1c6c));ssSetOutputPortDataType(S,(0xd2f+4987-0x20aa),SS_UINT8);ssSetNumSampleTimes(S,(0x1d6c+1144-0x21e3));ssSetNumModes(S,(0x331+707-0x5f4));ssSetNumNonsampledZCs(S,(0x498+8273-0x24e9));ssSetSFcnParamTunable(S,(0x1de9+2229-0x269e),(0xb61+546-0xd83));ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z39cbd24432)[(0x2286+139-0x2311)]==-1.0){ssSetSampleTime(S,(0x48b+8455-0x2592),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x10e4+3007-0x1ca3),FIXED_IN_MINOR_STEP_OFFSET);ssSetModelReferenceSampleTimeDefaultInheritance(S);}else{ssSetSampleTime(S,(0x80b+5132-0x1c17),mxGetPr(z39cbd24432)[(0xef7+1052-0x1313)]);ssSetOffsetTime(S,(0x32a+3599-0x1139),0.0);}}
#define MDL_START
static void mdlStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
int32_t*zc0efaa16c3=(int32_t*)ssGetOutputPortSignal(S,(0x5cd+8174-0x25bb));*zc0efaa16c3=sg_getCpuTemperature();if(*zc0efaa16c3<(0x4bc+6246-0x1d22)){ssSetErrorStatus(S,pSgErrorStr);return;}
#endif
}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){
#ifndef MATLAB_MEX_FILE
int32_t*zc0efaa16c3=(int32_t*)ssGetOutputPortSignal(S,(0x7f+2788-0xb63));*zc0efaa16c3=sg_getCpuTemperature();
#endif
}static void mdlTerminate(SimStruct*S){}
#ifdef  MATLAB_MEX_FILE    
#include "simulink.c"      
#else
#include "cg_sfun.h"       
#endif

