// Copyright 2006-2026 Speedgoat GmbH

#ifndef z447db74446
#define z447db74446
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include "simstruc.h" 
#ifdef 	 MATLAB_MEX_FILE
#include "mex.h"
#endif   
#ifndef  MATLAB_MEX_FILE
extern char z638371e1be[(0xd60+5101-0x204d)];extern bool z0fa109ddc8(uint16_t moduleId,int16_t bus,int16_t slot);
#include "IO619_hd_cch.h"     
#include "IO619_tcn_ap.h" 
#include "IO619_tcn_as.h"
#include "IO619_tcn_cm.h"
#include "IO619_tcn_pd.h"
#include "IO619_tcn_sv_mvb.h"
typedef struct z308711a705{z6849d8e411*z33b9546f94;zc8562b8eb0*zd60275a7b9;}z9f824691e0;typedef struct zc1f9067f35{double zf30711d604;uint8_t z4ce4ba15ee;uint8_t z2d3d50e903;uint8_t*zce0d4d8701;z5f8e4f6ca6*zca25fc3c1c;}zae4a64b0e7;
#endif
#define DEVNAME "Speedgoat IO619"
#define VENDORID 38672
#define DEVICEID 38981
#define z5d3cfc1867 (0x26b4+5221-0x1f1d) 
#define z1fba0d7478 9985
#define SUBVENDORID (0x13b9+7461-0x20de)
#define SUBDEVICEID (0x4a+3503-0xdf8)
#define z5f77085f4d (0x842+3781-0x16f7)
#define z64c765c376 (0x1ba+5976-0x1904)
#define z9fc12f01c6 (0x2142+4524-0x1abf)
#define za9b10107ac     6192
#define z247a93b6f5(msg, z8733c58839) switch(z8733c58839){case (0x9d7+3249-0x1688): strcat(msg,"\x41\x53\x5f\x4f\x4b" "\n"); break; \
                                                      case (0xd0c+2239-0x15ca): strcat(msg,"\x41\x53\x5f\x53\x45\x52\x56\x49\x43\x45\x5f\x4e\x4f\x54\x5f\x53\x55\x50\x50\x4f\x52\x54\x45\x44" "\n"); break; \
                                                      case (0x21d+4863-0x151a): strcat(msg,"\x41\x53\x5f\x45\x52\x52\x4f\x52" "\n"); break; \
                                                      case (0xfb7+1068-0x13e0): strcat(msg,"\x41\x53\x5f\x43\x4f\x4e\x46\x49\x47" "\n"); break; \
                                                      case (0x4ef+1852-0xc27): strcat(msg,"\x41\x53\x5f\x4d\x45\x4d\x4f\x52\x59" "\n"); break; \
                                                      case (0x1d3f+1864-0x2482): strcat(msg,"\x41\x53\x5f\x55\x4e\x4b\x4e\x4f\x57\x4e\x5f\x4c\x49\x4e\x4b" "\n"); break; \
                                                      case (0xa8a+1211-0xf3f): strcat(msg,"\x41\x53\x5f\x52\x41\x4e\x47\x45" "\n"); break; \
                                                      case (0x22+1371-0x576): strcat(msg,"\x41\x53\x5f\x44\x41\x54\x41\x5f\x54\x59\x50\x45" "\n"); break; \
                                                      case (0x19cd+1869-0x2111): strcat(msg,"\x41\x53\x5f\x42\x55\x53\x59" "\n"); break; \
                                                      case (0x1418+2797-0x1efb): strcat(msg,"\x41\x53\x5f\x43\x41\x4c\x4c\x5f\x53\x45\x51\x55\x45\x4e\x43\x45" "\n"); break; \
                                                      case (0x1960+2808-0x2449): strcat(msg,"\x41\x53\x5f\x4d\x41\x58\x5f\x45\x52\x52" "\n"); break; \
                                                      default: strcat(msg,"\x55\x6e\x6b\x6e\x6f\x77\x6e\x20\x45\x72\x72\x6f\x72" "\n"); break;}
#define zddf6cdc801(msg, z0a1737f081) switch(z0a1737f081){case (0x132+6429-0x1a4f): strcat(msg,"\x41\x50\x5f\x4f\x4b" "\n"); break; \
                                                      case (0x15fa+4162-0x263b): strcat(msg,"\x41\x50\x5f\x50\x52\x54\x5f\x50\x41\x53\x53\x49\x56\x45" "\n"); break; \
                                                      case (0x1626+2791-0x210b): strcat(msg,"\x41\x50\x5f\x45\x52\x52\x4f\x52" "\n"); break; \
                                                      case (0xf38+2819-0x1a38): strcat(msg,"\x41\x50\x5f\x43\x4f\x4e\x46\x49\x47" "\n"); break; \
                                                      case (0x1bad+2042-0x23a3): strcat(msg,"\x41\x50\x5f\x4d\x45\x4d\x4f\x52\x59" "\n"); break; \
                                                      case (0x90f+2489-0x12c3): strcat(msg,"\x41\x50\x5f\x55\x4e\x4b\x4e\x4f\x57\x5f\x54\x53" "\n"); break; \
                                                      case (0x1983+184-0x1a35): strcat(msg,"\x41\x50\x5f\x52\x41\x4e\x47\x45" "\n"); break; \
                                                      case (0x177d+535-0x198d): strcat(msg,"\x41\x50\x5f\x44\x41\x54\x41\x5f\x54\x59\x50\x45" "\n"); break; \
                                                      default: strcat(msg,"\x55\x6e\x6b\x6e\x6f\x77\x6e\x20\x45\x72\x72\x6f\x72" "\n"); break;}
#define z829e704616(msg, z50a2c0d1e6) switch(z50a2c0d1e6){case (0x38f+4200-0x13f7): strcat(msg,"\x43\x4d\x5f\x4f\x4b" "\n"); break; \
                                                      case (0x725+7152-0x2314): strcat(msg,"\x43\x4d\x5f\x50\x52\x54\x5f\x50\x41\x53\x53\x49\x56\x45" "\n"); break; \
                                                      case (0x1f23+1691-0x25bc): strcat(msg,"\x43\x4d\x5f\x45\x52\x52\x4f\x52" "\n"); break; \
                                                      case (0xaab+4080-0x1a98): strcat(msg,"\x43\x4d\x5f\x43\x4f\x4e\x46\x49\x47" "\n"); break; \
                                                      case (0x1bb7+2520-0x258b): strcat(msg,"\x43\x4d\x5f\x4d\x45\x4d\x4f\x52\x59" "\n"); break; \
                                                      case (0xb53+5757-0x21cb): strcat(msg,"\x43\x4d\x5f\x55\x4e\x4b\x4e\x4f\x57\x5f\x4c\x49\x4e\x4b" "\n"); break; \
                                                      case (0x477+6918-0x1f77): strcat(msg,"\x43\x4d\x5f\x52\x41\x4e\x47\x45" "\n"); break; \
                                                      case (0x3d6+2148-0xc33): strcat(msg,"\x43\x4d\x5f\x44\x41\x54\x41\x5f\x54\x59\x50\x45" "\n"); break; \
                                                      case (0x1916+1833-0x2037): strcat(msg,"\x43\x4d\x5f\x46\x49\x4c\x45\x5f\x41\x43\x43\x45\x53\x53" "\n"); break; \
                                                      case (0x6fc+7810-0x256f): strcat(msg,"\x43\x4d\x5f\x4d\x41\x58\x5f\x45\x52\x52" "\n"); break; \
                                                      case (0xb47+6632-0x24c1): strcat(msg,"\x57\x72\x6f\x6e\x67\x20\x63\x68\x65\x63\x6b\x73\x75\x6d" "\n"); break; \
                                                      case (0x1501+3889-0x23c3): strcat(msg,"\x46\x69\x6c\x65\x20\x73\x69\x7a\x65\x20\x6d\x69\x73\x73\x6d\x61\x74\x63\x68" "\n"); break; \
                                                      case (0x9c2+6046-0x20f0): strcat(msg,"\x4e\x6f\x20\x65\x6e\x74\x72\x69\x65\x73\x20\x6d\x69\x73\x73\x6d\x61\x74\x63\x68" "\n"); break; \
                                                      case (0x816+7344-0x2455): strcat(msg,"\x54\x4e\x4d\x20\x6b\x65\x79\x20\x65\x72\x72\x6f\x72" "\n"); break; \
                                                      default: strcat(msg,"\x55\x6e\x6b\x6e\x6f\x77\x6e\x20\x45\x72\x72\x6f\x72" "\n"); break;}
#endif

