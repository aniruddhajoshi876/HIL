// Copyright 2006-2026 Speedgoat GmbH

#pragma once
#ifdef _WIN32
#include <ntddk.h>
#include <wdf.h>
#endif
#include "Public/fcBaseTypes.h"
#include "Public/fcBaseTypesPMC.h"
#include "Public/fcBaseTypesCAN.h"
#include "Public/fcBaseTypesFlexRay.h"
#include "Public/fcBaseTypesEth.h"
#include "Public/fcBaseTypesUARTOverCAN.h"
#include "HwCom_Defines.h"
#include "fc_ioctl.h"
#include "fcx_hw_reg.h"
#include "systemromTypes.h"
#ifdef __linux__
#include <semaphore.h>
#include "windef_port.h"
#define z7d92bdf92a pthread_cond_t*
#endif
typedef struct zf1fbbff5f9{PVOID zb87c1e5b5b;za1115a0b47 z9ccff85eff;SIZE_T Length;}zf1fbbff5f9;const size_t zd9fa384b75=(0x40d+544-0x629);const size_t z2a2eaeb2ce=(0xf82+1367-0x14d1);const size_t z60c4931082=(0xc81+585-0xeba);struct z21f812fc1a{z13172f3938 za93d2154d6;z457d9094fc zeb8d827222[z283993117f];zc5a03ba995*zbda9328ccc;zc5a03ba995*z8c7ff25a27;};struct z14be3a88af{unsigned int z9136a692e0[z06df1fc38c];z21f812fc1a info[zcd5f40e172];};struct z1a8c641973{bool za58fa47cf4;bool z06b2efed7e;bool z96862ef23b;bool zf6c3395744;bool z57cdcadc96;bool z8de1b50539;bool z8ad5750972;bool zf1e78ccb11;bool z4ec38786d7;uint32_t z65e8e5eeb6;};typedef struct z67a639b576{z7d92bdf92a z75abca0f95;z7d92bdf92a z9055796436;z7d92bdf92a zdf09f54849;
#ifdef __linux__
sem_t*z3d7fd4a0c7;sem_t*z39ba39646c;sem_t*z54ce4d0efe;
#endif
}z255719730a;typedef struct z0d2b950a9d{ze331249cbf z46a05aaecc;unsigned char z07ef4f598c;}z91256ab21e;typedef struct ze9632ad501{BOOLEAN z8d99ce37c0;BOOLEAN z597d8a73da;BOOLEAN zc6069abd12;BOOLEAN zab2d984b88;BOOLEAN z1ee986d7ca;}ze356239def,*z4bc52f9613;
#ifdef _WIN32
z440064cdc3(ze356239def,z39a8587866)
#endif
typedef struct zd8c37426d2{BOOLEAN z425234f008;
#ifdef _WIN32
z76650a8649 z592e282c17;z76650a8649 zddac2e0362;z76650a8649 z786e302b85;zec7c0d9f88 z84f17c487c;zbc003f5df4 ze4de97a9d3;
#endif
zf1fbbff5f9 z273229c1d4[zd9fa384b75];zadf2d5135d zfc7e8833d8;zc5a03ba995 z4b56cddfde[zfc7e8833d8::z1b75855743][zbbcc2637ab];z14be3a88af z9571667a32;unsigned int z0d134115c9;
#ifdef _WIN32
LONG zfdd1bc92c7;LONG z8fea68eeff;
#endif
PUCHAR z6179506d35[sizeof(z1277422094)+z925fc22c0a];PVOID z4dc00a7a5f[(0x1d2+1728-0x882)];z1a8c641973 z3cfc4dd19c;
#ifdef _WIN32
zd2016eb2be zd0171c3d85;
#endif
ULONG za831cd32f4;
#ifdef _WIN32
z2e9610b357 z37c26d02a5;
#endif
ULONG ze231b7ed3a;z70f71ea521::ze64cf9894f::z39201b6139 zd4aafa35b0;unsigned int z8732a74488;z7d92bdf92a z6d008dcc46;z255719730a z80a5d4ff46[z2a2eaeb2ce];z91256ab21e z626999f539[z60c4931082];z9e902d7800 zfba755797d;BOOLEAN z434af904d9;
#ifdef __linux__
sem_t*z8dbc8fcd76;BYTE*za788b89c8d[zd9fa384b75];unsigned int z10aa93e89b;unsigned int z04d7c12fbc;int f;int z723f486322;z4bc52f9613 z8b68cf2257;uint32_t zcb87cb3c4b;uint32_t vendorId;uint32_t deviceId;int z5837f2f1df;pthread_mutex_t*z84f17c487c;z80f2c590d8 z5c5fc41d81;
#endif
}zde8f10b565,*z30ad037078;
#ifdef _WIN32
z440064cdc3(zde8f10b565,z69e07e3f31);
#endif
typedef struct z85ecae49cc{size_t z7e2eddb86e;size_t za2416fa1cc;size_t za1e6a06219;}z85ecae49cc,*z74a2a2a9cc;
#ifdef _WIN32
z440064cdc3(z85ecae49cc,z3b02f9fe48)
#endif
z50f7eb4283
#ifdef _WIN32
zdcc17a89bf zfc45863b5f;z1a55835b3f z2cf58bbf55;zf83754342f zc96d9bd43e;z9e95af9977 z3f85a652f8;z73f14ce36a z333e785d38;z88bbcfd3f3 za08592e3a8;z8a76e0a62a zfe0fbe5b6b;z0b0652d9b0 zc7495818c5;
#else
z7c2791ac2c z2cf58bbf55(IN z096008ef80 z36a364d87d,IN z5733c31b0e zf578f36c8b=NULL);
#endif
z1a8c641973 z4b554f68a4(zadf2d5135d zfc7e8833d8);void zd86bb4d87e(z30ad037078 z9a0f4c6b1a,ULONG zb554cc3ff8,ULONG z4c302a4ab5,ULONG zb5d49b071c);
#ifdef __linux__
#define zb674d226a6 3221225488
#endif
#ifdef _WIN32
#if defined _WIN64
#define z9dab14899b
#else
#define zfbe727c5d0
#endif
#endif
#ifdef __GNUC__
#if defined(__x86_64__) || defined(__ppc64__)
#define z9dab14899b
#else
#define zfbe727c5d0
#endif
#endif
z92325276bf
