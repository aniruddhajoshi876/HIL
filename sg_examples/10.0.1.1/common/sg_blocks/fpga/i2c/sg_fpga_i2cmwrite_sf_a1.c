// Copyright 2006-2026 Speedgoat GmbH

#define 	S_FUNCTION_LEVEL 	(0x13cc+674-0x166c)
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_fpga_i2cmwrite_sf_a1
#include 	<stddef.h>
#include 	<stdlib.h>
#include  <stdint.h>
#include 	"simstruc.h"
#ifdef 		MATLAB_MEX_FILE
#include 	"mex.h"
#endif
#ifndef   MATLAB_MEX_FILE
#include  "sg_common.h"
#include  "sg_fpga_io3xx_util.h"
#include  "sg_printf.h"
#endif
#include  "sg_callback.h"
#define ze13f49a01f           ssGetSFcnParam(S, (0x1c5f+591-0x1eae)) 
#define za9d8fb6bcf             ssGetSFcnParam(S, (0x1a3a+349-0x1b96)) 
#define zf5ee62a4ad        ssGetSFcnParam(S, (0x1ab3+2929-0x2622))
#define z8ba84e2285         ssGetSFcnParam(S, (0xb89+6015-0x2305))
#define zb0929cb988   ssGetSFcnParam(S, (0x2196+990-0x2570))
#define z3832b85a32           ssGetSFcnParam(S, (0xbd9+6336-0x2494))
#define z6c2191f017           ssGetSFcnParam(S, (0x134c+825-0x167f))
#define zdf24515981                           ((0x1597+3791-0x245f))
#define z2e6483d505              ((0x2057+338-0x21a9))
#define zc5ce4cb81a              ((0x1806+2923-0x2371))
#define z2b17e2ee3b              ((0x46a+6909-0x1f65))
#define z0194338df7         ((0xddd+4092-0x1dd9))
#define z9bd75cedb3         ((0x361+2550-0xd56))
#define z5bbcf8be2c            (0x16c6+3016-0x228d)
static char_T msg[(0x325+1731-0x8e8)];typedef struct z71f90c95f9{uint32_t start;uint32_t clear;uint32_t nTX_RX;uint32_t z21ab44ce3e;uint32_t count[(0x3f6+5622-0x19cc)];uint32_t z28e9d9261f[(0xb3b+2938-0x1695)];uint32_t z1fe5bfccaf[(0x11e5+2136-0x1a1d)];uint32_t z627a05d850[(0x17d5+871-0x1b1c)];uint32_t z94328689b6[(0x186+3303-0xe4d)];uint32_t z039626e71b[(0x57+3097-0xc50)];uint32_t EOT;uint32_t zdca56d3a3a;uint32_t version;}z71f90c95f9;static void mdlInitializeSizes(SimStruct*S){uint32_t i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x10aa+2621-0x1ae7));ssSetNumDiscStates(S,(0x419+7052-0x1fa5));if((uint32_t)mxGetPr(zb0929cb988)[(0x803+329-0x94c)]){if(!ssSetNumOutputPorts(S,(0x15d4+3529-0x239c))){return;}ssSetOutputPortWidth(S,(0x324+2004-0xaf8),(0x13f6+4651-0x2620));ssSetOutputPortDataType(S,(0x76+9612-0x2602),SS_BOOLEAN);}else{if(!ssSetNumOutputPorts(S,(0xc4d+1369-0x11a6))){return;}}if(!ssSetNumInputPorts(S,(0x1dc2+1841-0x24f0))){return;}ssSetInputPortWidth(S,(0xc0b+1404-0x1187),(0xea+5405-0x1606));ssSetInputPortDirectFeedThrough(S,(0x2c3+6603-0x1c8e),(0x10ec+5083-0x24c6));ssSetInputPortRequiredContiguous(S,(0x1499+1015-0x1890),(0x622+3856-0x1531));ssSetInputPortWidth(S,(0x5b8+2692-0x103b),(0x1107+2428-0x1a82));ssSetInputPortDirectFeedThrough(S,(0xf72+1963-0x171c),(0x221+8641-0x23e1));ssSetInputPortRequiredContiguous(S,(0x253+3268-0xf16),(0x203+8321-0x2283));ssSetInputPortWidth(S,(0xfe8+2974-0x1b84),(uint32_t)mxGetPr(z8ba84e2285)[(0x1886+3612-0x26a2)]);ssSetInputPortDirectFeedThrough(S,(0xc9b+658-0xf2b),(0x35d+5509-0x18e1));ssSetInputPortRequiredContiguous(S,(0x17+7824-0x1ea5),(0xf2d+3331-0x1c2f));ssSetNumSampleTimes(S,(0xe2+8034-0x2043));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x1adb+2415-0x244a));ssSetNumNonsampledZCs(S,(0xaaf+6302-0x234d));for(i=(0x3+4907-0x132e);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x53+5248-0x14d3));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x859+4845-0x1b46)]==-1.0){ssSetSampleTime(S,(0xcb1+6697-0x26da),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0xa44+927-0xde3),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x305+3065-0xefe),mxGetPr(z3832b85a32)[(0xe30+1796-0x1534)]);ssSetOffsetTime(S,(0x762+2858-0x128c),0.0);}}static void sg_ModelLoad(SimStruct*S){
#ifndef MATLAB_MEX_FILE
volatile z71f90c95f9*zca56c6316b;i2cState_t*z48b6195cd9;int moduleId=(int)mxGetScalar(ze13f49a01f);char*boardName=io3xxGetBoardNameSgLib(moduleId);if(!io3xxGetAddressSgLib((int32_t)(int)mxGetPr(ze13f49a01f)[(0x90+6684-0x1aac)],SG_FPGA_IO3XX_BAR2)){ssSetErrorStatus(S,pSgErrorStr);return;}uint32_t zf7ccd17be8=(0xeea+1225-0x13b3);if(sg_fpga_io3xx_getCmBaseAddress(moduleId,I2CM_BASE,&zf7ccd17be8)){sprintf(msg,"\x25\x73\x20\x49\x32\x43\x4d\x20\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x4f\x66\x66\x73\x65\x74\x20\x6c\x6f\x6f\x6b\x75\x70\x20\x75\x6e\x73\x75\x63\x63\x65\x73\x73\x66\x75\x6c\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}zca56c6316b=(volatile z71f90c95f9*)((uintptr_t)io3xxGetAddressSgLib((int32_t)(int)mxGetPr(ze13f49a01f)[(0x164c+3216-0x22dc)],SG_FPGA_IO3XX_BAR2)+zf7ccd17be8);ssSetPWorkValue(S,z0194338df7,(void*)zca56c6316b);if(sg_fpga_io3xx_checkCodeModuleVersion(zca56c6316b->version,z5bbcf8be2c,moduleId)){sprintf(msg,"\x25\x73\x20\x77\x72\x6f\x6e\x67\x20\x76\x65\x72\x73\x69\x6f\x6e\x20\x6f\x66\x20\x49\x32\x43\x4d\x20\x63\x6f\x64\x65\x20\x6d\x6f\x64\x75\x6c\x65\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}io3xxGetPointerI2cStateSgLib((int)mxGetPr(ze13f49a01f)[(0xb16+5937-0x2247)],&z48b6195cd9);ssSetPWorkValue(S,z9bd75cedb3,(void*)z48b6195cd9);
#endif
}static void sg_ModelStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE    
uint32_t channel;volatile z71f90c95f9*zca56c6316b=(volatile z71f90c95f9*)ssGetPWorkValue(S,z0194338df7);channel=(uint32_t)mxGetPr(za9d8fb6bcf)[(0x18f+666-0x429)]-(0x11cd+2052-0x19d0);zca56c6316b->z28e9d9261f[channel]=(uint32_t)mxGetPr(zf5ee62a4ad)[(0x12af+4889-0x25c8)];
#endif
}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_t i,channel,z039626e71b,count;real_T*y;boolean_T*out;volatile z71f90c95f9*zca56c6316b=(volatile z71f90c95f9*)ssGetPWorkValue(S,z0194338df7);i2cState_t*z48b6195cd9=(i2cState_t*)ssGetPWorkValue(S,z9bd75cedb3);channel=(uint32_t)mxGetPr(za9d8fb6bcf)[(0x1f1c+400-0x20ac)]-(0xcf3+1611-0x133d);while(!(zca56c6316b->EOT&(1UL<<channel))){}y=(real_T*)ssGetInputPortSignal(S,(0x609+5523-0x1b9c));z039626e71b=(uint32_t)y[(0x30d+9050-0x2667)];zca56c6316b->z039626e71b[channel]=z039626e71b;y=(real_T*)ssGetInputPortSignal(S,(0xde7+3305-0x1acf));count=(uint32_t)y[(0xee6+3394-0x1c28)];zca56c6316b->count[channel]=count;y=(real_T*)ssGetInputPortSignal(S,(0x384+367-0x4f1));for(i=(0xf00+3794-0x1dd2);i<count;i++){zca56c6316b->z1fe5bfccaf[channel]=(uint32_t)i;zca56c6316b->z627a05d850[channel]=(uint32_t)y[i];zca56c6316b->z21ab44ce3e=((0x246a+646-0x26ef)<<channel);zca56c6316b->z21ab44ce3e=(0x449+5329-0x191a);}sg_lockMutex(z48b6195cd9->mutex);z48b6195cd9->nTX_RX&=~(1UL<<channel);zca56c6316b->nTX_RX=z48b6195cd9->nTX_RX;if(count>(0x864+7221-0x2499)){zca56c6316b->start=(z48b6195cd9->start|(1UL<<channel));zca56c6316b->start=(z48b6195cd9->start&~(1UL<<channel));}sg_unlockMutex(z48b6195cd9->mutex);if((uint32_t)mxGetPr(zb0929cb988)[(0x85+8238-0x20b3)]){if(!(uint32_t)mxGetPr(z6c2191f017)[(0x1793+3440-0x2503)]){while(!(zca56c6316b->EOT&(1UL<<channel))){}}out=(boolean_T*)ssGetOutputPortSignal(S,(0x7aa+7127-0x2381));out[(0x17b+2560-0xb7b)]=((zca56c6316b->zdca56d3a3a)>>(channel))&(0x8d9+2918-0x143e);}
#endif
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE
#endif
}
#include "sg_sfcn_glue.h"   

