// Copyright 2006-2026 Speedgoat GmbH

#define     S_FUNCTION_LEVEL    (0x367+4127-0x1384)
#undef      S_FUNCTION_NAME
#define     S_FUNCTION_NAME     sg_IO183_da_s
#include "sg_IO183.h"
#include "sg_callback_legacy.h"
#include "sg_printf.h"
#define DEBUG (0x87+7414-0x1d7d)
#define ze13f49a01f           ssGetSFcnParam(S, (0x4d+555-0x278))    
#define z702a26a5e9                ssGetSFcnParam(S, (0x924+1488-0xef3))    
#define z3832b85a32           ssGetSFcnParam(S, (0x66b+2035-0xe5c))    
#define z143c69c545         ssGetSFcnParam(S, (0x448+5976-0x1b9d))
#define z750e357e3d             ssGetSFcnParam(S, (0x73f+5506-0x1cbd))    
#define z84dd9a9a5c            ssGetSFcnParam(S, (0x188c+957-0x1c44))    
#define z7441273c8e     ssGetSFcnParam(S, (0xae4+804-0xe02))
#define zdf24515981                        (   (0xc2a+5211-0x207e))
#define zae2a70bf76       ((0x1992+3023-0x2561))
#define zaca310c05f     ((0xae4+6382-0x23d1))
#define z6fbf191d78    ((0xf56+6026-0x26de))
#define z4604fff5be   ((0x1f87+314-0x20be))
#define z1c1e23c2e0  ((0x6b1+4212-0x1721))
#define z2e6483d505      ((0x1b9b+229-0x1c7b))
#define zc5ce4cb81a      ((0xb08+5472-0x2068))
#define z4991bf82ec       ((0x1986+2904-0x24de))
#define z2b17e2ee3b      ((0x14f1+3455-0x226f))
static char_T msg[(0xe60+3699-0x1bd3)];static void mdlInitializeSizes(SimStruct*S){uint32_T i,zd8a0291585;zd8a0291585=(uint_T)mxGetN(z143c69c545);ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0xfc0+2350-0x18ee));ssSetNumDiscStates(S,(0x46c+1824-0xb8c));ssSetNumInputPorts(S,zd8a0291585);ssSetNumOutputPorts(S,(0x136+9234-0x2548));for(i=(0x6d8+1166-0xb66);i<zd8a0291585;i++){ssSetInputPortWidth(S,i,(0x194a+2926-0x24b7));ssSetInputPortDirectFeedThrough(S,i,(0xdc9+2130-0x161a));ssSetInputPortRequiredContiguous(S,i,(0x298+8038-0x21fd));}ssSetNumSampleTimes(S,(0x430+1581-0xa5c));ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetNumModes(S,(0x17d6+335-0x1925));ssSetNumNonsampledZCs(S,(0xaff+2067-0x1312));for(i=(0x4fb+3875-0x141e);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x1661+2674-0x20d3));}ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(z3832b85a32)[(0x605+3535-0x13d4)]==-1.0){ssSetSampleTime(S,(0x987+3534-0x1755),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x1520+4201-0x2589),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x1445+184-0x14fd),mxGetPr(z3832b85a32)[(0x1a3c+1535-0x203b)]);ssSetOffsetTime(S,(0x2ec+6185-0x1b15),0.0);}}
#define MDL_START
static void mdlStart(SimStruct*S){
#ifndef MATLAB_MEX_FILE
sg_PCIDevice zeccbadd9b3;uintptr_t z1167769581;uint32_T bus,slot;uint_T ze3584cafff;if(mxGetN(z702a26a5e9)==(0xa1b+881-0xd8b)){bus=(0x1d87+800-0x20a7);slot=(int_T)mxGetPr(z702a26a5e9)[(0x2378+262-0x247e)];}else{bus=(int_T)mxGetPr(z702a26a5e9)[(0x1dd+7692-0x1fe9)];slot=(int_T)mxGetPr(z702a26a5e9)[(0xf81+1322-0x14aa)];}if(sg_findPciDevice(&zeccbadd9b3,DEVNAME,VENDORID,DEVICEID,SUBVENDORID,SUBDEVICEID,(int)mxGetPr(ze13f49a01f)[(0x191+7235-0x1dd4)],bus,slot)){ssSetErrorStatus(S,pSgErrorStr);return;}z1167769581=(uintptr_t)sg_mapIo(&zeccbadd9b3,(0x11d0+4500-0x2364));ze3584cafff=(uint_T)mxGetN(z143c69c545);if(DEBUG){SG_PRINTF(DEBUG,"\x4e\x75\x6d\x20\x64\x61\x20\x63\x68\x61\x6e\x6e\x65\x6c\x73\x3a\x20\x25\x64" "\n",ze3584cafff);SG_PRINTF(DEBUG,"\x53\x69\x6d\x75\x6c\x74\x20\x6f\x75\x74\x3a\x20\x25\x64" "\n",(int_T)mxGetPr(z7441273c8e)[(0x103a+3294-0x1d18)]);}ssSetPWorkValue(S,z4991bf82ec,(void*)z1167769581);ssSetIWorkValue(S,zae2a70bf76,ze3584cafff);
#endif
}static void mdlOutputs(SimStruct*S,int_T z27c0327a06){
#ifndef MATLAB_MEX_FILE
uint32_T i;uintptr_t z1167769581;real_T*zc7fdaf6331,z0da2224540;uint_T ze3584cafff;uint16_T value;uint8_T z147269ba29,z805b048f01,zccaa542b0c,z558f96456e;z1167769581=(uintptr_t)ssGetPWorkValue(S,z4991bf82ec);ze3584cafff=ssGetIWorkValue(S,zae2a70bf76);for(i=(0x181f+2220-0x20cb);i<ze3584cafff;i++){zc7fdaf6331=(real_T*)ssGetInputPortSignal(S,i);zccaa542b0c=sg_inpB(z1167769581+(0x7f4+4939-0x1b2a));zccaa542b0c&=(0xc85+6189-0x24b1);if(zccaa542b0c==(0x584+1633-0xbe5)){z0da2224540=(*zc7fdaf6331/2.5)<=(0x6e9+6740-0x213c)?(*zc7fdaf6331/2.5)*65535.0:65535.0;}else{z0da2224540=(*zc7fdaf6331/5.0)<=(0x1059+2303-0x1957)?(*zc7fdaf6331/5.0)*65535.0:65535.0;}if(z0da2224540<0.0)z0da2224540=0.0;value=(uint16_T)z0da2224540;z147269ba29=(value&(0x739+2754-0x10fc));z805b048f01=(value>>(0x155d+205-0x1622));sg_outpB(z1167769581+(0x16a+9416-0x2622),z147269ba29);sg_outpB(z1167769581+(0x1b1a+1771-0x21f4),z805b048f01);z558f96456e=((0x5b2+627-0x824)<<(0xe61+3996-0x1df9))+((0x2b0+6865-0x1d80)<<((uint8_T)mxGetPr(z143c69c545)[i]-(0x2d8+1052-0x6f3)));while(sg_inpB(z1167769581+(0x1f24+1349-0x2452))&(0x2116+1273-0x258f));sg_outpB(z1167769581+(0x125b+419-0x13ea),z558f96456e);}if((int_T)mxGetPr(z7441273c8e)[(0x21a+777-0x523)]){while(sg_inpB(z1167769581+(0x520+4537-0x16c2))&(0x1917+2331-0x21b2));sg_outpB(z1167769581+(0xf6b+4964-0x22b8),(0x12e2+5161-0x26cb));}
#endif
}static void mdlTerminate(SimStruct*S){
#ifndef MATLAB_MEX_FILE
uint32_T i;uintptr_t z1167769581;real_T z2bb60441de,z0da2224540;uint_T ze3584cafff;uint16_T value;uint8_T z147269ba29,z805b048f01,zccaa542b0c,z558f96456e;z1167769581=(uintptr_t)ssGetPWorkValue(S,z4991bf82ec);ze3584cafff=ssGetIWorkValue(S,zae2a70bf76);for(i=(0x1e9+2322-0xafb);i<ze3584cafff;i++){if(sg_isModelInit()||(uint8_T)mxGetPr(z84dd9a9a5c)[i]){z2bb60441de=(real_T)mxGetPr(z750e357e3d)[i];zccaa542b0c=sg_inpB(z1167769581+(0x2024+878-0x237d));zccaa542b0c&=(0x16a9+3758-0x2556);if(zccaa542b0c==(0x660+749-0x94d)){z0da2224540=(z2bb60441de/2.5)<=(0x10e8+2614-0x1b1d)?(z2bb60441de/2.5)*65535.0:65535.0;}else{z0da2224540=(z2bb60441de/5.0)<=(0xb02+4611-0x1d04)?(z2bb60441de/5.0)*65535.0:65535.0;}if(z0da2224540<0.0)z0da2224540=0.0;value=(uint16_T)z0da2224540;z147269ba29=(value&(0x27d+2115-0x9c1));z805b048f01=(value>>(0x61c+6132-0x1e08));sg_outpB(z1167769581+(0x49f+6956-0x1fbb),z147269ba29);sg_outpB(z1167769581+(0x13ed+906-0x1766),z805b048f01);z558f96456e=((0x5e1+186-0x69a)<<(0x855+3419-0x15ac))+((0xb78+2266-0x1451)<<((uint8_T)mxGetPr(z143c69c545)[i]-(0x1ca1+330-0x1dea)));while(sg_inpB(z1167769581+(0xcb8+3440-0x1a11))&(0x741+1935-0xe50));sg_outpB(z1167769581+(0x17a+2342-0xa8c),z558f96456e);}}if((int_T)mxGetPr(z7441273c8e)[(0xf27+808-0x124f)]){while(sg_inpB(z1167769581+(0x267+7272-0x1eb8))&(0x3bc+1903-0xaab));sg_outpB(z1167769581+(0xf4f+2660-0x199c),(0x288+2344-0xb70));}
#endif
}
#ifdef MATLAB_MEX_FILE  
#include "simulink.c"   
#else
#include "cg_sfun.h"    
#endif

