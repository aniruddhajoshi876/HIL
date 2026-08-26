#ifndef SG_INTERRUPT_CONFIG_AXI_H_
#define SG_INTERRUPT_CONFIG_AXI_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "sg_blocks/common/libsg/sg_common.h"
#include "sg_blocks/common/libsg/sg_target.h"
#include "sg_blocks/common/libsg/sg_printf.h"

// ================================================================================================
// The macro magic
// The ## operator concatenates two macro arguments, but it needs to be double nested
// SG_INT_PREFIX is defined in the hook file itself, let's say to "IO130"
// The macro SG_INT_MAP_FUNC_NAME   will make "IO130_map"        out of it
// The macro SG_INT_MAP_FUNC_NAME_P will make "IO130_map_public" out of it
// ================================================================================================

// The public guys are the ones with a global scope. Those are the function names that will be
// called by the SLRT generated code
#define SG_MAKE_INT_FUNC_NAME_P(type, modName)  modName ## _ ## type ## _public
#define SG_INT_FUNC_NAME_P(type, modName)       SG_MAKE_INT_FUNC_NAME_P(type, modName)
#define SG_INT_START_FUNC_NAME_P                SG_INT_FUNC_NAME_P(start, SG_INT_PREFIX)
#define SG_INT_STOP_FUNC_NAME_P                 SG_INT_FUNC_NAME_P(stop, SG_INT_PREFIX)
#define SG_INT_ISR_FUNC_NAME_P                  SG_INT_FUNC_NAME_P(isr, SG_INT_PREFIX)
#define SG_INT_WAIT_FUNC_NAME_P                 SG_INT_FUNC_NAME_P(isr, SG_INT_PREFIX) //It's still called isr to maintain compatibility with QNX
#define SG_INT_MAP_FUNC_NAME_P                  SG_INT_FUNC_NAME_P(map, SG_INT_PREFIX)

// The non-public (aka private) guys are the one called BY the public functions
// They are declared static in the hookfile itself -> not visible on a global scope
#define SG_MAKE_INT_FUNC_NAME(type, modName)    modName ## _ ## type
#define SG_INT_FUNC_NAME(type, modName)         SG_MAKE_INT_FUNC_NAME(type, modName)
#define SG_INT_START_FUNC_NAME                  SG_INT_FUNC_NAME(start, SG_INT_PREFIX)
#define SG_INT_STOP_FUNC_NAME                   SG_INT_FUNC_NAME(stop, SG_INT_PREFIX)
#define SG_INT_ISR_FUNC_NAME                    SG_INT_FUNC_NAME(isr, SG_INT_PREFIX)
#define SG_INT_MAP_FUNC_NAME                    SG_INT_FUNC_NAME(map, SG_INT_PREFIX)

// And that guy is used for the device name in sg_findPciDevice
#define STR_VALUE_ADD_SPEEDGOAT(arg)    "Speedgoat " arg
#define SG_MAKE_DEVNAME_TYPE(modName)   STR_VALUE_ADD_SPEEDGOAT(SG_INT_ ## modName ## _DEVNAME)
#define SG_DEVNAME_TYPE(modName)        SG_MAKE_DEVNAME_TYPE(modName)
#define SG_GET_DEVNAME                  SG_DEVNAME_TYPE(SG_INT_PREFIX)

// End of macro magic
// ================================================================================================

// The following 3 macros will be used in the hook files themselves to declare the hook functions
#define SG_INT_START_FUNC   static void SG_INT_START_FUNC_NAME(void* context)
#define SG_INT_STOP_FUNC    static void SG_INT_STOP_FUNC_NAME(void* context)
#define SG_INT_ISR_FUNC     static int SG_INT_ISR_FUNC_NAME(void* context)

//Return defines for isr function
#define SG_DROP_ISR 0
#define SG_RUN_ISR 1
#define SG_OVERLOAD_ISR 2

// Use these macros to access the BARs
#define SG_INT_NUM_BARS             (sizeof(SG_INT_BARS) / sizeof(SG_INT_BARS[0]))
#define SG_INT_MAPPED_BAR(barNr)    ((uintptr_t)((sg_InterruptContext*)context)->map[barNr])

// Use this macro if you need the axiDevice in your subroutine, to avoid obfuscation problems
#define SG_INT_GET_AXI_DEVICE (((sg_InterruptContext*)context)->axiDevice)

// Use this macro to access the interrupt channel in your hook function
#define SG_INT_INTERRUPT_CHANNEL (((sg_InterruptContext*)context)->interruptChannel)

// Use this macro to access the module ID in your hook function
#define SG_INT_MODULE_ID (((sg_InterruptContext*)context)->moduleId)

// Use this macro to store/retrieve custom data in your hook function
// (Just a pointer, you need to malloc the memory yourself)
#define SG_INT_CUSTOM_DATA (((sg_InterruptContext*)context)->customData)

// Use this macro to determine if you're executing in polling mode, or interrupt mode.
#define SG_INT_IS_POLLING (((sg_InterruptContext*)context)->is_polling)

// Check to make sure the name of the AXI device has been defined in the file adding this header:
// SG_AXI_DEVICE_NAME should match the value in the device tree.
#ifndef SG_AXI_DEVICE_NAME
#error "SG_AXI_DEVICE_NAME must be defined in the file including sg_interrupt_config_axi.h"
#endif

// Declare interrupt hook functions
SG_INT_START_FUNC;
SG_INT_STOP_FUNC;
SG_INT_ISR_FUNC;

#include <unistd.h>
#include <stdbool.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/select.h>
#include <time.h>
#include "sg_axi.h"

//Helpers (see below)
static int enable_ints(sg_InterruptContext* context);
static int disable_ints(sg_InterruptContext* context);

#ifdef SG_LEGACY_LINUX_ENABLE
#include "sg_interrupt_config_axi_legacy.h"
#else
int SG_INT_MAP_FUNC_NAME_P(void** contextOut, uint32_t *data)
{
    uint32_t moduleId = data[1];
    sg_InterruptContext *context = (sg_InterruptContext*)malloc(sizeof(sg_InterruptContext));
    *contextOut = (void*)context;
    context->is_polling = (bool)data[2];
    context->priority = data[3];
    context->isModelTrigger = (bool)data[4];
    context->defaultPriority = 50; // Default SCHED_FIFO priority

    SG_PRINTF(DEBUG, "AXI INT MAP -> Running in %s mode\n", context->is_polling ? "polling" : "IRQ");

    // Extract all information from module ID parameter
    // (TODO: In Linux, we have an unlimited array of data available. Not in QNX though...)
    //  Byte 3: FPGA interrupt channel
    //  Byte 2: Not used
    //  Byte 1: Not used
    //  Byte 0: Actual module ID
    SG_PRINTF(DEBUG, "AXI INT MAP -> Original (extended) module ID 0x%08X\n", moduleId);
    context->interruptChannel = (moduleId >> 24) & 0xFF;
    moduleId &= 0xFF;
    context->moduleId = moduleId;
    context->customData = NULL;

    // Find AXI device
    SG_PRINTF(DEBUG, "AXI INT MAP -> Searching for AXI device %s\n", SG_AXI_DEVICE_NAME);
    if (sg_findAxiDevice(&context->axiDevice, SG_AXI_DEVICE_NAME) != 0)
    {
        SG_PRINTF(DEBUG, "AXI INT MAP -> Error searching for %s\n", SG_AXI_DEVICE_NAME);
        SG_PRINTF(ERROR, "%s\n", pSgErrorStr);
        return -1;
    }
    SG_PRINTF(DEBUG, "AXI INT MAP -> Found AXI device ID %d on %s\n", moduleId,
        context->axiDevice.uioDevPath);

    // Map memory
    for (int i = 0; i < SG_INT_NUM_BARS; i++)
    {
        int barNum = SG_INT_BARS[i];
        context->map[barNum] = sg_mapAxiBar(&context->axiDevice, barNum);
        if (context->map[barNum] == NULL)
        {
            SG_PRINTF(ERROR, "AXI INT MAP -> Failed to map BAR %d (idx %d): %s\n", barNum, i,
                pSgErrorStr);
            return -1;
        }
        SG_PRINTF(DEBUG, "AXI INT MAP -> Mapped BAR %d of device -> 0x%p\n", barNum,
            context->map[barNum]);
    }

    // Open the device providing interrupt enable, disable and event count.
    SG_PRINTF(DEBUG, "AXI INT MAP -> Opening UIO device %s\n", context->axiDevice.uioDevPath);
    context->uiofd = open(context->axiDevice.uioDevPath, O_RDWR);
    if (context->uiofd < 0)
    {
        SG_PRINTF(ERROR, "AXI INT MAP -> Failed to open %s: %s\n", context->axiDevice.uioDevPath,
            strerror(errno));
        return -errno;
    }
    SG_PRINTF(DEBUG, "AXI INT MAP -> UIO fd: %d\n", context->uiofd);

    // Disable interrupts to begin with.
    if (disable_ints(context))
    {
        SG_PRINTF(ERROR, "AXI INT MAP -> Failed to disable interrupts: %s\n", strerror(errno));
        return -errno;
    }
    
    context->axi_device_name = SG_AXI_DEVICE_NAME;
    context->irq_cpu_assigned = -1;

    if (context->isModelTrigger) 
    {
        context->irq_cpu_assigned = 1; // Base rate always on CPU 1, already correctly pinned, no difference between polling/irq mode
    }
    else
    {
        // ASYNC IRQ Mode
        if(!context->is_polling)
        {
            context->irq_cpu_assigned = sg_pickNextAsyncCpu();
            if(context->priority > 90) // Base rate priority is 90, so we only start pinning if above that. This may still cause issues with async polling.
            {
                if(context->irq_cpu_assigned < 0)
                {
                    SG_PRINTF(ERROR, "AXI INT MAP -> Shouldn't get here!\n");
                    return -ENOSYS;
                }
                SG_PRINTF(DEBUG, "AXI INT MAP -> Pinning AXI interrupt user space thread to CPU %d\n", context->irq_cpu_assigned);
                if (sg_pinThisThreadToCpu(context->irq_cpu_assigned) != 0) {
                    // No need for a warning. We may, or may not use threading.
                    SG_PRINTF(WARNING, "Failed to pin thread to CPU %d: %s\n",
                            context->irq_cpu_assigned, strerror(errno));
                }
            }
        }
        // Hidden asynchronous polling mode - get a CPU and force other threads off.
        if(context->is_polling)
        {
            context->irq_cpu_assigned = sg_pickNextAsyncCpu();
            if(context->irq_cpu_assigned < 0)
            {
                SG_PRINTF(ERROR, "AXI INT MAP -> Should never be here!\n");
                return -ENOSYS;
            }
            if(sg_pinThreadExclusiveCpu(context->irq_cpu_assigned) != 0)
            {
                SG_PRINTF(ERROR, "AXI INT MAP -> Failed to pin async polling thread to CPU %d.\n",
                        context->irq_cpu_assigned);
                SG_PRINTF(ERROR, "AXI INT MAP -> Asynchronous polling mode not recommended.\n");
                return -ENOSYS;
            }
        }
    }

    if((!context->is_polling) && (context->irq_cpu_assigned >= 0))
    {
        SG_PRINTF(DEBUG, "AXI INT MAP -> Setting AXI IRQ affinity for %s to CPU %d\n",
            SG_AXI_DEVICE_NAME, context->irq_cpu_assigned);
        if(sg_setAxiIrqAffinity(SG_AXI_DEVICE_NAME, context->irq_cpu_assigned) != 0)
        {
            SG_PRINTF(WARNING, "AXI INT MAP -> Failed to set AXI IRQ affinity: %s\n",
                pSgErrorStr);
        }
    }
    return 0;
}

int SG_INT_START_FUNC_NAME_P(sg_InterruptContext* context)
{
    context->intCount = 0;
    context->noIntCount = 0;
    context->overloadCheckEnabled = true;

    if (!context->is_polling) {
        if (enable_ints(context)) {
            return -errno;
        }
    }

    SG_INT_START_FUNC_NAME(context);

    SG_PRINTF(DEBUG, "Model Started\n");

    return 0;
}

int SG_INT_WAIT_FUNC_NAME_P(sg_InterruptContext* context)
{
    int result;

    bool check_overload = context->overloadCheckEnabled;

    // Check for overload condition. An overload condition is defined as the interrupt
    // already being present when we enter the wait function the first time after either start, 
    // or the last time the ISR was run.
    if (check_overload)
    {
        result = SG_INT_ISR_FUNC_NAME(context);
        context->overloadCheckEnabled = false; // Only check once per start/ISR
        if (result == SG_RUN_ISR){
            context->overloadCheckEnabled = true; // Re-enable for next wait call.
            // We can only really detect if at least one overload occurred at a time. Therefore,
            // always return 2, signaling an overload condition.
            return SG_OVERLOAD_ISR; // Signal overload to caller.
        }
    }

    if(context->is_polling)
        // In polling mode, we keep calling the evaluation function directly
        result = SG_INT_ISR_FUNC_NAME(context);
    else
    {
        // In interrupt mode, we read in a blocking fashion from the UIO file to detect an interrupt.
        // We need a timeout so conditions like tg.stop can be detected.
        // So we use select to watch the file descriptor

        int icount;

        //Wait for interrupt
        //Initialize select parameters: Set of file descriptors to watch
        fd_set select_read_fds;
        FD_ZERO(&select_read_fds);
        FD_SET(context->uiofd, &select_read_fds);
        //Timeout at 100ms
        struct timeval select_tv;
        select_tv.tv_sec = 0;
        select_tv.tv_usec = 100 * 1000;
        //Select call blocks until timeout or interrupt occurred
        int err = select(context->uiofd + 1, &select_read_fds, NULL, NULL, &select_tv);
        if(err == -1)
        {
            if(errno == EINTR)
                return SG_DROP_ISR;

            perror("select:");
            return -errno;
        }
        else if(!err)
            //Timeout expired. Pass the handle back to slrealtime.
            // Will come back here if no special conditions occurred.
            return SG_DROP_ISR;

        //Verify reading file descriptor
        err = read(context->uiofd, &icount, 4);
        if (err != 4) {
            perror("uio read:");
            return -errno;
        }

        //Our module-specific ISR will determine if it actually was our interrupt
        result = SG_INT_ISR_FUNC_NAME(context);

        //Re-enable interrupts
        if(enable_ints(context))
            return -errno;
    }

    //Evaluate & return
    if (result){
        context->overloadCheckEnabled = true;
        context->intCount++;
    }
    else{
        context->noIntCount++;
    }
    return result;
}

int SG_INT_STOP_FUNC_NAME_P(sg_InterruptContext* context)
{
    SG_INT_STOP_FUNC_NAME(context);

    SG_PRINTF(DEBUG, "INT STOP\n");
    SG_PRINTF(DEBUG, "\t%d interrupts received from board\n", context->intCount);
    SG_PRINTF(DEBUG, "\t%d other interrupts received\n", context->noIntCount);

    close(context->uiofd);

    return 0;
}

#endif // SG_LEGACY_LINUX_ENABLE

// UIO disables interrupts until we get to handle the last one. Re-enable
static int enable_ints(sg_InterruptContext* context)
{
    int reenable = 1;
    // Writing a "1" to the file descriptor will re-enable the interrupt
    int ret = write(context->uiofd, (void *)&reenable, sizeof(int));
    if (ret != sizeof(int))
    {
        return -errno;
    }
    return 0;
}

static int disable_ints(sg_InterruptContext* context)
{
    int disable = 0;
    // Writing a "0" to the file descriptor will disable the interrupt
    int ret = write(context->uiofd, (void *)&disable, sizeof(int));
    if (ret != sizeof(int))
    {
        return -errno;
    }
    return 0;
}

#ifdef __cplusplus
}
#endif

#endif // SG_INTERRUPT_CONFIG_AXI_H_
