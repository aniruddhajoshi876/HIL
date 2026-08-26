// Copyright 2006-2026 Speedgoat GmbH

#define         S_FUNCTION_LEVEL        (0x2131+303-0x225e)
#undef          S_FUNCTION_NAME
#define         S_FUNCTION_NAME         sg_IO901_IO902_setup_s
#include        <stddef.h>
#include        <stdlib.h>
#include        <stdint.h>
#include        "simstruc.h"
#include        "sg_IO901_IO902.h"
#define SG_EARLY_INIT   
#ifdef          MATLAB_MEX_FILE
#include     "mex.h"
#endif
#include "sg_callback.h"
#include "sg_printf.h"
#define zdf24515981        ((0xc3c+1292-0x1142))
#define z9328966a6d            ssGetSFcnParam(S, (0xee7+920-0x127f))
#define za056907be1              ssGetSFcnParam(S, (0x102c+1613-0x1678))
#define z7ed8a65dbb              ssGetSFcnParam(S, (0x1394+716-0x165e))
#define za2bc3913f1             ssGetSFcnParam(S, (0xb4f+4795-0x1e07))
#define z702a26a5e9              ssGetSFcnParam(S, (0xb4c+2323-0x145b))
#define zfaa050b79d             ssGetSFcnParam(S, (0x983+7495-0x26c5))
#define z2e6483d505            ((0x841+2441-0x11ca))
#define zc5ce4cb81a            ((0xd8+1264-0x5c8))
#define z2b17e2ee3b            ((0x4f3+473-0x6cc))
static char msg[(0x1976+1269-0x1d6b)];
#define z95835284b8             ((0x1b35+253-0x8ab))
#define zdd9aa31c07             (21264)
#define z55367ad797           "\x53\x43\x52\x41\x4d\x4e\x65\x74\x20\x47\x54"
#define z6209bc9836              ((0x185+2770-0xc57))
#define zb06b34b5e4           ((0x2a+7370-0x1cf2))
#define z6768453e6b               ((0xc04+6048-0x23a1))
#define z9e17beac99              ((0xf98+4042-0x1f5e))
#define zb58a04b204            ((0x1119+5201-0x2564))
#define zd71b350345            ((0x19da+2203-0x226e))
#ifndef MATLAB_MEX_FILE
static void z89cae3dd39(volatile uint32_t*addr,int32_t value,uint32_t z290764d186);
#endif
static void mdlInitializeSizes(SimStruct*S){int i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n""\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x1b30+64-0x1b70));ssSetNumDiscStates(S,(0x444+4202-0x14ae));ssSetNumInputPorts(S,(0xc67+402-0xdf9));ssSetNumOutputPorts(S,(0x755+1622-0xdab));ssSetNumSampleTimes(S,(0xeb6+3959-0x1e2c));ssSetNumIWork(S,z2e6483d505);ssSetNumRWork(S,zc5ce4cb81a);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x4e8+2596-0xf0c));ssSetNumNonsampledZCs(S,(0x8dc+4471-0x1a53));for(i=(0xf07+1200-0x13b7);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0xc07+5573-0x21cc));}ssSetOptions(S,SS_OPTION_RUNTIME_EXCEPTION_FREE_CODE|SS_OPTION_PLACE_ASAP);}static void mdlInitializeSampleTimes(SimStruct*S){ssSetSampleTime(S,(0x22b+2408-0xb93),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x8d0+7390-0x25ae),FIXED_IN_MINOR_STEP_OFFSET);}
#ifndef MATLAB_MEX_FILE
static void sg_ModelLoad(SimStruct*S){int32_t val,ze5ca39eccf[(0xfaa+5610-0x2592)];sg_PCIDevice ze296e0333d;volatile uint32_t*z1bd4bfb626;sg_mod_info*mod_info;z78d32bde66*z39b46fd01d;int moduleId=(int)mxGetPr(zfaa050b79d)[(0x1731+945-0x1ae2)];SG_PRINTF(INFO,"\x53\x74\x61\x72\x74\x20\x49\x6e\x69\x74\x69\x61\x6c\x69\x7a\x61\x74\x69\x6f\x6e\x20\x25\x73" "\n",z55367ad797);mod_info=sg_module_get_single(z6cd618c289,moduleId);if(mod_info==NULL){mod_info=sg_module_register(z6cd618c289,moduleId);if((int)mxGetPr(z702a26a5e9)[(0x722+4237-0x17af)]<(0x764+6829-0x2211)){if(sg_findPciDevice(&ze296e0333d,z55367ad797,z95835284b8,zdd9aa31c07,SG_NO_SUB,SG_NO_SUB,moduleId,SG_NO_BUS_SLOT,SG_NO_BUS_SLOT)){ssSetErrorStatus(S,pSgErrorStr);return;}}else{int bus,slot;if(mxGetN(z702a26a5e9)==(0x3a3+4975-0x1711)){bus=(0x396+3871-0x12b5);slot=(int)mxGetPr(z702a26a5e9)[(0xd30+4403-0x1e63)];}else{bus=(int)mxGetPr(z702a26a5e9)[(0x18ca+3180-0x2536)];slot=(int)mxGetPr(z702a26a5e9)[(0x1172+3842-0x2073)];}if(sg_findPciDevice(&ze296e0333d,z55367ad797,z95835284b8,zdd9aa31c07,SG_NO_SUB,SG_NO_SUB,moduleId,bus,slot)){ssSetErrorStatus(S,pSgErrorStr);return;}}z39b46fd01d=calloc((0x3c+9864-0x26c3),sizeof(z78d32bde66));z39b46fd01d->z52d81e7135=(volatile uint32_t*)sg_mapMemory(&ze296e0333d,(0x1618+2556-0x2014));z39b46fd01d->zb2aecffdd7=(volatile uint32_t*)sg_mapMemory(&ze296e0333d,(0xdca+5165-0x21f6));z39b46fd01d->z0ad0eb424c=(volatile uint32_t*)sg_mapMemory(&ze296e0333d,(0x483+6260-0x1cf5));mod_info->custom_data=(void*)z39b46fd01d;}else{SG_PRINTF(DEBUG,"\x44\x6f\x20\x6e\x6f\x74\x20\x72\x65\x67\x69\x73\x74\x65\x72\x20\x25\x73\x20\x6d\x6f\x64\x75\x6c\x65" "\n",z55367ad797);return;}z1bd4bfb626=z39b46fd01d->z52d81e7135;val=(int32_t)mxGetPr(z9328966a6d)[(0xaa0+5353-0x1f89)];if((val>=(0xdd+8422-0x21c3))&&(val<=(0xd48+1610-0x1293))){z1bd4bfb626[z9e17beac99]&=~(65280);z1bd4bfb626[z9e17beac99]|=((val&(0x13d+7277-0x1cab))<<(0x4a3+4537-0x1654));}z89cae3dd39(&z1bd4bfb626[z9e17beac99],(int32_t)mxGetPr(za056907be1)[(0xcd2+1637-0x1337)],(0x269+9305-0x26b2));z89cae3dd39(&z1bd4bfb626[z9e17beac99],(int32_t)mxGetPr(z7ed8a65dbb)[(0x158+6758-0x1bbe)],131072);z89cae3dd39(&z1bd4bfb626[z9e17beac99],(int32_t)mxGetPr(z7ed8a65dbb)[(0x460+3235-0x1102)],65536);z89cae3dd39(&z1bd4bfb626[z9e17beac99],(int32_t)mxGetPr(z7ed8a65dbb)[(0x152+4930-0x1492)],262144);z89cae3dd39(&z1bd4bfb626[z9e17beac99],(int32_t)mxGetPr(z7ed8a65dbb)[(0x7fd+6927-0x2309)],1048576);z89cae3dd39(&z1bd4bfb626[z9e17beac99],(int32_t)mxGetPr(z7ed8a65dbb)[(0x382+5946-0x1ab8)],524288);z89cae3dd39(&z1bd4bfb626[zb06b34b5e4],(int32_t)mxGetPr(z7ed8a65dbb)[(0x1df3+1115-0x2249)],(0xc13+2978-0x17b3));z89cae3dd39(&z1bd4bfb626[zb06b34b5e4],(int32_t)mxGetPr(z7ed8a65dbb)[(0xe1c+759-0x110d)],(0x67d+7757-0x24c9));z89cae3dd39(&z1bd4bfb626[zb06b34b5e4],(int32_t)mxGetPr(z7ed8a65dbb)[(0xe0+6959-0x1c08)],(0x11a3+1167-0x1622));if((int)mxGetPr(z7ed8a65dbb)[(0x35+6009-0x17a6)]==(0x2ad+8342-0x2342)){z1bd4bfb626[zb58a04b204]=(uint32_t)mxGetPr(za2bc3913f1)[(0x13f2+1842-0x1b24)];SG_PRINTF(INFO,"\x62\x6d\x61\x73\x6b\x20\x3d\x20\x25\x78\x2c\x20\x25\x78\x2c\x20\x25\x66" "\n",(uint32_t)mxGetPr(za2bc3913f1)[(0x51f+8292-0x2583)],(int)mxGetPr(za2bc3913f1)[(0x1434+3615-0x2253)],mxGetPr(za2bc3913f1)[(0x1cbb+1018-0x20b5)]);}z89cae3dd39(&z1bd4bfb626[z9e17beac99],(int32_t)mxGetPr(z7ed8a65dbb)[(0x101d+206-0x10e2)],2097152);z89cae3dd39(&z1bd4bfb626[zd71b350345],(int32_t)mxGetPr(z7ed8a65dbb)[(0x84c+7595-0x25ed)],(0x1231+332-0x137c));z89cae3dd39(&z1bd4bfb626[z6768453e6b],(int32_t)mxGetPr(z7ed8a65dbb)[(0xf6f+6055-0x270b)],262144);val=((z1bd4bfb626[z9e17beac99]&(0x588+918-0x90e))>>(0x6d5+6521-0x204a));ze5ca39eccf[(0xa8f+6667-0x249a)]=(int)mxGetPr(z7ed8a65dbb)[(0x1242+1968-0x19e5)];ze5ca39eccf[(0x29f+9287-0x26e5)]=(int)mxGetPr(z7ed8a65dbb)[(0x136+300-0x254)];switch((int)mxGetPr(z7ed8a65dbb)[(0x2da+3359-0xfed)]){case(0xcb8+5051-0x2073):ze5ca39eccf[val]=(0x10e6+3589-0x1eeb);break;case(0xc40+2815-0x173e):ze5ca39eccf[val]=(0x1aa3+136-0x1b2a);break;}z89cae3dd39(&z1bd4bfb626[z9e17beac99],ze5ca39eccf[(0xc58+287-0xd77)],(0xc80+5151-0x209e));z89cae3dd39(&z1bd4bfb626[z9e17beac99],
ze5ca39eccf[(0x170b+3460-0x248e)],(0x722+7722-0x254a));SG_PRINTF(DEBUG,"\x6d\x6c\x64\x53\x74\x61\x72\x74\x20\x63\x6f\x6d\x70\x6c\x65\x74\x65\x20\x66\x6f\x72\x20\x47\x54\x20\x63\x61\x72\x64\x20\x69\x6f\x41\x64\x64\x72\x3d\x25\x78" "\n",z1bd4bfb626);SG_PRINTF(INFO,"\x49\x6e\x69\x74\x69\x61\x6c\x69\x7a\x61\x74\x69\x6f\x6e\x20\x4f\x4b" "\n");}static void sg_ModelStart(SimStruct*S){}static void sg_ModelStep(SimStruct*S){}static void sg_ModelStop(SimStruct*S){int moduleId=(int)mxGetPr(zfaa050b79d)[(0xc74+6194-0x24a6)];z78d32bde66*z39b46fd01d;z39b46fd01d=(z78d32bde66*)sg_module_get_custom_data(z6cd618c289,moduleId);if(z39b46fd01d==NULL){sprintf(msg,"\x25\x73\x20\x73\x65\x74\x75\x70\x3a\x20\x4d\x6f\x64\x75\x6c\x65\x20\x6e\x6f\x74\x20\x72\x65\x67\x69\x73\x74\x65\x72\x65\x64" "\n",z55367ad797);ssSetErrorStatus(S,msg);return;}free(z39b46fd01d);sg_module_unregister(z6cd618c289,moduleId);}static void z89cae3dd39(volatile uint32_t*addr,int32_t value,uint32_t z290764d186){switch(value){case-(0x1bb+1299-0x6cd):break;case(0x4d4+967-0x89b):*addr&=~(z290764d186);break;case(0x172+78-0x1bf):*addr|=z290764d186;break;}}
#endif
#include "sg_sfcn_glue.h"   

