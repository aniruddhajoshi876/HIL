// Copyright 2006-2026 Speedgoat GmbH

#define 	S_FUNCTION_LEVEL 	(0x8e2+3374-0x160e)
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_fpga_cam_decoder_sf_1
#include 	<stddef.h>
#include 	<stdlib.h>
#include    <stdint.h>
#include    <stdbool.h>
#include 	"simstruc.h" 
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif
#ifndef MATLAB_MEX_FILE
#include "sg_common.h"
#include "sg_fpga_io3xx_util.h"
#include "sg_printf.h"
#endif
#include "sg_callback.h"
typedef enum{CHANNEL,ze344b15ab1,z6c561dc4d0,ID,zdf24515981}z152e902856;
#define za9d8fb6bcf           ssGetSFcnParam(S, CHANNEL) 
#define z3832b85a32         ssGetSFcnParam(S, ze344b15ab1)
#define z7cd927ffe6       ssGetSFcnParam(S, z6c561dc4d0) 
#define z58f464b4bb                ssGetSFcnParam(S, ID) 
#define z2e6483d505            (0x16ff+2526-0x20dd)
#define zc5ce4cb81a            (0x366+4954-0x16c0)
#define z2b17e2ee3b            (0xf84+50-0xfb5)
#define z0194338df7       (0x112f+200-0x11f7)
#define z5bbcf8be2c          (0xbbb+5220-0x201e)
static char msg[(0x1e77+2424-0x26ef)];typedef volatile struct{uint32_t version;uint32_t enable;uint32_t z58a8cb195b;uint32_t zdb05105ebc[(0x1171+4954-0x24ab)];uint32_t z47a93282d4[(0x1ec+2046-0x9ca)];uint32_t z9ebfd36318[(0x1af3+985-0x1eac)];uint32_t z66db2d0400[(0x876+4518-0x19fc)];uint32_t z9dd6406a43[(0x5d1+6609-0x1f82)];uint32_t zbe4e604d65[(0x2f4+8837-0x2559)];uint32_t z249bdb356b[(0x137+6165-0x192c)];}zff3b76e06e;static void mdlInitializeSizes(SimStruct*S){uint32_t i,za0df33019b;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x2196+396-0x2322));ssSetNumDiscStates(S,(0x19fb+1916-0x2177));ssSetNumInputPorts(S,(0x1a6+1945-0x93f));za0df33019b=(0x20a3+1482-0x266b);ssSetNumOutputPorts(S,za0df33019b);for(i=(0x8b+7487-0x1dca);i<za0df33019b;i++){ssSetOutputPortWidth(S,i,mxGetN(za9d8fb6bcf));}ssSetNumSampleTimes(S,(0x1380+2959-0x1f0e));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x1701+2170-0x1f7b));ssSetNumNonsampledZCs(S,(0xcb3+925-0x1050));for(i=(0x1192+3035-0x1d6d);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x220b+1165-0x2698));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0xb21+4293-0x1be6)]==-1.0){ssSetSampleTime(S,(0x1057+2131-0x18aa),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x4a7+2232-0xd5f),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x13c+6303-0x19db),mxGetPr(z3832b85a32)[(0x1eba+752-0x21aa)]);ssSetOffsetTime(S,(0x255+8651-0x2420),0.0);}}static void sg_ModelLoad(SimStruct*S){
#ifndef MATLAB_MEX_FILE
zff3b76e06e*zb1d0380494;int moduleId=(int)mxGetScalar(z58f464b4bb);char*boardName=io3xxGetBoardNameSgLib(moduleId);void*bar2ptr;if(!io3xxGetAddressSgLib((int32_t)(int)mxGetPr(z58f464b4bb)[(0xa5d+5873-0x214e)],SG_FPGA_IO3XX_BAR2)){ssSetErrorStatus(S,pSgErrorStr);return;}uint32_t zf7ccd17be8=(0x177+2971-0xd12);if(sg_fpga_io3xx_getCmBaseAddress(moduleId,CAM_DECODER_BASE,&zf7ccd17be8)){sprintf(msg,"\x25\x73\x20\x43\x61\x6d\x20\x44\x65\x63\x6f\x64\x65\x72\x20\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x4f\x66\x66\x73\x65\x74\x20\x6c\x6f\x6f\x6b\x75\x70\x20\x75\x6e\x73\x75\x63\x63\x65\x73\x73\x66\x75\x6c\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}bar2ptr=io3xxGetAddressSgLib((int32_t)(int)mxGetPr(z58f464b4bb)[(0x1b16+675-0x1db9)],SG_FPGA_IO3XX_BAR2);zb1d0380494=(zff3b76e06e*)((uintptr_t)bar2ptr+(uintptr_t)zf7ccd17be8);ssSetPWorkValue(S,z0194338df7,(void*)zb1d0380494);if(sg_isFirstModelLoad()){if(sg_fpga_io3xx_checkCodeModuleVersion(zb1d0380494->version,z5bbcf8be2c,moduleId)){sprintf(msg,"\x25\x73\x20\x77\x72\x6f\x6e\x67\x20\x76\x65\x72\x73\x69\x6f\x6e\x20\x6f\x66\x20\x43\x61\x6d\x20\x44\x65\x63\x6f\x64\x65\x72\x20\x63\x6f\x64\x65\x20\x6d\x6f\x64\x75\x6c\x65\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}}
#endif  
}static void sg_ModelStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_t i;uint32_t channel,enable;zff3b76e06e*zb1d0380494;zb1d0380494=(zff3b76e06e*)(ssGetPWorkValue(S,z0194338df7));enable=(0x853+1149-0xcd0);for(i=(0x2e1+1484-0x8ad);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x47d+6883-0x1f5f);enable|=((0x5e6+8310-0x265b)<<channel);}zb1d0380494->enable|=enable;
#endif
}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_t i,channel,z34a675f13b,zb871a780a7;double*ze813527a99,*z2b26864496;double za531b53c76[(0x1d72+1390-0x22df)],za79ff3b1e4[(0x7ed+2593-0x120d)],z0deefe7e25[(0x32+8852-0x22c5)],za247c6e507[(0xb16+606-0xd73)];zff3b76e06e*zb1d0380494;zb1d0380494=(zff3b76e06e*)(ssGetPWorkValue(S,z0194338df7));zb871a780a7=(0x4f4+3334-0x11fa);for(i=(0x1c67+1636-0x22cb);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x17ac+3533-0x2578);zb871a780a7|=((0xb5a+5166-0x1f87)<<channel);}zb1d0380494->z58a8cb195b=zb871a780a7;zb1d0380494->z58a8cb195b=(0x27c+3560-0x1064);z34a675f13b=(0x395+812-0x6c1);ze813527a99=(double*)ssGetOutputPortSignal(S,z34a675f13b);z34a675f13b++;z2b26864496=(double*)ssGetOutputPortSignal(S,z34a675f13b);for(i=(0x10b0+4855-0x23a7);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x8e5+6896-0x23d4);za531b53c76[(0x1db2+1019-0x21ad)]=(double)zb1d0380494->zdb05105ebc[channel];z0deefe7e25[(0xf61+271-0x1070)]=(double)zb1d0380494->z47a93282d4[channel];za79ff3b1e4[(0x39b+6270-0x1c19)]=((double)zb1d0380494->z9ebfd36318[channel])*180.0/((double)mxGetPr(z7cd927ffe6)[i]);za247c6e507[(0x461+6961-0x1f92)]=((double)zb1d0380494->z66db2d0400[channel])*180.0/((double)mxGetPr(z7cd927ffe6)[i]);if(za531b53c76[(0x1315+213-0x13ea)]==(0xa97+7073-0x2636)){za79ff3b1e4[(0xcb9+2236-0x1575)]=za79ff3b1e4[(0x573+7462-0x2299)]+(0x1b73+2729-0x24b4);}if(z0deefe7e25[(0x444+3474-0x11d6)]==(0x129+4819-0x13fa)){za247c6e507[(0x19d8+3377-0x2709)]=za247c6e507[(0xf21+172-0xfcd)]+(0x12bf+92-0x11b3);}ze813527a99[i]=za79ff3b1e4[(0x970+5969-0x20c1)]+(double)zb1d0380494->z9dd6406a43[channel]/(double)zb1d0380494->z249bdb356b[channel]*180.0/((double)mxGetPr(z7cd927ffe6)[i]);if(ze813527a99[i]>(0x527+4549-0x141c)){ze813527a99[i]=ze813527a99[i]-(0x480+3743-0x104f);}z2b26864496[i]=za247c6e507[(0x2a4+7746-0x20e6)]+(double)zb1d0380494->zbe4e604d65[channel]/(double)zb1d0380494->z249bdb356b[channel]*180.0/((double)mxGetPr(z7cd927ffe6)[i])-ze813527a99[i];}
#endif
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE
zff3b76e06e*zb1d0380494;zb1d0380494=(zff3b76e06e*)(ssGetPWorkValue(S,z0194338df7));zb1d0380494->enable=(0x23a+4183-0x1291);
#endif
}
#include "sg_sfcn_glue.h"   

