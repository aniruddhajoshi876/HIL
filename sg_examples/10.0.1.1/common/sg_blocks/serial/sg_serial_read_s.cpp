// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL (0x1433+2606-0x1e5f)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_serial_read_s
#include "sg_serial.h"
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#ifndef MATLAB_MEX_FILE
#include <termios.h>
#endif
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
#define ze13f49a01f     ssGetSFcnParam(S, (0x13b1+4602-0x25ab))
#define za9d8fb6bcf       ssGetSFcnParam(S, (0x204+4600-0x13fb))
#define z6aab658c54         ssGetSFcnParam(S, (0x1fbb+472-0x2191))
#define z0f85e6ff7f ssGetSFcnParam(S, (0x1907+2497-0x22c5))
#define z39cbd24432   ssGetSFcnParam(S, (0x19bb+2683-0x2432))
#define z702a26a5e9          ssGetSFcnParam(S, (0x2479+651-0x26ff))
#define z3ec81e741b   ssGetSFcnParam(S, (0xa8f+5879-0x2180))
#define zbf4c83e854     ssGetSFcnParam(S, (0x879+19-0x885))
#define z4848d060ef     ssGetSFcnParam(S, (0x47a+8094-0x2410))
#define zdf24515981    ((0x12b2+3573-0x209e))
#define z2e6483d505 ((0x850+1452-0xdfc))
#define zc5ce4cb81a ((0x1338+28-0x1354))
#define z2b17e2ee3b ((0xa52+4913-0x1d83))
static char_T msg[(0xe2d+1169-0x11be)];static void mdlInitializeSizes(SimStruct*S){int i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x147+4825-0x1420));ssSetNumDiscStates(S,(0x1862+252-0x195e));ssSetNumInputPorts(S,(0x1f0b+500-0x20ff));if((int)mxGetPr(z0f85e6ff7f)[(0x22e2+680-0x258a)]){ssSetNumOutputPorts(S,(0x1801+1681-0x1e91));if(((int)mxGetPr(z4848d060ef)[(0x1103+1768-0x17eb)]==(0x404+1459-0x9b2))||((int)mxGetPr(z4848d060ef)[(0x1924+869-0x1c89)]==(0x1b69+1004-0x1f4f))){ssSetOutputPortWidth(S,(0x17e9+426-0x1993),(int)mxGetPr(zbf4c83e854)[(0x104a+4115-0x205d)]);}else{ssSetOutputPortWidth(S,(0x17cb+863-0x1b2a),(int)mxGetPr(zbf4c83e854)[(0x116d+1858-0x18af)]+(0x95+7227-0x1ccf));}switch((int)mxGetPr(z4848d060ef)[(0x10b9+3270-0x1d7f)]){case(0x1a9+6124-0x1994):ssSetOutputPortDataType(S,(0x1bc4+2310-0x24ca),SS_INT32);break;case(0x7d0+2293-0x10c3):ssSetOutputPortDataType(S,(0x13eb+2781-0x1ec8),SS_UINT32);break;case(0x11a+8701-0x2314):ssSetOutputPortDataType(S,(0x870+5433-0x1da9),SS_INT16);break;case(0xed+7314-0x1d7b):ssSetOutputPortDataType(S,(0x21eb+701-0x24a8),SS_UINT16);break;case(0x1c4+2767-0xc8e):ssSetOutputPortDataType(S,(0x4a0+8783-0x26ef),SS_INT8);break;case(0xb12+1376-0x106c):ssSetOutputPortDataType(S,(0x66+5363-0x1559),SS_UINT8);break;default:ssSetErrorStatus(S,"\x55\x6e\x6b\x6e\x6f\x77\x6e\x20\x64\x61\x74\x61\x20\x74\x79\x70\x65" "\n");return;}}else{ssSetNumOutputPorts(S,(0x15d8+1894-0x1d3c));ssSetOutputPortWidth(S,(0x7f+3751-0xf26),(0x167a+222-0x1757));ssSetOutputPortDataType(S,(0x57a+5643-0x1b85),SS_UINT32);ssSetOutputPortWidth(S,(0x1893+39-0x18b9),(int)mxGetPr(zbf4c83e854)[(0x1d87+138-0x1e11)]);ssSetOutputPortDataType(S,(0x1358+2991-0x1f06),SS_UINT8);}ssSetNumSampleTimes(S,(0x59b+2545-0xf8b));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x1799+679-0x1a40));ssSetNumNonsampledZCs(S,(0xed0+1843-0x1603));for(i=(0xa82+244-0xb76);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x12d7+4061-0x22b4));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z39cbd24432)[(0x14e8+4515-0x268b)]==-1.0){ssSetSampleTime(S,(0x1099+2345-0x19c2),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x1d9b+2322-0x26ad),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x175+4857-0x146e),mxGetPr(z39cbd24432)[(0x1f0c+1210-0x23c6)]);ssSetOffsetTime(S,(0x41c+5852-0x1af8),0.0);}}
#ifndef MATLAB_MEX_FILE
static void sg_ModelLoad(SimStruct*S){char zc43186f5f0[MAX_LENGTH_SERIAL_DEVICE_NAME];uint8_t channel=(uint8_t)mxGetPr(za9d8fb6bcf)[(0x5fb+430-0x7a9)]-(0xb79+5904-0x2288);sg_mod_info*mod_info=nullptr;z403b902beb*zae10e3f17f=nullptr;sg_block_info*z4b88529218=nullptr;z2c2985fa73*z1f72003d82=nullptr;
#ifdef zf734f25874
char z9d6b50f922[(0x88f+7146-0x23fa)];
#endif
uint32_t boardType=(int)mxGetPr(z3ec81e741b)[(0x1db9+1192-0x2261)]-(0x1b88+369-0x1cf8);int za0d38ae598=(int)mxGetPr(ze13f49a01f)[(0x402+590-0x650)];mod_info=(sg_mod_info*)sg_module_get_single(z0e14cce82f[boardType],za0d38ae598);zae10e3f17f=(z403b902beb*)mod_info->custom_data;if(!zae10e3f17f){sprintf(msg,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x69\x6e\x20\x52\x65\x61\x64\x20\x4d\x6f\x64\x65\x6c\x53\x74\x61\x72\x74" "\n",DEVNAME[boardType],za0d38ae598);ssSetErrorStatus(S,msg);return;}z4b88529218=(sg_block_info*)sg_block_register(mod_info,z41a83fe0f5,channel);if(!z4b88529218){sprintf(msg,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x67\x69\x73\x74\x65\x72\x20\x72\x65\x61\x64\x20\x62\x6c\x6f\x63\x6b\x20\x69\x6e\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x69\x6e\x20\x52\x65\x61\x64\x20\x4d\x6f\x64\x65\x6c\x4c\x6f\x61\x64" "\n",DEVNAME[boardType],za0d38ae598);ssSetErrorStatus(S,msg);return;}z1f72003d82=(z2c2985fa73*)malloc(sizeof(z2c2985fa73));z4b88529218->custom_data=(void*)z1f72003d82;
#if defined(__QNX__)
z1f72003d82->zcb322daed6=zae10e3f17f->zb003ac7e25+channel;
#elif defined(__linux__)
z1f72003d82->zcb322daed6=zae10e3f17f->z4e4c7f816f[channel];
#endif 
z1f72003d82->enabled=zae10e3f17f->enabled[channel];if(z1f72003d82->enabled){memset(zc43186f5f0,(0x723+1652-0xd97),sizeof(zc43186f5f0));
#if defined(__QNX__)
sprintf(zc43186f5f0,"\x2f\x64\x65\x76\x2f\x73\x65\x72\x25\x64",z1f72003d82->zcb322daed6);
#elif defined(__linux__)
sprintf(zc43186f5f0,"\x2f\x64\x65\x76\x2f\x74\x74\x79\x53\x54\x44\x52\x56\x30\x30\x32\x5f\x25\x64",z1f72003d82->zcb322daed6);
#endif 
z1f72003d82->fd=open(zc43186f5f0,O_RDWR|O_NONBLOCK);if(z1f72003d82->fd==-(0x1ce7+113-0x1d57)){sprintf(msg,"\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x6f\x70\x65\x6e\x20\x73\x65\x72\x69\x61\x6c\x20\x25\x73\x20\x28\x63\x68\x61\x6e\x6e\x65\x6c\x20\x25\x75\x29" "\n",zc43186f5f0,channel);ssSetErrorStatus(S,msg);return;}if((int)mxGetPr(z6aab658c54)[(0x996+4046-0x1964)]){if(tcflush(z1f72003d82->fd,TCIFLUSH)!=(0xf34+1634-0x1596)){
#if defined(__QNX__)
SG_PRINTF(ERROR,"\x5b\x63\x68\x61\x6e\x6e\x65\x6c\x20\x25\x64\x5d\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x66\x6c\x75\x73\x68\x20\x2f\x64\x65\x76\x2f\x73\x65\x72\x25\x64\x20\x69\x6e\x70\x75\x74\x20\x62\x75\x66\x66\x65\x72" "\n",channel,z1f72003d82->zcb322daed6);
#elif defined(__linux__)
SG_PRINTF(ERROR,"\x5b\x63\x68\x61\x6e\x6e\x65\x6c\x20\x25\x64\x5d\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x66\x6c\x75\x73\x68\x20\x2f\x64\x65\x76\x2f\x74\x74\x79\x53\x54\x44\x52\x56\x30\x30\x32\x5f\x25\x64\x20\x69\x6e\x70\x75\x74\x20\x62\x75\x66\x66\x65\x72" "\n",channel,z1f72003d82->zcb322daed6);
#endif 
}else{
#if defined(__QNX__)
SG_PRINTF(DEBUG,"\x5b\x63\x68\x61\x6e\x6e\x65\x6c\x20\x25\x64\x5d\x20\x46\x6c\x75\x73\x68\x65\x64\x20\x2f\x64\x65\x76\x2f\x73\x65\x72\x25\x64\x20\x69\x6e\x70\x75\x74\x20\x62\x75\x66\x66\x65\x72" "\n",channel,z1f72003d82->zcb322daed6);
#elif defined(__linux__)
SG_PRINTF(DEBUG,"\x5b\x63\x68\x61\x6e\x6e\x65\x6c\x20\x25\x64\x5d\x20\x46\x6c\x75\x73\x68\x65\x64\x20\x2f\x64\x65\x76\x2f\x74\x74\x79\x53\x54\x44\x52\x56\x30\x30\x32\x5f\x25\x64\x20\x69\x6e\x70\x75\x74\x20\x62\x75\x66\x66\x65\x72" "\n",channel,z1f72003d82->zcb322daed6);
#endif 
}}z1f72003d82->buffer=(uint8_t*)calloc((size_t)mxGetPr(zbf4c83e854)[(0x1015+1458-0x15c7)],sizeof(uint8_t));SG_PRINTF(DEBUG,"\x5b\x63\x68\x61\x6e\x6e\x65\x6c\x20\x25\x64\x5d\x20\x72\x65\x61\x64\x20\x3a\x20\x4d\x6f\x64\x65\x6c\x4c\x6f\x61\x64\x20\x28\x66\x64\x20\x3d\x20\x25\x64\x2c\x20\x6d\x6f\x64\x75\x6c\x65\x20\x64\x61\x74\x61\x3d\x30\x78\x25\x6c\x78\x2c\x20\x62\x75\x66\x66\x65\x72\x20\x30\x78\x25\x6c\x78\x20\x73\x69\x7a\x65\x20\x25\x64\x29\x20"
#if defined(__QNX__)
"\x66\x6f\x72\x20\x2f\x64\x65\x76\x2f\x73\x65\x72\x25\x64" "\n",
#elif defined(__linux__)
"\x66\x6f\x72\x20\x2f\x64\x65\x76\x2f\x74\x74\x79\x53\x54\x44\x52\x56\x30\x30\x32\x5f\x25\x64" "\n",
#endif 
channel,z1f72003d82->fd,zae10e3f17f,z1f72003d82->buffer,(int)mxGetPr(zbf4c83e854)[(0x319+8553-0x2482)],z1f72003d82->zcb322daed6);}else{
#if defined(__QNX__)
SG_PRINTF(DEBUG,"\x5b\x63\x68\x61\x6e\x6e\x65\x6c\x20\x25\x64\x5d\x20\x72\x65\x61\x64\x20\x3a\x20\x4d\x6f\x64\x65\x6c\x4c\x6f\x61\x64\x20\x3a\x20\x64\x69\x73\x61\x62\x6c\x65\x64\x20\x2f\x64\x65\x76\x2f\x73\x65\x72\x25\x64" "\n",channel,z1f72003d82->zcb322daed6);
#elif defined(__linux__)
SG_PRINTF(DEBUG,"\x5b\x63\x68\x61\x6e\x6e\x65\x6c\x20\x25\x64\x5d\x20\x72\x65\x61\x64\x20\x3a\x20\x4d\x6f\x64\x65\x6c\x4c\x6f\x61\x64\x20\x3a\x20\x64\x69\x73\x61\x62\x6c\x65\x64\x20\x2f\x64\x65\x76\x2f\x74\x74\x79\x53\x54\x44\x52\x56\x30\x30\x32\x5f\x25\x64" "\n",channel,z1f72003d82->zcb322daed6);
#endif 
}
#ifdef zf734f25874
memset(z9d6b50f922,(0x1bc2+870-0x1f28),sizeof(z9d6b50f922));sprintf(z9d6b50f922,"\x2f\x68\x6f\x6d\x65\x2f\x73\x6c\x72\x74\x2f\x49\x4f\x25\x64\x5f\x49\x44\x25\x64\x5f\x43\x48\x25\x64\x5f\x69\x6e\x2e\x74\x78\x74",zac61c2c0e1,zae10e3f17f->moduleId,channel);z7c9787d630->z8196b021ae=fopen(z9d6b50f922,"\x77");if(z7c9787d630->z8196b021ae!=NULL){SG_PRINTF(INFO,"\x5b\x63\x68\x61\x6e\x6e\x65\x6c\x20\x25\x64\x5d\x20\x52\x65\x61\x64\x20\x3a\x20\x66\x69\x6c\x65\x20\x63\x72\x65\x61\x74\x65\x64\x20\x25\x73" "\n",channel,z9d6b50f922);}else{SG_PRINTF(INFO,"\x5b\x63\x68\x61\x6e\x6e\x65\x6c\x20\x25\x64\x5d\x20\x52\x65\x61\x64\x20\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x63\x72\x65\x61\x74\x65\x20\x66\x69\x6c\x65\x20\x25\x73\x20\x28\x65\x72\x72\x20\x25\x64\x29" "\n",channel,z9d6b50f922,errno);}z7c9787d630->ze667de5014=(0xa38+4703-0x1c97);
#endif
}static void sg_ModelStart(SimStruct*S){}static void sg_ModelStep(SimStruct*S){int i=(0x1d5+9079-0x254c);int z7b5c8c9301=(0x99+5853-0x1776);uint8_t*z089caa3eaf;uint16_t*ze6e8f68f90;uint32_t*zffb4423670;uint8_t channel=(uint8_t)mxGetPr(za9d8fb6bcf)[(0x6cd+718-0x99b)]-(0x1b69+68-0x1bac);sg_mod_info*mod_info=nullptr;sg_block_info*z4b88529218=nullptr;z2c2985fa73*z1f72003d82=nullptr;uint32_t boardType=(int)mxGetPr(z3ec81e741b)[(0x129d+116-0x1311)]-(0x469+952-0x820);int za0d38ae598=(int)mxGetPr(ze13f49a01f)[(0x1331+1853-0x1a6e)];mod_info=(sg_mod_info*)sg_module_get_single(z0e14cce82f[boardType],za0d38ae598);z4b88529218=(sg_block_info*)sg_block_get(mod_info,z41a83fe0f5,channel);if(!z4b88529218){sprintf(msg,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x77\x72\x69\x74\x65\x20\x62\x6c\x6f\x63\x6b\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x69\x6e\x20\x52\x65\x61\x64\x20\x4d\x6f\x64\x65\x6c\x53\x74\x61\x72\x74" "\n",DEVNAME[boardType],za0d38ae598);ssSetErrorStatus(S,msg);return;}z1f72003d82=(z2c2985fa73*)z4b88529218->custom_data;if(z1f72003d82->enabled==zf7e8aabb5e){*(uint32_t*)ssGetOutputPortSignal(S,(0x1359+3210-0x1fe3))=(0x1aa0+1636-0x2104);SG_PRINTF(TRACE,"\x5b\x63\x68\x61\x6e\x6e\x65\x6c\x20\x25\x64\x5d\x20\x52\x65\x61\x64\x20\x3a\x20\x4d\x6f\x64\x65\x6c\x53\x74\x65\x70\x20\x3a\x20\x64\x69\x73\x61\x62\x6c\x65\x64" "\n",channel);return;}z7b5c8c9301=read(z1f72003d82->fd,z1f72003d82->buffer,(int)mxGetPr(zbf4c83e854)[(0x11cf+1494-0x17a5)]);if(z7b5c8c9301>(0x184c+3679-0x26ab)){
#ifdef zf734f25874
z7c9787d630->ze667de5014+=z7b5c8c9301;if(z7c9787d630->z8196b021ae!=NULL){fprintf(z7c9787d630->z8196b021ae,"\x30\x78\x25\x30\x32\x78\x20\x3a\x20",z7b5c8c9301);for(i=(0x693+2209-0xf34);i<z7b5c8c9301;i++){fprintf(z7c9787d630->z8196b021ae,"\x30\x78\x25\x30\x32\x78\x20",buffer[i]);}fprintf(z7c9787d630->z8196b021ae,"\n");}
#endif
if((int)mxGetPr(z0f85e6ff7f)[(0x138b+1065-0x17b4)]){switch((int)mxGetPr(z4848d060ef)[(0x11f9+5108-0x25ed)]){case(0x3c0+2924-0xf2b):case(0x638+97-0x697):zffb4423670=(uint32_t*)ssGetOutputPortSignal(S,(0x42+5363-0x1535));zffb4423670[(0x3a3+995-0x786)]=(uint32_t)z7b5c8c9301;for(i=(0x8b+4248-0x1123);i<z7b5c8c9301;i++){zffb4423670[i+(0x810+4238-0x189d)]=(uint32_t)z1f72003d82->buffer[i];}break;case(0x2170+75-0x21b8):case(0xa5a+6098-0x2228):ze6e8f68f90=(uint16_t*)ssGetOutputPortSignal(S,(0xf77+3680-0x1dd7));ze6e8f68f90[(0xe9d+3203-0x1b20)]=(uint16_t)z7b5c8c9301;for(i=(0x4ab+7925-0x23a0);i<z7b5c8c9301;i++){ze6e8f68f90[i+(0x1513+1202-0x19c4)]=(uint16_t)z1f72003d82->buffer[i];}break;case(0x78a+628-0x9f9):case(0x5c3+672-0x85d):z089caa3eaf=(uint8_t*)ssGetOutputPortSignal(S,(0xd5b+6125-0x2548));for(i=(0x1070+4342-0x2166);i<z7b5c8c9301;i++){z089caa3eaf[i]=(uint8_t)z1f72003d82->buffer[i];}z089caa3eaf[i]=(0xb1c+6957-0x2649);break;default:ssSetErrorStatus(S,"\x55\x6e\x6b\x6e\x6f\x77\x6e\x20\x64\x61\x74\x61\x20\x74\x79\x70\x65" "\n");return;}}else{*(uint32_t*)ssGetOutputPortSignal(S,(0x1b8+5424-0x16e8))=z7b5c8c9301;z089caa3eaf=(uint8_t*)ssGetOutputPortSignal(S,(0x27c+6736-0x1ccb));for(i=(0x5e3+5544-0x1b8b);i<z7b5c8c9301;i++){z089caa3eaf[i]=(uint8_t)z1f72003d82->buffer[i];}
#if defined(__QNX__)
SG_PRINTF(TRACE,"\x5b\x63\x68\x61\x6e\x6e\x65\x6c\x20\x25\x64\x5d\x20\x52\x65\x61\x64\x20\x25\x64\x20\x62\x79\x74\x65\x73\x20\x66\x72\x6f\x6d\x20\x2f\x64\x65\x76\x2f\x73\x65\x72\x25\x64" "\n",channel,z7b5c8c9301,z1f72003d82->zcb322daed6);
#elif defined(__linux__)
SG_PRINTF(TRACE,"\x5b\x63\x68\x61\x6e\x6e\x65\x6c\x20\x25\x64\x5d\x20\x52\x65\x61\x64\x20\x25\x64\x20\x62\x79\x74\x65\x73\x20\x66\x72\x6f\x6d\x20\x2f\x64\x65\x76\x2f\x74\x74\x79\x53\x54\x44\x52\x56\x30\x30\x32\x5f\x25\x64" "\n",channel,z7b5c8c9301,z1f72003d82->zcb322daed6);
#endif 
}}else{*(uint32_t*)ssGetOutputPortSignal(S,(0x503+2896-0x1053))=(0x218+3211-0xea3);}}static void sg_ModelStop(SimStruct*S){uint8_t channel=(uint8_t)mxGetPr(za9d8fb6bcf)[(0x112b+611-0x138e)]-(0x5c2+893-0x93e);sg_mod_info*mod_info=nullptr;z403b902beb*zae10e3f17f=nullptr;sg_block_info*z4b88529218=nullptr;z2c2985fa73*z1f72003d82=nullptr;uint32_t boardType=(int)mxGetPr(z3ec81e741b)[(0x77a+7064-0x2312)]-(0xabb+7046-0x2640);int za0d38ae598=(int)mxGetPr(ze13f49a01f)[(0x9a3+3230-0x1641)];mod_info=(sg_mod_info*)sg_module_get_single(z0e14cce82f[boardType],za0d38ae598);z4b88529218=(sg_block_info*)sg_block_get(mod_info,z41a83fe0f5,channel);if(!z4b88529218){sprintf(msg,"\x25\x73\x20\x28\x49\x44\x20\x25\x64\x29\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x77\x72\x69\x74\x65\x20\x62\x6c\x6f\x63\x6b\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x69\x6e\x20\x52\x65\x61\x64\x20\x4d\x6f\x64\x65\x6c\x53\x74\x6f\x70" "\n",DEVNAME[boardType],za0d38ae598);ssSetErrorStatus(S,msg);return;}zae10e3f17f=(z403b902beb*)mod_info->custom_data;z1f72003d82=(z2c2985fa73*)z4b88529218->custom_data;if(z1f72003d82->enabled){
#if defined(__QNX__)
SG_PRINTF(DEBUG,"\x5b\x63\x68\x61\x6e\x6e\x65\x6c\x20\x25\x64\x5d\x20\x72\x65\x61\x64\x3a\x20\x4d\x6f\x64\x65\x6c\x53\x74\x6f\x70\x20\x28\x66\x64\x20\x3d\x20\x25\x64\x2c\x20\x62\x75\x66\x66\x65\x72\x20\x30\x78\x25\x6c\x78\x29\x20\x66\x6f\x72\x20\x2f\x64\x65\x76\x2f\x73\x65\x72\x25\x64" "\n",channel,z1f72003d82->fd,z1f72003d82->buffer,z1f72003d82->zcb322daed6);
#elif defined(__linux__)
SG_PRINTF(DEBUG,"\x5b\x63\x68\x61\x6e\x6e\x65\x6c\x20\x25\x64\x5d\x20\x72\x65\x61\x64\x3a\x20\x4d\x6f\x64\x65\x6c\x53\x74\x6f\x70\x20\x28\x66\x64\x20\x3d\x20\x25\x64\x2c\x20\x62\x75\x66\x66\x65\x72\x20\x30\x78\x25\x6c\x78\x29\x20\x66\x6f\x72\x20\x2f\x64\x65\x76\x2f\x74\x74\x79\x53\x54\x44\x52\x56\x30\x30\x32\x5f\x25\x64" "\n",channel,z1f72003d82->fd,z1f72003d82->buffer,z1f72003d82->zcb322daed6);
#endif 
#ifdef zf734f25874
#if defined(__QNX__)
SG_PRINTF(INFO,"\x5b\x63\x68\x61\x6e\x6e\x65\x6c\x20\x25\x64\x5d\x20\x72\x65\x61\x64\x3a\x20\x43\x6f\x75\x6e\x74\x65\x72\x20\x25\x64\x20\x66\x6f\x72\x20\x2f\x64\x65\x76\x2f\x73\x65\x72\x25\x64" "\n",channel,z085e5fb475,z1f72003d82->zcb322daed6);
#elif defined(__linux__)
SG_PRINTF(INFO,"\x5b\x63\x68\x61\x6e\x6e\x65\x6c\x20\x25\x64\x5d\x20\x72\x65\x61\x64\x3a\x20\x43\x6f\x75\x6e\x74\x65\x72\x20\x25\x64\x20\x66\x6f\x72\x20\x2f\x64\x65\x76\x2f\x74\x74\x79\x53\x54\x44\x52\x56\x30\x30\x32\x5f\x25\x64" "\n",channel,z085e5fb475,z1f72003d82->zcb322daed6);
#endif 
if(z7c9787d630->z8196b021ae!=NULL){fclose(z7c9787d630->z8196b021ae);}
#endif
if(!zae10e3f17f->z5dd2589b61[channel]){if(z1f72003d82->fd>(0x853+7054-0x23e1)){SG_PRINTF(DEBUG,"\x5b\x63\x68\x61\x6e\x6e\x65\x6c\x20\x25\x64\x5d\x20\x72\x65\x61\x64\x3a\x20\x63\x6c\x6f\x73\x65\x20\x66\x64\x20\x25\x64" "\n",channel,z1f72003d82->fd);close(z1f72003d82->fd);}}if(z1f72003d82->buffer!=nullptr){SG_PRINTF(DEBUG,"\x5b\x63\x68\x61\x6e\x6e\x65\x6c\x20\x25\x64\x5d\x20\x72\x65\x61\x64\x3a\x20\x66\x72\x65\x65\x20\x62\x75\x66\x66\x65\x72\x20\x25\x78" "\n",channel,z1f72003d82->buffer);free(z1f72003d82->buffer);}}else{
#if defined(__QNX__)
SG_PRINTF(DEBUG,"\x5b\x63\x68\x61\x6e\x6e\x65\x6c\x20\x25\x64\x5d\x20\x72\x65\x61\x64\x3a\x20\x4d\x6f\x64\x65\x6c\x53\x74\x6f\x70\x20\x28\x64\x69\x73\x61\x62\x6c\x65\x64\x29\x20\x66\x6f\x72\x20\x2f\x64\x65\x76\x2f\x73\x65\x72\x25\x64" "\n",channel,z1f72003d82->zcb322daed6);
#elif defined(__linux__)
SG_PRINTF(DEBUG,"\x5b\x63\x68\x61\x6e\x6e\x65\x6c\x20\x25\x64\x5d\x20\x72\x65\x61\x64\x3a\x20\x4d\x6f\x64\x65\x6c\x53\x74\x6f\x70\x20\x28\x64\x69\x73\x61\x62\x6c\x65\x64\x29\x20\x66\x6f\x72\x20\x2f\x64\x65\x76\x2f\x74\x74\x79\x53\x54\x44\x52\x56\x30\x30\x32\x5f\x25\x64" "\n",channel,z1f72003d82->zcb322daed6);
#endif 
}sg_block_unregister(mod_info,z41a83fe0f5,channel);}
#endif 
#include "../common/libsg/sg_sfcn_glue.h" 

