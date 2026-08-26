// Copyright 2006-2026 Speedgoat GmbH

#define 	S_FUNCTION_LEVEL 	(0xb0+8551-0x2215)
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_fpga_cam_encoder_sf_1
#include 	<stddef.h>
#include 	<stdlib.h>
#include  <stdint.h>
#include 	"simstruc.h" 
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif
#ifndef MATLAB_MEX_FILE
#include "sg_common.h"
#include "sg_fpga_io3xx_util.h"
#include "sg_callback_legacy.h"
#include "sg_printf.h"
#endif
typedef enum{zf80bd68bc8,zfaa050b79d,CHANNEL,ze344b15ab1,SLOT,z6c561dc4d0,zb6f6b332b9,z75dacb6973,zdf24515981}z144a4b4b8d;
#define z533b11d03f            ssGetSFcnParam(S, zf80bd68bc8) 
#define ze13f49a01f            ssGetSFcnParam(S, zfaa050b79d)
#define za9d8fb6bcf              ssGetSFcnParam(S, CHANNEL) 
#define z3832b85a32            ssGetSFcnParam(S, ze344b15ab1)
#define z702a26a5e9                 ssGetSFcnParam(S, SLOT)
#define z7cd927ffe6          ssGetSFcnParam(S, z6c561dc4d0) 
#define zdecf152cfe     ssGetSFcnParam(S, zb6f6b332b9) 
#define z0c9862abe7       ssGetSFcnParam(S, z75dacb6973) 
#define z2e6483d505            (0x617+6373-0x1efc)
#define zc5ce4cb81a            (0xc53+1261-0x1140)
#define z2b17e2ee3b            (0x53b+3797-0x140f)
#define z93d7dbe681       (0x1bcc+2450-0x255e)
#define z5bbcf8be2c          (0x1238+3342-0x1f45)
#define za78b950d0e      1130496
static char_T msg[(0x1a71+100-0x19d5)];struct zb86e0b5f8b{uint32_t version;uint32_t enable;uint32_t z230b1088f7[(0x1418+818-0x172a)];uint32_t z425a04401c[(0x33d+6220-0x1b69)];uint32_t z6fd270185b[(0x353+1564-0x94f)];};static void mdlInitializeSizes(SimStruct*S){uint32_t i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0xccf+414-0xe6d));ssSetNumDiscStates(S,(0x1be5+470-0x1dbb));ssSetNumInputPorts(S,(0x14f+7315-0x1de2));ssSetNumOutputPorts(S,(0x1d3+3017-0xd9c));ssSetNumSampleTimes(S,(0x1347+2182-0x1bcc));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x1147+2510-0x1b15));ssSetNumNonsampledZCs(S,(0x77d+5239-0x1bf4));for(i=(0x1d46+65-0x1d87);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0xef7+4714-0x2161));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0xc18+5166-0x2046)]==-1.0){ssSetSampleTime(S,(0x187+2399-0xae6),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0xc8d+317-0xdca),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x1be9+1944-0x2381),mxGetPr(z3832b85a32)[(0x133+9670-0x26f9)]);ssSetOffsetTime(S,(0x244+7317-0x1ed9),0.0);}}
#define MDL_START
static void mdlStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
int32_t bus,slot;uint32_t i;uint32_t boardType,channel,enable;uint32_t z5abc1f8ab7,zf227f0a711,z97287efa46,zeeeba54a90;real_T z230b1088f7,z64198f8f6d;real_T z7dab6f6958=75000000.0;volatile struct zb86e0b5f8b*zddee59f23a;sg_fpga_io3xxModuleIdT moduleId;void*bar2ptr;boardType=(uint32_t)mxGetPr(z533b11d03f)[(0x1f3+8824-0x246b)];if((int32_t)sg_fpga_IO3xxGetModuleId(boardType,&moduleId)<(0x1847+1217-0x1d08)){sprintf(msg,"\x63\x61\x6d\x20\x65\x6e\x63\x6f\x64\x65\x72\x20\x62\x6c\x6f\x63\x6b\x3a\x20\x62\x6f\x61\x72\x64\x20\x74\x79\x70\x65\x20\x69\x6e\x63\x6f\x72\x72\x65\x63\x74\x2e");ssSetErrorStatus(S,msg);}if(mxGetN(z702a26a5e9)==(0x1768+899-0x1aea)){bus=(0xa34+6030-0x21c2);slot=(int_T)mxGetPr(z702a26a5e9)[(0x14b0+1265-0x19a1)];}else{bus=(int_T)mxGetPr(z702a26a5e9)[(0x1594+2272-0x1e74)];slot=(int_T)mxGetPr(z702a26a5e9)[(0x72b+7589-0x24cf)];}if(!io3xxGetAddressSgLib((int32_t)(int)mxGetPr(ze13f49a01f)[(0x17f0+2713-0x2289)],SG_FPGA_IO3XX_BAR2)){ssSetErrorStatus(S,pSgErrorStr);return;}bar2ptr=io3xxGetAddressSgLib((int32_t)(int)mxGetPr(ze13f49a01f)[(0x1bbc+1100-0x2008)],SG_FPGA_IO3XX_BAR2);zddee59f23a=(struct zb86e0b5f8b*)((uintptr_t)bar2ptr+(uintptr_t)za78b950d0e);ssSetPWorkValue(S,z93d7dbe681,(void*)zddee59f23a);if(!sg_isModelInit()){z5abc1f8ab7=((zddee59f23a->version&3221225472)>>(0xdb8+404-0xf2e));zf227f0a711=((zddee59f23a->version&1072693248)>>(0xe54+5130-0x2258));z97287efa46=((zddee59f23a->version&1047552)>>(0xa2+2349-0x9c5));zeeeba54a90=(zddee59f23a->version&(0x137b+3629-0x1da9));if(z5abc1f8ab7==(0x565+6500-0x1ec7)&&zf227f0a711==za78b950d0e&&z97287efa46==z5bbcf8be2c){SG_PRINTF(INFO,"\x25\x73\x20\x43\x61\x6d\x20\x45\x6e\x63\x6f\x64\x65\x72\x20\x4d\x6f\x64\x75\x6c\x65\x20\x56\x65\x72\x73\x69\x6f\x6e\x20\x74\x65\x73\x74\x20\x6f\x6b\x21" "\n",moduleId.devname);}else{SG_PRINTF(INFO,"\x25\x73\x20\x77\x72\x6f\x6e\x67\x20\x76\x65\x72\x73\x69\x6f\x6e\x20\x6f\x66\x20\x63\x61\x6d\x20\x65\x6e\x63\x6f\x64\x65\x72\x20\x63\x6f\x64\x65\x6d\x6f\x64\x75\x6c\x65\x2e" "\n" "\x6d\x6f\x64\x75\x6c\x65\x42\x61\x73\x65\x3a\x20\x30\x78\x25\x78" "\n" "\x20\x6d\x61\x6a\x6f\x72\x56\x65\x72\x73\x69\x6f\x6e\x3a\x20\x30\x78\x25\x78" "\n" "\x20\x6d\x69\x6e\x6f\x72\x56\x65\x72\x73\x69\x6f\x6e\x3a\x20\x30\x78\x25\x78" "\n",moduleId.devname,zf227f0a711,z97287efa46,zeeeba54a90);ssSetErrorStatus(S,msg);}for(i=(0x4d2+1752-0xbaa);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0xa9d+2456-0x1434);z230b1088f7=(real_T)mxGetPr(z7cd927ffe6)[i];z64198f8f6d=(real_T)180.0/z230b1088f7;zddee59f23a->z230b1088f7[channel]=(uint32_t)z230b1088f7;zddee59f23a->z425a04401c[channel]=(uint32_t)((real_T)mxGetPr(zdecf152cfe)[i]/z64198f8f6d);zddee59f23a->z6fd270185b[channel]=(uint32_t)((real_T)mxGetPr(z0c9862abe7)[i]/z64198f8f6d);}enable=(0x1426+392-0x15ae);for(i=(0x1142+3748-0x1fe6);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x1a36+91-0x1a90);enable|=((0x1fbd+1302-0x24d2)<<channel);}zddee59f23a->enable|=enable;}
#endif
}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){
#ifndef MATLAB_MEX_FILE
#endif
}static void mdlTerminate(SimStruct*S){
#ifndef MATLAB_MEX_FILE
volatile struct zb86e0b5f8b*zddee59f23a;zddee59f23a=(struct zb86e0b5f8b*)ssGetPWorkValue(S,z93d7dbe681);zddee59f23a->enable=(0x2235+262-0x233b);
#endif
}
#include "sg_sfcn_glue.h"   

