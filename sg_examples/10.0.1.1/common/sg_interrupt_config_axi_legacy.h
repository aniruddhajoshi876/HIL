#ifndef SG_INTERRUPT_CONFIG_AXI_LEGACY_H_
#define SG_INTERRUPT_CONFIG_AXI_LEGACY_H_

#ifdef __cplusplus
extern "C"
{
#endif

int SG_INT_MAP_FUNC_NAME_P(void** contextOut, uint32_t *data)
{
    uint32_t moduleId = data[1];
    sg_InterruptContext *context = (sg_InterruptContext*)malloc(sizeof(sg_InterruptContext));
    *contextOut = (void*)context;
    context->is_polling = (bool)data[2];
    context->priority = data[3];
    context->isModelTrigger = (bool)data[4];
    context->is_first_wait_call = true;
    context->waiting_for_start = true;
    context->defaultPriority = 50; // Default SCHED_FIFO priority

    sem_init(&context->start_func_finished_sem, 0, 0);
    sem_init(&context->wait_func_ready_sem, 0, 0);

    SG_PRINTF(DEBUG, "INT MAP -> Running in %s mode\n", context->is_polling ? "polling" : "IRQ");

    // Extract all information from module ID parameter
    // (TODO: In Linux, we have an unlimited array of data available. Not in QNX though...)
    //  Byte 3: FPGA interrupt channel
    //  Byte 2: Not used
    //  Byte 1: Not used
    //  Byte 0: Actual module ID
    SG_PRINTF(DEBUG, "INT MAP -> Original (extended) module ID 0x%08X\n", moduleId);
    context->interruptChannel = (moduleId >> 24) & 0xFF;
    moduleId &= 0xFF;
    context->moduleId = moduleId;
    context->customData = NULL;

    // Find AXI device
    SG_PRINTF(DEBUG, "INT MAP -> Searching for AXI device %s\n", SG_AXI_DEVICE_NAME);
    if (sg_findAxiDevice(&context->axiDevice, SG_AXI_DEVICE_NAME) != 0)
    {
        SG_PRINTF(DEBUG, "INT MAP -> Error searching for %s\n", SG_AXI_DEVICE_NAME);
        SG_PRINTF(ERROR, "%s\n", pSgErrorStr);
        return -1;
    }
    SG_PRINTF(DEBUG, "INT MAP -> Found AXI device ID %d on %s\n", moduleId,
        context->axiDevice.uioDevPath);

    // Map memory
    for (int i = 0; i < SG_INT_NUM_BARS; i++)
    {
        int barNum = SG_INT_BARS[i];
        context->map[barNum] = sg_mapAxiBar(&context->axiDevice, barNum);
        if (context->map[barNum] == NULL)
        {
            SG_PRINTF(ERROR, "INT MAP -> Failed to map BAR %d (idx %d): %s\n", barNum, i,
                pSgErrorStr);
            return -1;
        }
        SG_PRINTF(DEBUG, "INT MAP -> Mapped BAR %d of device -> 0x%p\n", barNum,
            context->map[barNum]);
    }

    // Open the device providing interrupt enable, disable and event count.
    SG_PRINTF(DEBUG, "INT MAP -> Opening UIO device %s\n", context->axiDevice.uioDevPath);
    context->uiofd = open(context->axiDevice.uioDevPath, O_RDWR);
    if (context->uiofd < 0)
    {
        SG_PRINTF(ERROR, "INT MAP -> Failed to open %s: %s\n", context->axiDevice.uioDevPath,
            strerror(errno));
        return -errno;
    }
    SG_PRINTF(DEBUG, "INT MAP -> UIO fd: %d\n", context->uiofd);

    // Disable interrupts to begin with.
    if (disable_ints(context))
    {
        SG_PRINTF(ERROR, "INT MAP -> Failed to disable interrupts: %s\n", strerror(errno));
        return -errno;
    }

    int priority = context->priority;
    priority++; // One higher than what the user specified
    if(priority > 99) priority = 99;
    if(context->isModelTrigger) priority = 90; // Equal to base rate priority
    SG_PRINTF(DEBUG, "INT MAP -> IRQ priority: %d\n", priority);

    return 0;
}

int SG_INT_START_FUNC_NAME_P(sg_InterruptContext* context)
{
    context->intCount = 0;
    context->noIntCount = 0;

    SG_PRINTF(DEBUG, "INT START - READY\n");

   //Don't actually do stuff until the baserate is ready (SG_INT_WAIT_FUNC_NAME_P gets called)

    sem_wait(&context->wait_func_ready_sem);

    SG_PRINTF(DEBUG, "INT START - EXECUTE\n");

    if (!context->is_polling) {
        if (enable_ints(context)) {
            return -errno;
        }
    }

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
                        // No need for a warning. We may, or may not use threading.
                        SG_PRINTF(WARNING, "Failed to pin thread to CPU %d: %s\n",
                                context->irq_cpu_assigned, strerror(errno));
                    }
                }
            }
            context->is_first_wait_call = false;
        }
        // Signal to start function that the thread is prepared.
        sem_post(&context->wait_func_ready_sem);
        SG_PRINTF(DEBUG, "INT WAIT Waiting for start to be finished\n");

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
    // SG_PRINTF(DEBUG, "INT WAIT Waiting for base rate.\n");   //Note: This is printed in every wait call (very often), so it can be very verbose. Uncomment for debugging purposes.

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
    SG_PRINTF(DEBUG, "\t%d interrupts received from board\n", context->intCount);
    SG_PRINTF(DEBUG, "\t%d other interrupts received\n", context->noIntCount);

    close(context->uiofd);

    return 0;
}

#ifdef __cplusplus
}
#endif

#endif // SG_INTERRUPT_CONFIG_AXI_LEGACY_H_
