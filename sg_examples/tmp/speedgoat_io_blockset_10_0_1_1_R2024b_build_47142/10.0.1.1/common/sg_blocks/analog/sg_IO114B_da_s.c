// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL        (0x2417+404-0x25a9)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME         sg_IO114B_da_s
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
#define za9d8fb6bcf             ssGetSFcnParam(S, (0x1f1f+119-0x1f96))
#define z8fd86139be               ssGetSFcnParam(S, (0xe33+4343-0x1f29))
#define zabe1e0cd2c          ssGetSFcnParam(S, (0x803+6996-0x2355))
#define z702a26a5e9                ssGetSFcnParam(S, (0x838+0-0x835))
#define zc8bbaa6115               ssGetSFcnParam(S, (0x20af+1175-0x2542))
#define zf80b27df71                ssGetSFcnParam(S, (0x2f1+7616-0x20ac))
#define ze13f49a01f           ssGetSFcnParam(S, (0x6bc+2626-0x10f8))
#define zdf24515981                           ((0x2a7+3316-0xf94))
#define zb901964b43            ((0x98b+4217-0x1a04))
#define zdb781881ab         ((0x803+2726-0x12a8))
#define z2e6483d505              ((0x107a+49-0x10a9))
#define zc5ce4cb81a              ((0x1f43+766-0x2241))
#define z0194338df7         ((0x1e44+1880-0x259c))
#define z2b17e2ee3b              ((0xe8a+1629-0x14e6))
static char_T msg[(0x1e24+2328-0x263c)];
#define VENDORID    (0x23b0+5630-0x2564)
#define DEVICEID    25352
#define SUBVENDORID (0x23b0+5055-0x2325)
#define SUBDEVICEID 25512
#define DEVNAME     "\x53\x70\x65\x65\x64\x67\x6f\x61\x74\x20\x49\x4f\x31\x31\x34\x42"
static void mdlInitializeSizes(SimStruct*S){uint16_T i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x107b+5238-0x24f1));ssSetNumDiscStates(S,(0x923+1741-0xff0));ssSetNumInputPorts(S,(int_T)mxGetN(za9d8fb6bcf));for(i=(0x10ea+1915-0x1865);i<(int)mxGetN(za9d8fb6bcf);i++){ssSetInputPortWidth(S,i,(0xa46+3230-0x16e3));ssSetInputPortDirectFeedThrough(S,i,(0xbd9+3936-0x1b38));}ssSetNumOutputPorts(S,(0x110+6558-0x1aae));ssSetNumSampleTimes(S,(0x86a+5627-0x1e64));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0xd34+1851-0x146f));ssSetNumNonsampledZCs(S,(0x1632+1953-0x1dd3));for(i=(0xc43+6311-0x24ea);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0xc4b+2775-0x1722));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(zabe1e0cd2c)[(0x1270+2310-0x1b76)]==-1.0){ssSetSampleTime(S,(0x371+1839-0xaa0),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0xc53+5351-0x213a),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0xf76+3456-0x1cf6),mxGetPr(zabe1e0cd2c)[(0x1122+5549-0x26cf)]);ssSetOffsetTime(S,(0xb9b+2802-0x168d),0.0);}}
#define MDL_START
static void mdlStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
sg_PCIDevice zeccbadd9b3;int_T bus,slot;uint32_T za0d38ae598;uintptr_t za42cf7dd4a;int offset,z429712b6a9;if(mxGetN(z702a26a5e9)==(0x1a04+2923-0x256e)){bus=(0x19cc+2626-0x240e);slot=(int_T)mxGetPr(z702a26a5e9)[(0x9a+3653-0xedf)];}else{bus=(int_T)mxGetPr(z702a26a5e9)[(0xf34+4738-0x21b6)];slot=(int_T)mxGetPr(z702a26a5e9)[(0xb48+1303-0x105e)];}za0d38ae598=(int_T)mxGetPr(ze13f49a01f)[(0x116f+4799-0x242e)];if(sg_findPciDevice(&zeccbadd9b3,DEVNAME,VENDORID,DEVICEID,SUBVENDORID,SUBDEVICEID,za0d38ae598,bus,slot)!=(0x4b5+5332-0x1989)){ssSetErrorStatus(S,pSgErrorStr);return;}za42cf7dd4a=(uintptr_t)sg_mapIo(&zeccbadd9b3,(0x1cc+5298-0x167c));ssSetPWorkValue(S,z0194338df7,(uint32_T*)za42cf7dd4a);switch((uint16_T)mxGetPr(z8fd86139be)[(0x514+5514-0x1a9e)]){case(0x575+2514-0xf46):offset=(0x176b+1874-0x1ebd);z429712b6a9=(0x2d6+4041-0x128b);break;case(0xada+6994-0x262a):offset=(0xdd+8642-0x229a);z429712b6a9=(0x208+492-0x3e0);break;case(0x756+3815-0x163a):offset=(0x21a3+556-0x23cb);z429712b6a9=(0x1244+1931-0x19bf);break;}ssSetIWorkValue(S,zb901964b43,offset);ssSetIWorkValue(S,zdb781881ab,z429712b6a9);
#endif
}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){
#ifndef MATLAB_MEX_FILE
uintptr_t za42cf7dd4a=(uintptr_t)ssGetPWorkValue(S,z0194338df7);real_T offset=(real_T)ssGetIWorkValue(S,zb901964b43);real_T z429712b6a9=(real_T)ssGetIWorkValue(S,zdb781881ab);uint32_T zf91d71c6d9=(uint32_T)mxGetN(za9d8fb6bcf);uint32_T i;int_T channel;real_T output;uint16_T zcb341ffb0e;uint16_T z23d1f4bef6;InputRealPtrsType z142f9c10a3;for(i=(0x1446+2309-0x1d4b);i<zf91d71c6d9;i++){channel=(int_T)mxGetPr(za9d8fb6bcf)[i]-(0x125a+1383-0x17c0);z142f9c10a3=ssGetInputPortRealSignalPtrs(S,i);output=*z142f9c10a3[(0x562+5733-0x1bc7)];output-=offset;if(output<0.0){output=0.0;}zcb341ffb0e=(uint32_T)((output/z429712b6a9)*4095.0);if(zcb341ffb0e>(0x1209+639-0x48a)){zcb341ffb0e=(0x1a4a+1990-0x1212);}while(sg_inpW(za42cf7dd4a)&(0x17ef+1286-0x1cf4)){SG_PRINTF(DEBUG,"\x77\x61\x69\x74\x20\x44\x61\x74\x61\x20\x53\x65\x6e\x64\x20\x3d\x20\x30" "\n");}switch(channel){case(0x1b2d+2803-0x2620):z23d1f4bef6=(0xc1b+6031-0x23a4);break;case(0xc1d+1893-0x1381):z23d1f4bef6=(0x4ff+31-0x51a);break;case(0x1591+4059-0x256a):z23d1f4bef6=(0x3a0+1172-0x832);break;case(0x1294+4285-0x234e):z23d1f4bef6=(0x1224+4570-0x23fe);break;case(0xe0d+1492-0x13dd):z23d1f4bef6=(0x10b3+112-0x1115);break;case(0xa58+6843-0x250e):z23d1f4bef6=(0x139+7036-0x1ca9);break;case(0x5fd+5905-0x1d08):z23d1f4bef6=(0x4aa+3836-0x139c);break;case(0x8f3+1461-0xea1):z23d1f4bef6=(0xa9c+633-0xd0d);break;}sg_outpW(za42cf7dd4a+z23d1f4bef6,zcb341ffb0e);}
#endif
}static void mdlTerminate(SimStruct*S){}
#include "sg_sfcn_glue.h"   

