% Load Model
mdl = 'eVTOL_System';
load_system(mdl);
% Define the aircraft modes of flight. 
Simulink.defineIntEnumType('flightState',...
{'Hover','Transition','FixedWing','BackTransition'},[0;1;2;3]);
% Set attitude to be 0.
iniRoll=0;
iniYaw=0;
initPitch=0;
% Set initial position to ground location in local coordinates (NED)
xGround=0;
yGround=0;
zGround=0;
% Define Bus interfaces for controller
exampleHelperDefineCtrlInterface;
% Define Plant bus interface.
exampleHelperDefineDigitalTwinInterface;
% Set VTOL Dynamics:Aerodynamics and Geometry Parameters
uavParam=exampleHelperSetVTOLDynamics;
% Flag to enable/disable visualization
Visualization = 1;
% Disable Wind
Wind=0;
% Disable Sensors
SensorType=0;
% Setup tuning flag
TuningMode = 0;
% Initialize Control and Guidance gains for Tiltrotor
exampleHelperInitializeVTOLGains;
% Initialize initial velocity
vIni = 0;
disp("Initialized VTOL model.")
% Initialize hover configuration
setupHoverConfiguration
setupHoverGuidanceMission

open('eVTOL_System.slx');
open_system("eVTOL_System");
open('GettingStarted.mlx');
