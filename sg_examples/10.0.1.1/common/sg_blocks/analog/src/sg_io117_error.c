// Copyright 2006-2026 Speedgoat GmbH

#include "../include/sg_io117_error.h"
#include <stdarg.h>
#include <stdio.h>
#define z90e0493069    ((0x111f+4265-0x20c8))
#define z7b81afd283   (z90e0493069 + (0x80+396-0x1cc))
static char_T z1907941b3f[z90e0493069];static char_T z04b4c6b902[z7b81afd283];static boolean_T z49348d02b8;static boolean_T ze56ddd1893;void z034b8bb1c5(void){z49348d02b8=false;ze56ddd1893=true;}void z0b799d87d7(const char_T*format,...){va_list args;va_start(args,format);vsprintf(z1907941b3f,format,args);va_end(args);z49348d02b8=true;}void zad7aed3542(const char_T*msg){sprintf(z1907941b3f,"\x25\x73",msg);z49348d02b8=true;}void zfff5bcce1f(void){ze56ddd1893=true;}void z779c62d932(void){ze56ddd1893=false;}const char_T*z620c52af23(const char_T*zd1826cf292,int_T zc3ac25f204){if(!z49348d02b8){z1907941b3f[(0x21f+577-0x460)]='\0';}if(ze56ddd1893){sprintf(z04b4c6b902,"\x49\x6e\x20\x49\x4f\x31\x31\x37\x2c\x20\x25\x73\x20\x62\x6c\x6f\x63\x6b\x2c\x20\x49\x44\x20\x25\x64\x3a\x20\x25\x73",zd1826cf292,zc3ac25f204,z1907941b3f);return z04b4c6b902;}else{return z1907941b3f;}}
