// Copyright 2006-2026 Speedgoat GmbH

#define 	S_FUNCTION_LEVEL 	(0x9a2+7143-0x2587)
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_fpga_pwm_sf_a3
#include 	<stddef.h>
#include 	<stdlib.h>
#include  <stdint.h>
#include 	"simstruc.h" 
#ifdef 		MATLAB_MEX_FILE
#include 	"mex.h"
#endif
#ifndef         MATLAB_MEX_FILE
#include        "sg_common.h"
#include        "sg_fpga_io3xx_util.h"
#include        "sg_callback_legacy.h"
#include        "sg_printf.h"
#endif
#define zdf24515981        ((0x1502+3429-0x2257))
#define z533b11d03f         ssGetSFcnParam(S, (0x1db1+1287-0x22b8)) 
#define ze13f49a01f         ssGetSFcnParam(S, (0x792+1069-0xbbe)) 
#define za9d8fb6bcf           ssGetSFcnParam(S, (0x414+3808-0x12f2))
#define z01bb085356         ssGetSFcnParam(S, (0xc3a+5256-0x20bf))
#define zc74c85e681           ssGetSFcnParam(S, (0x1009+1771-0x16f0))
#define z311fbc5bad           ssGetSFcnParam(S, (0x139+6876-0x1c10))
#define za04af20061           ssGetSFcnParam(S, (0x1dc1+800-0x20db))
#define za9b36fc92d            ssGetSFcnParam(S, (0x239+9030-0x2578))
#define zfde61350f8     ssGetSFcnParam(S, (0xc5+9194-0x24a7))
#define zeac6896859        ssGetSFcnParam(S, (0x18ba+1555-0x1ec4))
#define z2dceaadc0f         ssGetSFcnParam(S, (0xb1+1802-0x7b1))
#define z4eb7791e75     ssGetSFcnParam(S, (0x1467+2284-0x1d48))
#define z502d9ed0cf             ssGetSFcnParam(S, (0xa33+3008-0x15e7))
#define z1918c3f4db             ssGetSFcnParam(S, (0xf07+5325-0x23c7))
#define z3832b85a32         ssGetSFcnParam(S, (0x6a9+5895-0x1da2))
#define z702a26a5e9              ssGetSFcnParam(S, (0x413+8436-0x24f8))
#define z2e6483d505              ((0x13d+2736-0xbed))
#define zc5ce4cb81a              ((0xefa+2916-0x1a5e))
#define z2b17e2ee3b              ((0x774+4479-0x18f2))
#define z93d7dbe681         ((0xc3f+3785-0x1b08))
#define zf2a9add7f9              (98304)
static char_T msg[(0x143+3400-0xd8b)];typedef struct{uint32_t enable;uint32_t update;uint32_t z8db8bb5a06;uint32_t zee8378496a;uint32_t z37cfa98aaf;uint32_t ze7198b4532;uint32_t zba6c56af50;uint32_t zf30711d604[(0xaf2+3674-0x192c)];uint32_t z6756646a81[(0x66+8936-0x232e)];uint32_t z9ca0045836[(0x280+1367-0x7b7)];uint32_t z8e8b32e98e[(0x1e03+2289-0x26d4)];uint32_t z886a62b902[(0x43a+3574-0x1210)];uint32_t protection[(0x1453+1978-0x1bed)];uint32_t z7211d763fb[(0x1b56+433-0x1ce7)];uint32_t z64b63d5c98[(0xdf0+4453-0x1f35)];uint32_t z3144e9a755[(0xb34+270-0xc22)];}z8dc61d99bb;static void mdlInitializeSizes(SimStruct*S){uint32_t i,zbc7ebd0e53,width;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x826+1173-0xcbb));ssSetNumDiscStates(S,(0x1057+2162-0x18c9));width=(uint32_t)mxGetN(za9d8fb6bcf);zbc7ebd0e53=(0x529+866-0x88b);if((uint32_t)mxGetPr(z01bb085356)[(0x9a5+745-0xc8e)]==(0x9c0+4659-0x1bf2)){zbc7ebd0e53=(0xc56+1918-0x13d2);}else{zbc7ebd0e53=(0xefa+5490-0x2468);}ssSetNumInputPorts(S,zbc7ebd0e53);for(i=(0x953+5918-0x2071);i<zbc7ebd0e53;i++){ssSetInputPortWidth(S,i,width);ssSetInputPortDirectFeedThrough(S,i,(0x243+2103-0xa79));ssSetInputPortRequiredContiguous(S,i,(0x21b+2491-0xbd5));}ssSetNumOutputPorts(S,(0x4f0+3002-0x10aa));ssSetNumSampleTimes(S,(0x1b78+569-0x1db0));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x182c+2157-0x2099));ssSetNumNonsampledZCs(S,(0x125b+372-0x13cf));for(i=(0x14d5+1359-0x1a24);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0xfd+5686-0x1733));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x1105+2128-0x1955)]==-1.0){ssSetSampleTime(S,(0x1c23+2472-0x25cb),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x5a7+2057-0xdb0),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0xe87+4801-0x2148),mxGetPr(z3832b85a32)[(0x14cc+1221-0x1991)]);ssSetOffsetTime(S,(0x1487+3998-0x2425),0.0);}}
#define MDL_START
static void mdlStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
int32_t bus,slot;uint32_t i,channel,enable,z8db8bb5a06,zee8378496a,z37cfa98aaf;volatile z8dc61d99bb*z9e95a8730f;sg_fpga_io3xxModuleIdT moduleId;uint32_t boardType;void*bar2ptr;boardType=(uint32_t)mxGetPr(z533b11d03f)[(0x172b+3893-0x2660)];if((int32_t)sg_fpga_IO3xxGetModuleId(boardType,&moduleId)<(0x1f8+550-0x41e)){sprintf(msg,"\x70\x77\x6d\x28\x33\x29\x20\x62\x6c\x6f\x63\x6b\x3a\x20\x62\x6f\x61\x72\x64\x20\x74\x79\x70\x65\x20\x69\x6e\x63\x6f\x72\x72\x65\x63\x74\x2e");ssSetErrorStatus(S,msg);}if(mxGetN(z702a26a5e9)==(0x7ec+6644-0x21df)){bus=(0x8c9+414-0xa67);slot=(int_T)mxGetPr(z702a26a5e9)[(0x6d1+5097-0x1aba)];}else{bus=(int_T)mxGetPr(z702a26a5e9)[(0x205d+1693-0x26fa)];slot=(int_T)mxGetPr(z702a26a5e9)[(0x811+4513-0x19b1)];}if(!io3xxGetAddressSgLib((int32_t)(int)mxGetPr(ze13f49a01f)[(0x12d1+2456-0x1c69)],SG_FPGA_IO3XX_BAR2)){ssSetErrorStatus(S,pSgErrorStr);return;}bar2ptr=io3xxGetAddressSgLib((int32_t)(int)mxGetPr(ze13f49a01f)[(0x1078+1671-0x16ff)],SG_FPGA_IO3XX_BAR2);ssSetPWorkValue(S,z93d7dbe681,(void*)bar2ptr);z9e95a8730f=(z8dc61d99bb*)((uintptr_t)bar2ptr+zf2a9add7f9);if(!sg_isModelInit()){enable=z9e95a8730f->enable;z8db8bb5a06=z9e95a8730f->z8db8bb5a06;zee8378496a=z9e95a8730f->zee8378496a;z37cfa98aaf=z9e95a8730f->z37cfa98aaf;for(i=(0x20d+8243-0x2240);i<(uint32_t)mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x14a4+1868-0x1bef);z9e95a8730f->zf30711d604[channel]=(uint32_t)mxGetPr(za9b36fc92d)[i];z9e95a8730f->z3144e9a755[channel]=(uint32_t)mxGetPr(zfde61350f8)[i];z9e95a8730f->protection[channel]=(uint32_t)mxGetPr(zeac6896859)[i]-(0xed8+3685-0x1d3c);z9e95a8730f->z7211d763fb[channel]=(uint32_t)mxGetPr(z2dceaadc0f)[i]-(0x2478+132-0x24fb);z9e95a8730f->z64b63d5c98[channel]=(uint32_t)mxGetPr(z4eb7791e75)[(0xfd9+300-0x1105)]-(0x868+5834-0x1f31);if((uint32_t)mxGetPr(zc74c85e681)[i]==(0x32d+2641-0xd7c)){z8db8bb5a06|=((0xa32+30-0xa4f)<<channel);}else{z8db8bb5a06&=~((0x1da1+1360-0x22f0)<<channel);}if((uint32_t)mxGetPr(z311fbc5bad)[i]==(0x1547+4431-0x2694)){zee8378496a|=((0xab+8550-0x2210)<<channel);}else{zee8378496a&=~((0x15a7+4417-0x26e7)<<channel);}if((uint32_t)mxGetPr(za04af20061)[i]==(0x1153+4917-0x2486)){z37cfa98aaf|=((0x177d+467-0x194f)<<channel);}else{z37cfa98aaf&=~((0x31a+6851-0x1ddc)<<channel);}enable|=((0x9a1+7039-0x251f)<<channel);}z9e95a8730f->z8db8bb5a06=z8db8bb5a06;z9e95a8730f->zee8378496a=zee8378496a;z9e95a8730f->z37cfa98aaf=z37cfa98aaf;z9e95a8730f->update=enable;z9e95a8730f->update=(0x163d+629-0x18b2);z9e95a8730f->enable=enable;}
#endif
}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){
#ifndef MATLAB_MEX_FILE
uintptr_t base=(uintptr_t)ssGetPWorkValue(S,z93d7dbe681);uint32_t i,channel;volatile z8dc61d99bb*z9e95a8730f;uint32_t z6756646a81,z9ca0045836,z8e8b32e98e,z886a62b902,update,zf30711d604;real_T*z611581ab5c,*zf9036781e1,*z8f4e633df2,*z02d773b6fc;z9e95a8730f=(z8dc61d99bb*)(base+zf2a9add7f9);update=(0xe8+5558-0x169e);for(i=(0x33b+3442-0x10ad);i<(uint32_t)mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0xf1f+5915-0x2639);if((uint32_t)mxGetPr(z01bb085356)[(0xdd+1789-0x7da)]==(0x15d6+855-0x192c)){z611581ab5c=(real_T*)ssGetInputPortSignal(S,(0x1ec8+468-0x209c));zf9036781e1=(real_T*)ssGetInputPortSignal(S,(0x1614+513-0x1814));z6756646a81=(uint32_t)z611581ab5c[i];z8e8b32e98e=(uint32_t)zf9036781e1[i];zf30711d604=(uint32_t)mxGetPr(za9b36fc92d)[i];if(z6756646a81<=(0x76d+621-0x9da)){z9ca0045836=zf30711d604;}else if(z6756646a81>=zf30711d604){z9ca0045836=(0x2349+247-0x2440);}else if(z6756646a81==zf30711d604/(0x8b3+1498-0xe8b)){z9ca0045836=zf30711d604/(0xa11+4487-0x1b96);}else{z9ca0045836=zf30711d604-z6756646a81;}if(z8e8b32e98e<=(0x97b+4529-0x1b2c)){z886a62b902=zf30711d604;}else if(z8e8b32e98e>=zf30711d604){z886a62b902=(0x138b+1972-0x1b3f);}else if(z8e8b32e98e==zf30711d604/(0x13e9+2513-0x1db8)){z886a62b902=zf30711d604/(0x16f8+3328-0x23f6);}else{z886a62b902=zf30711d604-z8e8b32e98e;}}else{z611581ab5c=(real_T*)ssGetInputPortSignal(S,(0x132c+650-0x15b6));zf9036781e1=(real_T*)ssGetInputPortSignal(S,(0xedb+1261-0x13c7));z8f4e633df2=(real_T*)ssGetInputPortSignal(S,(0x143+53-0x176));z02d773b6fc=(real_T*)ssGetInputPortSignal(S,(0x210a+620-0x2373));z6756646a81=(uint32_t)z611581ab5c[i];z9ca0045836=(uint32_t)zf9036781e1[i];z8e8b32e98e=(uint32_t)z8f4e633df2[i];z886a62b902=(uint32_t)z02d773b6fc[i];}z9e95a8730f->z6756646a81[channel]=z6756646a81;z9e95a8730f->z9ca0045836[channel]=z9ca0045836;z9e95a8730f->z8e8b32e98e[channel]=z8e8b32e98e;z9e95a8730f->z886a62b902[channel]=z886a62b902;update|=((0xab9+3682-0x191a)<<channel);}z9e95a8730f->update=update;z9e95a8730f->update=(0x1d2d+45-0x1d5a);
#endif
}static void mdlTerminate(SimStruct*S){
#ifndef MATLAB_MEX_FILE    
uint32_t ze7198b4532,zba6c56af50;uint32_t i,channel;volatile z8dc61d99bb*z9e95a8730f;uintptr_t base=(uintptr_t)ssGetPWorkValue(S,z93d7dbe681);z9e95a8730f=(z8dc61d99bb*)(base+zf2a9add7f9);ze7198b4532=z9e95a8730f->ze7198b4532;zba6c56af50=z9e95a8730f->zba6c56af50;for(i=(0x1284+4472-0x23fc);i<(uint32_t)mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x878+1034-0xc81);if((uint32_t)mxGetPr(z502d9ed0cf)[i]==(0x126f+4430-0x23bc)){ze7198b4532&=~((0x14a+1163-0x5d4)<<channel);}else{ze7198b4532|=((0x619+4973-0x1985)<<channel);}if((uint32_t)mxGetPr(z1918c3f4db)[i]==(0x23c+7552-0x1fbb)){zba6c56af50&=~((0x12b8+3542-0x208d)<<channel);}else{zba6c56af50|=((0x1c23+1242-0x20fc)<<channel);}}z9e95a8730f->ze7198b4532=ze7198b4532;z9e95a8730f->zba6c56af50=zba6c56af50;z9e95a8730f->enable=(0xef5+1144-0x136d);
#endif
}
#include "sg_sfcn_glue.h"   

