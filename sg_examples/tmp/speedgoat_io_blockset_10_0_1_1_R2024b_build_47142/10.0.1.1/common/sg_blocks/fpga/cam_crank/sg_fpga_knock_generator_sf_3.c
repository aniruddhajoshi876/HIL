// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL (0x911+3137-0x1550)
#undef  S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_fpga_knock_generator_sf_3
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include  "sg_printf.h"
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
typedef enum{zfaa050b79d,CHANNEL,ze344b15ab1,z878b4ea0cf,z526572b9ed,zaab2eaa421,DURATION,z88c63e0ba1,z731cbedf5e,zdf24515981}z1ebbfc0a89;
#define ze13f49a01f                      ssGetSFcnParam(S, zfaa050b79d)
#define za9d8fb6bcf                        ssGetSFcnParam(S, CHANNEL) 
#define z3832b85a32                      ssGetSFcnParam(S, ze344b15ab1)
#define z0760155ccd                    ssGetSFcnParam(S, z878b4ea0cf)
#define z406ab40041                       ssGetSFcnParam(S, z526572b9ed)
#define z0e5e7f5f35                    ssGetSFcnParam(S, zaab2eaa421)
#define zbd3907fd29                       ssGetSFcnParam(S, DURATION)
#define za08eaecce0                      ssGetSFcnParam(S, z88c63e0ba1)
#define zd68f0d3534                       ssGetSFcnParam(S, z731cbedf5e)
#define z2e6483d505         ((0x8db+716-0xba7))
#define zc5ce4cb81a         ((0xa8c+181-0xb41))
#define z2b17e2ee3b         ((0x210+1067-0x63a))
#define z0194338df7    ((0x159c+1615-0x1beb))
#define z5bbcf8be2c       (0xfc4+1484-0x158d)
#define z4099fa3dcd      (32767/(0xc00+4856-0x1eee))
typedef struct{uint32_t delta[(0x1273+1666-0x18d5)];uint32_t z690a7995f2[(0x181d+2091-0x2028)];uint32_t zf88cb9c8fc[(0x5c7+2456-0xf3f)];uint32_t z23c9633098[(0xd1c+6068-0x24b0)];uint32_t zd05b5627b0[(0x393+8572-0x24ef)];uint32_t zdf15b4e3b9[(0x964+2139-0x119f)];uint32_t enable;uint32_t update;uint32_t zf741388403;uint32_t version;uint32_t z0e2b817c35[(0x2a9+5572-0x1731)];uint32_t zc37ed24f26;uint32_t zab48718e71;uint32_t zddae4affef;uint32_t ze4b98335b7[(0x86d+5715-0x1ea3)];uint32_t zb6428eee4d[(0xb4d+6074-0x22e7)];uint32_t zc177363da1[(0x2a6+5484-0x17f2)];uint32_t z498954e981[(0x1ee2+640-0x2142)];uint32_t zd0c76ea440[(0x962+6255-0x2051)];uint32_t z7ef5bb8552;uint32_t zd5bb56283a;uint32_t z2068b2116f;uint32_t z9f0e93f2b6[(0x380+2536-0xd4b)];uint32_t z836fa5ec39[(0xf04+5929-0x260d)];uint32_t z25b77c79e8[(0x905+6158-0x20f3)];uint32_t z80d280c997[(0x1201+4102-0x21e7)];uint32_t z13b0361a3c[(0xe8f+5891-0x2572)];uint32_t z82e8400eaa[(0x1fb+5640-0x17e3)];}zbfd7c63da9;static char_T msg[(0x1c4f+2582-0x2565)];static void mdlInitializeSizes(SimStruct*S){uint32_t i,z59d6c6c116;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x12f+293-0x254));ssSetNumDiscStates(S,(0x629+7896-0x2501));z59d6c6c116=(0x147c+3079-0x2081);if(!ssSetNumInputPorts(S,z59d6c6c116)){return;}ssSetInputPortWidth(S,(0x1029+3280-0x1cf9),mxGetN(za9d8fb6bcf));ssSetInputPortDirectFeedThrough(S,(0x98b+4031-0x194a),(0xca3+3960-0x1c1a));ssSetInputPortRequiredContiguous(S,(0x239+8042-0x21a3),(0x14d+6761-0x1bb5));ssSetInputPortDataType(S,(0x975+6609-0x2346),(0xc0a+5092-0x1fee));ssSetInputPortWidth(S,(0x7e3+792-0xafa),mxGetN(za9d8fb6bcf));ssSetInputPortDirectFeedThrough(S,(0x11a0+3072-0x1d9f),(0xdc6+4576-0x1fa5));ssSetInputPortRequiredContiguous(S,(0x438+5571-0x19fa),(0x86b+5643-0x1e75));if(!ssSetNumOutputPorts(S,(0xef+5966-0x183d))){return;}ssSetNumSampleTimes(S,(0x9a2+1549-0xfae));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x588+8547-0x26eb));ssSetNumNonsampledZCs(S,(0x831+2440-0x11b9));for(i=(0x14dc+106-0x1546);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x182c+715-0x1af7));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0xc0b+5396-0x211f)]==-1.0){ssSetSampleTime(S,(0xc6+772-0x3ca),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x934+1557-0xf49),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x195b+3196-0x25d7),mxGetPr(z3832b85a32)[(0x7c6+4071-0x17ad)]);ssSetOffsetTime(S,(0x21d+4988-0x1599),0.0);}}static void sg_ModelLoad(SimStruct*S){
#ifndef MATLAB_MEX_FILE
volatile zbfd7c63da9*z0aa3884f31;void*bar2ptr;int moduleId=(int)mxGetScalar(ze13f49a01f);char*boardName=io3xxGetBoardNameSgLib(moduleId);if(!io3xxGetAddressSgLib((int32_t)(int)mxGetPr(ze13f49a01f)[(0x1250+3991-0x21e7)],SG_FPGA_IO3XX_BAR2)){ssSetErrorStatus(S,pSgErrorStr);return;}uint32_t zf7ccd17be8=(0x1b0+8150-0x2186);if(sg_fpga_io3xx_getCmBaseAddress(moduleId,CRANK_ENCODER_BASE,&zf7ccd17be8)){sprintf(msg,"\x25\x73\x20\x4b\x6e\x6f\x63\x6b\x20\x47\x65\x6e\x65\x72\x61\x74\x6f\x72\x20\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x4f\x66\x66\x73\x65\x74\x20\x6c\x6f\x6f\x6b\x75\x70\x20\x75\x6e\x73\x75\x63\x63\x65\x73\x73\x66\x75\x6c\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}bar2ptr=io3xxGetAddressSgLib((int32_t)(int)mxGetPr(ze13f49a01f)[(0x1431+3301-0x2116)],SG_FPGA_IO3XX_BAR2);z0aa3884f31=(zbfd7c63da9*)((uintptr_t)bar2ptr+zf7ccd17be8);ssSetPWorkValue(S,z0194338df7,(void*)z0aa3884f31);if(sg_isFirstModelLoad()){if(sg_fpga_io3xx_checkCodeModuleVersion(z0aa3884f31->z2068b2116f,z5bbcf8be2c,moduleId)){sprintf(msg,"\x25\x73\x20\x77\x72\x6f\x6e\x67\x20\x76\x65\x72\x73\x69\x6f\x6e\x20\x6f\x66\x20\x4b\x6e\x6f\x63\x6b\x20\x47\x65\x6e\x65\x72\x61\x74\x6f\x72\x20\x63\x6f\x64\x65\x20\x6d\x6f\x64\x75\x6c\x65\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}}
#endif
}static void sg_ModelStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_t zb527a777b1;uint32_t i,channel,zeeeba54a90;volatile zbfd7c63da9*z0aa3884f31;uint32_t z836fa5ec39;z0aa3884f31=(zbfd7c63da9*)(ssGetPWorkValue(S,z0194338df7));zeeeba54a90=(z0aa3884f31->z2068b2116f&(0xa7d+3056-0x126e));zb527a777b1=(uint32_t)((int32_t)((real_T)mxGetPr(za08eaecce0)[(0x16b8+607-0x1917)]/(real_T)mxGetPr(zd68f0d3534)[(0x35a+8770-0x259c)]));z0aa3884f31->z7ef5bb8552=zb527a777b1;for(i=(0x7df+5258-0x1c69);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0xbdf+1100-0x102a);if(zeeeba54a90==(0x3a9+1482-0x973)){z836fa5ec39=(uint32_t)((int32_t)((real_T)mxGetPr(z0760155ccd)[i]));}else{z836fa5ec39=(uint32_t)((int32_t)((real_T)mxGetPr(z0760155ccd)[i]*0.5));}z0aa3884f31->z836fa5ec39[channel]=z836fa5ec39;z0aa3884f31->z25b77c79e8[channel]=(uint32_t)((int32_t)((real_T)mxGetPr(z406ab40041)[i]*65536));z0aa3884f31->z80d280c997[channel]=(uint32_t)((int32_t)((real_T)mxGetPr(z0e5e7f5f35)[i]*32768));z0aa3884f31->z13b0361a3c[channel]=(uint32_t)((int32_t)((real_T)mxGetPr(zbd3907fd29)[i]*65536));}
#endif
}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_t i,channel,z7245cf6162,zcd8ee5b32e;real_T*in;volatile zbfd7c63da9*z0aa3884f31;z0aa3884f31=(zbfd7c63da9*)(ssGetPWorkValue(S,z0194338df7));channel=(0x53f+2321-0xe50);in=(real_T*)ssGetInputPortSignal(S,(0x16b+8693-0x2360));for(i=(0x1376+4890-0x2690);i<(uint32_t)mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0xff4+2733-0x1aa0);if((in[i]<(0x17ad+3799-0x2684))|(in[i]>=(0xf74+4757-0x1f39))){z7245cf6162=(0xdd+7092-0x1c91);}else{z7245cf6162=(uint32_t)(in[i]/(0xcaa+4561-0x1bab)*4294967295);}z0aa3884f31->z82e8400eaa[channel]=z7245cf6162;}channel=(0xd87+5774-0x2415);zcd8ee5b32e=(0x153+2294-0xa49);in=(real_T*)ssGetInputPortSignal(S,(0x6a3+3885-0x15cf));for(i=(0x1005+428-0x11b1);i<(uint32_t)mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x4d6+168-0x57d);if(in[i]>=0.5){zcd8ee5b32e|=((0x157c+1381-0x1ae0)<<(channel));}}z0aa3884f31->zd5bb56283a=zcd8ee5b32e;
#endif
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE
#endif
}
#include "sg_sfcn_glue.h"   

