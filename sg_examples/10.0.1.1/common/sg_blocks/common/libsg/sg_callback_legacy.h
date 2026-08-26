// Copyright 2006-2026 Speedgoat GmbH

#ifndef MATLAB_MEX_FILE
#include "sg_common.h"
#include "simstruc.h"
#include "StartCallbackAPI.h"
static void z4a6b23443e(SimStruct*S);static void z6d09d60ddb(SimStruct*S);static void z4e25f06c79(void*in);static void z4e25f06c79(void*in){sg_clearModelInit();z4a6b23443e((SimStruct*)in);}
#define MDL_START
static void mdlStart(SimStruct*S){sg_checkModelInit();if(sg_isModelInit()){z4a6b23443e(S);registerCB_C(&z4e25f06c79,(void*)S,(0x150d+3793-0x23dd));if(ssGetErrorStatus(S)){return;}z6d09d60ddb(S);}else{registerCB_C(&z4e25f06c79,(void*)S,(0x416+1203-0x8c8));}}static void mdlTerminate(SimStruct*S){z6d09d60ddb(S);if(!sg_isModelInit())sg_tagModelRun();}
#define mdlStart(...)		z4a6b23443e(SimStruct *S)		
#define mdlTerminate(...)	z6d09d60ddb(SimStruct *S)
#endif 

