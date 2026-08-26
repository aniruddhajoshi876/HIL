// Copyright 2006-2026 Speedgoat GmbH

#define     S_FUNCTION_LEVEL    (0x3e4+8715-0x25ed)
#undef      S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_IOPIL_battery_s
#ifdef 		MATLAB_MEX_FILE
#include 	"mex.h"
#endif
#define SG_HAS_MDL_EXIT 
#define SG_EARLY_INIT   
#include    "sg_callback.h"
#include    "sg_IOPIL.h"
#define z58f464b4bb                  ssGetSFcnParam(S, (0x954+2859-0x147f)) 
#define z63fca46654            ssGetSFcnParam(S, (0x1799+463-0x1967)) 
#define za9d8fb6bcf             ssGetSFcnParam(S, (0xc15+1917-0x1390)) 
#define z39987748a1         ssGetSFcnParam(S, (0x16bb+1778-0x1daa)) 
#define z4ea1453708        ssGetSFcnParam(S, (0x6bf+4952-0x1a13)) 
#define zf90994d09c        ssGetSFcnParam(S, (0xf16+572-0x114d)) 
#define zcad462ae84       ssGetSFcnParam(S, (0xeb+2316-0x9f1)) 
#define z6df5e34903        ssGetSFcnParam(S, (0x1766+2279-0x2046)) 
#define ze5a3733a3e       ssGetSFcnParam(S, (0x9e4+6206-0x221a)) 
#define z3a4baa9b4c    ssGetSFcnParam(S, (0x512+6893-0x1ff6)) 
#define zed102d70b2     ssGetSFcnParam(S, (0x4aa+2000-0xc70)) 
#define z702a26a5e9                ssGetSFcnParam(S, (0x58f+7790-0x23f2)) 
#define zabe1e0cd2c          ssGetSFcnParam(S, (0x1e84+943-0x2227)) 
#define zb9e2d422d8         ssGetSFcnParam(S, (0x9b5+1094-0xdee)) 
#define z18c20ee744    ssGetSFcnParam(S, (0x1363+3799-0x222c)) 
#define zca9014403a      	ssGetSFcnParam(S, (0xd95+3368-0x1aae)) 
#define zbb2877a20e      	ssGetSFcnParam(S, (0x40f+3842-0x1301)) 
#define zb5b11ca684      	ssGetSFcnParam(S, (0x17af+2672-0x220e)) 
#define z27a4133c60      	ssGetSFcnParam(S, (0xb0f+3813-0x19e2)) 
#define z8829498ef2           ssGetSFcnParam(S, (0x187a+1107-0x1cba)) 
#define zcb272787be        ssGetSFcnParam(S, (0xe2+1968-0x87e)) 
#define zb9f539adad           ssGetSFcnParam(S, (0x2f9+7893-0x21b9)) 
#define z7f2cd70249        ssGetSFcnParam(S, (0x658+7953-0x2553)) 
#define zc1da8054c7			ssGetSFcnParam(S, (0x1682+2877-0x21a8))
#define z13e28da14a		ssGetSFcnParam(S, (0x889+5914-0x1f8b))
#define z6fed26fee7		ssGetSFcnParam(S, (0xdeb+2014-0x15b0))
#define zdf24515981                           ((0x27d+3742-0x1101)) 
#define z26afe87fed 45056
#define zac5e63f41e 			(0xa18+483-0x81c)
#define za6e89591ea 			(0xead+5223-0x1f34)
#define z2e6483d505              ((0xc56+3224-0x18ee))
#define zc5ce4cb81a              ((0xc11+1927-0x1398))
#define z2b17e2ee3b              ((0x451+4413-0x158e))
static char msg[(0x273+6541-0x1b00)];static void mdlInitializeSizes(SimStruct*S){int i,z8ee759dcbc,za7ad313183,z8af8ebd4a3;ssSetNumSFcnParams(S,zdf24515981);if(ssGetNumSFcnParams(S)!=ssGetSFcnParamsCount(S)){sprintf(msg,"\x57\x72\x6f\x6e\x67\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x69\x6e\x70\x75\x74\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x70\x61\x73\x73\x65\x64\x2e" "\n" "\x25\x64\x20\x61\x72\x67\x75\x6d\x65\x6e\x74\x73\x20\x61\x72\x65\x20\x65\x78\x70\x65\x63\x74\x65\x64" "\n",zdf24515981);ssSetErrorStatus(S,msg);return;}ssSetNumContStates(S,(0xfaf+4545-0x2170));ssSetNumDiscStates(S,(0x591+6187-0x1dbc));ssSetNumSampleTimes(S,(0xe19+520-0x1020));ssSetNumModes(S,(0xd50+4944-0x20a0));ssSetNumNonsampledZCs(S,(0xc15+1408-0x1195));for(i=(0x10c8+5288-0x2570);i<zdf24515981;i++){ssSetSFcnParamTunable(S,i,(0xb28+690-0xdda));}z8ee759dcbc=(int)mxGetN(za9d8fb6bcf);if(mxGetPr(z3a4baa9b4c)[(0x112b+4494-0x22b9)]){za7ad313183=(0x4b8+411-0x650)*z8ee759dcbc;ssSetNumInputPorts(S,za7ad313183);if(mxGetPr(zed102d70b2)[(0xa62+2255-0x1331)]){z8af8ebd4a3=(0x1d13+33-0x1d31)*z8ee759dcbc+(0xdf3+5586-0x23c4);}else{z8af8ebd4a3=z8ee759dcbc+(0x2344+129-0x23c4);}}else{za7ad313183=(0x1c8+5910-0x18dc)*z8ee759dcbc;ssSetNumInputPorts(S,za7ad313183);if(mxGetPr(zed102d70b2)[(0xc7+5464-0x161f)]){z8af8ebd4a3=(0x12a7+4960-0x2605)*z8ee759dcbc+(0x1cfd+2082-0x251e);}else{z8af8ebd4a3=(0x58+4256-0x10f8);}}for(i=(0x20a+2361-0xb43);i<za7ad313183;i++){ssSetInputPortWidth(S,i,(0x13fb+2592-0x1e1a));ssSetInputPortDirectFeedThrough(S,i,(0xc05+6536-0x258c));ssSetInputPortRequiredContiguous(S,i,(0xc8b+4518-0x1e30));if(i<z8ee759dcbc*(0xa39+3432-0x179f))ssSetInputPortDataType(S,i,SS_DOUBLE);else ssSetInputPortDataType(S,i,SS_BOOLEAN);}ssSetNumOutputPorts(S,z8af8ebd4a3);if(z8af8ebd4a3!=(0x180+8225-0x21a1)){for(i=(0x18a0+3632-0x26d0);i<z8af8ebd4a3;i++){ssSetOutputPortWidth(S,i,(0x1e4+2229-0xa98));if(mxGetPr(zed102d70b2)[(0x1778+3672-0x25d0)]){if(i<z8ee759dcbc*(0x88b+2744-0x1341))ssSetOutputPortDataType(S,i,SS_DOUBLE);else if(i>=z8ee759dcbc*(0x202a+1686-0x26be))ssSetOutputPortDataType(S,i,SS_BOOLEAN);else{sprintf(msg,"\x20\x50\x72\x6f\x62\x6c\x65\x6d\x20\x73\x65\x74\x74\x69\x6e\x67\x20\x74\x68\x65\x20\x6f\x75\x74\x70\x75\x74\x20\x70\x6f\x72\x74\x20\x25\x64" "\n",i);ssSetErrorStatus(S,msg);return;}}else{ssSetOutputPortDataType(S,i,SS_BOOLEAN);}}}else{ssSetNumOutputPorts(S,(0x180+5329-0x1651));}ssSetNumRWork(S,zc5ce4cb81a);ssSetNumIWork(S,z2e6483d505);ssSetNumPWork(S,z2b17e2ee3b);ssSetOptions(S,SS_OPTION_EXCEPTION_FREE_CODE);}static void mdlInitializeSampleTimes(SimStruct*S){if(mxGetPr(zabe1e0cd2c)[(0x99c+744-0xc84)]==-1.0){ssSetSampleTime(S,(0x1667+748-0x1953),INHERITED_SAMPLE_TIME);ssSetOffsetTime(S,(0xe4+5994-0x184e),FIXED_IN_MINOR_STEP_OFFSET);}else{ssSetSampleTime(S,(0x1829+2667-0x2294),mxGetPr(zabe1e0cd2c)[(0x213+1701-0x8b8)]);ssSetOffsetTime(S,(0x1138+1278-0x1636),0.0);}}
#ifndef MATLAB_MEX_FILE
static void ze22e9f4005(SimStruct*S,double*Voltage){double min,max;if(!S||!Voltage)return;if(*Voltage==(0x1204+2713-0x1c9d))return;min=(double)mxGetPr(zca9014403a)[(0x1890+3284-0x2564)];max=(double)mxGetPr(zbb2877a20e)[(0x1289+176-0x1339)];if(*Voltage>max)*Voltage=max;else if(*Voltage<min)*Voltage=min;}static void z4726e9e707(SimStruct*S,int zb9e97bf36a,int ch,double value){double z67172ebe1a=value;int z0fcae3df66=(0x27f+2868-0xdb3);ze22e9f4005(S,&z67172ebe1a);if(z67172ebe1a!=value)SG_PRINTF(TRACE,"\x63\x68\x20\x25\x69\x20\x73\x65\x74\x20\x56\x20\x74\x6f\x20\x25\x2e\x32\x66\x20\x28\x6c\x69\x6d\x69\x74\x65\x64\x20\x66\x72\x6f\x6d\x20\x25\x2e\x32\x66\x29\x20" "\n",ch,value,z67172ebe1a);else SG_PRINTF(TRACE,"\x63\x68\x20\x25\x69\x20\x73\x65\x74\x20\x56\x20\x74\x6f\x20\x25\x2e\x32\x66\x20" "\n",ch,value);
#ifndef zed77f4a138
z0fcae3df66=PIL_BattSetVoltage(zb9e97bf36a,ch,z67172ebe1a);
#endif
if(z0fcae3df66){z5142a89028(z0fcae3df66);sprintf(msg,"\x50\x49\x4c\x5f\x42\x61\x74\x74\x53\x65\x74\x56\x6f\x6c\x74\x61\x67\x65\x20\x72\x65\x74\x75\x72\x6e\x73\x20\x65\x72\x72\x6f\x72\x3a\x20\x25\x73" "\n",z423e891770);SG_PRINTF(WARNING,msg);}}static void z37e5978b37(SimStruct*S,int zb9e97bf36a,int ch,double*z905011c47a,int z085a926a2c){
#ifndef zed77f4a138
int z0fcae3df66;if(z085a926a2c==zc18e948446){z0fcae3df66=PIL_GetAttribute(zb9e97bf36a,ch,true,ATTR_VOLTAGE_V,z905011c47a);}else{z0fcae3df66=PIL_BattGetVoltage(zb9e97bf36a,ch,z905011c47a);}if(z0fcae3df66){z5142a89028(z0fcae3df66);SG_PRINTF(WARNING,"\x50\x49\x4c\x5f\x42\x61\x74\x74\x47\x65\x74\x56\x6f\x6c\x74\x61\x67\x65\x20\x72\x65\x74\x75\x72\x6e\x73\x3a\x20\x25\x73" "\n",z423e891770);}else{SG_PRINTF(TRACE,"\x63\x68\x20\x25\x69\x20\x56\x20\x3d\x20\x25\x2e\x32\x66\x20" "\n",ch,*z905011c47a);}
#endif 
}static void zcc954aa1bc(SimStruct*S,double*Current){double min,max;if(!S||!Current)return;if(*Current==(0x1260+2368-0x1ba0))return;min=(double)mxGetPr(zb5b11ca684)[(0x924+2628-0x1368)];max=(double)mxGetPr(z27a4133c60)[(0x7d7+6678-0x21ed)];if(*Current>max)*Current=max;else if(*Current<min)*Current=min;}static void za4214fe6a1(SimStruct*S,int zb9e97bf36a,int ch,double value){double zb514e5a168=value;int z0fcae3df66=(0x1809+2789-0x22ee);zcc954aa1bc(S,&zb514e5a168);if(zb514e5a168!=value)SG_PRINTF(TRACE,"\x63\x68\x20\x25\x69\x20\x73\x65\x74\x20\x49\x20\x74\x6f\x20\x25\x2e\x34\x66\x20\x28\x6c\x69\x6d\x69\x74\x65\x64\x20\x66\x72\x6f\x6d\x20\x25\x2e\x32\x66\x29\x20" "\n",ch,value,zb514e5a168);else SG_PRINTF(TRACE,"\x63\x68\x20\x25\x69\x20\x73\x65\x74\x20\x49\x20\x74\x6f\x20\x25\x2e\x34\x66\x20" "\n",ch,value);
#ifndef zed77f4a138
z0fcae3df66=PIL_BattSetCurrent(zb9e97bf36a,ch,zb514e5a168/(0x166d+1896-0x19ed));
#endif
if(z0fcae3df66){z5142a89028(z0fcae3df66);sprintf(msg,"\x50\x49\x4c\x5f\x42\x61\x74\x74\x53\x65\x74\x43\x75\x72\x72\x65\x6e\x74\x20\x72\x65\x74\x75\x72\x6e\x73\x20\x65\x72\x72\x6f\x72\x3a\x20\x25\x73" "\n",z423e891770);SG_PRINTF(WARNING,msg);}}static void z719087e5a9(SimStruct*S,int zb9e97bf36a,int ch,double*z2e51128cc3,int z085a926a2c){
#ifndef zed77f4a138
int z0fcae3df66;if(z085a926a2c==zc18e948446){z0fcae3df66=PIL_GetAttribute(zb9e97bf36a,ch,true,ATTR_CURRENT_MA,z2e51128cc3);}else{z0fcae3df66=PIL_BattGetCurrent(zb9e97bf36a,ch,z2e51128cc3);*z2e51128cc3*=(0x1312+2263-0x1801);}if(z0fcae3df66){z5142a89028(z0fcae3df66);SG_PRINTF(WARNING,"\x50\x49\x4c\x5f\x42\x61\x74\x74\x47\x65\x74\x43\x75\x72\x72\x65\x6e\x74\x20\x72\x65\x74\x75\x72\x6e\x73\x3a\x20\x25\x73" "\n",z423e891770);}else{SG_PRINTF(TRACE,"\x63\x68\x20\x25\x69\x20\x49\x20\x3d\x20\x25\x2e\x34\x66\x20" "\n",ch,*z2e51128cc3);}
#endif 
}static void z4bcc9f7c96(SimStruct*S,int zb9e97bf36a,int ch,bool value){int z0fcae3df66=(0x4f7+34-0x519);
#ifndef zed77f4a138
z0fcae3df66=PIL_BattSetEnable(zb9e97bf36a,ch,(uint32_t)value);
#endif
if(z0fcae3df66){
#ifdef SG_DEBUG_PRINT
if(z0fcae3df66==ER_EXECUTION_FAIL){SG_PRINTF(WARNING,"\x50\x49\x4c\x5f\x42\x61\x74\x74\x53\x65\x74\x45\x6e\x61\x62\x6c\x65\x20\x66\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x65\x78\x65\x63\x75\x74\x65\x20\x28\x65\x2e\x67\x2e\x20\x62\x6c\x6f\x63\x6b\x65\x64\x20\x62\x79\x20\x61\x20\x68\x61\x72\x64\x77\x61\x72\x65\x20\x63\x6f\x6e\x64\x69\x74\x69\x6f\x6e\x29" "\n");}else{z5142a89028(z0fcae3df66);sprintf(msg,"\x50\x49\x4c\x5f\x42\x61\x74\x74\x53\x65\x74\x45\x6e\x61\x62\x6c\x65\x20\x72\x65\x74\x75\x72\x6e\x73\x20\x65\x72\x72\x6f\x72\x3a\x20\x25\x73" "\n",z423e891770);SG_PRINTF(WARNING,msg);}
#endif
}}static void z106c4df0f4(int zb9e97bf36a,int ch,bool*z0d26ce449e){uint32_t enable;
#ifndef zed77f4a138
int z0fcae3df66=PIL_BattGetEnable(zb9e97bf36a,ch,&enable);if(z0fcae3df66){z5142a89028(z0fcae3df66);SG_PRINTF(WARNING,"\x50\x49\x4c\x5f\x42\x61\x74\x74\x47\x65\x74\x45\x6e\x61\x62\x6c\x65\x20\x72\x65\x74\x75\x72\x6e\x73\x20\x65\x72\x72\x6f\x72\x3a\x20\x25\x73" "\n",z423e891770);}else{*z0d26ce449e=(bool)enable;SG_PRINTF(TRACE,"\x63\x68\x20\x25\x69\x20\x45\x6e\x61\x62\x6c\x65\x3a\x20\x25\x64\x20" "\n",ch,enable);}
#endif 
}
#endif 
static void sg_ModelLoad(SimStruct*S){
#ifndef MATLAB_MEX_FILE
sg_PCIDevice ze296e0333d;uint32_t bus,slot;sg_mod_info*mod_info;z92aecbf1ff*z86f8673608;uint32_t VendorID=(uint32_t)mxGetPr(z8829498ef2)[(0x42f+1698-0xad1)];uint32_t SubVendorID=(uint32_t)mxGetPr(zcb272787be)[(0x652+4093-0x164f)];uint32_t DeviceID=(uint32_t)mxGetPr(zb9f539adad)[(0x60+2942-0xbde)];uint32_t SubDeviceID=(uint32_t)mxGetPr(z7f2cd70249)[(0xd8+3792-0xfa8)];char DevName[(0x13d+7117-0x1ca6)];uint32_t zb9e97bf36a;int z62b7fa9256=(uint32_t)mxGetPr(z58f464b4bb)[(0x2168+378-0x22e2)];char zd626712b39[(0x921+5743-0x1f2c)];double z37b14784fb=0.0,z412387274b=0.0;bool z33ad61b391=(0x11d0+493-0x13bd);int z78205ce1b7;int z0fcae3df66,channel;int zf91d71c6d9;double*z5c16132023,*z34a85f938e;uint32_t zc8e4e71095;mxGetString(z63fca46654,zd626712b39,mxGetN(z63fca46654)+(0x382+6860-0x1e4d));zf91d71c6d9=(uint32_t)mxGetN(za9d8fb6bcf);zc8e4e71095=z26afe87fed|(((uint32_t)mxGetPr(z13e28da14a)[(0x5c0+4244-0x1654)]-(0x257f+358-0x26e4))<<(0x41c+6692-0x1e37))|(((uint32_t)mxGetPr(z6fed26fee7)[(0x83b+7756-0x2687)]-(0xf33+642-0x11b4))<<(0x4ab+3244-0x1151))|((uint32_t)mxGetPr(zc1da8054c7)[(0xa79+1582-0x10a7)]-(0xaba+1421-0x1046));z5c16132023=calloc(zf91d71c6d9,sizeof(double));z34a85f938e=calloc(zf91d71c6d9,sizeof(double));strcpy(DevName,"\x53\x70\x65\x65\x64\x67\x6f\x61\x74\x20");strcat(DevName,zd626712b39);mod_info=sg_module_get_single(zd10302d34c,z62b7fa9256);if(mod_info==NULL){mod_info=sg_module_register(zd10302d34c,z62b7fa9256);z86f8673608=calloc((0xcb2+3938-0x1c13),sizeof(z92aecbf1ff));z86f8673608->z5c16132023=z5c16132023;z86f8673608->z34a85f938e=z34a85f938e;if(strncmp(zd626712b39,"\x49\x4f\x39\x39\x32",(0xc84+1226-0x1149))==(0x69d+26-0x6b7)){z86f8673608->z59c2dba4da=zc18e948446;}else{z86f8673608->z59c2dba4da=z236b614227;}mod_info->custom_data=(void*)z86f8673608;}else{SG_PRINTF(DEBUG,"\x44\x6f\x20\x6e\x6f\x74\x20\x72\x65\x67\x69\x73\x74\x65\x72\x20\x25\x73\x20\x6d\x6f\x64\x75\x6c\x65" "\n",DevName);return;}
#ifndef z196140dc34
if((int)mxGetPr(z702a26a5e9)[(0x1837+2493-0x21f4)]<(0x168b+1206-0x1b41)){if(sg_detectPciDevice(&ze296e0333d,DevName,VendorID,DeviceID,SubVendorID,SubDeviceID,z62b7fa9256)!=(0x160+2444-0xaec)){ssSetErrorStatus(S,pSgErrorStr);return;}bus=ze296e0333d.bus;slot=ze296e0333d.slot;}else{bus=(uint32_t)mxGetPr(z702a26a5e9)[(0xae4+2039-0x12db)];slot=(uint32_t)mxGetPr(z702a26a5e9)[(0x829+1795-0xf2b)];if(sg_detectPciDeviceAtSlot(&ze296e0333d,DevName,VendorID,DeviceID,SubVendorID,SubDeviceID,bus,slot)!=(0x1e11+596-0x2065)){ssSetErrorStatus(S,pSgErrorStr);return;}}
#else 
bus=(0xc81+879-0xff0);slot=(0x273+6002-0x19e5);
#endif
if(sg_setAbilities()!=(0x1d2f+436-0x1ee3)){ssSetErrorStatus(S,"\x43\x6f\x75\x6c\x64\x20\x6e\x6f\x74\x20\x67\x65\x74\x20\x70\x72\x69\x76\x69\x6c\x65\x67\x65\x73\x2e");return;}
#ifndef zed77f4a138
#ifdef z196140dc34
SG_PRINTF(DEBUG,"\x44\x52\x59\x20\x52\x55\x4e\x20\x28\x64\x65\x62\x75\x67\x20\x6d\x6f\x64\x65\x3a\x20\x72\x75\x6e\x20\x77\x69\x74\x68\x6f\x75\x74\x20\x63\x61\x72\x64\x29" "\n");
#else
z0fcae3df66=PIL_OpenSpecifiedCard(bus,slot,&zb9e97bf36a);if(z0fcae3df66){z5142a89028(z0fcae3df66);sprintf(msg,"\x25\x73\x20\x4f\x70\x65\x6e\x20\x63\x61\x72\x64\x20\x65\x72\x72\x6f\x72\x28\x62\x75\x73\x20\x25\x69\x2c\x20\x73\x6c\x6f\x74\x20\x25\x69\x29\x3a\x20\x25\x73",DevName,bus,slot,z423e891770);ssSetErrorStatus(S,msg);return;}
#endif
#endif
z86f8673608->zb9e97bf36a=zb9e97bf36a;SG_PRINTF(INFO,"\x25\x73\x20\x28\x62\x75\x73\x20\x25\x69\x20\x2f\x20\x73\x6c\x6f\x74\x20\x25\x69\x29\x20\x53\x74\x61\x74\x75\x73\x3a\x20" "\n",DevName,bus,slot);
#ifdef zed77f4a138
z0fcae3df66=(0x1a74+1825-0x2195);SG_PRINTF(DEBUG,"\x4e\x4f\x20\x4c\x49\x42\x20\x43\x41\x4c\x4c\x53\x20\x28\x64\x65\x62\x75\x67\x29" "\n");
#else
z0fcae3df66=PIL_Status(zb9e97bf36a);if(z0fcae3df66==STAT_OK){SG_PRINTF(INFO,"\x4f\x4b" "\n");}else{zec4dfa539e(z0fcae3df66);}
#endif
SG_PRINTF(DEBUG,"\x49\x4f\x39\x78\x78\x20\x4d\x6f\x64\x75\x6c\x65\x49\x44\x3a\x20\x25\x69\x2c\x20\x50\x49\x4c\x5f\x43\x61\x72\x64\x49\x44\x3a\x20\x25\x69" "\n",z62b7fa9256,zb9e97bf36a);SG_PRINTF(DEBUG,"\x53\x65\x74\x74\x69\x6e\x67\x20\x69\x6e\x69\x74\x69\x61\x6c\x20\x76\x61\x6c\x75\x65\x73\x20" "\n");for(z78205ce1b7=(0x1579+405-0x170e);z78205ce1b7<zf91d71c6d9;z78205ce1b7++){channel=(int)mxGetPr(za9d8fb6bcf)[z78205ce1b7];if(strncmp(zd626712b39,"\x49\x4f\x39\x39\x32",(0xc87+5893-0x2387))==(0x918+959-0xcd7)){PIL_SetAttribute(zb9e97bf36a,channel,true,ATTR_MEASURE_CONFIG,&zc8e4e71095);}z37b14784fb=(mxGetN(zf90994d09c)==(0x4d2+3722-0x135b))?mxGetPr(zf90994d09c)[(0x1622+2778-0x20fc)]:mxGetPr(zf90994d09c)[z78205ce1b7];z4726e9e707(S,zb9e97bf36a,channel,z37b14784fb);z412387274b=(mxGetN(z6df5e34903)==(0x3d4+2271-0xcb2))?mxGetPr(z6df5e34903)[(0x1f67+364-0x20d3)]:mxGetPr(z6df5e34903)[z78205ce1b7];za4214fe6a1(S,zb9e97bf36a,channel,z412387274b);z33ad61b391=(bool)((mxGetN(z39987748a1)==(0xec8+4978-0x2239))?mxGetPr(z39987748a1)[(0x8cd+2614-0x1303)]:mxGetPr(z39987748a1)[z78205ce1b7]);z4bcc9f7c96(S,zb9e97bf36a,channel,z33ad61b391);}
#endif
}static void sg_ModelStart(SimStruct*S){}static void sg_ModelStep(SimStruct*S){
#ifndef MATLAB_MEX_FILE
double*z6e7cc23b69,*z235e5703b9;bool*z41efbc85b3,*z2044d56e1a;boolean_T*z21457101df;double*z5c16132023;double*z34a85f938e;uint32_t zb9e97bf36a;int z78205ce1b7;int channel;int zf91d71c6d9;int z85091244c3;z92aecbf1ff*z86f8673608;zf91d71c6d9=(uint32_t)mxGetN(za9d8fb6bcf);z85091244c3=ssGetNumOutputPorts(S);z86f8673608=(z92aecbf1ff*)sg_module_get_custom_data(zd10302d34c,(uint32_t)mxGetPr(z58f464b4bb)[(0xa29+7387-0x2704)]);if(z86f8673608==NULL){ssSetErrorStatus(S,"\x42\x61\x74\x74\x65\x72\x79\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x69\x6e\x20\x4d\x6f\x64\x65\x6c\x53\x74\x65\x70" "\n");return;}zb9e97bf36a=z86f8673608->zb9e97bf36a;z5c16132023=z86f8673608->z5c16132023;z34a85f938e=z86f8673608->z34a85f938e;for(z78205ce1b7=(0x13ab+3820-0x2297);z78205ce1b7<zf91d71c6d9;z78205ce1b7++){channel=(int)mxGetPr(za9d8fb6bcf)[z78205ce1b7];z6e7cc23b69=(double*)ssGetInputPortRealSignal(S,z78205ce1b7*(0xc96+2379-0x15df));if(*z6e7cc23b69!=z5c16132023[z78205ce1b7]){z4726e9e707(S,zb9e97bf36a,channel,z6e7cc23b69[(0xccb+4284-0x1d87)]);z5c16132023[z78205ce1b7]=*z6e7cc23b69;}if(mxGetPr(zed102d70b2)[(0x827+6015-0x1fa6)]){z235e5703b9=ssGetOutputPortSignal(S,z78205ce1b7*(0xad1+4244-0x1b63));z37e5978b37(S,zb9e97bf36a,channel,z235e5703b9,z86f8673608->z59c2dba4da);}z6e7cc23b69=(double*)ssGetInputPortRealSignal(S,z78205ce1b7*(0x54a+6182-0x1d6e)+(0xbdf+2406-0x1544));if(*z6e7cc23b69!=z34a85f938e[z78205ce1b7]){za4214fe6a1(S,zb9e97bf36a,channel,z6e7cc23b69[(0x12d0+5104-0x26c0)]);z34a85f938e[z78205ce1b7]=*z6e7cc23b69;}if(mxGetPr(zed102d70b2)[(0x9ad+835-0xcf0)]){z235e5703b9=ssGetOutputPortSignal(S,z78205ce1b7*(0x748+6557-0x20e3)+(0x11e7+4242-0x2278));z719087e5a9(S,zb9e97bf36a,channel,z235e5703b9,z86f8673608->z59c2dba4da);}if(mxGetPr(z3a4baa9b4c)[(0x571+5025-0x1912)]){z41efbc85b3=(bool*)ssGetInputPortRealSignal(S,z78205ce1b7+zf91d71c6d9*(0xe35+3042-0x1a15));z4bcc9f7c96(S,zb9e97bf36a,channel,z41efbc85b3[(0x107d+1226-0x1547)]);}if(mxGetPr(z3a4baa9b4c)[(0xe45+4548-0x2009)]){int zaaf66dafad;if(mxGetPr(zed102d70b2)[(0x122b+2827-0x1d36)]){zaaf66dafad=z78205ce1b7+zf91d71c6d9*(0x156b+1513-0x1b52);}else{zaaf66dafad=z78205ce1b7;}z2044d56e1a=(bool*)ssGetOutputPortSignal(S,zaaf66dafad);z106c4df0f4(zb9e97bf36a,channel,z2044d56e1a);}}if(mxGetPr(zed102d70b2)[(0x1570+939-0x191b)]||mxGetPr(z3a4baa9b4c)[(0x629+48-0x659)]){z21457101df=(boolean_T*)ssGetOutputPortSignal(S,z85091244c3-(0x6b5+1609-0xcfd));PIL_BattReadInterlockState(zb9e97bf36a,BATT_ALL_BATT_SUB_UNITS,z21457101df);}
#endif
}static void sg_ModelStop(SimStruct*S){
#ifndef MATLAB_MEX_FILE
double z37b14784fb=0.0,z412387274b=0.0;bool z33ad61b391;uint32_t zb9e97bf36a;int z78205ce1b7;int channel;int zf91d71c6d9;z92aecbf1ff*z86f8673608;bool zbddf65b359,z54cacb0832,z76aa4a8066;zf91d71c6d9=(uint32_t)mxGetN(za9d8fb6bcf);z86f8673608=(z92aecbf1ff*)sg_module_get_custom_data(zd10302d34c,(uint32_t)mxGetPr(z58f464b4bb)[(0x2f+5708-0x167b)]);if(z86f8673608==NULL){ssSetErrorStatus(S,"\x42\x61\x74\x74\x65\x72\x79\x3a\x20\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x72\x65\x74\x72\x69\x65\x76\x65\x20\x6d\x6f\x64\x75\x6c\x65\x20\x66\x72\x6f\x6d\x20\x72\x65\x67\x69\x73\x74\x72\x79\x20\x69\x6e\x20\x4d\x6f\x64\x65\x6c\x53\x74\x65\x70" "\n");return;}zb9e97bf36a=z86f8673608->zb9e97bf36a;for(z78205ce1b7=(0x81b+3846-0x1721);z78205ce1b7<zf91d71c6d9;z78205ce1b7++){channel=(int)mxGetPr(za9d8fb6bcf)[z78205ce1b7];z76aa4a8066=(bool)((mxGetN(z4ea1453708)==(0xac5+5515-0x204f))?mxGetPr(z4ea1453708)[(0x25+9861-0x26aa)]:mxGetPr(z4ea1453708)[z78205ce1b7]);if(z76aa4a8066){z33ad61b391=(bool)((mxGetN(z39987748a1)==(0x195b+834-0x1c9c))?mxGetPr(z39987748a1)[(0x54c+3955-0x14bf)]:mxGetPr(z39987748a1)[z78205ce1b7]);z4bcc9f7c96(S,zb9e97bf36a,channel,z33ad61b391);}zbddf65b359=(bool)((mxGetN(zcad462ae84)==(0x813+7629-0x25df))?mxGetPr(zcad462ae84)[(0x968+3174-0x15ce)]:mxGetPr(zcad462ae84)[z78205ce1b7]);if(zbddf65b359){z37b14784fb=(mxGetN(zf90994d09c)==(0xaf8+6109-0x22d4))?mxGetPr(zf90994d09c)[(0x945+6729-0x238e)]:mxGetPr(zf90994d09c)[z78205ce1b7];z4726e9e707(S,zb9e97bf36a,channel,z37b14784fb);}z54cacb0832=(bool)((mxGetN(ze5a3733a3e)==(0xd+2846-0xb2a))?mxGetPr(ze5a3733a3e)[(0x711+6588-0x20cd)]:mxGetPr(ze5a3733a3e)[z78205ce1b7]);if(z54cacb0832){z412387274b=(mxGetN(z6df5e34903)==(0x1354+2039-0x1b4a))?mxGetPr(z6df5e34903)[(0x20a8+1458-0x265a)]:mxGetPr(z6df5e34903)[z78205ce1b7];za4214fe6a1(S,zb9e97bf36a,channel,z412387274b);}}
#endif
}static void sg_ModelExit(SimStruct*S){
#ifndef MATLAB_MEX_FILE
z92aecbf1ff*z86f8673608;uint32_t moduleId=(uint32_t)mxGetPr(z58f464b4bb)[(0x39d+7763-0x21f0)];uint32_t z0fcae3df66;z86f8673608=(z92aecbf1ff*)sg_module_get_custom_data(zd10302d34c,moduleId);if(z86f8673608!=NULL){z0fcae3df66=PIL_CloseSpecifiedCard(z86f8673608->zb9e97bf36a);if(z0fcae3df66){z5142a89028(z0fcae3df66);sprintf(msg,"\x46\x61\x69\x6c\x65\x64\x20\x74\x6f\x20\x63\x6c\x6f\x73\x65\x20\x63\x61\x72\x64\x20\x25\x69\x3a\x20\x25\x73",z86f8673608->zb9e97bf36a,z423e891770);SG_PRINTF(WARNING,"\x25\x73" "\n",msg);}free(z86f8673608->z5c16132023);free(z86f8673608->z34a85f938e);free(z86f8673608);sg_module_unregister(zd10302d34c,moduleId);SG_PRINTF(DEBUG,"\x42\x61\x74\x74\x65\x72\x79\x3a\x20\x55\x6e\x72\x65\x67\x69\x73\x74\x65\x72\x20\x6d\x6f\x64\x75\x6c\x65" "\n");}
#endif
}
#include "sg_sfcn_glue.h"   

