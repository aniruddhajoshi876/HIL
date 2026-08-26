// Copyright 2006-2026 Speedgoat GmbH

#define 	S_FUNCTION_LEVEL 	(0x585+1978-0xd3d)
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_fpga_ssi_sniffer_sf_1
#include 	<stddef.h>
#include 	<stdlib.h>
#include  <stdint.h>
#include 	"simstruc.h"
#include "fixedpoint.h"
#ifdef 		MATLAB_MEX_FILE
#include 	"mex.h"
#endif
#ifndef     MATLAB_MEX_FILE
#include    "sg_common.h"
#include    "sg_fpga_io3xx_util.h"
#include    "sg_printf.h"
#include    "sg_fpga_io3xx_scatter_gather_dma.h"
#endif
#include    "sg_callback.h"
#define ze13f49a01f         ssGetSFcnParam(S, (0x1158+2047-0x1957) ) 
#define za9d8fb6bcf           ssGetSFcnParam(S, (0x855+3203-0x14d7) ) 
#define zc4be5b4c26          ssGetSFcnParam(S, (0x11d0+5330-0x26a0) )
#define z7623fde002       ssGetSFcnParam(S, (0x212d+1217-0x25eb) )
#define z9ae511755d    ssGetSFcnParam(S, (0x8d2+7109-0x2493) )
#define z404f77167d       ssGetSFcnParam(S, (0x29d+8178-0x228a) )
#define z1fef3e2966          ssGetSFcnParam(S, (0x1425+2833-0x1f30) )
#define z0fbad31890         ssGetSFcnParam(S, (0x1e34+1528-0x2425) )
#define z0422d86ad2           ssGetSFcnParam(S, (0xf76+5764-0x25f2) )
#define z596b77cbe5            ssGetSFcnParam(S, (0xd24+1104-0x116b) ) 
#define z3832b85a32         ssGetSFcnParam(S, (0xb3d+6814-0x25d1))
#define z19b9dfa260    ssGetSFcnParam(S, (0x1137+2138-0x1986))
#define zdf24515981                         ((0x5a5+3365-0x12be))
#define z5bbcf8be2c           (0x155+7838-0x1ff2)
#define z2e6483d505            ((0x5cb+685-0x878))
#define zc5ce4cb81a            ((0x2232+738-0x2514))
#define z2b17e2ee3b            ((0x161+3048-0xd47))
#define z0194338df7       ((0xc9f+4307-0x1d72))
#define z66c66efec7  ((0x3e3+1761-0xac3))
#define zf0d3ea3e3b (0xadf+5262-0x1f2d)
typedef struct{uint32_t zb5504d2c07[(0xc4f+4826-0x1f09)];uint32_t data[(0x317+7110-0x1ebd)];uint32_t z234ec7021f[(0x63b+3945-0x1584)];uint32_t zb871a780a7;uint32_t version;uint32_t zee33e75c3e;uint32_t ze9fdea3865;uint32_t reserved[(0x1b88+1818-0x2296)];uint32_t zb8e1ca7d97[(0x16bc+769-0x199d)];uint32_t zfe02a5571e[(0x1d58+2504-0x2700)];}zc6fada630a;static char msg[(0x6e5+5775-0x1c74)];
#ifndef MATLAB_MEX_FILE
static io3xx_sgdma_Handle*zf30aa153dd(SimStruct*S);
#endif
#ifndef MATLAB_MEX_FILE
static io3xx_sgdma_Handle*zf30aa153dd(SimStruct*S){int i;int channel;int z5056c09cb0[zf0d3ea3e3b];zc6fada630a*z4c44fec2fd;io3xx_sgdma_Handle*ze639490358;io3xx_sgdma_Error z9b71752fdf;uint32_t zcd308d01c9=(0x1da6+1939-0x2539);int moduleId=(int)mxGetScalar(ze13f49a01f);int z979d8f17a3=(int)mxGetN(za9d8fb6bcf);for(i=(0x14d4+348-0x1630);i<z979d8f17a3;i++){channel=(int)mxGetPr(za9d8fb6bcf)[i]-(0x1b88+430-0x1d35);z5056c09cb0[i]=channel;zcd308d01c9|=((0xf0+7139-0x1cd2)<<channel);}uint32_t zf7ccd17be8=(0xb33+3213-0x17c0);if(sg_fpga_io3xx_getCmBaseAddress(moduleId,SSI_SNIFFER_BASE,&zf7ccd17be8)){SG_PRINTF(DEBUG,"\x25\x73\x3a\x20\x53\x53\x49\x20\x53\x4e\x49\x46\x46\x45\x52\x20\x62\x6c\x6f\x63\x6b\x3a\x20\x43\x6f\x75\x6c\x64\x20\x6e\x6f\x74\x20\x64\x65\x74\x65\x72\x6d\x69\x6e\x65\x20\x63\x6f\x64\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x6f\x66\x66\x73\x65\x74\x21" "\n",io3xxGetBoardNameSgLib(moduleId));return NULL;}bool z66bd01a1ae=false;z9b71752fdf=io3xx_sgdma_initialize(moduleId,sizeof(zc6fada630a),zf7ccd17be8,z66bd01a1ae,&ze639490358);if(z9b71752fdf){SG_PRINTF(DEBUG,"\x53\x53\x49\x20\x53\x6e\x69\x66\x66\x65\x72\x20\x62\x6c\x6f\x63\x6b\x3a\x20\x53\x47\x20\x44\x4d\x41\x20\x69\x6e\x69\x74\x69\x61\x6c\x69\x7a\x61\x74\x69\x6f\x6e\x20\x66\x61\x69\x6c\x65\x64\x20\x77\x69\x74\x68\x20\x65\x72\x72\x6f\x72\x20\x63\x6f\x64\x65\x3a\x20\x25\x64" "\n",z9b71752fdf);return NULL;}SG_PRINTF(DEBUG,"\x53\x53\x49\x20\x53\x6e\x69\x66\x66\x65\x72\x20\x62\x6c\x6f\x63\x6b\x3a\x20\x53\x47\x20\x44\x4d\x41\x20\x69\x6e\x69\x74\x69\x61\x6c\x69\x7a\x65\x64" "\n");z4c44fec2fd=(zc6fada630a*)io3xx_sgdma_getShadowRegister(ze639490358);io3xx_sgdma_enqueueConstValue(ze639490358,&(z4c44fec2fd->zb871a780a7),zcd308d01c9);io3xx_sgdma_enqueueConstValue(ze639490358,&(z4c44fec2fd->zb871a780a7),(0x1464+1121-0x18c5));io3xx_sgdma_enqueueData(ze639490358,&(z4c44fec2fd->zee33e75c3e),sizeof(z4c44fec2fd->zee33e75c3e),IO3XX_SGDMA_READ);io3xx_sgdma_enqueueIndexList(ze639490358,&(z4c44fec2fd->data[(0xe1+6431-0x1a00)]),sizeof(z4c44fec2fd->data[(0xeea+1412-0x146e)]),IO3XX_SGDMA_READ,z5056c09cb0,z979d8f17a3);io3xx_sgdma_enqueueIndexList(ze639490358,&(z4c44fec2fd->zfe02a5571e[(0x13c8+850-0x171a)]),sizeof(z4c44fec2fd->zfe02a5571e[(0x2662+56-0x269a)]),IO3XX_SGDMA_READ,z5056c09cb0,z979d8f17a3);io3xx_sgdma_enqueueIndexList(ze639490358,&(z4c44fec2fd->z234ec7021f[(0xac1+4821-0x1d96)]),sizeof(z4c44fec2fd->z234ec7021f[(0xc54+4207-0x1cc3)]),IO3XX_SGDMA_READ,z5056c09cb0,z979d8f17a3);io3xx_sgdma_enqueueData(ze639490358,&(z4c44fec2fd->ze9fdea3865),sizeof(z4c44fec2fd->ze9fdea3865),IO3XX_SGDMA_READ);io3xx_sgdma_enqueueIndexList(ze639490358,&(z4c44fec2fd->zb8e1ca7d97[(0x6fb+99-0x75e)]),sizeof(z4c44fec2fd->zb8e1ca7d97[(0x1635+3310-0x2323)]),IO3XX_SGDMA_READ,z5056c09cb0,z979d8f17a3);io3xx_sgdma_checkAndCorrect16ByteBoundary(ze639490358);return ze639490358;}
#endif 
static void mdlInitializeSizes(SimStruct*S){uint32_t i,za0df33019b;int z2694a87c6a,zd2f587b082,z75f75830fc,zec9bbc2f4f,z724504f38b;DTypeId z469f88b293=(0x7e1+5985-0x1f42);ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x2b7+8943-0x25a6));ssSetNumDiscStates(S,(0x2102+1312-0x2622));za0df33019b=(0x1af6+2923-0x2661);if(mxGetPr(zc4be5b4c26)[(0x172c+3242-0x23d6)]){z2694a87c6a=za0df33019b;za0df33019b++;}if(mxGetPr(z7623fde002)[(0x15f+6778-0x1bd9)]){zd2f587b082=za0df33019b;za0df33019b++;}if(mxGetPr(z9ae511755d)[(0x15fa+745-0x18e3)]){z75f75830fc=za0df33019b;za0df33019b++;}if(mxGetPr(z404f77167d)[(0x1c5b+493-0x1e48)]){zec9bbc2f4f=za0df33019b;za0df33019b++;}if(mxGetPr(z1fef3e2966)[(0x1dba+1925-0x253f)]){z724504f38b=za0df33019b;za0df33019b++;}ssSetNumOutputPorts(S,za0df33019b);for(i=(0x1ce9+2217-0x2592);i<za0df33019b;i++){ssSetOutputPortWidth(S,i,mxGetN(za9d8fb6bcf));}if(mxGetPr(zc4be5b4c26)[(0x10ff+5275-0x259a)]){
#ifdef MATLAB_MEX_FILE
z469f88b293=ssRegisterDataTypeInteger(S,(0xf16+4810-0x21e0),(0x7a0+919-0xaf7),(0x10d4+1378-0x1635));if(z469f88b293==INVALID_DTYPE_ID){sprintf(msg,"\x43\x61\x6e\x6e\x6f\x74\x20\x72\x65\x67\x69\x73\x74\x65\x72\x20\x36\x34\x20\x62\x69\x74\x20\x69\x6e\x74\x65\x67\x65\x72\x20\x74\x79\x70\x65");ssSetErrorStatus(S,msg);return;}
#else
z469f88b293=SS_DOUBLE;
#endif
ssSetOutputPortDataType(S,z2694a87c6a,z469f88b293);}if(mxGetPr(z7623fde002)[(0x331+7501-0x207e)]){ssSetOutputPortDataType(S,zd2f587b082,SS_UINT32);}if(mxGetPr(z9ae511755d)[(0x1055+497-0x1246)]){ssSetOutputPortDataType(S,z75f75830fc,SS_BOOLEAN);}if(mxGetPr(z404f77167d)[(0x985+4978-0x1cf7)]){ssSetOutputPortDataType(S,zec9bbc2f4f,SS_DOUBLE);}if(mxGetPr(z1fef3e2966)[(0xfeb+4679-0x2232)]){ssSetOutputPortDataType(S,z724504f38b,SS_BOOLEAN);}ssSetNumSampleTimes(S,(0x623+228-0x706));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x16f7+392-0x187f));ssSetNumNonsampledZCs(S,(0xe23+5254-0x22a9));for(i=(0x4+6568-0x19ac);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x172f+1280-0x1c2f));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x13f+3520-0xeff)]==-1.0){ssSetSampleTime(S,(0x18a3+883-0x1c16),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x18a7+695-0x1b5e),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x1216+4169-0x225f),mxGetPr(z3832b85a32)[(0x49b+3098-0x10b5)]);ssSetOffsetTime(S,(0xd9b+3401-0x1ae4),0.0);}}static void sg_ModelLoad(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uintptr_t z70fcda5f5d;volatile zc6fada630a*z95f3512820;int moduleId=(int)mxGetScalar(ze13f49a01f);char*boardName=io3xxGetBoardNameSgLib(moduleId);z70fcda5f5d=(uintptr_t)io3xxGetAddressSgLib((int)mxGetPr(ze13f49a01f)[(0x61c+7022-0x218a)],SG_FPGA_IO3XX_BAR2);if(z70fcda5f5d==(0xbc3+3561-0x19ac)){ssSetErrorStatus(S,pSgErrorStr);return;}uint32_t zf7ccd17be8=(0x19c3+2349-0x22f0);if(sg_fpga_io3xx_getCmBaseAddress(moduleId,SSI_SNIFFER_BASE,&zf7ccd17be8)){sprintf(msg,"\x25\x73\x20\x53\x53\x49\x20\x53\x6e\x69\x66\x66\x65\x72\x20\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x4f\x66\x66\x73\x65\x74\x20\x6c\x6f\x6f\x6b\x75\x70\x20\x75\x6e\x73\x75\x63\x63\x65\x73\x73\x66\x75\x6c\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}z95f3512820=(zc6fada630a*)(z70fcda5f5d+zf7ccd17be8);ssSetPWorkValue(S,z0194338df7,(void*)z95f3512820);if(sg_isFirstModelLoad()){if(sg_fpga_io3xx_checkCodeModuleVersion(z95f3512820->version,z5bbcf8be2c,moduleId)){sprintf(msg,"\x25\x73\x20\x77\x72\x6f\x6e\x67\x20\x76\x65\x72\x73\x69\x6f\x6e\x20\x6f\x66\x20\x53\x53\x49\x20\x53\x6e\x69\x66\x66\x65\x72\x20\x63\x6f\x64\x65\x20\x6d\x6f\x64\x75\x6c\x65\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}}
#endif
}static void sg_ModelStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_t i,channel;volatile zc6fada630a*z95f3512820;io3xx_sgdma_Handle*ze639490358=NULL;int moduleId=(int)mxGetScalar(ze13f49a01f);z95f3512820=(zc6fada630a*)(ssGetPWorkValue(S,z0194338df7));ScatterGatherDmaState*z50b84cc2b5;sg_fpga_io3xx_getSharedSgDmaState(moduleId,&z50b84cc2b5);modelTimings_t*z993c0995f5;sg_fpga_io3xx_getSharedTimingInfo(moduleId,&z993c0995f5);bool enableDma=z50b84cc2b5->enableDma;if(z50b84cc2b5->useFpgaDmaController){if(z993c0995f5->sampleTime==ssGetSampleTime(S,(0x274+1285-0x779))){enableDma=true;}else{enableDma=false;}}if(enableDma){ze639490358=zf30aa153dd(S);if(!ze639490358){sprintf(msg,"\x53\x53\x49\x20\x53\x6e\x69\x66\x66\x65\x72\x20\x62\x6c\x6f\x63\x6b\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x69\x6e\x69\x74\x69\x61\x6c\x69\x7a\x65\x20\x74\x68\x65\x20\x44\x4d\x41\x20\x65\x6e\x67\x69\x6e\x65");ssSetErrorStatus(S,msg);return;}SG_PRINTF(DEBUG,"\x53\x53\x49\x20\x53\x6e\x69\x66\x66\x65\x72\x20\x62\x6c\x6f\x63\x6b\x3a\x20\x53\x63\x61\x74\x74\x65\x72\x2d\x67\x61\x74\x68\x65\x72\x20\x44\x4d\x41\x20\x65\x6e\x61\x62\x6c\x65\x64" "\n");}else{SG_PRINTF(DEBUG,"\x53\x53\x49\x20\x53\x6e\x69\x66\x66\x65\x72\x20\x62\x6c\x6f\x63\x6b\x3a\x20\x53\x63\x61\x74\x74\x65\x72\x2d\x67\x61\x74\x68\x65\x72\x20\x44\x4d\x41\x20\x64\x69\x73\x61\x62\x6c\x65\x64" "\n");}ssSetPWorkValue(S,z66c66efec7,ze639490358);for(i=(0x201+1104-0x651);i<(uint32_t)mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x24c4+15-0x24d2);z95f3512820->zb5504d2c07[channel]=(uint32_t)mxGetPr(z0fbad31890)[i];}
#endif
}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
volatile zc6fada630a*z95f3512820;uint32_t i,z0add1d1c25,channel,zeeeba54a90,z4691513e3c;uint32_t zb871a780a7,z234ec7021f,z0f5a3a2788,x;uint64_t data,z6621e6a4ed;uint32_t*z0476165a9a;uint64_t*zf5f4acf2ec;double*zaa42196a62;bool zee33e75c3e;bool*z75ec4c8663;z95f3512820=(zc6fada630a*)(ssGetPWorkValue(S,z0194338df7));zeeeba54a90=(z95f3512820->version&(0xf1d+4451-0x1f81));io3xx_sgdma_Handle*ze639490358=(io3xx_sgdma_Handle*)ssGetPWorkValue(S,z66c66efec7);if(ze639490358){z95f3512820=(zc6fada630a*)io3xx_sgdma_getShadowRegister(ze639490358);}else{z95f3512820=(zc6fada630a*)ssGetPWorkValue(S,z0194338df7);}if(ze639490358){io3xx_sgdma_Error z9b71752fdf=io3xx_sgdma_commitTransfer(ze639490358);if(z9b71752fdf!=IO3XX_SGDMA_NO_ERROR){SG_PRINTF(WARNING,"\x53\x53\x49\x20\x53\x6e\x69\x66\x66\x65\x72\x20\x62\x6c\x6f\x63\x6b\x3a\x20\x44\x4d\x41\x20\x74\x72\x61\x6e\x73\x66\x65\x72\x20\x66\x61\x69\x6c\x65\x64\x21" "\n");return;}}else{zb871a780a7=(0x11f5+2313-0x1afe);for(i=(0x1764+3233-0x2405);i<mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0xd14+5856-0x23f3);zb871a780a7|=((0xb15+4351-0x1c13)<<channel);}z95f3512820->zb871a780a7=zb871a780a7;z95f3512820->zb871a780a7=(0x2186+452-0x234a);}z4691513e3c=(uint32_t)mxGetPr(z19b9dfa260)[(0x9d6+3099-0x15f1)];for(i=(0x174a+1994-0x1f14);i<(uint32_t)mxGetN(za9d8fb6bcf);i++){channel=(uint32_t)mxGetPr(za9d8fb6bcf)[i]-(0x3df+7443-0x20f1);if(zeeeba54a90>(0x2cc+779-0x5d6)){zee33e75c3e=(z95f3512820->zee33e75c3e>>channel)&(0x558+208-0x627);}else{zee33e75c3e=((uint32_t)mxGetPr(z0422d86ad2)[i]==(0x18d+6963-0x1cbf));}data=z95f3512820->data[channel]+(((uint64_t)(z95f3512820->zfe02a5571e[channel]))<<(0xbf+1676-0x72b));z234ec7021f=z95f3512820->z234ec7021f[channel];if(zee33e75c3e){z6621e6a4ed=(0x25dd+200-0x26a5);for(x=(0x1843+3428-0x25a7);x<z234ec7021f;x++){if(x!=(0x90b+5215-0x1d6a)){data=data>>(0xad8+2648-0x152f);z6621e6a4ed=z6621e6a4ed<<(0x430+2316-0xd3b);}z6621e6a4ed=z6621e6a4ed|(data&(0x159d+1098-0x19e6));}data=z6621e6a4ed;}if((uint32_t)mxGetPr(z596b77cbe5)[(0x6c8+1466-0xc82)]==(0x646+8250-0x267e)){z6621e6a4ed=data;for(x=(0x8c7+2429-0x1244);x<z234ec7021f;x++){z6621e6a4ed>>=(0x914+1323-0xe3e);data^=z6621e6a4ed;}}z0add1d1c25=(0x561+6948-0x2085);if(mxGetPr(zc4be5b4c26)[(0xa5b+1588-0x108f)]){zf5f4acf2ec=(uint64_t*)ssGetOutputPortSignal(S,z0add1d1c25++);zf5f4acf2ec[i]=data;}if(mxGetPr(z7623fde002)[(0xfa9+526-0x11b7)]){z0476165a9a=(uint32_t*)ssGetOutputPortSignal(S,z0add1d1c25++);z0476165a9a[i]=z234ec7021f;}if(mxGetPr(z9ae511755d)[(0x49f+3049-0x1088)]){z75ec4c8663=(bool*)ssGetOutputPortSignal(S,z0add1d1c25++);z75ec4c8663[i]=(z95f3512820->ze9fdea3865>>channel)&(0x5c8+5506-0x1b49);}if(mxGetPr(z404f77167d)[(0x197b+1399-0x1ef2)]){z0f5a3a2788=(uint32_t)z95f3512820->zb8e1ca7d97[channel];zaa42196a62=(real_T*)ssGetOutputPortSignal(S,z0add1d1c25++);zaa42196a62[i]=((real_T)z4691513e3c)/z0f5a3a2788;}if(mxGetPr(z1fef3e2966)[(0x580+1837-0xcad)]){z75ec4c8663=(bool*)ssGetOutputPortSignal(S,z0add1d1c25++);z75ec4c8663[i]=zee33e75c3e;}}
#endif
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE
io3xx_sgdma_Handle*ze639490358=(io3xx_sgdma_Handle*)ssGetPWorkValue(S,z66c66efec7);if(ze639490358){io3xx_sgdma_cleanup(ze639490358);}
#endif
}
#include "sg_sfcn_glue.h"   

