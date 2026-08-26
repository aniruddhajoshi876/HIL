// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL (0x46d+5755-0x1ae6)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_mscp_SC9503_SPST_TTL_write
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
#define z888793605c (0x11a9+1014-0x1597)
#define z89bd7ae7ba    (0x8b0+745-0xb98)
#define zdf24515981 ((0x12a7+139-0x1332))
#define z2e6483d505 ((0x1946+562-0x1b78))
#define zc5ce4cb81a ((0xfbc+1489-0x158d))
#define z2b17e2ee3b ((0x5a+8776-0x22a2))
static char msg[(0xb8d+5373-0x1f8a)];static void mdlInitializeSizes(SimStruct*S){ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0xf77+3161-0x1bd0));ssSetNumDiscStates(S,(0xbf+1831-0x7e6));if(!ssSetNumInputPorts(S,z888793605c))return;for(uint8_T i=(0x3f4+5857-0x1ad5);i<z888793605c;i++){ssSetInputPortWidth(S,i,(0x905+3391-0x1643));ssSetInputPortDataType(S,i,SS_UINT8);ssSetInputPortDirectFeedThrough(S,i,(0x109f+4768-0x233e));ssSetInputPortRequiredContiguous(S,i,(0xdbf+2581-0x17d3));}if(!ssSetNumOutputPorts(S,z89bd7ae7ba))return;for(uint8_T i=(0x3eb+1772-0xad7);i<z89bd7ae7ba;i++){ssSetOutputPortWidth(S,i,(0x428+6542-0x1db5));ssSetOutputPortDataType(S,i,SS_UINT8);}ssSetNumSampleTimes(S,(0x3b5+3031-0xf8b));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x1629+3211-0x22b4));ssSetNumNonsampledZCs(S,(0xf08+3090-0x1b1a));ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){ssSetSampleTime(S,(0x365+3845-0x126a),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x15db+4086-0x25d1),FIXED_IN_MINOR_STEP_OFFSET);}
#ifndef MATLAB_MEX_FILE
static void sg_ModelLoad(SimStruct*S){}static void sg_ModelStart(SimStruct*S){}static void sg_ModelStep(SimStruct*S){uint8_t zb0004dfabf[z888793605c]={(0x431+302-0x55f),(0x936+90-0x990),(0xc2f+863-0xf8e),(0x145b+2676-0x1ecf),(0x1304+3792-0x21d4),(0x171d+3002-0x22d7),(0x675+2565-0x107a),(0x1326+1966-0x1ad4)};for(size_t i=(0x1a63+1333-0x1f98);i<z888793605c;i++){zb0004dfabf[i]=*((uint8_t*)ssGetInputPortSignal(S,i));}uint8_t*z8144f427aa=(uint8_t*)ssGetOutputPortSignal(S,(0x601+139-0x68c));*z8144f427aa=z4f51a17a8b(zb0004dfabf,(0x95a+3519-0x1718));}static void sg_ModelStop(SimStruct*S){}static uint8_t z4f51a17a8b(uint8_t*zb0004dfabf,uint8_t z76ee6a2e95){uint8_t zbc0966abcd=(0x11f4+2068-0x1a08);for(uint8_t bit=(0x406+2538-0xdf0);bit<(0x911+6911-0x2408);bit++){zbc0966abcd|=((zb0004dfabf[(z76ee6a2e95-(0xc55+958-0x1012))+bit]&(0x11b6+4358-0x22bb))<<bit);}return zbc0966abcd;}
#endif                    
#include "sg_sfcn_glue.h" 

