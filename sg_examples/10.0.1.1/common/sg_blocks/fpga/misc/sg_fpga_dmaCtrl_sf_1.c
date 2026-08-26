// Copyright 2006-2026 Speedgoat GmbH

#define   S_FUNCTION_LEVEL  (0xf2f+5889-0x262e)
#undef    S_FUNCTION_NAME
#define   S_FUNCTION_NAME   sg_fpga_dmaCtrl_sf_1
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "simstruc.h"
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif
#ifndef MATLAB_MEX_FILE
#include "sg_common.h"
#include "sg_fpga_io3xx_scatter_gather_dma.h"
#include "sg_fpga_io3xx_util.h"
#include "sg_printf.h"
#endif
#include "sg_callback.h"
enum zd1afaba290{ID,zdf24515981};
#define z58f464b4bb              ssGetSFcnParam(S, ID)
enum zbb1f615c1d{z3250bb2679};enum z93bcf30780{z8a85396f5b};enum zb06a9f15ae{z5b2d2e8b62,z9cbfedf63b};
#define z5bbcf8be2c        (0xc21+5731-0x2283)
static char_T msg[(0x13f+632-0x2b7)];typedef struct{uint8_t*zcdc585b3f6;bool*zb07fe36158;double*Duration;}z56b96a2bea;static z56b96a2bea*z14830cfc7c(SimStruct*S);static void mdlInitializeSizes(SimStruct*S){uint32_t i,z60d0f0b300,z49c1c6abb8,width;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73" "\n" "\x20\x70\x61\x73\x73\x65\x64\x3a\x20\x25\x64" "\n" "\x20\x65\x78\x70\x65\x63\x74\x65\x64\x3a\x20\x25\x64" "\n",ssGetSFcnParamsCount(S),ssGetNumSFcnParams(S));ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x1c80+2365-0x25bd));ssSetNumDiscStates(S,(0x4cf+6525-0x1e4c));z60d0f0b300=(0x22f+877-0x59c);if(!ssSetNumInputPorts(S,z60d0f0b300)){return;}z49c1c6abb8=(0xfa4+3373-0x1cd1);{z49c1c6abb8+=(0xca3+4471-0x1e17);}if(!ssSetNumOutputPorts(S,z49c1c6abb8)){return;}z49c1c6abb8=(0x263+8759-0x249a);ssSetOutputPortDataType(S,z49c1c6abb8++,SS_UINT8);ssSetOutputPortDataType(S,z49c1c6abb8++,SS_BOOLEAN);ssSetOutputPortDataType(S,z49c1c6abb8++,SS_DOUBLE);width=(0x7fd+5925-0x1f21);for(i=(0x8e2+7476-0x2616);i<z49c1c6abb8;i++){ssSetOutputPortWidth(S,i,width);}ssSetNumSampleTimes(S,(0xaa+7809-0x1f2a));ssSetNumRWork(S,z8a85396f5b);ssSetNumIWork(S,z3250bb2679);ssSetNumPWork(S,z9cbfedf63b);ssSetNumModes(S,(0x3f8+971-0x7c3));ssSetNumNonsampledZCs(S,(0x6a3+6758-0x2109));for(i=(0xa23+5156-0x1e47);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x11b4+5448-0x26fc));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){ssSetSampleTime(S,(0x308+7829-0x219d),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x16d5+1129-0x1b3e),0.0);}static void sg_ModelLoad(SimStruct*S){
#ifndef MATLAB_MEX_FILE
#endif
}static void sg_ModelStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
ssSetPWorkValue(S,z5b2d2e8b62,z14830cfc7c(S));
#endif
}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
z56b96a2bea*zd3fe858a76=(z56b96a2bea*)ssGetPWorkValue(S,z5b2d2e8b62);ScatterGatherDmaState*z50b84cc2b5;modelTimings_t*z993c0995f5;sg_fpga_io3xx_getSharedSgDmaState((int)mxGetScalar(z58f464b4bb),&z50b84cc2b5);sg_fpga_io3xx_getSharedTimingInfo((int)mxGetScalar(z58f464b4bb),&z993c0995f5);zd3fe858a76->zcdc585b3f6[(0x10b0+4162-0x20f2)]=(uint8_t)*z50b84cc2b5->intPollCounterPtr&(0xba0+5950-0x225f);zd3fe858a76->zb07fe36158[(0xfe5+231-0x10cc)]=(bool)(*z50b84cc2b5->intPollCounterPtr&(0x1c6f+2533-0x25d4));zd3fe858a76->Duration[(0x2dd+6081-0x1a9e)]=(double)(*z50b84cc2b5->intPollCounterPtr>>(0x121d+4607-0x2414))/(z993c0995f5->fpgaFrequency);
#endif
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE
z56b96a2bea*zd3fe858a76=(z56b96a2bea*)ssGetPWorkValue(S,z5b2d2e8b62);if(zd3fe858a76){free(zd3fe858a76);}
#endif
}static z56b96a2bea*z14830cfc7c(SimStruct*S){int ze0f8e1c159=(0x1a4+5344-0x1684);z56b96a2bea*zd3fe858a76=(z56b96a2bea*)malloc(sizeof(z56b96a2bea));memset(zd3fe858a76,(0x1756+295-0x187d),sizeof(z56b96a2bea));zd3fe858a76->zcdc585b3f6=(uint8_t*)ssGetOutputPortSignal(S,ze0f8e1c159++);zd3fe858a76->zb07fe36158=(bool*)ssGetOutputPortSignal(S,ze0f8e1c159++);zd3fe858a76->Duration=(double*)ssGetOutputPortSignal(S,ze0f8e1c159++);return zd3fe858a76;}
#include "sg_sfcn_glue.h"   

