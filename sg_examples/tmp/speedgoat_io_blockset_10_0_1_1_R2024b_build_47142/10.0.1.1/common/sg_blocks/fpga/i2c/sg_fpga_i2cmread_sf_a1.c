// Copyright 2006-2026 Speedgoat GmbH

#define 	S_FUNCTION_LEVEL 	(0x9a+3186-0xd0a)
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_fpga_i2cmread_sf_a1
#include 	<stddef.h>
#include 	<stdlib.h>
#include    <stdint.h>
#include 	"simstruc.h"
#ifdef 		MATLAB_MEX_FILE
#include 	"mex.h"
#endif
#ifndef     MATLAB_MEX_FILE
#include    "sg_common.h"
#include    "sg_fpga_io3xx_util.h"
#include    "sg_printf.h"
#endif
#include    "sg_callback.h"
#define ze13f49a01f           ssGetSFcnParam(S, (0x102+1170-0x594)) 
#define za9d8fb6bcf             ssGetSFcnParam(S, (0x8a+8102-0x202f)) 
#define zf5ee62a4ad        ssGetSFcnParam(S, (0x674+4813-0x193f))
#define zdcecd118d0       ssGetSFcnParam(S, (0xa96+3881-0x19bc))
#define z8ba84e2285         ssGetSFcnParam(S, (0x4c2+8419-0x25a1))
#define zb0929cb988   ssGetSFcnParam(S, (0x1381+3720-0x2204))
#define z3832b85a32           ssGetSFcnParam(S, (0xd83+1822-0x149b))
#define z6c2191f017           ssGetSFcnParam(S, (0x1a05+1014-0x1df4))
#define zdf24515981                          ((0x269+4636-0x147d))
#define z2e6483d505              ((0x3b7+5187-0x17fa))
#define zc5ce4cb81a              ((0x997+3132-0x15d3))
#define z2b17e2ee3b              ((0x1edb+1166-0x2367))
#define z0194338df7         ((0x12b2+4042-0x227c))
#define z9bd75cedb3         ((0xfb7+451-0x1179))
#define z5bbcf8be2c            (0x64a+6756-0x20ad)
static char_T msg[(0x15f7+4484-0x267b)];typedef struct{uint32_t start;uint32_t clear;uint32_t nTX_RX;uint32_t z21ab44ce3e;uint32_t count[(0x2011+607-0x2250)];uint32_t z28e9d9261f[(0x4d8+5152-0x18d8)];uint32_t z1fe5bfccaf[(0x104c+710-0x12f2)];uint32_t z627a05d850[(0x22a+2204-0xaa6)];uint32_t z94328689b6[(0xa32+3428-0x1776)];uint32_t z039626e71b[(0x85c+6501-0x21a1)];uint32_t EOT;uint32_t zdca56d3a3a;uint32_t version;}z71f90c95f9;static void mdlInitializeSizes(SimStruct*S){uint32_t i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x93f+3867-0x185a));ssSetNumDiscStates(S,(0x16c3+317-0x1800));if((uint32_t)mxGetPr(zb0929cb988)[(0x7e0+2906-0x133a)]){if(!ssSetNumOutputPorts(S,(0x875+5983-0x1fd2))){return;}ssSetOutputPortWidth(S,(0xe83+3581-0x1c80),(uint32_t)mxGetPr(z8ba84e2285)[(0x150d+672-0x17ad)]);ssSetOutputPortDataType(S,(0x137c+315-0x14b6),SS_BOOLEAN);ssSetOutputPortWidth(S,(0x295+5118-0x1692),(0xb4c+4920-0x1e83));}else{if(!ssSetNumOutputPorts(S,(0x146+5062-0x150b))){return;}ssSetOutputPortWidth(S,(0x324+1270-0x81a),(uint32_t)mxGetPr(z8ba84e2285)[(0x20bc+33-0x20dd)]);}if((uint32_t)mxGetPr(zdcecd118d0)[(0xf12+2490-0x18cc)]){if(!ssSetNumInputPorts(S,(0x118a+5412-0x26ab))){return;}ssSetInputPortWidth(S,(0x167f+2187-0x1f0a),(0x13c+8977-0x244c));ssSetInputPortDirectFeedThrough(S,(0x4b8+2588-0xed4),(0x46+2299-0x940));ssSetInputPortRequiredContiguous(S,(0xed8+3424-0x1c38),(0x75a+3090-0x136b));ssSetInputPortWidth(S,(0x1b8b+1753-0x2263),(0x5b+5491-0x15cd));ssSetInputPortDirectFeedThrough(S,(0xdcc+2886-0x1911),(0x16d1+2684-0x214c));ssSetInputPortRequiredContiguous(S,(0x9e1+5504-0x1f60),(0x5da+3683-0x143c));ssSetInputPortWidth(S,(0x7c+6469-0x19bf),(0xa9b+615-0xd01));ssSetInputPortDirectFeedThrough(S,(0x2120+598-0x2374),(0x15f1+2486-0x1fa6));ssSetInputPortRequiredContiguous(S,(0x5c2+5454-0x1b0e),(0x11e9+3298-0x1eca));}else{if(!ssSetNumInputPorts(S,(0x203b+369-0x21aa))){return;}ssSetInputPortWidth(S,(0xff1+711-0x12b8),(0x10f4+3706-0x1f6d));ssSetInputPortDirectFeedThrough(S,(0x181+659-0x414),(0x516+1684-0xba9));ssSetInputPortRequiredContiguous(S,(0xc69+222-0xd47),(0x475+3271-0x113b));ssSetInputPortWidth(S,(0xde1+6405-0x26e5),(0xfb0+1065-0x13d8));ssSetInputPortDirectFeedThrough(S,(0xbfd+2950-0x1782),(0xfb4+830-0x12f1));ssSetInputPortRequiredContiguous(S,(0xde3+2719-0x1881),(0x842+5899-0x1f4c));}ssSetNumSampleTimes(S,(0x4f+1274-0x548));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0xc7f+936-0x1027));ssSetNumNonsampledZCs(S,(0x22cc+745-0x25b5));for(i=(0xa6d+31-0xa8c);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x704+10-0x70e));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x12f8+1932-0x1a84)]==-1.0){ssSetSampleTime(S,(0x219+4374-0x132f),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x135+1105-0x586),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x1567+4019-0x251a),mxGetPr(z3832b85a32)[(0x8a9+2938-0x1423)]);ssSetOffsetTime(S,(0x388+5321-0x1851),0.0);}}static void sg_ModelLoad(SimStruct*S){
#ifndef MATLAB_MEX_FILE
volatile z71f90c95f9*zca56c6316b;i2cState_t*z48b6195cd9;int moduleId=(int)mxGetScalar(ze13f49a01f);char*boardName=io3xxGetBoardNameSgLib(moduleId);if(!io3xxGetAddressSgLib((int32_t)(int)mxGetPr(ze13f49a01f)[(0x9a+8554-0x2204)],SG_FPGA_IO3XX_BAR2)){ssSetErrorStatus(S,pSgErrorStr);return;}uint32_t zf7ccd17be8=(0x62b+4962-0x198d);if(sg_fpga_io3xx_getCmBaseAddress(moduleId,I2CM_BASE,&zf7ccd17be8)){sprintf(msg,"\x25\x73\x20\x49\x32\x43\x4d\x20\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x4f\x66\x66\x73\x65\x74\x20\x6c\x6f\x6f\x6b\x75\x70\x20\x75\x6e\x73\x75\x63\x63\x65\x73\x73\x66\x75\x6c\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}zca56c6316b=(volatile z71f90c95f9*)((uintptr_t)io3xxGetAddressSgLib((int32_t)(int)mxGetPr(ze13f49a01f)[(0x2257+473-0x2430)],SG_FPGA_IO3XX_BAR2)+zf7ccd17be8);ssSetPWorkValue(S,z0194338df7,(void*)zca56c6316b);if(sg_fpga_io3xx_checkCodeModuleVersion(zca56c6316b->version,z5bbcf8be2c,moduleId)){sprintf(msg,"\x25\x73\x20\x77\x72\x6f\x6e\x67\x20\x76\x65\x72\x73\x69\x6f\x6e\x20\x6f\x66\x20\x49\x32\x43\x4d\x20\x63\x6f\x64\x65\x20\x6d\x6f\x64\x75\x6c\x65\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}io3xxGetPointerI2cStateSgLib((int)mxGetPr(ze13f49a01f)[(0x85+3151-0xcd4)],&z48b6195cd9);ssSetPWorkValue(S,z9bd75cedb3,(void*)z48b6195cd9);
#endif
}static void sg_ModelStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_t channel;volatile z71f90c95f9*zca56c6316b=(volatile z71f90c95f9*)ssGetPWorkValue(S,z0194338df7);channel=(uint32_t)mxGetPr(za9d8fb6bcf)[(0x842+2432-0x11c2)]-(0x40f+3169-0x106f);zca56c6316b->z28e9d9261f[channel]=(uint32_t)mxGetPr(zf5ee62a4ad)[(0x1535+498-0x1727)];
#endif
}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_t i,channel;real_T*z039626e71b,*count,*za2cbad8e67,*ze769fc7d2c;boolean_T*out;volatile z71f90c95f9*zca56c6316b=(volatile z71f90c95f9*)ssGetPWorkValue(S,z0194338df7);i2cState_t*z48b6195cd9=(i2cState_t*)ssGetPWorkValue(S,z9bd75cedb3);channel=(uint32_t)mxGetPr(za9d8fb6bcf)[(0x1018+4278-0x20ce)]-(0x2d+686-0x2da);z039626e71b=(real_T*)ssGetInputPortSignal(S,(0x889+7189-0x249e));zca56c6316b->z039626e71b[channel]=(uint32_t)z039626e71b[(0xcb2+5203-0x2105)];if(mxGetPr(zdcecd118d0)[(0x8eb+1212-0xda7)]){while(!(zca56c6316b->EOT&(1UL<<channel))){}za2cbad8e67=(real_T*)ssGetInputPortSignal(S,(0xcf2+2616-0x1728));zca56c6316b->z1fe5bfccaf[channel]=(0x1c4+1029-0x5c9);zca56c6316b->z627a05d850[channel]=(uint32_t)za2cbad8e67[(0x93d+5555-0x1ef0)];zca56c6316b->z21ab44ce3e=(1UL<<channel);zca56c6316b->z21ab44ce3e=(0x95f+228-0xa43);zca56c6316b->count[channel]=(0x9a7+1819-0x10c1);sg_lockMutex(z48b6195cd9->mutex);z48b6195cd9->nTX_RX&=~(1UL<<channel);zca56c6316b->nTX_RX=z48b6195cd9->nTX_RX;z48b6195cd9->start|=(1UL<<channel);zca56c6316b->start=z48b6195cd9->start;sg_unlockMutex(z48b6195cd9->mutex);}while(!(zca56c6316b->EOT&(1UL<<channel))){}count=(real_T*)ssGetInputPortSignal(S,(0x733+5029-0x1ad7));zca56c6316b->count[channel]=(uint32_t)count[(0xad4+4799-0x1d93)];sg_lockMutex(z48b6195cd9->mutex);z48b6195cd9->start&=~(1UL<<channel);z48b6195cd9->nTX_RX|=(1UL<<channel);zca56c6316b->start=z48b6195cd9->start;zca56c6316b->nTX_RX=z48b6195cd9->nTX_RX;zca56c6316b->start=(z48b6195cd9->start|(1UL<<channel));zca56c6316b->start=z48b6195cd9->start;sg_unlockMutex(z48b6195cd9->mutex);if(!(uint32_t)mxGetPr(z6c2191f017)[(0x276+1199-0x725)]){while(!(zca56c6316b->EOT&(1UL<<channel))){}}ze769fc7d2c=(real_T*)ssGetOutputPortSignal(S,(0x9a7+4200-0x1a0f));for(i=(0x4f9+6025-0x1c82);i<(0x21c6+1052-0x25a2);i++){ze769fc7d2c[i]=(0xe07+3914-0x1d51);}for(i=(0xaed+4414-0x1c2b);i<count[(0x492+1236-0x966)];i++){zca56c6316b->z1fe5bfccaf[channel]=(uint32_t)i;ze769fc7d2c[i]=zca56c6316b->z94328689b6[channel];}if((uint32_t)mxGetPr(zb0929cb988)[(0xa57+3399-0x179e)]){out=(boolean_T*)ssGetOutputPortSignal(S,(0x1ec8+2071-0x26de));out[(0x1832+2041-0x202b)]=((zca56c6316b->zdca56d3a3a)>>(channel))&(0xd15+4089-0x1d0d);}
#endif
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE
#endif
}
#include "sg_sfcn_glue.h"   

