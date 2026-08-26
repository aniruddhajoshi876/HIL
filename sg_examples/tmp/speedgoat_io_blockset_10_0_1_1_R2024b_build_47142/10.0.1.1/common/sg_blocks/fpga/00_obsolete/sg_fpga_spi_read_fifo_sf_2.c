// Copyright 2006-2026 Speedgoat GmbH

#define 	S_FUNCTION_LEVEL 	(0x177f+170-0x1827)
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_fpga_spi_read_fifo_sf_2
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
enum{zf80bd68bc8,ID,CHANNEL,ze344b15ab1,PCI_SLOT,zdf24515981};
#define z533b11d03f           ssGetSFcnParam(S, zf80bd68bc8           )
#define z58f464b4bb                  ssGetSFcnParam(S, ID                  )
#define za9d8fb6bcf             ssGetSFcnParam(S, CHANNEL             )
#define z3832b85a32           ssGetSFcnParam(S, ze344b15ab1           )
#define ze7b39f8507            ssGetSFcnParam(S, PCI_SLOT            )
#define z2e6483d505            (0x832+873-0xb9b)
#define zc5ce4cb81a            (0x1b0a+1666-0x218c)
#define z2b17e2ee3b            (0xda4+448-0xf63)
#define z93d7dbe681       (0x25c7+120-0x263f)
#define z5bbcf8be2c          (0x13f6+1000-0x17dc)
#define z9a3f261491              851968
static char msg[(0x26c5+315-0x2700)];struct z8e4b47c7a2{uint32_t z48d0bb18f6[(0x69a+3637-0x14af)];uint32_t z00d55f3f09[(0x341+3477-0x10b6)];uint32_t z29b8f4aa12[(0x182b+2312-0x2113)];uint32_t z12f528bf35[(0x51d+247-0x5f4)];uint32_t z38c71b4bf1[(0x2c3+6356-0x1b77)];uint32_t z5ba6171f0d[(0x11dc+1730-0x187e)];uint32_t zc9a3e36bdf[(0x54a+1843-0xc5d)];uint32_t z40bf21df8f[(0x1876+400-0x19e6)];uint32_t z2e87e7e5d4[(0x15f4+4093-0x25d1)];uint32_t zcb493c8a03[(0x13ec+150-0x1462)];uint32_t z045c082819[(0x1954+3226-0x25ce)];uint32_t ze2bbd49d5d[(0x211d+614-0x2363)];uint32_t zf1dc9838ef[(0x1122+931-0x14a5)];uint32_t z7885bab821[(0x13a6+274-0x1498)];uint32_t version;uint32_t zf64b65d5a7;uint32_t z184c2a9653;uint32_t z46c2b7bc26;uint32_t zbea4a89f24;uint32_t zdc0d676974;uint32_t z1b0476e135;uint32_t z90bc4b3324;uint32_t zfea0a3d037;uint32_t z83d556b26d;};static void mdlInitializeSizes(SimStruct*S){uint32_t i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0xd47+4393-0x1e70));ssSetNumDiscStates(S,(0x5dc+2301-0xed9));ssSetNumInputPorts(S,(0x23a1+116-0x2414));ssSetInputPortWidth(S,(0x1bcc+87-0x1c23),(0xc2d+2497-0x15ed));ssSetInputPortDataType(S,(0x24b+701-0x508),SS_UINT8);ssSetInputPortDirectFeedThrough(S,(0x1da+3987-0x116d),(0x90d+434-0xabe));ssSetInputPortRequiredContiguous(S,(0x104b+4038-0x2011),(0x180b+3154-0x245c));ssSetNumOutputPorts(S,(0x854+7776-0x26b2));ssSetOutputPortWidth(S,(0x495+3737-0x132e),(0x1a35+1258-0x1f1e));ssSetOutputPortDataType(S,(0x12df+3550-0x20bd),SS_UINT8);ssSetOutputPortWidth(S,(0x920+854-0xc75),(0x7e3+5784-0x1d7c));ssSetOutputPortDataType(S,(0x4ab+5672-0x1ad2),SS_UINT8);ssSetNumSampleTimes(S,(0x748+1182-0xbe5));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x895+5711-0x1ee4));ssSetNumNonsampledZCs(S,(0xf27+5623-0x251e));for(i=(0x12f9+3905-0x223a);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x71+113-0xe2));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x685+4469-0x17fa)]==-1.0){ssSetSampleTime(S,(0x14b6+1248-0x1996),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x118d+2799-0x1c7c),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x9fb+4717-0x1c68),mxGetPr(z3832b85a32)[(0x208+5427-0x173b)]);ssSetOffsetTime(S,(0x219+791-0x530),0.0);}}
#define MDL_START
static void mdlStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
int32_t bus,slot;uint32_t boardType;sg_fpga_io3xxModuleIdT moduleId;volatile struct z8e4b47c7a2*zb9f7147b6c;uint32_t za43d9fed9a,z43c341facf,z97287efa46,zeeeba54a90;boardType=(uint32_t)mxGetPr(z533b11d03f)[(0x1671+605-0x18ce)];if((int32_t)sg_fpga_IO3xxGetModuleId(boardType,&moduleId)<(0x2a4+6029-0x1a31)){sprintf(msg,"\x53\x50\x49\x20\x62\x6c\x6f\x63\x6b\x3a\x20\x62\x6f\x61\x72\x64\x20\x74\x79\x70\x65\x20\x69\x6e\x63\x6f\x72\x72\x65\x63\x74\x2e");ssSetErrorStatus(S,msg);}if(mxGetN(ze7b39f8507)==(0xd2+6907-0x1bcc)){bus=(0x1c48+1679-0x22d7);slot=(int_T)mxGetPr(ze7b39f8507)[(0xc95+1348-0x11d9)];}else{bus=(int_T)mxGetPr(ze7b39f8507)[(0x8f8+295-0xa1f)];slot=(int_T)mxGetPr(ze7b39f8507)[(0x345+1181-0x7e1)];}if(!io3xxGetAddressSgLib((int32_t)(int)mxGetPr(z58f464b4bb)[(0x1b1+1524-0x7a5)],SG_FPGA_IO3XX_BAR2)){ssSetErrorStatus(S,pSgErrorStr);return;}zb9f7147b6c=(volatile struct z8e4b47c7a2*)((uintptr_t)io3xxGetAddressSgLib((int32_t)(int)mxGetPr(z58f464b4bb)[(0x12da+3559-0x20c1)],SG_FPGA_IO3XX_BAR2)+z9a3f261491);ssSetPWorkValue(S,z93d7dbe681,(void*)zb9f7147b6c);if(!sg_isModelInit()){za43d9fed9a=((zb9f7147b6c->version&3221225472)>>(0x151a+1813-0x1c11));z43c341facf=((zb9f7147b6c->version&1072693248)>>(0x2182+806-0x24a2));z97287efa46=((zb9f7147b6c->version&1047552)>>(0x40b+566-0x637));zeeeba54a90=(zb9f7147b6c->version&(0x1139+3828-0x1c2e));if(za43d9fed9a==(0x4c3+2236-0xd7d)&&z43c341facf==z9a3f261491&&z97287efa46==z5bbcf8be2c){SG_PRINTF(INFO,"\x25\x73\x20\x53\x50\x49\x20\x43\x6f\x64\x65\x20\x4d\x6f\x64\x75\x6c\x65\x20\x25\x64\x2e\x25\x64\x20\x73\x74\x61\x72\x74\x65\x64\x2e" "\n",moduleId.devname,z97287efa46,zeeeba54a90);}else{sprintf(msg,"\x25\x73\x20\x57\x72\x6f\x6e\x67\x20\x56\x65\x72\x73\x69\x6f\x6e\x20\x6f\x66\x20\x53\x50\x49\x20\x4d\x6f\x64\x75\x6c\x65\x2e" "\n" "\x20\x75\x6e\x69\x71\x75\x65\x49\x64\x3a\x20\x30\x78\x25\x78" "\n" "\x20\x6d\x61\x6a\x6f\x72\x56\x65\x72\x3a\x20\x30\x78\x25\x78" "\n" "\x20\x6d\x69\x6e\x6f\x72\x56\x65\x72\x3a\x20\x30\x78\x25\x78" "\n" "\x20\x73\x74\x61\x74\x75\x73\x3a\x20\x30\x78\x25\x78" "\n",moduleId.devname,z43c341facf,z97287efa46,zeeeba54a90,za43d9fed9a);ssSetErrorStatus(S,msg);}}
#endif
}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){
#ifndef MATLAB_MEX_FILE
volatile struct z8e4b47c7a2*zb9f7147b6c;uint8_t*zb425515a78,*za8727e5143,*zf42484719c;uint8_t i;uint32_t channel;zb9f7147b6c=(volatile struct z8e4b47c7a2*)ssGetPWorkValue(S,z93d7dbe681);channel=(uint32_t)mxGetPr(za9d8fb6bcf)[(0x77c+3786-0x1646)]-(0x372+8325-0x23f6);zf42484719c=(uint8_t*)ssGetInputPortSignal(S,(0x1673+2521-0x204c));za8727e5143=(uint8_t*)ssGetOutputPortSignal(S,(0x22fd+810-0x2627));zb425515a78=(uint8_t*)ssGetOutputPortSignal(S,(0x5a9+5831-0x1c6f));for(i=(0x9c0+2925-0x152d);i<(0x97c+2829-0x138a);i++){zb425515a78[i]=(0x10cb+2954-0x1c55);}za8727e5143[(0xfab+31-0xfca)]=(0x9d+4575-0x127c);while(zb9f7147b6c->ze2bbd49d5d[channel]<zf42484719c[(0xbbc+1572-0x11e0)]);za8727e5143[(0x255+112-0x2c5)]=zb9f7147b6c->ze2bbd49d5d[channel];for(i=(0xb9a+498-0xd8c);i<za8727e5143[(0x69c+6176-0x1ebc)];i++){zb9f7147b6c->z83d556b26d=(0x3f7+7367-0x20bd)<<channel;zb9f7147b6c->z83d556b26d=(0x167b+4191-0x26da);zb425515a78[i]=zb9f7147b6c->z045c082819[channel];}
#endif
}static void mdlTerminate(SimStruct*S){
#ifndef MATLAB_MEX_FILE
#endif
}
#include "sg_sfcn_glue.h"   

