#ifndef  __SG_VME_IO812_C__
#define  __SG_VME_IO812_C__

#include <math.h>
#include "sg_vme_io812.h"



// Read unit8 from ZMI4104 
volatile uint8_T zmiRead8(ZMI4104TYPE* ptBaseReg, uint16_T offset)
{
    volatile uint8_T* ptTempReg = (volatile uint8_T*)ptBaseReg;
    
    return ptTempReg[offset];
}

// Read unit16 from ZMI4104 
volatile uint16_T zmiRead16(ZMI4104TYPE* ptBaseReg, uint16_T offset)
{
    volatile uint16_T* ptTempReg = (volatile uint16_T*)ptBaseReg;
    
    return (ptTempReg[offset/2]);
}

// Read unit32 from ZMI4104 - differs to IO810 in output form (big endian)
volatile uint32_T zmiRead32(ZMI4104TYPE* ptBaseReg, uint16_T offset)
{
 
	volatile uint32_T* ptTempReg = (volatile uint32_T*)ptBaseReg;
    	uint32_T v = ptTempReg[offset/4];
	
//dbv_printf("v is 0x%x \n", ptTempReg[offset/4]);
//dbv_printf("shifted is 0x%x \n", (v << 16) | (v >> 16));
//return (ptTempReg[offset/4]);
    return (v << 16) | (v >> 16);
   
}

// Write unit8 to ZMI4104 
void zmiWrite8(ZMI4104TYPE* ptBaseReg, uint16_T offset, uint8_T data)
{
    volatile uint8_T* ptTempReg = (volatile uint8_T*)ptBaseReg;
    ptTempReg[offset] = data;
}

// Write unit16 to ZMI4104 
void zmiWrite16(ZMI4104TYPE* ptBaseReg, uint16_T offset, uint16_T data)
{
  
	volatile uint16_T* ptTempReg = (volatile uint16_T*)ptBaseReg;
    ptTempReg[offset/2] = data;
}

// Write unit32 to ZMI4104 - watch out for the writing form (big endian/little endian)
void zmiWrite32(ZMI4104TYPE* ptBaseReg, uint16_T offset, uint32_T data)
{
	 
    volatile uint32_T* ptTempReg = (volatile uint32_T*)ptBaseReg;
	
	
    ptTempReg[offset/4] = (data << 16) | (data >> 16);
    //ptTempReg[offset/4] = data; 

}

/**************************************************************************
 * Function: VmeBusInit
 * arg 1, SimStruct *S : Simulink structure
 * arg 2, uintptr_t *mappingreg_bar: pointer to BAR 3
 * return: 0 if success, 1 if error
 * Description: Initialize Vme Bus through Bus Adapter card
 * 
 * Modifications 
 * +-------------+----------------------------------------------+--------+
 * | Date        | Comments                                     | Author |
 * +-------------+----------------------------------------------+--------+
 * | 18-Oct-2012 | First version                                | DK     |
 * +-------------+----------------------------------------------+--------+
 *
 *************************************************************************/

int VmeBusInit(SimStruct *S, uintptr_t mappingreg_bar, char msg[])
{
	 volatile uint32_T temp;
	 uint8_T VmeBusStat;

	 dbv_printf("Local Node: 0x%X\n",  mappingreg_bar+VME_NODE_LOCAL_STATUS & 0xF);

    if ((mappingreg_bar+VME_NODE_LOCAL_STATUS & 0x0F) == 0)   // Read Local Status register bit 0
    {
	
	// VME Master CSR Register (PVME_MASCSR) 0x404-0x407
	// Enable "vmas_READERR_BP" -> VME READ errors don't get aborted
    *((uint32_T *)(mappingreg_bar + 0x404)) |= (1 << 7);

	// PCI Express INgress MMU Address pointer (PCIE_MMUADD) 0x020 - 0x023
	// PCI Express INgress MMU Data Register (PCIE_MMUDAT) 0x024 - 0x027

	// Set "INgress SELECT" to non-prefetchable
    *((uint32_T *)(mappingreg_bar + 0x20)) = (1 << 16);
	
	// Refer to 2.1.6.1 PCIe_EP INgress MMU Page Descriptor Format in ALTHEA User Guide
    *((uint32_T *)(mappingreg_bar + 0x24)) = 0x1243;  // 1203 - include 4 for big endian / little endian

    // Debug
   	// dbv_printf("CSR Bar 3 0x24: 0x%X\n",  *((uint32_T *)(mappingreg_bar + 0x24)));
	// dbv_printf("CSR Bar 3 0x24: 0x%X\n",  *((uint32_T *)(mappingreg_bar + 0x24)));

	// Read from register to auto-increment MMU address pointer
	temp = *((uint32_T *)(mappingreg_bar + 0x24));

    *((uint32_T *)(mappingreg_bar + 0x20)) = (1 << 16) | (1 << 1);
    *((uint32_T *)(mappingreg_bar + 0x24)) = 0x0;

    *((uint32_T *)(mappingreg_bar + 0x20)) = (1 << 16);


	VmeBusStat = VmeBusStatus(S, (volatile uint8_T *) mappingreg_bar);

	dbv_printf("VmeBusStat: 0x%X\n",  VmeBusStat); 

	return VmeBusStat;



    }
    else
    {
		
//         sprintf(msg,"%s: initializazion failed\n", DEVNAME);
//         ssSetErrorStatus(S,msg);
        return -1;
    }  		 
}

/**************************************************************************
 * Function: VmeBusStatus
 * arg 1, SimStruct *S: Simulink Structure
 * arg 2,  uintptr_t *mappingreg_bar : pointer to the CSR
 * arg 3, char msg[]: return error message
 * return: 0 if success, or error code
 * Description: Check the VME CR/CSR BSR & BCR Registers
 * 
 * Modifications 
 * +-------------+----------------------------------------------+--------+
 * | Date        | Comments                                     | Author |
 * +-------------+----------------------------------------------+--------+
 * | 19-Oct-2012 | First version                                | DK     |
 * +-------------+----------------------------------------------+--------+
 * | 10-Dec-2012 | Error messages removed                       | DK     |
 * +-------------+----------------------------------------------+--------+
 *
 *************************************************************************/

// REWRITE FOR NEW BOARD
uint8_T VmeBusStatus (SimStruct *S, BAR1TYPE *mappingreg_bar)
{
	volatile uint32_T *bar3 = 0x00;
	volatile uint32_T tempByte = 0x00;
	volatile uint32_T tempByte1 = 0x00;
	volatile uint32_T tempByte2 = 0x00;
	volatile uint32_T tempByte3 = 0x00;


	bar3 = (volatile uint32_T*)  ((uintptr_t)(mappingreg_bar)); 
    // VME64x Status Error Register  
	tempByte = bar3[VME_LOCAL_ERROR_STATUS] & 1<<28;
	tempByte1 = bar3[VME_LOCAL_ERROR_STATUS] & 1<<31; 
	// Refer to 3.3.8 for more information
    
	// VME64x Agent_SW Interrupt Generator
	tempByte2 = bar3[VME_LOCAL_ERROR_STATUS2] & 1<<11; 
	// Refer to 3.3.4 for more information 

	// VME64x CR/CSR BSR & BCR Registers
	tempByte3 = bar3[VME_LOCAL_ERROR_STATUS3] & 1<<3;  
	// Refer to 3.3.21 for more information
	
	printf("E1: 0x%x \n",tempByte );
	printf("E2: 0x%x \n",tempByte1 ); 
	printf("E3: 0x%x \n",tempByte2 );  
	printf("E4: 0x%x \n",tempByte3); 


    if (tempByte)
    {	
		//VME BTO Error  
		dbv_printf("Error: 0x%X\n",  tempByte); 
        return 1;
    }else if (tempByte1)  //(tempByte1[VME_LOCAL_ERROR_STATUS] & 1<<31)
    {	
		//VME Error Flag   (tempByte1[VME_LOCAL_ERROR_STATUS] & 1<<31)
		dbv_printf("Error: 0x%X\n", tempByte1); 
        return 2;
    }
    else if (tempByte2) 
    {
        // VME Interrupt Pending status flag - Bit 11 
		dbv_printf("Error: 0x%X\n",  tempByte2);
        return 3;
    }
    else if (tempByte3)
    {
        // VME BERR condition generated 
		dbv_printf("Error: 0x%X\n",  tempByte3);
        return 4;
    } 

    return 0;
}

/**************************************************************************
 * Function: VmeZmiMapping
 * arg 1, int_T id: id of the card to map (1 or 2)
 * arg 2, uint32_T *mappingreg_bar: pointer to BAR 3
 * arg 3, int_T addr_sw1: Code of SW1
 * arg 4, int_T addr_sw2: Code of SW2
 * return: 0 if success
 * Description: Mapping of the ZMI card(s) on the Bus Adapter. After the
 *              call of this functions, the Remote windows registers are
 *              mapped with the ZMI card(s) registers.
 * 
 * Modifications 
 * +-------------+----------------------------------------------+--------+
 * | Date        | Comments                                     | Author |
 * +-------------+----------------------------------------------+--------+
 * | 18-Oct-2012 | First version                                | DK     |
 * +-------------+----------------------------------------------+--------+
 *
 *************************************************************************/

int VmeZmiMapping(int_T id, volatile uint32_T *mappingreg_bar, int_T addr_sw1, int_T addr_sw2)
{    
	// Not used for new HW anymore
   
    uint8_T i;
    uint32_T lword;
    printf("Zygo ZMI4104C Card %i mapping\n", id);
    
	dbv_printf("bar2 value: 0x%X\n", *(uint16_T *)(mappingreg_bar));
    for (i = 0; i < 4; i++)     // for each axis
    {
        
        dbv_printf("Zygo ZMI4104C Card %i, mapping axis %i\n",id, i+1);
       
                
        lword = 0x00000000;
		

        lword |= (0x00004 << 12);       //A31-A12
        lword |= (addr_sw1 << 20);      // A20-A23
        lword |= (addr_sw2 << 16);      // A16-A19
        lword |= i << 12;               // Axis #
         lword |= (0x3D << 6);           // Address Modifier
          lword |= (0x2 << 4);            // Function code
          lword |= (0x0 << 1);            // Data swapping
        	
		// do we need to do this 2-step writing here as well?
        /*if (id == 1)
        {

		if(i==0){
		*(mappingreg_bar+0x0000) = lword;
		dbv_printf("lword: 0x%X\n", lword);
		 printf("axis 0 value:  0x%08x\n", *(uint16_T *)(mappingreg_bar+0x0000));
		}else if(i==1){
		*(mappingreg_bar + 0x1000) = lword;
		 printf("axis 1 value:  0x%08x\n", *(uint16_T *)(mappingreg_bar + 0x1000));
		}else if(i==2){
		*(mappingreg_bar + 0x2000) = lword;
 		 printf("axis 2 value:  0x%08x\n", *(uint16_T *)(mappingreg_bar + 0x2000));
		}else if(i==3){
		*(mappingreg_bar + 0x3000) = lword;
		printf("axis 3 value:  0x%08x\n", *(uint16_T *)(mappingreg_bar + 0x3000));
		}

 		
          //  mappingreg_bar[i] = lword;
           
          dbv_printf("Mapping register 0x%x = 0x%08x \n", i, mappingreg_bar[i]);
           
        }
        else if (id == 2)
        {
            mappingreg_bar[i+4] = lword;
            dbv_printf("Mapping register 0x%x = 0x%08x \n", i+4, mappingreg_bar[i+4]);
            
        }*/
    }
 	 printf("lword value: 0x%X\n", lword);
    sg_wait_s(3); // Wait configuration (don't delete this delay!)
    
    return 0;
}

/* Axis init *************************************************************/
/**************************************************************************
 * Function: VmeZmiAxisInit
 * arg 1, ZMI4104TYPE *ptZmiRegs1: Pointer to the axis register
 * arg 2, int axis: Axis number to Initialize
 * return: 0 if success
 * Description: Initialization of Axis 
 * 
 * Modifications 
 * +-------------+----------------------------------------------+--------+
 * | Date        | Comments                                     | Author |
 * +-------------+----------------------------------------------+--------+
 * | 18-Oct-2012 | First version                                | DK     |
 * +-------------+----------------------------------------------+--------+
 *
 *************************************************************************/
int VmeZmiAxisInit(ZMI4104TYPE* ptZmiRegs, int axis)
{
    volatile uint16_T tempData16;
    
    zmiWrite32(ptZmiRegs, ZMI_VME_ERROR_CLEAR0, 0xFFFFFFFF);
    
    zmiWrite16(ptZmiRegs, ZMI_VME_COMMAND_REGISTER, 0x3F);
    
    tempData16 = zmiRead16(ptZmiRegs, ZMI_VME_CONTROL_REGISTER_2);
    
    tempData16 &= 0xFF1F;  // Delete VME Bit window
    tempData16 |= ZMI4000_VME_BIT_WINDOW << 5;  // Set VME Bit Window
    tempData16 |= 0x0200; // Set Aux register enable (for CEC)
    tempData16 &= 0xE7FF; // Set both SCLK VME Sample In and VME ENABLE 32-bit Overflow to 0
    tempData16 |= (1 << 4); // Set DACx16 Bit for amplified analog SSI-output
    
    zmiWrite16(ptZmiRegs, ZMI_VME_CONTROL_REGISTER_2, tempData16);
    
    if (axis == 1)
    {
        zmiWrite16(ptZmiRegs, ZMI_VME_SCLK_COMMAND_REGISTER, 0x1);
    }
    
    if (axis % 2)   // Axis 1 or 3
    {
        zmiWrite16(ptZmiRegs, ZMI_VME_CONTROL_REGISTER_16, 0x0023);
        zmiWrite16(ptZmiRegs, ZMI_VME_CONTROL_REGISTER_17, 0x0C00);
    }
	return 0;
}

/* Synchron Axis init *************************************************************/
// Added function (Source: CZ), 04/06/2016
int VmeZmiAxisSyncInit(ZMI4104TYPE* ptZmiRegs, int axis, int boardNumber)
{
    volatile uint16_T tempData16;
    
    zmiWrite32(ptZmiRegs, ZMI_VME_ERROR_CLEAR0, 0xFFFFFFFF); // VME Error Clear 0 und VME Error Clear 1 
    
    zmiWrite16(ptZmiRegs, ZMI_VME_COMMAND_REGISTER, 0x3F);   // Reset Axis, Position, Time, VME Error
    
    tempData16 = zmiRead16(ptZmiRegs, ZMI_VME_CONTROL_REGISTER_2);
    
    tempData16 &= 0xFF1F;  // Delete VME Bit window
    tempData16 |= ZMI4000_VME_BIT_WINDOW << 5; // Set VME Bit Window
    tempData16 |= 0x0200; // Set Aux register enable (for CEC)
    tempData16 &= 0xE7FF; // Set both SCLK VME Sample In and VME ENABLE 32-bit Overflow to 0
    tempData16 |= (1 << 4); // Set DACx16 Bit for amplified analog SSI-output(Interferometerjustage)
    
    zmiWrite16(ptZmiRegs, ZMI_VME_CONTROL_REGISTER_2, tempData16);
    
    if (axis == 1 && boardNumber == 1)
    {
        zmiWrite16(ptZmiRegs, ZMI_VME_SCLK_COMMAND_REGISTER, 0x1);
        zmiWrite16(ptZmiRegs, ZMI_VME_CONTROL_REGISTER_16, 0x3C00); /*3c00 FineTiming 1.Karte Kanal 1 und 2*/
        
    }
    if (axis == 3 && boardNumber == 1)
    {
        zmiWrite16(ptZmiRegs, ZMI_VME_CONTROL_REGISTER_16, 0x3E00); /*0x200 OutEnable + 3c00 FineTiming 1.Karte Kanal 3 und 4*/
        
    }
    if (axis == 1 && boardNumber == 2)
    {
        zmiWrite16(ptZmiRegs, ZMI_VME_CONTROL_REGISTER_16, 0x3C00); /*3c00 FineTiming 2.Karte Kanal 1 und 2*/
        
    }
    if (axis == 3 && boardNumber == 2)
    {
        zmiWrite16(ptZmiRegs, ZMI_VME_CONTROL_REGISTER_16, 0x3C00); /*3c00 FineTiming 2.Karte Kanal 3 und 4*/
        
    }
    if (axis % 2)   // Axis 1 or 3
    {
        zmiWrite16(ptZmiRegs, ZMI_VME_CONTROL_REGISTER_17, 0x0C00);        /*P2 SCLK1 Timer einstellen ueber Controlregister 17; Aber SCLK1 Timer nicht aktiv! Sinnlos!*/
    }
	return 0;
}

int VmeZmiAxisInit_intTriggerModeForceExtSample(ZMI4104TYPE* ptZmiRegs, int axis)
{
    volatile uint16_T Data = 0x0000;
   
    // uninstall Interrupt handle here ...
    
    zmiWrite16(ptZmiRegs, ZMI_VME_CONTROL_REGISTER_0, 0);
	
	zmiWrite16(ptZmiRegs, ZMI_VME_CONTROL_REGISTER_1, 0);

	zmiWrite16(ptZmiRegs, ZMI_VME_CONTROL_REGISTER_2, 0);
	
	zmiWrite16(ptZmiRegs, ZMI_VME_CONTROL_REGISTER_3, 0);
	
	zmiWrite16(ptZmiRegs, ZMI_VME_CONTROL_REGISTER_4, 0);
	
	zmiWrite16(ptZmiRegs, ZMI_VME_CONTROL_REGISTER_5, 0);
	
    if (axis % 2)   // Axis 1 or 3
    {
        zmiWrite16(ptZmiRegs, ZMI_VME_CONTROL_REGISTER_15, 0);
        zmiWrite16(ptZmiRegs, ZMI_VME_CONTROL_REGISTER_16, 0);
        zmiWrite16(ptZmiRegs, ZMI_VME_CONTROL_REGISTER_17, 0);
        
        zmiWrite16(ptZmiRegs, ZMI_VME_DIAG_TEMP_MONITOR_CONTROL_REG, 0x2A0D);
	}
    
    if (axis == 1)
    {
        zmiWrite16(ptZmiRegs, ZMI_VME_CE_CONTROL_REGISTER, 0x0000);
    }
    
    if (axis == 3)
    {
        zmiWrite16(ptZmiRegs, ZMI_VME_CE_CONTROL_REGISTER, 0x0003);
    }

	zmiWrite16(ptZmiRegs, ZMI_VME_EEPROM_CONTROL_REGISTER, 0x0000);

	zmiWrite16(ptZmiRegs, ZMI_VME_USER_VELOCITY_REGISTER, 0xFFFF);

    
    // Init internal trigger mode *****************************************
    
	zmiWrite32(ptZmiRegs, ZMI_VME_ERROR_CLEAR0, 0xFFFFFFFF);
		
	/*FA Reset axis, position quick, time, position, P2 errors VME errors*/
	/*FA setzen ueber Command Register*/
	zmiWrite16(ptZmiRegs, ZMI_VME_COMMAND_REGISTER, 0x003F);
		
	/*FA VME Bit Window werden in Position Register geshiftet */
	Data = zmiRead16(ptZmiRegs, ZMI_VME_CONTROL_REGISTER_2);

	Data &= 0xFF1F;	//VME Bit Window loeschen
	Data |= ZMI4000_VME_BIT_WINDOW << 5;	//VME Bit Window setzen
	Data |= 0x200;		//Aux Reg. Enable (fuer CEC Zugriff) setzen
	Data &= 0xE7FF;	//SCLK VME Sample In und VME enable 32bit overflow loeschen
	Data |= 1<< 4; //DACx16 Bit setzen um analoge SSI-Ausgabe zu verst�rken (Interferometerjustage) ~OtS 18.08.2010
	
    zmiWrite16(ptZmiRegs, ZMI_VME_CONTROL_REGISTER_2, Data);
	
	if (axis % 2) // Axis 1 and 3
	{	
		/*FA USERLED und SCLK devide by 2 einstellen ueber Controlregister 16*/
		zmiWrite16(ptZmiRegs, ZMI_VME_CONTROL_REGISTER_16, 0x0023);
	
		/*FA P2 SCLK1 Timer einstellen ueber Controlregister 17*/
		zmiWrite16(ptZmiRegs, ZMI_VME_CONTROL_REGISTER_17, 0x0C00);
    }
    
    zmiWrite16(ptZmiRegs, ZMI_VME_SCLK_COMMAND_REGISTER, 0x1);  // Force External Sample
    
    if (axis == 3)
    {
        zmiWrite16(ptZmiRegs, ZMI_VME_SAMPLE_TIMER_REGISTER, 0x1387);
	
        /*FA SCLK1 output enable ueber Controlregister 17 setzen*/
        zmiWrite16(ptZmiRegs,ZMI_VME_CONTROL_REGISTER_17, 0x200);

        /*FA USERLED und "SCLK devide by 2", SCLK0 enablen mit Output*/
        /*FA einstellen ueber Controlregister 16*/
        zmiWrite16(ptZmiRegs,ZMI_VME_CONTROL_REGISTER_16, 0x0E23);        
    }
    
    
    dbv_printf("Axis %i, init ok\n");

    
    return 0;
}


/**************************************************************************
 * Function: VmeZmiReadPosition
 * arg 1, ZMI4104TYPE *ptZmiRegs1: Pointer to the axis register
 * arg 2, uint32_T *ptOutPort_Pos: Sim out port for Position
 * return: 0 if success
 * Description: Read the Position from the VME Position MSB/LSB regs
 * 
 * Modifications 
 * +-------------+----------------------------------------------+--------+
 * | Date        | Comments                                     | Author |
 * +-------------+----------------------------------------------+--------+
 * | 23-Oct-2012 | First version                                | DK     |
 * +-------------+----------------------------------------------+--------+
 *
 *************************************************************************/
int VmeZmiReadPosition(ZMI4104TYPE *ptZmiRegs, real_T *ptOutPort_Pos)
{           
	volatile uint32_T lsb = 0x00000000;
	volatile uint16_T ext = 0x0000;

	ext = zmiRead16(ptZmiRegs, ZMI_VME_POSITION_EXT);
	
	dbv_printf("VmeZmiReadPosition: before zmiRead32\n");
	
	lsb = zmiRead32(ptZmiRegs, ZMI_VME_POSITION_LSB);
	
	dbv_printf("VmeZmiReadPosition: after zmiRead32\n");
	
	dbv_printf("ext = 0x%04x, msb+lsb = 0x%08x\n", ext, lsb); 

	ptOutPort_Pos[0] = GetRealValue(ext, lsb);

	return 0;
 }
    
void VmeZmiReadPositionComponents(ZMI4104TYPE *ptZmiRegs, uint32_T *lsb, uint16_T *ext)
{
	*ext = zmiRead16(ptZmiRegs, ZMI_VME_POSITION_EXT);
	*lsb = zmiRead32(ptZmiRegs, ZMI_VME_POSITION_LSB);
}
	
/**************************************************************************
 * Function: VmeZmiReadSamplePosition
 * arg 1, ZMI4104TYPE *ptZmiRegs1: Pointer to the axis register
 * arg 2, uint32_T *ptOutPort_SamPos: Sim out port for Sample Position
 * return: 0 if success
 * Description: Read the Sample Position from the VME Sample Position 
 *              MSB/LSB regs
 * 
 * Modifications 
 * +-------------+----------------------------------------------+--------+
 * | Date        | Comments                                     | Author |
 * +-------------+----------------------------------------------+--------+
 * | 23-Oct-2012 | First version                                | DK     |
 * +-------------+----------------------------------------------+--------+
 *
 *************************************************************************/
int VmeZmiReadSamplePosition(ZMI4104TYPE *ptZmiRegs, real_T *ptOutPort_SamPos)
{  
	volatile uint32_T lsb = 0x00000000;
	volatile uint16_T ext = 0x0000;

	ext = zmiRead16(ptZmiRegs, ZMI_VME_SAMPLE_POSITION_EXT);
	dbv_printf("VmeZmiReadSamplePosition: before zmiRead32\n");
	lsb = zmiRead32(ptZmiRegs, ZMI_VME_SAMPLE_POSITION_LSB);
	dbv_printf("VmeZmiReadSamplePosition: after zmiRead32\n");
	dbv_printf("ext = 0x%04x, msb+lsb = 0x%08x\n", ext, lsb);	

	ptOutPort_SamPos[0] = GetRealValue(ext, lsb);

	return 0;
}
    
/**************************************************************************
 * Function: VmeZmiReadVelocity
 * arg 1, ZMI4104TYPE *ptZmiRegs1: Pointer to the axis register
 * arg 2, uint32_T *ptOutPort_Vel: Sim out port for Velocity
 * return: 0 if success
 * Description: Read the Sample Position from the VME Velocity MSB/LSB regs
 * 
 * Modifications 
 * +-------------+----------------------------------------------+--------+
 * | Date        | Comments                                     | Author |
 * +-------------+----------------------------------------------+--------+
 * | 23-Oct-2012 | First version                                | DK     |
 * +-------------+----------------------------------------------+--------+
 *
 *************************************************************************/
int VmeZmiReadVelocity(ZMI4104TYPE *ptZmiRegs, real_T *ptOutPort_Vel)
{
    uint32_T lsb;
    
	dbv_printf("VmeZmiReadVelocity: before zmiRead32\n");
    lsb = zmiRead32(ptZmiRegs, ZMI_VME_VELOCITY_LSB);
	dbv_printf("VmeZmiReadVelocity: after zmiRead32\n");
    lsb = (lsb << 16) | (lsb >> 16);
    ptOutPort_Vel[0] = lsb;
    
    return 0;
}

/**************************************************************************
 * Function: VmeZmiReadTime
 * arg 1, ZMI4104TYPE *ptZmiRegs1: Pointer to the axis register
 * arg 2, uint32_T *ptOutPort_Time: Sim out port for Time
 * return: 0 if success
 * Description: Read the Sample Position from the VME Velocity MSB/LSB regs
 * 
 * Modifications 
 * +-------------+----------------------------------------------+--------+
 * | Date        | Comments                                     | Author |
 * +-------------+----------------------------------------------+--------+
 * | 23-Oct-2012 | First version                                | DK     |
 * +-------------+----------------------------------------------+--------+
 *
 *************************************************************************/
int VmeZmiReadTime(ZMI4104TYPE *ptZmiRegs, real_T *ptOutPort_Time)
{
    uint32_T lsb;
    
	dbv_printf("VmeZmiReadTime: before zmiRead32\n");
    lsb = zmiRead32(ptZmiRegs, ZMI_VME_TIME_LSB);
	dbv_printf("VmeZmiReadTime: after zmiRead32\n");
	
    lsb = (lsb << 16) | (lsb >> 16);    
    ptOutPort_Time[0] = (real_T)lsb * 25e-9;

    return 0;
}
    
/**************************************************************************
 * Function: VmeZmiSetFilter
 * arg 1, ZMI4104TYPE *ptZmiRegs: Pointer to the axis register
 * arg 2, int8_T kp_id: kp index 0..7
 * arg 3, int8_T kv_id: kv index 0..7 
 * return: 0 if success
 * Description: Set the value of Kp and Kv for digital filtering, for the
 *				provided axis
 * 
 * Modifications 
 * +-------------+----------------------------------------------+--------+
 * | Date        | Comments                                     | Author |
 * +-------------+----------------------------------------------+--------+
 * | 28-Nov-2012 | First version                                | DK     |
 * +-------------+----------------------------------------------+--------+
 *
 *************************************************************************/
int VmeZmiSetFilter(ZMI4104TYPE *ptZmiRegs, int8_T kp_id, int8_T kv_id)
{
	uint16_T temp = 0x0000;

	temp |= kv_id;
	temp |= (kp_id << 4);

	zmiWrite16(ptZmiRegs, ZMI_VME_CONTROL_REGISTER_1, temp);

	return 0;
}

/**************************************************************************
 * Function: VmeZmiEepromRead
 * arg 1, ZMI4104TYPE *ptZmiRegs: Pointer to the axis register
 * arg 2, uint8_T offset: offset address of the EEPROM
 * return: value contained on the register
 * Description: Read the value of an EEPROM address
 * 
 * Modifications 
 * +-------------+----------------------------------------------+--------+
 * | Date        | Comments                                     | Author |
 * +-------------+----------------------------------------------+--------+
 * | 28-Nov-2012 | First version                                | DK     |
 * +-------------+----------------------------------------------+--------+
 *
 *************************************************************************/
int VmeZmiEepromRead(ZMI4104TYPE *ptZmiRegs, uint8_T offset)
{
    uint16_T temp = 0x0000;
	//dbv_printf("Read 1 %i \n", zmiRead16(ptZmiRegs, ZMI_VME_TEST_STATUS1));

    if ((zmiRead16(ptZmiRegs, ZMI_VME_TEST_STATUS1) & 0x0800) == 0x0800)  // Check if Error = 1
    {
        volatile uint16_T data = zmiRead16(ptZmiRegs, ZMI_VME_TEST_COMMAND1);

        data |= 0x0004;
        zmiWrite16(ptZmiRegs, ZMI_VME_TEST_COMMAND1, data);
    }

    while((zmiRead16(ptZmiRegs,ZMI_VME_TEST_STATUS1) & 0x0200)==0x0200);   // Wait EEPROM busy

    temp |= (0x2 << 12);    // Read
    temp |= offset;         // address 0..1024

    zmiWrite16(ptZmiRegs,ZMI_VME_EEPROM_CONTROL_REGISTER, temp);

    while((zmiRead16(ptZmiRegs,ZMI_VME_TEST_STATUS1) & 0x0200)==0x0200);   // Wait EEPROM busy

    return zmiRead16(ptZmiRegs,ZMI_VME_EEPROM_READ);
}

/**************************************************************************
 * Function: VmeZmiWaitingAxis
 * arg 1, SimStruct *S: Simulink Structure
 * arg 2, ZMI4104TYPE *ptZmiRegs: Pointer to the axis register
 * arg 3, uint8_T ax_n: axis number
 * arg 4, char msg[]: Message for error
 * return: 0 for success or error code
 * Description: Wait that the axis is ready
 * 
 * Modifications 
 * +-------------+----------------------------------------------+--------+
 * | Date        | Comments                                     | Author |
 * +-------------+----------------------------------------------+--------+
 * | 29-Nov-2012 | First version                                | DK     |
 * +-------------+----------------------------------------------+--------+
 *
 *************************************************************************/

// NOT USED ANYMORE !?
int VmeZmiWaitingAxis(SimStruct *S, ZMI4104TYPE *ptZmiRegs, uint8_T ax_n,  char msg[])
{
    uint8_T timeout = 0;
    printf("Waiting Axis %i ", ax_n);

    while((zmiRead16(ptZmiRegs, ZMI_VME_STATUS_REGISTER0) & 0x0002) != 0x0002) // wait 
    {
        timeout++;
        sg_wait_s(1);
        printf(".");
        if (timeout == 5)   // Timeout 5 seconds
        {
            printf("\n");
            sprintf(msg,"%s: Timeout, axis %i", DEVNAME, ax_n);
            ssSetErrorStatus(S,msg);
            return 1;
        }
    }
    printf("\nAxis %i ready\n", ax_n);
    return 0;
}

/**************************************************************************
 * Function: VmeZmiReset
 * arg 1, ZMI4104TYPE *ptZmiRegs: Pointer to the axis register
 * return: 0 for success or error code
 * Description: Wait that the axis is ready
 * 
 * Modifications 
 * +-------------+----------------------------------------------+--------+
 * | Date        | Comments                                     | Author |
 * +-------------+----------------------------------------------+--------+
 * | 29-Nov-2012 | First version                                | DK     |
 * +-------------+----------------------------------------------+--------+
 *
 *************************************************************************/
int VmeZmiReset(ZMI4104TYPE *ptZmiRegs)
{
    ptZmiRegs[ZMI_VME_STATUS_REGISTER0] |= 0x0020;
    
    return 0;
}

/**************************************************************************
 * Function: GetRealValue
 * arg 1, uint32_T ext: Value of the Ext register
 * arg 2, uint32_T msb: Value of the MSB+LSB registers
 * return: double (real_T) value
 * Description: Wait that the axis is ready
 * 
 * Modifications 
 * +-------------+----------------------------------------------+--------+
 * | Date        | Comments                                     | Author |
 * +-------------+----------------------------------------------+--------+
 * | 10-Dec-2012 | First version                                | Unknow |
 * +-------------+----------------------------------------------+--------+
 * | 13-Feb-2013 | Byte swap removed                            | DK     |
 * +-------------+----------------------------------------------+--------+
 *
 *************************************************************************/
real_T GetRealValue(uint32_T ext, uint32_T msb)
{
	double result = 0;
	/*
	 double: bit  63     sign
	         bits 52-62  exponent
			 bits 0-51   fraction

			 v = (-1)^sign * 2^(exponent - 1023) x 1.fraction
	*/

	int exponent = 1023 + 52;
	uint32_T fraction_high = ext & 0xFF;
	uint32_T fraction_low = (msb << 16) | (msb >> 16);

	bool isNegative = ext & 0x10;

	if (isNegative)
	{
		fraction_high = ~fraction_high;
		fraction_low ^= 0xFFFFFFFF;

		if (fraction_low == 0xFFFFFFF)
		{
			fraction_low = 0;
			fraction_high++;
		}
		else
		{
			fraction_low++;
		}
	}

	fraction_high &= 0xFF;	

	if (!fraction_high && !fraction_low)
	{
		return 0.0;
	}

	while(!(fraction_high & (1 << 20)))
	{
		fraction_high <<= 1;
		fraction_high |= (fraction_low >> 31);
		fraction_low <<= 1;
		exponent--;
	}
	
	fraction_high &= (1 << 20) - 1;

	((uint32_T*)&result)[0] = fraction_low;
	((uint32_T*)&result)[1] = fraction_high | (exponent << 20);
	
	/* sign */
	if (isNegative)
		((uint32_T*)&result)[1] |= 0x80000000;

	return result;
}

int VmeZmiReadCyclicErrorCNReal(ZMI4104TYPE *ptZmiRegs, real_T *ptValue)
{
	uint32_T aCE_CN = 0;
	uint32_T aExponent, aSign, aMantissa;
	real_T result;
	dbv_printf("VmeZmiReadCyclicErrorCNReal: before zmiRead32\n");
	aCE_CN = zmiRead32(ptZmiRegs, ZMI_VME_CE_CN_CALCULATED);
	dbv_printf("VmeZmiReadCyclicErrorCNReal: after zmiRead32\n");
    aCE_CN = (aCE_CN << 16) | (aCE_CN >> 16);
	aExponent = (aCE_CN & VMICFLOAT_EXP_MASK) >> VMICFLOAT_EXP_SHIFT;
	aSign     = (aCE_CN & VMICFLOAT_RSIGN_MASK) >> VMICFLOAT_RSIGN_SHIFT;
	aMantissa = (aCE_CN & VMICFLOAT_RMANT_MASK) >> VMICFLOAT_RMANT_SHIFT;
	result = (real_T)(aMantissa) * pow(2.0, (real_T)((signed int)aExponent - VMICFLOAT_EXP_BIAS - VMICFLOAT_MANT_BITS));
	if (aSign)
	{
		result = -result;
	}

	*ptValue = result;
	
	return 0;
}

int VmeZmiReadCyclicErrorCNImaginary(ZMI4104TYPE *ptZmiRegs, real_T *ptValue)
{
	uint32_T aCE_CN = 0;
	uint32_T aExponent, aSign, aMantissa;
	real_T result;
	dbv_printf("VmeZmiReadCyclicErrorCNImaginary: before zmiRead32\n");
	aCE_CN = zmiRead32(ptZmiRegs, ZMI_VME_CE_CN_CALCULATED);
	dbv_printf("VmeZmiReadCyclicErrorCNImaginary: after zmiRead32\n");
    aCE_CN = (aCE_CN << 16) | (aCE_CN >> 16);

	aExponent = (aCE_CN & VMICFLOAT_EXP_MASK) >> VMICFLOAT_EXP_SHIFT;
	aSign 	  = (aCE_CN & VMICFLOAT_ISIGN_MASK) >> VMICFLOAT_ISIGN_SHIFT;
	aMantissa = (aCE_CN & VMICFLOAT_IMANT_MASK) >> VMICFLOAT_IMANT_SHIFT;
	result = (real_T)(aMantissa) * pow(2.0, (real_T)((signed int)aExponent - VMICFLOAT_EXP_BIAS - VMICFLOAT_MANT_BITS));
	if (aSign)
	{
		result = -result;
	}

	*ptValue = result;
	
	return 0;
}

int VmeZmiReadCyclicErrorC1Real(ZMI4104TYPE *ptZmiRegs, real_T *ptValue)
{
	uint32_T aCE_C1 = 0;
	uint32_T aExponent, aSign, aMantissa;
	real_T result;
	dbv_printf("VmeZmiReadCyclicErrorC1Real: before zmiRead32\n");
	aCE_C1 = zmiRead32(ptZmiRegs, ZMI_VME_CE_C1_CALCULATED);
	dbv_printf("VmeZmiReadCyclicErrorC1Real: after zmiRead32\n");
    aCE_C1 = (aCE_C1 << 16) | (aCE_C1 >> 16);

	aSign = (aCE_C1 & VMIFLOAT_SIGN_MASK) >> VMIFLOAT_SIGN_SHIFT;
	aExponent = (aCE_C1 & VMIFLOAT_EXP_MASK) >> VMIFLOAT_EXP_SHIFT;
	aMantissa = (aCE_C1 & VMIFLOAT_MANT_MASK) >> VMIFLOAT_MANT_SHIFT;
	result = (real_T)(aMantissa | VMIFLOAT_MANT_MSB) * pow(2.0, (real_T)((signed)aExponent - VMIFLOAT_EXP_BIAS - VMIFLOAT_MANT_BITS));
	if (aSign)
	{
		result = -result;
	}

	*ptValue = result;
	
	return 0;
}

int VmeZmiReadCyclicErrorC0Real(ZMI4104TYPE *ptZmiRegs, real_T *ptValue)
{
	uint32_T aCE_C0 = 0;
	signed short aShortCE_C0_real;
	//real_T result;
	dbv_printf("VmeZmiReadCyclicErrorC0Real: before zmiRead32\n");
	aCE_C0 = zmiRead32(ptZmiRegs, ZMI_VME_CE_C0_CALCULATED);
	dbv_printf("VmeZmiReadCyclicErrorC0Real: after zmiRead32\n");
    aCE_C0 = (aCE_C0 << 16) | (aCE_C0 >> 16);

	aShortCE_C0_real = (signed short)( (aCE_C0 >> 16) & 0xFFFF );

	*ptValue = 1.0 * aShortCE_C0_real;

	return 0;
}

int VmeZmiReadCyclicErrorC0Imaginary(ZMI4104TYPE *ptZmiRegs, real_T *ptValue)
{
	uint32_T aCE_C0 = 0;
	signed short aShortCE_C0_im;
	//real_T result;
	dbv_printf("VmeZmiReadCyclicErrorC0Imaginary: before zmiRead32\n");
	aCE_C0 = zmiRead32(ptZmiRegs, ZMI_VME_CE_C0_CALCULATED);
	dbv_printf("VmeZmiReadCyclicErrorC0Imaginary: after zmiRead32\n");
    aCE_C0 = (aCE_C0 << 16) | (aCE_C0 >> 16);

	aShortCE_C0_im = (signed short)( aCE_C0 & 0xFFFF );

	*ptValue = 1.0 * aShortCE_C0_im;

	return 0;
}

#endif