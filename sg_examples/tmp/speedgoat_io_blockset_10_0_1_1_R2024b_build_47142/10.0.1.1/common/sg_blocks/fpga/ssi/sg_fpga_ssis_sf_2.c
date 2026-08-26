// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL (0x4f2+1573-0xb15)
#undef  S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_fpga_ssis_sf_2
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include "simstruc.h"
#include "fixedpoint.h"
#ifdef   MATLAB_MEX_FILE
#include "mex.h"
#endif
#ifndef  MATLAB_MEX_FILE
#include "sg_common.h"
#include "sg_fpga_io3xx_util.h"
#include "sg_printf.h"
#include "sg_fpga_io3xx_scatter_gather_dma.h"
#endif
#include "sg_callback.h"
#define ze13f49a01f         ssGetSFcnParam(S, (0xb7f+4937-0x1ec8)) 
#define za9d8fb6bcf           ssGetSFcnParam(S, (0x1cd8+2532-0x26bb))
#define zbc98cfcf74          ssGetSFcnParam(S, (0x195d+65-0x199c))
#define z3832b85a32         ssGetSFcnParam(S, (0x66c+4214-0x16df))
#define z596b77cbe5            ssGetSFcnParam(S, (0x599+1829-0xcba))
#define z16f0e28da2  ssGetSFcnParam(S, (0x10b9+3468-0x1e40))
#define z28ae9668c9     ssGetSFcnParam(S, (0x569+5856-0x1c43))
#define z0422d86ad2           ssGetSFcnParam(S, (0x261d+175-0x26c5))
#define zdf24515981                        ((0x9bd+1315-0xed8))
#define z5bbcf8be2c           (0x15c8+460-0x1792)
#define z2e6483d505            ((0xe68+5107-0x225b))
#define zc5ce4cb81a            ((0x6ba+2486-0x1070))
#define z2b17e2ee3b            ((0xe74+4079-0x1e61))
#define z0194338df7       ((0x103+449-0x2c4))
#define z66c66efec7  ((0x54a+8113-0x24fa))
#define zf0d3ea3e3b (0x599+8609-0x26fa)
#define z3aeb20d2bd (0x1d9a+1568-0x237a)
typedef volatile struct{uint32_t z8016f977bd[(0x338+4841-0x1601)];uint32_t z6c26d53b83[(0x1bc4+1206-0x205a)];uint32_t z8cfdb4102b[(0x1351+3859-0x2244)];uint32_t zc8648e7352[(0x14f+2748-0xbeb)];uint32_t test1;uint32_t test2;uint32_t version;uint32_t filler[(0x14d2+560-0x16e5)];uint32_t z0555097756[(0xb61+7007-0x26a0)];}z6b3137e20b;static char msg[(0x2b1+6116-0x1995)];
#ifndef MATLAB_MEX_FILE
static io3xx_sgdma_Handle*zf30aa153dd(SimStruct*S);
#endif
#ifndef MATLAB_MEX_FILE
static io3xx_sgdma_Handle*zf30aa153dd(SimStruct*S){int i;int channel;int z5056c09cb0[zf0d3ea3e3b];z6b3137e20b*z476e5e7d2b;io3xx_sgdma_Handle*ze639490358;io3xx_sgdma_Error z9b71752fdf;int moduleId=(int)mxGetScalar(ze13f49a01f);int z979d8f17a3=(int)mxGetN(za9d8fb6bcf);for(i=(0x1c01+1600-0x2241);i<z979d8f17a3;i++){channel=(int)mxGetPr(za9d8fb6bcf)[i]-(0x312+7844-0x21b5);z5056c09cb0[i]=channel;}uint32_t zf7ccd17be8=(0x2a3+6526-0x1c21);if(sg_fpga_io3xx_getCmBaseAddress(moduleId,SSIS_BASE,&zf7ccd17be8)){SG_PRINTF(DEBUG,"\x25\x73\x3a\x20\x53\x53\x49\x53\x20\x62\x6c\x6f\x63\x6b\x3a\x20\x43\x6f\x75\x6c\x64\x20\x6e\x6f\x74\x20\x64\x65\x74\x65\x72\x6d\x69\x6e\x65\x20\x63\x6f\x64\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x6f\x66\x66\x73\x65\x74\x21" "\n",io3xxGetBoardNameSgLib(moduleId));return NULL;}bool z66bd01a1ae=false;z9b71752fdf=io3xx_sgdma_initialize(moduleId,sizeof(z6b3137e20b),zf7ccd17be8,z66bd01a1ae,&ze639490358);if(z9b71752fdf){SG_PRINTF(DEBUG,"\x53\x53\x49\x53\x20\x62\x6c\x6f\x63\x6b\x3a\x20\x53\x47\x20\x44\x4d\x41\x20\x69\x6e\x69\x74\x69\x61\x6c\x69\x7a\x61\x74\x69\x6f\x6e\x20\x66\x61\x69\x6c\x65\x64\x20\x77\x69\x74\x68\x20\x65\x72\x72\x6f\x72\x20\x63\x6f\x64\x65\x3a\x20\x25\x64" "\n",z9b71752fdf);return NULL;}SG_PRINTF(DEBUG,"\x53\x53\x49\x53\x20\x62\x6c\x6f\x63\x6b\x3a\x20\x53\x47\x20\x44\x4d\x41\x20\x69\x6e\x69\x74\x69\x61\x6c\x69\x7a\x65\x64" "\n");z476e5e7d2b=(z6b3137e20b*)io3xx_sgdma_getShadowRegister(ze639490358);io3xx_sgdma_enqueueIndexList(ze639490358,&(z476e5e7d2b->z6c26d53b83[(0x457+5415-0x197e)]),sizeof(z476e5e7d2b->z6c26d53b83[(0x13ef+3658-0x2239)]),IO3XX_SGDMA_WRITE,z5056c09cb0,z979d8f17a3);io3xx_sgdma_enqueueIndexList(ze639490358,&(z476e5e7d2b->z0555097756[(0xc99+1220-0x115d)]),sizeof(z476e5e7d2b->z0555097756[(0x1ae4+1891-0x2247)]),IO3XX_SGDMA_WRITE,z5056c09cb0,z979d8f17a3);return ze639490358;}
#endif 
static void mdlInitializeSizes(SimStruct*S){uint32_t i,zbc7ebd0e53;DTypeId z469f88b293=(0x826+7399-0x250d);ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x10c3+2606-0x1af1));ssSetNumDiscStates(S,(0x1f2f+1633-0x2590));zbc7ebd0e53=(uint32_t)mxGetN(za9d8fb6bcf);ssSetNumInputPorts(S,zbc7ebd0e53);for(i=(0x4f8+221-0x5d5);i<zbc7ebd0e53;i++){if(((uint32_t)mxGetPr(zbc98cfcf74)[i])>(0xce0+2271-0x159f)){
#ifdef MATLAB_MEX_FILE
z469f88b293=ssRegisterDataTypeInteger(S,(0x447+8269-0x2494),(0x536+3694-0x1364),(0x86d+5706-0x1eb6));if(z469f88b293==INVALID_DTYPE_ID){sprintf(msg,"\x43\x61\x6e\x6e\x6f\x74\x20\x72\x65\x67\x69\x73\x74\x65\x72\x20\x36\x34\x20\x62\x69\x74\x20\x69\x6e\x74\x65\x67\x65\x72\x20\x74\x79\x70\x65");ssSetErrorStatus(S,msg);return;}
#else
z469f88b293=SS_DOUBLE;
#endif
ssSetInputPortDataType(S,i,z469f88b293);}else{ssSetInputPortDataType(S,i,SS_UINT32);}ssSetInputPortWidth(S,i,(0x1f95+579-0x21d7));ssSetInputPortDirectFeedThrough(S,i,(0xba8+5994-0x2311));ssSetInputPortRequiredContiguous(S,i,(0x1fc2+1604-0x2605));}ssSetNumSampleTimes(S,(0xc60+5744-0x22cf));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x18a1+1451-0x1e4c));ssSetNumNonsampledZCs(S,(0x1bb4+1234-0x2086));for(i=(0xf10+4181-0x1f65);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x201+9275-0x263c));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x1445+3306-0x212f)]==-1.0){ssSetSampleTime(S,(0xf44+810-0x126e),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x5f4+3004-0x11b0),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x23cc+574-0x260a),mxGetPr(z3832b85a32)[(0x399+2857-0xec2)]);ssSetOffsetTime(S,(0x144d+698-0x1707),0.0);}}static void sg_ModelLoad(SimStruct*S){
#ifndef MATLAB_MEX_FILE
z6b3137e20b*z1b230a715b;int moduleId=(int)mxGetScalar(ze13f49a01f);char*boardName=io3xxGetBoardNameSgLib(moduleId);if(!io3xxGetAddressSgLib((int32_t)(int)mxGetPr(ze13f49a01f)[(0x594+2871-0x10cb)],SG_FPGA_IO3XX_BAR2)){ssSetErrorStatus(S,pSgErrorStr);return;}uint32_t zf7ccd17be8=(0x2fa+6593-0x1cbb);if(sg_fpga_io3xx_getCmBaseAddress(moduleId,SSIS_BASE,&zf7ccd17be8)){sprintf(msg,"\x25\x73\x20\x53\x53\x49\x53\x20\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x4f\x66\x66\x73\x65\x74\x20\x6c\x6f\x6f\x6b\x75\x70\x20\x75\x6e\x73\x75\x63\x63\x65\x73\x73\x66\x75\x6c\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}z1b230a715b=(z6b3137e20b*)((uintptr_t)io3xxGetAddressSgLib((int32_t)(int)mxGetPr(ze13f49a01f)[(0xcb7+1217-0x1178)],SG_FPGA_IO3XX_BAR2)+zf7ccd17be8);ssSetPWorkValue(S,z0194338df7,(void*)z1b230a715b);if(sg_isFirstModelLoad()){if(sg_fpga_io3xx_checkCodeModuleVersion(z1b230a715b->version,z5bbcf8be2c,moduleId)){sprintf(msg,"\x25\x73\x20\x77\x72\x6f\x6e\x67\x20\x76\x65\x72\x73\x69\x6f\x6e\x20\x6f\x66\x20\x53\x53\x49\x53\x20\x63\x6f\x64\x65\x20\x6d\x6f\x64\x75\x6c\x65\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}}
#endif
}static void sg_ModelStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_t i,channel;z6b3137e20b*z1b230a715b;io3xx_sgdma_Handle*ze639490358=NULL;int moduleId=(int)mxGetScalar(ze13f49a01f);z1b230a715b=(z6b3137e20b*)(ssGetPWorkValue(S,z0194338df7));ScatterGatherDmaState*z50b84cc2b5;sg_fpga_io3xx_getSharedSgDmaState(moduleId,&z50b84cc2b5);modelTimings_t*z993c0995f5;sg_fpga_io3xx_getSharedTimingInfo(moduleId,&z993c0995f5);bool enableDma=false;if(enableDma){ze639490358=zf30aa153dd(S);if(!ze639490358){sprintf(msg,"\x53\x53\x49\x4d\x20\x62\x6c\x6f\x63\x6b\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x69\x6e\x69\x74\x69\x61\x6c\x69\x7a\x65\x20\x74\x68\x65\x20\x44\x4d\x41\x20\x65\x6e\x67\x69\x6e\x65");ssSetErrorStatus(S,msg);return;}SG_PRINTF(DEBUG,"\x53\x53\x49\x4d\x20\x62\x6c\x6f\x63\x6b\x3a\x20\x53\x63\x61\x74\x74\x65\x72\x2d\x67\x61\x74\x68\x65\x72\x20\x44\x4d\x41\x20\x65\x6e\x61\x62\x6c\x65\x64" "\n");}else{SG_PRINTF(DEBUG,"\x53\x53\x49\x4d\x20\x62\x6c\x6f\x63\x6b\x3a\x20\x53\x63\x61\x74\x74\x65\x72\x2d\x67\x61\x74\x68\x65\x72\x20\x44\x4d\x41\x20\x64\x69\x73\x61\x62\x6c\x65\x64" "\n");}ssSetPWorkValue(S,z66c66efec7,ze639490358);z1b230a715b->test2=4042304170;for(i=(0x1dba+2012-0x2596);i<(uint32_t)mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x3ac+5550-0x1959);z1b230a715b->z8016f977bd[channel]=(uint32_t)mxGetPr(zbc98cfcf74)[i];z1b230a715b->z8cfdb4102b[channel]=(uint32_t)mxGetPr(z16f0e28da2)[i];z1b230a715b->zc8648e7352[channel]=(uint32_t)mxGetPr(z28ae9668c9)[i];}
#endif
}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_t i,channel;z6b3137e20b*z1b230a715b;uint64_t*in;uint64_t zb9e8f50428,zb76181bdf3,z81a0118eab;uint32_t x,za342e26c50,zdab7ffa39a;z1b230a715b=(z6b3137e20b*)(ssGetPWorkValue(S,z0194338df7));io3xx_sgdma_Handle*ze639490358=(io3xx_sgdma_Handle*)ssGetPWorkValue(S,z66c66efec7);if(ze639490358){z1b230a715b=(z6b3137e20b*)io3xx_sgdma_getShadowRegister(ze639490358);}else{z1b230a715b=(z6b3137e20b*)ssGetPWorkValue(S,z0194338df7);}for(i=(0xc36+6843-0x26f1);i<(uint32_t)mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x818+3139-0x145a);in=(uint64_t*)ssGetInputPortSignal(S,i);if(((uint32_t)mxGetPr(zbc98cfcf74)[i])<=(0x1117+4045-0x20c4)){zb76181bdf3=(uint64_t)(uint32_t)(*in);}else{zb76181bdf3=*in;}if((uint32_t)mxGetPr(z596b77cbe5)[(0xeea+2240-0x17aa)]==(0x134+5928-0x185a)){zb76181bdf3=zb76181bdf3^(zb76181bdf3>>(0xce0+648-0xf67));}if((uint32_t)mxGetPr(z0422d86ad2)[(0xdb7+4796-0x2073)]==(0x372+1119-0x7d0)){z81a0118eab=(0x51f+5752-0x1b97);for(x=(0x1a3+1072-0x5d3);x<(uint32_t)mxGetPr(zbc98cfcf74)[i];x++){if(x!=(0x1b37+2889-0x2680)){zb76181bdf3=zb76181bdf3>>(0xbc5+2524-0x15a0);z81a0118eab=z81a0118eab<<(0x14dd+1556-0x1af0);}z81a0118eab=z81a0118eab|(zb76181bdf3&(0x1948+511-0x1b46));}zb76181bdf3=z81a0118eab;}zb9e8f50428=zb76181bdf3<<(z3aeb20d2bd-(uint32_t)mxGetPr(zbc98cfcf74)[i]);za342e26c50=(uint32_t)(zb9e8f50428&0x00000000ffffffff);zdab7ffa39a=(uint32_t)((zb9e8f50428>>(0x11a3+4351-0x2282))&4294967295);z1b230a715b->z6c26d53b83[channel]=zdab7ffa39a;z1b230a715b->z0555097756[channel]=za342e26c50;}if(ze639490358){io3xx_sgdma_Error z9b71752fdf=io3xx_sgdma_commitTransfer(ze639490358);if(z9b71752fdf!=IO3XX_SGDMA_NO_ERROR){SG_PRINTF(WARNING,"\x53\x53\x49\x53\x20\x62\x6c\x6f\x63\x6b\x3a\x20\x44\x4d\x41\x20\x74\x72\x61\x6e\x73\x66\x65\x72\x20\x66\x61\x69\x6c\x65\x64\x21" "\n");return;}}
#endif
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE
io3xx_sgdma_Handle*ze639490358=(io3xx_sgdma_Handle*)ssGetPWorkValue(S,z66c66efec7);if(ze639490358){io3xx_sgdma_cleanup(ze639490358);}
#endif
}
#include "sg_sfcn_glue.h"   

