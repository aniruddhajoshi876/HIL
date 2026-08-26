// Copyright 2006-2026 Speedgoat GmbH

#include "IO601_Port.h"
#include "sg_common.h"
z75eb4775d3::z75eb4775d3(sg_IO601_Module_T*sg_IO601_pModule,unsigned char zb9276e93a2):za80e00a3a2(sg_IO601_pModule),z04ff90940a(zb9276e93a2),z20ee2ecb2d(0.0){z3eb822ce62.clear();}z75eb4775d3::~z75eb4775d3(){}bool z75eb4775d3::z35ed3b04c7(){return!z3eb822ce62.test_and_set(std::memory_order_acquire);}int z75eb4775d3::z6c8415406c(){int z35e3f99684=(0x597+644-0x81b);while(z3eb822ce62.test_and_set(std::memory_order_acquire)){z35e3f99684++;}return z35e3f99684;}void z75eb4775d3::zdb58049eea(){z3eb822ce62.clear();}void z75eb4775d3::z054b93aada(double z4e4bbdd9c7){sg_wait_s(z4e4bbdd9c7/(0xba8+6778-0x223a));}
