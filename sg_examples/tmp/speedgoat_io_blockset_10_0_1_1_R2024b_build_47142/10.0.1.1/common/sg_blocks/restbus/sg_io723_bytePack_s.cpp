// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL    (0x1dc6+130-0x1e46)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_io723_bytePack_s
#include "simstruc.h"
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif
#include "sg_callback.h"
#include "sg_IO723.h"
enum z9c14fdf935{za44a96867a,zdf24515981};enum zbb1f615c1d{z2e6483d505};enum z93bcf30780{zc5ce4cb81a};enum zb06a9f15ae{z2b17e2ee3b};static char msg[(0x909+7677-0x2606)];static void mdlInitializeSizes(SimStruct*S){int i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x7ea+4169-0x1833));ssSetNumDiscStates(S,(0x131f+4327-0x2406));ssSetNumOutputPorts(S,(0x174f+858-0x1aa8));ssSetOutputPortWidth(S,(0x677+7995-0x25b2),(int)mxGetPr(ssGetSFcnParam(S,za44a96867a))[(0x198+904-0x520)]);ssSetOutputPortDataType(S,(0xe04+1747-0x14d7),SS_UINT8);ssSetNumInputPorts(S,(0xb2d+2967-0x16c3));ssSetInputPortWidth(S,(0x533+7312-0x21c3),DYNAMICALLY_SIZED);ssSetInputPortDataType(S,(0x1fb+3731-0x108e),DYNAMICALLY_TYPED);ssSetNumSampleTimes(S,(0x110+3328-0xe0f));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0xa9d+471-0xc74));ssSetNumNonsampledZCs(S,(0x17bb+2144-0x201b));for(i=(0x13cd+2107-0x1c08);i<ssGetNumInputPorts(S);i++){ssSetInputPortDirectFeedThrough(S,i,(0x1703+3276-0x23ce));ssSetInputPortRequiredContiguous(S,i,(0x3ec+6351-0x1cba));}for(i=(0x1bc+3825-0x10ad);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0xad4+2650-0x152e));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}
#define z9a0a1a096e
static void mdlSetInputPortWidth(SimStruct*S,int_T z0add1d1c25,int_T width){if(width<(0x1ac+3207-0xe32)){sprintf(msg,"\x49\x6e\x70\x75\x74\x20\x76\x65\x63\x74\x6f\x72\x20\x77\x69\x64\x74\x68\x20\x6f\x66\x20\x70\x6f\x72\x74\x20\x25\x64\x20\x6d\x75\x73\x74\x20\x62\x65\x20\x61\x74\x20\x6c\x65\x61\x73\x74\x20\x31" "\n",z0add1d1c25);ssSetErrorStatus(S,msg);return;}ssSetInputPortWidth(S,z0add1d1c25,width);}
#define z77c8531164
static void mdlSetOutputPortWidth(SimStruct*S,int_T z0add1d1c25,int_T width){if(width<(0x2242+823-0x2578)){sprintf(msg,"\x4f\x75\x74\x70\x75\x74\x20\x76\x65\x63\x74\x6f\x72\x20\x77\x69\x64\x74\x68\x20\x6f\x66\x20\x70\x6f\x72\x74\x20\x25\x64\x20\x6d\x75\x73\x74\x20\x62\x65\x20\x61\x74\x20\x6c\x65\x61\x73\x74\x20\x31" "\n",z0add1d1c25);ssSetErrorStatus(S,msg);return;}ssSetOutputPortWidth(S,z0add1d1c25,width);}
#define z6e5bf7e48a
void mdlSetInputPortDataType(SimStruct*S,int_T z0add1d1c25,DTypeId id){if((id<(0x714+4633-0x192d))||(id>(0x8ed+2109-0x1122))){sprintf(msg,"\x4f\x6e\x6c\x79\x20\x62\x61\x73\x69\x63\x20\x64\x61\x74\x61\x20\x74\x79\x70\x65\x73\x20\x61\x72\x65\x20\x61\x6c\x6c\x6f\x77\x65\x64" "\n",z0add1d1c25);ssSetErrorStatus(S,msg);return;}ssSetInputPortDataType(S,z0add1d1c25,id);int zbc29571b7b=ssGetInputPortWidth(S,z0add1d1c25);switch(id){case(0x19e9+1502-0x1fc7):zbc29571b7b*=(0x5ba+7995-0x24ed);break;case(0x1648+154-0x16e1):zbc29571b7b*=(0x1bf3+2513-0x25c0);break;case(0x203f+709-0x2302):zbc29571b7b*=(0xad6+2184-0x135d);break;case(0x115b+5091-0x253b):zbc29571b7b*=(0xd39+2783-0x1817);break;case(0x8e7+5189-0x1d28):zbc29571b7b*=(0x11a1+3247-0x1e4e);break;case(0x6e5+2676-0x1154):zbc29571b7b*=(0x6a3+7447-0x23b8);break;case(0x93d+6519-0x22ae):zbc29571b7b*=(0x95+8869-0x2336);break;case(0x22d8+208-0x23a1):zbc29571b7b*=(0x1c65+779-0x1f6c);break;case(0x1fc8+204-0x208c):zbc29571b7b*=(0xfa6+5716-0x25f9);break;}if(zbc29571b7b!=ssGetOutputPortWidth(S,z0add1d1c25)){sprintf(msg,"\x49\x6e\x70\x75\x74\x20\x70\x6f\x72\x74\x20\x73\x69\x7a\x65\x20\x28\x25\x64\x20\x62\x79\x74\x65\x73\x29\x20\x64\x6f\x65\x73\x20\x6e\x6f\x74\x20\x6d\x61\x74\x63\x68\x20\x6f\x75\x74\x70\x75\x74\x20\x70\x6f\x72\x74\x20\x73\x69\x7a\x65\x20\x28\x25\x64\x20\x62\x79\x74\x65\x73\x29",zbc29571b7b,ssGetOutputPortWidth(S,z0add1d1c25));ssWarning(S,msg);}}static void mdlInitializeSampleTimes(SimStruct*S){ssSetSampleTime(S,(0x326+5045-0x16db),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x302+285-0x41f),FIXED_IN_MINOR_STEP_OFFSET);}static void sg_ModelLoad(SimStruct*S){
#ifndef MATLAB_MEX_FILE
#endif
}static void sg_ModelStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
#endif
}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint8_t*z32ef2da131=(uint8_t*)ssGetOutputPortSignal(S,(0x9d4+1999-0x11a3));uint8_t*zc945663db3=(uint8_t*)ssGetInputPortSignal(S,(0x1258+4113-0x2269));int z7af9cda755=ssGetInputPortWidth(S,(0x108b+1233-0x155c));switch(ssGetInputPortDataType(S,(0x14d3+3764-0x2387))){case(0x22b7+901-0x263c):z7af9cda755*=(0x25f+7897-0x2130);break;case(0xac1+831-0xdff):z7af9cda755*=(0x49a+3321-0x118f);break;case(0x15a3+1225-0x1a6a):z7af9cda755*=(0x521+8007-0x2467);break;case(0x807+4597-0x19f9):z7af9cda755*=(0x943+522-0xb4c);break;case(0x8f1+7307-0x2578):z7af9cda755*=(0x2c7+4978-0x1637);break;case(0xd12+588-0xf59):z7af9cda755*=(0x1231+1455-0x17de);break;case(0x7a7+7306-0x242b):z7af9cda755*=(0x71b+5806-0x1dc5);break;case(0x82c+7047-0x23ac):z7af9cda755*=(0x1590+2640-0x1fdc);break;case(0x17bf+2134-0x200d):z7af9cda755*=(0x3a8+926-0x745);break;}if((ssGetInputPortDataType(S,(0x17ac+3508-0x2560))==SS_DOUBLE)&&(ssGetOutputPortWidth(S,(0x1c36+2651-0x2691))<(0x7a1+6368-0x2079))){double z7be9105675,*z5bafefb1fb=(double*)ssGetInputPortSignal(S,(0x1be0+2465-0x2581));uint64_t input;z7be9105675=z5bafefb1fb[(0x6d9+663-0x970)];input=(uint64_t)z7be9105675;memcpy(z32ef2da131,&input,ssGetOutputPortWidth(S,(0x2e4+8394-0x23ae)));}else if((ssGetInputPortDataType(S,(0x1790+962-0x1b52))==SS_SINGLE)&&(ssGetOutputPortWidth(S,(0x81c+4306-0x18ee))<(0xa91+6013-0x220a))){float z7be9105675,*z5bafefb1fb=(float*)ssGetInputPortSignal(S,(0xf50+4524-0x20fc));uint32_t input;z7be9105675=z5bafefb1fb[(0xd9f+2388-0x16f3)];input=(uint32_t)z7be9105675;memcpy(z32ef2da131,&input,ssGetOutputPortWidth(S,(0x5dc+3544-0x13b4)));}else{if(z7af9cda755<ssGetOutputPortWidth(S,(0x1a7+4322-0x1289))){memcpy(z32ef2da131,zc945663db3,z7af9cda755);}else{memcpy(z32ef2da131,zc945663db3,ssGetOutputPortWidth(S,(0xdb+2659-0xb3e)));}}
#endif
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE
#endif  
}
#include "sg_sfcn_glue.h"   

