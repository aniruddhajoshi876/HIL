// Copyright 2006-2026 Speedgoat GmbH

#define 	S_FUNCTION_LEVEL 	(0x627+1839-0xd54)
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_fpga_cam_encoder_sf_3
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
typedef enum{CHANNEL,ze344b15ab1,z11530f4c08,z3ded689132,zb12fd20312,ID,zdf24515981}z144a4b4b8d;
#define za9d8fb6bcf                          ssGetSFcnParam(S, CHANNEL) 
#define z3832b85a32                        ssGetSFcnParam(S, ze344b15ab1)
#define z9710e99963 ssGetSFcnParam(S, z11530f4c08)
#define z475aa948c0             ssGetSFcnParam(S, z3ded689132)
#define zc8b1fb58da            ssGetSFcnParam(S, zb12fd20312)
#define z58f464b4bb                               ssGetSFcnParam(S, ID)
#define z2e6483d505            (0xe66+5096-0x224e)
#define zc5ce4cb81a            (0x472+6232-0x1cca)
#define z2b17e2ee3b            (0x920+5462-0x1e75)
#define z0194338df7       (0x1bc3+2480-0x2573)
#define z5bbcf8be2c          (0xb4b+1244-0x1024)
#define za9059c32c3           4294967295 
static char msg[(0x65c+7615-0x231b)];typedef struct{uint32_t z25640735be[(0x2563+175-0x24d2)];uint32_t zb49ee65d24[(0xf4b+724-0x10df)];uint32_t enable;uint32_t update;uint32_t version;}zddee59f23a;static void mdlInitializeSizes(SimStruct*S){uint32_t i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x105f+8-0x1067));ssSetNumDiscStates(S,(0x179+4342-0x126f));if((uint32_t)mxGetPr(z9710e99963)[(0x173b+3844-0x263f)]){if(!ssSetNumInputPorts(S,(0xd2c+719-0xff9))){return;}ssSetInputPortMatrixDimensions(S,(0x1501+1358-0x1a4f),(0x22a7+868-0x2601),mxGetN(za9d8fb6bcf));ssSetInputPortDirectFeedThrough(S,(0xa7f+4584-0x1c67),(0x5f4+8238-0x2621));ssSetInputPortRequiredContiguous(S,(0x1628+1489-0x1bf9),(0xa7b+4039-0x1a41));ssSetInputPortMatrixDimensions(S,(0xde3+3590-0x1be8),(0x16f5+326-0x1831),mxGetN(za9d8fb6bcf));ssSetInputPortDirectFeedThrough(S,(0x1bd5+2568-0x25dc),(0x1f3a+1077-0x236e));ssSetInputPortRequiredContiguous(S,(0x3b2+126-0x42f),(0x79+2985-0xc21));}else{if(!ssSetNumInputPorts(S,(0x543+4515-0x16e6))){return;}}if(!ssSetNumOutputPorts(S,(0xc24+5234-0x2096))){return;}ssSetNumSampleTimes(S,(0x1d6c+1971-0x251e));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0xd47+3444-0x1abb));ssSetNumNonsampledZCs(S,(0x163d+3933-0x259a));for(i=(0x1904+1350-0x1e4a);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x15c5+3192-0x223d));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x477+3424-0x11d7)]==-1.0){ssSetSampleTime(S,(0x63f+7527-0x23a6),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0xa51+883-0xdc4),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x1818+1244-0x1cf4),mxGetPr(z3832b85a32)[(0x325+1910-0xa9b)]);ssSetOffsetTime(S,(0x899+6849-0x235a),0.0);}}static void sg_ModelLoad(SimStruct*S){
#ifndef MATLAB_MEX_FILE
void*bar2ptr;volatile zddee59f23a*z06dded3a58;int moduleId=(int)mxGetScalar(z58f464b4bb);char*boardName=io3xxGetBoardNameSgLib(moduleId);if(!io3xxGetAddressSgLib((int32_t)(int)mxGetPr(z58f464b4bb)[(0xe27+4363-0x1f32)],SG_FPGA_IO3XX_BAR2)){ssSetErrorStatus(S,pSgErrorStr);return;}uint32_t zf7ccd17be8=(0x1338+3688-0x21a0);if(sg_fpga_io3xx_getCmBaseAddress(moduleId,CAM_ENCODER_BASE,&zf7ccd17be8)){sprintf(msg,"\x25\x73\x20\x43\x72\x61\x6e\x6b\x20\x45\x6e\x63\x6f\x64\x65\x72\x20\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x4f\x66\x66\x73\x65\x74\x20\x6c\x6f\x6f\x6b\x75\x70\x20\x75\x6e\x73\x75\x63\x63\x65\x73\x73\x66\x75\x6c\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}bar2ptr=io3xxGetAddressSgLib((int32_t)(int)mxGetPr(z58f464b4bb)[(0x1485+3467-0x2210)],SG_FPGA_IO3XX_BAR2);z06dded3a58=(zddee59f23a*)((uintptr_t)bar2ptr+(uintptr_t)zf7ccd17be8);ssSetPWorkValue(S,z0194338df7,(void*)z06dded3a58);if(sg_isFirstModelLoad()){if(sg_fpga_io3xx_checkCodeModuleVersion(z06dded3a58->version,z5bbcf8be2c,moduleId)){sprintf(msg,"\x25\x73\x20\x77\x72\x6f\x6e\x67\x20\x76\x65\x72\x73\x69\x6f\x6e\x20\x6f\x66\x20\x43\x61\x6d\x20\x45\x6e\x63\x6f\x64\x65\x72\x20\x63\x6f\x64\x65\x20\x6d\x6f\x64\x75\x6c\x65\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}}
#endif
}static void sg_ModelStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE    
uint32_t i,z26dbd73a5e;uint32_t channel,enable;double length,start,stop;uint32_t z5b25496ff9,z433e024ec3;enable=(0x14c+8189-0x2149);volatile zddee59f23a*z06dded3a58;z06dded3a58=(zddee59f23a*)(ssGetPWorkValue(S,z0194338df7));for(i=(0xd6b+6068-0x251f);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x570+5103-0x195e);for(z26dbd73a5e=(0x7ff+6996-0x2353);z26dbd73a5e<(0x2dd+6359-0x1baa);z26dbd73a5e++){start=(double)mxGetPr(z475aa948c0)[(0x12a9+503-0x1496)*i+z26dbd73a5e];if(start>=720.0){start-=720.0;}length=(double)mxGetPr(zc8b1fb58da)[(0x49b+979-0x864)*i+z26dbd73a5e];z5b25496ff9=(uint32_t)(za9059c32c3*(start/720.0));stop=z5b25496ff9+length;stop=start+length;if(stop>=720.0){stop-=720.0;}z433e024ec3=(uint32_t)(za9059c32c3*(stop/720.0));z06dded3a58->z25640735be[(0x26a+7496-0x1fa8)*channel+z26dbd73a5e]=z5b25496ff9;z06dded3a58->zb49ee65d24[(0x828+5857-0x1eff)*channel+z26dbd73a5e]=z433e024ec3;}enable|=((0x67b+6466-0x1fbc)<<channel);}z06dded3a58->update=(0xc7b+929-0x101b);z06dded3a58->update=(0x1b8c+1508-0x2170);z06dded3a58->enable|=enable;
#endif
}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_t i,z26dbd73a5e,channel;double*z995c3c405e,*z2bd774d5dc;double start,stop;uint32_t z5b25496ff9,z433e024ec3;volatile zddee59f23a*z06dded3a58;z06dded3a58=(zddee59f23a*)(ssGetPWorkValue(S,z0194338df7));if((uint32_t)mxGetPr(z9710e99963)[(0x13c8+542-0x15e6)]){z995c3c405e=(double*)ssGetInputPortSignal(S,(0xd1b+1697-0x13bc));z2bd774d5dc=(double*)ssGetInputPortSignal(S,(0x19c8+1875-0x211a));for(i=(0xc03+2059-0x140e);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0xd94+4343-0x1e8a);for(z26dbd73a5e=(0x1e96+484-0x207a);z26dbd73a5e<(0x6b6+4182-0x1702);z26dbd73a5e++){start=z995c3c405e[(0x72+8479-0x2187)*i+z26dbd73a5e];if(start>=720.0){start-=720.0;}z5b25496ff9=(uint32_t)(za9059c32c3*(start/720.0));stop=start+z2bd774d5dc[(0x609+1420-0xb8b)*i+z26dbd73a5e];if(stop>=720.0){stop-=720.0;}z433e024ec3=(uint32_t)(za9059c32c3*(stop/720.0));z06dded3a58->z25640735be[(0x871+3646-0x16a5)*channel+z26dbd73a5e]=z5b25496ff9;z06dded3a58->zb49ee65d24[(0x782+1849-0xeb1)*channel+z26dbd73a5e]=z433e024ec3;}}z06dded3a58->update=(0x212+3192-0xe89);z06dded3a58->update=(0x56a+4122-0x1584);}
#endif
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE
volatile zddee59f23a*z06dded3a58;z06dded3a58=(zddee59f23a*)(ssGetPWorkValue(S,z0194338df7));z06dded3a58->enable=(0xd7+8784-0x2327);
#endif
}
#include "sg_sfcn_glue.h"   

