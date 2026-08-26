// Copyright 2006-2026 Speedgoat GmbH

#define     S_FUNCTION_LEVEL    (0x841+6592-0x21ff)
#undef      S_FUNCTION_NAME
#define     S_FUNCTION_NAME     sg_IO183_di_s
#include "sg_IO183.h"
#include "sg_callback_legacy.h"
#include "sg_printf.h"
#define ze13f49a01f           ssGetSFcnParam(S, (0xf8+5361-0x15e9))    
#define z702a26a5e9                ssGetSFcnParam(S, (0x26a+2617-0xca2))    
#define z3832b85a32           ssGetSFcnParam(S, (0xa25+4073-0x1a0c))    
#define z82143b8d5e         ssGetSFcnParam(S, (0xebd+4263-0x1f61))    
#define zdf24515981                        (   (0x1db+3018-0xda1))
#define z2e6483d505      ((0x129d+4807-0x2564))
#define zc5ce4cb81a      ((0xefc+3517-0x1cb9))
#define z4991bf82ec       ((0xf1f+1800-0x1627))
#define z2b17e2ee3b      ((0xae6+5753-0x215e))
static char_T msg[(0xb53+2522-0x142d)];static void mdlInitializeSizes(SimStruct*S){uint32_T i;uint8_T z963c71b80b;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x179a+2394-0x20f4));ssSetNumDiscStates(S,(0x3e4+5580-0x19b0));z963c71b80b=(uint8_T)mxGetN(z82143b8d5e);if(!ssSetNumInputPorts(S,(0x514+5230-0x1982))){SG_PRINTF(ERROR,"\x65\x72\x72\x6f\x72\x20\x77\x68\x69\x6c\x65\x20\x73\x65\x74\x74\x69\x6e\x67\x20\x69\x6e\x70\x75\x74\x20\x70\x6f\x72\x74\x73" "\n");return;}if(!ssSetNumOutputPorts(S,z963c71b80b)){SG_PRINTF(ERROR,"\x65\x72\x72\x6f\x72\x20\x77\x68\x69\x6c\x65\x20\x73\x65\x74\x74\x69\x6e\x67\x20\x6f\x75\x74\x70\x75\x74\x20\x70\x6f\x72\x74\x73" "\n");return;}for(i=(0x10f7+1372-0x1653);i<z963c71b80b;i++){ssSetOutputPortWidth(S,i,(0xec+1143-0x562));}ssSetNumSampleTimes(S,(0x8d9+634-0xb52));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x1088+1607-0x16cf));ssSetNumNonsampledZCs(S,(0x4c2+6374-0x1da8));for(i=(0x6f1+6800-0x2181);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x4e0+3207-0x1167));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x3f3+7798-0x2269)]==-1.0){ssSetSampleTime(S,(0x108a+4306-0x215c),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0xd0+2923-0xc3b),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0xffb+802-0x131d),mxGetPr(z3832b85a32)[(0x10c4+5421-0x25f1)]);ssSetOffsetTime(S,(0xb10+4141-0x1b3d),0.0);}}
#define MDL_START  
static void mdlStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
sg_PCIDevice zeccbadd9b3;uintptr_t z1167769581;uint32_T bus,slot;if(mxGetN(z702a26a5e9)==(0xe1+6000-0x1850)){bus=(0x81+3511-0xe38);slot=(int_T)mxGetPr(z702a26a5e9)[(0x7ca+3398-0x1510)];}else{bus=(int_T)mxGetPr(z702a26a5e9)[(0x1bc7+2547-0x25ba)];slot=(int_T)mxGetPr(z702a26a5e9)[(0x4f6+560-0x725)];}if(sg_findPciDevice(&zeccbadd9b3,DEVNAME,VENDORID,DEVICEID,SUBVENDORID,SUBDEVICEID,(int)mxGetPr(ze13f49a01f)[(0x5da+5200-0x1a2a)],bus,slot)){ssSetErrorStatus(S,pSgErrorStr);return;}z1167769581=(uintptr_t)sg_mapIo(&zeccbadd9b3,(0x26f+4887-0x1586));sg_outpDW((0x2505+1133-0x1c7a),z1167769581);ssSetPWorkValue(S,z4991bf82ec,(void*)z1167769581);
#endif
}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){
#ifndef MATLAB_MEX_FILE
uint32_T z029a0d2c91;uintptr_t z1167769581;volatile uint8_T i,z963c71b80b,z78205ce1b7,z0a9b3ff301,zcaef6fd6c8,z6482a20f84,zc0d074c851;real_T*zc0efaa16c3;z1167769581=(uintptr_t)ssGetPWorkValue(S,z4991bf82ec);z029a0d2c91=(0x1877+1112-0x1ccf);z963c71b80b=(uint8_T)mxGetN(z82143b8d5e);zcaef6fd6c8=sg_inpB(z1167769581+(0x1301+883-0x1654)+(0xa58+7047-0x25df));z6482a20f84=sg_inpB(z1167769581+(0xddf+1254-0x12a5)+(0x597+3939-0x14f9));zc0d074c851=sg_inpB(z1167769581+(0xe68+4863-0x2147)+(0x12c1+713-0x1588));z029a0d2c91=(zc0d074c851<<(0x2198+813-0x24b5))|(z6482a20f84<<(0x1472+4721-0x26db))|zcaef6fd6c8;for(i=(0x1ca8+949-0x205d);i<z963c71b80b;i++){z78205ce1b7=(uint8_T)mxGetPr(z82143b8d5e)[i]-(0x1e24+73-0x1e6c);zc0efaa16c3=ssGetOutputPortSignal(S,i);z0a9b3ff301=(z029a0d2c91&((0xa63+6957-0x258f)<<z78205ce1b7))>>z78205ce1b7;*zc0efaa16c3=(real_T)z0a9b3ff301;}
#endif
}static void mdlTerminate(SimStruct*S){}
#ifdef MATLAB_MEX_FILE  
#include "simulink.c"   
#else
#include "cg_sfun.h"    
#endif

