// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL    (0x136b+896-0x16e9) 
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO104_DMA_di_s
#include <stdlib.h>
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#else
#include "sg_common.h"
#endif
#define SG_EARLY_INIT   
#include "sg_io104.h"
#include "sg_callback.h"
#define z102e21cf98          ssGetSFcnParam(S, (0x1beb+119-0x1c62))
#define z3832b85a32           ssGetSFcnParam(S, (0x1666+1482-0x1c2f))
#define z702a26a5e9                ssGetSFcnParam(S, (0xb4f+6913-0x264e))
#define za00184cdc1            ssGetSFcnParam(S, (0xe00+6166-0x2613)) 
#define zdf24515981                           ((0xbf8+3354-0x190e))
#define z2e6483d505              ((0xfda+1606-0x1620))
#define zc5ce4cb81a              ((0x38a+8399-0x2459))
#define z2b17e2ee3b              ((0x1bd+6709-0x1bf2))
static char msg[(0x1c4f+2286-0x243d)];static void mdlInitializeSizes(SimStruct*S){int i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x20c+8281-0x2265));ssSetNumDiscStates(S,(0x407+2171-0xc82));if(!ssSetNumInputPorts(S,(0x15a9+2650-0x2003))){return;}if(!ssSetNumOutputPorts(S,(int)mxGetN(z102e21cf98))){return;}for(i=(0x1041+5605-0x2626);i<(int)mxGetN(z102e21cf98);i++){ssSetOutputPortWidth(S,i,(0x671+3919-0x15bf));}ssSetNumSampleTimes(S,(0x1f56+1568-0x2575));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x342+5082-0x171c));ssSetNumNonsampledZCs(S,(0x519+8110-0x24c7));for(i=(0x140b+652-0x1697);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x12b3+4536-0x246b));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0xe58+751-0x1147)]==-1.0){ssSetSampleTime(S,(0x10a3+2332-0x19bf),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x519+1537-0xb1a),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x511+6780-0x1f8d),mxGetPr(z3832b85a32)[(0x57b+3254-0x1231)]);ssSetOffsetTime(S,(0x718+6997-0x226d),0.0);}}static void sg_ModelLoad(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_t moduleId;moduleId=(int)mxGetPr(za00184cdc1)[(0x24f5+51-0x2528)];z50df7b81b0*zae10e3f17f=(z50df7b81b0*)sg_module_get_custom_data(SG_MODULE_TYPE_IO104,moduleId);if(!zae10e3f17f){sprintf(msg,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x73\x74\x61\x74\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79" "\n",DEVNAME,moduleId);ssSetErrorStatus(S,msg);return;}else{SG_PRINTF_DEBUG("\x44\x49\x5f\x4c\x6f\x61\x64\x3a\x20\x4d\x6f\x64\x75\x6c\x65\x20\x61\x6c\x72\x65\x61\x64\x79\x20\x72\x65\x67\x69\x73\x74\x65\x72\x65\x64" "\n");}zae10e3f17f->z183fd27444=(z020494c81d*)(zae10e3f17f->z919abdb780);
#endif
}static void sg_ModelStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
#endif
}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_t zf91d71c6d9=(uint32_t)mxGetN(z102e21cf98);uint32_t z718c4c15f4,ch,ze1dce08a7a,i,z8a7e6753de,moduleId;double*zc0efaa16c3;moduleId=(int)mxGetPr(za00184cdc1)[(0x590+5745-0x1c01)];z50df7b81b0*zae10e3f17f=(z50df7b81b0*)sg_module_get_custom_data(SG_MODULE_TYPE_IO104,moduleId);if(!zae10e3f17f){sprintf(msg,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x73\x74\x61\x74\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79" "\n",DEVNAME,moduleId);ssSetErrorStatus(S,msg);return;}z718c4c15f4=zae10e3f17f->z183fd27444->dio;for(i=(0x994+3236-0x1638);i<zf91d71c6d9;i++){ch=(uint32_t)mxGetPr(z102e21cf98)[i]-(0x414+4434-0x1565);ze1dce08a7a=i;zc0efaa16c3=ssGetOutputPortSignal(S,ze1dce08a7a);z8a7e6753de=(0x7f3+4348-0x18ee)<<(ch+((ch>(0x116+6592-0x1acf))?zd4f65135a2-(0x9f0+3408-0x1738):(0x896+4919-0x1bcd)));*zc0efaa16c3=(z718c4c15f4&z8a7e6753de)?(0x13bb+4198-0x2420):(0x1de0+545-0x2001);}
#endif
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE
#endif
}
#include "sg_sfcn_glue.h"

