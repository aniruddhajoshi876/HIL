// Copyright 2006-2026 Speedgoat GmbH

#define   S_FUNCTION_LEVEL  (0xa19+2604-0x1443)
#undef    S_FUNCTION_NAME
#define   S_FUNCTION_NAME   sg_fpga_dshot_tx_sf_1
#include    <stddef.h>
#include    <stdlib.h>
#include    <stdint.h>
#include    <stdbool.h>
#include    "simstruc.h"
#ifdef MATLAB_MEX_FILE
#include    "mex.h"
#endif
#ifndef MATLAB_MEX_FILE
#include    "sg_common.h"
#include    "sg_fpga_io3xx_util.h"
#include    "sg_printf.h"
#endif
#include    "sg_callback.h"
#define debug
typedef enum{zfaa050b79d,CHANNEL,zac8c0ff69b,ze344b15ab1,z1c12f2148b,z958eccde6d,zdf24515981}z7d634622e8;
#define ze13f49a01f                       ssGetSFcnParam(S,zfaa050b79d)
#define za9d8fb6bcf                         ssGetSFcnParam(S,CHANNEL) 
#define z19b9dfa260                  ssGetSFcnParam(S,zac8c0ff69b)
#define z4f2115e66d                      ssGetSFcnParam(S,z1c12f2148b)
#define z3832b85a32                       ssGetSFcnParam(S,ze344b15ab1)
#define z3cea61299a             ssGetSFcnParam(S,z958eccde6d)
#define z2e6483d505            (0x1862+2648-0x22ba)
#define zc5ce4cb81a            (0x18c6+3048-0x24ae)
#define z2b17e2ee3b            (0x11c9+3652-0x200c)
#define z0194338df7       (0x10a7+3719-0x1f2e)
#define z5ae2c8ee5e       (0x6d3+5981-0x1e30)
#define z5bbcf8be2c          (0x3ba+831-0x6f8)
#define zb7aa091922           ((0xfe9+3739-0x1e82))
static char_T msg[(0x7e3+58-0x71d)];struct z8b5b9ae863{uint32_t z0527830bf8[(0x198f+394-0x1af9)];uint32_t zb8ab67b32f[(0x27f+815-0x58e)];uint32_t z2072a12113[(0x60c+3642-0x1426)];uint32_t zaa91623895[(0xd0+3082-0xcba)];uint32_t zea9d5c3d22;uint32_t version;};static void mdlInitializeSizes(SimStruct*S){uint32_t i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x14ac+2768-0x1f7c));ssSetNumDiscStates(S,(0x908+865-0xc69));ssSetNumInputPorts(S,(0x1193+1394-0x1704));ssSetNumOutputPorts(S,(0x50a+4396-0x1636));ssSetInputPortWidth(S,(0x1e45+218-0x1f1f),mxGetN(za9d8fb6bcf));ssSetInputPortDataType(S,(0xeec+813-0x1219),SS_UINT16);ssSetInputPortDirectFeedThrough(S,(0xf5d+2650-0x19b7),(0x363+2580-0xd76));ssSetInputPortRequiredContiguous(S,(0xb0+8209-0x20c1),(0x1544+2489-0x1efc));ssSetNumSampleTimes(S,(0x2e0+5014-0x1675));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x783+2696-0x120b));ssSetNumNonsampledZCs(S,(0xd67+6522-0x26e1));for(i=(0xf90+3365-0x1cb5);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x4c4+2036-0xcb8));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x3a7+6966-0x1edd)]==-1.0){ssSetSampleTime(S,(0x10bf+2137-0x1918),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x995+4240-0x1a25),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x64b+1215-0xb0a),mxGetPr(z3832b85a32)[(0xf04+2134-0x175a)]);ssSetOffsetTime(S,(0x1588+1878-0x1cde),0.0);}}static void sg_ModelLoad(SimStruct*S){
#ifndef MATLAB_MEX_FILE
volatile struct z8b5b9ae863*z2973855345;void*z8e7911eb93;int moduleId=(int)mxGetScalar(ze13f49a01f);char*boardName=io3xxGetBoardNameSgLib(moduleId);if(!io3xxGetAddressSgLib((int32_t)(int)mxGetPr(ze13f49a01f)[(0x1277+2015-0x1a56)],SG_FPGA_IO3XX_BAR2)){ssSetErrorStatus(S,pSgErrorStr);return;}z8e7911eb93=io3xxGetAddressSgLib((int32_t)(int)mxGetPr(ze13f49a01f)[(0xc65+793-0xf7e)],SG_FPGA_IO3XX_BAR2);uint32_t zf7ccd17be8=(0x947+1653-0xfbc);if(sg_fpga_io3xx_getCmBaseAddress(moduleId,DSHOT_TX_BASE,&zf7ccd17be8)){sprintf(msg,"\x25\x73\x20\x44\x73\x68\x6f\x74\x20\x54\x78\x20\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x4f\x66\x66\x73\x65\x74\x20\x6c\x6f\x6f\x6b\x75\x70\x20\x75\x6e\x73\x75\x63\x63\x65\x73\x73\x66\x75\x6c\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}z2973855345=(struct z8b5b9ae863*)((uintptr_t)z8e7911eb93+zf7ccd17be8);ssSetPWorkValue(S,z0194338df7,(void*)z2973855345);if(sg_isFirstModelLoad()){if(sg_fpga_io3xx_checkCodeModuleVersion(z2973855345->version,z5bbcf8be2c,moduleId)){sprintf(msg,"\x25\x73\x20\x77\x72\x6f\x6e\x67\x20\x76\x65\x72\x73\x69\x6f\x6e\x20\x6f\x66\x20\x44\x53\x48\x4f\x54\x20\x54\x78\x20\x63\x6f\x64\x65\x20\x6d\x6f\x64\x75\x6c\x65\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}}
#endif
}static void sg_ModelStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
real_T z5ec2b7da0a,z9f3c34b5fe=0.0;uint32_t channel,i;volatile struct z8b5b9ae863*z2973855345;z5ec2b7da0a=(real_T)mxGetPr(z19b9dfa260)[(0xe63+5733-0x24c8)];z2973855345=(struct z8b5b9ae863*)ssGetPWorkValue(S,z0194338df7);for(i=(0x890+7386-0x256a);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x7a0+794-0xab9);switch((uint32_t)mxGetPr(z4f2115e66d)[i]){case(0x7ba+1051-0xbd4):z9f3c34b5fe=z5ec2b7da0a/150000.0;break;case(0xa7a+988-0xe54):z9f3c34b5fe=z5ec2b7da0a/300000.0;break;case(0x42f+2947-0xfaf):z9f3c34b5fe=z5ec2b7da0a/600000.0;break;case(0x7f4+4144-0x1820):z9f3c34b5fe=z5ec2b7da0a/1200000.0;break;default:sprintf(msg,"\x54\x68\x69\x73\x20\x64\x61\x74\x61\x20\x66\x6f\x72\x6d\x61\x74\x20\x69\x73\x20\x6e\x6f\x74\x20\x73\x75\x70\x70\x6f\x72\x74\x65\x64\x2e" "\n");ssSetErrorStatus(S,msg);return;}z2973855345->z2072a12113[channel]=(uint32_t)z9f3c34b5fe;z2973855345->z0527830bf8[channel]=(uint32_t)(z9f3c34b5fe*(3.0/4.0));z2973855345->zb8ab67b32f[channel]=(uint32_t)(z9f3c34b5fe*(3.0/8.0));}
#endif
}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_t i,channel,z432cbd7f14,za8657d7521;uint32_t z1adae7c3bc,z44180a9e59,packet,z812c65ff2f,z101ad88574=(0xb53+4756-0x1de7);uint16_T*zd3561678fb,z227afd6abb;volatile struct z8b5b9ae863*z2973855345;z2973855345=(struct z8b5b9ae863*)ssGetPWorkValue(S,z0194338df7);zd3561678fb=(uint16_T*)ssGetInputPortSignal(S,(0x1462+1391-0x19d1));za8657d7521=(uint32_t)mxGetPr(z3cea61299a)[(0x1391+1891-0x1af4)];z2973855345->zea9d5c3d22=(0x502+1552-0xb12);for(i=(0x383+8596-0x2517);i<(uint32_t)mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x1c01+2684-0x267c);if(za8657d7521==(0xbab+5282-0x204d)){z227afd6abb=zd3561678fb[i]&(0x1329+5166-0x1f58);if(z227afd6abb>(0x462+166-0x4d9)||z227afd6abb<(0x152d+2024-0x1d14)){z432cbd7f14=(0xa65+2344-0x138d);}else{z432cbd7f14=(0x907+6672-0x2316);}packet=(z227afd6abb<<(0xc73+2407-0x15d9)|z432cbd7f14);}else{packet=zd3561678fb[i]&(0x10d5+8749-0x2303);}z1adae7c3bc=(0x705+3817-0x15ee);z44180a9e59=packet;for(z812c65ff2f=(0x3c8+1771-0xab3);z812c65ff2f<(0x1196+4285-0x2250);z812c65ff2f++){z1adae7c3bc^=z44180a9e59;z44180a9e59>>=(0x18c8+3503-0x2673);}z1adae7c3bc&=(0x6d3+7742-0x2502);z2973855345->zaa91623895[channel]=(packet<<(0x190d+3210-0x2593))|z1adae7c3bc;z101ad88574|=(0x109f+1739-0x1769)<<channel;}z2973855345->zea9d5c3d22=z101ad88574;
#endif
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE
#endif
}
#include "sg_sfcn_glue.h"   

