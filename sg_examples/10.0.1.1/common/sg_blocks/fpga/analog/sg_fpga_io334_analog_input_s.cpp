// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL    (0x33c+2707-0xdcd)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_fpga_io334_analog_input_s
#define ze1873db84a          (0x75+8023-0x1fcb)
#include "simstruc.h"
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#else
#include "sg_fpga_io3xx_regs.h"
#include "sg_fpga_io3xx_util.h"
#endif
#include "sg_callback.h"
#include "sg_mask_init.h"
#include "sg_printf.h"
#include "sg_fpga_analog_334.h"
enum z9c14fdf935{zc7d8502b91,za2c6d5f765,zabd1786fec,zbd13bc814a,z4e2c0a96af,zdf92df73c8,z304a067171,z2041d72f5c};
#define zfaa050b79d               ssGetSFcnParam(S, zc7d8502b91)
#define z5b76458894             ssGetSFcnParam(S, za2c6d5f765)
#define z9401605763             ssGetSFcnParam(S, zabd1786fec)
#define z0453ae337c    ssGetSFcnParam(S, zbd13bc814a)
#define z210424a835      ssGetSFcnParam(S, z4e2c0a96af)
#define zee0787c51a         ssGetSFcnParam(S, zdf92df73c8)
#define z16e4f81fa8           ssGetSFcnParam(S, z304a067171)
enum zbb1f615c1d{z32297f1282};enum z93bcf30780{z81b97a1b0d};enum zb06a9f15ae{zbeb0b06c22};
#ifndef MATLAB_MEX_FILE
static void zdb8b3de61d(SimStruct*S,zf741ad1d87*zab86ba64c9);static void z8fe6e37678(z9258e0f85a*z1946f35eb5,char*boardName,const char*title);static void z6274f5032f(z9258e0f85a*z1946f35eb5,char*boardName);
#endif
static char msg[(0x11a9+4440-0x2201)];static void mdlInitializeSizes(SimStruct*S){SgMaskInit_SetupSettingsArgs args;args.numberOfParams=z2041d72f5c;args.integerWorkVecLength=z32297f1282;args.realWorkVecLength=z81b97a1b0d;args.pointerWorkVecLength=zbeb0b06c22;if(sgMaskInit_initSizesForRegularBlock(S,&args)){sprintf(msg,"\x49\x4f\x33\x78\x78\x20\x41\x6e\x61\x6c\x6f\x67\x20\x69\x6e\x70\x75\x74\x20\x62\x6c\x6f\x63\x6b\x2c\x20\x49\x44\x20\x25\x64\x3a\x20\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n""\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64\x2e",(int)mxGetScalar(zfaa050b79d),z2041d72f5c);ssSetErrorStatus(S,msg);return;}sgMaskInit_setNoInputPorts(S);bool zede89c661a=(bool)mxGetScalar(zee0787c51a);int zbc29571b7b=(zede89c661a)?(int)mxGetScalar(z16e4f81fa8):(0x762+535-0x978);sgMaskInit_setOutputPorts(S,mxGetN(z9401605763),zbc29571b7b);}static void mdlInitializeSampleTimes(SimStruct*S){double sampleTime=mxGetScalar(z5b76458894);sgMaskInit_initSampleTimesForRegularBlock(S,sampleTime);}static void sg_ModelLoad(SimStruct*S){
#ifndef MATLAB_MEX_FILE
#endif  
}static void sg_ModelStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
int moduleId=(int)mxGetScalar(zfaa050b79d);char*boardName=io3xxGetBoardNameSgLib(moduleId);int z3e423c83e6=(0x118a+5098-0x2574);int ze0bc7e48d0=(int)(SG_BLOCK_TYPE_IO334_ANALOG_SETUP);sg_block_info*za9a3739e02=(sg_block_info*)sg_fpga_io3xx_block_get((uint32_t)moduleId,(uint32_t)ze0bc7e48d0,(uint32_t)z3e423c83e6);zf741ad1d87*zab86ba64c9=(zf741ad1d87*)za9a3739e02->custom_data;z55c8ec7b16*params=zab86ba64c9->zcd6b8fef93;SG_PRINTF(DEBUG,"\x25\x73\x20\x41\x6e\x61\x6c\x6f\x67\x20\x69\x6e\x70\x75\x74\x20\x62\x6c\x6f\x63\x6b\x2c\x20\x49\x44\x3a\x20\x25\x64" "\n",boardName,moduleId);zff17be5515*z6af3d2acb0=(zff17be5515*)zab86ba64c9->z6af3d2acb0;z9258e0f85a*z1946f35eb5=(z9258e0f85a*)zab86ba64c9->z1946f35eb5;mod_desc_FPGA_sg_lib*zeaf37cf405=(mod_desc_FPGA_sg_lib*)sg_module_get_custom_data(SG_MODULE_TYPE_FPGA,moduleId);if(!zeaf37cf405){sprintf(msg,"\x25\x73\x20\x41\x6e\x61\x6c\x6f\x67\x20\x69\x6e\x70\x75\x74\x3a\x20\x4d\x6f\x64\x75\x6c\x65\x20\x6e\x6f\x74\x20\x72\x65\x67\x69\x73\x74\x65\x72\x65\x64\x2e",boardName);ssSetErrorStatus(S,msg);return;}zab86ba64c9->z9e5d610777=zeaf37cf405->pDmaReadMemoryPool;SG_PRINTF(DEBUG,"\x25\x73\x20\x41\x6e\x61\x6c\x6f\x67\x20\x69\x6e\x70\x75\x74\x20\x44\x4d\x41\x20\x52\x65\x61\x64\x20\x4d\x65\x6d\x6f\x72\x79\x20\x50\x6f\x6f\x6c\x20\x30\x78\x25\x70" "\n",boardName,zab86ba64c9->z9e5d610777);if(!zab86ba64c9->z9e5d610777){sprintf(msg,"\x25\x73\x20\x41\x6e\x61\x6c\x6f\x67\x20\x69\x6e\x70\x75\x74\x3a\x20\x4e\x6f\x20\x6d\x65\x6d\x6f\x72\x79\x20\x70\x6f\x6f\x6c\x20\x61\x76\x61\x69\x6c\x61\x62\x6c\x65\x21",boardName);ssSetErrorStatus(S,msg);return;}if((z1946f35eb5->z93beb01ec7.zaed73eb2ad&z0919db1183)||(!(z1946f35eb5->z93beb01ec7.z3d41168cf2&z6e240cc96b))){SG_PRINTF(WARNING,"\x25\x73\x20\x41\x6e\x61\x6c\x6f\x67\x20\x69\x6e\x70\x75\x74\x3a\x20\x45\x6e\x67\x69\x6e\x65\x20\x61\x6c\x72\x65\x61\x64\x79\x20\x72\x75\x6e\x6e\x69\x6e\x67" "\n",boardName);}z1946f35eb5->z93beb01ec7.zaed73eb2ad|=z0919db1183;int timeout=(0x13b+4715-0x13a6);while(z1946f35eb5->z93beb01ec7.z3d41168cf2&z6e240cc96b){sg_wait_s(1e-6);timeout++;if(timeout==(0xfe0+345-0xd51)){SG_PRINTF(WARNING,"\x25\x73\x20\x41\x6e\x61\x6c\x6f\x67\x20\x69\x6e\x70\x75\x74\x3a\x20\x44\x4d\x41\x20\x73\x74\x61\x72\x74\x20\x74\x69\x6d\x65\x6f\x75\x74\x2e\x20\x44\x4d\x41\x53\x52\x3a\x20\x30\x78\x25\x78\x20\x44\x4d\x41\x43\x52\x3a\x20\x30\x78\x25\x78" "\n",boardName,z1946f35eb5->z93beb01ec7.z3d41168cf2,z1946f35eb5->z93beb01ec7.zaed73eb2ad);break;}}z1946f35eb5->z93beb01ec7.zf1756dff08=AXI_BAR0_START;z1946f35eb5->z93beb01ec7.z3d41168cf2|=z533cc0b976;z1946f35eb5->z93beb01ec7.zaed73eb2ad|=zda905d3958;if((int)mxGetScalar(zee0787c51a)){z1946f35eb5->z93beb01ec7.length=z28a3a4d9f2*z6af3d2acb0->z7c81aa577e*(0x1131+2085-0x1952)*((int)mxGetScalar(z16e4f81fa8)+(0x974+20-0x987));}if((int)mxGetScalar(z210424a835)){z1946f35eb5->z93beb01ec7.length=z28a3a4d9f2*z6af3d2acb0->z7c81aa577e*(0x1fad+1838-0x26d7);z6af3d2acb0->zba47d7264b();}z8fe6e37678(z1946f35eb5,boardName,"\x41\x6e\x61\x6c\x6f\x67\x20\x44\x4d\x41\x20\x41\x44\x43\x20\x49\x4e\x49\x54\x20\x45\x4e\x44");z6af3d2acb0->z7af6572ea9();
#endif  
}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
int moduleId=(int)mxGetScalar(zfaa050b79d);char*boardName=io3xxGetBoardNameSgLib(moduleId);int z3e423c83e6=(0x274+5973-0x19c9);int ze0bc7e48d0=(int)(SG_BLOCK_TYPE_IO334_ANALOG_SETUP);sg_block_info*za9a3739e02=(sg_block_info*)sg_fpga_io3xx_block_get((uint32_t)moduleId,(uint32_t)ze0bc7e48d0,(uint32_t)z3e423c83e6);zf741ad1d87*zab86ba64c9=(zf741ad1d87*)za9a3739e02->custom_data;zff17be5515*z6af3d2acb0=(zff17be5515*)zab86ba64c9->z6af3d2acb0;z9258e0f85a*z1946f35eb5=(z9258e0f85a*)zab86ba64c9->z1946f35eb5;z8fe6e37678(z1946f35eb5,boardName,"\x41\x6e\x61\x6c\x6f\x67\x20\x44\x4d\x41\x20\x41\x44\x43\x20\x53\x54\x45\x50\x20\x45\x4e\x54\x52\x59");int z5d07366fd3=z28a3a4d9f2*z6af3d2acb0->z7c81aa577e*(0x832+7108-0x23f2);if((int)mxGetScalar(zee0787c51a)){z5d07366fd3*=((int)mxGetScalar(z16e4f81fa8)+(0x1221+1124-0x1684));}else if((int)mxGetScalar(z210424a835)){zdb8b3de61d(S,zab86ba64c9);}if(!(int)mxGetScalar(zee0787c51a)){z1946f35eb5->z93beb01ec7.length=z5d07366fd3;
#if (0x245+1698-0x8e7)
SG_PRINTF(DEBUG,"\x53\x65\x74\x74\x69\x6e\x67\x20\x64\x6d\x61\x52\x65\x67\x73\x2d\x3e\x73\x32\x6d\x6d\x2e\x6c\x65\x6e\x67\x74\x68\x20\x74\x6f\x20\x25\x64" "\n",z5d07366fd3);SG_PRINTF(DEBUG,"\x53\x65\x6e\x64\x69\x6e\x67\x20\x6d\x61\x6e\x75\x61\x6c\x20\x74\x72\x69\x67\x67\x65\x72" "\n");
#endif
z6af3d2acb0->z582f6a936a();}if(!(int)mxGetScalar(z210424a835)&&!(int)mxGetScalar(zee0787c51a)){z6274f5032f(z1946f35eb5,boardName);}if(!(int)mxGetScalar(z210424a835)){zdb8b3de61d(S,zab86ba64c9);}if((int)mxGetScalar(zee0787c51a)){z1946f35eb5->z93beb01ec7.length=z5d07366fd3;
#if (0x1091+59-0x10cc)
SG_PRINTF(DEBUG,"\x53\x65\x74\x74\x69\x6e\x67\x20\x64\x6d\x61\x52\x65\x67\x73\x2d\x3e\x73\x32\x6d\x6d\x2e\x6c\x65\x6e\x67\x74\x68\x20\x74\x6f\x20\x25\x64" "\n",z5d07366fd3);
#endif
}
#if (0x5f2+7263-0x2251)
for(int i=(0xab2+3399-0x17f9);i<(uint32_t)mxGetN(z9401605763);i++){uint32_t channel=(uint32_t)mxGetPr(z9401605763)[i];uint32_t z0ec8ec3cc7=z6af3d2acb0->ze873e94f36(channel-(0x6bc+1782-0xdb1));SG_PRINTF(DEBUG,"\x52\x65\x61\x64\x69\x6e\x67\x20\x41\x44\x43\x20\x6f\x75\x74\x70\x75\x74\x20\x72\x65\x67\x69\x73\x74\x65\x72\x20\x25\x69\x3a\x20\x72\x65\x67\x56\x61\x6c\x75\x65\x20\x3d\x20\x25\x75" "\n",channel,z0ec8ec3cc7);}
#endif  
#endif  
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE
#endif  
}
#ifndef MATLAB_MEX_FILE
static void zdb8b3de61d(SimStruct*S,zf741ad1d87*zab86ba64c9){int32_t*zc60ddfc6a1=(int32_t*)zab86ba64c9->z9e5d610777;double*z3e9acb26bc=(double*)zab86ba64c9->z44132c7346;int za746b13f73=(int)mxGetScalar(zee0787c51a)?(int)mxGetScalar(z16e4f81fa8):(0x568+1567-0xb86);uint32_t zad0e5075a4=(int)mxGetScalar(zee0787c51a)?(uint32_t)mxGetN(z9401605763):(uint32_t)mxGetN(z0453ae337c);uint32_t zaaf66dafad=(0x1bf9+2438-0x257f);uint32_t z0f2105f03a=(0x19bb+2986-0x2565);for(uint32_t za7a53d33d9=(0x88+7561-0x1e11);za7a53d33d9<zad0e5075a4;za7a53d33d9++){uint32_t compare=(int)mxGetScalar(zee0787c51a)?(uint32_t)mxGetPr(z9401605763)[za7a53d33d9]:(uint32_t)mxGetPr(z0453ae337c)[za7a53d33d9];if((uint32_t)mxGetPr(z9401605763)[zaaf66dafad]==compare){double*zf8940086c1=ssGetOutputPortRealSignal(S,zaaf66dafad);for(int z2ca80d4e56=(0x9e8+4092-0x19e4);z2ca80d4e56<za746b13f73;z2ca80d4e56++){z0f2105f03a=(z2ca80d4e56*zad0e5075a4)+za7a53d33d9;int32_t value=(zc60ddfc6a1[z0f2105f03a]<<(0x681+2960-0x1205))>>(0x15a3+1566-0x1bb5);zf8940086c1[z2ca80d4e56]=(double)value*z3e9acb26bc[zaaf66dafad];
#if (0x1029+4472-0x21a1)
SG_PRINTF(DEBUG,"\x57\x72\x69\x74\x69\x6e\x67\x20\x41\x44\x43\x20\x62\x6c\x6f\x63\x6b\x20\x6f\x75\x74\x70\x75\x74\x20\x25\x69\x3a\x20\x25\x69\x20\x2a\x20\x25\x66\x20\x3d\x20\x28\x25\x66\x29" "\n",zaaf66dafad,value,z3e9acb26bc[zaaf66dafad],zf8940086c1[z2ca80d4e56]);
#endif            
}zaaf66dafad++;}}}static void z8fe6e37678(z9258e0f85a*z1946f35eb5,char*boardName,const char*title){
#if (0x48a+1189-0x92f)
SG_PRINTF(INFO,"\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x25\x73\x20\x25\x73\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d\x2d" "\n""\x49\x4f\x33\x78\x78\x20\x41\x44\x43\x3a\x20\x64\x6d\x61\x52\x65\x67\x73\x2d\x3e\x73\x32\x6d\x6d\x2e\x64\x6d\x61\x43\x72\x3a\x20\x30\x78\x25\x30\x38\x58" "\n""\x49\x4f\x33\x78\x78\x20\x41\x44\x43\x3a\x20\x64\x6d\x61\x52\x65\x67\x73\x2d\x3e\x73\x32\x6d\x6d\x2e\x64\x6d\x61\x53\x72\x3a\x20\x30\x78\x25\x30\x38\x58" "\n""\x49\x4f\x33\x78\x78\x20\x41\x44\x43\x3a\x20\x64\x6d\x61\x52\x65\x67\x73\x2d\x3e\x73\x32\x6d\x6d\x2e\x6c\x65\x6e\x67\x74\x68\x3a\x30\x78\x25\x30\x38\x58" "\n",boardName,title,z1946f35eb5->z93beb01ec7.zaed73eb2ad,z1946f35eb5->z93beb01ec7.z3d41168cf2,z1946f35eb5->z93beb01ec7.length);
#endif
}static void z6274f5032f(z9258e0f85a*z1946f35eb5,char*boardName){int timeout=(0x25a6+27-0x25c1);while(!(z1946f35eb5->z93beb01ec7.z3d41168cf2&z630b009214)){sg_wait_s(1e-6);timeout++;if(timeout==(0x199d+2740-0x2069)){SG_PRINTF(WARNING,"\x25\x73\x20\x41\x6e\x61\x6c\x6f\x67\x20\x69\x6e\x70\x75\x74\x3a\x20\x44\x4d\x41\x20\x72\x65\x63\x65\x69\x76\x65\x20\x74\x69\x6d\x65\x6f\x75\x74\x2e" "\n",boardName);break;}}}
#endif
#include "sg_sfcn_glue.h" 

