// Copyright 2006-2026 Speedgoat GmbH

#define 	S_FUNCTION_LEVEL 	(0x174a+332-0x1894)
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_fpga_serialrdhwfifo_sf_1
#include 	<stddef.h>
#include 	<stdlib.h>
#include  <stdint.h>
#include 	"simstruc.h" 
#ifdef 		MATLAB_MEX_FILE
#include 	"mex.h"
#endif
#ifndef         MATLAB_MEX_FILE
#include        "sg_common.h"
#include        "sg_fpga_io3xx_util.h"
#include "sg_callback_legacy.h"
#endif
#define zdf24515981        ((0x5e7+6378-0x1ecb))
#define z533b11d03f         ssGetSFcnParam(S, (0xb7+7975-0x1fde)) 
#define z58f464b4bb                ssGetSFcnParam(S, (0x229f+224-0x237e))
#define za9d8fb6bcf           ssGetSFcnParam(S, (0xaac+1099-0xef5)) 
#define zd1006aaed1      ssGetSFcnParam(S, (0x1ae3+461-0x1cad))
#define z3832b85a32         ssGetSFcnParam(S, (0x244d+515-0x264c))
#define z702a26a5e9              ssGetSFcnParam(S, (0x24f7+434-0x26a4))
#define z2e6483d505              ((0xb49+6279-0x23d0))
#define zc5ce4cb81a              ((0x184+500-0x378))
#define z2b17e2ee3b              ((0x1bbf+1930-0x2348))
#define z93d7dbe681         ((0xd6d+6069-0x2522))
#define z5ae2c8ee5e         ((0x369+8158-0x2347))    
static char_T msg[(0x927+6232-0x207f)];
#define z90917e531a                 (1081344)
#define zf7c50a4d4a                      ((0xb77+152-0xc0c))
#define z42ced913bb                 ((0x16d5+2272-0x1fb5))
#define LSR                      ((0x79d+5977-0x1ef1))
#define z05c486da54           ((0x44+6475-0x198e))
#define z2e9e745988           ((0x4f5+854-0x849))
struct SERIAL{uint32_t z8ed0e350a6;uint32_t z50c2fe3d67;uint32_t cs;uint32_t zdf75ab3269;uint32_t addr;uint32_t data;uint32_t ze1df3f2032[(0xe9c+2343-0x17a3)];uint32_t z9b71add2e2;uint32_t zd114ff6ac4;uint32_t z6ad1de6ae2;uint32_t test1;uint32_t test2;uint32_t z100bdfa0d3;uint32_t zf39deaa0a5;uint32_t version;};static uint8_t zdbce8f148f(SimStruct*S,uint8_t channel,uint8_t addr);static uint32_t z7a17c344fa(SimStruct*S,uint8_t channel);static void zdc4dfcc407(SimStruct*S,uint8_t channel,uint8_t addr);static void z60b36ec77c(SimStruct*S);static void z4959649fab(SimStruct*S,uint8_t channel,uint8_t addr,uint8_t data);
#ifndef MATLAB_MEX_FILE
static uint8_t zdbce8f148f(SimStruct*S,uint8_t channel,uint8_t addr){uintptr_t base=(uintptr_t)ssGetPWorkValue(S,z93d7dbe681);volatile struct SERIAL*serial=(volatile struct SERIAL*)(base+z90917e531a);uint8_t data;serial->cs=~((0x1fb6+459-0x2180)<<channel);serial->addr=addr;serial->z8ed0e350a6=~((0x840+7622-0x2605)<<channel);data=serial->data;serial->z8ed0e350a6=4294967295;serial->cs=4294967295;return data;}
#endif
#ifndef MATLAB_MEX_FILE
static uint32_t z7a17c344fa(SimStruct*S,uint8_t channel){uintptr_t base=(uintptr_t)ssGetPWorkValue(S,z93d7dbe681);volatile struct SERIAL*serial=(volatile struct SERIAL*)(base+z90917e531a);uint32_t data;serial->zd114ff6ac4=(0xf12+1279-0x1410)<<channel;serial->zd114ff6ac4=(0x493+7488-0x21d3);serial->test1=(0x1bb2+2351-0x24e1);serial->test1=(0x178c+3365-0x24b1);data=serial->z9b71add2e2;return data;}
#endif
#ifndef MATLAB_MEX_FILE
static void zdc4dfcc407(SimStruct*S,uint8_t channel,uint8_t addr){uintptr_t base=(uintptr_t)ssGetPWorkValue(S,z93d7dbe681);volatile struct SERIAL*serial=(volatile struct SERIAL*)(base+z90917e531a);serial->cs=~((0x91a+2014-0x10f7)<<channel);serial->addr=addr;}
#endif
#ifndef MATLAB_MEX_FILE
static void z60b36ec77c(SimStruct*S){uintptr_t base=(uintptr_t)ssGetPWorkValue(S,z93d7dbe681);volatile struct SERIAL*serial=(volatile struct SERIAL*)(base+z90917e531a);serial->cs=4294967295;}
#endif
#ifndef MATLAB_MEX_FILE
static void z4959649fab(SimStruct*S,uint8_t channel,uint8_t addr,uint8_t data){uintptr_t base=(uintptr_t)ssGetPWorkValue(S,z93d7dbe681);volatile struct SERIAL*serial=(volatile struct SERIAL*)(base+z90917e531a);serial->cs=~((0x1701+2551-0x20f7)<<channel);serial->addr=addr;serial->data=data;serial->z50c2fe3d67=~((0x13e1+1471-0x199f)<<channel);serial->z50c2fe3d67=4294967295;serial->cs=4294967295;}
#endif
static void mdlInitializeSizes(SimStruct*S){uint32_t i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0xd3c+936-0x10e4));ssSetNumDiscStates(S,(0xc5d+3594-0x1a67));ssSetNumInputPorts(S,(0xddd+298-0xf06));ssSetInputPortWidth(S,(0x36d+8117-0x2322),(0x87+742-0x36c));ssSetInputPortDataType(S,(0x79a+294-0x8c0),SS_BOOLEAN);ssSetInputPortDirectFeedThrough(S,(0x1b26+2299-0x2421),(0x19e1+3290-0x26ba));ssSetInputPortRequiredContiguous(S,(0x1b35+961-0x1ef6),(0x233+1310-0x750));ssSetNumOutputPorts(S,(0x1bdc+772-0x1edf));ssSetOutputPortWidth(S,(0x1a7d+2346-0x23a7),(0x4d2+5186-0x1893));if((uint32_t)mxGetPr(zd1006aaed1)[(0xa47+7290-0x26c1)]<=(0xd90+1663-0x1407)){ssSetOutputPortDataType(S,(0x217+347-0x372),SS_UINT8);}else{ssSetOutputPortDataType(S,(0xa81+4607-0x1c80),SS_UINT16);}ssSetNumSampleTimes(S,(0x7d1+5650-0x1de2));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x544+3400-0x128c));ssSetNumNonsampledZCs(S,(0x654+2145-0xeb5));for(i=(0x31+3584-0xe31);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x71f+6439-0x2046));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x8eb+3414-0x1641)]==-1.0){ssSetSampleTime(S,(0x929+6215-0x2170),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x70b+1210-0xbc5),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x12b8+2404-0x1c1c),mxGetPr(z3832b85a32)[(0x110d+1322-0x1637)]);ssSetOffsetTime(S,(0x1aac+315-0x1be7),0.0);}}
#define MDL_START
static void mdlStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
int32_t bus,slot;uint32_t boardType;sg_fpga_io3xxModuleIdT moduleId;void*bar2ptr;boardType=(uint32_t)mxGetPr(z533b11d03f)[(0x1bb4+2171-0x242f)];if((int32_t)sg_fpga_IO3xxGetModuleId(boardType,&moduleId)<(0x1995+1966-0x2143)){sprintf(msg,"\x73\x65\x72\x69\x61\x6c\x20\x72\x65\x61\x64\x20\x62\x6c\x6f\x63\x6b\x3a\x20\x62\x6f\x61\x72\x64\x20\x74\x79\x70\x65\x20\x69\x6e\x63\x6f\x72\x72\x65\x63\x74\x2e");ssSetErrorStatus(S,msg);}if(mxGetN(z702a26a5e9)==(0x18c+7776-0x1feb)){bus=(0x230b+954-0x26c5);slot=(int_T)mxGetPr(z702a26a5e9)[(0x308+7417-0x2001)];}else{bus=(int_T)mxGetPr(z702a26a5e9)[(0x1b25+355-0x1c88)];slot=(int_T)mxGetPr(z702a26a5e9)[(0x3e2+7640-0x21b9)];}if(!sg_isModelInit()){if(!io3xxGetAddressSgLib((int32_t)(int)mxGetPr(z58f464b4bb)[(0x19+8614-0x21bf)],SG_FPGA_IO3XX_BAR2)){ssSetErrorStatus(S,pSgErrorStr);return;}bar2ptr=io3xxGetAddressSgLib((int32_t)(int)mxGetPr(z58f464b4bb)[(0x167b+1571-0x1c9e)],SG_FPGA_IO3XX_BAR2);ssSetPWorkValue(S,z93d7dbe681,(void*)bar2ptr);}
#endif
}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){
#ifndef MATLAB_MEX_FILE
boolean_T*enable;uint8_t*data;uint8_t z6e7f3ebc67;uint16_t*z1376896266;uint16_t z70d9277d09;uint32_t channel,i;uint32_t z2aae6b6146,z0df89f427b;uint32_t z9b71add2e2;enable=(boolean_T*)ssGetInputPortSignal(S,(0x1e98+1987-0x265b));if(enable[(0x222a+65-0x226b)]){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[(0x3da+7134-0x1fb8)]-(0x9eb+1092-0xe2e);if((uint32_t)mxGetPr(zd1006aaed1)[(0x7d+7177-0x1c86)]<=(0x1f49+1890-0x26a3)){data=(uint8_t*)ssGetOutputPortSignal(S,(0x516+4192-0x1576));for(i=(0x493+409-0x62c);i<(0x19bd+2087-0x2163);i++){data[i]=(0x1898+3405-0x25e5);}z6e7f3ebc67=zdbce8f148f(S,channel,zf7c50a4d4a);data[(0x159c+3071-0x219b)]=z6e7f3ebc67;z2aae6b6146=z6e7f3ebc67/(0x1112+3011-0x1cd1);z0df89f427b=z6e7f3ebc67%(0xec3+3194-0x1b39);zdc4dfcc407(S,channel,(0x3d2+7688-0x21da));for(i=(0xbcf+5164-0x1ffb);i<z2aae6b6146;i++){z9b71add2e2=z7a17c344fa(S,channel);data[i*(0xbd5+2068-0x13e5)+(0x10a1+4003-0x2043)+(0xe8d+2684-0x1906)]=(uint8_t)(z9b71add2e2&(0x88f+3510-0x1546));data[i*(0x1910+760-0x1c04)+(0xbe5+166-0xc8a)+(0xd2+6378-0x19ba)]=(uint8_t)((z9b71add2e2&65280)>>(0x1417+4204-0x247b));data[i*(0x73f+7331-0x23de)+(0x41+2129-0x891)+(0x199b+467-0x1b6d)]=(uint8_t)((z9b71add2e2&16711680)>>(0x39+8301-0x2096));data[i*(0x96d+4447-0x1ac8)+(0x19fa+1440-0x1f99)+(0x14a+7606-0x1f00)]=(uint8_t)((z9b71add2e2&4278190080)>>(0x181b+3731-0x2696));}z60b36ec77c(S);for(i=(0x308+7831-0x219f);i<z0df89f427b;i++){data[z2aae6b6146*(0xf66+3682-0x1dc4)+i+(0x1b9c+239-0x1c8a)]=zdbce8f148f(S,channel,z42ced913bb);}}else{z1376896266=(uint16_t*)ssGetOutputPortSignal(S,(0xb43+854-0xe99));for(i=(0xcec+2030-0x14da);i<(0x1991+3081-0x2519);i++){z1376896266[i]=(0xe71+2702-0x18ff);}z70d9277d09=zdbce8f148f(S,channel,zf7c50a4d4a);z1376896266[(0x237+1630-0x895)]=z70d9277d09;z0df89f427b=z70d9277d09;for(i=(0x1078+1941-0x180d);i<z0df89f427b;i++){z1376896266[i+(0xe50+3680-0x1caf)]=((zdbce8f148f(S,channel,LSR)>>(0xfd+306-0x22d))&(0x491+3232-0x1130))<<(0x135d+3143-0x1f9c);z1376896266[i+(0x8bf+7733-0x26f3)]|=zdbce8f148f(S,channel,z42ced913bb);}}}
#endif
}static void mdlTerminate(SimStruct*S){
#ifndef MATLAB_MEX_FILE
#endif
}
#include "sg_sfcn_glue.h"   

