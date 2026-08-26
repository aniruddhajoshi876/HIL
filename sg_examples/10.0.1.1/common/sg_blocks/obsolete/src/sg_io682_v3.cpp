#include "sg_io682_v3.h"

#include "../../arinc429/lib/sg_IO682/include/cdev_api.h"
#include "sg_common.h"

#define MIN_BITRATE_ARX				105
#define MAX_BITRATE_ARX				79998

struct Sg_ModuleInfo
{
    const char *name;
    uint16_t vendorId;
    uint16_t deviceId;
    uint16_t subvendorId;
    uint16_t subdeviceId;
};

static int getPciBaseAddresses(Sg_ModuleInfo *moduleInfo, int16_t bus, int16_t slot,
    int moduleId, sg_PCIDevice *pciInfo, char *err);
static int findIo681(sg_PCIDevice *pciInfo, Sg_ModuleInfo *moduleInfo, int moduleId, int16_t pciBus,
    int16_t pciSlot);
static int setPciBaseAddresses(const Sg_ModuleInfo *moduleInfo, int boardId, sg_PCIDevice *pciInfo,
    char *err);

int io682_configPciAddresses(int deviceId,
                             int16_t bus,
							 int16_t slot,
                             int moduleId,
                             int boardId,
                             char *err)
{
    Sg_ModuleInfo moduleInfo;
    moduleInfo.name = "Speedgoat IO682";
    moduleInfo.vendorId = 0x13C6;   // Condor Engineering
    moduleInfo.deviceId = deviceId;
    moduleInfo.subvendorId = SG_NO_SUB;
    moduleInfo.subdeviceId = SG_NO_SUB;

    sg_PCIDevice pciInfo;
    if (getPciBaseAddresses(&moduleInfo, bus, slot, moduleId, &pciInfo, err))
    {
        return -1;
    }
    if (setPciBaseAddresses(&moduleInfo, boardId, &pciInfo, err))
    {
        return -1;
    }
    return 0;
}

int io682_initArincApi(int boardId, char *err)
{
    int result = arx30_loadslv(boardId, 0, 0, 0);
    if (result != ARS_NORMAL)
    {
        sprintf(err, "Failed to initialize API: %s", arx30_get_error(result));
        return -1;
    }
    return 0;
}

int io682_setConcurrencyMode(int boardId, char *err)
{
	//arx30_set_multithread_protect needed? or use arx30_set_device_config(,ARU_MULTITHREAD_PROTECT,) -> set by arx30_set_preload_config
    int result = arx30_set_preload_config(boardId, ARU_CONCURRENCY_MODE, AR_CONC_MULTITHRD);	//AR_CONC_NONE
    if (result != ARS_NORMAL)
    {
        sprintf(err, "Failed to set concurrency mode: %s", arx30_get_error(result));
        return -1;
    }
    return 0;
}

int io682_setTimerRate(int boardId, int timeSource, int timerRate)
{
    // Use IRIG timer input to sync the 1us clock
    if (timeSource == 1)
    {
        arx30_set_config(boardId, ARU_RX_TIMETAG_MODE, AR_TIMETAG_EXT_IRIG_64BIT);
    }
    else // Use the CEI-x20 compatible timer
    {
        arx30_set_timerrate(boardId, timerRate);	//not really supported
    }
    return 0;
}

int io682_startDriver(int boardId, char *err)
{
    // Start the slave processor after all the configuration
    int result = arx30_go(boardId);
    if (result != ARS_NORMAL)
    {
        sprintf(err, "Failed to start I/O module: %s", arx30_get_error(result));
        return -1;
    }
    return 0;
}

static int getPciBaseAddresses(Sg_ModuleInfo *moduleInfo,
                               int16_t bus, int16_t slot,
                               int moduleId,
                               sg_PCIDevice *pciInfo,
                               char *err)
{

    // Get PCI information
    if (sg_findPciDevice(pciInfo, moduleInfo->name, moduleInfo->vendorId, moduleInfo->deviceId,
            moduleInfo->subvendorId, moduleInfo->subdeviceId, moduleId, bus, slot) != 0)
    {
        bool tryVariants = false;
        switch (moduleInfo->deviceId)   // Try the variants for 430 and 830
        {
            case 0x430:  // CEI-430A
                tryVariants = true;
                moduleInfo->deviceId = 0x430A;
                break;
            case 0x830:  // RCEI-830A
                tryVariants = true;
                moduleInfo->deviceId = 0x830A;
                break;
        }
        if (tryVariants)
        {
            if (sg_findPciDevice(pciInfo, moduleInfo->name, moduleInfo->vendorId,
                    moduleInfo->deviceId, moduleInfo->subvendorId, moduleInfo->subdeviceId,
                    moduleId, bus, slot) != 0)
            {
                if (findIo681(pciInfo, moduleInfo, moduleId, bus, slot) != 0)
                {
                    strcpy(err, pSgErrorStr);
                    return -1;
                }
            }
        }
        else
        {
            if (findIo681(pciInfo, moduleInfo, moduleId, bus, slot) != 0)
            {
                strcpy(err, pSgErrorStr);
                return -1;
            }
        }
    }
    return 0;
}

// This function is kind of a hack because the IO682 blocks should work with the IO681, but we don't
// have the time to integrate it nicely (the I/O module is only used by one customer).
static int findIo681(sg_PCIDevice *pciInfo,
                     Sg_ModuleInfo *moduleInfo,
                     int moduleId,
                     int16_t pciBus,
                     int16_t pciSlot)
{
    // If the Simulink block said it is an IO682 (0x830A) but we couldn't find it, then try if it's
    // actually an IO681 (0x0530)
    if (moduleInfo->deviceId == 0x830A)
    {
        moduleInfo->deviceId = 0x0530;
        return sg_findPciDevice(pciInfo, moduleInfo->name, moduleInfo->vendorId,
            moduleInfo->deviceId, moduleInfo->subvendorId, moduleInfo->subdeviceId, moduleId,
            pciBus, pciSlot);
    }
    else
    {
        return -1;
    }
}

static int setPciBaseAddresses(const Sg_ModuleInfo *moduleInfo,
                               int boardId,
                               sg_PCIDevice *pciInfo,
                               char *err)
{
    // Map the PCI memory address regions
    uintptr_t bar0Addr = (uintptr_t)sg_mapMemory(pciInfo, 0);
    uintptr_t bar2Addr = (uintptr_t)sg_mapMemory(pciInfo, 2);

    int result = arx30_set_base_addresses(boardId, bar0Addr, bar2Addr, moduleInfo->vendorId,
        moduleInfo->deviceId);
    if (result == ARS_INVBOARD)
    {
        sprintf(err, "Could not set PCI base addresses: %s", arx30_get_error(result));
        return -1;
    }
    return 0;
}
