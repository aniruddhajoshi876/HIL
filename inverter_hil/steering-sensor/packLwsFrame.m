function frame = packLwsFrame(angleDeg, speedDegPerS, status, contract)
%PACKLWSFRAME Encode an independent Bosch LWS_Standard frame.
if nargin < 4 || isempty(contract)
    contract = lwsProtocol();
end
if nargin < 3 || isempty(status)
    status = struct('trim', true, 'cal', true, 'ok', true);
end
if ~isscalar(angleDeg) || ~isfinite(angleDeg) || ...
        angleDeg < contract.minimumAngleDeg || angleDeg > contract.maximumAngleDeg
    error('lws:AngleRange', 'LWS angle is outside the Bosch range.');
end
if ~isscalar(speedDegPerS) || ~isfinite(speedDegPerS) || ...
        speedDegPerS < contract.minimumSpeedDegPerS || ...
        speedDegPerS > contract.maximumSpeedDegPerS
    error('lws:SpeedValue', 'LWS speed is outside the Bosch range.');
end
angleRaw = round(double(angleDeg) / contract.angleScaleDegPerCount);
speedRaw = round(double(speedDegPerS) / contract.speedScaleDegPerSPerCount);
if angleRaw < -32768 || angleRaw > 32767 || speedRaw < 0 || speedRaw > 255
    error('lws:RawRange', 'LWS value cannot be represented on the wire.');
end
statusByte = uint8(0);
statusByte = statusByte + uint8(logical(status.trim)) * contract.status.trimMask;
statusByte = statusByte + uint8(logical(status.cal)) * contract.status.calMask;
statusByte = statusByte + uint8(logical(status.ok)) * contract.status.okMask;
angleU16 = uint16(mod(int32(angleRaw), 65536));
payload = uint8([bitand(angleU16, 255), bitshift(angleU16, -8), ...
    uint8(speedRaw), 0, statusByte]);
frame = struct('id', contract.standardId, 'dlc', contract.standardDlc, ...
    'payload', payload, 'angleDeg', double(angleRaw) * contract.angleScaleDegPerCount, ...
    'speedDegPerS', double(speedRaw) * contract.speedScaleDegPerSPerCount, ...
    'status', status, 'timestampS', NaN);
end
