// Copyright 2006-2026 Speedgoat GmbH

#define     S_FUNCTION_LEVEL    (0x50d+4684-0x1757)
#undef      S_FUNCTION_NAME
#define     S_FUNCTION_NAME    sg_fpga_inta_sf_2
#include    <stddef.h>
#include    <stdlib.h>
#include    <stdint.h>
#include    <stdbool.h>
#include    "simstruc.h"
#ifdef      MATLAB_MEX_FILE
#include    "mex.h"
#endif
#ifndef MATLAB_MEX_FILE
#include "sg_common.h"
#include "sg_fpga_io3xx_util.h"
#include "sg_printf.h"
#endif
#include "sg_callback.h"
#define ze13f49a01f           ssGetSFcnParam(S,(0xa7+6148-0x18ab))
#define za9d8fb6bcf             ssGetSFcnParam(S,(0xf4d+4415-0x208b))
#define z1120e7330e            ssGetSFcnParam(S,(0x405+4508-0x159f))
#define z644559a0a7               ssGetSFcnParam(S,(0x1a29+1601-0x2067))
#define za42e288061                ssGetSFcnParam(S,(0x1689+331-0x17d0))
#define z4d187edb3b      ssGetSFcnParam(S,(0x1e91+1224-0x2354))
#define z684fe3b765                 ssGetSFcnParam(S,(0x5e7+1142-0xa57))
#define z9efe7b3b47            ssGetSFcnParam(S,(0x233+5663-0x184b))
#define zc3fd540d44           ssGetSFcnParam(S,(0xe4f+5138-0x2259))
#define z824430e995                ssGetSFcnParam(S,(0x1353+3048-0x1f32))
#define z3832b85a32           ssGetSFcnParam(S,(0xa2c+5944-0x215a))
#define z19b9dfa260      ssGetSFcnParam(S,(0x476+6956-0x1f97))
#define zcca083e90d        ssGetSFcnParam(S,(0x7f4+840-0xb30))
#define z18b816e17c            ssGetSFcnParam(S,(0x3f4+2228-0xc9b))
#define zdf24515981                          ((0x5b7+2431-0xf28))
#define z2e6483d505              ((0xddd+1095-0x1223))
#define z7e2eeaa57c          ((0xe9b+56-0xed3))
#define zc5ce4cb81a              ((0x29c+9172-0x2660))
#define z2b17e2ee3b              ((0x796+3158-0x13eb))
#define z0194338df7         ((0x738+8050-0x26aa))
#define z5bbcf8be2c            (0xe37+5430-0x236b)
static char msg[(0xcbf+409-0xd58)];typedef struct{uint32_t enable;uint32_t event;uint32_t clear;uint32_t test1;uint32_t mode[(0x6dc+6356-0x1f90)];uint32_t delay[(0x5c3+5668-0x1bc7)];uint32_t zaa88aaf485[(0x922+919-0xc99)];uint32_t z16203ce901[(0x1d1+4855-0x14a8)];uint32_t zbea9f5f1a5[(0xd80+2957-0x18ed)];uint32_t zc0011fe779[(0x9ba+7213-0x25c7)];uint32_t z7294689cde[(0xffc+1729-0x169d)];uint32_t z5541dce2ea[(0x15d4+759-0x18ab)];uint32_t z9f1a7be944[(0x52a+6668-0x1f16)];uint32_t version;uint32_t ze1a82e7a19;uint32_t z75adbb7c26;uint32_t zb828f5ede4[(0x2f1+4563-0x14a4)];}z02171375f2;static void mdlInitializeSizes(SimStruct*S){uint32_t i,za0df33019b;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x1eea+1455-0x2499));ssSetNumDiscStates(S,(0x12b6+1008-0x16a6));if(!ssSetNumInputPorts(S,(0xa2d+5971-0x2180))){return;}za0df33019b=(0x1652+3150-0x22a0);if(mxGetPr(zcca083e90d)[(0x16e7+895-0x1a66)]){za0df33019b++;}if(mxGetPr(zc3fd540d44)[(0x2253+894-0x25d1)]){za0df33019b++;}if(mxGetPr(z824430e995)[(0xd7c+5175-0x21b3)]){za0df33019b++;}if(!ssSetNumOutputPorts(S,za0df33019b)){return;}for(i=(0x1a+6823-0x1ac1);i<za0df33019b;i++){ssSetOutputPortWidth(S,i,mxGetN(za9d8fb6bcf));}ssSetNumSampleTimes(S,(0x6f6+145-0x786));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x1870+643-0x1af3));ssSetNumNonsampledZCs(S,(0x8+7569-0x1d99));for(i=(0x7e7+3023-0x13b6);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x691+2013-0xe6e));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x1078+2309-0x197d)]==-1.0){ssSetSampleTime(S,(0xbd7+1872-0x1327),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x1719+142-0x17a7),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x530+6092-0x1cfc),mxGetPr(z3832b85a32)[(0x52c+1560-0xb44)]);ssSetOffsetTime(S,(0x13c3+2706-0x1e55),0.0);}}static void sg_ModelLoad(SimStruct*S){
#ifndef MATLAB_MEX_FILE
volatile z02171375f2*z79f5963ede;void*bar2ptr;int moduleId=(int)mxGetScalar(ze13f49a01f);char*boardName=io3xxGetBoardNameSgLib(moduleId);if(!io3xxGetAddressSgLib((int32_t)(int)mxGetPr(ze13f49a01f)[(0x1316+2392-0x1c6e)],SG_FPGA_IO3XX_BAR2)){ssSetErrorStatus(S,pSgErrorStr);return;}bar2ptr=io3xxGetAddressSgLib((int32_t)(int)mxGetPr(ze13f49a01f)[(0x21f9+1188-0x269d)],SG_FPGA_IO3XX_BAR2);SG_PRINTF(INFO,"\x25\x73\x20\x42\x41\x52\x32\x20\x61\x64\x64\x72\x65\x73\x73\x3a\x20\x30\x78\x25\x78" "\n",boardName,bar2ptr);uint32_t zf7ccd17be8=(0x3c1+2867-0xef4);if(sg_fpga_io3xx_getCmBaseAddress(moduleId,INTA_BASE,&zf7ccd17be8)){sprintf(msg,"\x25\x73\x20\x49\x4e\x54\x41\x20\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x4f\x66\x66\x73\x65\x74\x20\x6c\x6f\x6f\x6b\x75\x70\x20\x75\x6e\x73\x75\x63\x63\x65\x73\x73\x66\x75\x6c\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}SG_PRINTF(INFO,"\x25\x73\x20\x49\x4e\x54\x41\x20\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x4f\x66\x66\x73\x65\x74\x20\x30\x78\x25\x78" "\n",boardName,zf7ccd17be8);z79f5963ede=(z02171375f2*)((uintptr_t)bar2ptr+zf7ccd17be8);ssSetPWorkValue(S,z0194338df7,(void*)z79f5963ede);if(sg_fpga_io3xx_checkCodeModuleVersion(z79f5963ede->version,z5bbcf8be2c,moduleId)){sprintf(msg,"\x25\x73\x20\x77\x72\x6f\x6e\x67\x20\x76\x65\x72\x73\x69\x6f\x6e\x20\x6f\x66\x20\x49\x4e\x54\x41\x20\x63\x6f\x64\x65\x20\x6d\x6f\x64\x75\x6c\x65\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}
#endif
}static void sg_ModelStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_t enable,channel,i;volatile z02171375f2*z79f5963ede;uint32_t z4691513e3c;z79f5963ede=(z02171375f2*)ssGetPWorkValue(S,z0194338df7);z4691513e3c=(uint32_t)mxGetPr(z19b9dfa260)[(0x936+5512-0x1ebe)];enable=(0x16c1+1461-0x1c76);for(i=(0x125c+3851-0x2167);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x394+7913-0x227c);z79f5963ede->delay[channel]=(uint32_t)(mxGetPr(z644559a0a7)[i]*z4691513e3c);z79f5963ede->z16203ce901[channel]=(uint32_t)mxGetPr(z4d187edb3b)[i]+(0x857+3830-0x174c);z79f5963ede->zc0011fe779[channel]=(uint32_t)mxGetPr(z9efe7b3b47)[i]+(0x5a0+3449-0x1318);z79f5963ede->mode[channel]=(uint32_t)mxGetPr(za42e288061)[i];z79f5963ede->zaa88aaf485[channel]=(uint32_t)(mxGetPr(z1120e7330e)[i]*z4691513e3c);z79f5963ede->zbea9f5f1a5[channel]=(uint32_t)(mxGetPr(z684fe3b765)[i]*z4691513e3c);z79f5963ede->zb828f5ede4[channel]=(uint32_t)(z4691513e3c/mxGetPr(z18b816e17c)[i]);enable|=((0x108c+3149-0x1cd8)<<channel);}z79f5963ede->clear=enable;
#endif
}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_t i,event,channel,z0add1d1c25;double*y;volatile z02171375f2*z79f5963ede;z79f5963ede=(z02171375f2*)ssGetPWorkValue(S,z0194338df7);if(mxGetPr(zcca083e90d)[(0x12d+2008-0x905)]||mxGetPr(zc3fd540d44)[(0xbf1+480-0xdd1)]||mxGetPr(z824430e995)[(0x435+7170-0x2037)]){event=z79f5963ede->ze1a82e7a19;if(event){for(i=(0x11af+4185-0x2208);i<mxGetN(za9d8fb6bcf);i++){z0add1d1c25=(0x1269+1976-0x1a21);y=ssGetOutputPortRealSignal(S,z0add1d1c25);channel=(uint32_t)(mxGetPr(za9d8fb6bcf)[i]-(0x64c+5721-0x1ca4));if(mxGetPr(zcca083e90d)[(0xd4f+1551-0x135e)]){z0add1d1c25++;}if(event&((0x172c+325-0x1870)<<channel)){y[i]=(0x803+2467-0x11a5);if(mxGetPr(zc3fd540d44)[(0x105c+3124-0x1c90)]){y=(real_T*)ssGetOutputPortSignal(S,z0add1d1c25);y[i]=(real_T)((uint64_T)(z79f5963ede->z5541dce2ea[channel])<<(0xb41+4550-0x1ce7)|z79f5963ede->z7294689cde[channel]);z0add1d1c25++;}if(mxGetPr(z824430e995)[(0xce8+4144-0x1d18)]){y=(real_T*)ssGetOutputPortSignal(S,z0add1d1c25);y[i]=(real_T)z79f5963ede->z9f1a7be944[channel];}}else{y[i]=(0xc+3634-0xe3e);}}z79f5963ede->z75adbb7c26=event;}}else{z79f5963ede->z75adbb7c26=4294967295;}z79f5963ede->z75adbb7c26=(0xf21+834-0x1263);
#endif
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE
volatile z02171375f2*z79f5963ede;z79f5963ede=(z02171375f2*)ssGetPWorkValue(S,z0194338df7);z79f5963ede->clear=4294967295;z79f5963ede->clear=(0x1e3f+282-0x1f59);z79f5963ede->enable=(0xdb0+568-0xfe8);
#endif
}
#include "sg_sfcn_glue.h"   

