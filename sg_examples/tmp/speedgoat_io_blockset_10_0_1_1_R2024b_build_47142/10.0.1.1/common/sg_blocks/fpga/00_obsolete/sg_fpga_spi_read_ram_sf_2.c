// Copyright 2006-2026 Speedgoat GmbH

#define 	S_FUNCTION_LEVEL 	(0x23a+858-0x592)
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_fpga_spi_read_ram_sf_2
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
#define z2e6483d505            (0xea2+2992-0x1a52)
#define zc5ce4cb81a            (0x8bb+2007-0x1092)
#define z2b17e2ee3b            (0x922+5256-0x1da9)
#define z93d7dbe681       (0x18bf+2896-0x240f)
#define z5bbcf8be2c          (0x761+244-0x853)
#define z9a3f261491              851968
static char msg[(0xf25+3901-0x1d62)];struct z8e4b47c7a2{uint32_t z48d0bb18f6[(0x11d8+5385-0x26c1)];uint32_t z00d55f3f09[(0xe18+37-0xe1d)];uint32_t z29b8f4aa12[(0xd71+1569-0x1372)];uint32_t z12f528bf35[(0xd4+1831-0x7db)];uint32_t z38c71b4bf1[(0x417+4973-0x1764)];uint32_t z5ba6171f0d[(0x1012+863-0x1351)];uint32_t zc9a3e36bdf[(0x1697+1929-0x1e00)];uint32_t z40bf21df8f[(0x66b+7177-0x2254)];uint32_t z2e87e7e5d4[(0xd60+1787-0x143b)];uint32_t zcb493c8a03[(0x130+7685-0x1f15)];uint32_t z045c082819[(0x79b+3700-0x15ef)];uint32_t ze2bbd49d5d[(0x627+6061-0x1db4)];uint32_t zf1dc9838ef[(0xc56+1085-0x1073)];uint32_t z7885bab821[(0x44c+1788-0xb28)];uint32_t version;uint32_t zf64b65d5a7;uint32_t z184c2a9653;uint32_t z46c2b7bc26;uint32_t zbea4a89f24;uint32_t zdc0d676974;uint32_t z1b0476e135;uint32_t z90bc4b3324;uint32_t zfea0a3d037;uint32_t z83d556b26d;};static void mdlInitializeSizes(SimStruct*S){uint32_t i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x5b1+5593-0x1b8a));ssSetNumDiscStates(S,(0x11c6+4964-0x252a));ssSetNumInputPorts(S,(0x35a+8489-0x2483));ssSetNumOutputPorts(S,(0x2070+1560-0x2687));ssSetOutputPortWidth(S,(0x13a+2059-0x945),mxGetN(z9716afedb7));ssSetOutputPortDataType(S,(0xb6d+2289-0x145e),SS_UINT8);ssSetNumSampleTimes(S,(0x119a+2681-0x1c12));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x230+2372-0xb74));ssSetNumNonsampledZCs(S,(0xb5a+6855-0x2621));for(i=(0x17a+215-0x251);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x1a03+1899-0x216e));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x19+9920-0x26d9)]==-1.0){ssSetSampleTime(S,(0x5c5+1417-0xb4e),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x5f1+4312-0x16c9),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x1661+1546-0x1c6b),mxGetPr(z3832b85a32)[(0xa05+7353-0x26be)]);ssSetOffsetTime(S,(0x127f+400-0x140f),0.0);}}
#define MDL_START
static void mdlStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
int32_t bus,slot;uint32_t boardType;sg_fpga_io3xxModuleIdT moduleId;volatile struct z8e4b47c7a2*zb9f7147b6c;uint32_t za43d9fed9a,z43c341facf,z97287efa46,zeeeba54a90;boardType=(uint32_t)mxGetPr(z533b11d03f)[(0x2f2+6934-0x1e08)];if((int32_t)sg_fpga_IO3xxGetModuleId(boardType,&moduleId)<(0x104b+2196-0x18df)){sprintf(msg,"\x53\x50\x49\x20\x62\x6c\x6f\x63\x6b\x3a\x20\x62\x6f\x61\x72\x64\x20\x74\x79\x70\x65\x20\x69\x6e\x63\x6f\x72\x72\x65\x63\x74\x2e");ssSetErrorStatus(S,msg);}if(mxGetN(ze7b39f8507)==(0x9bf+1362-0xf10)){bus=(0x378+8471-0x248f);slot=(int_T)mxGetPr(ze7b39f8507)[(0xe8b+2047-0x168a)];}else{bus=(int_T)mxGetPr(ze7b39f8507)[(0x14b2+766-0x17b0)];slot=(int_T)mxGetPr(ze7b39f8507)[(0x485+3400-0x11cc)];}if(!io3xxGetAddressSgLib((int32_t)(int)mxGetPr(z58f464b4bb)[(0x1aa0+893-0x1e1d)],SG_FPGA_IO3XX_BAR2)){ssSetErrorStatus(S,pSgErrorStr);return;}zb9f7147b6c=(volatile struct z8e4b47c7a2*)((uintptr_t)io3xxGetAddressSgLib((int32_t)(int)mxGetPr(z58f464b4bb)[(0x7b3+7930-0x26ad)],SG_FPGA_IO3XX_BAR2)+z9a3f261491);ssSetPWorkValue(S,z93d7dbe681,(void*)zb9f7147b6c);if(!sg_isModelInit()){za43d9fed9a=((zb9f7147b6c->version&3221225472)>>(0x3ed+1353-0x918));z43c341facf=((zb9f7147b6c->version&1072693248)>>(0x1153+2258-0x1a1f));z97287efa46=((zb9f7147b6c->version&1047552)>>(0x9e3+189-0xa96));zeeeba54a90=(zb9f7147b6c->version&(0x155f+5270-0x25f6));if(za43d9fed9a==(0x26a+7959-0x217f)&&z43c341facf==z9a3f261491&&z97287efa46==z5bbcf8be2c){SG_PRINTF(INFO,"\x25\x73\x20\x53\x50\x49\x20\x43\x6f\x64\x65\x20\x4d\x6f\x64\x75\x6c\x65\x20\x25\x64\x2e\x25\x64\x20\x73\x74\x61\x72\x74\x65\x64\x2e" "\n",moduleId.devname,z97287efa46,zeeeba54a90);}else{sprintf(msg,"\x25\x73\x20\x57\x72\x6f\x6e\x67\x20\x56\x65\x72\x73\x69\x6f\x6e\x20\x6f\x66\x20\x53\x50\x49\x20\x4d\x6f\x64\x75\x6c\x65\x2e" "\n" "\x20\x75\x6e\x69\x71\x75\x65\x49\x64\x3a\x20\x30\x78\x25\x78" "\n" "\x20\x6d\x61\x6a\x6f\x72\x56\x65\x72\x3a\x20\x30\x78\x25\x78" "\n" "\x20\x6d\x69\x6e\x6f\x72\x56\x65\x72\x3a\x20\x30\x78\x25\x78" "\n" "\x20\x73\x74\x61\x74\x75\x73\x3a\x20\x30\x78\x25\x78" "\n",moduleId.devname,z43c341facf,z97287efa46,zeeeba54a90,za43d9fed9a);ssSetErrorStatus(S,msg);}}
#endif
}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){
#ifndef MATLAB_MEX_FILE
volatile struct z8e4b47c7a2*zb9f7147b6c;uint8_t*zb425515a78;uint8_t i;uint32_t channel;zb9f7147b6c=(volatile struct z8e4b47c7a2*)ssGetPWorkValue(S,z93d7dbe681);channel=(uint32_t)mxGetPr(za9d8fb6bcf)[(0x6b5+1688-0xd4d)]-(0x147+8426-0x2230);zb425515a78=(uint8_t*)ssGetOutputPortSignal(S,(0x2d4+7707-0x20ef));for(i=(0xc1b+5261-0x20a8);i<mxGetN(z9716afedb7);i++){zb9f7147b6c->z00d55f3f09[channel]=(uint32_t)mxGetPr(z9716afedb7)[i];zb425515a78[i]=zb9f7147b6c->z045c082819[channel];}
#endif
}static void mdlTerminate(SimStruct*S){
#ifndef MATLAB_MEX_FILE
#endif
}
#include "sg_sfcn_glue.h"   

