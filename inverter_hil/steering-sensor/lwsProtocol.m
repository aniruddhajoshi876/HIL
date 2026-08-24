function p = lwsProtocol()
%PROTOCOL Independent Bosch F02U.V02.894-01 LWS CAN contract.
%   This runs inside a MATLAB Function block, so every field must be created
%   before ANY field of P is read: code generation rejects a struct that
%   grows after it has been read or used. Values that are derived from
%   another field therefore come from a local variable, never from P itself.
updatePeriodS = 0.010;
p.standardId = uint32(hex2dec('2B0'));
p.standardDlc = uint8(5);
p.configId = uint32(hex2dec('7C0'));
p.configDlc = uint8(2);
p.updatePeriodS = updatePeriodS;
p.angleScaleDegPerCount = 0.1;
p.speedScaleDegPerSPerCount = 4;
p.minimumAngleDeg = -780;
p.maximumAngleDeg = 780;
p.minimumSpeedDegPerS = 0;
p.maximumSpeedDegPerS = 1016;
p.ccwResetCalibration = uint8(hex2dec('05'));
p.ccwZeroAngle = uint8(hex2dec('03'));
% Bosch specifies ordering but no delay. The target sequencer's conservative
% HIL policy waits ten standard-frame periods before its reset result check.
p.calibrationInterCommandS = 0.100;
p.calibrationResultCheckPeriodS = updatePeriodS;
p.calibrationResultTimeoutS = 0.100;
p.status.trimMask = uint8(4);
p.status.calMask = uint8(2);
p.status.okMask = uint8(1);
% Byte offsets, 1-based for MATLAB indexing. The datasheet numbers these
% bytes 0-4; the status byte is datasheet byte 3, NOT byte 4.
p.byteIndex.angleLow = 1;
p.byteIndex.angleHigh = 2;
p.byteIndex.speed = 3;
p.byteIndex.status = 4;
p.byteIndex.reserved = 5;
% Truth-table sentinels: whenever the status combination says a value is
% not valid, the sensor transmits these instead of a measurement.
p.angleFailureSentinel = uint16(hex2dec('7FFF'));
p.speedFailureSentinel = uint8(hex2dec('FF'));
% The four legal status bytes. Datasheet column order is TRIM, OK, CAL.
p.status.calibratedByte   = uint8(7);  % TRIM=1 OK=1 CAL=1, angle+speed valid
p.status.uncalibratedByte = uint8(5);  % TRIM=1 OK=1 CAL=0, angle = sentinel
p.status.failureByte      = uint8(4);  % TRIM=1 OK=0 CAL=0, both = sentinel
p.status.failureAltByte   = uint8(0);  % TRIM=0 OK=0 CAL=0, both = sentinel
% LWS_SPEED is UNSIGNED: 0..254 counts, 0xFF = invalid. The MFE26-VC driver
% casts it to int8_t, which corrupts every value above 508 deg/s -- finding
% D-L1 in references/sensors/imu_contract_delta.md. That is a firmware bug,
% not a simulator one; this encoder emits the correct unsigned byte.
p.speedSigned = false;
p.speedMaxRaw = uint8(254);
p.byteOrder = 'little';   % stated explicitly: "Byte order LSB (Intel)"
p.bitrateBitsPerSecond = 500000;
end
