function input = defaultChannelStateInput()
%DEFAULTCHANNELSTATEINPUT Quiescent, finite input for one channel step.

input.commandAgeMs = uint32(0);
input.commandEnable = false;
input.resetError = false;
input.ascAllowed = false;
input.currentMode = false;
input.speedRpm = 0;
input.positionAgeS = 0;
input.controlEnable = true;
input.controlDisable = false;
input.dcLinkV = 400;
input.phaseCurrentsA = zeros(1, 3);
input.desaturation = false;
input.motorTemperatureC = 25;
input.switchTemperatureC = 25;
input.idTrackingErrorA = 0;
input.iqTrackingErrorA = 0;
input.phaseCurrentMeasurementFailure = false;
input.dcLinkMeasurementFailure = false;
input.switchTemperatureMeasurementFailure = false;
input.dischargeActive = false;
input.powerCycle = false;
end
