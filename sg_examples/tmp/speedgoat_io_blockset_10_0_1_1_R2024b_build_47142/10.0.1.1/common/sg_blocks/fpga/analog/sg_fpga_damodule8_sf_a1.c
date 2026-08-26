// Copyright 2006-2026 Speedgoat GmbH

#define 	S_FUNCTION_LEVEL 	(0x12b4+1758-0x1990)
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_fpga_damodule8_sf_a1
#include 	<stddef.h>
#include 	<stdlib.h>
#include    <stdint.h>
#include    <stdbool.h>
#include 	"simstruc.h"
#ifdef 		MATLAB_MEX_FILE
#include 	"mex.h"
#endif
#ifndef   MATLAB_MEX_FILE
#include  "sg_common.h"
#include  "sg_fpga_io3xx_util.h"
#include  "sg_callback_legacy.h"
#include  "sg_printf.h"
#endif
typedef enum{zf80bd68bc8,ID,CHANNEL,z46570de0b9,z909b6244de,zfa609438a6,z59ee0f6783,z33b16a549a,ze344b15ab1,SLOT,zdf24515981}z4253320a41;
#define z533b11d03f   ssGetSFcnParam(S, zf80bd68bc8)
#define z58f464b4bb          ssGetSFcnParam(S, ID)
#define za9d8fb6bcf     ssGetSFcnParam(S, CHANNEL) 
#define z9ad049935d  ssGetSFcnParam(S, z46570de0b9)
#define z59bb2f4bac  ssGetSFcnParam(S, z909b6244de)
#define z962f28f429  ssGetSFcnParam(S, zfa609438a6)
#define z159ecbe81e     ssGetSFcnParam(S, z59ee0f6783) 
#define z04f0a23313    ssGetSFcnParam(S, z33b16a549a) 
#define z3832b85a32   ssGetSFcnParam(S, ze344b15ab1)
#define z702a26a5e9        ssGetSFcnParam(S, SLOT)
#define z2e6483d505              ((0xc12+1263-0x1101))
#define zc5ce4cb81a              ((0x88d+6121-0x2076))
#define z2b17e2ee3b              ((0x16db+3702-0x2550))
#define z0194338df7         ((0xe79+5810-0x252b))
#define z5bbcf8be2c            ((0x155c+3619-0x237e))
#define zde0f6a0b5c              (655360)
static char msg[(0x1595+851-0x17e8)];struct z6e54179dbd{uint32_t zd7f607991c[(0x1daa+2409-0x270b)];uint32_t z64c973e715[(0xd39+6026-0x24bb)];uint32_t z3a9c5f054e[(0x6c5+7991-0x25f4)];uint32_t enable;uint32_t z6a621e2ebc;uint32_t za87b7c2ad3;uint32_t z6054f6af1e;uint32_t z5e2f82e53b;uint32_t version;};static void mdlInitializeSizes(SimStruct*S){uint32_t i,za0df33019b;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0xc36+1764-0x131a));ssSetNumDiscStates(S,(0xe83+2165-0x16f8));za0df33019b=(0x1441+3434-0x21ab);for(i=(0x816+3593-0x161f);i<(uint32_t)mxGetN(za9d8fb6bcf);i++){if((uint32_t)mxGetPr(z9ad049935d)[i]==(0x69c+110-0x70a)){za0df33019b++;}}ssSetNumInputPorts(S,za0df33019b);for(i=(0x1509+4029-0x24c6);i<za0df33019b;i++){ssSetInputPortWidth(S,i,(0x591+6811-0x202b));ssSetInputPortDirectFeedThrough(S,i,(0x120a+4474-0x2383));ssSetInputPortRequiredContiguous(S,i,(0xd0f+2024-0x14f6));}ssSetNumOutputPorts(S,(0x955+1990-0x111b));ssSetNumSampleTimes(S,(0x6f1+6818-0x2192));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x10f3+4719-0x2362));ssSetNumNonsampledZCs(S,(0xa23+5101-0x1e10));for(i=(0x4a+1707-0x6f5);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x1960+2367-0x229f));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x12eb+646-0x1571)]==-1.0){ssSetSampleTime(S,(0x1bff+2816-0x26ff),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x1160+2666-0x1bca),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x17ec+3635-0x261f),mxGetPr(z3832b85a32)[(0xbc2+4607-0x1dc1)]);ssSetOffsetTime(S,(0x1a2c+2152-0x2294),0.0);}}
#define MDL_START
static void mdlStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_t i;uint32_t z6a621e2ebc;uint32_t z5abc1f8ab7,zf227f0a711,z97287efa46,zeeeba54a90;sg_fpga_io3xxModuleIdT moduleId;uint32_t boardType,channel,enable;volatile struct z6e54179dbd*zf1756dff08;void*bar2ptr;boardType=(uint32_t)mxGetPr(z533b11d03f)[(0x81a+6464-0x215a)];if((int32_t)sg_fpga_IO3xxGetModuleId(boardType,&moduleId)<(0xfca+1266-0x14bc)){sprintf(msg,"\x49\x4f\x33\x33\x78\x2d\x30\x38\x20\x64\x69\x67\x69\x74\x61\x6c\x20\x74\x6f\x20\x61\x6e\x61\x6c\x6f\x67\x20\x62\x6c\x6f\x63\x6b\x3a\x20\x62\x6f\x61\x72\x64\x20\x74\x79\x70\x65\x20\x69\x6e\x63\x6f\x72\x72\x65\x63\x74\x2e");ssSetErrorStatus(S,msg);return;}if(!io3xxGetAddressSgLib((int32_t)(int)mxGetPr(z58f464b4bb)[(0x65f+169-0x708)],SG_FPGA_IO3XX_BAR2)){ssSetErrorStatus(S,pSgErrorStr);return;}bar2ptr=io3xxGetAddressSgLib((int32_t)(int)mxGetPr(z58f464b4bb)[(0x5a9+1991-0xd70)],SG_FPGA_IO3XX_BAR2);ssSetPWorkValue(S,z0194338df7,bar2ptr);zf1756dff08=(volatile struct z6e54179dbd*)((uintptr_t)bar2ptr+zde0f6a0b5c);if(!sg_isModelInit()){z5abc1f8ab7=((zf1756dff08->version&3221225472)>>(0xcb0+5531-0x222d));zf227f0a711=((zf1756dff08->version&1072693248)>>(0x1d8a+197-0x1e49));z97287efa46=((zf1756dff08->version&1047552)>>(0xa9+3211-0xd2a));zeeeba54a90=(zf1756dff08->version&(0x797+6564-0x1d3c));(void)zeeeba54a90;if(z5abc1f8ab7==(0x4c9+6717-0x1f04)&&zf227f0a711==zde0f6a0b5c&&z97287efa46==z5bbcf8be2c){SG_PRINTF(INFO,"\x25\x73\x2d\x30\x38\x20\x56\x65\x72\x73\x69\x6f\x6e\x20\x74\x65\x73\x74\x20\x6f\x6b\x21" "\n",moduleId.devname);}else{}z6a621e2ebc=(0xbda+1320-0x1102);enable=(0xbaa+1461-0x115f);for(i=(0xa52+4926-0x1d90);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0xbe7+4848-0x1ed6);enable|=((0x1b5c+2993-0x270c)<<channel);if((uint32_t)mxGetPr(z9ad049935d)[i]==(0x8bc+5725-0x1f18)){z6a621e2ebc|=((0x1ec6+262-0x1fcb)<<channel);}else{z6a621e2ebc&=~((0x1940+2088-0x2167)<<channel);}zf1756dff08->z3a9c5f054e[channel]=(uint32_t)mxGetPr(z59bb2f4bac)[i]-(0x1015+5114-0x240e);zf1756dff08->z64c973e715[channel]=(uint32_t)mxGetPr(z962f28f429)[i]-(0x2286+44-0x22b1);}zf1756dff08->z5e2f82e53b=(0x402+655-0x68f);zf1756dff08->z5e2f82e53b|=((0x3d3+4949-0x1726)<<(0x2146+1280-0x2636));zf1756dff08->z6054f6af1e=(0x43b+8349-0x24d7);zf1756dff08->z6054f6af1e=(0x61f+6344-0x1ee7);zf1756dff08->z6a621e2ebc=z6a621e2ebc;zf1756dff08->enable=enable;}
#endif
}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){
#ifndef MATLAB_MEX_FILE
uint32_t i,channel,update,z0add1d1c25;volatile struct z6e54179dbd*zf1756dff08;double*in;uintptr_t base=(uintptr_t)ssGetPWorkValue(S,z0194338df7);uint16_t count;double z7de4111e09;zf1756dff08=(volatile struct z6e54179dbd*)(base+zde0f6a0b5c);update=(0x2d7+691-0x58a);z0add1d1c25=(0x1870+2862-0x239e);for(i=(0x3dd+4832-0x16bd);i<(uint32_t)mxGetN(za9d8fb6bcf);i++){if((uint32_t)mxGetPr(z9ad049935d)[i]==(0x1f86+952-0x233e)){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0xc3b+4011-0x1be5);update|=((0x1341+1332-0x1874)<<channel);in=(double*)ssGetInputPortSignal(S,z0add1d1c25);z7de4111e09=in[(0x8a+8378-0x2144)];z7de4111e09+=10.0;count=(uint16_t)((int16_t)((z7de4111e09/20.0)*65535.0));zf1756dff08->zd7f607991c[channel]=count;z0add1d1c25++;}}if(update>(0xe76+608-0x10d6)){zf1756dff08->za87b7c2ad3=update;zf1756dff08->za87b7c2ad3=(0x1a49+639-0x1cc8);}
#endif
}static void mdlTerminate(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uintptr_t base=(uintptr_t)ssGetPWorkValue(S,z0194338df7);uint32_t i,update,channel;uint16_t count;double z7de4111e09=(0x195+6044-0x1931);volatile struct z6e54179dbd*zf1756dff08;zf1756dff08=(struct z6e54179dbd*)(base+zde0f6a0b5c);if(sg_isModelInit()){zf1756dff08->z6a621e2ebc=(0xea4+6076-0x2660);zf1756dff08->z5e2f82e53b=(0x1c9+7907-0x20aa);zf1756dff08->z5e2f82e53b|=((0xdd+1656-0x753)<<(0xe43+1206-0x12e9));sg_wait_s(0.00001);zf1756dff08->z6054f6af1e=(0x5f3+631-0x869);zf1756dff08->z6054f6af1e=(0x60c+5583-0x1bdb);update=(0x2d2+4291-0x1395);for(i=(0x1253+3516-0x200f);i<(uint32_t)mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0xf6c+458-0x1135);update|=((0x15e8+4388-0x270b)<<channel);z7de4111e09=(double)mxGetPr(z159ecbe81e)[i];z7de4111e09+=10.0;count=(uint16_t)((int16_t)((z7de4111e09/20.0)*65535.0));zf1756dff08->zd7f607991c[channel]=count;}zf1756dff08->enable=update;zf1756dff08->za87b7c2ad3=update;zf1756dff08->za87b7c2ad3=(0xe9d+5101-0x228a);sg_wait_s(0.00001);}else{zf1756dff08->z6a621e2ebc=(0x11c6+4607-0x23c5);sg_wait_s(0.00001);update=(0x16cd+2150-0x1f33);for(i=(0xb48+2036-0x133c);i<(uint32_t)mxGetN(za9d8fb6bcf);i++){if((uint32_t)mxGetPr(z04f0a23313)[i]){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x1cff+155-0x1d99);update|=((0x267+5867-0x1951)<<channel);z7de4111e09=(double)mxGetPr(z159ecbe81e)[i];z7de4111e09+=10.0;count=(uint16_t)((int16_t)((z7de4111e09/20.0)*65535.0));zf1756dff08->zd7f607991c[channel]=count;}}zf1756dff08->za87b7c2ad3=update;zf1756dff08->za87b7c2ad3=(0x1fa3+1362-0x24f5);sg_wait_s(0.00001);}
#endif
}
#include "sg_sfcn_glue.h"   

