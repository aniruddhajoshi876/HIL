// SG_INT_PREFIX needs to match the prefix that was defined in sg.db.getInterrupts.m
#define SG_INT_PREFIX   IO312
// SG_INT_BARS needs to specify all the bars you’d like to memory map
static const int SG_INT_BARS[] = {0,2};

#include "sg_blocks/common/libsg/sg_common.h"
#include "sg_interrupt_config.h"
#include <stdint.h>
#define SYNCHBASE               (0x9C00)

struct SYNCH
{
  uint32_t parameter;
  uint32_t clear;
  uint32_t copy; 
  uint32_t event;
};
struct plxInt
{
  volatile uint32_t INTCSR;  // 0x68
};

SG_INT_START_FUNC
{
    volatile struct plxInt *plx;  
    volatile struct SYNCH *synch;

    if (!sg_isModelInit())
    {
        // interrupt activation on PLX side
        /* 1. Local interrupt activation [LINTi],  set the bits 11 and 8 to activate local interrupt source*/
        plx = (struct plxInt *)((uintptr_t)SG_INT_MAPPED_BAR(0) + 0x68);
        synch = (struct SYNCH *)((uintptr_t)SG_INT_MAPPED_BAR(2) + SYNCHBASE); 
        synch->clear = 0x1;
        synch->clear = 0x0;
        plx->INTCSR |= 0x900;
    }
    return;
}

SG_INT_STOP_FUNC
{
  volatile struct plxInt *plx;  
  volatile struct SYNCH *synch;
 
    if (!sg_isModelInit())
    { 
        // Disable interrupts from the board.
        plx = (struct plxInt *)((uintptr_t)SG_INT_MAPPED_BAR(0) + 0x68);
        synch = (struct SYNCH *)((uintptr_t)SG_INT_MAPPED_BAR(2) + SYNCHBASE); 
        synch->clear = 0x1;
        synch->clear = 0x0;
        
        plx->INTCSR &= (~0x900);
    }
    return;
}

SG_INT_ISR_FUNC
{
    volatile struct plxInt *plx;
    volatile struct SYNCH *synch;
    
    plx = (struct plxInt *)((uintptr_t)SG_INT_MAPPED_BAR(0) + 0x68);
    synch = (struct SYNCH *)((uintptr_t)SG_INT_MAPPED_BAR(2) + SYNCHBASE); 
    
    // does the FPGA asserts the interrupt?
    if (plx->INTCSR & 0x8000)
    {        
        synch->clear = 0x1;
        synch->clear = 0x0;
        return SG_RUN_ISR;
    }
    else
    {
        return SG_DROP_ISR; //not our interrupt
    }
}