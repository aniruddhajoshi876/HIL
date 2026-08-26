// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL (0x6d0+3147-0x1319)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_mscp_SC4101_100_0_1_read
#include "simstruc.h"
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#else
#include "sg_common.h"
#include "sg_printf.h"
#include <math.h>
static double z4f51a17a8b(uint8_t*zb0004dfabf,uint8_t za4fbfeeac1);
#endif
#include "sg_callback.h"
#define z888793605c (0x942+3563-0x1725)
#define z89bd7ae7ba    (0x11ad+3654-0x1fe9)
#define zdf24515981 ((0x1d9d+399-0x1f2c))
#define z2e6483d505 ((0x444+365-0x5b1))
#define zc5ce4cb81a ((0x1b08+1571-0x212b))
#define z2b17e2ee3b ((0x1020+4628-0x2234))
static char msg[(0x2f3+7292-0x1e6f)];static void mdlInitializeSizes(SimStruct*S){ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x12eb+1920-0x1a6b));ssSetNumDiscStates(S,(0x800+6485-0x2155));if(!ssSetNumInputPorts(S,z89bd7ae7ba))return;for(uint8_T i=(0x1cd8+746-0x1fc2);i<z89bd7ae7ba;i++){ssSetInputPortWidth(S,i,(0x801+3860-0x1714));ssSetInputPortDataType(S,i,SS_UINT8);ssSetInputPortDirectFeedThrough(S,i,(0x19f2+3022-0x25bf));ssSetInputPortRequiredContiguous(S,i,(0x4ed+1598-0xb2a));}if(!ssSetNumOutputPorts(S,z888793605c))return;for(uint8_T i=(0x1565+2601-0x1f8e);i<z888793605c;i++){ssSetOutputPortWidth(S,i,(0x159f+1602-0x1be0));ssSetOutputPortDataType(S,i,SS_DOUBLE);}ssSetNumSampleTimes(S,(0xbc+5530-0x1655));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x7ca+7183-0x23d9));ssSetNumNonsampledZCs(S,(0x537+7519-0x2296));ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){ssSetSampleTime(S,(0x3f4+8235-0x241f),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x24fa+187-0x25b5),FIXED_IN_MINOR_STEP_OFFSET);}
#ifndef MATLAB_MEX_FILE
static void sg_ModelLoad(SimStruct*S){}static void sg_ModelStart(SimStruct*S){}static void sg_ModelStep(SimStruct*S){uint8_t zb0004dfabf[z89bd7ae7ba]={(0x1f66+1869-0x26b3),(0x1353+1965-0x1b00),(0x58+4083-0x104b),(0x136b+2809-0x1e64),(0x514+7-0x51b),(0xa89+5080-0x1e61),(0x866+5896-0x1f6e),(0x64f+6877-0x212c),(0x977+1111-0xdce),(0x54+7401-0x1d3d)};for(size_t i=(0x9ea+4274-0x1a9c);i<z89bd7ae7ba;i++){uint8_t*number=(uint8_t*)ssGetInputPortSignal(S,i);zb0004dfabf[i]=~(*number);}for(size_t i=(0x128c+4742-0x2512);i<z888793605c;i++){double*z781a22fa08=(double*)ssGetOutputPortSignal(S,i);*z781a22fa08=z4f51a17a8b(zb0004dfabf,i);}}static void sg_ModelStop(SimStruct*S){}static double z4f51a17a8b(uint8_t*zb0004dfabf,uint8_t za4fbfeeac1){return(((zb0004dfabf[(0x195b+3175-0x25c2)]>>za4fbfeeac1)&(0xff0+1915-0x176a))<<(0x6af+3949-0x161c)|((zb0004dfabf[(0xa24+1489-0xff4)]>>za4fbfeeac1)&(0x14f+9303-0x25a5))<<(0x68c+8193-0x2684)|((zb0004dfabf[(0xcfd+3297-0x19dc)]>>za4fbfeeac1)&(0xf39+5531-0x24d3))<<(0x12e4+1067-0x170e)|((zb0004dfabf[(0xc24+5906-0x2333)]>>za4fbfeeac1)&(0x2196+292-0x22b9))<<(0xee7+2930-0x1a51)|((zb0004dfabf[(0xd6b+1170-0x11f9)]>>za4fbfeeac1)&(0x1623+880-0x1992))<<(0xa2a+789-0xd3d)|((zb0004dfabf[(0x18d+5009-0x1519)]>>za4fbfeeac1)&(0x135+4305-0x1205))<<(0x3b3+6822-0x1e52)|((zb0004dfabf[(0xdb7+5917-0x24ce)]>>za4fbfeeac1)&(0x10+9935-0x26de))<<(0x8f5+2027-0x10dd)|((zb0004dfabf[(0x1287+378-0x13fa)]>>za4fbfeeac1)&(0x775+2331-0x108f))<<(0x1498+3184-0x2102)|((zb0004dfabf[(0x13b+8413-0x2210)]>>za4fbfeeac1)&(0xc43+6486-0x2598))<<(0x354+7428-0x2054)|((zb0004dfabf[(0x156+6002-0x18bf)]>>za4fbfeeac1)&(0x2073+916-0x2406))<<(0x2211+348-0x2368))/10.0;}
#endif                    
#include "sg_sfcn_glue.h" 

