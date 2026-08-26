// Copyright 2006-2026 Speedgoat GmbH

#define     S_FUNCTION_LEVEL    (0x6eb+2965-0x127e)
#undef      S_FUNCTION_NAME
#define     S_FUNCTION_NAME     sg_IO101_ad_s
#include    <stddef.h>
#include    <stdlib.h>
#include    <stdbool.h>
#include    "simstruc.h"
#ifdef      MATLAB_MEX_FILE
#include    "mex.h"
#endif
#ifndef         MATLAB_MEX_FILE
#include        "sg_common.h"
#endif
#include "include/sg_io101_regs.h"
#include "sg_callback_legacy.h"
#include "sg_printf.h"
#define DEVNAME "\x53\x70\x65\x65\x64\x67\x6f\x61\x74\x20\x49\x4f\x31\x30\x31"
#define VENDORID (0x1a4d+6977-0x1eb9)
#define DEVICEID 17495
#define zb700a21e90 (0x239+4142-0x1167)
#define z405bc1a59d
#define zdf24515981          ((0x14ef+4075-0x24d0))
#define z7abddc8aad       ssGetSFcnParam(S,(0xc53+154-0xced))
#define z37c3cb7f0a         ssGetSFcnParam(S,(0xeb9+3611-0x1cd3))
#define z8e37b80355            ssGetSFcnParam(S,(0x38a+6845-0x1e45))
#define z8fd86139be               ssGetSFcnParam(S,(0x32+4320-0x110f))
#define z6e0dbe056e            ssGetSFcnParam(S,(0x9cc+2524-0x13a4))
#define z440bc5d441           ssGetSFcnParam(S,(0x8f5+6520-0x2268))
#define z3832b85a32           ssGetSFcnParam(S,(0x10b9+1649-0x1724))
#define z702a26a5e9                ssGetSFcnParam(S,(0x20f9+1322-0x261c))
#define z6b1a64c92c             ssGetSFcnParam(S,(0x143f+307-0x156a))
#define ze13f49a01f           ssGetSFcnParam(S,(0x14a7+2457-0x1e37))
#define z2e6483d505              ((0xec5+2251-0x178b))
#define zc65b792f40     ((0x2e5+8876-0x2591))
#define z5301267c3b      ((0x476+2514-0xe47))
#define z68983ebba8          ((0x219c+632-0x2412))
#define zbe66eb8546         ((0x2f8+1194-0x79f))
#define z43cf08dd43             ((0x3a0+1992-0xb64))
#define zc5ce4cb81a              ((0x91a+7255-0x256f))
#define z8caad2a8e6              ((0x1558+4423-0x269f))
#define z5bfe7a2613            ((0x995+4627-0x1ba7))
#define z2b17e2ee3b              ((0x2f4+1008-0x6e3))
#define z0194338df7         ((0xeac+5400-0x23c4))
static char_T msg[(0x8fa+4101-0x17ff)];
#ifndef MATLAB_MEX_FILE
static void z14abefc6ac(volatile uint32_T*za42cf7dd4a,SimStruct*S){int i;for(i=(0x1673+697-0x192c);!(za42cf7dd4a[ze4eca519da]&(0x15ac+3851-0x24b6));i++){if(i>100000){sprintf(msg,"\x25\x73\x20\x63\x61\x6c\x69\x62\x72\x61\x74\x69\x6f\x6e\x20\x64\x61\x74\x61\x20\x72\x65\x74\x72\x69\x65\x76\x61\x6c\x20\x74\x69\x6d\x65\x64\x20\x6f\x75\x74",DEVNAME);ssSetErrorStatus(S,msg);return;}sg_wait_ns((0xfd0+6919-0x26ef));}}
#endif
static void mdlInitializeSizes(SimStruct*S){uint32_T i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0xc7+7978-0x1ff1));ssSetNumDiscStates(S,(0x183b+3630-0x2669));ssSetNumInputPorts(S,(0x2df+726-0x5b5));switch((int32_T)mxGetPr(z440bc5d441)[(0x1c95+872-0x1ffd)]-(0x312+3887-0x1240)){case(0x911+6905-0x240a):ssSetNumOutputPorts(S,(int32_T)mxGetPr(z37c3cb7f0a)[(0xfc5+1126-0x142b)]);for(i=(0xbff+2114-0x1441);i<(uint32_T)mxGetPr(z37c3cb7f0a)[(0x63+798-0x381)];i++){ssSetOutputPortWidth(S,i,(0x1adb+597-0x1d2f));}break;case(0x8a0+4302-0x196d):ssSetNumOutputPorts(S,(int32_T)mxGetPr(z37c3cb7f0a)[(0x748+3148-0x1394)]+(0x75c+2776-0x1233));for(i=(0x1d79+1561-0x2392);i<(uint32_T)mxGetPr(z37c3cb7f0a)[(0x6bc+3231-0x135b)]+(0x211+6940-0x1d2c);i++){ssSetOutputPortWidth(S,i,(0xffb+4734-0x2278));}break;}ssSetNumSampleTimes(S,(0x6db+5968-0x1e2a));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x95c+2531-0x133f));ssSetNumNonsampledZCs(S,(0x1bd+1500-0x799));for(i=(0x20e5+419-0x2288);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x1478+2982-0x201e));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x6a2+7631-0x2471)]==-1.0){ssSetSampleTime(S,(0x86d+5344-0x1d4d),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x1a0+4174-0x11ee),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0xbfb+1402-0x1175),mxGetPr(z3832b85a32)[(0x82+8728-0x229a)]);ssSetOffsetTime(S,(0x375+8620-0x2521),0.0);}}
#define MDL_START
static void mdlStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
sg_PCIDevice zeccbadd9b3;volatile uint32_T*za42cf7dd4a;volatile uint8_T*z3283caa368;uint32_T i;uint8_T z34c68d4df7,z979d8f17a3;uint8_T zd254bf6903,z2a78d7bb7c,first;real_T zd7ed04e88c,z1d52f1a257;real_T za8a33144e7[(0x708+6721-0x2144)];uint32_T z32f0d7e7fd,z77a6329c73;uint32_T zd5317f54d8,zcadf9c54a7,z9fc7e38097;real_T z0754dd67cc;int moduleId=(int)mxGetScalar(ze13f49a01f);void*bar0ptr;if((int_T)mxGetPr(z702a26a5e9)[(0x1595+2340-0x1eb9)]<(0x35f+7182-0x1f6d)){if(sg_findPciDevice(&zeccbadd9b3,DEVNAME,VENDORID,DEVICEID,SG_NO_SUB,SG_NO_SUB,moduleId,SG_NO_BUS_SLOT,SG_NO_BUS_SLOT)){ssSetErrorStatus(S,pSgErrorStr);return;}}else{uint16_T bus,slot;if(mxGetN(z702a26a5e9)==(0x635+6359-0x1f0b)){bus=(0x3a8+5403-0x18c3);slot=(uint16_T)mxGetPr(z702a26a5e9)[(0xa6f+6450-0x23a1)];}else{bus=(uint16_T)mxGetPr(z702a26a5e9)[(0x1fdb+1720-0x2693)];slot=(uint16_T)mxGetPr(z702a26a5e9)[(0xc53+5257-0x20db)];}if(sg_findPciDevice(&zeccbadd9b3,DEVNAME,VENDORID,DEVICEID,SG_NO_SUB,SG_NO_SUB,moduleId,bus,slot)){ssSetErrorStatus(S,pSgErrorStr);return;}}bar0ptr=sg_mapMemory(&zeccbadd9b3,(0xb0d+5925-0x2232));za42cf7dd4a=(volatile uint32_T*)bar0ptr;z3283caa368=(volatile uint8_T*)bar0ptr;ssSetPWorkValue(S,z0194338df7,(void*)za42cf7dd4a);z34c68d4df7=(uint8_T)mxGetPr(z7abddc8aad)[(0x487+1714-0xb39)]-(0x12fa+4828-0x25d5);ssSetIWorkValue(S,zc65b792f40,z34c68d4df7);z979d8f17a3=(uint8_T)mxGetPr(z37c3cb7f0a)[(0x29d+3086-0xeab)];ssSetIWorkValue(S,z5301267c3b,z979d8f17a3);z2a78d7bb7c=(uint8_T)mxGetPr(z6e0dbe056e)[(0x1f94+934-0x233a)]-(0xbb9+4750-0x1e46);ssSetIWorkValue(S,z68983ebba8,z2a78d7bb7c);zd254bf6903=(uint8_T)mxGetPr(z440bc5d441)[(0xe3c+4108-0x1e48)]-(0xb0b+6638-0x24f8);ssSetIWorkValue(S,zbe66eb8546,zd254bf6903);first=(0xc9d+56-0xcd4);ssSetIWorkValue(S,z43cf08dd43,first);switch((int32_T)mxGetPr(z8fd86139be)[(0xd2+4114-0x10e4)]-(0x10f1+2855-0x1c17)){case(0x164f+3809-0x2530):z32f0d7e7fd=(0x10a+7462-0x1e2e);z77a6329c73=(0x8fc+1120-0xd58);zcadf9c54a7=(0x5c7+4223-0x1641);z9fc7e38097=(0x1b51+929-0x1eeb);break;case(0x747+7701-0x255b):z32f0d7e7fd=(0xe6c+5836-0x2537);z77a6329c73=(0x32a+2127-0xb75);zcadf9c54a7=(0x453+3934-0x13ad);z9fc7e38097=(0x483+5819-0x1b37);break;case(0x142b+2930-0x1f9b):z32f0d7e7fd=(0xe29+892-0x11a5);z77a6329c73=(0x1b6f+2384-0x24bb);zcadf9c54a7=(0xa8f+5073-0x1e5d);z9fc7e38097=(0xfc7+4517-0x2165);break;case(0x53+3416-0xda8):z32f0d7e7fd=(0x418+946-0x7c9);z77a6329c73=(0x1ba9+988-0x1f82);zcadf9c54a7=(0xbc5+42-0xbeb);z9fc7e38097=(0x37b+8724-0x2589);break;case(0x1106+2531-0x1ae5):z32f0d7e7fd=(0x2316+813-0x2643);z77a6329c73=(0x10b8+3200-0x1d35);zcadf9c54a7=(0xca6+1487-0x1272);z9fc7e38097=(0xd88+2663-0x17e9);break;}switch((int32_T)mxGetPr(z8e37b80355)[(0x59+5786-0x16f3)]-(0x1967+1901-0x20d3)){case(0xdf+4130-0x1101):zd5317f54d8=(0xd1b+3087-0x192a);break;case(0x3c0+6440-0x1ce7):zd5317f54d8=(0x1b25+2699-0x25af);break;}{char_T current;char_T str[(0x5a6+6983-0x20dd)];uint16_T index;uint32_T z548bd6fb7c;for(i=(0x8bd+5572-0x1e81);i<(0x1d82+2142-0x25dc);i++){index=(0x2297+424-0x243f);current=(0x539+6095-0x1d07);z548bd6fb7c=(0x84c+7459-0x254f)+i*(0x14d8+3691-0x2333);while(current!='\0'){za42cf7dd4a[z16268937aa]=((0x583+6911-0x2081)<<(0x647+6464-0x1f78))|(z548bd6fb7c<<(0x1127+1674-0x17a9));z14abefc6ac(za42cf7dd4a,S);current=(za42cf7dd4a[ze4eca519da]>>(0x6d6+6157-0x1edb))&(0x1bb8+2373-0x23fe);str[index]=current;index++;z548bd6fb7c++;sg_wait_s(0.001);}za8a33144e7[i]=atof(str);}za8a33144e7[(0x1902+1421-0x1e8b)]=0.0;}z3283caa368[z57c96017d8]=(0xad9+706-0xd9b);z3283caa368[zaae7e51e9f]=(0x4e7+2948-0x106b);za42cf7dd4a[z2121b5b990]=zb700a21e90-(0x538+304-0x667);za42cf7dd4a[zc370fd5091]=8960|(z9fc7e38097<<(0x403+6641-0x1df1));za42cf7dd4a[z93f52f63ec]=(0x464+1289-0x96c);while(!(za42cf7dd4a[zc370fd5091]&32768));za42cf7dd4a[zc370fd5091]=8192|(z9fc7e38097<<(0xf9c+5635-0x259c));zd7ed04e88c=0.0;for(i=zb700a21e90/(0x1cc4+1492-0x2296);i<zb700a21e90;i++){zd7ed04e88c+=(real_T)(int16_T)(za42cf7dd4a[z7873267188+i]&65535);}zd7ed04e88c=zd7ed04e88c/(real_T)zb700a21e90*2.0;za42cf7dd4a[zc370fd5091]=8960|(zcadf9c54a7<<(0xe07+6282-0x268e));za42cf7dd4a[z93f52f63ec]=(0x756+6310-0x1ffb);while(!(
za42cf7dd4a[zc370fd5091]&32768));za42cf7dd4a[zc370fd5091]=8192|(zcadf9c54a7<<(0x1bcd+1823-0x22e9));z1d52f1a257=0.0;for(i=zb700a21e90/(0x1722+318-0x185e);i<zb700a21e90;i++){z1d52f1a257+=(real_T)(int16_T)(za42cf7dd4a[z7873267188+i]&65535);}z1d52f1a257=z1d52f1a257/(real_T)zb700a21e90*2.0;z0754dd67cc=(z1d52f1a257-zd7ed04e88c)/(za8a33144e7[z32f0d7e7fd]-za8a33144e7[z77a6329c73]);ssSetRWorkValue(S,z8caad2a8e6,z0754dd67cc);ssSetRWorkValue(S,z5bfe7a2613,zd7ed04e88c-z0754dd67cc*za8a33144e7[z77a6329c73]);z3283caa368[z57c96017d8]=z34c68d4df7;z3283caa368[zaae7e51e9f]=z34c68d4df7+z979d8f17a3-(0x1611+2026-0x1dfa);za42cf7dd4a[z2121b5b990]=z979d8f17a3-(0xe5b+5017-0x21f3);switch(z2a78d7bb7c){case(0x1ef+977-0x5c0):za42cf7dd4a[zc370fd5091]=(0xfb6+1082-0xff0)|(zd5317f54d8<<(0x687+6213-0x1ec9));break;case(0x1415+4192-0x2474):za42cf7dd4a[zc370fd5091]=(0x1321+1534-0x151d)|(zd5317f54d8<<(0xc2b+4193-0x1c89));za42cf7dd4a[zeefa4afac7]=(0xa67+7654-0x2446);za42cf7dd4a[z531bfdd545]=(uint32_T)mxGetPr(z6b1a64c92c)[(0x1379+3871-0x2298)];za42cf7dd4a[z2645130aea]=(uint32_T)mxGetPr(z6b1a64c92c)[(0x3f2+3931-0x134c)];za42cf7dd4a[zfb07e71feb]=(0xf31+2058-0x173b);break;}
#endif
}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){
#ifndef MATLAB_MEX_FILE
volatile uint32_T*za42cf7dd4a=ssGetPWorkValue(S,z0194338df7);uint8_T z34c68d4df7=ssGetIWorkValue(S,zc65b792f40);uint8_T z979d8f17a3=ssGetIWorkValue(S,z5301267c3b);uint8_T z2a78d7bb7c=ssGetIWorkValue(S,z68983ebba8);uint8_T zd254bf6903=ssGetIWorkValue(S,zbe66eb8546);uint8_T first=ssGetIWorkValue(S,z43cf08dd43);uint8_T z8ceacacbdb;uint16_T i;uint32_T z812c65ff2f;real_T*y;int16_T count;uint8_T channel;uint32_T z7be9105675;real_T z0754dd67cc=ssGetRWorkValue(S,z8caad2a8e6);real_T offset=ssGetRWorkValue(S,z5bfe7a2613);z8ceacacbdb=(0x16ad+332-0x17f8);switch(z2a78d7bb7c){case(0x1412+4009-0x23bb):za42cf7dd4a[z93f52f63ec]=(0x1406+4571-0x25e0);break;case(0x1bad+180-0x1c60):za42cf7dd4a[z630d11f84f]=(0x1bf+6639-0x1bad);if(first){ssSetIWorkValue(S,z43cf08dd43,(0x8a8+876-0xc14));z8ceacacbdb=(0x1c80+1825-0x23a1);}break;}z812c65ff2f=(0x489+5739-0x1af4);if(z8ceacacbdb){while(!(za42cf7dd4a[zc370fd5091]&32768))z812c65ff2f++;}for(i=(0x1842+1042-0x1c54);i<z979d8f17a3;i++){y=ssGetOutputPortSignal(S,i);if(z8ceacacbdb){z7be9105675=za42cf7dd4a[z7873267188+i];count=(int16_T)(z7be9105675&65535);channel=(uint8_T)((z7be9105675>>(0xbe8+5332-0x20ac))&(0x1b30+495-0x1d00));if((i+z34c68d4df7)!=channel){SG_PRINTF(INFO,"\x41\x44\x43\x20\x6d\x65\x6d\x6f\x72\x79\x20\x6f\x72\x64\x65\x72\x20\x70\x72\x6f\x62\x6c\x65\x6d" "\n");}y[(0x1757+2357-0x208c)]=((real_T)count-offset)/z0754dd67cc;}else{y[(0x3a9+6635-0x1d94)]=0.0;}}if(zd254bf6903==(0xa9+7764-0x1efc)){y=ssGetOutputPortSignal(S,i);y[(0x1a96+1509-0x207b)]=(real_T)z812c65ff2f;}
#endif
}static void mdlTerminate(SimStruct*S){
#ifndef MATLAB_MEX_FILE
#endif
}
#include "sg_sfcn_glue.h"   

