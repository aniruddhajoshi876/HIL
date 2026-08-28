function decoded = decodeStatusFrame(id, payload)
%DECODESTATUSFRAME Decode physically received Ephorus status fields.
decoded = struct('known', false, 'id', uint32(id), 'payload', uint8(payload(:)'), ...
    'name', '', 'fields', struct());
if numel(decoded.payload) ~= 8
    return;
end

c = virtualvcu.config();
id = uint32(id);
if ~any(id == c.statusIds)
    return;
end
decoded.known = true;
decoded.name = sprintf('Ephorus status 0x%03X', id);
raw = payloadToU64(decoded.payload);

if id == uint32(hex2dec('400'))
    decoded.fields.dcLink12V = double(bitand(raw, uint64(65535))) / 64;
    decoded.fields.dcLink34V = double(bitand(bitshift(raw, -16), uint64(65535))) / 64;
    decoded.fields.dcLinkGood12 = bitget(raw, 49) ~= 0;
    decoded.fields.dcLinkGood34 = bitget(raw, 50) ~= 0;
elseif any(id == uint32(hex2dec({'383','393','3A3','3B3'})))
    decoded.fields.inverterState = uint8(bitand(raw, uint64(3)));
    decoded.fields.inverterReady = bitget(raw, 3) ~= 0;
    decoded.fields.torqueActualNm = signExtend(bitand(bitshift(raw,-16),uint64(4095)),12) / 32;
    decoded.fields.torqueSetpointNm = signExtend(bitand(bitshift(raw,-28),uint64(4095)),12) / 32;
else
    rpm = signExtend(bitand(bitshift(raw,-48),uint64(65535)),16);
    decoded.fields.actualSpeedRpm = rpm;
    decoded.fields.wheelSpeedRadS = rpm * (2*pi/60) / c.gearRatio;
end
end

function raw = payloadToU64(payload)
raw = uint64(0);
for k = 1:8
    raw = bitor(raw, bitshift(uint64(payload(k)), 8*(k-1)));
end
end

function value = signExtend(raw, bits)
value = double(raw);
signBit = 2^(bits-1);
if value >= signBit
    value = value - 2^bits;
end
end
