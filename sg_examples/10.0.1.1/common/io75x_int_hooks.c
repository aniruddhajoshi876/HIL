static const int SG_INT_BARS[] = {0}; 
#define SG_INT_PREFIX   IO75x

#include "sg_interrupt_config.h"
#include "cifxapi.h"

/*
*   This function is called by kernel when pci device throws an interrupt
*/
SG_INT_ISR_FUNC
{
    return Cifx_IntrPreFcn(((sg_PCIDevice*)pciinfo)->BaseAddress[0], 0);
}

/*
*   This function is called by kernel when realtime application starts, right after model initialization
*/
SG_INT_START_FUNC
{
    //if (!sg_isModelInit()) {
        Cifx_IntrStartFcn(((sg_PCIDevice*)pciinfo)->BaseAddress[0], 0);
    //}     
}

/*
*   This function is called by kernel when realtime application stops, right before model termination
*/
SG_INT_STOP_FUNC
{
    //if (!sg_isModelInit()) {
        Cifx_IntrStopFcn(((sg_PCIDevice*)pciinfo)->BaseAddress[0], 0);
	//}
}

