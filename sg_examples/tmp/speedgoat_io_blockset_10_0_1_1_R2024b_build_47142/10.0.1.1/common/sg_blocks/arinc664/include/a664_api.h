/**
* @file a664_api.h
* @brief Time-Triggered Ethernet and ARINC 664 End System Application Programmer's Interface
*
*  Created on: 12/15/2010
*   
*	- $HeadURL: http://ait-subversion/svn/Ethernet_ES/Development_ES/HostSW/branches/VxWorks7_664_v5.3.11/a664_api/include/a664_api.h $
*	- $Date: 2014-12-10 14:58:56 -0600 (Wed, 10 Dec 2014) $
*	- $Revision: 6678 $
*	- $Author: motttj $
*
* Copyright (c) 2010 by Avionics Interface Technologies
*  - Omaha, NE USA
*  - Beavercreek, OH USA
*  .
* All rights reserved.  No part of this software may
* be published, distributed, translated or otherwise
* reproduced by any means or for any purpose without
* the prior written consent of Avionics Interface Technologies. 
*/
#ifndef A664_API_H
#define A664_API_H
#include "a664_cdef.h"
#include "a664_error_def.h"

/** 
* @brief The Interface Version for this API
**/
#define A664_API_IO_VERSION 0x00000001

/**
*  @brief  Global variable to store the number of end systems.
**/
extern uint32_t  gNumEndSystems;

/**
* \defgroup a664ApiAdmin A664 API Administration Functions
* @{
*
* @section sec_oview Overview
* <p>
* This section contains the A664 Library Adminstration Functions that
* are used by the application program to Initialize the A664 API and
* to obtain Status and Version information about the API library
* </p>
*
*/

/**
* Gets error detail given an error code returned from the API.
* @param[in] aErrorCode The error code.
* @returns The associated error string.
* @note Do not hold on to the returned pointer, as it may be invalidated by further api or api-related calls.
*/
_A664_EXTERN const char* _A664_DLL_FUNC a664GetErrorString(A664Return aErrorCode);
/**
* @brief Initializes the Application Interface and returns the number of 
*  End System Devices found.
* This must be the first function called in the application program.
* @param[in] aStructureIoVersion This input is required to be the value of 
*  A664_API_IO_VERSION. This defines how the internal library will interpret 
*  input and output structures to the exported interface functions. Each time
*  an input or output structure is changed, the definition will be incremented
*  and the library will be able to interpret previously compiled applications
*  correctly, without recompiling.
* @param[out] aNumEndSystems The number of compatible End System devices found 
*  in the system.
* @return @link error Error Code @endlink
*/
A664_API_FUNC a664Init(const uint32_t aStructureIoVersion, uint32_t* aNumEndSystems);

/** 
* @brief Software version number where the format is Major.Minor.Maintenance.Revision
**/
typedef struct 
{
	/**
	* @brief Major Version for Version Format Major.Minor.Maintenance.Revision
	*/
	uint32_t mVersionMajor;
	/**
	* @brief Minor Version for Version Format Major.Minor.Maintenance.Revision
	*/
	uint32_t mVersionMinor;
	/**
	* @brief Maintenance Version for Version Format Major.Minor.Maintenance.Revision
	*/
	uint32_t mVersionMaintenance;
	/**
	* @brief Revision for Version Format Major.Minor.Maintenance.Revision
	*/
	uint32_t mVersionRevision;
} A664Version;

/**
* @brief Returns the Version of the A664 API and Kernel Module Driver.
* @param[out] aApiVersion The version of the API Library
* @param[out] aDriverVersion The version of the device driver
* @return @link error Error Code @endlink
*/
A664_API_FUNC a664GetApiVersions(A664Version* aApiVersion, A664Version* aDriverVersion);

/** 
* @brief Closes the API and releases resources
**/
A664_API_FUNC a664Close(void);

/**@}	(end defgroup a664ApiAdmin)	*/

/**
* \defgroup a664ApiEs A664 API End System Functions
* @{
*
* @section sec_oview Overview
* <p>
* This section contains the A664 Library functions that
* are used by the application program to operate on End System
* devices
* </p>
*
*/

/**
* @brief Gets the number of End System Devices available in the system
* @param[out] aNumEndSystems The number of End System Devices available for use in the system
* @return @link error Error Code @endlink
**/
A664_API_FUNC a664ESGetCount(uint32_t* aNumEndSystems);

/** 
* @brief Device Identification Structure
**/
typedef struct
{
	/** 
	* @brief Vendor ID
	**/
	uint16_t vid;
	/** 
	* @brief Device ID
	**/
	uint16_t did;
	/** 
	* Device name
	**/
	char name[64];
} A664DeviceIdent;

/** 
* @brief Status and Version Information for the End System
**/
typedef struct 
{
	/** 
	* @brief Unique Identifier for the End System Device (ES Hardware Serial Number)
	**/
	uint32_t aESId;
	/** 
	* @brief The part number identifying the end system
	**/
	uint32_t aESPartNumber;
	/**
	* @brief The number of Ethernet interfaces available at the End System
	**/
	uint32_t aNumNetworkInterfaces;
	/** 
	* @brief sNIC Version Information
	**/
	A664Version    sNicVersion;
	/** 
	* @brief Tx NIOS Software Version
	**/
	A664Version    txNIOSVersion;
	/** 
	* @brief Rx NIOS Software Version
	**/
	A664Version    rxNIOSVersion;
	/** 
	* @brief Tx Boot NIOS Software Version
	**/
	A664Version    txBootNIOSVersion;
	/** 
	* @brief Rx Boot NIOS Software Version
	**/
	A664Version    rxBootNIOSVersion;
	/**
	* @brief Hardware Device Identification
	**/
	A664DeviceIdent deviceIdent;
} A664EndSystemInfo;

/**
* @brief Returns information about an End System
* @param[in] aESIndex The index of the End System Device
* @param[out] aEndSystemInfo A block of information about the End System device
* @return @link error Error Code @endlink
**/
A664_API_FUNC a664ESGetInfo(const uint32_t aESIndex, A664EndSystemInfo* aEndSystemInfo);

/**
* @brief The End System's Handle
**/
typedef struct a664EndSystemHandle
{
	void* handle;
} A664EndSystemHandle;

/**
* @brief Returns information about an End System given an End System handle.
* @param[in] aEndSystemHandle The End System handle.
* @param[out] aEndSystemInfo The retrieved information for the End System device.
* @return @link error Error Code @endlink
**/
A664_API_FUNC a664ESGetInfoViaHandle(const A664EndSystemHandle aEndSystemHandle, A664EndSystemInfo* aEndSystemInfo);

/**
* @brief Phy status
**/
typedef struct a664PhyStatus
{
	/**
	* @brief Boolean link status for channel 0.
	**/
	uint32_t linkStatusCh0;
	/**
	* @brief Configured speed for channel 0 (b'10 for 1 Gbit/s, b'01 for 100 Mbit/s, b'00 otherwise, b'11 for Fiber SFPs).
	**/
	uint32_t speedCh0;
	/**
	* @brief Boolean link status for channel 1.
	**/
	uint32_t linkStatusCh1;
	/**
	* @brief Configured speed for channel 1 (b'10 for 1 Gbit/s, b'01 for 100 Mbit/s, b'00 otherwise, b'11 for Fiber SFPs).
	**/
	uint32_t speedCh1;
} A664PhyStatus;

/**
* @brief Returns information about PHY status given an End System handle.
*  This call will return A664_API_ERROR_SFP_COMM for unplugged SFPs and will return A664_API_ERROR_INVALID_SFP for fiber SFPs.
* @param[in] aEndSystemHandle The End System handle.
* @param[out] aPhyStatus The returned PHY status for End System.
* @return @link error Error Code @endlink
**/
A664_API_FUNC a664ESGetPhyStatus(const A664EndSystemHandle aEndSystemHandle, A664PhyStatus* aPhyStatus);

/**
* @brief Enum defining the type of SFP
**/
typedef enum
{
    /**
    * @brief Unknown SFP
    **/
    A664_SFP_UNKNOWN = 0,
    /**
    * @brief Copper SFP
    **/
    A664_SFP_COPPER = 1,
    /**
    * @brief Single Mode Fiber SFP
    **/
    A664_SFP_SINGLE_MODE_FIBER = 2,
    /**
    * @brief Multi Mode Fiber SFP
    **/
    A664_SFP_MULTI_MODE_FIBER = 3,
} A664SfpType;

/**
* @brief SFP Info
**/
typedef struct a664SfpInfo
{
    /**
    * @brief The Vendor Name for the PHY or SFP(ascii).
    **/
    char mVenName[20];
    /**
    * @brief The Vendor Part Number for the SFP(ascii).
    **/
    char mVenPartNum[20];
    /**
    * @brief The Vendor Revision for the SFP(ascii).
    **/
    char mVenRev[8];
    /**
    * @brief The SFP Type.
    **/
    A664SfpType mSfpType;
    /**
    * @brief The Maximum Signaling Rate(MBd).
    **/
    uint32_t mSignalRate;
    /**
    * @brief The supported Link Length(meters).
    **/
    uint32_t mLinkLength;
    /**
    * @brief The optical wavelength(nm).  Invalid for copper SFP.
    **/
    uint32_t mWavelength;
    /**
    * @brief The internally measured module temperature (1/256 degrees C) -128C to 128C.  Invalid for copper SFP.
    **/
    int16_t mIntTemp;
    /**
    * @brief The Measured TX Output Power(0.0001 mW) 0-6.5535 mW.  Invalid for copper SFP.
    **/
    uint16_t mTxOutPwr;
    /**
    * @brief The Measured RX Input Power(0.0001 mW) 0-6.5535 mW.  Invalid for copper SFP.
    **/
    uint16_t mRxInPwr;
    /**
    * @brief The RX_LOS signal.  Invalid for copper SFP.
    **/
    uint16_t mRxLos;
} A664SfpInfo;

/**
* @brief Returns information about the SFP given an End System handle.
*  This call will return A664_API_ERROR_SFP_COMM for unplugged SFPs.
* @param[in] aEndSystemHandle The End System handle.
* @param[in] aSfpIndex The 0 based index for the SFP.
* @param[out] aSfpInfo The returned SFP Info.
* @return @link error Error Code @endlink
**/
A664_API_FUNC a664ESGetSfpInfo(const A664EndSystemHandle aEndSystemHandle, uint32_t aSfpIndex, A664SfpInfo* aSfpInfo);

/**
* @brief Runs a self test on the end system, this will test for communication with the TXuP and RXuP, the SFPs and the RAM.
* @param[in] aEndSystemHandle The End System handle.
* @param[in] aFullTest Set to '1' to run the full RAM test, this will take a couple minutes.  
*   Set to '0' to perform a partial RAM test.
* @return @link error Error Code @endlink
**/
A664_API_FUNC a664ESSelfTest(const A664EndSystemHandle aEndSystemHandle, uint8_t aFullTest);

/** 
* @brief Enumeration of possible Network Interfaces at the End System
**/
typedef enum
{
	/** 
	* @brief No Network Interface
	**/
	A664_NET_NONE = 0,
	/** 
	* @brief Network A Interface
	**/
	A664_NET_A = 1,
	/** 
	* @brief Network B Interface
	**/
	A664_NET_B = 2,
	/** 
	* @brief Both Network Interface
	**/
	A664_NET_BOTH = 3,
} A664NetworkInterfaceBits;

/**
*  @brief  The types of the sNIC status registers.
**/
typedef enum
{
	LEDS_OFF  =  0,
	LEDS_ON  =  1,
	LEDS_FLASH  =  2, 
} A664LedPatternType;

/**
* @brief Overrides the LED Control to run a pattern for board identification.  This is only valid for V2 and DCE hardware
* @param[in] aEndSystemHandle The End System handle.
* @param[in] aNetwork Specifies the network interface.
* @param[in] aSecLength The number of seconds to run the LED pattern.
* @param[in] aLedPattern Specifies the LED pattern to use.
* @return @link error Error Code @endlink
**/
A664_API_FUNC a664ESIdentify(const A664EndSystemHandle aEndSystemHandle, A664NetworkInterfaceBits aNetwork, uint8_t aSecLength, A664LedPatternType aLedPattern);

/**
* @brief Checks if a board is PXIe.
* @param[in] aEndSystemHandle The End System handle.
* @param[out] apIsPxie Returns 1 if the board is PXIe, 0 otherwise.
* @return @link error Error Code @endlink
**/
A664_API_FUNC a664ESIsPxie(const A664EndSystemHandle aEndSystemHandle, uint8_t* apIsPxie);

/**
*  @brief  Describes the trigger polarity
**/
typedef enum
{
	A664_TRIG_ACTIVE_HIGH  =  0,
	A664_TRIG_ACTIVE_LOW  =  1,
} A664TrigPolarity;

/**
*  @brief  Defines the trigger as input ot output
**/
typedef enum
{
	A664_TRIG_INPUT  =  0,
	A664_TRIG_OUTPUT  =  1,
} A664TrigOutputCtl;

/**
* @brief PXIe front panel and backplane Trigger Configuration
**/
typedef struct a664TrigConfig
{
	/**
	* @brief Set to '1' to enable the trigger and '0' to disable the trigger.
	**/
	uint32_t mTrigEn;
	/**
	* @brief Trigger Polarity active high or active low.
	**/
	A664TrigPolarity mTrigPol;
	/**
	* @brief Defines the trigger as an input or an output.
	**/
	A664TrigOutputCtl mTrigOutCtl;
	/**
	* @brief Number of clocks to assert any output trigger for – count of 100 MHz clocks. Valid for an output trigger.
	**/
	uint32_t mTrigOutpTime;
	/**
	* @brief Number of clocks an input is asserted for before being considered a valid trigger event – count of 100 MHz clocks. Valid for an input trigger
	**/
	uint32_t mTrigInpTime;
	/**
	* @brief This register controls how events are routed. For PXIe backplane output configuration values 0-4 indicate the front panel input trigger.  For front panel output configuration values 0-7 indicate the PXIe trigger and values 8-9 indicate the star triggers.
	**/
	uint32_t mTrigEventRouting;
} A664TrigConfig;

/**
* @brief Configures a PXIe backplane trigger, this will only work on A664 V2 hardware and DCE hardware if a PXIe carrier is present.
* @param[in] aEndSystemHandle The End System handle.
* @param[in] aTrigIndex Specifies the backplane trigger index 0-7 to configure.
* @param[in] apTrigConfig a pointer to the structure defining the trigger configuration.
* @return @link error Error Code @endlink
**/
A664_API_FUNC a664ESSetPxieBpTrig(const A664EndSystemHandle aEndSystemHandle, uint8_t aTrgIndex, A664TrigConfig* apTrigConfig);

/**
* @brief Configures a PXIe front panel trigger, this will only work on A664 V2 hardware and DCE hardware if a PXIe carrier is present.
* @param[in] aEndSystemHandle The End System handle.
* @param[in] aTrigIndex Specifies the front panel trigger index 0-4 to configure.
* @param[in] apTrigConfig a pointer to the structure defining the trigger configuration.
* @return @link error Error Code @endlink
**/
A664_API_FUNC a664ESSetPxieFpTrig(const A664EndSystemHandle aEndSystemHandle, uint8_t aTrgIndex, A664TrigConfig* apTrigConfig);

/**
*  @brief  The types of the sNIC status registers.
**/
typedef enum
{
	A_STATE_G  =  1,
	A_STATE_P  =  2,
	A_STATE_C  =  3, 
} A664SnicStatusType;

/**
*  @brief  The number of 32-bit longwords comprising the A_STATE_G sNIC register.
**/
#define  A_STATE_G_SIZE  (14)
/**
*  @brief  The number of 32-bit longwords comprising the A_STATE_P sNIC register.
**/
#define  A_STATE_P_SIZE  ( 8)
/**
*  @brief  The number of 32-bit longwords comprising the A_STATE_C sNIC register.
**/
#define  A_STATE_C_SIZE  (19)

/**
*  @brief  An sNIC status register, an array of 32-bit words.
**/
typedef uint32_t A664SnicStatusRegister[20];

/**
*  @brief  Get a status register (as an array of 32-bit integers).  This function is not available for V2 or DCE boards.
*  @param[in] aEndSystemHandle A handle of an end system.
*  @param[in] snicStatusType The type of status register that is to be read from the sNIC.
*  @param[out] snicStatusRegister The sNIC status register, as an array of unsigned, 32-bit integers.
*  @return @link error Error Code @endlink 
**/
A664_API_FUNC a664GetSnicStatus(const A664EndSystemHandle aEndSystemHandle, const A664SnicStatusType snicStatusType,
                                A664SnicStatusRegister snicStatusRegister);

/** 
* @brief Open an End System and get an End System Handle to use for subsequent operations on the End System. The End System will be reset.
* @param[in] aESIndex The index of the End System Device
* @param[out] aEndSystemHandle A handle for the End System. To be used as input to API functions executing operations on the End System
* @return @link error Error Code @endlink 
**/
A664_API_FUNC a664ESOpen(const uint32_t aESIndex, A664EndSystemHandle* aEndSystemHandle);

/** 
* @brief Open an End System with the VISA Device Name and get an End System Handle to use for subsequent operations on the End System. The End System will be reset.  This function is only available when using VISA drivers.
* @param[in] aVisaDeviceName A pointer to the VISA Device Name of the End System, for example: "PXI5::12::INSTR"
* @param[out] aEndSystemHandle A handle for the End System. To be used as input to API functions executing operations on the End System
* @return @link error Error Code @endlink 
**/
A664_API_FUNC a664ESOpenVisaName(const char* aVisaDeviceName, A664EndSystemHandle* aEndSystemHandle);

/**
* @brief Close an End System and release the End System Handle
* @param[in] aEndSystemHandle The handle for the End System Device.
* @return @link error Error Code @endlink 
**/
A664_API_FUNC a664ESClose(const A664EndSystemHandle aEndSystemHandle);

/** 
* @brief Enumeration of possible Network Interfaces at the End System
**/
typedef enum
{
	/** 
	* @brief Base Address Register 0
	**/
	A664_BAR_0 = 0,
	/** 
	* @brief Base Address Register 1
	**/
	A664_BAR_1 = 1,
	/** 
	* @brief Base Address Register 2
	**/
	A664_BAR_2 = 2,
	/** 
	* @brief Base Address Register 3
	**/
	A664_BAR_3 = 3,
} A664Bar;

/**
* @brief Read data dWords directly from the End System
* @param[in] aEndSystemHandle The handle for the End System Device.
* @param[in] aBar The Base Address Register to read from.
* @param[in] aByteOffset The byte offset into the bar to start reading at.
* @param[in] aLength The number of dWords to read.
* @param[out] aData32 A pointer to the memory to write the data to.
* @return @link error Error Code @endlink 
**/
A664_API_FUNC a664ESRead32(A664EndSystemHandle aEndSystemHandle, A664Bar aBar, uint32_t aByteOffset, uint32_t aLength, uint32_t* aData32);

/**
* @brief Write data dWords directly to the End System
* @param[in] aEndSystemHandle The handle for the End System Device.
* @param[in] aBar The Base Address Register to write to.
* @param[in] aByteOffset The byte offset into the bar to start writing at.
* @param[in] aLength The number of dWords to write.
* @param[out] aData32 A pointer to the memory holding the data to be written.
* @return @link error Error Code @endlink 
**/
A664_API_FUNC a664ESWrite32(A664EndSystemHandle aEndSystemHandle, A664Bar aBar, uint32_t aByteOffset, uint32_t aLength, uint32_t* aData32);

/**
* @brief Reset an End System 
* @param[in] aEndSystemHandle The handle for the End System Device.
* @return @link error Error Code @endlink 
**/
A664_API_FUNC a664ESReset(const A664EndSystemHandle aEndSystemHandle);

/** 
* @brief End System Configuration Information
**/
typedef struct  
{
	/** 
	* @brief Pointer to the binary device specific Intel Hex formatted configuration Data for the sNIC 
	**/
	void* aSnicConf;
	/** 
	* @brief Pointer to the binary device specific Intel Hex formatted configuration data for the upper layer protocols (Tx)
	**/
	void* aTxUlpConf;
	/** 
	* @brief Pointer to the binary device specific Intel Hex formatted configuration data for the upper layer protocols (Rx)
	**/
	void* aRxUlpConf;
} A664Configuration;

/** 
* @brief Configure an End System using a TTE-Tools compiled device-specific configuration.
* @param[in] aEndSystemHandle The handle for the End System Device.
* @param[in] aEndSystemConfiguration Device-specific binary configuration data produced by TTE-Tools.
* @return @link error Error Code @endlink 
**/
A664_API_FUNC a664ESConfigure(const A664EndSystemHandle aEndSystemHandle, const A664Configuration* aEndSystemConfiguration);

/** 
* @brief Configure an End System using three Intel HEX configuration files.
* @param[in] aEndSystemHandle The handle for the End System Device.
* @param[in] aSnicConfig sNIC configuration filepath
* @param[in] aTxConfig   Tx configuration filepath
* @param[in] anRxConfig  Rx configuration filepath
* @return @link error Error Code @endlink 
**/
A664_API_FUNC a664ESConfigureFromHexPaths(const A664EndSystemHandle aEndSystemHandle, const char* aSnicConfig ,
                                          const char* aTxConfig, const char* anRxConfig);

/** 
* @brief Configure an End System using a AIT-Tools compiled device-specific configuration.
* @param[in] aEndSystemHandle The handle for the End System Device.
* @param[in] aEndSystemConfiguration Pointer to the device-specific binary configuration data produced by AIT-Tools.
* @return @link error Error Code @endlink 
**/
A664_API_FUNC a664ESConfigureEx(const A664EndSystemHandle aEndSystemHandle, const void* aEndSystemConfiguration);

/** 
* @brief Enumeration of link speed
**/
typedef enum
{
	/** 
	* @brief 10 Mbps
	**/
	A664_10_MBPS = 0,
	/** 
	* @brief 100 Mbps
	**/
	A664_100_MBPS = 1,
	/** 
	* @brief 1000 Mbps
	**/
	A664_1000_MBPS = 2,
	/** 
	* @brief 1000 Mbps
	**/
	A664_AUTONEGOTIATE = 3,
} A664LinkSpeed;

/** 
* @brief Configures a Dual Channel Ethernet board link speed settings, this must be called after the board is opened.  
*   This function will also work for A664-V2 hardware and must be called after configuration.
* @param[in] aEndSystemHandle The handle for the End System Device.
* @param[in] aSpeedCh0 The link speed to be set for channel 0.
* @param[in] aSpeedCh1 The link speed to be set for channel 1.
* @return @link error Error Code @endlink 
**/
A664_API_FUNC a664ESConfigureDce(const A664EndSystemHandle aEndSystemHandle, A664LinkSpeed aSpeedCh0, A664LinkSpeed aSpeedCh1);

/** 
* @brief Timestamp in DAY::HOUR::MIN::SEC::NANOSEC format
**/
typedef struct _A664Timestamp
{
	/** 
	* @brief The number of days
	**/
	uint32_t	mDay;
	/** 
	* @brief The number of hours
	**/
	uint32_t	mHour;
	/** 
	* @brief The number of minutes
	**/
	uint32_t	mMinute;
	/** 
	* @brief The number of seconds
	**/
	uint32_t	mSecond;
	/** 
	* @brief The number of nanoseconds
	**/
	uint32_t	mNanosecond;
}A664Timestamp;

/** 
* @brief Sets the time stamping clock for the end system.  For PXIe devices this function does not
* wait for the timestamp to propogate through the board.  It may take up to 4 seconds for the time 
* to propogate through a PXIe board.
* @param[in] aEndSystemHandle The handle for the End System Device.
* @param[in] aTime The time to set to the end system time stamping clock.
* @return @link error Error Code @endlink 
**/
A664_API_FUNC a664ESSetTime(const A664EndSystemHandle aEndSystemHandle, const A664Timestamp* apTime);

/** 
* @brief Gets the current time from the end system time stamping clock.
* @param[in] aEndSystemHandle The handle for the End System Device.
* @param[out] aTime The current time from the timestamping clock.
* @return @link error Error Code @endlink 
**/
A664_API_FUNC a664ESGetTime(const A664EndSystemHandle aEndSystemHandle, A664Timestamp* apTime);

/** 
* @brief Sets IRIG to external or internal.  Use a664ESSetIrig for PXIe compatibility.
* @param[in] aEndSystemHandle The handle for the End System Device.
* @param[in] aSetExt Use 0x01 to set IRIG to external, 0x00 to set to internal.
* @return @link error Error Code @endlink 
**/
A664_API_FUNC a664ESSetIrigExt(const A664EndSystemHandle aEndSystemHandle, const uint8_t aSetExt);

/** 
* @brief Enumeration of link speed
**/
typedef enum
{
	/** 
	* @brief Sets the clock to use onboard clock
	**/
	A664_IRIG_INTERNAL = 0,
	/** 
	* @brief Sets the clock to use IRIG through the front panel connector
	**/
	A664_IRIG_EXTERNAL = 1,
	/** 
	* @brief Sets the clock to use the PXIe backplane clock and polarity 0
	**/
	A664_IRIG_INTRACHASSIS_P0 = 2,
	/** 
	* @brief Sets the clock to use the PXIe backplane clock and polarity 1
	**/
	A664_IRIG_INTRACHASSIS_P1 = 3,
} A664Irig;

/** 
* @brief Sets IRIG to external or internal.
* @param[in] aEndSystemHandle The handle for the End System Device.
* @param[in] aSetIrig Use 0x01 to set IRIG to external, 0x00 to set to internal.
* @return @link error Error Code @endlink 
**/
A664_API_FUNC a664ESSetIrig(const A664EndSystemHandle aEndSystemHandle, A664Irig aSetIrig);

/** 
* @brief Gets the time of the last External Event.  The Event Timestamp will be cleared during a664ESReset() and a664ESSetTime().
* @param[in] aEndSystemHandle The handle for the End System Device.
* @param[out] aTime The time of the last occurance of the External Event.
* @param[out] aNewEvent, returns TRUE if this is the first time the event timestamp was returned for the event.
* @return @link error Error Code @endlink 
**/
A664_API_FUNC a664ESGetExternalEventTime(const A664EndSystemHandle aEndSystemHandle, A664Timestamp* aTime, uint32_t* aNewEvent);

/** 
* @brief MAC Interface Status Information
**/
typedef struct  
{
	/** 
	* @brief Indicates if the MAC Interface is enabled (TRUE) or not (FALSE)
	**/
	int      mInterfaceEnabled;
	/** 
	* @brief The number of bytes (including preamble and SOF delimiters)
	*        received at the MAC port
	**/
	uint32_t  mRxBytes;
	/** 
	* @brief The number of bytes (including preamble and SOF delimiters)
	*        transmitted at the MAC port
	**/
	uint32_t  mTxBytes;
	/** 
	* @brief The number of frames with MII Errors
	**/
	uint32_t  mMIIErrors;
	/** 
	* @brief The number of frames received with CRC Errors
	**/
	uint32_t  mCRCErrors;
	/** 
	* @brief The number of frames received with Allignment Errors
	**/
	uint32_t  mAlignmentErrors;
	/** 
	* @brief The number of frames received with Start of Frame Delimiter Errors
	**/
	uint32_t  mSOFErrors;
	/** 
	* @brief The number of frames received that are larger than 1518 bytes or less than 64 bytes
	**/
	uint32_t  mSizeErrors;
} A664MacStatus;

/** 
* @brief Enumeration of possible Network Interfaces at the End System
**/
typedef enum
{
	/** 
	* @brief Network A Interface
	**/
	A664_NETWORK_A  =  0,
	/** 
	* @brief Network B Interface
	**/
	A664_NETWORK_B  =  1,
} A664NetworkInterface;

/** 
*  @brief  Gets status information for the MAC Protocol Layer.
*          The counters returned via aMacStatus are re-set to zero
*          with each invocation of this function, and
*          at both power-on and board re-set.
*          This function is only available for V1 hardware.
*  @param[in]   aEndSystemHandle  A handle to an End System.
*  @param[in]   aNetwork          A Network Interface (A or B).
*  @param[out]  aMacStatus        A structure containing MAC Layer Status information.
*  @return @link error Error Code@endlink
**/
A664_API_FUNC a664ESGetMacStatus(const A664EndSystemHandle aEndSystemHandle, const A664NetworkInterface aNetwork,
								  A664MacStatus* aMacStatus);

/** 
*  @brief MAC Interface Control Settings
**/
typedef struct
{
	/** 
	*  @brief  Enables (true) or Disables (false) the Mac Interface
	**/
	uint32_t  mInterfaceEnabled;
} A664MacControl;
/**
*  @brief  Sets the control settings for a MAC interface (Net A or Net B) of the End System.  For V2 and DCE hardware this will set the SFP power down, it will take a couple seconds to power up and establish a link.
*  @param[in]   aEndSystemHandle  A handle to an End System.
*  @param[in]   aNetwork          A Network Interface (A or B).
*  @param[in]   aMacControl       The structure containing the MAC Interface Control settings
*  @return @link error Error Code@endlink
**/
A664_API_FUNC a664ESSetMacControl(const A664EndSystemHandle  aEndSystemHandle,
								  const A664NetworkInterface aNetwork,
								  A664MacControl* aMacControl);

/** 
* @brief MAC Counters for the V2 board
**/
typedef struct  
{
	/** 
	* @brief A count of bytes of frames received (destination address to 
	* frame check sequence inclusive). 
	**/
	uint64_t mRxBytes;
	/** 
	* @brief A count of bytes of frames transmitted (destination address 
	* to frame check sequence inclusive). 
	**/
	uint64_t mTxBytes;
	/** 
	* @brief A count of the number of frames received that were fewer 
	* than 64 bytes in length but otherwise well formed. 
	**/
	uint64_t mRxUndersizeFrames;
	/** 
	* @brief A count of the number of frames received that were fewer 
	* than 64 bytes in length and had a bad frame check sequence 
	* field. 
	**/
	uint64_t mRxFragmentFrames;
	/** 
	* @brief A count of error-free frames received 64 bytes in length. 
	**/
	uint64_t mRx64ByteFrames;
	/** 
	* @brief A count of error-free frames received between 65 and 127 
	* bytes in length. 
	**/
	uint64_t mRx65_127ByteFrames;
	/** 
	* @brief A count of error-free frames received between 128 and 255 
	* bytes in length. 
	**/
	uint64_t mRx128_255ByteFrames;
	/** 
	* @brief A count of error-free frames received between 256 and 511 
	* bytes in length. 
	**/
	uint64_t mRx256_511ByteFrames;
	/** 
	* @brief A count of error-free frames received between 512 and 1023 
	* bytes in length. 
	**/
	uint64_t mRx512_1023ByteFrames;
	/** 
	* @brief A count of error-free frames received between 1024 bytes and 
	* the specified IEEE Std 802.3-2008 maximum legal length. 
	**/
	uint64_t mRx1024_MaxByteFrames;
	/** 
	* @brief A count of otherwise error-free frames received that 
	* exceeded the maximum legal frame length specified in IEEE 
	* Std 802.3-2008.
	**/
	uint64_t mRxOversizeFrames;
	/** 
	* @brief A count of error-free frames transmitted that were 64 bytes in 
	* length. 
	**/
	uint64_t mTx64ByteFrames;
	/** 
	* @brief A count of error-free frames transmitted between 65 and 127 
	* bytes in length. 
	**/
	uint64_t mTx65_127ByteFrames;
	/** 
	* @brief A count of error-free frames transmitted between 128 and 
	* 255 bytes in length. 
	**/
	uint64_t mTx128_255ByteFrames;
	/** 
	* @brief A count of error-free frames transmitted between 256 and 511 
	* bytes in length. 
	**/
	uint64_t mTx256_511ByteFrames;
	/** 
	* @brief A count of error-free frames transmitted that were between 
	* 512 and 1023 bytes in length. 
	**/
	uint64_t mTx512_1023ByteFrames;
	/** 
	* @brief A count of error-free frames transmitted between 1024 and 
	* the specified IEEE Std 802.3-2008 maximum legal length. 
	**/
	uint64_t mTx1024_MaxByteFrames;
	/** 
	* @brief A count of otherwise error-free frames transmitted that 
	* exceeded the maximum legal frame length specified in IEEE 
	* Std 802.3-2008.
	**/
	uint64_t mTxOversizeFrames;
	/** 
	* @brief A count of error-free frames received. 
	**/
	uint64_t mRxGoodFrames;
	/** 
	* @brief A count of received frames that failed the CRC check and 
	* were at least 64 bytes in length. 
	**/
	uint64_t mRxFrameCheckSequenceErrors;
	/** 
	* @brief A count of frames successfully received and directed to the 
	* broadcast group address. 
	**/
	uint64_t mRxGoodBroadcastFrames;
	/** 
	* @brief A count of frames successfully received and directed to a 
	* non-broadcast group address. 
	**/
	uint64_t mRxGoodMulticastFrames;
	/** 
	* @brief A count of error-free frames received that contained the 
	* special control frame identifier in the length/type field. 
	**/
	uint64_t mRxGoodControlFrames;
	/** 
	* @brief A count of frames received that were at least 64 bytes in 
	* length where the length/type field contained a length value 
	* that did not match the number of MAC client data bytes 
	* received. The counter also increments for frames in which 
	* the length/type field indicated that the frame contained 
	* padding but where the number of MAC client data bytes 
	* received was greater than 64 bytes (minimum frame size). 
	* The exception is when the Length/Type Error Checks are 
	* disabled in the chosen MAC, in which case this counter does 
	* not increment.
	**/
	uint64_t mRxLengthTypeOutOfRange;
	/** 
	* @brief A count of error-free VLAN frames received. This counter 
	* only increments when the receiver is configured for VLAN 
	* operation.
	**/
	uint64_t mRxGoodVlanTaggedFrames;
	/** 
	* @brief A count of error-free frames received that contained the 
	* MAC Control type identifier 88-08 in the length/type field, 
	* contained a destination address that matched either the 
	* MAC Control multicast address or the configured source 
	* address of the MAC, contained the PAUSE opcode and were 
	* acted upon by the MAC. 
	**/
	uint64_t mRxGoodPauseFrames;
	/** 
	* @brief A count of error-free frames received that contained the 
	* MAC Control type identifier 88-08 in the Length/Type field 
	* but were received with an opcode other than the PAUSE 
	* opcode. 
	**/
	uint64_t mRxBadOpcode;
	/** 
	* @brief A count of error-free frames transmitted. 
	**/
	uint64_t mTxGoodFrames;
	/** 
	* @brief A count of error-free frames that were transmitted to the 
	* broadcast address. 
	**/
	uint64_t mTxGoodBroadcastFrames;
	/** 
	* @brief A count of error-free frames that were transmitted to a group 
	* destination address other than broadcast. 
	**/
	uint64_t mTxGoodMulticastFrames;
	/** 
	* @brief A count of frames that would otherwise be transmitted by 
	* the core but could not be completed due to the assertion of 
	* TX_UNDERRUN during the frame transmission. 
	**/
	uint64_t mTxGoodUnderrunErrors;
	/** 
	* @brief A count of error-free frames transmitted that contained the 
	* MAC Control Frame type identifier 88-08 in the length/type 
	* field. 
	**/
	uint64_t mTxGoodControlFrames;
	/** 
	* @brief A count of error-free VLAN frames transmitted. This counter 
	* only increments when the transmitter is configured for 
	* VLAN operation. 
	**/
	uint64_t mTxGoodVlanTaggedFrames;
	/** 
	* @brief A count of error-free PAUSE frames generated and 
	* transmitted by the MAC in response to an assertion of 
	* pause_req. 
	**/
	uint64_t mTXGoodPauseFrames;
	/** 
	* @brief A count of frames involved in a single collision but 
	* subsequently transmitted successfully (half-duplex mode 
	* only). 
	**/
	uint64_t mTxSingleCollisionFrames;
	/** 
	* @brief A count of frames involved in more than one collision but 
	* subsequently transmitted successfully (half-duplex mode 
	* only). 
	**/
	uint64_t mTxMultipleCollisionFrames;
	/** 
	* @brief A count of frames whose transmission was delayed on its 
	* first attempt because the medium was busy (half-duplex 
	* mode only). 
	**/
	uint64_t mTxDeferred;
	/** 
	* @brief A count of the times that a collision has been detected later 
	* than one slot Time from the start of the packet transmission. 
	* A late collision is counted twice — both as a collision and as 
	* a late Collision (half-duplex mode only). 
	**/
	uint64_t mTxLateCollisions;
	/** 
	* @brief A count of the frames that, due to excessive collisions, are not 
	* transmitted successfully (half-duplex mode only). 
	**/
	uint64_t mTxExcessCollisions;
	/** 
	* @brief A count of frames that deferred transmission for an excessive 
	* period of time (half-duplex mode only). 
	**/
	uint64_t mTxExcessDeferral;
	/** 
	* @brief Asserted for received frames of size 64-bytes and greater 
	* which contained an odd number of received nibbles and 
	* which also contained an invalid FCS field. 
	**/
	uint64_t mTxAlignmentErrors;
} A664MacCounters;

/** 
*  @brief  Gets the MAC layer counters.
*          This function is only available for the V2 board.
*  @param[in]   aEndSystemHandle  A handle to an End System.
*  @param[in]   aNetwork          A Network Interface (A or B).
*  @param[out]  aMacCounters      A structure containing MAC layer counters.
*  @return @link error Error Code@endlink
**/
A664_API_FUNC  a664ESGetMacCounters(const A664EndSystemHandle aEndSystemHandle, const A664NetworkInterface  aNetwork,
								  A664MacCounters* aMacCounters);

/**
*  @brief Type of ES Event
**/
typedef enum 
{
	/** 
	*   @brief Tx Event Queue overflow on the ES hardware. This event indicates that the event queue of the ES hardware has overflowed 
	*          and that one or more events has been dropped by the embedded Tx Processor (txNIOS). This event indicates that events are
	*          occurring faster than the host is processing events.
	**/
	A664_EVENT_TX_EVENT_QUEUE_OVERFLOW,
	/** 
	*   @brief Indicates a Tx Message Port Event
	**/
	A664_EVENT_TX_MESSAGE_PORT,
	/** 
	*   @brief Rx Event Queue overflow on the ES hardware. This event indicates that the event queue of the ES hardware has overflowed
	*          and that one or more events have been dropped by the embedded Rx Processor (rxNIOS). This event indicates taht the events are
	*          occurring faster than the host is processing events.
	**/
	A664_EVENT_RX_EVENT_QUEUE_OVERFLOW,
	/** 
	*   @brief Indicates an Rx Critical Traffic Message Port Event
	**/
	A664_EVENT_RX_CT_MESSAGE_PORT,
	/** 
	*   @brief Indicates an Rx Best Effort/COTS Message Port Event
	**/
	A664_EVENT_RX_BE_MESSAGE_PORT,
	/** 
	*   @brief Indicates a Loopback Message Port Event
	**/
	A664_EVENT_LOOPBACK_MESSAGE_PORT
} A664EventType;
/** 
* @brief End System Event Information. Holds information about the ES Event
**/
typedef struct  
{
	/** 
	* @brief Specifies the type of Event 
	**/
	A664EventType		mEventType;
	/** 
	* @brief Specifies the Event type specific source. The actual information contained 
	*        is dependent on the event type as specified below <BR>
	*        A664_EVENT_TX_EVENT_QUEUE_OVERFLOW :   N/A <BR>
	*        A664_EVENT_TX_MESSAGE_PORT         :   Tx Message Port Handle <BR>
	*        A664_EVENT_RX_EVENT_QUEUE_OVERFLOW :   N/A <BR>
	*        A664_EVENT_RX_CT_MESSAGE_PORT      :   Rx CT Message Port Handle <BR>
	*        A664_EVENT_RX_BE_MESSAGE_PORT      :   Rx BE/COTS Message Port Handle <BR>
	*		 A664_EVENT_LOOPBACK_MESSAGE_PORT	:	Loopback Message Port Handle <BR>
	**/
	void*				mEventSource;
	/** 
	* @brief Specifies the Event Type specific data. The actual information contained is 
	*        dependent on the event type as specified below <BR>
	*        A664_EVENT_TX_EVENT_QUEUE_OVERFLOW :   N/A <BR>
	*        A664_EVENT_TX_MESSAGE_PORT         :   See A664TxMessagePortEventData <BR>
	*        A664_EVENT_RX_EVENT_QUEUE_OVERFLOW :   N/A <BR>
	*        A664_EVENT_RX_CT_MESSAGE_PORT      :   See A664RxMessagePortEventData <BR>
	*        A664_EVENT_RX_BE_MESSAGE_PORT      :   See A664RxMessagePortEventData <BR>
	*        A664_EVENT_LOOPBACK_MESSAGE_PORT	:	See A664RxMessagePortEventData <BR>
	**/
	uint32_t            mEventData[2];
	
	uint32_t 			deviceIdx;
	
	/**
	* @brief User pointer
	**/
	void *mpUserData;
} A664EventInfo;

/** 
* @brief Tx Message Port Event Data
**/
typedef struct 
{
#ifndef __VXWORKS__
	/** 
	* @brief Indicates if the event is a Tx Message Port Invalid Message Event
	**/
	unsigned int 		mInvalidMessageEvent	: 1;
	/** 
	* @brief Indicates if the event is a Tx Message Port Buffer Overflow Event
	**/
	unsigned int		mBufferOverflowEvent	: 1;
	/** 
	* @brief Indicates if the event is a Tx Message Port Message Sent Event
	**/
	unsigned int		mMessageSentEvent		: 1;
	unsigned int		mReserved				: 29;
#else
	unsigned int		mReserved				: 29;
	unsigned int		mMessageSentEvent		: 1;
	unsigned int		mBufferOverflowEvent	: 1;
	unsigned int 		mInvalidMessageEvent	: 1;
#endif
} A664TxMessagePortEventData;


/** 
*  @brief Rx (CT and BE) Message Port Event Data
**/
typedef struct 
{
#ifndef __VXWORKS__
	/** 
	* @brief Indicates if the event is an Rx Message Port Invalid Message Event
	**/
	unsigned int		mInvalidMessageEvent	: 1;
	/** 
	* @brief Indicates if the event is a Rx Message Port Buffer Overflow Event
	**/
	unsigned int		mBufferOverflowEvent	: 1;
	/** 
	* @brief Indicates if the event is a Rx Message Port Message Sent Event
	**/
	unsigned int		mMessageReceivedEvent	: 1;
	/** 
	* @brief reserved
	**/
	unsigned int		mReserved				: 27;
	/** 
	* @brief Indicates if the port is a loopback port
	**/
	unsigned int		mLoopbackPort			: 1;
	/** 
	* @brief Indicates if the port is a critical traffic port
	**/
	unsigned int		mCtPort					: 1;
#else
	unsigned int		mCtPort					: 1;
	unsigned int		mLoopbackPort			: 1;
	unsigned int		mReserved				: 27;
	unsigned int		mMessageReceivedEvent	: 1;
	unsigned int		mBufferOverflowEvent	: 1;
	unsigned int		mInvalidMessageEvent	: 1;
#endif
} A664RxMessagePortEventData;

/** 
* @brief Interrupt handler callback function pointer
* @param[in] apEventInfo Event Information specifying the type, source, and other information about the event
* @param[in] apUserData  Pointer to the user application data. This is the pointer to the user data provided when the Event handler is registered.
**/
typedef void (A664EventFunc(A664EventInfo* apEventInfo, void* apUserData));

/** 
* @brief Registers the Event handler function which is to be used for Events originating from the End System.
* @param[in] aEndSystemHandle The handle for the End System Device.
* @param[in] apEventFunc A pointer to the user defined event handler function. This is the user application function that is
*            invoked for each ES event.
* @param[in] apUserData A pointer to user/application controlled data. This pointer will be passed into the Event callback.
* @return @link error Error Code @endlink 
**/
A664_API_FUNC a664ESRegisterEventHandler(A664EndSystemHandle aEndSystemHandle, A664EventFunc* apEventFunc, void* apUserData);



/**@}	(end defgroup a664ApiEs)	*/

/**
* \defgroup a664ApiTxMessages A664 API Transmit Functions
* @{
*
* @section Overview
* <p>
* This section contains the A664 Library functions that
* are used by the application program to perform Transmit
* operations on the End System.
* </p>
*/

/**
* @brief Sends the frames that are stored in the common cache to the board.  
*   The Common Cache provides a way to send up to 64 frames or 64KB of message data in a single call to decrease overhead.
* @param[in] aEndSystemHandle The handle to the End System Device
* @return @link error Error Code @endlink 
**/
A664_API_FUNC a664TxSendCommonCache(const A664EndSystemHandle aEndSystemHandle);

/**
* @brief General Container for Tx Message Port Handles. This type is used for input parameters to functions
* not requiring a Tx Message Port Type specific handle.
*/
typedef void* A664TxMessagePortHandle;

/** 
* @brief Handle for Tx COM_UDP  type message ports
**/
typedef struct a664TxComUdpHandle
{
	A664TxMessagePortHandle handle;
} A664TxComUdpHandle;
/**
* @brief Open a COM_UDP (UDP COMMUNICATIONS) Type of message port for communications. A handle to be used for subsequent
* functions operating on the message port is returned.
* @param[in] aEndSystemHandle The handle to the End System Device
* @param[in] aPortId The ID of the Port as defined in the End System Configuration. Valid values are 0 - 1023.
* @param[out] aTxComUdpHandle The handle to the COM_UDP port.
* @return @link error Error Code @endlink 
**/
A664_API_FUNC a664TxComUdpOpen(const A664EndSystemHandle aEndSystemHandle, const uint32_t aPortId ,
							   A664TxComUdpHandle* aTxComUdpHandle);

/** 
* @brief Writes Data to the COM_UDP (Sampling or Queuing) type message port
* @param[in] aTxComUdpHandle The handle to the COM_UDP port
* @param[in] aDataLength The number of bytes of data in aTxComUdpData to write. 
                         Max Value: 1471 (sampling, limited by port configuration and sequence numbering)
						 8192 (queuing, limited by port configuration)
* @param[in] aTxComUdpData The data to write to the port
* @param[out] aBytesWritten The number of bytes successfully written to the message port
* @return @link error Error Code @endlink 
**/
A664_API_FUNC a664TxComUdpWrite(const A664TxComUdpHandle aTxComUdpHandle, const uint16_t aDataLength, 
							    const void* aTxComUdpData, uint16_t* aBytesWritten);

/** 
* @brief Writes Data to the COM_UDP (Sampling or Queuing) type message port.  This function is available for the V2 board.
* @param[in] aTxComUdpHandle The handle to the COM_UDP port
* @param[in] aDataLength The number of bytes of data in aTxComUdpData to write. 
                         Max Value: 1471 (sampling, limited by port configuration and sequence numbering)
						 8192 (queuing, limited by port configuration)
* @param[in] aTxComUdpData The data to write to the port
* @param[in] aOptions Provides additional options that can be set on this message.
*   bit 31 - CommonQueue -Set this bit to '1' to send the frame to the Common Queue.  
*     The Common Queue should periodically be flushed to the board by calling a664TxSendCommonCache().
*   bit 30 - CyclicCommonQueue - Set this bit to '1' to send the frame to the Cyclic Common Queue.  
*     The Cyclic Common Queue data will need to be periodically written to the board by calling a664TxCycComQueSend().
*   bit 15 - Short Frame - Set this bit to '1' to disable the padding and allow short frames to be sent.
*   bit 13 - Disable Interface ID – Set this bit to '1' to disable changing the interface ID on frames transmitted from sub-VLs.
*   bit 12 - FCS Error - Set this bit to '1' to invert the FCS.
*   bit 11 - nSn - Set this bit to 1 to send the message without a sequence number.
*   bits 9:8 - Set bit 9 to transmit on port 1, Set bit 8 to transmit on port 0, leave both cleared
*     to use the default port table setting.
*   bit 7 - Don't Fragment – Set this bit to '1' to set the Don't Fragment bit in the IP header and prevent the embedded code from fragmenting the frame.  This allows frames longer than 1518 bytes to be sent.
* @param[out] aBytesWritten The number of bytes successfully written to the message port
* @return @link error Error Code @endlink 
**/
A664_API_FUNC a664TxComUdpWriteEx(const A664TxComUdpHandle aTxComUdpHandle, const uint16_t aDataLength, 
							    const void* aTxComUdpData, uint32_t aOptions, uint16_t* aBytesWritten);

/** 
* @brief Closes the COM_UDP type port
* @param[in] aTxComUdpHandle The handle to the COM_UDP port
* @return @link error Error Code @endlink 
**/
A664_API_FUNC a664TxComUdpClose(const A664TxComUdpHandle aTxComUdpHandle);

/** 
* @brief Handle for a SAP_UDP Type Tx Message Port
**/
typedef struct a664TxSapUdpHandle
{
	A664TxMessagePortHandle handle;
} A664TxSapUdpHandle;

/** 
*  @brief  An IP Address represented as a raw 32-bit value.
**/
typedef  uint32_t  A664IpAddress;

/** 
* @brief A User Datagram Protocol (UDP) port address
**/
typedef  uint16_t       A664UdpAddress;
/** 
* @brief Opens an SAP_UDP type Tx Message Port and returns a port handle to be used
*        as input for subsequent functions performing operations on the Tx Message Port
* @param[in] aEndSystemHandle The handle to the associated End System device
* @param[in] aPortId The Port ID of the message port to be opened. This is the Port ID specified in the 
*                    configuration created by the TTE-Tools. Valid values are 0 - 1023.
* @param[out] aTxSapUdpHandle The handle to the SAP_UDP Tx Message port
* @return @link error Error Code @endlink 
**/
A664_API_FUNC  a664TxSapUdpOpen(const A664EndSystemHandle aEndSystemHandle, const uint32_t aPortId,
								A664TxSapUdpHandle* aTxSapUdpHandle);
/** 
* @brief Writes a message to an SAP_UDP type Tx Message Port
* @param[in] aTxSapUdpHandle The handle to the SAP_UDP Tx Message port
* @param[in] aDestIpAddress The Destination IP Address to which this message should be sent
* @param[in] aDestUdpAddress The Destination UDP Port to which this message should be sent
* @param[in] aDataLength The length (in bytes) of the message data (pointed to by aTxSapUdpData).
*                        Max Value: 8192 (Limited by port configuration)
* @param[in] aTxSapUdpData Pointer to the message data to be transmitted
* @param[out] aBytesWritten The number of bytes successfully written to the message port
* @return @link error Error Code @endlink 
**/
A664_API_FUNC a664TxSapUdpWrite(const A664TxSapUdpHandle aTxSapUdpHandle, const A664IpAddress aDestIpAddress,
								const A664UdpAddress aDestUdpAddress, const uint16_t aDataLength,
								const void* aTxSapUdpData, uint16_t* aBytesWritten);

/** 
* @brief Writes a message to an SAP_UDP type Tx Message Port
* @param[in] aTxSapUdpHandle The handle to the SAP_UDP Tx Message port
* @param[in] aDestIpAddress The Destination IP Address to which this message should be sent
* @param[in] aDestUdpAddress The Destination UDP Port to which this message should be sent
* @param[in] aDataLength The length (in bytes) of the message data (pointed to by aTxSapUdpData).
*                        Max Value: 8192 (Limited by port configuration)
* @param[in] aTxSapUdpData Pointer to the message data to be transmitted
* @param[in] aOptions Provides additional options that can be set on this message.
*   bit 31 - CommonQueue -Set this bit to '1' to send the frame to the Common Queue.
*     The Common Queue should periodically be flushed to the board by calling a664TxSendCommonCache().
*   bit 30 - CyclicCommonQueue - Set this bit to '1' to send the frame to the Cyclic Common Queue.  
*     The Cyclic Common Queue data will need to be periodically written to the board by calling a664TxCycComQueSend().
*   bit 13 - Disable Interface ID – Set this bit to '1' to disable changing the interface ID on frames transmitted from sub-VLs.
*   bit 12 - FCS Error - Set this bit to '1' to invert the FCS.
*   bit 11 - nSn - Set this bit to 1 to send the message without a sequence number.
*   bits 9:8 - Set bit 9 to transmit on port 1, Set bit 8 to transmit on port 0, leave both cleared
*     to use the default port table setting.
*   bit 7 - Don't Fragment – Set this bit to '1' to set the Don't Fragment bit in the IP header and prevent the embedded code from fragmenting the frame.  This allows frames longer than 1518 bytes to be sent.
* @param[out] aBytesWritten The number of bytes successfully written to the message port
* @return @link error Error Code @endlink 
**/
A664_API_FUNC a664TxSapUdpWriteEx(const A664TxSapUdpHandle aTxSapUdpHandle, const A664IpAddress aDestIpAddress,
								const A664UdpAddress aDestUdpAddress, const uint16_t aDataLength,
								const void* aTxSapUdpData, uint32_t aOptions, uint16_t* aBytesWritten);

/** 
* @brief Closes a SAP_UDP Tx Message port and releases the port handle
* @param[in] aTxSapUdpHandle The handle to the associated Tx SAP_UDP message port
* @return @link error Error Code @endlink 
**/
A664_API_FUNC  a664TxSapUdpClose(const A664TxSapUdpHandle aTxSapUdpHandle);

/** 
* UNDOCUMENTED FUNCTION
* Changes the source UDP port.
* param[in] aTxSapUdpHandle The handle to the associated Tx SAP_UDP port.
* param[out] aUdpSrcPort The UDP source port to be set.
* returns A664_API_OK upon successful completion.
**/
A664_API_FUNC  a664TxSapUdpChgSrcPort(	const A664TxSapUdpHandle  aTxSapUdpHandle,
									  const A664UdpAddress      aUdpSrcPort);
/** 
* @brief Handle for an SAP_IP type Tx Message Port
**/
typedef struct a664TxSapIpHandle
{
	A664TxMessagePortHandle handle;
} A664TxSapIpHandle;
/** 
* @brief Opens a Tx SAP_IP type message port and returns the port handle to be used in subsequent operation
*        on the port
* @param[in] aEndSystemHandle The handle to the associated End System device
* @param[in] aPortId The Port ID as specified in the input to the TTE-Tools ES configuration. Valid values are 0 - 1023.
* @param[out] aTxSapIpHandle The handle to the associated Tx SAP_IP message port
* @return @link error Error Code @endlink 
**/
A664_API_FUNC  a664TxSapIpOpen(const A664EndSystemHandle aEndSystemHandle, const uint32_t aPortId,
							   A664TxSapIpHandle* aTxSapIpHandle);
/** 
* @brief Writes a message to a Tx SAP_IP type message port
* @param[in] aTxSapIpHandle The handle to the associated Tx SAP_IP message port
* @param[in] aDestIpAddress The Destination IP Address to which this message should be sent
* @param[in] aDataLength The length (in bytes) of the message data (pointed to by aTxSapIpData).
*                        Max Value: 8200 (Limited by port configuration)
* @param[in] aTxSapIpData Pointer to the message data to be transmitted
* @param[out] aBytesWritten The number of bytes successfully written to the message port
* @return @link error Error Code @endlink 
**/
A664_API_FUNC  a664TxSapIpWrite(const A664TxSapIpHandle aTxSapIpHandle, const A664IpAddress aDestIpAddress, 
								const uint16_t aDataLength, const void* aTxSapIpData, uint16_t* aBytesWritten);

/** 
* @brief Writes a message to a Tx SAP_IP type message port
* @param[in] aTxSapIpHandle The handle to the associated Tx SAP_IP message port
* @param[in] aDestIpAddress The Destination IP Address to which this message should be sent
* @param[in] aDataLength The length (in bytes) of the message data (pointed to by aTxSapIpData).
*                        Max Value: 8200 (Limited by port configuration)
* @param[in] aTxSapIpData Pointer to the message data to be transmitted
* @param[in] aOptions Provides additional options that can be set on this message.
*   bit 31 - CommonQueue -Set this bit to '1' to send the frame to the Common Queue.
*     The Common Queue should periodically be flushed to the board by calling a664TxSendCommonCache().
*   bit 30 - CyclicCommonQueue - Set this bit to '1' to send the frame to the Cyclic Common Queue.  
*     The Cyclic Common Queue data will need to be periodically written to the board by calling a664TxCycComQueSend().
*   bit 13 - Disable Interface ID – Set this bit to '1' to disable changing the interface ID on frames transmitted from sub-VLs.
*   bit 12 - FCS Error - Set this bit to '1' to invert the FCS.
*   bit 11 - nSn - Set this bit to 1 to send the message without a sequence number.
*   bits 9:8 - Set bit 9 to transmit on port 1, Set bit 8 to transmit on port 0, leave both cleared
*     to use the default port table setting.
*   bit 7 - Don't Fragment – Set this bit to '1' to set the Don't Fragment bit in the IP header and prevent the embedded code from fragmenting the frame.  This allows frames longer than 1518 bytes to be sent.
* @param[out] aBytesWritten The number of bytes successfully written to the message port
* @return @link error Error Code @endlink 
**/
A664_API_FUNC  a664TxSapIpWriteEx(const A664TxSapIpHandle aTxSapIpHandle, const A664IpAddress aDestIpAddress, 
								const uint16_t aDataLength, const void* aTxSapIpData, uint32_t aOptions, 
								uint16_t* aBytesWritten);

/** 
* @brief Closes a SAP_IP Tx Message port and releases the port handle
* @param[in] aTxSapIpHandle The handle to the associated Tx SAP_IP message port
* @return @link error Error Code @endlink 
**/
A664_API_FUNC  a664TxSapIpClose(const A664TxSapIpHandle aTxSapIpHandle);

/** 
* @brief Handle for a TX SAP_MAC Type Message port
**/
typedef struct a664TxSapMacHandle
{
	A664TxMessagePortHandle handle;
} A664TxSapMacHandle;
/** 
* @brief Opens a Tx SAP_MAC type port and returns a port handle to be used for subsequent operations on the port
* @param[in] aEndSystemHandle The handle to the associated End System device
* @param[in] aPortId The Port ID as specified in the input to the TTE-Tools ES configuration. Valid values are 0 - 1023.
* @param[out] aTxSapMacHandle The handle to the associated Tx SAP_MAC message port
* @return @link error Error Code @endlink 
**/
A664_API_FUNC a664TxSapMacOpen(const A664EndSystemHandle aEndSystemHandle, const uint32_t aPortId, A664TxSapMacHandle* aTxSapMacHandle);
/** 
* @brief Writes a message to a Tx SAP_MAC type message port
* @param[in] aTxSapMacHandle The handle to the associated Tx SAP_MAC message port
* @param[in] aDataLength The length (in bytes) of the message data (pointed to by aTxSapMacData).
*                        Max Value: 1500 (Limited by port configuration and sequence numbering)
* @param[in] aTxSapMacData Pointer to the message data to be transmitted
* @param[out] aBytesWritten The number of bytes successfully written to the message port
* @return @link error Error Code @endlink 
**/
A664_API_FUNC a664TxSapMacWrite(const A664TxSapMacHandle aTxSapMacHandle, const uint16_t aDataLength, 
								const void* aTxSapMacData, uint16_t* aBytesWritten);
/** 
* @brief Writes a message to a Tx SAP_MAC type message port
* @param[in] aTxSapMacHandle The handle to the associated Tx SAP_MAC message port
* @param[in] aDataLength The length (in bytes) of the message data (pointed to by aTxSapMacData).
*                        Max Value: 1500 (Limited by port configuration and sequence numbering)
* @param[in] aTxSapMacData Pointer to the message data to be transmitted
* @param[in] aOptions Provides additional options that can be set on this message.
*   bit 31 - CommonQueue -Set this bit to '1' to send the frame to the Common Queue.
*     The Common Queue should periodically be flushed to the board by calling a664TxSendCommonCache().
*   bit 30 - CyclicCommonQueue - Set this bit to '1' to send the frame to the Cyclic Common Queue.  
*     The Cyclic Common Queue data will need to be periodically written to the board by calling a664TxCycComQueSend().
*   bit 13 - Disable Interface ID – Set this bit to '1' to disable changing the interface ID on frames transmitted from sub-VLs.
*   bit 12 - FCS Error - Set this bit to '1' to invert the FCS.
*   bit 11 - nSn - Set this bit to 1 to send the message without a sequence number.
*   bits 9:8 - Set bit 9 to transmit on port 1, Set bit 8 to transmit on port 0, leave both cleared
*     to use the default port table setting.
* @param[out] aBytesWritten The number of bytes successfully written to the message port
* @return @link error Error Code @endlink 
**/
A664_API_FUNC a664TxSapMacWriteEx(const A664TxSapMacHandle aTxSapMacHandle, const uint16_t aDataLength, 
								const void* aTxSapMacData, uint32_t aOptions, uint16_t* aBytesWritten);
/** 
* @brief Closes a SAP_MAC Tx Message port and releases the port handle
* @param[in] aTxSapMacHandle The handle to the associated Tx SAP_MAC message port
* @return @link error Error Code @endlink 
**/
A664_API_FUNC a664TxSapMacClose(const A664TxSapMacHandle aTxSapMacHandle);

/** 
* @brief Handle for a COTS_MAC type Tx Message port
**/
typedef struct a664TxCotsMacHandle
{
	A664TxMessagePortHandle handle;
} A664TxCotsMacHandle;
/** 
* @brief Opens a Tx COTS_MAC type port and returns a port handle to be used for subsequent operations on the port
* @param[in] aEndSystemHandle The handle to the associated End System device
* @param[in] aPortId The Port ID as specified in the input to the TTE-Tools ES configuration. Valid values are 0 - 1023.
* @param[out] aTxCotsMacHandle The handle to the associated Tx COTS_MAC message port
* @return @link error Error Code @endlink 
**/
A664_API_FUNC  a664TxCotsMacOpen(const A664EndSystemHandle aEndSystemHandle, const uint32_t aPortId,
								 A664TxCotsMacHandle* aTxCotsMacHandle);
/** 
* @brief A MAC/Ethernet Address
**/
typedef struct  
{
	/** 
	* @brief The upper (high order) 16 bits of the MAC Address
	**/
	uint16_t     mMacAddressHigh;
	/** 
	* @brief The lower (low order) 32 bits of the MAC Address
	**/
	uint32_t     mMacAddressLow;
} A664MacAddress;
/** 
* @brief MAC Type Length Field
**/
typedef  uint16_t     A664MacTypeLen;

/** 
* @brief Writes a message to a Tx COTS_MAC type message port
* @param[in] aTxCotsMacHandle The handle to the associated Tx COTS_MAC message port
*.@param[in] aDestMacAddress The destination MAC Address to which the message shall be sent
* @param[in] aMacTypeLen The value to be inserted into the MAC Type/Len field of the outgoing message. If set to 0
*                        the End System will automatically fill this field with the correct length value.
* @param[in] aDataLength The length (in bytes) of the message data (pointed to by aTxCotsMacData).
*                        Max Value: 1500 (1518 - MacDest - MacSrc - MacType - CRC).
* @param[in] aTxCotsMacData Pointer to the message data to be transmitted
* @param[out] aBytesWritten The number of bytes successfully written to the message port
* @return @link error Error Code @endlink 
**/
A664_API_FUNC  a664TxCotsMacWrite(const A664TxCotsMacHandle  aTxCotsMacHandle, const A664MacAddress aDestMacAddress,
								  const A664MacTypeLen aMacTypeLen, const uint16_t aDataLength,
								  const void* aTxCotsMacData, uint16_t* aBytesWritten);
/** 
* @brief Closes a COTS_MAC Tx Message port and releases the port handle
* @param[in] aTxCotsMacHandle The handle to the associated Tx COTS_MAC message port
* @return @link error Error Code @endlink 
**/
A664_API_FUNC  a664TxCotsMacClose(const A664TxCotsMacHandle aTxCotsMacHandle);

/** 
* @brief Handle for a COTS_MAC_RAW type Tx Message port
**/
typedef struct a664TxCotsMacRawHandle
{
	A664TxMessagePortHandle handle;
} A664TxCotsMacRawHandle;

/** 
* @brief Handle for a VL_RTP type Tx Message port
**/
typedef struct a664TxVlRtpHandle
{
	A664TxMessagePortHandle handle;
} A664TxVlRtpHandle;

/** 
* @brief Opens a Tx COTS_MAC_RAW type port and returns a port handle to be used for subsequent operations on the port
* @param[in] aEndSystemHandle The handle to the associated End System device
* @param[in] aPortId The Port ID as specified in the input to the TTE-Tools ES configuration. Valid values are 0 - 1023.
* @param[out] aTxCotsMacRawHandle The handle to the associated Tx COTS_MAC_RAW message port
* @return @link error Error Code @endlink 
**/
A664_API_FUNC  a664TxCotsMacRawOpen(const A664EndSystemHandle aEndSystemHandle, 
									const uint32_t aPortId,
									A664TxCotsMacRawHandle* aTxCotsMacHandle);

/** 
* @brief Writes a message to a Tx COTS_MAC_RAW type message port
* @param[in] aTxCotsMacRawHandle The handle to the associated Tx COTS_MAC_RAW message port which can be used for timed playback
* @param[in] aDataLength The length (in bytes) of the data (pointed to by aTxCotsMacRawData).
*                        Max Value: 1514 (1518 - CRC).
* @param[in] aTxCotsMacData Pointer to the message data to be transmitted, this included the Mac header and payload
* @param[in] aTime Pointer to the timestamp for the frame, the frame will be sent out at this time minus time zero
* @param[in] aSetBaseTime If this is non zero then aTime + (nanoseconds)aSetBaseTime will be set as time zero for the COTS_MAC_RAW Tx ports on the ES, other than the first frame in the sequence it should be set to 0
* @param[out] aBytesWritten The number of bytes successfully written to the message port
* @return @link error Error Code @endlink 
**/
A664_API_FUNC  a664TxCotsMacRawWrite(const A664TxCotsMacRawHandle  aTxCotsMacRawHandle, 
									 const uint16_t aDataLength, 
									 const void* aTxCotsMacRawData, 
									 const A664Timestamp* aTime, 
									 const uint32_t aSetBaseTime,
									 uint16_t* aBytesWritten);

/** 
* @brief Closes a COTS_MAC_RAW Tx Message port and releases the port handle
* @param[in] aTxCotsMacRawHandle The handle to the associated Tx COTS_MAC_RAW message port
* @return @link error Error Code @endlink 
**/
A664_API_FUNC  a664TxCotsMacRawClose(const A664TxCotsMacRawHandle aTxCotsMacRawHandle);

/** 
* @brief Opens a Tx VL_RTP type port and returns a port handle to be used for subsequent operations on the port
* @param[in] aEndSystemHandle The handle to the associated End System device
* @param[in] aPortId The Port ID as specified in the configuration.
* @param[out] aTxVlRtpHandle The handle to the associated Tx VL_RTP message port
* @return @link error Error Code @endlink 
**/
A664_API_FUNC  a664TxVlRtpOpen(const A664EndSystemHandle aEndSystemHandle, 
									const uint32_t aPortId,
									A664TxVlRtpHandle* aTxVlRtpHandle);

/** 
* @brief Closes a VL_RTP Tx Message port and releases the port handle
* @param[in] aTxVlRtpHandle The handle to the associated Tx VL_RTP message port
* @return @link error Error Code @endlink 
**/
A664_API_FUNC  a664TxVlRtpClose(const A664TxVlRtpHandle aTxVlRtpHandle);

/** 
* @brief Handle for Tx COM_UDP  type message ports
**/
typedef struct a664TxComUdpCycHandle
{
	A664TxMessagePortHandle handle;
} A664TxComUdpCycHandle;

/**
* @brief Open a COM_UDP (UDP COMMUNICATIONS) Cyclic type of message port for communications. A handle to be used for subsequent
* functions operating on the message port is returned.
* @param[in] aEndSystemHandle The handle to the End System Device
* @param[in] aMessageIndex The index of the message port as defined in the End System Configuration. Valid values are 0 - 4095.
* @param[out] aTxComUdpCycHandle The handle to the COM_UDP Cyclic port.
* @return @link error Error Code @endlink 
**/
A664_API_FUNC a664TxComUdpCycOpenIdx(const A664EndSystemHandle aEndSystemHandle, const uint32_t aMessageIndex,
							   A664TxComUdpCycHandle* aTxComUdpCycHandle);

/** 
* @brief Writes Data to the COM_UDP (Sampling or Queuing) Cyclic type message port
* @param[in] aTxComUdpCycHandle The handle to the COM_UDP port
* @param[in] aDataLength The number of bytes of data in aTxComUdpData to write. 
                         Max Value: 1471 (sampling, limited by port configuration and sequence numbering)
* @param[in] aTxComUdpData The data to write to the port
* @param[out] aBytesWritten The number of bytes successfully written to the message port
* @return @link error Error Code @endlink 
**/
A664_API_FUNC a664TxComUdpCycWrite(const A664TxComUdpCycHandle aTxComUdpCycHandle, const uint16_t aDataLength, 
							    const void* aTxComUdpData, uint16_t* aBytesWritten);

/** 
* @brief Closes the COM_UDP Cyclic type port.  This is only valid for V2 hardware.
* @param[in] aTxComUdpCycHandle The handle to the COM_UDP Cyclic port
* @return @link error Error Code @endlink 
**/
A664_API_FUNC a664TxComUdpCycClose(const A664TxComUdpCycHandle aTxComUdpCycHandle);

/** 
* @brief Control information for a Cyclic Message Port
**/
typedef struct 
{
#ifndef __VXWORKS__
	/** 
	* @brief Enables (True) or Disables (False) Events on invalid messages for the message port
	**/
	unsigned int mInvalidMessageEventEnable		: 1;
	unsigned int mReserved1						: 1;
	/** 
	* @brief Enables (True) or Disables (False) Events on valid messages sent for the message port
	**/
	unsigned int mMessageSentEventEnable		: 1;
	unsigned int mReserved						: 28;
	/** 
	* @brief Enables (True) or Disables (False) the message port for sending messages
	**/
	unsigned int mMessagePortEnable				: 1;
#else
	unsigned int mMessagePortEnable				: 1;
	unsigned int mReserved						: 28;
	unsigned int mMessageSentEventEnable		: 1;
	unsigned int mReserved1						: 1;
	unsigned int mInvalidMessageEventEnable		: 1;
#endif
} A664TxCycMsgPrtCtl;


/** 
* @brief Set control settings for a TX Cyclic Message Port
* @param[in] aTxCycMsgPrtHandle The handle to the Cyclic Message Port
* @param[in] aTxCycMsgPrtControl The structure containing the Cyclic Message Port control settings
**/
A664_API_FUNC a664TxSetCycMsgPrtControl(const A664TxMessagePortHandle aTxCycMsgPrtHandle,
									 const A664TxCycMsgPrtCtl *aTxCycMsgPrtControl);
/** 
* @brief Status Data for a Cyclic Message Port
**/
typedef struct 
{
	/** 
	* @brief Count of valid messages sent
	**/
	uint32_t mValidMessageCount;
	/** 
	* @brief Count of invalid messages at the port 
	**/
	uint32_t mInvalidMessageCount;
	/** 
	* @brief Indicates the control information set for the message
	**/
	A664TxCycMsgPrtCtl mCycMsgControl;
} A664TxCycMsgPrtStat;

/** 
* @brief Get the current status for a TX Cyclic Message Port
* @param[in] aTxCycMsgPrtHandle The handle to the Cyclic Message Port
* @param[out] aTxCycMsgPrtStatus The structure containing the Cyclic Message Port status info
**/
A664_API_FUNC a664TxGetCycMsgPrtStatus( const A664TxMessagePortHandle aTxCycMsgPrtHandle,
									A664TxCycMsgPrtStat* aTxCycMsgPrtStatus);

/** 
* @brief Specifier of Tx Message Port Type
**/
typedef enum
{
	/** 
	* @brief Disabled Tx Message Port
	**/
	A664_TX_DISABLED         = 0,
	/**
	* @brief SAP_UDP Type Tx Message Port
	**/
	A664_TX_SAP_UDP          = 1,
	/**
	* @brief SAP_IP Type Tx Message Port
	**/
	A664_TX_SAP_IP           = 2,
	/**
	* @brief SAP_MAC Type Tx Message Port
	**/
	A664_TX_SAP_MAC          = 3,
	/**
	* @brief COM_UDP (Sampling) Type Tx Message Port
	**/
	A664_TX_COM_UDP_SAMPLING = 4,
	/**
	* @brief COM_UDP (Queuing) Type Tx Message Port
	**/
	A664_TX_COM_UDP_QUEUING  = 5,
	/**
	* @brief COTS_MAC_RAW Type Tx Message Port
	**/
	A664_TX_COTS_MAC_RAW     = 6,
	/**
	* @brief COTS_MAC Type Tx Message Port
	**/
	A664_TX_COTS_MAC         = 7,
	/** 
	* @brief VL_RTP	Type Tx Message Port - Only valid on V2 hardware
	**/
	A664_TX_VL_RTP			= 8,
	/**
	* @brief EDE COM_UDP (Sampling) Type Tx Message Port
	**/
	A664_TX_EDE_COM_UDP_SAMPLING = 10,
	/**
	* @brief EDE COM_UDP (Queuing) Type Tx Message Port
	**/
	A664_TX_EDE_COM_UDP_QUEUING  = 11
} A664TxMessagePortType;

/** 
* @brief Tx Message Port Control Data
**/
typedef struct 
{
#ifndef __VXWORKS__
	/** 
	* @brief Enables (True) or Disables (False) Events on invalid messages for the message port
	**/
	unsigned int mInvalidMessageEventEnable		: 1;
	/** 
	* @brief Enables (True) or Disables (False) Events on message port buffer overflows for the message port. 
	*        The message port buffer overflow events occur when VL buffer associated to the message port overflows.
	**/
	unsigned int mBufferOverflowEventEnable		: 1;
	/** 
	* @brief Enables (True) or Disables (False) Events on valid messages sent for the message port
	**/
	unsigned int mMessageSentEventEnable		: 1;
	unsigned int	mReserved					: 28;
	/** 
	* @brief Enables (True) or Disables (False) the message port for sending messages
	**/
	unsigned int mMessagePortEnable				: 1;
#else
	unsigned int mMessagePortEnable				: 1;
	unsigned int	mReserved					: 28;
	unsigned int mMessageSentEventEnable		: 1;
	unsigned int mBufferOverflowEventEnable		: 1;
	unsigned int mInvalidMessageEventEnable		: 1;
#endif
} A664TxMessagePortControl;
/** 
* @brief Sets the control settings for a Tx Message Port
* @param[in] aTxMessagePortHandle The handle of the Tx Message Port for which the control settings
*            shall be set
* @param[in] apTxMessagePortControl The structure containing the Tx Message Port control settings
* @return @link error Error Code @endlink
**/
A664_API_FUNC a664TxSetMessagePortControl(const A664TxMessagePortHandle aTxMessagePortHandle, A664TxMessagePortControl* apTxMessagePortControl);

/** 
* @brief Tx Message Port Status Information
**/
typedef struct  
{
	/** 
	* @brief The Type of Tx Message Port
	**/
	A664TxMessagePortType mTxMessagePortType;
	/**
	* @brief The Port ID
	**/
	uint32_t			mPortId;
	/** 
	* @brief The ES Index
	**/
	uint32_t			mEsIndex;
	/** 
	* @brief Count of valid messages transmitted from the Tx Message Port
	**/
	uint32_t              mValidMessageCount;
	/** 
	* @brief Count of invalid messages submitted to the Tx Message Port for transmission. 
	*        Messages may be invalid due to containing more data than the maximum message size
	*        configured for the port or due to the message written to the port being of the incorrect
	*        type (that is not matching the Tx Message Port Type)
	**/
	uint32_t              mInvalidMessageCount;
	/** 
	* @brief Count of messages not transmitted from the Tx Message Port due to no buffer resources 
	*        being available in the lower layer Sub Virtual Link associated to the Tx Message Port
	**/
	uint32_t              mNoBufferAvailableErrorCount;
	/** 
	* @brief Count of full buffers in the CT or BE Queue
	**/
	uint32_t              mNumFullBuffers;
	/** 
	* @brief Count of empty buffers in the CT or BE Queue
	**/
	uint32_t              mNumEmptyBuffers;
	/** 
	* @brief Indicates the control bits for the port
	**/
	A664TxMessagePortControl	mMessagePortControl;
} A664TxMessagePortStatus;
/**
* @brief Gets the status information for a Tx Message Port
* @param[in]  aTxMessagePortHandle The handle of the Tx Message Port from which the status information 
*             shall be retrieved
* @param[out] aTxMessagePortStatus The structure containing the Tx Message Port Status data
* @return @link error Error Code @endlink 
**/
A664_API_FUNC a664TxGetMessagePortStatus(const A664TxMessagePortHandle aTxMessagePortHandle, A664TxMessagePortStatus* aTxMessagePortStatus);
/** 
* @brief Tx UDP Layer Status Information
**/
typedef struct  
{
	/** 
	* @brief Count of the total number of messages processed by the Tx UDP layer
	**/
	uint32_t             mTotalMessageCount;
	/** 
	* @brief Count of the number of invalid messages received at the Tx UDP layer for transmission
	*        This field is the sum of all of the Invalid Message Counts of the Tx Message Ports
	**/
	uint32_t             mInvalidMessageCount;
	/** 
	* @brief Count of the number of messages submitted for transmission by the host for which 
	*        no configured Tx Message port is defined. 
	**/
	uint32_t             mNoPortCount;
} A664TxUdpStatus;
/** 
* @brief Gets the status information for the Tx UDP Protocol Layer
* @param[in]  aEndSystemHandle The handle to the End System Device
* @param[out]  aTxUdpStatus The structure containing the Tx UDP Layer Status Information
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664TxGetUdpStatus(const A664EndSystemHandle aEndSystemHandle, A664TxUdpStatus* aTxUdpStatus);
/** 
* @brief Tx IP Layer Status Information
**/
typedef struct  
{
	/** 
	* @brief Count of the total number of packets processed by the Tx IP layer
	**/
	uint32_t            mTotalPacketCount;
	/** 
	* @brief Count of the number of invalid packets processed by the Tx IP layer
	**/
	uint32_t            mInvalidPacketCount;
	/** 
	* @brief Count of the number of packets discarded by the Tx IP layer. Packets can
	*        be discarded for example if there are no available resources in the MAC
	*        layer for transmission of the packet
	**/
	uint32_t            mDiscardCount;
} A664TxIpStatus;
/** 
* @brief Gets the status information for the Tx IP Protocol Layer
* @param[in]   aEndSystemHandle The handle to the End System Device
* @param[out]  aTxIpStatus The structure containing the Tx IP Layer Status Information
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664TxGetIpStatus(const A664EndSystemHandle aEndSystemHandle, A664TxIpStatus* aTxIpStatus);

/** 
* @brief Gets network interfaces that frames will be sent on for the specified VL
* @param[in]   aEndSystemHandle The handle to the End System Device
* @param[in]   aVlId The VL Identification of the VL to retrieve the information for
* @param[out]  apNetwork The enum to return the enabled network interfaces in
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664TxGetVlNet(const A664EndSystemHandle aEndSystemHandle, uint16_t aVlId, A664NetworkInterfaceBits* apNetwork);

/** 
* @brief Sets network interfaces that frames will be sent on for the specified VL
* @param[in]   aEndSystemHandle The handle to the End System Device
* @param[in]   aVlId The VL Identification of the VL to set the network interface for
* @param[out]  aNetwork The enum specifying the network interfaces to enable
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664TxSetVlNet(const A664EndSystemHandle aEndSystemHandle, uint16_t aVlId, A664NetworkInterfaceBits aNetwork);

typedef struct a664TxLoopbackError
{
	/** 
	* @brief Start of Frame Error (e.g. invalid preamble)
	**/
	unsigned int mSofError				: 1;
	/** 
	* @brief Frame Size Error (smaller than 64 or larger than 2047)
	**/
	unsigned int mFrameSizeError		: 1;
	/** 
	* @brief Alignment Error (symbols not coming in at correct intervals)
	**/
	unsigned int mAlignmentError		: 1;
	/**
	* @brief MII Error (the TX MAC aborted the transmission)
	**/
	unsigned int mMiiError				: 1;
	/**
	* @Brief CRC Error (the final checksum is not correct)
	**/
	unsigned int mCrcError				: 1;
	unsigned int mReserved				: 27;
} A664TxLoopbackError;

/**
* @brief **Deprecated** use a664RxLoopbackRead() instead. 
* Reads a message from a Tx Loopback frame interface
* @param[in] aEndSystemHandle The handle to the ES Device
* @param[in] aNetwork The network interface from which to read a frame
* @param[in] aMaxDataBytes The maximum number of data bytes that can be read. This is the size of the 
*                          buffer allocated by the application to store the read data (pointed to by aRxLoopbackMacDataBuffer)
* @param[in] aTxLoopbackMacDataBuffer Pointer to the data buffer that is to hold the read message port data. The data stored in 
*                                 this buffer will be the entire MAC frame.
* @param[out] aBytesRead The actual number of message payload bytes read from the port.
* @param[out] aTime The time at which the frame was received
* @param[out] aLoopbackError Errors detected on the transmission
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664TxLoopbackMacRead(const A664EndSystemHandle aEndSystemHandle, 
									const A664NetworkInterface aNetwork,  
									const uint16_t aMaxDataBytes, 
									void* aTxLoopbackMacDataBuffer, 
									uint16_t* aBytesRead, 
									A664Timestamp* aTime,
									A664TxLoopbackError* aLoopbackError);

/** 
* @brief Resets the monitor pointer so the next monitor read will start with the next frame received.
* Make sure the board is not transmitting data when this function is called.
* This function is only available on AIT hardware.
* @param[in] aEndSystemHandle The handle to the associated End System device
* @param[in] aNetwork The network of the monitor to reset.
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664TxMonitorReset(const A664EndSystemHandle aEndSystemHandle, A664NetworkInterface aNetwork);

/** 
* @brief Reads a block of data from the Tx Monitor.  The data is returned in the firmware's monitor format.
*			The returned data may end in the middle of a frame, the next read will start where the last read left off.
*			This function is only valid on AIT hardware.
* @param[in] aEndSystemHandle The handle to the associated End System device
* @param[in] aNetwork The network of the monitor to read.
* @param[in] aMaxDataBytes The maximum number of data bytes that can be read. This is the size of the 
*                          buffer allocated by the application to store the read data (pointed to by aDataBuffer).
*							Efficiency will peak at 64KB.
* @param[in] aDataBuffer Pointer to the data buffer that is to hold the read monitor data. The data stored in 
*                         this buffer will be in the firmware's monitor format.  This buffer needs to be aligned to start on a 32 bit address.
* @param[out] aBytesRead The actual number of bytes read from the port.  This will be a multiple of 16 bytes.
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664TxMonitorRead(const A664EndSystemHandle aEndSystemHandle, A664NetworkInterface aNetwork, 
								const uint32_t aMaxDataBytes, void* aDataBuffer, uint32_t* aBytesRead);

/** 
* @brief Resets the Replay data in the TXuP.  This function must be called before a664TxReplayFirm is called.  
* This function is only available for the V2 board.
* @param[in] aEndSystemHandle The handle to the associated End System device.
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664TxReplayFirmReset(const A664EndSystemHandle aEndSystemHandle);

/** 
* @brief Stops loading replay frames into the transmit queue.
* Note: frames already in the queue will still be transmitted.
* This function is only available for the V2 board.
* @param[in] aEndSystemHandle The handle to the associated End System device.
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664TxReplayFirmStop(const A664EndSystemHandle aEndSystemHandle);

/** 
* @brief Replays data that is in the firmware monitor format.  This data can be feed to this function 
*  in blocks which will fill a replay buffer on the board for the TXuP to process and send to the 
*  firmware for timed replay.  This function is only available for the V2 board.
* @param[in] aEndSystemHandle The handle to the associated End System device.
* @param[in] aFirstBlock This should be set to 1 if this is the first block of replay data, 
*  it should be set to 0 otherwise.  This will indicate to the lower levels to set time 0.
* @param[in] aDataBuffer Pointer to the data buffer that holds the data to be replayed.  
*  The data does not need to end on the end of a frame, however the last frame will not be 
*  replayed until it is completed by the next block.
* @param[in] aDataBytes The number of bytes in the buffer for replay, this must be a multiple of 
*  16 bytes, if it is the end of a file the buffer should be padded to a 16 byte multiple. 
*  Maximum throughput should start at 64KB blocks.
* @param[out] aBytesSent The actual number of bytes sent to be replayed.  This will be a multiple 
*  of 16 bytes and may be less than aDataBytes if the buffer full.
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664TxReplayFirm(const A664EndSystemHandle aEndSystemHandle, uint8_t aFirstBlock, 
							   void* aDataBuffer, const uint32_t aDataBytes,  uint32_t* aBytesSent);

/** 
* @brief Retrieves the replay status.
* @param[in] aEndSystemHandle The handle to the associated End System device.
*  This function is only available for the V2 board.
* @param[out] aFramesSent Returns a count of the frames sent since aFirstBlock was set.
* @param[out] aBuffAvailable Returns the number of bytes available in the replay buffer.
* @param[out] aBuffSize Returns the size of the replay buffer in bytes.
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664TxReplayGetStatus(const A664EndSystemHandle aEndSystemHandle, uint32_t* aFramesSent, 
									uint32_t* aBuffAvailable, uint32_t* aBuffSize);

/** 
* @brief Resets the Replay data in the TXuP.  This function must be called before a664TxReplayFirm is called.  
*  This function is only available for the Dual Channel Ethernet board.
* @param[in] aEndSystemHandle The handle to the associated End System device.
* @param[in] aNetwork The replay network to reset.
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664TxReplayFirmResetDce(const A664EndSystemHandle aEndSystemHandle, A664NetworkInterface aNetwork);

/** 
* @brief Flushes the TX Posting FIFO in the firmware to stop transmitting frames and dump frames waiting to go out.
* This function is only available for the V2 board.
* @param[in] aEndSystemHandle The handle to the associated End System device.
* @param[in] aNetwork The replay network to reset.
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664TxReplayFirmStopDce(const A664EndSystemHandle aEndSystemHandle, A664NetworkInterface aNetwork);

/** 
* @brief Sets the transmit sync functionality for the specified port.  When this is enabled the replay will start on a trigger. This function must be called after a664TxReplayFirmResetDce().   
*  This function is only available for the Dual Channel Ethernet board.
* @param[in] aEndSystemHandle The handle to the associated End System device.
* @param[in] aNetwork The replay network to enable or disable sync.  Network A will wait for a pulse on pin 13.  Network B will wait for a trigger on pin 6.
* @param[in] aTxSyncEn Set to '1'  to enable the transmit sync start functionality, set to '0' to disable the functionality.
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664TxReplayTxSyncDce(const A664EndSystemHandle aEndSystemHandle, A664NetworkInterface aNetwork, uint8_t aTxSyncEn);

/** 
* @brief Replays data that is in the firmware monitor format.  This data can be feed to this function 
*  in blocks which will be processed and fill a replay buffer on the board and sent to the 
*  firmware for timed replay.
*  This function is only available for the Dual Channel Ethernet board.
* @param[in] aEndSystemHandle The handle to the associated End System device.
* @param[in] aFirstBlock This should be set to 1 if this is the first block of replay data, 
*  it should be set to 0 otherwise.  This will indicate to the lower levels to set time 0.
* @param[in] aDataBuffer Pointer to the data buffer that holds the data to be replayed.  
*  The data does not need to end on the end of a frame, however the last frame will not be 
*  replayed until it is completed by the next block.
* @param[in] aDataBytes The number of bytes in the buffer for replay, this must be a multiple of 
*  16 bytes, if it is the end of a file the buffer should be padded to a 16 byte multiple. 
*  Maximum throughput should start at 64KB blocks.
* @param[in] aNetwork The replay network to to send the frames on.
* @param[out] aBytesSent The actual number of bytes sent to be replayed.  This will be a multiple 
*  of 16 bytes and may be less than aDataBytes if the is buffer full or if the data ended with a partial frame.
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664TxReplayFirmDce(const A664EndSystemHandle aEndSystemHandle, uint8_t aFirstBlock, 
							   void* aDataBuffer, const uint32_t aDataBytes, A664NetworkInterface aNetwork, uint32_t* aBytesSent);

/** 
* @brief Outputs a transmit sync pulse.
*  This function is only available for the Dual Channel Ethernet board.
* @param[in] aEndSystemHandle The handle to the associated End System device.
* @param[in] aNetwork Determines the pin that the trigger will be sent on.  Network A will send a trigger on pin 14.  Network B will send a pulse on pin 3.
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664TxReplayTxSyncStartDce(const A664EndSystemHandle aEndSystemHandle, A664NetworkInterface aNetwork);

/** 
* @brief Retrieves the replay status.
* @param[in] aEndSystemHandle The handle to the associated End System device.
*  This function is only available for the Dual Channel Ethernet board.
* @param[in] aNetwork The replay network to to retreive the status for.
* @param[out] aFramesSent Returns a count of the frames sent since a664TxReplayFirmResetDce() was called.
* @param[out] aFramesProcessed Returns a count of the frames processed since a664TxReplayFirmResetDce() was called.
* @param[out] aBuffAvailable Returns the number of bytes available in the replay buffer.
* @param[out] aBuffSize Returns the size of the replay buffer in bytes.
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664TxReplayGetStatusDce(const A664EndSystemHandle aEndSystemHandle, A664NetworkInterface aNetwork, uint32_t* aFramesSent, 
									uint32_t* aFramesProcessed, uint32_t* aBuffAvailable, uint32_t* aBuffSize);

/**
* @brief Resends the replay data that was has been sent with a664TxReplayFirmDce() since a664TxReplayFirmResetDce() has been called.  
*  There is a limit of 1024 successful calls to a664TxReplayFirmDce() before buffer overflow is hit and this function will return an error.
*  This function will not return till the board has enough space to resend all of the data so it may take a while if the replay data is slow.  
*  The function will release the channel mutexes while waiting so that other API functions from another thread may interact with the board.
*  This function is only available for the Dual Channel Ethernet board.
* @param[in] aEndSystemHandle The handle to the associated End System device.
* @param[in] aNetwork The replay network to to send the frames on.
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664TxReplayFirmResendDce(const A664EndSystemHandle aEndSystemHandle, A664NetworkInterface aNetwork);

/** 
* @brief Starts the Tx Cyclic Schedule.
* param[in] aEndSystemHandle The handle to the ES Device
* param[in] aMajorFrameCount The number of times to send the major frame. Use 0 for continuous transmission.
**/
A664_API_FUNC a664TxCyclicStart( const A664EndSystemHandle aEndSystemHandle,
								const uint32_t aMajorFrameCount);

/** 
* @brief Stops the Tx Cyclic Schedule.
* param[in] aEndSystemHandle The handle to the ES Device
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664TxCyclicStop( const A664EndSystemHandle aEndSystemHandle);

/**
* @brief Gets the current Minor frame time for the Tx Cyclic Schedule. This function should only be called
*        when the Tx Cyclic Schedule is stopped.
* param[in] aEndSystemHandle The handle to the ES Device
* param[out] aMinorFrameTime The currently configured Minor Frame Time
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664TxGetCyclicMinorFrameTime( const A664EndSystemHandle aEndSystemHandle, uint32_t* aMinorFrameTime);

/**
* @brief Sets the current Minor frame time for the Tx Cyclic Schedule. This function should only be called
*        when the Tx Cyclic Schedule is stopped.
* param[in] aEndSystemHandle The handle to the ES Device
* param[out] aMinorFrameTime The currently configured Minor Frame Time
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664TxSetCyclicMinorFrameTime( const A664EndSystemHandle aEndSystemHandle, uint32_t aMinorFrameTime);

/** 
 * @brief Sets the Mac Destination address for the specified port.  This is only valid on version 2 hardware.
 * param[in] aTxMessagePortHandle The handle tot he message port to modify
 * param[in] aTxMacDstAddr the Mac Destination address to be set
 * @return @link error Error Code@endlink
 **/
A664_API_FUNC a664TxSetMsgPortMacDst(const A664TxMessagePortHandle aTxMessagePortHandle, A664MacAddress* aTxMacDstAddr);

/**
* @brief Sends the Cyclic Common Queue data to the board.  If the Cyclic Common Queue is not running this will start it.
*    The Cyclic Common Queue can be used to send frames at set periodic times and this function will update the data on the board.
*    This call is only valid for V2 hardware.
* param[in] aEndSystemHandle The handle to the ES Device
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664TxCycComQueSend(const A664EndSystemHandle aEndSystemHandle);

/**
* @brief Sends the Cyclic Common Queue data to the board.
*    The Cyclic Common Queue can be used to send frames at set periodic times and this function will update the data on the board as necessary.
*    This call is only valid for V2 hardware.
* param[in] aEndSystemHandle The handle to the ES Device
* @param[in] aOptions Provides additional options that can be set on this function.
*   bit 0 - Start - Set this bit to Start the Cyclic Common Queue if it is not currently running.
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664TxCycComQueSendEx(const A664EndSystemHandle aEndSystemHandle, uint32_t aOptions);

/**
* @brief Stops the Cyclic Common Queue processing on the board.
*    This call is only valid for V2 hardware.
* param[in] aEndSystemHandle The handle to the ES Device
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664TxCycComQueStop(const A664EndSystemHandle aEndSystemHandle);

/**@}	(end defgroup a664ApiTxMessages)	*/

/**
* \defgroup a664ApiRxMessages A664 API Receive Functions
* @{
*
* @section Overview
* <p>
* This section contains the A664 Library functions that
* are used by the application program to perform Receiver/Read
* operations on the End System.
* </p>
*/

/** 
* @brief Reads the RX Common Queue off of the board and caches the frames in the API for the associated ports.
*   The RX Common Queue provides a way to move multiple frames across the PCIe bus in a single DMA transfer decreasing overhead.
* @param[in] aEndSystemHandle The handle to the associated End System device
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664RxReadCommQueue(const A664EndSystemHandle aEndSystemHandle);

/** 
* @brief General Container for Rx Message Port Handle
**/
typedef void* A664RxMessagePortHandle;

/** 
* @brief Handle for an Rx COM_UDP type message port
**/
typedef struct a664RxComUdpHandle
{
	A664RxMessagePortHandle handle;
} A664RxComUdpHandle;

/** 
* @brief Opens an Rx COM_UDP type message port and returns a handle to be used for subsequent operations on the port
* @param[in] aEndSystemHandle The handle to the associated End System device
* @param[in] aPortId The ID of the Port to be opened as defined in the End System Configuration. Valid values are 0 - 4095.
* @param[out] aRxComUdpHandle The handle to the associated Rx COM_UDP port.
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664RxComUdpOpen(const A664EndSystemHandle aEndSystemHandle, const uint32_t aPortId,
							   A664RxComUdpHandle* aRxComUdpHandle);

/** 
* @brief Opens an Rx COM_UDP type message port and returns a handle to be used for subsequent operations on the port.  This function is only available for the V2 hardware.
* @param[in] aEndSystemHandle The handle to the associated End System device
* @param[in] aPortId The ID of the Port to be opened as defined in the End System Configuration. Valid values are 0 - 4095.
* @param[in] aOptions This provides different options available for this call, unused bits should be cleared.
*  Bit 31 - Set this bit to use the RX Common Queue for this port.  The function a664RxReadCommQueue() must be called before port reads using the RX Common Queue.
* @param[out] aRxComUdpHandle The handle to the associated Rx COM_UDP port.
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664RxComUdpOpenEx(const A664EndSystemHandle aEndSystemHandle, const uint32_t aPortId,
							   const uint32_t aOptions, A664RxComUdpHandle* aRxComUdpHandle);

/** 
* @brief Closes a COM_UDP Rx Message port and releases the port handle
* @param[in] aRxComUdpHandle The handle to the associated Rx COM_UDP port.
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664RxComUdpClose(const A664RxComUdpHandle aRxComUdpHandle);

/** 
* @brief Reads a message from an Rx COM_UDP message port
* @param[in] aRxComUdpHandle The handle to the associated Rx COM_UDP port.
* @param[in] aMaxDataBytes The maximum number of data bytes that can be read. This is the size of the 
*                          buffer allocated by the application to store the read data (pointed to by aRxComUdpDataBuffer)
* @param[in] aRxComUdpDataBuffer Pointer to the data buffer that is to hold the read message port data. The data stored
*                                in this buffer will be the UDP payload data.
* @param[out] aBytesRead The actual number of message payload bytes read from the port.
* @param[out] aNetwork The channel (network) from which the data was received.
* @param[out] aTime The time at which the message was received
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664RxComUdpRead(const A664RxComUdpHandle aRxComUdpHandle, const uint16_t aMaxDataBytes,
							   void* aRxComUdpDataBuffer, uint16_t* aBytesRead, A664NetworkInterface* aNetwork,
							   A664Timestamp* aTime);

/** 
* @brief Handle for an Rx SAP_UDP type message port
**/
typedef struct a664RxSapUdpHandle
{
	A664RxMessagePortHandle handle;
} A664RxSapUdpHandle;

/** 
* @brief Opens an Rx SAP_UDP type message port and returns a handle to be used for subsequent operations on the port
* @param[in] aEndSystemHandle The handle to the associated End System device
* @param[in] aPortId The ID of the Port to be opened as defined in the End System Configuration. Valid values are 0 - 4095.
* @param[out] aRxSapUdpHandle The handle to the associated Rx SAP_UDP port.
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664RxSapUdpOpen(const A664EndSystemHandle aEndSystemHandle, const uint32_t aPortId,
							   A664RxSapUdpHandle* aRxSapUdpHandle);

/** 
* @brief Opens an Rx SAP_UDP type message port and returns a handle to be used for subsequent operations on the port.  This function is only available for V2 hardware.
* @param[in] aEndSystemHandle The handle to the associated End System device
* @param[in] aPortId The ID of the Port to be opened as defined in the End System Configuration. Valid values are 0 - 4095.
* @param[in] aOptions This provides different options available for this call, unused bits should be cleared.
*  Bit 31 - Set this bit to use the RX Common Queue for this port.  The function a664RxReadCommQueue() must be called before port reads using the RX Common Queue.
* @param[out] aRxSapUdpHandle The handle to the associated Rx SAP_UDP port.
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664RxSapUdpOpenEx(const A664EndSystemHandle aEndSystemHandle, const uint32_t aPortId,
							   const uint32_t aOptions, A664RxSapUdpHandle* aRxSapUdpHandle);

/** 
* @brief Closes a SAP_UDP Rx Message port and releases the port handle
* @param[in] aRxSapUdpHandle The handle to the associated Rx SAP_UDP port.
* @return @link error Error Code@endlink
**/
A664_API_FUNC  a664RxSapUdpClose(const A664RxSapUdpHandle aRxSapUdpHandle);

/** 
* @brief Reads a message from an Rx SAP_UDP message port
* @param[in] aRxSapUdpHandle The handle to the associated Rx SAP_UDP port.
* @param[in] aMaxDataBytes The maximum number of data bytes that can be read. This is the size of the 
*                          buffer allocated by the application to store the read data (pointed to by aRxSapUdpDataBuffer)
* @param[in] aRxSapUdpDataBuffer Pointer to the data buffer that is to hold the read message port data. The data stored in
*                                this buffer will be the UDP payload data.
* @param[out] aBytesRead The actual number of message payload bytes read from the port.
* @param[out] aNetwork The channel (network) from which the data was received.
* @param[out] aIpSourceAddress The IP Source address of the read message.
* @param[out] aUdpSourcePort The UDP Source port of the read message.
* @param[out] aTime The time at which the message was received
* @return @link error Error Code@endlink
**/
A664_API_FUNC  a664RxSapUdpRead(const A664RxSapUdpHandle aRxSapUdpHandle, const uint16_t aMaxDataBytes,
							    void* aRxSapUdpDataBuffer, uint16_t* aBytesRead, A664NetworkInterface* aNetwork ,
								A664IpAddress* aIpSourceAddress, A664UdpAddress* aUdpSourcePort,
								A664Timestamp* aTime);

/** 
* UNDOCUMENTED FUNCTION
* Changes the destination UDP port and clears out the queue.
* param[in] aRxSapUdpHandle The handle to the associated Rx SAP_UDP port.
* param[out] aUdpDestPort The UDP destination port to be set.
* returns A664_API_OK upon successful completion.
**/
A664_API_FUNC  a664RxSapUdpChgDestPort(	const A664RxSapUdpHandle		aRxSapUdpHandle,
									   A664UdpAddress					aUdpDestPort);

/** 
* @brief Handle for an Rx SAP_IP type message port
**/
typedef struct a664RxSapIpHandle
{
	A664RxMessagePortHandle handle;
} A664RxSapIpHandle;

/** 
* @brief Opens an Rx SAP_IP type message port and returns a handle to be used for subsequent operations on the port
* @param[in] aEndSystemHandle The handle to the associated End System device
* @param[in] aPortId The ID of the Port to be opened as defined in the End System Configuration. Valid values are 0 - 4095.
* @param[out] aRxSapIpHandle The handle to the associated Rx SAP_IP port.
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664RxSapIpOpen(const A664EndSystemHandle aEndSystemHandle, const uint32_t aPortId,
							  A664RxSapIpHandle* aRxSapIpHandle);

/** 
* @brief Opens an Rx SAP_IP type message port and returns a handle to be used for subsequent operations on the port.  This function is only available for V2 hardware.
* @param[in] aEndSystemHandle The handle to the associated End System device
* @param[in] aPortId The ID of the Port to be opened as defined in the End System Configuration. Valid values are 0 - 4095.
* @param[in] aOptions This provides different options available for this call, unused bits should be cleared.
*  Bit 31 - Set this bit to use the RX Common Queue for this port.  The function a664RxReadCommQueue() must be called before port reads using the RX Common Queue.
* @param[out] aRxSapIpHandle The handle to the associated Rx SAP_IP port.
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664RxSapIpOpenEx(const A664EndSystemHandle aEndSystemHandle, const uint32_t aPortId,
							  const uint32_t aOptions, A664RxSapIpHandle* aRxSapIpHandle);

/** 
* @brief Closes a SAP_IP Rx Message port and releases the port handle
* @param[in] aRxSapIpHandle The handle to the associated Rx SAP_IP port.
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664RxSapIpClose(const A664RxSapIpHandle aRxSapIpHandle);

/** 
* @brief Reads a message from an Rx SAP_IP message port
* @param[in] aRxSapIpHandle The handle to the associated Rx SAP_IP port.
* @param[in] aMaxDataBytes The maximum number of data bytes that can be read. This is the size of the 
*                          buffer allocated by the application to store the read data (pointed to by aRxSapIpDataBuffer)
* @param[in] aRxSapIpDataBuffer Pointer to the data buffer that is to hold the read message port data. The data stored in
*                               this buffer will be the IP Packet Payload.
* @param[out] aBytesRead The actual number of message payload bytes read from the port.
* @param[out] aNetwork The channel (network) from which the data was received.
* @param[out] aIpSourceAddress The IP Source address of the read message.
* @param[out] aTime The time at which the message was received
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664RxSapIpRead(const A664RxSapIpHandle aRxSapIpHandle, const uint16_t aMaxDataBytes ,
							  void* aRxSapIpDataBuffer, uint16_t* aBytesRead, A664NetworkInterface* aNetwork,
							  A664IpAddress* aIpSourceAddress, A664Timestamp* aTime);

/** 
* @brief Handle for an Rx SAP_MAC type message port
**/
typedef struct a664RxSapMacHandle
{
	A664RxMessagePortHandle handle;
} A664RxSapMacHandle;

/** 
* @brief Opens an Rx SAP_MAC type message port and returns a handle to be used for subsequent operations on the port
* @param[in] aEndSystemHandle The handle to the associated End System device
* @param[in] aPortId The ID of the Port to be opened as defined in the End System Configuration. Valid values are 0 - 4095.
* @param[out] aRxSapMacHandle The handle to the associated Rx SAP_MAC port.
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664RxSapMacOpen(const A664EndSystemHandle aEndSystemHandle, const uint32_t aPortId,
							   A664RxSapMacHandle* aRxSapMacHandle);

/** 
* @brief Opens an Rx SAP_MAC type message port and returns a handle to be used for subsequent operations on the port.  This function is only available for V2 hardware.
* @param[in] aEndSystemHandle The handle to the associated End System device
* @param[in] aPortId The ID of the Port to be opened as defined in the End System Configuration. Valid values are 0 - 4095.
* @param[in] aOptions This provides different options available for this call, unused bits should be cleared.
*  Bit 31 - Set this bit to use the RX Common Queue for this port.  The function a664RxReadCommQueue() must be called before port reads using the RX Common Queue.
* @param[out] aRxSapMacHandle The handle to the associated Rx SAP_MAC port.
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664RxSapMacOpenEx(const A664EndSystemHandle aEndSystemHandle, const uint32_t aPortId,
							   const uint32_t aOptions, A664RxSapMacHandle* aRxSapMacHandle);

/** 
* @brief Closes a SAP_MAC Rx Message port and releases the port handle
* @param[in] aRxSapMacHandle The handle to the associated Rx SAP_MAC port.
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664RxSapMacClose(const A664RxSapMacHandle aRxSapMacHandle);

/** 
* @brief Reads a message from an Rx SAP_MAC message port
* @param[in] aRxSapMacHandle The handle to the associated Rx SAP_MAC port.
* @param[in] aMaxDataBytes The maximum number of data bytes that can be read. This is the size of the 
*                          buffer allocated by the application to store the read data (pointed to by aRxSapMacDataBuffer)
* @param[in] aRxSapMacDataBuffer Pointer to the data buffer that is to hold the read message port data. The data stored
*                                in this buffer will be the MAC Frame payload data (Does not include the MAC header,
*                                VL Sequence Number or MAC CRC).
* @param[out] aBytesRead The actual number of message payload bytes read from the port.
* @param[out] aNetwork The channel (network) from which the data was received
* @param[out] aTime The time at which the frame was received
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664RxSapMacRead(const A664RxSapMacHandle aRxSapMacHandle, const uint16_t aMaxDataBytes,
							   void* aRxSapMacDataBuffer, uint16_t* aBytesRead, A664NetworkInterface* aNetwork,
							   A664Timestamp* aTime);

/** 
* @brief Handle for an Rx COTS_MAC type message port
**/
typedef struct a664RxCotsMacHandle
{
	A664RxMessagePortHandle handle;
} A664RxCotsMacHandle;

/** 
* @brief Opens an Rx COTS_MAC type message port and returns a handle to be used for subsequent operations on the port
* @param[in] aEndSystemHandle The handle to the associated End System device
* @param[in] aPortId The ID of the Port to be opened as defined in the End System Configuration. Valid values are 0 - 31.
* @param[out] aRxCotsMacHandle The handle to the associated Rx COTS_MAC port.
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664RxCotsMacOpen(const A664EndSystemHandle aEndSystemHandle, const uint32_t aPortId,
								A664RxCotsMacHandle* aRxCotsMacHandle);

/** 
* @brief Closes a COTS_MAC Rx Message port and releases the port handle
* @param[in] aRxCotsMacHandle The handle to the associated Rx COTS_MAC port.
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664RxCotsMacClose(const A664RxCotsMacHandle aRxCotsMacHandle);

/** 
* @brief Reads a message from an Rx COTS_MAC message port
* @param[in] aRxCotsMacHandle The handle to the associated Rx COTS_MAC port.
* @param[in] aMaxDataBytes The maximum number of data bytes that can be read. This is the size of the 
*                          buffer allocated by the application to store the read data (pointed to by aRxCotsMacDataBuffer)
* @param[in] aRxCotsMacDataBuffer Pointer to the data buffer that is to hold the read message port data. The data stored in 
*                                 this buffer will be the entire MAC frame (excluding the 4 byte MAC CRC).
* @param[out] aBytesRead The actual number of message payload bytes read from the port.
* @param[out] aNetwork The channel (network) from which the data was received.
* @param[out] aTime The time at which the frame was received
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664RxCotsMacRead(const A664RxCotsMacHandle aRxCotsMacHandle, const uint16_t aMaxDataBytes,
							    void* aRxCotsMacDataBuffer, uint16_t* aBytesRead, A664NetworkInterface* aNetwork,
								A664Timestamp* aTime);

/** 
* @brief Handle for a Loopback type message port
**/
typedef struct a664RxLoopbackHandle
{
	A664RxMessagePortHandle handle;
} A664RxLoopbackHandle;

typedef struct a664RxLoopbackError
{
#ifndef __VXWORKS__
	/** 
	* @brief Start of Frame Error (e.g. invalid preamble)
	**/
	unsigned int mSofError				: 1;
	/** 
	* @brief Frame Size Error (smaller than 64 or larger than 2047)
	**/
	unsigned int mFrameSizeError		: 1;
	/** 
	* @brief Alignment Error (symbols not coming in at correct intervals)
	**/
	unsigned int mAlignmentError		: 1;
	/**
	* @brief MII Error (the TX MAC aborted the transmission)
	**/
	unsigned int mMiiError				: 1;
	/**
	* @Brief CRC Error (the final checksum is not correct)
	**/
	unsigned int mCrcError				: 1;
	unsigned int mReserved				: 27;
#else
	unsigned int mReserved				: 27;
	unsigned int mCrcError				: 1;
	unsigned int mMiiError				: 1;
	unsigned int mAlignmentError		: 1;
	unsigned int mFrameSizeError		: 1;
	unsigned int mSofError				: 1;
#endif
} A664RxLoopbackError;

/** 
* @brief Opens a Loopback type message port and returns a handle to be used for subsequent operations on the port
* @param[in] aEndSystemHandle The handle to the associated End System device
* @param[in] aNetwork The the network of the loopback port to open.
* @param[out] aLoopbackHandle The handle to the associated Loopback port.
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664RxLoopbackOpen(const A664EndSystemHandle aEndSystemHandle, A664NetworkInterface aNetwork,
								A664RxLoopbackHandle* aLoopbackHandle);

/** 
* @brief Closes a Loopback Message port and releases the port handle
* @param[in] aLoopbackHandle The handle to the associated Loopback port.
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664RxLoopbackClose(const A664RxLoopbackHandle aLoopbackHandle);

/** 
* @brief Reads a message from an Rx Loopback message port
* @param[in] aLoopbackHandle The handle to the associated Loopback port.
* @param[in] aMaxDataBytes The maximum number of data bytes that can be read. This is the size of the 
*                          buffer allocated by the application to store the read data (pointed to by aLoopbackDataBuffer)
* @param[in] aLoopbackDataBuffer Pointer to the data buffer that is to hold the read message port data. The data stored in 
*                                 this buffer will be the entire MAC frame (excluding the 4 byte MAC CRC).
* @param[out] aBytesRead The actual number of message payload bytes read from the port.
* @param[out] aLoopbackError Error information for the port.
* @param[out] aTime The time at which the frame was received
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664RxLoopbackRead(const A664RxLoopbackHandle aLoopbackHandle, const uint16_t aMaxDataBytes,
								void* aLoopbackDataBuffer, uint16_t* aBytesRead, A664Timestamp* aTime,
								A664RxLoopbackError* aLoopbackError);

/** 
* @brief Resets the monitor pointer so the next monitor read will start with the next frame received. Starts the monitor on Dual Channel Ethernet hardware.
* This function is only available on AIT's hardware.
* @param[in] aEndSystemHandle The handle to the associated End System device
* @param[in] aNetwork The network of the monitor to reset.
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664RxMonitorReset(const A664EndSystemHandle aEndSystemHandle, A664NetworkInterface aNetwork);

/** 
* @brief Stops the monitor.
* This function is only available on Dual Channel Ethernet hardware.
* @param[in] aEndSystemHandle The handle to the associated End System device
* @param[in] aNetwork The network of the monitor to stop.
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664RxMonitorStop(const A664EndSystemHandle aEndSystemHandle, A664NetworkInterface aNetwork);

/** 
* @brief Reads a block of data from the Rx Monitor.  The data is returned in the firmware's monitor format.
*			The returned data may end in the middle of a frame, the next read will start where the last read left off.
*			This function is only valid on AIT hardware.
* @param[in] aEndSystemHandle The handle to the associated End System device
* @param[in] aNetwork The network of the monitor to read.
* @param[in] aMaxDataBytes The maximum number of data bytes that can be read. This is the size of the 
*                          buffer allocated by the application to store the read data (pointed to by aDataBuffer).
*							Efficiency will peak at 64KB.
* @param[in] aDataBuffer Pointer to the data buffer that is to hold the read monitor data. The data stored in 
*                         this buffer will be in the firmware's monitor format.  This buffer needs to be aligned to start on a 32 bit address.
* @param[out] aBytesRead The actual number of bytes read from the port.  This will be a multiple of 16 bytes.
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664RxMonitorRead(const A664EndSystemHandle aEndSystemHandle, A664NetworkInterface aNetwork, 
								const uint32_t aMaxDataBytes, void* aDataBuffer, uint32_t* aBytesRead);

/** 
* @brief Status information for a Receive VL
**/
typedef struct  
{
	/** 
	* @brief Count of the number of frames that have been discarded by Redundancy Management due to the VL
	*        sequence number being outside of the acceptable range.
	**/
	uint32_t rmFailCount;
	/** 
	* @brief Count of the number of frames on the VL that have failed integrity checking on network interface A
	**/
	uint32_t icFailNetworkACount;
	/** 
	* @brief Count of the number of frames on the VL that have failed integrity checking on network interface B
	**/
	uint32_t icFailNetworkBCount;
} A664RxVLStatus;

/** 
* @brief Gets status information for an Rx Virtual Link.  The counters rmFailCount,
* icFailNetworkACount, and icFailNetworkBCount are reset to zero at power-on and
* whenever this function is invoked.  Also, none of these counters wrap-around.  This is only valid for the V1 board.
* @param[in] aEndSystemHandle The handle to the End System Device
* @param[in] aVLId The Virtual Link ID
* @param[out] aRxVLStatus The VL Status Information
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664RxGetVLStatus(const A664EndSystemHandle aEndSystemHandle, const uint16_t aVLId,
								A664RxVLStatus* aRxVLStatus);

/** 
* @brief Status information for a Receive VL
**/
typedef struct  
{
	/** 
	* @brief The VL ID.
	**/
	uint16_t mVLID;
	/** 
	* @brief Count of the frames that have been received on the specified network before IC and RM.
	**/
	uint32_t mNetCountA;
	/** 
	* @brief Count of the frames that have been received on the specified network before IC and RM.
	**/
	uint32_t mNetCountB;
	/** 
	* @brief Count of the number of frames that have been discarded by Redundancy Management due to the VL
	*        sequence number being outside of the acceptable range.
	**/
	uint32_t mRmFailCountA;
	/** 
	* @brief Count of the number of frames that have been discarded by Redundancy Management due to the VL
	*        sequence number being outside of the acceptable range.
	**/
	uint32_t mRmFailCountB;
	/** 
	* @brief Count of the number of frames on the VL that have failed integrity checking on network interface A
	**/
	uint32_t mIcFailCountA;
	/** 
	* @brief Count of the number of frames on the VL that have failed integrity checking on network interface B
	**/
	uint32_t mIcFailCountB;
} A664RxVLCounters;

/** 
* @brief Retrieves the VL Index of the given VLID.
* @param[in] aEndSystemHandle The handle to the End System Device
* @param[in] aVlId The Virtual Link ID
* @param[out] aVlIndex The Virtual Link index
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664RxGetVLIndex(const A664EndSystemHandle aEndSystemHandle, const uint16_t aVlId, uint16_t* aVlIndex);

/** 
* @brief Gets the counters for an Rx Virtual Link.  This is only valid for the V2 board.
* @param[in] aEndSystemHandle The handle to the End System Device
* @param[in] aVlIndex The Virtual Link index
* @param[out] aRxVlCounters The Rx VL counters
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664RxGetVLCounters(const A664EndSystemHandle aEndSystemHandle, const uint16_t aVlIndex,
								A664RxVLCounters* aRxVlCounters);

/** 
* @brief Resets the counters for an Rx Virtual Link.  This is only valid for the V2 board.
* @param[in] aEndSystemHandle The handle to the End System Device
* @param[in] aVlIndex The Virtual Link index
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664RxResetVLCounters(const A664EndSystemHandle aEndSystemHandle, const uint16_t aVIndex);

/** 
* @brief Rx UDP Layer Status Information
**/
typedef struct  
{
	/** 
	* @brief Count of the total number of messages processed by the Rx UDP Layer
	*        inlcudes both valid and invalid message processed
	**/
	uint32_t    mTotalMessageCount;
	/** 
	* @brief Count of the total number of invalid messages processed by the Rx UDP Layer
	*        A message may be counted as invalid if for instance it does not have a valid
	*        UDP CRC or UDP Length field
	**/
	uint32_t    mInvalidMessageCount;
	/** 
	* @brief Count of the total number of messages received at the UDP layer for which no
	*        configured message port is defined to receive.
	**/
	uint32_t    mNoPortCount;
} A664RxUdpStatus;

/** 
* @brief Gets the status information for the Rx UDP Protocol Layer
* @param[in] aEndSystemHandle The handle to the End System Device
* @param[out] aRxUdpStatus The structure containing the Rx UDP Layer Status Information
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664RxGetUdpStatus(const A664EndSystemHandle aEndSystemHandle, A664RxUdpStatus* aRxUdpStatus);

/** 
* @brief The Rx IP Protocol Layer status information
**/
typedef struct  
{
	/** 
	* @brief The total number of IP packets processed. Includes both valid and invalid packets
	**/
	uint32_t    mTotalPacketCount;
	/** 
	* @brief The total number of IP packet errors detected. Errors can be due to 
	*        badly formed packets, IP Checksum errors, etc.
	**/
	uint32_t    mPacketErrorCount;
	/** 
	* @brief The total number of IP packets that have been detected to have invalid IP Checksums
	**/
	uint32_t    mChecksumErrorCount;
	/** 
	* @brief The total number of IP packets that have been detected to have an unknown IP protocol. Only
	*        packets with protocol indicating UDP (17) or ICMP (1) are considered valid.
	**/
	uint32_t    mUnknownProtocolCount;
	/** 
	* @brief The total number of IP packets that have been discarded due to either detected errors
	*        or due to unavailable resorces in the IP layer
	**/
	uint32_t    mDiscardCount;
	/** 
	* @brief The total number of IP Reassembly errors that have occured in the IP layer. Reasembly errors
	*        can occur for instance if fragments are received out of order or with invalid fragment offsets
	**/
	uint32_t    mReassemblyErrorCount;
	/** 
	* @brief The total number of fragmented IP packets that are not processed (dropped) due to no resources
	*        available in the IP layer for processing the reassembly
	**/
	uint32_t    mReassemblyNoResourcesCount;
} A664RxIpStatus;

/** 
* @brief Gets the status information for the Rx IP Protocol Layer
* @param[in] aEndSystemHandle The handle to the End System Device
* @param[out] aRxIpStatus The structure containing the Rx IP Layer Status Information
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664RxGetIpStatus(const A664EndSystemHandle aEndSystemHandle, A664RxIpStatus* aRxIpStatus);

/** 
* @brief Specifier of Rx Message Port Type
**/
typedef enum
{
	/** 
	* @brief Disabled Rx Message Port
	**/
	A664_RX_DISABLED         = 0,
	/** 
	* @brief SAP_UDP Type Rx Message Port
	**/
	A664_RX_SAP_UDP          = 1,
	/** 
	* @brief SAP_IP Type Rx Message Port
	**/
	A664_RX_SAP_IP           = 2,
	/** 
	* @brief SAP_MAC Type Rx Message Port
	**/
	A664_RX_SAP_MAC          = 3,
	/** 
	* @brief COM_UDP (Sampling) Type Rx Message Port
	**/
	A664_RX_COM_UDP_SAMPLING = 4,
	/** 
	* @brief COM_UDP (Queuing) Type Rx Message Port
	**/
	A664_RX_COM_UDP_QUEUING  = 5,
	/**
	* @brief Loopback Port 
	**/
	A664_API_PORT_LOOPBACK = 6,
	/** 
	* @brief COTS_MAC Type Rx Message Port
	**/
	A664_RX_COTS_MAC         = 7,
	/** 
	* @brief EDE COM_UDP (Sampling) Type Rx Message Port
	**/
	A664_RX_EDE_COM_UDP_SAMPLING = 10,
	/** 
	* @brief EDE COM_UDP (Queuing) Type Rx Message Port
	**/
	A664_RX_EDE_COM_UDP_QUEUING  = 11
} A664RxMessagePortType;

/** 
* @brief Rx Message Port Control Data
**/

typedef struct 
{
#ifndef __VXWORKS__
	/** 
	* @brief Enables (True) or Disables (False) Events on invalid messages received at the message port
	**/
	unsigned int mInvalidMessageEventEnable		: 1;
	/** 
	* @brief Enables (True) or Disables (False) Events on message port buffer overflows for the message port. 
	*        Port buffer overflow events occur when incoming message cannot be delivered to the message port due to a full buffer.
	**/
	unsigned int mBufferOverflowEventEnable		: 1;
	/** 
	* @brief Enables (True) or Disables (False) Events on valid messages received to the message port
	**/
	unsigned int mMessageReceivedEventEnable	: 1;
	unsigned int mReserved						: 28;
	/** 
	* @brief Enables (True) or Disables (False) the message port for receiving messages
	**/
	unsigned int mMessagePortEnable				: 1;
#else
	unsigned int mMessagePortEnable				: 1;
	unsigned int mReserved						: 28;
	unsigned int mMessageReceivedEventEnable	: 1;
	unsigned int mBufferOverflowEventEnable		: 1;
	unsigned int mInvalidMessageEventEnable		: 1;
#endif
} A664RxMessagePortControl;
/** 
* @brief Sets the control settings for a Rx Message Port
* @param[in] aRxMessagePortHandle The handle of the Rx Message Port for which the control settings
*            shall be set
* @param[in] apRxMessagePortControl The structure containing the Rx Message Port control settings
* @return @link error Error Code @endlink
**/
A664_API_FUNC a664RxSetMessagePortControl(const A664RxMessagePortHandle aRxMessagePortHandle, A664RxMessagePortControl* apRxMessagePortControl);

/** 
* @brief Rx Message Port Status Information
**/
typedef struct  
{
	/** 
	* @brief The type of Rx Message Port
	**/
	A664RxMessagePortType   mRxMessagePortType;
	/**
	* @brief The Port ID
	**/
	uint32_t			mPortId;
	/** 
	* @brief The ES Index
	**/
	uint32_t			mEsIndex;
	/** 
	* @brief Count of valid messages received at the Rx Message Port
	**/
	uint32_t                mValidMessageCount;
	/** 
	* @brief Count of invalid messages destined the Rx Message Port but
	*         no delivered due to being invalid
	**/
	uint32_t                mInvalidMessageCount;
	/** 
	* @brief Count of valid messages not delivered to the Rx Message Port
	*         due to no available space in the port's buffer queue
	**/
	uint32_t                mNoBufferAvailableErrorCount;
	/**
	* @brief Number of full buffers in the queue
	**/
	uint16_t				mNumFullBuffers;
	/** 
	* @brief Number of empty buffers in the queue
	**/
	uint16_t				mNumEmptyBuffers;
	/** 
	* @brief Indicates the control bits for the port
	**/
	A664RxMessagePortControl	mMessagePortControl;
	
} A664RxMessagePortStatus;

/** 
* @brief Gets the status information for an Rx Message Port
* @param[in] aRxMessagePortHandle The handle to the associated Rx Message Port
* @param[out] aRxMessagePortStatus The structure containing the Rx Message Port Status Information
* @return @link error Error Code @endlink
**/
A664_API_FUNC a664RxGetMessagePortStatus(const A664RxMessagePortHandle aRxMessagePortHandle, A664RxMessagePortStatus* aRxMessagePortStatus);

/** 
* @brief Gets the number of full buffers for an Rx Message Port
* @param[in] aRxMessagePortHandle The handle to the associated Rx Message Port
* @param[out] aNumFullBuff Returns the number of full buffers
* @return @link error Error Code @endlink
**/
A664_API_FUNC a664RxGetMsgPortNumFullBuf(const A664RxMessagePortHandle aRxMessagePortHandle, uint32_t* aNumFullBuff);

/** 
* @brief Indicates if the RX Processor is loaded down and falling behind.  This function is only available on the Version 2 hardware.
* @param[in] aEndSystemHandle The handle to the End System Device
* @param[out] aIsBehind Returns 1 if the RX Processor is falling behind, 0 if the RX Processor is keeping up.
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664RxIsBehind(const A664EndSystemHandle aEndSystemHandle, uint32_t* aIsBehind);

/**
* UNDOCUMENTED FUNCTION
* brief Extracts a device configuration from a End System Configuration
* param[in] apEndSystemConfig The combined configuration hex data
* param[in] aDeviceType The device type of the configuration to be returned
* param[out] apConfigBufer The buffer for the configuration to be placed in
* param[in] aBufferLength The length of the user buffer provided in bytes
* return link error Error Code endlink
**/
A664_API_FUNC a664ESExtractDevice(	const void*	apEndSystemConfig, 
									uint8_t		aDeviceType, 
									void*		apConfigBufer, 
									uint32_t	aBufferLength);

/**@}	(end defgroup a664ApiRxMessages)	*/

/**
* \defgroup a664ApiVlStats A664 API VL Statistics Functions
* @{
*
* @section sec_oview Overview
* <p>
* This section contains the A664 Library Statistics Functions
* </p>
*
*/

/**
* @brief ARINC664 UDP Statistics
**/
typedef struct
{
	/**
	* @brief UDP Port address of Src/Dst table entry
	**/
	uint32_t mUdpPort;
	
	/**
	* @brief Number of frames for this UDP Port
	**/
	uint32_t mFrameCount;

	/**
	* @brief Last UDP frame time stamp
	**/
	A664Timestamp mLastTimeStamp;

} A664UdpStats;

/**
* @brief ARINC664 IP Statistics
**/
typedef struct
{
	/**
	* @brief IP address of Src/Dst table entry
	**/
	uint32_t mIpAddress;

	/**
	* @brief Number of Frames for this IP Address
	**/
	uint32_t mFrameCount;
	
	/**
	* @brief Last frame time stamp
	**/
	A664Timestamp mLastTimeStamp;
	
	/**
	* @brief Number of UDP ports recorded on this IP address
	**/
	uint32_t mNumUdpEntries;
	
	/**
	* @brief RESERVED
	**/
	uint32_t mReserved;
	
	/**
	* @brief Table of UDP port statistics for this IP address
	**/
	A664UdpStats mUdpTable[64];
	
} A664IpStats;

/**
* @brief ARINC664 VL Statistics
**/
typedef struct
{
	
	/**
	* @brief The VL ID of this table
	**/
	uint16_t mVlId;

	/**
	* @brief The VL's Source MAC address, High 16 bits
	**/
	uint16_t mMacDstHi;

	/**
	* @brief The VL's Source MAC address, Low Word
	**/
	uint32_t mMacDstLow;

	/**
	* @brief The VL's Source MAC address, High 16 bits
	**/
	uint16_t mMacSrcHi;

	/**
	* @brief The VL's Source MAC address, Low Word
	**/
	uint32_t mMacSrcLow;

	/**
	* @brief Last frame time stamp
	**/
	A664Timestamp mLastTimeStamp;

	/**
	* @brief Number of Frames on VL
	**/
	uint32_t mFrameCount;

	/**
	* @brief Largest Frame on VL
	**/
	uint32_t mMaxFrameSize;

	/**
	* @brief Source IP Statistics Table
	**/
	A664IpStats mIpSrcTable[16];

	/**
	* @brief Destination IP Statistics Table
	**/
	A664IpStats mIpDstTable[16];

	/**
	* @brief Valid number of Entries in Source IP Table
	**/
	uint32_t mNumIpSrcEntries;

	/**
	* @brief Valid number of Entries in Destination IP Table
	**/
	uint32_t mNumIpDstEntries;
} A664VlStats;


/**
* @brief ARINC664 Statistics
**/
typedef struct
{
	/**
	* @brief Number of frames received on this network that are not valid VL
	**/
	uint32_t mFrameCountOther;
	
	/**
	* @brief Number of valid VLs in the Stats table
	**/
	uint32_t mNumVls;

	/**
	* @brief VL stats table
	**/
	A664VlStats mNetVlStats[128];

}A664Stats;

/**
* @brief VL Stats Lookup Table
**/
typedef struct
{
	/**
	* @brief VL Frame Count Table
	*/
	uint16_t mVlFrameCount[65536];

	/**
	* @brief VL Stats Enable/Disable table
	*/
	uint8_t mVlEnable[65536];

	/**
	* @brief VL lookup table converts VL ID to an index into the VL Stats table.
	**/
	uint8_t mVlLookupIdx[65536];

}A664VlLookup;


/**
* @brief Starts the VL Network Statistics - Only Valid on AIT Hardware
* @param[in] aEndSystemHandle The handle to the ES Device
* @param[in] aNetworkPort ES Device Port
**/
A664_API_FUNC a664RxStartStatistics(
								const A664EndSystemHandle aEndSystemHandle,
								const A664NetworkInterface aNetworkPort);
/**
* @brief Starts the VL Network Statistics - Only Valid on AIT Hardware
* @param[in] aEndSystemHandle The handle to the ES Device
* @param[in] aNetworkPort ES Device Port
* @param[out] Boolean indicator if stats are running
**/
A664_API_FUNC a664RxStatisticsGetState(
		const A664EndSystemHandle aEndSystemHandle, 
		const A664NetworkInterface aNetworkPort, 
		uint8_t* aIsRunning);

/**
* @brief Stop the VL Network Statistics - Only Valid on AIT Hardware
* @param[in] aEndSystemHandle The handle to the ES Device
* @param[in] aNetworkPort ES Device Port
**/
A664_API_FUNC a664RxStopStatistics(const A664EndSystemHandle aEndSystemHandle,
								   const A664NetworkInterface aNetworkPort);

/**
* @brief Retrieve all VL statistics for this network - Only Valid on AIT Hardware
* @param[in] aEndSystemHandle The handle to the ES Device
* @param[in] aNetworkPort ES Device Port
* @param[out] Pointer to A664Stats struct to fill.
**/
A664_API_FUNC a664RxGetStatistics(const A664EndSystemHandle aEndSystemHandle,
								   const A664NetworkInterface aNetworkPort,
								   A664Stats* aA664StatsOut);
/**
* @brief Retrieve the VL statistics for the specified VL ID - Only Valid on AIT Hardware
* @param[in] aEndSystemHandle The handle to the ES Device
* @param[in] aNetworkPort ES Device Port
* @param[in] VL ID to retrieve stats for.
* @param[out] Pointer to A664VlStats struct to fill.
**/
A664_API_FUNC a664RxGetVlStatistics(const A664EndSystemHandle aEndSystemHandle,
								   const A664NetworkInterface aNetworkPort,
								   uint16_t aVlId, 
								   A664VlStats* aVlStatsOut);

/**
* @brief Retrieve the VL lookup table for specified network  - Only Valid on AIT Hardware
* @param[in] aEndSystemHandle The handle to the ES Device
* @param[in] aNetworkPort ES Device Port
* @param[out] Pointer to A664VlLookup struct to fill.
**/
A664_API_FUNC a664RxGetVlLookup(const A664EndSystemHandle aEndSystemHandle,
								   const A664NetworkInterface aNetworkPort,
								   A664VlLookup* aVlLookupOut);
/**
* @brief Save the VL lookup table for specified network  - Only Valid on AIT Hardware
* This allows you to specifically disable statisitcs for certain VL IDs
* Statistics cannot be running for this function to work.  Otherwise it will 
* return A664_RX_STATS_ENABLED.s
* @param[in] aEndSystemHandle The handle to the ES Device
* @param[in] aNetworkPort ES Device Port
* @param[in] Pointer to A664VlLookup struct to save to the card.
**/
A664_API_FUNC a664RxSetVlLookup(const A664EndSystemHandle aEndSystemHandle,
								   const A664NetworkInterface aNetworkPort,
								   A664VlLookup* aVlLookupIn);

/**@}	(end defgroup a664ApiVlStats)	*/

#endif /* A664_API_H */


