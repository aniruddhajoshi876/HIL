function cal = defaultCalibration()
%DEFAULTCALIBRATION Conservative, explicit, non-identified model defaults.

p = inverterhil.protocol();
cal.sampleTimeS = 1e-3;
% Torque scale resolved 2026-08-02 by firmware evidence (see
% INVERTERHIL.PROTOCOL's torqueProfiles.vcu256 comment): the control-frame
% torque-limit fields use 1/256 Nm/count, not the previously-default 1/512.
cal.protocolProfileId = p.torqueProfiles.vcu256.id;
cal.torqueScaleNmPerCount = p.torqueProfiles.vcu256.scaleNmPerCount;
cal.torqueScaleVerified = p.torqueProfiles.vcu256.verified;
cal.dcLinkMinimumV = 350;
cal.switchingFrequencyKHz = 10;
cal.configErrorScope = uint8(0); % 0 per-channel, 1 unit-wide

cal.speedKp = repmat(0.05, 1, 4);
cal.speedKi = zeros(1, 4);
cal.inertiaKgM2 = repmat(0.05, 1, 4);
cal.dragNmPerRadS = repmat(0.005, 1, 4);
cal.torqueConstantNmPerA = repmat(0.5, 1, 4);
cal.torqueLagS = repmat(0.010, 1, 4);
cal.torqueSlewNmPerS = repmat(1000, 1, 4);
cal.modelTorqueMinNm = repmat(-64, 1, 4);
cal.modelTorqueMaxNm = repmat(64, 1, 4);
cal.motorShutdownC = repmat(155, 1, 4);
cal.ascThresholdRpm = repmat(1000, 1, 4);
cal.resetBackoffMaxS = 100;

% Conservative host-model defaults; none are identified inverter/motor data.
cal.speedMaxRpm = repmat(20000, 1, 4);
cal.modelCurrentMaxA = repmat(120, 1, 4);
cal.motorDerateStartC = repmat(120, 1, 4);
cal.motorDerateEndC = repmat(150, 1, 4);
cal.motoringEfficiency = repmat(0.90, 1, 4);
cal.regenEfficiency = repmat(0.85, 1, 4);
cal.dcVoltageFloorV = repmat(10, 1, 4);
cal.ambientTemperatureC = repmat(25, 1, 4);
cal.motorThermalTimeConstantS = repmat(30, 1, 4);
cal.switchThermalTimeConstantS = repmat(10, 1, 4);
cal.motorThermalResistanceCPerW = repmat(0.020, 1, 4);
cal.switchThermalResistanceCPerW = repmat(0.010, 1, 4);
cal.motorLossFraction = repmat(0.60, 1, 4);

cal.pedals.releasedV = [NaN NaN NaN NaN];
cal.pedals.pressedV = [NaN NaN NaN NaN];
cal.pedals.minimumV = zeros(1, 4);
cal.pedals.maximumV = repmat(5, 1, 4);
% RAISED from 0.250 (2026-08-19): the GUI's 0.25 s status timer period
% assumed a sub-250 ms host-target round trip. Observed slrealtime
% getParam/setParam round trips on this bench run closer to 1.5 s (the
% timer's own BusyMode='drop' silently absorbed the overrun, so most
% scheduled heartbeat writes never happened rather than erroring visibly).
% 3.0 s stays a genuine staleness check -- it still trips on a truly dead
% GUI or disconnected host -- without tripping on ordinary round-trip
% latency this bench actually has.
cal.guiHeartbeatTimeoutS = 3.0;

inverterhil.validateCalibration(cal);
end
