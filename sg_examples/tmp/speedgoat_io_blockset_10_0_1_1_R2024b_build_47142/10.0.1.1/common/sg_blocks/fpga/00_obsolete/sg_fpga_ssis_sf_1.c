// Copyright 2006-2026 Speedgoat GmbH

#define 	S_FUNCTION_LEVEL 	(0x131a+3739-0x21b3)
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_fpga_ssis_sf_1
#include 	<stddef.h>
#include 	<stdlib.h>
#include  <stdint.h>
#include 	"simstruc.h" 
#ifdef 		MATLAB_MEX_FILE
#include 	"mex.h"
#endif
#ifndef         MATLAB_MEX_FILE
#include        "sg_common.h"
#include        "sg_fpga_io3xx_util.h"
#include        "sg_callback_legacy.h"
#include        "sg_printf.h"
#endif
#define zdf24515981        ((0x14fa+1698-0x1b8c))
#define z533b11d03f         ssGetSFcnParam(S,  (0x842+85-0x897)) 
#define ze13f49a01f         ssGetSFcnParam(S,  (0x1e01+173-0x1ead))
#define za9d8fb6bcf           ssGetSFcnParam(S,  (0x1291+409-0x1428)) 
#define z31fb671cb8              ssGetSFcnParam(S,  (0x1b8+1361-0x706))
#define z86af52d74e              ssGetSFcnParam(S,  (0x1ad8+2587-0x24ef))
#define zf5ee62a4ad      ssGetSFcnParam(S,  (0x1a2a+3043-0x2608))
#define z3a4907dee5          ssGetSFcnParam(S,  (0x840+4076-0x1826))
#define zb0ce0940e9         ssGetSFcnParam(S,  (0x66c+7703-0x247c))
#define zb00b469153        ssGetSFcnParam(S,  (0xad4+3795-0x199f))
#define zd259a80613    ssGetSFcnParam(S,  (0x18c2+3635-0x26ec))
#define zbdd1493fee         ssGetSFcnParam(S, (0xeef+4770-0x2187))
#define z3832b85a32         ssGetSFcnParam(S, (0xc4+1871-0x808))
#define z702a26a5e9              ssGetSFcnParam(S, (0x401+7538-0x2167))
#define z596b77cbe5            ssGetSFcnParam(S, (0xcad+4129-0x1cc1))
#define z6ee4a37819            	  ssGetSFcnParam(S, (0x6c8+1552-0xcca))
#define z6699565c9c        ssGetSFcnParam(S, (0x4cb+341-0x611))
#define z2e6483d505            ((0xc4+3295-0xda3))
#define zc5ce4cb81a            ((0x9a+3818-0xf84))
#define z2b17e2ee3b            ((0x4b6+4438-0x160b))
#define z93d7dbe681       ((0x14e4+2956-0x2070))
#define z375a4ff848              (737280)
static char_T msg[(0x13ca+2892-0x1e16)];typedef struct{uint32_t z15923ef3d9[(0xbe1+5060-0x1f85)];uint32_t za746b13f73[(0xb56+5214-0x1f94)];uint32_t z02bb7b1721[(0x17a9+2878-0x22c7)];uint32_t z1ad71181ab[(0x1ca3+1935-0x2412)];uint32_t z2681ed6ece[(0x1667+3282-0x2319)];uint32_t z28e9d9261f[(0x155f+1744-0x1c0f)];uint32_t z2ae1a9d412[(0x66c+3707-0x14c7)];uint32_t z07f373fbd4[(0x15f3+937-0x197c)];uint32_t zac3cadef55[(0x1030+3071-0x1c0f)];uint32_t za3910307c9[(0x65c+1501-0xc19)];uint32_t zd176e82c10[(0x11dd+4017-0x216e)];uint32_t z4ae288e0c9[(0xc61+6747-0x269c)];uint32_t z12402c138a[(0xecd+1166-0x133b)];uint32_t z8575031947[(0x4cc+8152-0x2484)];uint32_t za98b68092e[(0xc13+1455-0x11a2)];uint32_t z75afeb530f[(0x1a9b+732-0x1d57)];uint32_t zbea4a89f24;uint32_t zdc0d676974;uint32_t test1;uint32_t test2;}z6b3137e20b;void z643389039d(uint32_t*zb9e8f50428,uint32_t*z5b2574d0cd,uint32_t z15923ef3d9,uint32_t za746b13f73){int32_t i,z26dbd73a5e,z5f52b5adb3;uint8_t z718c4c15f4[(0xf04+6115-0x25e7)]={(0x17c3+307-0x18f6)};for(i=(0x2366+701-0x2623);i<(0x7b6+6242-0x2010);i++){zb9e8f50428[i]=(0x1942+1706-0x1fec);}z5f52b5adb3=(0x9d0+4229-0x1956);for(i=za746b13f73-(0x1514+2118-0x1d59);i>=(0x12cf+3224-0x1f67);i--){for(z26dbd73a5e=z15923ef3d9-(0x10b+3332-0xe0e);z26dbd73a5e>=(0xa65+5160-0x1e8d);z26dbd73a5e--){if((z5b2574d0cd[i]&((0x22d8+171-0x2382)<<z26dbd73a5e))>(0x16b+3032-0xd43)){z718c4c15f4[z5f52b5adb3]=(0x224c+424-0x23f3);}z5f52b5adb3--;}}z5f52b5adb3=(0x11fd+5242-0x2677);for(i=(0x95f+4124-0x197b);i<(0xb00+1513-0x10e1);i++){for(z26dbd73a5e=(0x92a+3943-0x1891);z26dbd73a5e<(0xa2+2262-0x958);z26dbd73a5e++){if(z718c4c15f4[z5f52b5adb3]){zb9e8f50428[i]|=((0x1619+2148-0x1e7c)<<z26dbd73a5e);}z5f52b5adb3++;}}}static void mdlInitializeSizes(SimStruct*S){uint32_t i,zbc7ebd0e53;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x10f5+2364-0x1a31));ssSetNumDiscStates(S,(0x9f8+1219-0xebb));zbc7ebd0e53=(uint32_t)mxGetN(za9d8fb6bcf);ssSetNumInputPorts(S,zbc7ebd0e53);for(i=(0x33d+3229-0xfda);i<zbc7ebd0e53;i++){ssSetInputPortDataType(S,i,SS_UINT32);ssSetInputPortWidth(S,i,(uint32_t)mxGetPr(zb0ce0940e9)[i]);ssSetInputPortDirectFeedThrough(S,i,(0x5ab+4280-0x1662));ssSetInputPortRequiredContiguous(S,i,(0xf21+3673-0x1d79));}ssSetNumSampleTimes(S,(0x1a8+7472-0x1ed7));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0xc61+4760-0x1ef9));ssSetNumNonsampledZCs(S,(0x1059+2330-0x1973));for(i=(0x987+5866-0x2071);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x1605+3865-0x251e));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0xe90+700-0x114c)]==-1.0){ssSetSampleTime(S,(0x35f+4646-0x1585),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x12ba+386-0x143c),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x145a+3298-0x213c),mxGetPr(z3832b85a32)[(0x19dc+896-0x1d5c)]);ssSetOffsetTime(S,(0xeed+4490-0x2077),0.0);}}
#define MDL_START
static void mdlStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
int32_t bus,slot;uint32_t i,channel,zbea4a89f24,zdc0d676974;volatile z6b3137e20b*z1b230a715b;sg_fpga_io3xxModuleIdT moduleId;uint32_t boardType;void*bar2ptr;boardType=(uint32_t)mxGetPr(z533b11d03f)[(0xa+1257-0x4f3)];if((int32_t)sg_fpga_IO3xxGetModuleId(boardType,&moduleId)<(0x21ed+516-0x23f1)){sprintf(msg,"\x53\x53\x49\x53\x20\x62\x6c\x6f\x63\x6b\x3a\x20\x62\x6f\x61\x72\x64\x20\x74\x79\x70\x65\x20\x69\x6e\x63\x6f\x72\x72\x65\x63\x74\x2e");ssSetErrorStatus(S,msg);}if(mxGetN(z702a26a5e9)==(0x1f78+109-0x1fe4)){bus=(0x1c64+1775-0x2353);slot=(int_T)mxGetPr(z702a26a5e9)[(0xccb+4112-0x1cdb)];}else{bus=(int_T)mxGetPr(z702a26a5e9)[(0xa97+6734-0x24e5)];slot=(int_T)mxGetPr(z702a26a5e9)[(0x136+8279-0x218c)];}if(!io3xxGetAddressSgLib((int32_t)(int)mxGetPr(ze13f49a01f)[(0x1f13+969-0x22dc)],SG_FPGA_IO3XX_BAR2)){ssSetErrorStatus(S,pSgErrorStr);return;}bar2ptr=io3xxGetAddressSgLib((int32_t)(int)mxGetPr(ze13f49a01f)[(0x17e0+3435-0x254b)],SG_FPGA_IO3XX_BAR2);ssSetPWorkValue(S,z93d7dbe681,(void*)bar2ptr);z1b230a715b=(z6b3137e20b*)((uintptr_t)bar2ptr+z375a4ff848);if(!sg_isModelInit()){z1b230a715b->test2=2863311530;zbea4a89f24=z1b230a715b->zbea4a89f24;zdc0d676974=z1b230a715b->zdc0d676974;for(i=(0xefc+4798-0x21ba);i<(uint32_t)mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x4df+2953-0x1067);if((uint32_t)mxGetPr(z31fb671cb8)[i]){zbea4a89f24|=((0x17b4+2870-0x22e9)<<channel);}else{zbea4a89f24&=~((0x1a5d+1694-0x20fa)<<channel);}if((uint32_t)mxGetPr(z86af52d74e)[i]){zdc0d676974|=((0xe85+2655-0x18e3)<<channel);}else{zdc0d676974&=~((0x17d5+837-0x1b19)<<channel);}z1b230a715b->z15923ef3d9[channel]=(uint32_t)mxGetPr(z3a4907dee5)[i];z1b230a715b->za746b13f73[channel]=(uint32_t)mxGetPr(zb0ce0940e9)[i];z1b230a715b->z02bb7b1721[channel]=(uint32_t)mxGetPr(zb00b469153)[i];z1b230a715b->z1ad71181ab[channel]=(uint32_t)mxGetPr(zd259a80613)[i];z1b230a715b->z2681ed6ece[channel]=(uint32_t)mxGetPr(zbdd1493fee)[i];z1b230a715b->z28e9d9261f[channel]=(uint32_t)mxGetPr(zf5ee62a4ad)[i];z1b230a715b->za98b68092e[channel]=(uint32_t)mxGetPr(z6ee4a37819)[i];z1b230a715b->z75afeb530f[channel]=(uint32_t)mxGetPr(z6699565c9c)[i];}z1b230a715b->zbea4a89f24=zbea4a89f24;z1b230a715b->zdc0d676974=zdc0d676974;}
#endif
}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){
#ifndef MATLAB_MEX_FILE
uintptr_t base=(uintptr_t)ssGetPWorkValue(S,z93d7dbe681);uint32_t i,z26dbd73a5e,channel;volatile z6b3137e20b*z1b230a715b;uint32_t*in;uint32_t z463aec3630,zb9e8f50428[(0x1169+3644-0x1f9d)],z68d7c00737[(0x2072+104-0x20ba)];z1b230a715b=(z6b3137e20b*)(base+z375a4ff848);for(i=(0x1f49+1858-0x268b);i<(uint32_t)mxGetN(za9d8fb6bcf);i++){zb9e8f50428[(0x9a4+4630-0x1bba)]=(0x3a7+8659-0x257a);zb9e8f50428[(0x463+806-0x788)]=(0x792+2830-0x12a0);zb9e8f50428[(0x10d8+731-0x13b1)]=(0x21+9685-0x25f6);zb9e8f50428[(0x1395+2409-0x1cfb)]=(0xd71+6240-0x25d1);zb9e8f50428[(0x13c3+4249-0x2458)]=(0x1a4a+591-0x1c99);zb9e8f50428[(0xf22+5295-0x23cc)]=(0xa17+1315-0xf3a);zb9e8f50428[(0x4ac+7735-0x22dd)]=(0x173b+2797-0x2228);zb9e8f50428[(0x136+9388-0x25db)]=(0x1b83+808-0x1eab);channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0xa3b+352-0xb9a);in=(uint32_t*)ssGetInputPortSignal(S,i);for(z26dbd73a5e=(0xb+6797-0x1a98);z26dbd73a5e<(uint32_t)mxGetPr(zb0ce0940e9)[i];z26dbd73a5e++){if((uint32_t)mxGetPr(z596b77cbe5)[(0x1182+1620-0x17d6)]==(0xa93+5212-0x1eee)){z68d7c00737[z26dbd73a5e]=in[z26dbd73a5e];}else{z463aec3630=in[z26dbd73a5e]^(in[z26dbd73a5e]>>(0x1674+2402-0x1fd5));z68d7c00737[z26dbd73a5e]=z463aec3630;}}z643389039d(zb9e8f50428,z68d7c00737,(uint32_t)mxGetPr(z3a4907dee5)[i],(uint32_t)mxGetPr(zb0ce0940e9)[i]);z1b230a715b->z2ae1a9d412[channel]=zb9e8f50428[(0x669+6420-0x1f7d)]<<(0xbe0+1872-0x132f);z1b230a715b->z07f373fbd4[channel]=zb9e8f50428[(0x1e6+17-0x1f6)]<<(0x2c1+7608-0x2078);z1b230a715b->zac3cadef55[channel]=zb9e8f50428[(0x3a5+2624-0xde3)]<<(0x1807+827-0x1b41);z1b230a715b->za3910307c9[channel]=zb9e8f50428[(0xbd0+2748-0x1689)]<<(0x34a+7167-0x1f48);z1b230a715b->zd176e82c10[channel]=zb9e8f50428[(0x1ccd+89-0x1d22)]<<(0x1a43+1611-0x208d);z1b230a715b->z4ae288e0c9[channel]=zb9e8f50428[(0xdbf+2170-0x1634)]<<(0x822+668-0xabd);z1b230a715b->z12402c138a[channel]=zb9e8f50428[(0xc9a+3645-0x1ad1)]<<(0x2224+612-0x2487);z1b230a715b->z8575031947[channel]=zb9e8f50428[(0x1d3d+568-0x1f6e)]<<(0x13d+3259-0xdf7);}
#endif
}static void mdlTerminate(SimStruct*S){
#ifndef MATLAB_MEX_FILE     
#endif
}
#include "sg_sfcn_glue.h"   

