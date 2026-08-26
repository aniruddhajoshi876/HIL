
#ifndef SG_INTERRUPT_FIXES_H_
#define SG_INTERRUPT_FIXES_H_

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef SG_INT_ENABLE_INTERRUPT_FIX
    #define SG_INT_ENABLE_INTERRUPT_FIX(target_register, int_mask, fix_type) {}
#endif

/* Implementing special handling in the uio_speedgoat kernel module 
 * (most likely because of non-conformities in the PCIe endpoint)
 * - Implement the special handling in uio_speedgoat.c, assign it a number
 * - Add your fix here, together with the number you assigned in the kernel_module
 * - Call this macro from the start function in your int hook file. Pass it the target register
 *   & the value that should be written to it to re-enable interrupts after clearing the interrupt
 */
#define SG_INT_ENABLE_FPGA_7SERIES_FIX(target_register, int_mask) \
        SG_INT_ENABLE_INTERRUPT_FIX(target_register, int_mask, 1)

#define SG_INT_ENABLE_FPGA_7SERIES_FIX_CI(int_mask) \
        SG_INT_ENABLE_INTERRUPT_FIX(NULL, int_mask, 1)

#define SG_INT_ENABLE_PLX_FIX(target_register, int_mask) \
	SG_INT_ENABLE_INTERRUPT_FIX(target_register, int_mask, 2)

#define SG_INT_ENABLE_FPGA_6SERIES_INTA_FIX() \
        SG_INT_ENABLE_INTERRUPT_FIX(NULL, 0x1, 3)

#define SG_INT_ENABLE_FPGA_6SERIES_SERIAL_FIX() \
        SG_INT_ENABLE_INTERRUPT_FIX(NULL, 0x1, 4)

#define SG_INT_ENABLE_FPGA_6SERIES_INTAV2_FIX() \
        SG_INT_ENABLE_INTERRUPT_FIX(NULL, 0x1, 5)


#ifdef __cplusplus
}
#endif

#endif // SG_INTERRUPT_FIXES_H_
