#ifndef __SG_FPGA_IO3XX_SCATTER_GATHER_DMA_H__
#define __SG_FPGA_IO3XX_SCATTER_GATHER_DMA_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct io3xx_sgdma_Handle io3xx_sgdma_Handle;

typedef enum {
    IO3XX_SGDMA_READ,
    IO3XX_SGDMA_WRITE,
} io3xx_sgdma_Direction;

typedef enum {
    IO3XX_SGDMA_NO_ERROR = 0,
    IO3XX_SGDMA_ERROR_ADDR_OUT_OF_RANGE = -1,
    IO3XX_SGDMA_ERROR_SG_CHAIN_TIMEOUT = -2,
    IO3XX_SGDMA_ERROR_CDMA_RESET_TIMEOUT = -3,
    IO3XX_SGDMA_ERROR_CDMA_IDLE_TIMEOUT = -4,
    IO3XX_SGDMA_ERROR_MEMORY_ALLOCATION = -5,
    IO3XX_SGDMA_ERROR_CDMA_ENGINE_NOT_IDLE = -6,
    IO3XX_SGDMA_ERROR_INVALID_ARG = -7,
    IO3XX_SGDMA_ERROR_NO_SCATTER_GATHER_AVAIL = -8,
} io3xx_sgdma_Error;

/*****************************************************************************
 * Standard API
 *****************************************************************************/
io3xx_sgdma_Error io3xx_sgdma_initialize(int moduleId, size_t shadowRegSize,
                                         uint32_t codeModuleBaseAddr,
                                         bool enableDmaController,
                                         io3xx_sgdma_Handle **handlePtr);
void io3xx_sgdma_cleanup(io3xx_sgdma_Handle *handle);
volatile void *io3xx_sgdma_getShadowRegister(io3xx_sgdma_Handle *handle);
void io3xx_sgdma_setKeyholeRead(io3xx_sgdma_Handle *handle);
void io3xx_sgdma_setKeyholeWrite(io3xx_sgdma_Handle *handle);
bool io3xx_sgdma_getEnableDmaController(io3xx_sgdma_Handle *handle);
void io3xx_sgdma_checkAndCorrect16ByteBoundary(io3xx_sgdma_Handle *handle);
io3xx_sgdma_Error io3xx_sgdma_enqueueData(io3xx_sgdma_Handle *handle, volatile void *regAddr,
                                          size_t regSize, io3xx_sgdma_Direction readWrite);
io3xx_sgdma_Error io3xx_sgdma_enqueueConstValue(io3xx_sgdma_Handle *handle, volatile void *regAddr,
                                                uint32_t constantVal);
io3xx_sgdma_Error io3xx_sgdma_enqueueIndexList(io3xx_sgdma_Handle *handle, volatile void *regAddr,
                                               size_t regSize, io3xx_sgdma_Direction readWrite,
                                               int *indexList, int indexListLength);
io3xx_sgdma_Error io3xx_sgdma_enqueueFifo(io3xx_sgdma_Handle *handle, volatile void *regAddr,
                                          size_t regSize, io3xx_sgdma_Direction readWrite,
                                          volatile uintptr_t destAddr, volatile uint32_t **descControl);
// This is the blocking function to complete DMA access across the descriptor chain.
io3xx_sgdma_Error io3xx_sgdma_commitTransfer(io3xx_sgdma_Handle *handle);

double getAverageDMATime(io3xx_sgdma_Handle *handle);

io3xx_sgdma_Error io3xx_sgdma_finalizeDmaController(int moduleId);
void io3xx_sgdma_startDmaController(int moduleId);
void io3xx_sgdma_feedSequential(int moduleId);
void io3xx_sgdma_stopDmaController(int moduleId);
/*****************************************************************************
 * Simple API
 *****************************************************************************/
io3xx_sgdma_Error io3xx_sgdma_simpleTransfer(io3xx_sgdma_Handle *handle, volatile void *regAddr,
                                             size_t regSize, io3xx_sgdma_Direction readWrite);

/*****************************************************************************
 * Printing / Debug Functions
 *****************************************************************************/
void io3xx_sgdma_printDescrChainDmaController(int moduleId);
void io3xx_sgdma_printDescrChain(io3xx_sgdma_Handle *handle);
void io3xx_sgdma_printDmaEngineRegs(io3xx_sgdma_Handle *handle);

#ifdef __cplusplus
}
#endif

#endif // __SG_FPGA_IO3XX_SCATTER_GATHER_DMA_H__
