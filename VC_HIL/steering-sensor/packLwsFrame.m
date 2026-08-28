function frame = packLwsFrame(angleDeg, speedDegPerS, status, contract)
%PACKLWSFRAME Encode an independent Bosch LWS_Standard frame.
%   Layout, from the Bosch F02U.V02.894-01 datasheet CAN Message table
%   (references/sensors/datasheets/, and the independently derived vectors
%   in references/sensors/golden_vectors/lws/):
%
%     byte 0-1  LWS_ANGLE, int16 little-endian, 0.1 deg/count
%     byte 2    LWS_SPEED, uint8, 4 deg/s per count
%     byte 3    bits 7:3 reserved, bit 2 TRIM, bit 1 CAL, bit 0 OK
%     byte 4    reserved
%
%   The status bits are not free-form. The datasheet truth table fixes what
%   ANGLE and SPEED carry for each permitted TRIM/OK/CAL combination and
%   declares every other combination invalid:
%
%     TRIM OK CAL   ANGLE    SPEED
%       1  1  1     value    value    calibrated, information valid
%       1  1  0     0x7FFF   value    not calibrated, speed still valid
%       1  0  0     0x7FFF   0xFF     failure mode
%       0  0  0     0x7FFF   0xFF     failure mode
%
%   Enforcing it here is what lets the GUI inject a fault and get the frame
%   a real sensor would actually put on the wire, instead of a live
%   measurement with the status bits quietly cleared.
if nargin < 4 || isempty(contract)
    contract = lwsProtocol();
end
if nargin < 3 || isempty(status)
    status = struct('trim', true, 'cal', true, 'ok', true);
end
trim = logical(status.trim);
cal = logical(status.cal);
ok = logical(status.ok);

% Datasheet column order is TRIM, OK, CAL -- not TRIM, CAL, OK.
combination = [trim, ok, cal];
if isequal(combination, [true true true])
    angleIsSentinel = false;
    speedIsSentinel = false;
elseif isequal(combination, [true true false])
    angleIsSentinel = true;
    speedIsSentinel = false;
elseif isequal(combination, [true false false]) || ...
        isequal(combination, [false false false])
    angleIsSentinel = true;
    speedIsSentinel = true;
else
    error('lws:InvalidStatusCombination', ...
        ['TRIM=%d OK=%d CAL=%d is listed under "Other combinations for ' ...
        'TRIM, OK and CAL are not valid".'], trim, ok, cal);
end

% Only the fields actually transmitted are range checked. A sentinel frame
% carries no measurement, so an out-of-range angle handed in alongside a
% failure status is not an error -- it is simply not on the wire.
if ~angleIsSentinel
    if ~isscalar(angleDeg) || ~isfinite(angleDeg) || ...
            angleDeg < contract.minimumAngleDeg || ...
            angleDeg > contract.maximumAngleDeg
        error('lws:AngleRange', 'LWS angle is outside the Bosch range.');
    end
    angleRaw = round(double(angleDeg) / contract.angleScaleDegPerCount);
    if angleRaw < -32768 || angleRaw > 32767
        error('lws:RawRange', 'LWS angle cannot be represented on the wire.');
    end
else
    angleRaw = double(contract.angleFailureSentinel);
end

if ~speedIsSentinel
    if ~isscalar(speedDegPerS) || ~isfinite(speedDegPerS) || ...
            speedDegPerS < contract.minimumSpeedDegPerS || ...
            speedDegPerS > contract.maximumSpeedDegPerS
        error('lws:SpeedValue', 'LWS speed is outside the Bosch range.');
    end
    speedRaw = round(double(speedDegPerS) / contract.speedScaleDegPerSPerCount);
    % 1016/4 = 254 is the top of the documented range; 255 is reserved as
    % the failure sentinel and must never be produced by a live reading.
    if speedRaw < 0 || speedRaw >= double(contract.speedFailureSentinel)
        error('lws:RawRange', 'LWS speed cannot be represented on the wire.');
    end
else
    speedRaw = double(contract.speedFailureSentinel);
end

statusByte = uint8(0);
statusByte = statusByte + uint8(trim) * contract.status.trimMask;
statusByte = statusByte + uint8(cal) * contract.status.calMask;
statusByte = statusByte + uint8(ok) * contract.status.okMask;
angleU16 = uint16(mod(int32(angleRaw), 65536));
% Byte 3 is the status byte and byte 4 is reserved. Writing the status into
% byte 4 instead would round-trip through a matching decoder and still be
% wrong on the wire.
payload = uint8([bitand(angleU16, 255), bitshift(angleU16, -8), ...
    uint8(speedRaw), statusByte, 0]);
if angleIsSentinel
    reportedAngleDeg = NaN;
else
    reportedAngleDeg = double(angleRaw) * contract.angleScaleDegPerCount;
end
if speedIsSentinel
    reportedSpeedDegPerS = NaN;
else
    reportedSpeedDegPerS = double(speedRaw) * ...
        contract.speedScaleDegPerSPerCount;
end
frame = struct('id', contract.standardId, 'dlc', contract.standardDlc, ...
    'payload', payload, 'angleDeg', reportedAngleDeg, ...
    'speedDegPerS', reportedSpeedDegPerS, ...
    'status', struct('trim', trim, 'cal', cal, 'ok', ok), ...
    'angleIsSentinel', angleIsSentinel, ...
    'speedIsSentinel', speedIsSentinel, 'timestampS', NaN);
end
