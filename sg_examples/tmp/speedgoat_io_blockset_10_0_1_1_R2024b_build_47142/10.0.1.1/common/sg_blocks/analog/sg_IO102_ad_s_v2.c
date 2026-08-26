// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL    (0x660+5208-0x1ab6)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO102_ad_s_v2
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
#define zdf24515981          ((0x86a+338-0x9b5))
#define ze13f49a01f           ssGetSFcnParam(S,(0xbbf+858-0xf19))
#define za9d8fb6bcf             ssGetSFcnParam(S,(0xded+5384-0x22f4))
#define z8fd86139be               ssGetSFcnParam(S,(0xa15+5373-0x1f10))
#define z3832b85a32           ssGetSFcnParam(S,(0xca+2048-0x8c7))
#define z702a26a5e9                ssGetSFcnParam(S,(0x1c6b+2212-0x250b))
#define z05e67510ff        ssGetSFcnParam(S,(0x580+3437-0x12e8))
#define z0d9acd09bb         ssGetSFcnParam(S,(0x381+6418-0x1c8d))
#define z2e6483d505              ((0xbe4+5285-0x2089))
#define zc5ce4cb81a              ((0xe9+6616-0x1ac1))
#define z2b17e2ee3b              ((0x395+2544-0xd85))
static char_T msg[(0x1d6+3663-0xf25)];static void mdlInitializeSizes(SimStruct*S){uint16_T i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x973+4480-0x1af3));ssSetNumDiscStates(S,(0xc19+5947-0x2354));if(!ssSetNumInputPorts(S,(0xe31+4419-0x1f74)))return;if(!ssSetNumOutputPorts(S,(uint16_T)mxGetN(za9d8fb6bcf)))return;for(i=(0x79f+7905-0x2680);i<(uint16_T)mxGetN(za9d8fb6bcf);i++){ssSetOutputPortWidth(S,i,(0x586+13-0x592));}ssSetNumSampleTimes(S,(0x1fd1+1441-0x2571));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x615+2851-0x1138));ssSetNumNonsampledZCs(S,(0x148b+644-0x170f));for(i=(0x82b+7070-0x23c9);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x517+3769-0x13d0));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x126+6778-0x1ba0)]==-1.0){ssSetSampleTime(S,(0x13aa+3702-0x2220),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0xc57+5842-0x2329),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x203+333-0x350),mxGetPr(z3832b85a32)[(0x124d+3101-0x1e6a)]);ssSetOffsetTime(S,(0x1217+2522-0x1bf1),0.0);}}
#ifndef MATLAB_MEX_FILE
static void sg_ModelLoad(SimStruct*S){}static void sg_ModelStart(SimStruct*S){}static void sg_ModelStep(SimStruct*S){uint16_T zf91d71c6d9=(uint32_T)mxGetN(za9d8fb6bcf);real_T*y;uint32_T i;uint32_T count;uint32_T za0d38ae598=((int_T)mxGetPr(ze13f49a01f)[(0xa02+6086-0x21c8)]);zcdb36f3262*zae10e3f17f=(zcdb36f3262*)sg_module_get_custom_data(z12ba1d7c25,za0d38ae598);if(!zae10e3f17f){sprintf(msg,"\x49\x4f\x25\x64\x20\x28\x49\x44\x20\x25\x64\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x69\x6e\x20\x41\x44\x20\x4d\x6f\x64\x65\x6c\x53\x74\x65\x70" "\n",z12ba1d7c25,za0d38ae598);ssSetErrorStatus(S,msg);return;}zae10e3f17f->z3fad3d9764[(0xdab+3-0xdae)]|=(0x22c3+2955-0x1e4e);for(i=(0x2f3+5574-0x18b9);i<zf91d71c6d9;i++){y=ssGetOutputPortSignal(S,i);while(!(zae10e3f17f->z3fad3d9764[(0x644+1456-0xbf1)]&65536));count=zae10e3f17f->z3fad3d9764[(0x909+6575-0x22b6)]&65535;if(mxGetPr(z05e67510ff)[(0x241b+91-0x2476)]==(0x496+3324-0x1192)){*y=(real_T)count/zae10e3f17f->z0754dd67cc-zae10e3f17f->offset;}else{if(mxGetPr(z0d9acd09bb)[(0xcdf+2463-0x167e)]==(0x7f8+6170-0x2010)){if((mxGetPr(za9d8fb6bcf)[i]-(0x5d+4302-0x112a))<(0xb81+3799-0x1a48))*y=(real_T)count/zae10e3f17f->z0754dd67cc-zae10e3f17f->offset;else*y=((real_T)count/zae10e3f17f->z0754dd67cc-zae10e3f17f->offset)*(0x45d+7949-0x2364);}else{if((mxGetPr(za9d8fb6bcf)[i]-(0xffb+3092-0x1c0e))<(0x991+5595-0x1f64))*y=(real_T)count/zae10e3f17f->z0754dd67cc-zae10e3f17f->offset;else*y=((real_T)count/zae10e3f17f->z0754dd67cc-zae10e3f17f->offset)*(0x82f+6366-0x2107);}}}}static void sg_ModelStop(SimStruct*S){}
#endif 
#include "sg_sfcn_glue.h" 

