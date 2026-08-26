// Copyright 2006-2026 Speedgoat GmbH

#define   S_FUNCTION_LEVEL  (0xdc0+4435-0x1f11)
#undef    S_FUNCTION_NAME
#define   S_FUNCTION_NAME   sg_fpga_endat_sniffer_sf_1
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
typedef enum{zfaa050b79d,CHANNEL,ze344b15ab1,ze2eddeec2f,zc3aa9f6eb0,zc81faee503,z75ba243455,z90c65c39fe,zdf24515981}z9b6f228a71;
#define ze13f49a01f         ssGetSFcnParam(S,  zfaa050b79d)
#define za9d8fb6bcf           ssGetSFcnParam(S,  CHANNEL)
#define z3832b85a32         ssGetSFcnParam(S,  ze344b15ab1)
#define z4d50d51381            ssGetSFcnParam(S,  ze2eddeec2f)
#define z3273efc6eb      ssGetSFcnParam(S,  zc3aa9f6eb0)
#define ze98ad4a472           ssGetSFcnParam(S,  zc81faee503)
#define z837907708e   ssGetSFcnParam(S,  z75ba243455)
#define z1272ff95a8    ssGetSFcnParam(S,  z90c65c39fe)
#define zc3abbe7eb0 (0xb8b+6420-0x246f)
enum zbb1f615c1d{z3250bb2679};enum z93bcf30780{z8a85396f5b};enum zb06a9f15ae{z00deac365e,z9cbfedf63b};
#define z5bbcf8be2c          ((0x812+5234-0x1c83))
enum z27dce6945f{z017eafc8e7=(0x60d+7851-0x24b1),z1bdb5475e3=(0x15df+3278-0x229f),za0025817ff=(0x1625+1545-0x1c12),z44434285f4=(0xcb0+536-0xea5),zf8b38fdc22=(0xdc+8795-0x230d),za870d43c64=(0x1415+472-0x15d8),zf5f9a4b551=(0x1549+3566-0x2306),z1209f5d6ff=(0x1dea+216-0x1e8a),z1cf42ca33f=(0x1a6c+1034-0x1e6d),zf022f0025c=(0xafb+4546-0x1ca2),z2d518d8bbe=(0xa34+1269-0xf05),z47e41ac44f=(0x1161+12-0x1140),z0c91ffb2ea=(0x524+3195-0x1169),za515f21bce=(0x5e9+1144-0xa4f)};static char_T msg[(0x118c+5389-0x2599)];typedef volatile struct{uint32_t z6c0009ff13[(0xb6c+4355-0x1c4f)];uint32_t z6d065ec30a[(0xe57+2268-0x1713)];uint32_t z6db80e269f[(0xdc3+2406-0x1709)];uint32_t zacb9d9140d[(0x1f6d+1446-0x24f3)];uint32_t z3884ceefa0[(0xf69+3784-0x1e11)];uint32_t error[(0x1c1a+340-0x1d4e)];uint32_t version;uint32_t zd6bcfb237b;}z91da7e14e8;static void mdlInitializeSizes(SimStruct*S){uint32_t i,zbc7ebd0e53,zde2210a484;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73" "\n" "\x20\x70\x61\x73\x73\x65\x64\x3a\x20\x25\x64" "\n" "\x20\x65\x78\x70\x65\x63\x74\x65\x64\x3a\x20\x25\x64" "\n",ssGetSFcnParamsCount(S),ssGetNumSFcnParams(S));ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x406+1801-0xb0f));ssSetNumDiscStates(S,(0x9e7+396-0xb73));ssSetNumInputPorts(S,(0x1b17+653-0x1da4));zbc7ebd0e53=(0x12f2+2808-0x1de9);if((uint32_t)mxGetPr(z1272ff95a8)[(0x1b4d+1639-0x21b4)]){zbc7ebd0e53+=(0xaa2+6531-0x2422);}if((uint32_t)mxGetPr(z837907708e)[(0x195f+3237-0x2604)]){zbc7ebd0e53+=(0x13f+3640-0xf76);}zde2210a484=(uint32_t)mxGetN(za9d8fb6bcf);ssSetNumOutputPorts(S,zbc7ebd0e53);for(i=(0x405+8308-0x2479);i<zbc7ebd0e53;i++){ssSetOutputPortDataType(S,i,SS_UINT32);ssSetOutputPortWidth(S,i,zde2210a484);}ssSetNumSampleTimes(S,(0x11fc+2122-0x1a45));ssSetNumRWork(S,z8a85396f5b);ssSetNumIWork(S,z3250bb2679);ssSetNumPWork(S,z9cbfedf63b);ssSetNumModes(S,(0x0+5731-0x1663));ssSetNumNonsampledZCs(S,(0x15dd+2856-0x2105));for(i=(0x4e6+7035-0x2061);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0xc8+5234-0x153a));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x42f+4325-0x1514)]==-1.0){ssSetSampleTime(S,(0xf3b+841-0x1284),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x762+3446-0x14d8),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0xc1f+5101-0x200c),mxGetPr(z3832b85a32)[(0x6fb+5702-0x1d41)]);ssSetOffsetTime(S,(0x62a+5956-0x1d6e),0.0);}}static void sg_ModelLoad(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uintptr_t z70fcda5f5d;int moduleId=(int)mxGetScalar(ze13f49a01f);char*boardName=io3xxGetBoardNameSgLib(moduleId);z91da7e14e8*z2d44fbf165;z70fcda5f5d=(uintptr_t)io3xxGetAddressSgLib((int)mxGetPr(ze13f49a01f)[(0x1404+304-0x1534)],SG_FPGA_IO3XX_BAR2);if(z70fcda5f5d==(0x128d+2297-0x1b86)){ssSetErrorStatus(S,pSgErrorStr);return;}uint32_t zf7ccd17be8=(0x7ec+5831-0x1eb3);if(sg_fpga_io3xx_getCmBaseAddress(moduleId,ENDAT_SNIFFER_BASE,&zf7ccd17be8)){sprintf(msg,"\x25\x73\x20\x45\x6e\x64\x61\x74\x20\x53\x6e\x69\x66\x66\x65\x72\x20\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x4f\x66\x66\x73\x65\x74\x20\x6c\x6f\x6f\x6b\x75\x70\x20\x75\x6e\x73\x75\x63\x63\x65\x73\x73\x66\x75\x6c\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}z2d44fbf165=(z91da7e14e8*)(z70fcda5f5d+zf7ccd17be8);ssSetPWorkValue(S,z00deac365e,(void*)z2d44fbf165);if(sg_isFirstModelLoad()){if(sg_fpga_io3xx_checkCodeModuleVersion(z2d44fbf165->version,z5bbcf8be2c,moduleId)){sprintf(msg,"\x25\x73\x20\x77\x72\x6f\x6e\x67\x20\x76\x65\x72\x73\x69\x6f\x6e\x20\x6f\x66\x20\x45\x6e\x64\x61\x74\x53\x6e\x69\x66\x66\x65\x72\x20\x63\x6f\x64\x65\x20\x6d\x6f\x64\x75\x6c\x65\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}}
#endif
}static void sg_ModelStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
z91da7e14e8*z2d44fbf165=(z91da7e14e8*)ssGetPWorkValue(S,z00deac365e);uint32_t i,channel;for(i=(0x52d+7285-0x21a2);i<(uint32_t)mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x1224+3635-0x2056);z2d44fbf165->z6c0009ff13[channel]=(uint32_t)mxGetPr(z4d50d51381)[i];z2d44fbf165->z6d065ec30a[channel]=(uint32_t)mxGetPr(z3273efc6eb)[i]+(uint32_t)mxGetPr(ze98ad4a472)[i];z2d44fbf165->z6db80e269f[channel]=(uint32_t)mxGetPr(ze98ad4a472)[i];}
#endif
}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
int i,channel;z91da7e14e8*z2d44fbf165=(z91da7e14e8*)ssGetPWorkValue(S,z00deac365e);uint32_t*z6eb2d4d8b7=NULL;uint32_t*z907a1f4c6a=NULL;uint32_t*z0e0892c1c0=NULL;uint32_t*z4865974c9b=NULL;uint32_t*z1312a42048=NULL;uint8_t zfb0d8e35a1;uint32_t z407efd0741;uint32_t z4334ea8c38=(0xcc+7752-0x1f14);uint32_t z9f43637a3a;zfb0d8e35a1=(uint32_t)mxGetPr(z1272ff95a8)[(0x243+8330-0x22cd)];z6eb2d4d8b7=(uint32_t*)ssGetOutputPortSignal(S,(0x1890+3150-0x24de));if((uint32_t)mxGetPr(z1272ff95a8)[(0xa95+506-0xc8f)]){z907a1f4c6a=(uint32_t*)ssGetOutputPortSignal(S,(0xf81+3332-0x1c84));z0e0892c1c0=(uint32_t*)ssGetOutputPortSignal(S,(0xc7a+4147-0x1cab));z4865974c9b=(uint32_t*)ssGetOutputPortSignal(S,(0x1899+115-0x1909));if((uint32_t)mxGetPr(z837907708e)[(0x9ed+4928-0x1d2d)]){z1312a42048=(uint32_t*)ssGetOutputPortSignal(S,(0x59a+6928-0x20a6));}}else{if((uint32_t)mxGetPr(z837907708e)[(0x421+8657-0x25f2)]){z1312a42048=(uint32_t*)ssGetOutputPortSignal(S,(0xc5+798-0x3e2));}}for(i=(0x136+5956-0x187a);i<(uint32_t)mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x11ed+5115-0x25e7);z407efd0741=z2d44fbf165->zacb9d9140d[channel];z6eb2d4d8b7[i]=z407efd0741;if(zfb0d8e35a1==(0xc4+6301-0x1960)){z4334ea8c38=z2d44fbf165->z3884ceefa0[channel];}if((uint32_t)mxGetPr(z1272ff95a8)[(0x1a79+931-0x1e1c)]){z0e0892c1c0[i]=z4334ea8c38;z907a1f4c6a[i]=(uint32_t)mxGetPr(z3273efc6eb)[i];z4865974c9b[i]=(uint32_t)mxGetPr(ze98ad4a472)[i];}if((uint32_t)mxGetPr(z837907708e)[(0x89+317-0x1c6)]){z9f43637a3a=z2d44fbf165->error[channel];z1312a42048[i]=z9f43637a3a;}}
#endif
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE
z91da7e14e8*z2d44fbf165=(z91da7e14e8*)ssGetPWorkValue(S,z00deac365e);z2d44fbf165->zd6bcfb237b=4294967295;z2d44fbf165->zd6bcfb237b=(0x8ca+6588-0x2286);
#endif
}
#include "sg_sfcn_glue.h"   

