// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL        (0xc00+950-0xfb4)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME         sg_IO103_setup_s
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include "simstruc.h"
#include "sg_callback_legacy.h"
#include "sg_printf.h"
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#else
#include "sg_common.h"
#endif
#define DEVNAME     "\x53\x70\x65\x65\x64\x67\x6f\x61\x74\x20\x49\x4f\x31\x30\x33"
#define VENDORID    (0x1305+6157-0x1a5d)
#define DEVICEID    36992
#define SUBVENDORID (0x169f+3910-0x1530)
#define SUBDEVICEID 10361
#define ze13f49a01f           ssGetSFcnParam(S, (0x1011+1172-0x14a5))
#define z8fd86139be               ssGetSFcnParam(S, (0x15c0+521-0x17c8))
#define zd6d6a44c19                 ssGetSFcnParam(S, (0x18b4+1584-0x1ee2))
#define z702a26a5e9                ssGetSFcnParam(S, (0x15ed+3580-0x23e6))
#define z2afc595703           ssGetSFcnParam(S, (0x515+4268-0x15bd))
#define z186580de21          ssGetSFcnParam(S, (0x247+4802-0x1504))
#define z79b944ae89           ssGetSFcnParam(S, (0xa2+7142-0x1c82))
#define za6b3fb79a3             ssGetSFcnParam(S, (0x5a0+691-0x84c))
#define z5317f28eb6           ssGetSFcnParam(S, (0x83b+5406-0x1d51))
#define zb18e38a301           ssGetSFcnParam(S, (0x1fe6+784-0x22ed))
#define z5bc3ce0d50           ssGetSFcnParam(S, (0x213+451-0x3cc))
#define z1f9bebb47b             ssGetSFcnParam(S, (0x79+5081-0x1447))
#define z2d8f240c11           ssGetSFcnParam(S, (0x76+9632-0x260a))
#define zdf24515981                           ((0x53f+718-0x800))
#define zc2f3e0cbc0        ((0x2c5+5181-0x1702))
#define z2e6483d505              ((0x22b2+1102-0x26ff))
#define z8caad2a8e6              ((0xaeb+6852-0x25af))
#define z5bfe7a2613            ((0x1c99+168-0x1d40))
#define zc5ce4cb81a              ((0x2020+183-0x20d5))
#define z0194338df7         ((0x5bf+353-0x720))
#define z2b17e2ee3b              ((0x1f2+2982-0xd97))
#define THRESHOLD               0.5
static char_T msg[(0x1fda+123-0x1f55)];static void mdlInitializeSizes(SimStruct*S){uint16_T i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x56d+2947-0x10f0));ssSetNumDiscStates(S,(0x500+4053-0x14d5));ssSetNumInputPorts(S,(0xd87+886-0x10fd));ssSetNumOutputPorts(S,(0xa85+2341-0x13aa));ssSetNumSampleTimes(S,(0x23b7+277-0x24cb));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x8a7+876-0xc13));ssSetNumNonsampledZCs(S,(0x1c2d+1668-0x22b1));for(i=(0x92c+7405-0x2619);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x1c09+1905-0x237a));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE|SS_OPTION_PLACE_ASAP);}static void mdlInitializeSampleTimes(SimStruct*S){ssSetSampleTime(S,(0x1fa6+789-0x22bb),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x384+3248-0x1034),FIXED_IN_MINOR_STEP_OFFSET);}
#define MDL_START
static void mdlStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
sg_PCIDevice zeccbadd9b3;int_T bus,slot;int i;uint32_T za0d38ae598;volatile uint32_T*za42cf7dd4a;uint32_T range,z8b9d33e44f,out;uint32_T zf91d71c6d9=(uint32_T)mxGetN(z2afc595703);if(mxGetN(z702a26a5e9)==(0x16cd+384-0x184c)){bus=(0x480+6882-0x1f62);slot=(int_T)mxGetPr(z702a26a5e9)[(0x819+3267-0x14dc)];}else{bus=(int_T)mxGetPr(z702a26a5e9)[(0xe9f+1311-0x13be)];slot=(int_T)mxGetPr(z702a26a5e9)[(0x5f+8347-0x20f9)];}za0d38ae598=((int_T)mxGetPr(ze13f49a01f)[(0x1086+4468-0x21fa)]);if(sg_findPciDevice(&zeccbadd9b3,DEVNAME,VENDORID,DEVICEID,SUBVENDORID,SUBDEVICEID,za0d38ae598,bus,slot)){ssSetErrorStatus(S,pSgErrorStr);return;}za42cf7dd4a=sg_mapMemory(&zeccbadd9b3,(0x16ed+3397-0x2430));ssSetPWorkValue(S,z0194338df7,(uint32_T*)za42cf7dd4a);ssSetIWorkValue(S,zc2f3e0cbc0,zf91d71c6d9);switch((uint16_T)mxGetPr(z8fd86139be)[(0xe96+2973-0x1a33)]){case(0x9db+6399-0x22d9):ssSetRWorkValue(S,z8caad2a8e6,3276.8);ssSetRWorkValue(S,z5bfe7a2613,10.0);range=(0x2034+20-0x2046);break;case(0x21cb+1027-0x25cc):ssSetRWorkValue(S,z8caad2a8e6,6553.6);ssSetRWorkValue(S,z5bfe7a2613,5.0);range=(0xbc1+2863-0x16ef);break;case(0xf22+4560-0x20ef):ssSetRWorkValue(S,z8caad2a8e6,13107.2);ssSetRWorkValue(S,z5bfe7a2613,2.5);range=(0x264+3510-0x101a);break;}if((uint16_T)mxGetPr(z186580de21)[(0x122b+2756-0x1cef)]==(0xdf3+3506-0x1ba4)){z8b9d33e44f=(0x16e7+1028-0x1aeb);}else{z8b9d33e44f=(0xf57+2679-0x19cd);}za42cf7dd4a[(0x147d+996-0x1861)]=(0x1edb+192-0x1c5b)|(range<<(0x1cd4+335-0x1e1f))|z8b9d33e44f;out=(0x1672+2900-0x1eea);switch(zf91d71c6d9){case(0x1142+4064-0x2121):out|=(0xc09+1239-0x8e0)|(((uint32_T)mxGetPr(z2afc595703)[(0x22ec+164-0x2390)]-(0xcb1+5487-0x221f))<<(0x4b8+4122-0x14c6));break;case(0x8df+1354-0xe27):out|=131072;break;case(0x1df+8954-0x24d5):out|=(0x11b0+884-0x1524);break;case(0x8f1+3712-0x1769):out|=(0xd0d+2699-0x1797);break;case(0x6ca+5965-0x1e07):out|=(0x39c+9074-0x270c);break;case(0x10a3+292-0x11a7):out|=(0xa7+5488-0x1614);break;}za42cf7dd4a[(0x526+3938-0x1480)]=out;za42cf7dd4a[(0xda0+4736-0x201d)]=32768;for(i=(0x700+5851-0x1ddb);za42cf7dd4a[(0x429+1370-0x980)]&32768;i++){if(i>1193000.0*1.0){sprintf(msg,"\x20\x20\x25\x73\x20\x66\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x63\x6c\x65\x61\x72\x20\x61\x6e\x61\x6c\x6f\x67\x20\x69\x6e\x70\x75\x74\x20\x46\x49\x46\x4f",DEVNAME);ssSetErrorStatus(S,msg);return;}}za42cf7dd4a[(0x46b+5984-0x1bc8)]=(0x7f+6699-0x1aaa);if(sg_isModelInit()&&((int)mxGetPr(zd6d6a44c19)[(0x491+8729-0x26aa)]==(0x79+4911-0x13a7))){za42cf7dd4a[(0x4bf+674-0x761)]=8192;SG_PRINTF(INFO,"\x25\x73\x20\x61\x75\x74\x6f\x63\x61\x6c\x69\x62\x72\x61\x74\x69\x6f\x6e\x20\x73\x74\x61\x72\x74\x65\x64\x2e\x2e" "\n",DEVNAME);for(i=(0xbc+247-0x1b3);za42cf7dd4a[(0xde8+3457-0x1b69)]&8192;i++){if(i>1193000.0*7.0){sprintf(msg,"\x25\x73\x20\x61\x75\x74\x6f\x63\x61\x6c\x69\x62\x72\x61\x74\x69\x6f\x6e\x20\x74\x69\x6d\x65\x64\x20\x6f\x75\x74",DEVNAME);ssSetErrorStatus(S,msg);return;}}if(za42cf7dd4a[(0xafa+2468-0x149e)]&16384){SG_PRINTF(INFO,"\x25\x73\x20\x61\x75\x74\x6f\x63\x61\x6c\x69\x62\x72\x61\x74\x69\x6f\x6e\x20\x73\x75\x63\x63\x65\x65\x64\x65\x64\x2e" "\n",DEVNAME);}else{sprintf(msg,"\x25\x73\x20\x61\x75\x74\x6f\x63\x61\x6c\x69\x62\x72\x61\x74\x69\x6f\x6e\x20\x66\x61\x69\x6c\x65\x64",DEVNAME);ssSetErrorStatus(S,msg);return;}}
#endif
}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){}static void mdlTerminate(SimStruct*S){
#ifndef MATLAB_MEX_FILE
volatile uint32_T*za42cf7dd4a=ssGetPWorkValue(S,z0194338df7);uint16_T zf91d71c6d9=(uint16_T)mxGetN(z79b944ae89);real_T z0754dd67cc=ssGetRWorkValue(S,z8caad2a8e6);real_T offset=ssGetRWorkValue(S,z5bfe7a2613);uint16_T i;int32_T out;uint16_T channel;uint16_T first=(0x888+6436-0x21ab);uint32_T z718c4c15f4;if(sg_isModelInit()){for(i=(0x1361+1835-0x1a8c);i<(0x1ff3+1702-0x2691);i++){if(first){first=(0x1126+5409-0x2647);}else{za42cf7dd4a[(0x18cb+3411-0x2618)]=out|(channel<<(0xb8f+3517-0x193c));}channel=i;out=(int32_T)((0.0+offset)*z0754dd67cc);if(out>65535){out=65535;}if(out<(0x137f+3747-0x2222)){out=(0x8da+123-0x955);}}za42cf7dd4a[(0x10ad+4505-0x2240)]=out|(channel<<(0x5e8+5185-0x1a19))|1572864;za42cf7dd4a[(0x15c+549-0x381)]=za42cf7dd4a[(0x748+370-0x8ba)]|(0xbe6+1564-0xa02);}first=(0x7d4+5423-0x1d02);for(i=(0x2160+1423-0x26ef);i<zf91d71c6d9;i++){if(sg_isModelInit()||(int)mxGetPr(za6b3fb79a3)[i]){if(first){first=(0x536+8330-0x25c0);}else{za42cf7dd4a[(0xf7+4919-0x1428)]=out|(channel<<(0x723+2318-0x1021));}channel=(uint16_T)mxGetPr(z79b944ae89)[i]-(0x1bd3+1829-0x22f7);out=(int32_T)(((real_T)mxGetPr(z5317f28eb6)[i]+offset)*z0754dd67cc);if(out>65535){out=65535;}if(out<(0x5f3+7031-0x216a)){out=(0x50a+1454-0xab8);}}}if(first==(0xf7+3190-0xd6d)){za42cf7dd4a[(0xe65+3524-0x1c23)]=out|(channel<<(0xa2+1048-0x4aa))|1572864;za42cf7dd4a[(0x113+7623-0x1eda)]=za42cf7dd4a[(0x312+5705-0x195b)]|(0x1299+2418-0x140b);}z718c4c15f4=(0x96d+6928-0x247d);for(i=(0x1576+1352-0x1abe);i<(uint16_T)mxGetPr(z5bc3ce0d50)[i];i++){if(sg_isModelInit()||(int)mxGetPr(z1f9bebb47b)[i]){channel=(uint32_T)mxGetPr(z5bc3ce0d50)[i]-(0x10a8+4820-0x237b);out=(int32_T)mxGetPr(z2d8f240c11)[i];if(out>=THRESHOLD){z718c4c15f4|=(0x15b8+3551-0x2396)<<channel;}}}za42cf7dd4a[(0x15c1+1725-0x1c75)]=z718c4c15f4;
#endif
}
#include "sg_sfcn_glue.h"   

