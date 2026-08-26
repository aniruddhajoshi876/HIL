// Copyright 2006-2026 Speedgoat GmbH

#define   S_FUNCTION_LEVEL  (0x1d11+1453-0x22bc)
#undef    S_FUNCTION_NAME
#define   S_FUNCTION_NAME   sg_fpga_da_sf_a1
#include  <stddef.h>
#include  <stdlib.h>
#include  <stdint.h>
#include  <stdbool.h>
#include  "simstruc.h"
#ifdef    MATLAB_MEX_FILE
#include  "mex.h"
#endif
#ifndef   MATLAB_MEX_FILE
#include  "sg_common.h"
#include  "sg_fpga_io3xx_util.h"
#include  "sg_printf.h"
#endif
#include  "sg_callback.h"
#define ze13f49a01f     ssGetSFcnParam(S, (0x7cf+4952-0x1b27))
#define za9d8fb6bcf       ssGetSFcnParam(S, (0x2d5+7248-0x1f24)) 
#define z4eb7791e75 ssGetSFcnParam(S, (0x6c2+8190-0x26be)) 
#define z159ecbe81e       ssGetSFcnParam(S, (0x8bd+3000-0x1472)) 
#define z04f0a23313      ssGetSFcnParam(S, (0x7f6+1161-0xc7b)) 
#define z3832b85a32     ssGetSFcnParam(S, (0x91a+3217-0x15a6))
#define zdf24515981                     ((0x13f1+2414-0x1d59))
#define zd7444a6eb4        (0x3e4+6665-0x1ded)
#define z56d9a5f3fc        (0xf30+2285-0x181c)
#define z224e3428b1 (0xb1b+6802-0x25ab)
#define z2e6483d505        ((0x126d+3348-0x1f80))
#define zad6b2ff006     ((0x1416+284-0x1532))
#define zc5ce4cb81a        ((0x1622+3934-0x2580))
#define z2b17e2ee3b        ((0x5aa+5029-0x194e))
#define z0194338df7   ((0x149f+3513-0x2258))
#define zb7aa091922       ((0x7b0+5474-0x1d10))
#define z5674e18e88      (0x9af+1513-0xf90)
#define z4099fa3dcd      (32767/(0x66+1596-0x698))
static char msg[(0xc28+2557-0x1525)];struct z6e54179dbd{uint32_t zcbaef9b07f;uint32_t command;int32_t data[(0x1364+2079-0x1b7b)];uint32_t zaf91a33927;uint32_t zc78a7188e6;};static void mdlInitializeSizes(SimStruct*S){uint32_t i,za0df33019b;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0xed1+758-0x11c7));ssSetNumDiscStates(S,(0x1ed+686-0x49b));za0df33019b=(uint32_t)mxGetN(za9d8fb6bcf);if(!ssSetNumInputPorts(S,za0df33019b)){return;}if(!ssSetNumOutputPorts(S,(0x8b6+193-0x977))){return;}for(i=(0x130+1126-0x596);i<za0df33019b;i++){ssSetInputPortWidth(S,i,(0x1f32+1803-0x263c));ssSetInputPortDirectFeedThrough(S,i,(0xbed+3595-0x19f7));ssSetInputPortRequiredContiguous(S,i,(0x1808+1668-0x1e8b));}ssSetNumSampleTimes(S,(0x1864+2467-0x2206));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x921+6057-0x20ca));ssSetNumNonsampledZCs(S,(0xf21+4665-0x215a));for(i=(0xc96+3529-0x1a5f);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x70d+7021-0x227a));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x1e54+1736-0x251c)]==-1.0){ssSetSampleTime(S,(0x8c2+6086-0x2088),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0xedb+878-0x1249),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x1890+1109-0x1ce5),mxGetPr(z3832b85a32)[(0x1864+2643-0x22b7)]);ssSetOffsetTime(S,(0xc2d+3580-0x1a29),0.0);}}static void sg_ModelLoad(SimStruct*S){
#ifndef MATLAB_MEX_FILE
volatile struct z6e54179dbd*zf1756dff08;uintptr_t z70fcda5f5d;int moduleId=(int)mxGetScalar(ze13f49a01f);char*boardName=io3xxGetBoardNameSgLib(moduleId);z70fcda5f5d=(uintptr_t)io3xxGetAddressSgLib((int)mxGetPr(ze13f49a01f)[(0x334+6646-0x1d2a)],SG_FPGA_IO3XX_BAR2);if(z70fcda5f5d==(0x1c6b+269-0x1d78)){ssSetErrorStatus(S,pSgErrorStr);return;}uint32_t zf7ccd17be8=(0x68f+7008-0x21ef);if(sg_fpga_io3xx_getCmBaseAddress(moduleId,DABASE,&zf7ccd17be8)){sprintf(msg,"\x25\x73\x20\x44\x41\x20\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x4f\x66\x66\x73\x65\x74\x20\x6c\x6f\x6f\x6b\x75\x70\x20\x75\x6e\x73\x75\x63\x63\x65\x73\x73\x66\x75\x6c\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}zf1756dff08=(volatile struct z6e54179dbd*)(z70fcda5f5d+zf7ccd17be8);ssSetPWorkValue(S,z0194338df7,(void*)zf1756dff08);ssSetIWorkValue(S,zad6b2ff006,(uint32_t)zd7444a6eb4);
#endif
}static void sg_ModelStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE  
volatile struct z6e54179dbd*zf1756dff08;zf1756dff08=(volatile struct z6e54179dbd*)ssGetPWorkValue(S,z0194338df7);uint32_t channel,enable,i;ssSetIWorkValue(S,zad6b2ff006,z56d9a5f3fc);enable=(0x233+1104-0x683);for(i=(0xbe2+4792-0x1e9a);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x339+6459-0x1c73);enable|=((0x16e5+1133-0x1b51)<<channel);}zf1756dff08->zcbaef9b07f=enable;zf1756dff08->zaf91a33927=(uint32_t)mxGetPr(z4eb7791e75)[(0x1511+2053-0x1d16)]-(0x1bba+1498-0x2193);
#endif
}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_t i,channel;double*y,value;volatile struct z6e54179dbd*zf1756dff08;zf1756dff08=(volatile struct z6e54179dbd*)ssGetPWorkValue(S,z0194338df7);for(i=(0xead+1733-0x1572);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x85a+5405-0x1d76);y=(double*)ssGetInputPortSignal(S,i);value=(double)(y[(0x13+5107-0x1406)]);if(value>(0x2e7+5250-0x175f)){zf1756dff08->data[channel]=32767;}else if(value<-(0x94f+301-0xa72)){zf1756dff08->data[channel]=32768;}else{zf1756dff08->data[channel]=(int32_t)(value*z4099fa3dcd);}}if((uint32_t)mxGetPr(z4eb7791e75)[(0x1c3+7014-0x1d29)]==(0x1b14+2406-0x2479)){zf1756dff08->zc78a7188e6=(0x865+3673-0x16bd);zf1756dff08->zc78a7188e6=(0x14a4+3084-0x20b0);}
#endif
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_t i,channel,enable,z0f0c5d6bfa;volatile struct z6e54179dbd*zf1756dff08;zf1756dff08=(volatile struct z6e54179dbd*)ssGetPWorkValue(S,z0194338df7);z0f0c5d6bfa=(uint32_t)ssGetIWorkValue(S,zad6b2ff006);if(zd7444a6eb4==z0f0c5d6bfa){for(i=(0x1a71+191-0x1b30);i<z5674e18e88;i++){zf1756dff08->data[i]=(0xe5+3796-0xfb9);}zf1756dff08->zaf91a33927=(0x1854+3233-0x24f5);enable=(0x1933+2076-0x214f);for(i=(0x18c9+1281-0x1dca);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x437+870-0x79c);SG_PRINTF(INFO,"\x49\x6e\x69\x74\x76\x20\x56\x61\x6c\x20\x6f\x66\x20\x43\x48\x25\x64\x20\x3d\x20\x25\x66" "\n",channel+(0x85d+150-0x8f2),mxGetPr(z159ecbe81e)[i]);enable|=((0x234a+585-0x2592)<<channel);zf1756dff08->data[channel]=(int32_t)(mxGetPr(z159ecbe81e)[i]*z4099fa3dcd);}zf1756dff08->zcbaef9b07f=(0x16e9+2974-0x2188);zf1756dff08->zc78a7188e6=(0x9c9+4148-0x19fc);zf1756dff08->zc78a7188e6=(0xf77+2778-0x1a51);sg_wait_s(0.0001);zf1756dff08->zcbaef9b07f=enable;}else{zf1756dff08->zaf91a33927=(0xd5f+2246-0x1625);sg_wait_s(0.0001);enable=(0x4da+6644-0x1ece);for(i=(0xaa2+6902-0x2598);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0xa53+1337-0xf8b);if((uint32_t)mxGetPr(z04f0a23313)[i]){zf1756dff08->data[channel]=(int32_t)(mxGetPr(z159ecbe81e)[i]*z4099fa3dcd);enable|=((0x151d+176-0x15cc)<<channel);}}zf1756dff08->zcbaef9b07f=enable;zf1756dff08->zc78a7188e6=(0xa7f+5102-0x1e6c);zf1756dff08->zc78a7188e6=(0x2383+422-0x2529);sg_wait_s(0.0001);}
#endif
}
#include "sg_sfcn_glue.h"   

