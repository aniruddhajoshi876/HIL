// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL    (0xcd0+178-0xd80)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO113_di_s
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sg_io113_18.h"
#include "simstruc.h"
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#else
#include "sg_common.h"
#include "sg_printf.h"
#include "sg_module_registry.h"
#include "sg_module_types.h"
#endif
#define SG_EARLY_INIT
#include "sg_callback.h"
#define ze13f49a01f           ssGetSFcnParam(S, (0x68b+2877-0x11c8))
#define za9d8fb6bcf             ssGetSFcnParam(S, (0x93d+3792-0x180c))
#define z3832b85a32           ssGetSFcnParam(S, (0x21d1+628-0x2443))
#define z702a26a5e9                ssGetSFcnParam(S, (0x1c1c+2071-0x2430))
#define zdf24515981                           ((0x3d+1690-0x6d3))
#define z2e6483d505              ((0xb5+2926-0xc23))
#define zc5ce4cb81a              ((0x1309+366-0x1477))
#define z2b17e2ee3b              ((0x23d4+315-0x250f))
static char_T msg[(0x2dc+1530-0x7d6)];static void mdlInitializeSizes(SimStruct*S){uint32_T i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x9ba+4530-0x1b6c));ssSetNumDiscStates(S,(0x675+7003-0x21d0));if(!ssSetNumInputPorts(S,(0x1696+812-0x19c2)))return;if(!ssSetNumOutputPorts(S,(int)mxGetN(za9d8fb6bcf)))return;for(i=(0x677+1397-0xbec);i<(int)mxGetN(za9d8fb6bcf);i++){ssSetOutputPortWidth(S,i,(0x117+3788-0xfe2));ssSetOutputPortDataType(S,i,SS_DOUBLE);}ssSetNumSampleTimes(S,(0xbc3+4986-0x1f3c));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x5f5+1242-0xacf));ssSetNumNonsampledZCs(S,(0xe23+4086-0x1e19));for(i=(0x1637+3955-0x25aa);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x24d+4578-0x142f));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0xab3+6296-0x234b)]==-1.0){ssSetSampleTime(S,(0x3f3+3455-0x1172),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x9fb+3765-0x18b0),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x1c48+753-0x1f39),mxGetPr(z3832b85a32)[(0x1aa3+1611-0x20ee)]);ssSetOffsetTime(S,(0x278+938-0x622),0.0);}}
#ifndef MATLAB_MEX_FILE
static void sg_ModelLoad(SimStruct*S){}static void sg_ModelStart(SimStruct*S){}static void sg_ModelStep(SimStruct*S){uint32_T zf91d71c6d9=(uint32_T)mxGetN(za9d8fb6bcf);uint32_T i,channel;uint32_T input;real_T*y;uint32_T za0d38ae598=(uint32_T)mxGetPr(ze13f49a01f)[(0x12a0+3910-0x21e6)];za7f5fcb87c*zae10e3f17f=(za7f5fcb87c*)sg_module_get_custom_data(z12ba1d7c25,za0d38ae598);if(!zae10e3f17f){sprintf(msg,"\x25\x73\x20\x28\x49\x44\x20\x25\x75\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x69\x6e\x20\x44\x49\x20\x4d\x6f\x64\x65\x6c\x53\x74\x65\x70" "\n",DEVNAME,za0d38ae598);ssSetErrorStatus(S,msg);return;}input=zae10e3f17f->z3fad3d9764[z9621b996a9];SG_PRINTF(TRACE,"\x52\x45\x47\x5f\x44\x50\x52\x20\x28\x64\x69\x29\x3a\x20\x30\x78\x25\x78" "\n",input);for(i=(0x18a7+655-0x1b36);i<zf91d71c6d9;i++){channel=(uint32_T)mxGetPr(za9d8fb6bcf)[i]-(0x12ba+46-0x12e7);y=ssGetOutputPortSignal(S,i);switch(channel){case(0x106c+1631-0x16cb):y[(0x62c+6279-0x1eb3)]=(input&(0x990+7380-0x2663));break;case(0x148b+4731-0x2705):y[(0x9b+6749-0x1af8)]=(input&(0x4a+8202-0x2052))>>(0x3e8+8550-0x254d);break;case(0x13ff+237-0x14ea):y[(0x212+9258-0x263c)]=(input&(0x388+60-0x3c0))>>(0x1763+1908-0x1ed5);break;case(0x75b+7431-0x245f):y[(0x20ea+1390-0x2658)]=(input&(0x53d+5059-0x18f8))>>(0x1458+1196-0x1901);break;case(0x97d+2353-0x12aa):y[(0x15d6+2343-0x1efd)]=(input&(0x1549+2932-0x1fbd))>>(0x302+4146-0x132c);break;case(0x341+4570-0x1516):y[(0x59a+413-0x737)]=(input&(0xb5a+7536-0x26ca))>>(0xda+6805-0x1b66);break;case(0x1ca5+662-0x1f35):y[(0x1565+894-0x18e3)]=(input&(0xbb3+3881-0x16dc))>>(0x1b+6135-0x1808);break;case(0xce2+5780-0x236f):y[(0xe10+3275-0x1adb)]=(input&(0x1424+1638-0x128a))>>(0x6e4+7677-0x24d6);break;default:y[(0x9d6+1303-0xeed)]=0.0;break;}}}static void sg_ModelStop(SimStruct*S){}
#endif 
#include "sg_sfcn_glue.h"   

