// Copyright 2006-2026 Speedgoat GmbH

#define   S_FUNCTION_LEVEL  (0x10cb+3051-0x1cb4)
#undef    S_FUNCTION_NAME
#define   S_FUNCTION_NAME   sg_fpga_dshot_rx_sf_1
#include    <stddef.h>
#include    <stdlib.h>
#include    <stdint.h>
#include    <stdbool.h>
#include    "simstruc.h" 
#ifdef  MATLAB_MEX_FILE
#include    "mex.h"
#endif
#ifndef MATLAB_MEX_FILE
#include    "sg_common.h"
#include    "sg_fpga_io3xx_util.h"
#include    "sg_printf.h"
#endif
#include    "sg_callback.h"
#define debug
typedef enum{zfaa050b79d,CHANNEL,zac8c0ff69b,ze344b15ab1,z1c12f2148b,z9072ebbf73,z265ff5f8dd,zdf24515981}z031509f2f9;
#define ze13f49a01f                       ssGetSFcnParam(S,zfaa050b79d)
#define za9d8fb6bcf                         ssGetSFcnParam(S,CHANNEL) 
#define z19b9dfa260                  ssGetSFcnParam(S,zac8c0ff69b)
#define z4f2115e66d                      ssGetSFcnParam(S,z1c12f2148b)
#define za93f8793ea                     ssGetSFcnParam(S,z9072ebbf73)
#define zced744b5e1                    ssGetSFcnParam(S,z265ff5f8dd)
#define z3832b85a32                       ssGetSFcnParam(S,ze344b15ab1)
#define z2e6483d505            (0x1190+4863-0x248f)
#define zc5ce4cb81a            (0xfb8+104-0x1020)
#define z2b17e2ee3b            (0x3c3+4415-0x1501)
#define z0194338df7       (0x1542+2274-0x1e24)
#define z5ae2c8ee5e       (0xf6a+1367-0x14c1)
#define z5bbcf8be2c          (0x5a0+4783-0x184e)
#define zb7aa091922           ((0xe34+1164-0x12be))
static char_T msg[(0x1ee4+899-0x2167)];struct z6abe543fc4{uint32_t z0527830bf8[(0x1321+3363-0x2024)];uint32_t z2072a12113[(0x6eb+4328-0x17b3)];uint32_t z39254fcf1c[(0x10a5+1116-0x14e1)];uint32_t z9a3d43b4f0[(0x72b+7779-0x256e)];uint32_t version;};static void mdlInitializeSizes(SimStruct*S){uint32_t i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x916+2259-0x11e9));ssSetNumDiscStates(S,(0x2474+552-0x269c));ssSetNumInputPorts(S,(0xaba+975-0xe89));ssSetNumOutputPorts(S,(0x97b+6991-0x24c7));ssSetOutputPortWidth(S,(0x759+4337-0x184a),mxGetN(za9d8fb6bcf));ssSetOutputPortDataType(S,(0x65f+5920-0x1d7f),SS_UINT16);ssSetOutputPortWidth(S,(0xf67+3000-0x1b1e),mxGetN(za9d8fb6bcf));ssSetOutputPortDataType(S,(0x679+1033-0xa81),SS_BOOLEAN);ssSetOutputPortWidth(S,(0x16c5+2133-0x1f18),mxGetN(za9d8fb6bcf));ssSetOutputPortDataType(S,(0x1a99+93-0x1af4),SS_BOOLEAN);ssSetNumSampleTimes(S,(0x4e9+859-0x843));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x277+8965-0x257c));ssSetNumNonsampledZCs(S,(0x25c+6198-0x1a92));for(i=(0x1512+496-0x1702);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0xa24+1447-0xfcb));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x1fa+8876-0x24a6)]==-1.0){ssSetSampleTime(S,(0x716+3441-0x1487),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x80+5650-0x1692),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x7+8250-0x2041),mxGetPr(z3832b85a32)[(0xd37+4672-0x1f77)]);ssSetOffsetTime(S,(0xf80+299-0x10ab),0.0);}}static void sg_ModelLoad(SimStruct*S){
#ifndef MATLAB_MEX_FILE
volatile struct z6abe543fc4*z6166d81440;void*z8e7911eb93;int moduleId=(int)mxGetScalar(ze13f49a01f);char*boardName=io3xxGetBoardNameSgLib(moduleId);if(!io3xxGetAddressSgLib((int32_t)(int)mxGetPr(ze13f49a01f)[(0x1a13+1968-0x21c3)],SG_FPGA_IO3XX_BAR2)){ssSetErrorStatus(S,pSgErrorStr);return;}z8e7911eb93=io3xxGetAddressSgLib((int32_t)(int)mxGetPr(ze13f49a01f)[(0xa2a+7178-0x2634)],SG_FPGA_IO3XX_BAR2);uint32_t zf7ccd17be8=(0xc9+2994-0xc7b);if(sg_fpga_io3xx_getCmBaseAddress(moduleId,DSHOT_RX_BASE,&zf7ccd17be8)){sprintf(msg,"\x25\x73\x20\x44\x73\x68\x6f\x74\x20\x52\x78\x20\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x4f\x66\x66\x73\x65\x74\x20\x6c\x6f\x6f\x6b\x75\x70\x20\x75\x6e\x73\x75\x63\x63\x65\x73\x73\x66\x75\x6c\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}z6166d81440=(struct z6abe543fc4*)((uintptr_t)z8e7911eb93+zf7ccd17be8);ssSetPWorkValue(S,z0194338df7,(void*)z6166d81440);if(sg_isFirstModelLoad()){if(sg_fpga_io3xx_checkCodeModuleVersion(z6166d81440->version,z5bbcf8be2c,moduleId)){sprintf(msg,"\x25\x73\x20\x77\x72\x6f\x6e\x67\x20\x76\x65\x72\x73\x69\x6f\x6e\x20\x6f\x66\x20\x51\x41\x44\x20\x63\x6f\x64\x65\x20\x6d\x6f\x64\x75\x6c\x65\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}}
#endif
}static void sg_ModelStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_t channel,i,zeeeba54a90;real_T z5ec2b7da0a,z9f3c34b5fe=0.0;volatile struct z6abe543fc4*z6166d81440;z6166d81440=(struct z6abe543fc4*)ssGetPWorkValue(S,z0194338df7);z5ec2b7da0a=(real_T)mxGetPr(z19b9dfa260)[(0xef4+5046-0x22aa)];for(i=(0x4d3+1523-0xac6);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x665+3874-0x1586);switch((uint32_t)mxGetPr(z4f2115e66d)[i]){case(0x7f3+1107-0xc45):z9f3c34b5fe=z5ec2b7da0a/150000.0;break;case(0x1582+745-0x1869):z9f3c34b5fe=z5ec2b7da0a/300000.0;break;case(0x9e7+5991-0x214b):z9f3c34b5fe=z5ec2b7da0a/600000.0;break;case(0x2248+1147-0x26bf):z9f3c34b5fe=z5ec2b7da0a/1200000.0;break;default:sprintf(msg,"\x54\x68\x69\x73\x20\x64\x61\x74\x61\x20\x66\x6f\x72\x6d\x61\x74\x20\x69\x73\x20\x6e\x6f\x74\x20\x73\x75\x70\x70\x6f\x72\x74\x65\x64\x2e" "\n");ssSetErrorStatus(S,msg);return;}z6166d81440->z2072a12113[channel]=(uint32_t)z9f3c34b5fe;zeeeba54a90=((z6166d81440->version&1023)>>(0xdcc+3762-0x1c7e));if(zeeeba54a90>=(0xe2+7056-0x1c71)){z6166d81440->z0527830bf8[channel]=(uint32_t)(z9f3c34b5fe*(9.0/16.0));}else{z6166d81440->z0527830bf8[channel]=(uint32_t)(z9f3c34b5fe*(3.0/4.0));}z6166d81440->z39254fcf1c[channel]=(uint32_t)mxGetPr(zced744b5e1)[i];}
#endif
}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_t i,channel,data,z1adae7c3bc,z44180a9e59,z812c65ff2f;uint16_T*zeeb642ab2c;boolean_T*zce0b9eb663,*zc8f72eadfc,ze3d982d3f8;volatile struct z6abe543fc4*z6166d81440;z6166d81440=(struct z6abe543fc4*)ssGetPWorkValue(S,z0194338df7);zeeb642ab2c=(uint16_T*)ssGetOutputPortSignal(S,(0x139b+40-0x13c3));zce0b9eb663=(boolean_T*)ssGetOutputPortSignal(S,(0xe09+1553-0x1419));zc8f72eadfc=(boolean_T*)ssGetOutputPortSignal(S,(0x119f+736-0x147d));for(i=(0x321+204-0x3ed);i<(uint32_t)mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x25aa+43-0x25d4);data=z6166d81440->z9a3d43b4f0[channel];ze3d982d3f8=(boolean_T)(data&(0xa53+1116-0xe9f))>>(0x22f8+380-0x2470);z1adae7c3bc=(0x1282+1073-0x16b3);z44180a9e59=data>>(0x731+7676-0x2529);for(z812c65ff2f=(0x30b+1012-0x6ff);z812c65ff2f<(0x3d0+5856-0x1aad);z812c65ff2f++){z1adae7c3bc^=z44180a9e59;z44180a9e59>>=(0x16ad+252-0x17a5);}z1adae7c3bc&=(0x1771+2538-0x214c);if(z1adae7c3bc-(data&(0xb22+402-0xca5))!=(0x13a8+1362-0x18fa)){zce0b9eb663[i]=(0x1bb1+132-0x1c35);}else{zce0b9eb663[i]=(0x1432+1765-0x1b16);}if(ze3d982d3f8==(0x7c8+4881-0x1ad8)){zc8f72eadfc[i]=(0x1486+1949-0x1c22);}else{zc8f72eadfc[i]=(0xc3b+1589-0x1270);}zeeb642ab2c[i]=(uint16_T)(data&65535)>>(0x1aba+2089-0x22de);}
#endif
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE
#endif
}
#include "sg_sfcn_glue.h"   

