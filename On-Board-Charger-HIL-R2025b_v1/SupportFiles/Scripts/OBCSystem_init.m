%% OBCSystem Initialization Script
% Defines all parameters used by OBCSystem.slx
% Run this script before building or simulating the model.
%
% Usage:
%   OBCSystem_init   (from command window)
%   or set as model PreLoadFcn callback

% Safety: clear variables that might shadow MATLAB built-ins
clear prod run

%% ======================================================================
%  Grid Parameters
%  ======================================================================
grid.ACVoltageRMS   = 230;       % [V]   RMS phase voltage
grid.SystemFrequency = 50;       % [Hz]  Grid frequency

%% ======================================================================
%  Totem-Pole PFC Converter
%  ======================================================================
totemPole.DCVoltage                 = 600;       % [V]   DC bus voltage reference
totemPole.PowerReference            = 2e3;       % [W]   Power reference
totemPole.lineInductance            = 1e-3;      % [H]   Line inductor
totemPole.lineResistance            = 20e-3;     % [Ohm] Line resistance
totemPole.OutputCapacitance         = 18e-3;     % [F]   Output capacitance
totemPole.OutputCapacitanceInitVoltage = 400;    % [V]   Initial capacitor voltage
totemPole.SwitchingFrequency        = 100e3;     % [Hz]  Switching frequency
totemPole.tdt                       = 1e-6;      % [s]   Dead time (fast leg)
totemPole.tdtSlow                   = 4e-3;      % [s]   Dead time (slow leg)
totemPole.VoltageSensorG            = 1;         % [-]   Voltage sensor gain
totemPole.VoltageSensorT            = 1/(2*totemPole.SwitchingFrequency); % [s] Sensor time const
totemPole.CurrentSensorG            = 1;         % [-]   Current sensor gain
totemPole.CurrentSensorT            = 1/(2*totemPole.SwitchingFrequency); % [s] Sensor time const
totemPole.CaseTemp                  = 25;        % [degC] Case temperature
totemPole.AllGateEnable             = 0;         % [-]   All gate enable
totemPole.SiMOSEnable               = 0;         % [-]   SiMOS enable
totemPole.SiMOSDelaySamples         = 2e3;       % [-]   SiMOS delay samples
totemPole.CurrentControllerKp       = 0.06;      % [-]   Current Kp (orig)
totemPole.CurrentControllerKi       = 1500/4;    % [-]   Current Ki (orig)
totemPole.VoltageControllerKp       = 1.17;      % [-]   Voltage Kp (orig)
totemPole.VoltageControllerKi       = 31.30;     % [-]   Voltage Ki (orig)
totemPole.VoltageControllerSaturation = 2000;    % [-]   Voltage saturation

%% ======================================================================
%  DAB Converter
%  ======================================================================
DAB.VDC_HV      = 400;           % [V]   HV-side DC voltage
DAB.VDC_LV      = 400;           % [V]   LV-side DC voltage
DAB.L_DAB_HV    = 130e-6;        % [H]   Series inductance
DAB.R_DAB_HV    = 0.02;          % [Ohm] Series resistance
DAB.N_DAB       = DAB.VDC_HV / DAB.VDC_LV; % [-] Transformer turns ratio
DAB.Cout        = 1.5e-3;        % [F]   Output capacitance
DAB.VCout       = 390;           % [V]   Initial capacitor voltage
DAB.fsw         = 100e3;         % [Hz]  Switching frequency
DAB.tdt         = 2e-7;          % [s]   Dead time
DAB.VoltageSensorG = 1;          % [-]   Voltage sensor gain
DAB.VoltageSensorT = 1/(2*DAB.fsw); % [s] Sensor time const
DAB.CurrentSensorG = 1;          % [-]   Current sensor gain
DAB.CurrentSensorT = 1/(2*DAB.fsw); % [s] Sensor time const
DAB.CaseTemp    = 25;            % [degC] Case temperature

%% ======================================================================
%  PFC Controller - PI Gains (Simulink.Parameter for ExportedGlobal)
%  ======================================================================
% Voltage loop (PI Voltage block uses P = Kp_voltage/10, I = Ki_voltage/10)
Kp_voltage = Simulink.Parameter(single(21.06));      % [-] Voltage loop Kp
Kp_voltage.CoderInfo.StorageClass = 'ExportedGlobal';
Ki_voltage = Simulink.Parameter(single(225.36));      % [-] Voltage loop Ki
Ki_voltage.CoderInfo.StorageClass = 'ExportedGlobal';

% Current loop (PI current block uses P = Kp_current, I = Ki_current)
Kp_current = Simulink.Parameter(single(0.013));       % [-] Current loop Kp (optimal)
Kp_current.CoderInfo.StorageClass = 'ExportedGlobal';
Ki_current = Simulink.Parameter(single(2));           % [-] Current loop Ki (optimal)
Ki_current.CoderInfo.StorageClass = 'ExportedGlobal';

% Open-loop controls
OpenLoopEnable = Simulink.Parameter(0);               % [-] 0=closed-loop, 1=open-loop
OpenLoopEnable.CoderInfo.StorageClass = 'ExportedGlobal';
OpenLoopDuty = Simulink.Parameter(0);                 % [-] Open-loop duty cycle
OpenLoopDuty.CoderInfo.StorageClass = 'ExportedGlobal';

%% ======================================================================
%  PFC Controller - Anti-Windup and Saturation
%  ======================================================================
% PI Voltage anti-windup
PFC_Voltage_Kb        = 500;                          % [-]  Back-calculation gain
PFC_Voltage_UpperSat  = 7500;                         % [-]  Upper saturation limit
PFC_Voltage_LowerSat  = -1000;                        % [-]  Lower saturation limit

% PI Current anti-windup
PFC_Current_Kb        = 2000;                         % [-]  Back-calculation gain
PFC_Current_UpperSat  = 1;                            % [-]  Upper saturation limit
PFC_Current_LowerSat  = -1;                           % [-]  Lower saturation limit

% PFC reference setpoints
PFCReferenceDCVoltage = 400;                          % [V]  DC bus voltage reference
% PFCReferencePower is not used. The voltage loop determines output power.

% PFC saturation limits
PFC_Sat_Pwr_Upper = 0.97 * 32 * grid.ACVoltageRMS;   % [W]  Power saturation upper
PFC_Sat_Pwr_Lower = 0;                               % [W]  Power saturation lower
PFC_Sat_iL_Upper  = sqrt(2) * 32;                    % [A]  Current saturation upper
PFC_Sat_iL_Lower  = -sqrt(2) * 32;                   % [A]  Current saturation lower
PFC_Sat_DC_Upper  = 1;                               % [-]  Duty cycle upper
PFC_Sat_DC_Lower  = 0;                              % [-]  Duty cycle lower

%% ======================================================================
%  DAB Controller
%  ======================================================================
DAB_Charging          = 1;                            % [-]  1=charging, 0=off
DAB_CurrentReference  = 15;                           % [A]  Battery current reference
DAB_PhaseShiftInit    = 0;                            % [-]  Initial phase shift
DAB_PhaseToDeg        = 360;                          % [deg] Phase-to-degree conversion
DAB_DCOffset          = 0.5;                          % [-]  DC offset for PWM

% DAB PID controller
DAB_PID_Kp       = 0.01;                           % [-]  Proportional gain
DAB_PID_Ki       = 0.125;                       % [-]  Integral gain
DAB_PID_Kd       = 0;                                % [-]  Derivative gain
DAB_PID_N        = 100;                              % [-]  Filter coefficient
DAB_PID_UpperSat = 0.25;                             % [-]  PID upper saturation
DAB_PID_LowerSat = -0.25;                            % [-]  PID lower saturation

% DAB phase shift saturation
DAB_PhaseShift_UpperSat = 0.25;                      % [-]  Phase shift upper limit
DAB_PhaseShift_LowerSat = -0.25;                     % [-]  Phase shift lower limit

% DAB Battery CC-CV controller
MaxCellVoltage    = 400;                              % [V]  Max battery voltage (CV threshold)
DAB_CCCV_Kp      = 5;                                % [-]  CC-CV proportional gain
DAB_CCCV_Ki      = 0.5;                              % [-]  CC-CV integral gain
DAB_CCCV_Kaw     = 1;                                % [-]  CC-CV anti-windup gain
DAB_CCCV_Kt      = 1;                                % [-]  CC-CV tracking gain

%% ======================================================================
%  Battery Model Parameters
%  ======================================================================
Battery_Vnom       = 400;                             % [V]   Nominal voltage
Battery_AH         = 1;                               % [Ah]  Capacity
Battery_InitCharge = 0.75;                            % [-]   Initial state of charge (0-1)
Battery_R1         = 0.001;                           % [Ohm] Internal resistance
Battery_V1         = 280;                             % [V]   Voltage at exponential zone
Battery_AH1        = 0.2;                             % [Ah]  Capacity at exponential zone
Battery_ThermalMass = 300;                            % [J/K] Thermal mass

%% ======================================================================
%  Timing Parameters
%  ======================================================================
ts_CPU      = 5e-5;                                   % [s]   CPU sample time (20 kHz)
ts_FPGA_clk = 1/100e6;                               % [s]   FPGA clock (100 MHz)
ts_FPGA_mdl = 5/(1000*totemPole.SwitchingFrequency); % [s]   FPGA model sample time
f_FPGA      = 1/ts_FPGA_clk;                         % [Hz]  FPGA clock frequency
oversampling = ts_FPGA_mdl/ts_FPGA_clk;              % [-]   Oversampling ratio

% Simulation control (NOTE: SimulationMode is set in the model Constant block,
% not as a workspace variable, because the variant subsystem reads the block value)
SimulationStopTime = 120;                             % [s]   Simulation stop time

%% ======================================================================
%  PWM Generation Parameters
%  ======================================================================
PFC_PWM_BitWidth  = 24;                               % [bits] PFC PWM counter width
PFC_PWM_Deadband  = ts_FPGA_clk * 10;                % [s]    PFC dead band duration
DAB_PWM_BitWidth  = 24;                               % [bits] DAB PWM counter width
DAB_PWM_Deadband  = 1e-7;                             % [s]    DAB dead band duration

%% ======================================================================
%  Streaming DMA Parameters
%  ======================================================================
ts_log = 25*ts_FPGA_clk;                             % [s]   Logging sample time
SamplesPerFrame = floor(ts_CPU/ts_log);               % [-]   Samples per frame per signal
VectorSize      = 2;                                  % [-]   Number of streamed signals
FrameSize       = VectorSize * SamplesPerFrame;       % [-]   Total frame data points

%% ======================================================================
%  FPGA Plant Model Mask Parameters
%  ======================================================================
R_out    = 1e6;                                       % [Ohm] Output resistance (open circuit)
C_out    = totemPole.OutputCapacitance;               % [F]   DC bus capacitance
V_C_init = totemPole.OutputCapacitanceInitVoltage;    % [V]   Initial capacitor voltage
L_line   = totemPole.lineInductance;                  % [H]   Line inductance
L        = DAB.L_DAB_HV;                             % [H]   DAB series inductance
n        = DAB.N_DAB;                                % [-]   Transformer turns ratio
C        = DAB.Cout;                                 % [F]   DAB output capacitance
R        = 0.5;                                      % [Ohm] Load resistance

%% ======================================================================
%  Instrumentation Parameters
%  ======================================================================
Instr_MeanFreq    = 50;                               % [Hz]  One-cycle mean frequency
Instr_PinGain     = 1e-3;                             % [kW^-1] Input power display scaling
Instr_PoutGain    = 1e-3;                             % [kW^-1] Output power display scaling
Instr_EffGain     = 100;                              % [%%]  Efficiency display scaling
Instr_RippleGain  = 100;                              % [%%]  Ripple display scaling
Instr_SoCGain     = 100;                              % [%%]  State-of-charge display scaling
Instr_pUtoDeg     = 360;                              % [deg] Per-unit to degrees conversion

%% ======================================================================
%  FE Conditioning (PFC Signals)
%  ======================================================================
FE_min_IL       = -100;                               % [A]
FE_max_IL       = 100;                                % [A]
FE_min_Vs       = -400;                               % [V]
FE_max_Vs       = 400;                                % [V]
FE_min_Vbus     = 0;                                  % [V]
FE_max_Vbus     = 1000;                               % [V]
FE_min_Vbus_ref = 0;                                  % [V]
FE_max_Vbus_ref = 1000;                               % [V]
FE_min_P        = 0;                                  % [W]
FE_max_P        = 12000;                              % [W]

%% ======================================================================
%  FE Conditioning (DAB Signals)
%  ======================================================================
FE_min_Isigma   = -30;                                % [A]
FE_max_Isigma   = 30;                                 % [A]
FE_min_Ibat     = -30;                                % [A]
FE_max_Ibat     = 30;                                 % [A]
FE_min_Vbat     = 0;                                  % [V]
FE_max_Vbat     = 500;                                % [V]
FE_min_Vbat_ref = 0;                                  % [V]
FE_max_Vbat_ref = 500;                                % [V]

%% ======================================================================
%  DSP Parameters
%  ======================================================================
Target = mcb.getProcessorParameters('F28379D', totemPole.SwitchingFrequency);
ftics           = 200e6;                              % [Hz]  DSP oscillator frequency
fc              = 20e3;                               % [Hz]  Control update frequency
Tc              = 1/fc;                               % [s]   Control period
fsw_DAB         = DAB.fsw;                            % [Hz]  DAB switching frequency
Tsw_DAB         = 1/fsw_DAB;                          % [s]   DAB switching period
Tdt_DAB         = 0.5e-6;                             % [s]   DAB H-bridge dead time
TicsFsw_df_DAB  = (1/fsw_DAB)/(1/ftics);             % [-]   DAB PWM period in ticks
f_AnalogOutput  = 100e3;                              % [Hz]  Analog output frequency
TicsAnalogOutput = (1/f_AnalogOutput)/(1/ftics);     % [-]   Analog output ticks
FE_VPWM_AO      = 3.3;                               % [V]   PWM analog output voltage
Percentage2Tics_AO = (1/f_AnalogOutput/2)/(1/ftics)/100; % [-] Percent to ticks conversion
FE_V            = 3;                                  % [V]   FE voltage reference

%% ======================================================================
%  Semiconductor Data
%  ======================================================================
Rblock = 1/(1/1e9 + 1/1e9);                          % [Ohm] Blocking resistance
RDSON  = 0.1;                                         % [Ohm] MOSFET on-resistance
VDSth  = 0;                                           % [V]   Drain-source threshold
VFth   = 1;                                           % [V]   Forward voltage threshold
RF     = 0.1;                                         % [Ohm] Forward resistance

fprintf('OBCSystem_init: All parameters loaded.\n');
