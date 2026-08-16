function measurement = decodeLwsFrame(frame, contract)
%DECODELWSFRAME Decode and validate a Bosch LWS_Standard frame.
%   The status byte is datasheet byte 3 (MATLAB index 4) and byte 4 is
%   reserved. See PACKLWSFRAME for the full layout and truth table.
if nargin < 2 || isempty(contract)
    contract = lwsProtocol();
end
payload = uint8(frame.payload(:).');
if uint32(frame.id) ~= contract.standardId || ...
        numel(payload) < double(contract.standardDlc)
    error('lws:InvalidFrame', 'Frame ID or DLC does not match LWS_Standard.');
end
angleU16 = bitor(uint16(payload(contract.byteIndex.angleLow)), ...
    bitshift(uint16(payload(contract.byteIndex.angleHigh)), 8));
speedRaw = payload(contract.byteIndex.speed);
statusByte = payload(contract.byteIndex.status);

trim = bitand(statusByte, contract.status.trimMask) ~= 0;
cal = bitand(statusByte, contract.status.calMask) ~= 0;
ok = bitand(statusByte, contract.status.okMask) ~= 0;

% Only the four rows of the datasheet truth table are legal. Anything else
% is reported rather than silently decoded as if it were a measurement.
combination = [trim, ok, cal];
statusCombinationValid = isequal(combination, [true true true]) || ...
    isequal(combination, [true true false]) || ...
    isequal(combination, [true false false]) || ...
    isequal(combination, [false false false]);

angleIsSentinel = angleU16 == contract.angleFailureSentinel;
speedIsSentinel = speedRaw == contract.speedFailureSentinel;

if angleIsSentinel
    angleDeg = NaN;
else
    angleRaw = double(angleU16);
    if angleRaw >= 32768
        angleRaw = angleRaw - 65536;
    end
    angleDeg = angleRaw * contract.angleScaleDegPerCount;
end
if speedIsSentinel
    speedDegPerS = NaN;
else
    speedDegPerS = double(speedRaw) * contract.speedScaleDegPerSPerCount;
end

measurement = struct( ...
    'angleDeg', angleDeg, ...
    'speedDegPerS', speedDegPerS, ...
    'trim', trim, ...
    'cal', cal, ...
    'ok', ok, ...
    'statusCombinationValid', statusCombinationValid, ...
    'angleIsSentinel', angleIsSentinel, ...
    'speedIsSentinel', speedIsSentinel, ...
    'reservedByte', payload(contract.byteIndex.reserved), ...
    'valid', statusCombinationValid && trim && cal && ok && ...
        ~angleIsSentinel && ~speedIsSentinel);
end
