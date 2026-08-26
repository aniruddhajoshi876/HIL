// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL (0xfe9+3203-0x1c6a)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_mscp_SC4191_5110k_10k_write
#include "simstruc.h"
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#else
#include "sg_common.h"
#include "sg_printf.h"
#include <math.h>
#endif
#include "sg_callback.h"
#define z89bd7ae7ba    (0x11b9+4586-0x23a1)
#define zdf24515981 ((0xb03+1139-0xf76))
#define z2e6483d505 ((0x232+2526-0xc10))
#define zc5ce4cb81a ((0x1032+5476-0x2596))
#define z2b17e2ee3b ((0x1fd1+114-0x2043))
static char msg[(0x3e5+8993-0x2606)];static void mdlInitializeSizes(SimStruct*S){ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0xe83+1394-0x13f5));ssSetNumDiscStates(S,(0xc8b+6616-0x2663));if(!ssSetNumInputPorts(S,(0x232+4200-0x1299)))return;ssSetInputPortWidth(S,(0xdf6+6034-0x2588),(0x2282+380-0x23fd));ssSetInputPortDataType(S,(0x487+4722-0x16f9),SS_DOUBLE);ssSetInputPortDirectFeedThrough(S,(0xf+5975-0x1766),(0x151+9460-0x2644));ssSetInputPortRequiredContiguous(S,(0x8f4+4750-0x1b82),(0x4d1+209-0x5a1));if(!ssSetNumOutputPorts(S,z89bd7ae7ba))return;for(uint8_T i=(0x1482+2394-0x1ddc);i<z89bd7ae7ba;i++){ssSetOutputPortWidth(S,i,(0x50b+2293-0xdff));ssSetOutputPortDataType(S,i,SS_UINT8);}ssSetNumSampleTimes(S,(0x3e8+806-0x70d));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x1ceb+588-0x1f37));ssSetNumNonsampledZCs(S,(0xedc+6187-0x2707));ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){ssSetSampleTime(S,(0x7+5521-0x1598),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x1445+253-0x1542),FIXED_IN_MINOR_STEP_OFFSET);}
#ifndef MATLAB_MEX_FILE
static void sg_ModelLoad(SimStruct*S){}static void sg_ModelStart(SimStruct*S){}static void sg_ModelStep(SimStruct*S){uint16_t zb0004dfabf;double*number=(double*)ssGetInputPortSignal(S,(0x862+1558-0xe78));if(*number<(0x3b3+6265-0x1c2c)){zb0004dfabf=(0x231+4475-0x13ac);}else if(*number>5110000){zb0004dfabf=(0x548+1406-0xac5);}else{zb0004dfabf=~((uint16_t)round(*number/(0x807+4278-0x14d5)/(0x594+5992-0x1cf2))<<(0x1+9609-0x2589));}SG_PRINTF(TRACE,"\x69\x6e\x20\x3d\x20\x25\x2e\x31\x66\x2c\x20\x6f\x75\x74\x20\x3d\x20\x30\x78\x25\x78\x20" "\n",*number,zb0004dfabf);uint8_t*z8144f427aa=(uint8_t*)ssGetOutputPortSignal(S,(0x126c+1599-0x18ab));*z8144f427aa=zb0004dfabf&(0xb00+6505-0x236a);z8144f427aa=(uint8_t*)ssGetOutputPortSignal(S,(0x1a83+2777-0x255b));*z8144f427aa=(zb0004dfabf>>(0x223+8235-0x2246))&(0x45d+4087-0x1451);}static void sg_ModelStop(SimStruct*S){}
#endif                    
#include "sg_sfcn_glue.h" 

