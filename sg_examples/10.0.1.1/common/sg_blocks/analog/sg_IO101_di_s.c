// Copyright 2006-2026 Speedgoat GmbH

#define         S_FUNCTION_LEVEL        (0x1d4+6159-0x19e1)
#undef          S_FUNCTION_NAME
#define         S_FUNCTION_NAME         sg_IO101_di_s
#include        <stddef.h>
#include        <stdlib.h>
#include        <stdbool.h>
#include        "simstruc.h"
#ifdef          MATLAB_MEX_FILE
#include        "mex.h"
#endif
#ifndef         MATLAB_MEX_FILE
#include        "sg_common.h"
#endif
#include "include/sg_io101_regs.h"
#include "sg_callback_legacy.h"
#include "sg_printf.h"
#define DEVNAME "\x53\x70\x65\x65\x64\x67\x6f\x61\x74\x20\x49\x4f\x31\x30\x31"
#define VENDORID (0x1e4b+3488-0x1516)
#define DEVICEID 17495
#define zdf24515981          ((0x9b4+7096-0x2564))
#define z942d41a49c        ssGetSFcnParam(S,(0x2eb+9040-0x263b))
#define z0cf2e207bc        ssGetSFcnParam(S,(0x20f+7965-0x212b))
#define z7bf3bce264        ssGetSFcnParam(S,(0x1590+3296-0x226e))
#define z6fccdc8f6e       ssGetSFcnParam(S,(0x2105+1446-0x26a8))
#define z12acd7bee3       ssGetSFcnParam(S,(0x23c5+642-0x2643))
#define z3832b85a32           ssGetSFcnParam(S,(0x221+5237-0x1691))
#define z702a26a5e9                ssGetSFcnParam(S,(0x1109+3760-0x1fb3))
#define ze13f49a01f           ssGetSFcnParam(S,(0x13c7+2565-0x1dc5))
#define z824efc2f8d           ((0xae3+3958-0x1a59))
#define zf552029f69           ((0xdad+4073-0x1d96))
#define z2e6483d505              ((0x1b29+473-0x1d02))
#define zc5ce4cb81a              ((0x8db+5582-0x1ea9))
#define z2b17e2ee3b              ((0x142f+1823-0x1b4d))
#define z0194338df7         ((0x346+4291-0x1409))
static char_T msg[(0x1737+1056-0x1a57)];static void mdlInitializeSizes(SimStruct*S){uint32_T i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x831+799-0xb50));ssSetNumDiscStates(S,(0x469+3177-0x10d2));if((uint32_T)mxGetPr(z942d41a49c)[(0x422+6873-0x1efb)]==(0x14b4+3604-0x22c7)){ssSetNumOutputPorts(S,mxGetN(z0cf2e207bc));for(i=(0xa39+4515-0x1bdc);i<mxGetN(z0cf2e207bc);i++){ssSetOutputPortWidth(S,i,(0x540+607-0x79e));ssSetOutputPortDataType(S,(0x1738+341-0x188d),SS_DOUBLE);}}else{ssSetNumOutputPorts(S,mxGetN(z7bf3bce264));for(i=(0x181a+598-0x1a70);i<mxGetN(z7bf3bce264);i++){ssSetOutputPortWidth(S,i,(0x759+4057-0x1731));ssSetOutputPortDataType(S,(0x1a66+2359-0x239d),SS_DOUBLE);}}ssSetNumInputPorts(S,(0xfcd+1610-0x1617));ssSetNumSampleTimes(S,(0x1434+2564-0x1e37));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x12f+3980-0x10bb));ssSetNumNonsampledZCs(S,(0x165f+2209-0x1f00));for(i=(0xc83+450-0xe45);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x25f0+283-0x270b));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x185f+3089-0x2470)]==-1.0){ssSetSampleTime(S,(0xfb2+2490-0x196c),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x823+5084-0x1bff),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x61f+5901-0x1d2c),mxGetPr(z3832b85a32)[(0x13da+4554-0x25a4)]);ssSetOffsetTime(S,(0xb4+5678-0x16e2),0.0);}}
#define MDL_START
static void mdlStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
sg_PCIDevice zeccbadd9b3;volatile uint32_T*za42cf7dd4a;uint32_T zaa88aaf485,i,z0c3eef007f,channel;uint8_T zf841bb2451;int moduleId=(int)mxGetScalar(ze13f49a01f);if((int_T)mxGetPr(z702a26a5e9)[(0x11ad+755-0x14a0)]<(0x1f7+9206-0x25ed)){if(sg_findPciDevice(&zeccbadd9b3,DEVNAME,VENDORID,DEVICEID,SG_NO_SUB,SG_NO_SUB,moduleId,SG_NO_BUS_SLOT,SG_NO_BUS_SLOT)){ssSetErrorStatus(S,pSgErrorStr);return;}}else{int_T bus,slot;if(mxGetN(z702a26a5e9)==(0xc11+6409-0x2519)){bus=(0xd18+4209-0x1d89);slot=(int_T)mxGetPr(z702a26a5e9)[(0x49a+7036-0x2016)];}else{bus=(int_T)mxGetPr(z702a26a5e9)[(0x986+422-0xb2c)];slot=(int_T)mxGetPr(z702a26a5e9)[(0x2bd+5045-0x1671)];}if(sg_findPciDevice(&zeccbadd9b3,DEVNAME,VENDORID,DEVICEID,SG_NO_SUB,SG_NO_SUB,moduleId,bus,slot)){ssSetErrorStatus(S,pSgErrorStr);return;}}za42cf7dd4a=(volatile uint32_T*)sg_mapMemory(&zeccbadd9b3,(0x23a+3910-0x1180));ssSetPWorkValue(S,z0194338df7,(void*)za42cf7dd4a);if((uint32_T)mxGetPr(z942d41a49c)[(0x440+3011-0x1003)]==(0xd45+1512-0x132c)){z0c3eef007f=mxGetN(z0cf2e207bc);zaa88aaf485=(0x35d+5481-0x18c6);for(i=(0xbeb+5847-0x22c2);i<z0c3eef007f;i++){channel=(int_T)mxGetPr(z0cf2e207bc)[i]-(0xb5b+6746-0x25b4);zf841bb2451=(uint8_T)mxGetPr(z6fccdc8f6e)[channel];zaa88aaf485|=(zf841bb2451<<(0x13c+1712-0x7e8)*i);}za42cf7dd4a[zfb07e71feb]=zaa88aaf485;}else{z0c3eef007f=mxGetN(z7bf3bce264);zaa88aaf485=(0x1b48+1261-0x2035);for(i=(0x2c7+6675-0x1cda);i<z0c3eef007f;i++){channel=(int_T)mxGetPr(z7bf3bce264)[i]-(0x1bab+414-0x1d48);zf841bb2451=(uint8_T)mxGetPr(z12acd7bee3)[channel];zaa88aaf485|=(zf841bb2451<<(0x3a8+6287-0x1c33)*i);}za42cf7dd4a[z04ea076420]=zaa88aaf485;}
#endif
}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){
#ifndef MATLAB_MEX_FILE
volatile uint32_T*za42cf7dd4a=ssGetPWorkValue(S,z0194338df7);uint32_T z0c3eef007f;uint32_T i,input,channel;real_T*y;input=za42cf7dd4a[z1c7b619405]&65535;if((uint32_T)mxGetPr(z942d41a49c)[(0x1d08+2560-0x2708)]==(0x11eb+4259-0x228d)){z0c3eef007f=mxGetN(z0cf2e207bc);for(i=(0x86d+5882-0x1f67);i<z0c3eef007f;i++){channel=(int_T)mxGetPr(z0cf2e207bc)[i]-(0x1309+147-0x139b);y=ssGetOutputPortSignal(S,i);y[(0xd8a+2607-0x17b9)]=(input>>channel)&(0xd7b+3235-0x1a1d);}}else{z0c3eef007f=mxGetN(z7bf3bce264);for(i=(0x18c6+2896-0x2416);i<z0c3eef007f;i++){channel=(int_T)mxGetPr(z7bf3bce264)[i]-(0x4c8+1535-0xac6);y=ssGetOutputPortSignal(S,i);y[(0x1bb0+1567-0x21cf)]=(input>>(channel+(0x2054+1279-0x254b)))&(0x1033+1939-0x17c5);}}
#endif
}static void mdlTerminate(SimStruct*S){}
#include "sg_sfcn_glue.h"   

