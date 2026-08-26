/*
*   Files      : sg_IO601_fcn.c / sg_IO601_fcn.h
*   Descirption: This file includes all necessary functions for the IO601 CAN and LIN driver.
*   Version    : $Revison$
*   Author     : $Author$
*   Date       : $Date$

*/

#ifdef MATLAB_MEX_FILE

#include "mex.h"

void mexFunction(int nlhs, mxArray *plhs[],
                 int nrhs, const mxArray *prhs[])
{
    // Dummy function, only for the mex-process.
}

#endif // _MYMEXFLAG

#ifndef MATLAB_MEX_FILE

#pragma region Inlcude


#ifdef __cplusplus
extern "C"
{
#endif
#include "sg_IO601_fcn.h"
////#include "..\..\common\libsg\sg_common.h"
#ifdef __cplusplus
}
#endif


////#if _MSC_VER > 1600
////#include "iConcurrentExecution.h"
#include "sg_printf.h"
////#endif

#pragma endregion

#pragma region Global

/*
    Pointer to the I/O module data.
*/
sg_IO601_Module_T *sg_IO601_pModule = NULL;

/*
    Counter of active I/O-Modules in the model.
*/
uint32_T sg_IO601_ModuleCounter = 0;

#pragma endregion

#pragma region Forward-Declaration

void CleanupSetupBlock();
void CleanupCANPort();
void CleanupBackgroundTask();
void IO601_LINRstSndMsgInRecQueue(uint32_T modIdx);
void IO601_ChkErrMsg(uint32_T modIdx);

boolean_T IO601_SetGlbSndRec(uint32_T modIdx);
boolean_T IO601_LINWrtMsg(uint32_T modIdx, uint8_T protID);
boolean_T IO601_LINSlvWrtMsgBuf(uint32_T modIdx, uint8_T protID);

uint8_T CheckSum(uint32_T modIdx, uint8_T protID);
uint8_T IO601_FndGlbSender(uint32_T modIdx);
uint8_T IO601_FndGlbReceiver(uint32_T modIdx);


uint8_T IO601_CANPrepareCANQueueEntry(canMsg *pMessage, volatile CAN_QUEUEENTRY *pQueue);
uint32_T IO601_CANWriteFIFO(uintptr_t queueEntryAddress, canMsg *pMessage);



////void IO601_LINFreePortQueue();
////boolean_T IO601_LINGlbHelpSender(uint32_T modIdx, uint8_T protID, double ts);
////boolean_T IO601_LINGlbHelperReceiver(uint32_T modIdx, uint8_T protID, double ts);
////boolean_T IO601_LINUpdateSlvBuffer1(uint32_T modIdx, uint8_T protID, uint8_T rdIdx);
////boolean_T IO601_LINUpdateSlvBuffer2(uint32_T modIdx, uint8_T protID, uint8_T rdIdx);
////void IO601_CANClearConCurExeHdl();
////void IO601_LINClearConCurExeHdl();


#pragma endregion


#pragma region Functions - Static

/*
    Convert the assigned ID into the Intel format.
*/
static uint32_T ToIntel(uint32_T id, uint32_T nBits)
{
    uint32_T intel;

    intel = id;
    intel = (uint32_T)(((intel & 0x000000FF) << 24) +
        ((intel & 0x0000FF00) << 8) +
                       ((intel & 0x00FF0000) >> 8) +
                       ((intel & 0xFF000000) >> 24));
    intel = intel >> (32 - nBits);
    return intel;
}

#pragma endregion


#pragma region Functions - General

/*
    Set all start values for all CAN ports, so that the I/O module and the CAN ports can be initilized.
*/
void SetGeneralStartValuesBySetupBlock(uint32_T moduleIndex)
{
    sg_IO601_pModule[moduleIndex].pCommandPacket = (volatile BCICOMMAND*)sg_IO601_pModule[moduleIndex].pIOAddress2;
    memset((void*)sg_IO601_pModule[moduleIndex].pCommandPacket, 0x0, sizeof(BCICOMMAND));

    sg_IO601_pModule[moduleIndex].CAN.CANPort[0].Communication.WriteCounter = 0;
    sg_IO601_pModule[moduleIndex].CAN.CANPort[0].Communication.ReadCounter = 0;
    sg_IO601_pModule[moduleIndex].CAN.CANPort[1].Communication.WriteCounter = 0;
    sg_IO601_pModule[moduleIndex].CAN.CANPort[1].Communication.ReadCounter = 0;
    sg_IO601_pModule[moduleIndex].CAN.CANPort[0].StartAutoBusRecovery = 0;
    sg_IO601_pModule[moduleIndex].CAN.CANPort[1].StartAutoBusRecovery = 0;
    sg_IO601_pModule[moduleIndex].CAN.CANPort[0].Status = CpsStopped; //CpsRunning;
    sg_IO601_pModule[moduleIndex].CAN.CANPort[1].Status = CpsStopped; //CpsRunning;
    sg_IO601_pModule[moduleIndex].PortStatus[0] = CpsStopped;
    sg_IO601_pModule[moduleIndex].PortStatus[1] = CpsStopped;
    sg_IO601_pModule[moduleIndex].PortStatus[2] = CpsStopped;
    sg_IO601_pModule[moduleIndex].LIN.ConsNoLIN = 0;
    sg_IO601_pModule[moduleIndex].LIN.NextMsgIdx = 0;

    sg_IO601_pModule[moduleIndex].LIN.ReadIndex = 48;
    sg_IO601_pModule[moduleIndex].LIN.WriteIndex = 0;


    /* DEBUG: Use message only for debugging!!! *
    SG_PRINTF(DEBUG, "\nDEBUG - sg_IO601_pModule[%i].pCommandPacket = %#X - %#X", moduleIndex, sg_IO601_pModule[moduleIndex].pCommandPacket, *sg_IO601_pModule[moduleIndex].pCommandPacket);
    SG_PRINTF(DEBUG, "\nDEBUG - sg_IO601_pModule[%i].CAN.CANPort[0].Communication.WriteCounter = %i", moduleIndex, sg_IO601_pModule[moduleIndex].CAN.CANPort[0].Communication.WriteCounter);
    SG_PRINTF(DEBUG, "\nDEBUG - sg_IO601_pModule[%i].CAN.CANPort[0].Communication.ReadCounter = %i", moduleIndex, sg_IO601_pModule[moduleIndex].CAN.CANPort[0].Communication.ReadCounter);
    SG_PRINTF(DEBUG, "\nDEBUG - sg_IO601_pModule[%i].CAN.CANPort[1].Communication.WriteCounter = %i", moduleIndex, sg_IO601_pModule[moduleIndex].CAN.CANPort[0].Communication.WriteCounter);
    SG_PRINTF(DEBUG, "\nDEBUG - sg_IO601_pModule[%i].CAN.CANPort[1].Communication.ReadCounter = %i", moduleIndex, sg_IO601_pModule[moduleIndex].CAN.CANPort[0].Communication.ReadCounter);
    SG_PRINTF(DEBUG, "\nDEBUG - sg_IO601_pModule[%i].CAN.CANPort[0].Status = %i", moduleIndex, sg_IO601_pModule[moduleIndex].CAN.CANPort[0].Status);
    SG_PRINTF(DEBUG, "\nDEBUG - sg_IO601_pModule[%i].CAN.CANPort[1].Status = %i", moduleIndex, sg_IO601_pModule[moduleIndex].CAN.CANPort[1].Status);
    SG_PRINTF(DEBUG, "\n");
    //*/

}

/*
    Clear the buffer of the CAN port 1 and 2.
*/
void ClearAllBoardBuffers(uint32_T moduleIndex)
{
    uint32_T i;

    for (i = 0; i < QUANTITY_OF_CAN_PORTS; i++)
    {
        ClearMCToPCBuffers(moduleIndex, i);
        ClearPCToMCBuffers(moduleIndex, i);
    }
}

/*
    Clear the PC to uC buffer queue 0 and 1.
*/
void ClearPCToMCBuffers(uint32_T moduleIndex, uint8_T CANPort)
{
    int32_T i;
    volatile CAN_QUEUEENTRY *pQueue;

    if (0 == CANPort)
    {
        ////SG_PRINTF(DEBUG, "\nDbg - Clear port 1: %s", __FUNCTION__);

        for (i = 0; i < 50; i++)
        {
            pQueue = (CAN_QUEUEENTRY *)((sg_IO601_pModule[moduleIndex].pIOAddress2) + 0x50 + (i * sizeof(CAN_QUEUEENTRY)));
            pQueue->word[0] = 0;
        }
    }
    else
    {
        ////SG_PRINTF(DEBUG, "\nDbg - Clear port 2: %s", __FUNCTION__);

        for (i = 0; i < 50; i++)
        {
            pQueue = (CAN_QUEUEENTRY *)((sg_IO601_pModule[moduleIndex].pIOAddress2) + 0x438 + (i * sizeof(CAN_QUEUEENTRY)));
            pQueue->word[0] = 0;
        }
    }
}

void AnalyseMCToPCBuffers(uint32_T moduleIndex, uint8_T CANPort)
{
	int32_T i;
	volatile CAN_QUEUEENTRY *pQueue;
	int msgcount = 0;

	if (0 == CANPort)
	{
		for (i = 0; i < 50; i++)
		{
			pQueue = (CAN_QUEUEENTRY *)((sg_IO601_pModule[moduleIndex].pIOAddress2) + 0x820 + (i * sizeof(CAN_QUEUEENTRY)));
			if (pQueue->word[0])
				msgcount++;
		}
		SG_PRINTF(DEBUG, "\nDbg - Message count for port 1: %i", msgcount);
	}
	else
	{
		for (i = 0; i < 50; i++)
		{
			pQueue = (CAN_QUEUEENTRY *)((sg_IO601_pModule[moduleIndex].pIOAddress2) + 0xC08 + (i * sizeof(CAN_QUEUEENTRY)));
			if (pQueue->word[0])
				msgcount++;
		}
		SG_PRINTF(DEBUG, "\nDbg - Message count for port 2: %i", msgcount);

	}
}

/*
    Clear the uC to PC buffer queue 0 and 1.
*/
void ClearMCToPCBuffers(uint32_T moduleIndex, uint8_T CANPort)
{
    int32_T i;
    volatile CAN_QUEUEENTRY *pQueue;

    if (0 == CANPort)
    {
        ////SG_PRINTF(DEBUG, "\nDbg - Clear port 1: %s", __FUNCTION__);

        for (i = 0; i < 50; i++)
        {
            pQueue = (CAN_QUEUEENTRY *)((sg_IO601_pModule[moduleIndex].pIOAddress2) + 0x820 + (i * sizeof(CAN_QUEUEENTRY)));
            pQueue->word[0] = 0;
            pQueue->word[1] = 0;
            pQueue->word[2] = 0;
            pQueue->word[3] = 0;
            pQueue->word[4] = 0;
        }
    }
    else
    {
        ////SG_PRINTF(DEBUG, "\nDbg - Clear port 2: %s", __FUNCTION__);

        for (i = 0; i < 50; i++)
        {
            pQueue = (CAN_QUEUEENTRY *)((sg_IO601_pModule[moduleIndex].pIOAddress2) + 0xC08 + (i * sizeof(CAN_QUEUEENTRY)));
            pQueue->word[0] = 0;
            pQueue->word[1] = 0;
            pQueue->word[2] = 0;
            pQueue->word[3] = 0;
            pQueue->word[4] = 0;
        }
    }
}

/*
    Cleanup the complete global structure of the project.
*/
void CleanupAll(uint32_T moduleIndex)
{
    sg_IO601_ModuleCounter--;

    if (NULL != sg_IO601_pModule)
    {
        if (0 == sg_IO601_ModuleCounter)
        {
            CleanupSetupBlock();
            CleanupCANPort();

            ////#if _MSC_VER > 1600
            ////            IO601_CANClearConCurExeHdl();
            ////            IO601_LINClearConCurExeHdl();
            ////            IO601_LINFreePortQueue();
            ////#endif // _MSC_VER > 1600

            CleanupBackgroundTask();

            free(sg_IO601_pModule);
            sg_IO601_pModule = NULL;
        }
    }
}

/*
    Cleanup the complete global structure of the project in case of error.
*/
void CleanupAllOnError(uint32_T moduleIndex)
{
    sg_IO601_ModuleCounter = 1;
    CleanupAll(moduleIndex);
}

/*
    Free all allocated memory of all SETUP blocks and set the variables and pointers to their default values.
*/
void CleanupSetupBlock()
{
    uint32_T i;

    for (i = 0; i < QUANTITY_IO_MODULES; i++)
    {
        sg_IO601_pModule[i].BusNumber = 0;
        sg_IO601_pModule[i].SlotNumber = 0;
        sg_IO601_pModule[i].ModuleIndex = 0;
        sg_IO601_pModule[i].ModuleID = 0;
        sg_IO601_pModule[i].pIOAddress0 = NULL;
        sg_IO601_pModule[i].pIOAddress2 = NULL;
        sg_IO601_pModule[i].pCommandPacket = NULL;
        sg_IO601_pModule[i].CAN.pStatus = NULL;
    }
}

/*
    Delete all semaphores, threads and set the handler to the default values (normaly NULL);
*/
void CleanupBackgroundTask()
{
    uint32_T i;
    uint32_T j;

    for (i = 0; i < QUANTITY_IO_MODULES; i++)
    {
        if (NULL != sg_IO601_pModule[i].BackgroundTask.pBusStatusSemaphore)
        {
            for (j = 0; j < QUANTITY_OF_CAN_PORTS; j++)
            {
                if (NULL != sg_IO601_pModule[i].BackgroundTask.pCANRecoveryThread[j])
                {
                    sg_destroyThread(sg_IO601_pModule[i].BackgroundTask.pCANRecoveryThread[j]);
                    sg_IO601_pModule[i].BackgroundTask.pCANRecoveryThread[j] = NULL;
                }
            }

            sg_destroySemaphore(sg_IO601_pModule[i].BackgroundTask.pBusStatusSemaphore);
            sg_IO601_pModule[i].BackgroundTask.pBusStatusSemaphore = NULL;
            sg_IO601_pModule[i].BackgroundTask.pSemaphoreStatus = NULL;
        }
    }
}

/*
    Do an board reset by the GPIO pins of the uC.
*/
void ResetBoard(uint32_T moduleIndex)
{
    uint32_T regtemp = sg_IO601_pModule[moduleIndex].pIOAddress0[0x15];

    ////sg_IO601_pModule[moduleIndex].pIOAddress0[0x15] = regtemp & ~(1 << 11);
    ////sg_wait_s(0.001);
    ////sg_IO601_pModule[moduleIndex].pIOAddress0[0x15] = regtemp | (1 << 11);
    ////sg_wait_s(0.001);

    regtemp &= ~(1 << 11);
    sg_IO601_pModule[moduleIndex].pIOAddress0[0x15] = regtemp;
    sg_wait_s(0.05);
    regtemp |= (1 << 11);
    sg_IO601_pModule[moduleIndex].pIOAddress0[0x15] = regtemp;
    sg_wait_s(0.05);


    /* DEBUG: Use message only for debugging!!! *
    SG_PRINTF(DEBUG, "\nDEBUG - Reset board is done.");
    SG_PRINTF(DEBUG, "\n");
    //*/
}

/*
    Reset the microcontroller by GPIO pins, accessable by base0 addres.
*/
void InterruptMicrocontroller(uint32_T moduleIndex)
{
    uint32_T regtemp = 0;

    // generate MC interrupt through GPIO pin
    regtemp = sg_IO601_pModule[moduleIndex].pIOAddress0[0x15];

    ////SG_PRINTF(DEBUG, "\nDbg - regtemp: %#X", regtemp);

    sg_IO601_pModule[moduleIndex].pIOAddress0[0x15] = regtemp & ~(1 << 2);
    sg_IO601_pModule[moduleIndex].pIOAddress0[0x15] = regtemp | (1 << 2);
}

/*
    Set the start values of the I/O module.
*/
void SetModuleStartValues(int16_T moduleIndex, int16_T slot, int16_T bus)
{
    if (NULL == sg_IO601_pModule)
    {
        uint32_T arraySize = sizeof(sg_IO601_Module_T) * QUANTITY_IO_MODULES;
        sg_IO601_pModule = (sg_IO601_Module_T*)malloc(arraySize);

        memset(sg_IO601_pModule, 0x00, arraySize);
    }

    sg_IO601_pModule[moduleIndex].BusNumber = bus;
    sg_IO601_pModule[moduleIndex].SlotNumber = slot;
    sg_IO601_pModule[moduleIndex].ModuleID = moduleIndex + 1;
    sg_IO601_pModule[moduleIndex].ModuleIndex = moduleIndex;
    sg_IO601_pModule[moduleIndex].pCommandPacket = NULL;
    sg_IO601_pModule[moduleIndex].BackgroundTask.pBusStatusSemaphore = NULL;
    sg_IO601_pModule[moduleIndex].BackgroundTask.pCANRecoveryThread[0] = NULL;
    sg_IO601_pModule[moduleIndex].BackgroundTask.pCANRecoveryThread[1] = NULL;


    /* DEBUG: Use message only for debugging!!! *
    SG_PRINTF(DEBUG, "\nDEBUG - Set start values");
    SG_PRINTF(DEBUG, "\nDEBUG - pModule[%i].BusNumber = %i", moduleIndex, pModule[moduleIndex].BusNumber);
    SG_PRINTF(DEBUG, "\nDEBUG - pModule[%i].SlotNumber =  %i", moduleIndex, pModule[moduleIndex].SlotNumber);
    SG_PRINTF(DEBUG, "\nDEBUG - pModule[%i].ModuleID = %i", moduleIndex, pModule[moduleIndex].ModuleID);
    SG_PRINTF(DEBUG, "\nDEBUG - pModule[%i].ModuleIndex = %i", moduleIndex, pModule[moduleIndex].ModuleIndex);
    SG_PRINTF(DEBUG, "\n");
    //*/
}


/*
    Set the bus start values for a CAN port.
*/
void SetBusSpecificValues(uint32_T moduleIndex, uint8_T CANPort,
                          uint8_T busTimingRegisterBRP, uint8_T busTimingRegisterSJW, uint8_T busTimingRegisterTSEG1, uint8_T busTimingRegisterTSEG2, uint8_T mode,
                          uint32_T acceptanceMask1, uint32_T acceptanceCode1, uint32_T acceptanceMask2, uint32_T acceptanceCode2,
                          uint32_T extAcceptanceMask1, uint32_T extAcceptanceCode1, uint32_T extAcceptanceMask2, uint32_T extAcceptanceCode2)
{
    sg_IO601_pModule[moduleIndex].CAN.CANPort[CANPort].IsEnabled = 1;
    sg_IO601_pModule[moduleIndex].CAN.CANPort[CANPort].TimingRegisterBRP = busTimingRegisterBRP;
    sg_IO601_pModule[moduleIndex].CAN.CANPort[CANPort].TimingRegisterSJW = busTimingRegisterSJW;
    sg_IO601_pModule[moduleIndex].CAN.CANPort[CANPort].TimingRegisterTSEG1 = busTimingRegisterTSEG1;
    sg_IO601_pModule[moduleIndex].CAN.CANPort[CANPort].TimingRegisterTSEG2 = busTimingRegisterTSEG2;
    sg_IO601_pModule[moduleIndex].CAN.CANPort[CANPort].Mode = mode;
    sg_IO601_pModule[moduleIndex].CAN.CANPort[CANPort].StandardAcceptanceMask[0] = acceptanceMask1;
    sg_IO601_pModule[moduleIndex].CAN.CANPort[CANPort].StandardAcceptanceMask[1] = acceptanceMask2;
    sg_IO601_pModule[moduleIndex].CAN.CANPort[CANPort].StandardAcceptanceCode[0] = acceptanceCode1;
    sg_IO601_pModule[moduleIndex].CAN.CANPort[CANPort].StandardAcceptanceCode[1] = acceptanceCode2;
    sg_IO601_pModule[moduleIndex].CAN.CANPort[CANPort].ExtendedAcceptanceMask[0] = extAcceptanceMask1;
    sg_IO601_pModule[moduleIndex].CAN.CANPort[CANPort].ExtendedAcceptanceMask[1] = extAcceptanceMask2;
    sg_IO601_pModule[moduleIndex].CAN.CANPort[CANPort].ExtendedAcceptanceCode[0] = extAcceptanceCode1;
    sg_IO601_pModule[moduleIndex].CAN.CANPort[CANPort].ExtendedAcceptanceCode[1] = extAcceptanceCode2;

}

/*
    Set the output port of the status block.
*/
void SetOutputPortValue(uint32_T moduleIndex, uint8_T CANPort, uint32_T valueIndex, uint16_T *pOutputPortCAN0)
{
    switch (valueIndex)
    {
        case 1:     // Error/Warning (Bit 1)
            *pOutputPortCAN0 = (0 == CANPort) ? (sg_IO601_pModule[moduleIndex].CAN.pStatus->Status0 >> 1) & 0x0001 : (sg_IO601_pModule[moduleIndex].CAN.pStatus->Status1 >> 1) & 0x01;
            break;
        case 2:     // Bus Off (Bit 2)
            *pOutputPortCAN0 = (0 == CANPort) ? (sg_IO601_pModule[moduleIndex].CAN.pStatus->Status0 >> 2) & 0x0001 : (sg_IO601_pModule[moduleIndex].CAN.pStatus->Status1 >> 2) & 0x01;

            // Activate bus-recovery if BUS OFF = 1
            if (1 == *pOutputPortCAN0)
            {
                sg_IO601_pModule[moduleIndex].CAN.CANPort[CANPort].StartAutoBusRecovery += 1;
            }

            break;
        case 3:     // Data overrun (Bit 3)
            *pOutputPortCAN0 = (0 == CANPort) ? (sg_IO601_pModule[moduleIndex].CAN.pStatus->Status0 >> 3) & 0x0001 : (sg_IO601_pModule[moduleIndex].CAN.pStatus->Status1 >> 3) & 0x01;
            break;
        case 4:     // Transmit (Bit 5)
            *pOutputPortCAN0 = (0 == CANPort) ? (sg_IO601_pModule[moduleIndex].CAN.pStatus->Status0 >> 5) & 0x0001 : (sg_IO601_pModule[moduleIndex].CAN.pStatus->Status1 >> 5) & 0x01;
            break;
        case 5:     // Tranceiver error (Bit 6)
            *pOutputPortCAN0 = (0 == CANPort) ? (sg_IO601_pModule[moduleIndex].CAN.pStatus->Status0 >> 6) & 0x0001 : (sg_IO601_pModule[moduleIndex].CAN.pStatus->Status1 >> 6) & 0x01;
            break;
        case 6:     // Receive queue overrun (Bit 8)
            *pOutputPortCAN0 = (0 == CANPort) ? (sg_IO601_pModule[moduleIndex].CAN.pStatus->Status0 >> 8) & 0x0001 : (sg_IO601_pModule[moduleIndex].CAN.pStatus->Status1 >> 8) & 0x01;
            break;
        case 7:     // Receive queue empty (Bit 9) 
            *pOutputPortCAN0 = (0 == CANPort) ? (sg_IO601_pModule[moduleIndex].CAN.pStatus->Status0 >> 9) & 0x0001 : (sg_IO601_pModule[moduleIndex].CAN.pStatus->Status1 >> 9) & 0x01;
            break;
        case 8:     // Reveive (Bit 4)
            *pOutputPortCAN0 = (0 == CANPort) ? (sg_IO601_pModule[moduleIndex].CAN.pStatus->Status0 >> 4) & 0x0001 : (sg_IO601_pModule[moduleIndex].CAN.pStatus->Status1 >> 4) & 0x01;
            break;
        case 9:     // Bus load
            *pOutputPortCAN0 = (0 == CANPort) ? sg_IO601_pModule[moduleIndex].CAN.pStatus->BusLoad0 : sg_IO601_pModule[moduleIndex].CAN.pStatus->BusLoad1;
            break;
        case 10:    // CPU load
            *pOutputPortCAN0 = sg_IO601_pModule[moduleIndex].CAN.pStatus->CPULoad;
            break;
        case 11:    // live counter
            *pOutputPortCAN0 = sg_IO601_pModule[moduleIndex].CAN.pStatus->LiveCounter;
            break;
        case 12:    // Recovery counter
            *pOutputPortCAN0 = sg_IO601_pModule[moduleIndex].CAN.CANPort[CANPort].BusRecoveryCounter;
            break;
        case 13:    // Single Transmission Try (STT)
            *pOutputPortCAN0 = (0 == CANPort) ? (sg_IO601_pModule[moduleIndex].CAN.pStatus->Status0 >> 7) & 0x0001 : (sg_IO601_pModule[moduleIndex].CAN.pStatus->Status1 >> 7) & 0x01;
            break;
        default:
            break;
    }
}

/*
    Set the bus status for the background task of each CAN port.
*/
void SetBusStatusForBackgroundTask(uint32_T moduleIndex, uint8_T CANPort)
{
    ////sg_IO601_pModule[moduleIndex].CAN.CANPort[CANPort].BusStatus = 0;
    sg_IO601_pModule[moduleIndex].CAN.CANPort[CANPort].Status = CpsStopped;
    sg_IO601_pModule[moduleIndex].PortStatus[CANPort] = CpsStopped;
    sg_IO601_pModule[moduleIndex].CAN.CANPort[CANPort].RecoveryStatus = CrsStop;
    ////sg_IO601_pModule[moduleIndex].CAN.CANPort[CANPort].RecoveryStatus = RpCANStopPhase;
    ////ReleaseSemaphore(sg_IO601_pModule[moduleIndex].BackgroundTask.BusStatusSemaphore, 1, NULL);
}

/*
    Restart the firmware ot the PCI device.
*/
void RestartFirmware(volatile uint32_T *ioaddress0, volatile BCICOMMAND *bci, uint8_T blocking)
{
    bci->synch = 0;
    bci->count = 2;
    bci->reserved = (3 << 8);
    bci->command = 0x2;
    bci->data[0] = 0x0;
    bci->data[1] = 1;
    bci->synch = 1;

    //InterruptMicrocontroller(ioaddress0);

    if (blocking == BLOCKING_CMD)
    {
        while (bci->synch != 2);
    }
    return;
}

/*
    Update the LIN transmit buffer in the DPRAM.
*/
void UpdateLinTxBufDpramEntry(uintptr_t base, uint8_T entry, volatile BCI_t_LIN_MSG msg)
{

    // Variable declaration:
    uint8_T update0, update1;
    volatile t_semaphores *pSema;
    volatile BCI_t_LIN_MSG *pMsg;

    // Initialization        
    update0 = 0;
    update1 = 1;
    pSema = (t_semaphores *)(base + 0x2000);

    while (!update0 || !update1)
    {
        // we try to obtain the semaphore of buffer image 1    
        if (!update0 && (pSema->LINUpdateBuffer1 & 1))
        {
            while ((pSema->LINUpdateBuffer1 & 1) != 0)
            {
                pSema->LINUpdateBuffer1 &= ~1;
            };


            pMsg = (BCI_t_LIN_MSG *)(base + 0x18A8 + entry * sizeof(BCI_t_LIN_MSG));
            *pMsg = msg;
            update0 = 1;
            // we release the semaphore
            pSema->LINUpdateBuffer1 |= 1;

        }

        // we try to obtain the semaphore of buffer image 2    
        if (!update1 && (pSema->LINUpdateBuffer2 & 1))
        {

            while ((pSema->LINUpdateBuffer2 & 1) != 0)
            {
                pSema->LINUpdateBuffer2 &= ~1;
            };

            pMsg = (BCI_t_LIN_MSG *)(base + 0x1C28 + entry * sizeof(BCI_t_LIN_MSG));
            *pMsg = msg;
            update1 = 1;
            // we release the semaphore
            pSema->LINUpdateBuffer2 |= 1;

        }
    }

}

/*
    Check driver structure if it is initialized or not.
*/
uint8_T CheckDriver()
{
    if (NULL == sg_IO601_pModule)
    {
        return SetDefaultValuesBySetupBlock(0, false);      // only set the driver structure so moduleIndex is not necessary.
    }

    return 1;
}

/*
    Set all fields of the global process structure to their default values.
*/
uint8_T SetDefaultValuesBySetupBlock(uint32_T moduleIndex, boolean_T isSetupBlk)
{
    if (NULL == sg_IO601_pModule)
    {
        uint32_T i;
        uint32_T arraySize = sizeof(sg_IO601_Module_T) * QUANTITY_IO_MODULES;

        // Create global structure
        sg_IO601_pModule = (sg_IO601_Module_T*)malloc(arraySize);

        if (NULL == sg_IO601_pModule)
        {
            return 0;
        }

        memset(sg_IO601_pModule, 0x00, arraySize);

        // Set default values
        for (i = 0; i < QUANTITY_IO_MODULES; i++)
        {
            sg_IO601_pModule[i].pIOAddress0 = NULL;
            sg_IO601_pModule[i].pIOAddress2 = NULL;
            sg_IO601_pModule[i].pCommandPacket = NULL;
            sg_IO601_pModule[i].CAN.Test = 1;
            sg_IO601_pModule[i].CAN.pStatus = NULL;
            sg_IO601_pModule[i].BackgroundTask.pBusStatusSemaphore = NULL;
            sg_IO601_pModule[i].BackgroundTask.pCANRecoveryThread[0] = NULL;
            sg_IO601_pModule[i].BackgroundTask.pCANRecoveryThread[1] = NULL;
            sg_IO601_pModule[i].BackgroundTask.pSemaphoreStatus = NULL;
            sg_IO601_pModule[i].pGlbSnd = NULL;
            sg_IO601_pModule[i].CAN.CANPort[0].ConCurExe.pGlbSnd = NULL;
            sg_IO601_pModule[i].CAN.CANPort[1].ConCurExe.pGlbSnd = NULL;
            sg_IO601_pModule[i].LIN.ConCurExe.pGlbSnd = NULL;
            sg_IO601_pModule[i].LIN.ConCurExe.pGlbRec = NULL;
        }
    }

    if (isSetupBlk)
    {
        sg_IO601_pModule[moduleIndex].ModuleID = moduleIndex + 1;
        sg_IO601_pModule[moduleIndex].ModuleIndex = moduleIndex;
        sg_IO601_ModuleCounter++;
    }

    /* DEBUG: Use message only for debugging!!! *
    SG_PRINTF(DEBUG, "\nDEBUG - Set default values by SETUP block:");
    SG_PRINTF(DEBUG, "\nDEBUG - pModule[%i].ModuleID = %i", moduleIndex, sg_IO601_pModule[moduleIndex].ModuleID);
    SG_PRINTF(DEBUG, "\nDEBUG - pModule[%i].ModuleIndex = %i", moduleIndex, sg_IO601_pModule[moduleIndex].ModuleIndex);
    SG_PRINTF(DEBUG, "\n");
    //*/

    return 1;
}

/*
    Set the start values of variables and pointer of the STATUS block.
*/
uint8_T SetStartValuesStatusBlock(uint32_T moduleIndex)
{
    if (NULL == sg_IO601_pModule)
    {
        return 0;
    }

    sg_IO601_pModule[moduleIndex].CAN.pStatus = (CANStatusBufferDPRAM*)(sg_IO601_pModule[moduleIndex].pIOAddress2 + OFFSET_CAN_STATUS_BUFFER);
    return 1;
}

/*
    Get all PCI device information e.g. base addresses, virtual addresses and so on.
*/
uint8_T GetPCIDeviceInformation(uint32_T moduleIndex, int16_T busNumber, int16_T slotNumber)
{
    sg_PCIDevice PCIDevice = {0};

    // Get PCI device data
    if(sg_findPciDevice(&PCIDevice, "Io601", VENDORID, DEVICEID, SUBVENDORID, SUBDEVICEID, moduleIndex, busNumber, slotNumber))
    {
    	//ssSetErrorStatus(S,pSgErrorStr);
    	return 0;
    }

    // Set module data
    sg_IO601_pModule[moduleIndex].BusNumber = PCIDevice.bus;
    sg_IO601_pModule[moduleIndex].SlotNumber = PCIDevice.slot;
    sg_IO601_pModule[moduleIndex].pIOAddress0 = sg_mapMemory(&PCIDevice, 0);
	sg_IO601_pModule[moduleIndex].pIOAddress2 = sg_mapMemory(&PCIDevice, 2);

    /* DEBUG: Use message only for debugging!!! *
    SG_PRINTF(DEBUG, "\nDEBUG - PCIDevice.BaseAddress[0] = %#X, ASI = %#X, L = %#X", PCIDevice.BaseAddress[0], PCIDevice.AddressSpaceIndicator[0], PCIDevice.Length[0]);
    SG_PRINTF(DEBUG, "\nDEBUG - PCIDevice.BaseAddress[1] = %#X, ASI = %#X, L = %#X", PCIDevice.BaseAddress[1], PCIDevice.AddressSpaceIndicator[1], PCIDevice.Length[1]);
    SG_PRINTF(DEBUG, "\nDEBUG - PCIDevice.BaseAddress[2] = %#X, ASI = %#X, L = %#X", PCIDevice.BaseAddress[2], PCIDevice.AddressSpaceIndicator[2], PCIDevice.Length[2]);
    SG_PRINTF(DEBUG, "\nDEBUG - PCIDevice.BaseAddress[3] = %#X, ASI = %#X, L = %#X", PCIDevice.BaseAddress[3], PCIDevice.AddressSpaceIndicator[3], PCIDevice.Length[3]);
    SG_PRINTF(DEBUG, "\nDEBUG - PCIDevice.BaseAddress[4] = %#X, ASI = %#X, L = %#X", PCIDevice.BaseAddress[4], PCIDevice.AddressSpaceIndicator[4], PCIDevice.Length[4]);
    SG_PRINTF(DEBUG, "\nDEBUG - PCIDevice.BaseAddress[5] = %#X, ASI = %#X, L = %#X", PCIDevice.BaseAddress[5], PCIDevice.AddressSpaceIndicator[5], PCIDevice.Length[5]);
    SG_PRINTF(DEBUG, "\n");
    SG_PRINTF(DEBUG, "\nDEBUG - sg_IO601_pModule[%i].pIOAddress0 = %#X", moduleIndex, sg_IO601_pModule[moduleIndex].pIOAddress0);
    SG_PRINTF(DEBUG, "\nDEBUG - sg_IO601_pModule[%i].pIOAddress2 = %#X", moduleIndex, sg_IO601_pModule[moduleIndex].pIOAddress2);
    SG_PRINTF(DEBUG, "\nDEBUG - sg_IO601_pModule[%i].pCommandPacket = %#X - %#X", moduleIndex, sg_IO601_pModule[moduleIndex].pCommandPacket, *sg_IO601_pModule[moduleIndex].pCommandPacket);
    SG_PRINTF(DEBUG, "\nPCI bus number: %i", sg_IO601_pModule[moduleIndex].BusNumber);
    SG_PRINTF(DEBUG, "\n");
    SG_PRINTF(DEBUG, "\nPCI bus number: %i", sg_IO601_pModule[moduleIndex].SlotNumber);
    SG_PRINTF(DEBUG, "\n");
    //*/

    return 1;
}

/*
    Initialization of the board.
*/
uint8_T InitializationBoard(uint32_T moduleIndex)
{
    uint32_T counter = 0;

    sg_IO601_pModule[moduleIndex].pIOAddress2[0x00] = 0;             // sync
    sg_IO601_pModule[moduleIndex].pIOAddress2[0x01] = 0;             // count
    sg_IO601_pModule[moduleIndex].pIOAddress2[0x02] = 0;             // reserved 0
    sg_IO601_pModule[moduleIndex].pIOAddress2[0x03] = 3;             // reserved 1
    sg_IO601_pModule[moduleIndex].pIOAddress2[0x04] = 2;             // command
    sg_IO601_pModule[moduleIndex].pIOAddress2[0x05] = 0;             // data[1]
    sg_IO601_pModule[moduleIndex].pIOAddress2[0x06] = 1;             // data[0]
    sg_IO601_pModule[moduleIndex].pIOAddress2[0x00] = 1;             // sync
    sg_wait_s(0.050);
    sg_IO601_pModule[moduleIndex].pIOAddress2[0x01] = 0;             // count
    sg_wait_s(0.050);

    InterruptMicrocontroller(moduleIndex);

    while (TIMEOUT_FOR_SEND_PACKET > counter)
    {
        if (1 == sg_IO601_pModule[moduleIndex].pCommandPacket->synch)
        {
            sg_wait_s(0.001);
        }
        else if (0 == sg_IO601_pModule[moduleIndex].pCommandPacket->synch)
        {
            memset((void*)sg_IO601_pModule[moduleIndex].pCommandPacket, 0x00, sizeof(BCICOMMAND));

            /* DEBUG: Use message only for debugging!!! *
            SG_PRINTF(DEBUG, "\nDEBUG - Initialization of board was successful.");
            SG_PRINTF(DEBUG, "\n");
            //*/

            return 1;
        }

        counter++;
    }

    return 0;
}

/*
    Read the application identifying information as string.
*/
uint8_T ReadApplicationIdentifyingInformation(uint32_T moduleIndex)
{
    uint32_T counter = 0;

    sg_IO601_pModule[moduleIndex].pCommandPacket->synch = 0;
    sg_IO601_pModule[moduleIndex].pCommandPacket->count = 2;
    sg_IO601_pModule[moduleIndex].pCommandPacket->command = CMD_ID;
    sg_IO601_pModule[moduleIndex].pCommandPacket->synch = 1;

    InterruptMicrocontroller(moduleIndex);

    while (TIMEOUT_FOR_SEND_PACKET > counter)
    {
        if (1 == sg_IO601_pModule[moduleIndex].pCommandPacket->synch)
        {
            sg_wait_s(0.001);
        }
        else if (2 == sg_IO601_pModule[moduleIndex].pCommandPacket->synch)
        {
            memset((void*)sg_IO601_pModule[moduleIndex].pCommandPacket, 0x00, sizeof(BCICOMMAND));

            /* DEBUG: Use message only for debugging!!! *
            SG_PRINTF(DEBUG, "\nDEBUG - Application identifying information: \n\t\t%s", sg_IO601_pModule[moduleIndex].pCommandPacket->data);
            SG_PRINTF(DEBUG, "\n");
            //*/

            return 1;
        }

        counter++;
    }

    return 0;
}

/*
    Readout the version number of the I/O module as string.
*/
uint8_T ReadoutVersionNumber(int32_T moduleIndex)
{
    uint32_T counter = 0;

    sg_IO601_pModule[moduleIndex].pCommandPacket->synch = 0;
    sg_IO601_pModule[moduleIndex].pCommandPacket->count = 2;
    sg_IO601_pModule[moduleIndex].pCommandPacket->command = CMD_VERSION;
    sg_IO601_pModule[moduleIndex].pCommandPacket->synch = 1;

    InterruptMicrocontroller(moduleIndex);

    while (TIMEOUT_FOR_SEND_PACKET > counter)
    {
        if (1 == sg_IO601_pModule[moduleIndex].pCommandPacket->synch)
        {
            sg_wait_s(0.001);
        }
        else if (2 == sg_IO601_pModule[moduleIndex].pCommandPacket->synch)
        {
            if (0 == strncmp((char*)sg_IO601_pModule[moduleIndex].pCommandPacket->data, "V4.27", 6) || 0 == strncmp((char*)sg_IO601_pModule[moduleIndex].pCommandPacket->data, "V4.18", 6))
            {
                memset((void*)sg_IO601_pModule[moduleIndex].pCommandPacket, 0x00, sizeof(BCICOMMAND));

                /* DEBUG: Use message only for debugging!!! */
                SG_PRINTF(DEBUG, "\nDEBUG - Version number: %s", sg_IO601_pModule[moduleIndex].pCommandPacket->data);
                SG_PRINTF(DEBUG, "\n");
                //*/

                return 1;
            }

            break;
        }

        counter++;
    }

    return 0;
}

/*
    Test the DPRAM command interface.
*/
uint8_T TestBoard(uint32_T moduleIndex)
{
    uint32_T i;
    uint32_T counter = 0;

    sg_IO601_pModule[moduleIndex].pCommandPacket->synch = 0;
    sg_IO601_pModule[moduleIndex].pCommandPacket->count = 76;
    sg_IO601_pModule[moduleIndex].pCommandPacket->command = CMD_TEST;
    sg_IO601_pModule[moduleIndex].pCommandPacket->synch = 1;

    InterruptMicrocontroller(moduleIndex);

    while (TIMEOUT_FOR_SEND_PACKET > counter)
    {
        if (1 == sg_IO601_pModule[moduleIndex].pCommandPacket->synch)
        {
            sg_wait_s(0.001);
        }
        else if (2 == sg_IO601_pModule[moduleIndex].pCommandPacket->synch)
        {
            for (i = 0; i < 75; i++)
            {
                if (0xFF != sg_IO601_pModule[moduleIndex].pCommandPacket->data[i])
                {
                    return 0;
                }
            }

            memset((void*)sg_IO601_pModule[moduleIndex].pCommandPacket, 0x00, sizeof(BCICOMMAND));

            /* DEBUG: Use message only for debugging!!! *
            SG_PRINTF(DEBUG, "\nDEBUG - Test DPRAM command interface was successful.");
            SG_PRINTF(DEBUG, "\n");
            //*/

            return 1;
        }

        counter++;
    }

    return 0;
}

/*
    Set the acceptance mask for 11 Bit and 29 Bit identifier.

       2 masks can be configured for each frame format.

       Command to set the acceptance mask for 11-bit and 29-bit identifier.
       There for each frame format Messsage 2 masks with which to received CAN Messages can be configured.
       The CAN message is received, if the following condition is satisfied:
       ((ID & MASK1) == CODE1) | | ((id & MASK2) == CODE2)
*/
uint8_T SetStandardAcceptanceMask(uint32_T moduleIndex, uint8_T CANPort, uint8_T maskNumber, uint8_T mode, uint32_T acceptanceMask,
                                  uint32_T acceptanceCode)
{
    uint8_T rtnValue = 0;
    uint32_T counter = 0;

    sg_IO601_pModule[moduleIndex].pCommandPacket->synch = 0;
    sg_IO601_pModule[moduleIndex].pCommandPacket->count = 10;
    sg_IO601_pModule[moduleIndex].pCommandPacket->command = CMD_SET_ACC_MASK;
    sg_IO601_pModule[moduleIndex].pCommandPacket->data[0] = CANPort;
    sg_IO601_pModule[moduleIndex].pCommandPacket->data[1] = maskNumber;
    sg_IO601_pModule[moduleIndex].pCommandPacket->data[2] = mode;
    sg_IO601_pModule[moduleIndex].pCommandPacket->data[3] = (uint8_T)(acceptanceMask & 0x000000FF);
    sg_IO601_pModule[moduleIndex].pCommandPacket->data[4] = (uint8_T)((acceptanceMask >> 8) & 0x000000FF);
    sg_IO601_pModule[moduleIndex].pCommandPacket->data[5] = (uint8_T)((acceptanceMask >> 16) & 0x000000FF);
    sg_IO601_pModule[moduleIndex].pCommandPacket->data[6] = (uint8_T)((acceptanceMask >> 24) & 0x000000FF);
    sg_IO601_pModule[moduleIndex].pCommandPacket->data[7] = (uint8_T)(acceptanceCode & 0x000000FF);
    sg_IO601_pModule[moduleIndex].pCommandPacket->data[8] = (uint8_T)((acceptanceCode >> 8) & 0x000000FF);
    sg_IO601_pModule[moduleIndex].pCommandPacket->data[9] = (uint8_T)((acceptanceCode >> 16) & 0x000000FF);
    sg_IO601_pModule[moduleIndex].pCommandPacket->data[10] = (uint8_T)((acceptanceCode >> 24) & 0x000000FF);
    sg_IO601_pModule[moduleIndex].pCommandPacket->synch = 1;

    InterruptMicrocontroller(moduleIndex);

    while (TIMEOUT_FOR_SEND_PACKET > counter)
    {
        if (1 == sg_IO601_pModule[moduleIndex].pCommandPacket->synch)
        {
            sg_wait_s(0.001);
        }
        else if (2 == sg_IO601_pModule[moduleIndex].pCommandPacket->synch)
        {
            rtnValue = sg_IO601_pModule[moduleIndex].pCommandPacket->data[0];
            memset((void*)sg_IO601_pModule[moduleIndex].pCommandPacket, 0x00, sizeof(BCICOMMAND));

            /* DEBUG: Use message only for debugging!!! *
            SG_PRINTF(DEBUG, "\nDEBUG - Set standard=0/extended=1 (mode = %i)  acceptance mask %i \n\t\tfor CAN %i (Port %i) was succesfull.",
            mode, maskNumber+1, CANPort, CANPort+1);
            SG_PRINTF(DEBUG, "\n");
            //*/

            break;
        }

        counter++;
    }

    return rtnValue;
}

/*
    Configuration of the receive queue (Rx Queue).
*/
uint8_T ConfigureReceivingQueue(uint32_T moduleIndex, uint8_T CANPort, uint8_T receiveMode)
{
    uint8_T rtnValue = 0;
    uint32_T counter = 0;

    sg_IO601_pModule[moduleIndex].pCommandPacket->synch = 0;
    sg_IO601_pModule[moduleIndex].pCommandPacket->count = 4;
    sg_IO601_pModule[moduleIndex].pCommandPacket->command = CMD_CONFIG_RX_QUEUE;
    sg_IO601_pModule[moduleIndex].pCommandPacket->data[0] = CANPort;
    sg_IO601_pModule[moduleIndex].pCommandPacket->data[1] = receiveMode;
    sg_IO601_pModule[moduleIndex].pCommandPacket->synch = 1;

    InterruptMicrocontroller(moduleIndex);

    while (TIMEOUT_FOR_SEND_PACKET > counter)
    {
        if (1 == sg_IO601_pModule[moduleIndex].pCommandPacket->synch)
        {
            sg_wait_s(0.001);
        }
        else if (2 == sg_IO601_pModule[moduleIndex].pCommandPacket->synch)
        {
            rtnValue = sg_IO601_pModule[moduleIndex].pCommandPacket->data[0];
            memset((void*)sg_IO601_pModule[moduleIndex].pCommandPacket, 0x00, sizeof(BCICOMMAND));

            /* DEBUG: Use message only for debugging!!! *
            SG_PRINTF(DEBUG, "\nDEBUG - Configuration of receiving (RX) queue for CAN %i (Port %i) was succesfull.", CANPort, CANPort+1);
            SG_PRINTF(DEBUG, "\n");
            //*/

            break;
        }

        counter++;
    }

    return rtnValue;
}

/*
    Create the bus status semaphore.
*/
uint8_T CreateBusStatusSemaphore(uint32_T moduleIndex)
{
    if (NULL == sg_IO601_pModule[moduleIndex].BackgroundTask.pBusStatusSemaphore)
    {
        sg_IO601_pModule[moduleIndex].BackgroundTask.pSemaphoreStatus = (t_semaphores*)(sg_IO601_pModule[moduleIndex].pIOAddress2 + OFFSET_SEMAPHORES_START_ADDRESS);
        sg_IO601_pModule[moduleIndex].BackgroundTask.pBusStatusSemaphore = sg_createSemaphore(0);

        if (NULL == sg_IO601_pModule[moduleIndex].BackgroundTask.pBusStatusSemaphore)
        {
            return 0;
        }
    }

    return 1;
}

/*
    Check the bus off status of the assigned port with the semaphore and return the status.
*/
uint8_T IsBusOff(uint32_T moduleIndex, uint8_T CANPort)
{
    uint8_T busOff = 0;

    while (0 != (sg_IO601_pModule[moduleIndex].BackgroundTask.pSemaphoreStatus->CANStatusBuffer & 1))
    {
        sg_IO601_pModule[moduleIndex].BackgroundTask.pSemaphoreStatus->CANStatusBuffer &= ~1;
    }

    if (0 == CANPort)
    {
        busOff = ((sg_IO601_pModule[moduleIndex].CAN.pStatus->Status0) >> 1) & 0x1;
    }

    if (1 == CANPort)
    {
        busOff = ((sg_IO601_pModule[moduleIndex].CAN.pStatus->Status1) >> 1) & 0x1;
    }

    return busOff;
}

/*
    Read the CAN message from the DPRAM.

    The CAN message is written with the message pointer (arg in).<BR>
    A CAN entry contains up to 20 bytes, which are:<BR>
    | n   | Standard    | extended    |
    | :-: | :---------- | :---------- |
    | 0   | status      | status      |
    | 1   | count       | count       |
    | 2   | TimeStamp   | TimeStamp   |
    | 3   | TimeStamp   | TimeStamp   |
    | 4   | TimeStamp   | TimeStamp   |
    | 5   | TimeStamp   | TimeStamp   |
    | 6   | Type        | Type        |
    | 7   | Information | Information |
    | 8   | Identifier  | Identifier  |
    | 9   | Identifier  | Identifier  |
    | 10  | Data        | Identifier  |
    | 11  | Data        | Identifier  |
    | 12  | Data        | Data        |
    | 13  | Data        | Data        |
    | 14  | Data        | Data        |
    | 15  | Data        | Data        |
    | 16  | Data        | Data        |
    | 17  | Data        | Data        |
    | 18  | Reserved    | Data        |
    | 19  | Reserved    | Data        |
*/
uint8_T ReadFIFO(uint32_T moduleIndex, uintptr_t queueEntryAddress, canMsg *message, uint32_T* tsOut)
{
    uint8_T status;

    volatile CAN_QUEUEENTRY *pQueue;
    uint32_T word[5];
    uint8_T bytes[20];
    uint16_T standardID;
    uint32_T extendedID;

    static_assert(sizeof(char*) == sizeof(uintptr_t), "pointer size not correct!");
    pQueue = (volatile CAN_QUEUEENTRY *)(queueEntryAddress);

    // Get the status byte which indicates if a new entry is present at this location.
    word[0] = pQueue->word[0];
    status = word[0] & 0xFF;

    if (!status)
		return 0;

	 // Because the status indicated a new message, we can read one complete queue entry.
        word[1] = pQueue->word[1];
        word[2] = pQueue->word[2];
        word[3] = pQueue->word[3];
        word[4] = pQueue->word[4];

        // now we split the words into bytes, to unpack the CAN frame.
        memcpy(bytes, word, 20);

		if (bytes[6] & 0x1) {
			// we got a CAN status message. According to docu, this happens in following cases:
			// - Bus Off
			// - Error status set
			// - error status reset.

			// handling here - just copy like regular msg.
		}

        // the message type (standard or extended) changes the Frame format.
		// Timestamp resolution is 8 kHz, little endian 32-bit.
		if (bytes[7] & 0x80) // extended 
        {
			uint32_T Timestamp = bytes[2] | (bytes[3] << 8) | (bytes[4] << 16) | (bytes[5] << 24);
			message->Timestamp = (real_T)Timestamp;
			if (tsOut)
				*tsOut = Timestamp;

			message->Extended = 1;
            message->Length = bytes[7] & 0xF;
            message->Remote = (bytes[7] & 0x40) >> 6;
            message->Error = 0;

            extendedID = bytes[8] | (bytes[9] << 8) | (bytes[10] << 16) | (bytes[11] << 24);
            message->ID = ToIntel(extendedID, 29);
            message->Data[0] = bytes[12];
            message->Data[1] = bytes[13];
            message->Data[2] = bytes[14];
            message->Data[3] = bytes[15];
            message->Data[4] = bytes[16];
            message->Data[5] = bytes[17];
            message->Data[6] = bytes[18];
            message->Data[7] = bytes[19];
		}
        else
        {
			uint32_T Timestamp = (bytes[2] + (bytes[3] << 8) + (bytes[4] << 16) + (bytes[5] << 24));
			message->Timestamp = (real_T)Timestamp;
			if (tsOut)
				*tsOut = Timestamp;

			message->Extended = 0;
            message->Length = bytes[7] & 0xF;
            message->Remote = (bytes[7] & 0x40) >> 6;
            message->Error = 0;
            standardID = bytes[8] | (bytes[9] << 8);
            message->ID = ToIntel(standardID, 11);
            message->Data[0] = bytes[10];
            message->Data[1] = bytes[11];
            message->Data[2] = bytes[12];
            message->Data[3] = bytes[13];
            message->Data[4] = bytes[14];
            message->Data[5] = bytes[15];
            message->Data[6] = bytes[16];
            message->Data[7] = bytes[17];
        }

        // Mark the FIFO entry as free.
        pQueue->word[0] = 0;

        return 1;
}

/*
    Create LIN message ID

    Two parity bits are computed P0 and P1.
    P0 = id(0) xor id(1) xor id(2) xor id(4)
    P1 = !(id(1) xor id(3) xor id(4) xor id(5))

    The identifier is then:
    0: id0
    1: id1
    2: id2
    3: id3
    4: id4
    5: id5
    6: P0
    7: P1
*/
uint8_T CreateID(uint8_T id)
{

    t_BITSINBYTE_U u_id;

    u_id.b = id;                                                  /* get the id */
    u_id.u.o6 = u_id.u.o0 ^ u_id.u.o1 ^ u_id.u.o2 ^ u_id.u.o4;    /* create even parity p0 */
    u_id.u.o7 = ~(u_id.u.o1 ^ u_id.u.o3 ^ u_id.u.o4 ^ u_id.u.o5); /* create odd parity p1 */

    return (uint8_T)u_id.b;

}

/*
    Creates the Checksum in Classic and enhanced form and
    (originally "LIN_CreateChecksum" received from Andreas Stobe in Technical Support at IXXAT via email 16-06-2015))

*/
uint8_T CheckSum(uint32_T modIdx, uint8_T protID)
{
    uint8_T i;
    uint16_T w_LocalHelp = 0;

    // Include the protected ID for the checksum calculation (= Enhanced checksum for LIN version 2.x)
    if (sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].IsEnhcdChksum)
    {
        w_LocalHelp = sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].FullProtID;

        if (w_LocalHelp > 0xFF)     // If protected ID is higher than 255 (full protected ID includes the message ID + parity bits
        {
            w_LocalHelp -= 0xFF;
        }
    }

    // Summarize the values of the message data regarding the DLC of the message.
    for (i = 0; i < sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].DLC; i++)
    {
        w_LocalHelp = w_LocalHelp + sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].Data[i];

        if (w_LocalHelp > 0xFF)     // If value is higher than 255 do value - 255
        {
            w_LocalHelp -= 0xFF;
        }
    }

    return (uint8_T)(~w_LocalHelp); // return the inverted modulo-256 checksum
}

/*
    Write FIFO
*/
uint32_T WriteFIFO(uintptr_t queueEntryAddress, canMsg message)
{
    int32_T frc = 0;
    volatile CAN_QUEUEENTRY *pQueue;

    switch (message.Extended)
    {
        case 0:
            if (message.ID > 2047)
            {
                frc = -12; //in standard, identifer cannot be larger than 2^11 - 1
            }
            break;
        case 1:
            if (message.ID > 536870911)
            {
                frc = -13; //in extended, identifer cannot be larger than 2^19 - 1
            }
            break;
        default:
            frc = -11; // not a correct frame format.
            break;
    }

    if (message.Length > 8)
    {
        frc = -14;
    }

    // when the frames passed all the tests, we send it. A negative ident is a "don't send this message" flag.
    if (frc == 0 && message.ID >= 0)
    {
        pQueue = (CAN_QUEUEENTRY *)(queueEntryAddress);

        // now the CAN message has to be placed in the queueentry.
        if (0 == PrepareCANQueueEntry(message, pQueue))
        {
            frc = -1; /* the queue entry wasn't free. */
        }
    }
    else
    {
        frc = -15;
    }

    return frc;

}

/*
    This function returns the identifier given in parameter, coded in Motorola format.

    Motorola uses a Big Endian format, this means that:

    In a word (4 bytes):

    Intel[0] = Motorola[3]
    Intel[1] = Motorola[2]
    Intel[2] = Motorola[1]
    Intel[3] = Motorola[0]

    Important, if the data is not complete (size != 32), we have to align it.
*/
uint32_T ToMotorola(uint32_T id, uint32_T nBits)
{
    uint32_T motorola;

    motorola = (id << (32 - nBits));
    motorola = (uint32_T)(((motorola & 0x000000FF) << 24) +
        ((motorola & 0x0000FF00) << 8) +
                          ((motorola & 0x00FF0000) >> 8) +
                          ((motorola & 0xFF000000) >> 24));
    return motorola;
}

/*
    Write RAW message to the DPRAM and send CAN message.
*/
int32_T SendRAWMessage(uint32_T moduleIndex, uint8_T CANPort, uint8_T *pRAWDataInputPort, uint32_T *pRAWIdentifierInputPort, uint32_T *pRAWLengthInputPort,
                       uint32_T *pRAWIdentifierTypeInputPort)
{
    canMsg message = {0};
    message.ID = (int32_T)*pRAWIdentifierInputPort;
    message.Extended = (uint8_T)*pRAWIdentifierTypeInputPort;
    message.Length = (uint8_T)*pRAWLengthInputPort;
    message.Error = 0;
    message.Remote = 0;
    message.Timestamp = 0;
    memcpy(&message.Data, pRAWDataInputPort, sizeof(message.Data));

    return SendCANMessage(moduleIndex, CANPort, &message);
}

/*
    Encode the LIN message.
*/
BCI_t_LIN_MSG EncodeLINMessage(uint8_T id, uint8_T length, uint8_T enhancedChecksum, uint8_T* data)
{
    BCI_t_LIN_MSG msg;

    msg.bId = CreateID(id);
    msg.bSendData = 1;
    msg.bLength = length;
    msg.bDummy = 0;
    memcpy(msg.bDataByte, data, 8);

    // Frame identifiers 60 (0x3C) to 61 (0x3D) shall always use classic checksum
    if ((id == 60) || (id == 61) || !enhancedChecksum)
    {
        msg.bModel = LIN_k_CLASSIC;
    }
    else
    {
        msg.bModel = LIN_k_ENHANCED;
    }

    ////msg.bCheckSum = CheckSum(msg);      // TODO: Activate this line

    return msg;
}

#pragma endregion


#pragma region Functions - CAN

/*
    Set all CAN port variables and pointer to their default values.
*/
void CleanupCANPort()
{
    uint32_T i;
    uint32_T j;

    for (i = 0; i < QUANTITY_IO_MODULES; i++)
    {
        sg_IO601_pModule[i].CAN.pStatus = NULL;

        for (j = 0; j < QUANTITY_OF_CAN_PORTS; j++)
        {
            sg_IO601_pModule[i].CAN.CANPort[j].BusRecoveryCounter = 0;
            sg_IO601_pModule[i].CAN.CANPort[j].StartAutoBusRecovery = 0;
            sg_IO601_pModule[i].CAN.CANPort[j].Communication.ReadCounter = 0;
            sg_IO601_pModule[i].CAN.CANPort[j].Communication.WriteCounter = 0;
            sg_IO601_pModule[i].CAN.CANPort[j].Communication.Status = CcsStopCommunication;
            sg_IO601_pModule[i].CAN.CANPort[j].ExtendedAcceptanceCode[0] = 0;
            sg_IO601_pModule[i].CAN.CANPort[j].ExtendedAcceptanceCode[1] = 0;
            sg_IO601_pModule[i].CAN.CANPort[j].ExtendedAcceptanceMask[0] = 0;
            sg_IO601_pModule[i].CAN.CANPort[j].ExtendedAcceptanceMask[1] = 0;
            sg_IO601_pModule[i].CAN.CANPort[j].IsEnabled = 0;
            sg_IO601_pModule[i].CAN.CANPort[j].IsInitializationDone = 0;
            sg_IO601_pModule[i].CAN.CANPort[j].Mode = 0;
            sg_IO601_pModule[i].CAN.CANPort[j].RecoveryStatus = CrsStop;
            sg_IO601_pModule[i].CAN.CANPort[j].StandardAcceptanceCode[0] = 0;
            sg_IO601_pModule[i].CAN.CANPort[j].StandardAcceptanceCode[1] = 0;
            sg_IO601_pModule[i].CAN.CANPort[j].StandardAcceptanceMask[0] = 0;
            sg_IO601_pModule[i].CAN.CANPort[j].StandardAcceptanceMask[1] = 0;
            sg_IO601_pModule[i].CAN.CANPort[j].Status = CpsStopped;
            sg_IO601_pModule[i].PortStatus[j] = CpsStopped;
            sg_IO601_pModule[i].PortStatus[2] = CpsStopped;
            sg_IO601_pModule[i].CAN.CANPort[j].TimingRegisterBRP = 0;
            sg_IO601_pModule[i].CAN.CANPort[j].TimingRegisterSJW = 0;
            sg_IO601_pModule[i].CAN.CANPort[j].TimingRegisterTSEG1 = 0;
            sg_IO601_pModule[i].CAN.CANPort[j].TimingRegisterTSEG2 = 0;
        }
    }
}

/*
    Increment the current CAN queue entry position.
*/
void IncrementCANQueueEntryPosition(uint8_T readWrite, uint32_T moduleIndex, uint32_T port)
{
    if (FIFO_READ == readWrite)
    {
        ////sg_IO601_pModule[moduleIndex].CAN.Communication.ReadCounter[port] = (49 == sg_IO601_pModule[moduleIndex].CAN.Communication.ReadCounter[port]) ? 0 \
                ////                                                            : ++sg_IO601_pModule[moduleIndex].CAN.Communication.ReadCounter[port];

        sg_IO601_pModule[moduleIndex].CAN.CANPort[port].Communication.ReadCounter = (sg_IO601_pModule[moduleIndex].CAN.CANPort[port].Communication.ReadCounter + 1) % 50;
            
    }
    else
    {
        ////sg_IO601_pModule[moduleIndex].CAN.Communication.WriteCounter[port] = (49 == sg_IO601_pModule[moduleIndex].CAN.Communication.WriteCounter[port]) ? 0 \
                ////                                                            : ++sg_IO601_pModule[moduleIndex].CAN.Communication.WriteCounter[port];

        sg_IO601_pModule[moduleIndex].CAN.CANPort[port].Communication.WriteCounter = (sg_IO601_pModule[moduleIndex].CAN.CANPort[port].Communication.WriteCounter + 1) % 50;
            
    }
}


/*
    Initialization of the CAN controller. Return 1 if succeeded.
*/
uint8_T InitializeCANPort(uint32_T moduleIndex, uint8_T CANPort)
{
    uint8_T rtnValue = 0;
    uint32_T counter = 0;

    sg_IO601_pModule[moduleIndex].pCommandPacket->synch = 0;
    sg_IO601_pModule[moduleIndex].pCommandPacket->count = 5;
    sg_IO601_pModule[moduleIndex].pCommandPacket->command = CMD_INIT_CAN;
    sg_IO601_pModule[moduleIndex].pCommandPacket->data[0] = CANPort;
    sg_IO601_pModule[moduleIndex].pCommandPacket->data[1] = ((sg_IO601_pModule[moduleIndex].CAN.CANPort[CANPort].TimingRegisterSJW - 1) << 6) |
        (sg_IO601_pModule[moduleIndex].CAN.CANPort[CANPort].TimingRegisterBRP - 1);
    sg_IO601_pModule[moduleIndex].pCommandPacket->data[2] = ((sg_IO601_pModule[moduleIndex].CAN.CANPort[CANPort].TimingRegisterTSEG2 - 1) << 4) |
        (sg_IO601_pModule[moduleIndex].CAN.CANPort[CANPort].TimingRegisterTSEG1 - 1);
    sg_IO601_pModule[moduleIndex].pCommandPacket->data[3] = 2 | (sg_IO601_pModule[moduleIndex].CAN.CANPort[CANPort].Mode - 1);
    sg_IO601_pModule[moduleIndex].pCommandPacket->synch = 1;

    InterruptMicrocontroller(moduleIndex);

    while (TIMEOUT_FOR_SEND_PACKET > counter)
    {
        if (1 == sg_IO601_pModule[moduleIndex].pCommandPacket->synch)
        {
            sg_wait_s(0.001);
        }
        else if (2 == sg_IO601_pModule[moduleIndex].pCommandPacket->synch)
        {
            rtnValue = sg_IO601_pModule[moduleIndex].pCommandPacket->data[0];
            memset((void*)sg_IO601_pModule[moduleIndex].pCommandPacket, 0x00, sizeof(BCICOMMAND));

            /* DEBUG: Use message only for debugging!!! *
            SG_PRINTF(DEBUG, "\nDEBUG - CAN %i (Port %i) is succesfull intialized.", CANPort, CANPort+1);
            SG_PRINTF(DEBUG, "\n");
            //*/

            break;
        }

        counter++;
    }

    return rtnValue;
}

/*
    Start the CAN controller.
*/
uint8_T StartCANPort(uint32_T moduleIndex, uint8_T CANPort)
{
    uint8_T rtnValue = 0;
    uint32_T counter = 0;

    sg_IO601_pModule[moduleIndex].pCommandPacket->synch = 0;
    sg_IO601_pModule[moduleIndex].pCommandPacket->count = 2;
    sg_IO601_pModule[moduleIndex].pCommandPacket->command = CMD_START_CAN;
    sg_IO601_pModule[moduleIndex].pCommandPacket->data[0] = CANPort;
    sg_IO601_pModule[moduleIndex].pCommandPacket->synch = 1;

    InterruptMicrocontroller(moduleIndex);

    while (TIMEOUT_FOR_SEND_PACKET > counter)
    {
        if (1 == sg_IO601_pModule[moduleIndex].pCommandPacket->synch)
        {
            sg_wait_s(0.001);
        }
        else if (2 == sg_IO601_pModule[moduleIndex].pCommandPacket->synch)
        {
            rtnValue = sg_IO601_pModule[moduleIndex].pCommandPacket->data[0];
            memset((void*)sg_IO601_pModule[moduleIndex].pCommandPacket, 0x00, sizeof(BCICOMMAND));

            /* DEBUG: Use message only for debugging!!! *
            SG_PRINTF(DEBUG, "\nDEBUG - Start of CAN %i (Port %i) was succesfull.", CANPort, CANPort+1);
            SG_PRINTF(DEBUG, "\n");
            //*/

            break;
        }

        counter++;
    }

    if (0 != rtnValue)
    {
        sg_IO601_pModule[moduleIndex].CAN.CANPort[CANPort].Status = CpsRunning;
        sg_IO601_pModule[moduleIndex].PortStatus[CANPort] = CpsRunning;
    }
    return rtnValue;
}

/*
    Prepare the CAN queue entry.

       A CAN entry contains up to 20 elements, which are:
       | n   | standard    | extended    |
       | :-: | :---------: | :---------: |
       | 0   | status      | status      |
       | 1   | count       | count       |
       | 2   | TimeStamp   | TimeStamp   |
       | 3   | TimeStamp   | TimeStamp   |
       | 4   | TimeStamp   | TimeStamp   |
       | 5   | TimeStamp   | TimeStamp   |
       | 6   | Type        | Type        |
       | 7   | Information | Information |
       | 8   | Identifier  | Identifier  |
       | 9   | Identifier  | Identifier  |
       | 10  | Data        | Identifier  |
       | 11  | Data        | Identifier  |
       | 12  | Data        | Data        |
       | 13  | Data        | Data        |
       | 14  | Data        | Data        |
       | 15  | Data        | Data        |
       | 16  | Data        | Data        |
       | 17  | Data        | Data        |
       | 18  | Reserved    | Data        |
       | 19  | Reserved    | Data        |

       TimeStamp is not relevant. Because the MC generates it.
       Type is always 0 for sending
       Information is:
       Bits 0-3: Length (up to 8 bytes).
       Bits 4-5: reserved
       Bits 6  : remote frame (0: data frame, 1: remote frame)
       Bits 7  : frame format (0: standard, 1: extended)
*/
uint8_T PrepareCANQueueEntry(canMsg message, volatile CAN_QUEUEENTRY *pQueue)
{
    uint8_T status;
    uint8_T nBytes;
    uint8_T information;
    uint16_T standardID;
    uint32_T extendedID;

    status = pQueue->word[0] & 0xFF;

    if (0 == status)    // queue is free to be written?
    {
        if (message.Extended)
        {
            status = 1;
            nBytes = 10 + message.Length;
            information = message.Length | (message.Remote << 6) | (message.Extended << 7);
            extendedID = ToMotorola(message.ID, 29);

            pQueue->word[1] = (information << 24);
            pQueue->word[2] = (extendedID);
            pQueue->word[3] = (message.Data[3] << 24) | (message.Data[2] << 16) | (message.Data[1] << 8) | message.Data[0];
            pQueue->word[4] = (message.Data[7] << 24) | (message.Data[6] << 16) | (message.Data[5] << 8) | message.Data[4];
            pQueue->word[0] = (nBytes << 8) | (status);
        }
        else
        {
            status = 1;
            nBytes = 8 + message.Length;
            information = (message.Length) | (message.Remote << 6) | (message.Extended << 7);
            standardID = ToMotorola(message.ID, 11);

            pQueue->word[1] = (information << 24);
            pQueue->word[2] = (message.Data[1] << 24) | (message.Data[0] << 16) | standardID;
            pQueue->word[3] = (message.Data[5] << 24) | (message.Data[4] << 16) | (message.Data[3] << 8) | message.Data[2];
            pQueue->word[4] = (message.Data[7] << 8) | message.Data[6];
            pQueue->word[0] = (nBytes << 8) | (status);
        }
        return 1;
    }
    else
    {
        return 0;
    }
}

/*
    Stop CAN controller.
*/
uint8_T StopCANPort(uint32_T moduleIndex, uint8_T CANPort)
{
    uint8_T rtnValue = 1;
    uint32_T counter = 0;

    if (NULL != sg_IO601_pModule)
    {
        sg_IO601_pModule[moduleIndex].pCommandPacket->synch = 0;
        sg_IO601_pModule[moduleIndex].pCommandPacket->count = 2;
        sg_IO601_pModule[moduleIndex].pCommandPacket->command = CMD_STOP_CAN;
        sg_IO601_pModule[moduleIndex].pCommandPacket->data[0] = CANPort;
        sg_IO601_pModule[moduleIndex].pCommandPacket->synch = 1;

        InterruptMicrocontroller(moduleIndex);

        while (TIMEOUT_FOR_SEND_PACKET > counter)
        {
            if (1 == sg_IO601_pModule[moduleIndex].pCommandPacket->synch)
            {
                sg_wait_s(0.001);
            }
            else if (2 == sg_IO601_pModule[moduleIndex].pCommandPacket->synch)
            {
                rtnValue = sg_IO601_pModule[moduleIndex].pCommandPacket->data[0];
                memset((void*)sg_IO601_pModule[moduleIndex].pCommandPacket, 0x00, sizeof(BCICOMMAND));
                break;
            }

            counter++;
        }
    }

    return rtnValue;
}

/*
	Get the base address of a CAN message queue.
*/
uintptr_t GetCANQueueBaseAddress(uint32_T moduleIndex, uint32_T port, uint8_T fifo)
{
	uint32_T fifoOffset;

	// Determine which of the two output buffers should be used.
	if (fifo == FIFO_WRITE)
	{
		if (port == 0)
		{
			fifoOffset = 0x50;
		}
		else
		{
			fifoOffset = 0x438;
		}
	}
	else
	{
		if (port == 0)
		{
			fifoOffset = 0x820;
		}
		else
		{
			fifoOffset = 0xC08;
		}
	}

	return (uintptr_t)(sg_IO601_pModule[moduleIndex].pIOAddress2) + fifoOffset;
}

/*
    Get the address of a CAN queue entry.
*/
uintptr_t GetCANQueueEntryAddress(uint32_T moduleIndex, uint32_T port, uint8_T fifo)
{
    uint32_T queueOffset;

    ////queueOffset = ptr[moduleID - 1 + 10 * (port - 1)];
    if (FIFO_READ == fifo)
    {
        queueOffset = sg_IO601_pModule[moduleIndex].CAN.CANPort[port].Communication.ReadCounter;
    }
    else
    {
        queueOffset = sg_IO601_pModule[moduleIndex].CAN.CANPort[port].Communication.WriteCounter;
    }

    return (uintptr_t)GetCANQueueBaseAddress(moduleIndex, port, fifo) + (queueOffset * sizeof(CAN_QUEUEENTRY));
}

/*
    Write message in the DPRAM to send CAN message.
*/
int32_T SendCANMessage(uint32_T moduleIndex, uint8_T CANPort, canMsg *pCANMessageInputPort)
{
    uintptr_t address = GetCANQueueEntryAddress(moduleIndex, CANPort, FIFO_WRITE);
    int32_T frc;
    canMsg message = {0};

    memcpy(&message, pCANMessageInputPort, sizeof(message));
    frc = WriteFIFO(address, message);

    /* DEBUG: Use message only for debugging!!! *
    SG_PRINTF(DEBUG, "\nDEBUG - Base address = %#X", sg_IO601_pModule[moduleIndex].pIOAddress2);
    SG_PRINTF(DEBUG, "\nDEBUG - Message address = %#X", address);
    SG_PRINTF(DEBUG, "\nDEBUG - Write counter: = %i", sg_IO601_pModule[moduleIndex].CAN.CANPort[CANPort].Communication.WriteCounter);
    SG_PRINTF(DEBUG, "\nDEBUG - Message.ID = %i", message.ID);
    SG_PRINTF(DEBUG, "\nDEBUG - Message.Extended = %#X", message.Extended);
    SG_PRINTF(DEBUG, "\nDEBUG - Message.Length = %i", message.Length);
    SG_PRINTF(DEBUG, "\nDEBUG - Message.Error = %#X", message.Error);
    SG_PRINTF(DEBUG, "\nDEBUG - Message.Remote = %#X", message.Remote);
    SG_PRINTF(DEBUG, "\nDEBUG - Message.Timestamp = %f", message.Timestamp);
    SG_PRINTF(DEBUG, "\nDEBUG - Data = %X-%X-%X-%X-%X-%X-%X-%X", message.Data[0], message.Data[1], message.Data[2], message.Data[3], message.Data[4], message.Data[5],
    message.Data[6], message.Data[7]);
    SG_PRINTF(DEBUG, "\nDEBUG - frc = %i", frc);
    SG_PRINTF(DEBUG, "\n");
    //*/

    if (frc == 0)
    {
        // Succes: Increment the buffer position to prepare the next access.
        InterruptMicrocontroller(moduleIndex);
        ////sg_wait_s(0.001);
        IncrementCANQueueEntryPosition(FIFO_WRITE, moduleIndex, CANPort);
    }

    return frc;
}


/*
Write message in the DPRAM to send CAN message.
*/
int32_T IO601_CANSendMessage(uint32_T moduleIndex, uint8_T CANPort, canMsg *pCANMessageInputPort)
{
    uintptr_t address = GetCANQueueEntryAddress(moduleIndex, CANPort, FIFO_WRITE);
    int32_T frc;
    // DELETE_: canMsg message = {{0}};

    // DELETE_: memcpy(&message, pCANMessageInputPort, sizeof(message));

    ////SG_PRINTF(DEBUG, "\nDbg - Snd id: %i -- data: %i", pCANMessageInputPort->ID, pCANMessageInputPort->Data[0]);

    frc = IO601_CANWriteFIFO(address, pCANMessageInputPort);

    /* DEBUG: Use message only for debugging!!! *
    SG_PRINTF(DEBUG, "\nDEBUG - Base address = %#X", sg_IO601_pModule[moduleIndex].pIOAddress2);
    SG_PRINTF(DEBUG, "\nDEBUG - Message address = %#X", address);
    SG_PRINTF(DEBUG, "\nDEBUG - Write counter: = %i", sg_IO601_pModule[moduleIndex].CAN.CANPort[CANPort].Communication.WriteCounter);
    SG_PRINTF(DEBUG, "\nDEBUG - Message.ID = %i", message.ID);
    SG_PRINTF(DEBUG, "\nDEBUG - Message.Extended = %#X", message.Extended);
    SG_PRINTF(DEBUG, "\nDEBUG - Message.Length = %i", message.Length);
    SG_PRINTF(DEBUG, "\nDEBUG - Message.Error = %#X", message.Error);
    SG_PRINTF(DEBUG, "\nDEBUG - Message.Remote = %#X", message.Remote);
    SG_PRINTF(DEBUG, "\nDEBUG - Message.Timestamp = %f", message.Timestamp);
    SG_PRINTF(DEBUG, "\nDEBUG - Data = %X-%X-%X-%X-%X-%X-%X-%X", message.Data[0], message.Data[1], message.Data[2], message.Data[3], message.Data[4], message.Data[5],
    message.Data[6], message.Data[7]);
    SG_PRINTF(DEBUG, "\nDEBUG - frc = %i", frc);
    SG_PRINTF(DEBUG, "\n");
    //*/


    if (frc == 0)
    {
        // Succes: Increment the buffer position to prepare the next access.
        ////InterruptMicrocontroller(moduleIndex);
        ////sg_wait_s(0.001);
        ////IncrementCANQueueEntryPosition(FIFO_WRITE, moduleIndex, CANPort);
        uint8_T wrtIdx = sg_IO601_pModule[moduleIndex].CAN.CANPort[CANPort].Communication.WriteCounter;
        sg_IO601_pModule[moduleIndex].CAN.CANPort[CANPort].Communication.WriteCounter = (wrtIdx + 1) % 50;
        return 1;
    }
/* TODO: activate for debugging *
    else
    {
        SG_PRINTF(DEBUG, "\nDbg - frc: %i  -- modIdx: %i - portIdx: %i - wrtCnt: %i (%i)", frc, moduleIndex, CANPort
               , sg_IO601_pModule[moduleIndex].CAN.CANPort[CANPort].Communication.WriteCounter, sg_IO601_pModule[moduleIndex].CAN.CANPort[CANPort].Communication.ReadCounter);
        
    }

/* END TODO ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    return 0;
}


/*
Write FIFO
*/
uint32_T IO601_CANWriteFIFO(uintptr_t queueEntryAddress, canMsg *pMessage)
{
    int32_T frc = 0;
    volatile CAN_QUEUEENTRY *pQueue;

    switch (pMessage->Extended)
    {
        case 0:
            if (pMessage->ID > 2047)
            {
                frc = -12; //in standard, identifer cannot be larger than 2^11 - 1
            }
            break;
        case 1:
            if (pMessage->ID > 536870911)
            {
                frc = -13; //in extended, identifer cannot be larger than 2^19 - 1
            }
            break;
        default:
            frc = -11; // not a correct frame format.
            break;
    }

    if (pMessage->Length > 8)
    {
        frc = -14;
    }

    // when the frames passed all the tests, we send it. A negative ident is a "don't send this message" flag.
    if (frc == 0 && pMessage->ID >= 0)
    {
        pQueue = (CAN_QUEUEENTRY *)(queueEntryAddress);

        // now the CAN message has to be placed in the queueentry.
        if (0 == IO601_CANPrepareCANQueueEntry(pMessage, pQueue))
        {
            frc = -1; /* the queue entry wasn't free. */
        }
    }
    else
    {
        frc = -15;
    }

    return frc;

}

uint8_T IO601_CANPrepareCANQueueEntry(canMsg *pMessage, volatile CAN_QUEUEENTRY *pQueue)
{
    uint8_T status;
    uint8_T nBytes;
    uint8_T information;
    uint16_T standardID;
    uint32_T extendedID;

    status = pQueue->word[0] & 0xFF;

    if (0 == status)    // queue is free to be written?
    {
        if (pMessage->Extended)
        {
            status = 1;
            nBytes = 10 + pMessage->Length;
            information = pMessage->Length | (pMessage->Remote << 6) | (pMessage->Extended << 7);
            extendedID = ToMotorola(pMessage->ID, 29);

            pQueue->word[1] = (information << 24);
            pQueue->word[2] = (extendedID);
            pQueue->word[3] = (pMessage->Data[3] << 24) | (pMessage->Data[2] << 16) | (pMessage->Data[1] << 8) | pMessage->Data[0];
            pQueue->word[4] = (pMessage->Data[7] << 24) | (pMessage->Data[6] << 16) | (pMessage->Data[5] << 8) | pMessage->Data[4];
            pQueue->word[0] = (nBytes << 8) | (status);
        }
        else
        {
            status = 1;
            nBytes = 8 + pMessage->Length;
            information = (pMessage->Length) | (pMessage->Remote << 6) | (pMessage->Extended << 7);
            standardID = ToMotorola(pMessage->ID, 11);

            pQueue->word[1] = (information << 24);
            pQueue->word[2] = (pMessage->Data[1] << 24) | (pMessage->Data[0] << 16) | standardID;
            pQueue->word[3] = (pMessage->Data[5] << 24) | (pMessage->Data[4] << 16) | (pMessage->Data[3] << 8) | pMessage->Data[2];
            pQueue->word[4] = (pMessage->Data[7] << 8) | pMessage->Data[6];
            pQueue->word[0] = (nBytes << 8) | (status);
        }
        return 1;
    }
    else
    {
        ////SG_PRINTF(DEBUG, "\nDbg - status: %i  --  info: %#X", pQueue->word[0] & 0xFF, pQueue->word[1]>>24);
        return 0;
    }
}


#pragma endregion


#pragma region Functions - LIN controller handling

/*
    Reset LIN controller
*/
uint8_T ResetLIN(uint32_T moduleIndex)
{
    uint8_T rtnValue = 0;
    uint32_T counter = 0;

    sg_IO601_pModule[moduleIndex].pCommandPacket->synch = 0;
    sg_IO601_pModule[moduleIndex].pCommandPacket->count = 2;
    sg_IO601_pModule[moduleIndex].pCommandPacket->command = CMD_RESET_LIN;
    sg_IO601_pModule[moduleIndex].pCommandPacket->synch = 1;

    while (TIMEOUT_FOR_SEND_PACKET > counter)
    {
        if (1 == sg_IO601_pModule[moduleIndex].pCommandPacket->synch)
        {
            InterruptMicrocontroller(moduleIndex);
            sg_wait_s(0.001);
        }
        else if (2 == sg_IO601_pModule[moduleIndex].pCommandPacket->synch)
        {
            rtnValue = sg_IO601_pModule[moduleIndex].pCommandPacket->data[0];
            memset((void*)sg_IO601_pModule[moduleIndex].pCommandPacket, 0x00, sizeof(BCICOMMAND));
            break;
        }

        counter++;
    }

    if (1 == rtnValue)
    {
        //SG_PRINTF(DEBUG, "\nINFO - Reset of LIN controller was succesfull.");
    }
    else if (2 == rtnValue)
    {
        //SG_PRINTF(DEBUG, "\nINFO - Command reset LIN controller is not supported.");
        rtnValue = 0;
    }

    return rtnValue;
}

/*
    Initialize LIN controller
*/
uint8_T InitializeLIN(uint32_T moduleIndex, uint8_T role, uint16_T baudrate)
{
    uint8_T rtnValue = 0;
    uint32_T counter = 0;

    sg_IO601_pModule[moduleIndex].pCommandPacket->synch = 0;
    sg_IO601_pModule[moduleIndex].pCommandPacket->count = 6;
    sg_IO601_pModule[moduleIndex].pCommandPacket->command = CMD_INIT_LIN;
    sg_IO601_pModule[moduleIndex].pCommandPacket->data[1] = (1 == role) ? 1 : 0;
    sg_IO601_pModule[moduleIndex].pCommandPacket->data[3] = baudrate & 0xFF;
    sg_IO601_pModule[moduleIndex].pCommandPacket->data[4] = (baudrate >> 8) & 0xFF;
    sg_IO601_pModule[moduleIndex].pCommandPacket->synch = 1;
    sg_IO601_pModule[moduleIndex].LIN.ErrIdx = 0;
    sg_IO601_pModule[moduleIndex].LIN.ErrIdxRd = 64;

    while (TIMEOUT_FOR_SEND_PACKET > counter)
    {
        if (1 == sg_IO601_pModule[moduleIndex].pCommandPacket->synch)
        {
            InterruptMicrocontroller(moduleIndex);
            sg_wait_s(0.001);
        }
        else if (2 == sg_IO601_pModule[moduleIndex].pCommandPacket->synch)
        {
            rtnValue = sg_IO601_pModule[moduleIndex].pCommandPacket->data[0];
            memset((void*)sg_IO601_pModule[moduleIndex].pCommandPacket, 0x00, sizeof(BCICOMMAND));
            break;
        }

        counter++;
    }

    if (1 == rtnValue)
    {
        //SG_PRINTF(DEBUG, "\nINFO - Initialize of LIN controller was succesfull.");
    }
    else if (2 == rtnValue)
    {
        //SG_PRINTF(DEBUG, "\nINFO - Command initialize LIN controller is not supported.");
        rtnValue = 0;
    }

    sg_IO601_pModule[moduleIndex].LIN.IsMaster = (1 == role) ? true : false;
    return rtnValue;
}

/*
    Start LIN controller
*/
uint8_T StartLIN(uint32_T moduleIndex)
{
    uint8_T rtnValue = 0;
    uint32_T counter = 0;

    sg_IO601_pModule[moduleIndex].pCommandPacket->synch = 0;
    sg_IO601_pModule[moduleIndex].pCommandPacket->count = 2;
    sg_IO601_pModule[moduleIndex].pCommandPacket->command = CMD_START_LIN;
    sg_IO601_pModule[moduleIndex].pCommandPacket->synch = 1;

    while (TIMEOUT_FOR_SEND_PACKET > counter)
    {
        if (1 == sg_IO601_pModule[moduleIndex].pCommandPacket->synch)
        {
            InterruptMicrocontroller(moduleIndex);
            sg_wait_s(0.001);
        }
        else if (2 == sg_IO601_pModule[moduleIndex].pCommandPacket->synch)
        {
            rtnValue = sg_IO601_pModule[moduleIndex].pCommandPacket->data[0];
            memset((void*)sg_IO601_pModule[moduleIndex].pCommandPacket, 0x00, sizeof(BCICOMMAND));
            break;
        }

        counter++;
    }

    if (1 == rtnValue)
    {
        //SG_PRINTF(DEBUG, "\nINFO - Start of LIN controller was succesfull.");
        sg_IO601_pModule[moduleIndex].PortStatus[2] = CpsRunning;

    }
    else if (2 == rtnValue)
    {
        SG_PRINTF(INFO, "\nINFO - Command start LIN controller is not supported.");
        rtnValue = 0;
    }

    return rtnValue;
}

/*
    Stop LIN controller
*/
uint8_T StopLIN(uint32_T moduleIndex)
{
    uint8_T rtnValue = 1;

    if (NULL != sg_IO601_pModule)
    {
        uint32_T counter = 0;

        sg_IO601_pModule[moduleIndex].pCommandPacket->synch = 0;
        sg_IO601_pModule[moduleIndex].pCommandPacket->count = 2;
        sg_IO601_pModule[moduleIndex].pCommandPacket->command = CMD_STOP_LIN;
        sg_IO601_pModule[moduleIndex].pCommandPacket->synch = 1;

        while (TIMEOUT_FOR_SEND_PACKET > counter)
        {
            if (1 == sg_IO601_pModule[moduleIndex].pCommandPacket->synch)
            {
                InterruptMicrocontroller(moduleIndex);
                sg_wait_s(0.001);
            }
            else if (2 == sg_IO601_pModule[moduleIndex].pCommandPacket->synch)
            {
                rtnValue = sg_IO601_pModule[moduleIndex].pCommandPacket->data[0];
                memset((void*)sg_IO601_pModule[moduleIndex].pCommandPacket, 0x00, sizeof(BCICOMMAND));
                break;
            }

            counter++;
        }

        if (1 == rtnValue)
        {
            //SG_PRINTF(DEBUG, "\nINFO - Stop of LIN controller was succesfull.");
        }
        else if (2 == rtnValue)
        {
            //SG_PRINTF(DEBUG, "\nINFO - Command stop LIN controller is not supported.");
            rtnValue = 0;
        }
    }

    return rtnValue;
}

/*
    Check and set the value of the LIN status semaphore

- [NEW]: boolean_T IO601_LINChkStateSema(uint32_T modIdx, boolean_T isSemaLock)
    * Check and set the value of the LIN status semaphore
*/
boolean_T IO601_LINChkStateSema(uint32_T modIdx, boolean_T isSemaLock)
{
    t_semaphores *pSema = (t_semaphores *)(sg_IO601_pModule[modIdx].pIOAddress2 + 0x2000);

    if (isSemaLock)
    {
        if (0 != pSema->LINStatusBuffer)
        {
            pSema->LINStatusBuffer = 0;
            return false;
        }
    }
    else
    {
        pSema->LINStatusBuffer = 1;
    }

    return true;
}

/*
Get LIN status Role

*/
void IO601_LINStatusRole(uint32_T modIdx, uint32_T *pRole)
{
    LINStatus *pStat = (LINStatus*)(sg_IO601_pModule[modIdx].pIOAddress2 + 0x1898);
    *pRole = (uint32_T)pStat->Role;
}


/*
Get LIN status busload

*/
void IO601_LINStatusBusload(uint32_T modIdx, uint32_T *pBusload)
{
    LINStatus *pStat = (LINStatus*)(sg_IO601_pModule[modIdx].pIOAddress2 + 0x1898);
    *pBusload = (uint32_T)pStat->Busload;
}


/*
Get LIN status bitrate

*/
void IO601_LINStatusBitrate(uint32_T modIdx, uint32_T *pBitrate)
{
    LINStatus *pStat = (LINStatus*)(sg_IO601_pModule[modIdx].pIOAddress2 + 0x1898);
    *pBitrate = (uint32_T)pStat->Bitrate;
}


/*
Get LIN status status

*/
void IO601_LINStatusStatus(uint32_T modIdx, uint32_T *pStatus)
{
    LINStatus *pStat = (LINStatus*)(sg_IO601_pModule[modIdx].pIOAddress2 + 0x1898);
    *pStatus = (uint32_T)pStat->Status;
}


#pragma endregion

#pragma region Functions - LIN message buffer handling

/*
Add LIN message to the global message buffer

*/
boolean_T IO601_LINAddMsgToBuf(uint32_T modIdx, uint8_T protID, uint8_T blkType, boolean_T enaToSnd, boolean_T isSndData, boolean_T isChkSumV2x, uint8_T dlc,
                               real_T sampleTime, uint8_T qtyMsg, uint8_T *pDefMsgData)
{
    if (NULL != pDefMsgData)
    {
        uint8_T i = 0;

        for (i = 0; i < dlc; i++)
        {
            sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].Data[i] = pDefMsgData[i];
        }
    }

    sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].DLC = dlc;
    sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].FullProtID = CreateID(protID);
    sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].IsEnhcdChksum = isChkSumV2x;
    sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].Chksum = CheckSum(modIdx, protID);
    sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].SampelTime = sampleTime;
    sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].isSndData = isSndData;
    sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].BlkType = (IO601_BlockType)blkType;
    sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].UpdState = 1;
    sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].EnaToSend = enaToSnd;
    sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].ConsNo = sg_IO601_pModule[modIdx].LIN.ConsNoLIN++;

    if (sg_IO601_pModule[modIdx].LIN.ConsNoLIN == qtyMsg)
    {
        IO601_SetGlbSndRec(modIdx);
    }

    return true;
}

/*
Set the global sender and receiver message of the LIN driver.

*/
boolean_T IO601_SetGlbSndRec(uint32_T modIdx)
{
    uint8_T protIDSnd = 0;
    uint8_T protIDRec = 0;

    // Find sample time, global sender and receiver
    protIDSnd = IO601_FndGlbSender(modIdx);
    protIDRec = IO601_FndGlbReceiver(modIdx);


    //SG_PRINTF(DEBUG, "\nDbg - global sender modID: %i", protIDSnd);
    //SG_PRINTF(DEBUG, "\nDbg - global receiv modID: %i", protIDRec);


    // Set global sender and receiver
    sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protIDSnd].BlkType |= BtGlbSender;
    sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protIDRec].BlkType |= BtGlbReceiver;
    return true;
}

/*
Find the module with the lowest sample time and the highest module ID and define it as global sender.

*/
uint8_T IO601_FndGlbSender(uint32_T modIdx)
{
    uint8_T i = 0;
    uint8_T protID = 0;
    uint8_T consNo = 0;
    real_T sampleTime = 99999.9;

    for (i = 0; i < 64; i++)
    {
        if (BtSender & sg_IO601_pModule[modIdx].LIN.LINMsgBuf[i].BlkType)
        {
            if (sg_IO601_pModule[modIdx].LIN.LINMsgBuf[i].SampelTime < sampleTime)
            {
                sampleTime = sg_IO601_pModule[modIdx].LIN.LINMsgBuf[i].SampelTime;
                consNo = sg_IO601_pModule[modIdx].LIN.LINMsgBuf[i].ConsNo;
                protID = i;
            }
            else if (sg_IO601_pModule[modIdx].LIN.LINMsgBuf[i].SampelTime == sampleTime)
            {
                if (sg_IO601_pModule[modIdx].LIN.LINMsgBuf[i].ConsNo >= consNo)
                {
                    consNo = sg_IO601_pModule[modIdx].LIN.LINMsgBuf[i].ConsNo;
                    protID = i;
                }
            }
        }
    }

    return protID;
}

/*
Find the module with the lowest sample time and the lowest module ID and define it as global receiver.

*/
uint8_T IO601_FndGlbReceiver(uint32_T modIdx)
{
    uint8_T i = 0;
    uint8_T protID = 0;
    uint8_T consNo = 100;
    real_T sampleTime = 9999.9;

    for (i = 0; i < 64; i++)
    {
        if (BtReceiver & sg_IO601_pModule[modIdx].LIN.LINMsgBuf[i].BlkType)
        {
            if (sg_IO601_pModule[modIdx].LIN.LINMsgBuf[i].SampelTime < sampleTime)
            {
                sampleTime = sg_IO601_pModule[modIdx].LIN.LINMsgBuf[i].SampelTime;
                consNo = sg_IO601_pModule[modIdx].LIN.LINMsgBuf[i].ConsNo;
                protID = i;
            }
            else if (sg_IO601_pModule[modIdx].LIN.LINMsgBuf[i].SampelTime == sampleTime)
            {
                if (sg_IO601_pModule[modIdx].LIN.LINMsgBuf[i].ConsNo < consNo)
                {
                    consNo = sg_IO601_pModule[modIdx].LIN.LINMsgBuf[i].ConsNo;
                    protID = i;
                }
            }
        }
    }

    return protID;
}

/*
Copy the values of the input port to the corresponding message in the global message buffer.

*/
void IO601_SetMsgData(uint8_T modIdx, uint8_T protID, uint8_T *pData)
{
    if (NULL != pData)
    {
        uint8_T i = 0;

        for (i = 0; i < sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].DLC; i++)
        {
            sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].Data[i] = pData[i];
        }

        sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].Chksum = CheckSum(modIdx, protID);
    }

    sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].EnaToSend = true;
}

/*
Get the message state of the corresponding LIN message by protected ID from the global message buffer

*/
void IO601_LINGetMsgState(uint32_T modIdx, uint8_T protID, int32_T *pMsgState)
{
    *pMsgState = sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].UpdState;
}

/*
    Get the information of the LIN message

*/
void IO601_LINGetMsgInfo(uint32_T modIdx, uint8_T protID, int32_T *pInfo)
{
    *pInfo = (int32_T)sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].MsgInfo;
}

/*
    Get error message for the LIN message only possible for LIN master.

*/
void IO601_LINGetMsgError(uint32_T modIdx, uint8_T protID, int32_T *pErr)
{
    *pErr = (int32_T)sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].ErrCode;
}

/*
Get the timestamp of the corresponding LIN message by protected ID from the global message buffer

*/
void IO601_LINGetMsgTstp(uint32_T modIdx, uint8_T protID, uint32_T *pTstp)
{
    *pTstp = sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].Tstp;
}

/*
Get message data of the corresponding LIN message by protected ID from the global message buffer

*/
void IO601_LINGetMsgData(uint32_T modIdx, uint8_T protID, uint8_T *pData)
{
    if (1 == sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].UpdState)
    {
        memcpy(pData, sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].Data,
                 sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].DLC);
        sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].UpdState = 0;
    }
}

/*
Check the global message buffer if value is not set then check if an error is available and assign the error code.

*/
void IO601_ChkErrMsg(uint32_T modIdx)
{
    uint8_T i = 0;
    uint8_T errIdx = 0;

    for (i = 0; i < 64; i++)
    {
        if (5 == sg_IO601_pModule[modIdx].LIN.LINMsgBuf[i].UpdState)
        {
            sg_IO601_pModule[modIdx].LIN.LINMsgBuf[i].UpdState = -1;
            sg_IO601_pModule[modIdx].LIN.LINMsgBuf[i].ErrCode = sg_IO601_pModule[modIdx].LIN.ErrCodes[errIdx++];
        }
    }
}

/*
*   Cleanup all messages in the LIN message queues
*/
void LINCleanupMsgBuffer(uint32_T modIdx)
{
    LINQueueEntry_T *pQueueSnd = (LINQueueEntry_T*)((uintptr_t)sg_IO601_pModule[modIdx].pIOAddress2 + 0x1000);
    LINQueueEntry_T *pQueueRec = (LINQueueEntry_T*)((uintptr_t)sg_IO601_pModule[modIdx].pIOAddress2 + 0x144C);
    uint8_T i = 0;

    for (i = 0; i < 50; i++)
    {
        pQueueSnd[i].status = 0;
        pQueueRec[i].status = 0;

        ////SG_PRINTF(DEBUG, "\nDbg - snd buf status: %i  --  rec buf status: %i", pQueueSnd[i].status, pQueueRec[i].status);
    }
}

#pragma endregion

#pragma region Functions - LIN send and receive handling

/*
Check if LIN message block is global sender if yes write all LIN messages to the send queue of the device.

*/
boolean_T IO601_LINWrtMsgToSndQueue(uint32_T modIdx, uint8_T protID)
{
    boolean_T rtnVal = true;

    if (BtGlbSender == (BtGlbSender & sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].BlkType))
    {
        uint8_T i = 0;
        LINQueueEntry_T *pQueue = NULL;

        for (i = 0; i < 64; i++)
        {
            if (sg_IO601_pModule[modIdx].LIN.LINMsgBuf[i].EnaToSend)
            {
                rtnVal = IO601_LINWrtMsg(modIdx, i);
            }
        }

        InterruptMicrocontroller(modIdx);
    }

    return rtnVal;
}

/*
Write the LIN message to the send queue and trigger the interrupt of the LIN controller to send the message.

*/
boolean_T IO601_LINWrtMsg(uint32_T modIdx, uint8_T protID)
{
    LINQueueEntry_T *pQueue = NULL;

    pQueue = (LINQueueEntry_T*)((uintptr_t)sg_IO601_pModule[modIdx].pIOAddress2 + 0x1000 + (sg_IO601_pModule[modIdx].LIN.WriteIndex * sizeof(LINQueueEntry_T)));
    
    IO601_SleepMilliseconds(0.1);

    if (0 == pQueue->status)
    {
        pQueue->count = 12 + sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].DLC;
        pQueue->type = 0;
        pQueue->information = 0;
        pQueue->sMsg.bId = sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].FullProtID;
        pQueue->sMsg.bModel = sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].IsEnhcdChksum;
        pQueue->sMsg.bCheckSum = sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].Chksum;
        pQueue->sMsg.bSendData = sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].isSndData;
        pQueue->sMsg.bLength = sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].DLC;
        pQueue->sMsg.bDummy = 0;
        pQueue->sMsg.bDataByte[0] = sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].Data[0];
        pQueue->sMsg.bDataByte[1] = sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].Data[1];
        pQueue->sMsg.bDataByte[2] = sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].Data[2];
        pQueue->sMsg.bDataByte[3] = sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].Data[3];
        pQueue->sMsg.bDataByte[4] = sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].Data[4];
        pQueue->sMsg.bDataByte[5] = sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].Data[5];
        pQueue->sMsg.bDataByte[6] = sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].Data[6];
        pQueue->sMsg.bDataByte[7] = sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].Data[7];
        pQueue->status = 1;
        sg_IO601_pModule[modIdx].LIN.WriteIndex = (sg_IO601_pModule[modIdx].LIN.WriteIndex < 49) ? sg_IO601_pModule[modIdx].LIN.WriteIndex + 1 : 0;
        sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].EnaToSend = false;
        sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].UpdState = 5;
        return true;
    }

    return false;
}

/*
Read LIN message from the receive queue and save the values in the corresponding message in the global message buffer.

*/
void IO601_LINRstSndMsgInRecQueue(uint32_T modIdx)
{
    LINQueueEntry_T *pQueue = (LINQueueEntry_T*)((uintptr_t)sg_IO601_pModule[modIdx].pIOAddress2 + 0x144C + (sg_IO601_pModule[modIdx].LIN.ReadIndex * sizeof(LINQueueEntry_T)));
    uint8_T readIndex = 0;

    if (pQueue->status && pQueue->sMsg.bSendData)
    {
        pQueue->status = 0;
    }
}

/*
Check if the message block is global receiver if yes then read all LIN messages from the receive queue.

*/
boolean_T IO601_LINRdMsgFromRecQueue(uint32_T modIdx, uint8_T protID)
{
    boolean_T rtnVal = true;

    if (BtGlbReceiver == (BtGlbReceiver & sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].BlkType))
    {
        uint8_T readIdx = 0;
        uint8_T errIdx = 0;
        uint8_T msgID = 0;
        LINQueueEntry_T *pQueue = NULL;

        while (readIdx < 50)
        {
            pQueue = (LINQueueEntry_T*)((uintptr_t)sg_IO601_pModule[modIdx].pIOAddress2 + 0x144C + (readIdx * sizeof(LINQueueEntry_T)));

            if (1 == pQueue->status)
            {
                msgID = pQueue->sMsg.bId & 0x3F;

                if (!sg_IO601_pModule[modIdx].LIN.LINMsgBuf[msgID].isSndData)
                {


                    sg_IO601_pModule[modIdx].LIN.LINMsgBuf[msgID].MsgType = pQueue->type;
                    sg_IO601_pModule[modIdx].LIN.LINMsgBuf[msgID].MsgInfo = pQueue->information;

                    if (0 == pQueue->type)
                    {
                        sg_IO601_pModule[modIdx].LIN.LINMsgBuf[msgID].Data[0] = pQueue->sMsg.bDataByte[0];
                        sg_IO601_pModule[modIdx].LIN.LINMsgBuf[msgID].Data[1] = pQueue->sMsg.bDataByte[1];
                        sg_IO601_pModule[modIdx].LIN.LINMsgBuf[msgID].Data[2] = pQueue->sMsg.bDataByte[2];
                        sg_IO601_pModule[modIdx].LIN.LINMsgBuf[msgID].Data[3] = pQueue->sMsg.bDataByte[3];
                        sg_IO601_pModule[modIdx].LIN.LINMsgBuf[msgID].Data[4] = pQueue->sMsg.bDataByte[4];
                        sg_IO601_pModule[modIdx].LIN.LINMsgBuf[msgID].Data[5] = pQueue->sMsg.bDataByte[5];
                        sg_IO601_pModule[modIdx].LIN.LINMsgBuf[msgID].Data[6] = pQueue->sMsg.bDataByte[6];
                        sg_IO601_pModule[modIdx].LIN.LINMsgBuf[msgID].Data[7] = pQueue->sMsg.bDataByte[7];
                        sg_IO601_pModule[modIdx].LIN.LINMsgBuf[msgID].ErrCode = 0;
                        sg_IO601_pModule[modIdx].LIN.LINMsgBuf[msgID].Tstp = *(uint32_T*)pQueue->timeStamp;
                        sg_IO601_pModule[modIdx].LIN.LINMsgBuf[msgID].UpdState = 1;
                    }
                    else if (2 == pQueue->type)
                    {
                        uint8_T *pErrCode = (uint8_T*)&sg_IO601_pModule[modIdx].LIN.ErrCodes[errIdx++];

                        pErrCode[0] = pQueue->sMsg.bId;
                        pErrCode[1] = pQueue->sMsg.bModel;
                    }
                    else
                    {
                        sg_IO601_pModule[modIdx].LIN.LINMsgBuf[msgID].UpdState = 0;
                    }

                    pQueue->status = 0;

                }
                else
                {
                    pQueue->status = 0;
                }


            }

            readIdx++;
        }

        if (sg_IO601_pModule[modIdx].LIN.IsMaster)
        {
            IO601_ChkErrMsg(modIdx);
        }

    }

    return true;
}

/*
Write the LIN message update into the slave send queue.

*/
boolean_T IO601_LINSlvWrtMsgToQueue(uint32_T modIdx, uint8_T protID)
{
    boolean_T rtnVal = true;

    if (BtGlbSender & (sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].BlkType))
    {
        boolean_T upd1 = true;
        boolean_T upd2 = false;
        uint8_T i = 0;

        for (i = 0; i < 64; i++)
        {
            upd1 = IO601_LINSlvWrtMsgBuf(modIdx, i);

            if (!upd1)
            {
                SG_PRINTF(ERROR, "\nError - Update LIN message filter failed for ProtID: %i", i);
                rtnVal = false;
                break;
            }
        }
    }

    return rtnVal;
}

/*
Write the LIN message to the corresponding queue index in the slave send queue.


*/
boolean_T IO601_LINSlvWrtMsgBuf(uint32_T modIdx, uint8_T protID)
{
    boolean_T updVal1 = false;
    boolean_T updVal2 = false;
    uint8_T timeout = 0;
    BCI_t_LIN_MSG *pMsg = NULL;
    t_semaphores *pSema = (t_semaphores *)(sg_IO601_pModule[modIdx].pIOAddress2 + 0x2000);

    // Set semaphore 1
    if (pSema->LINUpdateBuffer1 & 1)
    {
        while ((pSema->LINUpdateBuffer1 & 1) != 0)
        {
            pSema->LINUpdateBuffer1 &= ~1;
        }
    }

    while (timeout < 5)
    {
        if (pSema->LINUpdateBuffer1 == 0)
        {
            pMsg = (BCI_t_LIN_MSG *)(sg_IO601_pModule[modIdx].pIOAddress2 + 0x18A8 + (protID * sizeof(BCI_t_LIN_MSG)));
            pMsg->bId = sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].FullProtID;
            pMsg->bSendData = sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].isSndData;
            pMsg->bLength = sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].DLC;
            pMsg->bDummy = 0;
            pMsg->bModel = sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].IsEnhcdChksum;
            sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].EnaToSend = false;

            if (sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].isSndData)
            {
                memcpy(pMsg->bDataByte, sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].Data, pMsg->bLength);
                pMsg->bCheckSum = sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].Chksum;
            }

            pSema->LINUpdateBuffer1 |= 1;
            updVal1 = true;
            break;
        }

        IO601_SleepMilliseconds(0.0001);
        timeout += 1;
    }

    // Set Semaphore 2
    timeout = 0;

    if (pSema->LINUpdateBuffer2 & 1)
    {
        while ((pSema->LINUpdateBuffer2 & 1) != 0)
        {
            pSema->LINUpdateBuffer2 &= ~1;
        }
    }

    while (timeout < 5)
    {
        if (pSema->LINUpdateBuffer2 == 0)
        {
            pMsg = (BCI_t_LIN_MSG *)(sg_IO601_pModule[modIdx].pIOAddress2 + 0x1C28 + (protID * sizeof(BCI_t_LIN_MSG)));
            pMsg->bId = sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].FullProtID;
            pMsg->bSendData = sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].isSndData;
            pMsg->bLength = sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].DLC;
            pMsg->bDummy = 0;
            pMsg->bModel = sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].IsEnhcdChksum;
            sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].EnaToSend = false;

            if (sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].isSndData)
            {
                memcpy(pMsg->bDataByte, sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].Data, pMsg->bLength);
                pMsg->bCheckSum = sg_IO601_pModule[modIdx].LIN.LINMsgBuf[protID].Chksum;
            }

            pSema->LINUpdateBuffer2 |= 1;
            updVal2 = true;
            break;
        }

        IO601_SleepMilliseconds(0.0001);
        timeout += 1;
    }

    return updVal1 && updVal2;
}

void IO601_SleepMilliseconds(real_T milliseconds)
{
    sg_wait_s(milliseconds / 1000.0);
}

#pragma endregion


#pragma region Functions - Concurrent Execution CAN

/////*
////*   Set the concurrent execution handler for CAN.
////*/
////boolean_T IO601_CANSetConCurExeHdl(uint32_T modIdx)
////{
////    return IO601_CANCreateConCurExeHdl(&sg_IO601_pModule[modIdx].CAN.pConCurExeHdl);
////}
////
/////*
////*   Clear the concurrent execution handler for CAN
////*/
////void IO601_CANClearConCurExeHdl()
////{
////    uint8_T i = 0;
////
////    for (i = 0; i < QUANTITY_IO_MODULES; i++)
////    {
////        IO601_CANDeleteConCurExeHdl(&sg_IO601_pModule[i].CAN.pConCurExeHdl);
////
////        if (NULL != sg_IO601_pModule[i].CAN.CANPort[0].ConCurExe.GlbSnd.pQueueAddr)
////        {
////            free(sg_IO601_pModule[i].CAN.CANPort[0].ConCurExe.GlbSnd.pQueueAddr);
////            sg_IO601_pModule[i].CAN.CANPort[0].ConCurExe.GlbSnd.pQueueAddr = NULL;
////        }
////
////        if (NULL != sg_IO601_pModule[i].CAN.CANPort[1].ConCurExe.GlbSnd.pQueueAddr)
////        {
////            free(sg_IO601_pModule[i].CAN.CANPort[1].ConCurExe.GlbSnd.pQueueAddr);
////            sg_IO601_pModule[i].CAN.CANPort[1].ConCurExe.GlbSnd.pQueueAddr = NULL;
////        }
////    }
////}
////
/////*
////*   Set the size of the send queue array addresses of the module.
////*/
////boolean_T IO601_SetSndQueueArray(uint32_T modIdx, uint8_T ptIdx, uint32_T qtySndBlocks)
////{
////    if (NULL == sg_IO601_pModule[modIdx].CAN.CANPort[ptIdx].ConCurExe.GlbSnd.pQueueAddr)
////    {
////        uint32_T arySz = sizeof(uint32_T) * qtySndBlocks;
////
////        sg_IO601_pModule[modIdx].CAN.CANPort[ptIdx].ConCurExe.GlbSnd.pQueueAddr = (uint32_T*)malloc(arySz);
////
////        if (NULL == sg_IO601_pModule[modIdx].CAN.CANPort[ptIdx].ConCurExe.GlbSnd.pQueueAddr)
////        {
////            return FALSE;
////        }
////
////        memset(sg_IO601_pModule[modIdx].CAN.CANPort[ptIdx].ConCurExe.GlbSnd.pQueueAddr, 0x00, arySz);
////        sg_IO601_pModule[modIdx].CAN.CANPort[ptIdx].ConCurExe.GlbSnd.QtySndBlk = qtySndBlocks;
////    }
////
////    return TRUE;
////}
////
/////*
////*   Set the send queue for the selected CAN port and set start values.
////*/
////boolean_T IO601_CANSetPortQueue(uint32_T modIdx, uint8_T ptIdx, void **ppQueue)
////{
////    IO601_CANPortSndQueue *pHelpValue = (IO601_CANPortSndQueue*)calloc(1, sizeof(IO601_CANPortSndQueue));
////
////    if (NULL == pHelpValue)
////    {
////        return FALSE;
////    }
////
////    pHelpValue->IsUpdated = FALSE;
////    pHelpValue->WrtIdx = 0;
////    pHelpValue->RdIdx = 2;
////    *ppQueue = (void*)pHelpValue;
////    sg_IO601_pModule[modIdx].CAN.CANPort[ptIdx].ConCurExe.GlbSnd.pQueueAddr[sg_IO601_pModule[modIdx].CAN.CANPort[ptIdx].ConCurExe.GlbSnd.AryIdx++] = \
////        (uint32_T)pHelpValue;
////    return TRUE;
////}
////
/////*
////*   Global sender for CAN messages of the whole module.
////*/
////boolean_T IO601_CANGlbSender(uint32_T modIdx, uint8_T ptIdx, int id, time_T ts)
////{
////    if (sg_IO601_pModule[modIdx].CAN.CANPort[ptIdx].ConCurExe.GlbSnd.LastTs < ts)
////    {
////        sg_IO601_pModule[modIdx].CAN.CANPort[ptIdx].ConCurExe.GlbSnd.LastTs = ts;
////
////        if (IO601_LockCAN(sg_IO601_pModule[modIdx].CAN.pConCurExeHdl, ptIdx))
////        {
////            uint32_T i = 0;
////            uint8_T rdIdx = 0;
////            IO601_CANPortSndQueue *pHelp = NULL;
////
////            for (i = 0; i < sg_IO601_pModule[modIdx].CAN.CANPort[ptIdx].ConCurExe.GlbSnd.QtySndBlk; i++)
////            {
////                pHelp = (IO601_CANPortSndQueue*)sg_IO601_pModule[modIdx].CAN.CANPort[ptIdx].ConCurExe.GlbSnd.pQueueAddr[i];
////                rdIdx = (pHelp->RdIdx + 1) % 3;
////
////                SG_PRINTF(DEBUG, "\nDbg - rdIdx: %i  -- isUpdated: %i", rdIdx, pHelp->BufMsg[rdIdx].isUpdated);
////
////                if (pHelp->BufMsg[rdIdx].isUpdated)
////                {
////                    SendCANMessage(modIdx, ptIdx, &pHelp->BufMsg[rdIdx].Msg);
////                    pHelp->BufMsg[rdIdx].isUpdated = FALSE;
////                    pHelp->RdIdx = rdIdx;
////                }
////            }
////
////            IO601_UnlockCAN(sg_IO601_pModule[modIdx].CAN.pConCurExeHdl, ptIdx);
////        }
////    }
////
////    return TRUE;
////}
////
/////*
////*   Copy CAN message to the block queue and set update status flag for global sender.
////*/
////boolean_T IO601_CANSetMsgToBuffer(uint32_T modIdx, void *pQueue, canMsg *pMsg)
////{
////    IO601_CANPortSndQueue *pHelp = (IO601_CANPortSndQueue*)pQueue;
////    uint8_T wrtIdx = pHelp->WrtIdx;
////
////    ////SG_PRINTF(DEBUG, "\nDbg - set msg: wrtIdx: %i", wrtIdx);
////
////    pHelp->BufMsg[wrtIdx].Msg.ID = pMsg->ID;
////    pHelp->BufMsg[wrtIdx].Msg.Length = pMsg->Length;
////    pHelp->BufMsg[wrtIdx].Msg.Extended = pMsg->Extended;
////    pHelp->BufMsg[wrtIdx].Msg.Data[0] = pMsg->Data[0];
////    pHelp->BufMsg[wrtIdx].Msg.Data[1] = pMsg->Data[1];
////    pHelp->BufMsg[wrtIdx].Msg.Data[2] = pMsg->Data[2];
////    pHelp->BufMsg[wrtIdx].Msg.Data[3] = pMsg->Data[3];
////    pHelp->BufMsg[wrtIdx].Msg.Data[4] = pMsg->Data[4];
////    pHelp->BufMsg[wrtIdx].Msg.Data[5] = pMsg->Data[5];
////    pHelp->BufMsg[wrtIdx].Msg.Data[6] = pMsg->Data[6];
////    pHelp->BufMsg[wrtIdx].Msg.Data[7] = pMsg->Data[7];
////    pHelp->BufMsg[wrtIdx].isUpdated = TRUE;
////    pHelp->WrtIdx = (wrtIdx + 1) % 3;
////    return TRUE;
////}

#pragma endregion


#pragma region Functions - Concurrent Execution LIN

/*
*   Update the first of the two message buffers of the LIN slave.
*/
unsigned char IO601_LINLockUnlockBuffer1(uint32_T modIdx, boolean_T enaLock)
{
    uint8_T timeout = 0;
    t_semaphores *pSema = (t_semaphores *)(sg_IO601_pModule[modIdx].pIOAddress2 + 0x2000);

    if (enaLock)
    {
        if (pSema->LINUpdateBuffer1 == 0)
        {
            return 1;
        }
        else if (pSema->LINUpdateBuffer1 & 1)
        {
            while ((pSema->LINUpdateBuffer1 & 1) != 0)
            {
                pSema->LINUpdateBuffer1 &= ~1;
            }

            while (timeout < 10)
            {
                if (pSema->LINUpdateBuffer1 == 0)
                {
                    ////SG_PRINTF(DEBUG, "\nDbg - sema for rwwb 1 is locked");
                    return 1;
                }

                IO601_SleepMilliseconds(0.0001);
                timeout += 1;
            }
        }
    }
    else
    {
        ////SG_PRINTF(DEBUG, "\nDbg -  sema for rwwb 1 is unlocked");
        pSema->LINUpdateBuffer1 |= 1;
        return 1;
    }

    return 0;



    ////while (timeout < 5)
    ////{
    ////    if (pSema->LINUpdateBuffer1 == 0)
    ////    {
    ////        SG_PRINTF(DEBUG, "\nDbg - sema for rwwb 1 is locked");
    ////    }
    ////    IO601_SleepMilliseconds(0.0001);
    ////    timeout += 1;
    ////}

    ////return FALSE;
}



/*
*   Update the first of the two message buffers of the LIN slave.
*/
unsigned char IO601_LINLockUnlockBuffer2(uint32_T modIdx, boolean_T enaLock)
{
    uint8_T timeout = 0;
    t_semaphores *pSema = (t_semaphores *)(sg_IO601_pModule[modIdx].pIOAddress2 + 0x2000);

    ////SG_PRINTF(DEBUG, "\nDbg - try to lock sema 2");

    if (enaLock)
    {
        if (pSema->LINUpdateBuffer2 == 0)
        {
            return 1;
        }
        else if (pSema->LINUpdateBuffer2 & 1)
        {
            ////SG_PRINTF(DEBUG, "\nDbg - sema 2 == 1");

            while ((pSema->LINUpdateBuffer2 & 1) != 0)
            {
                pSema->LINUpdateBuffer2 &= ~1;
            }

            while (timeout < 10)
            {
                if (pSema->LINUpdateBuffer2 == 0)
                {
                    ////SG_PRINTF(DEBUG, "\nDbg - sema for rwwb 2 is locked");
                    return 1;
                }

                IO601_SleepMilliseconds(0.0001);
                timeout += 1;
            }
        }
    }
    else
    {
        ////SG_PRINTF(DEBUG, "\nDbg - sema for rwwb 2 is unlocked");
        pSema->LINUpdateBuffer2 |= 1;
        return 1;
    }

    return 0;
}

/*
*   Copy LIN message to RWWB 1
*/
void IO601_WrtMsgToRwwb(uint32_T modIdx, IO601_LINBlkBufMsg *pMsg)
{
    BCI_t_LIN_MSG *pHelpMsg = (BCI_t_LIN_MSG *)(sg_IO601_pModule[modIdx].pIOAddress2 + 0x18A8 + (pMsg->ProtID * sizeof(BCI_t_LIN_MSG)));

    pHelpMsg->bId = pMsg->FullProtID;
    pHelpMsg->bSendData = pMsg->isSndData;
    pHelpMsg->bLength = pMsg->DLC;
    pHelpMsg->bDummy = 0;
    pHelpMsg->bModel = pMsg->IsEnhcdChksum;

    if (pMsg->isSndData)
    {
        memcpy(pHelpMsg->bDataByte, pMsg->Data, pMsg->DLC);
        pHelpMsg->bCheckSum = pMsg->Chksum;
    }
}



void IO601_WrtMsgToRwwb_22(uint32_T modIdx, IO601_LINBlkBufMsg *pMsg)
{
    BCI_t_LIN_MSG *pHelpMsg = (BCI_t_LIN_MSG *)(sg_IO601_pModule[modIdx].pIOAddress2 + 0x1C28 + (pMsg->ProtID * sizeof(BCI_t_LIN_MSG)));

    pHelpMsg->bId = pMsg->FullProtID;
    pHelpMsg->bSendData = pMsg->isSndData;
    pHelpMsg->bLength = pMsg->DLC;
    pHelpMsg->bDummy = 0;
    pHelpMsg->bModel = pMsg->IsEnhcdChksum;

    if (pMsg->isSndData)
    {
        memcpy(pHelpMsg->bDataByte, pMsg->Data, pMsg->DLC);
        pHelpMsg->bCheckSum = pMsg->Chksum;
    }
}


void IO601_WrtMsgToRwwb2(uint32_T modIdx, IO601_LINBlkBufMsg *pMsg)
{
    BCI_t_LIN_MSG *pHelpMsg = (BCI_t_LIN_MSG *)(sg_IO601_pModule[modIdx].pIOAddress2 + 0x1C28 + (pMsg->ProtID * sizeof(BCI_t_LIN_MSG)));

    pHelpMsg->bId = pMsg->FullProtID;
    pHelpMsg->bSendData = pMsg->isSndData;
    pHelpMsg->bLength = pMsg->DLC;
    pHelpMsg->bDummy = 0;
    pHelpMsg->bModel = pMsg->IsEnhcdChksum;

    if (pMsg->isSndData)
    {
        memcpy(pHelpMsg->bDataByte, pMsg->Data, pMsg->DLC);
        pHelpMsg->bCheckSum = pMsg->Chksum;
    }
}


/*
*   Copy LIN messages from RWWB 1 to RWWB 2
*/
void IO601_LINCopyRwwb(uint32_T modIdx)
{

    BCI_t_LIN_MSG *pRwwb1 = NULL;
    BCI_t_LIN_MSG *pRwwb2 = NULL;
    uint8_T i = 0;

    ////SG_PRINTF(DEBUG, "\nDbg - copy rwwb1 to rwwb2");

    for (i = 0; i < 64; i++)
    {
        pRwwb1 = (BCI_t_LIN_MSG *)(sg_IO601_pModule[modIdx].pIOAddress2 + 0x18A8 + (i * sizeof(BCI_t_LIN_MSG)));
        pRwwb2 = (BCI_t_LIN_MSG *)(sg_IO601_pModule[modIdx].pIOAddress2 + 0x1C28 + (i * sizeof(BCI_t_LIN_MSG)));
        memcpy(pRwwb2->bDataByte, pRwwb1->bDataByte, pRwwb1->bLength);
    }
}

/*
*   Global sender for LIN master
*/
unsigned char IO601_LINMaSend(uint32_T modIdx, IO601_LINBlkBufMsg *pMsg)
{
    uint8_T cnt = 0;
    uint32_T i = 0;
    uint8_T rdIdx = 0;
    ////uint8_T queueWrtIdx = (sg_IO601_pModule[modIdx].LIN.WriteIndex + 1) % 50;

    uint8_T queueWrtIdx = sg_IO601_pModule[modIdx].LIN.WriteIndex;

    LINQueueEntry_T *pQueue = (LINQueueEntry_T*)((uintptr_t)sg_IO601_pModule[modIdx].pIOAddress2
                                                 + 0x1000 + (queueWrtIdx * sizeof(LINQueueEntry_T)));

    ////LINQueueEntry_T *pQueue2 = (LINQueueEntry_T*)((uint32_T)sg_IO601_pModule[modIdx].pIOAddress2
    ////                                             + 0x1000 );

    ////IO601_SleepMilliseconds(0.1);

    ////for (i = 0; i < 50; i++)
    ////{
    ////    if (pQueue2[i].status == 1)
    ////    {
    ////        SG_PRINTF(DEBUG, "\nDbg - queue check LIN ->  queue status: %i  -- wrtIdx: %i", pQueue2[i].status, i);
    ////    }
    ////}

    
    

     

    ////SG_PRINTF(DEBUG, "\nDbg - send msg %i  (%i) ->  queue status: %i  -- wrtIdx: %i", pMsg->ProtID, pMsg->Data[0], pQueue->status, queueWrtIdx);


    if (0 == pQueue->status)
    {
        pQueue->count = 12 + pMsg->DLC;
        pQueue->type = 0;
        pQueue->information = 0;
        pQueue->sMsg.bId = pMsg->FullProtID;
        pQueue->sMsg.bModel = pMsg->IsEnhcdChksum;
        pQueue->sMsg.bCheckSum = pMsg->Chksum;
        pQueue->sMsg.bSendData = pMsg->isSndData;
        pQueue->sMsg.bLength = pMsg->DLC;
        pQueue->sMsg.bDummy = 0;
        pQueue->sMsg.bDataByte[0] = pMsg->Data[0];
        pQueue->sMsg.bDataByte[1] = pMsg->Data[1];
        pQueue->sMsg.bDataByte[2] = pMsg->Data[2];
        pQueue->sMsg.bDataByte[3] = pMsg->Data[3];
        pQueue->sMsg.bDataByte[4] = pMsg->Data[4];
        pQueue->sMsg.bDataByte[5] = pMsg->Data[5];
        pQueue->sMsg.bDataByte[6] = pMsg->Data[6];
        pQueue->sMsg.bDataByte[7] = pMsg->Data[7];
        pQueue->status = 1;
        pMsg->isUpdated = 0;
        sg_IO601_pModule[modIdx].LIN.WriteIndex = (queueWrtIdx + 1) % 50;

        ////SG_PRINTF(DEBUG, "\nDbg - WriteIndex. %i", sg_IO601_pModule[modIdx].LIN.WriteIndex);
        ////sg_IO601_pModule[modIdx].LIN.WriteIndex = (sg_IO601_pModule[modIdx].LIN.WriteIndex < 49) ? sg_IO601_pModule[modIdx].LIN.WriteIndex + 1 : 0;
    }
    else
    {
        SG_PRINTF(DEBUG, "\nDbg - Queue status is %i for id: %i  on queueWriteIdx: %i", pQueue->status, pMsg->ProtID, queueWrtIdx);
        return 0;
    }

    
    return 1;

    ////for (i = 0; i < 64; i++)
    ////{
    ////    if (NULL != sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbSnd.QueueAry[i])
    ////    {
    ////        rdIdx = (sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbSnd.QueueAry[i]->RdIdx + 1) % 3;
    ////        
    ////        if (sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbSnd.QueueAry[i]->BufMsg[rdIdx].isUpdated)
    ////        {
    ////            if (0 == pQueue->status)
    ////            {
    ////                ////SG_PRINTF(DEBUG, "\n%f Send ID: %i (%i)  on rdIdx: %i  -  data: %i", ts, i, protID, rdIdx, sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbSnd.QueueAry[i]->BufMsg[rdIdx].Data[0]);
    ////                
    ////            }
    ////            else
    ////            {
    ////                ////SG_PRINTF(DEBUG, "\nDbg - ID: %i --> status: %i", i, pQueue->status);
    ////                return FALSE;
    ////            }
    ////            if (cnt++ == 30)
    ////            {
    ////                InterruptMicrocontroller(modIdx);
    ////                cnt = 0;
    ////            }
    ////        }
    ////        if (cnt != 0)
    ////        {
    ////            InterruptMicrocontroller(modIdx);
    ////        }
    ////        sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbSnd.QueueAry[i]->RdIdx = rdIdx;
    ////    }
    ////}
}







/////*
////*   Set the concurrent execution handler for LIN.
////*/
////boolean_T IO601_LINSetConCurExeHdl(uint32_T modIdx)
////{
////    return IO601_LINCreateConCurExeHdl(sg_IO601_pModule[modIdx].LIN.ConCurExe.pHandler);
////}
////
/////*
////*   Delete the handler for concurrent execution.
////*/
////void IO601_LINClearConCurExeHdl()
////{
////    uint32_T i = 0;
////
////    for (i = 0; i < QUANTITY_IO_MODULES; i++)
////    {
////        IO601_LINDeleteConCurExeHdl(sg_IO601_pModule[i].LIN.ConCurExe.pHandler);
////    }
////}
////
/////*
////*   Set the queue for the selected LIN port and set start values.
////*/
////boolean_T IO601_LINSetPortQueue(uint32_T modIdx, uint8_T protID, boolean_T isEnhcdChkSum, uint8_T dlc, boolean_T isSndData, boolean_T isSender, time_T ts, void **ppQueue)
////{
////    uint8_T i = 0;
////    uint8_T fullID = CreateID(protID);
////    IO601_LINPortQueue *pHelpValue = (IO601_LINPortQueue*)calloc(1, sizeof(IO601_LINPortQueue));
////
////    if (NULL == pHelpValue)
////    {
////        return FALSE;
////    }
////
////    *ppQueue = (void*)pHelpValue;
////    pHelpValue->WrtIdx = 0;
////    pHelpValue->RdIdx = 1;
////
////    for (i = 0; i < BLK_BUF_SZ; i++)
////    {
////        pHelpValue->BufMsg[i].isUpdated = FALSE;
////        pHelpValue->BufMsg[i].ProtID = protID;
////        pHelpValue->BufMsg[i].FullProtID = fullID;
////        pHelpValue->BufMsg[i].IsEnhcdChksum = isEnhcdChkSum;
////        pHelpValue->BufMsg[i].DLC = dlc;
////        pHelpValue->BufMsg[i].isSndData = isSndData;
////    }
////
////    if (isSender)
////    {
////        sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbSnd.QueueAry[protID] = pHelpValue;
////
////        if (ts <= sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbSnd.FastestTs)
////        {
////            sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbSnd.FastestTs = ts;
////            sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbSnd.BlockQty += 1;
////        }
////
////        ////SG_PRINTF(DEBUG, "\nDbg - %i global updater is: %i  - %f", protID, sg_IO601_pModule[modIdx].LIN.ConCurExe.SndIdx, sg_IO601_pModule[modIdx].LIN.ConCurExe.SndTs);
////    }
////    else
////    {
////        sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbRec.QueueAry[protID] = pHelpValue;
////
////        if (ts < sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbRec.FastestTs)
////        {
////            sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbRec.FastestTs = ts;
////        }
////
////        ////SG_PRINTF(DEBUG, "\nDbg - %i -> global receiver is: %i  - %f", protID, sg_IO601_pModule[modIdx].LIN.ConCurExe.SndIdx, sg_IO601_pModule[modIdx].LIN.ConCurExe.SndTs);
////    }
////
////    return TRUE;
////}
////
/////*
////*   Free the allocated memory
////*/
////void IO601_LINFreePortQueue()
////{
////    uint8_T i = 0;
////
////    uint32_T j = 0;
////
////    for (j = 0; j < QUANTITY_IO_MODULES; j++)
////    {
////        for (i = 0; i < 64; i++)
////        {
////            if (NULL != sg_IO601_pModule[j].LIN.ConCurExe.GlbSnd.QueueAry[i])
////            {
////                free(sg_IO601_pModule[j].LIN.ConCurExe.GlbSnd.QueueAry[i]);
////                sg_IO601_pModule[j].LIN.ConCurExe.GlbSnd.QueueAry[i] = NULL;
////                ////SG_PRINTF(DEBUG, "\nDbg - Free glbSender: %i", i);
////            }
////
////            if (NULL != sg_IO601_pModule[j].LIN.ConCurExe.GlbRec.QueueAry[i])
////            {
////                free(sg_IO601_pModule[j].LIN.ConCurExe.GlbRec.QueueAry[i]);
////                sg_IO601_pModule[j].LIN.ConCurExe.GlbRec.QueueAry[i] = NULL;
////                ////SG_PRINTF(DEBUG, "\nDbg - Free glbReceiver: %i", i);
////            }
////        }
////    }
////}
////
/////*
////*   Copy LIN message to the block queue and set update status flag for global sender.
////*/
////boolean_T IO601_LINSetMsgToBuffer(uint32_T modIdx, void *pQueue, uint8_T *pData, double ts, uint8_T protID)
////{
////    IO601_LINPortQueue *pHelp = (IO601_LINPortQueue*)pQueue;
////    uint8_T wrtIdx = pHelp->WrtIdx;
////
////    if (NULL != pData)
////    {
////        uint8_T i = 0;
////        uint16_T w_LocalHelp = 0;
////
////        if (pHelp->BufMsg[wrtIdx].IsEnhcdChksum)
////        {
////            w_LocalHelp = pHelp->BufMsg[wrtIdx].FullProtID;
////
////            if (w_LocalHelp > 0xFF)     // If protected ID is higher than 255 (full protected ID includes the message ID + parity bits
////            {
////                w_LocalHelp -= 0xFF;
////            }
////        }
////
////        for (i = 0; i < pHelp->BufMsg[wrtIdx].DLC; i++)
////        {
////            pHelp->BufMsg[wrtIdx].Data[i] = pData[i];
////            w_LocalHelp = w_LocalHelp + pHelp->BufMsg[wrtIdx].Data[i];
////
////            if (w_LocalHelp > 0xFF)     // If value is higher than 255 do value - 255
////            {
////                w_LocalHelp -= 0xFF;
////            }
////        }
////
////        pHelp->BufMsg[wrtIdx].Chksum = (uint8_T)(~w_LocalHelp);      // return the inverted modulo-256 checksum
////    }
////
////    pHelp->BufMsg[wrtIdx].isUpdated = TRUE;
////    pHelp->WrtIdx = (wrtIdx + 1) % 3;
////
////    ////SG_PRINTF(DEBUG, "\n%f - Set (%i) id: %i --  wrtIdx: %i  -- data: %i", ts, protID, pHelp->BufMsg[wrtIdx].ProtID, wrtIdx, pHelp->BufMsg[wrtIdx].Data[0]);
////    return TRUE;
////}
////
/////*
////*   Global sender for LIN master
////*/
////boolean_T IO601_LINGlbSender(uint32_T modIdx, uint8_T protID, time_T ts)
////{
////
////    if (protID == sg_IO601_pModule[modIdx].LIN.ConCurExe.SndIdx)
////    {
////        if (!IO601_LINGlbHelpSender(modIdx, protID, ts))
////        {
////            SG_PRINTF(DEBUG, "\nError - Send LIN message with ID %i failed, no empty queue entry", protID);
////            return FALSE;
////        }
////
////    }
////
////    return TRUE;
////}
////
/////*
////*   Global help sender for LIN
////*/
////boolean_T IO601_LINGlbHelpSender(uint32_T modIdx, uint8_T protID, double ts)
////{
////    uint8_T cnt = 0;
////    uint32_T i = 0;
////    uint8_T rdIdx = 0;
////    LINQueueEntry_T *pQueue = NULL;
////
////    for (i = 0; i < 64; i++)
////    {
////        if (NULL != sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbSnd.QueueAry[i])
////        {
////            rdIdx = (sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbSnd.QueueAry[i]->RdIdx + 1) % 3;
////
////            pQueue = (LINQueueEntry_T*)((uint32_T)sg_IO601_pModule[modIdx].pIOAddress2 + 0x1000 +
////                (sg_IO601_pModule[modIdx].LIN.WriteIndex * sizeof(LINQueueEntry_T)));
////
////            if (sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbSnd.QueueAry[i]->BufMsg[rdIdx].isUpdated)
////            {
////                if (0 == pQueue->status)
////                {
////                    ////SG_PRINTF(INFO, "\n%f Send ID: %i (%i)  on rdIdx: %i  -  data: %i", ts, i, protID, rdIdx, sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbSnd.QueueAry[i]->BufMsg[rdIdx].Data[0]);
////
////                    pQueue->count = 12 + sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbSnd.QueueAry[i]->BufMsg[rdIdx].DLC;
////                    pQueue->type = 0;
////                    pQueue->information = 0;
////                    pQueue->sMsg.bId = sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbSnd.QueueAry[i]->BufMsg[rdIdx].FullProtID;
////                    pQueue->sMsg.bModel = sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbSnd.QueueAry[i]->BufMsg[rdIdx].IsEnhcdChksum;
////                    pQueue->sMsg.bCheckSum = sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbSnd.QueueAry[i]->BufMsg[rdIdx].Chksum;
////                    pQueue->sMsg.bSendData = sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbSnd.QueueAry[i]->BufMsg[rdIdx].isSndData;
////                    pQueue->sMsg.bLength = sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbSnd.QueueAry[i]->BufMsg[rdIdx].DLC;
////                    pQueue->sMsg.bDummy = 0;
////                    pQueue->sMsg.bDataByte[0] = sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbSnd.QueueAry[i]->BufMsg[rdIdx].Data[0];
////                    pQueue->sMsg.bDataByte[1] = sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbSnd.QueueAry[i]->BufMsg[rdIdx].Data[1];
////                    pQueue->sMsg.bDataByte[2] = sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbSnd.QueueAry[i]->BufMsg[rdIdx].Data[2];
////                    pQueue->sMsg.bDataByte[3] = sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbSnd.QueueAry[i]->BufMsg[rdIdx].Data[3];
////                    pQueue->sMsg.bDataByte[4] = sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbSnd.QueueAry[i]->BufMsg[rdIdx].Data[4];
////                    pQueue->sMsg.bDataByte[5] = sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbSnd.QueueAry[i]->BufMsg[rdIdx].Data[5];
////                    pQueue->sMsg.bDataByte[6] = sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbSnd.QueueAry[i]->BufMsg[rdIdx].Data[6];
////                    pQueue->sMsg.bDataByte[7] = sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbSnd.QueueAry[i]->BufMsg[rdIdx].Data[7];
////                    pQueue->status = 1;
////                    sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbSnd.QueueAry[i]->BufMsg[rdIdx].isUpdated = FALSE;
////                    sg_IO601_pModule[modIdx].LIN.WriteIndex = (sg_IO601_pModule[modIdx].LIN.WriteIndex < 49) ? sg_IO601_pModule[modIdx].LIN.WriteIndex + 1 : 0;
////                }
////                else
////                {
////                    ////SG_PRINTF(DEBUG, "\nDbg - ID: %i --> status: %i", i, pQueue->status);
////                    return FALSE;
////                }
////
////                if (cnt++ == 30)
////                {
////                    InterruptMicrocontroller(modIdx);
////                    cnt = 0;
////                }
////            }
////
////            if (cnt != 0)
////            {
////                InterruptMicrocontroller(modIdx);
////            }
////
////            sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbSnd.QueueAry[i]->RdIdx = rdIdx;
////        }
////    }
////
////    return TRUE;
////}
////
/////*
////*   Global recevier for LIN
////*/
////boolean_T IO601_LINGlbReceiver(uint32_T modIdx, uint8_T protID, time_T ts)
////{
////    if (protID == sg_IO601_pModule[modIdx].LIN.ConCurExe.SndIdx)
////    {
////        if (!IO601_LINGlbHelpSender(modIdx, protID, ts))
////        {
////            SG_PRINTF(ERROR, "\nError - Send LIN message with ID %i failed, no empty queue entry", protID);
////            return FALSE;
////        }
////    }
////
////    if (protID == sg_IO601_pModule[modIdx].LIN.ConCurExe.RecIdx)
////    {
////        if (!IO601_LINGlbHelperReceiver(modIdx, protID, ts))
////        {
////            SG_PRINTF(ERROR, "\nError - Send LIN message with ID %i failed, no empty queue entry", protID);
////            return FALSE;
////        }
////    }
////    return TRUE;
////}
////
/////*
////*   Global help receiver for LIN
////*/
////boolean_T IO601_LINGlbHelperReceiver(uint32_T modIdx, uint8_T protID, double ts)
////{
////    uint8_T j = 0;
////    uint8_T wrtIdx = 0;
////    uint8_T msgID = 0;
////    uint8_T *pErrCode = NULL;
////    LINQueueEntry_T *pQueue = NULL;
////
////    while (j < 50)
////    {
////        pQueue = (LINQueueEntry_T*)((uint32_T)sg_IO601_pModule[modIdx].pIOAddress2 + 0x144C + (j * sizeof(LINQueueEntry_T)));
////
////        if (1 == pQueue->status)
////        {
////            if (2 == pQueue->type)
////            {
////                pErrCode = (uint8_T*)&sg_IO601_pModule[modIdx].LIN.ErrCodes[sg_IO601_pModule[modIdx].LIN.ErrIdx];
////                pErrCode[0] = pQueue->sMsg.bId;
////                pErrCode[1] = pQueue->sMsg.bModel;
////                sg_IO601_pModule[modIdx].LIN.ErrIdx = (sg_IO601_pModule[modIdx].LIN.ErrIdx + 1) % 64;
////            }
////            else if (0 == pQueue->type)
////            {
////                msgID = pQueue->sMsg.bId & 0x3F;
////
////                if (NULL != sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbRec.QueueAry[msgID])
////                {
////                    wrtIdx = sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbRec.QueueAry[msgID]->WrtIdx;
////
////                    ////SG_PRINTF(DEBUG, "\n%f - Rec by %i -> msg: %i, data: %i - to idx: %i", ts, protID, msgID, pQueue->sMsg.bDataByte[0], wrtIdx);
////
////                    sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbRec.QueueAry[msgID]->BufMsg[wrtIdx].Type = pQueue->type;
////                    sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbRec.QueueAry[msgID]->BufMsg[wrtIdx].Info = pQueue->information;
////                    sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbRec.QueueAry[msgID]->BufMsg[wrtIdx].Data[0] = pQueue->sMsg.bDataByte[0];
////                    sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbRec.QueueAry[msgID]->BufMsg[wrtIdx].Data[1] = pQueue->sMsg.bDataByte[1];
////                    sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbRec.QueueAry[msgID]->BufMsg[wrtIdx].Data[2] = pQueue->sMsg.bDataByte[2];
////                    sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbRec.QueueAry[msgID]->BufMsg[wrtIdx].Data[3] = pQueue->sMsg.bDataByte[3];
////                    sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbRec.QueueAry[msgID]->BufMsg[wrtIdx].Data[4] = pQueue->sMsg.bDataByte[4];
////                    sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbRec.QueueAry[msgID]->BufMsg[wrtIdx].Data[5] = pQueue->sMsg.bDataByte[5];
////                    sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbRec.QueueAry[msgID]->BufMsg[wrtIdx].Data[6] = pQueue->sMsg.bDataByte[6];
////                    sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbRec.QueueAry[msgID]->BufMsg[wrtIdx].Data[7] = pQueue->sMsg.bDataByte[7];
////                    sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbRec.QueueAry[msgID]->BufMsg[wrtIdx].ErrCode = 0;
////                    sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbRec.QueueAry[msgID]->BufMsg[wrtIdx].Tstp = *(uint32_T*)pQueue->timeStamp;
////                    sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbRec.QueueAry[msgID]->BufMsg[wrtIdx].UpdState = 1;
////                    sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbRec.QueueAry[msgID]->BufMsg[wrtIdx].isUpdated = TRUE;
////                    sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbRec.QueueAry[msgID]->WrtIdx = (wrtIdx + 1) % 3;
////                }
////            }
////        }
////
////        pQueue->status = 0;
////        j++;
////    }
////
////    for (j = 0; j < 64; j++)
////    {
////        if (NULL != sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbRec.QueueAry[j])
////        {
////            if (sg_IO601_pModule[modIdx].LIN.ErrIdxRd != sg_IO601_pModule[modIdx].LIN.ErrIdx)
////            {
////                sg_IO601_pModule[modIdx].LIN.ErrIdxRd = (sg_IO601_pModule[modIdx].LIN.ErrIdxRd + 1) % 64;
////                sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbRec.QueueAry[j]->ErrCode = sg_IO601_pModule[modIdx].LIN.ErrCodes[sg_IO601_pModule[modIdx].LIN.ErrIdxRd];
////            }
////        }
////    }
////
////    return TRUE;
////}
////
/////*
////*   Get the current active read index of the block queue.
////*/
////void IO601_LINGetReadIdx(uint32_T modIdx, uint8_T protID, uint8_T *pIdx, void *pQueue, double ts)
////{
////    IO601_LINPortQueue *pHelp = (IO601_LINPortQueue*)pQueue;
////    uint8_T rdIdx = (sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbRec.QueueAry[protID]->RdIdx + 1) % 3;
////
////    if (pHelp->BufMsg[rdIdx].isUpdated)
////    {
////        *pIdx = rdIdx;
////    }
////    else
////    {
////        *pIdx = sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbRec.QueueAry[protID]->RdIdx;
////    }
////}
////
/////*
////*   Get LIN message state from the block receive queue.
////*/
////void IO601_LINGetMsgFromBufferUpdState(uint32_T modIdx, uint8_T rdIdx, void *pQueue, int32_T *pState)
////{
////    IO601_LINPortQueue *pHelp = (IO601_LINPortQueue*)pQueue;
////
////    if (pHelp->BufMsg[rdIdx].isUpdated)
////    {
////        *pState = pHelp->BufMsg[rdIdx].UpdState;
////    }
////    else if (0 != pHelp->ErrCode)
////    {
////        *pState = -1;
////    }
////    else
////    {
////        *pState = 0;
////    }
////}
////
/////*
////*   Get LIN message info from the block receive queue.
////*/
////void IO601_LINGetMsgFromBufferMsgInfo(uint32_T modIdx, uint8_T rdIdx, void *pQueue, int32_T *pInfo)
////{
////    IO601_LINPortQueue *pHelp = (IO601_LINPortQueue*)pQueue;
////
////    if (pHelp->BufMsg[rdIdx].isUpdated)
////    {
////        *pInfo = pHelp->BufMsg[rdIdx].Info;
////    }
////}
////
/////*
////*   Get LIN message error code from the block receive queue.
////*/
////void IO601_LINGetMsgFromBufferMsgErrCode(uint32_T modIdx, uint8_T rdIdx, void *pQueue, int32_T *pErrCode)
////{
////    IO601_LINPortQueue *pHelp = (IO601_LINPortQueue*)pQueue;
////    *pErrCode = (int32_T)pHelp->ErrCode;
////}
////
/////*
////*   Get LIN message time stamp from the block receive queue.
////*/
////void IO601_LINGetMsgFromBufferTstp(uint32_T modIdx, uint8_T rdIdx, void *pQueue, int32_T *pTstp)
////{
////    IO601_LINPortQueue *pHelp = (IO601_LINPortQueue*)pQueue;
////
////    if (pHelp->BufMsg[rdIdx].isUpdated)
////    {
////        *pTstp = pHelp->BufMsg[rdIdx].Tstp;
////    }
////}
////
/////*
////*   Get LIN message from the block receive queue.
////*/
////void IO601_LINGetMsgFromBuffer(uint32_T modIdx, uint8_T rdIdx, void *pQueue, uint8_T *pData, double ts)
////{
////    IO601_LINPortQueue *pHelp = (IO601_LINPortQueue*)pQueue;
////
////    ////SG_PRINTF(DEBUG, "\n%f - Get msg: %i, data: %i - on idx: %i, upd: %i", ts, pHelp->BufMsg[rdIdx].ProtID, pHelp->BufMsg[rdIdx].Data[0], rdIdx, pHelp->BufMsg[rdIdx].isUpdated);
////
////    if (pHelp->BufMsg[rdIdx].isUpdated)
////    {
////        uint8_T i = 0;
////
////        ////SG_PRINTF(INFO, " - Out - IsUpd (%i): %i", pHelp->RdIdx, pHelp->MsgBuf[pHelp->RdIdx].isUpdated);
////
////        for (i = 0; i < pHelp->BufMsg[rdIdx].DLC; i++)
////        {
////            pData[i] = pHelp->BufMsg[rdIdx].Data[i];
////        }
////
////        ////SG_PRINTF(INFO, "\n - wrtData (%i): %i)", pHelp->BufMsg[rdIdx].ProtID, pHelp->BufMsg[rdIdx].Data[0]);
////
////        pHelp->BufMsg[rdIdx].isUpdated = FALSE;
////        pHelp->RdIdx = rdIdx;
////
////    }
////
////    ////SG_PRINTF(INFO, " - New rd: %i", pHelp->RdIdx);
////}
////
/////*
////*   Global recevier for LIN slave
////*/
////boolean_T IO601_LINGlbSlvReceiver(uint32_T modIdx, uint8_T protID, time_T ts)
////{
////
////    if (protID == sg_IO601_pModule[modIdx].LIN.ConCurExe.RecIdx)
////    {
////        if (!IO601_LINGlbHelperReceiver(modIdx, protID, ts))
////        {
////            SG_PRINTF(ERROR, "\nError - Receive LIN message with ID %i failed, no empty queue entry", protID);
////            return FALSE;
////        }
////    }
////
////    return TRUE;
////}
////
/////*
////*   Global updater for the LIN slave send buffer
////*/
////boolean_T IO601_LINGlbUpdaterSlv(uint32_T modIdx, uint8_T protID, time_T ts)
////{
////    if (protID == sg_IO601_pModule[modIdx].LIN.ConCurExe.SndIdx)
////    {
////        uint8_T i = 0;
////        uint8_T rdIdx = 0;
////
////        for (i = 0; i < 64; i++)
////        {
////            if (NULL != sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbSnd.QueueAry[i])
////            {
////                rdIdx = (sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbSnd.QueueAry[i]->RdIdx + 1) % 3;
////
////                if (sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbSnd.QueueAry[i]->BufMsg[rdIdx].isUpdated)
////                {
////                    SG_PRINTF(INFO, "\n%f - Upd by %i ->> msg: %i, data: %i - on idx %i",
////                           ts, protID, sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbSnd.QueueAry[i]->BufMsg[rdIdx].ProtID, sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbSnd.QueueAry[i]->BufMsg[rdIdx].Data[0], rdIdx);
////
////                    if (!(IO601_LINUpdateSlvBuffer1(modIdx, i, rdIdx) && IO601_LINUpdateSlvBuffer2(modIdx, i, rdIdx)))
////                    {
////                        SG_PRINTF(ERROR, "\nError - Update LIN message filter failed for ProtID: %i", i);
////                        return FALSE;
////                    }
////
////                    sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbSnd.QueueAry[i]->BufMsg[rdIdx].isUpdated = FALSE;
////                }
////
////                sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbSnd.QueueAry[i]->RdIdx = rdIdx;
////            }
////        }
////    }
////
////    return TRUE;
////}
////
/////*
////*   Update the first of the two message buffers of the LIN slave.
////*/
////boolean_T IO601_LINUpdateSlvBuffer1(uint32_T modIdx, uint8_T protID, uint8_T rdIdx)
////{
////    uint8_T timeout = 0;
////    BCI_t_LIN_MSG *pMsg = NULL;
////    t_semaphores *pSema = (t_semaphores *)(sg_IO601_pModule[modIdx].pIOAddress2 + 0x2000);
////
////    if (pSema->LINUpdateBuffer1 & 1)
////    {
////        while ((pSema->LINUpdateBuffer1 & 1) != 0)
////        {
////            pSema->LINUpdateBuffer1 &= ~1;
////        }
////    }
////
////    while (timeout < 5)
////    {
////        if (pSema->LINUpdateBuffer1 == 0)
////        {
////            pMsg = (BCI_t_LIN_MSG *)(sg_IO601_pModule[modIdx].pIOAddress2 + 0x18A8 + (protID * sizeof(BCI_t_LIN_MSG)));
////            pMsg->bId = sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbSnd.QueueAry[protID]->BufMsg[rdIdx].FullProtID;
////            pMsg->bSendData = sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbSnd.QueueAry[protID]->BufMsg[rdIdx].isSndData;
////            pMsg->bLength = sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbSnd.QueueAry[protID]->BufMsg[rdIdx].DLC;
////            pMsg->bDummy = 0;
////            pMsg->bModel = sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbSnd.QueueAry[protID]->BufMsg[rdIdx].IsEnhcdChksum;
////
////            if (sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbSnd.QueueAry[protID]->BufMsg[rdIdx].isSndData)
////            {
////                memcpy_s(pMsg->bDataByte, pMsg->bLength, sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbSnd.QueueAry[protID]->BufMsg[rdIdx].Data, pMsg->bLength);
////                pMsg->bCheckSum = sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbSnd.QueueAry[protID]->BufMsg[rdIdx].Chksum;
////            }
////
////            pSema->LINUpdateBuffer1 |= 1;
////
////            ////SG_PRINTF(DEBUG, "\nDbg - Update %i index %i with data %i", sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbSnd.QueueAry[protID]->MsgBuf[rdIdx].ProtID, rdIdx, pMsg->bDataByte[0]);
////
////            return TRUE;
////        }
////
////        IO601_SleepMilliseconds(0.0001);
////        timeout += 1;
////    }
////
////    return FALSE;
////}
////
/////*
////*   Update the second of the two message buffers of the LIN slave.
////*/
////boolean_T IO601_LINUpdateSlvBuffer2(uint32_T modIdx, uint8_T protID, uint8_T rdIdx)
////{
////    uint8_T timeout = 0;
////    BCI_t_LIN_MSG *pMsg = NULL;
////    t_semaphores *pSema = (t_semaphores *)(sg_IO601_pModule[modIdx].pIOAddress2 + 0x2000);
////
////    if (pSema->LINUpdateBuffer2 & 1)
////    {
////        while ((pSema->LINUpdateBuffer2 & 1) != 0)
////        {
////            pSema->LINUpdateBuffer2 &= ~1;
////        }
////    }
////
////    while (timeout < 5)
////    {
////        if (pSema->LINUpdateBuffer2 == 0)
////        {
////            pMsg = (BCI_t_LIN_MSG *)(sg_IO601_pModule[modIdx].pIOAddress2 + 0x1C28 + (protID * sizeof(BCI_t_LIN_MSG)));
////            pMsg->bId = sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbSnd.QueueAry[protID]->BufMsg[rdIdx].FullProtID;
////            pMsg->bSendData = sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbSnd.QueueAry[protID]->BufMsg[rdIdx].isSndData;
////            pMsg->bLength = sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbSnd.QueueAry[protID]->BufMsg[rdIdx].DLC;
////            pMsg->bDummy = 0;
////            pMsg->bModel = sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbSnd.QueueAry[protID]->BufMsg[rdIdx].IsEnhcdChksum;
////
////            if (sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbSnd.QueueAry[protID]->BufMsg[rdIdx].isSndData)
////            {
////                memcpy_s(pMsg->bDataByte, pMsg->bLength, sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbSnd.QueueAry[protID]->BufMsg[rdIdx].Data, pMsg->bLength);
////                pMsg->bCheckSum = sg_IO601_pModule[modIdx].LIN.ConCurExe.GlbSnd.QueueAry[protID]->BufMsg[rdIdx].Chksum;
////            }
////
////            pSema->LINUpdateBuffer2 |= 1;
////            return TRUE;
////        }
////
////        IO601_SleepMilliseconds(0.0001);
////        timeout += 1;
////    }
////
////    return FALSE;
////}

#pragma endregion

#endif
