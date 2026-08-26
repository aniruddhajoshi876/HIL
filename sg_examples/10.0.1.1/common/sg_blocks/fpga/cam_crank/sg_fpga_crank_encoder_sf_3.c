// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL (0x257+8287-0x22b4)
#undef  S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_fpga_crank_encoder_sf_3
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "simstruc.h"
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif
#ifndef MATLAB_MEX_FILE
#include "sg_common.h"
#include "sg_fpga_io3xx_util.h"
#include "sg_printf.h"
#endif
#include "sg_callback.h"
typedef enum{CHANNEL,ze344b15ab1,zbde7cc3034,ze0aac8e8a5,z171ab173f8,z017f598ef0,z89bd094ce9,za8793ce5e2,z86f09446ec,z6e266e9ace,zac8c0ff69b,ID,z4675e56882,zdf24515981}zeb58ea8bfc;
#define za9d8fb6bcf                        ssGetSFcnParam(S, CHANNEL) 
#define z3832b85a32                      ssGetSFcnParam(S, ze344b15ab1)
#define z503cfc73f9             ssGetSFcnParam(S, zbde7cc3034) 
#define zc86d225ab5     ssGetSFcnParam(S, ze0aac8e8a5)
#define zed5a8d5eee                      ssGetSFcnParam(S, z171ab173f8)
#define z32d1003186                     ssGetSFcnParam(S, z017f598ef0)
#define zb2c0d1790a              ssGetSFcnParam(S, z89bd094ce9)
#define za79e5b2ad0               ssGetSFcnParam(S, za8793ce5e2)
#define ze7ba4e6903          ssGetSFcnParam(S, z86f09446ec)
#define zdb9387c47d		   ssGetSFcnParam(S, z6e266e9ace)
#define z19b9dfa260                 ssGetSFcnParam(S, zac8c0ff69b)
#define z58f464b4bb                             ssGetSFcnParam(S, ID)
#define z3e673eccd7                    ssGetSFcnParam(S, z4675e56882)
#define z2e6483d505         ((0x1cf9+2122-0x2543))
#define z2b17e2ee3b         ((0x1590+2777-0x2068))
#define z0194338df7    ((0x1a3+9556-0x26f7))
#define z5bbcf8be2c       (0x77f+195-0x83f)
#define za9059c32c3        (4294967296.0) 
typedef struct{uint32_t delta[(0x190+8052-0x20e4)];uint32_t z690a7995f2[(0xcec+2628-0x1710)];uint32_t zf88cb9c8fc[(0xee1+4654-0x20ef)];uint32_t z23c9633098[(0x145+4751-0x13b4)];uint32_t zd05b5627b0[(0x5b0+7552-0x2310)];uint32_t zdf15b4e3b9[(0x251+1369-0x78a)];uint32_t enable;uint32_t update;uint32_t zf741388403;uint32_t version;uint32_t zbb387eab83;uint32_t z816e645438[(0x197c+2325-0x2276)];uint32_t zf61bab1fa4[(0xba6+1552-0x1196)];uint32_t z5ab5306ac9[(0xb9+4468-0x120d)];uint32_t zc5186e3d82[(0xa6f+7271-0x26b6)];uint32_t z6222f79c28[(0x3dd+6482-0x1d0f)];}za517359485;static char msg[(0x493+7521-0x20f4)];static void mdlInitializeSizes(SimStruct*S){uint32_t i,z79ff37644d,z0654cd984b;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x10db+2155-0x1946));ssSetNumDiscStates(S,(0x104a+516-0x124e));z79ff37644d=(0x5f0+5730-0x1c52);z0654cd984b=(0x989+3483-0x1724);if(mxGetPr(za79e5b2ad0)[(0x105a+3467-0x1de5)]){z79ff37644d++;}if(mxGetPr(ze7ba4e6903)[(0x11fc+4438-0x2352)]){z79ff37644d++;}if(!ssSetNumInputPorts(S,z79ff37644d)){return;}for(i=(0x59a+1979-0xd55);i<z79ff37644d;i++){ssSetInputPortWidth(S,i,mxGetN(za9d8fb6bcf));ssSetInputPortDirectFeedThrough(S,i,(0x3c2+1776-0xab1));ssSetInputPortRequiredContiguous(S,i,(0x117a+926-0x1517));}if(mxGetPr(zdb9387c47d)[(0x47c+633-0x6f5)]){z0654cd984b=z0654cd984b+(0x20b+7136-0x1dea);}if(!ssSetNumOutputPorts(S,z0654cd984b)){return;}for(i=(0x166b+1130-0x1ad5);i<z0654cd984b;i++){ssSetOutputPortWidth(S,i,mxGetN(za9d8fb6bcf));}ssSetNumSampleTimes(S,(0x117+5912-0x182e));ssSetNumRWork(S,mxGetN(za9d8fb6bcf));ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x13c1+3519-0x2180));ssSetNumNonsampledZCs(S,(0x4b6+7052-0x2042));for(i=(0x531+8304-0x25a1);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x4ea+5170-0x191c));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x5b6+4588-0x17a2)]==-1.0){ssSetSampleTime(S,(0xe17+143-0xea6),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x10da+2531-0x1abd),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x962+2852-0x1486),mxGetPr(z3832b85a32)[(0x6b2+2655-0x1111)]);ssSetOffsetTime(S,(0xc40+3451-0x19bb),0.0);}}static void sg_ModelLoad(SimStruct*S){
#ifndef MATLAB_MEX_FILE
volatile za517359485*z80afbc93c6;void*bar2ptr;int moduleId=(int)mxGetScalar(z58f464b4bb);char*boardName=io3xxGetBoardNameSgLib(moduleId);if(!io3xxGetAddressSgLib((int32_t)(int)mxGetPr(z58f464b4bb)[(0x34d+1619-0x9a0)],SG_FPGA_IO3XX_BAR2)){ssSetErrorStatus(S,pSgErrorStr);return;}uint32_t zf7ccd17be8=(0x63+8808-0x22cb);if(sg_fpga_io3xx_getCmBaseAddress(moduleId,CRANK_ENCODER_BASE,&zf7ccd17be8)){sprintf(msg,"\x25\x73\x20\x43\x72\x61\x6e\x6b\x20\x45\x6e\x63\x6f\x64\x65\x72\x20\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x4f\x66\x66\x73\x65\x74\x20\x6c\x6f\x6f\x6b\x75\x70\x20\x75\x6e\x73\x75\x63\x63\x65\x73\x73\x66\x75\x6c\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}bar2ptr=io3xxGetAddressSgLib((int32_t)(int)mxGetPr(z58f464b4bb)[(0x576+5305-0x1a2f)],SG_FPGA_IO3XX_BAR2);z80afbc93c6=(za517359485*)((uintptr_t)bar2ptr+(uintptr_t)zf7ccd17be8);ssSetPWorkValue(S,z0194338df7,(void*)z80afbc93c6);if(sg_isFirstModelLoad()){if(sg_fpga_io3xx_checkCodeModuleVersion(z80afbc93c6->version,z5bbcf8be2c,moduleId)){sprintf(msg,"\x25\x73\x20\x77\x72\x6f\x6e\x67\x20\x76\x65\x72\x73\x69\x6f\x6e\x20\x6f\x66\x20\x43\x72\x61\x6e\x6b\x20\x45\x6e\x63\x6f\x64\x65\x72\x20\x63\x6f\x64\x65\x20\x6d\x6f\x64\x75\x6c\x65\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}}
#endif
}static void sg_ModelStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_t i;uint32_t channel,enable;volatile za517359485*z80afbc93c6;z80afbc93c6=(za517359485*)(ssGetPWorkValue(S,z0194338df7));uint32_t z690a7995f2,z60fa22f531;real_T z5ab5306ac9;uint32_t z5c83b18c32,z1e678f3fe7,z2bc718ce52;enable=(0x1701+1467-0x1cbc);;for(i=(0x8b7+6956-0x23e3);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x1bf5+1010-0x1fe6);enable|=((0xcec+5476-0x224f)<<channel);z80afbc93c6->zd05b5627b0[channel]=(uint32_t)mxGetPr(z503cfc73f9)[i];z80afbc93c6->zdf15b4e3b9[channel]=(uint32_t)mxGetPr(zc86d225ab5)[i];z80afbc93c6->delta[channel]=(uint32_t)((za9059c32c3/(double)mxGetPr(z19b9dfa260)[(0x1db9+2170-0x2633)])*((double)mxGetPr(zed5a8d5eee)[i]/60.0)/2.0);ssSetRWorkValue(S,i,0.0);z690a7995f2=(uint32_t)(za9059c32c3/(uint32_t)mxGetPr(z503cfc73f9)[i]);z80afbc93c6->z690a7995f2[channel]=z690a7995f2;z80afbc93c6->zf88cb9c8fc[channel]=(0x24f+6120-0x1a37);z80afbc93c6->z23c9633098[channel]=(uint32_t)((za9059c32c3/(uint32_t)mxGetPr(z503cfc73f9)[i])*(double)mxGetPr(z32d1003186)[i]);uint32_t zeeeba54a90=(z80afbc93c6->version&(0x1f26+1123-0x1f8a));if(zeeeba54a90>=(0x1877+442-0x1a29)){z5ab5306ac9=(double)mxGetPr(z3e673eccd7)[i];z5c83b18c32=(uint32_t)(z5ab5306ac9*(za9059c32c3-(0xf4b+690-0x11fc))/(0x2503+399-0x23c2));z60fa22f531=z690a7995f2/(0x1667+8-0x166d);z2bc718ce52=z5c83b18c32/z60fa22f531;z1e678f3fe7=(uint32_t)(z5c83b18c32-(z2bc718ce52*z690a7995f2*0.5));z80afbc93c6->z5ab5306ac9[channel]=z5c83b18c32;z80afbc93c6->zc5186e3d82[channel]=z1e678f3fe7;z80afbc93c6->z6222f79c28[channel]=z2bc718ce52;}}if((uint32_t)mxGetPr(zb2c0d1790a)[(0x1cdc+284-0x1df8)]){z80afbc93c6->zf741388403|=enable;}else{z80afbc93c6->zf741388403&=~enable;}z80afbc93c6->update=(0xf24+4887-0x223a);z80afbc93c6->update=(0x528+1530-0xb22);z80afbc93c6->enable|=enable;
#endif
}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_t i,channel,z66a0c13c76,zc899ce874c;double*in;double z9be60e2073,z64cad4ef4c;volatile za517359485*z80afbc93c6;z80afbc93c6=(za517359485*)(ssGetPWorkValue(S,z0194338df7));real_T zf61bab1fa4;real_T*za39f68f063;z66a0c13c76=(0x1d52+258-0x1e54);zc899ce874c=(0x602+2077-0xe1f);channel=(0x4a0+5150-0x18be);if((uint32_t)mxGetPr(za79e5b2ad0)[(0xfa4+313-0x10dd)]){in=(double*)ssGetInputPortSignal(S,zc899ce874c);for(i=(0xb78+1036-0xf84);i<(uint32_t)mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x1779+2363-0x20b3);z9be60e2073=((double)ssGetRWorkValue(S,i));z64cad4ef4c=((za9059c32c3/(double)mxGetPr(z19b9dfa260)[(0x30f+9106-0x26a1)])*(in[i]/60.0)/2.0);z80afbc93c6->delta[channel]=(uint32_t)(z9be60e2073+z64cad4ef4c);ssSetRWorkValue(S,i,((z9be60e2073+z64cad4ef4c)-(int32_t)(z9be60e2073+z64cad4ef4c)));}z66a0c13c76=(0xd72+5299-0x2224);zc899ce874c++;}if((uint32_t)mxGetPr(ze7ba4e6903)[(0x5ab+3523-0x136e)]){in=(double*)ssGetInputPortSignal(S,zc899ce874c);for(i=(0x499+3197-0x1116);i<(uint32_t)mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x1666+520-0x186d);z80afbc93c6->z23c9633098[channel]=(uint32_t)((za9059c32c3/(uint32_t)mxGetPr(z503cfc73f9)[i])*(double)in[i]);;}z66a0c13c76=(0xa01+5822-0x20be);zc899ce874c++;}if(z66a0c13c76){z80afbc93c6->update=(0x543+1407-0xac1);z80afbc93c6->update=(0x80b+5537-0x1dac);}if(mxGetPr(zdb9387c47d)[(0x1520+2037-0x1d15)]){z80afbc93c6->zbb387eab83=(0x1a9d+582-0x1ce2);z80afbc93c6->zbb387eab83=(0x8b2+6588-0x226e);za39f68f063=(real_T*)ssGetOutputPortSignal(S,(0xfbb+1909-0x1730));for(i=(0x170a+225-0x17eb);i<(uint32_t)mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x1bb4+1869-0x2300);zf61bab1fa4=(real_T)z80afbc93c6->zf61bab1fa4[channel];za39f68f063[i]=zf61bab1fa4/za9059c32c3*(0xd73+1823-0x11c2);}}
#endif
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE
volatile za517359485*z80afbc93c6;z80afbc93c6=(za517359485*)(ssGetPWorkValue(S,z0194338df7));z80afbc93c6->enable=(0x34f+2353-0xc80);
#endif
}
#include "sg_sfcn_glue.h"   

