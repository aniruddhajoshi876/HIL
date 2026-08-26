/*
*   Copyright:      n/a
*   Description:    This file includes the forward declarations of the S-Function interface file of the Speedgoat CAN driver library.
*   Version:        $Revision
*   Date:           $Date$
*   Modified by:    $Author$
*/

#ifndef __SGESD_SFUNCTION_INTERFACE_H__
#define __SGESD_SFUNCTION_INTERFACE_H__

#include "CANFD_Message_Definition.h"
#include "CAN_Message_Definition.h"

#include "IO602_IO691_CANStatus.h"
using namespace sg::esd;

#pragma endregion

#include <cstdio>
#include <exception>
#ifdef MATLAB_MEX_FILE
#include "simstruc.h"
#else
#include "../../common/libsg/sg_printf.h"
#endif

#ifdef DEBUG_PRINT  // Macro set in ESD project properties
// _DEBUG is defined by Visual C++, in Debug mode.
inline void sg_assert_fail(const char *file, int line, const char* msg)
{
	char message[512];
	std::sprintf(message, "ESD_ASSERT failed in line %d of %s: %s\n", line, file, msg);
	// in clean code, the forwarded exception should be also contain the message, but we don't want to rely on than and print it in Simulink or Simulink Target.
#ifdef MATLAB_MEX_FILE
	ssPrintf(message);
#else
	SG_PRINTF(ERROR, message);
#endif
	throw std::exception(message);
}
#define ESD_ASSERT(condition, message)  if (!(condition)) { sg_assert_fail(__FILE__, __LINE__, (message)); }
#else
#define ESD_ASSERT(condition, message)
#endif


namespace sg
{
	namespace esd
	{
		typedef struct ModuleInitData_T
		{
			double Module;   // module type as an integer, e.g. 691
			double Id;       // user-defined module id, integer
		} ModuleInitData;

		typedef struct EsdChannelValues_T
		{
			double IsChannelActive;
			struct { double brp, sjw, ts1, ts2; } brc[2]; // manual settings for CAN (idx 0) and CAN-FD (idx 1)

		} EsdChannelValues;

		typedef struct ModulePciInitValues_T
		{
			double Bus;
			double Slot;

		} ModulePciInitValues;

		typedef struct ChannelInitValues_T
		{
			double SampleTime;
			double Index;  // index beginning at 0, equals channel index in Mask of S-Function - 1 
			double messageType;
			double canType;  // 1 = CAN, 2 = CAN-FD
		} ChannelInitValues;

		// Initialization parameter vector used in Setup S-Function block
		typedef struct SetuptInitValues_T
		{
			ModuleInitData mid;
			ModulePciInitValues Pci;
			EsdChannelValues ChannelData[4];
		} SetupInitValues;

		// used in Read S-Function block
		typedef struct ReadInitValues_T
		{
			ModuleInitData mid;
			ChannelInitValues Channel;
		} ReadInitValues;

		// used in Write S-Function block
		typedef struct WriteInitValues_T
		{
			ModuleInitData mid;
			ChannelInitValues Channel;
			double enableStatusPort;
		} WriteInitValues;
	}

    namespace esdSFcn
    {
		enum PortType : int32_t {
			CAN = 0,
			CANFD = 1
		};	

		/* returns the module index, which is main ID to be used with DriverRoot object. */
		int32_t GetModuleIndexFromIdEx(int32_t, int32_t);
		int32_t GetModuleIndexEx(const ModuleInitData&);

		// check that driver root exists. Returns true if a module with given type and id was already registered.
        void Setup_ModelStart(const SetupInitValues&, const double*);
		void CheckOrCreateModule(const ModuleInitData&);
		bool IsStarted(int32_t);
		void StartAllChannelsEx(int32_t);
		void* GetBlockBufferEx(const WriteInitValues&);
		void* GetBlockBufferEx(int32_t, uint8_t);
		// returns 1 if message could be added to buffer
        int8_t AddMessageToBuffer(const WriteInitValues&, const CanFdMessage*, void *);
		void SendInitOrTermStructure(const SetupInitValues&, const double*);
		uint8_t GetMessageDataLengthByDlc(uint8_t);
		uint8_t GetMessageDlcByDataLength(uint8_t);
		// resets the list of buffers; after this any pointers to the send buffers become invalid.
		void DisableGlobalSender(int32_t);
		void Setup_ModelStop(const SetupInitValues&, const double*);
        void ReleaseSenderSemaphore(int32_t);
		void TerminateThread(int32_t);

		/** CANMsg*  pOut
		    return 1 if message was received, 0 otherwise */
        bool ReadCanMessage(const ReadInitValues&, CanFdMessage*);
		/* read out all messages without returning them */
		uint8_t EvaluateCanMessages(int32_t moduleIndex, uint8_t channelIndex);

		/* register Read block */
		void setModuleHasRead(const ReadInitValues&);
		/* is Read block present */
		bool getModuleHasRead(int32_t moduleIndex, uint8_t channelIndex);
		/* Read CAN status from controller with moduleIndex,  requestMask tells which status to read. */
		void UpdateCanStatus(int32_t moduleIndex, uint8_t channelIndex, uint32_t requestMask);
		CanStatus* GetCanStatus(int32_t moduleIndex, uint8_t channelIndex);
		void setModuleBusRecoveryMode(int32_t moduleIndex, uint8_t channelIndex, uint32_t CanStatus_BusRecoveryMode);
		void triggerModuleBusRecovery(int32_t moduleIndex, uint8_t channelIndex);
    }
}

#endif // !__SGESD_SFUNCTION_INTERFACE_H__
