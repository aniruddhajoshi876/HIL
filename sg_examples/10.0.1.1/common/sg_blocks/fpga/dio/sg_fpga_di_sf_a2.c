// Copyright 2006-2026 Speedgoat GmbH

#define 	S_FUNCTION_LEVEL 	(0x3b7+2225-0xc66)
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_fpga_di_sf_a2
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
#define ze13f49a01f         ssGetSFcnParam(S, (0x1166+3915-0x20b1)) 
#define za9d8fb6bcf           ssGetSFcnParam(S, (0x66+3646-0xea3)) 
#define zeb9408a20d        ssGetSFcnParam(S, (0xd3b+99-0xd9c))
#define z3832b85a32         ssGetSFcnParam(S, (0x19cb+2057-0x21d1))
#define zdf24515981                         ((0x1821+2678-0x2293))
#define z2e6483d505              ((0x10ba+3818-0x1fa4))
#define zc5ce4cb81a              ((0x3c5+348-0x521))
#define z2b17e2ee3b              ((0xec+8146-0x20bc))
#define z0194338df7         ((0x16a9+1263-0x1b98))
#define z220e066c7e         ((0x63b+5331-0x1b0d))
#define TEST                    ((0x896+6865-0x2367))
static char msg[(0x1eec+1194-0x2296)];static void mdlInitializeSizes(SimStruct*S){uint32_t i,za0df33019b;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x1ec7+236-0x1fb3));ssSetNumDiscStates(S,(0x1b9+5307-0x1674));za0df33019b=(uint32_t)mxGetN(za9d8fb6bcf);if((uint32_t)mxGetPr(zeb9408a20d)[(0xc70+1675-0x12fb)]){if(!ssSetNumOutputPorts(S,(0xf2d+4102-0x1f32))){return;}ssSetOutputPortWidth(S,(0x8b5+6465-0x21f6),za0df33019b);}else{if(!ssSetNumOutputPorts(S,za0df33019b)){return;}for(i=(0x129b+4117-0x22b0);i<za0df33019b;i++){ssSetOutputPortWidth(S,i,(0x4a8+784-0x7b7));}}if(!ssSetNumInputPorts(S,(0xd60+4291-0x1e23))){return;}ssSetNumSampleTimes(S,(0x1376+3259-0x2030));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x9ab+1897-0x1114));ssSetNumNonsampledZCs(S,(0xe19+3834-0x1d13));for(i=(0xa5a+5753-0x20d3);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x110f+5495-0x2686));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x1ce8+1515-0x22d3)]==-1.0){ssSetSampleTime(S,(0x88+4930-0x13ca),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x8a4+1928-0x102c),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0xb5b+6126-0x2349),mxGetPr(z3832b85a32)[(0x15a5+1426-0x1b37)]);ssSetOffsetTime(S,(0x922+4377-0x1a3b),0.0);}}static void sg_ModelLoad(SimStruct*S){
#ifndef MATLAB_MEX_FILE
volatile dio*z84bcaa13e8;dioState_t*z8697219b1f;if(!io3xxGetAddressSgLib((int32_t)(int)mxGetPr(ze13f49a01f)[(0xda+8989-0x23f7)],SG_FPGA_IO3XX_BAR2)){ssSetErrorStatus(S,pSgErrorStr);return;}uint32_t zf7ccd17be8=(0xb94+3334-0x189a);if(sg_fpga_io3xx_getCmBaseAddress((int)mxGetPr(ze13f49a01f)[(0x88a+7540-0x25fe)],DIO_BASE,&zf7ccd17be8)){sprintf(msg,"\x25\x73\x20\x44\x49\x4f\x20\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x4f\x66\x66\x73\x65\x74\x20\x6c\x6f\x6f\x6b\x75\x70\x20\x75\x6e\x73\x75\x63\x63\x65\x73\x73\x66\x75\x6c\x21" "\n",io3xxGetBoardNameSgLib((int)mxGetPr(ze13f49a01f)[(0x92a+387-0xaad)]));ssSetErrorStatus(S,msg);return;}z84bcaa13e8=(dio*)((uintptr_t)io3xxGetAddressSgLib((int32_t)(int)mxGetPr(ze13f49a01f)[(0x169+7547-0x1ee4)],SG_FPGA_IO3XX_BAR2)+zf7ccd17be8);io3xxGetPointerDioStateSgLib((int)mxGetPr(ze13f49a01f)[(0xe13+6021-0x2598)],&z8697219b1f);ssSetPWorkValue(S,z220e066c7e,z8697219b1f);ssSetPWorkValue(S,z0194338df7,(void*)z84bcaa13e8);
#if TEST
SG_PRINTF(INFO,"\x74\x65\x73\x74\x31\x3a\x20\x30\x78\x25\x58" "\n",z84bcaa13e8->half[(0x2b0+3611-0x10cb)].test1);SG_PRINTF(INFO,"\x74\x65\x73\x74\x32\x3a\x20\x30\x78\x25\x58" "\n",z84bcaa13e8->half[(0x19e8+2656-0x2448)].test2);z84bcaa13e8->half[(0x1d36+1625-0x238f)].test2=2863311530;SG_PRINTF(INFO,"\x74\x65\x73\x74\x32\x3a\x20\x30\x78\x25\x58" "\n",z84bcaa13e8->half[(0x71b+4274-0x17cd)].test2);
#endif
SG_PRINTF(DEBUG,"\x44\x49\x20\x74\x65\x73\x74\x31\x3a\x20\x30\x78\x25\x58" "\n",z84bcaa13e8->half[(0x545+6858-0x200f)].test1);SG_PRINTF(DEBUG,"\x44\x49\x20\x76\x65\x72\x73\x69\x6f\x6e\x3a\x20\x30\x78\x25\x58" "\n",z84bcaa13e8->half[(0x23e0+734-0x26be)].version);
#endif
}void sg_ModelStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
volatile dio*z84bcaa13e8;dioState_t*z8697219b1f;uint32_t version,z97287efa46,zeeeba54a90;uint32_t i,channel,z79d0db3ad6,z56ed9aceb1,zd3a118e8e8;uint32_t ze563fb1859[NBR_DIO_CH_DIV_32];memset(ze563fb1859,(0xa74+6830-0x2522),NBR_DIO_CH_DIV_32*sizeof(uint32_t));z84bcaa13e8=(dio*)ssGetPWorkValue(S,z0194338df7);z8697219b1f=(dioState_t*)ssGetPWorkValue(S,z220e066c7e);version=z84bcaa13e8->half[(0x3f9+817-0x72a)].version;z97287efa46=((version&1047552)>>(0x1e79+845-0x21bc));zeeeba54a90=((version&(0x477+9441-0x2559))>>(0x708+2398-0x1066));if(z97287efa46==(0x761+7907-0x2643)&&zeeeba54a90>=(0xbf1+495-0xddc)){zd3a118e8e8=NBR_DIO_CH_DIV_32;}else{zd3a118e8e8=NBR_DIO_CH_DIV_32_OLD;}for(i=(0x1807+3383-0x253e);i<(uint32_t)mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x509+6577-0x1eb9);if(channel>=zd3a118e8e8*(0x8b9+3433-0x1602)){sprintf(msg,"\x45\x72\x72\x6f\x72\x3a\x20\x75\x6e\x73\x75\x70\x70\x6f\x72\x74\x65\x64\x20\x63\x68\x61\x6e\x6e\x65\x6c\x20\x25\x64\x2e",channel);ssSetErrorStatus(S,msg);return;}z79d0db3ad6=channel/(0x27a+4433-0x13ab);z56ed9aceb1=channel-z79d0db3ad6*(0x1bd+7714-0x1fbf);ze563fb1859[z79d0db3ad6]|=((0xa05+3790-0x18d2)<<z56ed9aceb1);}sg_lockMutex(z8697219b1f->mutex);for(i=(0xf8f+4205-0x1ffc);i<zd3a118e8e8;i++){z8697219b1f->active[i]|=ze563fb1859[i];z84bcaa13e8->half[i/(0x1798+3886-0x26c2)].select[i%(0x59b+1481-0xb60)]=z8697219b1f->active[i];}sg_unlockMutex(z8697219b1f->mutex);
#endif
}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_t channel,i,z4488144911,zbcab70ac37;uint8_t zfd727b2800[NBR_DIO_CH_DIV_32]={(0xd1+7377-0x1da2)};uint32_t z3fad3d9764[NBR_DIO_CH_DIV_32];real_T*out;volatile dio*z84bcaa13e8;z84bcaa13e8=(dio*)ssGetPWorkValue(S,z0194338df7);for(i=(0x379+2373-0xcbe);i<(uint32_t)mxGetN(za9d8fb6bcf);i++){uint32_t channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x8c1+5849-0x1f99);zfd727b2800[channel/(0x1f6c+1332-0x2480)]=(0xfb4+5553-0x2564);}for(i=(0x12e3+1060-0x1707);i<NBR_DIO_CH_DIV_32;i++){if(zfd727b2800[i]){z3fad3d9764[i]=z84bcaa13e8->half[i/(0x149+8795-0x23a0)].dio[i%(0xc16+2038-0x1408)];}}for(i=(0x630+4319-0x170f);i<(uint32_t)mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x937+2569-0x133f);z4488144911=channel/(0x3b9+1860-0xadd);zbcab70ac37=channel%(0x60+6807-0x1ad7);if((uint32_t)mxGetPr(zeb9408a20d)[(0x87+7991-0x1fbe)]){out=(real_T*)ssGetOutputPortSignal(S,(0x1866+1476-0x1e2a));out[i]=(z3fad3d9764[z4488144911]>>zbcab70ac37)&(0x1038+2670-0x1aa5);}else{out=(real_T*)ssGetOutputPortSignal(S,i);out[(0x3e1+5340-0x18bd)]=(z3fad3d9764[z4488144911]>>zbcab70ac37)&(0x45c+346-0x5b5);}}
#endif
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE
#endif
}
#include "sg_sfcn_glue.h"   

