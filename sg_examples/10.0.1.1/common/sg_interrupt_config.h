
#ifndef SG_INTERRUPT_CONFIG_H_
#define SG_INTERRUPT_CONFIG_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "sg_blocks/common/libsg/sg_common.h"
#include "sg_blocks/common/libsg/sg_target.h"
#include "sg_blocks/common/libsg/sg_printf.h"

// ================================================================================================
// The macro magic
// The ## operator concatenates two macro arguments, but it needs to be double nested
// SG_INT_PREFIX is defined in the hook file itself, let's say to "IO130"
// The macro SG_INT_MAP_FUNC_NAME   will make "IO130_map"        out of it
// The macro SG_INT_MAP_FUNC_NAME_P will make "IO130_map_public" out of it
// ================================================================================================

// The public guys are the ones with a global scope. Those are the function names that will be
// called by the SLRT generated code
#define SG_MAKE_INT_FUNC_NAME_P(type, modName)  modName ## _ ## type ## _public
#define SG_INT_FUNC_NAME_P(type, modName)       SG_MAKE_INT_FUNC_NAME_P(type, modName)
#define SG_INT_START_FUNC_NAME_P                SG_INT_FUNC_NAME_P(start, SG_INT_PREFIX)
#define SG_INT_STOP_FUNC_NAME_P                 SG_INT_FUNC_NAME_P(stop, SG_INT_PREFIX)
#define SG_INT_ISR_FUNC_NAME_P                  SG_INT_FUNC_NAME_P(isr, SG_INT_PREFIX)
#define SG_INT_WAIT_FUNC_NAME_P                 SG_INT_FUNC_NAME_P(isr, SG_INT_PREFIX) //It's still called isr to maintain compatibility with QNX
#define SG_INT_MAP_FUNC_NAME_P                  SG_INT_FUNC_NAME_P(map, SG_INT_PREFIX)

// The non-public (aka private) guys are the one called BY the public functions
// They are declared static in the hookfile itself -> not visible on a global scope
#define SG_MAKE_INT_FUNC_NAME(type, modName)    modName ## _ ## type
#define SG_INT_FUNC_NAME(type, modName)         SG_MAKE_INT_FUNC_NAME(type, modName)
#define SG_INT_START_FUNC_NAME                  SG_INT_FUNC_NAME(start, SG_INT_PREFIX)
#define SG_INT_STOP_FUNC_NAME                   SG_INT_FUNC_NAME(stop, SG_INT_PREFIX)
#define SG_INT_ISR_FUNC_NAME                    SG_INT_FUNC_NAME(isr, SG_INT_PREFIX)
#define SG_INT_MAP_FUNC_NAME                    SG_INT_FUNC_NAME(map, SG_INT_PREFIX)

// The ID-guys are used to assemble the name of the defines that are passed at code generation
// and are used to define the hardware IDs for sg_findPciDevice
#define SG_MAKE_ID_TYPE(type, modName)  SG_INT_ ## modName ## _ ## type
#define SG_ID_TYPE(type, modName)       SG_MAKE_ID_TYPE(type, modName)
#define SG_GET_VID                      SG_ID_TYPE(VID, SG_INT_PREFIX)
#define SG_GET_DID                      SG_ID_TYPE(DID, SG_INT_PREFIX)
#define SG_GET_SUBVID                   SG_ID_TYPE(SUBVID, SG_INT_PREFIX)
#define SG_GET_SUBDID                   SG_ID_TYPE(SUBDID, SG_INT_PREFIX)

// And that guy is used for the device name in sg_findPciDevice
#define STR_VALUE_ADD_SPEEDGOAT(arg)    "Speedgoat " arg
#define SG_MAKE_DEVNAME_TYPE(modName)   STR_VALUE_ADD_SPEEDGOAT(SG_INT_ ## modName ## _DEVNAME)
#define SG_DEVNAME_TYPE(modName)        SG_MAKE_DEVNAME_TYPE(modName)
#define SG_GET_DEVNAME                  SG_DEVNAME_TYPE(SG_INT_PREFIX)

// End of macro magic
// ================================================================================================

// The following 3 macros will be used in the hook files themselves to declare the hook functions
#define SG_INT_START_FUNC   static void SG_INT_START_FUNC_NAME(void* pciinfo)
#define SG_INT_STOP_FUNC    static void SG_INT_STOP_FUNC_NAME(void* pciinfo)
#define SG_INT_ISR_FUNC     static int SG_INT_ISR_FUNC_NAME(void* pciinfo)

//Return defines for isr function
#define SG_DROP_ISR 0
#define SG_RUN_ISR 1
#define SG_OVERLOAD_ISR 2

//The following macros are used for mapping the bars
#define SG_INT_NUM_BARS             (sizeof(SG_INT_BARS) / sizeof(SG_INT_BARS[0]))
#define SG_INT_MAPPED_BAR(barNr)    (((sg_PCIDevice*)pciinfo)->VirtAddress[barNr])

// Use this macro if you need the pciinfo in your subroutine, to avoid obfuscation problems
#define SG_INT_GET_PCIINFO (sg_PCIDevice*)pciinfo

// Use this macro to check if the interrupt is used in polling mode
#ifdef __linux__
#define SG_INT_IS_POLLING (((sg_InterruptContext*)pciinfo)->is_polling)
#define SG_INT_OVERLOAD_CHECK       (((sg_InterruptContext*)pciinfo)->overloadCheckEnabled)
#define SG_INT_OVERLOAD_CHECK_CLEAR (((sg_InterruptContext*)pciinfo)->overloadCheckEnabled = false)
#define SG_INT_OVERLOAD_CHECK_SET   (((sg_InterruptContext*)pciinfo)->overloadCheckEnabled = true)
#else
#define SG_INT_IS_POLLING 0
#define SG_INT_OVERLOAD_CHECK 0
#endif

// Use this macro to access the interrupt channel in your hook function
#define SG_INT_INTERRUPT_CHANNEL (((sg_InterruptContext*)pciinfo)->interruptChannel)

// Use this macro to access the module ID in your hook function
#define SG_INT_MODULE_ID (((sg_InterruptContext*)pciinfo)->moduleId)

// Use this macro to store/retrieve custom data in your hook function
// (Just a pointer, you need to malloc the memory yourself)
#define SG_INT_CUSTOM_DATA (((sg_InterruptContext*)pciinfo)->customData)

//In order to implement the PCI device search in a custom function, proceed as follows:
// -> Before the inclusion of this header file, prototype your function and set a define
/*
       static int findIo130Device(sg_PCIDevice *pciinfo, uint32_t moduleId, int bus, int slot);
       #define SG_INT_CUSTOM_FIND_PCI_FUNCTION findIo130Device
*/
// -> After the inclusion of this header file, place the function. It could look like this:
/*
        static int findIo130Device(sg_PCIDevice *pciinfo, uint32_t moduleId, int bus, int slot)
        {
            if (sg_findPciDevice(pciinfo, SG_GET_DEVNAME, SG_GET_VID, SG_GET_DID, SG_GET_SUBVID,
                    SG_GET_SUBDID, moduleId, bus, slot) != 0)
            {
               PRINTF(ERROR, "%s\n", pSgErrorStr);
                return -1;
            }
            return 0;
        }
*/

// Declare interrupt hook functions
SG_INT_START_FUNC;
SG_INT_STOP_FUNC;
SG_INT_ISR_FUNC;

#ifdef __QNX__ // -> QNX

#include "sg_interrupt_config_qnx.h"

#elif defined(__linux__) // -> Linux
    #ifdef SG_LEGACY_LINUX_ENABLE
        #include "sg_interrupt_config_linux_legacy.h"
    #else
        #include "sg_interrupt_config_linux.h"
    #endif // __SG_LEGACY_LINUX_ENABLE__
    #define SG_INT_ENABLE_INTERRUPT_FIX(target_register, int_mask, fix_type) \
        _sg_int_enable_fix(((sg_InterruptContext*)pciinfo), target_register, int_mask, fix_type)
#endif // __QNX__//__linux__

// Always include this, but only active in Linux.
#include "sg_interrupt_fixes.h"

#ifdef __cplusplus
}
#endif

#endif // SG_INTERRUPT_CONFIG_H_
