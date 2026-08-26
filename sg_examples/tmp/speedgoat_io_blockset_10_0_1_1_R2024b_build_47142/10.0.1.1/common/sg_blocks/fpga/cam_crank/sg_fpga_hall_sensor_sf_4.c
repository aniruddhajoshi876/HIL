// Copyright 2006-2026 Speedgoat GmbH

#define    S_FUNCTION_LEVEL   (0xc38+5412-0x215a)
#undef     S_FUNCTION_NAME
#define    S_FUNCTION_NAME   sg_fpga_hall_sensor_sf_4
#include   <stddef.h>
#include   <stdlib.h>
#include   <stdint.h>
#include   <stdbool.h>
#include   "simstruc.h"
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif
#ifndef MATLAB_MEX_FILE
#include "sg_common.h"
#include "sg_fpga_io3xx_scatter_gather_dma.h"
#include "sg_fpga_io3xx_util.h"
#include "sg_printf.h"
#endif
#define SG_EARLY_INIT
#include "sg_callback.h"
typedef enum{ID,CHANNEL,ze344b15ab1,zea52f4bb4e,z5113040715,z749c8761d8,z6cd83f66b3,ze7431a239e,zf1556bad85,zc54a691ef6,z8f67d40899,zdb9d259599,z6b484412fb,z7f12cbcf73,zdf24515981}z2d96948f32;
#define z58f464b4bb                        ssGetSFcnParam(S, ID)
#define za9d8fb6bcf                   ssGetSFcnParam(S, CHANNEL) 
#define z3832b85a32                 ssGetSFcnParam(S, ze344b15ab1)
#define z62e46f52ac              ssGetSFcnParam(S, zea52f4bb4e)
#define zfededf31b4              ssGetSFcnParam(S, z5113040715)
#define zdba86fa350         ssGetSFcnParam(S, z749c8761d8)
#define z245fc13caf            ssGetSFcnParam(S, z6cd83f66b3)
#define zedf83f7c01           ssGetSFcnParam(S, ze7431a239e)
#define z6d8cf67e42   ssGetSFcnParam(S, zf1556bad85)
#define z7c9f87b11a              ssGetSFcnParam(S, zc54a691ef6)
#define z6fdc2c8c7d             ssGetSFcnParam(S, z8f67d40899)
#define z09d3a801f6 ssGetSFcnParam(S, zdb9d259599)
#define z3e6080e8ec     ssGetSFcnParam(S, z6b484412fb)
#define z3e974bee53     ssGetSFcnParam(S, z7f12cbcf73)
#define z2e6483d505                (0xb8f+3224-0x1827)
#define zc5ce4cb81a                (0x37b+8538-0x24d5)
#define z2b17e2ee3b                (0x1630+4063-0x260f)
#define z5bbcf8be2c              (0x576+8395-0x263d)
#define TABLE_SIZE                262144 
#define zae4028a32c                4294967296
#define z39f8db5f6e              (0xd43+6506-0x268d)
static char msg[(0x9b8+4380-0x19d4)];typedef struct{uint32_t z01b12ebff6[z39f8db5f6e];uint32_t z2c0e94e04f[z39f8db5f6e];uint32_t zb46289d48f[z39f8db5f6e];uint32_t offset[z39f8db5f6e];uint32_t zd4b9d383d6[z39f8db5f6e];uint32_t position[z39f8db5f6e];uint32_t reserved[(0x1cdb+725-0x1870)];}z69330d0baf;typedef struct{z69330d0baf channel;uint32_t version;uint32_t zb871a780a7;uint32_t enable;}z5a0bf6e7ac;
#ifndef MATLAB_MEX_FILE
typedef struct{z5a0bf6e7ac*z952a96a3f5;io3xx_sgdma_Handle*ze639490358;ScatterGatherDmaState*z50b84cc2b5;}za8875f70bd;
#endif
static void mdlInitializeSizes(SimStruct*S){ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0xba+8840-0x2342));ssSetNumDiscStates(S,(0x18ed+3237-0x2592));uint32_t z9f25147305=(0xe74+2850-0x1996);if((uint32_t)mxGetPr(z09d3a801f6)[(0x9e8+3093-0x15fd)]){z9f25147305++;}if((uint32_t)mxGetPr(z3e6080e8ec)[(0x912+4511-0x1ab1)]){z9f25147305++;}(void)ssSetNumInputPorts(S,z9f25147305);for(int i=(0x357+375-0x4ce);i<z9f25147305;i++){ssSetInputPortWidth(S,i,(0x7af+4712-0x1a16));ssSetInputPortDirectFeedThrough(S,i,(0x1715+1496-0x1cec));ssSetInputPortRequiredContiguous(S,i,(0x2014+1189-0x24b8));ssSetInputPortDataType(S,i,SS_DOUBLE);}uint32_t z7c076b8413=(0x9c3+6595-0x2386);if((uint32_t)mxGetPr(z3e974bee53)[(0xb39+5071-0x1f08)]){z7c076b8413++;}(void)ssSetNumOutputPorts(S,z7c076b8413);if(z7c076b8413>(0x12aa+2630-0x1cf0)){ssSetOutputPortWidth(S,(0x9ac+2312-0x12b4),(0xefc+4845-0x21e8));}ssSetNumSampleTimes(S,(0x212b+1226-0x25f4));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x1002+3598-0x1e10));ssSetNumNonsampledZCs(S,(0x797+4926-0x1ad5));for(int i=(0xd0b+3763-0x1bbe);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0xdfd+5030-0x21a3));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x1b22+1156-0x1fa6)]==-1.0){ssSetSampleTime(S,(0x1c1a+1423-0x21a9),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x6cd+7828-0x2561),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x97+5504-0x1617),mxGetPr(z3832b85a32)[(0x702+2443-0x108d)]);ssSetOffsetTime(S,(0x14dc+613-0x1741),0.0);}}static void sg_ModelLoad(SimStruct*S){
#ifndef MATLAB_MEX_FILE
SG_PRINTF(DEBUG,"\x48\x61\x6c\x6c\x20\x53\x65\x6e\x73\x6f\x72\x3a\x20\x4d\x6f\x64\x65\x6c\x20\x4c\x6f\x61\x64" "\n");volatile z5a0bf6e7ac*z952a96a3f5;void*bar2ptr;int moduleId=(int)mxGetScalar(z58f464b4bb);char*boardName=io3xxGetBoardNameSgLib(moduleId);int z3e423c83e6=(int)mxGetPr(za9d8fb6bcf)[(0x60f+5001-0x1998)]-(0x3a6+1991-0xb6c);int ze0bc7e48d0=(int)(SG_BLOCK_TYPE_HALL_SENSOR);za8875f70bd*zda6ad2aee5=(za8875f70bd*)calloc((0x13f6+767-0x16f4),sizeof(za8875f70bd));sg_fpga_io3xx_block_register((uint32_t)moduleId,(uint32_t)ze0bc7e48d0,(uint32_t)z3e423c83e6,(void*)zda6ad2aee5);SG_PRINTF(DEBUG,"\x48\x61\x6c\x6c\x20\x53\x65\x6e\x73\x6f\x72\x3a\x20\x42\x6c\x6f\x63\x6b\x20\x72\x65\x67\x69\x73\x74\x65\x72\x65\x64\x21" "\n");if(!io3xxGetAddressSgLib((int32_t)moduleId,SG_FPGA_IO3XX_BAR2)){ssSetErrorStatus(S,pSgErrorStr);return;}bar2ptr=io3xxGetAddressSgLib((int32_t)moduleId,SG_FPGA_IO3XX_BAR2);uint32_t zf7ccd17be8=(0x1cd8+2408-0x2640);if(sg_fpga_io3xx_getCmBaseAddress(moduleId,HALL_SENSOR_BASE,&zf7ccd17be8)){sprintf(msg,"\x25\x73\x20\x48\x61\x6c\x6c\x20\x53\x65\x6e\x73\x6f\x72\x20\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x4f\x66\x66\x73\x65\x74\x20\x6c\x6f\x6f\x6b\x75\x70\x20\x75\x6e\x73\x75\x63\x63\x65\x73\x73\x66\x75\x6c\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}zda6ad2aee5->z952a96a3f5=(z5a0bf6e7ac*)((uintptr_t)bar2ptr+zf7ccd17be8);z952a96a3f5=zda6ad2aee5->z952a96a3f5;SG_PRINTF(DEBUG,"\x48\x61\x6c\x6c\x20\x53\x65\x6e\x73\x6f\x72\x3a\x20\x41\x64\x64\x72\x65\x73\x73\x20\x6c\x6f\x6f\x6b\x75\x70\x20\x73\x75\x63\x63\x65\x73\x73\x66\x75\x6c\x21" "\n");SG_PRINTF(DEBUG,"\x48\x61\x6c\x6c\x20\x53\x65\x6e\x73\x6f\x72\x3a\x20\x43\x6f\x64\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x76\x65\x72\x73\x69\x6f\x6e\x3a\x20\x30\x78\x25\x78" "\n",z952a96a3f5->version);if(sg_isFirstModelLoad()){if(sg_fpga_io3xx_checkCodeModuleVersion(z952a96a3f5->version,z5bbcf8be2c,moduleId)){sprintf(msg,"\x25\x73\x20\x77\x72\x6f\x6e\x67\x20\x76\x65\x72\x73\x69\x6f\x6e\x20\x6f\x66\x20\x48\x61\x6c\x6c\x20\x53\x65\x6e\x73\x6f\x72\x20\x63\x6f\x64\x65\x20\x6d\x6f\x64\x75\x6c\x65\x21" "\n",boardName);ssSetErrorStatus(S,msg);return;}}if((uint32_t)mxGetN(za9d8fb6bcf)!=(0x4c0+8332-0x254b)){sprintf(msg,"\x25\x73\x20\x48\x61\x6c\x6c\x20\x53\x65\x6e\x73\x6f\x72\x20\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x43\x68\x61\x6e\x6e\x65\x6c\x20\x70\x61\x72\x61\x6d\x65\x74\x65\x72\x20\x6d\x75\x73\x74\x20\x62\x65\x20\x61\x20\x73\x63\x61\x6c\x61\x72\x2e" "\n",boardName);ssSetErrorStatus(S,msg);return;}uint32_t channel=(uint32_t)mxGetPr(za9d8fb6bcf)[(0xcc0+4001-0x1c61)]-(0x487+4461-0x15f3);uint32_t z3ebe0cb315=((uint32_t)mxGetPr(z62e46f52ac)[(0x10ad+4988-0x2429)]-(0xf99+881-0x1309))&(0x117a+3334-0x1e61);uint32_t z5e4143f772=(uint32_t)mxGetPr(z245fc13caf)[(0xb8f+94-0xbed)]&(0xbf+5934-0x17ec);uint32_t zb002e624e0=(uint32_t)mxGetPr(zfededf31b4)[(0x80+5161-0x14a9)]&(0xd27+3123-0x1959);uint32_t z37b3c08bea=(0x1321+4967-0x2687);uint32_t ze607ede8f1=(z3ebe0cb315<<(0xcbd+6453-0x25ea))|(z5e4143f772<<(0xb94+4831-0x1e71))|(zb002e624e0<<(0x803+3879-0x1729))|z37b3c08bea;z952a96a3f5->channel.z2c0e94e04f[channel]=ze607ede8f1;uint32_t z17645a7e30=(uint32_t)(mxGetPr(z6d8cf67e42)[(0x32a+5058-0x16ec)]/(0x16f4+1103-0x1873)*zae4028a32c);z952a96a3f5->channel.offset[channel]=z17645a7e30;uint32_t z68139e58f3=(uint32_t)mxGetPr(zdba86fa350)[(0xc4d+6483-0x25a0)];z952a96a3f5->channel.zd4b9d383d6[channel]=z68139e58f3-(0xa58+6767-0x24c6);uint32_t zd056c7c027=(uint32_t)(mxGetPr(zedf83f7c01)[(0x9ed+1769-0x10d6)]/(0x10e4+1008-0x1204)*zae4028a32c);z952a96a3f5->channel.zb46289d48f[channel]=zd056c7c027;uint32_t zbe4636403c=(uint32_t)mxGetN(z7c9f87b11a);uint32_t z106eaac635=TABLE_SIZE;if(zbe4636403c!=z106eaac635){sprintf(msg,"\x25\x73\x20\x48\x61\x6c\x6c\x20\x53\x65\x6e\x73\x6f\x72\x20\x6d\x6f\x64\x75\x6c\x65\x3a\x20\x45\x78\x70\x65\x63\x74\x65\x64\x20\x73\x69\x67\x6e\x61\x6c\x20\x74\x61\x62\x6c\x65\x20\x6c\x65\x6e\x67\x74\x68\x20\x69\x73\x20\x25\x75\x2c\x20\x62\x75\x74\x20\x65\x66\x66\x65\x63\x74\x69\x76\x65\x20\x74\x61\x62\x6c\x65\x20\x6c\x65\x6e\x67\x74\x68\x20\x69\x73\x20\x25\x75\x2e" "\n",boardName,z106eaac635,zbe4636403c);
ssSetErrorStatus(S,msg);return;}for(int i=(0x1f76+1921-0x26f7);i<TABLE_SIZE;i++){uint32_t z3e184557b3=(0xfa9+3990-0x1f3e)<<(0x852+6067-0x1fe6);uint32_t data=((uint32_t)mxGetPr(z7c9f87b11a)[i]&(0x117+6730-0x1b60))<<(0x651+3331-0x1336);uint32_t addr=i&262143;z952a96a3f5->channel.z01b12ebff6[channel]=z3e184557b3|data|addr;}z952a96a3f5->zb871a780a7=(0x1d+5325-0x14e9)<<channel;SG_PRINTF(DEBUG,"\x48\x61\x6c\x6c\x20\x53\x65\x6e\x73\x6f\x72\x20\x43\x68\x61\x6e\x6e\x65\x6c\x20\x25\x75\x20\x52\x65\x67\x69\x73\x74\x65\x72\x20\x56\x61\x6c\x75\x65\x73\x3a" "\n",channel+(0x12fd+3715-0x217f));SG_PRINTF(DEBUG,"\x20\x20\x63\x74\x72\x6c\x5b\x25\x75\x5d\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x3d\x20\x30\x78\x25\x30\x38\x58" "\n",channel,ze607ede8f1);SG_PRINTF(DEBUG,"\x20\x20\x6f\x66\x66\x73\x65\x74\x5b\x25\x75\x5d\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x3d\x20\x30\x78\x25\x30\x38\x58" "\n",channel,z17645a7e30);SG_PRINTF(DEBUG,"\x20\x20\x74\x61\x62\x6c\x65\x5f\x61\x64\x64\x72\x5b\x25\x75\x5d\x20\x20\x20\x20\x20\x20\x20\x20\x3d\x20\x30\x78\x25\x30\x38\x58" "\n",channel,z68139e58f3);
#endif
}static void sg_ModelStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
SG_PRINTF(DEBUG,"\x47\x45\x54\x54\x49\x4e\x47\x20\x53\x54\x41\x52\x54\x45\x44" "\n");
#endif
}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
volatile z5a0bf6e7ac*z952a96a3f5;int moduleId=(int)mxGetScalar(z58f464b4bb);int z3e423c83e6=(int)mxGetPr(za9d8fb6bcf)[(0x1d5a+62-0x1d98)]-(0x30+9137-0x23e0);int ze0bc7e48d0=(int)(SG_BLOCK_TYPE_HALL_SENSOR);sg_block_info*z05264739a1=sg_fpga_io3xx_block_get((uint32_t)moduleId,(uint32_t)ze0bc7e48d0,(uint32_t)z3e423c83e6);za8875f70bd*zda6ad2aee5=(za8875f70bd*)z05264739a1->custom_data;z952a96a3f5=zda6ad2aee5->z952a96a3f5;uint32_t channel=(uint32_t)mxGetPr(za9d8fb6bcf)[(0x3a5+2349-0xcd2)]-(0x2a2+2371-0xbe4);if((uint32_t)mxGetPr(z3e974bee53)[(0x1ae0+282-0x1bfa)]){uint32_t position=z952a96a3f5->channel.position[channel];double z4b95808058=((double)position/zae4028a32c)*720.0;double*z34a675f13b=(double*)ssGetOutputPortSignal(S,(0x1022+893-0x139f));*z34a675f13b=z4b95808058;}if((uint32_t)mxGetPr(z3e6080e8ec)[(0x4f3+4944-0x1843)]){double*z2ff6f8ed02=(double*)ssGetInputPortSignal(S,(0x1080+101-0x10e5));uint32_t z68139e58f3=(uint32_t)(*z2ff6f8ed02);if(z68139e58f3<(0xf4+4782-0x13a1)||z68139e58f3>(0x1eff+2066-0x270d)){z68139e58f3=(0x106b+5338-0x2544);}z952a96a3f5->channel.zd4b9d383d6[channel]=z68139e58f3-(0x251+3435-0xfbb);}if((uint32_t)mxGetPr(z09d3a801f6)[(0x113c+1732-0x1800)]){double*z12a353c906=(double*)ssGetInputPortSignal(S,(0x1102+2204-0x199d));uint32_t z17645a7e30=(uint32_t)((*z12a353c906)/720.0*zae4028a32c);z952a96a3f5->channel.offset[channel]=z17645a7e30;}z952a96a3f5->zb871a780a7=(0x49f+2161-0xd0f)<<channel;
#endif
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE
volatile z5a0bf6e7ac*z952a96a3f5;int moduleId=(int)mxGetScalar(z58f464b4bb);int z3e423c83e6=(int)mxGetPr(za9d8fb6bcf)[(0xaf1+3201-0x1772)]-(0xefa+1253-0x13de);int ze0bc7e48d0=(int)(SG_BLOCK_TYPE_HALL_SENSOR);sg_block_info*z05264739a1=sg_fpga_io3xx_block_get((uint32_t)moduleId,(uint32_t)ze0bc7e48d0,(uint32_t)z3e423c83e6);za8875f70bd*zda6ad2aee5=(za8875f70bd*)z05264739a1->custom_data;z952a96a3f5=zda6ad2aee5->z952a96a3f5;uint32_t channel=(uint32_t)mxGetPr(za9d8fb6bcf)[(0x14d8+401-0x1669)]-(0x860+4583-0x1a46);uint32_t z55295fd6cc=z952a96a3f5->enable;z952a96a3f5->enable=(~((0x101d+4552-0x21e4)<<channel))&z55295fd6cc;
#endif
}
#include "sg_sfcn_glue.h"   

