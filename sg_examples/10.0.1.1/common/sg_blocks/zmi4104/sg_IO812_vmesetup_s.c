#define 	S_FUNCTION_LEVEL 	2
#undef 		S_FUNCTION_NAME
#define 	S_FUNCTION_NAME 	sg_IO812_vmesetup_s

#include 	<stddef.h>
#include 	<stdlib.h>
#include    <stdbool.h>

#include 	"simstruc.h" 

#ifdef 		MATLAB_MEX_FILE
#include 	"mex.h"
#endif

#ifndef         MATLAB_MEX_FILE
#include        <windows.h>

#include    "sg_common.h"
#include    "sg_vme_io812.h"
#include "sg_callback_legacy.h"

#endif

/* Input Arguments */

#define NUMBER_OF_ARGS          (7)
#define SLOT_ARG                ssGetSFcnParam(S,0)
#define SAMPLETIME_ARG          ssGetSFcnParam(S,1)
#define MODULES_ARG             ssGetSFcnParam(S,2)
#define Z1_ADDRSW1_ARG          ssGetSFcnParam(S,3)
#define Z1_ADDRSW2_ARG          ssGetSFcnParam(S,4)
#define Z2_ADDRSW1_ARG          ssGetSFcnParam(S,5)
#define Z2_ADDRSW2_ARG          ssGetSFcnParam(S,6)

#define NO_I_WORKS              (3)
#define BASE_ADDR1_I_IND        (0)
#define BASE_ADDR2_I_IND        (1)
#define BASE_ADDR3_I_IND        (2)

#define NO_R_WORKS              (0)

#define NO_P_WORKS              (0)

char msg[256];

int32_T i;
 
/* Initialize Sizes ******************************************************/
static void mdlInitializeSizes(SimStruct *S)
{
    int32_T i;

    ssSetNumSFcnParams(S, NUMBER_OF_ARGS);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S))
    {
        sprintf(msg,"Wrong number of input arguments passed.\n%d arguments are expected\n", NUMBER_OF_ARGS);
        ssSetErrorStatus(S,msg);
        return;
    }

    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);

    
    ssSetNumSampleTimes(S, 1);

    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

    for( i = 0 ; i < NUMBER_OF_ARGS ; i++ )
    {
        /* None of the parameters are tunable */
        ssSetSFcnParamTunable(S,i,0);  
    }

    ssSetNumInputPorts(S, 0);
    
    ssSetNumOutputPorts(S, (int_T)mxGetPr(MODULES_ARG)[0]);
    for (i = 0 ; i < (int_T)mxGetPr(MODULES_ARG)[0] ; i++)
    {         
        ssSetOutputPortWidth(S, i, 4);
        ssSetOutputPortDataType(S, i, SS_UINT32);
    } 
    
    
    ssSetNumRWork(S, NO_R_WORKS);
    ssSetNumIWork(S, NO_I_WORKS);
    ssSetNumPWork(S, NO_P_WORKS);
    
    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE | SS_OPTION_PLACE_ASAP);
}

/* Initialize Sample Times ***********************************************/
static void mdlInitializeSampleTimes(SimStruct *S)
{
    if (mxGetPr(SAMPLETIME_ARG)[0]==-1.0)
    {
        ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
        ssSetOffsetTime(S, 0, FIXED_IN_MINOR_STEP_OFFSET);
    }
    else
    {
        ssSetSampleTime(S, 0, mxGetPr(SAMPLETIME_ARG)[0]);
        ssSetOffsetTime(S, 0, 0.0);
    }
}

/* mdlStart **************************************************************/
#define MDL_START
static void mdlStart(SimStruct *S)
{
#ifndef MATLAB_MEX_FILE

    sg_PCIDevice pciinfo;
    
    volatile uint32_T *bar4;
    volatile uint32_T *bar3;
    volatile uint32_T *bar2;
    volatile uint32_T *bar0;
    volatile uint32_T *ptAxis1, *ptAxis2, *ptAxis3, *ptAxis4, *ptBarBuffer;
    uintptr_t bar0ptr;
    uintptr_t bar2ptr;
    uintptr_t bar3ptr;
    uintptr_t bar4ptr;
    
    uint32_T *ptOutputPort1;
    uint32_T *ptOutputPort2;

    uint32_T reg_read, lbus, lslot, ii, j;
    uint8_T vmeFound;


    // Check PCI slot
    if ((int_T)mxGetPr(SLOT_ARG)[0]<0) 
    {
        dbv_printf("Slot Arg %d \n", mxGetPr(SLOT_ARG)[0]);
        if (sg_findPciDevice(&pciinfo, DEVNAME, VENDORID, DEVICEID, SUBVENDORID,
                SUBDEVICEID, 1, 0, -1)){
            ssSetErrorStatus(S, pSgErrorStr);
            return;
        }
        dbv_printf("Slot Arg slot %d \n", pciinfo.slot);
        dbv_printf("Slot Arg bus %d \n", pciinfo.bus);
    } 
    else
    {
        uint16_T bus, slot;

        if (mxGetN(SLOT_ARG) == 1) 
        {
            bus = 0;
            slot = (uint16_T)mxGetPr(SLOT_ARG)[0];
        } 
        else 
        {
            bus = (uint16_T)mxGetPr(SLOT_ARG)[0];
            slot = (uint16_T)mxGetPr(SLOT_ARG)[1];
        }
        
    if (sg_findPciDevice(&pciinfo, DEVNAME, VENDORID, DEVICEID, SUBVENDORID, SUBDEVICEID, 1, bus, slot))
        {
            ssSetErrorStatus(S, pSgErrorStr);
            return;
        }
    }
    dbv_printf("\n\n\n");
    dbv_printf("xpcShowDeviceInfo:\n");
    if (IO812_DEBUG_VERBOSE)
    {
        xpcShowPCIDeviceInfo(&pciinfo);
    }
    dbv_printf("---------------\n");
    vmeFound = 0;
    for (lslot = 0; lslot < 32; lslot++ )
    {
        for (lbus = 0; lbus < 255; lbus++)
        {
            sg_outpDW(0x0CF8, 0x80000000 | (lbus << 16) | (lslot << 11));
            reg_read = sg_inpDW(0xCFC);
            if (((reg_read & 0xFFFF) == VENDORID) && ((reg_read >> 16) & 0xFFFF) == DEVICEID)
            {
                dbv_printf("Found VME at bus(%d) and slot(%d)\n", lbus, lslot);
                vmeFound = 1;
                break;
            }
        }
        if (vmeFound)
        {
            break;
        }
    }
    for (ii = 0; ii < 16; ii++)
    {
        sg_outpDW(0x0CF8, 0x80000000 | (lbus << 16) | (lslot << 11) | (ii * 4));
        reg_read = sg_inpDW(0xCFC);

        dbv_printf("reg (%d): 0x%X\n", ii, reg_read);
    }

    sg_outpDW(0x0CF8, 0x80000000 | (lbus << 16) | (lslot << 11) | 4);
    sg_outpDW(0xCFC, 0x100007);

    sg_outpDW(0x0CF8, 0x80000000 | (lbus << 16) | (lslot << 11) | 4);

    reg_read = sg_inpDW(0xCFC);

    dbv_printf("After update of the init reg: 0x%X\n", reg_read);


    bar0ptr = (uintptr_t)sg_mapMemory(&pciinfo, 0);
    bar2ptr = (uintptr_t)sg_mapMemory(&pciinfo, 2);
    bar3ptr = (uintptr_t)sg_mapMemory(&pciinfo, 3);
    dbv_printf("bar3ptr: 0x%X\n", bar3ptr);
    bar4ptr = (uintptr_t)sg_mapMemory(&pciinfo, 4);
    bar3 = (volatile uint32_T*) ((uintptr_t)bar3ptr);                   // BAR3 CSR

    bar2 = (volatile uint32_T*) ((uintptr_t)bar2ptr);                   // BAR2 PCI MEM Space
    bar0 = (volatile uint32_T*) ((uintptr_t)bar0ptr);                   // BAR0 PCI PMEM Space
    bar4 = (volatile uint32_T*)  ((uintptr_t)bar4ptr);                  // BAR4 PCI IO Space 

    ssSetIWorkValue(S, BASE_ADDR1_I_IND, (int_T)bar3);
    ssSetIWorkValue(S, BASE_ADDR2_I_IND, (int_T)bar2);
    ssSetIWorkValue(S, BASE_ADDR3_I_IND, (int_T)bar0);

    if (sg_isModelInit() == 1)
    //Configuration routine
    {
        //PVME_SLOT1 - Set vmeBTOMOD to 111 (2048 us)
        dbv_printf("new: bar3[0x400/4]: 0x%X\n", bar3[0x400/4]);
        ptBarBuffer = &bar3[0x400/4];
        ptBarBuffer[0x00] |= 7<<8;
        dbv_printf("after: bar3[0x400/4]: 0x%X\n", bar3[0x400/4]);
        
        for (j=0; j<3; j++)
        {
            dbv_printf("bar3[0x20/4]: 0x%X\n", bar3[0x20/4]);
            //sg_wait_s(0.1);
            ptBarBuffer = &bar3[0x20/4];
            //sg_wait_s(0.1);
            ptBarBuffer[0x00] = 0x10000;
            dbv_printf("bar3[0x20/4]: 0x%X\n", bar3[0x20/4]);

            if (j==1)
            {
                ptBarBuffer = &bar3[0x24/4];
                //sg_wait_s(0.1);
                ptBarBuffer[0x00] = 0x01243;
                //sg_wait_s(0.1);
                ptBarBuffer[0x00] = 0x0;
                //sg_wait_s(0.1);
                ptBarBuffer[0x00] = 0x11243;
                //sg_wait_s(0.1);
                ptBarBuffer[0x00] = 0x0;
                //sg_wait_s(0.1);
            }

            //Read out 8 times the PCI_MMUDAT register
            for (i=0;i<8;i++)
            {
                //sg_wait_s(0.1);
                ptBarBuffer = &bar3[0x24/4];
                dbv_printf("\n%d : PCI_MMUDAT (ptBarBuffer[0x00]): %08x\n",i+1,ptBarBuffer[0x00]);
            }
        }
    }

    if (sg_isModelInit() == 0)
    {
        VmeBusInit(S, bar3ptr, msg); // VME bus initialization

        // Keep this line too see if initialization worked right (no 0xFFFF)
    
        sg_wait_s(2);
        if (VmeBusInit(S, bar3ptr, msg) != 0)
        {
            dbv_printf("%s: initialization failed\n", DEVNAME);
        }
        else
        {
            dbv_printf("%s: VME bus access done\n", DEVNAME);
        }

        /* One board only ************************************************/

        if ((int_T)mxGetPr(MODULES_ARG)[0] == 1)
        {
            dbv_printf("One board routine\n");
            /*Board 1*/
            
            ptAxis1 = &bar2[VME_REMOTE_ZMI_BOARD1_AXIS1];
            ptAxis2 = &bar2[VME_REMOTE_ZMI_BOARD1_AXIS2];
            ptAxis3 = &bar2[VME_REMOTE_ZMI_BOARD1_AXIS3];
            ptAxis4 = &bar2[VME_REMOTE_ZMI_BOARD1_AXIS4];
            ptBarBuffer = &bar2[0];
            
            dbv_printf("Remote Memory address ptAxis1[0x00]: 0x%x \n",ptAxis1[0x00]);   // Answers 0xB******* | 0x00000001, e.g. 0xB0A19001s
            dbv_printf("Remote Memory address ptAxis2[0x00]: 0x%x \n",ptAxis2[0x00]);   // Answers 0xB******* | 0x00000001   ,ptAxis2[0x20]
            dbv_printf("Remote Memory address ptAxis3[0x00]: 0x%x \n",ptAxis3[0x00]);   // Answers 0xB******* | 0x00000001
            dbv_printf("Remote Memory address ptAxis4[0x00]: 0x%x \n",ptAxis4[0x00]);   // Answers 0xB******* | 0x00000001

            ptOutputPort1 = ssGetOutputPortSignal(S, 0);

            ptOutputPort1[0] = (uint32_T)ptAxis1;
            ptOutputPort1[1] = (uint32_T)ptAxis2;
            ptOutputPort1[2] = (uint32_T)ptAxis3;
            ptOutputPort1[3] = (uint32_T)ptAxis4;

        }
        
        /* Two boards ****************************************************/
        else if ((int_T)mxGetPr(MODULES_ARG)[0] == 2)
        {
            dbv_printf("Two boards routine\n");
            /* Board 1 */
            ptAxis1 = &bar2[VME_REMOTE_ZMI_BOARD1_AXIS1];
            ptAxis2 = &bar2[VME_REMOTE_ZMI_BOARD1_AXIS2];
            ptAxis3 = &bar2[VME_REMOTE_ZMI_BOARD1_AXIS3];
            ptAxis4 = &bar2[VME_REMOTE_ZMI_BOARD1_AXIS4];

            dbv_printf("Board 1 - Remote Memory address ptAxis1[0x00]: 0x%x \n",ptAxis1[0x00]);   // Answers 0xB******* | 0x00000001, e.g. 0xB0A19001s
            dbv_printf("Board 1 - Remote Memory address ptAxis2[0x00]: 0x%x \n",ptAxis2[0x00]);   // Answers 0xB******* | 0x00000001   ,ptAxis2[0x20]
            dbv_printf("Board 1 - Remote Memory address ptAxis3[0x00]: 0x%x \n",ptAxis3[0x00]);   // Answers 0xB******* | 0x00000001
            dbv_printf("Board 1 - Remote Memory address ptAxis4[0x00]: 0x%x \n",ptAxis4[0x00]);   // Answers 0xB******* | 0x00000001
            
            
            ptOutputPort1 = ssGetOutputPortSignal(S, 0);

            ptOutputPort1[0] = (uint32_T)ptAxis1;
            ptOutputPort1[1] = (uint32_T)ptAxis2;
            ptOutputPort1[2] = (uint32_T)ptAxis3;
            ptOutputPort1[3] = (uint32_T)ptAxis4;

            /* Board 2*/
            ptAxis1 = &bar2[VME_REMOTE_ZMI_BOARD2_AXIS1];
            ptAxis2 = &bar2[VME_REMOTE_ZMI_BOARD2_AXIS2];
            ptAxis3 = &bar2[VME_REMOTE_ZMI_BOARD2_AXIS3];
            ptAxis4 = &bar2[VME_REMOTE_ZMI_BOARD2_AXIS4];


            ptOutputPort2 = ssGetOutputPortSignal(S, 1);

            ptOutputPort2[0] = (uint32_T)ptAxis1;
            ptOutputPort2[1] = (uint32_T)ptAxis2;
            ptOutputPort2[2] = (uint32_T)ptAxis3;
            ptOutputPort2[3] = (uint32_T)ptAxis4;
            
            dbv_printf("Board 2 - Remote Memory address ptAxis1[0x00]: 0x%x \n",ptAxis1[0x00]);   // Answers 0xB******* | 0x00000001, e.g. 0xB0A19001s
            dbv_printf("Board 2 - Remote Memory address ptAxis2[0x00]: 0x%x \n",ptAxis2[0x00]);   // Answers 0xB******* | 0x00000001   ,ptAxis2[0x20]
            dbv_printf("Board 2 - Remote Memory address ptAxis3[0x00]: 0x%x \n",ptAxis3[0x00]);   // Answers 0xB******* | 0x00000001
            dbv_printf("Board 2 - Remote Memory address ptAxis4[0x00]: 0x%x \n",ptAxis4[0x00]);   // Answers 0xB******* | 0x00000001
        }

    }
#endif
}

/* mdlOutput *************************************************************/
static void mdlOutputs(SimStruct *S, int_T tid)
{
#ifndef MATLAB_MEX_FILE
         
#endif
}

/* mdlTerminate **********************************************************/
static void mdlTerminate(SimStruct *S)
{   
#ifndef MATLAB_MEX_FILE
      
#endif    
}

#ifdef MATLAB_MEX_FILE  /* Is this file being compiled as a MEX-file? */
#include "simulink.c"   /* Mex glue */
#else
#include "cg_sfun.h"    /* Code generation glue */
#endif


