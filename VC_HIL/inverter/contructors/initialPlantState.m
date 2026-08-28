function state = initialPlantState(cal)
%INITIALPLANTSTATE Create deterministic state for four independent plants.

if nargin < 1
    cal = defaultCalibration();
end
validateCalibration(cal);

state.protocolProfileId = cal.protocolProfileId;
state.omegaRadPerS = zeros(1, 4);
state.torqueSetpointNm = zeros(1, 4);
state.torqueActualNm = zeros(1, 4);
state.speedIntegratorNm = zeros(1, 4);
state.motorTemperatureC = cal.ambientTemperatureC;
state.switchTemperatureC = cal.ambientTemperatureC;
state.stepCount = uint64(0);
end
