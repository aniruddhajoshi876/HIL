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
end
