
#ifndef SG_INTERRUPT_CONFIG_LINUX_LEGACY_H_
#define SG_INTERRUPT_CONFIG_LINUX_LEGACY_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <unistd.h>
#include <stdbool.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/select.h>
#include <semaphore.h>

#include "sg_uio.h"
#include <time.h>

static int enable_ints(sg_InterruptContext* context);

int SG_INT_MAP_FUNC_NAME_P(void** contextOut, uint32_t *data)
{
    int bus, slot;
    uint32_t moduleId = data[1];
    sg_InterruptContext *context = (sg_InterruptContext*)malloc(sizeof(sg_InterruptContext));
    *contextOut = (void*)context;
    context->is_polling = (bool)data[2];
    context->priority = data[3];
    context->isModelTrigger = (bool)data[4];
    context->is_first_wait_call = true;
    context->waiting_for_start = true;

    sem_init(&context->start_func_finished_sem, 0, 0);
    sem_init(&context->wait_func_ready_sem, 0, 0);
    //data[0] = length of data
    //data[3...N] = user data

    SG_PRINTF(DEBUG, "INT MAP -> Running in %s mode\n", context->is_polling ? "polling" : "IRQ");

    // Extract all information from module ID parameter
    // (TODO: In Linux, we have an unlimited array of data available. Not in QNX though...)
    //  Byte 3: FPGA interrupt channel
    //  Byte 2: PCI Slot
    //  Byte 1: PCI Bus
    //  Byte 0: Actual module ID
    SG_PRINTF(DEBUG, "INT MAP -> Original (extended) module ID 0x%08X\n", moduleId);
    context->interruptChannel = (moduleId >> 24) & 0xFF;
    slot = (int)(int8_t)((moduleId >> 16) & 0xFF);
    bus = (int)(int8_t)((moduleId >> 8) & 0xFF);
    moduleId &= 0xFF;
    context->moduleId = moduleId;
    context->customData = NULL;
    context->sg_int_fix.requested_by_user = 0;

    // Find PCI device
#ifdef SG_INT_CUSTOM_FIND_PCI_FUNCTION
    //Let the user look for the PCI device themselves
    SG_PRINTF(DEBUG, "Custom find PCI device function: 0x%p\n", SG_INT_CUSTOM_FIND_PCI_FUNCTION);
    int res = SG_INT_CUSTOM_FIND_PCI_FUNCTION(&context->pciInfo, moduleId, bus, slot);
    SG_PRINTF(DEBUG, "Custom find PCI device function - result: %d\n", res);
    if(res)
        return res;
#else
    //Default implementation (used by most)
    if (sg_findPciDevice(&context->pciInfo, SG_GET_DEVNAME, SG_GET_VID, SG_GET_DID, SG_GET_SUBVID,
            SG_GET_SUBDID, moduleId, bus, slot) != 0)
    {
        SG_PRINTF(ERROR, "%s\n", pSgErrorStr);
        return (uint32_t)-1;
    }
#endif //SG_INT_CUSTOM_FIND_PCI_FUNCTION
    SG_PRINTF(DEBUG, "INT MAP -> Found PCI device ID %d on bus %d slot %d\n", moduleId,
        context->pciInfo.bus, context->pciInfo.slot);

    // Map memory
    for (int barIdx = 0; barIdx < SG_INT_NUM_BARS; barIdx++)
    {
        context->map[barIdx] = sg_mapMemory(&context->pciInfo, SG_INT_BARS[barIdx]);
        if (context->map[barIdx] == NULL)
        {
            SG_PRINTF(ERROR, "INT MAP -> Failed to map BAR %d (idx %d): 0x%08X (%s)\n",
                SG_INT_BARS[barIdx], barIdx, errno, strerror(errno));
            return -errno;
        }
        SG_PRINTF(DEBUG, "INT MAP -> Mapped BAR %d of device -> 0x%p\n", SG_INT_BARS[barIdx],
            context->pciInfo.VirtAddress[SG_INT_BARS[barIdx]]);
    }

    //For interrupt mode - Set up the UIO framework to receive interrupts in user space
    //For polling mode - we don't need UIO
    if(!context->is_polling)
    {
        //Make UIO take ownership of our interrupt device
        context->uioIndex = sg_uio_bindDeviceToUio(&context->pciInfo);
        if (context->uioIndex < 0) {
            SG_PRINTF(ERROR, "INT MAP -> Failed to bind UIO device: %s\n", strerror(errno));
            return -errno;
        }

        //UIO fd will be read to detect interrupts: read call blocks until interrupts occur
        char devname[20];
        sprintf(devname, "/dev/uio%d", context->uioIndex);
        context->uiofd = open(devname, O_RDWR);
        if (context->uiofd < 0)
        {
            SG_PRINTF(ERROR, "INT MAP -> Failed to open UIO device %s: %s\n", devname, strerror(errno));
            return -errno;
        }
        SG_PRINTF(DEBUG, "INT MAP -> UIO fd: %d\n", context->uiofd);

        SG_PRINTF(DEBUG, "INT MAP -> isModelTrigger: %d\n", context->isModelTrigger);
        SG_PRINTF(DEBUG, "INT MAP -> IRQ priority: %d\n", context->priority);
        // Need to sleep here briefly to allow the UIO driver to set up its IRQ thread
        // Otherwise we read back the default priority before it is changed and it gets
        // overridden to the default again (on the first load of the sg_uio module)
        usleep(100000); //100ms
        if (sg_uio_setIrqProps(context) != 0) {
            SG_PRINTF(WARNING, "%s\n", pSgErrorStr);
        }
    }
    // Config fd will be used to enable interrupts
    context->configfd = sg_pci_openPciConfig(&context->pciInfo, O_RDWR);
    if (context->configfd < 0)
    {
        SG_PRINTF(ERROR, "INT MAP -> Failed to open PCI configuration: %s\n", strerror(errno));
        return -errno;
    }
    SG_PRINTF(DEBUG, "INT MAP -> Config file fd: %d\n", context->configfd);

    // Get original state of the command register in config space (upper byte)
    #define INT_DISABLE_BIT_MASK 0x4
    int err = pread(context->configfd, &context->command_high, 1, 5);
    if (err != 1)
    {
        SG_PRINTF(ERROR, "INT MAP -> Failed to read upper command byte: %s\n", strerror(errno));
        return -errno;
    }
    // Disable interrupts for a start.
    // In Polling Mode, we don't want to emit an actual interrupt.
    // In Interrupt Mode, we will enable interrupts in the _start() function
    context->command_high |= INT_DISABLE_BIT_MASK;
    err = pwrite(context->configfd, &context->command_high, 1, 5);
    if (err != 1)
    {
        SG_PRINTF(ERROR, "INT MAP -> Failed to write upper command byte: %s\n", strerror(errno));
        return -errno;
    }
    // Store value with Disable bit cleared. Will be used to enable interrupts
    context->command_high &= ~INT_DISABLE_BIT_MASK;
    SG_PRINTF(DEBUG, "INT MAP -> Upper command byte (enabled): %d\n", context->command_high);

    return 0;
}

int SG_INT_START_FUNC_NAME_P(sg_InterruptContext* context)
{
    context->intCount = 0;
    context->noIntCount = 0;

    SG_PRINTF(DEBUG, "INT START ready\n");

    //Don't actually do stuff until the baserate is ready (SG_INT_WAIT_FUNC_NAME_P gets called)

    sem_wait(&context->wait_func_ready_sem);

    SG_PRINTF(DEBUG, "INT START go\n");

    if(!context->is_polling)
        if(enable_ints(context))
            return -errno;

    SG_INT_START_FUNC_NAME(context);
    
    sem_post(&context->start_func_finished_sem);
    SG_PRINTF(DEBUG, "Model Started\n");

    return 0;
}

int SG_INT_WAIT_FUNC_NAME_P(sg_InterruptContext* context)
{
    int result;

    if(context->waiting_for_start)
    {
        if(!context->is_polling && context->is_first_wait_call)
        {
            if((context->priority > 90) && (context->isModelTrigger==0)) // Base rate priority is 90, so we only start pinning if above that. Base rate is always on CPU 1.
            {
                // Pin the thread to the assigned CPU
                SG_PRINTF(DEBUG, "INT WAIT -> Pinning interrupt user space thread to CPU %d\n", context->irq_cpu_assigned);

                if(context->irq_cpu_assigned >= 0) // If there are only two cores, there will be no IRQ assignment.
                {
                    if (sg_pinThisThreadToCpu(context->irq_cpu_assigned) != 0) {
                        SG_PRINTF(WARNING, "Failed to pin thread to CPU %d: %s\n",
                                context->irq_cpu_assigned, strerror(errno));
                    }
                }
            }
            context->is_first_wait_call = false;
        }
        // Signal to start function that the thread is prepared.
        sem_post(&context->wait_func_ready_sem);
        SG_PRINTF(DEBUG, "INT WAIT First call\n");

        // Don't actually do stuff until SG_INT_START_FUNC_NAME_P has been executed
        struct timespec ts;
        clock_gettime(CLOCK_REALTIME, &ts);
        long add_ns = 100 * 1000;          // 100 microseconds = 100,000 ns
        // Normalize timespec
        ts.tv_nsec += add_ns;
        if (ts.tv_nsec >= 1000000000L) {
            ts.tv_sec += ts.tv_nsec / 1000000000L;
            ts.tv_nsec = ts.tv_nsec % 1000000000L;
        }
        if(sem_timedwait(&context->start_func_finished_sem, &ts) != 0)
        {
            return SG_DROP_ISR;
        }

        context->waiting_for_start = false;
    }

    if(!context->isModelTrigger)
    {
        // Wait for base rate synchronization
        // Would deadlock if we are the base rate ourselves
        if(sg_waitForBaseRateSync())
        {
            return SG_DROP_ISR;
        }
    }

    if(context->is_polling)
        // In polling mode, we keep calling the evaluation function directly
        result = SG_INT_ISR_FUNC_NAME(context);
    else
    {
        // In interrupt mode, we blockingly read from the UIO file to detect an interrupt.
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
            if(errno != EINTR)
                SG_PRINTF(WARNING, "INT WAIT: select error: %s\n", strerror(errno));
            return SG_DROP_ISR;
        }
        else if(!err)
            //Timeout expired. Pass the handle back to slrealtime.
            // Will come back here if no special conditions occurred.
            return SG_DROP_ISR;

        //Verify reading file descriptor
        err = read(context->uiofd, &icount, 4);
        if (err != 4) {
            SG_PRINTF(WARNING, "INT WAIT: read error: %s\n", strerror(errno));
            context->noIntCount++;
            return SG_DROP_ISR;
        }

        //Our module-specific ISR will determine if it actually was our interrupt
        result = SG_INT_ISR_FUNC_NAME(context);

        //Re-enable interrupts
        if(enable_ints(context)){
            context->noIntCount++;
            return SG_DROP_ISR;
        }
    }

    //Evaluate & return
    if (result)
        context->intCount++;
    else
        context->noIntCount++;
    return result;
}

int SG_INT_STOP_FUNC_NAME_P(sg_InterruptContext* context)
{

    SG_INT_STOP_FUNC_NAME(context);

    SG_PRINTF(DEBUG, "INT STOP\n");
    SG_PRINTF(DEBUG, "%d interrupts received from board\n", context->intCount);
    SG_PRINTF(DEBUG, "%d other interrupts received\n", context->noIntCount);

    // Closing the file descriptors will cause UIO to close the module
    close(context->configfd);
    close(context->uiofd);

    // Return the IRQ thread priority back to normal
    // setting this to 50 returns it to the default SCHED_FIFO priority
    // Interestingly htop always shows realtime priorities as -(priority_set + 1)
    if (context->is_polling == false){
        context->defaultPriority = 50;
        if(sg_uio_resetIrqProps(context)){
            SG_PRINTF(WARNING, "Failed to demote IRQ thread priority: %s\n", pSgErrorStr);
        }
    }

    return 0;
}

// UIO disables interrupts until we get to handle the last one. Re-enable
static int enable_ints(sg_InterruptContext* context)
{
    if(context->sg_int_fix.requested_by_user)
    {
        if(context->sg_int_fix.target_register != NULL)
            *context->sg_int_fix.target_register = context->sg_int_fix.int_mask ;
    }
    else
    {
        int err = pwrite(context->configfd, &context->command_high, 1, 5);
        if (err != 1)
        {
            SG_PRINTF(ERROR, "INT EN - Failed to write config file: %s\n", strerror(err));
            return -errno;
        }
    }
    return 0;
}

static int _sg_int_enable_fix(sg_InterruptContext* context,
    volatile uint32_t* target_register, uint32_t int_mask, uint32_t fix_type)
{
    // Fixes only apply when running in External Interrupt Mode. External Polling Mode does not
    // employ the uio_speedgoat kernel module, so no fixes and we return 0.
    if (context->is_polling)
        return 0;

    context->sg_int_fix.requested_by_user = true;
    context->sg_int_fix.int_mask = int_mask;
    context->sg_int_fix.target_register = target_register;

    int err = pwrite(context->uiofd, &fix_type, 4, 0);
    if (err != 4)
    {
        SG_PRINTF(ERROR, "Failed to enable Speedgoat interrupt fix: %s\n", strerror(errno));
        return -errno;
    }

    err = pwrite(context->uiofd, &context->sg_int_fix.int_mask, 4, 0);
    if (err != 4)
    {
        SG_PRINTF(ERROR, "Failed to write Speedgoat interrupt fix int mask: %s\n", strerror(errno));
        return -errno;
    }
    return 0;
}

#ifdef __cplusplus
}
#endif

#endif // SG_INTERRUPT_CONFIG_LINUX_LEGACY_H_
