/*
*   Copyright:      n/a
*   Description:    This file includes the forward declarations of the S-Function interface file of the Speedgoat CAN driver library.
*   Version:        $Revision
*   Date:           $Date$
*   Modified by:    $Author$
*/

#pragma once

#include "CANFD_Message_Definition.h"
#include "CAN_Message_Definition.h"
#include "LIN_Message_Definition.h"

#include <cstdio>
#include <exception>
#ifdef MATLAB_MEX_FILE
#include "simstruc.h"
#else
#include "sg_printf.h"
#include <sg_module_types.h>
#include <sg_common.h>
#include <sg_time.h>
#endif

namespace sg
{
    namespace ofa
    {
        typedef struct ModuleInitData_T
        {
            double Module; // module type as an integer
            double Id;     // user-defined module id, integer
        } ModuleInitData;

        typedef struct ChannelValues_T
        {
            double IsChannelActive; // 1. = Disabled, 2. = HS-CAN, 3. = CAN-FD, 4. = LS-CAN
            struct { double brp, sjw, ts1, ts2; } brc[2]; // manual settings for CAN (idx 0) and CAN-FD (idx 1)
        } ChannelValues;

        typedef struct LinChannelValues_T
        {
            double IsChannelActive; // 1. = Disabled, 2. = Slave, 3. = Master
            double bdr; // Baudrate
        } LinChannelValues;

        typedef struct ModulePciInitValues_T
        {
            double PciAutosearchPos;
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

        typedef struct LinChannelInitValues_T
        {
            double SampleTime;
            double Index;  // index beginning at 0, equals channel index in Mask of S-Function - 1 (for LIN and IO611: Index=2,3, for LIN and IO614: Index=4)
            double messageType; // 1 = LIN, 2 = RAW
            double isSlv; 
        } LinChannelInitValues;

        // Initialization parameter vector used in Setup S-Function block
        typedef struct SetupInitValues_T
        {
            ModuleInitData mid;
            ModulePciInitValues Pci;
            ChannelValues ChannelData[4];
            LinChannelValues LinChannelData[2];
        } SetupInitValues;

        typedef struct StatusParameters_T
        {
            double autoRecovery;
            double enableInput;
            double avgBusLoad;
            bool errBusOff;
            uint32_t busRecoveryCounter;
            bool dataOverrunTx;
            bool dataOverrunRx;
            bool errWarnLimit;
            bool errPassLimit;
        } CanStatus;

        // Initialization parameter vector used in Setup S-Function block
        typedef struct StatusInitValues_T
        {
            ModuleInitData mid;
            ChannelInitValues Channel;
            CanStatus pars;
        } StatusInitValues;

        // used in Read S-Function block
        typedef struct MessageIdentifyerData_T
        {
            double
                HasMulReadPlusOne,
                NumIDs,
                pIDs;
        } MessageIdentifyerData;

        // used in Read S-Function block
        typedef struct ReadInitValues_T
        {
            ModuleInitData mid;
            ChannelInitValues Channel;
            double enableInput;
            double useBusOutput;
            double useExtendedID;
            MessageIdentifyerData IDdat;
        } ReadInitValues;

        // used in Write S-Function block
        typedef struct WriteInitValues_T
        {
            ModuleInitData mid;
            ChannelInitValues Channel;
            double enableStatusPort;
            double numOfMsg;
            double hasTxCtrlInput;
            double useBusInput;
        } WriteInitValues;

        // used in Write S-Function block
        typedef struct LinWriteInitValues_T
        {
            ModuleInitData mid;
            LinChannelInitValues Channel;
            double protIdent;
            double dlc;
            double isEnhcdChksum;
            double inputEnableResponse;
        } LinWriteInitValues;

        // used in Write S-Function block
        typedef struct LinReadInitValues_T
        {
            ModuleInitData mid;
            LinChannelInitValues Channel;
            double protIdent;
            double dlc;
            double isEnhcdChksum;
            double enaUpdateState;
            double enaMsgType;
            double enaDataOverrun;
            double enaTimeStamp;
        } LinReadInitValues;

        typedef struct
        {
            union {
                CanFdMessage* canfd;
                CANMsg* can;
                LINMsg* lin;
            } msg;
            typedef enum {
                none = 0,
                can = 1,
                canfd = 2,
                lin = 3
            } Type;
            Type type;
        } SimMsgComp;

        void Setup_Load(const sg::ofa::SetupInitValues&);
        void Setup_Start(const sg::ofa::SetupInitValues&, const double*);
        void Setup_Stop(const sg::ofa::SetupInitValues&, const double*);
        void Setup_Exit(const sg::ofa::SetupInitValues&);

        void Setup_Step();
        void Read_Start(const sg::ofa::ReadInitValues&, size_t);
        bool Read_Step(const sg::ofa::ReadInitValues&, CanFdMessage*, uint8_t, size_t);
        void Read_Stop(const sg::ofa::ReadInitValues&, size_t);

        void Write_Start(const sg::ofa::WriteInitValues&, size_t);
        bool Write_Step(const sg::ofa::WriteInitValues&, sg::ofa::SimMsgComp, uint8_t, uint32_t, size_t);
        void Write_Stop(const sg::ofa::WriteInitValues&, size_t);

        sg::ofa::CanStatus* Status_Step(const StatusInitValues&, bool);

        void Lin_Read_Start(const sg::ofa::LinReadInitValues&, size_t);
        bool Lin_Read_Step(const sg::ofa::LinReadInitValues& , int32_t*, uint32_t*, uint32_t*, double*, uint8_t*);
        bool Lin_Write_Step_From_Read(const sg::ofa::LinReadInitValues&, void*, size_t);
        void Lin_Read_Stop(const sg::ofa::LinReadInitValues&, size_t);

        void Lin_Write_Start(const sg::ofa::LinWriteInitValues&, size_t);
        bool Lin_Write_Step(const sg::ofa::LinWriteInitValues&, void*, size_t);
        void Lin_Write_Stop(const sg::ofa::LinWriteInitValues&, size_t);
    }
}
