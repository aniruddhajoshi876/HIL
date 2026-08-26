// Copyright 2006-2026 Speedgoat GmbH

#define         S_FUNCTION_LEVEL        (0x574+3327-0x1271)
#undef          S_FUNCTION_NAME
#define         S_FUNCTION_NAME         sg_IO901_IO902_read_s
#include        <stddef.h>
#include        <stdlib.h>
#include        <stdint.h>
#include        "simstruc.h"
#include        "sg_IO901_IO902.h"
#ifdef          MATLAB_MEX_FILE
#include        "mex.h"
#endif
#include    "sg_callback.h"
#define zdf24515981        ((0x70c+140-0x793))
#define z8c2942e11d            ssGetSFcnParam(S, (0x7cb+2775-0x12a2))
#define z0406ba5a19            ssGetSFcnParam(S, (0x55+6621-0x1a31))
#define zabe1e0cd2c        ssGetSFcnParam(S, (0xfd9+2049-0x17d8))
#define z702a26a5e9              ssGetSFcnParam(S, (0xc52+634-0xec9))
#define zfaa050b79d             ssGetSFcnParam(S, (0x79c+7511-0x24ef))
#define z2e6483d505            ((0x21f6+349-0x2353))
#define zc5ce4cb81a            ((0x131b+2502-0x1ce1))
#define z2b17e2ee3b            ((0x180+7645-0x1f5d))
#define z95835284b8             ((0x1ce7+4064-0x1940))
#define zdd9aa31c07             (21264)
#define z55367ad797           "\x53\x43\x52\x41\x4d\x4e\x65\x74\x20\x47\x54"
static char msg[(0x96f+5286-0x1d15)];static void mdlInitializeSizes(SimStruct*S){int i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n""\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x1890+1930-0x201a));ssSetNumDiscStates(S,(0x1b9+8189-0x21b6));ssSetNumInputPorts(S,(0x10d+3806-0xfeb));ssSetNumOutputPorts(S,(0xe73+3935-0x1dd1));ssSetOutputPortWidth(S,(0x18e8+1671-0x1f6f),(int)mxGetPr(z0406ba5a19)[(0x1645+1303-0x1b5c)]);ssSetOutputPortDataType(S,(0x781+3230-0x141f),SS_UINT32);ssSetNumSampleTimes(S,(0x3b6+1606-0x9fb));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x219+5173-0x164e));ssSetNumNonsampledZCs(S,(0x5d6+1610-0xc20));for(i=(0x97a+7353-0x2633);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x331+8629-0x24e6));}ssSetOptions(S,SS_OPTION_RUNTIME_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(zabe1e0cd2c)[(0x1e7+507-0x3e2)]==-1.0){ssSetSampleTime(S,(0x135+2465-0xad6),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x99+569-0x2d2),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x14f5+3705-0x236e),mxGetPr(zabe1e0cd2c)[(0x11b2+140-0x123e)]);ssSetOffsetTime(S,(0xbcf+5805-0x227c),0.0);}}static void sg_ModelLoad(SimStruct*S){}static void sg_ModelStart(SimStruct*S){}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_t i;uint32_t*y=(uint32_t*)ssGetOutputPortSignal(S,(0x71a+1037-0xb27));uint32_t z8d2075ecef=(uint32_t)mxGetPr(z0406ba5a19)[(0x751+3186-0x13c3)];uint32_t offset=(uint32_t)mxGetPr(z8c2942e11d)[(0x125c+883-0x15cf)];volatile uint32_t*z8b2eb1d4e4;z78d32bde66*z39b46fd01d;z39b46fd01d=(z78d32bde66*)sg_module_get_custom_data(z6cd618c289,(uint32_t)mxGetPr(zfaa050b79d)[(0x21f6+1032-0x25fe)]);if(z39b46fd01d==NULL){ssSetErrorStatus(S,"\x49\x4f\x39\x30\x31\x20\x52\x65\x61\x64\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x69\x6e\x20\x4d\x6f\x64\x65\x6c\x53\x74\x65\x70" "\n");return;}z8b2eb1d4e4=z39b46fd01d->z0ad0eb424c;for(i=(0x1b4+8685-0x23a1);i<z8d2075ecef;i++){y[i]=z8b2eb1d4e4[(offset/(0x20e0+1281-0x25dd))+i];}
#endif
}static void sg_ModelStop(SimStruct*S){}
#include "sg_sfcn_glue.h"   

