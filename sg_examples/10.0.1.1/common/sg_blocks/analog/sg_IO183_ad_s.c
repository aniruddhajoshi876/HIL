// Copyright 2006-2026 Speedgoat GmbH

#define     S_FUNCTION_LEVEL    (0x75d+2861-0x1288)
#undef      S_FUNCTION_NAME
#define     S_FUNCTION_NAME     sg_IO183_ad_s
#include "sg_IO183.h"
#include "sg_callback_legacy.h"
#include "sg_printf.h"
#define DEBUG (0x562+7411-0x2255)
#define ze13f49a01f           ssGetSFcnParam(S, (0x7e9+2650-0x1243))    
#define z702a26a5e9                ssGetSFcnParam(S, (0x7f9+4921-0x1b31))    
#define z3832b85a32           ssGetSFcnParam(S, (0x27d+5393-0x178c))
#define z0015209c28      ssGetSFcnParam(S, (0xdd2+4615-0x1fd6))
#define z25e7e9d55f     ssGetSFcnParam(S, (0x9d2+2217-0x1277))
#define zdf24515981                        (   (0x1cac+1824-0x23c7))
#define ze476b8046d       ((0x1d0c+682-0x1fb6))
#define zc37b9bd51f     ((0x35b+3588-0x115e))
#define z946edd4b97    ((0x116a+4927-0x24a7))
#define z4e1dcb8e78   ((0x17d0+3452-0x2549))
#define z05881e5c9f  ((0x709+4406-0x183b))
#define z2e6483d505      ((0xfcb+4099-0x1fc9))
#define zc5ce4cb81a      ((0xb3+9426-0x2585))
#define z4991bf82ec       ((0x1260+3288-0x1f38))
#define z2b17e2ee3b      ((0x1765+3465-0x24ed))
static char_T msg[(0xafa+6288-0x228a)];static void mdlInitializeSizes(SimStruct*S){uint32_T i,z68c505c5e0;uint8_T z9874ec47f8,z8eed94f548;z8eed94f548=(int_T)mxGetPr(z25e7e9d55f)[(0x60b+6215-0x1e52)]-(0x109f+3425-0x1dff);z9874ec47f8=(int_T)mxGetPr(z0015209c28)[(0x1ac1+504-0x1cb9)]-(0xcc1+334-0xe0e);z68c505c5e0=z8eed94f548-z9874ec47f8+(0xbab+4009-0x1b53);ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x8f6+814-0xc24));ssSetNumDiscStates(S,(0x17f4+3443-0x2567));ssSetNumInputPorts(S,(0x6f+2682-0xae9));ssSetNumOutputPorts(S,z68c505c5e0);for(i=(0x1986+1487-0x1f55);i<z68c505c5e0;i++){ssSetOutputPortWidth(S,i,(0xcf0+4579-0x1ed2));}ssSetNumSampleTimes(S,(0x1c48+1448-0x21ef));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0xf0f+4304-0x1fdf));ssSetNumNonsampledZCs(S,(0x1dcd+9-0x1dd6));for(i=(0x287+4587-0x1472);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x1328+1176-0x17c0));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0xd43+2078-0x1561)]==-1.0){ssSetSampleTime(S,(0x1386+4446-0x24e4),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x19fd+218-0x1ad7),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0xe91+1650-0x1503),mxGetPr(z3832b85a32)[(0xc7d+6554-0x2617)]);ssSetOffsetTime(S,(0x1aca+2352-0x23fa),0.0);}}
#define MDL_START
static void mdlStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
sg_PCIDevice zeccbadd9b3;uintptr_t z1167769581;uint32_T bus,slot,z3dff973793,z5d2fa37e03;int32_T z0754dd67cc;uint8_T range;if(mxGetN(z702a26a5e9)==(0xb9d+3191-0x1813)){bus=(0xd34+4531-0x1ee7);slot=(int_T)mxGetPr(z702a26a5e9)[(0x6ef+3108-0x1313)];}else{bus=(int_T)mxGetPr(z702a26a5e9)[(0x59c+7113-0x2165)];slot=(int_T)mxGetPr(z702a26a5e9)[(0xa98+1759-0x1176)];}if(sg_findPciDevice(&zeccbadd9b3,DEVNAME,VENDORID,DEVICEID,SUBVENDORID,SUBDEVICEID,(int)mxGetPr(ze13f49a01f)[(0x40c+3822-0x12fa)],bus,slot)){ssSetErrorStatus(S,pSgErrorStr);return;}z1167769581=(uintptr_t)sg_mapIo(&zeccbadd9b3,(0x1a0f+469-0x1be4));range=sg_inpB(z1167769581+(0x1d63+736-0x203b))&(0xfbb+4813-0x2285);switch(range){case(0x1297+1788-0x1993):z0754dd67cc=(0xc31+25-0xc40);break;case(0x1f+5208-0x1476):z0754dd67cc=(0x196a+2282-0x2240);break;case(0x14a2+2259-0x1d73):z0754dd67cc=(0x202+4936-0x1545);break;case(0x7cb+3877-0x16ed):z0754dd67cc=(0x96b+3534-0x172f);break;}z5d2fa37e03=sg_inpB(z1167769581+(0x1374+831-0x16ae))&(0x1e29+1708-0x24ce);z3dff973793=sg_inpB(z1167769581+(0x169b+4104-0x269f))&(0x20c+4220-0x1281);ssSetPWorkValue(S,z4991bf82ec,(void*)z1167769581);ssSetIWorkValue(S,z4e1dcb8e78,z3dff973793);ssSetIWorkValue(S,z05881e5c9f,z5d2fa37e03);ssSetIWorkValue(S,zc37b9bd51f,z0754dd67cc);ssSetIWorkValue(S,z946edd4b97,range);
#endif
}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){
#ifndef MATLAB_MEX_FILE
uint32_T i;uintptr_t z1167769581;uint8_T range;int32_T z0754dd67cc;volatile uint8_T z4650136643,zee7c929a2f;volatile uint8_T zc433c376ef,zf171298cf4;uint16_T z6230f7a200;int16_T z3df970e3b7;real_T*zc0efaa16c3;real_T z3546cf30de;z1167769581=(uintptr_t)ssGetPWorkValue(S,z4991bf82ec);z4650136643=ssGetIWorkValue(S,z4e1dcb8e78);zee7c929a2f=ssGetIWorkValue(S,z05881e5c9f);range=ssGetIWorkValue(S,z946edd4b97);z0754dd67cc=ssGetIWorkValue(S,zc37b9bd51f);z3546cf30de=65536;for(i=z4650136643;i<=zee7c929a2f;i++){if(DEBUG){SG_PRINTF(DEBUG,"\x43\x68\x20\x63\x6f\x75\x6e\x74\x3a\x20\x25\x64" "\n",sg_inpB(z1167769581+(0xce2+5692-0x2318)));}sg_outpB(z1167769581,(0x686+5232-0x1af5));zc433c376ef=(0x373+6883-0x1e56);zf171298cf4=(0x3cc+2264-0xca4);while(sg_inpB(z1167769581+(0x284+6063-0x1a30))!=(0x120d+5272-0x26a5)){}zc433c376ef=sg_inpB(z1167769581);zf171298cf4=sg_inpB(z1167769581+(0xf3d+4874-0x2246));z6230f7a200=(zf171298cf4<<(0xa44+6927-0x254b))|zc433c376ef;zc0efaa16c3=ssGetOutputPortSignal(S,i-z4650136643);if(range<(0xbe6+2160-0x1454)){z3df970e3b7=(int16_T)z6230f7a200;*zc0efaa16c3=((z3df970e3b7/z3546cf30de)*z0754dd67cc);}else{*zc0efaa16c3=((z6230f7a200/z3546cf30de)*z0754dd67cc);}}if(DEBUG){SG_PRINTF(DEBUG,"\x46\x49\x46\x4f\x20\x6c\x65\x76\x65\x6c\x3a\x25\x64" "\n",((sg_inpB(z1167769581+(0x652+2999-0x11c4))<<(0x807+7201-0x2420))|sg_inpB(z1167769581+(0xc98+5551-0x2203))));}
#endif
}static void mdlTerminate(SimStruct*S){}
#ifdef MATLAB_MEX_FILE  
#include "simulink.c"   
#else
#include "cg_sfun.h"    
#endif

