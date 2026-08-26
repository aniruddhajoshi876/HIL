#ifndef SG_UIO_H
#define SG_UIO_H

#include "sg_common.h"
#include <semaphore.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __linux__

// These structs were moved from sg_interrupt_config.h to here snce it will be used in speedgoatlib as well
// as the model interrupt context.

// struct _sg_int_fix contains the resources we need internally to implement special handling
//  Interrupts are handled differently in the kernel (uio_speedgoat module)
//  because of a non-conformity in the endpoint.
struct _sg_int_fix{
    bool requested_by_user;
    volatile uint32_t* target_register;
    uint32_t int_mask;
    uint32_t fix_type;
};

// The sg_InterruptContext type "inherits" from the sg_PCIDevice type. This way, pointers to a
// sg_InterruptContext struct are also valid pointers to a sg_PCIDevice struct (need to be casted).
// This behavior is defined in the C standard and works therefore with all compilers.
typedef struct
{
    //PCI device
    sg_PCIDevice pciInfo;

    //Configuration
    bool is_polling;

    //UIO specific information
    void* map[6];
    int uioIndex;
    int uiofd;
    int configfd;
    unsigned char command_high;

    //Internal configuration
    uint16_t interruptChannel;
    int moduleId;
    void* customData;
    struct _sg_int_fix sg_int_fix;

    //Runtime state
    sem_t start_func_finished_sem;
    sem_t wait_func_ready_sem;
    bool is_first_wait_call;
    bool waiting_for_start;
    int intCount;
    int noIntCount;
    int irq_cpu_assigned;
    int priority;
    int defaultPriority;
    bool isModelTrigger;
    bool overloadCheckEnabled;
} sg_InterruptContext;


// Makes UIO take ownership of the specified PCI device.
// On success, returns the number of the /dev/uioX device node.
// On failure, returns -1 and errno is set.
int sg_uio_bindDeviceToUio(sg_PCIDevice *pciDev);

// Use this to set the priority of the IRQ thread associated with a UIO device.
int sg_uio_setIrqProps(sg_InterruptContext * context);
int sg_uio_resetIrqProps(sg_InterruptContext * context);

// Functions for directly spinning off an interrupt thread for UIO devices from within an S-function (or wherever)
int sg_uio_createInterruptContext(sg_InterruptContext **contextOut, sg_PCIDevice *pciInfo);
int sg_uio_interruptAttach(sg_InterruptContext * context);
int sg_uio_interruptEnableFix(sg_InterruptContext* context);
int sg_uio_enableInterrupt(sg_InterruptContext* context);
int sg_uio_interruptWait(sg_InterruptContext *context);
void sg_uio_interruptDetach(sg_InterruptContext *context);

#endif // __linux__

#ifdef __cplusplus
}
#endif

#endif // SG_UIO_H
