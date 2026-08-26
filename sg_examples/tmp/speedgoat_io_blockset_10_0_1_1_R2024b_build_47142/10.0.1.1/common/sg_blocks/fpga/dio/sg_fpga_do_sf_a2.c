// Copyright 2006-2026 Speedgoat GmbH

#define 	S_FUNCTION_LEVEL 	(0xdf7+3127-0x1a2c)
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_fpga_do_sf_a2
#include 	<stddef.h>
#include 	<stdlib.h>
#include    <stdint.h>
#include    <stdbool.h>
#include 	"simstruc.h"
#ifdef 		MATLAB_MEX_FILE
#include 	"mex.h"
#endif
#ifndef   MATLAB_MEX_FILE
#include  "sg_common.h"
#include  "sg_fpga_io3xx_util.h"
#include  "sg_printf.h"
#include  "sg_fpga_cm_dio.h"
#endif
#include  "sg_callback.h"
#define ze13f49a01f         ssGetSFcnParam(S, (0x584+4857-0x187d)) 
#define za9d8fb6bcf           ssGetSFcnParam(S, (0x187d+3293-0x2559)) 
#define zeb9408a20d        ssGetSFcnParam(S, (0x6a8+2003-0xe79))
#define zc8bbaa6115             ssGetSFcnParam(S, (0x605+180-0x6b6))
#define zf80b27df71              ssGetSFcnParam(S, (0xb57+2300-0x144f))
#define z3832b85a32         ssGetSFcnParam(S, (0x1a8+6719-0x1be2))
#define zdf24515981                         ((0x121+8049-0x208c))
#define z2e6483d505              ((0xf40+3339-0x1c4a))
#define zc5ce4cb81a              ((0x855+1786-0xf4f))
#define z2b17e2ee3b              ((0x106d+4510-0x2209))
#define z2bb97589e4       ((0x7b+3618-0xe9d))
#define z0194338df7         ((0xe8b+222-0xf69))
#define z220e066c7e         ((0x2151+1399-0x26c7))
static char msg[(0x1e1b+785-0x202c)];static void mdlInitializeSizes(SimStruct*S){uint32_t i,za0df33019b;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x111f+747-0x140a));ssSetNumDiscStates(S,(0x1209+2527-0x1be8));if((uint32_t)mxGetPr(zeb9408a20d)[(0x9c4+6166-0x21da)]){if(!ssSetNumInputPorts(S,(0x812+4093-0x180e))){return;}ssSetInputPortWidth(S,(0xbc6+6668-0x25d2),(uint32_t)mxGetN(za9d8fb6bcf));ssSetInputPortDirectFeedThrough(S,(0x9f8+5129-0x1e01),(0x1112+2883-0x1c54));ssSetInputPortRequiredContiguous(S,(0x44b+8634-0x2605),(0x9ab+2434-0x132c));}else{za0df33019b=(uint32_t)mxGetN(za9d8fb6bcf);if(!ssSetNumInputPorts(S,za0df33019b)){return;}for(i=(0x2231+10-0x223b);i<za0df33019b;i++){ssSetInputPortWidth(S,i,(0x1785+3219-0x2417));ssSetInputPortDirectFeedThrough(S,i,(0x1e15+276-0x1f28));ssSetInputPortRequiredContiguous(S,i,(0x3cb+3976-0x1352));}}if(!ssSetNumOutputPorts(S,(0x1004+4843-0x22ef))){return;}ssSetNumSampleTimes(S,(0x4ba+2427-0xe34));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x15+9040-0x2365));ssSetNumNonsampledZCs(S,(0x81b+152-0x8b3));for(i=(0x7ff+6171-0x201a);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x1df3+463-0x1fc2));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x3e7+4901-0x170c)]==-1.0){ssSetSampleTime(S,(0x2168+1013-0x255d),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x904+625-0xb75),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0xc8d+1340-0x11c9),mxGetPr(z3832b85a32)[(0xa0f+6079-0x21ce)]);ssSetOffsetTime(S,(0x42a+1845-0xb5f),0.0);}}static void sg_ModelLoad(SimStruct*S){
#ifndef MATLAB_MEX_FILE
volatile dio*z84bcaa13e8;dioState_t*z8697219b1f;if(!io3xxGetAddressSgLib((int32_t)(int)mxGetPr(ze13f49a01f)[(0x6b9+4601-0x18b2)],SG_FPGA_IO3XX_BAR2)){ssSetErrorStatus(S,pSgErrorStr);return;}uint32_t zf7ccd17be8=(0x537+7213-0x2164);if(sg_fpga_io3xx_getCmBaseAddress((int)mxGetPr(ze13f49a01f)[(0xb33+6493-0x2490)],DIO_BASE,&zf7ccd17be8)){sprintf(msg,"\x25\x73\x20\x44\x49\x4f\x20\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x4f\x66\x66\x73\x65\x74\x20\x6c\x6f\x6f\x6b\x75\x70\x20\x75\x6e\x73\x75\x63\x63\x65\x73\x73\x66\x75\x6c\x21" "\n",io3xxGetBoardNameSgLib((int)mxGetPr(ze13f49a01f)[(0x4b3+3644-0x12ef)]));ssSetErrorStatus(S,msg);return;}z84bcaa13e8=(volatile dio*)((uintptr_t)io3xxGetAddressSgLib((int32_t)(int)mxGetPr(ze13f49a01f)[(0x79c+2103-0xfd3)],SG_FPGA_IO3XX_BAR2)+zf7ccd17be8);ssSetPWorkValue(S,z0194338df7,(void*)z84bcaa13e8);io3xxGetPointerDioStateSgLib((int)mxGetPr(ze13f49a01f)[(0x11ba+4211-0x222d)],&z8697219b1f);ssSetPWorkValue(S,z220e066c7e,z8697219b1f);
#endif
}void sg_ModelStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_t i,channel,z79d0db3ad6,z56ed9aceb1,zd3a118e8e8;uint32_t version,z97287efa46,zeeeba54a90;volatile dio*z84bcaa13e8;dioState_t*z8697219b1f;uint32_t z33b21830ce[NBR_DIO_CH_DIV_32];uint32_t ze563fb1859[NBR_DIO_CH_DIV_32];uint32_t z612b4ef0fe[NBR_DIO_CH_DIV_32];uint32_t z2b7c2286a4[NBR_DIO_CH_DIV_32];z84bcaa13e8=(dio*)ssGetPWorkValue(S,z0194338df7);z8697219b1f=(dioState_t*)ssGetPWorkValue(S,z220e066c7e);version=z84bcaa13e8->half[(0x1d7+7372-0x1ea3)].version;z97287efa46=((version&1047552)>>(0xc54+5801-0x22f3));zeeeba54a90=((version&(0x1d20+910-0x1caf))>>(0x107d+1634-0x16df));if(z97287efa46==(0x4ba+2882-0xffb)&&zeeeba54a90>=(0xb4+4391-0x11d7)){zd3a118e8e8=NBR_DIO_CH_DIV_32;}else{zd3a118e8e8=NBR_DIO_CH_DIV_32_OLD;}ssSetIWorkValue(S,z2bb97589e4,zd3a118e8e8);memset(z33b21830ce,(0x1fc9+1040-0x23d9),NBR_DIO_CH_DIV_32*sizeof(uint32_t));memset(ze563fb1859,(0x1f28+587-0x2173),NBR_DIO_CH_DIV_32*sizeof(uint32_t));memset(z612b4ef0fe,(0x5a6+2690-0x1028),NBR_DIO_CH_DIV_32*sizeof(uint32_t));memset(z2b7c2286a4,(0x6c+2941-0xbe9),NBR_DIO_CH_DIV_32*sizeof(uint32_t));for(i=(0x5ea+2806-0x10e0);i<(uint32_t)mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x18d6+1536-0x1ed5);channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0xb54+6493-0x24b0);if(channel>=zd3a118e8e8*(0x696+793-0x98f)){sprintf(msg,"\x45\x72\x72\x6f\x72\x3a\x20\x75\x6e\x73\x75\x70\x70\x6f\x72\x74\x65\x64\x20\x63\x68\x61\x6e\x6e\x65\x6c\x20\x25\x64\x2e",channel);ssSetErrorStatus(S,msg);return;}z79d0db3ad6=channel/(0xff1+3386-0x1d0b);z56ed9aceb1=channel-z79d0db3ad6*(0x1cb6+2304-0x2596);z33b21830ce[z79d0db3ad6]|=((0x745+911-0xad3)<<z56ed9aceb1);ze563fb1859[z79d0db3ad6]|=((0x1a9f+2235-0x2359)<<z56ed9aceb1);}sg_lockMutex(z8697219b1f->mutex);for(i=(0x1784+1920-0x1f04);i<zd3a118e8e8;i++){z8697219b1f->direction[i]|=z33b21830ce[i];z8697219b1f->active[i]|=ze563fb1859[i];z84bcaa13e8->half[i/(0x50+7879-0x1f13)].dir[i%(0x13e4+887-0x1757)]=z8697219b1f->direction[i];z84bcaa13e8->half[i/(0x391+6725-0x1dd2)].select[i%(0xe09+581-0x104a)]=z8697219b1f->active[i];}sg_unlockMutex(z8697219b1f->mutex);for(i=(0x1904+921-0x1c9d);i<(uint32_t)mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0xf6+3209-0xd7e);z79d0db3ad6=channel/(0x1d8+5632-0x17b8);z56ed9aceb1=channel-z79d0db3ad6*(0x1136+4853-0x240b);if((uint32_t)mxGetPr(zf80b27df71)[i]){z612b4ef0fe[z79d0db3ad6]|=((0x1fc+6442-0x1b25)<<z56ed9aceb1);}else{z2b7c2286a4[z79d0db3ad6]|=((0x18f6+747-0x1be0)<<z56ed9aceb1);}}sg_lockMutex(z8697219b1f->mutex);for(i=(0xc81+4620-0x1e8d);i<zd3a118e8e8;i++){z8697219b1f->outputState[i]|=z612b4ef0fe[i];z8697219b1f->outputState[i]&=~z2b7c2286a4[i];z84bcaa13e8->half[i/(0x1ab5+1152-0x1f31)].dio[i%(0xa20+4733-0x1c99)]=z8697219b1f->outputState[i];}sg_unlockMutex(z8697219b1f->mutex);
#endif
}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_t i,channel,z79d0db3ad6,z56ed9aceb1;real_T data;real_T*in;volatile dio*z84bcaa13e8;dioState_t*z8697219b1f;z84bcaa13e8=(dio*)ssGetPWorkValue(S,z0194338df7);z8697219b1f=(dioState_t*)ssGetPWorkValue(S,z220e066c7e);uint32_t z612b4ef0fe[NBR_DIO_CH_DIV_32];uint32_t z2b7c2286a4[NBR_DIO_CH_DIV_32];uint32_t zbcf4460cc4;memset(z612b4ef0fe,(0xad8+1129-0xf41),NBR_DIO_CH_DIV_32*sizeof(uint32_t));memset(z2b7c2286a4,(0xc9f+3686-0x1b05),NBR_DIO_CH_DIV_32*sizeof(uint32_t));for(i=(0x800+7425-0x2501);i<(uint32_t)mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x157c+1375-0x1ada);if((uint32_t)mxGetPr(zeb9408a20d)[(0x44f+258-0x551)]){in=(real_T*)ssGetInputPortSignal(S,(0xd3b+1911-0x14b2));data=in[i];}else{in=(real_T*)ssGetInputPortSignal(S,i);data=in[(0x5+3642-0xe3f)];}z79d0db3ad6=channel/(0x18aa+631-0x1b01);z56ed9aceb1=channel-z79d0db3ad6*(0x512+7224-0x212a);if(data>0.5){z612b4ef0fe[z79d0db3ad6]|=((0x18a1+3172-0x2504)<<z56ed9aceb1);}else{z2b7c2286a4[z79d0db3ad6]|=((0x37b+3980-0x1306)<<z56ed9aceb1);}}sg_lockMutex(z8697219b1f->mutex);for(i=(0x706+2828-0x1212);i<(uint32_t)ssGetIWorkValue(S,z2bb97589e4);i++){zbcf4460cc4=z8697219b1f->outputState[i];zbcf4460cc4|=z612b4ef0fe[i];zbcf4460cc4&=~z2b7c2286a4[i];if(zbcf4460cc4!=z8697219b1f->outputState[i]){z84bcaa13e8->half[i/(0x1d83+2421-0x26f4)].dio[i%(0xa69+4123-0x1a80)]=zbcf4460cc4;z8697219b1f->outputState[i]=zbcf4460cc4;}}sg_unlockMutex(z8697219b1f->mutex);
#endif
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_t i,channel,z79d0db3ad6,z56ed9aceb1;volatile dio*z84bcaa13e8;dioState_t*z8697219b1f;uint32_t z612b4ef0fe[NBR_DIO_CH_DIV_32];uint32_t z2b7c2286a4[NBR_DIO_CH_DIV_32];memset(z612b4ef0fe,(0x2b6+5853-0x1993),NBR_DIO_CH_DIV_32*sizeof(uint32_t));memset(z2b7c2286a4,(0xe06+6016-0x2586),NBR_DIO_CH_DIV_32*sizeof(uint32_t));z84bcaa13e8=(dio*)(ssGetPWorkValue(S,z0194338df7));z8697219b1f=(dioState_t*)ssGetPWorkValue(S,z220e066c7e);for(i=(0x764+7103-0x2323);i<(uint32_t)mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x17e1+3569-0x25d1);if((uint32_t)mxGetPr(zc8bbaa6115)[i]){z79d0db3ad6=channel/(0x1b0b+11-0x1af6);z56ed9aceb1=channel-z79d0db3ad6*(0x1338+3344-0x2028);if((uint32_t)mxGetPr(zf80b27df71)[i]){z612b4ef0fe[z79d0db3ad6]|=((0xa3d+2093-0x1269)<<z56ed9aceb1);}else{z2b7c2286a4[z79d0db3ad6]|=((0x2045+1388-0x25b0)<<z56ed9aceb1);}}}sg_lockMutex(z8697219b1f->mutex);for(i=(0x205a+1457-0x260b);i<(uint32_t)ssGetIWorkValue(S,z2bb97589e4);i++){z8697219b1f->outputState[i]|=z612b4ef0fe[i];z8697219b1f->outputState[i]&=~z2b7c2286a4[i];z84bcaa13e8->half[i/(0x10e8+3515-0x1e9f)].dio[i%(0x5f4+5879-0x1ce7)]=z8697219b1f->outputState[i];}sg_unlockMutex(z8697219b1f->mutex);
#endif
}
#include "sg_sfcn_glue.h"   

