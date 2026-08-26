// Copyright 2006-2026 Speedgoat GmbH

#define 	S_FUNCTION_LEVEL 	(0x9bc+1859-0x10fd)
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_fpga_serialwrhwfifo_sf_1
#include 	<stddef.h>
#include 	<stdlib.h>
#include  <stdint.h>
#include 	"simstruc.h" 
#ifdef 		MATLAB_MEX_FILE
#include 	"mex.h"
#endif
#ifndef MATLAB_MEX_FILE
#include  "sg_common.h"
#include  "sg_fpga_io3xx_util.h"
#include  "sg_callback_legacy.h"
#endif
#define zdf24515981              ((0xcc9+3059-0x18b5))
#define z533b11d03f               ssGetSFcnParam(S, (0xefc+2124-0x1748)) 
#define z58f464b4bb                      ssGetSFcnParam(S, (0x2f4+2605-0xd20))
#define za9d8fb6bcf                 ssGetSFcnParam(S, (0x43f+5768-0x1ac5)) 
#define zd1006aaed1            ssGetSFcnParam(S, (0x1199+3859-0x20a9))
#define za228ac10f3            ssGetSFcnParam(S, (0xa6b+5644-0x2073))
#define z3832b85a32               ssGetSFcnParam(S, (0x902+2814-0x13fb))
#define z702a26a5e9                    ssGetSFcnParam(S, (0x1fc0+1256-0x24a2))
#define z2e6483d505              ((0x1214+2703-0x1ca3))
#define zc5ce4cb81a              ((0x16b5+939-0x1a60))
#define z2b17e2ee3b              ((0xcf0+5135-0x20fe))
#define z93d7dbe681         ((0x2d9+6484-0x1c2d))  
static char_T msg[(0x849+2506-0x1113)];
#define z90917e531a                 (1081344)
#define z9e2acbd2a6                         ((0x924+1243-0xdfb))
#define SPR                         ((0x6e0+5609-0x1cc2))
struct SERIAL{uint32_t z8ed0e350a6;uint32_t z50c2fe3d67;uint32_t cs;uint32_t zdf75ab3269;uint32_t addr;uint32_t data;uint32_t ze1df3f2032[(0xdc+8726-0x22d2)];uint32_t z9b71add2e2;uint32_t zd114ff6ac4;uint32_t z6ad1de6ae2;uint32_t test1;uint32_t test2;uint32_t z100bdfa0d3;uint32_t zf39deaa0a5;uint32_t version;};static uint8_t zdbce8f148f(SimStruct*S,uint8_t channel,uint8_t addr);static void z4959649fab(SimStruct*S,uint8_t channel,uint8_t addr,uint8_t data);
#ifndef MATLAB_MEX_FILE
static uint8_t zdbce8f148f(SimStruct*S,uint8_t channel,uint8_t addr){uintptr_t base=(uintptr_t)ssGetPWorkValue(S,z93d7dbe681);volatile struct SERIAL*serial=(volatile struct SERIAL*)(base+z90917e531a);uint8_t data;serial->cs=~((0x5d9+6627-0x1fbb)<<channel);serial->addr=addr;serial->z8ed0e350a6=~((0x5fa+4700-0x1855)<<channel);data=serial->data;serial->z8ed0e350a6=4294967295;serial->cs=4294967295;return data;}
#endif
#ifndef MATLAB_MEX_FILE
static void z4959649fab(SimStruct*S,uint8_t channel,uint8_t addr,uint8_t data){uintptr_t base=(uintptr_t)ssGetPWorkValue(S,z93d7dbe681);volatile struct SERIAL*serial=(volatile struct SERIAL*)(base+z90917e531a);serial->cs=~((0x149a+2430-0x1e17)<<channel);serial->addr=addr;serial->data=data;serial->z50c2fe3d67=~((0x1530+808-0x1857)<<channel);serial->z50c2fe3d67=4294967295;serial->cs=4294967295;}
#endif
#ifndef MATLAB_MEX_FILE
static void zdc4dfcc407(SimStruct*S,uint8_t channel,uint8_t addr){uintptr_t base=(uintptr_t)ssGetPWorkValue(S,z93d7dbe681);volatile struct SERIAL*serial=(volatile struct SERIAL*)(base+z90917e531a);serial->cs=~((0x3c6+8045-0x2332)<<channel);serial->addr=addr;}
#endif
#ifndef MATLAB_MEX_FILE
static void z1a301dcb7d(SimStruct*S){uintptr_t base=(uintptr_t)ssGetPWorkValue(S,z93d7dbe681);volatile struct SERIAL*serial=(volatile struct SERIAL*)(base+z90917e531a);serial->cs=4294967295;}
#endif
#ifndef MATLAB_MEX_FILE
static void z9858781dd9(SimStruct*S,uint32_t channel,uint32_t z9b71add2e2){uintptr_t base=(uintptr_t)ssGetPWorkValue(S,z93d7dbe681);volatile struct SERIAL*serial=(volatile struct SERIAL*)(base+z90917e531a);serial->z100bdfa0d3=z9b71add2e2;serial->zf39deaa0a5=((0x97d+4847-0x1c6b)<<channel);serial->zf39deaa0a5=(0xa84+2092-0x12b0);}
#endif
static void mdlInitializeSizes(SimStruct*S){uint32_t i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x2206+325-0x234b));ssSetNumDiscStates(S,(0x4ec+3885-0x1419));ssSetNumInputPorts(S,(0xf17+1301-0x142a));ssSetInputPortWidth(S,(0x431+3219-0x10c4),(0x1080+163-0x10a2));if((uint32_t)mxGetPr(zd1006aaed1)[(0x12f7+4997-0x267c)]<=(0x1212+2727-0x1cb1)){ssSetInputPortDataType(S,(0x171a+996-0x1afe),SS_UINT8);}else{ssSetInputPortDataType(S,(0x19c+1439-0x73b),SS_UINT16);}ssSetInputPortDirectFeedThrough(S,(0x5b6+877-0x923),(0x19c3+811-0x1ced));ssSetInputPortRequiredContiguous(S,(0x6d4+7011-0x2237),(0xa05+7392-0x26e4));ssSetInputPortWidth(S,(0xd07+6213-0x254b),(0x1891+1007-0x1c7f));ssSetInputPortDataType(S,(0x7c8+3323-0x14c2),SS_BOOLEAN);ssSetInputPortDirectFeedThrough(S,(0x1015+2478-0x19c2),(0x931+3080-0x1538));ssSetInputPortRequiredContiguous(S,(0x9d7+549-0xbfb),(0x6f2+395-0x87c));ssSetNumOutputPorts(S,(0xa76+6377-0x235f));ssSetNumSampleTimes(S,(0xa6+1667-0x728));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x955+6958-0x2483));ssSetNumNonsampledZCs(S,(0x136+5430-0x166c));for(i=(0x17a5+2353-0x20d6);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x170d+2266-0x1fe7));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x793+7704-0x25ab)]==-1.0){ssSetSampleTime(S,(0x669+2530-0x104b),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x345+588-0x591),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x77+4775-0x131e),mxGetPr(z3832b85a32)[(0x893+7655-0x267a)]);ssSetOffsetTime(S,(0xbea+2411-0x1555),0.0);}}
#define MDL_START
static void mdlStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
int32_t bus,slot;sg_fpga_io3xxModuleIdT moduleId;uint32_t boardType;void*bar2ptr;boardType=(uint32_t)mxGetPr(z533b11d03f)[(0x9c5+3798-0x189b)];if((int32_t)sg_fpga_IO3xxGetModuleId(boardType,&moduleId)<(0x771+4635-0x198c)){sprintf(msg,"\x73\x65\x72\x69\x61\x6c\x20\x77\x72\x69\x74\x65\x20\x62\x6c\x6f\x63\x6b\x3a\x20\x62\x6f\x61\x72\x64\x20\x74\x79\x70\x65\x20\x69\x6e\x63\x6f\x72\x72\x65\x63\x74\x2e");ssSetErrorStatus(S,msg);}if(mxGetN(z702a26a5e9)==(0x2402+240-0x24f1)){bus=(0x22c+7334-0x1ed2);slot=(int_T)mxGetPr(z702a26a5e9)[(0x8af+2067-0x10c2)];}else{bus=(int_T)mxGetPr(z702a26a5e9)[(0x19ac+2112-0x21ec)];slot=(int_T)mxGetPr(z702a26a5e9)[(0x65d+2197-0xef1)];}if(!sg_isModelInit()){if(!io3xxGetAddressSgLib((int32_t)(int)mxGetPr(z58f464b4bb)[(0x5ac+3248-0x125c)],SG_FPGA_IO3XX_BAR2)){ssSetErrorStatus(S,pSgErrorStr);return;}bar2ptr=io3xxGetAddressSgLib((int32_t)(int)mxGetPr(z58f464b4bb)[(0xb3f+4592-0x1d2f)],SG_FPGA_IO3XX_BAR2);ssSetPWorkValue(S,z93d7dbe681,(void*)bar2ptr);}
#endif
}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){
#ifndef MATLAB_MEX_FILE
uint8_t*enable;uint8_t*data;uint16_t*z1376896266;uint16_t z70d9277d09;uint8_t z6e7f3ebc67,za04c2624c1;uint32_t channel,i,z26dbd73a5e,z82ac44565f,z3b381ce2a4,z9b71add2e2;uint32_t z11fa5208eb;real_T z9ab632cec0,zcbcca07cb5;enable=(boolean_T*)ssGetInputPortSignal(S,(0x14a0+1047-0x18b6));if(enable[(0x1650+551-0x1877)]){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[(0xbcb+5342-0x20a9)]-(0x7b8+2562-0x11b9);if((uint32_t)mxGetPr(zd1006aaed1)[(0x438+7538-0x21aa)]<=(0x219c+428-0x2340)){data=(uint8_t*)ssGetInputPortSignal(S,(0x527+1919-0xca6));z6e7f3ebc67=data[(0x239+4742-0x14bf)];if(((uint32_t)mxGetPr(za228ac10f3)[(0x1bad+2532-0x2591)])==(0x8eb+948-0xc9e)){z11fa5208eb=(0x3b9+4294-0x13ff)-zdbce8f148f(S,channel,z9e2acbd2a6);if(z11fa5208eb<z6e7f3ebc67){sprintf(msg,"\x53\x65\x72\x69\x61\x6c\x20\x46\x50\x47\x41\x20\x43\x6f\x64\x65\x20\x4d\x6f\x64\x75\x6c\x65\x20\x25\x64\x3a\x20\x6f\x75\x74\x70\x75\x74\x20\x62\x75\x66\x66\x65\x72\x20\x6f\x76\x65\x72\x66\x6c\x6f\x77",channel+(0x5cc+4015-0x157a));ssSetErrorStatus(S,msg);return;}z82ac44565f=z6e7f3ebc67/(0x7bf+4905-0x1ae4);z3b381ce2a4=z6e7f3ebc67%(0x1bea+1650-0x2258);zdc4dfcc407(S,channel,(0xb4c+4680-0x1d94));for(i=(0x10d+6385-0x19fe);i<z82ac44565f;i++){z9b71add2e2=data[i*(0x73+3467-0xdfa)+(0x46b+6843-0x1f25)]|(data[i*(0x1f22+1311-0x243d)+(0x14e9+3616-0x2307)]<<(0xac6+2752-0x157e))|(data[i*(0x1ec8+354-0x2026)+(0xaa2+317-0xbdc)]<<(0xc9b+735-0xf6a))|(data[i*(0x702+934-0xaa4)+(0x1093+339-0x11e2)]<<(0xe26+2394-0x1768));z9858781dd9(S,channel,z9b71add2e2);}z1a301dcb7d(S);for(i=(0xba6+3910-0x1aec);i<z3b381ce2a4;i++){z4959649fab(S,channel,(0x9c2+822-0xcf8),data[(0xf46+1865-0x168b)*z82ac44565f+i+(0x1a1b+2339-0x233d)]);}}else if(((uint32_t)mxGetPr(za228ac10f3)[(0x208b+95-0x20ea)])==(0x96d+6703-0x239a)){za04c2624c1=z6e7f3ebc67;z26dbd73a5e=(0x3aa+1235-0x87d);z9ab632cec0=sg_getElapsedTime();while(za04c2624c1>(0x15d1+3338-0x22db)){zcbcca07cb5=sg_getElapsedTime();if(zcbcca07cb5-z9ab632cec0>3.0){sprintf(msg,"\x54\x69\x6d\x65\x6f\x75\x74\x2d\x65\x72\x72\x6f\x72\x20\x77\x68\x69\x6c\x65\x20\x77\x61\x69\x74\x69\x6e\x67\x20\x6f\x6e\x20\x46\x49\x46\x4f\x20\x61\x63\x63\x65\x73\x73" "\n");ssSetErrorStatus(S,msg);return;}z11fa5208eb=(0xa44+517-0xbc9)-zdbce8f148f(S,channel,z9e2acbd2a6);for(i=(0xee9+414-0x1087);i<z11fa5208eb;i++){z4959649fab(S,channel,(0x700+2217-0xfa9),data[z26dbd73a5e+(0x975+1461-0xf29)]);z26dbd73a5e++;za04c2624c1--;if(za04c2624c1==(0x13fd+4104-0x2405)){break;}}};}else{z82ac44565f=z6e7f3ebc67/(0xc37+37-0xc58);z3b381ce2a4=z6e7f3ebc67%(0x134+9602-0x26b2);zdc4dfcc407(S,channel,(0x2469+577-0x26aa));for(i=(0x295+6217-0x1ade);i<z82ac44565f;i++){z9b71add2e2=data[i*(0xbbd+111-0xc28)+(0xaa7+3137-0x16e7)]|(data[i*(0xb26+4107-0x1b2d)+(0xfd1+5151-0x23ee)]<<(0x64c+7159-0x223b))|(data[i*(0x1404+3437-0x216d)+(0x10f9+3790-0x1fc4)]<<(0x4e4+1883-0xc2f))|(data[i*(0x14e0+70-0x1522)+(0x12b2+3686-0x2114)]<<(0x17fb+543-0x1a02));z9858781dd9(S,channel,z9b71add2e2);}z1a301dcb7d(S);for(i=(0xf1a+4089-0x1f13);i<z3b381ce2a4;i++){z4959649fab(S,channel,(0xba2+6072-0x235a),data[(0x1441+3531-0x2208)*z82ac44565f+i+(0x949+1533-0xf45)]);}}}else{z1376896266=(uint16_t*)ssGetInputPortSignal(S,(0x1682+830-0x19c0));z70d9277d09=z1376896266[(0xcec+5233-0x215d)];if(!((uint32_t)mxGetPr(za228ac10f3)[(0xc8+1977-0x881)])){z11fa5208eb=(0x222d+1349-0x26f2)-zdbce8f148f(S,channel,z9e2acbd2a6);if(z11fa5208eb<z70d9277d09){sprintf(msg,"\x53\x65\x72\x69\x61\x6c\x20\x46\x50\x47\x41\x20\x43\x6f\x64\x65\x20\x4d\x6f\x64\x75\x6c\x65\x20\x25\x64\x3a\x20\x6f\x75\x74\x70\x75\x74\x20\x62\x75\x66\x66\x65\x72\x20\x6f\x76\x65\x72\x66\x6c\x6f\x77",channel+(0x103a+3672-0x1e91));ssSetErrorStatus(S,msg);return;}}for(i=(0x27f+693-0x534);i<z70d9277d09;i++){z4959649fab(S,channel,SPR,(z1376896266[i+(0x82a+4691-0x1a7c)]>>(0x850+4503-0x19df))&(0xdd0+2671-0x183e));z4959649fab(S,channel,(0x702+4578-0x18e4),z1376896266[i+(0x9f+5804-0x174a)]&(0x698+5508-0x1b1d));}}}
#endif
}static void mdlTerminate(SimStruct*S){
#ifndef MATLAB_MEX_FILE
#endif
}
#include "sg_sfcn_glue.h"   

