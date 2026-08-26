// Copyright 2006-2026 Speedgoat GmbH

#define     S_FUNCTION_LEVEL    (0x2090+1228-0x255a)
#undef      S_FUNCTION_NAME
#define     S_FUNCTION_NAME     sg_IO183_do_s
#include "sg_IO183.h"
#include "sg_callback_legacy.h"
#include "sg_printf.h"
#define ze13f49a01f           ssGetSFcnParam(S, (0x1000+125-0x107d))    
#define z702a26a5e9                ssGetSFcnParam(S, (0x1fc+2814-0xcf9))    
#define z3832b85a32           ssGetSFcnParam(S, (0x129+3089-0xd38))    
#define ze43f97b6ea         ssGetSFcnParam(S, (0xac4+4949-0x1e16))
#define z2ef2842ad3             ssGetSFcnParam(S, (0x1b8+3568-0xfa4))
#define z724139b233            ssGetSFcnParam(S, (0x54f+627-0x7bd))
#define zdf24515981                        (   (0xf4d+214-0x101d))
#define z2e6483d505      ((0xda7+1186-0x1249))
#define zc5ce4cb81a      ((0x1172+4871-0x2479))
#define z4991bf82ec       ((0xb8f+2498-0x1551))
#define z2b17e2ee3b      ((0x9e7+6079-0x21a5))
#define THRESHOLD       0.5
static char_T msg[(0x439+7067-0x1ed4)];static void mdlInitializeSizes(SimStruct*S){uint32_T i;uint8_T zaf49fd5709;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x1e8+7811-0x206b));ssSetNumDiscStates(S,(0x110c+5571-0x26cf));zaf49fd5709=(uint8_T)mxGetN(ze43f97b6ea);if(!ssSetNumInputPorts(S,zaf49fd5709)){SG_PRINTF(ERROR,"\x65\x72\x72\x6f\x72\x20\x77\x68\x69\x6c\x65\x20\x73\x65\x74\x74\x69\x6e\x67\x20\x69\x6e\x70\x75\x74\x20\x70\x6f\x72\x74\x73" "\n");return;}for(i=(0x1fe6+53-0x201b);i<zaf49fd5709;i++){ssSetInputPortWidth(S,i,(0x1c1a+903-0x1fa0));ssSetInputPortDirectFeedThrough(S,i,(0x20d6+809-0x23fe));ssSetInputPortRequiredContiguous(S,i,(0xda5+3773-0x1c61));}if(!ssSetNumOutputPorts(S,(0x98+3130-0xcd2))){SG_PRINTF(ERROR,"\x65\x72\x72\x6f\x72\x20\x77\x68\x69\x6c\x65\x20\x73\x65\x74\x74\x69\x6e\x67\x20\x6f\x75\x74\x70\x75\x74\x20\x70\x6f\x72\x74\x73" "\n");return;}ssSetNumSampleTimes(S,(0x10f+45-0x13b));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0xfd8+167-0x107f));ssSetNumNonsampledZCs(S,(0xe9c+5272-0x2334));for(i=(0x1f69+1516-0x2555);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x621+3016-0x11e9));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x13a+4943-0x1489)]==-1.0){ssSetSampleTime(S,(0xffb+916-0x138f),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x1595+1668-0x1c19),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x1786+2108-0x1fc2),mxGetPr(z3832b85a32)[(0x1520+1087-0x195f)]);ssSetOffsetTime(S,(0x815+6116-0x1ff9),0.0);}}
#define MDL_START  
static void mdlStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
sg_PCIDevice zeccbadd9b3;uintptr_t z1167769581;uint32_T bus,slot,z868f107306,z029a0d2c91;uint8_T zaf49fd5709,i,zdc2178657f,z1a0ca037f4,z1d60e437e1;z029a0d2c91=(0x489+3791-0x1358);z868f107306=(0x43c+7621-0x2201);if(mxGetN(z702a26a5e9)==(0x378+8945-0x2668)){bus=(0x1176+3908-0x20ba);slot=(int_T)mxGetPr(z702a26a5e9)[(0x59c+7157-0x2191)];}else{bus=(int_T)mxGetPr(z702a26a5e9)[(0x680+4440-0x17d8)];slot=(int_T)mxGetPr(z702a26a5e9)[(0x42a+7779-0x228c)];}if(sg_findPciDevice(&zeccbadd9b3,DEVNAME,VENDORID,DEVICEID,SUBVENDORID,SUBDEVICEID,(int)mxGetPr(ze13f49a01f)[(0x849+4760-0x1ae1)],bus,slot)){ssSetErrorStatus(S,pSgErrorStr);return;}z1167769581=(uintptr_t)sg_mapIo(&zeccbadd9b3,(0x871+434-0xa23));sg_outpDW((0x181b+1052-0xf3f),z1167769581);zaf49fd5709=(uint8_T)mxGetN(ze43f97b6ea);for(i=(0x15b0+2560-0x1fb0);i<zaf49fd5709;i++){z868f107306|=((0x125d+552-0x1484)<<((uint8_T)mxGetPr(ze43f97b6ea)[i]-(0x1552+2529-0x1f32)));}zdc2178657f=z868f107306&(0x1c8+4455-0x1230);z1a0ca037f4=(z868f107306&65280)>>(0x3a6+3935-0x12fd);z1d60e437e1=(z868f107306&16711680)>>(0x2189+1151-0x25f8);sg_outpB(z1167769581+(0x121c+4039-0x21c3)+(0x546+2601-0xf67),zdc2178657f);sg_outpB(z1167769581+(0x472+8739-0x2675)+(0x98a+1562-0xf9b),z1a0ca037f4);sg_outpB(z1167769581+(0x170c+2827-0x21f7)+(0x1a8c+105-0x1aeb),z1d60e437e1);ssSetPWorkValue(S,z4991bf82ec,(void*)z1167769581);
#endif
}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){
#ifndef MATLAB_MEX_FILE
uint32_T z029a0d2c91;uintptr_t z1167769581;uint8_T i,zaf49fd5709,z78205ce1b7,z55ccb1eb8c,zcaef6fd6c8,z6482a20f84,zc0d074c851;real_T*zc0efaa16c3;z1167769581=(uintptr_t)ssGetPWorkValue(S,z4991bf82ec);z029a0d2c91=(0x66a+4942-0x19b8);zaf49fd5709=(uint8_T)mxGetN(ze43f97b6ea);for(i=(0x740+8088-0x26d8);i<zaf49fd5709;i++){z55ccb1eb8c=(0x280+2782-0xd5e);z78205ce1b7=(uint8_T)mxGetPr(ze43f97b6ea)[i]-(0x1bc+960-0x57b);zc0efaa16c3=(real_T*)ssGetInputPortSignal(S,i);if(*zc0efaa16c3>=THRESHOLD){z55ccb1eb8c=(0x851+2952-0x13d8);}z029a0d2c91|=(z55ccb1eb8c<<z78205ce1b7);}zcaef6fd6c8=z029a0d2c91&(0x17cc+3509-0x2482);z6482a20f84=(z029a0d2c91&65280)>>(0xcb7+6467-0x25f2);zc0d074c851=(z029a0d2c91&16711680)>>(0x161f+3167-0x226e);sg_outpB(z1167769581+(0x762+2869-0x1277)+(0xf00+4428-0x204c),zcaef6fd6c8);sg_outpB(z1167769581+(0x4da+746-0x7a4)+(0xed8+3658-0x1d21),z6482a20f84);sg_outpB(z1167769581+(0x82c+330-0x956)+(0x8c9+6132-0x20bb),zc0d074c851);
#endif
}static void mdlTerminate(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_T z029a0d2c91;uintptr_t z1167769581;uint8_T zaf49fd5709,i,zcaef6fd6c8,z6482a20f84,zc0d074c851;z1167769581=(uintptr_t)ssGetPWorkValue(S,z4991bf82ec);z029a0d2c91=(0x46b+5473-0x19cc);zaf49fd5709=(uint8_T)mxGetN(ze43f97b6ea);for(i=(0x923+6970-0x245d);i<zaf49fd5709;i++){if(sg_isModelInit()||(uint8_T)mxGetPr(z724139b233)[i]){z029a0d2c91|=((uint8_T)mxGetPr(z2ef2842ad3)[i]<<((uint8_T)mxGetPr(ze43f97b6ea)[i]-(0x15d5+1840-0x1d04)));}}zcaef6fd6c8=z029a0d2c91&(0x69f+7324-0x223c);z6482a20f84=(z029a0d2c91&65280)>>(0x63+6158-0x1869);zc0d074c851=(z029a0d2c91&16711680)>>(0x11d4+2625-0x1c05);sg_outpB(z1167769581+(0x117a+1078-0x1590)+(0x1585+668-0x1821),zcaef6fd6c8);sg_outpB(z1167769581+(0xa1f+5704-0x2047)+(0x17a2+3746-0x2643),z6482a20f84);sg_outpB(z1167769581+(0x62c+1654-0xc82)+(0x73d+2300-0x1037),zc0d074c851);
#endif
}
#ifdef MATLAB_MEX_FILE  
#include "simulink.c"   
#else
#include "cg_sfun.h"    
#endif

