// Copyright 2006-2026 Speedgoat GmbH

#define 	S_FUNCTION_LEVEL 	(0x398+8398-0x2464)
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_fpga_i2csread_sf_a1
#include 	<stddef.h>
#include 	<stdlib.h>
#include 	"simstruc.h" 
#ifdef 		MATLAB_MEX_FILE
#include 	"mex.h"
#endif
#ifndef         MATLAB_MEX_FILE
#include        "sg_common.h"
#include        "sg_fpga_io3xx_util.h"
#include        "sg_printf.h"
#endif
#include        "sg_callback.h"
#define ze13f49a01f                 ssGetSFcnParam(S, (0x16a6+2565-0x20ab)) 
#define za9d8fb6bcf                   ssGetSFcnParam(S, (0x592+1408-0xb11)) 
#define zd7a15617ca                 ssGetSFcnParam(S, (0x1dd0+195-0x1e91))
#define z3832b85a32                 ssGetSFcnParam(S, (0xe85+678-0x1128))
#define z2e48a9d37f    ssGetSFcnParam(S, (0x8f8+4790-0x1baa))
#define z8bc90a906d       ssGetSFcnParam(S, (0x1bd2+911-0x1f5c))
#define z38d6bfb542 ssGetSFcnParam(S, (0x8f0+5053-0x1ca7))
#define zdf24515981                                 ((0x5a+3045-0xc38))
#define z2e6483d505              ((0x132+2429-0xaaf))
#define zc5ce4cb81a              ((0x16f8+3948-0x2664))
#define z2b17e2ee3b              ((0xdea+4917-0x211e))
#define z0194338df7         ((0xcb9+2537-0x16a2))
static char_T msg[(0xc85+3119-0x17b4)];typedef struct z4ffeb08593{uint32_T enable;uint32_T clear;uint32_T z553991aa78;uint32_T z039626e71b[(0xa4d+7349-0x26e2)];uint32_T z7515281f6c[(0x8a4+6123-0x206f)];uint32_T zd6e550175f[(0xb78+466-0xd2a)];uint32_T z2678040317[(0x675+2901-0x11aa)];uint32_T skipRegAddress;uint32_T version;uint32_T ze46c7dc275[(0x635+4474-0x178f)];}z4ffeb08593;static void mdlInitializeSizes(SimStruct*S){uint32_T i,z49c1c6abb8;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0xa10+2754-0x14d2));ssSetNumDiscStates(S,(0x8c3+6633-0x22ac));z49c1c6abb8=(0x1bc+7028-0x1d2f);if(mxGetPr(z2e48a9d37f)[(0x1c3d+1167-0x20cc)]){z49c1c6abb8++;}if(mxGetPr(z8bc90a906d)[(0x2d4+8619-0x247f)]){z49c1c6abb8++;}if(mxGetPr(z38d6bfb542)[(0x312+4383-0x1431)]){z49c1c6abb8++;}if(!ssSetNumOutputPorts(S,z49c1c6abb8)){return;}z49c1c6abb8=(0x12b1+1351-0x17f8);ssSetOutputPortDataType(S,z49c1c6abb8,SS_DOUBLE);ssSetOutputPortWidth(S,z49c1c6abb8,mxGetN(zd7a15617ca));z49c1c6abb8++;if(mxGetPr(z2e48a9d37f)[(0x668+8343-0x26ff)]){ssSetOutputPortDataType(S,z49c1c6abb8,SS_BOOLEAN);ssSetOutputPortWidth(S,z49c1c6abb8,mxGetN(zd7a15617ca));z49c1c6abb8++;}if(mxGetPr(z8bc90a906d)[(0x1203+2369-0x1b44)]){ssSetOutputPortDataType(S,z49c1c6abb8,SS_DOUBLE);ssSetOutputPortWidth(S,z49c1c6abb8,(0x2db+965-0x69f));z49c1c6abb8++;}if(mxGetPr(z38d6bfb542)[(0xa11+4160-0x1a51)]){ssSetOutputPortDataType(S,z49c1c6abb8,SS_BOOLEAN);ssSetOutputPortWidth(S,z49c1c6abb8,(0x2093+329-0x21db));z49c1c6abb8++;}if(!ssSetNumInputPorts(S,(0x493+3234-0x1135))){return;}ssSetNumSampleTimes(S,(0x458+3078-0x105d));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x3f2+4137-0x141b));ssSetNumNonsampledZCs(S,(0x21fb+1001-0x25e4));for(i=(0x1103+184-0x11bb);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0xb3b+3776-0x19fb));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x709+4498-0x189b)]==-1.0){ssSetSampleTime(S,(0x12ec+2624-0x1d2c),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x1bbc+161-0x1c5d),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x861+48-0x891),mxGetPr(z3832b85a32)[(0xb8+6834-0x1b6a)]);ssSetOffsetTime(S,(0x26b+5306-0x1725),0.0);}}static void sg_ModelLoad(SimStruct*S){
#ifndef MATLAB_MEX_FILE
volatile z4ffeb08593*z77b62f8983;int moduleId=(int)mxGetScalar(ze13f49a01f);char*boardName=io3xxGetBoardNameSgLib(moduleId);if(!io3xxGetAddressSgLib((int32_t)(int)mxGetPr(ze13f49a01f)[(0x1c9+788-0x4dd)],SG_FPGA_IO3XX_BAR2)){ssSetErrorStatus(S,pSgErrorStr);return;}uint32_t zf7ccd17be8=(0x20+6328-0x18d8);if(sg_fpga_io3xx_getCmBaseAddress(moduleId,I2CS_BASE,&zf7ccd17be8)){sprintf(msg,"\x25\x73\x20\x49\x32\x43\x53\x20\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x4f\x66\x66\x73\x65\x74\x20\x6c\x6f\x6f\x6b\x75\x70\x20\x75\x6e\x73\x75\x63\x63\x65\x73\x73\x66\x75\x6c\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}z77b62f8983=(volatile z4ffeb08593*)((uintptr_t)io3xxGetAddressSgLib((int32_t)(int)mxGetPr(ze13f49a01f)[(0x1250+3603-0x2063)],SG_FPGA_IO3XX_BAR2)+zf7ccd17be8);ssSetPWorkValue(S,z0194338df7,(void*)z77b62f8983);
#endif
}static void sg_ModelStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE	
#endif
}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_T i,channel,data,z8bd205f0ee;real_T*y=NULL,*zf16e212a0d=NULL;boolean_T*zf7c5a7f624=NULL,*zc82893a8ac=NULL;int ze0f8e1c159=(0x18bf+617-0x1b28);volatile z4ffeb08593*z77b62f8983=(volatile z4ffeb08593*)(ssGetPWorkValue(S,z0194338df7));y=(real_T*)ssGetOutputPortSignal(S,ze0f8e1c159);ze0f8e1c159++;if((uint32_t)mxGetPr(z2e48a9d37f)[(0x345+348-0x4a1)]){zf7c5a7f624=(boolean_T*)ssGetOutputPortSignal(S,ze0f8e1c159++);}if((uint32_t)mxGetPr(z8bc90a906d)[(0x638+5844-0x1d0c)]){zf16e212a0d=(real_T*)ssGetOutputPortSignal(S,ze0f8e1c159++);}if((uint32_t)mxGetPr(z38d6bfb542)[(0xcc1+2419-0x1634)]){zc82893a8ac=(boolean_T*)ssGetOutputPortSignal(S,ze0f8e1c159++);}channel=(uint32_T)mxGetPr(za9d8fb6bcf)[(0x65+9612-0x25f1)]-(0x1893+2506-0x225c);for(i=(0x448+4454-0x15ae);i<mxGetN(zd7a15617ca);i++){z77b62f8983->z7515281f6c[channel]=(uint32_T)mxGetPr(zd7a15617ca)[i]-(0x9a9+5987-0x210b);data=z77b62f8983->z2678040317[channel];y[i]=(real_T)(data&(0x4c7+8630-0x257e));if((uint32_t)mxGetPr(z2e48a9d37f)[(0x1625+3777-0x24e6)]){zf7c5a7f624[i]=(boolean_T)((data>>(0x127a+2557-0x1c6f))&(0xa59+4002-0x19fa));}}z8bd205f0ee=(0xacc+3653-0x1911);if((uint32_t)mxGetPr(z8bc90a906d)[(0x9c6+4920-0x1cfe)]||(uint32_t)mxGetPr(z38d6bfb542)[(0x1957+1146-0x1dd1)]){z8bd205f0ee=z77b62f8983->ze46c7dc275[channel];}if((uint32_t)mxGetPr(z8bc90a906d)[(0x5ac+7712-0x23cc)]){zf16e212a0d[(0xe19+5320-0x22e1)]=(real_T)(z8bd205f0ee&(0x15c6+2866-0x1ff9));}if((uint32_t)mxGetPr(z38d6bfb542)[(0x517+8223-0x2536)]){zc82893a8ac[(0x2d6+583-0x51d)]=(boolean_T)((z8bd205f0ee>>(0xd79+375-0xee8))&(0x906+3610-0x171f));}
#endif
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE   
#endif
}
#include "sg_sfcn_glue.h"   

