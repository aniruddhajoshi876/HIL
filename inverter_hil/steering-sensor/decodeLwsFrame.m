function measurement = decodeLwsFrame(frame, contract)
%DECODELWSFRAME Decode and validate a Bosch LWS_Standard frame.
if nargin < 2 || isempty(contract)
    contract = lwsProtocol();
end
payload = uint8(frame.payload(:).');
if uint32(frame.id) ~= contract.standardId || numel(payload) < double(contract.standardDlc)
    error('lws:InvalidFrame', 'Frame ID or DLC does not match LWS_Standard.');
end
angleU16 = bitor(uint16(payload(1)), bitshift(uint16(payload(2)), 8));
angleRaw = double(angleU16);
if angleRaw >= 32768
    angleRaw = angleRaw - 65536;
end
speedRaw = double(payload(3));
statusByte = payload(5);
measurement = struct( ...
    'angleDeg', angleRaw * contract.angleScaleDegPerCount, ...
    'speedDegPerS', speedRaw * contract.speedScaleDegPerSPerCount, ...
    'trim', bitand(statusByte, contract.status.trimMask) ~= 0, ...
    'cal', bitand(statusByte, contract.status.calMask) ~= 0, ...
    'ok', bitand(statusByte, contract.status.okMask) ~= 0, ...
    'valid', bitand(statusByte, uint8(7)) == uint8(7));
end
