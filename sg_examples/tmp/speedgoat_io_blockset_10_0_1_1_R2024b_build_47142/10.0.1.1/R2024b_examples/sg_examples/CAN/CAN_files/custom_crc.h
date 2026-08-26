#ifndef CUSTOM_CRC_H
#define CUSTOM_CRC_H

#include "stdint.h"

unsigned char reflect(unsigned char data, unsigned char numBits) ;

extern "C" uint64_t ComputeCustomCrc(const uint8_t* byteArray, unsigned int bitLength);

#endif
