#ifndef __SG_VME_ZMI4104_H__
#define __SG_VME_ZMI4104_H__

#ifndef     MATLAB_MEX_FILE

#include 	<stddef.h>
#include 	<stdlib.h>

#include 	"simstruc.h" 
#include    "xpcimports.h"

#define DEVNAME         "Speedgoat VME Adapter"
#define VENDORID        0x108A
#define DEVICEID        0x0040
#define SUBVENDORID     XPC_NO_VEND_DEV
#define SUBDEVICEID     XPC_NO_VEND_DEV

/* VME Remote memory for ZMI card */
#define VME_REMOTE_ZMI_BOARD1_AXIS1    0x0000
#define VME_REMOTE_ZMI_BOARD1_AXIS2    0x0400
#define VME_REMOTE_ZMI_BOARD1_AXIS3    0x0800
#define VME_REMOTE_ZMI_BOARD1_AXIS4    0x0C00

#define VME_REMOTE_ZMI_BOARD2_AXIS1    0x1000
#define VME_REMOTE_ZMI_BOARD2_AXIS2    0x1400
#define VME_REMOTE_ZMI_BOARD2_AXIS3    0x1800
#define VME_REMOTE_ZMI_BOARD2_AXIS4    0x1C00

/* VME Node local register (Bus Adapter, BAR1) */
#define VME_NODE_LOCAL_COMMAND          0x00
#define VME_NODE_INTERRUPT_CONTROL      0x01
#define VME_NODE_LOCAL_STATUS           0x02
#define VME_NODE_INTERRUPT_STATUS       0x03
#define VME_NODE_PCI_CONTROL            0x04
#define VME_NODE_LOOPBACK_CONTROL       0x05
#define VME_NODE_MAPPING_RAM_CONTROL    0x06

#define VME_NODE_REMOTE_COMMAND_REG_1           0x08
#define VME_NODE_REMOTE_STATUS_REG              0x08
#define VME_NODE_ADAPTER_ID                     0x0C
#define VME_NODE_REMOVE_VMEBUS_ADDR_MODIFIER    0x0D
#define VME_NODE_REMOTE_IACK_READ_LOW           0x0E
#define VME_NODE_REMOTE_IACK_READ_HIGH          0x0F

/* VME ZMI4104 register */

#define ZMI_VME_STATUS_REGISTER0                0x00
#define ZMI_VME_COMMAND_REGISTER                0x00
#define ZMI_VME_STATUS_REGISTER1                0x02
#define ZMI_VME_SCLK_COMMAND_REGISTER           0x02
#define ZMI_VME_INTERRUPT_ENABLE0               0x04
#define ZMI_VME_INTERRUPT_ENABLE1               0x06
#define ZMI_VME_ERROR_STATUS0                   0x08
#define ZMI_VME_ERROR_CLEAR0                    0x08
#define ZMI_VME_ERROR_STATUS1                   0x0A
#define ZMI_VME_ERROR_CLEAR1                    0x0A
#define ZMI_VME_CONTROL_REGISTER_0              0x10
#define ZMI_VME_CONTROL_REGISTER_1              0x12
#define ZMI_VME_CONTROL_REGISTER_2              0x14
#define ZMI_VME_CONTROL_REGISTER_3              0x16
#define ZMI_VME_CONTROL_REGISTER_4              0x18
#define ZMI_VME_CONTROL_REGISTER_5              0x1A
#define ZMI_VME_CONTROL_REGISTER_15             0x3A
#define ZMI_VME_CONTROL_REGISTER_16             0x3C
#define ZMI_VME_CONTROL_REGISTER_17             0x3E
#define ZMI_VME_ERROR_STATUS2                   0x1E
#define ZMI_VME_USER_VELOCITY_REGISTER          0x32
#define ZMI_VME_SAMPLE_TIMER_REGISTER           0x38
#define ZMI_VME_POSITION_MSB                    0x40
#define ZMI_VME_POSITION_LSB                    0x42
#define ZMI_VME_POSITION_EXT                    0x44
#define ZMI_VME_SAMPLE_POSITION_MSB             0x48
#define ZMI_VME_SAMPLE_POSITION_LSB             0x4A
#define ZMI_VME_SAMPLE_POSITION_EXT             0x4C
#define ZMI_VME_VELOCITY_MSB                    0x50
#define ZMI_VME_VELOCITY_LSB                    0x52
#define ZMI_VME_TIME_MSB                        0x54
#define ZMI_VME_TIME_LSB                        0x56
#define ZMI_VME_OFFSET_LSB_REGISTER             0x6A
#define ZMI_VME_TEST_COMMAND1                   0xA0
#define ZMI_VME_TEST_STATUS1                    0xA0
#define ZMI_VME_INTERRUPT_VECTOR                0xB2
#define ZMI_VME_DIAG_FFT_CONTROL                0xB4
#define ZMI_VME_OPTICAL_POWER_L2                0x192
#define ZMI_VME_SSI_AVG                         0x2A
#define ZMI_VME_CE_CONTROL_REGISTER             0x102
#define ZMI_VME_CE_STATUS_REGISTER              0x100
#define ZMI_VME_CE_C1_CALCULATED                0x118
#define ZMI_VME_CE_C0_CALCULATED                0x120
#define ZMI_VME_CE_CN_CALCULATED                0x130
#define ZMI_VME_DIAG_TEMP_MONITOR_CONTROL_REG	0xA4
#define ZMI_VME_EEPROM_CONTROL_REGISTER         0xAC
#define ZMI_VME_EEPROM_READ                     0xB0
#define ZMI_VME_DIAG_FFT_RAM_DATA               0x400

#define ZMI4000_VME_BIT_WINDOW                  (0x7)       // 3-bits (0..7) "0b111"

#define AXIS234_DETECTION_FILTER                0x3000

#define BITS2MASK(n)                                    ((1<<n)-1)
#define VMIFLOAT_MANT_BITS                                      16
#define VMIFLOAT_EXP_BIAS                                       127
#define VMIFLOAT_SIGN_SHIFT                                     24
#define VMIFLOAT_SIGN_MASK (BITS2MASK(1)<<VMIFLOAT_SIGN_SHIFT)
#define VMIFLOAT_EXP_SHIFT                                      16
#define VMIFLOAT_EXP_MASK (BITS2MASK(8)<<VMIFLOAT_EXP_SHIFT)
#define VMIFLOAT_MANT_SHIFT                                     0
#define VMIFLOAT_MANT_MASK (BITS2MASK(16)<<VMIFLOAT_MANT_SHIFT)
#define VMIFLOAT_MANT_MSB                                       (1<<16)
#define VMICFLOAT_MANT_BITS                                     10
#define VMICFLOAT_EXP_BIAS                                      127
#define VMICFLOAT_EXP_SHIFT                                     24
#define VMICFLOAT_EXP_MASK (BITS2MASK(8)<<VMICFLOAT_EXP_SHIFT)
#define VMICFLOAT_RSIGN_SHIFT                           	23
#define VMICFLOAT_RSIGN_MASK (BITS2MASK(1)<<VMICFLOAT_RSIGN_SHIFT)
#define VMICFLOAT_RMANT_SHIFT                           	12
#define VMICFLOAT_RMANT_MASK (BITS2MASK(11)<<VMICFLOAT_RMANT_SHIFT)
#define VMICFLOAT_ISIGN_SHIFT                           	11
#define VMICFLOAT_ISIGN_MASK (BITS2MASK(1)<<VMICFLOAT_ISIGN_SHIFT)
#define VMICFLOAT_IMANT_SHIFT                           	0
#define VMICFLOAT_IMANT_MASK (BITS2MASK(11)<<VMICFLOAT_IMANT_SHIFT)
#define PI    3.14159265359
#define CEC_LAMBDA (632.99070)	//nm
#define CEC_CYCLIC_FACTOR (CEC_LAMBDA * sqrt(2.0) / (16 * PI))
typedef volatile uint8_T    BAR1TYPE;
typedef volatile uint32_T   ZMI4104TYPE;

/* Functions prototypes **************************************************/
volatile uint8_T zmiRead8(ZMI4104TYPE* ptBaseReg, uint16_T offset);
volatile uint16_T zmiRead16(ZMI4104TYPE* ptBaseReg, uint16_T offset);
volatile uint32_T zmiRead32(ZMI4104TYPE* ptBaseReg, uint16_T offset);
void zmiWrite8(ZMI4104TYPE* ptBaseReg, uint16_T offset, uint8_T data);
void zmiWrite16(ZMI4104TYPE* ptBaseReg, uint16_T offset, uint16_T data);
void zmiWrite32(ZMI4104TYPE* ptBaseReg, uint16_T offset, uint32_T data);

int VmeBusInit(SimStruct *S, BAR1TYPE *nodeio_bar, char msg[]);
uint8_T VmeBusStatus (SimStruct *S, BAR1TYPE *nodeio_bar);
int VmeZmiMapping(int_T id, volatile uint32_T *mappingreg_bar, int_T addr_sw1, int_T addr_sw2);

int VmeZmiReadPosition(ZMI4104TYPE *ptZmiRegs, real_T *ptOutPort_Pos);
void VmeZmiReadPositionComponents(ZMI4104TYPE *ptZmiRegs, uint32_T *lsb, uint16_T *ext);
int VmeZmiReadSamplePosition(ZMI4104TYPE *ptZmiRegs, real_T *ptOutPort_SamPos);
int VmeZmiReadVelocity(ZMI4104TYPE *ptZmiRegs, real_T *ptOutPort_Vel);
int VmeZmiReadTime(ZMI4104TYPE *ptZmiRegs, real_T *ptOutPort_Time);

int VmeZmiSetFilter(ZMI4104TYPE *ptZmiRegs, int8_T kp_id, int8_T kv_id);

int VmeZmiEepromRead(ZMI4104TYPE *ptZmiRegs, uint8_T offset);

int VmeZmiWaitingAxis(SimStruct *S, ZMI4104TYPE *ptZmiRegs, uint8_T ax_n,  char msg[]);
int VmeZmiReset(ZMI4104TYPE *ptZmiRegs);

int VmeZmiAxisInit(ZMI4104TYPE* ptZmiRegs, int axis);
int VmeZmiAxisInit_intTriggerModeForceExtSample(ZMI4104TYPE* ptZmiRegs, int axis);

real_T GetRealValue(uint32_T ext, uint32_T msb);

int VmeZmiReadCyclicErrorCNReal(ZMI4104TYPE *ptZmiRegs, real_T *ptValue);
int VmeZmiReadCyclicErrorCNImaginary(ZMI4104TYPE *ptZmiRegs, real_T *ptValue);
int VmeZmiReadCyclicErrorC1Real(ZMI4104TYPE *ptZmiRegs, real_T *ptValue);
int VmeZmiReadCyclicErrorC0Real(ZMI4104TYPE *ptZmiRegs, real_T *ptValue);
int VmeZmiReadCyclicErrorC0Imaginary(ZMI4104TYPE *ptZmiRegs, real_T *ptValue);
#endif

#endif
