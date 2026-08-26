// Copyright 2006-2026 Speedgoat GmbH

#define S_FUNCTION_LEVEL    (0xbe7+5978-0x233f)
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO421_ref_s
#define zd6a3cd0da0 "\x49\x4f\x34\x32\x31\x2d\x35"
#define zdd9aa31c07 30354
#define z95835284b8 5548
#define z20f97d736d 22320 
#define z24077972a0   22361 
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif
#define SG_HAS_MDL_EXIT 
#define SG_EARLY_INIT   
#include    "sg_callback.h"
#include    "sg_printf.h"
#define z403d45b116 za42cf7dd4a[(0x1ac3+757-0x1db8)]    
#define z86992bd6b1                 ssGetSFcnParam(S, (0x893+4224-0x1913))
#define zce920812fd                    ssGetSFcnParam(S, (0x13e8+4491-0x2572))
#define z73855d5f1e                 ssGetSFcnParam(S, (0xac0+1983-0x127d))
#define z702a26a5e9                    ssGetSFcnParam(S, (0x1091+4397-0x21bb))
#define ze13f49a01f               ssGetSFcnParam(S, (0x883+3368-0x15a7))
#define zdf24515981                               ((0x21+2724-0xac0))
#define z2e6483d505              ((0x144c+313-0x1585))
#define zc5ce4cb81a              ((0x537+58-0x571))
#define z2b17e2ee3b              ((0x902+320-0xa42))
#define zc43f61927d             (0xdb6+4727-0x1e6d)
#define zec98984c71            (0x3c9+4832-0x14a9)
#define zb8eceb6db5            (0x1744+1401-0x1ab9)
#define z5cca8a360f            (0x676+1771-0xb59)
#define z34de2919eb            (0x8da+955-0xa89)
#define zf0a367e7e1  (0xfc0+5200-0x1ca8)
#define z8389a0694a      (0xced+8001-0x24c2)
#define zfd273e051e         (0x1b5d+3135-0x202c)
#define z4267492038        (0x1175+5155-0x1e24)
#define z88e2416cde              (0x1441+3207-0x1950)
#define zfaa050b79d(slot)     za42cf7dd4a[((((slot-(0xab+1374-0x608)) * (0xe13+7828-0x24a7) + z88e2416cde)/(0xf1f+4892-0x2239)))]
static char msg[(0x1ad6+1510-0x1fbc)];static void mdlInitializeSizes(SimStruct*S){uint32_t i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0xe8+8444-0x21e4));ssSetNumDiscStates(S,(0x2226+259-0x2329));ssSetNumOutputPorts(S,(0xc19+1141-0x108e));ssSetNumInputPorts(S,(0x2620+160-0x26c0));ssSetNumSampleTimes(S,(0x15f5+1911-0x1d6b));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x137f+7-0x1386));ssSetNumNonsampledZCs(S,(0xd4c+2937-0x18c5));for(i=(0x124a+4916-0x257e);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x1e0+535-0x3f7));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){ssSetSampleTime(S,(0xd90+5529-0x2329),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x2299+736-0x2579),FIXED_IN_MINOR_STEP_OFFSET);}static void sg_ModelLoad(SimStruct*S){
#ifndef MATLAB_MEX_FILE
sg_PCIDevice zc3b39a639a;volatile uint16_t*za42cf7dd4a;uint32_t zd0072007fc=(0xd0+2187-0x95b);double z4d7ed90f27,za2273a11ad;uint32_t zd4b3a173d5,z61ab524473;uint16_t bus=(0x672+899-0x9f5),slot=(0x821+1001-0xc0a);uint32_t moduleId=(uint32_t)mxGetPr(ze13f49a01f)[(0x1fc6+827-0x2301)];sg_mod_info*mod_info;mod_info=sg_module_get_single(z46e1e90e3b,moduleId);if(mod_info==NULL){mod_info=sg_module_register(z46e1e90e3b,moduleId);if((int)mxGetPr(z702a26a5e9)[(0x2a8+8221-0x22c5)]<(0x1776+526-0x1984)){if(sg_findPciDevice(&zc3b39a639a,zd6a3cd0da0,z95835284b8,zdd9aa31c07,SG_NO_SUB,SG_NO_SUB,moduleId,SG_NO_BUS_SLOT,SG_NO_BUS_SLOT)){ssSetErrorStatus(S,pSgErrorStr);return;}}else{if(mxGetN(z702a26a5e9)==(0xd8f+5218-0x21f0)){bus=(0x1947+597-0x1b9c);slot=(uint16_t)mxGetPr(z702a26a5e9)[(0x1191+1005-0x157e)];}else{bus=(uint16_t)mxGetPr(z702a26a5e9)[(0x1c85+1102-0x20d3)];slot=(uint16_t)mxGetPr(z702a26a5e9)[(0x248+2277-0xb2c)];}if(sg_findPciDevice(&zc3b39a639a,zd6a3cd0da0,z95835284b8,zdd9aa31c07,SG_NO_SUB,SG_NO_SUB,moduleId,bus,slot)){ssSetErrorStatus(S,pSgErrorStr);return;}}za42cf7dd4a=(volatile uint16_t*)sg_mapMemory(&zc3b39a639a,(0x1411+3613-0x222e));mod_info->custom_data=(void*)za42cf7dd4a;}else{SG_PRINTF(DEBUG,"\x44\x6f\x20\x6e\x6f\x74\x20\x72\x65\x67\x69\x73\x74\x65\x72\x20\x25\x73\x20\x6d\x6f\x64\x75\x6c\x65" "\n",zd6a3cd0da0);za42cf7dd4a=(uint16_t*)sg_module_get_custom_data(z46e1e90e3b,(uint32_t)mxGetPr(ze13f49a01f)[(0x1966+3421-0x26c3)]);if(za42cf7dd4a==NULL){ssSetErrorStatus(S,"\x49\x4f\x34\x32\x31\x2d\x35\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x69\x6e\x20\x4d\x6f\x64\x65\x6c\x4c\x6f\x61\x64" "\n");return;}}switch((uint32_t)mxGetPr(z86992bd6b1)[(0x1b89+2642-0x25db)]){case(0xaa6+5552-0x2055):zd0072007fc=(0xca4+4109-0x1cb1);break;case(0x11dd+2413-0x1b48):zd0072007fc=(0x925+5737-0x178e);break;case(0x62c+624-0x899):zd0072007fc=(0x11c9+6971-0x1d04);break;}uint16_t z0879a25298=zfaa050b79d((int)mxGetPr(z86992bd6b1)[(0xe17+3588-0x1c1b)]);if((z0879a25298<z20f97d736d)||(z0879a25298>z24077972a0)){sprintf(msg,"\x25\x73\x20\x5b\x25\x64\x2f\x25\x64\x5d\x3a\x20\x57\x72\x6f\x6e\x67\x20\x70\x6c\x75\x67\x2d\x69\x6e\x20\x27\x25\x63\x25\x63\x27\x20\x69\x6e\x20\x73\x6c\x6f\x74\x20\x25\x69\x2e",zd6a3cd0da0,bus,slot,(char)(z0879a25298>>(0x10a5+2572-0x1aa9)),(char)z0879a25298,(int)mxGetPr(z86992bd6b1)[(0xa2d+2236-0x12e9)]);ssSetErrorStatus(S,msg);return;}z4d7ed90f27=mxGetPr(zce920812fd)[(0x93d+935-0xce4)];z4d7ed90f27*=(0x4e6+5529-0x1a1b);zd4b3a173d5=(uint32_t)z4d7ed90f27;za42cf7dd4a[zd0072007fc/(0x1a2a+2151-0x228f)+zec98984c71/(0x156b+1048-0x1981)]=(uint16_t)(zd4b3a173d5&65535);z403d45b116;za42cf7dd4a[zd0072007fc/(0x1b19+1025-0x1f18)+zb8eceb6db5/(0x75b+4551-0x1920)]=(uint16_t)((zd4b3a173d5>>(0x665+193-0x716))&65535);z403d45b116;za2273a11ad=mxGetPr(z73855d5f1e)[(0xf0a+5089-0x22eb)];za2273a11ad*=(0x1f0d+1486-0x2477);z61ab524473=(uint32_t)za2273a11ad;za42cf7dd4a[zd0072007fc/(0x88+4497-0x1217)+z5cca8a360f/(0x14aa+2919-0x200f)]=(uint16_t)(z61ab524473&65535);z403d45b116;za42cf7dd4a[zd0072007fc/(0xd7+3856-0xfe5)+z34de2919eb/(0x29f+6745-0x1cf6)]=(uint16_t)((z61ab524473>>(0xe2b+593-0x106c))&65535);z403d45b116;za42cf7dd4a[zd0072007fc/(0x11eb+965-0x15ae)+zc43f61927d/(0xe85+4168-0x1ecb)]=(0x9d3+6890-0x24bc);SG_PRINTF(INFO,"\x49\x4f\x34\x32\x31\x2d\x35\x20\x53\x6c\x6f\x74\x20\x25\x64\x3a\x20\x52\x65\x66\x65\x72\x65\x6e\x63\x65\x20\x73\x6f\x75\x72\x63\x65\x20\x63\x6f\x6e\x66\x69\x67\x75\x72\x65\x64\x2e" "\n",(uint32_t)mxGetPr(z86992bd6b1)[(0x237+427-0x3e2)]);
#endif
}static void sg_ModelStart(SimStruct*S){}static void sg_ModelStep(SimStruct*S){}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE
volatile uint16_t*za42cf7dd4a;uint16_t zd0072007fc=(0x2ec+4136-0x1314);za42cf7dd4a=(uint16_t*)sg_module_get_custom_data(z46e1e90e3b,(uint32_t)mxGetPr(ze13f49a01f)[(0x1bf0+1564-0x220c)]);if(za42cf7dd4a==NULL){ssSetErrorStatus(S,"\x49\x4f\x34\x32\x31\x2d\x35\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x69\x6e\x20\x4d\x6f\x64\x65\x6c\x53\x74\x6f\x70" "\n");return;}switch((uint32_t)mxGetPr(z86992bd6b1)[(0x12bf+1779-0x19b2)]){case(0x11b7+3239-0x1e5d):zd0072007fc=(0x1104+3794-0x1fd6);break;case(0x1075+1350-0x15b9):zd0072007fc=(0xdca+5059-0x198d);break;case(0x17ca+401-0x1958):zd0072007fc=(0x19cd+1683-0x1060);break;}za42cf7dd4a[zd0072007fc/(0x8da+5858-0x1fba)+zc43f61927d/(0x5f3+6602-0x1fbb)]=(0x1ca0+721-0x1f71);
#endif
}static void sg_ModelExit(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_t moduleId=(uint32_t)mxGetPr(ze13f49a01f)[(0x18c1+1767-0x1fa8)];sg_module_unregister(z46e1e90e3b,moduleId);SG_PRINTF(DEBUG,"\x49\x4f\x34\x32\x31\x2d\x35\x3a\x20\x55\x6e\x72\x65\x67\x69\x73\x74\x65\x72\x20\x6d\x6f\x64\x75\x6c\x65" "\n");
#endif
}
#include "sg_sfcn_glue.h"   

