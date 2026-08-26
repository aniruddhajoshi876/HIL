// Copyright 2006-2026 Speedgoat GmbH

#define   S_FUNCTION_LEVEL  (0x798+7071-0x2335)
#undef    S_FUNCTION_NAME
#define   S_FUNCTION_NAME   sg_fpga_ssim_sf_2
#include  <stddef.h>
#include  <stdlib.h>
#include  <stdint.h>
#include  "simstruc.h"
#ifdef    MATLAB_MEX_FILE
#include  "mex.h"
#include "fixedpoint.h"
#endif
#ifndef   MATLAB_MEX_FILE
#include  "sg_common.h"
#include  "sg_fpga_io3xx_util.h"
#include  "sg_printf.h"
#include  "sg_fpga_io3xx_scatter_gather_dma.h"
#endif
#include  "sg_callback.h"
#define ze13f49a01f         ssGetSFcnParam(S, (0x3da+6844-0x1e96) ) 
#define za9d8fb6bcf           ssGetSFcnParam(S, (0x432+577-0x672) ) 
#define zf5ee62a4ad      ssGetSFcnParam(S, (0x3b4+2595-0xdd5) )
#define zbc98cfcf74          ssGetSFcnParam(S, (0x18f0+3372-0x2619) )
#define z3832b85a32         ssGetSFcnParam(S, (0xfbd+1850-0x16f3) )
#define z3e94973266                ssGetSFcnParam(S, (0x1bab+2179-0x2429) )
#define z2624d402ab                ssGetSFcnParam(S, (0x3a8+3358-0x10c0) )
#define z0422d86ad2           ssGetSFcnParam(S, (0x60d+2588-0x1022) )
#define z596b77cbe5            ssGetSFcnParam(S, (0x1e59+274-0x1f63) )
#define za42e288061              ssGetSFcnParam(S, (0x1371+3559-0x214f) )  
#define zdf24515981                         ((0x409+1079-0x836))
#define z5bbcf8be2c           (0x113d+1590-0x1771)
#define z2e6483d505            ((0x280+3370-0xfa8))
#define zc5ce4cb81a            ((0x1a+9363-0x24ad))
#define z2b17e2ee3b            ((0x14d8+4591-0x26c4))
#define z0194338df7       ((0x706+7094-0x22bc))
#define z66c66efec7  ((0x1ebb+339-0x200d))
#define z9cbfedf63b     ((0xa13+1697-0x10b2))
#define z91044fd421     ((0x189+4643-0x13ac))
#define z221a5cd0c2       ((0x267+8532-0x23ba))
#define zbf9f93799a              ((0x1592+4117-0x25a6))
#define z48257d3a6a       ((0x16fc+3995-0x2695))
#define z8216f23a91  ((0x790+1928-0xf15))
#define zf0d3ea3e3b (0x11a0+2938-0x1cda)
typedef volatile struct{uint32_t z8016f977bd[(0x324+8-0x30c)];uint32_t z28e9d9261f[(0xd8b+4284-0x1e27)];uint32_t z0e813df4a6[(0x14ac+4070-0x2472)];uint32_t z8c1a8bbff3[(0xb71+5577-0x211a)];uint32_t zdc1eed0ad0[(0x1d31+1426-0x22a3)];uint32_t start;uint32_t test1;uint32_t test2;uint32_t version;uint32_t zb2b6fc7553;uint32_t z23e37dbadc;uint32_t filler[(0x163a+449-0x17e1)];uint32_t z90cd3a78a8[(0x11d1+4950-0x2507)];}za22b8fa9db;static char msg[(0x1be4+1670-0x216a)];
#ifndef MATLAB_MEX_FILE
static io3xx_sgdma_Handle*zf30aa153dd(SimStruct*S);
#endif
#ifndef MATLAB_MEX_FILE
static io3xx_sgdma_Handle*zf30aa153dd(SimStruct*S){int i;int channel;int z5056c09cb0[zf0d3ea3e3b];uint32_t zcd308d01c9=(0x1b80+325-0x1cc5);za22b8fa9db*z263e3fa79e;io3xx_sgdma_Handle*ze639490358;io3xx_sgdma_Error z9b71752fdf;int moduleId=(int)mxGetScalar(ze13f49a01f);int z979d8f17a3=(int)mxGetN(za9d8fb6bcf);for(i=(0x395+3253-0x104a);i<z979d8f17a3;i++){channel=(int)mxGetPr(za9d8fb6bcf)[i]-(0x1d77+63-0x1db5);z5056c09cb0[i]=channel;zcd308d01c9|=((0x1153+4264-0x21fa)<<channel);}uint32_t zf7ccd17be8=(0x738+664-0x9d0);if(sg_fpga_io3xx_getCmBaseAddress(moduleId,SSIM_BASE,&zf7ccd17be8)){SG_PRINTF(DEBUG,"\x25\x73\x3a\x20\x53\x53\x49\x4d\x20\x62\x6c\x6f\x63\x6b\x3a\x20\x43\x6f\x75\x6c\x64\x20\x6e\x6f\x74\x20\x64\x65\x74\x65\x72\x6d\x69\x6e\x65\x20\x63\x6f\x64\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x6f\x66\x66\x73\x65\x74\x21" "\n",io3xxGetBoardNameSgLib(moduleId));return NULL;}bool z66bd01a1ae=false;z9b71752fdf=io3xx_sgdma_initialize(moduleId,sizeof(za22b8fa9db),zf7ccd17be8,z66bd01a1ae,&ze639490358);if(z9b71752fdf){SG_PRINTF(DEBUG,"\x53\x53\x49\x4d\x20\x62\x6c\x6f\x63\x6b\x3a\x20\x53\x47\x20\x44\x4d\x41\x20\x69\x6e\x69\x74\x69\x61\x6c\x69\x7a\x61\x74\x69\x6f\x6e\x20\x66\x61\x69\x6c\x65\x64\x20\x77\x69\x74\x68\x20\x65\x72\x72\x6f\x72\x20\x63\x6f\x64\x65\x3a\x20\x25\x64" "\n",z9b71752fdf);return NULL;}SG_PRINTF(DEBUG,"\x53\x53\x49\x4d\x20\x62\x6c\x6f\x63\x6b\x3a\x20\x53\x47\x20\x44\x4d\x41\x20\x69\x6e\x69\x74\x69\x61\x6c\x69\x7a\x65\x64" "\n");z263e3fa79e=(za22b8fa9db*)io3xx_sgdma_getShadowRegister(ze639490358);io3xx_sgdma_enqueueIndexList(ze639490358,&(z263e3fa79e->z0e813df4a6[(0xf2d+1217-0x13ee)]),sizeof(z263e3fa79e->z0e813df4a6[(0x1243+2462-0x1be1)]),IO3XX_SGDMA_READ,z5056c09cb0,z979d8f17a3);io3xx_sgdma_enqueueIndexList(ze639490358,&(z263e3fa79e->z90cd3a78a8[(0x1aff+206-0x1bcd)]),sizeof(z263e3fa79e->z90cd3a78a8[(0x2255+515-0x2458)]),IO3XX_SGDMA_READ,z5056c09cb0,z979d8f17a3);if((uint32_t)mxGetPr(za42e288061)[(0x1e81+2175-0x2700)]!=z8216f23a91){io3xx_sgdma_enqueueConstValue(ze639490358,&(z263e3fa79e->start),zcd308d01c9);}io3xx_sgdma_checkAndCorrect16ByteBoundary(ze639490358);return ze639490358;}
#endif 
static void mdlInitializeSizes(SimStruct*S){uint32_t i,zbc7ebd0e53;DTypeId z469f88b293=(0x1277+3304-0x1f5f);ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x1c96+652-0x1f22));ssSetNumDiscStates(S,(0x8b2+5995-0x201d));zbc7ebd0e53=(uint32_t)mxGetN(za9d8fb6bcf);ssSetNumOutputPorts(S,zbc7ebd0e53);for(i=(0x1b66+2930-0x26d8);i<zbc7ebd0e53;i++){if(((uint32_t)mxGetPr(zbc98cfcf74)[i])>(0x852+4495-0x19c1)){
#ifdef MATLAB_MEX_FILE
z469f88b293=ssRegisterDataTypeInteger(S,(0xc5a+3176-0x18c2),(0xf7f+685-0x11ec),(0x13a8+1787-0x1aa2));if(z469f88b293==INVALID_DTYPE_ID){sprintf(msg,"\x43\x61\x6e\x6e\x6f\x74\x20\x72\x65\x67\x69\x73\x74\x65\x72\x20\x36\x34\x20\x62\x69\x74\x20\x69\x6e\x74\x65\x67\x65\x72\x20\x74\x79\x70\x65");ssSetErrorStatus(S,msg);return;}
#else
z469f88b293=SS_DOUBLE;
#endif
ssSetOutputPortDataType(S,i,z469f88b293);}else{ssSetOutputPortDataType(S,i,SS_UINT32);}ssSetOutputPortWidth(S,i,(0x93b+3825-0x182b));}ssSetNumSampleTimes(S,(0x2363+106-0x23cc));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0xa0+2516-0xa74));ssSetNumNonsampledZCs(S,(0x1567+3950-0x24d5));for(i=(0x162d+4079-0x261c);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x5ef+2809-0x10e8));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0xb91+3056-0x1781)]==-1.0){ssSetSampleTime(S,(0x1cba+1910-0x2430),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x8dd+5786-0x1f77),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x1d+7075-0x1bc0),mxGetPr(z3832b85a32)[(0x7df+1621-0xe34)]);ssSetOffsetTime(S,(0x701+3345-0x1412),0.0);}}static void sg_ModelLoad(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uintptr_t z70fcda5f5d;za22b8fa9db*z0b706f91d0;int moduleId=(int)mxGetScalar(ze13f49a01f);char*boardName=io3xxGetBoardNameSgLib(moduleId);z70fcda5f5d=(uintptr_t)io3xxGetAddressSgLib((int)mxGetPr(ze13f49a01f)[(0xfed+3376-0x1d1d)],SG_FPGA_IO3XX_BAR2);if(z70fcda5f5d==(0x120f+77-0x125c)){ssSetErrorStatus(S,pSgErrorStr);return;}uint32_t zf7ccd17be8=(0x288+7504-0x1fd8);if(sg_fpga_io3xx_getCmBaseAddress(moduleId,SSIM_BASE,&zf7ccd17be8)){sprintf(msg,"\x25\x73\x20\x53\x53\x49\x4d\x20\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x4f\x66\x66\x73\x65\x74\x20\x6c\x6f\x6f\x6b\x75\x70\x20\x75\x6e\x73\x75\x63\x63\x65\x73\x73\x66\x75\x6c\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}z0b706f91d0=(za22b8fa9db*)(z70fcda5f5d+zf7ccd17be8);ssSetPWorkValue(S,z0194338df7,(void*)z0b706f91d0);if(sg_isFirstModelLoad()){if(sg_fpga_io3xx_checkCodeModuleVersion(z0b706f91d0->version,z5bbcf8be2c,moduleId)){sprintf(msg,"\x25\x73\x20\x77\x72\x6f\x6e\x67\x20\x76\x65\x72\x73\x69\x6f\x6e\x20\x6f\x66\x20\x53\x53\x49\x4d\x20\x63\x6f\x64\x65\x20\x6d\x6f\x64\x75\x6c\x65\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}}
#endif
}static void sg_ModelStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
za22b8fa9db*z0b706f91d0;io3xx_sgdma_Handle*ze639490358=NULL;uint32_t i=(0x1216+1103-0x1665),channel=(0x1a0+3063-0xd97),z3bf7fa31c2=(0x17f8+1180-0x1c94);uint32_t zcd308d01c9=(0x3c4+9006-0x26f2);int moduleId=(int)mxGetScalar(ze13f49a01f);z0b706f91d0=(za22b8fa9db*)(ssGetPWorkValue(S,z0194338df7));ScatterGatherDmaState*z50b84cc2b5;sg_fpga_io3xx_getSharedSgDmaState(moduleId,&z50b84cc2b5);modelTimings_t*z993c0995f5;sg_fpga_io3xx_getSharedTimingInfo(moduleId,&z993c0995f5);bool enableDma=z50b84cc2b5->enableDma;if(z50b84cc2b5->useFpgaDmaController){if(z993c0995f5->sampleTime==ssGetSampleTime(S,(0x23f+1566-0x85d))){enableDma=true;}else{enableDma=false;}}if(enableDma){ze639490358=zf30aa153dd(S);if(!ze639490358){sprintf(msg,"\x53\x53\x49\x4d\x20\x62\x6c\x6f\x63\x6b\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x69\x6e\x69\x74\x69\x61\x6c\x69\x7a\x65\x20\x74\x68\x65\x20\x44\x4d\x41\x20\x65\x6e\x67\x69\x6e\x65");ssSetErrorStatus(S,msg);return;}SG_PRINTF(DEBUG,"\x53\x53\x49\x4d\x20\x62\x6c\x6f\x63\x6b\x3a\x20\x53\x63\x61\x74\x74\x65\x72\x2d\x67\x61\x74\x68\x65\x72\x20\x44\x4d\x41\x20\x65\x6e\x61\x62\x6c\x65\x64" "\n");}else{SG_PRINTF(DEBUG,"\x53\x53\x49\x4d\x20\x62\x6c\x6f\x63\x6b\x3a\x20\x53\x63\x61\x74\x74\x65\x72\x2d\x67\x61\x74\x68\x65\x72\x20\x44\x4d\x41\x20\x64\x69\x73\x61\x62\x6c\x65\x64" "\n");}ssSetPWorkValue(S,z66c66efec7,ze639490358);for(i=(0xcd+6758-0x1b33);i<(uint32_t)mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0xa6f+5522-0x2000);zcd308d01c9|=((0x55b+4698-0x17b4)<<channel);if((uint32_t)mxGetPr(za42e288061)[(0xe03+221-0xee0)]==z48257d3a6a||(uint32_t)mxGetPr(za42e288061)[(0x128d+2044-0x1a89)]==z8216f23a91){z3bf7fa31c2|=((0x352+4815-0x1620)<<channel);}else{z3bf7fa31c2=(0xda2+94-0xe00);}z0b706f91d0->z8016f977bd[channel]=(uint32_t)mxGetPr(zbc98cfcf74)[i];z0b706f91d0->z28e9d9261f[channel]=(uint32_t)mxGetPr(zf5ee62a4ad)[i];z0b706f91d0->z8c1a8bbff3[channel]=(uint32_t)mxGetPr(z2624d402ab)[i];if((uint32_t)mxGetPr(z0422d86ad2)[(0xa27+4605-0x1c24)]==(0xd7f+652-0x100a)){z0b706f91d0->zdc1eed0ad0[channel]=(uint32_t)mxGetPr(z3e94973266)[i];}else{z0b706f91d0->zdc1eed0ad0[channel]=(0xaa2+1120-0xf02);}}ssSetIWorkValue(S,z91044fd421,zcd308d01c9);z0b706f91d0->start|=zcd308d01c9;z0b706f91d0->z23e37dbadc|=z3bf7fa31c2;SG_PRINTF(DEBUG,"\x53\x53\x49\x4d\x20\x62\x6c\x6f\x63\x6b\x3a\x20\x4d\x6f\x64\x65\x3a\x20\x25\x69" "\n",(uint32_t)mxGetPr(za42e288061)[(0x1750+1191-0x1bf7)]);
#endif
}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_t i,channel,x;uint64_t binary,zf67c59be22;uint32_t zcd308d01c9,zd8084c5125;double z9ab632cec0,zab642cf9f7;volatile za22b8fa9db*z0b706f91d0,*zb4b96c1b01;uint64_t*out,zc5ac1d6073,za892a705b5;z0b706f91d0=(za22b8fa9db*)(ssGetPWorkValue(S,z0194338df7));zcd308d01c9=ssGetIWorkValue(S,z91044fd421);io3xx_sgdma_Handle*ze639490358=(io3xx_sgdma_Handle*)ssGetPWorkValue(S,z66c66efec7);if(ze639490358){z0b706f91d0=(za22b8fa9db*)io3xx_sgdma_getShadowRegister(ze639490358);zb4b96c1b01=(za22b8fa9db*)ssGetPWorkValue(S,z0194338df7);;}else{z0b706f91d0=(za22b8fa9db*)ssGetPWorkValue(S,z0194338df7);zb4b96c1b01=(za22b8fa9db*)ssGetPWorkValue(S,z0194338df7);;}if((uint32_t)mxGetPr(za42e288061)[(0xc6c+4326-0x1d52)]==z8216f23a91){zb4b96c1b01->start|=zcd308d01c9;z9ab632cec0=sg_getElapsedTime();while(((zb4b96c1b01->start)&zcd308d01c9)>(0xde7+178-0xe99)){zab642cf9f7=sg_getElapsedTime();if((zab642cf9f7-z9ab632cec0)>3.0){sprintf(msg,"\x53\x53\x49\x4d\x20\x72\x65\x61\x64\x3a\x20\x54\x69\x6d\x65\x2d\x6f\x75\x74\x20\x65\x72\x72\x6f\x72");ssSetErrorStatus(S,msg);return;}}}if(ze639490358){io3xx_sgdma_Error z9b71752fdf=io3xx_sgdma_commitTransfer(ze639490358);if(z9b71752fdf!=IO3XX_SGDMA_NO_ERROR){SG_PRINTF(WARNING,"\x53\x53\x49\x4d\x20\x62\x6c\x6f\x63\x6b\x3a\x20\x44\x4d\x41\x20\x74\x72\x61\x6e\x73\x66\x65\x72\x20\x66\x61\x69\x6c\x65\x64\x21" "\n");return;}}for(i=(0xa94+5275-0x1f2f);i<(uint32_t)mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0xb36+761-0xe2e);zc5ac1d6073=z0b706f91d0->z0e813df4a6[channel]+(((uint64_t)(z0b706f91d0->z90cd3a78a8[channel]))<<(0x3dc+3307-0x10a7));zd8084c5125=(uint32_t)mxGetPr(zbc98cfcf74)[i];if((uint32_t)mxGetPr(z0422d86ad2)[(0x803+3377-0x1534)]==(0xd9+1857-0x819)){za892a705b5=(0x1242+3027-0x1e15);for(x=(0xdc6+1398-0x133c);x<zd8084c5125;x++){if(x!=(0x1059+2407-0x19c0)){zc5ac1d6073=zc5ac1d6073>>(0x222+4749-0x14ae);za892a705b5=za892a705b5<<(0x2e1+97-0x341);}za892a705b5=za892a705b5|(zc5ac1d6073&(0x913+6895-0x2401));}zc5ac1d6073=za892a705b5;SG_PRINTF(DEBUG,"\x64\x61\x74\x61\x52\x65\x63\x65\x69\x76\x65\x64\x20\x53\x53\x49\x32\x3a\x20\x25\x23\x30\x38\x58" "\n",zc5ac1d6073);}if((uint32_t)mxGetPr(z596b77cbe5)[(0x50d+7875-0x23d0)]==(0x2078+1438-0x2614)){binary=zc5ac1d6073;zf67c59be22=zc5ac1d6073;for(x=(0x13b2+2897-0x1f03);x<zd8084c5125;x++){zf67c59be22>>=(0x1a59+2780-0x2534);binary^=zf67c59be22;}zc5ac1d6073=binary;SG_PRINTF(DEBUG,"\x64\x61\x74\x61\x52\x65\x63\x65\x69\x76\x65\x64\x20\x47\x72\x61\x79\x3a\x20\x25\x23\x30\x31\x30\x58" "\n",zc5ac1d6073);}out=(uint64_t*)ssGetOutputPortSignal(S,i);*out=zc5ac1d6073;}if(!(ze639490358)&&((uint32_t)mxGetPr(za42e288061)[(0xaa6+5249-0x1f27)]==z48257d3a6a)){z0b706f91d0->start|=zcd308d01c9;}
#endif
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE
volatile za22b8fa9db*z0b706f91d0;z0b706f91d0=(za22b8fa9db*)(ssGetPWorkValue(S,z0194338df7));z0b706f91d0->start=(uint32_t)(0x1716+3091-0x2329);z0b706f91d0->z23e37dbadc=(uint32_t)(0x8b9+3579-0x16b4);io3xx_sgdma_Handle*ze639490358=(io3xx_sgdma_Handle*)ssGetPWorkValue(S,z66c66efec7);if(ze639490358){io3xx_sgdma_cleanup(ze639490358);}
#endif
}
#include "sg_sfcn_glue.h"   

