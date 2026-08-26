// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL    (0xe6d+4830-0x2149)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO102_da_s_v2
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sg_io102.h"
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
#define zdf24515981          ((0x298+4038-0x1259))
#define ze13f49a01f           ssGetSFcnParam(S,(0xaa9+4476-0x1c25))
#define za9d8fb6bcf             ssGetSFcnParam(S,(0x16e4+3621-0x2508))
#define z8fd86139be               ssGetSFcnParam(S,(0x1d2+3189-0xe45))
#define z3832b85a32           ssGetSFcnParam(S,(0x399+3251-0x1049))
#define z702a26a5e9                ssGetSFcnParam(S,(0x1908+332-0x1a50))
#define z2e6483d505              ((0x1121+919-0x14b8))
#define zc5ce4cb81a              ((0x355+496-0x545))
#define z2b17e2ee3b              ((0x49c+895-0x81b))
static char_T msg[(0x153c+676-0x16e0)];static void mdlInitializeSizes(SimStruct*S){uint32_T i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x553+3765-0x1408));ssSetNumDiscStates(S,(0x6c5+5448-0x1c0d));if(!ssSetNumOutputPorts(S,(0x192+4037-0x1157)))return;if(!ssSetNumInputPorts(S,(int)mxGetN(za9d8fb6bcf)))return;for(i=(0xc3d+1770-0x1327);i<(int)mxGetN(za9d8fb6bcf);i++){ssSetInputPortWidth(S,i,(0x1153+790-0x1468));ssSetInputPortDirectFeedThrough(S,i,(0x6aa+2367-0xfe8));ssSetInputPortRequiredContiguous(S,i,(0x1d9+1893-0x93d));}ssSetNumSampleTimes(S,(0x118b+2717-0x1c27));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x603+1691-0xc9e));ssSetNumNonsampledZCs(S,(0x23fb+290-0x251d));for(i=(0x953+5016-0x1ceb);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x3e8+5269-0x187d));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x220a+1111-0x2661)]==-1.0){ssSetSampleTime(S,(0x1d7f+358-0x1ee5),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x42+7997-0x1f7f),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0xf6f+3840-0x1e6f),mxGetPr(z3832b85a32)[(0x1e3a+1294-0x2348)]);ssSetOffsetTime(S,(0x1afd+1771-0x21e8),0.0);}}
#ifndef MATLAB_MEX_FILE
static void sg_ModelLoad(SimStruct*S){}static void sg_ModelStart(SimStruct*S){}static void sg_ModelStep(SimStruct*S){uint32_T za0d38ae598=((int_T)mxGetPr(ze13f49a01f)[(0x4bd+4059-0x1498)]);uint16_T zf91d71c6d9=(uint32_T)mxGetN(za9d8fb6bcf);uint16_T i,channel;real_T*zc7fdaf6331;int32_T out;uint32_T flags;zcdb36f3262*zae10e3f17f=(zcdb36f3262*)sg_module_get_custom_data(z12ba1d7c25,za0d38ae598);if(!zae10e3f17f){sprintf(msg,"\x49\x4f\x25\x64\x20\x28\x49\x44\x20\x25\x64\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x69\x6e\x20\x44\x41\x20\x4d\x6f\x64\x65\x6c\x53\x74\x65\x70" "\n",z12ba1d7c25,za0d38ae598);ssSetErrorStatus(S,msg);return;}bool z11971b8360=false;for(i=(0x656+3830-0x154c);i<zf91d71c6d9;i++){channel=(uint16_T)mxGetPr(za9d8fb6bcf)[i]-(0x1c7f+1232-0x214e);zc7fdaf6331=(real_T*)ssGetInputPortRealSignal(S,i);out=(int32_T)((*zc7fdaf6331+zae10e3f17f->offset)*zae10e3f17f->z0754dd67cc);if(out>65535)out=65535;if(out<(0x6a8+2388-0xffc))out=(0xe42+2494-0x1800);flags=(i==zf91d71c6d9-(0x971+6163-0x2183))?786432:(0x14d+1901-0x8ba);zae10e3f17f->z3fad3d9764[(0x13f3+4370-0x24ff)]=out|(channel<<(0x7a0+7104-0x2350))|flags;z11971b8360=true;}if(z11971b8360){zae10e3f17f->z3fad3d9764[(0x1919+3195-0x2594)]|=(0x1899+3961-0x2012);}}static void sg_ModelStop(SimStruct*S){}
#endif 
#include "sg_sfcn_glue.h" 

