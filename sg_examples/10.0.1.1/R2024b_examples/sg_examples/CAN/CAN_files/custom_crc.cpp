#include "custom_crc.h"

unsigned char reflect(unsigned char data, unsigned char numBits) {
    unsigned char reflection = 0x00;
    for (unsigned char i = 0; i < numBits; i++) {
        if (data & (1 << i)) {
            reflection |= (1 << ((numBits - 1) - i));
        }
    }
    return reflection;
}

uint64_t ComputeCustomCrc(const uint8_t* byteArray, unsigned int bitLength) {
    const uint16_t polynomial = 0x80F; // CRC-12/CCITT polynomial
    uint16_t crc = 0xFFF;              // Initial value (12 bits)
    uint8_t reflectOutput = false;
    uint8_t reflectInput = false;
    
    // Loop through byteArray bytewise
    for (unsigned int i = 0; i < (bitLength/8); ++i) {
        uint8_t byte = byteArray[i];
        if (reflectInput) {
            byte = reflect(byte, 8);
        }
        crc ^= (byte << 4); // Align byte with top 8 bits of 12-bit CRC

        for (int j = 0; j < 8; ++j) {
            if (crc & 0x800) { // Check top bit of 12-bit CRC
                crc = (crc << 1) ^ polynomial;
            } else {
                crc <<= 1;
            }
        }
    }

    if (reflectOutput) {
        crc = reflect(crc, 8);
    }
    crc &= 0xFFF; // Mask to 12 bits
    return crc;
}
