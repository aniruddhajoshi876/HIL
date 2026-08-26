/* Abstract: Hook functions for Scramnet SC-150+ boards
 *
 * Copyright 1996-2007 The MathWorks, Inc.
 */

#ifndef __XPCSCRAMNETHOOKS_C__
#define __XPCSCRAMNETHOOKS_C__

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "xpctarget.h"

#include <conio.h>
#define CSR0                                    0x400001
#define CSR1                                    0x400080
#define CSR2                                    0x400103
#define CSR3                                    0x400182
#define CSR4                                    0x400205
#define CSR5                                    0x400284
#define CSR6                                    0x400307
#define CSR7                                    0x400386
#define CSR8                                    0x400409
#define CSR9                                    0x400488
#define CSR10                                   0x40050B
#define CSR11                                   0x40058A
#define CSR12                                   0x40060D
#define CSR13                                   0x40068C
#define CSR14                                   0x40070F
#define CSR15                                   0x40078E

typedef unsigned short uint16_T;

int  __cdecl xpcscramnetprehook(xpcPCIDevice *pci);
void __cdecl xpcscramnetstart(xpcPCIDevice *pci);
void __cdecl xpcscramnetstop(xpcPCIDevice *pci);

int  __cdecl xpcscramnetprehook(xpcPCIDevice *pci)
{
    volatile unsigned long  *ioaddress32pci =
        (volatile unsigned long *)pci->VirtAddress[0];
    volatile unsigned short *ioaddress16    =
        (volatile unsigned short *)pci->VirtAddress[1];
    unsigned short csr4, csr5;
    unsigned long status;
    int rval = XPC_DROP_ISR;

    status= ioaddress32pci[0x12];
    ioaddress32pci[0x12]= status;

    // Clear the interrupt fifo
    csr5 = ioaddress16[CSR5];

    while ( (csr5 & 0x8000)== 0x8000) {
        rval = XPC_RUN_ISR;  // There was at least one address.
        csr4  = ioaddress16[CSR4];
        csr5 = ioaddress16[CSR5];
    }

    // Reset the interrupts armed bit
    ioaddress16[CSR1]=0x0000;
    return rval;
}

void __cdecl xpcscramnetstart(xpcPCIDevice *pci)
{
    volatile unsigned long  *ioaddress32pci;
    void *Physical0, *Physical1; //, * Virtual0, *Virtual1;
    unsigned long status;
    volatile unsigned short *ioaddress16;
    unsigned short csr4, csr5;

    Physical0=(void *)pci->BaseAddress[0];
    pci->VirtAddress[0]
        = (unsigned long)xpcReserveMemoryRegion(Physical0,
                                                0x100,
                                                XPC_RT_PG_USERREADWRITE);
    ioaddress32pci=(void *)pci->VirtAddress[0];

    Physical1 = (void *)pci->BaseAddress[1];
    pci->VirtAddress[1]
        = (unsigned long)xpcReserveMemoryRegion(Physical1,
                                                0x1000000,
                                                XPC_RT_PG_USERREADWRITE);
    ioaddress16=(void *)pci->VirtAddress[1];

    ioaddress32pci[0x13]= 0x01060002;
    status= ioaddress32pci[0x12];
    ioaddress32pci[0x12]= status;
    csr5 = ioaddress16[CSR5];
    while ( (csr5 & 0x8000)== 0x8000) {
        csr4 = ioaddress16[CSR4];
        csr5 = ioaddress16[CSR5];
    }
    ioaddress16[CSR1]=0x0000;
    return;
}

void __cdecl xpcscramnetstop(xpcPCIDevice *pci)
{
    volatile unsigned long  *ioaddress32pci;
    unsigned long status;
    volatile unsigned short *ioaddress16;
    unsigned short csr4, csr5;

    ioaddress32pci = (void *)pci->VirtAddress[0];
    ioaddress16 = (void *)pci->VirtAddress[1];

    ioaddress32pci[0x13]= 0x00000000;
    ioaddress16[CSR0]=0x0000;
    ioaddress16[CSR0]=0x2000;
    ioaddress16[CSR0]=0x0000;
    status= ioaddress32pci[0x12];
    ioaddress32pci[0x12]= status;
    csr5 = ioaddress16[CSR5];
    while ( (csr5 & 0x8000)== 0x8000) {
        csr4 = ioaddress16[CSR4];
        csr5 = ioaddress16[CSR5];
    }
    ioaddress16[CSR1]=0x0000;
    return;
}

#endif /* __XPCSCRAMNETHOOKS_C__ */
