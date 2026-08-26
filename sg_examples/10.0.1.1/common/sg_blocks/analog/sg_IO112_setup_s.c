// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL    (0xa77+4078-0x1a63)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO112_setup_s
#include "sg_IO112.h"
#include "simstruc.h"
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#else
#include "sg_common.h"
#endif
#include "sg_callback_legacy.h"
#include "sg_printf.h"
#define ze13f49a01f           ssGetSFcnParam(S, (0x465+289-0x586))
#define zd6d6a44c19                 ssGetSFcnParam(S, (0x3d1+5815-0x1a87))
#define z1c6ce8e1bc           ssGetSFcnParam(S, (0x501+4167-0x1546))
#define z702a26a5e9                ssGetSFcnParam(S, (0x68f+1239-0xb63))
#define z2afc595703           ssGetSFcnParam(S, (0x660+1261-0xb49))
#define zea2279958e             ssGetSFcnParam(S, (0x175c+2749-0x2214))
#define z186580de21          ssGetSFcnParam(S, (0xd62+1534-0x135a))
#define z8305e81beb            ssGetSFcnParam(S, (0x6c2+4085-0x16b0))
#define z2f0cae928e        ssGetSFcnParam(S, (0x3db+6893-0x1ec0))
#define zdf24515981                           ((0x1610+2192-0x1e97))
#define zc2f3e0cbc0        ((0x1cf3+388-0x1e77))
#define z2e6483d505              ((0x539+1624-0xb90))
#define z8caad2a8e6              ((0x87d+2290-0x116f))
#define z5bfe7a2613            ((0x1925+1701-0x1fc9))
#define zc5ce4cb81a              ((0xedf+569-0x1116))
#define z0194338df7         ((0xac0+7022-0x262e))
#define z2b17e2ee3b              ((0x58c+294-0x6b1))
#define THRESHOLD               0.5
static char_T msg[(0x1172+3612-0x1e8e)];static void mdlInitializeSizes(SimStruct*S){uint16_T i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x1fb2+711-0x2279));ssSetNumDiscStates(S,(0xed+6348-0x19b9));ssSetNumInputPorts(S,(0x1d34+1256-0x221c));ssSetNumOutputPorts(S,(0xe18+2996-0x19cc));ssSetNumSampleTimes(S,(0x64d+7650-0x242e));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x72+9789-0x26af));ssSetNumNonsampledZCs(S,(0x1424+1210-0x18de));for(i=(0x1eb+4233-0x1274);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x423+4637-0x1640));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE|SS_OPTION_PLACE_ASAP);}static void mdlInitializeSampleTimes(SimStruct*S){ssSetSampleTime(S,(0x892+2250-0x115c),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0xfac+5743-0x261b),FIXED_IN_MINOR_STEP_OFFSET);}
#define MDL_START
static void mdlStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
sg_PCIDevice zeccbadd9b3;int_T bus,slot;uint32_T za0d38ae598;volatile uint32_T*za42cf7dd4a;int i;uint32_T z2c1768fde6,z8b9d33e44f,z0a7ca59f77,z605608625c,z80a2b1bccf;uint32_T z6acd4b4bf9,z37a693f042,zae7c2b43fb;uint32_T zf91d71c6d9=(uint32_T)mxGetPr(z2afc595703)[(0x9ff+3635-0x1832)];if(mxGetN(z702a26a5e9)==(0x16aa+2129-0x1efa)){bus=(0x1760+452-0x1924);slot=(int_T)mxGetPr(z702a26a5e9)[(0x2b+3940-0xf8f)];}else{bus=(int_T)mxGetPr(z702a26a5e9)[(0x2374+335-0x24c3)];slot=(int_T)mxGetPr(z702a26a5e9)[(0x13bd+2430-0x1d3a)];}za0d38ae598=((int_T)mxGetPr(ze13f49a01f)[(0x17c6+2582-0x21dc)]);if(sg_findPciDevice(&zeccbadd9b3,DEVNAME,VENDORID,DEVICEID,SUBVENDORID,SUBDEVICEID,za0d38ae598,bus,slot)){ssSetErrorStatus(S,pSgErrorStr);return;}za42cf7dd4a=(volatile uint32_T*)sg_mapMemory(&zeccbadd9b3,(0x4e8+6439-0x1e0d));ssSetPWorkValue(S,z0194338df7,(uint32_T*)za42cf7dd4a);ssSetIWorkValue(S,zc2f3e0cbc0,(uint32_T)zf91d71c6d9);switch((uint16_T)mxGetPr(zea2279958e)[(0xe7c+2993-0x1a2d)]){case(0x5cb+3861-0x14df):z0a7ca59f77=(0x581+2076-0xd9d);z2c1768fde6=(0x415+3175-0x107a);break;case(0x673+6482-0x1fc3):z0a7ca59f77=(0x881+2470-0x1227);z2c1768fde6=(0x338+2119-0xb7e);break;}switch((uint16_T)mxGetPr(z186580de21)[(0x1ad2+2350-0x2400)]){case(0xb70+4307-0x1c42):z8b9d33e44f=(0x1001+546-0x1223);break;case(0x49b+1307-0x9b4):z8b9d33e44f=(0x1a98+2248-0x235f);break;case(0x214+4098-0x1213):z8b9d33e44f=(0x5cf+7941-0x24d2);break;}if((uint16_T)mxGetPr(z1c6ce8e1bc)[(0xe9f+2859-0x19ca)]==(0xf99+5136-0x23a8)){z605608625c=(0x110a+3421-0x1e67);z80a2b1bccf=(0x890+4114-0x189f);}else{z605608625c=(0xd8+2937-0xc51);z80a2b1bccf=(0x1158+22-0x116e);}if(((uint16_T)mxGetPr(z8305e81beb)[(0xadc+2839-0x15f3)]==(0x8e7+4871-0x1bed))){z37a693f042=(0x2106+378-0x227f);}else{z37a693f042=(0xb81+5357-0x206e);}if((uint16_T)mxGetPr(z2f0cae928e)[(0x1ae6+2477-0x2493)]==(0x18a0+3508-0x2653)){z6acd4b4bf9=(0x115c+3423-0x1eba);zae7c2b43fb=(0xee9+4310-0x1fbf);}else{z6acd4b4bf9=(0x1aa+4015-0x1159);zae7c2b43fb=(0xd35+5282-0x21d6);}if(z6acd4b4bf9==(0xc5d+2322-0x156e)){if((za42cf7dd4a[(0x283+8161-0x225a)]&1048576)==(0xc7a+664-0xf12)){sprintf(msg,"\x25\x73\x20\x5b\x62\x75\x73\x3a\x20\x25\x64\x2c\x20\x73\x6c\x6f\x74\x3a\x20\x25\x64\x5d\x3a\x20\x31\x38\x2d\x62\x69\x74\x20\x72\x65\x73\x6f\x6c\x75\x74\x69\x6f\x6e\x20\x69\x73\x20\x6e\x6f\x74\x20\x73\x75\x70\x70\x6f\x72\x74\x65\x64\x20\x6f\x6e\x20\x74\x68\x69\x73\x20\x64\x65\x76\x69\x63\x65\x20\x28\x6e\x61\x74\x69\x76\x65\x20\x31\x36\x2d\x62\x69\x74\x20\x6f\x6e\x6c\x79\x29",DEVNAME,zeccbadd9b3.bus,zeccbadd9b3.slot);ssSetErrorStatus(S,msg);return;}}za42cf7dd4a[(0xfa8+475-0x1183)]=(0x166a+2602-0x2054)|(z2c1768fde6<<(0x1397+4370-0x24a5))|(zae7c2b43fb<<(0x817+6198-0x203b));za42cf7dd4a[(0x13a3+4495-0x252a)]=(0x304+5324-0x17c9)|(z80a2b1bccf<<(0x1034+5470-0x258f))|(z37a693f042<<(0x1161+4105-0x215f));za42cf7dd4a[(0x1504+1006-0x18e9)]=((uint8_T)zf91d71c6d9-(0x89d+5356-0x1d88))<<(0xd14+110-0xd7a);za42cf7dd4a[(0x4a0+8352-0x2532)]=(0x1cad+1152-0x212c);za42cf7dd4a[(0x162b+4303-0x26eb)]=(0x11e7+4964-0x254a);za42cf7dd4a[(0x582+5521-0x1b10)]=za42cf7dd4a[(0xa9d+5155-0x1ebd)]|262144;for(i=(0xb2+507-0x2ad);za42cf7dd4a[(0x1a2+7133-0x1d7c)]&262144;i++){if(i>1193000.0*1.0){sprintf(msg,"\x25\x73\x20\x66\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x63\x6c\x65\x61\x72\x20\x61\x6e\x61\x6c\x6f\x67\x20\x69\x6e\x70\x75\x74\x20\x46\x49\x46\x4f",DEVNAME);ssSetErrorStatus(S,msg);return;}}za42cf7dd4a[(0x18d9+2802-0x23c8)]=(0x1091+4619-0x229c)|(z6acd4b4bf9<<(0x21a9+892-0x2511));if(sg_isModelInit()&&((int)mxGetPr(zd6d6a44c19)[(0xa3c+6593-0x23fd)]==(0xb9f+686-0xe4c))){za42cf7dd4a[(0x1854+1320-0x1d7c)]=(0x2652+959-0xa11)|za42cf7dd4a[(0x3a+9240-0x2452)];SG_PRINTF(INFO,"\x25\x73\x20\x61\x75\x74\x6f\x63\x61\x6c\x69\x62\x72\x61\x74\x69\x6f\x6e\x20\x73\x74\x61\x72\x74\x65\x64\x2e\x2e" "\n",DEVNAME);for(i=(0x6c1+1811-0xdd4);za42cf7dd4a[(0x69b+4690-0x18ed)]&(0x22d4+6967-0x1e0b);i++){if(i>1193000.0*5.0){sprintf(msg,"\x25\x73\x20\x61\x75\x74\x6f\x63\x61\x6c\x69\x62\x72\x61\x74\x69\x6f\x6e\x20\x74\x69\x6d\x65\x64\x20\x6f\x75\x74",DEVNAME);ssSetErrorStatus(S,msg);return;}}SG_PRINTF(INFO,
"\x25\x73\x20\x61\x75\x74\x6f\x63\x61\x6c\x69\x62\x72\x61\x74\x69\x6f\x6e\x20\x73\x75\x63\x63\x65\x65\x64\x65\x64\x2e" "\n",DEVNAME);}if(!sg_isModelInit()){za42cf7dd4a[(0x34b+313-0x47c)]=(0x744+746-0xa0e)|za42cf7dd4a[(0x1437+1016-0x1827)];}
#endif
}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){}static void mdlTerminate(SimStruct*S){
#ifndef MATLAB_MEX_FILE
volatile uint32_T*za42cf7dd4a=ssGetPWorkValue(S,z0194338df7);if(!sg_isModelInit()){za42cf7dd4a[(0x5a2+5469-0x1af7)]=~((0xedd+6194-0x26ef))&za42cf7dd4a[(0xbcc+4974-0x1f32)];}
#endif
}
#include "sg_sfcn_glue.h"   

