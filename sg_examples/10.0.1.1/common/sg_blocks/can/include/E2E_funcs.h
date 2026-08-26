// Copyright 2006-2026 Speedgoat GmbH

#ifndef z76630e016b
#define z76630e016b
#include <iostream>
#include <vector>
#include <string>
#include <array>
#ifndef MATLAB_MEX_FILE
#include <dlfcn.h>
#endif
#include "sg_printf.h"
#include "CANFD_Message_Definition.h"
#include "CAN_Message_Definition.h"
#define CAN (0xfa4+5720-0x25fb)
#define CANFD (0x581+7323-0x221a)
#define zaf1a625eb5 (0xbb1+5495-0x2125)
#define z45caccd58a (0x7ca+6729-0x2212)
#define z66414eecdc (0xc46+6264-0x24bc)
#define zc105913554 (0x1ab9+541-0x1cd3)
#define ze1966e3ba2 (0x18ba+1619-0x1f09)
#define z986f7b4d5e (0xd20+6124-0x2507)
#define z1f3552a099 (0xe7d+2929-0x19e8)
#define z4159f2d10f (0xc3a+684-0xedf)
#define z57b5092321 (0x14df+1821-0x1bf4)
#define z34ae2503e2 (0xdb3+3707-0x1b2e)
const uint8_t zaac3790bd9[(0x1993+121-0x19fc)]={(0x1d06+2474-0x26b0),(0x5f7+652-0x882),(0x21d5+575-0x2412),(0x502+6088-0x1cc7),(0x996+2882-0x14d4),(0x220+1214-0x6d9),(0x695+7905-0x2570),(0x1028+5051-0x23dc),(0x1bc3+2040-0x23b3),(0x779+7210-0x2397),(0x276+8242-0x2298),(0xed6+198-0xf88),(0x7a7+4056-0x1767),(0x318+3171-0xf5b),(0x1143+2112-0x1953),(0xb15+664-0xd6d)};typedef uint64_t(*zc8b986da00)(const uint8_t*z1577805315,size_t length);typedef struct zaae1b145f2{double zcb26ed2b98;double z1a3dcafd74;double z21f19b17c2;double z674a7b62b9;double za38b55f0d5;double z9582bd1f9b;double z6650e26b38;double zb8c650ee1f;double z897a60cc29;double z2f4ef4f406;double z4c36db9643;double ts;}zaae1b145f2;typedef struct z7912a85e7c{double zcb26ed2b98;double z1a3dcafd74;double z21f19b17c2;double z674a7b62b9;double za38b55f0d5;double z9582bd1f9b;double z6650e26b38;double zb8c650ee1f;double zb8d31b5726;double z0907738b84;double z19a616bb56;double z2f4ef4f406;double z4c36db9643;double ts;}z7912a85e7c;typedef struct z4b8e8a8e6f{double z5daf37cbb7;double zde29a86f5f;double zf049225d56;double zad17f2661e;double zc7e65eb5c5;double zf088482126;double zdd24f9c078;double zf8de2d161d;double z358e2a8364;double z4c36db9643;double ts;}z4b8e8a8e6f;typedef struct za2d16ddac6{double zf7e6b8c083;double zd5ef391573;double z934371ac7e;double zdd24f9c078;double zf8de2d161d;double z4e3f4edada;double z2bb352f1f9;double zb823ae90ab;double z3da24ba376;double z4c36db9643;double ts;}za2d16ddac6;typedef struct z8257531766{double z9170ef6751;double zdeec2f3e5d;double zf049225d56;double zb0b77d2d35;double zb4dd38f023;double z31e27aa90d;double z0623811d17;double z5d3b41ec94;double z1a3dcafd74;double z21f19b17c2;double z674a7b62b9;double za38b55f0d5;double z9582bd1f9b;double z6650e26b38;double z8b64a47a07;double z45118653f4;double z550100a863;double zad17f2661e;double zc7e65eb5c5;double zf088482126;double zf4bffc1e7f;double z811fe36fa0;double z4c36db9643;double ts;}z8257531766;using namespace std;void zfdf8ec2808(uint8_t z25ebc68ac2[(0x1911+1030-0x1c17)]);void ze11d72d2e7(uint16_t z8f14c9c3dd[(0xdcc+509-0xec9)]);void zce19147c57(uint32_t z43d1aa68e6[(0x224+5391-0x1633)]);void za76c432fe5(uint64_t zb70dc3d5e9[(0xccc+1998-0x139a)]);uint8_t z4d55495826(uint8_t value,int z718c4c15f4);uint16_t z4d55495826(uint16_t value,int z718c4c15f4);uint32_t z4d55495826(uint32_t value,int z718c4c15f4);uint8_t z8c1bfd4aee(const uint8_t*z1577805315,size_t length,const uint8_t z722a0f9d25[(0xa05+2898-0x1457)],uint8_t z0c16e7f0c0,uint8_t ze332e1fa89,bool zd198799de0,bool z97357d7de8);uint16_t ze79dee4a2e(const uint8_t*z1577805315,size_t length,const uint16_t z722a0f9d25[(0x43c+6181-0x1b61)],uint16_t z0c16e7f0c0,uint16_t ze332e1fa89,bool zd198799de0,bool z97357d7de8);uint32_t z8557cb7782(const uint8_t*z1577805315,size_t length,const uint32_t z722a0f9d25[(0xab4+531-0xbc7)],uint32_t z0c16e7f0c0,uint32_t ze332e1fa89,bool zd198799de0,bool z97357d7de8);void z66a90ae83a(uint8_t*destination,const uint8_t*source,uint16_t zddf1ed7ac7,uint16_t z3907447b1f,uint16_t zeaa2022426,bool z5f1115c786);void z6e35ec596f(uint8_t*destination,const uint8_t*source,uint16_t z3907447b1f,uint16_t zeaa2022426);void z678f4c4759(uint8_t*destination,const uint8_t*source,uint16_t zddf1ed7ac7,uint16_t z3907447b1f,uint16_t zeaa2022426);
#endif

