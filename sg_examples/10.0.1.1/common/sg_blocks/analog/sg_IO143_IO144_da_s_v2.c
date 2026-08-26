// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL    (0x11f1+4041-0x21b8)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO143_IO144_da_s_v2
#include "sg_IO143_IO144_v2.h"
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
#define z533b11d03f           ssGetSFcnParam(S,  (0x77a+1383-0xce1)) 
#define za00184cdc1            ssGetSFcnParam(S,  (0x463+2069-0xc77)) 
#define z702a26a5e9                ssGetSFcnParam(S,  (0x153b+1430-0x1acf)) 
#define zabe1e0cd2c          ssGetSFcnParam(S,  (0x683+1048-0xa98)) 
#define z9de81b9c1a             ssGetSFcnParam(S,  (0x760+2253-0x1029)) 
#define z143c69c545         ssGetSFcnParam(S,  (0xbbc+3442-0x1929)) 
#define z033d84d2f9          ssGetSFcnParam(S,  (0x516+6967-0x2047)) 
#define z84dd9a9a5c            ssGetSFcnParam(S,  (0xcb9+2548-0x16a6)) 
#define z8c935c4ad2       ssGetSFcnParam(S,  (0xb09+6138-0x22fb)) 
#define zc6f930323f            ssGetSFcnParam(S,  (0x1e39+421-0x1fd5)) 
#define z38b4297158 ssGetSFcnParam(S, (0x1399+3710-0x220d)) 
#define zdf24515981                        (   (0x1f13+2054-0x270e))
#define z2e6483d505              ((0x4c+3393-0xd8d))
#define zc5ce4cb81a              ((0x108a+1041-0x149b))
#define z2b17e2ee3b              ((0x1c2c+2733-0x26d9))
static char msg[(0x1cf4+1859-0x2337)];static int zdc01648b54;static void mdlInitializeSizes(SimStruct*S){uint_T i;zdc01648b54=sprintf(msg,"\x49\x6e\x20\x49\x4f\x25\x64\x2c\x20\x41\x6e\x61\x6c\x6f\x67\x20\x6f\x75\x74\x70\x75\x74\x20\x62\x6c\x6f\x63\x6b\x2c\x20\x49\x44\x20\x25\x64\x3a\x20",(int)mxGetPr(z533b11d03f)[(0xa0c+5138-0x1e1e)],(int)mxGetPr(za00184cdc1)[(0x153d+4134-0x2563)]);ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf((msg+zdc01648b54),"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n""\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64\x2e" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x204f+15-0x205e));ssSetNumDiscStates(S,(0xc0+3826-0xfb2));if(!ssSetNumOutputPorts(S,(0x1040+2662-0x1aa6)))return;if(!ssSetNumInputPorts(S,(int)mxGetN(z143c69c545)))return;for(i=(0x3ca+4071-0x13b1);i<(uint_T)mxGetN(z143c69c545);i++){if((uint32_T)mxGetPr(z9de81b9c1a)[(0x17bd+913-0x1b4e)]){ssSetInputPortWidth(S,i,(int)mxGetPr(z8c935c4ad2)[(0xbd+538-0x2d7)]);}else{ssSetInputPortWidth(S,i,(0x6d4+2135-0xf2a));}ssSetInputPortDirectFeedThrough(S,i,(0x38d+2967-0xf23));ssSetInputPortRequiredContiguous(S,i,(0x5ca+7873-0x248a));}ssSetNumSampleTimes(S,(0x1151+336-0x12a0));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x13b7+2058-0x1bc1));ssSetNumNonsampledZCs(S,(0x1110+2344-0x1a38));for(i=(0x5e2+6108-0x1dbe);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,SS_PRM_NOT_TUNABLE);}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(zabe1e0cd2c)[(0x1456+1945-0x1bef)]==-1.0){ssSetSampleTime(S,(0xd1a+3579-0x1b15),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x643+174-0x6f1),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x8a4+5682-0x1ed6),mxGetPr(zabe1e0cd2c)[(0x6ec+88-0x744)]);ssSetOffsetTime(S,(0x50c+6165-0x1d21),0.0);}}
#ifndef MATLAB_MEX_FILE
static void sg_ModelLoad(SimStruct*S){}static void sg_ModelStart(SimStruct*S){}static void sg_ModelStep(SimStruct*S){uint32_T z85c496e7c0;uint32_T z028c91d133,z33e869f256;int32_T out;uint_T i;int boardType=(int)mxGetPr(z533b11d03f)[(0x189+5265-0x161a)];int za0d38ae598=(int)mxGetPr(za00184cdc1)[(0x1427+3232-0x20c7)];uint32_T zf91d71c6d9=(uint32_T)mxGetN(z143c69c545);zc8ee45929d*zae10e3f17f=(zc8ee45929d*)sg_module_get_custom_data(boardType,za0d38ae598);if(!zae10e3f17f){sprintf(msg,"\x49\x4f\x25\x64\x20\x28\x49\x44\x20\x25\x64\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x69\x6e\x20\x44\x41\x20\x4d\x6f\x64\x65\x6c\x53\x74\x65\x70" "\n",boardType,za0d38ae598);ssSetErrorStatus(S,msg);return;}for(i=(0xc9f+6352-0x256f);i<zf91d71c6d9;i++){z85c496e7c0=zae10e3f17f->z40ce00b3e8.zb688cad4fb[i]-(0x18d+8758-0x23c2);if(!(uint32_T)mxGetPr(z9de81b9c1a)[(0x180b+965-0x1bd0)]){z028c91d133=z85c496e7c0/zb61d943c19;z33e869f256=(0x1127+1487-0x16f3)-(z85c496e7c0%zb61d943c19);SG_PRINTF(TRACE,"\x44\x41\x20\x64\x65\x76\x69\x63\x65\x3a\x20\x25\x64\x2c\x20\x44\x41\x20\x63\x68\x61\x6e\x6e\x65\x6c\x3a\x20\x25\x64" "\n",z028c91d133,z33e869f256);out=(int32_T)((*ssGetInputPortRealSignal(S,zae10e3f17f->z40ce00b3e8.z096c009dce[i])+zae10e3f17f->z40ce00b3e8.offset[zae10e3f17f->z40ce00b3e8.z096c009dce[i]])*zae10e3f17f->z40ce00b3e8.z0754dd67cc[zae10e3f17f->z40ce00b3e8.z096c009dce[i]]);if(zae10e3f17f->z40ce00b3e8.z6c5ef6aa7d[zae10e3f17f->z40ce00b3e8.z096c009dce[i]]){if(out>32767){out=32767;}else{if(out<-32768){out=32768;}}}else{if(out>65535){out=65535;}else{if(out<(0xdef+1191-0x1296)){out=(0x5d0+3662-0x141e);}}}SG_PRINTF(TRACE,"\x47\x61\x69\x6e\x3a\x20\x25\x2e\x33\x65\x2c\x20\x4f\x66\x66\x73\x65\x74\x3a\x20\x25\x2e\x33\x65" "\n",zae10e3f17f->z40ce00b3e8.z0754dd67cc[i],zae10e3f17f->z40ce00b3e8.offset[i]);SG_PRINTF(TRACE,"\x44\x41\x20\x64\x61\x74\x61\x3a\x20\x25\x58\x2c\x20\x43\x48\x20\x25\x64" "\n",(uint16_T)out,z85c496e7c0);zae10e3f17f->z3fad3d9764->zd7db60cc2e[z028c91d133].z81e9443289[z33e869f256]=(int16_T)out;}}if(!(uint32_T)mxGetPr(z9de81b9c1a)[(0x1dc+3292-0xeb8)]){if((uint32_T)mxGetPr(z38b4297158)[(0x420+7741-0x225d)]){(void)zae10e3f17f->z3fad3d9764->z9dbf96ff0e;SG_PRINTF(TRACE,"\x53\x69\x6d\x75\x6c\x74\x61\x6e\x65\x6f\x75\x73\x20\x6f\x75\x74\x70\x75\x74\x20\x65\x6e\x61\x62\x6c\x65\x64" "\n");while(zae10e3f17f->z3fad3d9764->z9dbf96ff0e&z4ed075a551);zae10e3f17f->z3fad3d9764->zc1730e6634=za1461cb286;}else{SG_PRINTF(TRACE,"\x53\x69\x6d\x75\x6c\x74\x61\x6e\x65\x6f\x75\x73\x20\x6f\x75\x74\x70\x75\x74\x20\x64\x69\x73\x61\x62\x6c\x65\x64" "\n");}}}static void sg_ModelStop(SimStruct*S){}
#endif 
#include "sg_sfcn_glue.h"   

