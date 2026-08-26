// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL   (0x19eb+656-0x1c79)
#undef  S_FUNCTION_NAME
#define S_FUNCTION_NAME    sg_gettargettime_s
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include "simstruc.h"
#ifndef MATLAB_MEX_FILE
#include "sg_common.h" 
#include "sg_time.h" 
#include "sg_callback_legacy.h"
#include "sg_printf.h"  
#else
#include "mex.h"
#endif
#include "sg_mask_init.h"
enum z0171725444{za2c6d5f765,z2041d72f5c};static void mdlInitializeSizes(SimStruct*S){ssSetNumSFcnParams(S,z2041d72f5c);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){return;}if(!ssSetNumInputPorts(S,(0x197b+1597-0x1fb8)))return;if(!ssSetNumOutputPorts(S,(0x173b+3737-0x25d3)))return;ssSetOutputPortWidth(S,(0xf72+4795-0x222d),(0x1734+3433-0x249c));ssSetOutputPortDataType(S,(0xd43+4844-0x202f),SS_DOUBLE);ssSetNumSampleTimes(S,(0x2aa+762-0x5a3));ssSetOptions(S,SS_OPTION_DISALLOW_CONSTANT_SAMPLE_TIME|SS_OPTION_RUNTIME_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){double sampleTime=mxGetScalar(ssGetSFcnParam(S,za2c6d5f765));sgMaskInit_initSampleTimesForRegularBlock(S,sampleTime);}
#define MDL_START
static void mdlStart(SimStruct*S){}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){
#ifndef MATLAB_MEX_FILE
double*z42b1084ab3=(double*)ssGetOutputPortSignal(S,(0x587+3646-0x13c5));*z42b1084ab3=sg_getTargetTimeNum();
#endif
}static void mdlTerminate(SimStruct*S){}
#ifdef  MATLAB_MEX_FILE    
#include "simulink.c"      
#else
#include "cg_sfun.h"       
#endif

