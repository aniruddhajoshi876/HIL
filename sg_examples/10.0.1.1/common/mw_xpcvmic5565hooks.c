/* Abstract: Hook functions for the GE Fanuc(VMIC) 5565
 * shared/reflective memory boards.
 */
 
/* Copyright 1996-2009 The MathWorks, Inc.
 */

#ifndef __XPCVMIC5565HOOKS_C__
#define __XPCVMIC5565HOOKS_C__

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "xpctarget.h"

#define RFM_BRV    (*((uint8_T *)(rfmcontrolregisters+0x00)))
#define RFM_BID    (*((uint8_T *)(rfmcontrolregisters+0x01)))
#define RFM_NID    (*((uint8_T *)(rfmcontrolregisters+0x04)))
#define RFM_LCSR1  (*((uint32_T *)(rfmcontrolregisters+0x08)))
#define RFM_LISR   (*((uint32_T *)(rfmcontrolregisters+0x10)))

#define RFM_SID1   (*((uint8_T *)(rfmcontrolregisters+0x24)))
#define RFM_SID2   (*((uint8_T *)(rfmcontrolregisters+0x2C)))
#define RFM_SID3   (*((uint8_T *)(rfmcontrolregisters+0x34)))
#define RFM_INITN  (*((uint8_T *)(rfmcontrolregisters+0x3C)))

#define RUNREG_INTCSR (*((uint32_T *)(runtimeregisters+0x68)))

#include <conio.h>
#include "tmwtypes.h"

int  __cdecl xpcvmic5565prehook(xpcPCIDevice *pci);
void __cdecl xpcvmic5565start(xpcPCIDevice *pci);
void __cdecl xpcvmic5565stop(xpcPCIDevice *pci);

// Pre hook is called for each interrupt and should
// clear the interrupt.  This is called while interrupts are disabled
//
int __cdecl xpcvmic5565prehook(xpcPCIDevice *pci)
{
   volatile uint8_T *rfmcontrolregisters = (void *)(pci->VirtAddress[2]);
   volatile uint8_T *runtimeregisters =(void *)(pci->VirtAddress[0]);

   uint32_T intcsr = RUNREG_INTCSR;
   uint32_T lisr = RFM_LISR;
   uint8_T dummy;

   if( !(intcsr & 0x8000) )
   {
       return XPC_DROP_ISR;  // Not our interrupt
   }
   // check for a network interrupt
     
   if(lisr & 0x01) {
       dummy = RFM_SID1;
       RFM_SID1 = 0;  // clear ALL pending interrupts from FIFO
   }
   if(lisr & 0x02) { // Network interrupt 1
       dummy = RFM_SID2;
       RFM_SID2 = 0;  /// clear ALL pending interrupts from FIFO
   }
   if(lisr & 0x04) { // Network interrupt 1
       dummy = RFM_SID3;
       RFM_SID3 = 0;   /// clear ALL pending interrupts from FIFO
   }
   if(lisr & 0x80) { // Init interrupt 
       dummy = RFM_INITN;
       RFM_INITN = 0;   /// clear ALL pending interrupts from FIFO
   }
    return XPC_RUN_ISR;
}
 
// this is called at mdlStart time to configure the interrupt
// Note specific interrupt souce must have been defined in
//  the init block.  This simply enables the interrupt bit
void __cdecl xpcvmic5565start(xpcPCIDevice *pci)
{
    // Base Address 2 (define as byte-wide to simplify offset calculation)
    volatile uint8_T  *rfmcontrolregisters;

    // Base Address 0 (define as byte-wide to simplify offset calculation)
    volatile uint8_T  *runtimeregisters;

    pci->VirtAddress[0]
        = (unsigned long)xpcReserveMemoryRegion( (void *)pci->BaseAddress[0],
                                                 0x108,
                                                 XPC_RT_PG_USERREADWRITE );

    pci->VirtAddress[2]
        = (unsigned long)xpcReserveMemoryRegion( (void *)pci->BaseAddress[2],
                                                 0x40,
                                                 XPC_RT_PG_USERREADWRITE );

    rfmcontrolregisters= (void *)(pci->VirtAddress[2]);
    runtimeregisters =(void *)(pci->VirtAddress[0]);

    RFM_SID1 = 0;  // Clear any unscheduled network interrupts (old ones)
    RFM_SID2 = 0;
    RFM_SID3 = 0;
    RFM_INITN =0;
    RFM_LISR = 0x4000;   // Enable interrupts on board (and clear any old stuff)
   
    RUNREG_INTCSR = RUNREG_INTCSR | 0x900;  //sets bit 11 and 8 of INTCSR

    return;
}

void __cdecl xpcvmic5565stop(xpcPCIDevice *pci)
{
    volatile uint8_T  *rfmcontrolregisters;  // Base Address 2 (define as byte-wide to simplify offset calculation)
    volatile uint8_T  *runtimeregisters;  // Base Address 2 (define as byte-wide to simplify offset calculation)

    rfmcontrolregisters = (void *)(pci->VirtAddress[2]);
    runtimeregisters = (void *)(pci->VirtAddress[0]);
    RFM_LISR = 0x0000;   // Disable interrupts on board (and clear any old stuff)
    return;
}

#endif /* __XPCVMIC5565HOOKS_C__ */
