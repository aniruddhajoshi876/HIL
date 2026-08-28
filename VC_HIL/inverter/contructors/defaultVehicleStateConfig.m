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
% Build-time safety gate for the CarMaker PHYSICS truth (0x503-0x506) feeding
% the MTi-680G emulation in place of the internal kinematic model. Enable only
% after the CarMaker truth path passes the documented bench acceptance
% sequence (VC_HIL/docs/carmaker_imu_truth_source_plan.md). When false,
% SELECTVEHICLEOBSERVATION uses the internal kinematic observation and the
% 0x503-0x506 frames are decoded for diagnostics only.
config.carMakerTruthEnabled = false;
% Explicit steering-source selection for the angle fed to the Bosch LWS
% emulator and the shared vehicle state. There is no implicit source and no
% silent fallback -- see SELECTSTEERINGSOURCE.
%
%   0  MANUAL   the GUI steering dial. Shipping default and documented
%               rollback; must be selected deliberately, and is reported as
%               manual input in the telemetry.
%   1  CARMAKER the Fanatec wheel via CarMaker Steer.WhlAng and the 0x507
%               CarMakerSteeringTruth frame. Select only after the
%               Fanatec -> CarMaker -> 0x507 -> Speedgoat -> 0x2B0 path
%               passes the documented bench acceptance sequence
%               (VC_HIL/docs/carmaker_fanatec_lws_steering.md).
%
% In CARMAKER mode a stale or missing 0x507 does NOT revert to the dial: the
% LWS emulator encodes the Bosch failure state instead, so the VCU can never
% be handed GUI steering while it believes it is reading the driver's wheel.
config.steeringSourceMode = uint8(0);
% Freshness timeout for the retained 0x507 steering value, in milliseconds.
% 0x507 is sent at 100 Hz (10 ms); 30 ms tolerates two consecutive misses
% before the selector declares the steering unavailable. Matches the 30 ms
% CARMAKERPHYSICSSNAPSHOT freshness window, so physics and steering from the
% same CarMaker producer time out together.
config.carMakerSteeringFreshnessMs = 30;
end
