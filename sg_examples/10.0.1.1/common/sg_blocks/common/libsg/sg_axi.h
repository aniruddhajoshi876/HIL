#ifndef SG_UIO_H
#define SG_UIO_H

#include "sg_common.h"
#include <semaphore.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __linux__

typedef struct
{
    // AXI device
    sg_AxiDevice axiDevice;
    void* map[6]; // Up to six per UIO device. This is an arbitrary limit.
    int uiofd;
    const char* axi_device_name;

    // Configuration
    bool is_polling;

    // Internal configuration
    uint16_t interruptChannel;
    int moduleId;
    void* customData;

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

    // IRQ information associated with this context
    int irqNumber;
} sg_InterruptContext;

// Functions to work with AXI devices (on-board FPGAs)
int sg_findAxiDevice(sg_AxiDevice* axiDevice, const char* deviceName);
void* sg_mapAxiBar(sg_AxiDevice *axiDevice, int bar);
int sg_setAxiIrqPriority(const char* uio_name, int priority);
// Set CPU affinity for the IRQ associated with an AXI UIO device name.
int sg_setAxiIrqAffinity(const char* deviceName, int cpuNumber);

#endif // __linux__

#ifdef __cplusplus
}
#endif

#endif // SG_UIO_H
