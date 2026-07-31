function cal = defaultCalibration()
%DEFAULTCALIBRATION Conservative, explicit, non-identified model defaults.

p = inverterhil.protocol();
cal.sampleTimeS = 1e-3;
cal.protocolProfileId = p.torqueProfiles.provisional512.id;
cal.torqueScaleNmPerCount = p.torqueProfiles.provisional512.scaleNmPerCount;
cal.torqueScaleVerified = p.torqueProfiles.provisional512.verified;
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
cal.guiHeartbeatTimeoutS = 0.250;

inverterhil.validateCalibration(cal);
end
