#ifndef SG_FPGA_IO3XX_REGS_H
#define SG_FPGA_IO3XX_REGS_H

#include <stdint.h>

// CDMA Acceleration
#define AXI_PCIE_BASE                 0x00530000    // AXI Base Address Translation Configuration Registers

// Vivado AXI BARs
#define AXI_BAR0_START         0x02000000 // AXI BAR 0
#define AXI_BAR0_SIZE          0x01000000 // 16 MB
#define AXI_BAR1_START         0x03000000 // AXI BAR 1
#define AXI_BAR1_SIZE          0x01000000 // 16 MB
#define AXI_BAR2_START         0x10000000 // AXI BAR 2
#define AXI_BAR2_SIZE          0x01000000 // 16 MB
#define AXI_BAR3_START         0x20000000 // AXI BAR 3
#define AXI_BAR3_SIZE          0x01000000 // 16 MB
#define AXI_BAR4_START         0x30000000 // AXI BAR 4
#define AXI_BAR4_SIZE          0x00010000 // 64 kB
#define AXI_BAR5_START         0x40000000 // AXI BAR 5
#define AXI_BAR5_SIZE          0x00010000 // 64 kB

// IMPORTANT: AXI BAR 5 is 16 MB on early IO324 designs. 
// These were generated with the old CI Tool. 
// All CI's generated with the new tool should have AXI BAR 5 set to 64 kB (inherited from the HCIP).

/*****************************************************************************
 * IO36x/Linux AXI BAR
 *****************************************************************************/

#define LOWER32BITS(data_64bit) (data_64bit & 0xFFFFFFFF)
#define UPPER32BITS(data_64bit) (data_64bit >> 32)

#define SGLIB_PCIE_READ_DMA_ADDR_OFFSET (0x70000000)
#define SGLIB_PCIE_EGRESS_APERTURE_OFFSET (0xE8000000)
#define SGLIB_PCIE_INDIVIDUAL_EGRESS_SIZE (0x1000000)
#define SGLIB_PCIE_TOTAL_EGRESS_APERTURE_SIZE (0x1000000*8)

#define SGLIB_PCIE_16M_APPERTURE_SIZE (0x1000000)
#define SGLIB_PCIE_64K_APPERTURE_SIZE (0x0010000)

#define EGRESS_SIZE_BITS_16M (0xC0000)
#define EGRESS_SIZE_BITS_64K (0x40000)

// Define which egress bars are active (bars 0, 1, and 5)
#define EGRESS_BAR_ACTIVE(bar_index) ((bar_index == 0) || (bar_index == 1) || (bar_index == 5))

#define EGRESS_0_START (0x8C00)
#define EGRESS_1_START (0x8C20)
#define EGRESS_2_START (0x8C40)
#define EGRESS_3_START (0x8C60)
#define EGRESS_4_START (0x8C80)
#define EGRESS_5_START (0x8CA0)
#define EGRESS_6_START (0x8CC0)
#define EGRESS_7_START (0x8CE0)

typedef struct egressRegisters
{
    uint32_t caps;
    uint32_t status;
    uint32_t control;
    uint32_t res;
    uint32_t srcLo;
    uint32_t srcHi;
    uint32_t dstLo;
    uint32_t dstHi;
} egressRegisters_t;

#define EGRESS_ENABLE_BIT (0x1)
#define EGRESS_SECURITY_EN (0x4)
#define EGRESS_SIZE_BITS (0xC0000)
#define EGRESS_RW_ATTRIB (0xFF800000)

#endif  // SG_FPGA_IO3XX_REGS_H
