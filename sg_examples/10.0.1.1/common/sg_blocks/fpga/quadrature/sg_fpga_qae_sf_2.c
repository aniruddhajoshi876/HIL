// Copyright 2006-2026 Speedgoat GmbH

#define     S_FUNCTION_LEVEL  (0x189b+2505-0x2262)
#undef      S_FUNCTION_NAME
#define     S_FUNCTION_NAME   sg_fpga_qae_sf_2
#include    <stddef.h>
#include    <stdlib.h>
#include    <stdbool.h>
#include    <math.h>
#include    "simstruc.h"
#ifdef      MATLAB_MEX_FILE
#include    "mex.h"
#endif
#ifndef     MATLAB_MEX_FILE
#include    "sg_common.h"
#include    "sg_fpga_io3xx_util.h"
#include    "sg_printf.h"
#endif
#include    "sg_callback.h"
#define debug
typedef enum{zfaa050b79d,CHANNEL,zac8c0ff69b,za59eb17498,z4ff1522c54,z7963cdc72a,zfb96b5cdc6,z06c7c2826b,z682264a946,z6aded47b5c,z62bf73e3a7,ze344b15ab1,zdf24515981}z711e67e22f;
#define ze13f49a01f           ssGetSFcnParam(S,zfaa050b79d)
#define za9d8fb6bcf             ssGetSFcnParam(S,CHANNEL) 
#define z19b9dfa260      ssGetSFcnParam(S,zac8c0ff69b)
#define z503e6ced0f      ssGetSFcnParam(S,za59eb17498) 
#define zf0a85064b6       ssGetSFcnParam(S,z4ff1522c54) 
#define ze4d3b8eb95          ssGetSFcnParam(S,z7963cdc72a) 
#define zb59583bf39           ssGetSFcnParam(S,zfb96b5cdc6) 
#define z1437fe8de1           ssGetSFcnParam(S,z06c7c2826b) 
#define z290889a43b        ssGetSFcnParam(S,z682264a946) 
#define z13bb501290           ssGetSFcnParam(S,z6aded47b5c) 
#define z4d864ecfe6              ssGetSFcnParam(S,z62bf73e3a7) 
#define z3832b85a32           ssGetSFcnParam(S,ze344b15ab1)
#define z2e6483d505              (0xf06+6118-0x26ec)
#define zc5ce4cb81a              (0x4c0+2759-0xf85)
#define z2b17e2ee3b              (0x3ec+8540-0x2547)
#define z0194338df7         (0x536+6115-0x1d19)
#define z5ae2c8ee5e         (0x8c4+7271-0x252b)
#define z892eac7a26             (0xae2+1432-0x1079)
#define z5bbcf8be2c            (0x2003+927-0x23a0)
static char_T msg[(0x210d+538-0x2227)];typedef struct{uint32_T z3fd72505ec;uint32_T enable;uint32_T z2a375934c9;uint32_T ze0c70c0014;int32_T delta[(0x1640+3686-0x2486)];uint32_T z4d136236e7[(0x461+4289-0x1502)];uint32_T z6f082d3668[(0x3a2+6233-0x1bdb)];uint32_T z148a181967[(0x954+4914-0x1c66)];uint32_T z6c329339eb[(0x22f8+802-0x25fa)];uint32_T z81006f8f44[(0x908+6182-0x210e)];uint32_T z04236b3cd8[(0x158a+4183-0x25c1)];uint32_T position[(0x112b+2147-0x196e)];uint32_T version;}z57bf1945ef;static void mdlInitializeSizes(SimStruct*S){uint32_T i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x7e8+7743-0x2627));ssSetNumDiscStates(S,(0xeda+2418-0x184c));if(mxGetPr(zf0a85064b6)[(0x6cd+5470-0x1c2b)]){if(mxGetPr(ze4d3b8eb95)[(0x8e0+7416-0x25d8)]){ssSetNumInputPorts(S,(0xd7+7275-0x1d40));ssSetInputPortWidth(S,(0x129b+4095-0x229a),mxGetN(za9d8fb6bcf));ssSetInputPortDirectFeedThrough(S,(0x492+1900-0xbfe),(0xfcb+4400-0x20fa));ssSetInputPortRequiredContiguous(S,(0x118d+2051-0x1990),(0xda9+1520-0x1398));ssSetInputPortWidth(S,(0x17d+3748-0x1020),mxGetN(za9d8fb6bcf));ssSetInputPortDirectFeedThrough(S,(0x1221+3550-0x1ffe),(0x22c+5134-0x1639));ssSetInputPortRequiredContiguous(S,(0xef+7532-0x1e5a),(0x19d7+381-0x1b53));}else{ssSetNumInputPorts(S,(0x138f+3580-0x218a));ssSetInputPortWidth(S,(0x77+7451-0x1d92),mxGetN(za9d8fb6bcf));ssSetInputPortDirectFeedThrough(S,(0x1bc9+2727-0x2670),(0x195f+254-0x1a5c));ssSetInputPortRequiredContiguous(S,(0x22d3+149-0x2368),(0x800+1046-0xc15));}}else{if(mxGetPr(ze4d3b8eb95)[(0x1990+3151-0x25df)]){ssSetNumInputPorts(S,(0x16b1+386-0x1832));ssSetInputPortWidth(S,(0x10b+4804-0x13cf),mxGetN(za9d8fb6bcf));ssSetInputPortDirectFeedThrough(S,(0x1c72+2215-0x2519),(0x13d+5925-0x1861));ssSetInputPortRequiredContiguous(S,(0x1bea+1283-0x20ed),(0x19a+356-0x2fd));}else{ssSetNumInputPorts(S,(0x19f9+2200-0x2291));}}if(mxGetPr(z503e6ced0f)[(0x7ac+6480-0x20fc)]){ssSetNumOutputPorts(S,(0x3db+1659-0xa55));ssSetOutputPortWidth(S,(0x1394+4968-0x26fc),mxGetN(za9d8fb6bcf));}else{ssSetNumOutputPorts(S,(0xacc+4183-0x1b23));}ssSetNumSampleTimes(S,(0x24e5+386-0x2666));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0xa3a+7038-0x25b8));ssSetNumNonsampledZCs(S,(0xf8f+2919-0x1af6));for(i=(0x5f3+67-0x636);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0xa31+12-0xa3d));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x22ff+432-0x24af)]==-1.0){ssSetSampleTime(S,(0x4ed+6925-0x1ffa),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0xe79+4328-0x1f61),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x656+7672-0x244e),mxGetPr(z3832b85a32)[(0x1c90+169-0x1d39)]);ssSetOffsetTime(S,(0x528+6439-0x1e4f),0.0);}}static void sg_ModelLoad(SimStruct*S){
#ifndef MATLAB_MEX_FILE
volatile z57bf1945ef*z9d2a5f6580;uintptr_t z70fcda5f5d;int moduleId=(int)mxGetScalar(ze13f49a01f);char*boardName=io3xxGetBoardNameSgLib(moduleId);real_T z5ec2b7da0a;z5ec2b7da0a=(real_T)mxGetPr(z19b9dfa260)[(0x808+2532-0x11ec)];ssSetRWorkValue(S,z5ae2c8ee5e,z5ec2b7da0a);z70fcda5f5d=(uintptr_t)io3xxGetAddressSgLib((int)mxGetPr(ze13f49a01f)[(0x6e9+5997-0x1e56)],SG_FPGA_IO3XX_BAR2);if(z70fcda5f5d==(0x1ab9+1524-0x20ad)){ssSetErrorStatus(S,pSgErrorStr);return;}uint32_t zf7ccd17be8=(0x24c+8901-0x2511);if(sg_fpga_io3xx_getCmBaseAddress(moduleId,QAE_BASE,&zf7ccd17be8)){sprintf(msg,"\x25\x73\x20\x51\x41\x45\x20\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x4f\x66\x66\x73\x65\x74\x20\x6c\x6f\x6f\x6b\x75\x70\x20\x75\x6e\x73\x75\x63\x63\x65\x73\x73\x66\x75\x6c\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}z9d2a5f6580=(z57bf1945ef*)(z70fcda5f5d+zf7ccd17be8);ssSetPWorkValue(S,z0194338df7,(void*)z9d2a5f6580);if(sg_isFirstModelLoad()){if(sg_fpga_io3xx_checkCodeModuleVersion(z9d2a5f6580->version,z5bbcf8be2c,moduleId)){sprintf(msg,"\x25\x73\x20\x77\x72\x6f\x6e\x67\x20\x76\x65\x72\x73\x69\x6f\x6e\x20\x6f\x66\x20\x51\x41\x45\x20\x63\x6f\x64\x65\x20\x6d\x6f\x64\x75\x6c\x65\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}}
#endif
}static void sg_ModelStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_T i;int32_T delta;uint32_T z67beccaa3c,z92f3eab96a,ze9454eef29,zcd308d01c9;real_T z5ec2b7da0a;boolean_T z7239227cdb;real_T z6f498cb09b;uint32_T channel,enable,z3fd72505ec,z81006f8f44;volatile z57bf1945ef*z9d2a5f6580;z9d2a5f6580=(z57bf1945ef*)(ssGetPWorkValue(S,z0194338df7));zcd308d01c9=(0x9a4+6311-0x224b);for(i=(0x2c7+1054-0x6e5);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_T)mxGetPr(za9d8fb6bcf)[i]-(0x157d+1013-0x1971);zcd308d01c9|=((0x466+44-0x491)<<channel);z81006f8f44=(uint32_T)mxGetPr(z4d864ecfe6)[i];z9d2a5f6580->z81006f8f44[channel]=z81006f8f44;delta=(int32_T)(4294967295.0/60.0*((real_T)mxGetPr(z13bb501290)[i]/z5ec2b7da0a)*(real_T)z81006f8f44);z9d2a5f6580->delta[channel]=delta;z7239227cdb=(real_T)mxGetPr(z1437fe8de1)[i]>=(0x1cc+813-0x4f9)?(0x1018+4891-0x2332):(0x417+6975-0x1f56);z6f498cb09b=z7239227cdb?(real_T)mxGetPr(z1437fe8de1)[i]:-(0x20db+199-0x21a1)*(real_T)mxGetPr(z1437fe8de1)[i];ze9454eef29=(uint32_T)(z6f498cb09b/(real_T)180.0*(real_T)4294967295.0);if(z7239227cdb){z9d2a5f6580->z4d136236e7[channel]=ze9454eef29;z9d2a5f6580->z6f082d3668[channel]=(0x172a+3821-0x2617);}else{z9d2a5f6580->z4d136236e7[channel]=(0x5ac+2729-0x1055);z9d2a5f6580->z6f082d3668[channel]=ze9454eef29;}z67beccaa3c=(uint32_T)mxGetPr(z290889a43b)[i];z92f3eab96a=z67beccaa3c;if(fabs((real_T)mxGetPr(z1437fe8de1)[i])==180.0){z92f3eab96a=(z92f3eab96a==z81006f8f44)?(0x1572+880-0x18e2):z92f3eab96a+(0x992+1871-0x10e0);}z9d2a5f6580->z148a181967[channel]=z67beccaa3c;z9d2a5f6580->z6c329339eb[channel]=z92f3eab96a;}z9d2a5f6580->z2a375934c9=zcd308d01c9;z9d2a5f6580->z2a375934c9=(0x894+1619-0xee7);z9d2a5f6580->ze0c70c0014=zcd308d01c9;z9d2a5f6580->ze0c70c0014=(0x2293+675-0x2536);ssSetRWorkValue(S,z892eac7a26,0.0);enable=(0x8c1+4623-0x1ad0);z3fd72505ec=(0x49f+7568-0x222f);for(i=(0x1588+907-0x1913);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_T)mxGetPr(za9d8fb6bcf)[i]-(0x1e91+2165-0x2705);enable|=((0x4c4+5700-0x1b07)<<channel);z3fd72505ec|=((uint32_T)(mxGetPr(zb59583bf39)[(0x3d6+2770-0xea8)])<<channel);}z9d2a5f6580->z3fd72505ec|=z3fd72505ec;z9d2a5f6580->enable|=enable;
#endif
}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_T i,channel;int32_T delta;uint32_T z81006f8f44;real_T*y1,*y2;real_T*out;real_T z5ec2b7da0a,z9be60e2073,z52754d10b7;volatile z57bf1945ef*z9d2a5f6580;z5ec2b7da0a=ssGetRWorkValue(S,z5ae2c8ee5e);z9d2a5f6580=(z57bf1945ef*)(ssGetPWorkValue(S,z0194338df7));if(mxGetPr(z503e6ced0f)[(0x360+9076-0x26d4)]){out=(real_T*)ssGetOutputPortSignal(S,(0x1212+4064-0x21f2));for(i=(0x19e8+949-0x1d9d);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_T)mxGetPr(za9d8fb6bcf)[i]-(0xafd+3983-0x1a8b);out[i]=(real_T)z9d2a5f6580->position[channel];}}if(mxGetPr(zf0a85064b6)[(0x1db0+1780-0x24a4)]){if(mxGetPr(ze4d3b8eb95)[(0x91+8563-0x2204)]){for(i=(0x14a+3624-0xf72);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_T)mxGetPr(za9d8fb6bcf)[i]-(0x15dd+2013-0x1db9);z81006f8f44=(uint32_T)mxGetPr(z4d864ecfe6)[i];y1=(real_T*)ssGetInputPortSignal(S,(0x100+152-0x198));y2=(real_T*)ssGetInputPortSignal(S,(0x356+5853-0x1a32));z9d2a5f6580->z04236b3cd8[channel]=(uint32_T)y1[i];z9be60e2073=(real_T)ssGetRWorkValue(S,z892eac7a26);z52754d10b7=(real_T)(4294967295.0/60.0*((real_T)y2[i]/z5ec2b7da0a)*(real_T)z81006f8f44);delta=(int32_T)(z52754d10b7+z9be60e2073);ssSetRWorkValue(S,z892eac7a26,(z52754d10b7+z9be60e2073-(int32_T)(z52754d10b7+z9be60e2073)));z9d2a5f6580->delta[channel]=delta;}}else{y1=(real_T*)ssGetInputPortSignal(S,(0x2e0+4596-0x14d4));for(i=(0x2f7+6418-0x1c09);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_T)mxGetPr(za9d8fb6bcf)[i]-(0x918+5511-0x1e9e);z9d2a5f6580->z04236b3cd8[channel]=(uint32_T)y1[i];}}}else{if(mxGetPr(ze4d3b8eb95)[(0x2239+1030-0x263f)]){y1=(real_T*)ssGetInputPortSignal(S,(0x1b9c+1062-0x1fc2));for(i=(0x1943+591-0x1b92);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_T)mxGetPr(za9d8fb6bcf)[i]-(0x1768+205-0x1834);z81006f8f44=(uint32_T)mxGetPr(z4d864ecfe6)[i];z9be60e2073=(real_T)ssGetRWorkValue(S,z892eac7a26);z52754d10b7=(real_T)(4294967295.0/60.0*((real_T)y1[i]/z5ec2b7da0a)*(real_T)z81006f8f44);delta=(int32_T)(z52754d10b7+z9be60e2073);ssSetRWorkValue(S,z892eac7a26,(z52754d10b7+z9be60e2073-(int32_T)(z52754d10b7+z9be60e2073)));z9d2a5f6580->delta[channel]=delta;}}}
#endif
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE
volatile z57bf1945ef*z9d2a5f6580=(z57bf1945ef*)(ssGetPWorkValue(S,z0194338df7));z9d2a5f6580->enable=(0xa8b+2143-0x12ea);
#endif
}
#include "sg_sfcn_glue.h"   

