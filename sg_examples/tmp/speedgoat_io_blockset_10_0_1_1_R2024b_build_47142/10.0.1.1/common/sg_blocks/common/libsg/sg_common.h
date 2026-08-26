/**
IMPORTANT!
If you change a function prototype, check if the function is used in the "sg_hdlc_api.h". 
Please align with FPGA development
*/

#ifndef SG_COMMON_H
#define SG_COMMON_H

#ifdef __cplusplus
extern "C"
{
#endif

/////////////////////
// Includes       
/////////////////////
#include <stdio.h>
#include <stdint.h>

// Matlab/Simulink
#ifdef __QNX__
    #include <pci/pci.h> // Used in sg_PCIDevice typedef
#else // Linux
    #include <sys/types.h>
#endif

//Includes for module registy
//This is just back-up for the drivers who still expect these functions in sg_common.h
//If you're using the module registry, please also include these files directly in your drivers
#include "sg_module_types.h"
#include "sg_module_registry.h"

/////////////////////
// Typedefs       
/////////////////////
#ifdef __QNX__
  typedef struct _sg_PCIDevice {
    pci_bdf_t dev;
    pci_devhdl_t hdl;
    uint32_t bus;
    uint32_t slot;
    pci_ba_t BaseAddress_raw[6];
    uint32_t BaseAddress[6];
    uint32_t Length[6];
    uintptr_t VirtAddress[6];
    uint16_t VendorId;
    uint16_t DeviceId;
    uint16_t SubDeviceId;
    uint16_t SubVendorId;
    uint32_t pciIdx;
  } sg_PCIDevice;
#else //Linux
  typedef struct _sg_PCIDevice {
    void* dev;
    void* hdl;
    uint32_t bus;
    uint32_t slot;
    uintptr_t BaseAddress_raw[6];
    uint32_t BaseAddress[6];
    uint32_t Length[6];
    uintptr_t VirtAddress[6];
    uint16_t VendorId;
    uint16_t DeviceId;
    uint16_t SubDeviceId;
    uint16_t SubVendorId;
    uint32_t pciIdx;
  } sg_PCIDevice;
#endif

typedef struct {
    int uioIndex;
    char uioDevPath[256];
} sg_AxiDevice;

/////////////////////
// Function Prototypes       
/////////////////////

//Direct I/O functions
uint8_t sg_inpB(uintptr_t port);
uint16_t sg_inpW(uintptr_t port);
uint32_t sg_inpDW(uintptr_t port);
void sg_outpB(uintptr_t port, uint8_t val);
void sg_outpW(uintptr_t port, uint16_t val);
void sg_outpDW(uintptr_t port, uint32_t val);

//IsModelInit for legacy S-function behavior (before stage 3)
bool sg_isModelInit();

//Physical memory allocation
void* sg_allocPhysicalMemory_cached(size_t size);
void* sg_allocPhysicalMemory_uncached(size_t size);
#if defined(SG_USE_CACHED_DMA_BUFFERS) && !(SG_USE_CACHED_DMA_BUFFERS == 0)
    #define sg_allocPhysicalMemory sg_allocPhysicalMemory_cached
#else
    //By default, we use uncached physical memory yet. This should/will change
    #define sg_allocPhysicalMemory sg_allocPhysicalMemory_uncached
#endif //SG_USE_CACHED_DMA_BUFFERS
void sg_freePhysicalMemory(void* ptr);  

#ifndef __QNX__
// Can be used to get (cacheable) physical memory address from virtual address space
// Unless you are using e.g. a cache coherent DMA engine, this function might not be for you
uintptr_t sg_getPhysicalBufferAddr(void* virtual_address);
#endif

// Defines for sg_findPciDevice
#define SG_NO_BUS_SLOT -1
#define SG_NO_SUB -1

// The following 4 functions are only used intrinsically for sg_isModelInit()
// Don't use them in your drivers ;)
bool sg_tagModelRun();
void sg_checkModelInit();
void sg_clearModelInit();
void sg_setModelInit();

// On QNX: By default, cached physical memory
void* sg_allocPhysicalMemory_v2(size_t size, uintptr_t* physicalOut);
#ifdef __linux__
void *sg_allocPhysicalMemory_v2_cached(size_t size, uintptr_t *physicalOut);
void *sg_allocPhysicalMemory_v2_uncached(size_t size, uintptr_t *physicalOut);
#endif

//Find a device on the PCI bus
int sg_findPciDevice(sg_PCIDevice* pPciInfo, const char* pDevNameStr,
    uint16_t vendorId,    uint16_t deviceId,
    uint16_t subVendorId, uint16_t subDeviceId,
    int ModuleId, int Bus, int Slot);
int sg_findPciDeviceMultiIDs(sg_PCIDevice* pPciInfo, const char* pDevNameStr, size_t nDevs,
    uint16_t* pVendorId,    uint16_t* pDeviceId,
    uint16_t* pSubVendorId, uint16_t* pSubDeviceId,
    int PciAutosearchPos, int Bus, int Slot);    
int sg_detectPciDevice(sg_PCIDevice* pPciInfo, const char* pDevNameStr,
    uint16_t vendorId,    uint16_t deviceId,
    uint16_t subVendorId, uint16_t subDeviceId,
    int ModuleId);
int sg_detectPciDeviceAtSlot(sg_PCIDevice* pPciInfo, const char* pDevNameStr,
    uint16_t vendorId,    uint16_t deviceId,
    uint16_t subVendorId, uint16_t subDeviceId,
    int Bus, int Slot);
void sg_showPciDevice(sg_PCIDevice *pdev);

// Writes to PCI config space.
#ifdef __QNX__
int sg_disablePciDeviceInterrupt(sg_PCIDevice* pPciInfo);
int sg_readPciDeviceConfigCmd(sg_PCIDevice* pPciInfo, uint16_t* value);
int sg_writePciDeviceConfigCmd(sg_PCIDevice* pPciInfo, uint16_t value);
int sg_writePciDeviceConfigWord(sg_PCIDevice* pPciInfo, uint8_t offset, uint16_t value);
#endif

// Used in Linux only
#ifdef __linux__
// PCI functions used for FPGAs which drop off the bus and reappear
void sgPCI_backupPCIConfig(sg_PCIDevice *pciinfo, uint32_t* configSave);
void sgPCI_restorePCIConfig(sg_PCIDevice *pciinfo, const uint32_t* configSave);
void sgPCI_printPCIConfig(sg_PCIDevice *pciinfo);

// Opens the configuration space of the specified PCI device. You can set whether it's read-only or
// read/write via the 'flags' parameter (like POSIX 'open()' call).
// On success, returns a file descriptor for the config space.
// On failure, returns -1 and errno is set.
int sg_pci_openPciConfig(sg_PCIDevice *pciDev, int flags);

// In case you want to use some other drivers for PCI devices
int sg_pci_bindDriver(sg_PCIDevice* device, const char* driverName);
int sg_pci_unbindDriver(sg_PCIDevice* device);
int sg_pci_probeDriver(sg_PCIDevice* device);
#endif // __linux__

//Map a PCI devices address space       
void* sg_mapMemory(sg_PCIDevice* device, uint32_t bar);
void* sg_mapIo(sg_PCIDevice* device, uint32_t bar);

#ifdef __linux__
// Functions to work with AXI devices (on-board FPGAs)
int sg_findAxiDevice(sg_AxiDevice* axiDevice, const char* deviceName);
void* sg_mapAxiBar(sg_AxiDevice *axiDevice, int bar);

// Functions to work with SoCs / on-board FPGAs
int sg_loadOnChipBitstream(const char *bitstreamFile);
#endif // __linux__

//For delays n' waiting
void sg_wait_ns(uint32_t delay_ns);
void sg_wait_s(double delay_s);
double sg_getElapsedTime();

// This is used in Linux to differentiate x86 and ARM
uint64_t sg_getTSCFrequency();

//File system handling working for both releases
bool sg_doesFsNodeExist(char* pPath);
void sg_fullFile(int nParts, char* path, ...);
void sg_setDriveLetter(char driveLetter);
int sg_getModelBaseDir(char* outPath, uint32_t maxLen);
int sg_getConfigBaseDir(char* outPath, uint32_t maxLen);

//General utilities
int sg_setAbilities(void);

//Threads
void* sg_createThread(void* (*func)(void*), void* arg);
int sg_destroyThread(void* handler);

#ifdef __linux__
int sg_setPidPriority(pid_t pid, int priority);
int sg_getPidPriority(pid_t pid);
int sg_pickNextAsyncCpu();
int sg_pinThisThreadToCpu(int cpu);
int sg_pinThreadExclusiveCpu(int cpu);
#endif

//Semaphores
void* sg_createSemaphore(int initCount);
int sg_destroySemaphore(void* handler);
int sg_releaseSemaphore(void* handler);
int sg_waitForSemaphore(void* handler);

//Creates a mutex
//  Input: 
//    - initialOwner: set to true to pass ownership of the mutex to the calling thread
//  Return: handler to the mutex
void* sg_createMutex(bool initialOwner);

//Destroys a mutex
//  Input: 
//    - handler: handler of the mutex
void sg_destroyMutex(void* handler);

//Releases ownership of a mutex
//  Input: 
//    - handler: handler of the mutex
void sg_unlockMutex(void* handler);

//Locks a mutex. If another thread has already locked the mutex, 
//the calling thread is blocked until the mutex can be locked.
//  Input: 
//    - handler: handler of the mutex
void sg_lockMutex(void* handler);

//Tries to lock a mutex and returns immediately.
//  Input: 
//    - handler: handler of the mutex
//  Return: On successful lock acquisition returns true, otherwise false.
bool sg_tryLockMutex(void* handler);

//Executes an executable in a newly spawned process
//  Input: 
//    - path: Location of the executable
//    - executableName: Name of the executable
//    - options: Arguments to the call of the executable
//  Return: PID (new process id) on successful spawn, -1 on failure
int sg_spawnExecutable(const char* path, const char* executableName, const char* options);

//Get the available and total Bytes from the block device 
//  Input: 
//    - path: Location of the block device
//    - mountPoint: Location where the device is mounted on 
//    - total: Total number of bytes
//    - available: Available number of bytes
//  Return: 0 on successful stat, -1 on failure
int sg_statPath(const char* path, char *mountPoint, double* total, double* available);

// Initializes a new model run. This function needs to be called by Setup blocks that use TLC.
void sg_initModelRun();

//For stage 3 S-functions: Identify the first model load
//  Return: False if the current model has been loaded already, without reboot or recompilation
bool sg_isFirstModelLoad();

//Register a function to be called at model exit
void sg_add_exit_handler(void (handler) (void*), void* argument);

//Register a function to be called at model start
// (Priority should be 0 by default - If in doubt, use 0)
void sg_add_start_callback(void (callback) (void*), void* argument, int priority);

// Synchronization functions for synchronizing asynchronous subrates with the baserate
// Function calls are used by the speedgoatSyncService class and attached asynchronous rates.
#ifdef __linux__
void sg_initBaseRateSync();
int sg_waitForBaseRateSync();
void sg_signalBaseRateSync();
int sg_destroyBaseRateSync();
#endif // __linux__

//********************
// Global variables       
//********************         

/// Global error string
extern char pSgErrorStr[500]; 
/**< Contains error message if libsg function fails (returns < 0). 
 The caller should then clean up and invoke "ssSetErrorStatus(S,pSgErrorStr); return;"
*/

#ifdef __cplusplus
}
#endif

#endif // #ifndef SG_COMMON_H
