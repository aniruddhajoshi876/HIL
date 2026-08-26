// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL    (0x1b5d+1496-0x2133)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO113_do_s
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
#define ze13f49a01f           ssGetSFcnParam(S, (0x83+8577-0x2204))
#define za9d8fb6bcf             ssGetSFcnParam(S, (0x2236+64-0x2275))
#define z3832b85a32           ssGetSFcnParam(S, (0xf92+5707-0x25db))
#define z702a26a5e9                ssGetSFcnParam(S, (0xc5b+5067-0x2023))
#define z2d8f240c11           ssGetSFcnParam(S, (0x12eb+72-0x132f))
#define z1f9bebb47b             ssGetSFcnParam(S, (0x12e2+3313-0x1fce))
#define zdf24515981                           ((0x1d66+234-0x1e4a))
#define z2e6483d505              ((0x33b+1495-0x912))
#define zc5ce4cb81a              ((0x1384+3296-0x2064))
#define z2b17e2ee3b              ((0xa4b+5244-0x1ec7))
static char_T msg[(0x825+5330-0x1bf7)];static void mdlInitializeSizes(SimStruct*S){uint32_T i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x147f+3260-0x213b));ssSetNumDiscStates(S,(0x736+7170-0x2338));if(!ssSetNumOutputPorts(S,(0x8fb+2289-0x11ec)))return;if(!ssSetNumInputPorts(S,(int)mxGetN(za9d8fb6bcf)))return;for(i=(0x139c+339-0x14ef);i<(int)mxGetN(za9d8fb6bcf);i++){ssSetInputPortWidth(S,i,(0x1a06+1893-0x216a));ssSetInputPortDirectFeedThrough(S,i,(0x274+5318-0x1739));ssSetInputPortRequiredContiguous(S,i,(0x112+1470-0x6cf));}ssSetNumSampleTimes(S,(0x1584+274-0x1695));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x1da8+859-0x2103));ssSetNumNonsampledZCs(S,(0x2b7+1579-0x8e2));for(i=(0xcf0+2312-0x15f8);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x1d1+3448-0xf49));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x1147+146-0x11d9)]==-1.0){ssSetSampleTime(S,(0x717+5095-0x1afe),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0xed9+3317-0x1bce),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0xdf3+5827-0x24b6),mxGetPr(z3832b85a32)[(0x20d4+67-0x2117)]);ssSetOffsetTime(S,(0x259+9316-0x26bd),0.0);}}
#ifndef MATLAB_MEX_FILE
static void z95e7ebbeb7(SimStruct*S,za7f5fcb87c*zae10e3f17f,int z4f19fbae54){uint16_T zf91d71c6d9=(uint16_T)mxGetN(za9d8fb6bcf);uint16_T i;uint32_T channel;uint32_T z718c4c15f4;z718c4c15f4=z4f19fbae54?(zae10e3f17f->z3fad3d9764[z9621b996a9]&32896):zae10e3f17f->z3fad3d9764[z9621b996a9];for(i=(0x678+281-0x791);i<zf91d71c6d9;i++){if(!z4f19fbae54&&!(int)mxGetPr(z1f9bebb47b)[i])continue;channel=(uint32_T)mxGetPr(za9d8fb6bcf)[i]-(0x1e6+9366-0x267b);if(mxGetPr(z2d8f240c11)[i]>=THRESHOLD){if((channel<=(0x9e2+6506-0x2349))&&(zae10e3f17f->z3fad3d9764[z9621b996a9]&(1u<<(0x1997+2899-0x24e3))))z718c4c15f4|=(1u<<channel);else if(zae10e3f17f->z3fad3d9764[z9621b996a9]&(1u<<(0xdd5+604-0x1022)))z718c4c15f4|=(1u<<(channel+(0x13f8+2468-0x1d98)));}else{if(channel<=(0x399+8459-0x24a1))z718c4c15f4&=~(1u<<channel);else z718c4c15f4&=~(1u<<(channel+(0x152b+2767-0x1ff6)));}}zae10e3f17f->z3fad3d9764[z9621b996a9]=z718c4c15f4;SG_PRINTF(DEBUG,"\x52\x45\x47\x5f\x44\x50\x52\x20\x28\x64\x6f\x20\x25\x73\x29\x3a\x20\x30\x78\x25\x78" "\n",z4f19fbae54?"\x69\x6e\x69\x74":"\x72\x65\x73\x65\x74",zae10e3f17f->z3fad3d9764[z9621b996a9]);}static void sg_ModelLoad(SimStruct*S){uint32_T za0d38ae598=(uint32_T)mxGetPr(ze13f49a01f)[(0x1513+3168-0x2173)];za7f5fcb87c*zae10e3f17f=(za7f5fcb87c*)sg_module_get_custom_data(z12ba1d7c25,za0d38ae598);if(!zae10e3f17f){sprintf(msg,"\x25\x73\x20\x28\x49\x44\x20\x25\x75\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x69\x6e\x20\x44\x4f\x20\x4d\x6f\x64\x65\x6c\x4c\x6f\x61\x64" "\n",DEVNAME,za0d38ae598);ssSetErrorStatus(S,msg);return;}z95e7ebbeb7(S,zae10e3f17f,(0xdc0+4644-0x1fe3));}static void sg_ModelStart(SimStruct*S){}static void sg_ModelStep(SimStruct*S){uint16_T zf91d71c6d9=(uint16_T)mxGetN(za9d8fb6bcf);uint32_T za0d38ae598=(uint32_T)mxGetPr(ze13f49a01f)[(0x20e7+1430-0x267d)];uint16_T i;uint32_T z718c4c15f4,channel;real_T*zc7fdaf6331;za7f5fcb87c*zae10e3f17f=(za7f5fcb87c*)sg_module_get_custom_data(z12ba1d7c25,za0d38ae598);if(!zae10e3f17f){sprintf(msg,"\x25\x73\x20\x28\x49\x44\x20\x25\x75\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x69\x6e\x20\x44\x4f\x20\x4d\x6f\x64\x65\x6c\x53\x74\x65\x70" "\n",DEVNAME,za0d38ae598);ssSetErrorStatus(S,msg);return;}z718c4c15f4=zae10e3f17f->z3fad3d9764[z9621b996a9]&32896;for(i=(0x1ecc+907-0x2257);i<zf91d71c6d9;i++){channel=(uint32_T)mxGetPr(za9d8fb6bcf)[i]-(0x1a51+2598-0x2476);zc7fdaf6331=(real_T*)ssGetInputPortRealSignal(S,i);if(zc7fdaf6331[(0x1c79+1008-0x2069)]>=THRESHOLD){if((channel<=(0x7ba+7002-0x2311))&&(zae10e3f17f->z3fad3d9764[z9621b996a9]&(1u<<(0x6cc+4373-0x17da)))){z718c4c15f4|=(1u<<channel);}else if(zae10e3f17f->z3fad3d9764[z9621b996a9]&(1u<<(0x62+9539-0x2596))){z718c4c15f4|=(1u<<(channel+(0xb36+3305-0x181b)));}}}zae10e3f17f->z3fad3d9764[z9621b996a9]=z718c4c15f4;SG_PRINTF(TRACE,"\x52\x45\x47\x5f\x44\x50\x52\x20\x28\x64\x6f\x29\x3a\x20\x30\x78\x25\x78" "\n",zae10e3f17f->z3fad3d9764[z9621b996a9]);}static void sg_ModelStop(SimStruct*S){uint32_T za0d38ae598=(uint32_T)mxGetPr(ze13f49a01f)[(0x1bec+660-0x1e80)];za7f5fcb87c*zae10e3f17f=(za7f5fcb87c*)sg_module_get_custom_data(z12ba1d7c25,za0d38ae598);if(!zae10e3f17f){sprintf(msg,"\x25\x73\x20\x28\x49\x44\x20\x25\x75\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x69\x6e\x20\x44\x4f\x20\x4d\x6f\x64\x65\x6c\x53\x74\x6f\x70" "\n",DEVNAME,za0d38ae598);ssSetErrorStatus(S,msg);return;}z95e7ebbeb7(S,zae10e3f17f,(0xd58+4750-0x1fe6));}
#endif 
#include "sg_sfcn_glue.h"   

