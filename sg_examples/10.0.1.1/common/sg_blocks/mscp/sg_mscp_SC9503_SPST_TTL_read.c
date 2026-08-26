// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL (0x1308+3885-0x2233)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_mscp_SC9503_SPST_TTL_read
#include "simstruc.h"
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#else
#include "sg_common.h"
#include "sg_printf.h"
static uint8_t z4f51a17a8b(uint8_t z5a81a04045,uint8_t zb81d41919e);
#endif
#include "sg_callback.h"
#define z888793605c (0xb6c+1079-0xf9b)
#define z89bd7ae7ba    (0x352+232-0x439)
#define zdf24515981 ((0x40c+6817-0x1ead))
#define z2e6483d505 ((0x7e1+4725-0x1a56))
#define zc5ce4cb81a ((0x12cc+2992-0x1e7c))
#define z2b17e2ee3b ((0x2e4+7284-0x1f58))
static char msg[(0x1017+4525-0x20c4)];static void mdlInitializeSizes(SimStruct*S){ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0xf37+2894-0x1a85));ssSetNumDiscStates(S,(0xc10+2888-0x1758));if(!ssSetNumInputPorts(S,z89bd7ae7ba))return;for(uint8_T i=(0x1140+2722-0x1be2);i<z89bd7ae7ba;i++){ssSetInputPortWidth(S,i,(0x1c36+2437-0x25ba));ssSetInputPortDataType(S,i,SS_UINT8);ssSetInputPortDirectFeedThrough(S,i,(0x1701+1326-0x1c2e));ssSetInputPortRequiredContiguous(S,i,(0x180f+2533-0x21f3));}if(!ssSetNumOutputPorts(S,z888793605c))return;for(uint8_T i=(0x862+5920-0x1f82);i<z888793605c;i++){ssSetOutputPortWidth(S,i,(0x2308+885-0x267c));ssSetOutputPortDataType(S,i,SS_UINT8);}ssSetNumSampleTimes(S,(0x1499+123-0x1513));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0xa96+5023-0x1e35));ssSetNumNonsampledZCs(S,(0x151a+24-0x1532));ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){ssSetSampleTime(S,(0x136+2064-0x946),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x1d3c+426-0x1ee6),FIXED_IN_MINOR_STEP_OFFSET);}
#ifndef MATLAB_MEX_FILE
static void sg_ModelLoad(SimStruct*S){}static void sg_ModelStart(SimStruct*S){}static void sg_ModelStep(SimStruct*S){uint8_t z5a81a04045=(0x18ca+788-0x1bde);z5a81a04045=*((uint8_t*)ssGetInputPortSignal(S,(0x1b7+9291-0x2602)));for(size_t i=(0x1b15+544-0x1d35);i<z888793605c;i++){uint8_t zb81d41919e=(uint8_t)(i%(0x54+6447-0x197b));uint8_t*z781a22fa08=(uint8_t*)ssGetOutputPortSignal(S,i);*z781a22fa08=z4f51a17a8b(z5a81a04045,zb81d41919e);}}static void sg_ModelStop(SimStruct*S){}static uint8_t z4f51a17a8b(uint8_t z5a81a04045,uint8_t zb81d41919e){return(z5a81a04045>>zb81d41919e)&(0xfa5+3889-0x1ed5);}
#endif                    
#include "sg_sfcn_glue.h" 

