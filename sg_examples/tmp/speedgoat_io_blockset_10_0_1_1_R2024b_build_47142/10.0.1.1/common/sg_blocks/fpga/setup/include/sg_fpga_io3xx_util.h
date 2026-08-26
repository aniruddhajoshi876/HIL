#ifndef __SG_FPGA_IO3XX_UTIL_H__
#define __SG_FPGA_IO3XX_UTIL_H__

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef MATLAB_MEX_FILE
  #include <sg_common.h>
  #include "sg_fpga_io3xx_enum.h"
#endif


#include <stdint.h>
#include <stdlib.h>

/* type definitions **********************************************************************/
typedef enum
{
    TEWS_TXMC,
    TEWS_TPMC,
    TEWS_MPCIE,
    ACROMAG_PMC,
    ACROMAG_XMC,
    ENCLUSTRA_SOM,
    FORDSP_FMC,
    XILINX_MPSOC
} ModuleArchitecture_T;

typedef struct sg_fpga_io3xxModuleIdT{
    uint16_t vendorid;
    uint16_t deviceid;
    uint16_t subvendorid;
    uint16_t subdeviceid;
    char devname[30];
    ModuleArchitecture_T moduleArchitecture; // 0:IO31x, IO32x; 1: IO331, 2: IO33x, 3: IO38x
} sg_fpga_io3xxModuleIdT;

typedef volatile struct {
    uint32_t axiBarToPcieBar_0U;
    uint32_t axiBarToPcieBar_0L;
    uint32_t axiBarToPcieBar_1U;
    uint32_t axiBarToPcieBar_1L;
    uint32_t axiBarToPcieBar_2U;
    uint32_t axiBarToPcieBar_2L;
    uint32_t axiBarToPcieBar_3U;
    uint32_t axiBarToPcieBar_3L;
    uint32_t axiBarToPcieBar_4U;
    uint32_t axiBarToPcieBar_4L;
    uint32_t axiBarToPcieBar_5U;
    uint32_t axiBarToPcieBar_5L;
} sg_fpga_io3xx_AxiBaseAddrTrnsConfReg;

// Utilities for working with the module registry
typedef enum {
    SG_FPGA_IO3XX_BAR0 = 0,
    SG_FPGA_IO3XX_BAR1 = 1,
    SG_FPGA_IO3XX_BAR2 = 2,
    SG_FPGA_IO3XX_BAR3 = 3,
    SG_FPGA_IO3XX_BAR4 = 4,
    SG_FPGA_IO3XX_BAR5 = 5
} sg_fpga_io3xx_BarEnum;

//Error states to return from setup functions to the top level
typedef enum {
    NO_ERR = 0,
    BOARD_NOT_FOUND = -1,
    BITSTREAM_NOT_FOUND = -2,
    ICAP_RECONF_FAILED = -3,
    BOARD_TYPE_UNKNOWN = -4,
    EEPROM_ERROR = -5,
    REPROG_ERROR = -6,
    FLASH_ERROR = -7,
    BIST_ERROR = -8,
    PCIE_ENDPOINT_ERROR = -9,
    DMA_SETUP_ERROR = -10,
    OTHER_ERROR = -11
}SETUP_ERROR_T;

///////////////////////////////////////////////////////////////////
// Define an FPGA custom data type to append to the interrupt-context

typedef struct
{
    int moduleId;
    volatile uint32_t *cycleCounterPtr;
    uint32_t cycleCounter_old;
    volatile void* util_ptr;
} sg_fpga_intContext_customData;

///////////////////////////////////////////////////////////////////
// Define an FPGA custom data type to append to the module-registry

typedef struct
{
    void*    mutex;
    uint32_t direction[8];
    uint32_t active[8];
    uint32_t outputState[8];
} dioState_t;

typedef struct
{
    void*    mutex;
    uint64_t enabled;
    uint64_t invert_a;
    uint64_t invert_b;
    uint64_t invert_c;
    uint64_t idle_a;
    uint64_t idle_b;
    uint64_t idle_c;
    uint32_t inv_idle_initialized;
    uint64_t enable_latch_half_period;
    uint64_t force_stop;
    uint64_t enable_natural_pwm;
} pwmState_t;

typedef struct
{
    void*    mutex;
    uint32_t start;
    uint32_t nTX_RX;
    uint32_t skipRegAddress;
} i2cState_t;

typedef struct
{
    void*    mutex;
    uint32_t enable;
} inta2State_t;


typedef struct
{
    uint32_t operationReg[32];
} pulsecounterState_t;

typedef struct {
    void*               mutex;                  // To protect scatter-gather DMA from concurrent accesses
                                                // the following pointers are used for CPU-Controlled DMA, where each code-module
                                                // starts his own part of DMA during model-step
    uint32_t            dmaTriggerTimeTicks;    // number of FPGA Ticks for the dma controller trigger
    uint32_t            dmaTriggerSourceSel;    // trigger source selection for the dma controller
    uintptr_t           lastDescriptorAddr;     // pointer to last descriptor that was active during CPU-controlled DMA
    uint32_t            cdmaCrBackup;           // control register backup common, especially to restore keyhole settings
    bool                dmaIsReset;             // indicate if DMA is reset
    bool                enableDma;              // DMA engine is enabled resp. available
    bool                useFpgaDmaController;   // use the Dma Controller from FPGA
    bool                finishWithCPU;          // add a dummy descriptor when finishing FPGA-DMA chain so CPU-DMA can be inserted as well
    bool                dmaModeSequential;      // sequential mode
    bool                dmaModeParallel;        // parallel mode
    volatile uint32_t   *intPollCounterPtr;     // pointer to the counter which is written from the FPGA-controlled DMA
                                                // this one can be used on the CPU to see when a read-DMA (Data from FPGA to CPU)
                                                // has been finished. There are also additional status informations
                                                // the following pointers are used for FPGA-Controlled DMA, where the whole DMA-chain
                                                // for all existing code-modules is executed at one time
    uintptr_t           firstDescriptorRead;    // pointer to first read-DMA descriptor (Data from FPGA to CPU)
    uintptr_t           lastDescriptorRead;     // pointer to last read-DMA descriptor (Data from FPGA to CPU)
    uintptr_t           dummyDescriptor;        // pointer to dummy descriptor (used to insert CPU-DMA chains in FPGA-DMA chain during runtime)
    uintptr_t           firstDescriptorWrite;   // pointer to first write-DMA descriptor (Data from FPGA to CPU)
    uintptr_t           lastDescriptorWrite;    // pointer to last write-DMA descriptor (Data from FPGA to CPU)
    volatile uint32_t   *commonScratchRegPtr;   // scratch register Pointer
    int                 commonScratchRegIndex;  // scratch register index
    uint32_t            cdmaControlAxiAddr;     // AXI address of the cdma controller
    uintptr_t           cdmaControlPhysAddr;    // physical address of the cdma controller
    bool                writeMSWcommit;         // write MSW to start commit (used for MPSOC based CDMA)
    uint32_t            axiAddrCDMA;            // AXI address of the CDMA in the design
    uintptr_t           cpuAddrCDMA;            // CPU address of the CDMA in the design
} ScatterGatherDmaState;

typedef struct
{
    double   sampleTime;
    double   fpgaFrequency;
} modelTimings_t;

// structure for ISOSPI module custom data
typedef struct 
{
    uint8_t PlugOnType[4]; // PlugOn type for each channel
    uint8_t *pciPtrI2cP14 ; // Pointer to the P14 I2C controller
} mod_desc_ISOSPI;


typedef struct mod_desc_FPGA_sg_lib
{
    int32_t deviceIndex;
    int16_t vendorId;
    int16_t deviceId;
    char boardName[256];
    void* bar0ptr;
    void* bar1ptr;
    void* bar2ptr;
    void* bccPtr;
    void* pDMAPoolBase;
    void* pDMAPoolBasePhys;
    void* pDmaReadMemoryPool;
    void* pDmaReadMemoryPoolPhys;
    void* pDmaWriteMemoryPool;
    void* pDmaWriteMemoryPoolPhys;
    void* pCdmaMemoryPool[2];
    void* pCdmaMemoryPoolPhys[2];
    void* modTypeSpecificCustomData;
    uintptr_t  fpgaDmaMemCpuPtr;
    size_t     fpgaDmaMemSize;
    uintptr_t  fpgaDmaMemPhysicalPtr;
    uintptr_t  fpgaDmaMemStackPointer;
    uint32_t   fpgaBaseAxiAddrCodeModules;
    uint32_t   fpgaBaseAxiAddrBram;
    uintptr_t  fpgaBaseAxiAddrDmaMemPool;
    void*      bramPtr;
    uintptr_t  bramStackPointer;
    dioState_t dioState;
    pwmState_t pwmState;
    i2cState_t i2cState;
    inta2State_t inta2State;
    pulsecounterState_t pulsecounterState;
    ScatterGatherDmaState sgDmaState;
    uint32_t serialNumber;
    uint32_t boardType;
    modelTimings_t modelTimings;
    uint32_t analogInputBuffer;
    uint32_t analogOutputBuffer;
} mod_desc_FPGA_sg_lib;

// blocktype for the block registry
typedef enum
{
    SG_BLOCK_TYPE_BISS,
    SG_BLOCK_TYPE_BISS_ENCODER,
    SG_BLOCK_TYPE_BISS_SNIFFER,
    SG_BLOCK_TYPE_IO3XX_120_ANALOG_SETUP,
    SG_BLOCK_TYPE_IO324_ANALOG_SETUP,
    SG_BLOCK_TYPE_IO334_ANALOG_SETUP,
    SG_BLOCK_TYPE_IO336_ANALOG_SETUP,
    SG_BLOCK_TYPE_IO337_ANALOG_SETUP,
    SG_BLOCK_TYPE_EVENTS_CAPTURE,
    SG_BLOCK_TYPE_CRANK_ANGLE,
    SG_BLOCK_TYPE_VRS,
    SG_BLOCK_TYPE_HALL_SENSOR,
}block_type_T;

// type containing the device address, register addres and value for i2c write operations
// (used for i/o extensions and resolver measurement configuration)
typedef struct
{
    uint8_t devAddr;
    uint8_t regAddr;
    uint8_t data;
} ioExtConfig24;

// register map of the timestamp ip core
typedef struct
{
    volatile uint32_t timestamp;
    volatile uint32_t functionCode0;
    volatile uint32_t functionCode1;
    volatile uint32_t functionCode2;
}sg_fpga_io3xx_timestamp_reg_map;

int32_t  sg_fpga_IO3xxGetModuleId(int boardType, sg_fpga_io3xxModuleIdT* moduleId);

//register the module.
void registerFPGAModuleSgLib(int32_t moduleId, int32_t device_index,int16_t vendorId,int16_t deviceId, sg_PCIDevice* pciinfo, const char* boardname);
#ifdef __linux__
void registerAxiFPGASgLib(int32_t moduleId, sg_AxiDevice *axiDevice, const char* boardname);
#endif

// search the FPGA IO-Board specific ID
int sg_fpga_io3xx_getID(sg_PCIDevice* pciinfo);
void sg_fpga_io3xx_initDioLines(int32_t moduleId, int barIndex);
void freeFPGAModuleSgLib(int32_t moduleId);

uint32_t io3xxGetPointerDioStateSgLib(int moduleId, dioState_t **ptrDioState);
uint32_t io3xxGetPointerPwmStateSgLib(int moduleId, pwmState_t **ptrPwmState);
uint32_t io3xxGetPointerI2cStateSgLib(int moduleId, i2cState_t **ptrI2cState);
uint32_t io3xxGetPointerInta2StateSgLib(int moduleId, inta2State_t **ptrInta2State);
uint32_t io3xxGetPointerPulsecounterStateSgLib(int moduleId, pulsecounterState_t **ptrPulsecounterState);

void* io3xxGetAddressSgLib(int32_t moduleId, int barIndex);
int sg_fpga_io3xx_setBccAddr(int moduleId, uintptr_t bccAddr);
uintptr_t sg_fpga_io3xx_getBccAddr(int moduleId);
void io3xxSetBoardTypeSgLib(int moduleId, uint32_t boardType);
uint32_t io3xxGetBoardTypeSgLib(int moduleId);
char* io3xxGetBoardNameSgLib(int moduleId);
uint32_t sg_fpga_io3xx_getP14AxiIicFlag(int moduleId);

// DMA framework functions
int createDmaMemoryPool(int32_t moduleId);
void freeDmaMemoryPool(int32_t moduleId);
void *sg_fpga_io3xx_allocFromFpgaDmaMem(int moduleId, size_t size);
int sg_fpga_io3xx_getSharedSgDmaState(int moduleId, ScatterGatherDmaState **sgDmaStatePtr);
int sg_fpga_io3xx_getSharedTimingInfo(int moduleId, modelTimings_t **modelTimingsPtr);
uintptr_t io3xxGetFpgaDmaMemCpuPtrSgLib(int moduleId);
uintptr_t io3xxGetFpgaBaseAxiAddrDmaMemPoolSgLib(int moduleId);
void* io3xxGetPointerDmaReadMemoryPoolPhys(int moduleId);
void* io3xxGetPointerDmaWriteMemoryPoolPhys(int moduleId);
size_t io3xxGetFPGADmaMemPoolSizeSgLib(int moduleId);
uint32_t io3xxGetFpgaBaseAxiAddrBramSgLib(int moduleId);
uint32_t io3xxGetFpgaBaseAxiAddrCodeModulesSgLib(int moduleId);
void *sg_fpga_io3xx_allocFromBram(int moduleId, size_t size);
uintptr_t sg_fpga_io3xx_getBramBaseAddr(int moduleId);

uint32_t sg_fpga_io3xx_checkCodeModuleVersion(uint32_t versionInfo, uint8_t MAJORVERSION, int moduleId);
uint32_t sg_fpga_io3xx_getCmBaseAddress(int moduleId, uint32_t lookup, uint32_t *offset);

void *sg_fpga_io3xx_block_register(uint32_t moduleId, uint32_t blockType, uint32_t blockId, void* blockdata);
void sg_fpga_io3xx_block_unregister(uint32_t moduleId, uint32_t blockType, uint32_t blockId);
void *sg_fpga_io3xx_block_get(uint32_t moduleId, uint32_t blockType, uint32_t blockId);



// DMA memory pool status codes
#define MEMORY_POOL_NOT_CREATED -1
#define MEMORY_POOL_CREATED 0
#define DMA_POOL_FREED 0
#define DMA_POOL_NOT_FREED -1

/*****************************************************************************
 * Location for code module offsets.
 * Presently these are all defined in their individual s-functions (or other places).
 * We need to gather them in one place, where they can be returned from a utility function.
 * Also making the naming more unique at the same time to prevent namespace collisions.
 *****************************************************************************/
#define LUT_OFFSET              (0x110000)
#define LUT_SIZE                (0x0200)
#define DUT_TIME_STAMP_OFFSET   (0x8) 

// Duplicated definitions here should not be an issue (older versions of code modules),
// since it is allowed to redefine a macro with the same value!
#define ADBASE                      (0x0000C000)
#define DABASE                      (0x00010000)
#define DIO_BASE                    (0x00014000)
#define PWM_BASE                    (0x00018000)
#define QAE_BASE                    (0x00030000)
#define BISS_SNIFFER_BASE           (0x00040000)
#define BISS_BASE                   (0x00044000)
#define BISS_ENCODER_BASE           (0x00048000)
#define CAP_BASE                    (0x0001C000)
#define INTA_BASE                   (0x00024000)
#define QAD_BASE                    (0x00020000)
#define I2CM_BASE                   (0x0002C000)
#define I2CS_BASE                   (0x00034000)
#define ENDAT_BASE                  (0x00060000)
#define ENDAT_ENCODER_BASE          (0x00068000)
#define ENDAT_SNIFFER_BASE          (0x0006C000)
#define SENT_RX_BASE                (0x00070000)
#define SENT_TX_BASE                (0x00074000)
#define SPI_BASE                    (0x000D0000)
#define SPI_SNIFFER_BASE            (0x000D4000)
#define SERIAL_BASE                 (0x00108000)
#define IO397_AD_BASE               (0x00120000)
#define IO397_DA_BASE               (0x00124000)
#define DSHOT_RX_BASE               (0x0012C000)
#define DSHOT_TX_BASE               (0x00130000)
#define PULSECOUNTER_BASE           (0x00134000)
#define RESOLVER_BASE               (0x0013C000)
#define RESOLVER_DECODER_BASE       (0x00140000)
#define A2B_BASE                    (0x00144000)
#define A2B_I2C_BASE                (0x00148000)
#define A2B_SPI_BASE                (0x0014A000)
#define SSIS_BASE                   (0x000B4000)
#define SSIM_BASE                   (0x0003C000)
#define SSI_SNIFFER_BASE            (0x000AC000)
#define CRANK_ENCODER_BASE          (0x00100000)
#define CRANK_DECODER_BASE          (0x00104000)
#define ADBASE32x                   (0x00110000)
#define CAM_ENCODER_BASE            (0x00114000)
#define CAM_DECODER_BASE            (0x00118000)
#define CRANK_DECODER_EVENT_BASE    (0x0011c000)
#define VRS_BASE                    (0x00138000)
#define EVENTS_CAPTURE_BASE         (0x00128000)
#define CRANK_ANGLE_BASE            (0x00200000)
#define HALL_SENSOR_BASE            (0x00204000)
#define ADBMS6832_33_BASE           (0x001FC000)
// Plug-in base address
#define IO3xx_2x_BASE               (0xA4000) 

// address of timestamp ip core
#define SG_FPGA_IO3XX_TIMESTAMP_ADDR        (0x570000)

// Add defines of bit masks for time stamp ip function code registers here:
#define IO3xx_FC0_P14IIC_MASK 0x01 // function code register 0 bit 0: Presence of P14 AXI IIC IP

#ifdef __cplusplus
}
#endif

#endif      // END: __SG_FPGA_IO3XX_UTIL_H__
