// Copyright 2006-2026 Speedgoat GmbH

#define 	S_FUNCTION_LEVEL 	(0x1061+5031-0x2406)
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_fpga_serialsetup_sf_1
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
#include "sg_printf.h"
#endif
#define debug
#define zdf24515981               ((0x154+2924-0xcb4))
#define z533b11d03f                ssGetSFcnParam(S, (0x95f+7107-0x2522)) 
#define z58f464b4bb                       ssGetSFcnParam(S, (0x1699+3138-0x22da))
#define za9d8fb6bcf                  ssGetSFcnParam(S, (0x300+3487-0x109d)) 
#define zbd954fbed8               ssGetSFcnParam(S, (0x185a+3011-0x241a))
#define z4a2fe7124b                ssGetSFcnParam(S, (0x755+154-0x7eb))
#define z541071e281               ssGetSFcnParam(S, (0x599+1963-0xd3f))
#define z239b53272f                  ssGetSFcnParam(S, (0x10d7+1880-0x1829))
#define z31db3d00a8                      ssGetSFcnParam(S, (0x85f+6139-0x2053))
#define z366e11aa37                      ssGetSFcnParam(S, (0x13e7+2320-0x1cef))
#define zd14d00ebd1                   ssGetSFcnParam(S, (0x519+805-0x835))
#define zc119ce0b67 ssGetSFcnParam(S, (0x205a+682-0x22fa))
#define z702a26a5e9                     ssGetSFcnParam(S, (0xe5c+4836-0x2135))
#define z2e6483d505              ((0x1e9b+1465-0x2454))
#define zc5ce4cb81a              ((0x1d3+8723-0x23e6))
#define z2b17e2ee3b              ((0x413+3000-0xfca))
#define z93d7dbe681         ((0xee0+4207-0x1f4f))
#define z5bbcf8be2c            (0x7ad+247-0x8a3)
#define z90917e531a                 (1081344)
#define z7376ad934b                   ((0x25b+5116-0x1657))
#define z5f2b516546                   ((0xd1b+1256-0x1203))
#define z5f9e951a26                   ((0x497+7135-0x2075))
#define z3c6792cef0                   ((0x642+5684-0x1c74))
#define zd7a63ed4fc                   ((0xe38+4844-0x2122)) 
#define z5e97281b12                   ((0x707+2714-0x119e))
#define z14bf75f7ac                   ((0x1140+3249-0x1ded))
#define zcad73eeed4                   ((0x2c0+8026-0x2215))
#define zce62c99fe0                   ((0x162d+3786-0x24f2))
#define zb20dfcc339                   ((0x129+2658-0xb85))
#define z53f0064694                   ((0x371+5437-0x18a7))
#define zd9ac1b740a                   ((0x199c+562-0x1bce))
#define zad1288679b                   ((0x1e7+1069-0x613))
#define z1d8c44109b                   ((0x49b+2168-0xd11))
#define z0054b6acff                  ((0x36d+8216-0x2381))
#define zeb97cccafa                  ((0x1080+519-0x1282))
#define z390551c2f6                 ((0x3b7+7358-0x206f))
#define zd5cc9e7877                 ((0x117b+5493-0x26e9))
#define zde9cc57973                   ((0x2489+423-0x2630))
#define z3ca7df652d                   ((0x1d68+584-0x1faf))
#define za83f73d6ef                   ((0xac2+5271-0x1f57))
#define z5aab5d6138                   ((0x797+1372-0xcf0))
#define zf9026494f1                   ((0x129c+2589-0x1cb5))
#define zce6e74befd                   ((0x9cc+4897-0x1ce8))
#define zd6d170ef44                   ((0xccb+5410-0x21e7))
#define z660be450cb                   ((0x5c6+8433-0x26b0))
#define zb1edd36243                   ((0x6c9+6784-0x2141))
#define z5f7ba7ea13                   ((0xfc2+1138-0x142b))
#define z3111898ab4                   ((0xa2a+4644-0x1c44))
#define z7ca3d1663e                   ((0xc54+2474-0x15f3))
#define z486899c8fe                   ((0x2da+1142-0x744))
#define zca0a938969                   ((0x1045+4190-0x2096))
#define z2cb8b47b40                   ((0x1d9a+2196-0x2620))
#define z9836a6a21a                   ((0x64c+2172-0xeb9))
#define z3ed86c0394                   ((0x127+7875-0x1fda))
#define zb4a37c9db4                   ((0x980+2452-0x1303))
#define z8ae87e399a                  ((0x89c+6757-0x22ef))
#define z64190a141a                   ((0xb0+4546-0x125f))
#define bASE                   ((0xbcc+2508-0x1518))
#define z6c69cb6d75                   ((0x8fb+4579-0x1ac6))
#define z365248d143                    ((0x69c+4388-0x17b0))
struct SERIAL{uint32_t z8ed0e350a6;uint32_t z50c2fe3d67;uint32_t cs;uint32_t zdf75ab3269;uint32_t addr;uint32_t data;uint32_t ze1df3f2032[(0xbea+1801-0x12d3)];uint32_t z9b71add2e2;uint32_t zd114ff6ac4;uint32_t z6ad1de6ae2;uint32_t test1;uint32_t test2;uint32_t z100bdfa0d3;uint32_t zf39deaa0a5;uint32_t version;};static char_T msg[(0xab3+4392-0x1adb)];static uint8_t zdbce8f148f(SimStruct*S,uint8_t channel,uint8_t addr);static void z4959649fab(SimStruct*S,uint8_t channel,uint8_t addr,uint8_t data);
#ifndef MATLAB_MEX_FILE
static uint8_t zdbce8f148f(SimStruct*S,uint8_t channel,uint8_t addr){uintptr_t base=(uintptr_t)ssGetPWorkValue(S,z93d7dbe681);volatile struct SERIAL*serial=(volatile struct SERIAL*)(base+z90917e531a);uint8_t data;serial->cs=~((0xeb2+3359-0x1bd0)<<channel);serial->addr=addr;serial->z8ed0e350a6=~((0xfe9+1071-0x1417)<<channel);data=serial->data;serial->z8ed0e350a6=4294967295;serial->cs=4294967295;return data;}
#endif
#ifndef MATLAB_MEX_FILE
static void z4959649fab(SimStruct*S,uint8_t channel,uint8_t addr,uint8_t data){uintptr_t base=(uintptr_t)ssGetPWorkValue(S,z93d7dbe681);volatile struct SERIAL*serial=(volatile struct SERIAL*)(base+z90917e531a);serial->cs=~((0xf91+3687-0x1df7)<<channel);serial->addr=addr;serial->data=data;serial->z50c2fe3d67=~((0xaa6+1877-0x11fa)<<channel);serial->z50c2fe3d67=4294967295;serial->cs=4294967295;}
#endif
#ifndef MATLAB_MEX_FILE
static void zd61e321164(SimStruct*S,uint8_t channel,uint8_t z78350de0c1,uint8_t z6734ee89bc){uint8_t lcr;lcr=zdbce8f148f(S,channel,z5e97281b12);z4959649fab(S,channel,z5e97281b12,(0x1a28+2123-0x2273));z4959649fab(S,channel,z53f0064694,z78350de0c1);z4959649fab(S,channel,zce62c99fe0,z6734ee89bc);z4959649fab(S,channel,z5e97281b12,lcr);}
#endif
#ifndef MATLAB_MEX_FILE
static uint8_t z48eeab246c(SimStruct*S,uint8_t channel,uint8_t z78350de0c1){uint8_t lcr;uint8_t data;lcr=zdbce8f148f(S,channel,z5e97281b12);z4959649fab(S,channel,z5e97281b12,(0xab+3488-0xe4b));zd61e321164(S,channel,zde9cc57973,(0x326+656-0x576));z4959649fab(S,channel,z53f0064694,z78350de0c1);data=zdbce8f148f(S,channel,zce62c99fe0);zd61e321164(S,channel,zde9cc57973,(0x126d+2454-0x1c03));z4959649fab(S,channel,z5e97281b12,lcr);return data;}
#endif
static void mdlInitializeSizes(SimStruct*S){uint32_t i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0xa68+2136-0x12c0));ssSetNumDiscStates(S,(0x801+2331-0x111c));ssSetNumInputPorts(S,(0x120f+3042-0x1df1));ssSetNumInputPorts(S,(0x22b+5874-0x191d));ssSetNumSampleTimes(S,(0xc53+3684-0x1ab6));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0xa13+5185-0x1e54));ssSetNumNonsampledZCs(S,(0x7f4+311-0x92b));for(i=(0xc3c+1085-0x1079);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x159d+3755-0x2448));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE|SS_OPTION_PLACE_ASAP);}static void mdlInitializeSampleTimes(SimStruct*S){ssSetSampleTime(S,(0x151f+130-0x15a1),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x1bf3+1924-0x2377),FIXED_IN_MINOR_STEP_OFFSET);}
#define MDL_START
static void mdlStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
int32_t bus,slot;sg_fpga_io3xxModuleIdT moduleId;uint32_t boardType;volatile struct SERIAL*serial;uint32_t i,channel;uint8_t lcr;uint16_t ze64e2b2feb;uint32_t z5abc1f8ab7;uint32_t z43c341facf;uint32_t z97287efa46;uint32_t zeeeba54a90;void*bar2ptr;boardType=(uint32_t)mxGetPr(z533b11d03f)[(0x407+4308-0x14db)];if((int32_t)sg_fpga_IO3xxGetModuleId(boardType,&moduleId)<(0x167a+524-0x1886)){sprintf(msg,"\x53\x65\x72\x69\x61\x6c\x20\x73\x65\x74\x75\x70\x20\x62\x6c\x6f\x63\x6b\x3a\x20\x62\x6f\x61\x72\x64\x20\x74\x79\x70\x65\x20\x69\x6e\x63\x6f\x72\x72\x65\x63\x74\x2e");ssSetErrorStatus(S,msg);}if(mxGetN(z702a26a5e9)==(0x61d+6064-0x1dcc)){bus=(0x339+8001-0x227a);slot=(int_T)mxGetPr(z702a26a5e9)[(0x1ff0+1338-0x252a)];}else{bus=(int_T)mxGetPr(z702a26a5e9)[(0xab3+3090-0x16c5)];slot=(int_T)mxGetPr(z702a26a5e9)[(0x10d0+927-0x146e)];}if(!sg_isModelInit()){if(!io3xxGetAddressSgLib((int32_t)(int)mxGetPr(z58f464b4bb)[(0x1493+3844-0x2397)],SG_FPGA_IO3XX_BAR2)){ssSetErrorStatus(S,pSgErrorStr);return;}bar2ptr=io3xxGetAddressSgLib((int32_t)(int)mxGetPr(z58f464b4bb)[(0x7b6+5492-0x1d2a)],SG_FPGA_IO3XX_BAR2);ssSetPWorkValue(S,z93d7dbe681,(void*)bar2ptr);serial=(volatile struct SERIAL*)((uintptr_t)bar2ptr+z90917e531a);z5abc1f8ab7=((serial->version&3221225472)>>(0x4fa+6302-0x1d7a));z43c341facf=((serial->version&1072693248)>>(0xed7+3588-0x1cd5));z97287efa46=((serial->version&1047552)>>(0x1a7d+1110-0x1ec9));SG_PRINTF(INFO,"\x4d\x61\x6a\x6f\x72\x20\x56\x65\x72\x73\x69\x6f\x6e\x3a\x20\x30\x78\x25\x58" "\n",z97287efa46);zeeeba54a90=(serial->version&(0xe12+2137-0x126c));if(z5abc1f8ab7==(0xfc1+5521-0x2550)&&z43c341facf==z90917e531a&&z97287efa46==z5bbcf8be2c){SG_PRINTF(INFO,"\x25\x73\x20\x53\x45\x52\x49\x41\x4c\x20\x63\x6f\x64\x65\x6d\x6f\x64\x75\x6c\x65\x20\x56\x65\x72\x73\x69\x6f\x6e\x20\x74\x65\x73\x74\x20\x6f\x6b" "\n",moduleId.devname);}else{sprintf(msg,"\x25\x73\x20\x77\x72\x6f\x6e\x67\x20\x76\x65\x72\x73\x69\x6f\x6e\x20\x6f\x66\x20\x53\x45\x52\x49\x41\x4c\x20\x63\x6f\x64\x65\x6d\x6f\x64\x75\x6c\x65\x2e\x20\x75\x6e\x69\x71\x75\x65\x49\x64\x3a\x20\x30\x78\x25\x78\x20\x6d\x61\x6a\x6f\x72\x56\x65\x72\x73\x69\x6f\x6e\x3a\x20\x30\x78\x25\x78\x20\x6d\x69\x6e\x6f\x72\x56\x65\x72\x73\x69\x6f\x6e\x3a\x20\x30\x78\x25\x78" "\n",moduleId.devname,z43c341facf,z97287efa46,zeeeba54a90);ssSetErrorStatus(S,msg);}serial->z50c2fe3d67=4294967295;serial->z8ed0e350a6=4294967295;serial->cs=4294967295;for(i=(0x13da+4235-0x2465);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x3f4+4410-0x152d);serial->ze1df3f2032[channel]=(uint32_t)mxGetPr(zd14d00ebd1)[i]-(0x125+7872-0x1fe4);zd61e321164(S,channel,zde9cc57973,(0x1dd+7253-0x1e32));lcr=(0x155c+3905-0x249d);z4959649fab(S,channel,z5e97281b12,(0x18c2+1103-0x1c52));ze64e2b2feb=(uint16_t)mxGetPr(z239b53272f)[i];z4959649fab(S,channel,z1d8c44109b,z365248d143);z4959649fab(S,channel,zad1288679b,(ze64e2b2feb>>(0x1ca8+266-0x1daa))&(0x1c19+1597-0x2157));z4959649fab(S,channel,zd9ac1b740a,(ze64e2b2feb)&(0x1727+2662-0x208e));z4959649fab(S,channel,z5e97281b12,lcr);z4959649fab(S,channel,z3c6792cef0,(0xfb3+4779-0x2257));z4959649fab(S,channel,z3c6792cef0,(0xdf1+3473-0x1b81));zd61e321164(S,channel,z3ca7df652d,((uint8_t)mxGetPr(z366e11aa37)[i])<<(0x12b1+2667-0x1d19));z4959649fab(S,channel,z14bf75f7ac,(0x45+7473-0x1d76));zd61e321164(S,channel,za83f73d6ef,((uint8_t)mxGetPr(z31db3d00a8)[i])&(0xdf8+3490-0x1b8b));lcr=(0x651+4877-0x195e);if((uint32_t)mxGetPr(zbd954fbed8)[i]==(0x1251+3242-0x1ef2)){zd61e321164(S,channel,zca0a938969,(0x20d0+98-0x2131));}else if((uint32_t)mxGetPr(zbd954fbed8)[i]==(0x74b+1941-0xed8)){lcr|=(0x279+145-0x307);}else if((uint32_t)mxGetPr(zbd954fbed8)[i]==(0xe53+600-0x10a4)){lcr|=(0xd5+9537-0x2614);}else if((uint32_t)mxGetPr(zbd954fbed8)[i]==(0xa70+4176-0x1aba)){lcr|=(0x1974+2293-0x2268);}else if((uint32_t)mxGetPr(zbd954fbed8)[i]==(0x685+580-0x8c4)){lcr|=(0x1b74+1932-0x2300);}else{sprintf(msg,"\x53\x65\x72\x69\x61\x6c\x20\x46\x50\x47\x41\x20\x43\x6f\x64\x65\x20\x4d\x6f\x64\x75\x6c\x65\x20\x25\x64\x3a\x20\x49\x6d\x70\x72\x6f\x70\x65\x72\x20\x64\x61\x74\x61\x20\x6c\x65\x6e\x67\x74\x68",channel+
(0x209a+918-0x242f));ssSetErrorStatus(S,msg);return;}if((uint32_t)mxGetPr(z4a2fe7124b)[i]==(0x3+3868-0xf1e)){lcr|=(0xff3+3312-0x1ce3);}if((uint32_t)mxGetPr(z4a2fe7124b)[i]==(0x1d77+99-0x1dd8)){lcr|=(0x1c6f+900-0x1fdb);}if((uint32_t)mxGetPr(z4a2fe7124b)[i]==(0xe6b+2443-0x17f3)){lcr|=(0x9c6+3674-0x1818);}if((uint32_t)mxGetPr(z4a2fe7124b)[i]==(0x59f+2628-0xfdf)){lcr|=(0x2ec+8118-0x227a);}if((uint32_t)mxGetPr(z4a2fe7124b)[i]==(0x785+2741-0x1235)){lcr|=(0x6ef+5107-0x1aaa);}if((uint32_t)mxGetPr(z541071e281)[i]==(0xb75+5140-0x1f88)){lcr|=(0x322+1520-0x912);}else{lcr|=(0x1cb0+445-0x1e69);}z4959649fab(S,channel,z5e97281b12,lcr);if((uint32_t)mxGetPr(zc119ce0b67)[(0xea3+5964-0x25ef)]){zd61e321164(S,channel,zde9cc57973,bASE|z6c69cb6d75);serial->z6ad1de6ae2|=((0x199a+1626-0x1ff3)<<channel);}else{zd61e321164(S,channel,zde9cc57973,bASE);serial->z6ad1de6ae2&=~((0x5e4+7223-0x221a)<<channel);}}}
#endif
}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){
#ifndef MATLAB_MEX_FILE       
#endif
}static void mdlTerminate(SimStruct*S){
#ifndef MATLAB_MEX_FILE
#endif
}
#include "sg_sfcn_glue.h"   

