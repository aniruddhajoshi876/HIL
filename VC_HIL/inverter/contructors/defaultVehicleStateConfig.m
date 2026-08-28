function config = defaultVehicleStateConfig()
%DEFAULTVEHICLESTATECONFIG Parameters for the independent HIL vehicle state.
%   This model is deliberately outside the production VCU path.  Every
%   value is exposed here so a vehicle model can replace it without editing
%   the sensor protocol or CAN boundary.
config.massKg = 300;
config.wheelRadiusM = 0.25;
config.yawInertiaKgM2 = 120;
config.frontAxleDistanceM = 0.75;
config.rearAxleDistanceM = 0.75;
config.steeringGain = 1;
% Build-time safety gate. Enable only after the CarMaker truth path passes
% the documented bench acceptance sequence.
config.carMakerTruthEnabled = false;
% Build-time gate for sourcing the steering-wheel angle fed to the Bosch LWS
% emulator (and the shared vehicle state) from CarMaker's 0x507
% CarMakerDriverSteering transport frame instead of the GUI steering dial.
% Enable only after the Fanatec -> CarMaker -> 0x507 -> Speedgoat -> 0x2B0
% path passes the documented bench acceptance sequence
% (VC_HIL/docs/carmaker_fanatec_lws_steering.md). When disabled the GUI dial
% is the only steering source and 0x507 is ignored.
config.carMakerSteeringEnabled = false;
% Freshness timeout for the retained 0x507 steering value, in milliseconds.
% 0x507 is sent at 100 Hz (10 ms); 30 ms tolerates two consecutive misses
% before the selector falls back to the GUI dial. Matches the 30 ms
% CARMAKERPHYSICSSNAPSHOT freshness window.
config.carMakerSteeringFreshnessMs = 30;
end
