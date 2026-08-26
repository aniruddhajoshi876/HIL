// Copyright 2006-2026 Speedgoat GmbH

#define         S_FUNCTION_LEVEL        (0x924+5006-0x1cb0)
#undef          S_FUNCTION_NAME
#define         S_FUNCTION_NAME         sg_IO901_IO902_write_s
#include        <stddef.h>
#include        <stdlib.h>
#include        <stdint.h>
#include        "simstruc.h"
#include        "sg_IO901_IO902.h"
#ifdef          MATLAB_MEX_FILE
#include        "mex.h"
#endif
#include    "sg_callback.h"
#define zdf24515981        ((0xa64+691-0xd12))
#define z8c2942e11d            ssGetSFcnParam(S, (0x2ec+5805-0x1999))
#define z0406ba5a19            ssGetSFcnParam(S, (0x29b+2953-0xe23))
#define zabe1e0cd2c        ssGetSFcnParam(S, (0x91b+7488-0x2659))
#define z702a26a5e9              ssGetSFcnParam(S, (0x5f+3451-0xdd7))
#define zfaa050b79d             ssGetSFcnParam(S, (0xe67+3357-0x1b80))
#define z2e6483d505            ((0x24d+7367-0x1f14))
#define zc5ce4cb81a            ((0x1376+1054-0x1794))
#define z2b17e2ee3b            ((0x1ca+6383-0x1ab9))
#define z95835284b8             ((0x1971+575-0x829))
#define zdd9aa31c07             (21264)
#define z55367ad797           "\x53\x43\x52\x41\x4d\x4e\x65\x74\x20\x47\x54"
static char msg[(0xd70+5034-0x201a)];static void mdlInitializeSizes(SimStruct*S){int i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n""\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x1760+2737-0x2211));ssSetNumDiscStates(S,(0x285+479-0x464));ssSetNumOutputPorts(S,(0x1466+1566-0x1a84));ssSetNumInputPorts(S,(0x39c+1975-0xb52));ssSetInputPortWidth(S,(0xa32+4219-0x1aad),(int_T)mxGetPr(z0406ba5a19)[(0x19c7+2130-0x2219)]);ssSetInputPortDataType(S,(0x559+7110-0x211f),SS_UINT32);ssSetInputPortDirectFeedThrough(S,(0xee7+779-0x11f2),(0xb5+8723-0x22c7));ssSetInputPortRequiredContiguous(S,(0x53b+5891-0x1c3e),(0x10c8+1244-0x15a3));ssSetNumSampleTimes(S,(0x102+8270-0x214f));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x1252+1392-0x17c2));ssSetNumNonsampledZCs(S,(0xc31+6125-0x241e));for(i=(0xe51+5905-0x2562);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x4c+3191-0xcc3));}ssSetOptions(S,SS_OPTION_RUNTIME_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(zabe1e0cd2c)[(0x5a4+7847-0x244b)]==-1.0){ssSetSampleTime(S,(0xce8+383-0xe67),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0xefd+1985-0x16be),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x7b+3159-0xcd2),mxGetPr(zabe1e0cd2c)[(0x13b0+2185-0x1c39)]);ssSetOffsetTime(S,(0x1680+1579-0x1cab),0.0);}}static void sg_ModelLoad(SimStruct*S){}static void sg_ModelStart(SimStruct*S){}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_t i;uint32_t*u=(uint32_t*)ssGetInputPortSignal(S,(0xd20+4109-0x1d2d));uint32_t z8d2075ecef=(uint32_t)mxGetPr(z0406ba5a19)[(0x1591+1548-0x1b9d)];uint32_t offset=(uint32_t)mxGetPr(z8c2942e11d)[(0x639+1596-0xc75)];volatile uint32_t*z8b2eb1d4e4;z78d32bde66*z39b46fd01d;z39b46fd01d=(z78d32bde66*)sg_module_get_custom_data(z6cd618c289,(uint32_t)mxGetPr(zfaa050b79d)[(0xe9c+5748-0x2510)]);if(z39b46fd01d==NULL){ssSetErrorStatus(S,"\x49\x4f\x39\x30\x31\x20\x57\x72\x69\x74\x65\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x69\x6e\x20\x4d\x6f\x64\x65\x6c\x53\x74\x65\x70" "\n");return;}z8b2eb1d4e4=z39b46fd01d->z0ad0eb424c;for(i=(0x1923+1639-0x1f8a);i<z8d2075ecef;i++){z8b2eb1d4e4[(offset/(0x1b35+2548-0x2525))+i]=u[i];}
#endif
}static void sg_ModelStop(SimStruct*S){}
#include "sg_sfcn_glue.h"   

