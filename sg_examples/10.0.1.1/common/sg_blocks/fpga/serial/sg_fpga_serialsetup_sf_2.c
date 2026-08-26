// Copyright 2006-2026 Speedgoat GmbH

#define 	S_FUNCTION_LEVEL 	(0x1d0+6811-0x1c69)
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_fpga_serialsetup_sf_2
#include 	<stddef.h>
#include 	<stdlib.h>
#include    <stdint.h>
#include 	"simstruc.h" 
#ifdef 		MATLAB_MEX_FILE
#include 	"mex.h"
#endif
#ifndef     MATLAB_MEX_FILE
#include    "sg_common.h"
#include    "sg_fpga_io3xx_util.h"
#include    "sg_printf.h"
#endif
#include  "sg_callback.h"
typedef enum{zfaa050b79d,CHANNEL,za5c2503840,za3d4d926e8,z382e5eb017,zd67e984d9a,zb538604f8f,z613e493327,zdf24515981}z9b42a7026b;
#define ze13f49a01f		    ssGetSFcnParam(S, zfaa050b79d             )
#define za9d8fb6bcf             ssGetSFcnParam(S, CHANNEL               )
#define z9c505d438b       ssGetSFcnParam(S, za5c2503840         )
#define z93b46933bc         ssGetSFcnParam(S, za3d4d926e8           )
#define z80397074ac         ssGetSFcnParam(S, z382e5eb017           )
#define zcf4c56ba2e         ssGetSFcnParam(S, zd67e984d9a           )
#define z08c7a44908 ssGetSFcnParam(S, zb538604f8f   )
#define z6f4a9190dd  ssGetSFcnParam(S, z613e493327    )
enum zbb1f615c1d{z3250bb2679};enum z93bcf30780{z8a85396f5b};enum zb06a9f15ae{z00deac365e,z9cbfedf63b};
#define z5bbcf8be2c          (0x2550+394-0x26d8)
static char msg[(0x1602+1205-0x19b7)];typedef volatile struct{uint32_t z5113d6a8d4;uint32_t zbc53575f66;uint32_t z937b9aa588;uint32_t zad12366ed6;uint32_t z224b61a322;uint32_t z05a38d9688;uint32_t z96ef554f24;uint32_t z41cf12af39;uint32_t version;uint32_t za6d2280101[(0x234+446-0x3d2)];uint32_t zcf124b5c7b[(0x1073+1892-0x17b7)];uint32_t ze963c724bd[(0xfa3+5686-0x25b9)];uint32_t z5933ba9eef[(0xaa3+4625-0x1c94)];uint32_t zb527a777b1[(0x180d+2749-0x22aa)];uint32_t zbb6601ed0b[(0x4fc+1238-0x9b2)];uint32_t zb2bfe8fd67[(0xa62+2611-0x1475)];uint32_t z9d9906152b[(0x202f+1688-0x26a7)];uint32_t z0cb32ea574[(0x118f+4832-0x244f)];uint32_t z80200c8b92[(0x39b+4670-0x15b9)];uint32_t z0fac3ac62e[(0x244+820-0x558)];uint32_t z47dac54a30[(0xdb5+4802-0x2057)];uint32_t z00cc33cb8e[(0xbf4+2525-0x15b1)];uint32_t z0c6f5b8493[(0x7af+3245-0x143c)];uint32_t zb741e2a3ac[(0x1b25+95-0x1b64)];uint32_t z239d126e9d;uint32_t zdbfe9a161d;uint32_t z2292c73d55;uint32_t z2ccd606be7;uint32_t z3c2f87c6d7;uint32_t z20b2ce87e9;uint32_t zb4886fe8bc[(0x1a0d+2424-0x2365)];uint32_t zb4e57f0e16[(0x12cc+3161-0x1f05)];uint32_t z6aa32fb21c;uint32_t z9d6cfd9b17;uint32_t reset;uint32_t z4e3fbb236e;}z555c3b09c0;static void mdlInitializeSizes(SimStruct*S){uint32_t i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73" "\n" "\x20\x70\x61\x73\x73\x65\x64\x3a\x20\x25\x64" "\n" "\x20\x65\x78\x70\x65\x63\x74\x65\x64\x3a\x20\x25\x64" "\n",ssGetSFcnParamsCount(S),ssGetNumSFcnParams(S));ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x7e3+1858-0xf25));ssSetNumDiscStates(S,(0xbab+3076-0x17af));ssSetNumInputPorts(S,(0x31+6616-0x1a09));ssSetNumInputPorts(S,(0x12a7+1372-0x1803));ssSetNumSampleTimes(S,(0xb48+6886-0x262d));ssSetNumRWork(S,z8a85396f5b);ssSetNumIWork(S,z3250bb2679);ssSetNumPWork(S,z9cbfedf63b);ssSetNumModes(S,(0x81b+7627-0x25e6));ssSetNumNonsampledZCs(S,(0x1144+2126-0x1992));for(i=(0x1356+1967-0x1b05);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x153f+1894-0x1ca5));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE|SS_OPTION_PLACE_ASAP);}static void mdlInitializeSampleTimes(SimStruct*S){ssSetSampleTime(S,(0xd2d+2583-0x1744),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x122+4933-0x1467),FIXED_IN_MINOR_STEP_OFFSET);}static void sg_ModelLoad(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uintptr_t z70fcda5f5d;int moduleId=(int)mxGetScalar(ze13f49a01f);char*boardName=io3xxGetBoardNameSgLib(moduleId);z555c3b09c0*serial;z70fcda5f5d=(uintptr_t)io3xxGetAddressSgLib((int)mxGetPr(ze13f49a01f)[(0x887+4837-0x1b6c)],SG_FPGA_IO3XX_BAR2);if(z70fcda5f5d==(0xcfb+1940-0x148f)){ssSetErrorStatus(S,pSgErrorStr);return;}uint32_t zf7ccd17be8=(0x1b10+3046-0x26f6);if(sg_fpga_io3xx_getCmBaseAddress(moduleId,SERIAL_BASE,&zf7ccd17be8)){sprintf(msg,"\x25\x73\x20\x53\x65\x72\x69\x61\x6c\x20\x53\x65\x74\x75\x70\x20\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x4f\x66\x66\x73\x65\x74\x20\x6c\x6f\x6f\x6b\x75\x70\x20\x75\x6e\x73\x75\x63\x63\x65\x73\x73\x66\x75\x6c\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}serial=(z555c3b09c0*)(z70fcda5f5d+zf7ccd17be8);ssSetPWorkValue(S,z00deac365e,(void*)serial);if(sg_isFirstModelLoad()){if(sg_fpga_io3xx_checkCodeModuleVersion(serial->version,z5bbcf8be2c,moduleId)){sprintf(msg,"\x25\x73\x20\x77\x72\x6f\x6e\x67\x20\x76\x65\x72\x73\x69\x6f\x6e\x20\x6f\x66\x20\x53\x65\x72\x69\x61\x6c\x20\x53\x65\x74\x75\x70\x20\x63\x6f\x64\x65\x20\x6d\x6f\x64\x75\x6c\x65\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}}
#endif
}static void sg_ModelStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_t i,channel;uint32_t zea31a1697d,z8b0a3fe5b4;z555c3b09c0*serial=(z555c3b09c0*)ssGetPWorkValue(S,z00deac365e);zea31a1697d=(0x1fb1+961-0x2372);for(i=(0x1e0+2293-0xad5);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x80c+5051-0x1bc6);serial->zb527a777b1[channel]=(uint32_t)mxGetPr(z9c505d438b)[i];serial->zbb6601ed0b[channel]=(uint32_t)mxGetPr(z93b46933bc)[i];serial->zb2bfe8fd67[channel]=(uint32_t)mxGetPr(z80397074ac)[i];serial->z9d9906152b[channel]=(uint32_t)mxGetPr(zcf4c56ba2e)[i]-(0x1557+333-0x16a3);serial->zb741e2a3ac[channel]=(uint32_t)mxGetPr(z08c7a44908)[i];z8b0a3fe5b4=(uint32_t)mxGetPr(z6f4a9190dd)[i];if(z8b0a3fe5b4!=(0x1748+518-0x194e)){zea31a1697d|=((0x1a0c+1242-0x1ee5)<<channel);zea31a1697d|=((0x1239+2724-0x1cdc)<<channel);}}serial->z4e3fbb236e=zea31a1697d;SG_PRINTF(DEBUG,"\x65\x6e\x61\x62\x6c\x65\x5f\x68\x61\x6c\x66\x5f\x64\x75\x70\x6c\x65\x78\x5f\x72\x65\x67\x3a\x20\x25\x78" "\n",zea31a1697d);
#endif
}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
#endif
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE
#endif
}
#include "sg_sfcn_glue.h"   

