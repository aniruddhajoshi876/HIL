// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL (0x1f76+1443-0x2517)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_serial_onboard_setup_s
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simstruc.h"
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#else
#include "sg_onboard_serial.h"
#include "sg_serial_device.h"
#include <errno.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#endif
#include "sg_printf.h"
#define SG_HAS_MDL_EXIT 
#define SG_EARLY_INIT   
#include "sg_callback.h"
#define za42e288061            ssGetSFcnParam(S, (0x198d+1140-0x1e01)) 
#define ze4059883e9            ssGetSFcnParam(S, (0x1443+2552-0x1e3a))
#define z3feec805f8    ssGetSFcnParam(S, (0x320+2736-0xdce))
#define z90aad68923       ssGetSFcnParam(S, (0xe43+125-0xebd))
#define z3d4ad966bd           ssGetSFcnParam(S, (0x1da+4313-0x12af))
#define za0b607dd5a           ssGetSFcnParam(S, (0x1708+997-0x1ae8))
#define z3a4043dd01          ssGetSFcnParam(S, (0x68d+3655-0x14ce))
#define z1448879324         ssGetSFcnParam(S, (0x445+4093-0x143b))
#define z9730049580      ssGetSFcnParam(S, (0xbbc+3182-0x1822))
#define zba954b6a25            ssGetSFcnParam(S, (0x732+6967-0x2260))
#define zdf24515981                       ((0x181b+1155-0x1c94))
#define z967d0f201f    (0x1a08+2434-0x2389)
#define z2e6483d505 ((0x1196+1825-0x18b7))
#define zc5ce4cb81a ((0xbb+7124-0x1c8f))
#define z2b17e2ee3b ((0xe56+1886-0x15b4))
#ifndef MATLAB_MEX_FILE
#if defined(__linux__)
static speed_t z87b9deeea1[]={B1000000,B921600,B576000,B500000,B460800,B230400,B115200,B57600,B38400,B19200,B9600,B4800,B2400,B1200,B600,B300};static speed_t z41f398d05b[]={B500000,B460800,B230400,B115200,B57600,B38400,B19200,B9600,B4800,B2400,B1200,B600,B300};
#endif
static speed_t zf9c352684b[]={B115200,B57600,B38400,B19200,B9600,B4800,B2400,B1200,B600,B300};static int z1f779271ed[]={(0xe36+934-0x11d8),(0x147+5256-0x15cb),(0x6b9+1587-0xcea),(0x10e2+1604-0x1724)};static const char*ze05bba9763[]={"\x4d\x6f\x62\x69\x6c\x65","\x50\x65\x72\x66\x6f\x72\x6d\x61\x6e\x63\x65","\x42\x61\x73\x65\x6c\x69\x6e\x65","\x50\x75\x6c\x73\x65"};
#endif
static char msg[(0x4f5+7082-0x1f9f)];static void mdlInitializeSizes(SimStruct*S){int i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x58d+6885-0x2072));ssSetNumDiscStates(S,(0xd68+5843-0x243b));if(!ssSetNumOutputPorts(S,(0x433+6693-0x1e58)))return;if(!ssSetNumInputPorts(S,(0x10a9+2900-0x1bfd)))return;ssSetNumSampleTimes(S,(0x1179+4068-0x215c));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0xd29+5990-0x248f));ssSetNumNonsampledZCs(S,(0xfd5+5385-0x24de));for(i=(0xee6+5152-0x2306);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x1071+4127-0x2090));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE|SS_OPTION_PLACE_ASAP);}static void mdlInitializeSampleTimes(SimStruct*S){ssSetSampleTime(S,(0x8d6+5367-0x1dcd),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x9bd+5588-0x1f91),FIXED_IN_MINOR_STEP_OFFSET);}
#ifndef MATLAB_MEX_FILE
static void sg_ModelLoad(SimStruct*S){z20c725b0cc*zae10e3f17f=nullptr;sg_mod_info*mod_info=nullptr;speed_t baudrate;int z612ee389d2=(0xf49+1300-0x145d);int zbc7ebd0e53,i;char*Name=NULL;int z0add1d1c25=(0x1bdd+661-0x1e72);int mode;Name=Name;if(sg_module_get_single(SG_ONBOARD_SERIAL_UART,z967d0f201f)){SG_PRINTF(DEBUG,"\x4f\x6e\x62\x6f\x61\x72\x64\x20\x53\x65\x72\x69\x61\x6c\x20\x53\x65\x74\x75\x70\x3a\x20\x4d\x6f\x64\x75\x6c\x65\x20\x61\x6c\x72\x65\x61\x64\x79\x20\x72\x65\x67\x69\x73\x74\x65\x72\x65\x64\x21" "\n");return;}SG_PRINTF(DEBUG,"\x4f\x6e\x62\x6f\x61\x72\x64\x20\x53\x65\x72\x69\x61\x6c\x20\x28\x49\x44\x20\x25\x64\x29\x20\x53\x65\x74\x75\x70\x3a\x20\x52\x65\x67\x69\x73\x74\x65\x72\x69\x6e\x67\x20\x6d\x6f\x64\x75\x6c\x65" "\n",z967d0f201f);zbc7ebd0e53=z1f779271ed[(int)mxGetPr(z9730049580)[(0x4e0+5116-0x18dc)]-(0x1144+413-0x12e0)];Name=(char*)(ze05bba9763[(int)mxGetPr(z9730049580)[(0x1623+171-0x16ce)]-(0x267+8384-0x2326)]);SG_PRINTF(DEBUG,"\x4d\x61\x78\x20\x25\x64\x20\x70\x6f\x72\x74\x73\x20\x6f\x6e\x20\x25\x73" "\n",zbc7ebd0e53,Name);for(i=(0xf8d+3664-0x1ddd);i<zbc7ebd0e53;i++){SG_PRINTF(DEBUG,"\x69\x20\x3d\x20\x25\x64" "\n",i);SG_PRINTF(DEBUG,"\x4d\x4f\x44\x45\x5f\x41\x52\x47\x20\x25\x64" "\n",(int)mxGetPr(za42e288061)[i]);SG_PRINTF(DEBUG,"\x42\x41\x55\x44\x5f\x41\x52\x47\x20\x25\x64" "\n",(int)mxGetPr(ze4059883e9)[i]);SG_PRINTF(DEBUG,"\x57\x49\x44\x54\x48\x5f\x41\x52\x47\x20\x25\x64" "\n",(int)mxGetPr(z3d4ad966bd)[i]);SG_PRINTF(DEBUG,"\x4e\x53\x54\x4f\x50\x5f\x41\x52\x47\x20\x25\x64" "\n",(int)mxGetPr(za0b607dd5a)[i]);SG_PRINTF(DEBUG,"\x50\x41\x52\x49\x54\x59\x5f\x41\x52\x47\x20\x25\x64" "\n",(int)mxGetPr(z3a4043dd01)[i]);SG_PRINTF(DEBUG,"\x43\x54\x53\x4d\x4f\x44\x45\x5f\x41\x52\x47\x20\x25\x64" "\n",(int)mxGetPr(z1448879324)[i]);SG_PRINTF(DEBUG,"\x54\x45\x52\x4d\x5f\x41\x52\x47\x20\x25\x64" "\n",(int)mxGetPr(zba954b6a25)[i]);}mod_info=sg_module_register(SG_ONBOARD_SERIAL_UART,z967d0f201f);zae10e3f17f=(z20c725b0cc*)malloc(sizeof(z20c725b0cc));zae10e3f17f->ze3584cafff=zbc7ebd0e53;mod_info->custom_data=(void*)zae10e3f17f;for(i=(0x7c2+7559-0x2549);i<zbc7ebd0e53;i++){mode=(int)mxGetPr(za42e288061)[i]-(0x306+5336-0x17dd);z0add1d1c25=i+(0x12ed+4110-0x22fa);if(mode!=(0x1db+4504-0x1373)){zae10e3f17f->enabled[z0add1d1c25]=true;if(strcmp(Name,"\x50\x75\x6c\x73\x65")){baudrate=zf9c352684b[(int)(mxGetPr(ze4059883e9)[i]-(0x1d35+1404-0x22b0))];}else if(!strcmp(Name,"\x50\x75\x6c\x73\x65")){if((int)(mxGetPr(z3feec805f8)[i])>(0x731+2329-0x104a)){baudrate=(int)(mxGetPr(z90aad68923)[i]);}else{if(mode==(0x18f6+969-0x1cbe)){
#if defined(__linux__)
baudrate=z41f398d05b[(int)(mxGetPr(ze4059883e9)[i]-(0x583+975-0x951))];
#endif
}else if(((mode==(0xd5b+2591-0x1778))||(mode==(0xc7+1265-0x5b5)))){
#if defined(__linux__)
baudrate=z87b9deeea1[(int)(mxGetPr(ze4059883e9)[i]-(0xbed+396-0xd78))];
#endif                
}else{sprintf(msg,"\x53\x65\x72\x69\x61\x6c\x20\x53\x65\x74\x75\x70\x20\x66\x6f\x72\x20\x70\x6f\x72\x74\x20\x25\x64\x20\x65\x72\x72\x6f\x72\x3a\x20\x69\x6e\x63\x6f\x72\x72\x65\x63\x74\x20\x62\x61\x75\x64\x72\x61\x74\x65\x20\x63\x6f\x6e\x66\x69\x67\x75\x72\x61\x74\x69\x6f\x6e" "\n",z0add1d1c25);ssSetErrorStatus(S,msg);return;}}}SG_PRINTF(DEBUG,"\x43\x68\x25\x64\x20\x4c\x4f\x41\x44\x20\x73\x65\x74\x20\x62\x61\x75\x64\x72\x61\x74\x65\x3a\x20\x30\x78\x25\x58\x2c\x20\x25\x64" "\n",i,baudrate,baudrate);int z46013fbdaf=(int)(mxGetPr(z3d4ad966bd)[i]);z2319db2dfc zf12d8b9b7a=(z2319db2dfc)mxGetPr(z3a4043dd01)[i];int zb06095ec0f=(int)mxGetPr(za0b607dd5a)[i];int zbca6783f35=(int)mxGetPr(z1448879324)[i];z612ee389d2=sg_serial_device_config(z0add1d1c25,baudrate,z46013fbdaf,zf12d8b9b7a,zb06095ec0f,zbca6783f35);if(z612ee389d2<(0x10f0+3260-0x1dac)){sprintf(msg,"\x53\x65\x72\x69\x61\x6c\x20\x53\x65\x74\x75\x70\x20\x66\x6f\x72\x20\x70\x6f\x72\x74\x20\x25\x64\x20\x65\x72\x72\x6f\x72\x3a\x20\x25\x73" "\n",z0add1d1c25,strerror(errno));ssSetErrorStatus(S,msg);return;}if((int)mxGetPr(z9730049580)[(0xb28+4410-0x1c62)]==(0xd0b+6311-0x25ae)){z612ee389d2=sg_serial_device_set_mode(z0add1d1c25,mode);if(z612ee389d2<(0xd66+2657-0x17c7)){sprintf(msg,"\x53\x65\x72\x69\x61\x6c\x20\x53\x65\x74\x75\x70\x20\x66\x6f\x72\x20\x70\x6f\x72\x74\x20\x25\x64\x20\x65\x72\x72\x6f\x72\x3a\x20\x25\x73" "\n",z0add1d1c25,strerror(errno));ssSetErrorStatus(S,msg);return;}sg_serial_device_set_termination(z0add1d1c25,(int)(mxGetPr(zba954b6a25)[i]));if(z612ee389d2<(0x1610+2774-0x20e6)){sprintf(msg,"\x53\x65\x72\x69\x61\x6c\x20\x53\x65\x74\x75\x70\x20\x66\x6f\x72\x20\x70\x6f\x72\x74\x20\x25\x64\x20\x65\x72\x72\x6f\x72\x3a\x20\x25\x73" "\n",z0add1d1c25,strerror(errno));ssSetErrorStatus(S,msg);return;}}sg_serial_device_flush(z0add1d1c25,zba6a39c684);SG_PRINTF(DEBUG,"\x5b\x70\x6f\x72\x74\x20\x25\x64\x5d\x20\x73\x65\x74\x75\x70\x20\x3a\x20\x73\x67\x5f\x4d\x6f\x64\x65\x6c\x4c\x6f\x61\x64" "\n",z0add1d1c25);}else{zae10e3f17f->enabled[z0add1d1c25]=false;}}}static void sg_ModelStart(SimStruct*S){}static void sg_ModelStep(SimStruct*S){}static void sg_ModelStop(SimStruct*S){}static void sg_ModelExit(SimStruct*S){SG_PRINTF(DEBUG,"\x4f\x6e\x62\x6f\x61\x72\x64\x20\x53\x65\x72\x69\x61\x6c\x20\x28\x49\x44\x20\x25\x64\x29\x20\x53\x65\x74\x75\x70\x3a\x20\x73\x67\x5f\x4d\x6f\x64\x65\x6c\x45\x78\x69\x74" "\n",z967d0f201f);z20c725b0cc*zae10e3f17f=(z20c725b0cc*)sg_module_get_custom_data(SG_ONBOARD_SERIAL_UART,z967d0f201f);if(zae10e3f17f){SG_PRINTF(DEBUG,"\x4f\x6e\x62\x6f\x61\x72\x64\x20\x53\x65\x72\x69\x61\x6c\x20\x28\x49\x44\x20\x25\x64\x29\x20\x53\x65\x74\x75\x70\x3a\x20\x46\x72\x65\x65\x20\x64\x65\x76\x69\x63\x65\x20\x73\x74\x72\x75\x63\x74" "\n",z967d0f201f);free(zae10e3f17f);SG_PRINTF(DEBUG,"\x4f\x6e\x62\x6f\x61\x72\x64\x20\x53\x65\x72\x69\x61\x6c\x20\x28\x49\x44\x20\x25\x64\x29\x20\x53\x65\x74\x75\x70\x3a\x20\x55\x6e\x72\x65\x67\x69\x73\x74\x65\x72\x20\x64\x65\x76" "\n",z967d0f201f);sg_module_unregister(SG_ONBOARD_SERIAL_UART,z967d0f201f);SG_PRINTF(INFO,"\x54\x65\x72\x6d\x69\x6e\x61\x74\x65\x64\x20\x3a\x20\x4f\x6e\x42\x6f\x61\x72\x64\x20\x73\x65\x72\x69\x61\x6c" "\n");}}
#endif 
#include "sg_sfcn_glue.h"   

