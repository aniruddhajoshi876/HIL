// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL (0xdc5+791-0x10da)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_mscp_SC4191_5110k_10k_read
#include "simstruc.h"
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#else
#include "sg_common.h"
#include "sg_printf.h"
#endif
#include "sg_callback.h"
#define z89bd7ae7ba    (0x373+443-0x52c)
#define zdf24515981 ((0x9e5+6937-0x24fe))
#define z2e6483d505 ((0xc8f+3440-0x19ff))
#define zc5ce4cb81a ((0x960+2800-0x1450))
#define z2b17e2ee3b ((0x704+4868-0x1a08))
static char msg[(0x786+2884-0x11ca)];static void mdlInitializeSizes(SimStruct*S){ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x12a6+4605-0x24a3));ssSetNumDiscStates(S,(0x60b+381-0x788));if(!ssSetNumInputPorts(S,z89bd7ae7ba))return;for(uint8_T i=(0x192c+410-0x1ac6);i<z89bd7ae7ba;i++){ssSetInputPortWidth(S,i,(0x428+8054-0x239d));ssSetInputPortDataType(S,i,SS_UINT8);ssSetInputPortDirectFeedThrough(S,i,(0x7b9+3196-0x1434));ssSetInputPortRequiredContiguous(S,i,(0xbdc+864-0xf3b));}if(!ssSetNumOutputPorts(S,(0xa93+1183-0xf31)))return;ssSetOutputPortWidth(S,(0x713+3166-0x1371),(0xe0c+2668-0x1877));ssSetOutputPortDataType(S,(0xee8+3723-0x1d73),SS_DOUBLE);ssSetNumSampleTimes(S,(0x43a+3988-0x13cd));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x1738+3194-0x23b2));ssSetNumNonsampledZCs(S,(0x84a+1984-0x100a));ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){ssSetSampleTime(S,(0x1971+1072-0x1da1),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x14a2+1881-0x1bfb),FIXED_IN_MINOR_STEP_OFFSET);}
#ifndef MATLAB_MEX_FILE
static void sg_ModelLoad(SimStruct*S){}static void sg_ModelStart(SimStruct*S){}static void sg_ModelStep(SimStruct*S){uint8_t zb0004dfabf[z89bd7ae7ba]={(0xf69+4961-0x22ca),(0x1816+2657-0x2277)};for(size_t i=(0x12e4+3487-0x2083);i<z89bd7ae7ba;i++){uint8_t*number=(uint8_t*)ssGetInputPortSignal(S,i);zb0004dfabf[i]=~(*number);}SG_PRINTF(TRACE,"\x69\x6e\x70\x75\x74\x56\x61\x6c\x75\x65\x5b\x30\x5d\x20\x3d\x20\x25\x75\x2c\x20\x69\x6e\x70\x75\x74\x56\x61\x6c\x75\x65\x5b\x31\x5d\x20\x3d\x20\x25\x75\x20" "\n",zb0004dfabf[(0x13cc+4535-0x2583)],zb0004dfabf[(0x6ad+2664-0x1114)]);double*z781a22fa08=(double*)ssGetOutputPortSignal(S,(0xa10+6267-0x228b));if(zb0004dfabf[(0x37f+2176-0xbff)]&(0x29c+1835-0x9c6)){*z781a22fa08=-(0x22c9+589-0x2515);}else{*z781a22fa08=(zb0004dfabf[(0x1bd9+509-0x1dd6)]>>(0x953+3308-0x163e)|(zb0004dfabf[(0x10d5+2619-0x1b0f)]&(0x1423+3613-0x223d))<<(0xa81+4857-0x1d73))*(0x6d8+2539-0x10b9)*1000.0;}}static void sg_ModelStop(SimStruct*S){}
#endif                    
#include "sg_sfcn_glue.h" 

