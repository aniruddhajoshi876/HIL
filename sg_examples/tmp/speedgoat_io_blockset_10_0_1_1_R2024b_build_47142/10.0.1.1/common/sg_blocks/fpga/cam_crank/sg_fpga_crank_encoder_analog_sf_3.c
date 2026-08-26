// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL (0x882+5705-0x1ec9)
#undef  S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_fpga_crank_encoder_analog_sf_3
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
typedef enum{zfaa050b79d,CHANNEL,ze344b15ab1,zfdf89295d4,zbde7cc3034,z88c63e0ba1,z731cbedf5e,z878b4ea0cf,zdf24515981}z1ebbfc0a89;
#define ze13f49a01f                      ssGetSFcnParam(S, zfaa050b79d)
#define za9d8fb6bcf                        ssGetSFcnParam(S, CHANNEL) 
#define z3832b85a32                      ssGetSFcnParam(S, ze344b15ab1)
#define zc762654f17                    ssGetSFcnParam(S, zfdf89295d4)
#define z503cfc73f9             ssGetSFcnParam(S, zbde7cc3034)
#define za08eaecce0                      ssGetSFcnParam(S, z88c63e0ba1)
#define zd68f0d3534                       ssGetSFcnParam(S, z731cbedf5e)
#define z0760155ccd                    ssGetSFcnParam(S, z878b4ea0cf)
#define z2e6483d505         ((0xfd2+4230-0x2058))
#define zc5ce4cb81a         ((0xff3+1905-0x1764))
#define z2b17e2ee3b         ((0x73d+3245-0x13e9))
#define z0194338df7    ((0x9aa+2009-0x1183))
#define z5bbcf8be2c       (0x7ff+4906-0x1b26)
#define z4099fa3dcd      (32767/(0x6df+2175-0xf54))
typedef struct{uint32_t delta[(0x702+3164-0x133e)];uint32_t z690a7995f2[(0x107f+3454-0x1ddd)];uint32_t zf88cb9c8fc[(0x96f+3708-0x17cb)];uint32_t z23c9633098[(0x16a0+3496-0x2428)];uint32_t zd05b5627b0[(0x50b+1649-0xb5c)];uint32_t zdf15b4e3b9[(0x1ca2+1688-0x231a)];uint32_t enable;uint32_t update;uint32_t zf741388403;uint32_t version;uint32_t z0e2b817c35[(0x4d4+760-0x690)];uint32_t zc37ed24f26;uint32_t zab48718e71;uint32_t zddae4affef;uint32_t ze4b98335b7[(0xd20+1185-0x11a4)];uint32_t zb6428eee4d[(0x388+7908-0x224c)];uint32_t zc177363da1[(0x16ea+771-0x19cd)];uint32_t z498954e981[(0x58d+6122-0x1d57)];uint32_t zd0c76ea440[(0x1a2+9503-0x2541)];uint32_t z7ef5bb8552;uint32_t zd5bb56283a;uint32_t z2068b2116f;uint32_t z9f0e93f2b6[(0xde7+5807-0x2479)];uint32_t z836fa5ec39[(0xa2d+190-0xacb)];uint32_t z25b77c79e8[(0x9f6+2490-0x1390)];uint32_t z80d280c997[(0xce7+6375-0x25ae)];uint32_t z13b0361a3c[(0xf10+5222-0x2356)];uint32_t z82e8400eaa[(0x1c85+2158-0x24d3)];}z65219302fc;static char_T msg[(0x14c4+1106-0x1816)];static void mdlInitializeSizes(SimStruct*S){uint32_t i,z59d6c6c116;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x820+5659-0x1e3b));ssSetNumDiscStates(S,(0xf4d+2642-0x199f));z59d6c6c116=(0x3f3+1419-0x97c);ssSetNumInputPorts(S,z59d6c6c116);ssSetInputPortWidth(S,(0x275+3100-0xe91),mxGetN(za9d8fb6bcf));ssSetInputPortDirectFeedThrough(S,(0x1703+2389-0x2058),(0x8e0+96-0x93f));ssSetInputPortRequiredContiguous(S,(0xd56+54-0xd8c),(0x434+7944-0x233b));ssSetInputPortDataType(S,(0xfb2+4882-0x22c4),(0x8f4+5191-0x1d3b));ssSetInputPortWidth(S,(0x11a5+4800-0x2464),mxGetN(za9d8fb6bcf));ssSetInputPortDirectFeedThrough(S,(0x3bc+7780-0x221f),(0x8b4+4821-0x1b88));ssSetInputPortRequiredContiguous(S,(0x136d+4909-0x2699),(0x817+7298-0x2498));ssSetNumOutputPorts(S,(0xbc+5392-0x15cc));ssSetNumSampleTimes(S,(0xb54+5386-0x205d));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x104+8608-0x22a4));ssSetNumNonsampledZCs(S,(0x882+6229-0x20d7));for(i=(0xc3c+483-0xe1f);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x891+4879-0x1ba0));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0xaac+5034-0x1e56)]==-1.0){ssSetSampleTime(S,(0x6a0+3681-0x1501),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x968+6545-0x22f9),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x1345+1659-0x19c0),mxGetPr(z3832b85a32)[(0x8a1+5828-0x1f65)]);ssSetOffsetTime(S,(0x1dda+1020-0x21d6),0.0);}}static void sg_ModelLoad(SimStruct*S){
#ifndef MATLAB_MEX_FILE
volatile z65219302fc*zb62dafada7;void*bar2ptr;int moduleId=(int)mxGetScalar(ze13f49a01f);char*boardName=io3xxGetBoardNameSgLib(moduleId);if(!io3xxGetAddressSgLib((int32_t)(int)mxGetPr(ze13f49a01f)[(0x6fb+7555-0x247e)],SG_FPGA_IO3XX_BAR2)){ssSetErrorStatus(S,pSgErrorStr);return;}uint32_t zf7ccd17be8=(0x20bf+245-0x21b4);if(sg_fpga_io3xx_getCmBaseAddress(moduleId,CRANK_ENCODER_BASE,&zf7ccd17be8)){sprintf(msg,"\x25\x73\x20\x43\x72\x61\x6e\x6b\x20\x45\x6e\x63\x6f\x64\x65\x72\x20\x41\x6e\x61\x6c\x6f\x67\x20\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x4f\x66\x66\x73\x65\x74\x20\x6c\x6f\x6f\x6b\x75\x70\x20\x75\x6e\x73\x75\x63\x63\x65\x73\x73\x66\x75\x6c\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}bar2ptr=io3xxGetAddressSgLib((int32_t)(int)mxGetPr(ze13f49a01f)[(0xec8+5153-0x22e9)],SG_FPGA_IO3XX_BAR2);zb62dafada7=(z65219302fc*)((uintptr_t)bar2ptr+zf7ccd17be8);ssSetPWorkValue(S,z0194338df7,(void*)zb62dafada7);if(sg_isFirstModelLoad()){if(sg_fpga_io3xx_checkCodeModuleVersion(zb62dafada7->zddae4affef,z5bbcf8be2c,moduleId)){sprintf(msg,"\x25\x73\x20\x77\x72\x6f\x6e\x67\x20\x76\x65\x72\x73\x69\x6f\x6e\x20\x6f\x66\x20\x43\x72\x61\x6e\x6b\x20\x45\x6e\x63\x6f\x64\x65\x72\x20\x41\x6e\x61\x6c\x6f\x67\x20\x63\x6f\x64\x65\x20\x6d\x6f\x64\x75\x6c\x65\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}}
#endif
}static void sg_ModelStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_t zb527a777b1,zebdd849dd8;uint32_t i;uint32_t channel;real_T z280b6f3f00;volatile z65219302fc*zb62dafada7;zb62dafada7=(z65219302fc*)(ssGetPWorkValue(S,z0194338df7));zb527a777b1=(uint32_t)((int32_t)((real_T)mxGetPr(za08eaecce0)[(0x2c7+4199-0x132e)]/(real_T)mxGetPr(zd68f0d3534)[(0x1623+2875-0x215e)]));zb62dafada7->zc37ed24f26=zb527a777b1;zebdd849dd8=(0x1f81+1237-0x2456);channel=(0xf3b+2326-0x1851);for(i=(0xdf1+1370-0x134b);i<(uint32_t)mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x64a+3539-0x141c);if(((uint32_t)((int32_t)((real_T)mxGetPr(zc762654f17)[i])))>0.5){zebdd849dd8|=((0x77c+68-0x7bf)<<(channel));}}zb62dafada7->zab48718e71=zebdd849dd8;for(i=(0x10a+511-0x309);i<(uint32_t)mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x1cb7+2447-0x2645);z280b6f3f00=((real_T)mxGetPr(z503cfc73f9)[i])/4294967295;zb62dafada7->zb6428eee4d[channel]=(uint32_t)(z280b6f3f00*2147483648);}
#endif
}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_t i,channel;real_T*zb51b8fbc4f,*zb640018cea;real_T zb8f6393571,za14f472c58;uint32_t z87a9298581;volatile z65219302fc*zb62dafada7;zb62dafada7=(z65219302fc*)(ssGetPWorkValue(S,z0194338df7));channel=(0x3b5+4886-0x16cb);zb51b8fbc4f=(real_T*)ssGetInputPortSignal(S,(0x1301+3858-0x2213));zb640018cea=(real_T*)ssGetInputPortSignal(S,(0x15f6+4097-0x25f6));z87a9298581=(uint32_t)((int32_t)((real_T)mxGetPr(z0760155ccd)[(0x97+7133-0x1c74)]));for(i=(0x9b0+6810-0x244a);i<(uint32_t)mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0xaf8+171-0xba2);zb8f6393571=zb51b8fbc4f[i]/(0x75a+7258-0x23b2);if(zb8f6393571>(0x347+5838-0x1a0b)){zb8f6393571=(0x146d+2962-0x1ff5);}else if(zb8f6393571<(0x130f+2625-0x1d50)){zb8f6393571=(0xbfd+1612-0x1249);}za14f472c58=zb640018cea[i];if(za14f472c58>(0x982+2739-0x1430)){za14f472c58=(0x2cb+1340-0x802);}else if(za14f472c58<-(0x126+9189-0x2506)){za14f472c58=-(0x532+287-0x64c);}zb62dafada7->zc177363da1[channel]=(uint32_t)((int32_t)(zb8f6393571*z87a9298581));zb62dafada7->z498954e981[channel]=(uint32_t)((int32_t)(za14f472c58*z87a9298581));}
#endif
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE
#endif
}
#include "sg_sfcn_glue.h"   

