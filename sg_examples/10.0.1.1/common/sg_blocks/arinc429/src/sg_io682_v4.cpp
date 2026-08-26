#include "sg_io682_v4.h"

#include "cdev_api.h"
#include "sg_common.h"


struct Sg_ModuleInfo
{
    const char *name;
    uint16_t vendorId;
    uint16_t deviceId;
    uint16_t subvendorId;
    uint16_t subdeviceId;
};

static int getPciBaseAddresses(Sg_ModuleInfo *moduleInfo, const SgParam_IntVec *pciSlotParam,
    int moduleId, sg_PCIDevice *pciInfo, SgError *err);
static int findIo681(sg_PCIDevice *pciInfo, Sg_ModuleInfo *moduleInfo, int moduleId, int16_t pciBus,
    int16_t pciSlot);
static int setPciBaseAddresses(const Sg_ModuleInfo *moduleInfo, int boardId, sg_PCIDevice *pciInfo,
    SgError *err);

int io682_configPciAddresses(int deviceId,
                             const SgParam_IntVec *pciSlotParam,
                             int moduleId,
                             int boardId,
                             SgError *err)
{
    Sg_ModuleInfo moduleInfo;
    moduleInfo.name = "Speedgoat IO682";
    moduleInfo.vendorId = 0x13C6;   // Condor Engineering
    moduleInfo.deviceId = deviceId;
    moduleInfo.subvendorId = SG_NO_SUB;
    moduleInfo.subdeviceId = SG_NO_SUB;

    sg_PCIDevice pciInfo;
    if (getPciBaseAddresses(&moduleInfo, pciSlotParam, moduleId, &pciInfo, err))
    {
        return -1;
    }
    if (setPciBaseAddresses(&moduleInfo, boardId, &pciInfo, err))
    {
        return -1;
    }
    return 0;
}

int io682_initArincApi(int boardId, SgError *err)
{
    int result = arx30_loadslv(boardId, 0, 0, 0);
    if (result != ARS_NORMAL)
    {
        sgError_setMsg(err, "Failed to initialize API: %s", arx30_get_error(result));
        return -1;
    }
    return 0;
}

int io682_setConcurrencyMode(int boardId, SgError *err)
{
	//arx30_set_multithread_protect needed? or use arx30_set_device_config(,ARU_MULTITHREAD_PROTECT,) -> set by arx30_set_preload_config
    int result = arx30_set_preload_config(boardId, ARU_CONCURRENCY_MODE, AR_CONC_MULTITHRD);	//AR_CONC_NONE
    if (result != ARS_NORMAL)
    {
        sgError_setMsg(err, "Failed to set concurrency mode: %s", arx30_get_error(result));
        return -1;
    }
    return 0;
}

int io682_configChannels(SimStruct *S,int moduleId, SgError *err, const mxArray *sFcnParamInConfig, const mxArray *sFcnParamOutConfig)
{
    int16_t boardId = moduleId - 1;
	int nInCh=0;
	int nOutCh=0;
	int result;
	int16_t i,bitError,gapError;

	
	//SG_PRINTF(INFO, "In n=%d, m=%d\n", mxGetN(sFcnParamInConfig), mxGetM(sFcnParamInConfig));
	//SG_PRINTF(INFO, "Out n=%d, m=%d\n", mxGetN(sFcnParamOutConfig), mxGetM(sFcnParamOutConfig));
	nInCh = mxGetM(sFcnParamInConfig);
	nOutCh = mxGetM(sFcnParamOutConfig);
	
	for (i=0; i<nInCh;i++)
	{
		//SG_PRINTF(INFO, "In Rate %d, Buffer %d, Enable %d, Parity %d, Wrap %d\n",(uint16_t)mxGetPr(sFcnParamInConfig)[i],(uint16_t)mxGetPr(sFcnParamInConfig)[nInCh+i],(uint16_t)mxGetPr(sFcnParamInConfig)[2*nInCh+i],(uint16_t)mxGetPr(sFcnParamInConfig)[3*nInCh+i],(uint16_t)mxGetPr(sFcnParamInConfig)[4*nInCh+i]);
		result = arx30_set_device_config(boardId, i, ARU_RX_BITRATE, (int16_t)mxGetPr(sFcnParamInConfig)[i]);
		if (result != ARS_NORMAL)
		{
			break;
		}
		result = arx30_set_device_config(boardId, i, ARU_RX_MERGED_MODE, (int16_t)mxGetPr(sFcnParamInConfig)[nInCh+i]);
		if (result != ARS_NORMAL)
		{
			break;
		}
		result = arx30_set_device_config(boardId, i, ARU_RX_FIFO_ENABLE, (int16_t)mxGetPr(sFcnParamInConfig)[2*nInCh+i]);
		if (result != ARS_NORMAL)
		{
			break;
		}
		result = arx30_set_device_config(boardId, i, ARU_RX_PARITY, (int16_t)mxGetPr(sFcnParamInConfig)[3*nInCh+i]);
		if (result != ARS_NORMAL)
		{
			break;
		}
		result = arx30_set_device_config(boardId, i, ARU_RECV_MODE, (int16_t)mxGetPr(sFcnParamInConfig)[4*nInCh+i]);
		if (result != ARS_NORMAL)
		{
			break;
		}
	}
	if (result != ARS_NORMAL)
    {
        sgError_setMsg(err, "Failed to load input channel configuration: %s", arx30_get_error(result));
        return -1;
    }
	for (i=0; i<nOutCh;i++)
	{
		result = arx30_set_device_config(boardId, i, ARU_TX_BITRATE, (int16_t)mxGetPr(sFcnParamOutConfig)[i]);
		if (result != ARS_NORMAL)
		{
			break;
		}
		result = arx30_set_device_config(boardId, i, ARU_TX_PARITY, (int16_t)mxGetPr(sFcnParamOutConfig)[nOutCh+i]);
		if (result != ARS_NORMAL)
		{
			break;
		}
		switch((int16_t)mxGetPr(sFcnParamOutConfig)[2*nOutCh+i])
		{
			case PROT_ERROR_HI:
				bitError = 1; gapError = 8;
				break;
			case PROT_ERROR_LO:
				bitError = 0; gapError = 8;
				break;
			case PROT_ERROR_SHORT_GAP:
				bitError = 8; gapError = 7;
				break;
			case PROT_ERROR_NONE:
				bitError = 8; gapError = 8;
				break;
			default:
				sgError_setMsg(err, "Invalid Protocol Error selection");
				return -1;	
		}
		result = arx30_set_device_config(boardId, i, ARU_TX_BIT_ERROR, bitError);
		if (result != ARS_NORMAL)
		{
			break;
		}
		result = arx30_set_device_config(boardId, i, ARU_TX_GAP_ERROR, gapError);
		if (result != ARS_NORMAL)
		{
			break;
		}
		result = arx30_set_device_config(boardId, i, ARU_TX_FIFO_ENABLE, (int16_t)mxGetPr(sFcnParamOutConfig)[3*nOutCh+i]);
		if (result != ARS_NORMAL)
		{
			break;
		}
	}
	
    if (result != ARS_NORMAL)
    {
        sgError_setMsg(err, "Failed to load output channel configuration: %s", arx30_get_error(result));
        return -1;
    }
    return 0;
}

int io682_configScheduler(SimStruct *S,int moduleId, SgError *err, const mxArray *sFcnParamSchedMsg)
{
    int boardId = moduleId - 1;
	int nMsg=0;
	int i;
	int maxMsg = 1000;	//move to header
	AR_SCHEDULED_MSG_ENTRY_TYPE scheduledMessages[1000];	//use malloc to save mem

	
	//SG_PRINTF(INFO, "Sched n=%d, m=%d\n", mxGetN(sFcnParamSchedMsg), mxGetM(sFcnParamSchedMsg));
	nMsg = mxGetM(sFcnParamSchedMsg);
	
	if (nMsg > maxMsg)
	{
		sgError_setMsg(err, "Maximal number of scheduled messages is %d\n",maxMsg);
        return -1;
	}
	
	for (i=0;i<nMsg;i++)
	{
		//SG_PRINTF(INFO,"Ch %d, Rate %d, Offset %d, TxCnt %X, Data %X\n",(uint32_t)mxGetPr(sFcnParamSchedMsg)[i],(uint32_t)mxGetPr(sFcnParamSchedMsg)[nMsg+i],(uint32_t)mxGetPr(sFcnParamSchedMsg)[2*nMsg+i],(uint32_t)mxGetPr(sFcnParamSchedMsg)[3*nMsg+i],(uint32_t)mxGetPr(sFcnParamSchedMsg)[4*nMsg+i]);
		scheduledMessages[i].messageIndex = i;
		scheduledMessages[i].board = boardId;
		scheduledMessages[i].channel = (uint32_t)mxGetPr(sFcnParamSchedMsg)[i]-1;
		scheduledMessages[i].rate = (uint32_t)mxGetPr(sFcnParamSchedMsg)[nMsg+i];
		scheduledMessages[i].start = (uint32_t)mxGetPr(sFcnParamSchedMsg)[2*nMsg+i];
		scheduledMessages[i].txCount = (uint32_t)mxGetPr(sFcnParamSchedMsg)[3*nMsg+i];
		scheduledMessages[i].data = (uint32_t)mxGetPr(sFcnParamSchedMsg)[4*nMsg+i];
	}
	
	int result = arx30_define_msg_block (nMsg, scheduledMessages);
    if (result != ARS_NORMAL)
    {
        sgError_setMsg(err, "Failed to load scheduled messages: %s", arx30_get_error(result));
        return -1;
    }
    return 0;
}

int io682_setTimerRate(int boardId, int timeSource, int timerRate)
{
    // Use IRIG timer input to sync the 1us clock
    if (timeSource == 1)
    {
        arx30_set_config(boardId, ARU_RX_TIMETAG_MODE, AR_TIMETAG_EXT_IRIG_64BIT);
    }
    else // Use the CEI-x20 compatible timer
    {
        arx30_set_timerrate(boardId, timerRate);	//not really supported
    }
    return 0;
}

int io682_startDriver(int boardId, SgError *err)
{
    // Start the slave processor after all the configuration
    int result = arx30_go(boardId);
    if (result != ARS_NORMAL)
    {
        sgError_setMsg(err, "Failed to start I/O module: %s", arx30_get_error(result));
        return -1;
    }
    return 0;
}

static int getPciBaseAddresses(Sg_ModuleInfo *moduleInfo,
                               const SgParam_IntVec *pciSlotParam,
                               int moduleId,
                               sg_PCIDevice *pciInfo,
                               SgError *err)
{
    int16_t pciBus;
    int16_t pciSlot;

    // Get PCI bus and slot number
    if (pciSlotParam->len == 1)
    {
        pciBus = 0;
        pciSlot = pciSlotParam->val[0];
    }
    else
    {
        pciBus = pciSlotParam->val[0];
        pciSlot = pciSlotParam->val[1];
    }

    // Get PCI information
    if (sg_findPciDevice(pciInfo, moduleInfo->name, moduleInfo->vendorId, moduleInfo->deviceId,
            moduleInfo->subvendorId, moduleInfo->subdeviceId, moduleId, pciBus, pciSlot) != 0)
    {
        bool tryVariants = false;
        switch (moduleInfo->deviceId)   // Try the variants for 430 and 830
        {
            case 0x430:  // CEI-430A
                tryVariants = true;
                moduleInfo->deviceId = 0x430A;
                break;
            case 0x830:  // RCEI-830A
                tryVariants = true;
                moduleInfo->deviceId = 0x830A;
                break;
        }
        if (tryVariants)
        {
            if (sg_findPciDevice(pciInfo, moduleInfo->name, moduleInfo->vendorId,
                    moduleInfo->deviceId, moduleInfo->subvendorId, moduleInfo->subdeviceId,
                    moduleId, pciBus, pciSlot) != 0)
            {
                if (findIo681(pciInfo, moduleInfo, moduleId, pciBus, pciSlot) != 0)
                {
                    sgError_extractMsg(err, pSgErrorStr);
                    return -1;
                }
            }
        }
        else
        {
            if (findIo681(pciInfo, moduleInfo, moduleId, pciBus, pciSlot) != 0)
            {
                sgError_extractMsg(err, pSgErrorStr);
                return -1;
            }
        }
    }
    return 0;
}

// This function is kind of a hack because the IO682 blocks should work with the IO681, but we don't
// have the time to integrate it nicely (the I/O module is only used by one customer).
static int findIo681(sg_PCIDevice *pciInfo,
                     Sg_ModuleInfo *moduleInfo,
                     int moduleId,
                     int16_t pciBus,
                     int16_t pciSlot)
{
    // If the Simulink block said it is an IO682 (0x830A) but we couldn't find it, then try if it's
    // actually an IO681 (0x0530)
    if (moduleInfo->deviceId == 0x830A)
    {
        moduleInfo->deviceId = 0x0530;
        return sg_findPciDevice(pciInfo, moduleInfo->name, moduleInfo->vendorId,
            moduleInfo->deviceId, moduleInfo->subvendorId, moduleInfo->subdeviceId, moduleId,
            pciBus, pciSlot);
    }
    else
    {
        return -1;
    }
}

static int setPciBaseAddresses(const Sg_ModuleInfo *moduleInfo,
                               int boardId,
                               sg_PCIDevice *pciInfo,
                               SgError *err)
{
    // Map the PCI memory address regions
    uintptr_t bar0Addr = (uintptr_t)sg_mapMemory(pciInfo, 0);
    uintptr_t bar2Addr = (uintptr_t)sg_mapMemory(pciInfo, 2);

    int result = arx30_set_base_addresses(boardId, bar0Addr, bar2Addr, moduleInfo->vendorId,
        moduleInfo->deviceId);
    if (result == ARS_INVBOARD)
    {
        sgError_setMsg(err, "Could not set PCI base addresses: %s", arx30_get_error(result));
        return -1;
    }
    return 0;
}
