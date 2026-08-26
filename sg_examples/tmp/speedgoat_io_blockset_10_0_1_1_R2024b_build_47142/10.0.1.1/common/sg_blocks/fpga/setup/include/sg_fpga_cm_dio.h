#ifndef __SG_FPGA_CM_DIO_H__
#define __SG_FPGA_CM_DIO_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stdlib.h>

// Address Structure
typedef struct
{
    uint32_t dir[4];
    uint32_t dio[4];
    uint32_t test1;
    uint32_t test2;
    uint32_t version;
    uint32_t select[4];
    uint32_t dummy;
}DioBlock;

// the extension to 256 channels added a second half of "DioBlock", but only the registers
// dir, dio & select are accessible in the upper half. 
// test1, test2 & version are only available in the lower half.
typedef struct
{
    DioBlock half[2]; 
} dio;

// other defines
#define NBR_DIO_CH_DIV_32   8
#define NBR_DIO_CH_DIV_32_OLD   4


#ifdef __cplusplus
}
#endif

#endif      // END: __SG_FPGA_CM_DIO_H__
