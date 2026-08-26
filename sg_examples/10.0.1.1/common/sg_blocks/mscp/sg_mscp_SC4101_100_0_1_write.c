// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL (0x1261+2594-0x1c81)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_mscp_SC4101_100_0_1_write
#include "simstruc.h"
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#else
#include "sg_common.h"
#include "sg_printf.h"
#include <math.h>
static uint8_t z4f51a17a8b(uint16_t*zb0004dfabf,uint8_t za4fbfeeac1);
#endif
#include "sg_callback.h"
#define z888793605c (0x123+4930-0x145d)
#define z89bd7ae7ba    (0xfed+2475-0x198e)
#define zdf24515981 ((0x106+6521-0x1a7f))
#define z2e6483d505 ((0xd43+657-0xfd4))
#define zc5ce4cb81a ((0xc49+2926-0x17b7))
#define z2b17e2ee3b ((0x3e6+459-0x5b1))
static char msg[(0x1086+3206-0x1c0c)];static void mdlInitializeSizes(SimStruct*S){ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0xc39+2403-0x159c));ssSetNumDiscStates(S,(0x7c5+1974-0xf7b));if(!ssSetNumInputPorts(S,z888793605c))return;for(uint8_T i=(0xd79+5549-0x2326);i<z888793605c;i++){ssSetInputPortWidth(S,i,(0xbd5+6634-0x25be));ssSetInputPortDataType(S,i,SS_DOUBLE);ssSetInputPortDirectFeedThrough(S,i,(0x39+765-0x335));ssSetInputPortRequiredContiguous(S,i,(0x3f2+5010-0x1783));}if(!ssSetNumOutputPorts(S,z89bd7ae7ba))return;for(uint8_T i=(0x13cd+2284-0x1cb9);i<z89bd7ae7ba;i++){ssSetOutputPortWidth(S,i,(0x1850+3420-0x25ab));ssSetOutputPortDataType(S,i,SS_UINT8);}ssSetNumSampleTimes(S,(0x245+6918-0x1d4a));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0xb3+5623-0x16aa));ssSetNumNonsampledZCs(S,(0xddb+5158-0x2201));ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){ssSetSampleTime(S,(0xa17+7129-0x25f0),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x1a2a+1005-0x1e17),FIXED_IN_MINOR_STEP_OFFSET);}
#ifndef MATLAB_MEX_FILE
static void sg_ModelLoad(SimStruct*S){}static void sg_ModelStart(SimStruct*S){}static void sg_ModelStep(SimStruct*S){uint16_t zb0004dfabf[(0x11c2+520-0x13c2)]={(0x623+1652-0xc97),(0x82f+4706-0x1a91),(0xf6d+3232-0x1c0d),(0xb03+5535-0x20a2),(0x32a+8872-0x25d2),(0x11c8+1966-0x1976),(0x81c+823-0xb53),(0x14df+4052-0x24b3)};for(size_t i=(0x2669+124-0x26e5);i<z888793605c;i++){double*number=(double*)ssGetInputPortSignal(S,i);if(*number<(0x6aa+3273-0x1373)){zb0004dfabf[i]=(0xd99+6197-0x25ce);}else if(*number>102.3){zb0004dfabf[i]=(0x408+2201-0xca1);}else{zb0004dfabf[i]=~(uint16_t)round(*number*(0x1320+2149-0x1b7b));}SG_PRINTF(TRACE,"\x69\x6e\x20\x3d\x20\x25\x2e\x31\x66\x2c\x20\x6f\x75\x74\x20\x3d\x20\x30\x78\x25\x78\x20" "\n",*number,zb0004dfabf[i]);}uint8_t*z8144f427aa=(uint8_t*)ssGetOutputPortSignal(S,(0x4aa+8692-0x269e));*z8144f427aa=z4f51a17a8b(zb0004dfabf,(0x1e99+928-0x2239));z8144f427aa=(uint8_t*)ssGetOutputPortSignal(S,(0x1036+3866-0x1f4f));*z8144f427aa=z4f51a17a8b(zb0004dfabf,(0x88b+2263-0x1159));z8144f427aa=(uint8_t*)ssGetOutputPortSignal(S,(0x1257+4595-0x2448));*z8144f427aa=z4f51a17a8b(zb0004dfabf,(0x3bb+8654-0x2588));z8144f427aa=(uint8_t*)ssGetOutputPortSignal(S,(0xa7+7578-0x1e3e));*z8144f427aa=z4f51a17a8b(zb0004dfabf,(0x1780+1881-0x1ed1));z8144f427aa=(uint8_t*)ssGetOutputPortSignal(S,(0xc52+3111-0x1875));*z8144f427aa=z4f51a17a8b(zb0004dfabf,(0xa61+3364-0x1783));z8144f427aa=(uint8_t*)ssGetOutputPortSignal(S,(0xae9+961-0xea5));*z8144f427aa=z4f51a17a8b(zb0004dfabf,(0x365+8843-0x25e9));z8144f427aa=(uint8_t*)ssGetOutputPortSignal(S,(0x164d+1353-0x1b90));*z8144f427aa=z4f51a17a8b(zb0004dfabf,(0x647+2105-0xe7d));z8144f427aa=(uint8_t*)ssGetOutputPortSignal(S,(0x75+8432-0x215e));*z8144f427aa=z4f51a17a8b(zb0004dfabf,(0x771+7748-0x25af));z8144f427aa=(uint8_t*)ssGetOutputPortSignal(S,(0x1bb3+140-0x1c37));*z8144f427aa=z4f51a17a8b(zb0004dfabf,(0x148+1887-0x8a3));z8144f427aa=(uint8_t*)ssGetOutputPortSignal(S,(0x241c+702-0x26d1));*z8144f427aa=z4f51a17a8b(zb0004dfabf,(0x87b+2012-0x1052));}static void sg_ModelStop(SimStruct*S){}static uint8_t z4f51a17a8b(uint16_t*zb0004dfabf,uint8_t za4fbfeeac1){return(((zb0004dfabf[(0xf81+674-0x1223)]>>za4fbfeeac1)&(0x31a+4166-0x135f))<<(0x1e0+2320-0xaf0)|((zb0004dfabf[(0x44b+6038-0x1be0)]>>za4fbfeeac1)&(0x85+800-0x3a4))<<(0x1a70+961-0x1e30)|((zb0004dfabf[(0x1374+448-0x1532)]>>za4fbfeeac1)&(0x11c7+2008-0x199e))<<(0x22+7719-0x1e47)|((zb0004dfabf[(0xf17+737-0x11f5)]>>za4fbfeeac1)&(0x13e0+1736-0x1aa7))<<(0x29b+4930-0x15da)|((zb0004dfabf[(0x225+5392-0x1731)]>>za4fbfeeac1)&(0x5e8+7339-0x2292))<<(0x12ea+1225-0x17af)|((zb0004dfabf[(0xe3b+234-0xf20)]>>za4fbfeeac1)&(0x4d6+5089-0x18b6))<<(0xb4c+1953-0x12e8)|((zb0004dfabf[(0x7d4+5523-0x1d61)]>>za4fbfeeac1)&(0x1cdf+1158-0x2164))<<(0x9f4+5270-0x1e84)|((zb0004dfabf[(0xa76+3744-0x190f)]>>za4fbfeeac1)&(0xbe5+3839-0x1ae3))<<(0x111a+4982-0x2489));}
#endif                    
#include "sg_sfcn_glue.h" 

