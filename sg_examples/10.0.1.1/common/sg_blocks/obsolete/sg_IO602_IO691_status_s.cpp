/*
*   File       : sg_esd_v1_status_s.c
*   Description: This file includes all functions of the Simulik S-Function CAN status block for the ESD IO691 module.
*   Version    : $Revison$
*   Author     : $Author$
*   Date       : $Date$
*
*/

#define S_FUNCTION_LEVEL    2
#undef S_FUNCTION_NAME
#define S_FUNCTION_NAME     sg_IO602_IO691_status_s

#include "simstruc.h"
#include "include/IO602_IO691_SFunctionInterface.h"
using namespace sg::esdSFcn;

#ifndef MATLAB_MEX_FILE
#ifdef _MSC_BUILD //On Time
#include "xpctarget.h"
#include "xpcimports.h"
#include <windowsx.h>
#endif
#include "../common/libsg/sg_common.h"
#else
#include "mex.h"
#endif

#include "../common/libsg/sg_callback.h"
#include "../common/libsg/sg_printf.h"

#include <exception>

static int SetAndCheckSFunctionParames(uint8_T isTunable, SimStruct *S);
static void SetSFunctionInputPortProperties(int_T portNumber, uint32_T portWidth, BuiltInDTypeId dataType, boolean_T isRequiredContiguous, boolean_T isDirectFeedThrough, uint8_T propertySelection, SimStruct *S);
static void CreateSFunctionInputPorts(int32_T quantityOfInputs, SimStruct *S);
static void CreateSFunctionOutputPorts(int32_T quantityOfOutputs, SimStruct *S);
/* propertySelection says what property to put (1: width, 2: datatype, 0: all) */
static void SetSFunctionOutputPortProperties(int portNumber, int32_T portWidth, BuiltInDTypeId dataType, uint8_T propertySelection, SimStruct *S);
/* a version of GetCanStatus only for testing of S-Function interface, without ESD library. */
static void GetCanStatus_testing(int32_t moduleIndex, uint8_t channelIndex, uint32_t requestMask, CanStatus& cs);

static void mdlOutputs(SimStruct * S, int_T tid);

const int QTY_PARAM = 34;        // Quantity of the S-Function block parameters which are used in this S-Function code file.
const int QTY_R_WORK = 0;        // Quantity of vectors/pointers of the data type REAL/DOUBLE of the S-Function.
const int QTY_I_WORK = QTY_PARAM;        // Quantity of vectors/pointers of the data type INT of the S-Function.
const int QTY_P_WORK = 0;        // Quantity of vectors/pointers of the data type VOID of the S-Function.

// S-Function parameter with unset type info
struct SFuncPar0 {
	int _idx;          // index in S-Function parameter list, starts at 0 
	SFuncPar0(int idx) { 
		_idx = idx; 
		_parType = _outType = -1; //unset
	}
	real_T get(SimStruct* S) {
		return mxGetPr(ssGetSFcnParam(S, _idx))[0];
	}
	int _parType;
	int _outType;
};

typedef  real_T outputTypeDefault; // previously, was uint32_T, but decided to move to same output type everywhere.

// S-Function parameter with type info of parameter and corresponding output
template<class ParamT, class OutputT = outputTypeDefault>
class SFuncPar : public SFuncPar0 {
public:
	SFuncPar(int idx);

	ParamT operator()(SimStruct* S) {
		return (ParamT)this->get(S);
	}
	// set the correponding Simulink output, if enabled
	void setOut(SimStruct* S, OutputT value) {
		// find index of corresponding output signal if it is available; starts at 0
		bool outAsArray = ssGetIWorkValue(S, 0);
		int outIdx = ssGetIWorkValue(S, _idx);

		if (outIdx < 0)
			return;
		if (!outAsArray)
			//*(OutputT*)(S->portInfo.outputs[outIdx].signalVect) = value;
			*(OutputT*)ssGetOutputPortSignal(S, outIdx) = value;
		else
			// array - all outs same type = real_T
			//((outputTypeDefault*)S->portInfo.outputs[0].signalVect)[outIdx] = (outputTypeDefault)value;
			((outputTypeDefault*)ssGetOutputPortSignal(S, 0))[outIdx] = (outputTypeDefault)value;
	}
};
// define constructor only for explicit types:
template<>
SFuncPar<int32_T, uint32_T>::SFuncPar(int idx) : SFuncPar0(idx) { _parType = SS_INT32; _outType = SS_UINT32; }
template<>
SFuncPar<int32_T, real32_T>::SFuncPar(int idx) : SFuncPar0(idx) { _parType = SS_INT32; _outType = SS_SINGLE; }
template<>
SFuncPar<int32_T, real_T>::SFuncPar(int idx) : SFuncPar0(idx) { _parType = SS_INT32; _outType = SS_DOUBLE; }
template<>
SFuncPar<uint32_T, uint32_T>::SFuncPar(int idx) : SFuncPar0(idx) { _parType = SS_UINT32; _outType = SS_UINT32; }
template<>
SFuncPar<uint32_T, real_T>::SFuncPar(int idx) : SFuncPar0(idx) { _parType = SS_UINT32; _outType = SS_DOUBLE; }
template<>
SFuncPar<boolean_T, uint32_T>::SFuncPar(int idx) : SFuncPar0(idx) { _parType = SS_BOOLEAN; _outType = SS_UINT32; }
template<>
SFuncPar<boolean_T, real32_T>::SFuncPar(int idx) : SFuncPar0(idx) { _parType = SS_BOOLEAN; _outType = SS_SINGLE; }
template<>
SFuncPar<boolean_T, real_T>::SFuncPar(int idx) : SFuncPar0(idx) { _parType = SS_BOOLEAN; _outType = SS_DOUBLE; }
template<>
SFuncPar<real_T, uint32_T>::SFuncPar(int idx) : SFuncPar0(idx) { _parType = SS_DOUBLE; _outType = SS_UINT32; }
template<>
SFuncPar<real_T, real_T>::SFuncPar(int idx) : SFuncPar0(idx) { _parType = SS_DOUBLE; _outType = SS_DOUBLE; }

class SFuncParameters {
public:
	// these S-function parameters and their order are defined in the Dialog "Block Parameters -> S-function parameters" in Simulink.
	SFuncPar<int32_T>   mod_id;         // Module ID
	SFuncPar<real_T>    sample_time;     // Sample time of the block. 
	SFuncPar<uint8_T>  port_selection;  // port selection
#define BUS_RECO_CAN_OFF 1
#define BUS_RECO_CAN_AUTO 2
#define BUS_RECO_CAN_MANUAL 3
	// Modus selection for bus recovery for CAN; activates input port if value is 'Manual'.
	SFuncPar<uint32_T> bus_reco_CAN;
	// Output signal selection (0 = disabled, 1 = enabled)
	SFuncPar<boolean_T, real_T> ena_avg_bus_load;	// Average bus load 
    SFuncPar<boolean_T> ena_op_mode;       // CAN operation mode 
	SFuncPar<boolean_T> ena_BRP; 
	SFuncPar<boolean_T> ena_TSEG1;
	SFuncPar<boolean_T> ena_TSEG2;
	SFuncPar<boolean_T> ena_SJW;
	// CAN-FD controller status
	SFuncPar<boolean_T> ena_TSEG1_FD;
	SFuncPar<boolean_T> ena_TSEG2_FD;
	SFuncPar<boolean_T> ena_SJW_FD;

	SFuncPar<boolean_T> ena_tx_pending;
	SFuncPar<boolean_T> ena_data_overrun_tx;
	SFuncPar<boolean_T> ena_receiving;
	SFuncPar<boolean_T> ena_rx_queue_empty;
	SFuncPar<boolean_T> ena_data_overrun_rx;
	SFuncPar<boolean_T> ena_err_warn_limit;
	SFuncPar<boolean_T> ena_err_pass_limit;
	SFuncPar<boolean_T> ena_bus_off_state;
	SFuncPar<boolean_T> ena_bus_reco_cnt;
	SFuncPar<boolean_T> ena_init_mode_act;
	SFuncPar<boolean_T> ena_bus_coupling_err;
	SFuncPar<boolean_T> ena_transceiver_err;
	SFuncPar<boolean_T, real_T> ena_controller_cpu_load;
	SFuncPar<boolean_T> ena_controller_live;
	SFuncPar<boolean_T, real_T> ena_rx_buff_level;
	SFuncPar<boolean_T, real_T> ena_tx_buff_level;
	// if true, output all selected signals in a vector
	SFuncPar<boolean_T> out_as_array;

	// Hidden
	SFuncPar<int32_T>    module_type; // integer of module type, e.g. 691 for IO691
	SFuncPar<uint8_T>    quantity_status_blk; // Quantity of available status blocks in the model.
	SFuncPar<uint8_T>    port_index; // Port index - no longer used.
	SFuncPar<boolean_T>  is_fd_module; // Status flag if current module a CAN-FD module (=true) or not (=false)
	static_assert(QTY_PARAM == 34, "check S-function parameters!");
	int outputPortCounter;

	const static int nEnableParameters = 25;
	SFuncPar0* enableParameters[nEnableParameters];

	inline SFuncParameters()
		: mod_id(0),
		sample_time(1),
		port_selection(2),
		bus_reco_CAN(3),
		ena_avg_bus_load(4),
		ena_op_mode(5),
		ena_BRP(6),
		ena_TSEG1(7),
		ena_TSEG2(8),
		ena_SJW(9),
		ena_TSEG1_FD(10),
		ena_TSEG2_FD(11),
		ena_SJW_FD(12),
		ena_tx_pending(13),
		ena_data_overrun_tx(14),
		ena_receiving(15),
		ena_rx_queue_empty(16),
		ena_data_overrun_rx(17),
		ena_err_warn_limit(18),
		ena_err_pass_limit(19),
		ena_bus_off_state(20),
		ena_bus_reco_cnt(21),
		ena_init_mode_act(22),
		ena_bus_coupling_err(23),
		ena_transceiver_err(24),
		ena_controller_cpu_load(25),
		ena_controller_live(26),
		ena_rx_buff_level(27),
		ena_tx_buff_level(28),
		out_as_array(29),
		module_type(30),
		quantity_status_blk(31),
		port_index(32),
		is_fd_module(33)
	{
		outputPortCounter = 0;
		// here we define the order of the output signals - this must agree with mask definition in Matlab file
		// CAN controller status
		int i = 0;
		enableParameters[i++] = &ena_controller_cpu_load;
		enableParameters[i++] = &ena_controller_live;
		enableParameters[i++] = &ena_init_mode_act;
		// Channel  status
		enableParameters[i++] = &ena_avg_bus_load;
		enableParameters[i++] = &ena_receiving;
		enableParameters[i++] = &ena_rx_queue_empty;
		enableParameters[i++] = &ena_data_overrun_rx;
		enableParameters[i++] = &ena_rx_buff_level;
		enableParameters[i++] = &ena_tx_pending;
		enableParameters[i++] = &ena_data_overrun_tx;
		enableParameters[i++] = &ena_tx_buff_level;

		enableParameters[i++] = &ena_err_warn_limit;
		enableParameters[i++] = &ena_err_pass_limit;
		enableParameters[i++] = &ena_bus_off_state;
		enableParameters[i++] = &ena_bus_reco_cnt;

		enableParameters[i++] = &ena_bus_coupling_err;
		enableParameters[i++] = &ena_transceiver_err;

		// CAN operation mode and parameters
		enableParameters[i++] = &ena_op_mode;
		enableParameters[i++] = &ena_BRP;
		enableParameters[i++] = &ena_TSEG1;
		enableParameters[i++] = &ena_TSEG2;
		enableParameters[i++] = &ena_SJW;
		// CAN-FD
		enableParameters[i++] = &ena_TSEG1_FD;
		enableParameters[i++] = &ena_TSEG2_FD;
		enableParameters[i++] = &ena_SJW_FD;
	}

	void configure(SimStruct* S)
	{
		// count outputs
		outputPortCounter = 0;
		for (int p = 0; p < nEnableParameters; p++) {
			if (enableParameters[p] && enableParameters[p]->get(S))
				outputPortCounter++;
		}
		// create and configure output ports in Simstruct
		if (out_as_array(S)) {
			CreateSFunctionOutputPorts(1, S);
			//SetSFunctionOutputPortProperties(0, outputPortCounter, SS_UINT32, 0, S);
			SetSFunctionOutputPortProperties(0, outputPortCounter, SS_DOUBLE, 0, S);  // should match outputTypeDefault
		}
		else {
			CreateSFunctionOutputPorts(outputPortCounter, S);
			int portIdx = 0;
			for (int p = 0; p < nEnableParameters; p++) {
				if (enableParameters[p] && enableParameters[p]->get(S)) {
					BuiltInDTypeId type = (BuiltInDTypeId)enableParameters[p]->_outType;
					SetSFunctionOutputPortProperties(portIdx, 1, type, 0, S);
					portIdx++;
				}
			}
		}
	}
	void setOutputIndices(SimStruct* S)
	{
		ssSetIWorkValue(S, 0, out_as_array(S));  // we know that index 0 is not used for an enable output parameter
		// get output port indices, store them in IWork
		int c = 0;
		for (int p = 0; p < nEnableParameters; p++) {
			int outIdx = -1;
			if (enableParameters[p] && enableParameters[p]->get(S))
				outIdx = c++;
			ssSetIWorkValue(S, enableParameters[p]->_idx, outIdx);
		}
	}
};
SFuncParameters pars;


static char_T ErrMsg[256];      // String for the error message of the S-Function.

/*
*   Set all properties of the S-Function block (e.g. parameters, input ports, output ports and so on).
*/
static void mdlInitializeSizes(SimStruct *S)
{
    uint8_T i = 0;

    // Set and check parameters
    if (0 == SetAndCheckSFunctionParames(0, S))
    {
        sprintf(ErrMsg, "Check list of parameters, %i parameters are expected!!!", QTY_PARAM);
        ssSetErrorStatus(S, ErrMsg);
        return;
    }

	pars.configure(S);
	

    if (pars.bus_reco_CAN(S) == BUS_RECO_CAN_MANUAL)
    {
        CreateSFunctionInputPorts(1, S);
        SetSFunctionInputPortProperties(0, 1, SS_UINT32, 1, 1, 0, S);
    }
    else
    {
        CreateSFunctionInputPorts(0, S);
    }

    // Set RWork vector
    ssSetNumRWork(S, QTY_R_WORK);

    // Set IWork vector
    ssSetNumIWork(S, QTY_I_WORK);

    // Set PWork vector
    ssSetNumPWork(S, QTY_P_WORK);

    // Default settings
    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);
    ssSetNumSampleTimes(S, 1);
    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

    // Specify the sim state compliance to be same as a built-in block
    // UNCOMMENT: ssSetSimStateCompliance(S, USE_DEFAULT_SIM_STATE);

    // Set options
    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE);     // see SS_OPTION in simstruct.h
}

/*
*   This function creates and checks the parameters of the S-Function block.

*/
static int SetAndCheckSFunctionParames(uint8_T isTunable, SimStruct *S)
{
    int i = 0;

    ssSetNumSFcnParams(S, QTY_PARAM);

    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S))
    {
        return 0;
    }

    for (i = 0; i < QTY_PARAM; i++)
    {
        ssSetSFcnParamTunable(S, i, isTunable);
    }

    return 1;
}

/*
*   This function creates the input ports of the S-Function block.
*/
static void CreateSFunctionInputPorts(int quantityOfInputs, SimStruct *S)
{
    ssSetNumInputPorts(S, quantityOfInputs);
}


/*
*   This function set the properties of the singe input port.

*/
static void SetSFunctionInputPortProperties(int_T portNumber, uint32_T portWidth, BuiltInDTypeId dataType, boolean_T isRequiredContiguous,
                                            boolean_T isDirectFeedThrough, uint8_T propertySelection, SimStruct *S)
{
    if (1 == propertySelection)
    {
        ssSetInputPortWidth(S, portNumber, portWidth);
    }
    else if (2 == propertySelection)
    {
        ssSetInputPortDataType(S, portNumber, dataType);
    }
    else if (3 == propertySelection)
    {
        ssSetInputPortRequiredContiguous(S, portNumber, isRequiredContiguous);
    }
    else if (4 == propertySelection)
    {
        ssSetInputPortDirectFeedThrough(S, portNumber, isDirectFeedThrough);
    }
    else
    {
        ssSetInputPortWidth(S, portNumber, portWidth);
        ssSetInputPortDataType(S, portNumber, dataType);
        ssSetInputPortRequiredContiguous(S, portNumber, isRequiredContiguous);
        ssSetInputPortDirectFeedThrough(S, portNumber, isDirectFeedThrough);
    }
}

/*
*   This function creates the output ports of the S-Function block.
*/
static void CreateSFunctionOutputPorts(int quantityOfOutputs, SimStruct *S)
{
    ssSetNumOutputPorts(S, quantityOfOutputs);
}

/*
*   This function set the properties of the singe output port.

*/
static void SetSFunctionOutputPortProperties(int portNumber, int32_T portWidth, BuiltInDTypeId dataType, uint8_T propertySelection, SimStruct *S)
{
    if (1 == propertySelection)
    {
        ssSetOutputPortWidth(S, portNumber, portWidth);
    }
    else if (2 == propertySelection)
    {
        ssSetOutputPortDataType(S, portNumber, dataType);
    }
    else
    {
        ssSetOutputPortWidth(S, portNumber, portWidth);
        ssSetOutputPortDataType(S, portNumber, dataType);
    }
}

/*
*   Set the sample times of the S-Function block.
*/

static void mdlInitializeSampleTimes(SimStruct *S)
{
	real_T sample_time = pars.sample_time(S);
    if (sample_time == -1.0)
    {
        ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
        ssSetOffsetTime(S, 0, FIXED_IN_MINOR_STEP_OFFSET);
    }
    else
    {
        ssSetSampleTime(S, 0, sample_time);
        ssSetOffsetTime(S, 0, 0.0);
    }
}

static void sg_ModelLoad(SimStruct* S) { ; }

static void sg_ModelStart (SimStruct *S) { pars.setOutputIndices(S); }

static void sg_ModelStep (SimStruct *S)
{
	CanStatus canStatus;
	uint8_T channelIdx = pars.port_selection(S) -1;
	uint32_T busRecoverySignalIn = 0;
	uint32_T busRecoveryMode = CanStatus_BusRecoveryMode_Off;
	if (pars.bus_reco_CAN(S) == BUS_RECO_CAN_MANUAL) {
		busRecoveryMode = CanStatus_BusRecoveryMode_Manual;
		busRecoverySignalIn = *(uint32_T*)ssGetInputPortSignal(S, 0);
	}
	else if (pars.bus_reco_CAN(S) == BUS_RECO_CAN_AUTO) {
		busRecoveryMode = CanStatus_BusRecoveryMode_Auto;
		busRecoverySignalIn = 1;
	}

	int32_T modIdx = 0;
	try {
#ifdef MATLAB_MEX_FILE
#ifdef DEBUG
		modIdx = pars.mod_id(S);
		mexPrintf("Dbg - Call GetCanStatus with moduleType: %d, moduleId %d, channelIdx %d, busRecoveryIn=%d\n", 
			pars.module_type(S), modIdx, channelIdx, busRecoverySignalIn);
		GetCanStatus_testing(modIdx, channelIdx, CanStatusRequestMask_all, canStatus);
#endif
#else
		modIdx = GetModuleIndexFromIdEx(pars.module_type(S), pars.mod_id(S));
		SG_PRINTF(DEBUG, "Dbg CanStatus - module index = %d, channel = %d\n", modIdx, channelIdx);

		setModuleBusRecoveryMode(modIdx, channelIdx, busRecoveryMode);
		SG_PRINTF(DEBUG, "Dbg - recovery mode = %d, signal = %d\n", busRecoveryMode, busRecoverySignalIn);

		if (!sg::esdSFcn::getModuleHasRead(modIdx, channelIdx)) {
			SG_PRINTF(DEBUG, "There is no Read block for channel %d - Status block reads out Msg Fifo instead\n",
				channelIdx);
			EvaluateCanMessages(modIdx, channelIdx);
		}
		UpdateCanStatus(modIdx, channelIdx, CanStatusRequestMask_all);
	    canStatus = *GetCanStatus(modIdx, channelIdx);

		if (busRecoverySignalIn && canStatus.err_bus_off>0)
		//if (busRecoverySignalIn && canStatus.err_warning_limit > 0) // only for testing
			triggerModuleBusRecovery(modIdx, channelIdx);

#endif // MATLAB_MEX_FILE

	}
	catch (const std::exception &e)
	{
		strncpy(ErrMsg, e.what(), sizeof(ErrMsg));
		ssSetErrorStatus(S, ErrMsg);
		return;
	}

	// CAN controller status
	pars.ena_controller_cpu_load.setOut(S, (real_T)(100 * canStatus.controller_cpu_load));
	pars.ena_controller_live.setOut(S, (outputTypeDefault)canStatus.live_counter);
	pars.ena_init_mode_act.setOut(S, (outputTypeDefault)canStatus.init_mode_active);
	// Channel  status
	pars.ena_avg_bus_load.setOut(S, (real_T)(100 * canStatus.avg_bus_load));
	pars.ena_receiving.setOut(S, (outputTypeDefault)canStatus.receiving);
	pars.ena_rx_queue_empty.setOut(S, (outputTypeDefault)canStatus.receive_queue_empty);
	pars.ena_data_overrun_rx.setOut(S, (outputTypeDefault)canStatus.data_overrun_receive_dma);
	pars.ena_rx_buff_level.setOut(S, (outputTypeDefault)canStatus.receive_buffer_level);

	pars.ena_tx_pending.setOut(S, (outputTypeDefault)canStatus.transmit_pending);
	//pars.ena_data_overrun_tx.setOut(S, canStatus.data_overrun_transmit);
	pars.ena_data_overrun_tx.setOut(S, (outputTypeDefault)canStatus.sendqueue_overrun);
	pars.ena_tx_buff_level.setOut(S, (outputTypeDefault)canStatus.transmit_buffer_level);
	pars.ena_err_warn_limit.setOut(S, (outputTypeDefault)canStatus.err_warning_limit);
	pars.ena_err_pass_limit.setOut(S, (outputTypeDefault)canStatus.err_passive_limit);
	pars.ena_bus_off_state.setOut(S, (outputTypeDefault)canStatus.err_bus_off);
	pars.ena_bus_reco_cnt.setOut(S, (outputTypeDefault)canStatus.bus_recovery_counter);

	pars.ena_bus_coupling_err.setOut(S, (outputTypeDefault)canStatus.bus_coupling_err);
	pars.ena_transceiver_err.setOut(S, (outputTypeDefault)canStatus.transceiver_err);
	// CAN operation mode and parameters
	pars.ena_op_mode.setOut(S, (outputTypeDefault)canStatus.op_mode);
	pars.ena_BRP.setOut(S, (outputTypeDefault)canStatus.brp);
	pars.ena_TSEG1.setOut(S, (outputTypeDefault)canStatus.tseg1);
	pars.ena_TSEG2.setOut(S, (outputTypeDefault)canStatus.tseg2);
	pars.ena_SJW.setOut(S, (outputTypeDefault)canStatus.sjw);

	pars.ena_TSEG1_FD.setOut(S, (outputTypeDefault)canStatus.data_tseg1);
	pars.ena_TSEG2_FD.setOut(S, (outputTypeDefault)canStatus.data_tseg2);
	pars.ena_SJW_FD.setOut(S, (outputTypeDefault)canStatus.data_sjw);

}

static void GetCanStatus_testing(int32_t moduleIndex, uint8_t channelIndex, uint32_t requestMask, CanStatus& cs)
{
	// some values just for testing the interface
	if (requestMask & CanStatusRequestMask_error_status) {
		cs.err_warning_limit = 4;
		cs.err_passive_limit = 5;
		cs.receive_queue_empty = 6;
		cs.data_overrun_receive_hw = 7;
		cs.data_overrun_receive_dma = 8;
		cs.transmit_pending = 8;
		cs.err_bus_off = 3;
		cs.receiving = 9;
		cs.bus_recovery_counter = 11;
		cs.receive_buffer_level = 32.f;
		cs.transmit_buffer_level = 33.f;
		cs.sendqueue_overrun = 34;
	}
	if (requestMask & CanStatusRequestMask_bus_load) {
		cs.avg_bus_load = .31f + .01f* channelIndex;
	}
	if (requestMask & CanStatusRequestMask_controller_state) {
		cs.controller_cpu_load = .20f;
		cs.live_counter++;
		cs.init_mode_active = 22;
	}
}

static void sg_ModelStop (SimStruct *S)
{
#ifndef MATLAB_MEX_FILE

#endif 
}

#include "../common/libsg/sg_sfcn_glue.h"
