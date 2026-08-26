// Copyright 2006-2026 Speedgoat GmbH

#define     S_FUNCTION_LEVEL    (0x632+6575-0x1fdf)
#undef      S_FUNCTION_NAME
#define     S_FUNCTION_NAME     sg_IO183_setup_s
#include "sg_IO183.h"
#include "sg_callback_legacy.h"
#include "sg_printf.h"
#include "sg_module_types.h"
#define DEBUG (0x1826+1524-0x1e1a)
#define ze13f49a01f                   ssGetSFcnParam(S, (0x824+2094-0x1052))    
#define z702a26a5e9                        ssGetSFcnParam(S, (0x191+5348-0x1674))    
#define z7441273c8e             ssGetSFcnParam(S, (0x365+1381-0x8c8))
#define z0d9acd09bb                 ssGetSFcnParam(S, (0xee5+6098-0x26b4))    
#define z71374cdff0                    ssGetSFcnParam(S, (0x9a3+3680-0x17ff))    
#define z2e5c48c1a3                  ssGetSFcnParam(S, (0x1df6+1876-0x2545))
#define z12d825af76                 ssGetSFcnParam(S, (0xfa0+5087-0x2379))
#define z143c69c545                 ssGetSFcnParam(S, (0x1f6d+533-0x217b))
#define zc6f930323f                    ssGetSFcnParam(S, (0x1910+2020-0x20ec))
#define zcc03c07da0     ssGetSFcnParam(S, (0x29f+438-0x44c))    
#define ze5bdce7221      ssGetSFcnParam(S, (0xb7b+4609-0x1d72))   
#define zdf24515981                                (   (0x1933+482-0x1b0a))
#define zba952b5889      ((0x170+7113-0x1d39)) 
#define z2e6483d505              (zba952b5889 + z173eaebd82)
#define zc5ce4cb81a              ((0x342+8387-0x2405))
#define za3099081ca             ((0x6da+3822-0x15c8))
#define z2b17e2ee3b              ((0x3d+2315-0x947))
static char_T msg[(0x19ca+3235-0x256d)];static void z67f70fdb79(real_T t);static void mdlInitializeSizes(SimStruct*S){uint32_T i;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0xb38+2686-0x15b6));ssSetNumDiscStates(S,(0x1037+5374-0x2535));if(!ssSetNumInputPorts(S,(0x140b+3594-0x2215))){SG_PRINTF(ERROR,"\x65\x72\x72\x6f\x72\x20\x77\x68\x69\x6c\x65\x20\x73\x65\x74\x74\x69\x6e\x67\x20\x69\x6e\x70\x75\x74\x20\x70\x6f\x72\x74\x73" "\n");return;}if(!ssSetNumOutputPorts(S,(0xaa2+1161-0xf2b))){SG_PRINTF(ERROR,"\x65\x72\x72\x6f\x72\x20\x77\x68\x69\x6c\x65\x20\x73\x65\x74\x74\x69\x6e\x67\x20\x6f\x75\x74\x70\x75\x74\x20\x70\x6f\x72\x74\x73" "\n");return;}ssSetNumSampleTimes(S,(0x1a3a+2690-0x24bb));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0xbf4+6070-0x23aa));ssSetNumNonsampledZCs(S,(0x1095+4177-0x20e6));for(i=(0x5f7+1575-0xc1e);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x418+6836-0x1ecc));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE|SS_OPTION_PLACE_ASAP);}static void mdlInitializeSampleTimes(SimStruct*S){ssSetSampleTime(S,(0x713+7882-0x25dd),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x347+7871-0x2206),FIXED_IN_MINOR_STEP_OFFSET);}
#define MDL_START  
static void mdlStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
sg_PCIDevice zeccbadd9b3;uintptr_t z1167769581;uint32_T bus,slot;uint8_T z5235660200=(0x8e8+3301-0x15cd);int_T z615e5086bc;uint8_T z2c2b4ddfac,z3dff973793,z5d2fa37e03,z2344790e88,z3546cf30de,z07458b2bb8,z14e5316b99,z5df224bdcd;sg_mod_list z00018d0b83;uint32_T moduleId;moduleId=(uint32_T)mxGetPr(ze13f49a01f)[(0x805+6836-0x22b9)];if(sg_module_get(&z00018d0b83,z8379fe31ba,moduleId)>(0x36b+3848-0x1273)){return;}sg_module_register(z8379fe31ba,moduleId);if(mxGetN(z702a26a5e9)==(0x1fb+2800-0xcea)){bus=(0x416+3309-0x1103);slot=(int_T)mxGetPr(z702a26a5e9)[(0xbb+6803-0x1b4e)];}else{bus=(int_T)mxGetPr(z702a26a5e9)[(0x16da+1985-0x1e9b)];slot=(int_T)mxGetPr(z702a26a5e9)[(0x293+3316-0xf86)];}if(sg_findPciDevice(&zeccbadd9b3,DEVNAME,VENDORID,DEVICEID,SUBVENDORID,SUBDEVICEID,(int)moduleId,bus,slot)){ssSetErrorStatus(S,pSgErrorStr);return;}z1167769581=(uintptr_t)sg_mapIo(&zeccbadd9b3,(0xf34+5086-0x2312));z14e5316b99=(uint8_T)mxGetPr(z0d9acd09bb)[(0x6b1+3138-0x12f3)]-(0x935+973-0xd01);z3dff973793=(uint8_T)mxGetPr(z2e5c48c1a3)[(0xe85+2048-0x1685)]-(0x12f8+1619-0x194a);z5d2fa37e03=(uint8_T)mxGetPr(z12d825af76)[(0x1977+3274-0x2641)]-(0xd71+5155-0x2193);z3546cf30de=(uint8_T)mxGetPr(z71374cdff0)[(0xd1+751-0x3c0)]-(0x1770+775-0x1a76);z07458b2bb8=(uint8_T)mxGetPr(zc6f930323f)[(0x132b+4886-0x2641)]-(0x124d+1272-0x1744);z615e5086bc=(int_T)mxGetPr(z7441273c8e)[(0x1021+3089-0x1c32)];if(DEBUG){SG_PRINTF(DEBUG,"\x43\x6f\x75\x70\x6c\x69\x6e\x67\x3a\x20\x25\x64" "\n",z14e5316b99);SG_PRINTF(DEBUG,"\x41\x44\x20\x63\x68\x20\x6c\x6f\x77\x3a\x20\x25\x64" "\n",z3dff973793);SG_PRINTF(DEBUG,"\x41\x44\x20\x63\x68\x20\x68\x69\x67\x68\x3a\x20\x25\x64" "\n",z5d2fa37e03);SG_PRINTF(DEBUG,"\x41\x44\x20\x72\x61\x6e\x67\x65\x3a\x20\x25\x64" "\n",z3546cf30de);SG_PRINTF(DEBUG,"\x53\x69\x6d\x75\x6c\x74\x3a\x20\x25\x64" "\n",z615e5086bc);}sg_outpB(z1167769581+(0x7cd+7000-0x22b5)+(0x847+1424-0xdc8),(0x405+3404-0x10d1));z67f70fdb79((0x3e0+686-0x65c));z2c2b4ddfac=sg_inpB(z1167769581+(0x11a7+4962-0x2509)+(0x206b+530-0x227d));z2c2b4ddfac|=(0x13c8+3645-0x2185);sg_outpB(z1167769581+(0x1727+1086-0x1b65)+(0x922+1549-0xf2f),z2c2b4ddfac);z67f70fdb79((0x1524+2012-0x1cce));z2344790e88=sg_inpB(z1167769581+(0x1769+3822-0x2657)+(0x595+4853-0x1882));if(z14e5316b99){z2344790e88|=(0xd4a+1943-0x14d5);}z2344790e88|=z3546cf30de;sg_outpB(z1167769581+(0x238+2293-0xb2d)+(0xad6+6375-0x23b5),z2344790e88);z67f70fdb79((0x459+8552-0x258f));if(DEBUG){SG_PRINTF(DEBUG,"\x43\x6f\x75\x70\x6c\x6e\x67\x20\x61\x6e\x64\x20\x52\x61\x6e\x67\x65\x3a\x20\x25\x58" "\n",sg_inpB(z1167769581+(0x6db+4652-0x1907)+(0x4e4+8660-0x26b0)));}if(z14e5316b99){if(z5d2fa37e03>(0x5bb+6907-0x20b3)){sprintf(msg,"\x4f\x6e\x6c\x79\x20\x34\x20\x63\x68\x61\x6e\x6e\x65\x6c\x73\x20\x61\x72\x65\x20\x61\x76\x61\x69\x6c\x61\x62\x6c\x65\x20\x69\x6e\x20\x64\x69\x66\x66\x65\x72\x65\x6e\x74\x69\x61\x6c\x20\x6d\x6f\x64\x65\x2e");ssSetErrorStatus(S,msg);return;}}sg_outpB(z1167769581+(0xee5+1697-0x1586)+(0x156f+2650-0x1fc5),z3dff973793);sg_outpB(z1167769581+(0x7ef+7307-0x247a)+(0x58b+1966-0xd34),z5d2fa37e03);if(DEBUG){SG_PRINTF(DEBUG,"\x53\x63\x61\x6e\x6e\x65\x6e\x3a\x20\x25\x64" "\n",sg_inpB(z1167769581+(0xbf9+1810-0x130b)+(0x13a6+2319-0x1cab)));}z5df224bdcd=sg_inpB(z1167769581+(0x1c7c+2713-0x2705)+(0x56f+1997-0xd35));z5df224bdcd|=(0x794+5832-0x1ddc);sg_outpB(z1167769581+(0x144b+4816-0x270b)+(0x186+4022-0x1135),z5df224bdcd);z67f70fdb79((0x1368+967-0x16fd));sg_outpB(z1167769581+(0x1048+1053-0x1450),z07458b2bb8);z67f70fdb79((0x302+120-0x348));switch((uint8_T)mxGetPr(zcc03c07da0)[(0x11e1+5243-0x265c)]-(0xfb7+4186-0x2010)){case(0x34d+5503-0x18cc):z5235660200=z239cf1f1c9;break;case(0xe04+337-0xf54):z5235660200=z3dca907fe3;break;default:sprintf(msg,"\x49\x6e\x76\x61\x6c\x69\x64\x20\x70\x75\x6c\x6c\x20\x72\x65\x73\x69\x73\x74\x6f\x72\x20\x76\x61\x6c\x75\x65");ssSetErrorStatus(S,msg);return;}sg_outpB(z1167769581+(0x3af+8766-0x2578),(0x19dc+727-0x1cb3));sg_outpB(z1167769581+(0x581+7472-0x223c),z5235660200<<(0x1620+281-0x1738));sg_outpB(z1167769581+(0x392+5890-0x1a1f),(z5235660200<<(0x15c8+1208-0x1a7f))+(0x636+6257-0x1ea6));z67f70fdb79((0x1280+6748-0x250c));
sg_outpB(z1167769581+(0xd94+4625-0x1f30),z5235660200<<(0x998+2538-0x1381));if(z615e5086bc){sg_outpB(z1167769581+(0x509+3405-0x1240),(0x229c+402-0x242d));if(DEBUG){SG_PRINTF(DEBUG,"\x53\x69\x6d\x75\x6c\x74\x20\x6d\x6f\x64\x65\x20\x73\x65\x6c\x65\x63\x74\x65\x64" "\n");}z67f70fdb79((0x1254+4596-0x2416));}
#endif
}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){}static void mdlTerminate(SimStruct*S){
#ifndef MATLAB_MEX_FILE
sg_module_unregister(z8379fe31ba,(uint32_T)mxGetPr(ze13f49a01f)[(0x1f3+471-0x3ca)]);
#endif  
}static void z67f70fdb79(real_T t){
#ifndef MATLAB_MEX_FILE
sg_wait_s(t/1000000.0);
#endif
}
#ifdef MATLAB_MEX_FILE  
#include "simulink.c"   
#else
#include "cg_sfun.h"    
#endif

