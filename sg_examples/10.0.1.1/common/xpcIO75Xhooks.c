#ifndef __XPCIO75XHOOKS_C__
#define __XPCIO75XHOOKS_C__

#include "xpcimports.h"
#include "cifxapi.h"

int  __cdecl xpcIO75Xprehook(xpcPCIDevice *pci);
void __cdecl xpcIO75Xstart(xpcPCIDevice *pci);
void __cdecl xpcIO75Xstop(xpcPCIDevice *pci);

/*
*   This function is called by kernel when pci device throws an interrupt
*/
int __cdecl xpcIO75Xprehook(xpcPCIDevice *pci)
{
    return Cifx_IntrPreFcn(pci->BaseAddress[0], pci->InterruptLine);
}

/*
*   This function is called by kernel when realtime application starts, right after model initialization
*/
void __cdecl xpcIO75Xstart(xpcPCIDevice *pci)
{
    if (!xpcIsModelInit()) {
        Cifx_IntrStartFcn(pci->BaseAddress[0], pci->InterruptLine);
    }     
}

/*
*   This function is called by kernel when realtime application stops, right before model termination
*/
void __cdecl xpcIO75Xstop(xpcPCIDevice *pci)
{
    if (!xpcIsModelInit()) {
        Cifx_IntrStopFcn(pci->BaseAddress[0], pci->InterruptLine);
	}
}

#endif
