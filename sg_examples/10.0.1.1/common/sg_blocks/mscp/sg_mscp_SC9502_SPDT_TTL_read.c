// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL (0x1313+2339-0x1c34)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_mscp_SC9502_SPDT_TTL_read
#include "simstruc.h"
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#else
#include "sg_common.h"
#include "sg_printf.h"
static uint8_t z4f51a17a8b(uint8_t z5a81a04045,uint8_t zb81d41919e);
#endif
#include "sg_callback.h"
#define z888793605c (0xea4+5338-0x236e)
#define z89bd7ae7ba    (0x13b8+3531-0x2181)
#define zdf24515981 ((0x6f4+5417-0x1c1d))
#define z2e6483d505 ((0x3d4+1796-0xad8))
#define zc5ce4cb81a ((0x383+2656-0xde3))
#define z2b17e2ee3b ((0x191b+611-0x1b7e))
static char msg[(0x713+1806-0xd21)];static void mdlInitializeSizes(SimStruct*S){ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x20f+8270-0x225d));ssSetNumDiscStates(S,(0xfd3+4886-0x22e9));if(!ssSetNumInputPorts(S,z89bd7ae7ba))return;for(uint8_T i=(0x871+5209-0x1cca);i<z89bd7ae7ba;i++){ssSetInputPortWidth(S,i,(0x1235+1421-0x17c1));ssSetInputPortDataType(S,i,SS_UINT8);ssSetInputPortDirectFeedThrough(S,i,(0xd67+4572-0x1f42));ssSetInputPortRequiredContiguous(S,i,(0xf85+3820-0x1e70));}if(!ssSetNumOutputPorts(S,z888793605c))return;for(uint8_T i=(0x2370+617-0x25d9);i<z888793605c;i++){ssSetOutputPortWidth(S,i,(0x1469+4743-0x26ef));ssSetOutputPortDataType(S,i,SS_UINT8);}ssSetNumSampleTimes(S,(0x201c+424-0x21c3));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x91c+5590-0x1ef2));ssSetNumNonsampledZCs(S,(0xc8c+1860-0x13d0));ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){ssSetSampleTime(S,(0x4a8+900-0x82c),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x1666+3897-0x259f),FIXED_IN_MINOR_STEP_OFFSET);}
#ifndef MATLAB_MEX_FILE
static void sg_ModelLoad(SimStruct*S){}static void sg_ModelStart(SimStruct*S){}static void sg_ModelStep(SimStruct*S){uint8_t z2467c10f63[z89bd7ae7ba]={(0x639+5303-0x1af0),(0x88+1531-0x683)};for(size_t i=(0x940+3249-0x15f1);i<z89bd7ae7ba;i++){z2467c10f63[i]=*((uint8_t*)ssGetInputPortSignal(S,i));}for(size_t i=(0x674+3227-0x130f);i<z888793605c;i++){uint8_t ze3e2313a2c=(uint8_t)(i/(0x3c1+8255-0x23f8));uint8_t zb81d41919e=(uint8_t)(i%(0x91c+4461-0x1a81));uint8_t*z781a22fa08=(uint8_t*)ssGetOutputPortSignal(S,i);*z781a22fa08=z4f51a17a8b(z2467c10f63[ze3e2313a2c],zb81d41919e);}}static void sg_ModelStop(SimStruct*S){}static uint8_t z4f51a17a8b(uint8_t z5a81a04045,uint8_t zb81d41919e){return(z5a81a04045>>zb81d41919e)&(0x1261+4897-0x2581);}
#endif                    
#include "sg_sfcn_glue.h" 

