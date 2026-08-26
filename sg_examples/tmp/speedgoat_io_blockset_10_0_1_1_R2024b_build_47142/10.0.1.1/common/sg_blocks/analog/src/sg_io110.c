// Copyright 2006-2026 Speedgoat GmbH

#include "sg_io110.h"
#include <stdlib.h>
#include "sg_common.h"
#include "sg_printf.h"
static void zd8daa90d05(real_T*val,int z6c5ef6aa7d);uint16_T z6f16ec95a7(uint16_T x){if(x%(0x132+182-0x1e6)==(0xe30+5287-0x22d7))return x+(0x18c2+1207-0x1d78);else return x-(0x1b26+1725-0x21e2);}void zdf15c763dd(int range,real_T z0754dd67cc,real_T offset,real_T*val){real_T out=*val;if(range<(0x79+218-0x150)){out=out*(1.0-z0754dd67cc/262144.0)-offset/4.0;zd8daa90d05(&out,(0x1834+3384-0x256c));}else{out=out*(1.0-z0754dd67cc/131072.0)-offset/4.0;zd8daa90d05(&out,(0x143d+1976-0x1bf4));}*val=out;}static void zd8daa90d05(real_T*val,int z6c5ef6aa7d){real_T out=*val;if(z6c5ef6aa7d==(0xed6+5618-0x24c8)){if(out>65535){out=65535;}if(out<(0x7d4+3713-0x1655)){out=(0x3af+2839-0xec6);}}else{if(out>32767){out=32767;}if(out<-32768){out=-32768;}}*val=out;}
