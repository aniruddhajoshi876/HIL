// Copyright 2006-2026 Speedgoat GmbH

#define         S_FUNCTION_LEVEL        (0x620+1512-0xc06)
#undef          S_FUNCTION_NAME
#define         S_FUNCTION_NAME         sg_disable_smi_s
#include        <stddef.h>
#include        <stdlib.h>
#include        "simstruc.h"
#ifdef          MATLAB_MEX_FILE
#include        "mex.h"
#endif
#ifndef         MATLAB_MEX_FILE
#include        <windows.h>
#include        "xpcimports.h"
#endif
#define zdf24515981    ((0x6c9+5103-0x1ab8))
#define zc5ce4cb81a        ((0xf5a+2336-0x187a))
#define z2e6483d505        ((0x8f1+3959-0x1863))
#define z2b17e2ee3b        ((0xd1c+4123-0x1d37))
#define  z8f49cf4196      ((0x94d+4800-0x1c0d))
#define  zf95459c125      ((0xcc3+6592-0x2682))
#define zf24010f582      ((0x900+3362-0x1620))
#define z0f0ee58ec5      ((0x1412+495-0x15fe))
#define z35b267a35d        ((0x17c8+640-0x1a44))
#define z412d1ea254            ((0x480+3462-0x1201))
#define z267a3712d4          ((0xeab+3858-0x1db7))
static char msg[(0x383+8305-0x22f4)];static void z94d4b24eec(short zc430a259a4,short zebca149147);static void mdlInitializeSizes(SimStruct*S){int z26dbd73a5e;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n""\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x180d+2121-0x2056));ssSetNumDiscStates(S,(0x1666+102-0x16cc));ssSetNumInputPorts(S,(0xaa5+1764-0x1189));ssSetNumOutputPorts(S,(0x8b0+5158-0x1cd6));ssSetNumSampleTimes(S,(0x429+4179-0x147b));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x2277+811-0x25a2));ssSetNumNonsampledZCs(S,(0xcef+992-0x10cf));for(z26dbd73a5e=(0x1a83+899-0x1e06);z26dbd73a5e<zdf24515981;z26dbd73a5e++)ssSetSFcnParamNotTunable(S,z26dbd73a5e);ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE|SS_OPTION_PLACE_ASAP);return;}static void mdlInitializeSampleTimes(SimStruct*S){ssSetSampleTime(S,(0x9a8+3758-0x1856),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x1432+3387-0x216d),FIXED_IN_MINOR_STEP_OFFSET);}
#ifndef MATLAB_MEX_FILE
static const struct ze2ec40958f{uint16_T id;const char*zd7653867c6;}zca0e1c304e[]={{9232,"\x38\x32\x38\x30\x31\x41\x41\x5f\x30"},{9248,"\x38\x32\x38\x30\x31\x41\x42\x5f\x30"},{9280,"\x38\x32\x38\x30\x31\x42\x41\x5f\x30"},{9292,"\x38\x32\x38\x30\x31\x42\x41\x5f\x31\x30"},{9296,"\x38\x32\x38\x30\x31\x45\x5f\x30"},{9344,"\x38\x32\x38\x30\x31\x43\x41\x5f\x30"},{9356,"\x38\x32\x38\x30\x31\x43\x41\x5f\x31\x32"},{9408,"\x38\x32\x38\x30\x31\x44\x42\x5f\x30"},{9420,"\x38\x32\x38\x30\x31\x44\x42\x5f\x31\x32"},{9424,"\x38\x32\x38\x30\x31\x45\x42\x5f\x30"},{9633,"\x36\x33\x30\x30\x45\x53\x42\x20\x4c\x49\x42"},{9792,"\x49\x43\x48\x36\x5f\x30"},{9793,"\x49\x43\x48\x36\x5f\x31"},{9794,"\x49\x43\x48\x36\x5f\x32"},{10168,"\x49\x43\x48\x37"},{10512,"\x49\x43\x48\x39"},{10520,"\x49\x43\x48\x39"},{(0x141+6817-0x1be2),NULL}};
#endif
#define BIT(n) ((0x13c7+954-0x1780) << (n))
#define z3014320d12 BIT((0x1101+3636-0x1f35))
#define zb478812b1b BIT((0xc53+2345-0x1579))
#define zde6207d0a1 BIT((0x74c+4434-0x188d))
#define zc85d2e55e9  BIT((0xb91+3618-0x19a1))
#define zf759b7c5fe (z3014320d12 | zb478812b1b | zde6207d0a1 | zc85d2e55e9)
void z4df50f1dda(void){
#ifndef MATLAB_MEX_FILE
uint32_T z9e92215ca6;xpcOutpDW((0xf11+331-0x364),2147483648|((0x8d8+3031-0x1490)<<(0x6f4+3422-0x1447)));z9e92215ca6=xpcInpDW((0x1209+5417-0x1a36));
#endif
}
#define MDL_START
static void mdlStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
int32_T*i=ssGetIWork(S),z812c65ff2f;xpcPCIDevice zeccbadd9b3;struct ze2ec40958f*zb996cda81b;uint32_T z663e47f260;
#include "io_xpcimport.c"
#include "pci_xpcimport.c"
#include "util_xpcimport.c"
if(!xpcIsModelInit()){return;}z4df50f1dda();for(zb996cda81b=zca0e1c304e;zb996cda81b->id>(0x1526+1332-0x1a5a);zb996cda81b++){if(xpcGetPCIDeviceInfo(32902,zb996cda81b->id,XPC_NO_SUB,XPC_NO_SUB,(0xa87+4495-0x1c16),(0x49b+4835-0x175f),&zeccbadd9b3)==(0x15f1+2647-0x2048)){break;}}i[z35b267a35d]=zb996cda81b->id;printf("\x20\x20\x53\x70\x65\x65\x64\x67\x6f\x61\x74\x20\x72\x65\x61\x6c\x2d\x74\x69\x6d\x65\x20\x74\x61\x72\x67\x65\x74\x20\x6d\x61\x63\x68\x69\x6e\x65\x3a" "\n");if(zb996cda81b->id==(0x16e2+2947-0x2265)){printf("\x20\x20\x20\x20\x55\x6e\x73\x75\x70\x70\x6f\x72\x74\x65\x64\x20\x63\x68\x69\x70\x73\x65\x74\x20\x66\x6f\x75\x6e\x64\x21" "\n");printf("\x20\x20\x20\x20\x50\x6f\x74\x65\x6e\x74\x69\x61\x6c\x6c\x79\x20\x6e\x6f\x74\x20\x61\x6c\x6c\x20\x53\x4d\x49\x73\x20\x64\x69\x73\x61\x62\x6c\x65\x64" "\n");return;}else{printf("\x20\x20\x20\x20\x41\x6c\x6c\x20\x53\x4d\x49\x73\x20\x66\x6f\x72\x20\x25\x73\x20\x63\x68\x69\x70\x73\x65\x74\x20\x64\x69\x73\x61\x62\x6c\x65\x64" "\n",zb996cda81b->zd7653867c6);printf("\x20\x20\x20\x20\x52\x65\x61\x6c\x2d\x74\x69\x6d\x65\x20\x62\x65\x68\x61\x76\x69\x6f\x72\x20\x67\x75\x61\x72\x61\x6e\x74\x65\x65\x64" "\n");}xpcOutpDW((0xd2b+8265-0x207c),2147483648|((0x2275+718-0x2524)<<(0x17ef+2379-0x212f))|(0x1ab+4444-0x12c7));z663e47f260=xpcInpDW((0x1307+2309-0xf10))&(uint32_T)((0xb3f+7626-0x270a)<<(0x884+3517-0x163a));i[z8f49cf4196]=z663e47f260+(0x1563+3548-0x230f);i[zf24010f582]=z663e47f260+(0x12f6+3482-0x2064);i[z412d1ea254]=z663e47f260;i[zf95459c125]=(uint32_T)xpcInpDW((uint16_T)i[z8f49cf4196]);i[z0f0ee58ec5]=(uint32_T)xpcInpDW((uint16_T)i[zf24010f582]);xpcOutpDW((uint16_T)i[z8f49cf4196],(uint32_T)i[zf95459c125]&~zf759b7c5fe);xpcOutpDW(((uint16_T)(z663e47f260+(0x12ba+2790-0x1d6c))),65535);
#endif
}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){
#ifndef MATLAB_MEX_FILE
#endif 
}static void mdlTerminate(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_T*i=(uint32_T*)ssGetIWork(S);if(i[z35b267a35d]==(0x259a+11-0x25a5))return;xpcOutpDW((uint16_T)i[z8f49cf4196],i[zf95459c125]);xpcOutpDW((uint16_T)i[zf24010f582],i[z0f0ee58ec5]);
#endif
}
#ifndef MATLAB_MEX_FILE
static void z94d4b24eec(short zc430a259a4,short zebca149147){unsigned long zdcdadfc170;unsigned long z794bbc97f5,z2a39f7dd4f;xpcOutpDW((0xefa+3821-0x10ef),(2147483648|(0x53b+2062-0xd2a)<<(0x208+3222-0xe93)|(0x1221+4162-0x2223)));zdcdadfc170=xpcInpDW((0x1056+467-0x52d));zdcdadfc170&=65408;z794bbc97f5=xpcInpDW((uint16_T)(zdcdadfc170+(0x60c+166-0x682)));z2a39f7dd4f=xpcInpDW((uint16_T)(zdcdadfc170+(0x113c+1909-0x187d)));if(zebca149147==(0x11ad+5122-0x25ae))xpcOutpDW((uint16_T)(zdcdadfc170+(0x218a+1245-0x2633)),4294967295);z2a39f7dd4f=xpcInpDW((uint16_T)(zdcdadfc170+(0x803+4716-0x1a3b)));if(zc430a259a4==(0x560+962-0x921))xpcOutpDW((uint16_T)(zdcdadfc170+(0x15d1+336-0x16f1)),(0x1d2+7230-0x1e10));z794bbc97f5=xpcInpDW((uint16_T)(zdcdadfc170+(0x854+6006-0x1f9a)));}
#endif
#ifdef MATLAB_MEX_FILE  
#include "simulink.c"   
#else
#include "cg_sfun.h"    
#endif

