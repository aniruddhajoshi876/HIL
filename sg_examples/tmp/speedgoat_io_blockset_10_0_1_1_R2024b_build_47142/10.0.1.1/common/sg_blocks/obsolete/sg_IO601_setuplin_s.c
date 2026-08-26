//#define DEBUG_PRINT_FUNCTION_CALLS
//#define DEBUG_VERBOSE

#define S_FUNCTION_LEVEL 2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME sg_IO601_setuplin_s

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
#endif

#define NUMBER_OF_ARGS         (4)
#define MODULE_ARG             ssGetSFcnParam(S, 0)
#define BAUDRATE_ARG           ssGetSFcnParam(S, 1)
#define ROLE_ARG               ssGetSFcnParam(S, 2)  // master or slave
#define SLOT_ARG               ssGetSFcnParam(S, 3)

#define DEVNAME                "Speedgoat IO601"
#define VENDORID               (0x10b5)
#define DEVICEID               (0x9030)
#define SUBVENDORID            (0x10b5)
#define SUBDEVICEID            (0x2977)

#define NO_I_WORKS             (2)
#define BASE_ADDR0_I_IND       (0)
#define BASE_ADDR_I_IND        (1)

#define NO_R_WORKS             (0)
//#define DEBUG_VERBOSE           (1)


/* list of the DPRAM command
  command 0x5, 0x9 0xA are not supported since firmware V4.03 */
#define CMD_ID                    (0x1)
#define CMD_VERSION               (0x2)
#define CMD_TEST                  (0x3)
#define CMD_INIT_CAN              (0x4)
#define CMD_START_CAN             (0x6)
#define CMD_STOP_CAN              (0x7)
#define CMD_RESET_CAN             (0x8)
#define CMD_CONFIG_RX_QUEUE       (0xB)
#define CMD_GET_BOARD_INFO        (0xC)
#define CMD_START_TIMER           (0xD)
#define CMD_STOP_TIMER            (0xE)
#define CMD_SET_ACC_MASK          (0xF)

// Specific to LIN.
#define CMD_GET_LIN_STAT          (0x29)
#define CMD_START_LIN             (0x2A)
#define CMD_STOP_LIN              (0x2B)
#define CMD_RESET_LIN             (0x2C)
#define CMD_INIT_LIN              (0x2D)
#define CMD_UPDATE_RES_BUFFER_LIN (0x2E)

/* and a few parameters values: */
#define BCI_POLL_MODE          (0x0)
#define BCI_LATENCY_MODE       (0x1)
#define BCI_THROUGHPUT_MODE    (0x2)

static char_T msg[256];
uint8_T ptrWritePointer[10];
uint8_T ptrReadPointer[10];

#ifndef MATLAB_MEX_FILE

typedef struct
{
  uint8_T bId;
  uint8_T bModel;
  uint8_T bCheckSum;
  uint8_T bSendData;  
  uint8_T bLength;
  uint8_T bDummy;
  uint8_T bDataByte[8];
}BCI_t_LIN_MSG;

typedef struct 
{
    uint8_T synch;
    uint8_T count;
    uint16_T reserved;
    uint8_T command;
    uint8_T data[75];
}BCICOMMAND;


static void InterruptMicroController(volatile uint32_T *ioaddress0)
{
    uint32_T regtemp; 
    
    /* generate MC interrupt */
    regtemp = ioaddress0[0x15];
    ioaddress0[0x15] = regtemp & ~(1 << 2);
    ioaddress0[0x15] = regtemp | (1 << 2);
}

/**************************************************************************
 * Reset board
 * Uses a GPIO pin to reset the board
 *
 *
 *************************************************************************/
#define WAIT_TIME 0.050
//#define WAIT_TIME 0.2
 static void ResetBoard(volatile uint32_T *ioaddress0, volatile uint8_T *ioaddress2)
{

    uint32_T regtemp;    
    
    //reset board (PLX9030)
    regtemp = ioaddress0[0x15];    
    regtemp &= ~(1 << 11);    
    ioaddress0[0x15] = regtemp;    
    rl32eWaitDouble(WAIT_TIME);     

    regtemp |= (1 << 11);
    ioaddress0[0x15] = regtemp;

    rl32eWaitDouble(WAIT_TIME);
   
    
    /* restart firmware 
     (this part is not clear, have to ask IXXAT)
     */
            
    ioaddress2[0x00] = 0;
    ioaddress2[0x01] = 0;
    ioaddress2[0x02] = 0;
    ioaddress2[0x03] = 3;
    ioaddress2[0x04] = 2;
    ioaddress2[0x05] = 0;
    ioaddress2[0x06] = 1;
    ioaddress2[0x00] = 1;
    rl32eWaitDouble(WAIT_TIME);
    ioaddress2[0x01] = 0;
    rl32eWaitDouble(WAIT_TIME);  
    
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
    #ifdef DEBUG_VERBOSE
    printf("LIN controller firmware...");
    #endif
    bci->synch = 0;
    bci->count = 1;
    bci->command = CMD_VERSION;
    bci->synch = 1; 

    InterruptMicroController(ioaddress0);

    #ifdef DEBUG_VERBOSE
    while (bci->synch != 2)
        printf(".");
        
    printf("v%c%c%c%c\n", bci->data[1],bci->data[2],bci->data[3],bci->data[4]);
    #else
    while (bci->synch != 2);
    #endif
    return;

}

/**************************************************************************
 * Function name: StartLIN
 * Command to start the LIN controller (one per board)
 *************************************************************************/
static uint8_T StartLIN(volatile uint32_T * ioaddress0, volatile BCICOMMAND *bci) 
{    
    #ifdef DEBUG_VERBOSE
    printf("LIN controller start...");
    #endif
    bci->synch = 0;
    bci->count = 2;
    bci->command = CMD_START_LIN;    
    bci->synch = 1;

    InterruptMicroController(ioaddress0);

    #ifdef DEBUG_VERBOSE
    while (bci->synch != 2)
        printf(".");
    if(bci->data[0])
        printf(" ok\n");
    else
        printf(" failed\n");
    #else
    while (bci->synch != 2);
    #endif
    return bci->data[0]; // contains the status of the command
}

/**************************************************************************
 * Function name: StopLIN
 * Command to stop the LIN controller (one per board)
 *************************************************************************/
static uint8_T StopLIN(volatile uint32_T * ioaddress0, volatile BCICOMMAND *bci) 
{    
    #ifdef DEBUG_VERBOSE
    printf("LIN controller stop...");
    #endif
    bci->synch = 0;
    bci->count = 2;
    bci->command = CMD_STOP_LIN;    
    bci->synch = 1;

    InterruptMicroController(ioaddress0);
    #ifdef DEBUG_VERBOSE
    while (bci->synch != 2)
        printf(".");
    if(bci->data[0])
        printf(" ok\n");
    else
        printf(" failed\n");
    #else
    while (bci->synch != 2);
    #endif
    return bci->data[0]; // contains the status of the command
}

/**************************************************************************
 * Function name: ResetLIN
 * Command to stop the LIN controller (one per board)
 *************************************************************************/
static uint8_T ResetLIN(volatile uint32_T * ioaddress0, volatile BCICOMMAND *bci) 
{    
    #ifdef DEBUG_VERBOSE
    printf("LIN controller reset...");
    #endif
    bci->synch = 0;
    bci->count = 2;
    bci->command = CMD_RESET_LIN;    
    bci->synch = 1;

    InterruptMicroController(ioaddress0);

    #ifdef DEBUG_VERBOSE
    while (bci->synch != 2)
        printf(".");
    if(bci->data[0])
        printf(" ok\n");
    else
        printf(" failed\n");
    #else
    while (bci->synch != 2);
    #endif
    return bci->data[0]; // contains the status of the command
}


/**************************************************************************
 * function name: InitLIN
 *
 * purpose: this function initialize the LIN controller. Mode and baudrate
 * are configured at this moment.
 *
 * Return true when successful.
 *************************************************************************/
static uint8_T InitLIN(volatile uint32_T * ioaddress0, volatile BCICOMMAND *bci, uint8_T role, uint16_T baudrate) 
{    
    #ifdef DEBUG_VERBOSE
    printf("LIN controller init...");
    #endif
    bci->synch = 0;
    bci->count = 6;
    bci->command = CMD_INIT_LIN;
    
    bci->data[0] = 0; // reserved
    bci->data[1] = role; // master(1) or slave(0)
    //printf("role: %d\n", role);
    bci->data[2] = 0; // reserved
    bci->data[3] = baudrate & 0xFF;
    //printf("baudRate: %d\n", baudrate & 0xFF);
    bci->data[4] = (baudrate >> 8) & 0xFF;
    //printf("baudRate: %d\n", (baudrate >> 8) & 0xFF);
    bci->synch = 1;

    InterruptMicroController(ioaddress0);

    #ifdef DEBUG_VERBOSE
    while (bci->synch != 2)
        printf(".");
    if(bci->data[0])
        printf(" ok\n");
    else
        printf(" failed\n");
    #else
    while (bci->synch != 2);
    #endif
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
    #ifdef DEBUG_VERBOSE
    printf("LIN controller config rx queue...");
    #endif
    bci->synch = 0;
    bci->count = 3;
    bci->command = CMD_CONFIG_RX_QUEUE;
    bci->data[0] = port;
    bci->data[1] = mode;
    bci->synch = 1;    

    InterruptMicroController(ioaddress0);

    #ifdef DEBUG_VERBOSE
    while (bci->synch != 2)
        printf(".");
    if(bci->data[0])
        printf(" ok\n");
    else
        printf(" failed\n");
    #else
    while (bci->synch != 2);
    #endif
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

    uint16_T baudrate;
    uint8_T role;
    int8_T status;

    volatile BCICOMMAND *bci;
    volatile uint32_T *ioaddress0;
    volatile uint8_T *ioaddress2;
   

    /* board detection */
    if (mxGetN(SLOT_ARG) == 1)
    {
        bus = 0;
        slot = (int_T)mxGetPr(SLOT_ARG)[0];
    }
    else
    {
        bus = (int_T)mxGetPr(SLOT_ARG)[0];
        slot = (int_T)mxGetPr(SLOT_ARG)[1];
    }

    /* look for the PCI-Device */
    if (xpcGetPCIDeviceInfo(VENDORID, DEVICEID, SUBVENDORID, SUBDEVICEID, bus, slot, &pciinfo))
    {
        sprintf(msg, "%s SETUP (bus %d, slot %d): board not present", DEVNAME, bus, slot);
        ssSetErrorStatus(S, msg);
        return;
    }
    
    pciinfo.VirtAddress[0] = (unsigned long)xpcReserveMemoryRegion((void *)pciinfo.BaseAddress[0], pciinfo.Length[0], XPC_RT_PG_USERREADWRITE);  
    pciinfo.VirtAddress[2] = (unsigned long)xpcReserveMemoryRegion((void *)pciinfo.BaseAddress[2], pciinfo.Length[2], XPC_RT_PG_USERREADWRITE);  
    ssSetIWorkValue(S, BASE_ADDR_I_IND, pciinfo.VirtAddress[2]);
    ssSetIWorkValue(S, BASE_ADDR0_I_IND, pciinfo.VirtAddress[0]);
    
    bci = (volatile BCICOMMAND *)(pciinfo.VirtAddress[2]);    
    ioaddress0 = (volatile uint32_T *)(pciinfo.VirtAddress[0]); 
    ioaddress2 = (volatile uint8_T *)(pciinfo.VirtAddress[2]); 
    
    ptrWritePointer[(uint8_T)mxGetPr(MODULE_ARG)[0] - 1] = 0;
    ptrReadPointer[(uint8_T)mxGetPr(MODULE_ARG)[0] - 1] = 0;
    

    ResetBoard(ioaddress0, ioaddress2);

    GetFirmwareVersion(ioaddress0, bci);   

    /* the version under the pattern VX.XX is extracted from data */
    version[0] = bci->data[1];
    version[1] = bci->data[2];
    version[2] = bci->data[3];
    version[3] = bci->data[4];
    version[4] = bci->data[5];
    version[5] = '\0';

    if (strncmp(version, "4.27", 5))
    {
        sprintf(msg, "%s: wrong firmware (%s)", DEVNAME, version);
        ssSetErrorStatus(S, msg);
        return;
    }    


    // reset the LIN controller
    status = ResetLIN(ioaddress0, bci);
    if (!status)
    {
        sprintf(msg, "%s: Failed to reset LIN controller", DEVNAME);
        ssSetErrorStatus(S, msg);
        return;
    }


    // init the LIN controller
    baudrate = (uint16_T)mxGetPr(BAUDRATE_ARG)[0];
    role = (uint8_T)mxGetPr(ROLE_ARG)[0] - 1;
    status = InitLIN(ioaddress0, bci, role, baudrate);
    if (!status)
    {
        sprintf(msg, "%s: Failed to init LIN controller", DEVNAME);
        ssSetErrorStatus(S, msg);
        return;
    }

    // Config the RX queue... Is it required?
    status = ConfigRxQueue(ioaddress0, bci, 0, BCI_POLL_MODE);
    if (!status)
    {
        sprintf(msg, "%s: Failed to configure RX queue (LIN)", DEVNAME);
        ssSetErrorStatus(S, msg);
        return;
    }
    
    
    // start the LIN controller
    status = StartLIN(ioaddress0, bci);
    if(!status)
    {
        sprintf(msg, "%s: Failed to start LIN controller", DEVNAME);
        ssSetErrorStatus(S, msg);
        return;
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
  
    int8_T status;
    volatile uint32_T *ioaddress0;
    volatile BCICOMMAND *bci;
    uint32_T base0;
    uint32_T base2;    

    base0 = ssGetIWorkValue(S, BASE_ADDR0_I_IND);
    base2 = ssGetIWorkValue(S, BASE_ADDR_I_IND);
    ioaddress0 = (void *)base0;       
    bci = (volatile BCICOMMAND *)(base2);  

    status = StopLIN(ioaddress0, bci);
    if(!status)
    {
        sprintf(msg, "%s: Failed to stop LIN controller", DEVNAME);
        ssSetErrorStatus(S, msg);
        return;
    }
 
    
#endif 


}

#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif
