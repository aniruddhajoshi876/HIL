// Copyright 2006-2026 Speedgoat GmbH

#define         S_FUNCTION_LEVEL        (0x55b+8324-0x25dd)
#undef          S_FUNCTION_NAME
#define         S_FUNCTION_NAME         sg_IO901_IO902_send_interrupt_s
#include        <stddef.h>
#include        <stdlib.h>
#include        <stdint.h>
#include        "simstruc.h"
#include        "sg_IO901_IO902.h"
#ifdef          MATLAB_MEX_FILE
#include        "mex.h"
#endif
#include    "sg_callback.h"
#define zdf24515981        ((0x78d+4170-0x17d4))
#define zabe1e0cd2c        ssGetSFcnParam(S, (0x2e8+3521-0x10a9))
#define z702a26a5e9              ssGetSFcnParam(S, (0xc07+544-0xe26))
#define zfaa050b79d             ssGetSFcnParam(S, (0x15e3+3234-0x2283))
#define z2e6483d505            ((0x8a5+4030-0x1863))
#define zc5ce4cb81a            ((0x450+7907-0x2333))
#define z2b17e2ee3b            ((0x1751+392-0x18d9))
#define z95835284b8             (4999)
#define zdd9aa31c07             (21264)
#define z55367ad797           "\x53\x43\x52\x41\x4d\x4e\x65\x74\x20\x47\x54"
static char msg[(0xfa0+5068-0x226c)];static void mdlInitializeSizes(SimStruct*S){int i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n""\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x345+596-0x599));ssSetNumDiscStates(S,(0x745+6980-0x2289));ssSetNumOutputPorts(S,(0x1c97+201-0x1d60));for(i=(0x256+4137-0x127f);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x1a7+8534-0x22fd));}if(ssSetNumInputPorts(S,(0x5a6+1314-0xac5))==(0x5a1+4869-0x18a6)){sprintf(msg,"\x73\x73\x53\x65\x74\x4e\x75\x6d\x49\x6e\x70\x75\x74\x50\x6f\x72\x74\x73\x20\x72\x65\x74\x75\x72\x6e\x65\x64\x20\x30\x2c\x20\x69\x6e\x64\x69\x63\x61\x74\x69\x6e\x67\x20\x61\x20\x70\x72\x6f\x62\x6c\x65\x6d\x20\x63\x72\x65\x61\x74\x69\x6e\x67\x20\x69\x6e\x70\x75\x74\x20\x70\x6f\x72\x74\x73\x2e" "\n");ssSetErrorStatus(S,msg);return;}ssSetInputPortWidth(S,(0x71d+3189-0x1392),(0x4c2+7178-0x20cb));ssSetInputPortDataType(S,(0x663+4403-0x1796),SS_UINT8);ssSetInputPortDirectFeedThrough(S,(0x452+1415-0x9d9),(0x1ceb+970-0x20b4));ssSetInputPortRequiredContiguous(S,(0x12ca+4012-0x2276),(0x1a51+2164-0x22c4));ssSetInputPortWidth(S,(0x58c+7267-0x21ee),(0x131+9022-0x246e));ssSetInputPortDataType(S,(0x1b8a+1969-0x233a),SS_UINT8);ssSetInputPortDirectFeedThrough(S,(0xd28+5424-0x2257),(0x16d+828-0x4a8));ssSetInputPortRequiredContiguous(S,(0x1218+1185-0x16b8),(0x11bc+3879-0x20e2));ssSetInputPortWidth(S,(0x5d7+6420-0x1ee9),(0xda6+1073-0x11d6));ssSetInputPortDataType(S,(0xd23+5624-0x2319),SS_UINT32);ssSetInputPortDirectFeedThrough(S,(0x2172+1000-0x2558),(0x1a2f+988-0x1e0a));ssSetInputPortRequiredContiguous(S,(0x7f9+4410-0x1931),(0x1aad+935-0x1e53));ssSetNumSampleTimes(S,(0x143b+2235-0x1cf5));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x2265+747-0x2550));ssSetNumNonsampledZCs(S,(0x636+3307-0x1321));ssSetOptions(S,SS_OPTION_RUNTIME_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(zabe1e0cd2c)[(0x893+7670-0x2689)]==-1.0){ssSetSampleTime(S,(0x3b5+7196-0x1fd1),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x202+139-0x28d),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x6d3+8237-0x2700),mxGetPr(zabe1e0cd2c)[(0x11d+7329-0x1dbe)]);ssSetOffsetTime(S,(0x701+4420-0x1845),0.0);}}static void sg_ModelLoad(SimStruct*S){}static void sg_ModelStart(SimStruct*S){}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint8_t*z25c38fa6ae=(uint8_t*)ssGetInputPortSignal(S,(0x6b8+7664-0x24a8));uint8_t*z767a7fda26=(uint8_t*)ssGetInputPortSignal(S,(0x451+2062-0xc5e));uint32_t*zd356bc580f=(uint32_t*)ssGetInputPortSignal(S,(0x1fc2+1334-0x24f6));uint32_t value;uint8_t id;z78d32bde66*zae10e3f17f;zae10e3f17f=(z78d32bde66*)sg_module_get_custom_data(z6cd618c289,(uint32_t)mxGetPr(zfaa050b79d)[(0xa41+5454-0x1f8f)]);if(zae10e3f17f==NULL){ssSetErrorStatus(S,"\x49\x4f\x39\x30\x31\x20\x53\x65\x6e\x64\x20\x49\x6e\x74\x65\x72\x72\x75\x70\x74\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x69\x6e\x20\x4d\x6f\x64\x65\x6c\x53\x74\x65\x70" "\n");return;}id=*z767a7fda26;value=*zd356bc580f;if(*z25c38fa6ae==zb871a82aea){if(id>(0x1e0d+1090-0x2230)){sprintf(msg,"\x53\x65\x6e\x64\x20\x49\x6e\x74\x65\x72\x72\x75\x70\x74\x20\x65\x72\x72\x6f\x72\x3a\x42\x72\x6f\x61\x64\x63\x61\x73\x74\x20\x49\x44\x20\x76\x61\x6c\x75\x65\x20\x25\x64\x20\x6f\x75\x74\x73\x69\x7a\x65\x20\x76\x61\x6c\x69\x64\x20\x72\x61\x6e\x67\x20\x30\x2d\x33\x31",id);ssSetErrorStatus(S,msg);return;}zdd9d2caed5(zae10e3f17f,z6794e6f3a0+(id*(0x18f+6201-0x19c4)),value);}else if(*z25c38fa6ae==z5492e845c0){zdd9d2caed5(zae10e3f17f,zcccef5369b+(id*(0x188c+16-0x1898)),value);}else{sprintf(msg,"\x53\x65\x6e\x64\x20\x49\x6e\x74\x65\x72\x72\x75\x70\x74\x20\x65\x72\x72\x6f\x72\x3a\x20\x55\x6e\x6b\x6e\x6f\x77\x6e\x20\x49\x6e\x74\x65\x72\x72\x75\x70\x74\x20\x74\x79\x70\x65\x20\x25\x64\x20",*z25c38fa6ae);ssSetErrorStatus(S,msg);return;}
#endif
}static void sg_ModelStop(SimStruct*S){}
#include "sg_sfcn_glue.h"   

