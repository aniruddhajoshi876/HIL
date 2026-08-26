
#ifndef SG_INTERRUPT_CONFIG_QNX_H_
#define SG_INTERRUPT_CONFIG_QNX_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <pci/pci.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/neutrino.h>
#include <sys/procmgr.h>

static int intCount;
static int noIntCount;

// The sg_InterruptContext type "inherits" from the sg_PCIDevice type. This way, pointers to a
// sg_InterruptContext struct are also valid pointers to a sg_PCIDevice struct (need to be casted).
// This behavior is defined in the C standard and works therefore with all compilers.
typedef struct
{
    sg_PCIDevice pciInfo;   // Needs to be first for compatibility with On Time
    uint16_t interruptChannel;
    int moduleId;
    void* customData;
} sg_InterruptContext;

void SG_INT_START_FUNC_NAME_P(void* pciinfo, bool ispolling)
{
    intCount = 0;
    noIntCount = 0;

    SG_PRINTF(DEBUG, "INT START\n");

    SG_INT_START_FUNC_NAME(pciinfo);
}

void SG_INT_STOP_FUNC_NAME_P(void* pciinfo)
{
    SG_INT_STOP_FUNC_NAME(pciinfo);

    SG_PRINTF(DEBUG, "INT STOP\n");
    SG_PRINTF(DEBUG, "\t%d interrupts received from board\n", intCount);
    SG_PRINTF(DEBUG, "\t%d other interrupts received\n", noIntCount);
}

int SG_INT_ISR_FUNC_NAME_P(void* pciinfo)
{
    int result = SG_INT_ISR_FUNC_NAME(pciinfo);
    if (result)
        intCount++;
    else
        noIntCount++;
    return result;
}

int32_t SG_INT_MAP_FUNC_NAME_P(void** contextOut, uint32_t moduleId)
{
    int32_t irqNumber = -1;
    int bus, slot;
    sg_InterruptContext *context = (sg_InterruptContext*)malloc(sizeof(sg_InterruptContext));
    sg_PCIDevice *pciinfo = (sg_PCIDevice*)context;

    SG_PRINTF(DEBUG, "INT MAP\n");

    // Extract all information from module ID parameter
    //  Byte 3: FPGA interrupt channel
    //  Byte 2: PCI Slot
    //  Byte 1: PCI Bus
    //  Byte 0: Actual module ID
    SG_PRINTF(DEBUG, "INT MAP original module ID 0x%08X\n", moduleId);
    context->interruptChannel = (moduleId >> 24) & 0xFF;
    slot = (int)(int8_t)((moduleId >> 16) & 0xFF);
    bus = (int)(int8_t)((moduleId >> 8) & 0xFF);
    moduleId &= 0xFF;
    context->moduleId = moduleId;
    context->customData = NULL;

    // Find PCI device
#ifdef SG_INT_CUSTOM_FIND_PCI_FUNCTION
    //Let the user look for the PCI device themselves
    SG_PRINTF(DEBUG, "Custom find PCI device function: 0x%p\n", SG_INT_CUSTOM_FIND_PCI_FUNCTION);
    int res = SG_INT_CUSTOM_FIND_PCI_FUNCTION(pciinfo, moduleId, bus, slot);
    SG_PRINTF(DEBUG, "Custom find PCI device function - result: %d\n", res);
    if(res)
        return res;
#else
    //Default implementation (used by most)
    if (sg_findPciDevice(pciinfo, SG_GET_DEVNAME, SG_GET_VID, SG_GET_DID, SG_GET_SUBVID,
            SG_GET_SUBDID, moduleId, bus, slot) != 0)
    {
        SG_PRINTF(ERROR, "%s\n", pSgErrorStr);
        return (uint32_t)-1;
    }
#endif //SG_INT_CUSTOM_FIND_PCI_FUNCTION
    SG_PRINTF(DEBUG, "INT MAP found PCI device ID %d on bus %d slot %d\n", moduleId, pciinfo->bus, pciinfo->slot);

    for (int barIdx = 0; barIdx < SG_INT_NUM_BARS; barIdx++)
    {
        if (sg_mapMemory(pciinfo, SG_INT_BARS[barIdx]) == NULL)
        {
            SG_PRINTF(ERROR, "Error: 0x%08X (%s)\n", errno, strerror(errno));
            return (uint32_t)-1;
        }
        SG_PRINTF(DEBUG, "INT MAP mapped bar %d of device -> 0x%p\n", SG_INT_BARS[barIdx], SG_INT_MAPPED_BAR(SG_INT_BARS[barIdx]));
    }

    *contextOut = context;

    irqNumber = sg_getIrqNumber(pciinfo);
    SG_PRINTF(DEBUG, "INT MAP returns irqNumber %d\n", irqNumber);
    return irqNumber;
}

#define SG_INT_ENABLE_INTERRUPT_FIX(target_register, int_mask, fix_type) {}

#ifdef __cplusplus
}
#endif

#endif // SG_INTERRUPT_CONFIG_QNX_H_
