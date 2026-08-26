// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL    (0x2148+1333-0x267b)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO113_20_da_s
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sg_io113_20.h"
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
#define ze13f49a01f           ssGetSFcnParam(S, (0x5f6+2975-0x1195))
#define z3832b85a32           ssGetSFcnParam(S, (0x104f+1652-0x16c2))
#define z702a26a5e9                ssGetSFcnParam(S, (0x1538+1653-0x1bab))
#define z79b944ae89           ssGetSFcnParam(S, (0x8ac+2254-0x1177))
#define z05c7872e14          ssGetSFcnParam(S, (0x260+1965-0xa09))
#define z8d3b82b9ab              ssGetSFcnParam(S, (0x90a+2242-0x11c7))
#define z0605a52701              ssGetSFcnParam(S, (0x71d+6297-0x1fb0))
#define z5317f28eb6           ssGetSFcnParam(S, (0x1d2+8603-0x2366))
#define za6b3fb79a3             ssGetSFcnParam(S, (0x1fac+853-0x22f9))
#define zdf24515981                           ((0x6f9+5353-0x1bd9))
#define z2e6483d505              ((0x18a+9292-0x25d6))
#define zc5ce4cb81a              ((0x1ae6+346-0x1c40))
#define z2b17e2ee3b              ((0x15b2+1403-0x1b2d))
static char_T msg[(0x15c1+3190-0x2137)];static void mdlInitializeSizes(SimStruct*S){uint32_T i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x352+3053-0xf3f));ssSetNumDiscStates(S,(0x1b5f+366-0x1ccd));if(!ssSetNumOutputPorts(S,(0x50a+2540-0xef6)))return;if(!ssSetNumInputPorts(S,(int)mxGetN(z79b944ae89)))return;for(i=(0x916+6361-0x21ef);i<(int)mxGetN(z79b944ae89);i++){ssSetInputPortWidth(S,i,(0x8eb+2511-0x12b9));ssSetInputPortDirectFeedThrough(S,i,(0xf87+2628-0x19ca));ssSetInputPortRequiredContiguous(S,i,(0xf29+4378-0x2042));}ssSetNumSampleTimes(S,(0xcf1+2520-0x16c8));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x7ef+5291-0x1c9a));ssSetNumNonsampledZCs(S,(0x1020+2624-0x1a60));for(i=(0xe0+7512-0x1e38);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0xca+3216-0xd5a));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x1cd1+2144-0x2531)]==-1.0){ssSetSampleTime(S,(0x1093+3628-0x1ebf),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x2b1+1703-0x958),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x16c7+3164-0x2323),mxGetPr(z3832b85a32)[(0xcb0+2263-0x1587)]);ssSetOffsetTime(S,(0x23d4+447-0x2593),0.0);}}
#ifndef MATLAB_MEX_FILE
static void z95e7ebbeb7(SimStruct*S,zd63abbc96e*zae10e3f17f,int z4f19fbae54){uint16_T zf91d71c6d9=(uint16_T)mxGetN(z79b944ae89);uint16_T i;uint32_T z7711a772ed;for(i=(0x25bf+238-0x26ad);i<zf91d71c6d9;i++){if(!z4f19fbae54&&!(int)mxGetPr(za6b3fb79a3)[i])continue;z7711a772ed=(uint32_T)(((real_T)mxGetPr(z5317f28eb6)[i]+zae10e3f17f->offset)*zae10e3f17f->z0754dd67cc);if(z7711a772ed>z7935114df5)z7711a772ed=z7935114df5;zae10e3f17f->z3fad3d9764[z6071a79265]=z7711a772ed;
#ifdef SG_DEBUG_PRINT
uint16_T channel=(uint16_T)mxGetPr(z79b944ae89)[i]-(0x13ab+1703-0x1a51);SG_PRINTF(DEBUG,"\x25\x73\x3a\x20\x63\x68\x25\x75\x20\x25\x73\x20\x74\x6f\x20\x25\x66\x56\x20\x28\x25\x75\x29" "\n",DEVNAME,channel,z4f19fbae54?"\x69\x6e\x69\x74\x69\x61\x6c\x69\x73\x65\x64":"\x72\x65\x73\x65\x74",(real_T)mxGetPr(z5317f28eb6)[i],z7711a772ed);
#endif
}zae10e3f17f->z3fad3d9764[z307adcf8f5]|=((0xe13+5224-0x227a)<<(0x184+7944-0x2085))|((0x79a+5635-0x1d9c)<<(0xcf7+5124-0x20f6));}static void sg_ModelLoad(SimStruct*S){uint32_T za0d38ae598=(uint32_T)mxGetPr(ze13f49a01f)[(0x853+2559-0x1252)];zd63abbc96e*zae10e3f17f=(zd63abbc96e*)sg_module_get_custom_data(z12ba1d7c25,za0d38ae598);if(!zae10e3f17f){sprintf(msg,"\x25\x73\x20\x28\x49\x44\x20\x25\x75\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x69\x6e\x20\x44\x41\x20\x4d\x6f\x64\x65\x6c\x4c\x6f\x61\x64" "\n",DEVNAME,za0d38ae598);ssSetErrorStatus(S,msg);return;}z95e7ebbeb7(S,zae10e3f17f,(0x337+7463-0x205d));zae10e3f17f->z3fad3d9764[zf6f7d641c6]|=(1u<<(0xbd0+2761-0x1692));}static void sg_ModelStart(SimStruct*S){}static void sg_ModelStep(SimStruct*S){uint16_T zf91d71c6d9=(uint16_T)mxGetN(z79b944ae89);uint16_T i;real_T*zc7fdaf6331;int32_T out;uint32_T za0d38ae598=(uint32_T)mxGetPr(ze13f49a01f)[(0x14fd+4182-0x2553)];zd63abbc96e*zae10e3f17f=(zd63abbc96e*)sg_module_get_custom_data(z12ba1d7c25,za0d38ae598);if(!zae10e3f17f){sprintf(msg,"\x25\x73\x20\x28\x49\x44\x20\x25\x75\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x69\x6e\x20\x44\x41\x20\x4d\x6f\x64\x65\x6c\x53\x74\x65\x70" "\n",DEVNAME,za0d38ae598);ssSetErrorStatus(S,msg);return;}for(i=(0x18c8+3339-0x25d3);i<zf91d71c6d9;i++){zc7fdaf6331=(real_T*)ssGetInputPortRealSignal(S,i);out=(int32_T)((zc7fdaf6331[(0x188f+230-0x1975)]+zae10e3f17f->offset)*zae10e3f17f->z0754dd67cc);if(out>(int32_T)z7935114df5)out=(int32_T)z7935114df5;else if(out<(0x649+4290-0x170b))out=(0x1a77+298-0x1ba1);zae10e3f17f->z3fad3d9764[z6071a79265]=(uint32_T)out;}zae10e3f17f->z3fad3d9764[z307adcf8f5]|=((0x9a8+4240-0x1a37)<<(0x507+2504-0xec8))|((0x174+262-0x279)<<(0xa32+7115-0x25f8));}static void sg_ModelStop(SimStruct*S){uint32_T za0d38ae598=(uint32_T)mxGetPr(ze13f49a01f)[(0xaea+3826-0x19dc)];zd63abbc96e*zae10e3f17f=(zd63abbc96e*)sg_module_get_custom_data(z12ba1d7c25,za0d38ae598);if(!zae10e3f17f){sprintf(msg,"\x25\x73\x20\x28\x49\x44\x20\x25\x75\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x69\x6e\x20\x44\x41\x20\x4d\x6f\x64\x65\x6c\x53\x74\x6f\x70" "\n",DEVNAME,za0d38ae598);ssSetErrorStatus(S,msg);return;}uint16_T zf91d71c6d9=(uint16_T)mxGetN(z79b944ae89);uint16_T i;int32_T out;real_T*zc7fdaf6331;zae10e3f17f->z3fad3d9764[zf6f7d641c6]|=(1u<<(0x130d+1039-0x1707));for(i=(0x4f3+5667-0x1b16);i<zf91d71c6d9;i++){if((int)mxGetPr(za6b3fb79a3)[i]){out=(int32_T)(((real_T)mxGetPr(z5317f28eb6)[i]+zae10e3f17f->offset)*zae10e3f17f->z0754dd67cc);
#ifdef SG_DEBUG_PRINT
SG_PRINTF(DEBUG,"\x25\x73\x3a\x20\x63\x68\x25\x75\x20\x72\x65\x73\x65\x74\x20\x74\x6f\x20\x25\x66\x56" "\n",DEVNAME,(uint16_T)mxGetPr(z79b944ae89)[i]-(0x1267+507-0x1461),(real_T)mxGetPr(z5317f28eb6)[i]);
#endif
}else{zc7fdaf6331=(real_T*)ssGetInputPortRealSignal(S,i);out=(int32_T)((zc7fdaf6331[(0x162+2532-0xb46)]+zae10e3f17f->offset)*zae10e3f17f->z0754dd67cc);}if(out>(int32_T)z7935114df5)out=(int32_T)z7935114df5;if(out<(0x1b0+5105-0x15a1))out=(0x22a1+1004-0x268d);zae10e3f17f->z3fad3d9764[z6071a79265]=(uint32_T)out;}zae10e3f17f->z3fad3d9764[z307adcf8f5]|=(0x1u<<(0x13c0+3079-0x1fc0))|(0x1u<<(0xc93+3610-0x1aa8));}
#endif 
#include "sg_sfcn_glue.h"   

