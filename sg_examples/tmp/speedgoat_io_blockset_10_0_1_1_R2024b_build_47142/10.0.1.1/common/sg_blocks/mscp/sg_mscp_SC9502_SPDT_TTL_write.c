// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL (0x15e1+2962-0x2171)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_mscp_SC9502_SPDT_TTL_write
#include "simstruc.h"
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#else
#include "sg_common.h"
#include "sg_printf.h"
#include <math.h>
static uint8_t z4f51a17a8b(uint8_t*zb0004dfabf,uint8_t z76ee6a2e95);
#endif
#include "sg_callback.h"
#define z888793605c (0x235+5827-0x18e8)
#define z89bd7ae7ba    (0xc06+3783-0x1acb)
#define zdf24515981 ((0x4c4+4269-0x1571))
#define z2e6483d505 ((0x502+3628-0x132e))
#define zc5ce4cb81a ((0x16b+8093-0x2108))
#define z2b17e2ee3b ((0x2422+22-0x2438))
static char msg[(0xb5b+1593-0x1094)];static void mdlInitializeSizes(SimStruct*S){ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x1e7f+649-0x2108));ssSetNumDiscStates(S,(0x71a+6020-0x1e9e));if(!ssSetNumInputPorts(S,z888793605c))return;for(uint8_T i=(0xc0a+4859-0x1f05);i<z888793605c;i++){ssSetInputPortWidth(S,i,(0x10d2+2604-0x1afd));ssSetInputPortDataType(S,i,SS_UINT8);ssSetInputPortDirectFeedThrough(S,i,(0x1c7+9053-0x2523));ssSetInputPortRequiredContiguous(S,i,(0xd81+5114-0x217a));}if(!ssSetNumOutputPorts(S,z89bd7ae7ba))return;for(uint8_T i=(0x212+7905-0x20f3);i<z89bd7ae7ba;i++){ssSetOutputPortWidth(S,i,(0x59a+7904-0x2479));ssSetOutputPortDataType(S,i,SS_UINT8);}ssSetNumSampleTimes(S,(0x138b+3741-0x2227));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x1f+1400-0x597));ssSetNumNonsampledZCs(S,(0x557+7690-0x2361));ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){ssSetSampleTime(S,(0x97+3552-0xe77),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x5e1+6820-0x2085),FIXED_IN_MINOR_STEP_OFFSET);}
#ifndef MATLAB_MEX_FILE
static void sg_ModelLoad(SimStruct*S){}static void sg_ModelStart(SimStruct*S){}static void sg_ModelStep(SimStruct*S){uint8_t zb0004dfabf[z888793605c]={(0x18ec+3321-0x25e5),(0x1eea+944-0x229a),(0x2493+47-0x24c2),(0x790+4478-0x190e),(0x710+3680-0x1570),(0x579+2743-0x1030),(0x12a7+1367-0x17fe),(0x459+7481-0x2192),(0x344+8464-0x2454),(0xc0f+6870-0x26e5),(0x13a3+2393-0x1cfc),(0x146c+2399-0x1dcb),(0x40+4614-0x1246),(0x1405+3128-0x203d),(0x12b9+918-0x164f),(0xc77+3622-0x1a9d)};for(size_t i=(0x1042+1959-0x17e9);i<z888793605c;i++){zb0004dfabf[i]=*((uint8_t*)ssGetInputPortSignal(S,i));}uint8_t*z8144f427aa=(uint8_t*)ssGetOutputPortSignal(S,(0x114d+4128-0x216d));*z8144f427aa=z4f51a17a8b(zb0004dfabf,(0x1867+961-0x1c27));z8144f427aa=(uint8_t*)ssGetOutputPortSignal(S,(0x466+3726-0x12f3));*z8144f427aa=z4f51a17a8b(zb0004dfabf,(0x1801+420-0x199c));}static void sg_ModelStop(SimStruct*S){}static uint8_t z4f51a17a8b(uint8_t*zb0004dfabf,uint8_t z76ee6a2e95){uint8_t zbc0966abcd=(0x566+2658-0xfc8);for(uint8_t bit=(0x2a2+786-0x5b4);bit<(0x125c+1706-0x18fe);bit++){zbc0966abcd|=((zb0004dfabf[(z76ee6a2e95-(0x170+2093-0x99c))+bit]&(0x15ef+503-0x17e5))<<bit);}return zbc0966abcd;}
#endif                    
#include "sg_sfcn_glue.h" 

