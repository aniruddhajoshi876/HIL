// Copyright 2006-2026 Speedgoat GmbH

#define    S_FUNCTION_LEVEL   (0x1ca7+818-0x1fd7)
#undef     S_FUNCTION_NAME
#define    S_FUNCTION_NAME   sg_fpga_events_capture_sf_3
#include   <stddef.h>
#include   <stdlib.h>
#include   <stdint.h>
#include   <stdbool.h>
#include   "simstruc.h"
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif
#ifndef MATLAB_MEX_FILE
#include "sg_common.h"
#include "sg_fpga_io3xx_util.h"
#include "sg_printf.h"
#endif
#include "sg_callback.h"
typedef enum{CHANNEL,ze344b15ab1,zecdb89c120,z47ff634556,zb61ec744bb,z88c63e0ba1,zd36b1349d1,ID,zdf24515981}z0d33d5cbe6;
#define za9d8fb6bcf            ssGetSFcnParam(S, CHANNEL) 
#define z3832b85a32          ssGetSFcnParam(S, ze344b15ab1)
#define z9025f678b8       ssGetSFcnParam(S, zecdb89c120)
#define z7406514f86  ssGetSFcnParam(S, z47ff634556)
#define z8c2f8041a4 ssGetSFcnParam(S, zb61ec744bb)
#define z19b9dfa260     ssGetSFcnParam(S, z88c63e0ba1)
#define z1120e7330e           ssGetSFcnParam(S, zd36b1349d1)
#define z58f464b4bb                 ssGetSFcnParam(S, ID)
#define z2e6483d505             (0x5bf+8129-0x2580)
#define zc5ce4cb81a             (0x171+4508-0x130d)
#define z2b17e2ee3b             (0x953+2074-0x116c)
#define z0194338df7        (0xec4+709-0x1189)
#define z5bbcf8be2c           (0x1f03+678-0x21a6)
#define za9059c32c3            4294967295 
static char msg[(0x1c5f+2011-0x233a)];typedef struct{uint32_t zd1e68ee73d[(0xc41+1003-0x100c)];uint32_t z37b591a7d2[32];uint32_t z71b534306c[(0x22a+3100-0xe26)];uint32_t z072695491e[(0x7c+2475-0xa07)];uint32_t z344c5ac569[(0x1011+2953-0x1b7a)];uint32_t zbb26572b92[(0x109a+183-0x1131)];uint32_t za861233e50[(0x1724+3372-0x2430)];uint32_t zeab8425154[(0xd1f+2350-0x162d)];uint32_t enable;uint32_t zb871a780a7;uint32_t version;uint32_t z509472aca9[(0x1f1+4544-0x1394)];uint32_t zaa88aaf485[(0x2385+29-0x2382)];}z867297d97e;static void mdlInitializeSizes(SimStruct*S){uint32_t i,z59d6c6c116;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x4f7+8441-0x25f0));ssSetNumDiscStates(S,(0xaea+2310-0x13f0));ssSetNumInputPorts(S,(0x1a5f+2602-0x2489));z59d6c6c116=(0xfc0+249-0x10b9);if((uint32_t)mxGetPr(z7406514f86)[(0x117f+1790-0x187d)]){z59d6c6c116++;}if((uint32_t)mxGetPr(z8c2f8041a4)[(0x927+2891-0x1472)]){z59d6c6c116++;}ssSetNumOutputPorts(S,z59d6c6c116);for(i=(0xb8c+5924-0x22b0);i<z59d6c6c116;i++){ssSetOutputPortMatrixDimensions(S,i,(uint32_t)mxGetPr(z9025f678b8)[(0x19c3+672-0x1c63)],mxGetN(za9d8fb6bcf));}ssSetNumSampleTimes(S,(0xda3+491-0xf8d));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x366+2139-0xbc1));ssSetNumNonsampledZCs(S,(0x1748+506-0x1942));for(i=(0x398+3045-0xf7d);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x459+2930-0xfcb));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x97b+6130-0x216d)]==-1.0){ssSetSampleTime(S,(0x848+700-0xb04),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0xecf+65-0xf10),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x111b+1681-0x17ac),mxGetPr(z3832b85a32)[(0x2372+19-0x2385)]);ssSetOffsetTime(S,(0xb4d+6749-0x25aa),0.0);}}static void sg_ModelLoad(SimStruct*S){
#ifndef MATLAB_MEX_FILE
volatile z867297d97e*z8052fadad2;void*bar2ptr;int moduleId=(int)mxGetScalar(z58f464b4bb);char*boardName=io3xxGetBoardNameSgLib(moduleId);if(!io3xxGetAddressSgLib((int32_t)(int)mxGetPr(z58f464b4bb)[(0x314+2971-0xeaf)],SG_FPGA_IO3XX_BAR2)){ssSetErrorStatus(S,pSgErrorStr);return;}uint32_t zf7ccd17be8=(0xc22+919-0xfb9);if(sg_fpga_io3xx_getCmBaseAddress(moduleId,EVENTS_CAPTURE_BASE,&zf7ccd17be8)){sprintf(msg,"\x25\x73\x20\x45\x76\x65\x6e\x74\x73\x20\x43\x61\x70\x74\x75\x72\x65\x20\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x4f\x66\x66\x73\x65\x74\x20\x6c\x6f\x6f\x6b\x75\x70\x20\x75\x6e\x73\x75\x63\x63\x65\x73\x73\x66\x75\x6c\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}bar2ptr=io3xxGetAddressSgLib((int32_t)(int)mxGetPr(z58f464b4bb)[(0xcc7+2359-0x15fe)],SG_FPGA_IO3XX_BAR2);z8052fadad2=(z867297d97e*)((uintptr_t)bar2ptr+(uintptr_t)zf7ccd17be8);ssSetPWorkValue(S,z0194338df7,(void*)z8052fadad2);if(sg_fpga_io3xx_checkCodeModuleVersion(z8052fadad2->version,z5bbcf8be2c,moduleId)){sprintf(msg,"\x25\x73\x20\x77\x72\x6f\x6e\x67\x20\x76\x65\x72\x73\x69\x6f\x6e\x20\x6f\x66\x20\x45\x76\x65\x6e\x74\x73\x20\x43\x61\x70\x74\x75\x72\x65\x20\x63\x6f\x64\x65\x20\x6d\x6f\x64\x75\x6c\x65\x21" "\n",boardName);sprintf(msg,"\x65\x78\x70\x65\x63\x74\x65\x64\x20\x6d\x61\x6a\x6f\x72\x20\x76\x65\x72\x73\x69\x6f\x6e\x3a\x20\x25\x75\x2c\x20\x64\x65\x74\x65\x63\x74\x65\x64\x20\x6d\x61\x6a\x6f\x72\x20\x76\x65\x72\x73\x69\x6f\x6e\x3a\x20\x25\x75" "\n",z5bbcf8be2c,z8052fadad2->version);ssSetErrorStatus(S,msg);return;}
#endif
}static void sg_ModelStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_t i;uint32_t channel,enable,zaa88aaf485;volatile z867297d97e*z8052fadad2;z8052fadad2=(z867297d97e*)(ssGetPWorkValue(S,z0194338df7));enable=(0x1078+2310-0x197e);for(i=(0x761+513-0x962);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0xa54+7148-0x263f);enable|=((0x13b+2826-0xc44)<<channel);zaa88aaf485=(uint32_t)(mxGetPr(z1120e7330e)[(0xb45+4064-0x1b25)]*mxGetPr(z19b9dfa260)[(0x8f7+1965-0x10a4)]);z8052fadad2->zaa88aaf485[channel]=zaa88aaf485;}z8052fadad2->enable|=enable;
#endif
}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_t i,channel,zc899ce874c;uint32_t z8f9159c57a;double*z9b805f4b4c,*z30c09d7708;double start,length,stop;volatile z867297d97e*z8052fadad2;z8052fadad2=(z867297d97e*)(ssGetPWorkValue(S,z0194338df7));z8052fadad2->zb871a780a7=(0x1019+2525-0x19f5);z8052fadad2->zb871a780a7=(0x1a19+920-0x1db1);z8f9159c57a=(uint32_t)mxGetPr(z9025f678b8)[(0xfc2+4274-0x2074)];z9b805f4b4c=NULL;z30c09d7708=NULL;zc899ce874c=(0x74c+4681-0x1995);if((uint32_t)mxGetPr(z7406514f86)[(0xe59+2610-0x188b)]){z9b805f4b4c=(double*)ssGetOutputPortSignal(S,zc899ce874c);zc899ce874c++;}if((uint32_t)mxGetPr(z8c2f8041a4)[(0x11f0+4280-0x22a8)]){z30c09d7708=(double*)ssGetOutputPortSignal(S,zc899ce874c);zc899ce874c++;}for(i=(0x787+875-0xaf2);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x15f6+191-0x16b4);if(z8f9159c57a>(0xbfd+5552-0x21ad)){start=((double)(z8052fadad2->zd1e68ee73d[channel]))/za9059c32c3*720.0;if((uint32_t)mxGetPr(z7406514f86)[(0xb0c+2262-0x13e2)]){z9b805f4b4c[z8f9159c57a*i+(0x13b7+1297-0x18c8)]=start;}if((uint32_t)mxGetPr(z8c2f8041a4)[(0x18d9+2695-0x2360)]){stop=((double)(z8052fadad2->z344c5ac569[channel]))/za9059c32c3*720.0;if(start>stop){length=720.0-start+stop;}else{length=stop-start;}z30c09d7708[z8f9159c57a*i+(0xa35+1564-0x1051)]=length;}}if(z8f9159c57a>(0x679+5932-0x1da4)){start=((double)(z8052fadad2->z37b591a7d2[channel]))/za9059c32c3*720.0;if((uint32_t)mxGetPr(z7406514f86)[(0x77d+5301-0x1c32)]){z9b805f4b4c[z8f9159c57a*i+(0x8fa+390-0xa7f)]=start;}if((uint32_t)mxGetPr(z8c2f8041a4)[(0x1a55+1921-0x21d6)]){stop=((double)(z8052fadad2->zbb26572b92[channel]))/za9059c32c3*720.0;if(start>stop){length=720.0-start+stop;}else{length=stop-start;}z30c09d7708[z8f9159c57a*i+(0x1d8d+1943-0x2523)]=length;}}if(z8f9159c57a>(0x3da+3984-0x1368)){start=((double)(z8052fadad2->z71b534306c[channel]))/za9059c32c3*720.0;if((uint32_t)mxGetPr(z7406514f86)[(0x2cc+6402-0x1bce)]){z9b805f4b4c[z8f9159c57a*i+(0x103d+2616-0x1a73)]=start;}if((uint32_t)mxGetPr(z8c2f8041a4)[(0x15a6+3054-0x2194)]){stop=((double)(z8052fadad2->za861233e50[channel]))/za9059c32c3*720.0;if(start>stop){length=720.0-start+stop;}else{length=stop-start;}z30c09d7708[z8f9159c57a*i+(0xc19+2519-0x15ee)]=length;}}if(z8f9159c57a>(0x1065+2779-0x1b3d)){start=((double)(z8052fadad2->z072695491e[channel]))/za9059c32c3*720.0;if((uint32_t)mxGetPr(z7406514f86)[(0x987+5371-0x1e82)]){z9b805f4b4c[z8f9159c57a*i+(0xa0b+2885-0x154d)]=start;}if((uint32_t)mxGetPr(z8c2f8041a4)[(0x956+3990-0x18ec)]){stop=((double)(z8052fadad2->zeab8425154[channel]))/za9059c32c3*720.0;if(start>stop){length=720.0-start+stop;}else{length=stop-start;}z30c09d7708[z8f9159c57a*i+(0x82+7514-0x1dd9)]=length;}}}
#endif
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE
volatile z867297d97e*z8052fadad2;z8052fadad2=(z867297d97e*)(ssGetPWorkValue(S,z0194338df7));z8052fadad2->enable=(0x2d+2485-0x9e2);
#endif
}
#include "sg_sfcn_glue.h"   

