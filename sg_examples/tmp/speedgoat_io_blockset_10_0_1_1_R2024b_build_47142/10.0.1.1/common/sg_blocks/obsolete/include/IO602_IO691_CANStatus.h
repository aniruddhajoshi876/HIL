/*
*   Copyright:      n/a
*   Description:    This file includes the CAN status structure declarations used by the S-Function interface file of the Speedgoat CAN driver library.
*   Version:        $Revision
*   Date:           $Date$
*   Modified by:    $Author$
*/

#ifndef __SGESD_CANSTATUS_H__
#define __SGESD_CANSTATUS_H__

#include <cstdint>

namespace sg
{
    namespace esd
    {
		// used in CAN status interface for S-Function
        struct CanStatus {
            // error counters and queue status. -1 stands for unknown/no value
            int8_t err_warning_limit;
            int8_t err_passive_limit;
            int8_t err_bus_off;
			// percentage receive buffer (DMA); 0..100
			float receive_buffer_level;
			// percentage of send buffer, in the CAN controller only; 0..100
			float transmit_buffer_level;
			// Did overrun receive occur, in CAN controller receive queue.
			// This is only useful if bus master feature is _not_ used.
			uint32_t data_overrun_receive_hw;
			// counts number of skipped messages in busmaster-feeded receive queue
			uint32_t data_overrun_receive_dma;
			// overrun counter in driver-level send queues
			uint32_t sendqueue_overrun;
			// overrun counter for controller CAN TX queue.
			// pcie402: not used, consider sendqueue_overrun instead.
			uint32_t data_overrun_transmit;
			int8_t transmit_pending;
			int8_t receiving;
            int8_t receive_queue_empty; // 1 if CAN controller RX queue _and_ DMA queue empty
			int16_t err_cnt_rx;
			int16_t err_cnt_tx;
			int32_t bus_recovery_counter;

			// counts events: sender thread waiting because CAN controller FIFO full
			uint32_t senderthread_waiting;
            // bus load status, range 0..1; average calculated since last reset of averaging_deltaT
            float avg_bus_load;
            // controller and hardware state
			// not available on pcie402
            float controller_cpu_load; 
			/*  Each time the CanStatus is updated, this counter is updated if the controller is still alive.
			  For pcie402: we read out the timestamp of the controller, and look for a change vs. last timestamp. */
            uint32_t live_counter;
			unsigned long long int timeStamp;
			// Is firmware currently initializing.
			// pcie402: not available.
            int8_t init_mode_active; 
			// Transceiver error status.
			// pcie402: not available
            int8_t transceiver_err;
			// bus coupling error
			// pcie402: not available
            int8_t bus_coupling_err;
            // active parameters
			static const int8_t op_mode_off = 0, op_mode_low_speed = 1, op_mode_high_speed = 2, op_mode_fd = 3;
            int8_t op_mode;
            uint8_t brp;
            uint8_t tseg1;
            uint8_t tseg2;
            uint8_t sjw;
            uint8_t data_tseg1;
            uint8_t data_tseg2;
            uint8_t data_sjw;

			// fields used for state tracking  of load statistics; for each channel
			unsigned long long bus_statistic_ts;  // timestamp of bus statistic msg
			float bus_load_current;  // range 0..1; last measured value
			// fields below must be atomic because of concurrent access:
			// averaging time over which bus_load_avg is calculated, in 80 MHz ticks
			uint32_t averaging_deltaT; // type uint32_t is atomic
			// reset flag which may be set by Status block, to restart averaging 
			bool reset_averaging;
			// collection of status flags; see below
			uint32_t statusFlags;

			/* Set masked status flags; return (modified) status flags */
			inline uint32_t getSetModuleStatusFlags(uint32_t mask, uint32_t flags) {
				return this->statusFlags =
					(this->statusFlags & ~mask) | (mask & flags);
			}
			/* reset status info, except flags and bus recovery counter */
			inline void reset() { 
				CanStatus newstatus;
				newstatus.statusFlags = statusFlags;
				newstatus.bus_recovery_counter = bus_recovery_counter;
				*this = newstatus;
			}
			inline CanStatus() {
				err_warning_limit = -1;
				err_passive_limit = -1;
				err_bus_off = -1;
				receive_buffer_level = 0;
				transmit_buffer_level = 0;
				data_overrun_receive_hw = 0;
				data_overrun_receive_dma = 0;
				sendqueue_overrun = 0;
				data_overrun_transmit = 0;
				transmit_pending = -1;
				receiving = 0;
				receive_queue_empty = -1;
				err_cnt_rx = 0;
				err_cnt_tx = 0;
				bus_recovery_counter = 0;
				senderthread_waiting = 0;
				avg_bus_load = 0.;
				controller_cpu_load = -1;
				live_counter = 0;
				timeStamp = 0;
				init_mode_active = 0;
				transceiver_err = 0;
				bus_coupling_err = 0;
				op_mode = -1;
				brp = 0;
				tseg1 = 0;
				tseg2 = 0;
				sjw = 0;
				data_tseg1 = 0;
				data_tseg2 = 0;
				data_sjw = 0;
				bus_statistic_ts = 0;
				bus_load_current = 0.f;
				averaging_deltaT = 0;
				reset_averaging = false;
				statusFlags = 0;
			}
        };

        const uint32_t CanStatusRequestMask_all = 0xFFFF;
        const uint32_t CanStatusRequestMask_error_status = 1 << 0;
        const uint32_t CanStatusRequestMask_bus_load = 1 << 1;
        const uint32_t CanStatusRequestMask_controller_state = 1 << 2;
        const uint32_t CanStatusRequestMask_parameters = 1 << 3;
		//  are there any Read S-function instances for this channel
		const uint32_t CanStatusMask_HasRead = 0x01;
		//  2 bits wide - bus recovery mode
		const uint32_t CanStatusMask_BusRecoveryMode = 0x3 << 4;
		const uint32_t CanStatus_BusRecoveryMode_Off = 0x0 << 4;
		const uint32_t CanStatus_BusRecoveryMode_Auto = 0x1 << 4;
		const uint32_t CanStatus_BusRecoveryMode_Manual = 0x2 << 4;

    }
}

#endif // !__SGESD_CANSTATUS_H__

