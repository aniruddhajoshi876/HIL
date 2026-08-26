// Copyright 2006-2026 Speedgoat GmbH

#include "simstruc.h"
#ifndef MATLAB_MEX_FILE
#include "StartCallbackAPI.h"
#include "sg_common.h"
#include "sg_early_init.h"
#endif
static void sg_ModelLoad(SimStruct*S);static void sg_ModelStart(SimStruct*S);static void sg_ModelStep(SimStruct*S);static void sg_ModelStop(SimStruct*S);
#ifdef SG_HAS_MDL_EXIT
static void sg_ModelExit(SimStruct*S);
#endif 
#define MDL_START
static void mdlStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
#ifdef SG_EARLY_INIT
if(!sg_is_early_init())return;
#endif 
sg_checkModelInit();sg_ModelLoad(S);
#ifdef SG_HAS_MDL_EXIT
if(!ssGetErrorStatus(S))sg_add_exit_handler((void(*)(void*))sg_ModelExit,(void*)S);
#endif 
registerCB_C((void(*)(void*))sg_ModelStart,(void*)S,(0x1e2+7634-0x1fb3));
#endif 
}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){
#ifndef MATLAB_MEX_FILE
sg_ModelStep(S);
#endif
}static void mdlTerminate(SimStruct*S){
#ifndef MATLAB_MEX_FILE
sg_ModelStop(S);
#endif
}
