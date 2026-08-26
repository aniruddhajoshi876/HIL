// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL   (0xbf2+840-0xf38)
#undef  S_FUNCTION_NAME
#define S_FUNCTION_NAME    sg_getserialnumber_s
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include "simstruc.h"
#ifndef MATLAB_MEX_FILE
#include "sg_common.h" 
#include "sg_target.h" 
#include "sg_callback_legacy.h"
#else
#include "mex.h"
#endif
static void mdlInitializeSizes(SimStruct*S){ssSetNumSFcnParams(S,(0xa7d+4740-0x1d01));if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){return;}if(!ssSetNumInputPorts(S,(0x7c4+4510-0x1962)))return;if(!ssSetNumOutputPorts(S,(0x397+7942-0x229c)))return;ssSetOutputPortWidth(S,(0x72d+7958-0x2643),(0xcb3+2082-0x14d4));ssSetOutputPortDataType(S,(0x105f+3512-0x1e17),SS_INT32);ssSetNumSampleTimes(S,(0xcdc+6360-0x25b3));ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){ssSetSampleTime(S,(0x85b+4181-0x18b0),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x655+2162-0xec7),0.0);ssSetModelReferenceSampleTimeDefaultInheritance(S);}
#define MDL_START
static void mdlStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
int32_t*z5bbfe3b470=(int32_t*)ssGetOutputPortSignal(S,(0xc7c+5092-0x2060));*z5bbfe3b470=sg_getSerialNumber();if(*z5bbfe3b470<(0x3df+6988-0x1f2b)){*z5bbfe3b470=sg_getSerialNumberSupplier();if(*z5bbfe3b470<(0x27b+5557-0x1830)){*z5bbfe3b470=sg_getSerialNumberInternal();}}
#endif
}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){}static void mdlTerminate(SimStruct*S){}
#ifdef  MATLAB_MEX_FILE    
#include "simulink.c"      
#else
#include "cg_sfun.h"       
#endif

