// Copyright 2006-2026 Speedgoat GmbH

#define    S_FUNCTION_LEVEL   (0xa86+394-0xc0e)
#undef     S_FUNCTION_NAME
#define    S_FUNCTION_NAME   sg_fpga_vrs_sf_4
#include   <stddef.h>
#include   <stdlib.h>
#include   <stdint.h>
#include   <stdbool.h>
#include   <stdio.h>
#include   "simstruc.h"
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif
#ifndef MATLAB_MEX_FILE
#include "sg_common.h"
#include "sg_fpga_io3xx_util.h"
#include "sg_printf.h"
#endif
#define SG_EARLY_INIT
#include "sg_callback.h"
typedef enum{zfaa050b79d,CHANNEL,ze344b15ab1,zea52f4bb4e,z1c6d416fde,z88c63e0ba1,z731cbedf5e,z878b4ea0cf,z1591296ec0,zab4b0248d6,za950a51ae2,zd8d2962a39,zecbe120e5b,z867e62fe81,zdf24515981}z1ebbfc0a89;
#define ze13f49a01f         ssGetSFcnParam(S, zfaa050b79d)
#define za9d8fb6bcf           ssGetSFcnParam(S, CHANNEL)
#define z3832b85a32         ssGetSFcnParam(S, ze344b15ab1)
#define z38f57ee110     ssGetSFcnParam(S, z1c6d416fde)
#define za08eaecce0         ssGetSFcnParam(S, z88c63e0ba1)
#define zd68f0d3534          ssGetSFcnParam(S, z731cbedf5e)
#define z0760155ccd       ssGetSFcnParam(S, z878b4ea0cf)
#define za10893a465         ssGetSFcnParam(S, z1591296ec0)
#define zb8a484fa5c   ssGetSFcnParam(S, zab4b0248d6)
#define zaaf55eaed6       ssGetSFcnParam(S, za950a51ae2)
#define zee2316ae4d      ssGetSFcnParam(S, zd8d2962a39)
#define zdd9dec61b1       ssGetSFcnParam(S, zecbe120e5b)
#define z62e46f52ac      ssGetSFcnParam(S, zea52f4bb4e)
#define zf332288c20         ssGetSFcnParam(S, z867e62fe81)
#define z2e6483d505            ((0x16ad+244-0x17a1))
#define zc5ce4cb81a            ((0x122b+1509-0x1810))
#define z2b17e2ee3b            ((0x407+8852-0x269b))
#define z5bbcf8be2c          (0xcab+3118-0x18d5)
#define z4099fa3dcd          (32767/(0x6fa+4597-0x18e5))
#define zae4028a32c            4294967296.0  
#define z703d77db05            65536U        
#define z62917fff17            32768.0       
#define z2352836e59            16384U        
#define z70b7fa4779    720.0
#define zfd3fa9274b      32U
typedef struct{uint32_t version;uint32_t enable;uint32_t z172df257bb;uint32_t reserved[(0x1ef6+912-0x2269)];uint32_t z4a29242ba3[(0x4bc+3976-0x1424)];uint32_t z8e28bead35[(0x2aa+4551-0x1451)];uint32_t z8302df4cf5[(0xceb+2992-0x187b)];uint32_t z0754dd67cc[(0x1412+2835-0x1f05)];uint32_t zb640018cea[(0x1850+3705-0x26a9)];uint32_t z35e0b1bf97[(0x663+2040-0xe3b)];uint32_t z7b2bfa7236[(0x10a+5988-0x184e)];uint32_t zfb17dcf6d2[(0xaef+4273-0x1b80)];uint32_t z4250da54be[(0x17d2+2391-0x2109)];uint32_t position[(0xbd4+499-0xda7)];uint32_t z91da63235a[(0xd78+2281-0x1641)];uint32_t offset[(0x512+8399-0x25c1)];uint32_t zb46289d48f[(0x989+4255-0x1a08)];uint32_t zd4b9d383d6[(0xd30+5794-0x23b2)];}z84da6f474e;
#ifndef MATLAB_MEX_FILE
typedef struct{z84da6f474e*zf2ea15f185;real_T z87a9298581;uint32_t z03cd415bce;uint32_t z24a76e5f56[(0x1a6+3906-0x10c8)];uint32_t ze679452aeb[(0x105c+99-0x109f)];}z524b6b92ed;
#endif
static char_T msg[(0x11dd+2670-0x1b4b)];
#ifndef MATLAB_MEX_FILE
static uint32_t z019dbba4ef(real_T z4fe630f9c1){while(z4fe630f9c1>=z70b7fa4779){z4fe630f9c1-=z70b7fa4779;}while(z4fe630f9c1<0.0){z4fe630f9c1+=z70b7fa4779;}return(uint32_t)(z4fe630f9c1*zae4028a32c/z70b7fa4779);}
#endif
static void mdlInitializeSizes(SimStruct*S){uint32_t i,z4d71223f46,zbb09957843;real_T channel;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}if(mxGetM(za9d8fb6bcf)*mxGetN(za9d8fb6bcf)!=(0xe70+5970-0x25c1)){sprintf(msg,"\x56\x52\x53\x20\x64\x72\x69\x76\x65\x72\x20\x73\x75\x70\x70\x6f\x72\x74\x73\x20\x65\x78\x61\x63\x74\x6c\x79\x20\x6f\x6e\x65\x20\x63\x68\x61\x6e\x6e\x65\x6c\x20\x70\x65\x72\x20\x62\x6c\x6f\x63\x6b\x2e" "\n");ssSetErrorStatus(S,msg);return;}channel=mxGetPr(za9d8fb6bcf)[(0x400+8324-0x2484)];if(channel<1.0||channel>(real_T)zfd3fa9274b){sprintf(msg,"\x56\x52\x53\x20\x63\x68\x61\x6e\x6e\x65\x6c\x20\x6d\x75\x73\x74\x20\x62\x65\x20\x69\x6e\x20\x74\x68\x65\x20\x72\x61\x6e\x67\x65\x20\x31\x2e\x2e\x25\x75\x2e" "\n",zfd3fa9274b);ssSetErrorStatus(S,msg);return;}if(mxGetM(z38f57ee110)*mxGetN(z38f57ee110)<z703d77db05){sprintf(msg,"\x56\x52\x53\x20\x73\x69\x67\x6e\x61\x6c\x20\x76\x65\x63\x74\x6f\x72\x20\x6d\x75\x73\x74\x20\x31\x20\x63\x6f\x6e\x74\x61\x69\x6e\x20\x61\x74\x20\x6c\x65\x61\x73\x74\x20\x25\x64\x2c\x20\x25\x64\x73\x61\x6d\x70\x6c\x65\x73\x2e" "\n",mxGetM(z38f57ee110),mxGetN(z38f57ee110));ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0xddd+5177-0x2216));ssSetNumDiscStates(S,(0x1240+3499-0x1feb));z4d71223f46=2U;if((uint32_t)mxGetPr(za10893a465)[(0x2315+899-0x2698)]){z4d71223f46++;}if((uint32_t)mxGetPr(zdd9dec61b1)[(0xc0+6550-0x1a56)]){z4d71223f46++;}(void)ssSetNumInputPorts(S,z4d71223f46);for(i=(0x10d+9014-0x2443);i<z4d71223f46;i++){ssSetInputPortWidth(S,i,(0x72a+3405-0x1476));ssSetInputPortDirectFeedThrough(S,i,(0x833+5637-0x1e37));ssSetInputPortRequiredContiguous(S,i,(0x11f9+4311-0x22cf));ssSetInputPortDataType(S,i,SS_DOUBLE);}if((uint32_t)mxGetPr(zb8a484fa5c)[(0x1308+1255-0x17ef)]){zbb09957843=1U;(void)ssSetNumOutputPorts(S,zbb09957843);ssSetOutputPortWidth(S,(0xdb0+3501-0x1b5d),(0xb7f+4129-0x1b9f));}else{zbb09957843=0U;(void)ssSetNumOutputPorts(S,zbb09957843);}ssSetNumSampleTimes(S,(0x6f4+6630-0x20d9));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x1a01+1473-0x1fc2));ssSetNumNonsampledZCs(S,(0x8d1+1994-0x109b));for(i=(0x85+2906-0xbdf);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x956+2002-0x1128));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x492+5895-0x1b99)]==-1.0){ssSetSampleTime(S,(0x6a4+3640-0x14dc),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x24+7810-0x1ea6),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x40c+1050-0x826),mxGetPr(z3832b85a32)[(0x1392+2680-0x1e0a)]);ssSetOffsetTime(S,(0x1cf+7123-0x1da2),0.0);}}static void sg_ModelLoad(SimStruct*S){
#ifndef MATLAB_MEX_FILE
volatile z84da6f474e*zf2ea15f185;void*bar2ptr;int moduleId=(int)mxGetScalar(ze13f49a01f);char*boardName=io3xxGetBoardNameSgLib(moduleId);int z3e423c83e6=(int)mxGetPr(za9d8fb6bcf)[(0x13a+8146-0x210c)]-(0xdc8+2548-0x17bb);int ze0bc7e48d0=(int)(SG_BLOCK_TYPE_VRS);z524b6b92ed*zbfee7303f3=(z524b6b92ed*)calloc((0xf6b+5296-0x241a),sizeof(z524b6b92ed));if(zbfee7303f3==NULL){sprintf(msg,"\x25\x73\x20\x56\x52\x53\x20\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x43\x6f\x75\x6c\x64\x20\x6e\x6f\x74\x20\x61\x6c\x6c\x6f\x63\x61\x74\x65\x20\x62\x6c\x6f\x63\x6b\x20\x64\x61\x74\x61\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}sg_fpga_io3xx_block_register((uint32_t)moduleId,(uint32_t)ze0bc7e48d0,(uint32_t)z3e423c83e6,(void*)zbfee7303f3);if(!io3xxGetAddressSgLib((int32_t)moduleId,SG_FPGA_IO3XX_BAR2)){sg_fpga_io3xx_block_unregister((uint32_t)moduleId,(uint32_t)ze0bc7e48d0,(uint32_t)z3e423c83e6);free(zbfee7303f3);ssSetErrorStatus(S,pSgErrorStr);return;}bar2ptr=io3xxGetAddressSgLib((int32_t)moduleId,SG_FPGA_IO3XX_BAR2);uint32_t zf7ccd17be8=(0x1de7+2049-0x25e8);if(sg_fpga_io3xx_getCmBaseAddress(moduleId,VRS_BASE,&zf7ccd17be8)){sg_fpga_io3xx_block_unregister((uint32_t)moduleId,(uint32_t)ze0bc7e48d0,(uint32_t)z3e423c83e6);free(zbfee7303f3);ssSetErrorStatus(S,msg);return;}zbfee7303f3->zf2ea15f185=(z84da6f474e*)((uintptr_t)bar2ptr+zf7ccd17be8);zf2ea15f185=zbfee7303f3->zf2ea15f185;SG_PRINTF(INFO,"\x56\x52\x53\x3a\x20\x43\x6f\x64\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x76\x65\x72\x73\x69\x6f\x6e\x3a\x20\x30\x78\x25\x78" "\n",zf2ea15f185->version);zbfee7303f3->z24a76e5f56[z3e423c83e6]=(0xe78+280-0xf90);zbfee7303f3->ze679452aeb[z3e423c83e6]=(0x2f5+878-0x663);if((uint32_t)mxGetPr(za10893a465)[(0x26b+6445-0x1b98)]!=(0xddf+3050-0x19c9)){zbfee7303f3->z24a76e5f56[z3e423c83e6]=(0xb0d+6613-0x24e0);if((uint32_t)mxGetPr(zdd9dec61b1)[(0x194+682-0x43e)]!=(0xba5+6822-0x264b)){zbfee7303f3->ze679452aeb[z3e423c83e6]=(0x960+6267-0x21d8);}}else if((uint32_t)mxGetPr(zdd9dec61b1)[(0x3a8+8876-0x2654)]!=(0x435+5023-0x17d4)){zbfee7303f3->ze679452aeb[z3e423c83e6]=(0x893+4412-0x19cd);}if(sg_isFirstModelLoad()){if(sg_fpga_io3xx_checkCodeModuleVersion(zf2ea15f185->version,z5bbcf8be2c,moduleId)){sg_fpga_io3xx_block_unregister((uint32_t)moduleId,(uint32_t)ze0bc7e48d0,(uint32_t)z3e423c83e6);free(zbfee7303f3);sprintf(msg,"\x25\x73\x20\x77\x72\x6f\x6e\x67\x20\x76\x65\x72\x73\x69\x6f\x6e\x20\x6f\x66\x20\x56\x52\x53\x20\x63\x6f\x64\x65\x20\x6d\x6f\x64\x75\x6c\x65\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}}
#else
(void)S;
#endif
}static void sg_ModelStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
volatile z84da6f474e*zf2ea15f185;int moduleId=(int)mxGetScalar(ze13f49a01f);int z3e423c83e6=(int)mxGetPr(za9d8fb6bcf)[(0x8a2+3010-0x1464)]-(0x22d+7111-0x1df3);int ze0bc7e48d0=(int)(SG_BLOCK_TYPE_VRS);sg_block_info*z05264739a1=sg_fpga_io3xx_block_get((uint32_t)moduleId,(uint32_t)ze0bc7e48d0,(uint32_t)z3e423c83e6);z524b6b92ed*zbfee7303f3=(z524b6b92ed*)z05264739a1->custom_data;if(z05264739a1==NULL||z05264739a1->custom_data==NULL){sprintf(msg,"\x56\x52\x53\x20\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x42\x6c\x6f\x63\x6b\x20\x64\x61\x74\x61\x20\x6c\x6f\x6f\x6b\x75\x70\x20\x75\x6e\x73\x75\x63\x63\x65\x73\x73\x66\x75\x6c\x21\x20\x6d\x6f\x64\x75\x6c\x65\x49\x64\x3d\x25\x64\x20\x62\x6c\x6f\x63\x6b\x54\x79\x70\x65\x3d\x25\x64\x20\x62\x6c\x6f\x63\x6b\x49\x64\x3d\x25\x64" "\n",moduleId,ze0bc7e48d0,z3e423c83e6);ssSetErrorStatus(S,msg);return;}zf2ea15f185=zbfee7303f3->zf2ea15f185;uint32_t channel=(uint32_t)z3e423c83e6;uint32_t zc743909e80=(0x01U<<channel);zbfee7303f3->z87a9298581=(real_T)mxGetPr(z0760155ccd)[(0x1af+1374-0x70d)];zbfee7303f3->z03cd415bce=(uint32_t)mxGetPr(zb8a484fa5c)[(0xf08+3637-0x1d3d)];if(zbfee7303f3->z24a76e5f56[z3e423c83e6]){zf2ea15f185->z8302df4cf5[z3e423c83e6]=0U;zf2ea15f185->zd4b9d383d6[z3e423c83e6]=(uint32_t)ssGetInputPortSignal(S,zbfee7303f3->z24a76e5f56[z3e423c83e6]);}else{zf2ea15f185->z8302df4cf5[z3e423c83e6]=1U;zf2ea15f185->zd4b9d383d6[z3e423c83e6]=(uint32_t)ssGetInputPortSignal(S,zbfee7303f3->z24a76e5f56[z3e423c83e6]);}if(zbfee7303f3->ze679452aeb[z3e423c83e6]){real_T*z73435dd536=(real_T*)ssGetInputPortSignal(S,zbfee7303f3->ze679452aeb[z3e423c83e6]);zf2ea15f185->offset[z3e423c83e6]=z019dbba4ef(*z73435dd536);}else{zf2ea15f185->offset[z3e423c83e6]=z019dbba4ef(mxGetPr(zf332288c20)[(0xf31+3033-0x1b0a)]);}zf2ea15f185->z172df257bb|=zc743909e80;if(~(uint32_t)mxGetPr(zaaf55eaed6)[(0x8f0+2948-0x1474)]){zf2ea15f185->z172df257bb&=~zc743909e80;}zf2ea15f185->zb46289d48f[channel]=z019dbba4ef((real_T)mxGetPr(zee2316ae4d)[(0x1151+437-0x1306)]);for(uint32_t i=(0x477+5257-0x1900);i<z703d77db05;i++){zf2ea15f185->z4a29242ba3[channel]=i;zf2ea15f185->z8e28bead35[channel]=0x80000000U|(0xFFFFU&(uint32_t)((int32_t)mxGetPr(z38f57ee110)[i]));}zf2ea15f185->z8e28bead35[channel]=0U;zf2ea15f185->z4a29242ba3[channel]=0U;double zded09faf59=mxGetScalar(z62e46f52ac);zf2ea15f185->z91da63235a[channel]=(uint32_t)((int32_t)zded09faf59)-(0xce5+6310-0x258a);zf2ea15f185->enable|=zc743909e80;
#else
(void)S;
#endif
}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
volatile z84da6f474e*zf2ea15f185;int moduleId=(int)mxGetScalar(ze13f49a01f);int z3e423c83e6=(int)mxGetPr(za9d8fb6bcf)[(0x137b+3871-0x229a)]-(0x6d2+4522-0x187b);int ze0bc7e48d0=(int)(SG_BLOCK_TYPE_VRS);sg_block_info*z05264739a1=sg_fpga_io3xx_block_get((uint32_t)moduleId,(uint32_t)ze0bc7e48d0,(uint32_t)z3e423c83e6);z524b6b92ed*zbfee7303f3=(z524b6b92ed*)z05264739a1->custom_data;if(z05264739a1==NULL||z05264739a1->custom_data==NULL){sprintf(msg,"\x56\x52\x53\x20\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x42\x6c\x6f\x63\x6b\x20\x64\x61\x74\x61\x20\x6c\x6f\x6f\x6b\x75\x70\x20\x75\x6e\x73\x75\x63\x63\x65\x73\x73\x66\x75\x6c\x21\x20\x6d\x6f\x64\x75\x6c\x65\x49\x64\x3d\x25\x64\x20\x62\x6c\x6f\x63\x6b\x54\x79\x70\x65\x3d\x25\x64\x20\x62\x6c\x6f\x63\x6b\x49\x64\x3d\x25\x64" "\n",moduleId,ze0bc7e48d0,z3e423c83e6);ssSetErrorStatus(S,msg);return;}zf2ea15f185=zbfee7303f3->zf2ea15f185;uint32_t channel=(uint32_t)z3e423c83e6;uint32_t zc743909e80=(0x01U<<channel);uint32_t z40a5b4a9e6=0U;real_T z87a9298581=zbfee7303f3->z87a9298581;real_T*z0754dd67cc=(real_T*)ssGetInputPortSignal(S,z40a5b4a9e6);real_T zf8a793f028=z0754dd67cc[(0x933+2625-0x1374)]*z87a9298581/2.0;if(zf8a793f028>256.0){zf8a793f028=256.0;}else if(zf8a793f028<-256.0){zf8a793f028=-256.0;}zf2ea15f185->z0754dd67cc[channel]=(uint32_t)((int32_t)(zf8a793f028*z62917fff17));z40a5b4a9e6++;real_T*zb640018cea=(real_T*)ssGetInputPortSignal(S,z40a5b4a9e6);real_T z3269ea9aaa=zb640018cea[(0xd3b+628-0xfaf)]*z87a9298581;if(z3269ea9aaa>1.0){z3269ea9aaa=1.0;}else if(z3269ea9aaa<-1.0){z3269ea9aaa=-1.0;}zf2ea15f185->zb640018cea[channel]=(uint32_t)((int32_t)(z3269ea9aaa*z62917fff17));if(zbfee7303f3->z24a76e5f56[channel]){real_T*z75eddf9707=ssGetInputPortSignal(S,zbfee7303f3->z24a76e5f56[channel]);zf2ea15f185->zd4b9d383d6[channel]=(uint32_t)((int32_t)z75eddf9707[(0x1c4a+2156-0x24b6)]);z40a5b4a9e6++;}if(zbfee7303f3->ze679452aeb[channel]){real_T*offset=(real_T*)ssGetInputPortSignal(S,zbfee7303f3->ze679452aeb[channel]);zf2ea15f185->offset[channel]=z019dbba4ef(offset[(0xa4c+3283-0x171f)]);z40a5b4a9e6++;}if(zbfee7303f3->z03cd415bce){real_T*out=(real_T*)ssGetOutputPortSignal(S,(0xdfa+4699-0x2055));out[(0x13eb+3521-0x21ac)]=(real_T)zf2ea15f185->position[channel]/zae4028a32c*z70b7fa4779;}
#else
(void)S;
#endif
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE
volatile z84da6f474e*zf2ea15f185;int moduleId=(int)mxGetScalar(ze13f49a01f);int z3e423c83e6=(int)mxGetPr(za9d8fb6bcf)[(0x1c0a+100-0x1c6e)]-(0x6ac+1611-0xcf6);int ze0bc7e48d0=(int)(SG_BLOCK_TYPE_VRS);sg_block_info*z05264739a1=sg_fpga_io3xx_block_get((uint32_t)moduleId,(uint32_t)ze0bc7e48d0,(uint32_t)z3e423c83e6);if(z05264739a1==NULL||z05264739a1->custom_data==NULL){return;}z524b6b92ed*zbfee7303f3=(z524b6b92ed*)z05264739a1->custom_data;zf2ea15f185=zbfee7303f3->zf2ea15f185;uint32_t channel=(uint32_t)z3e423c83e6;uint32_t zc743909e80=(0x01U<<channel);zf2ea15f185->enable&=~zc743909e80;zf2ea15f185->z172df257bb&=~zc743909e80;sg_fpga_io3xx_block_unregister((uint32_t)moduleId,(uint32_t)ze0bc7e48d0,(uint32_t)z3e423c83e6);free(zbfee7303f3);
#else
(void)S;
#endif
}
#include "sg_sfcn_glue.h"   

