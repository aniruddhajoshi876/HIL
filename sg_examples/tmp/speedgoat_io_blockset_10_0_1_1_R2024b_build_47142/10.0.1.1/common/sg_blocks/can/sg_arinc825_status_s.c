// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL    (0x2dd+6454-0x1c11)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_arinc825_status_s
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#else
#include "sg_common.h"
#endif
#define SG_EARLY_INIT   
#include "sg_arinc825.h"
#include "simstruc.h"
#include "sg_callback.h"
enum zfb6915538d{zfaa050b79d,PCI_SLOT,z5b76458894,CHANNEL,z5b4926c440,z84c840ef6d,z5a46d47cec,zb21714e21d,z2ccbf15f4b,zefa1aec7af,z43434943e0,zdf24515981};static char msg[(0x1a07+1564-0x1f23)];static void mdlInitializeSizes(SimStruct*S){int i,z094c0030e8=(int)z9fe96ce105(zefa1aec7af)[(0x1089+498-0x127b)];ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n""\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64\x2e" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0xd2c+2854-0x1852));ssSetNumDiscStates(S,(0x5a3+843-0x8ee));if(!ssSetNumOutputPorts(S,z094c0030e8))return;for(i=(0x1cba+2518-0x2690);i<z094c0030e8;i++){ssSetOutputPortWidth(S,i,(0x20d+4609-0x140d));}i=(0x2016+667-0x22b1);if((int)z9fe96ce105(z5b4926c440)[(0x36d+4570-0x1547)]==(0xc53+2155-0x14bd)){ssSetOutputPortDataType(S,i,SS_UINT8);i++;}if((int)z9fe96ce105(z84c840ef6d)[(0x1ff9+1556-0x260d)]==(0x8a6+3572-0x1699)){ssSetOutputPortDataType(S,i,SS_UINT32);i++;}if((int)z9fe96ce105(z5a46d47cec)[(0x196+3736-0x102e)]==(0x900+1926-0x1085)){ssSetOutputPortDataType(S,i,SS_UINT32);i++;}if((int)z9fe96ce105(zb21714e21d)[(0x182b+832-0x1b6b)]==(0xbb2+2828-0x16bd)){ssSetOutputPortDataType(S,i,SS_UINT8);i++;}if((int)z9fe96ce105(z2ccbf15f4b)[(0x14b+8425-0x2234)]==(0x164a+3722-0x24d3)){ssSetOutputPortDataType(S,i,SS_UINT8);i++;}if(!ssSetNumInputPorts(S,(0x12ec+983-0x16c3)))return;ssSetNumSampleTimes(S,(0x1aa+645-0x42e));ssSetNumRWork(S,(0xadd+1328-0x100d));ssSetNumIWork(S,(0x3d1+5400-0x18e9));ssSetNumPWork(S,(0x728+3714-0x15aa));ssSetNumModes(S,(0x31+4161-0x1072));ssSetNumNonsampledZCs(S,(0x1f53+741-0x2238));for(i=(0x1122+4547-0x22e5);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,SS_PRM_NOT_TUNABLE);}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if((double)z9fe96ce105(z5b76458894)[(0x1277+326-0x13bd)]==-1.0){ssSetSampleTime(S,(0x1d16+1994-0x24e0),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x9fc+5319-0x1ec3),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x1d72+315-0x1ead),(double)z9fe96ce105(z5b76458894)[(0x384+5985-0x1ae5)]);ssSetOffsetTime(S,(0x16a7+3630-0x24d5),0.0);}}static void sg_ModelLoad(SimStruct*S){
#ifndef MATLAB_MEX_FILE
#endif
}static void sg_ModelStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
#endif
}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
int moduleId=(int)z9fe96ce105(zfaa050b79d)[(0x1f8+7089-0x1da9)];z71f9003a14*zae10e3f17f=(z71f9003a14*)sg_module_get_custom_data(z6668cd44ca,moduleId);if(!zae10e3f17f){sprintf(z56b1f895ea,"\x54\x79\x70\x65\x20\x25\x64\x2c\x20\x49\x44\x20\x25\x64\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79",z6668cd44ca,moduleId);ssSetErrorStatus(S,z56b1f895ea);return;}int i,ch=(int)z9fe96ce105(CHANNEL)[(0x1ce7+1472-0x22a7)]-(0x11bc+5358-0x26a9);ARINC_RESULT z9e92215ca6;ARINC_STATUS status;z9e92215ca6=arincStatus(zae10e3f17f->z123d2c471a[ch],&status);if(z9e92215ca6!=ARINC_SUCCESS){sprintf(msg,"\x43\x68\x25\x64\x20\x72\x65\x61\x64\x20\x64\x61\x74\x61\x20\x66\x61\x69\x6c\x65\x64\x3a\x20\x25\x58",ch+(0xc98+1198-0x1145),z9e92215ca6);ssSetErrorStatus(S,msg);return;}i=(0x648+4447-0x17a7);if((int)z9fe96ce105(z5b4926c440)[(0x1061+4059-0x203c)]==(0x2382+292-0x24a5)){uint8_t*data=(uint8_t*)ssGetOutputPortSignal(S,i);*data=status.canStatus;i++;}if((int)z9fe96ce105(z84c840ef6d)[(0xa84+5457-0x1fd5)]==(0x34+7896-0x1f0b)){uint32_t*data=(uint32_t*)ssGetOutputPortSignal(S,i);*data=status.zbee47c169c;i++;}if((int)z9fe96ce105(z5a46d47cec)[(0xe40+2238-0x16fe)]==(0x846+6312-0x20ed)){uint32_t*data=(uint32_t*)ssGetOutputPortSignal(S,i);*data=status.z8a78cd5e82;i++;}if((int)z9fe96ce105(zb21714e21d)[(0x902+4983-0x1c79)]==(0x85a+6771-0x22cc)){uint8_t*data=(uint8_t*)ssGetOutputPortSignal(S,i);*data=status.z311a280923;i++;}if((int)z9fe96ce105(z2ccbf15f4b)[(0x1fec+952-0x23a4)]==(0x133+6442-0x1a5c)){uint8_t*data=(uint8_t*)ssGetOutputPortSignal(S,i);*data=status.z20823b70de;i++;}
#endif
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE
#endif
}
#include "sg_sfcn_glue.h"   

