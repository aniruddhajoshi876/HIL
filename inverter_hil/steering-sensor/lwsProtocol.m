function p = lwsProtocol()
%PROTOCOL Independent Bosch F02U.V02.894-01 LWS CAN contract.
p.standardId = uint32(hex2dec('2B0'));
p.standardDlc = uint8(5);
p.configId = uint32(hex2dec('7C0'));
p.configDlc = uint8(2);
p.updatePeriodS = 0.010;
p.angleScaleDegPerCount = 0.1;
p.speedScaleDegPerSPerCount = 4;
p.minimumAngleDeg = -780;
p.maximumAngleDeg = 780;
p.minimumSpeedDegPerS = 0;
p.maximumSpeedDegPerS = 1016;
p.ccwResetCalibration = uint8(hex2dec('05'));
p.ccwZeroAngle = uint8(hex2dec('03'));
p.status.trimMask = uint8(4);
p.status.calMask = uint8(2);
p.status.okMask = uint8(1);
end
