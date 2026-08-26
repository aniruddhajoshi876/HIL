// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL    (0x22ea+832-0x2628)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO624_sync_e_s
#include "sg_IO624.h"
#include "sg_callback.h"
#define ze13f49a01f           ssGetSFcnParam(S, (0x1c41+1512-0x2229))
#define z3832b85a32           ssGetSFcnParam(S, (0x84d+4337-0x193d))
#define z702a26a5e9                ssGetSFcnParam(S, (0x21e5+831-0x2522))
#define z90cfdad132             ssGetSFcnParam(S, (0x1b15+2118-0x2358))        
#define zdf24515981                           ((0xb41+3099-0x1758))
#define z2e6483d505              ((0x35+2394-0x98f))
#define zc5ce4cb81a              ((0x1232+4662-0x2468))
#define z2b17e2ee3b              ((0x41+3635-0xe74))
static char_T msg[(0x9b7+7733-0x26ec)];static void mdlInitializeSizes(SimStruct*S){uint32_t i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x11ba+4737-0x243b));ssSetNumDiscStates(S,(0x2a6+1430-0x83c));if(!ssSetNumInputPorts(S,(0xdc6+3115-0x19f1)))return;if(!ssSetNumOutputPorts(S,(int)mxGetN(z90cfdad132)))return;for(i=(0x1c70+2374-0x25b6);i<(int)mxGetN(z90cfdad132);i++){ssSetOutputPortWidth(S,i,(0x14f3+3646-0x2330));ssSetOutputPortDataType(S,(0x22cd+734-0x25ab),SS_DOUBLE);}ssSetNumSampleTimes(S,(0x110b+3550-0x1ee8));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0xecb+1168-0x135b));ssSetNumNonsampledZCs(S,(0x40b+1594-0xa45));for(i=(0x1f3c+1620-0x2590);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x1a21+1057-0x1e42));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x13c9+1166-0x1857)]==-1.0){ssSetSampleTime(S,(0x154f+2745-0x2008),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x1928+447-0x1ae7),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x42c+7159-0x2023),mxGetPr(z3832b85a32)[(0x9a4+3538-0x1776)]);ssSetOffsetTime(S,(0x1653+1136-0x1ac3),0.0);}}
#ifndef MATLAB_MEX_FILE
static void sg_ModelLoad(SimStruct*S){}static void sg_ModelStart(SimStruct*S){}static void sg_ModelStep(SimStruct*S){z5d72151f3f*zdca355e255=NULL;uint32_t moduleId=((uint32_t)mxGetPr(ze13f49a01f)[(0x8eb+5638-0x1ef1)]);uint16_t zf91d71c6d9=(uint16_t)mxGetN(z90cfdad132);uint32_t z8c1b21b73f=(0x170c+3699-0x257f);uint16_t i=(0x819+3994-0x17b3);uint16_t z812c65ff2f=(0x1bc+5283-0x165f);uint16_t ch=(0x1574+2784-0x2054);real_T*y=NULL;zdca355e255=(z5d72151f3f*)sg_module_get_custom_data(z8c043b2b63,moduleId);if(zdca355e255==NULL){sprintf(msg,"\x25\x73\x20\x73\x65\x6e\x64\x3a\x20\x4d\x6f\x64\x75\x6c\x65\x20\x6e\x6f\x74\x20\x72\x65\x67\x69\x73\x74\x65\x72\x65\x64" "\n",DEVNAME);ssSetErrorStatus(S,msg);return;}for(i=(0x969+3546-0x1743);i<zf91d71c6d9;i++){ch=(uint16_t)mxGetPr(z90cfdad132)[i]-(0x228a+890-0x2603);z8c1b21b73f=(uint32_t)(zdca355e255->z5450d078d5->za492cac76b[ch]&(0x18c7+3476-0x2654));if(z8c1b21b73f>(0x42f+3432-0x1197)){zdca355e255->z5450d078d5->za492cac76b[ch]=(0x5d+2087-0x875);for(z812c65ff2f=(0xc2c+3997-0x1bc9);(zdca355e255->z5450d078d5->za492cac76b[ch]&(0x1b5d+2229-0x2412));z812c65ff2f++){if(z812c65ff2f>1193000.0*(0x1d1+360-0x338)){sprintf(msg,"\x25\x73\x20\x74\x69\x6d\x65\x2d\x6f\x75\x74\x20\x64\x75\x72\x69\x6e\x67\x20\x63\x6c\x65\x61\x72\x65\x73\x20\x73\x79\x6e\x63\x20\x65\x72\x72\x6f\x72",DEVNAME);ssSetErrorStatus(S,msg);return;}}if((zdca355e255->z5450d078d5->z0825218bf7>>ch)&(0xfcf+2591-0x19ed)){z8c1b21b73f=z8c1b21b73f+(0xcdc+1429-0x126b);}}else if((zdca355e255->z5450d078d5->z0825218bf7>>ch)&(0xf83+2952-0x1b0a)){z8c1b21b73f=(0x114f+324-0x128d);}else{z8c1b21b73f=(0x1765+2383-0x20b4);}y=ssGetOutputPortSignal(S,i);y[(0x460+6335-0x1d1f)]=(real_T)z8c1b21b73f;}}static void sg_ModelStop(SimStruct*S){}
#endif 
#include "sg_sfcn_glue.h"   

