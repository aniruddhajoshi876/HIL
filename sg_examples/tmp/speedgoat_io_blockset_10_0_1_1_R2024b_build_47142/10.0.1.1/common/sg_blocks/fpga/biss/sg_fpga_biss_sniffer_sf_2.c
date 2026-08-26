// Copyright 2006-2026 Speedgoat GmbH

#define 	S_FUNCTION_LEVEL 	(0x1b0f+2179-0x2390)
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_fpga_biss_sniffer_sf_2
#include 	<stddef.h>
#include 	<stdint.h>
#include 	<stdlib.h>
#include 	"simstruc.h" 
#ifdef 		MATLAB_MEX_FILE
#include 	"mex.h"
#endif
#ifndef         MATLAB_MEX_FILE
#include     "sg_common.h"
#include     "sg_fpga_io3xx_util.h"
#include     "sg_printf.h"
#endif
#define SG_EARLY_INIT
#include "sg_callback.h"
#define ze13f49a01f         ssGetSFcnParam(S, (0x49d+4906-0x17c7)) 
#define za9d8fb6bcf           ssGetSFcnParam(S, (0x3ca+2272-0xca9)) 
#define zf12578dfb8           ssGetSFcnParam(S, (0x731+1241-0xc08))
#define z0fbad31890         ssGetSFcnParam(S, (0xe73+4015-0x1e1f))
#define z3832b85a32         ssGetSFcnParam(S, (0x120a+3077-0x1e0b))
#define zdf24515981                         ((0x17f5+414-0x198e))
#define z2e6483d505            ((0x29f+8969-0x25a8))
#define zc5ce4cb81a            ((0x1a7c+66-0x1abe))
#define z2b17e2ee3b            ((0x869+6755-0x22cc))
#define z5bbcf8be2c            (0x1951+2787-0x2432)
static char msg[(0x602+5461-0x1a57)];typedef struct{uint32_t timeout[(0x1cac+668-0x1f28)];uint32_t zb5504d2c07[(0x7d3+4918-0x1ae9)];uint32_t z63ed22d5f0[(0x4ca+7677-0x22a7)];uint32_t z91e669dbb0[(0x83+265-0x16c)];uint32_t z234ec7021f[(0x3a2+1582-0x9b0)];uint32_t zb871a780a7;uint32_t version;}z7a6eea8a71;typedef struct{z7a6eea8a71*z372c4452d9;}zedee96a198;static void mdlInitializeSizes(SimStruct*S){uint32_t i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x8fb+1523-0xeee));ssSetNumDiscStates(S,(0x1219+3068-0x1e15));ssSetNumOutputPorts(S,(0xd39+4916-0x206a));ssSetOutputPortDataType(S,(0x11b9+3207-0x1e40),SS_UINT32);ssSetOutputPortWidth(S,(0x1dec+1721-0x24a5),mxGetN(za9d8fb6bcf));ssSetOutputPortDataType(S,(0x6ec+683-0x996),SS_UINT32);ssSetOutputPortWidth(S,(0x68f+118-0x704),mxGetN(za9d8fb6bcf));ssSetOutputPortDataType(S,(0x1109+2114-0x1949),SS_UINT32);ssSetOutputPortWidth(S,(0x860+707-0xb21),mxGetN(za9d8fb6bcf));ssSetNumSampleTimes(S,(0xe55+5173-0x2289));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0xa5+7312-0x1d35));ssSetNumNonsampledZCs(S,(0x235d+528-0x256d));for(i=(0x916+5361-0x1e07);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x18b5+1131-0x1d20));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0xac2+5305-0x1f7b)]==-1.0){ssSetSampleTime(S,(0x1268+771-0x156b),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0xe43+2544-0x1833),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x31d+4019-0x12d0),mxGetPr(z3832b85a32)[(0x2ec+5991-0x1a53)]);ssSetOffsetTime(S,(0x120f+2280-0x1af7),0.0);}}static void sg_ModelLoad(SimStruct*S){
#ifndef MATLAB_MEX_FILE
void*bar2ptr;int moduleId=(int)mxGetScalar(ze13f49a01f);char*boardName=io3xxGetBoardNameSgLib(moduleId);int z3e423c83e6=(int)mxGetPr(za9d8fb6bcf)[(0x8e0+5332-0x1db4)]-(0x12e3+2854-0x1e08);int ze0bc7e48d0=(int)(SG_BLOCK_TYPE_BISS_SNIFFER);zedee96a198*za06fdddc20=(zedee96a198*)malloc(sizeof(zedee96a198));sg_fpga_io3xx_block_register((uint32_t)moduleId,(uint32_t)ze0bc7e48d0,(uint32_t)z3e423c83e6,(void*)za06fdddc20);if(!io3xxGetAddressSgLib((int32_t)(int)mxGetPr(ze13f49a01f)[(0x1279+2672-0x1ce9)],SG_FPGA_IO3XX_BAR2)){ssSetErrorStatus(S,pSgErrorStr);return;}uint32_t zf7ccd17be8=(0x463+1784-0xb5b);if(sg_fpga_io3xx_getCmBaseAddress(moduleId,BISS_SNIFFER_BASE,&zf7ccd17be8)){sprintf(msg,"\x25\x73\x20\x42\x49\x53\x53\x20\x53\x6e\x69\x66\x66\x65\x72\x20\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x4f\x66\x66\x73\x65\x74\x20\x6c\x6f\x6f\x6b\x75\x70\x20\x75\x6e\x73\x75\x63\x63\x65\x73\x73\x66\x75\x6c\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}bar2ptr=io3xxGetAddressSgLib((int32_t)(int)mxGetPr(ze13f49a01f)[(0x2212+974-0x25e0)],SG_FPGA_IO3XX_BAR2);za06fdddc20->z372c4452d9=(z7a6eea8a71*)((uintptr_t)bar2ptr+zf7ccd17be8);if(sg_fpga_io3xx_checkCodeModuleVersion(za06fdddc20->z372c4452d9->version,z5bbcf8be2c,moduleId)){sprintf(msg,"\x25\x73\x20\x77\x72\x6f\x6e\x67\x20\x76\x65\x72\x73\x69\x6f\x6e\x20\x6f\x66\x20\x42\x49\x53\x53\x20\x53\x6e\x69\x66\x66\x65\x72\x20\x63\x6f\x64\x65\x20\x6d\x6f\x64\x75\x6c\x65\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}
#endif
}static void sg_ModelStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
volatile z7a6eea8a71*z372c4452d9;uint32_t i,channel;int moduleId=(int)mxGetScalar(ze13f49a01f);int z3e423c83e6=(int)mxGetPr(za9d8fb6bcf)[(0x18c4+1022-0x1cc2)]-(0x1b29+1429-0x20bd);int ze0bc7e48d0=(int)(SG_BLOCK_TYPE_BISS_SNIFFER);sg_block_info*z05264739a1=sg_fpga_io3xx_block_get((uint32_t)moduleId,(uint32_t)ze0bc7e48d0,(uint32_t)z3e423c83e6);zedee96a198*za06fdddc20=(zedee96a198*)z05264739a1->custom_data;z372c4452d9=za06fdddc20->z372c4452d9;for(i=(0x547+1194-0x9f1);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0xac0+1937-0x1250);z372c4452d9->zb5504d2c07[channel]=(uint32_t)mxGetPr(z0fbad31890)[i];z372c4452d9->timeout[channel]=(uint32_t)mxGetPr(zf12578dfb8)[i];}
#endif
}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_t i,channel,zb871a780a7,z234ec7021f;volatile z7a6eea8a71*z372c4452d9;uint32_t*z126ed5de63;int moduleId=(int)mxGetScalar(ze13f49a01f);int z3e423c83e6=(int)mxGetPr(za9d8fb6bcf)[(0x2b8+4167-0x12ff)]-(0xa9+6130-0x189a);int ze0bc7e48d0=(int)(SG_BLOCK_TYPE_BISS_SNIFFER);sg_block_info*z05264739a1=sg_fpga_io3xx_block_get((uint32_t)moduleId,(uint32_t)ze0bc7e48d0,(uint32_t)z3e423c83e6);zedee96a198*za06fdddc20=(zedee96a198*)z05264739a1->custom_data;z372c4452d9=za06fdddc20->z372c4452d9;zb871a780a7=(0x14bd+4477-0x263a);for(i=(0x10ca+5036-0x2476);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0xfa5+3723-0x1e2f);zb871a780a7|=((0x2c0+5445-0x1804)<<channel);}z372c4452d9->zb871a780a7=zb871a780a7;z372c4452d9->zb871a780a7=(0x29b+1510-0x881);for(i=(0x8e6+5729-0x1f47);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0xfa1+1942-0x1736);z126ed5de63=(uint32_t*)ssGetOutputPortSignal(S,(0xcd5+6497-0x2634));z234ec7021f=z372c4452d9->z234ec7021f[channel];z126ed5de63[i]=(uint32_t)z234ec7021f;if(z234ec7021f>(0x8d+19-0xa0)){z126ed5de63=(uint32_t*)ssGetOutputPortSignal(S,(0x16a+2734-0xc17));z126ed5de63[i]=z372c4452d9->z63ed22d5f0[channel];if(z234ec7021f>(0xf66+6056-0x26ee)){z126ed5de63=(uint32_t*)ssGetOutputPortSignal(S,(0x237+1034-0x641));z126ed5de63[i]=z372c4452d9->z91e669dbb0[channel];}else{z126ed5de63=(uint32_t*)ssGetOutputPortSignal(S,(0x59+5627-0x1654));z126ed5de63[i]=(0x450+4721-0x16c1);}}else{z126ed5de63=(uint32_t*)ssGetOutputPortSignal(S,(0x94f+3610-0x1769));z126ed5de63[i]=(0x91d+265-0xa26);z126ed5de63=(uint32_t*)ssGetOutputPortSignal(S,(0x655+5494-0x1bca));z126ed5de63[i]=(0x1207+713-0x14d0);}}
#endif
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE     
int moduleId=(int)mxGetScalar(ze13f49a01f);int z3e423c83e6=(int)mxGetPr(za9d8fb6bcf)[(0xf8+7777-0x1f59)]-(0xdcb+1705-0x1473);int ze0bc7e48d0=(int)(SG_BLOCK_TYPE_BISS_SNIFFER);sg_block_info*z05264739a1=sg_fpga_io3xx_block_get((uint32_t)moduleId,(uint32_t)ze0bc7e48d0,(uint32_t)z3e423c83e6);zedee96a198*za06fdddc20=(zedee96a198*)z05264739a1->custom_data;sg_fpga_io3xx_block_unregister((uint32_t)moduleId,(uint32_t)ze0bc7e48d0,(uint32_t)z3e423c83e6);free(za06fdddc20);
#endif
}
#include "sg_sfcn_glue.h"   

