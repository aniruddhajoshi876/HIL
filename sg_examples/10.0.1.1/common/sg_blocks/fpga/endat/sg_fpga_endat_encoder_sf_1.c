// Copyright 2006-2026 Speedgoat GmbH

#define   S_FUNCTION_LEVEL  (0xc8b+3795-0x1b5c)
#undef 	  S_FUNCTION_NAME
#define   S_FUNCTION_NAME   sg_fpga_endat_encoder_sf_1
#include  <stddef.h>
#include  <stdlib.h>
#include  <stdint.h>
#include  <math.h>
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
typedef enum{zfaa050b79d,CHANNEL,ze344b15ab1,zd3ea823cae,z7c1ba57595,zc3aa9f6eb0,zddd8dacb98,TM,z448b491306,z1da9017839,zdf24515981}z9b42a7026b;
#define ze13f49a01f     ssGetSFcnParam(S, zfaa050b79d     )
#define za9d8fb6bcf       ssGetSFcnParam(S, CHANNEL       )
#define z3832b85a32     ssGetSFcnParam(S, ze344b15ab1     )
#define zf65a5b6411     ssGetSFcnParam(S, zd3ea823cae     )
#define z544191c318            ssGetSFcnParam(S, z7c1ba57595            )
#define z3273efc6eb  ssGetSFcnParam(S, zc3aa9f6eb0  )
#define zf0ff66802e      ssGetSFcnParam(S, zddd8dacb98      )
#define z6ee4a37819            ssGetSFcnParam(S, TM            )
#define zd9a5e71785            ssGetSFcnParam(S, z448b491306            )
#define z45bd0c2296          ssGetSFcnParam(S, z1da9017839          )
#define zc3abbe7eb0 (0x1738+3849-0x2611)
enum zbb1f615c1d{zf188deb2ac,z3250bb2679};enum z93bcf30780{z8a85396f5b};enum zb06a9f15ae{z00deac365e,z9cbfedf63b};
#define z5bbcf8be2c          (0x662+8081-0x25f2)
enum z27dce6945f{z017eafc8e7=(0x6d9+4636-0x18ee),z1bdb5475e3=(0xff7+3067-0x1be4),za0025817ff=(0x1d7b+379-0x1eda),z44434285f4=(0x221+7503-0x1f4d),zf8b38fdc22=(0x736+1570-0xd2e),za870d43c64=(0x3bf+1353-0x8f3),zf5f9a4b551=(0x198d+3048-0x2544),z1209f5d6ff=(0x6ef+1369-0xc10),z1cf42ca33f=(0x1174+2695-0x1bf2),zf022f0025c=(0xdd5+6025-0x2543),z2d518d8bbe=(0x2c0+3414-0xff2),z47e41ac44f=(0xb53+548-0xd4a),z0c91ffb2ea=(0x96a+3376-0x1664),za515f21bce=(0xeb0+3469-0x1c2b)};static char_T msg[(0x3e7+3763-0x119a)];typedef volatile struct{uint32_t z4a2f10bfe9[(0x85+2742-0xb1b)];uint32_t z225993a4e1[(0x1bf+5360-0x168f)];uint32_t z1d311fe91a[(0x11ad+3710-0x200b)];uint32_t z2924592fb2[(0x1b00+891-0x1e5b)];uint32_t z6d065ec30a[(0x366+6055-0x1aed)];uint32_t z6db80e269f[(0xe84+3519-0x1c23)];uint32_t tm[(0x2239+1238-0x26ef)];uint32_t z3d1bc9ceb1[(0x367+2631-0xd8e)];uint32_t z7cb9b03ff3[(0xaf9+3971-0x1a5c)];uint32_t z97287efa46;uint32_t zeeeba54a90;uint32_t version;uint32_t test1;uint32_t test2;uint32_t zd6bcfb237b;}z1c26c1bb11;static void mdlInitializeSizes(SimStruct*S){uint32_t i,zbc7ebd0e53,zde2210a484;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73" "\n" "\x20\x70\x61\x73\x73\x65\x64\x3a\x20\x25\x64" "\n" "\x20\x65\x78\x70\x65\x63\x74\x65\x64\x3a\x20\x25\x64" "\n",ssGetSFcnParamsCount(S),ssGetNumSFcnParams(S));ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x1b97+2318-0x24a5));ssSetNumDiscStates(S,(0xb71+4889-0x1e8a));zde2210a484=(uint32_t)mxGetN(za9d8fb6bcf);zbc7ebd0e53=(0x212+541-0x42d);ssSetNumInputPorts(S,zbc7ebd0e53);for(i=(0xfed+2582-0x1a03);i<zbc7ebd0e53;i++){ssSetInputPortDataType(S,i,SS_UINT32);ssSetInputPortWidth(S,i,zde2210a484);ssSetInputPortDirectFeedThrough(S,i,(0x1303+1128-0x176a));ssSetInputPortRequiredContiguous(S,i,(0xf3+3975-0x1079));}ssSetNumOutputPorts(S,(0x8cd+7590-0x2673));ssSetNumSampleTimes(S,(0x1178+2086-0x199d));ssSetNumRWork(S,z8a85396f5b);ssSetNumIWork(S,z3250bb2679);ssSetNumPWork(S,z9cbfedf63b);ssSetNumModes(S,(0xdcd+2855-0x18f4));ssSetNumNonsampledZCs(S,(0x24d8+366-0x2646));for(i=(0x101b+1488-0x15eb);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x1997+1286-0x1e9d));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE|SS_OPTION_PLACE_ASAP);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x15db+2005-0x1db0)]==-1.0){ssSetSampleTime(S,(0x337+4524-0x14e3),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0xb37+732-0xe13),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x245a+410-0x25f4),mxGetPr(z3832b85a32)[(0x1e0+4621-0x13ed)]);ssSetOffsetTime(S,(0xe1+7080-0x1c89),0.0);}}static void sg_ModelLoad(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uintptr_t z70fcda5f5d;int moduleId=(int)mxGetScalar(ze13f49a01f);char*boardName=io3xxGetBoardNameSgLib(moduleId);z1c26c1bb11*z5e695a7fd7;z70fcda5f5d=(uintptr_t)io3xxGetAddressSgLib((int)mxGetPr(ze13f49a01f)[(0x1b60+2757-0x2625)],SG_FPGA_IO3XX_BAR2);if(z70fcda5f5d==(0x1012+2418-0x1984)){ssSetErrorStatus(S,pSgErrorStr);return;}uint32_t zf7ccd17be8=(0x1da7+2123-0x25f2);if(sg_fpga_io3xx_getCmBaseAddress(moduleId,ENDAT_ENCODER_BASE,&zf7ccd17be8)){sprintf(msg,"\x25\x73\x20\x45\x6e\x64\x61\x74\x20\x45\x6e\x63\x6f\x64\x65\x72\x20\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x4f\x66\x66\x73\x65\x74\x20\x6c\x6f\x6f\x6b\x75\x70\x20\x75\x6e\x73\x75\x63\x63\x65\x73\x73\x66\x75\x6c\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}z5e695a7fd7=(z1c26c1bb11*)(z70fcda5f5d+zf7ccd17be8);ssSetPWorkValue(S,z00deac365e,(void*)z5e695a7fd7);if(sg_isFirstModelLoad()){if(sg_fpga_io3xx_checkCodeModuleVersion(z5e695a7fd7->version,z5bbcf8be2c,moduleId)){sprintf(msg,"\x25\x73\x20\x77\x72\x6f\x6e\x67\x20\x76\x65\x72\x73\x69\x6f\x6e\x20\x6f\x66\x20\x45\x6e\x64\x61\x74\x45\x6e\x63\x6f\x64\x65\x72\x20\x63\x6f\x64\x65\x20\x6d\x6f\x64\x75\x6c\x65\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}}
#endif
}static void sg_ModelStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
z1c26c1bb11*z5e695a7fd7=(z1c26c1bb11*)ssGetPWorkValue(S,z00deac365e);uint32_t i,channel;z5e695a7fd7->zd6bcfb237b=4294967295;z5e695a7fd7->zd6bcfb237b=(0x1080+1731-0x1743);for(i=(0x1619+1174-0x1aaf);i<(uint32_t)mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x5a7+3163-0x1201);z5e695a7fd7->z4a2f10bfe9[channel]=(uint32_t)mxGetPr(zf65a5b6411)[i];z5e695a7fd7->z2924592fb2[channel]=(uint32_t)mxGetPr(z544191c318)[i];z5e695a7fd7->z6d065ec30a[channel]=(uint32_t)mxGetPr(z3273efc6eb)[i]+(uint32_t)mxGetPr(zf0ff66802e)[i];z5e695a7fd7->z6db80e269f[channel]=(uint32_t)mxGetPr(zf0ff66802e)[i];z5e695a7fd7->tm[channel]=(uint32_t)mxGetPr(z6ee4a37819)[i];z5e695a7fd7->z3d1bc9ceb1[channel]=(uint32_t)mxGetPr(zd9a5e71785)[i];z5e695a7fd7->z7cb9b03ff3[channel]=(uint32_t)mxGetPr(z45bd0c2296)[i];}
#endif
}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
int i,channel;z1c26c1bb11*z5e695a7fd7=(z1c26c1bb11*)ssGetPWorkValue(S,z00deac365e);uint32_t*zc69dafe0e2;uint32_t*z0f91b2425e;zc69dafe0e2=(uint32_t*)ssGetInputPortSignal(S,(0x1d6+5570-0x1798));z0f91b2425e=(uint32_t*)ssGetInputPortSignal(S,(0x1eda+1810-0x25eb));for(i=(0x689+6286-0x1f17);i<(uint32_t)mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0xd9b+1242-0x1274);z5e695a7fd7->z1d311fe91a[channel]=zc69dafe0e2[i];z5e695a7fd7->z225993a4e1[channel]=z0f91b2425e[i];}
#endif
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE
z1c26c1bb11*z5e695a7fd7=(z1c26c1bb11*)ssGetPWorkValue(S,z00deac365e);z5e695a7fd7->zd6bcfb237b=4294967295;z5e695a7fd7->zd6bcfb237b=(0x13b8+108-0x1424);
#endif
}
#include "sg_sfcn_glue.h"   

