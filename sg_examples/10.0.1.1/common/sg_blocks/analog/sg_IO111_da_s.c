// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL    (0x207c+1631-0x26d9)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO111_da_s
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sg_io111.h"
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
#define zdf24515981          ((0x1306+1314-0x1821))
#define ze13f49a01f           ssGetSFcnParam(S,(0x902+4063-0x18e1))
#define z702a26a5e9                ssGetSFcnParam(S,(0x18ef+484-0x1ad2))
#define z1f7e7173d9          ssGetSFcnParam(S,(0x9b7+4031-0x1974))
#define zc6f930323f            ssGetSFcnParam(S,(0x5e9+6774-0x205c))
#define z3832b85a32           ssGetSFcnParam(S,(0x227+4942-0x1571))
#define z84dd9a9a5c            ssGetSFcnParam(S,(0x548+1881-0xc9c))
#define z4d2d92ea80         ssGetSFcnParam(S,(0x9b9+1694-0x1051))
#define z2e6483d505              ((0x1d16+859-0x2071))
#define zc5ce4cb81a              ((0x138+80-0x188))
#define z2b17e2ee3b              ((0x13a4+2644-0x1df8))
static char_T msg[(0x220+7683-0x1f23)];static void mdlInitializeSizes(SimStruct*S){uint16_T i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0xff6+4-0xffa));ssSetNumDiscStates(S,(0x68c+4245-0x1721));if(!ssSetNumOutputPorts(S,(0x15cb+2075-0x1de6)))return;if(!ssSetNumInputPorts(S,(int)mxGetN(z1f7e7173d9)))return;for(i=(0x262+7882-0x212c);i<(int)mxGetN(z1f7e7173d9);i++){ssSetInputPortWidth(S,i,(0xd20+3539-0x1af2));ssSetInputPortDirectFeedThrough(S,i,(0x1c1d+1779-0x230f));ssSetInputPortRequiredContiguous(S,i,(0x6ed+5504-0x1c6c));}ssSetNumSampleTimes(S,(0xa79+2106-0x12b2));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x1ce4+246-0x1dda));ssSetNumNonsampledZCs(S,(0x474+2052-0xc78));for(i=(0x745+423-0x8ec);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,SS_PRM_NOT_TUNABLE);}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x161d+65-0x165e)]==-1.0){ssSetSampleTime(S,(0x126b+673-0x150c),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x130f+2100-0x1b43),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x1d34+1002-0x211e),mxGetPr(z3832b85a32)[(0x2fd+6535-0x1c84)]);ssSetOffsetTime(S,(0xbbf+2276-0x14a3),0.0);}}
#ifndef MATLAB_MEX_FILE
static void sg_ModelLoad(SimStruct*S){}static void sg_ModelStart(SimStruct*S){}static void sg_ModelStep(SimStruct*S){uint16_T i,channel,range;real_T out,*zc7fdaf6331;uint32_T za0d38ae598=((int_T)mxGetPr(ze13f49a01f)[(0x1527+2183-0x1dae)]);zcda1f3535f*zae10e3f17f=(zcda1f3535f*)sg_module_get_custom_data(z12ba1d7c25,za0d38ae598);if(!zae10e3f17f){sprintf(msg,"\x49\x4f\x25\x64\x20\x28\x49\x44\x20\x25\x64\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x69\x6e\x20\x44\x41\x20\x4d\x6f\x64\x65\x6c\x53\x74\x65\x70" "\n",z12ba1d7c25,za0d38ae598);ssSetErrorStatus(S,msg);return;}for(i=(0x688+7861-0x253d);i<mxGetN(z1f7e7173d9);i++){channel=(uint16_T)mxGetPr(z1f7e7173d9)[i]-(0x45a+1727-0xb18);range=(uint16_T)mxGetPr(zc6f930323f)[channel];zc7fdaf6331=(real_T*)ssGetInputPortRealSignal(S,i);out=zc7fdaf6331[(0x236+4162-0x1278)]*zae10e3f17f->z0eea8c34d0[channel];z2ecaac0920(range,zae10e3f17f->z9fb53cdf50[channel],zae10e3f17f->zb817ad7ad6[channel],&out);zae10e3f17f->z571d7e98ef[zc3ebc5e98b(channel)]=(int16_T)out;}}static void sg_ModelStop(SimStruct*S){}
#endif 
#include "sg_sfcn_glue.h"   

