// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL    (0x1bf+8572-0x2339)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_fpga_io3xx_120_analog_input_s
#define ze1873db84a          (0x1a98+2944-0x2617)
#include "simstruc.h"
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#else
#include "sg_fpga_io3xx_regs.h"
#include "sg_fpga_io3xx_util.h"
#include "sg_fpga_setup_util.h"
#include "sg_fpga_analog_120.h"
#endif
#include "sg_callback.h"
#include "sg_mask_init.h"
#include "sg_printf.h"
#include "sg_AnalogInputCm_IO336.h"
#include "sg_fpga_analog_dma.h"
using sg::z39db9ebd35;enum z9c14fdf935{zc7d8502b91,za2c6d5f765,zabd1786fec,zbd13bc814a,zdf92df73c8,z304a067171,z2041d72f5c};
#define zfaa050b79d               ssGetSFcnParam(S, zc7d8502b91)
#define z5b76458894             ssGetSFcnParam(S, za2c6d5f765)
#define z9401605763             ssGetSFcnParam(S, zabd1786fec)
#define z0453ae337c    ssGetSFcnParam(S, zbd13bc814a)
#define zee0787c51a         ssGetSFcnParam(S, zdf92df73c8)
#define z16e4f81fa8           ssGetSFcnParam(S, z304a067171)
enum zbb1f615c1d{z96932fc556,z107990a782,z32297f1282};enum z93bcf30780{z81b97a1b0d};enum zb06a9f15ae{zbeb0b06c22};
#ifndef MATLAB_MEX_FILE
static void zdb8b3de61d(SimStruct*S,zbba09dac2e*zab86ba64c9);static void z8fe6e37678(z9258e0f85a*z1946f35eb5,char*boardName,const char*title);static void z6274f5032f(z9258e0f85a*z1946f35eb5,char*boardName);
#endif
static char msg[(0x526+1676-0xab2)];static void mdlInitializeSizes(SimStruct*S){SgMaskInit_SetupSettingsArgs args;args.numberOfParams=z2041d72f5c;args.integerWorkVecLength=z32297f1282;args.realWorkVecLength=z81b97a1b0d;args.pointerWorkVecLength=zbeb0b06c22;if(sgMaskInit_initSizesForRegularBlock(S,&args)){sprintf(msg,"\x49\x4f\x33\x78\x78\x20\x41\x6e\x61\x6c\x6f\x67\x20\x69\x6e\x70\x75\x74\x20\x62\x6c\x6f\x63\x6b\x2c\x20\x49\x44\x20\x25\x64\x3a\x20\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n""\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64\x2e",(int)mxGetScalar(zfaa050b79d),z2041d72f5c);ssSetErrorStatus(S,msg);return;}sgMaskInit_setNoInputPorts(S);bool zede89c661a=(bool)mxGetScalar(zee0787c51a);int zbc29571b7b=(zede89c661a)?(int)mxGetScalar(z16e4f81fa8):(0xd0f+1280-0x120e);sgMaskInit_setOutputPorts(S,mxGetN(z9401605763),zbc29571b7b);}static void mdlInitializeSampleTimes(SimStruct*S){double sampleTime=mxGetScalar(z5b76458894);sgMaskInit_initSampleTimesForRegularBlock(S,sampleTime);}static void sg_ModelLoad(SimStruct*S){
#ifndef MATLAB_MEX_FILE
#endif  
}static void sg_ModelStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
int moduleId=(int)mxGetScalar(zfaa050b79d);char*boardName=io3xxGetBoardNameSgLib(moduleId);int z3e423c83e6=(0x5a3+4708-0x1807);int ze0bc7e48d0=(int)(SG_BLOCK_TYPE_IO3XX_120_ANALOG_SETUP);sg_block_info*za9a3739e02=(sg_block_info*)sg_fpga_io3xx_block_get((uint32_t)moduleId,(uint32_t)ze0bc7e48d0,(uint32_t)z3e423c83e6);zbba09dac2e*zab86ba64c9=(zbba09dac2e*)za9a3739e02->custom_data;z55c8ec7b16*params=zab86ba64c9->zcd6b8fef93;SG_PRINTF(DEBUG,"\x25\x73\x20\x41\x6e\x61\x6c\x6f\x67\x20\x69\x6e\x70\x75\x74\x20\x62\x6c\x6f\x63\x6b\x2c\x20\x49\x44\x3a\x20\x25\x64" "\n",boardName,moduleId);int z02005603d4=(0x8ba+1729-0xf7b);z02005603d4=(0xd5d+2956-0x18e9);for(int i=(0x2c3+471-0x49a);i<params->z4303a50079->len;i++){if(params->z4303a50079->val[i]==z1a881996bd){z02005603d4++;}}ssSetIWorkValue(S,z96932fc556,z02005603d4==params->z4303a50079->len);ssSetIWorkValue(S,z107990a782,z02005603d4!=(0x451+6036-0x1be5));z39db9ebd35*z6af3d2acb0=(z39db9ebd35*)zab86ba64c9->z6af3d2acb0;z9258e0f85a*z1946f35eb5=(z9258e0f85a*)zab86ba64c9->z1946f35eb5;mod_desc_FPGA_sg_lib*zeaf37cf405=(mod_desc_FPGA_sg_lib*)sg_module_get_custom_data(SG_MODULE_TYPE_FPGA,moduleId);zab86ba64c9->z9e5d610777=zeaf37cf405->pDmaReadMemoryPool;SG_PRINTF(DEBUG,"\x25\x73\x20\x41\x6e\x61\x6c\x6f\x67\x20\x69\x6e\x70\x75\x74\x20\x44\x4d\x41\x20\x52\x65\x61\x64\x20\x4d\x65\x6d\x6f\x72\x79\x20\x50\x6f\x6f\x6c\x20\x30\x78\x25\x70" "\n",boardName,zab86ba64c9->z9e5d610777);if(!zab86ba64c9->z9e5d610777){sprintf(msg,"\x25\x73\x20\x41\x6e\x61\x6c\x6f\x67\x20\x69\x6e\x70\x75\x74\x3a\x20\x4e\x6f\x20\x6d\x65\x6d\x6f\x72\x79\x20\x70\x6f\x6f\x6c\x20\x61\x76\x61\x69\x6c\x61\x62\x6c\x65\x21",boardName);ssSetErrorStatus(S,msg);return;}if((z1946f35eb5->z93beb01ec7.zaed73eb2ad&z0919db1183)||(!(z1946f35eb5->z93beb01ec7.z3d41168cf2&z6e240cc96b))){SG_PRINTF(WARNING,"\x25\x73\x20\x41\x6e\x61\x6c\x6f\x67\x20\x69\x6e\x70\x75\x74\x3a\x20\x45\x6e\x67\x69\x6e\x65\x20\x61\x6c\x72\x65\x61\x64\x79\x20\x72\x75\x6e\x6e\x69\x6e\x67" "\n",boardName);}z1946f35eb5->z93beb01ec7.zaed73eb2ad|=z0919db1183;int timeout=(0x1976+1986-0x2138);while(z1946f35eb5->z93beb01ec7.z3d41168cf2&z6e240cc96b){sg_wait_s(1e-6);timeout++;if(timeout==(0x1b90+511-0x19a7)){SG_PRINTF(WARNING,"\x25\x73\x20\x41\x6e\x61\x6c\x6f\x67\x20\x69\x6e\x70\x75\x74\x3a\x20\x44\x4d\x41\x20\x73\x74\x61\x72\x74\x20\x74\x69\x6d\x65\x6f\x75\x74\x2e\x20\x44\x4d\x41\x53\x52\x3a\x20\x30\x78\x25\x78\x20\x44\x4d\x41\x43\x52\x3a\x20\x30\x78\x25\x78" "\n",boardName,z1946f35eb5->z93beb01ec7.z3d41168cf2,z1946f35eb5->z93beb01ec7.zaed73eb2ad);break;}}uint32_t*pDmaReadMemoryPoolPhys;if(!strcmp(boardName,"\x53\x70\x65\x65\x64\x67\x6f\x61\x74\x20\x50\x75\x6c\x73\x65\x20\x49\x2f\x4f")){pDmaReadMemoryPoolPhys=(uint32_t*)io3xxGetPointerDmaReadMemoryPoolPhys(moduleId);}else{pDmaReadMemoryPoolPhys=(uint32_t*)(SGLIB_PCIE_EGRESS_APERTURE_OFFSET);}if(pDmaReadMemoryPoolPhys!=NULL){z1946f35eb5->z93beb01ec7.zf1756dff08=(uint32_t)(uintptr_t)pDmaReadMemoryPoolPhys;}else{SG_PRINTF(ERROR,"\x25\x73\x20\x41\x6e\x61\x6c\x6f\x67\x20\x69\x6e\x70\x75\x74\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x67\x65\x74\x20\x70\x6f\x69\x6e\x74\x65\x72\x20\x74\x6f\x20\x44\x4d\x41\x20\x72\x65\x61\x64\x20\x6d\x65\x6d\x6f\x72\x79\x20\x70\x6f\x6f\x6c\x21" "\n",boardName);}z1946f35eb5->z93beb01ec7.z3d41168cf2|=z533cc0b976;z1946f35eb5->z93beb01ec7.zaed73eb2ad|=zda905d3958;if((int)mxGetScalar(zee0787c51a)){z1946f35eb5->z93beb01ec7.length=zab86ba64c9->zcd6b8fef93->z65ccc06e80->len*z6af3d2acb0->z7c81aa577e*z2a363480a3*((int)mxGetScalar(z16e4f81fa8)+(0x4c6+539-0x6e0))*(0x453+3194-0x10c9);}if(params->z9725148e53){z1946f35eb5->z93beb01ec7.length=zab86ba64c9->zcd6b8fef93->z65ccc06e80->len*z6af3d2acb0->z7c81aa577e*z2a363480a3*(0x98c+1306-0xea2);z6af3d2acb0->zba47d7264b();}
#if (0xf63+4123-0x1f7e)
z8fe6e37678(z1946f35eb5,boardName,"\x41\x6e\x61\x6c\x6f\x67\x20\x44\x4d\x41\x20\x41\x44\x43\x20\x49\x4e\x49\x54\x20\x45\x4e\x44");
#endif
z6af3d2acb0->z7af6572ea9();
#endif  
}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
int moduleId=(int)mxGetScalar(zfaa050b79d);char*boardName=io3xxGetBoardNameSgLib(moduleId);int z3e423c83e6=(0x90a+6100-0x20de);int ze0bc7e48d0=(int)(SG_BLOCK_TYPE_IO3XX_120_ANALOG_SETUP);sg_block_info*za9a3739e02=(sg_block_info*)sg_fpga_io3xx_block_get((uint32_t)moduleId,(uint32_t)ze0bc7e48d0,(uint32_t)z3e423c83e6);zbba09dac2e*zab86ba64c9=(zbba09dac2e*)za9a3739e02->custom_data;z39db9ebd35*z6af3d2acb0=(z39db9ebd35*)zab86ba64c9->z6af3d2acb0;z9258e0f85a*z1946f35eb5=(z9258e0f85a*)zab86ba64c9->z1946f35eb5;int z5d07366fd3=zab86ba64c9->zcd6b8fef93->z65ccc06e80->len*z6af3d2acb0->z7c81aa577e*z2a363480a3*(0x2475+661-0x2706);z8fe6e37678(z1946f35eb5,boardName,"\x41\x6e\x61\x6c\x6f\x67\x20\x44\x4d\x41\x20\x41\x44\x43\x20\x53\x54\x45\x50\x20\x45\x4e\x54\x52\x59");if(ssGetIWorkValue(S,z96932fc556)){if(zab86ba64c9->zcd6b8fef93->z9725148e53)zdb8b3de61d(S,zab86ba64c9);z1946f35eb5->z93beb01ec7.length=z5d07366fd3;z8fe6e37678(z1946f35eb5,boardName,"\x41\x6e\x61\x6c\x6f\x67\x20\x44\x4d\x41\x20\x41\x44\x43\x20\x53\x54\x45\x50\x20\x44\x4d\x41\x20\x52\x65\x2d\x53\x54\x41\x52\x54\x45\x44");z6af3d2acb0->zba47d7264b();if(!(zab86ba64c9->zcd6b8fef93->z9725148e53)){z6274f5032f(z1946f35eb5,boardName);zdb8b3de61d(S,zab86ba64c9);};}else if((int)mxGetScalar(zee0787c51a)){zdb8b3de61d(S,zab86ba64c9);z5d07366fd3*=((int)mxGetScalar(z16e4f81fa8)+(0xe48+5191-0x228e));z1946f35eb5->z93beb01ec7.length=z5d07366fd3;z8fe6e37678(z1946f35eb5,boardName,"\x41\x6e\x61\x6c\x6f\x67\x20\x44\x4d\x41\x20\x41\x44\x43\x20\x53\x54\x45\x50\x20\x44\x4d\x41\x20\x52\x65\x2d\x53\x54\x41\x52\x54\x45\x44");}else{if(zab86ba64c9->zcd6b8fef93->z9725148e53)zdb8b3de61d(S,zab86ba64c9);z1946f35eb5->z93beb01ec7.length=z5d07366fd3;z8fe6e37678(z1946f35eb5,boardName,"\x41\x6e\x61\x6c\x6f\x67\x20\x44\x4d\x41\x20\x41\x44\x43\x20\x53\x54\x45\x50\x20\x44\x4d\x41\x20\x52\x65\x2d\x53\x54\x41\x52\x54\x45\x44");if(ssGetIWorkValue(S,z107990a782)){z6af3d2acb0->zba47d7264b();sg_wait_s(1e-6);}z6af3d2acb0->z582f6a936a();if(!(zab86ba64c9->zcd6b8fef93->z9725148e53)){z6274f5032f(z1946f35eb5,boardName);zdb8b3de61d(S,zab86ba64c9);};}
#endif  
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE
#endif  
}
#ifndef MATLAB_MEX_FILE
static void zdb8b3de61d(SimStruct*S,zbba09dac2e*zab86ba64c9){int32_t*zc60ddfc6a1=(int32_t*)zab86ba64c9->z9e5d610777;double*z3e9acb26bc=(double*)zab86ba64c9->z44132c7346;int za746b13f73=(int)mxGetScalar(zee0787c51a)?(int)mxGetScalar(z16e4f81fa8):(0xb24+5565-0x20e0);uint32_t zad0e5075a4=(int)mxGetScalar(zee0787c51a)?(uint32_t)mxGetN(z9401605763):(uint32_t)mxGetN(z0453ae337c);uint32_t zaaf66dafad=(0x88+802-0x3aa);uint32_t z0f2105f03a=(0x1581+3187-0x21f4);for(uint32_t za7a53d33d9=(0x760+7062-0x22f6);za7a53d33d9<zad0e5075a4;za7a53d33d9++){uint32_t compare=(int)mxGetScalar(zee0787c51a)?(uint32_t)mxGetPr(z9401605763)[za7a53d33d9]:(uint32_t)mxGetPr(z0453ae337c)[za7a53d33d9];if((uint32_t)mxGetPr(z9401605763)[zaaf66dafad]==compare){double*zf8940086c1=ssGetOutputPortRealSignal(S,zaaf66dafad);for(int z2ca80d4e56=(0xf33+2660-0x1997);z2ca80d4e56<za746b13f73;z2ca80d4e56++){z0f2105f03a=(z2ca80d4e56*zad0e5075a4)+za7a53d33d9;int32_t value=(zc60ddfc6a1[z0f2105f03a]<<(0xdc1+4161-0x1df6))>>(0xb7+9225-0x24b4);zf8940086c1[z2ca80d4e56]=(double)value*z3e9acb26bc[zaaf66dafad];}zaaf66dafad++;}}}static void z8fe6e37678(z9258e0f85a*z1946f35eb5,char*boardName,const char*title){
#if (0x11af+3709-0x202c)
SG_PRINTF(INFO,"\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x25\x73\x20\x25\x73\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d" "\n""\x49\x4f\x33\x78\x78\x20\x41\x44\x43\x3a\x20\x64\x6d\x61\x52\x65\x67\x73\x2d\x3e\x73\x32\x6d\x6d\x2e\x64\x6d\x61\x43\x72\x3a\x20\x30\x78\x25\x30\x38\x58" "\n""\x49\x4f\x33\x78\x78\x20\x41\x44\x43\x3a\x20\x64\x6d\x61\x52\x65\x67\x73\x2d\x3e\x73\x32\x6d\x6d\x2e\x64\x6d\x61\x53\x72\x3a\x20\x30\x78\x25\x30\x38\x58" "\n""\x49\x4f\x33\x78\x78\x20\x41\x44\x43\x3a\x20\x64\x6d\x61\x52\x65\x67\x73\x2d\x3e\x73\x32\x6d\x6d\x2e\x6c\x65\x6e\x67\x74\x68\x3a\x30\x78\x25\x30\x38\x58" "\n",boardName,title,z1946f35eb5->z93beb01ec7.zaed73eb2ad,z1946f35eb5->z93beb01ec7.z3d41168cf2,z1946f35eb5->z93beb01ec7.length);
#endif
}static void z6274f5032f(z9258e0f85a*z1946f35eb5,char*boardName){int timeout=(0x133d+1950-0x1adb);while(!(z1946f35eb5->z93beb01ec7.z3d41168cf2&z630b009214)){sg_wait_s(1e-6);timeout++;if(timeout==(0x6a4+1329-0x7ed)){SG_PRINTF(WARNING,"\x25\x73\x20\x41\x6e\x61\x6c\x6f\x67\x20\x69\x6e\x70\x75\x74\x3a\x20\x44\x4d\x41\x20\x72\x65\x63\x65\x69\x76\x65\x20\x74\x69\x6d\x65\x6f\x75\x74\x2e" "\n",boardName);break;}}}
#endif  
#include "sg_sfcn_glue.h" 

