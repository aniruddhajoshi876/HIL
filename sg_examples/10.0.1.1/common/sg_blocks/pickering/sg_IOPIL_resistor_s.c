// Copyright 2006-2026 Speedgoat GmbH

#define     S_FUNCTION_LEVEL    (0x17f5+2131-0x2046)
#undef      S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_IOPIL_resistor_s
#ifdef MATLAB_MEX_FILE
#include    "mex.h"
#endif
#define SG_HAS_MDL_EXIT 
#define SG_EARLY_INIT   
#include    "sg_callback.h"
#include    "sg_IOPIL.h"
#define     z1ee33e4ee9    100e6       
#define z58f464b4bb                  ssGetSFcnParam(S, (0x181a+562-0x1a4c)) 
#define z63fca46654            ssGetSFcnParam(S, (0x1733+571-0x196d)) 
#define za9d8fb6bcf             ssGetSFcnParam(S, (0xd62+3862-0x1c76)) 
#define zf80b27df71                ssGetSFcnParam(S, (0x853+3808-0x1730)) 
#define zc8bbaa6115               ssGetSFcnParam(S, (0x68a+7881-0x254f)) 
#define zed102d70b2     ssGetSFcnParam(S, (0x45b+148-0x4ea)) 
#define z702a26a5e9                ssGetSFcnParam(S, (0x1bcf+1688-0x2261)) 
#define zabe1e0cd2c          ssGetSFcnParam(S, (0x5a4+1539-0xba0)) 
#define zb9e2d422d8         ssGetSFcnParam(S, (0xdf5+5050-0x21a7)) 
#define z18c20ee744    ssGetSFcnParam(S, (0xf43+3924-0x1e8e)) 
#define zfff8e838b7      ssGetSFcnParam(S,(0xaa5+788-0xdaf)) 
#define z8661f90f0f      ssGetSFcnParam(S,(0x1616+1797-0x1d10)) 
#define zef1a16a792      ssGetSFcnParam(S,(0xf6c+3603-0x1d73)) 
#define za0b945e05b      ssGetSFcnParam(S,(0x14b9+4190-0x250a)) 
#define zc59091b31f       ssGetSFcnParam(S,(0x388+3373-0x10a7)) 
#define z8829498ef2           ssGetSFcnParam(S,(0x3cb+8695-0x25b3)) 
#define zcb272787be        ssGetSFcnParam(S,(0x593+303-0x6b2)) 
#define zb9f539adad           ssGetSFcnParam(S,(0xb73+5925-0x2287)) 
#define z7f2cd70249        ssGetSFcnParam(S,(0x287+1971-0xa28)) 
#define z81bccb6f6f        ssGetSFcnParam(S,(0x1da9+583-0x1fdd)) 
#define z3a1bb87b55     ssGetSFcnParam(S,(0x5d7+8061-0x2540)) 
#define z5e881ae671        ssGetSFcnParam(S,(0x1333+3598-0x212c)) 
#define zb679937c2d     ssGetSFcnParam(S,(0xe57+109-0xeae)) 
#define zdf24515981                          ((0x1d93+1731-0x243f)) 
#define z2e6483d505              ((0x10e7+559-0x1316))
#define zc5ce4cb81a              ((0x1777+2938-0x22f1))
#define z2b17e2ee3b              ((0x1108+322-0x124a))
static char msg[(0x1313+2660-0x1c77)];static void mdlInitializeSizes(SimStruct*S){int32_t i,z1125a0a075;zfe27abf92b z59c2dba4da=(uint32_t)mxGetPr(zb9e2d422d8)[(0xa57+3033-0x1630)];ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0x2617+11-0x2622));ssSetNumDiscStates(S,(0x684+2029-0xe71));ssSetNumSampleTimes(S,(0x7cd+5385-0x1cd5));ssSetNumModes(S,(0x59d+5826-0x1c5f));ssSetNumNonsampledZCs(S,(0x1a1b+151-0x1ab2));for(i=(0x85f+2374-0x11a5);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0x942+7170-0x2544));}z1125a0a075=(int)mxGetN(za9d8fb6bcf);switch(z59c2dba4da){case z653c47301b:case z63f8622009:case zebd117054a:case zabf4e37527:ssSetNumInputPorts(S,z1125a0a075);for(i=(0x1b54+2997-0x2709);i<z1125a0a075;i++){ssSetInputPortWidth(S,i,(0xe82+926-0x121f));ssSetInputPortDirectFeedThrough(S,i,(0x92c+5610-0x1f15));ssSetInputPortRequiredContiguous(S,i,(0x1d80+2378-0x26c9));}if(mxGetPr(zed102d70b2)[(0xf2b+2075-0x1746)]){ssSetNumOutputPorts(S,z1125a0a075);for(i=(0x23b+7489-0x1f7c);i<z1125a0a075;i++){ssSetOutputPortWidth(S,i,(0xf8d+5648-0x259c));}}else{ssSetNumOutputPorts(S,(0xdf1+2217-0x169a));}break;case zda5a04ed90:ssSetNumInputPorts(S,z1125a0a075*(0x20a1+1129-0x2508));for(i=(0xc70+5800-0x2318);i<z1125a0a075*(0xe61+2818-0x1961);i++){ssSetInputPortWidth(S,i,(0x10f4+3550-0x1ed1));ssSetInputPortDirectFeedThrough(S,i,(0xa0+3554-0xe81));ssSetInputPortRequiredContiguous(S,i,(0x1ffb+1167-0x2489));}if(mxGetPr(zed102d70b2)[(0xb55+3239-0x17fc)]){ssSetNumOutputPorts(S,z1125a0a075*(0x19b7+310-0x1aeb));for(i=(0x318+1810-0xa2a);i<z1125a0a075*(0x1783+1020-0x1b7d);i++){ssSetOutputPortWidth(S,i,(0xd9b+5376-0x229a));}}else{ssSetNumOutputPorts(S,(0x2126+345-0x227f));}break;case z3b8f1118bd:default:sprintf(msg,"\x4d\x6f\x64\x75\x6c\x65\x20\x63\x61\x74\x65\x67\x6f\x72\x79\x20\x75\x6e\x64\x65\x66\x69\x6e\x65\x64\x3a\x20\x42\x6f\x61\x72\x64\x20\x6e\x6f\x74\x20\x73\x75\x70\x70\x6f\x72\x74\x65\x64\x21" "\n");ssSetErrorStatus(S,msg);return;}ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(zabe1e0cd2c)[(0xd14+1775-0x1403)]==-1.0){ssSetSampleTime(S,(0xa3f+401-0xbd0),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0x1cda+824-0x2012),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x393+3607-0x11aa),mxGetPr(zabe1e0cd2c)[(0x1c7c+255-0x1d7b)]);ssSetOffsetTime(S,(0x32f+8249-0x2368),0.0);}}
#ifndef MATLAB_MEX_FILE
static uint32_t z29442cf092(uint32_t z615725805d,uint32_t z41654156de){uint32_t Mask;if(z41654156de>(0x18e1+2248-0x2189)){SG_PRINTF(TRACE,"\x45\x52\x52\x4f\x52\x3a\x20\x72\x65\x76\x65\x72\x73\x65\x33\x32\x20\x63\x61\x6e\x27\x74\x20\x72\x65\x76\x65\x72\x73\x65\x20\x76\x61\x6c\x75\x65\x73\x20\x67\x72\x65\x61\x74\x65\x72\x20\x74\x68\x61\x6e\x20\x33\x32\x20\x62\x69\x74\x21" "\n");return(0xf90+2037-0x1785);}Mask=((0x693+6073-0x1e4b)<<z41654156de)-(0x1779+3688-0x25e0);z615725805d=((z615725805d&4294901760)>>(0x1561+3808-0x2431))|((z615725805d&65535)<<(0xc14+2861-0x1731));z615725805d=((z615725805d&4278255360)>>(0x96b+763-0xc5e))|((z615725805d&16711935)<<(0x10b+727-0x3da));z615725805d=((z615725805d&4042322160)>>(0xb3c+551-0xd5f))|((z615725805d&252645135)<<(0xde1+6373-0x26c2));z615725805d=((z615725805d&3435973836)>>(0x72d+10-0x735))|((z615725805d&858993459)<<(0x25+6256-0x1893));z615725805d=((z615725805d&2863311530)>>(0x57d+1694-0xc1a))|((z615725805d&1431655765)<<(0x4c6+7618-0x2287));z615725805d=(z615725805d>>((0x61d+3393-0x133e)-z41654156de))&Mask;return z615725805d;}static void zbd9be05e78(SimStruct*S,real_T*R){real_T min,max;if(!S||!R)return;if(*R==(0x1228+744-0x1510))return;min=(real_T)mxGetPr(zfff8e838b7)[(0x77d+5173-0x1bb2)];max=(real_T)mxGetPr(zef1a16a792)[(0x1075+307-0x11a8)];if(*R>max)*R=max;else if(*R<min)*R=min;}static void z0c58c711d5(SimStruct*S,int zb9e97bf36a,int ch,real_T value){real_T r=value;int z0fcae3df66=(0x1b+4910-0x1349);if(r>=z1ee33e4ee9){r=HUGE_VAL;SG_PRINTF(TRACE,"\x63\x68\x20\x25\x69\x20\x73\x65\x74\x20\x52\x20\x3d\x20\x6f\x70\x65\x6e\x20\x63\x69\x72\x63\x75\x69\x74" "\n",ch);}else{zbd9be05e78(S,&r);if(r!=value)SG_PRINTF(TRACE,"\x63\x68\x20\x25\x69\x20\x73\x65\x74\x20\x52\x20\x74\x6f\x20\x25\x2e\x32\x66\x20\x28\x6c\x69\x6d\x69\x74\x65\x64\x20\x66\x72\x6f\x6d\x20\x25\x2e\x32\x66\x29\x20" "\n",ch,value,r);else SG_PRINTF(TRACE,"\x63\x68\x20\x25\x69\x20\x73\x65\x74\x20\x52\x20\x74\x6f\x20\x25\x2e\x32\x66\x20",ch,value);}
#ifndef zed77f4a138
z0fcae3df66=PIL_ResSetResistance(zb9e97bf36a,ch,(0x18ec+1769-0x1fd5),r);
#endif
if(z0fcae3df66){if(z0fcae3df66==ER_BAD_RESISTANCE){sprintf(msg,"\x63\x68\x20\x25\x69\x20\x72\x65\x71\x75\x65\x73\x74\x65\x64\x20\x52\x20\x3d\x20\x25\x2e\x32\x66\x20\x28\x25\x2e\x32\x66\x29\x20\x6e\x6f\x74\x20\x73\x75\x70\x70\x6f\x72\x74\x65\x64",ch,value,r);ssSetErrorStatus(S,msg);return;}else{z5142a89028(z0fcae3df66);sprintf(msg,"\x50\x49\x4c\x5f\x52\x65\x73\x53\x65\x74\x52\x65\x73\x69\x73\x74\x61\x6e\x63\x65\x20\x72\x65\x74\x75\x72\x6e\x73\x20\x25\x73" "\n",z423e891770);
#ifdef z196140dc34
SG_PRINTF(TRACE,msg);
#else
ssSetErrorStatus(S,msg);return;
#endif
}}}static void z8b679a1f37(int zb9e97bf36a,int ch,real_T*z97ab4274ec){
#ifndef zed77f4a138
int z0fcae3df66=PIL_ResGetResistance(zb9e97bf36a,ch,z97ab4274ec);if(z0fcae3df66){z5142a89028(z0fcae3df66);SG_PRINTF(TRACE,"\x50\x49\x4c\x5f\x52\x65\x73\x47\x65\x74\x52\x65\x73\x69\x73\x74\x61\x6e\x63\x65\x20\x72\x65\x74\x75\x72\x6e\x73\x20\x25\x73" "\n",z423e891770);}else{SG_PRINTF(TRACE,"\x63\x68\x20\x25\x69\x20\x52\x20\x3d\x20\x25\x2e\x32\x66\x20" "\n",ch,*z97ab4274ec);}
#endif 
}static void sg_ModelLoad(SimStruct*S){sg_PCIDevice ze296e0333d;uint32_t VendorID=(uint32_t)mxGetPr(z8829498ef2)[(0x10f1+3948-0x205d)];uint32_t SubVendorID=(uint32_t)mxGetPr(zcb272787be)[(0xc77+2769-0x1748)];uint32_t DeviceID=(uint32_t)mxGetPr(zb9f539adad)[(0x1073+4224-0x20f3)];uint32_t SubDeviceID=(uint32_t)mxGetPr(z7f2cd70249)[(0x1667+151-0x16fe)];uint32_t zc3522d5e82=(uint32_t)mxGetPr(z81bccb6f6f)[(0x847+62-0x885)];uint32_t z32d77e63e5=(uint32_t)mxGetPr(z3a1bb87b55)[(0xe71+1327-0x13a0)];uint32_t z6996cbbe95=(uint32_t)mxGetPr(z5e881ae671)[(0xa97+4948-0x1deb)];uint32_t z786cb64f75=(uint32_t)mxGetPr(zb679937c2d)[(0x2197+80-0x21e7)];char DevName[(0x2200+453-0x2361)];uint32_t zb9e97bf36a;uint32_t moduleId=(uint32_t)mxGetPr(z58f464b4bb)[(0x2082+28-0x209e)];sg_mod_info*mod_info;z92aecbf1ff*z86f8673608;real_T za3a4dd5546=0.0;uint32_t zcbc7e3fc60,z199e5a4ac9;int z78205ce1b7,z0fcae3df66,channel;char zd626712b39[(0x7b9+1084-0xb91)];zfe27abf92b z59c2dba4da;uint32_t z41654156de=(uint32_t)mxGetPr(z8661f90f0f)[(0x8c1+4408-0x19f9)];int z19eeaa569b=(int)mxGetPr(z18c20ee744)[(0x9f4+19-0xa07)];uint32_t z615725805d,z61bb1f585f;uint64_t zef1a26df0e,z94e28eea33;uint32_t bus,slot;z59c2dba4da=(zfe27abf92b)mxGetPr(zb9e2d422d8)[(0xfdd+2303-0x18dc)];mxGetString(z63fca46654,zd626712b39,mxGetN(z63fca46654)+(0x1351+3978-0x22da));strcpy(DevName,"\x53\x70\x65\x65\x64\x67\x6f\x61\x74\x20");strcat(DevName,zd626712b39);mod_info=sg_module_get_single(z172e6e4f91,moduleId);if(mod_info==NULL){mod_info=sg_module_register(z172e6e4f91,moduleId);z86f8673608=calloc((0xd81+1616-0x13d0),sizeof(z92aecbf1ff));z86f8673608->z59c2dba4da=z59c2dba4da;mod_info->custom_data=(void*)z86f8673608;}else{SG_PRINTF(DEBUG,"\x44\x6f\x20\x6e\x6f\x74\x20\x72\x65\x67\x69\x73\x74\x65\x72\x20\x25\x73\x20\x6d\x6f\x64\x75\x6c\x65" "\n",DevName);return;}
#ifndef z196140dc34
if((int)mxGetPr(z702a26a5e9)[(0x4df+462-0x6ad)]<(0x129+8823-0x23a0)){if(sg_detectPciDevice(&ze296e0333d,DevName,VendorID,DeviceID,SubVendorID,SubDeviceID,(0xd80+6461-0x26bc))!=(0x1ae5+2066-0x22f7)){if(sg_detectPciDevice(&ze296e0333d,DevName,z6996cbbe95,zc3522d5e82,z786cb64f75,z32d77e63e5,(0x7d2+4027-0x178c))!=(0x1a77+2541-0x2464)){ssSetErrorStatus(S,pSgErrorStr);return;}}bus=ze296e0333d.bus;slot=ze296e0333d.slot;}else{bus=(uint32_t)mxGetPr(z702a26a5e9)[(0x107+7699-0x1f1a)];slot=(uint32_t)mxGetPr(z702a26a5e9)[(0xdf7+873-0x115f)];if(sg_detectPciDeviceAtSlot(&ze296e0333d,DevName,VendorID,DeviceID,SubVendorID,SubDeviceID,bus,slot)!=(0x676+5977-0x1dcf)){if(sg_detectPciDeviceAtSlot(&ze296e0333d,DevName,z6996cbbe95,zc3522d5e82,z786cb64f75,z32d77e63e5,bus,slot)!=(0x666+614-0x8cc)){ssSetErrorStatus(S,pSgErrorStr);return;}}}
#else 
bus=(0xeef+2814-0x19ed);slot=(0x13e6+3635-0x2219);
#endif
if(sg_setAbilities()!=(0x164b+4100-0x264f)){ssSetErrorStatus(S,"\x43\x6f\x75\x6c\x64\x20\x6e\x6f\x74\x20\x67\x65\x74\x20\x70\x72\x69\x76\x69\x6c\x65\x67\x65\x73\x2e");return;}
#ifndef zed77f4a138
#ifdef z196140dc34
SG_PRINTF(DEBUG,"\x44\x52\x59\x20\x52\x55\x4e\x20\x28\x64\x65\x62\x75\x67\x20\x6d\x6f\x64\x65\x3a\x20\x72\x75\x6e\x20\x77\x69\x74\x68\x6f\x75\x74\x20\x63\x61\x72\x64\x29" "\n");
#else
z0fcae3df66=PIL_OpenSpecifiedCard(bus,slot,&zb9e97bf36a);if(z0fcae3df66){z5142a89028(z0fcae3df66);sprintf(msg,"\x25\x73\x20\x4f\x70\x65\x6e\x20\x63\x61\x72\x64\x20\x65\x72\x72\x6f\x72\x28\x62\x75\x73\x20\x25\x69\x2c\x20\x73\x6c\x6f\x74\x20\x25\x69\x29\x3a\x20\x25\x73",DevName,bus,slot,z423e891770);ssSetErrorStatus(S,msg);return;}
#endif
#endif
z86f8673608->zb9e97bf36a=zb9e97bf36a;SG_PRINTF(INFO,"\x25\x73\x20\x28\x25\x69\x2f\x25\x69\x29" "\n",DevName,bus,slot);
#ifdef zed77f4a138
z0fcae3df66=(0x1a24+938-0x1dce);SG_PRINTF(DEBUG,"\x4e\x4f\x20\x4c\x49\x42\x20\x43\x41\x4c\x4c\x53\x20\x28\x64\x65\x62\x75\x67\x29" "\n");
#else
z0fcae3df66=PIL_Status(zb9e97bf36a);if(z0fcae3df66==STAT_OK){SG_PRINTF(INFO,"\x53\x74\x61\x74\x75\x73\x3a\x20\x4f\x4b" "\n");}else{zec4dfa539e(z0fcae3df66);}
#endif
SG_PRINTF(DEBUG,"\x49\x4f\x39\x78\x78\x20\x4d\x6f\x64\x75\x6c\x65\x49\x44\x3a\x20\x25\x69\x2c\x20\x50\x49\x4c\x5f\x43\x61\x72\x64\x49\x44\x3a\x20\x25\x69" "\n",moduleId,zb9e97bf36a);if(z59c2dba4da==z653c47301b||z59c2dba4da==zda5a04ed90){for(z78205ce1b7=(0xbd1+1872-0x1321);z78205ce1b7<(int)mxGetN(za9d8fb6bcf);z78205ce1b7++){
#ifndef zed77f4a138
double z4c3a7c95fa,z8d90ec5c87,zdee13bad76,za1a6c447ea,zd11466038d,zc23452a018,z2cc6cbc324;uint32_t z0b969267e6;
#endif
channel=(int)mxGetPr(za9d8fb6bcf)[z78205ce1b7];
#ifdef zed77f4a138
z0fcae3df66=(0x2198+458-0x2362);
#else
z0fcae3df66=PIL_ResInfo(zb9e97bf36a,channel,&z4c3a7c95fa,&z8d90ec5c87,&zdee13bad76,&za1a6c447ea,&zd11466038d,&zc23452a018,&z2cc6cbc324,&z0b969267e6);
#endif
if(z0fcae3df66){z5142a89028(z0fcae3df66);sprintf(msg,"\x25\x73\x3a\x20\x50\x49\x4c\x5f\x52\x65\x73\x49\x6e\x66\x6f\x20\x65\x72\x72\x6f\x72\x3a\x20\x25\x73",DevName,z423e891770);ssSetErrorStatus(S,msg);return;}}}SG_PRINTF(DEBUG,"\x53\x65\x74\x74\x69\x6e\x67\x20\x69\x6e\x69\x74\x69\x61\x6c\x20\x76\x61\x6c\x75\x65\x73\x20" "\n");for(z78205ce1b7=(0x7fb+5805-0x1ea8);z78205ce1b7<(int)mxGetN(za9d8fb6bcf);z78205ce1b7++){channel=(int)mxGetPr(za9d8fb6bcf)[z78205ce1b7];switch(z59c2dba4da){case z653c47301b:z61bb1f585f=((0x74b+4705-0x19ab)<<z41654156de)-(0x10f8+1561-0x1710);za3a4dd5546=(real_T)mxGetPr(zf80b27df71)[z78205ce1b7];z615725805d=(za3a4dd5546>z61bb1f585f)?z61bb1f585f:(uint32_t)za3a4dd5546;SG_PRINTF(DEBUG,"\x63\x68\x20\x25\x69\x20\x73\x65\x74\x20\x52\x20\x74\x6f\x20\x25\x69\x20\x28\x25\x2e\x32\x66\x29" "\n",channel,z615725805d,za3a4dd5546);z615725805d=z615725805d^z61bb1f585f;
#ifdef zed77f4a138
z0fcae3df66=(0x111a+1176-0x15b2);
#else
z0fcae3df66=PIL_WriteSub(zb9e97bf36a,channel,&z615725805d);
#endif
if(z0fcae3df66){z5142a89028(z0fcae3df66);sprintf(msg,"\x25\x73\x20\x3a\x20\x50\x49\x4c\x5f\x57\x72\x69\x74\x65\x53\x75\x62\x20\x65\x72\x72\x6f\x72\x28\x63\x68\x2e\x20\x25\x69\x29\x3a\x20\x25\x73",DevName,channel,z423e891770);ssSetErrorStatus(S,msg);return;}break;case zda5a04ed90:z61bb1f585f=((0xa73+6926-0x2580)<<z41654156de)-(0xb6+9159-0x247c);za3a4dd5546=(real_T)mxGetPr(zf80b27df71)[(z78205ce1b7*(0x7b1+7831-0x2646))];zcbc7e3fc60=(za3a4dd5546>z61bb1f585f)?z61bb1f585f:(uint32_t)za3a4dd5546;SG_PRINTF(DEBUG,"\x63\x68\x20\x25\x69\x20\x73\x65\x74\x20\x52\x41\x20\x74\x6f\x20\x25\x69\x20\x28\x25\x2e\x32\x66\x29" "\n",channel,zcbc7e3fc60,za3a4dd5546);za3a4dd5546=(real_T)mxGetPr(zf80b27df71)[(z78205ce1b7*(0x9e0+6329-0x2297))+(0x123+4577-0x1303)];z199e5a4ac9=(za3a4dd5546>z61bb1f585f)?z61bb1f585f:(uint32_t)za3a4dd5546;SG_PRINTF(DEBUG,"\x63\x68\x20\x25\x69\x20\x73\x65\x74\x20\x52\x42\x20\x74\x6f\x20\x25\x69\x20\x28\x25\x2e\x32\x66\x29" "\n",channel,z199e5a4ac9,za3a4dd5546);z94e28eea33=(uint64_t)z61bb1f585f;zef1a26df0e=((uint64_t)zcbc7e3fc60&z94e28eea33)|(((uint64_t)z29442cf092(z199e5a4ac9,z41654156de)<<z41654156de)&(z94e28eea33<<z41654156de));z94e28eea33=(uint64_t)z61bb1f585f+((uint64_t)z61bb1f585f<<z41654156de);zef1a26df0e=zef1a26df0e^z94e28eea33;
#ifdef zed77f4a138
z0fcae3df66=(0x19+3296-0xcf9);
#else
z0fcae3df66=PIL_WriteSub(zb9e97bf36a,channel,(uint32_t*)&zef1a26df0e);
#endif
if(z0fcae3df66){z5142a89028(z0fcae3df66);sprintf(msg,"\x25\x73\x20\x3a\x20\x50\x49\x4c\x5f\x57\x72\x69\x74\x65\x53\x75\x62\x20\x65\x72\x72\x6f\x72\x28\x63\x68\x2e\x20\x25\x69\x29\x3a\x20\x25\x73",DevName,channel,z423e891770);ssSetErrorStatus(S,msg);return;}break;case z63f8622009:case zebd117054a:za3a4dd5546=(real_T)mxGetPr(zf80b27df71)[z78205ce1b7];z0c58c711d5(S,zb9e97bf36a,channel,za3a4dd5546);break;case zabf4e37527:za3a4dd5546=(real_T)mxGetPr(zf80b27df71)[z78205ce1b7];
#if (0x1478+2548-0x1e6b) 
z615725805d=(0x15b2+1478-0x1b6a);
#ifdef zed77f4a138
z0fcae3df66=(0x274+3972-0x11f8);
#else
z0fcae3df66=PIL_WriteSub(zb9e97bf36a,channel+z19eeaa569b,&z615725805d);
#endif
if(z0fcae3df66){z5142a89028(z0fcae3df66);sprintf(msg,"\x25\x73\x20\x3a\x20\x50\x49\x4c\x5f\x57\x72\x69\x74\x65\x53\x75\x62\x20\x65\x72\x72\x6f\x72\x28\x63\x68\x2e\x20\x25\x69\x29\x3a\x20\x25\x73",DevName,channel,z423e891770);ssSetErrorStatus(S,msg);return;}
#else 
SG_PRINTF(DEBUG,"\x52\x65\x73\x69\x73\x74\x61\x6e\x63\x65\x20\x63\x68\x65\x63\x6b\x3a\x20\x63\x68\x25\x69\x20\x3d\x20\x25\x66" "\n",channel,za3a4dd5546);z615725805d=(0xe13+3771-0x1cc8);
#ifdef zed77f4a138
z0fcae3df66=(0x14aa+3416-0x2202);
#else
z0fcae3df66=PIL_WriteSub(zb9e97bf36a,channel+z19eeaa569b,&z615725805d);
#endif
if(z0fcae3df66){z5142a89028(z0fcae3df66);sprintf(msg,"\x25\x73\x20\x3a\x20\x50\x49\x4c\x5f\x57\x72\x69\x74\x65\x53\x75\x62\x20\x65\x72\x72\x6f\x72\x28\x63\x68\x2e\x20\x25\x69\x29\x3a\x20\x25\x73",DevName,channel,z423e891770);ssSetErrorStatus(S,msg);return;}
#endif 
z0c58c711d5(S,zb9e97bf36a,channel,za3a4dd5546);break;default:sprintf(msg,"\x25\x73\x20\x3a\x20\x75\x6e\x64\x65\x66\x69\x6e\x65\x64\x20\x63\x61\x72\x64\x20\x74\x79\x70\x65\x21\x20\x65\x43\x61\x72\x64\x54\x79\x70\x65\x20\x3d\x20\x25\x69\x20\x28\x63\x68\x2e\x20\x25\x69\x29",DevName,z59c2dba4da,channel);ssSetErrorStatus(S,msg);return;}}}static void sg_ModelStart(SimStruct*S){}static void sg_ModelStep(SimStruct*S){real_T*z235e5703b9;real_T*z6e7cc23b69;int z78205ce1b7;int channel;int z0fcae3df66;uint32_t zcbc7e3fc60,z199e5a4ac9;zfe27abf92b z59c2dba4da=z3b8f1118bd;uint32_t zb9e97bf36a;uint32_t z41654156de=(uint32_t)mxGetPr(z8661f90f0f)[(0x20c6+895-0x2445)];uint32_t z615725805d,z61bb1f585f;uint64_t zef1a26df0e,z94e28eea33;z92aecbf1ff*z86f8673608;z86f8673608=(z92aecbf1ff*)sg_module_get_custom_data(z172e6e4f91,(uint32_t)mxGetPr(z58f464b4bb)[(0xa30+6909-0x252d)]);if(z86f8673608==NULL){ssSetErrorStatus(S,"\x52\x65\x73\x69\x73\x74\x6f\x72\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x69\x6e\x20\x4d\x6f\x64\x65\x6c\x53\x74\x65\x70" "\n");return;}zb9e97bf36a=z86f8673608->zb9e97bf36a;z59c2dba4da=z86f8673608->z59c2dba4da;for(z78205ce1b7=(0x401+5468-0x195d);z78205ce1b7<(int)mxGetN(za9d8fb6bcf);z78205ce1b7++){channel=(int)mxGetPr(za9d8fb6bcf)[z78205ce1b7];switch(z59c2dba4da){case z653c47301b:z61bb1f585f=((0x3bc+2306-0xcbd)<<z41654156de)-(0x209b+471-0x2271);z6e7cc23b69=(real_T*)ssGetInputPortRealSignal(S,z78205ce1b7);if(!z6e7cc23b69){sprintf(msg,"\x20\x70\x74\x49\x6e\x50\x6f\x72\x74\x20\x69\x73\x20\x70\x4e\x55\x4c\x4c\x20\x28\x63\x68\x20\x25\x69\x29",channel);ssSetErrorStatus(S,msg);return;}z615725805d=(z6e7cc23b69[(0x91+7995-0x1fcc)]>z61bb1f585f)?z61bb1f585f:(uint32_t)z6e7cc23b69[(0xd80+4669-0x1fbd)];if(mxGetPr(zed102d70b2)[(0x1692+1817-0x1dab)]){z235e5703b9=ssGetOutputPortSignal(S,z78205ce1b7);z235e5703b9[(0xd04+728-0xfdc)]=(real_T)(z615725805d);}z615725805d=z615725805d^z61bb1f585f;
#ifdef zed77f4a138
z0fcae3df66=(0x5f+7418-0x1d59);
#else
z0fcae3df66=PIL_WriteSub(zb9e97bf36a,channel,&z615725805d);
#endif
if(z0fcae3df66){z5142a89028(z0fcae3df66);sprintf(msg,"\x50\x49\x4c\x5f\x57\x72\x69\x74\x65\x53\x75\x62\x20\x72\x65\x74\x75\x72\x6e\x73\x20\x25\x73",z423e891770);ssSetErrorStatus(S,msg);return;}break;case zda5a04ed90:z61bb1f585f=((0xb+5358-0x14f8)<<z41654156de)-(0x1af+2585-0xbc7);z6e7cc23b69=(real_T*)ssGetInputPortRealSignal(S,(z78205ce1b7*(0x1789+3966-0x2705)));if(!z6e7cc23b69){sprintf(msg,"\x20\x70\x74\x49\x6e\x50\x6f\x72\x74\x20\x69\x73\x20\x70\x4e\x55\x4c\x4c\x20\x28\x63\x68\x20\x25\x69\x29",channel);ssSetErrorStatus(S,msg);return;}zcbc7e3fc60=(z6e7cc23b69[(0x144a+291-0x156d)]>z61bb1f585f)?z61bb1f585f:(uint32_t)z6e7cc23b69[(0xcba+4054-0x1c90)];z6e7cc23b69=(real_T*)ssGetInputPortRealSignal(S,(z78205ce1b7*(0x59f+2213-0xe42))+(0x927+7384-0x25fe));if(!z6e7cc23b69){sprintf(msg,"\x20\x70\x74\x49\x6e\x50\x6f\x72\x74\x20\x69\x73\x20\x70\x4e\x55\x4c\x4c\x20\x28\x63\x68\x20\x25\x69\x29",channel);ssSetErrorStatus(S,msg);return;}z199e5a4ac9=(z6e7cc23b69[(0x1374+3680-0x21d4)]>z61bb1f585f)?z61bb1f585f:(uint32_t)z6e7cc23b69[(0xf9f+508-0x119b)];z94e28eea33=(uint64_t)z61bb1f585f;zef1a26df0e=((uint64_t)zcbc7e3fc60&z94e28eea33)|(((uint64_t)z29442cf092(z199e5a4ac9,z41654156de)<<z41654156de)&(z94e28eea33<<z41654156de));if(mxGetPr(zed102d70b2)[(0x8bf+5990-0x2025)]){z235e5703b9=ssGetOutputPortSignal(S,(z78205ce1b7*(0x617+5889-0x1d16)));z235e5703b9[(0x35+2316-0x941)]=(real_T)(zcbc7e3fc60);z235e5703b9=ssGetOutputPortSignal(S,(z78205ce1b7*(0x9c4+2722-0x1464))+(0x619+4467-0x178b));z235e5703b9[(0x7c1+583-0xa08)]=(real_T)(z199e5a4ac9);}z94e28eea33=(uint64_t)z61bb1f585f+((uint64_t)z61bb1f585f<<z41654156de);zef1a26df0e=zef1a26df0e^z94e28eea33;
#ifdef zed77f4a138
z0fcae3df66=(0x1609+2068-0x1e1d);
#else
z0fcae3df66=PIL_WriteSub(zb9e97bf36a,channel,(uint32_t*)&zef1a26df0e);
#endif
if(z0fcae3df66){z5142a89028(z0fcae3df66);sprintf(msg,"\x50\x6f\x74\x65\x6e\x74\x69\x6f\x6d\x65\x74\x65\x72\x3a\x20\x50\x49\x4c\x5f\x57\x72\x69\x74\x65\x53\x75\x62\x20\x65\x72\x72\x6f\x72\x28\x63\x68\x2e\x20\x25\x69\x29\x3a\x20\x25\x73",channel,z423e891770);ssSetErrorStatus(S,msg);return;}break;case z63f8622009:case zebd117054a:case zabf4e37527:z6e7cc23b69=(real_T*)ssGetInputPortRealSignal(S,z78205ce1b7);if(!z6e7cc23b69){sprintf(msg,"\x20\x70\x74\x49\x6e\x50\x6f\x72\x74\x20\x69\x73\x20\x70\x4e\x55\x4c\x4c\x20\x28\x63\x68\x20\x25\x69\x29",channel);ssSetErrorStatus(S,msg);return;}z0c58c711d5(S,zb9e97bf36a,channel,z6e7cc23b69[(0x210+9307-0x266b)]);if(mxGetPr(zed102d70b2)[(0x324+8406-0x23fa)]){z235e5703b9=ssGetOutputPortSignal(S,z78205ce1b7);z8b679a1f37(zb9e97bf36a,channel,z235e5703b9);}break;default:sprintf(msg,"\x75\x6e\x64\x65\x66\x69\x6e\x65\x64\x20\x63\x61\x72\x64\x20\x74\x79\x70\x65\x21\x20\x65\x43\x61\x72\x64\x54\x79\x70\x65\x20\x3d\x20\x25\x69\x20\x28\x63\x68\x2e\x20\x25\x69\x29",z59c2dba4da,channel);ssSetErrorStatus(S,msg);return;}}}static void sg_ModelStop(SimStruct*S){real_T za3a4dd5546=0.0;int z78205ce1b7;int channel;uint32_t zcbc7e3fc60,z199e5a4ac9;uint32_t z41654156de=(uint32_t)mxGetPr(z8661f90f0f)[(0x236a+456-0x2532)];zfe27abf92b z59c2dba4da;uint32_t zb9e97bf36a;uint32_t z0fcae3df66;uint32_t z615725805d,z61bb1f585f;uint64_t zef1a26df0e,z94e28eea33;z92aecbf1ff*z86f8673608;z86f8673608=(z92aecbf1ff*)sg_module_get_custom_data(z172e6e4f91,(uint32_t)mxGetPr(z58f464b4bb)[(0xd3f+5622-0x2335)]);if(z86f8673608==NULL){ssSetErrorStatus(S,"\x52\x65\x73\x69\x73\x74\x6f\x72\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x69\x6e\x20\x4d\x6f\x64\x65\x6c\x53\x74\x6f\x70" "\n");return;}zb9e97bf36a=z86f8673608->zb9e97bf36a;z59c2dba4da=z86f8673608->z59c2dba4da;z61bb1f585f=((0x137c+130-0x13fd)<<z41654156de)-(0x9bc+845-0xd08);for(z78205ce1b7=(0x8a8+5254-0x1d2e);z78205ce1b7<(int)mxGetN(za9d8fb6bcf);z78205ce1b7++){channel=(int)mxGetPr(za9d8fb6bcf)[z78205ce1b7];switch(z59c2dba4da){case z653c47301b:if(mxGetPr(zc8bbaa6115)[z78205ce1b7]==(0xa64+4504-0x1bfb)){za3a4dd5546=(real_T)mxGetPr(zf80b27df71)[z78205ce1b7];z615725805d=(za3a4dd5546>z61bb1f585f)?z61bb1f585f:(uint32_t)za3a4dd5546;z615725805d=z615725805d^z61bb1f585f;
#ifdef zed77f4a138
z0fcae3df66=(0x5ef+7389-0x22cc);
#else
z0fcae3df66=PIL_WriteSub(zb9e97bf36a,channel,&z615725805d);
#endif
if(z0fcae3df66){z5142a89028(z0fcae3df66);sprintf(msg,"\x50\x49\x4c\x5f\x57\x72\x69\x74\x65\x53\x75\x62\x20\x72\x65\x74\x75\x72\x6e\x73\x20\x25\x73",z423e891770);ssSetErrorStatus(S,msg);return;}}break;case zda5a04ed90:if(mxGetPr(zc8bbaa6115)[z78205ce1b7]==(0x1089+2141-0x18e5)){za3a4dd5546=(uint32_t)mxGetPr(zf80b27df71)[(z78205ce1b7*(0x812+613-0xa75))];zcbc7e3fc60=(za3a4dd5546>z61bb1f585f)?(uint32_t)z61bb1f585f:(uint32_t)za3a4dd5546;za3a4dd5546=(uint32_t)mxGetPr(zf80b27df71)[(z78205ce1b7*(0x14d8+2840-0x1fee))+(0x18a+7964-0x20a5)];z199e5a4ac9=(za3a4dd5546>z61bb1f585f)?(uint32_t)z61bb1f585f:(uint32_t)za3a4dd5546;z94e28eea33=(uint64_t)z61bb1f585f;zef1a26df0e=((uint64_t)zcbc7e3fc60&z94e28eea33)|(((uint64_t)z29442cf092(z199e5a4ac9,z41654156de)<<z41654156de)&(z94e28eea33<<z41654156de));z94e28eea33=(uint64_t)z61bb1f585f+((uint64_t)z61bb1f585f<<z41654156de);zef1a26df0e=zef1a26df0e^z94e28eea33;
#ifdef zed77f4a138
z0fcae3df66=(0x6d5+724-0x9a9);
#else
z0fcae3df66=PIL_WriteSub(zb9e97bf36a,channel,(uint32_t*)&zef1a26df0e);
#endif
if(z0fcae3df66){z5142a89028(z0fcae3df66);sprintf(msg,"\x50\x6f\x74\x65\x6e\x74\x69\x6f\x6d\x65\x74\x65\x72\x3a\x20\x50\x49\x4c\x5f\x57\x72\x69\x74\x65\x53\x75\x62\x20\x65\x72\x72\x6f\x72\x28\x63\x68\x2e\x20\x25\x69\x29\x3a\x20\x25\x73",channel,z423e891770);ssSetErrorStatus(S,msg);return;}}break;case z63f8622009:case zebd117054a:case zabf4e37527:if(mxGetPr(zc8bbaa6115)[z78205ce1b7]==(0x64d+7510-0x23a2)){za3a4dd5546=(real_T)mxGetPr(zf80b27df71)[z78205ce1b7];z0c58c711d5(S,zb9e97bf36a,channel,za3a4dd5546);}break;default:sprintf(msg,"\x75\x6e\x64\x65\x66\x69\x6e\x65\x64\x20\x63\x61\x72\x64\x20\x74\x79\x70\x65\x21\x20\x65\x43\x61\x72\x64\x54\x79\x70\x65\x20\x3d\x20\x25\x69\x20\x28\x63\x68\x2e\x20\x25\x69\x29",z59c2dba4da,channel);ssSetErrorStatus(S,msg);return;}}}static void sg_ModelExit(SimStruct*S){z92aecbf1ff*z86f8673608;uint32_t moduleId=(uint32_t)mxGetPr(z58f464b4bb)[(0x15fc+406-0x1792)];uint32_t z0fcae3df66;z86f8673608=(z92aecbf1ff*)sg_module_get_custom_data(z172e6e4f91,moduleId);if(z86f8673608!=NULL){
#ifndef zed77f4a138
#ifdef z196140dc34
SG_PRINTF(DEBUG,"\x44\x52\x59\x20\x52\x55\x4e\x20\x28\x77\x69\x74\x68\x6f\x75\x74\x20\x63\x61\x72\x64\x29" "\n");
#else
z0fcae3df66=PIL_CloseSpecifiedCard(z86f8673608->zb9e97bf36a);if(z0fcae3df66){z5142a89028(z0fcae3df66);sprintf(msg,"\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x63\x6c\x6f\x73\x65\x20\x63\x61\x72\x64\x20\x25\x69\x3a\x20\x25\x73",z86f8673608->zb9e97bf36a,z423e891770);SG_PRINTF(WARNING,"\x25\x73" "\n",msg);}
#endif
#endif
free(z86f8673608);sg_module_unregister(z172e6e4f91,moduleId);SG_PRINTF(DEBUG,"\x52\x65\x73\x69\x73\x74\x6f\x72\x3a\x20\x55\x6e\x72\x65\x67\x69\x73\x74\x65\x72\x20\x6d\x6f\x64\x75\x6c\x65" "\n");}}
#endif 
#include "sg_sfcn_glue.h"   

