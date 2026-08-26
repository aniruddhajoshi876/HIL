// Copyright 2006-2026 Speedgoat GmbH

#define 	S_FUNCTION_LEVEL 	(0x81+6950-0x1ba5)
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_fpga_serialrdframe_sf_1
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
#define zdf24515981        ((0x6da+6422-0x1fe9))
#define z533b11d03f         ssGetSFcnParam(S, (0xe2c+937-0x11d5)) 
#define z58f464b4bb                ssGetSFcnParam(S, (0x1b9d+916-0x1f30))
#define za9d8fb6bcf           ssGetSFcnParam(S, (0x984+7210-0x25ac)) 
#define z88e9cc24a0            ssGetSFcnParam(S, (0xabb+6853-0x257d))
#define z88420335f7   ssGetSFcnParam(S, (0x11db+4828-0x24b3))
#define z3832b85a32         ssGetSFcnParam(S, (0x7ff+3509-0x15af))
#define z702a26a5e9              ssGetSFcnParam(S, (0x6ea+5450-0x1c2e))
#define z2e6483d505              ((0xe5+6045-0x1881))
#define z51bcf7ad6c                 ((0x1530+640-0x17b0))
#define zc5ce4cb81a              ((0xdcc+830-0x110a))
#define z2b17e2ee3b              ((0x555+7985-0x2484))
#define z93d7dbe681         ((0x90+2295-0x987))
#define za17de91730                ((0x10a6+5537-0x2646))
#define z5ae2c8ee5e         ((0x373+1475-0x936))    
static char_T msg[(0x18d6+1419-0x1d61)];
#define z90917e531a                 (1081344)
#define zf7c50a4d4a                      ((0xedf+3069-0x1ad9))
struct SERIAL{uint32_t z8ed0e350a6;uint32_t z50c2fe3d67;uint32_t cs;uint32_t zdf75ab3269;uint32_t addr;uint32_t data;uint32_t ze1df3f2032[(0x844+5660-0x1e40)];uint32_t z9b71add2e2;uint32_t zd114ff6ac4;uint32_t z6ad1de6ae2;uint32_t test1;uint32_t test2;uint32_t z100bdfa0d3;uint32_t zf39deaa0a5;uint32_t version;};static uint8_t zdbce8f148f(SimStruct*S,uint8_t channel,uint8_t addr);static uint32_t z7a17c344fa(SimStruct*S,uint8_t channel);static void zdc4dfcc407(SimStruct*S,uint8_t channel,uint8_t addr);static void z60b36ec77c(SimStruct*S);static void z4959649fab(SimStruct*S,uint8_t channel,uint8_t addr,uint8_t data);
#ifndef MATLAB_MEX_FILE
static uint8_t zdbce8f148f(SimStruct*S,uint8_t channel,uint8_t addr){uintptr_t base=(uintptr_t)ssGetPWorkValue(S,z93d7dbe681);volatile struct SERIAL*serial=(volatile struct SERIAL*)(base+z90917e531a);uint8_t data;serial->cs=~((0x5c5+4397-0x16f1)<<channel);serial->addr=addr;serial->z8ed0e350a6=~((0xe77+5107-0x2269)<<channel);data=serial->data;serial->z8ed0e350a6=4294967295;serial->cs=4294967295;return data;}
#endif
#ifndef MATLAB_MEX_FILE
static uint32_t z7a17c344fa(SimStruct*S,uint8_t channel){uintptr_t base=(uintptr_t)ssGetPWorkValue(S,z93d7dbe681);volatile struct SERIAL*serial=(volatile struct SERIAL*)(base+z90917e531a);uint32_t data;serial->zd114ff6ac4=(0xbfc+3368-0x1923)<<channel;serial->zd114ff6ac4=(0x2532+217-0x260b);data=serial->z9b71add2e2;return data;}
#endif
#ifndef MATLAB_MEX_FILE
static void zdc4dfcc407(SimStruct*S,uint8_t channel,uint8_t addr){uintptr_t base=(uintptr_t)ssGetPWorkValue(S,z93d7dbe681);volatile struct SERIAL*serial=(volatile struct SERIAL*)(base+z90917e531a);serial->cs=~((0x1ff+1138-0x670)<<channel);serial->addr=addr;}
#endif
#ifndef MATLAB_MEX_FILE
static void z60b36ec77c(SimStruct*S){uintptr_t base=(uintptr_t)ssGetPWorkValue(S,z93d7dbe681);volatile struct SERIAL*serial=(volatile struct SERIAL*)(base+z90917e531a);serial->cs=4294967295;}
#endif
#ifndef MATLAB_MEX_FILE
static void z4959649fab(SimStruct*S,uint8_t channel,uint8_t addr,uint8_t data){uintptr_t base=(uintptr_t)ssGetPWorkValue(S,z93d7dbe681);volatile struct SERIAL*serial=(volatile struct SERIAL*)(base+z90917e531a);serial->cs=~((0xb0c+732-0xde7)<<channel);serial->addr=addr;serial->data=data;serial->z50c2fe3d67=~((0x1cc4+886-0x2039)<<channel);serial->z50c2fe3d67=4294967295;serial->cs=4294967295;}
#endif
static void mdlInitializeSizes(SimStruct*S){uint32_t i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x905+3096-0x151d));ssSetNumDiscStates(S,(0x4a+6610-0x1a1c));ssSetNumInputPorts(S,(0xdaf+4966-0x2114));ssSetInputPortWidth(S,(0x455+5824-0x1b15),(0xf56+5753-0x25ce));ssSetInputPortDataType(S,(0x1824+2120-0x206c),SS_BOOLEAN);ssSetInputPortDirectFeedThrough(S,(0x402+3551-0x11e1),(0x1c6f+253-0x1d6b));ssSetInputPortRequiredContiguous(S,(0x9c+3032-0xc74),(0xbfd+6399-0x24fb));ssSetNumOutputPorts(S,(0x73f+6496-0x209d));ssSetOutputPortWidth(S,(0x90c+5683-0x1f3f),(0x16c9+1231-0x1b17));ssSetOutputPortDataType(S,(0xe50+5133-0x225d),SS_UINT8);ssSetOutputPortWidth(S,(0x11+824-0x348),(0xbf3+6043-0x238d));ssSetOutputPortDataType(S,(0x1cd0+1609-0x2318),SS_BOOLEAN);ssSetNumSampleTimes(S,(0xd72+3296-0x1a51));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x459+1355-0x9a4));ssSetNumNonsampledZCs(S,(0x1078+3127-0x1caf));for(i=(0x301+7993-0x223a);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x16df+2126-0x1f2d));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0xcb0+5124-0x20b4)]==-1.0){ssSetSampleTime(S,(0x1e94+1592-0x24cc),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x3e6+267-0x4f1),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x18d+7117-0x1d5a),mxGetPr(z3832b85a32)[(0x1c9f+1061-0x20c4)]);ssSetOffsetTime(S,(0x749+2018-0xf2b),0.0);}}
#define MDL_START
static void mdlStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
int32_t bus,slot;uint32_t boardType;uint8_t*databuf;uint32_t i;sg_fpga_io3xxModuleIdT moduleId;void*bar2ptr;boardType=(uint32_t)mxGetPr(z533b11d03f)[(0xbd8+4375-0x1cef)];if(sg_fpga_IO3xxGetModuleId(boardType,&moduleId)<(0x1578+3623-0x239f)){sprintf(msg,"\x49\x4f\x33\x78\x78\x20\x73\x65\x72\x69\x61\x6c\x20\x72\x65\x61\x64\x20\x66\x72\x61\x6d\x65\x3a\x20\x62\x6f\x61\x72\x64\x20\x74\x79\x70\x65\x20\x69\x6e\x63\x6f\x72\x72\x65\x63\x74\x2e");ssSetErrorStatus(S,msg);}if(mxGetN(z702a26a5e9)==(0x2c9+6352-0x1b98)){bus=(0x617+3734-0x14ad);slot=(int_T)mxGetPr(z702a26a5e9)[(0x1d9c+1768-0x2484)];}else{bus=(int_T)mxGetPr(z702a26a5e9)[(0x1cf8+1584-0x2328)];slot=(int_T)mxGetPr(z702a26a5e9)[(0xb0f+218-0xbe8)];}if(!sg_isModelInit()){if(!io3xxGetAddressSgLib((int32_t)(int)mxGetPr(z58f464b4bb)[(0x8c7+652-0xb53)],SG_FPGA_IO3XX_BAR2)){ssSetErrorStatus(S,pSgErrorStr);return;}bar2ptr=io3xxGetAddressSgLib((int32_t)(int)mxGetPr(z58f464b4bb)[(0x635+6383-0x1f24)],SG_FPGA_IO3XX_BAR2);ssSetPWorkValue(S,z93d7dbe681,(void*)bar2ptr);databuf=(uint8_t*)malloc((0x1c5b+2033-0x224c)*sizeof(uint8_t));for(i=(0x143b+1457-0x19ec);i<(0x1e22+284-0x1d3e);i++){*(databuf+i)=(0x14f7+4137-0x2520);}ssSetPWorkValue(S,za17de91730,(void*)databuf);ssSetIWorkValue(S,z51bcf7ad6c,(0x1e80+509-0x207d));}
#endif
}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){
#ifndef MATLAB_MEX_FILE
boolean_T*enable;uint8_t*data;boolean_T*zccefb0ae1c;uint8_t z6e7f3ebc67,zc7f9014d96,zcdbc5a6601;uint32_t channel,i,z26dbd73a5e,z812c65ff2f,zd0118775b4;uint8_t*databuf=(uint8_t*)ssGetPWorkValue(S,za17de91730);uint8_t z567f5f4395;uint8_t zedf940b068;uint32_t z9b71add2e2;enable=(boolean_T*)ssGetInputPortSignal(S,(0x470+6430-0x1d8e));if(enable[(0x1ac2+1494-0x2098)]){zedf940b068=(uint8_t)ssGetIWorkValue(S,z51bcf7ad6c);channel=(uint32_t)mxGetPr(za9d8fb6bcf)[(0xae2+4918-0x1e18)]-(0x1288+907-0x1612);data=(uint8_t*)ssGetOutputPortSignal(S,(0x580+267-0x68b));for(i=(0xc10+6042-0x23aa);i<(0x635+366-0x722);i++){data[i]=(0x575+2550-0xf6b);}zccefb0ae1c=(boolean_T*)ssGetOutputPortSignal(S,(0x291+8255-0x22cf));z6e7f3ebc67=zdbce8f148f(S,channel,zf7c50a4d4a);zc7f9014d96=databuf[(0x1a9+4575-0x1388)];zdc4dfcc407(S,channel,(0xd41+650-0xfcb));for(i=(0x776+3554-0x1558);i<(uint32_t)z6e7f3ebc67/(0x153b+3981-0x24c4);i++){z9b71add2e2=z7a17c344fa(S,channel);databuf[i*(0xb5c+6280-0x23e0)+(0x1ac7+1022-0x1ec4)+zc7f9014d96+(0xedf+2496-0x189c)]=(uint8_t)(z9b71add2e2&(0x61a+2481-0xecc));databuf[i*(0x1f46+1679-0x25d1)+(0x8b6+1343-0xdf4)+zc7f9014d96+(0x899+7426-0x2599)]=(uint8_t)((z9b71add2e2&65280)>>(0x1564+4515-0x26ff));databuf[i*(0x3d7+7535-0x2142)+(0x7cd+6568-0x2174)+zc7f9014d96+(0x2f5+2698-0xd7e)]=(uint8_t)((z9b71add2e2&16711680)>>(0x1c0+7803-0x202b));databuf[i*(0x1421+1819-0x1b38)+(0x493+6635-0x1e7d)+zc7f9014d96+(0xb90+4026-0x1b4a)]=(uint8_t)((z9b71add2e2&4278190080)>>(0x2140+956-0x24e4));databuf[(0x538+6073-0x1cf1)]+=(0xeb8+3020-0x1a80);}z60b36ec77c(S);if(!zedf940b068){if(databuf[(0x1e34+2171-0x26af)]>=(0x4c7+2922-0x102e)*(uint32_t)mxGetPr(z88420335f7)[(0x41b+3892-0x134f)]){z567f5f4395=(0x308+7565-0x2095);for(i=(0x296+4250-0x1330);i<(uint32_t)mxGetPr(z88420335f7)[(0x15ca+2360-0x1f02)];i++){if(databuf[i+(0x7eb+920-0xb82)]==(uint8_t)mxGetPr(z88e9cc24a0)[(0x11e8+4110-0x21f6)]&&databuf[i+(0x19ed+886-0x1d62)+(uint32_t)mxGetPr(z88420335f7)[(0x1819+1535-0x1e18)]]==(uint8_t)mxGetPr(z88e9cc24a0)[(0x1030+3757-0x1edd)]){zedf940b068=(0x85a+4476-0x19d5);break;}else{z567f5f4395+=(0x13a1+1446-0x1946);}}if(!zedf940b068){for(i=(0x1348+4437-0x249d);i<(0x46a+4749-0x14f7);i++){databuf[i]=(0x594+260-0x698);}}}if(zedf940b068){for(z26dbd73a5e=(0x2095+654-0x2323);z26dbd73a5e<z567f5f4395;z26dbd73a5e++){for(i=(0x2d2+6990-0x1e20);i<(uint32_t)(databuf[(0x6ea+1376-0xc4a)]-z567f5f4395);i++){databuf[i+(0x9c+3576-0xe93)]=databuf[i+(0x1506+1633-0x1b65)];}}databuf[(0x12b4+2002-0x1a86)]-=z567f5f4395;}}if(zedf940b068){z26dbd73a5e=(0x128f+3829-0x2184);while((databuf[(0x1b08+932-0x1eac)]>(uint32_t)mxGetPr(z88420335f7)[(0x313+5349-0x17f8)])){for(z812c65ff2f=(0xaa6+1638-0x110c);z812c65ff2f<(uint32_t)mxGetPr(z88420335f7)[(0x11dd+5022-0x257b)];z812c65ff2f++){data[z26dbd73a5e+(0x5b8+4300-0x1683)]=databuf[(0x159f+2502-0x1f64)];databuf[(0x12c5+705-0x1586)]-=(0x1c5+5142-0x15da);for(i=(0x32b+6204-0x1b67);i<databuf[(0x23f1+615-0x2658)];i++){databuf[i+(0x60c+329-0x754)]=databuf[i+(0x4b0+6036-0x1c42)];}z26dbd73a5e+=(0xd7a+754-0x106b);}}data[(0x122a+108-0x1296)]=z26dbd73a5e;zcdbc5a6601=data[(0x684+4460-0x17f0)];zd0118775b4=(0x40d+5066-0x17d7);while(zcdbc5a6601>(uint32_t)mxGetPr(z88420335f7)[(0x209a+1012-0x248e)]){if(data[(0x10ad+2568-0x1ab4)+zd0118775b4*(uint32_t)mxGetPr(z88420335f7)[(0x209+4930-0x154b)]]!=(uint8_t)mxGetPr(z88e9cc24a0)[(0xf01+2424-0x1879)]){zedf940b068=(0x5b7+5251-0x1a3a);for(i=(0xa13+6700-0x243f);i<(0x405+354-0x4e6);i++){data[i]=(0x32+7753-0x1e7b);}for(i=(0x1991+1751-0x2068);i<(0x644+7129-0x201d);i++){databuf[i]=(0x18fb+1534-0x1ef9);}}zcdbc5a6601-=(uint32_t)mxGetPr(z88420335f7)[(0x31+3173-0xc96)];}}zccefb0ae1c[(0x38d+7254-0x1fe3)]=zedf940b068;ssSetIWorkValue(S,z51bcf7ad6c,zedf940b068);}
#endif
}static void mdlTerminate(SimStruct*S){
#ifndef MATLAB_MEX_FILE
if(!sg_isModelInit()){free(ssGetPWorkValue(S,za17de91730));}
#endif
}
#include "sg_sfcn_glue.h"   

