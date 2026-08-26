/*********************************************************************************************
 * This setup is the configuration part of the 3rd version of the CAN drivers.
 *
 * Since the version 2 of the setup was still compatible with the 1st version, there
 * was no sg_IO601_setup_s_2.c file.
 *
 * Instead of naming this file sg_IO601_setup_s_2, we choose to maintain readability
 * between the files and to skip name 2 for this file.
 *
 * In this version, the changes are:
 * 
 *  # support of the messages filtering.
 *    * important: acceptance and filter was a naming valid for firmware V4.02, but since
 *      v4.03 a new set of registers are dedicated to this purpose:
 *      mask + code
 *
 *  # init and termination messages have been moved to the write block.
 *    * global variables were shared between this function and the write one.
 *      
 * General information:
 * The commands are sent to the micro-controller through a DPRAM interface. The commands
 * always follow this sequence:
 * 
 * byte 0 : synchronization
 * byte 1 : command length (includes command byte)
 * byte 2 and 3 : reserved
 * byte 4 to 80 : command parameters (variable)
 *
 * the synchronization byte as to be set in order to declare the command as "new".
 *
 * The micro-controller must be then interrupted to read the DPRAM and accomplished the cmd.
 *
 * When the command is done, the status is set to 2.
 *
 *
 * Modifications:
 * Cedric: 25.04.2013, Global variable re-introduced to allow multiple sample time.
 *********************************************************************************************/

#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_IO601_setup_s_3

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include "simstruc.h"

#ifdef MATLAB_MEX_FILE
#include "mex.h"
#endif

#ifndef MATLAB_MEX_FILE
#include <windows.h>
#include "xpcimports.h"
#include "ioext_xpcimport.h"
#endif

#define NUMBER_OF_ARGS         (12)
#define MODULEID_ARG           ssGetSFcnParam(S,0)
#define CAN1_ENABLE_ARG        ssGetSFcnParam(S,1)
#define CAN1_BUS_ARG           ssGetSFcnParam(S,2)  // can be low or high speed.
#define CAN1_USER_BAUDRATE_ARG ssGetSFcnParam(S,3)
#define STDACC1_ARG            ssGetSFcnParam(S,4)
#define EXTACC1_ARG            ssGetSFcnParam(S,5)
#define CAN2_ENABLE_ARG        ssGetSFcnParam(S,6)
#define CAN2_BUS_ARG           ssGetSFcnParam(S,7)
#define CAN2_USER_BAUDRATE_ARG ssGetSFcnParam(S,8)
#define STDACC2_ARG            ssGetSFcnParam(S,9)
#define EXTACC2_ARG            ssGetSFcnParam(S,10)
#define SLOT_ARG               ssGetSFcnParam(S,11)

#define DEVNAME                "Speedgoat IO601"
#define VENDORID               (0x10b5)
#define DEVICEID               (0x9030)
#define SUBVENDORID            (0x10b5)
#define SUBDEVICEID            (0x2977)

#define NO_I_WORKS             (2)
#define IOADDRESS0_I_IND       (0)
#define IOADDRESS2_I_IND       (1)
#define NO_R_WORKS             (0)



/* list of the DPRAM command
  command 0x5, 0x9 0xA are not supported since firmware V4.03 */
#define CMD_ID                 (0x1)
#define CMD_VERSION            (0x2)
#define CMD_TEST               (0x3)
#define CMD_INIT_CAN           (0x4)
#define CMD_START_CAN          (0x6)
#define CMD_STOP_CAN           (0x7)
#define CMD_RESET_CAN          (0x8)
#define CMD_CONFIG_RX_QUEUE    (0xB)
#define CMD_GET_BOARD_INFO     (0xC)
#define CMD_START_TIMER        (0xD)
#define CMD_STOP_TIMER         (0xE)
#define CMD_SET_ACC_MASK       (0xF)

/* and a few parameters values: */
#define BCI_POLL_MODE          (0x0)
#define BCI_LATENCY_MODE       (0x1)
#define BCI_THROUGHPUT_MODE    (0x2)

static char_T msg[256];

#ifndef MATLAB_MEX_FILE

uint8_T ptrWritePointer1[10];
uint8_T ptrWritePointer2[10];

typedef struct 
{
    uint8_T synch;
    uint8_T count;
    uint16_T reserved;
    uint8_T command;
    uint8_T data[75];
} BCICOMMAND;

typedef struct QUEUEENTRY
{
    uint32_T word[5];
}QUEUEENTRY;


static void InterruptMicroController(volatile uint32_T *ioaddress0)
{
    uint32_T regtemp;  
    
    /* generate MC interrupt */
    regtemp = ioaddress0[0x15];
    ioaddress0[0x15] = regtemp & ~(1 << 2);
    ioaddress0[0x15] = regtemp | (1 << 2);
}

/**************************************************************************
 *
 *
 *
 *
 *************************************************************************/
static void ResetBoard(volatile uint32_T *ioaddress0, volatile uint8_T *ioaddress2)
{

    uint32_T regtemp;    
    
    //reset board (PLX9030)
    regtemp = ioaddress0[0x15];    
    regtemp &= ~(1 << 11);    
    ioaddress0[0x15] = regtemp;    
    rl32eWaitDouble(0.050);     

    regtemp |= (1 << 11);
    ioaddress0[0x15] = regtemp;

    rl32eWaitDouble(0.050);
   
               
    ioaddress2[0x00] = 0;
    ioaddress2[0x01] = 0;
    ioaddress2[0x02] = 0;
    ioaddress2[0x03] = 3;
    ioaddress2[0x04] = 2;
    ioaddress2[0x05] = 0;
    ioaddress2[0x06] = 1;
    ioaddress2[0x00] = 1;
    rl32eWaitDouble(0.050);
    ioaddress2[0x01] = 0;
    rl32eWaitDouble(0.050);  
    
    InterruptMicroController(ioaddress0);
}

/**************************************************************************
 * function name: GetFirmwareVersion
 *
 * purpose: reads the board and return true when the version is available.
 *
 *************************************************************************/
static void GetFirmwareVersion(volatile uint32_T *ioaddress0, volatile BCICOMMAND *bci)
{  
   bci->synch = 0;
   bci->count = 1;
   bci->command = CMD_VERSION;
   bci->synch = 1; 
   
   InterruptMicroController(ioaddress0);

   while (bci->synch != 2);  
   return;

}

/**************************************************************************
 * function name: InitCAN
 *
 * purpose: this function initialize the given CAN controller, baudrates
 * are configured at this moment.
 *
 * Return true when successful.
 *************************************************************************/
static uint8_T InitCAN(volatile uint32_T * ioaddress0, volatile BCICOMMAND *bci, uint8_T port, uint8_T bt0, uint8_T bt1, uint8_T mode) 
{    
    bci->synch = 0;
    bci->count = 5;
    bci->command = CMD_INIT_CAN;
    bci->data[0] = port;
    bci->data[1] = bt0;
    bci->data[2] = bt1;
    bci->data[3] = 2 | mode;
    bci->synch = 1;

    InterruptMicroController(ioaddress0);

    while (bci->synch != 2);    
    return bci->data[0]; // contains the status of the command
}

/**************************************************************************
 * function name: StartCAN
 *
 * purpose: this function starts the given CAN controller
 *
 *************************************************************************/
static uint8_T StartCAN(volatile uint32_T * ioaddress0, volatile BCICOMMAND *bci, uint8_T port)
{    
   
    bci->synch = 0;
    bci->count = 2;
    bci->command = CMD_START_CAN;
    bci->data[0] = port;
    bci->synch = 1;
    
    InterruptMicroController(ioaddress0);      
   
    // sync byte changes to 2 when command is done.
    while (bci->synch != 2); 
    
    return bci->data[0]; // contains the status of the command
}

/**************************************************************************
 * function name: ConfigRxQueue
 *
 * purpose: this function configure the RX queue.
 *
 *************************************************************************/
static uint8_T ConfigRxQueue(volatile uint32_T * ioaddress0, volatile BCICOMMAND *bci, uint8_T port, uint8_T mode)
{   
   
    bci->synch = 0;
    bci->count = 3;
    bci->command = CMD_CONFIG_RX_QUEUE;
    bci->data[0] = port;
    bci->data[1] = mode;
    bci->synch = 1;    

    InterruptMicroController(ioaddress0);

    while (bci->synch != 2);  
    return bci->data[0]; // contains the status of the command
    
}

/**************************************************************************
 * function name: StopCAN
 *
 * purpose: this function stops the given CAN Controller
 *
 *************************************************************************/
static uint8_T StopCAN(volatile uint32_T * ioaddress0, volatile BCICOMMAND *bci, uint8_T port)
{    
    
    bci->synch = 0;
    bci->count = 2;
    bci->command = CMD_STOP_CAN;
    bci->data[0] = port;
    bci->synch = 1;

    InterruptMicroController(ioaddress0);
     
    while (bci->synch != 2);  
    return bci->data[0]; // contains the status of the command
    
}

/**************************************************************************
 * function name: SetAcceptanceMask
 *
 * purpose: this function configure the acceptance mask. Valid for 11-bits
 * and 29-bits identifier.
 *
 * 2 masks can be configured for each frame format.
 *
 * Command to set the acceptance mask for 11-bit and 29-bit identifier. there
 * for each frame format Messsage 2 masks with which to received CAN
 * Messages can be configured.
 * The CAN message is received, if the following condition is satisfied:
 * ((ID & MASK1) == CODE1) | | ((id & MASK2) == CODE2)
 *************************************************************************/
static uint8_T SetAcceptanceMask(volatile uint32_T *ioaddress0, volatile BCICOMMAND *bci, uint8_T port, uint8_T mask_num, uint8_T mode, uint32_T accMask, uint32_T accCode)
{
    
    bci->synch = 0;
    bci->count = 10;
    bci->command = CMD_SET_ACC_MASK;
    bci->data[0] = port;
    bci->data[1] = mask_num;
    bci->data[2] = mode;
    bci->data[3] = (uint8_T)(accMask & 0xFF);
    bci->data[4] = (uint8_T)((accMask >> 8) & 0xFF);
    bci->data[5] = (uint8_T)((accMask >> 16) & 0xFF);
    bci->data[6] = (uint8_T)((accMask >> 24) & 0xFF);
    bci->data[7] = (uint8_T)(accCode & 0xFF);
    bci->data[8] = (uint8_T)((accCode >> 8) & 0xFF);
    bci->data[9] = (uint8_T)((accCode >> 16) & 0xFF);
    bci->data[10] = (uint8_T)((accCode >> 24) & 0xFF);
    bci->synch = 1;

    //printf("Acc mask: %d\  Acc code: %d\n", accMask, accCode);
    
    InterruptMicroController(ioaddress0);
     
    while (bci->synch != 2);  
    return bci->data[0]; // contains the status of the command
}

#endif



static void mdlInitializeSizes(SimStruct *S)
{
    int_T i;
    ssSetNumSFcnParams(S, NUMBER_OF_ARGS);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) 
    {
        sprintf(msg, "Wrong number of input arguments passed.\n%d arguments are expected\n", NUMBER_OF_ARGS);
        ssSetErrorStatus(S, msg);
        return;
    }

    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);

    ssSetNumInputPorts(S, 0);
    ssSetNumOutputPorts(S, 0);

    ssSetNumSampleTimes(S, 1);

    ssSetNumRWork(S, NO_R_WORKS);
    ssSetNumIWork(S, NO_I_WORKS);
    ssSetNumPWork(S, 0);

    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

    for (i = 0; i < NUMBER_OF_ARGS; i++) 
    {
        ssSetSFcnParamNotTunable(S,i);
    }

    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE | SS_OPTION_PLACE_ASAP);

}


static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, 0.0);
}


#define MDL_START
static void mdlStart(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE
    xpcPCIDevice pciinfo;
    int32_T bus, slot;
    uint8_T version[6];
    uint8_T canbus;
    uint8_T bt0, bt1;
    uint8_T port, mode, mask_num;
    int8_T status;
    uint32_T accMask, accCode, i;
    volatile BCICOMMAND *bci;
    volatile uint32_T *ioaddress0;
    volatile uint8_T *ioaddress2;
    volatile QUEUEENTRY *pQueue;
    uint32_T nbOccurences, temp;


    /* board detection */
    if (mxGetN(SLOT_ARG) == 1)
    {
        if ((int32_T)mxGetPr(SLOT_ARG)[0] == -1)
        {
            nbOccurences = 0;
              
            // browse bus and slot until deviceID and vendorID have been found
            for (bus = 0; bus < 256; bus++)
            {
                for (slot = 0; slot < 32; slot++)
                {
                    xpcOutpDW(0xCF8, 0x80000000 | (bus << 16) | (slot << 11));
                    temp = xpcInpDW(0xCFC);

                    if ((temp & 0xFFFF) == VENDORID && ((temp >> 16)& 0xFFFF) == DEVICEID)
                    {
                        
                        nbOccurences += 1;
                        if (nbOccurences == ((uint32_T)mxGetPr(MODULEID_ARG)[0]))     
                        {
                            break;
                        }
                    }

                }

                if (nbOccurences == ((uint32_T)mxGetPr(MODULEID_ARG)[0]))
                {
                    break;
                }              
            };
            
            if (nbOccurences < ((uint32_T)mxGetPr(MODULEID_ARG)[0]))     
            {
                sprintf(msg, "%s: Failed to find I/O Module with ID %d", DEVNAME, (uint32_T)mxGetPr(MODULEID_ARG)[0]);
                ssSetErrorStatus(S, msg);
                return;
            }
            
            
        }
        else
        {
            bus = 0;
            slot = (int_T)mxGetPr(SLOT_ARG)[0];
        }
        
    }
    else
    {
        bus = (int_T)mxGetPr(SLOT_ARG)[0];
        slot = (int_T)mxGetPr(SLOT_ARG)[1];
    }

    /* look for the PCI-Device */
    if (xpcGetPCIDeviceInfo(VENDORID, DEVICEID, SUBVENDORID, SUBDEVICEID, bus, slot, &pciinfo))
    {
        sprintf(msg, "%s (bus %d, slot %d): board not present", DEVNAME, bus, slot);
        ssSetErrorStatus(S, msg);
        return;
    }

    pciinfo.VirtAddress[0] = (unsigned long)xpcReserveMemoryRegion((void *)pciinfo.BaseAddress[0], pciinfo.Length[0], XPC_RT_PG_USERREADWRITE);  
    pciinfo.VirtAddress[2] = (unsigned long)xpcReserveMemoryRegion((void *)pciinfo.BaseAddress[2], pciinfo.Length[2], XPC_RT_PG_USERREADWRITE);  
    ssSetIWorkValue(S, IOADDRESS2_I_IND, pciinfo.VirtAddress[2]);
    ssSetIWorkValue(S, IOADDRESS0_I_IND, pciinfo.VirtAddress[0]);
    
    //ssSetIWorkValue(S, BASE_ADDR_I_IND, pciinfo.VirtAddress[2]);
    bci = (volatile BCICOMMAND *)(pciinfo.VirtAddress[2]);    
    ioaddress0 = (volatile uint32_T *)(pciinfo.VirtAddress[0]); 
    ioaddress2 = (volatile uint8_T *)(pciinfo.VirtAddress[2]); 
    
    // reset the write pointers to 0. These global variables are reused within Write v3 block
    for (i = 0; i < 10; i++)
    {
        ptrWritePointer1[i] = 0;
        ptrWritePointer2[i] = 0;
    }

    ResetBoard(ioaddress0, ioaddress2);   
    
    
    GetFirmwareVersion(ioaddress0, bci);   
    /* the version under the pattern VX.XX is extracted from data */
    version[0] = bci->data[1];
    version[1] = bci->data[2];
    version[2] = bci->data[3];
    version[3] = bci->data[4];
    version[4] = bci->data[5];
    version[5] = '\0';
    
    //printf("%s\n", version);
    
    if (strncmp(version, "4.27", 5) && strncmp(version, "4.18", 5))
    {
        sprintf(msg, "%s: wrong firmware (%s)", DEVNAME, version);
        ssSetErrorStatus(S, msg);
        return;
    }    
    
    
    /* if required, configure port 1 */
    if ((uint8_T)mxGetPr(CAN1_ENABLE_ARG)[0]) 
    {
        port = 0;
        printf("initialize Speedgoat IO601 CAN 1\n");
        
        bt0 = (((uint8_T)mxGetPr(CAN1_USER_BAUDRATE_ARG)[1] -1) << 6) | ((uint8_T)mxGetPr(CAN1_USER_BAUDRATE_ARG)[0] - 1);
        bt1 = (((uint8_T)mxGetPr(CAN1_USER_BAUDRATE_ARG)[3] -1) << 4) | ((uint8_T)mxGetPr(CAN1_USER_BAUDRATE_ARG)[2] - 1);
        canbus = (uint8_T)mxGetPr(CAN1_BUS_ARG)[0] - 1;
        
        status = InitCAN(ioaddress0, bci, port, bt0, bt1, canbus);  
        if (!status)
        {
            sprintf(msg, "%s: Failed to init CAN 1", DEVNAME);
            ssSetErrorStatus(S, msg);
            return;
        }       
        
        accMask = (uint32_T)mxGetPr(STDACC1_ARG)[0];
        accCode = (uint32_T)mxGetPr(STDACC1_ARG)[1];
        mode = 0;
        mask_num = 0;
        status = SetAcceptanceMask(ioaddress0, bci, port, mask_num, mode, accMask, accCode);  
        if (!status)
        {
            sprintf(msg, "%s: Failed to set STD acceptance mask 1 (CAN 1)", DEVNAME);
            ssSetErrorStatus(S, msg);
            return;
        }
       
        accMask = (uint32_T)mxGetPr(STDACC1_ARG)[2];
        accCode = (uint32_T)mxGetPr(STDACC1_ARG)[3];
        mode = 0;
        mask_num = 1;
        status = SetAcceptanceMask(ioaddress0, bci, port, mask_num, mode, accMask, accCode);  
        if (!status)
        {
            sprintf(msg, "%s: Failed to set STD acceptance mask 2 (CAN 1)", DEVNAME);
            ssSetErrorStatus(S, msg);
            return;
        }
        
        accMask = (uint32_T)mxGetPr(EXTACC1_ARG)[0];
        accCode = (uint32_T)mxGetPr(EXTACC1_ARG)[1];
        mode = 1;
        mask_num = 0;
        status = SetAcceptanceMask(ioaddress0, bci, port, mask_num, mode, accMask, accCode);  
        if (!status)
        {
            sprintf(msg, "Failed to set EXT acceptance mask 1 (CAN 1)"); //, DEVNAME);
            ssSetErrorStatus(S, msg);
            return;
        }
       
        accMask = (uint32_T)mxGetPr(EXTACC1_ARG)[2];
        accCode = (uint32_T)mxGetPr(EXTACC1_ARG)[3];
        mode = 1;
        mask_num = 1;
        status = SetAcceptanceMask(ioaddress0, bci, port, mask_num, mode, accMask, accCode);  
        if (!status)
        {
            sprintf(msg, "Failed to set EXT acceptance mask 2 (CAN 1)"); //, DEVNAME);
            ssSetErrorStatus(S, msg);
            return;
        }
        
        mode = BCI_POLL_MODE;
        status = ConfigRxQueue(ioaddress0, bci, port, mode);
        if (!status)
        {
            sprintf(msg, "%s: Failed to configure RX queue (CAN 1)", DEVNAME);
            ssSetErrorStatus(S, msg);
            return;
        }
        
        status = StartCAN(ioaddress0, bci, port);
        if (!status)
        {
            sprintf(msg, "%s: Failed to start CAN on port 1", DEVNAME);
            ssSetErrorStatus(S, msg);
            return;
        }
        
    
    }
    
    /* if required, configure port 2 */
    if ((uint8_T)mxGetPr(CAN2_ENABLE_ARG)[0]) 
    {
        port = 1;
        printf("initialize Speedgoat IO601 CAN 2\n");
        
        bt0 = (((uint8_T)mxGetPr(CAN2_USER_BAUDRATE_ARG)[1] -1) << 6) | ((uint8_T)mxGetPr(CAN2_USER_BAUDRATE_ARG)[0] - 1);
        bt1 = (((uint8_T)mxGetPr(CAN2_USER_BAUDRATE_ARG)[3] -1) << 4) | ((uint8_T)mxGetPr(CAN2_USER_BAUDRATE_ARG)[2] - 1);
        canbus = (uint8_T)mxGetPr(CAN2_BUS_ARG)[0] - 1;
        
        status = InitCAN(ioaddress0, bci, port, bt0, bt1, canbus);  
        if (!status)
        {
            sprintf(msg, "%s: Failed to init CAN 2", DEVNAME);
            ssSetErrorStatus(S, msg);
            return;
        }       
        
        accMask = (uint32_T)mxGetPr(STDACC2_ARG)[0];
        accCode = (uint32_T)mxGetPr(STDACC2_ARG)[1];
        mode = 0;
        mask_num = 0;
        status = SetAcceptanceMask(ioaddress0, bci, port, mask_num, mode, accMask, accCode);  
        if (!status)
        {
            sprintf(msg, "%s: Failed to set STD acceptance mask 1 (CAN 2)", DEVNAME);
            ssSetErrorStatus(S, msg);
            return;
        }
       
        accMask = (uint32_T)mxGetPr(STDACC2_ARG)[2];
        accCode = (uint32_T)mxGetPr(STDACC2_ARG)[3];
        mode = 0;
        mask_num = 1;
        status = SetAcceptanceMask(ioaddress0, bci, port, mask_num, mode, accMask, accCode);  
        if (!status)
        {
            sprintf(msg, "%s: Failed to set STD acceptance mask 2 (CAN 2)", DEVNAME);
            ssSetErrorStatus(S, msg);
            return;
        }
        
        accMask = (uint32_T)mxGetPr(EXTACC2_ARG)[0];
        accCode = (uint32_T)mxGetPr(EXTACC2_ARG)[1];
        mode = 1;
        mask_num = 0;
        status = SetAcceptanceMask(ioaddress0, bci, port, mask_num, mode, accMask, accCode);  
        if (!status)
        {
            sprintf(msg, "Failed to set EXT acceptance mask 1 (CAN 2)"); //, DEVNAME);
            ssSetErrorStatus(S, msg);
            return;
        }
        
        accMask = (uint32_T)mxGetPr(EXTACC2_ARG)[2];
        accCode = (uint32_T)mxGetPr(EXTACC2_ARG)[3];
        mode = 1;
        mask_num = 1;
        status = SetAcceptanceMask(ioaddress0, bci, port, mask_num, mode, accMask, accCode);  
        if (!status)
        {
            sprintf(msg, "Failed to set EXT acceptance mask 2 (CAN 2)"); //, DEVNAME);
            ssSetErrorStatus(S, msg);
            return;
        }
        
        
        mode = BCI_POLL_MODE;
        status = ConfigRxQueue(ioaddress0, bci, port, mode);
        if (!status)
        {
            sprintf(msg, "%s: Failed to configure RX queue (CAN 2)", DEVNAME);
            ssSetErrorStatus(S, msg);
            return;
        }
        
        status = StartCAN(ioaddress0, bci, port);
        if (!status)
        {
            sprintf(msg, "%s: Failed to start CAN on port 2", DEVNAME);
            ssSetErrorStatus(S, msg);
            return;
        }
        
        /* clear the buffer */
        for (i = 0; i < 50; i++)
        {
            pQueue = (QUEUEENTRY *)((pciinfo.VirtAddress[2]) + 0x820 + i * sizeof(QUEUEENTRY));
            pQueue->word[0] = 0;
            
            pQueue = (QUEUEENTRY *)((pciinfo.VirtAddress[2]) + 0xC08 + i * sizeof(QUEUEENTRY));
            pQueue->word[0] = 0;
        }
    
        
    
    }
    
#endif

}

static void mdlOutputs(SimStruct *S, int_T tid)
{
#ifndef MATLAB_MEX_FILE  
#endif
}

static void mdlTerminate(SimStruct *S)
{

#ifndef MATLAB_MEX_FILE      

   uint8_T port;
   uint32_T  base0= ssGetIWorkValue(S, IOADDRESS0_I_IND);
   uint32_T   base2= ssGetIWorkValue(S, IOADDRESS2_I_IND);
   volatile uint32_T *ioaddress0;
   volatile BCICOMMAND *bci;

   uint8_T CommandResult;

   
   ioaddress0 =( void *)base0;
   bci = (volatile BCICOMMAND *)base2;    
  
   if ((uint8_T)mxGetPr(CAN1_ENABLE_ARG)[0]) 
   {
      port = 0;
      CommandResult = StopCAN(ioaddress0, bci, port);
      if (!CommandResult)
      {
            sprintf(msg, "IO601: Failed to stop CAN on port 1");
            ssSetErrorStatus(S, msg);
            return;
      }
   }
    
   if ((uint8_T)mxGetPr(CAN2_ENABLE_ARG)[0]) 
   {
      port = 1;
      CommandResult = StopCAN(ioaddress0, bci, port);
      if (!CommandResult)
      {
        sprintf(msg, "IO601: Failed to stop CAN on port 2");
        ssSetErrorStatus(S, msg);
        return;
      }
   }
    
#endif 


}

#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif
