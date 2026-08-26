// Copyright 2006-2026 Speedgoat GmbH

#define 	S_FUNCTION_LEVEL 	(0x5a6+3341-0x12b1)
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_fpga_spi_write_ram_sf_2
#include 	<stddef.h>
#include 	<stdlib.h>
#include  <stdint.h>
#include 	"simstruc.h"
#ifdef 		MATLAB_MEX_FILE
#include 	"mex.h"
#endif
#ifndef  MATLAB_MEX_FILE
#include "sg_common.h"
#include "sg_fpga_io3xx_util.h"
#include "sg_callback_legacy.h"
#endif
#include "sg_printf.h"
enum{zf80bd68bc8,ID,CHANNEL,ze344b15ab1,PCI_SLOT,za255258437,zdf24515981};
#define z533b11d03f           ssGetSFcnParam(S, zf80bd68bc8           )
#define z58f464b4bb                  ssGetSFcnParam(S, ID                  )
#define za9d8fb6bcf             ssGetSFcnParam(S, CHANNEL             )
#define z3832b85a32           ssGetSFcnParam(S, ze344b15ab1           )
#define ze7b39f8507            ssGetSFcnParam(S, PCI_SLOT            )
#define z9716afedb7           ssGetSFcnParam(S, za255258437           )
#define z2e6483d505            (0x180+4304-0x1250)
#define zc5ce4cb81a            (0x48c+653-0x719)
#define z2b17e2ee3b            (0xc5f+4630-0x1e74)
#define z93d7dbe681       (0x425+7408-0x2115)
#define z5bbcf8be2c          (0x159a+306-0x16ca)
#define z9a3f261491              851968
static char msg[(0x2403+646-0x2589)];struct z8e4b47c7a2{uint32_t z48d0bb18f6[(0x3f5+2968-0xf6d)];uint32_t z00d55f3f09[(0x173f+546-0x1941)];uint32_t z29b8f4aa12[(0x5a6+4264-0x162e)];uint32_t z12f528bf35[(0x262+9120-0x25e2)];uint32_t z38c71b4bf1[(0x1aad+742-0x1d73)];uint32_t z5ba6171f0d[(0x157d+3208-0x21e5)];uint32_t zc9a3e36bdf[(0xd04+2748-0x17a0)];uint32_t z40bf21df8f[(0x18c+6158-0x197a)];uint32_t z2e87e7e5d4[(0x812+941-0xb9f)];uint32_t zcb493c8a03[(0x10a0+2559-0x1a7f)];uint32_t z045c082819[(0xd47+1609-0x1370)];uint32_t ze2bbd49d5d[(0x1015+709-0x12ba)];uint32_t zf1dc9838ef[(0x14c5+4045-0x2472)];uint32_t z7885bab821[(0x219b+1289-0x2684)];uint32_t version;uint32_t zf64b65d5a7;uint32_t z184c2a9653;uint32_t z46c2b7bc26;uint32_t zbea4a89f24;uint32_t zdc0d676974;uint32_t z1b0476e135;uint32_t z90bc4b3324;uint32_t zfea0a3d037;uint32_t z83d556b26d;};static void mdlInitializeSizes(SimStruct*S){uint32_t i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x5ef+4960-0x194f));ssSetNumDiscStates(S,(0x386+1353-0x8cf));ssSetNumInputPorts(S,(0xd4f+353-0xeaf));ssSetInputPortWidth(S,(0xe37+2001-0x1608),mxGetN(z9716afedb7));ssSetInputPortDataType(S,(0x1e57+1397-0x23cc),SS_UINT8);ssSetInputPortDirectFeedThrough(S,(0x22bb+789-0x25d0),(0x15a+4693-0x13ae));ssSetInputPortRequiredContiguous(S,(0x739+6467-0x207c),(0x681+996-0xa64));ssSetNumOutputPorts(S,(0x107+6947-0x1c2a));ssSetNumSampleTimes(S,(0xc4f+5032-0x1ff6));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x6aa+2926-0x1218));ssSetNumNonsampledZCs(S,(0x4bf+760-0x7b7));for(i=(0x57b+1076-0x9af);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x1857+1118-0x1cb5));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x64a+7880-0x2512)]==-1.0){ssSetSampleTime(S,(0x1626+2924-0x2192),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x1861+2505-0x222a),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x768+5389-0x1c75),mxGetPr(z3832b85a32)[(0x1170+1430-0x1706)]);ssSetOffsetTime(S,(0x515+6891-0x2000),0.0);}}
#define MDL_START
static void mdlStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
int32_t bus,slot;uint32_t boardType;sg_fpga_io3xxModuleIdT moduleId;volatile struct z8e4b47c7a2*zb9f7147b6c;uint32_t za43d9fed9a,z43c341facf,z97287efa46,zeeeba54a90;boardType=(uint32_t)mxGetPr(z533b11d03f)[(0x64+8791-0x22bb)];if((int32_t)sg_fpga_IO3xxGetModuleId(boardType,&moduleId)<(0x1d91+1913-0x250a)){sprintf(msg,"\x53\x50\x49\x20\x62\x6c\x6f\x63\x6b\x3a\x20\x62\x6f\x61\x72\x64\x20\x74\x79\x70\x65\x20\x69\x6e\x63\x6f\x72\x72\x65\x63\x74\x2e");ssSetErrorStatus(S,msg);}if(mxGetN(ze7b39f8507)==(0x502+3188-0x1175)){bus=(0x36b+5952-0x1aab);slot=(int_T)mxGetPr(ze7b39f8507)[(0x7d9+5602-0x1dbb)];}else{bus=(int_T)mxGetPr(ze7b39f8507)[(0x511+8458-0x261b)];slot=(int_T)mxGetPr(ze7b39f8507)[(0xc72+113-0xce2)];}if(!io3xxGetAddressSgLib((int32_t)(int)mxGetPr(z58f464b4bb)[(0x197a+500-0x1b6e)],SG_FPGA_IO3XX_BAR2)){ssSetErrorStatus(S,pSgErrorStr);return;}zb9f7147b6c=(volatile struct z8e4b47c7a2*)((uintptr_t)io3xxGetAddressSgLib((int32_t)(int)mxGetPr(z58f464b4bb)[(0xd42+3526-0x1b08)],SG_FPGA_IO3XX_BAR2)+z9a3f261491);ssSetPWorkValue(S,z93d7dbe681,(void*)zb9f7147b6c);if(!sg_isModelInit()){za43d9fed9a=((zb9f7147b6c->version&3221225472)>>(0x1836+664-0x1ab0));z43c341facf=((zb9f7147b6c->version&1072693248)>>(0x8+1331-0x535));z97287efa46=((zb9f7147b6c->version&1047552)>>(0x463+3119-0x1088));zeeeba54a90=(zb9f7147b6c->version&(0x135a+4293-0x2020));if(za43d9fed9a==(0x460+7876-0x2322)&&z43c341facf==z9a3f261491&&z97287efa46==z5bbcf8be2c){SG_PRINTF(INFO,"\x25\x73\x20\x53\x50\x49\x20\x43\x6f\x64\x65\x20\x4d\x6f\x64\x75\x6c\x65\x20\x25\x64\x2e\x25\x64\x20\x73\x74\x61\x72\x74\x65\x64\x2e" "\n",moduleId.devname,z97287efa46,zeeeba54a90);}else{sprintf(msg,"\x25\x73\x20\x57\x72\x6f\x6e\x67\x20\x56\x65\x72\x73\x69\x6f\x6e\x20\x6f\x66\x20\x53\x50\x49\x20\x4d\x6f\x64\x75\x6c\x65\x2e" "\n" "\x20\x75\x6e\x69\x71\x75\x65\x49\x64\x3a\x20\x30\x78\x25\x78" "\n" "\x20\x6d\x61\x6a\x6f\x72\x56\x65\x72\x3a\x20\x30\x78\x25\x78" "\n" "\x20\x6d\x69\x6e\x6f\x72\x56\x65\x72\x3a\x20\x30\x78\x25\x78" "\n" "\x20\x73\x74\x61\x74\x75\x73\x3a\x20\x30\x78\x25\x78" "\n",moduleId.devname,z43c341facf,z97287efa46,zeeeba54a90,za43d9fed9a);ssSetErrorStatus(S,msg);}}
#endif
}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){
#ifndef MATLAB_MEX_FILE
volatile struct z8e4b47c7a2*zb9f7147b6c;uint8_t*zb425515a78;uint8_t i;uint32_t channel;zb9f7147b6c=(volatile struct z8e4b47c7a2*)ssGetPWorkValue(S,z93d7dbe681);channel=(uint32_t)mxGetPr(za9d8fb6bcf)[(0x4e8+7714-0x230a)]-(0xb44+703-0xe02);zb425515a78=(uint8_t*)ssGetInputPortSignal(S,(0x17a9+605-0x1a06));for(i=(0xb5c+959-0xf1b);i<mxGetN(z9716afedb7);i++){zb9f7147b6c->z48d0bb18f6[channel]=zb425515a78[i];zb9f7147b6c->z00d55f3f09[channel]=(uint32_t)mxGetPr(z9716afedb7)[i];zb9f7147b6c->z184c2a9653=(0x1f12+1162-0x239b)<<channel;zb9f7147b6c->z184c2a9653=(0x901+7171-0x2504);}
#endif
}static void mdlTerminate(SimStruct*S){
#ifndef MATLAB_MEX_FILE
#endif
}
#include "sg_sfcn_glue.h"   

