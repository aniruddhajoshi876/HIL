/*
 * HCIP API to the libsg.
 * Provides a versioned wrapper for each libsg function used in the HCIP to ensure
 * compatibility for the different release cycles of the speedgoatlib and HCIPs.
 *
 * The HCIP uses the sg_hdlc_common.h which defines what version will be used.
 */

#ifndef SG_HDLC_API_H
#define SG_HDLC_API_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "sg_common.h"
#include "sg_printf.h"
#include "sg_license.h"

typedef sg_mod_info sg_hdlc_mod_info_v24a;
typedef sg_mod_list sg_hdlc_mod_list_v24a;
typedef sg_PCIDevice sg_hdlc_PCIDevice_v24a;
typedef sg_AxiDevice sg_hdlc_AxiDevice_v25a;
typedef sg_block_info sg_hdlc_block_info_v24a;


/***************************************************************************************
 ** sg_common.h API
 ***************************************************************************************/
uint32_t sg_hdlc_inpDW_v19b(uintptr_t port);
void sg_hdlc_outpDW_v19b(uintptr_t port, uint32_t val);
bool sg_hdlc_isModelInit_v19b();
void *sg_hdlc_allocPhysicalMemory_v19b(size_t size);
void *sg_hdlc_allocPhysicalMemory_v2_v22b(size_t size,uintptr_t *physicalAddress);
void sg_hdlc_freePhysicalMemory_v19b(void *ptr);
int sg_hdlc_setAbilities_v19b(void);
int sg_hdlc_findPciDevice_v19b(sg_PCIDevice *pPciInfo, const char *pDevNameStr, uint16_t vendorId,
                               uint16_t deviceId, uint16_t subVendorId, uint16_t subDeviceId,
                               int ModuleId, int Bus, int Slot);
void sg_hdlc_showPciDevice_v19b(sg_PCIDevice *pdev);
void *sg_hdlc_mapMemory_v19b(sg_PCIDevice *device, uint32_t bar);
uintptr_t sg_hdlc_getPhysicalBufferAddr_v25a(void* virtualAddress);

#ifdef __linux__
int sg_hdlc_findAxiDevice_v25a(sg_hdlc_AxiDevice_v25a *axiDevice, const char *deviceName);
void *sg_hdlc_mapAxiBar_v25a(sg_hdlc_AxiDevice_v25a *axiDevice, int bar);
int sg_hdlc_loadOnChipBitstream_v25a(const char *bitstreamFile);
#endif

void sg_hdlc_wait_s_v19b(double delay_s);
double sg_hdlc_getElapsedTime_v19b();
sg_mod_info *sg_hdlc_module_register_v19b(uint32_t mod_type, uint32_t mod_id);
void sg_hdlc_module_unregister_v19b(uint32_t mod_type, uint32_t mod_id);
int32_t sg_hdlc_module_get_v19b(sg_mod_list *modules, uint32_t mod_type, uint32_t mod_id);

sg_block_info *sg_hdlc_block_register_v24a(sg_mod_info* module, uint32_t block_type, uint32_t block_id);
void sg_hdlc_block_unregister_v24a(sg_mod_info* module, uint32_t block_type, uint32_t block_id);
sg_block_info *sg_hdlc_block_get_v24a(sg_mod_info* module, uint32_t block_type, uint32_t block_id);
sg_mod_info *sg_hdlc_module_get_single_v24a(uint32_t mod_type, uint32_t mod_id);

int sg_hdlc_getModelBaseDir_v21a(char *outPath, uint32_t maxLen);
int sg_hdlc_spawnExecutable_v21b(const char *path, const char *executableName, const char *options);
void sg_hdlc_initModelRun_v21b();
void sg_hdlc_terminateModelRun_v22a();
bool sg_hdlc_isFirstModelLoad_v26a();

//PCI functions used for FPGA's which drop off the bus and reappear
//Used in Linux only
#ifdef __linux__
void sgPCI_backupPCIConfig_v22a(sg_PCIDevice *pciinfo, uint32_t* ConfigSave);
void sgPCI_restorePCIConfig_v22a(sg_PCIDevice *pciinfo, uint32_t* ConfigSave);
void sgPCI_printPCIConfig_v22a(sg_PCIDevice *pciinfo);
#endif

//PCI functions used for devices targeting different drivers.
//Used in Linux only
#ifdef __linux__
int sg_pci_bindDriver_v26a(sg_PCIDevice* device, const char* driverName);
int sg_pci_unbindDriver_v26a(sg_PCIDevice* device);
#endif // __linux__

void sg_hdlc_add_start_callback_v26a(void (callback) (void*), void* argument, int priority);

/***************************************************************************************
 ** sg_target.h API
 ***************************************************************************************/
#ifdef __QNX__
int32_t sg_hdlc_getIrqNumber_v21b(sg_PCIDevice *device);
#endif // __QNX__

/***************************************************************************************
 ** sg_printf.h API
 ***************************************************************************************/
#define SG_HDLC_PRINTF_V19B(SEVERITY, ...) SG_PRINTF(SEVERITY, __VA_ARGS__);

/************************************************************************
 * sg_license.h
 ************************************************************************/
int32_t sg_hdlc_getRunTimeLicense_v25b(char* Key);
int32_t sg_hdlc_getRunTimeLicenseSimulatedCustomerTG_v25b(char* Key, int SerialNumberFake);

#ifdef __cplusplus
}
#endif

#endif // SG_HDLC_API_H
