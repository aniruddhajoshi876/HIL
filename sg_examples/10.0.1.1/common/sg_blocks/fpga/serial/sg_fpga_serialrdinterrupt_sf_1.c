// Copyright 2006-2026 Speedgoat GmbH

#define 	S_FUNCTION_LEVEL 	(0x15e2+1704-0x1c88)
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_fpga_serialrdinterrupt_sf_1
#include 	<stddef.h>
#include 	<stdlib.h>
#include    <stdint.h>
#include 	"simstruc.h" 
#ifdef 		MATLAB_MEX_FILE
#include 	"mex.h"
#endif
#ifndef     MATLAB_MEX_FILE
#include    "sg_fpga_io3xx_util.h"
#include 	"sg_printf.h"
#endif
#include  "sg_callback.h"
typedef enum{zfaa050b79d,CHANNEL,ze344b15ab1,zdf24515981}z9b42a7026b;
#define ze13f49a01f		  ssGetSFcnParam(S, zfaa050b79d   )
#define za9d8fb6bcf           ssGetSFcnParam(S, CHANNEL     )
#define z3832b85a32         ssGetSFcnParam(S, ze344b15ab1   )
enum zbb1f615c1d{z3250bb2679};enum z93bcf30780{z8a85396f5b};enum zb06a9f15ae{z00deac365e,z9cbfedf63b};
#define z5bbcf8be2c          (0x356+6194-0x1b86)
static char msg[(0x158c+2447-0x1e1b)];typedef volatile struct{uint32_t z5113d6a8d4;uint32_t zbc53575f66;uint32_t z937b9aa588;uint32_t zad12366ed6;uint32_t z224b61a322;uint32_t z05a38d9688;uint32_t z96ef554f24;uint32_t z41cf12af39;uint32_t version;uint32_t za6d2280101[(0x14f5+1502-0x1ab3)];uint32_t zcf124b5c7b[(0x2588+93-0x25c5)];uint32_t ze963c724bd[(0x1cd1+2275-0x2594)];uint32_t z5933ba9eef[(0x1015+3231-0x1c94)];uint32_t zb527a777b1[(0x257+4315-0x1312)];uint32_t zbb6601ed0b[(0xa6d+3443-0x17c0)];uint32_t zb2bfe8fd67[(0xcca+2358-0x15e0)];uint32_t z9d9906152b[(0x47c+2059-0xc67)];uint32_t z0cb32ea574[(0xd99+5925-0x249e)];uint32_t z80200c8b92[(0x31d+3396-0x1041)];uint32_t z0fac3ac62e[(0xc88+4057-0x1c41)];uint32_t z47dac54a30[(0x132c+3118-0x1f3a)];uint32_t z00cc33cb8e[(0xa38+3643-0x1853)];uint32_t z0c6f5b8493[(0x1a5b+1407-0x1fba)];uint32_t zb741e2a3ac[(0xa00+626-0xc52)];uint32_t z239d126e9d;uint32_t zdbfe9a161d;uint32_t z2292c73d55;uint32_t z2ccd606be7;uint32_t z3c2f87c6d7;uint32_t z20b2ce87e9;uint32_t zb4886fe8bc[(0x7e4+5254-0x1c4a)];uint32_t zb4e57f0e16[(0x1c72+1469-0x220f)];uint32_t z6aa32fb21c;uint32_t z9d6cfd9b17;}z555c3b09c0;static void mdlInitializeSizes(SimStruct*S){uint32_t i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73" "\n" "\x20\x70\x61\x73\x73\x65\x64\x3a\x20\x25\x64" "\n" "\x20\x65\x78\x70\x65\x63\x74\x65\x64\x3a\x20\x25\x64" "\n",ssGetSFcnParamsCount(S),ssGetNumSFcnParams(S));ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x1534+3369-0x225d));ssSetNumDiscStates(S,(0x1315+2975-0x1eb4));ssSetNumInputPorts(S,(0x4f7+7101-0x20b4));ssSetNumOutputPorts(S,(0x1b48+1712-0x21f7));ssSetOutputPortWidth(S,(0x23a6+104-0x240e),(uint32_t)mxGetN(za9d8fb6bcf));ssSetOutputPortDataType(S,(0x1a58+2501-0x241d),SS_BOOLEAN);ssSetNumSampleTimes(S,(0x516+459-0x6e0));ssSetNumRWork(S,z8a85396f5b);ssSetNumIWork(S,z3250bb2679);ssSetNumPWork(S,z9cbfedf63b);ssSetNumModes(S,(0x1b31+2421-0x24a6));ssSetNumNonsampledZCs(S,(0xa43+4596-0x1c37));for(i=(0xdf8+22-0xe0e);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x1470+1078-0x18a6));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x773+7188-0x2387)]==-1.0){ssSetSampleTime(S,(0x31f+5306-0x17d9),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x16f5+2943-0x2274),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x104a+2355-0x197d),mxGetPr(z3832b85a32)[(0x1b91+1220-0x2055)]);ssSetOffsetTime(S,(0x1bd3+908-0x1f5f),0.0);}}static void sg_ModelLoad(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uintptr_t z70fcda5f5d;int moduleId=(int)mxGetScalar(ze13f49a01f);char*boardName=io3xxGetBoardNameSgLib(moduleId);z555c3b09c0*serial;z70fcda5f5d=(uintptr_t)io3xxGetAddressSgLib((int)mxGetPr(ze13f49a01f)[(0xe8b+1644-0x14f7)],SG_FPGA_IO3XX_BAR2);if(z70fcda5f5d==(0x8c7+259-0x9ca)){ssSetErrorStatus(S,pSgErrorStr);return;}uint32_t zf7ccd17be8=(0x504+5551-0x1ab3);if(sg_fpga_io3xx_getCmBaseAddress(moduleId,SERIAL_BASE,&zf7ccd17be8)){sprintf(msg,"\x25\x73\x20\x53\x65\x72\x69\x61\x6c\x20\x46\x69\x66\x6f\x20\x52\x65\x61\x64\x20\x49\x6e\x74\x65\x72\x72\x75\x70\x74\x20\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x4f\x66\x66\x73\x65\x74\x20\x6c\x6f\x6f\x6b\x75\x70\x20\x75\x6e\x73\x75\x63\x63\x65\x73\x73\x66\x75\x6c\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}serial=(z555c3b09c0*)(z70fcda5f5d+zf7ccd17be8);ssSetPWorkValue(S,z00deac365e,(void*)serial);if(sg_isFirstModelLoad()){if(sg_fpga_io3xx_checkCodeModuleVersion(serial->version,z5bbcf8be2c,moduleId)){sprintf(msg,"\x25\x73\x20\x77\x72\x6f\x6e\x67\x20\x76\x65\x72\x73\x69\x6f\x6e\x20\x6f\x66\x20\x53\x65\x72\x69\x61\x6c\x20\x46\x69\x66\x6f\x20\x52\x65\x61\x64\x20\x49\x6e\x74\x65\x72\x72\x75\x70\x74\x20\x63\x6f\x64\x65\x20\x6d\x6f\x64\x75\x6c\x65\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}}
#endif
}static void sg_ModelStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
#endif
}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_t z2ccd606be7,i,channel;bool*out;z555c3b09c0*serial=(z555c3b09c0*)ssGetPWorkValue(S,z00deac365e);z2ccd606be7=serial->z2ccd606be7;out=(bool*)ssGetOutputPortSignal(S,(0x95c+3027-0x152f));for(i=(0x91a+1512-0xf02);i<(uint32_t)mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0xea8+1917-0x1624);out[i]=(z2ccd606be7>>channel)&(0xafb+233-0xbe3);}serial->z2292c73d55=z2ccd606be7;serial->z2292c73d55=(0xc88+3535-0x1a57);
#endif
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE
#endif
}
#include "sg_sfcn_glue.h"   

