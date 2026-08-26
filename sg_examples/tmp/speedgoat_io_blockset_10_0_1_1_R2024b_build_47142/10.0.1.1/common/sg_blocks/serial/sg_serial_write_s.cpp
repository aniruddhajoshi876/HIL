// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL (0x16f9+1140-0x1b6b)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_serial_write_s
#include "sg_serial.h"
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#else
#include "sg_common.h"
#include "sg_module_registry.h"
#include "sg_module_types.h"
#include "sg_printf.h"
static const int z0e14cce82f[]={SG_MODULE_TYPE_IO503,SG_MODULE_TYPE_IO504,SG_MODULE_TYPE_IO505,SG_MODULE_TYPE_IO581};
#endif
#define SG_EARLY_INIT   
#include "sg_callback.h"
#define ze13f49a01f           ssGetSFcnParam(S, (0x1395+4020-0x2349))
#define za9d8fb6bcf             ssGetSFcnParam(S, (0x180f+1812-0x1f22))
#define z39cbd24432         ssGetSFcnParam(S, (0x12ea+5088-0x26c8))
#define z0f85e6ff7f       ssGetSFcnParam(S, (0x401+2063-0xc0d))
#define z4848d060ef           ssGetSFcnParam(S, (0x163d+1070-0x1a67))
#define z702a26a5e9                ssGetSFcnParam(S, (0x16b7+3027-0x2285))
#define z3ec81e741b         ssGetSFcnParam(S, (0x1191+3300-0x1e6f))
#define zbf4c83e854           ssGetSFcnParam(S, (0xaab+1431-0x103b))
#define z7346ef245e    ssGetSFcnParam(S, (0x1eea+1778-0x25d4))
#define zf949290bb2  ssGetSFcnParam(S, (0x1314+651-0x1596))
#define zb14c7a24bf      ssGetSFcnParam(S, (0xa7b+6370-0x2353))
#define zdfb5404315       ssGetSFcnParam(S, (0x16f0+1400-0x1c5d))
#define zdf24515981                           ((0x338+5621-0x1921))
#define z2e6483d505 ((0x445+2507-0xe10))
#define zc5ce4cb81a ((0xc7f+681-0xf28))
#define z2b17e2ee3b ((0x1898+2207-0x2137))
static char_T msg[(0x1d3a+2173-0x24b7)];static void mdlInitializeSizes(SimStruct*S){int i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0xde3+409-0xf7c));ssSetNumDiscStates(S,(0xe9+9488-0x25f9));ssSetNumOutputPorts(S,(0x1430+3365-0x2155));if((int)mxGetPr(z0f85e6ff7f)[(0x1baa+1412-0x212e)]){ssSetNumInputPorts(S,(0x10da+3609-0x1ef2));ssSetInputPortRequiredContiguous(S,(0x297+157-0x334),(0x840+4688-0x1a8f));if(((int)mxGetPr(z4848d060ef)[(0x962+1104-0xdb2)]==(0x10ea+98-0x1147))||((int)mxGetPr(z4848d060ef)[(0x1e1d+2174-0x269b)]==(0x21ba+842-0x24fe))){ssSetInputPortWidth(S,(0x8c4+6835-0x2377),(int)mxGetPr(zbf4c83e854)[(0x23d+1274-0x737)]);}else{ssSetInputPortWidth(S,(0x223a+315-0x2375),(int)mxGetPr(zbf4c83e854)[(0x1d22+1075-0x2155)]+(0x1863+1282-0x1d64));}switch((int)mxGetPr(z4848d060ef)[(0x101f+2901-0x1b74)]){case(0x719+6732-0x2164):ssSetInputPortDataType(S,(0xb1a+5847-0x21f1),SS_INT32);break;case(0x176f+3427-0x24d0):ssSetInputPortDataType(S,(0x154b+1210-0x1a05),SS_UINT32);break;case(0x108f+3958-0x2002):ssSetInputPortDataType(S,(0x1de5+1041-0x21f6),SS_INT16);break;case(0x992+6867-0x2461):ssSetInputPortDataType(S,(0x980+5089-0x1d61),SS_UINT16);break;case(0x154a+2940-0x20c1):ssSetInputPortDataType(S,(0x874+6171-0x208f),SS_INT8);break;case(0x1865+1164-0x1ceb):ssSetInputPortDataType(S,(0xc5f+1032-0x1067),SS_UINT8);break;default:ssSetErrorStatus(S,"\x55\x6e\x6b\x6e\x6f\x77\x6e\x20\x64\x61\x74\x61\x20\x74\x79\x70\x65" "\n");return;}ssSetInputPortDirectFeedThrough(S,(0x1263+47-0x1292),(0x6f1+3439-0x145f));}else{ssSetNumInputPorts(S,(0x1d17+1887-0x2474));ssSetInputPortRequiredContiguous(S,(0x11da+2128-0x1a2a),(0x8c9+5600-0x1ea8));ssSetInputPortWidth(S,(0x1ac0+812-0x1dec),(0x36+5423-0x1564));ssSetInputPortDataType(S,(0x64a+1139-0xabd),SS_UINT32);ssSetInputPortDirectFeedThrough(S,(0x652+6430-0x1f70),(0x735+4800-0x19f4));ssSetInputPortRequiredContiguous(S,(0xd99+2295-0x168f),(0x861+7291-0x24db));ssSetInputPortWidth(S,(0x2a4+3485-0x1040),(int)mxGetPr(zbf4c83e854)[(0x18ab+871-0x1c12)]);ssSetInputPortDataType(S,(0xd7f+1750-0x1454),SS_UINT8);ssSetInputPortDirectFeedThrough(S,(0xf31+1048-0x1348),(0x130+527-0x33e));}ssSetNumSampleTimes(S,(0x178a+2901-0x22de));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0xaa1+6238-0x22ff));ssSetNumNonsampledZCs(S,(0xbb5+4456-0x1d1d));for(i=(0x3c3+3528-0x118b);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x369+6528-0x1ce9));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z39cbd24432)[(0xc89+57-0xcc2)]==-1.0){ssSetSampleTime(S,(0x1a40+2071-0x2257),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0xb2b+2139-0x1386),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x1dbd+280-0x1ed5),mxGetPr(z39cbd24432)[(0xcd5+2644-0x1729)]);ssSetOffsetTime(S,(0x77b+6504-0x20e3),0.0);}}
#ifndef MATLAB_MEX_FILE
static void sg_ModelLoad(SimStruct*S){char zc43186f5f0[MAX_LENGTH_SERIAL_DEVICE_NAME];uint8_t channel;sg_mod_info*mod_info=nullptr;z403b902beb*zae10e3f17f=nullptr;sg_block_info*z1e47b02c71=nullptr;z2c2985fa73*z7c9787d630=nullptr;
#ifdef z5c227f1beb
char z03266361d7[(0x4c8+3831-0x1340)];
#endif
channel=(uint8_t)mxGetPr(za9d8fb6bcf)[(0x1075+1325-0x15a2)]-(0x1050+4978-0x23c1);uint32_t boardType=(int)mxGetPr(z3ec81e741b)[(0xa6d+4444-0x1bc9)]-(0x613+1262-0xb00);int za0d38ae598=(int)mxGetPr(ze13f49a01f)[(0x4b1+1118-0x90f)];mod_info=(sg_mod_info*)sg_module_get_single(z0e14cce82f[boardType],za0d38ae598);zae10e3f17f=(z403b902beb*)mod_info->custom_data;if(!zae10e3f17f){sprintf(msg,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x69\x6e\x20\x57\x72\x69\x74\x65\x20\x4d\x6f\x64\x65\x6c\x53\x74\x61\x72\x74" "\n",DEVNAME[boardType],za0d38ae598);ssSetErrorStatus(S,msg);return;}z1e47b02c71=(sg_block_info*)sg_block_register(mod_info,z7210713648,channel);if(!z1e47b02c71){sprintf(msg,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x63\x72\x65\x61\x74\x65\x20\x77\x72\x69\x74\x65\x20\x62\x6c\x6f\x63\x6b\x20\x69\x6e\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x69\x6e\x20\x57\x72\x69\x74\x65\x20\x4d\x6f\x64\x65\x6c\x4c\x6f\x61\x64" "\n",DEVNAME[boardType],za0d38ae598);ssSetErrorStatus(S,msg);return;}z7c9787d630=(z2c2985fa73*)malloc(sizeof(z2c2985fa73));z1e47b02c71->custom_data=(void*)z7c9787d630;
#if defined(__QNX__)
z7c9787d630->zcb322daed6=zae10e3f17f->zb003ac7e25+channel;
#elif defined(__linux__)
z7c9787d630->zcb322daed6=zae10e3f17f->z4e4c7f816f[channel];
#endif 
z7c9787d630->enabled=zae10e3f17f->enabled[channel];if(z7c9787d630->enabled){memset(zc43186f5f0,(0x1405+4247-0x249c),sizeof(zc43186f5f0));
#if defined(__QNX__)
sprintf(zc43186f5f0,"\x2f\x64\x65\x76\x2f\x73\x65\x72\x25\x64",z7c9787d630->zcb322daed6);
#elif defined(__linux__)
sprintf(zc43186f5f0,"\x2f\x64\x65\x76\x2f\x74\x74\x79\x53\x54\x44\x52\x56\x30\x30\x32\x5f\x25\x64",z7c9787d630->zcb322daed6);
#endif 
z7c9787d630->fd=open(zc43186f5f0,O_RDWR|O_NONBLOCK);if(z7c9787d630->fd==-(0x18bc+1519-0x1eaa)){sprintf(msg,"\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x6f\x70\x65\x6e\x20\x73\x65\x72\x69\x61\x6c\x20\x25\x73\x20\x28\x63\x68\x61\x6e\x6e\x65\x6c\x20\x25\x75\x29" "\n",zc43186f5f0,channel);ssSetErrorStatus(S,msg);return;}z7c9787d630->buffer=(uint8_t*)calloc((size_t)mxGetPr(zbf4c83e854)[(0x9f4+6757-0x2459)],sizeof(uint8_t));
#if defined(__QNX__)
SG_PRINTF(DEBUG,"\x5b\x63\x68\x61\x6e\x6e\x65\x6c\x20\x25\x64\x5d\x20\x77\x72\x69\x74\x65\x3a\x20\x4d\x6f\x64\x65\x6c\x4c\x6f\x61\x64\x20\x28\x66\x64\x20\x3d\x20\x25\x64\x2c\x20\x64\x65\x76\x3d\x30\x78\x25\x6c\x78\x2c\x20\x62\x75\x66\x66\x65\x72\x20\x30\x78\x25\x6c\x78\x29\x20\x66\x6f\x72\x20\x2f\x64\x65\x76\x2f\x73\x65\x72\x25\x64" "\n",channel,z7c9787d630->fd,zae10e3f17f,z7c9787d630->buffer,z7c9787d630->zcb322daed6);
#elif defined(__linux__)
SG_PRINTF(DEBUG,"\x5b\x63\x68\x61\x6e\x6e\x65\x6c\x20\x25\x64\x5d\x20\x77\x72\x69\x74\x65\x3a\x20\x4d\x6f\x64\x65\x6c\x4c\x6f\x61\x64\x20\x28\x66\x64\x20\x3d\x20\x25\x64\x2c\x20\x64\x65\x76\x3d\x30\x78\x25\x6c\x78\x2c\x20\x62\x75\x66\x66\x65\x72\x20\x30\x78\x25\x6c\x78\x29\x20\x66\x6f\x72\x20\x2f\x64\x65\x76\x2f\x74\x74\x79\x53\x54\x44\x52\x56\x30\x30\x32\x5f\x25\x64" "\n",channel,z7c9787d630->fd,zae10e3f17f,z7c9787d630->buffer,z7c9787d630->zcb322daed6);
#endif 
if((int)mxGetPr(z7346ef245e)[(0x1ca1+1013-0x2096)]){zae10e3f17f->z5dd2589b61[channel]=true;}}else{
#if defined(__QNX__)
SG_PRINTF(DEBUG,"\x5b\x63\x68\x61\x6e\x6e\x65\x6c\x20\x25\x64\x5d\x20\x77\x72\x69\x74\x65\x3a\x20\x4d\x6f\x64\x65\x6c\x4c\x6f\x61\x64\x20\x3a\x20\x64\x69\x73\x61\x62\x6c\x65\x64\x20\x2f\x64\x65\x76\x2f\x73\x65\x72\x25\x64" "\n",channel,z7c9787d630->zcb322daed6);
#elif defined(__linux__)
SG_PRINTF(DEBUG,"\x5b\x63\x68\x61\x6e\x6e\x65\x6c\x20\x25\x64\x5d\x20\x77\x72\x69\x74\x65\x3a\x20\x4d\x6f\x64\x65\x6c\x4c\x6f\x61\x64\x20\x3a\x20\x64\x69\x73\x61\x62\x6c\x65\x64\x20\x2f\x64\x65\x76\x2f\x74\x74\x79\x53\x54\x44\x52\x56\x30\x30\x32\x5f\x25\x64" "\n",channel,z7c9787d630->zcb322daed6);
#endif 
}
#ifdef z5c227f1beb
memset(z03266361d7,(0xe65+522-0x106f),sizeof(z03266361d7));sprintf(z03266361d7,"\x2f\x68\x6f\x6d\x65\x2f\x73\x6c\x72\x74\x2f\x49\x4f\x25\x64\x5f\x49\x44\x25\x64\x5f\x43\x48\x25\x64\x5f\x6f\x75\x74\x2e\x74\x78\x74",zac61c2c0e1,zae10e3f17f->moduleId,channel);z7c9787d630->z8196b021ae=fopen(z03266361d7,"\x77");if(z7c9787d630->z8196b021ae!=NULL){SG_PRINTF(INFO,"\x5b\x63\x68\x61\x6e\x6e\x65\x6c\x20\x25\x64\x5d\x20\x57\x72\x69\x74\x65\x20\x3a\x20\x66\x69\x6c\x65\x20\x63\x72\x65\x61\x74\x65\x64\x20\x25\x73" "\n",channel,z03266361d7);}else{SG_PRINTF(INFO,"\x5b\x63\x68\x61\x6e\x6e\x65\x6c\x20\x25\x64\x5d\x20\x57\x72\x69\x74\x65\x20\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x63\x72\x65\x61\x74\x65\x20\x66\x69\x6c\x65\x20\x25\x73\x20\x28\x65\x72\x72\x20\x25\x64\x29" "\n",channel,z03266361d7,errno);}z7c9787d630->ze667de5014=(0x1223+4997-0x25a8);
#endif
}static void sg_ModelStart(SimStruct*S){}static void sg_ModelStep(SimStruct*S){unsigned int i;uint32_t z7b5c8c9301=(0xc9b+3858-0x1bad);uint8_t*z24ccd0f8f9;uint16_t*z00570e9d86;uint32_t*zec9a534d9f;uint32_t channel=(uint8_t)mxGetPr(za9d8fb6bcf)[(0x448+5765-0x1acd)]-(0x4aa+6440-0x1dd1);sg_mod_info*mod_info=nullptr;sg_block_info*z1e47b02c71=nullptr;z2c2985fa73*z7c9787d630=nullptr;uint32_t boardType=(int)mxGetPr(z3ec81e741b)[(0x3b4+527-0x5c3)]-(0x215d+1066-0x2586);int za0d38ae598=(int)mxGetPr(ze13f49a01f)[(0x2239+860-0x2595)];mod_info=(sg_mod_info*)sg_module_get_single(z0e14cce82f[boardType],za0d38ae598);z1e47b02c71=(sg_block_info*)sg_block_get(mod_info,z7210713648,channel);if(!z1e47b02c71){sprintf(msg,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x77\x72\x69\x74\x65\x20\x62\x6c\x6f\x63\x6b\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x69\x6e\x20\x57\x72\x69\x74\x65\x20\x4d\x6f\x64\x65\x6c\x53\x74\x61\x72\x74" "\n",DEVNAME[boardType],za0d38ae598);ssSetErrorStatus(S,msg);return;}z7c9787d630=(z2c2985fa73*)z1e47b02c71->custom_data;if(z7c9787d630->enabled==zf7e8aabb5e){SG_PRINTF(TRACE,"\x5b\x63\x68\x61\x6e\x6e\x65\x6c\x20\x25\x64\x5d\x20\x57\x72\x69\x74\x65\x20\x3a\x20\x4d\x6f\x64\x65\x6c\x53\x74\x65\x70\x20\x3a\x20\x64\x69\x73\x61\x62\x6c\x65\x64" "\n",channel);return;}if((int)mxGetPr(z0f85e6ff7f)[(0x166f+4234-0x26f9)]){switch((int)mxGetPr(z4848d060ef)[(0xddb+5328-0x22ab)]){case(0x1736+2361-0x206e):case(0x6bb+1593-0xcf2):zec9a534d9f=(uint32_t*)ssGetInputPortSignal(S,(0xb47+278-0xc5d));z7b5c8c9301=(uint32_t)zec9a534d9f[(0x197+1974-0x94d)];for(i=(0x10a4+3295-0x1d83);i<z7b5c8c9301;i++){z7c9787d630->buffer[i]=zec9a534d9f[i+(0x1cfa+152-0x1d91)]&(0x1953+3062-0x244a);}break;case(0x2487+150-0x251a):case(0x59b+3060-0x118b):z00570e9d86=(uint16_t*)ssGetInputPortSignal(S,(0x283+606-0x4e1));z7b5c8c9301=(uint32_t)z00570e9d86[(0x369+456-0x531)];for(i=(0x1350+2444-0x1cdc);i<z7b5c8c9301;i++){z7c9787d630->buffer[i]=z00570e9d86[i+(0x3d3+8496-0x2502)]&(0x136+7483-0x1d72);}break;case(0x3a+508-0x231):case(0xfb1+1564-0x15c7):z24ccd0f8f9=(uint8_t*)ssGetInputPortSignal(S,(0x1359+686-0x1607));for(i=(0xe81+4505-0x201a);i<(unsigned int)mxGetPr(zbf4c83e854)[(0x1b6f+215-0x1c46)];i++){z7c9787d630->buffer[i]=z24ccd0f8f9[i]&(0xeff+551-0x1027);if(z24ccd0f8f9[i]==(0x1687+876-0x19f3)){z7b5c8c9301=i;break;}}break;default:ssSetErrorStatus(S,"\x55\x6e\x6b\x6e\x6f\x77\x6e\x20\x64\x61\x74\x61\x20\x74\x79\x70\x65" "\n");return;}}else{z7b5c8c9301=*(uint32_t*)ssGetInputPortSignal(S,(0x19ea+2639-0x2439));z24ccd0f8f9=(uint8_t*)ssGetInputPortSignal(S,(0x108d+2432-0x1a0c));for(i=(0x1b67+1271-0x205e);i<z7b5c8c9301;i++){z7c9787d630->buffer[i]=z24ccd0f8f9[i]&(0x1a18+609-0x1b7a);}}unsigned int nBytes=write(z7c9787d630->fd,z7c9787d630->buffer,z7b5c8c9301);if(nBytes>(0x3f5+4607-0x15f4)){
#if defined(__QNX__)
SG_PRINTF(TRACE,"\x5b\x63\x68\x61\x6e\x6e\x65\x6c\x20\x25\x64\x5d\x20\x57\x72\x69\x74\x74\x65\x6e\x20\x25\x64\x20\x62\x79\x74\x65\x73\x20\x6f\x75\x74\x20\x6f\x66\x20\x25\x64\x20\x74\x6f\x20\x2f\x64\x65\x76\x2f\x73\x65\x72\x25\x64" "\n",channel,nBytes,z7b5c8c9301,z7c9787d630->zcb322daed6);
#elif defined(__linux__)
SG_PRINTF(TRACE,"\x5b\x63\x68\x61\x6e\x6e\x65\x6c\x20\x25\x64\x5d\x20\x57\x72\x69\x74\x74\x65\x6e\x20\x25\x64\x20\x62\x79\x74\x65\x73\x20\x6f\x75\x74\x20\x6f\x66\x20\x25\x64\x20\x74\x6f\x20\x2f\x64\x65\x76\x2f\x74\x74\x79\x53\x54\x44\x52\x56\x30\x30\x32\x5f\x25\x64" "\n",channel,nBytes,z7b5c8c9301,z7c9787d630->zcb322daed6);
#endif 
for(i=(0xa6b+5037-0x1e18);i<nBytes;i++){SG_PRINTF(TRACE,"\x5b\x63\x68\x61\x6e\x6e\x65\x6c\x20\x25\x64\x5d\x20\x54\x78\x5b\x25\x64\x5d\x20\x3a\x20\x30\x78\x25\x78" "\n",channel,i,z7c9787d630->buffer[i]);}
#ifdef z5c227f1beb
z7c9787d630->ze667de5014+=nBytes;if(z7c9787d630->z8196b021ae!=NULL){fprintf(z7c9787d630->z8196b021ae,"\x30\x78\x25\x30\x32\x78\x20\x3a\x20",nBytes);for(i=(0xf8a+202-0x1054);i<nBytes;i++){fprintf(z7c9787d630->z8196b021ae,"\x30\x78\x25\x30\x32\x78\x20",buffer[i]);}fprintf(z7c9787d630->z8196b021ae,"\n");}
#endif
}}static void sg_ModelStop(SimStruct*S){uint8_t channel=(uint8_t)mxGetPr(za9d8fb6bcf)[(0x8a6+5399-0x1dbd)]-(0x16b9+2803-0x21ab);unsigned int nBytes;uint16_t za4f80989e2;int ret=(0x1a79+803-0x1d9c);sg_mod_info*mod_info=nullptr;sg_block_info*z1e47b02c71=nullptr;z2c2985fa73*z7c9787d630=nullptr;uint32_t boardType=(int)mxGetPr(z3ec81e741b)[(0x3ea+3345-0x10fb)]-(0x8dc+6073-0x2094);int za0d38ae598=(int)mxGetPr(ze13f49a01f)[(0x1779+2336-0x2099)];mod_info=(sg_mod_info*)sg_module_get_single(z0e14cce82f[boardType],za0d38ae598);z1e47b02c71=(sg_block_info*)sg_block_get(mod_info,z7210713648,channel);if(!z1e47b02c71){sprintf(msg,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x77\x72\x69\x74\x65\x20\x62\x6c\x6f\x63\x6b\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x69\x6e\x20\x57\x72\x69\x74\x65\x20\x4d\x6f\x64\x65\x6c\x53\x74\x61\x72\x74" "\n",DEVNAME[boardType],za0d38ae598);ssSetErrorStatus(S,msg);return;}z7c9787d630=(z2c2985fa73*)z1e47b02c71->custom_data;if(z7c9787d630->enabled){
#if defined(__QNX__)
#elif defined(__linux__)
#endif 
SG_PRINTF(DEBUG,"\x5b\x63\x68\x61\x6e\x6e\x65\x6c\x20\x25\x64\x5d\x20\x77\x72\x69\x74\x65\x3a\x20\x4d\x6f\x64\x65\x6c\x53\x74\x6f\x70\x20\x28\x66\x64\x20\x3d\x20\x25\x64\x2c\x20\x62\x75\x66\x66\x65\x72\x20\x30\x78\x25\x6c\x78\x29\x20\x66\x6f\x72\x20\x2f\x64\x65\x76\x2f\x73\x65\x72\x25\x64" "\n",channel,z7c9787d630->fd,z7c9787d630->buffer,z7c9787d630->zcb322daed6);
#ifdef z5c227f1beb
#if defined(__QNX__)
SG_PRINTF(INFO,"\x5b\x63\x68\x61\x6e\x6e\x65\x6c\x20\x25\x64\x5d\x20\x77\x72\x69\x74\x65\x3a\x20\x43\x6f\x75\x6e\x74\x65\x72\x20\x25\x64\x20\x66\x6f\x72\x20\x2f\x64\x65\x76\x2f\x73\x65\x72\x25\x64" "\n",channel,z085e5fb475,zcb322daed6);
#elif defined(__linux__)
SG_PRINTF(INFO,"\x5b\x63\x68\x61\x6e\x6e\x65\x6c\x20\x25\x64\x5d\x20\x77\x72\x69\x74\x65\x3a\x20\x43\x6f\x75\x6e\x74\x65\x72\x20\x25\x64\x20\x66\x6f\x72\x20\x2f\x64\x65\x76\x2f\x74\x74\x79\x53\x54\x44\x52\x56\x30\x30\x32\x5f\x25\x64" "\n",channel,z085e5fb475,zcb322daed6);
#endif 
if(z7c9787d630->z8196b021ae!=NULL){fclose(z7c9787d630->z8196b021ae);}
#endif
if((int)mxGetPr(z7346ef245e)[(0x507+611-0x76a)]){switch((int)mxGetPr(zf949290bb2)[(0x1e57+2203-0x26f2)]){case(0x223+7205-0x1e47):SG_PRINTF(DEBUG,"\x25\x64\x20\x49\x44\x3a\x20\x25\x64\x20\x5b\x63\x68\x61\x6e\x6e\x65\x6c\x20\x25\x64\x5d\x20\x4d\x64\x6c\x53\x74\x6f\x70\x20\x4d\x73\x67\x20\x64\x69\x72\x65\x63\x74\x6c\x79\x20\x69\x6e\x74\x6f\x20\x46\x49\x46\x4f" "\n",z0e14cce82f[boardType],za0d38ae598,(channel+(0xa47+4705-0x1ca7)));break;case(0x143f+3538-0x220f):ret=zf7ad6ab803(z7c9787d630->zcb322daed6,z794372c9c9);SG_PRINTF(DEBUG,"\x25\x64\x20\x49\x44\x3a\x20\x25\x64\x20\x5b\x63\x68\x61\x6e\x6e\x65\x6c\x20\x25\x64\x5d\x20\x4d\x64\x6c\x53\x74\x6f\x70\x20\x4d\x73\x67\x20\x77\x61\x69\x74\x20\x66\x6f\x72\x20\x65\x6d\x70\x74\x79\x20\x46\x49\x46\x4f" "\n",z0e14cce82f[boardType],za0d38ae598,(channel+(0x8ea+6948-0x240d)));break;case(0x4d0+3237-0x1172):ret=zf7ad6ab803(z7c9787d630->zcb322daed6,z5acdb06588);SG_PRINTF(DEBUG,"\x25\x64\x20\x49\x44\x3a\x20\x25\x64\x20\x5b\x63\x68\x61\x6e\x6e\x65\x6c\x20\x25\x64\x5d\x20\x46\x6c\x75\x73\x68\x20\x46\x49\x46\x4f\x20\x62\x65\x66\x6f\x72\x65\x20\x4d\x64\x6c\x53\x74\x6f\x70\x20\x4d\x73\x67" "\n",z0e14cce82f[boardType],za0d38ae598,(channel+(0xce1+994-0x10c2)));break;default:break;}za4f80989e2=(int)mxGetPr(zb14c7a24bf)[(0x25d+827-0x598)];SG_PRINTF(DEBUG,"\x25\x64\x20\x49\x44\x3a\x20\x25\x64\x20\x5b\x63\x68\x61\x6e\x6e\x65\x6c\x20\x25\x64\x5d\x20\x73\x74\x6f\x70\x20\x6d\x73\x67\x20\x73\x69\x7a\x65\x20\x25\x64" "\n",z0e14cce82f[boardType],za0d38ae598,(channel+(0xcfb+6035-0x248d)),za4f80989e2);for(uint8_t i=(0x849+1938-0xfdb);i<za4f80989e2;i++){z7c9787d630->buffer[i]=(int)mxGetPr(zdfb5404315)[i]&(0xf62+501-0x1058);}nBytes=write(z7c9787d630->fd,z7c9787d630->buffer,za4f80989e2);if(nBytes>(0x1007+265-0x1110)){SG_PRINTF(INFO,"\x25\x64\x20\x49\x44\x3a\x20\x25\x64\x20\x5b\x63\x68\x61\x6e\x6e\x65\x6c\x20\x25\x64\x5d\x20\x57\x72\x69\x74\x74\x65\x6e\x20\x25\x64\x20\x62\x79\x74\x65\x73\x20\x6f\x75\x74\x20\x6f\x66\x20\x25\x64" "\n",z0e14cce82f[boardType],za0d38ae598,(channel+(0x158+8095-0x20f6)),nBytes,za4f80989e2);}}if(z7c9787d630->fd>(0x6e6+5987-0x1e49)){SG_PRINTF(DEBUG,"\x25\x64\x20\x5b\x63\x68\x61\x6e\x6e\x65\x6c\x20\x25\x64\x5d\x20\x77\x72\x69\x74\x65\x3a\x20\x63\x6c\x6f\x73\x65\x20\x66\x64\x20\x25\x64" "\n",(channel+(0xe8b+6055-0x2631)),z7c9787d630->fd);close(z7c9787d630->fd);}if(z7c9787d630->buffer!=nullptr){SG_PRINTF(DEBUG,"\x25\x64\x20\x5b\x63\x68\x61\x6e\x6e\x65\x6c\x20\x25\x64\x5d\x20\x77\x72\x69\x74\x65\x3a\x20\x66\x72\x65\x65\x20\x62\x75\x66\x66\x65\x72\x20\x25\x78" "\n",(channel+(0x906+4360-0x1a0d)),z7c9787d630->buffer);free(z7c9787d630->buffer);}}else{
#if defined(__QNX__)
SG_PRINTF(DEBUG,"\x5b\x63\x68\x61\x6e\x6e\x65\x6c\x20\x25\x64\x5d\x20\x77\x72\x69\x74\x65\x3a\x20\x4d\x6f\x64\x65\x6c\x53\x74\x6f\x70\x20\x28\x64\x69\x73\x61\x62\x6c\x65\x64\x29\x20\x66\x6f\x72\x20\x2f\x64\x65\x76\x2f\x73\x65\x72\x25\x64" "\n",channel,z7c9787d630->zcb322daed6);
#elif defined(__linux__)
SG_PRINTF(DEBUG,"\x5b\x63\x68\x61\x6e\x6e\x65\x6c\x20\x25\x64\x5d\x20\x77\x72\x69\x74\x65\x3a\x20\x4d\x6f\x64\x65\x6c\x53\x74\x6f\x70\x20\x28\x64\x69\x73\x61\x62\x6c\x65\x64\x29\x20\x66\x6f\x72\x20\x2f\x64\x65\x76\x2f\x74\x74\x79\x53\x54\x44\x52\x56\x30\x30\x32\x5f\x25\x64" "\n",channel,z7c9787d630->zcb322daed6);
#endif 
}sg_block_unregister(mod_info,z7210713648,channel);}
#endif 
#include "../common/libsg/sg_sfcn_glue.h" 

