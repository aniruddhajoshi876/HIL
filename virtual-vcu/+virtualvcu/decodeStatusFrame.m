function decoded = decodeStatusFrame(id, payload)
%DECODESTATUSFRAME Decode inverter status using the shared HIL definitions.
decoded = struct('known', false, 'id', uint32(id), 'payload', uint8(payload(:)'), ...
    'name', '', 'fields', struct());
if numel(decoded.payload) ~= 8
    return;
end
id = uint32(id);
if any(id == virtualvcu.config().statusIds)
    decoded.known = true;
    decoded.name = sprintf('Ephorus status 0x%03X', id);
    if id == uint32(hex2dec('400'))
        decoded.fields.dcLink12V = (double(decoded.payload(1)) + ...
            256 * double(decoded.payload(2))) / 64;
        decoded.fields.dcLink34V = (double(decoded.payload(3)) + ...
            256 * double(decoded.payload(4))) / 64;
        decoded.fields.dcLinkGood12 = bitget(decoded.payload(7), 1) ~= 0;
        decoded.fields.dcLinkGood34 = bitget(decoded.payload(7), 2) ~= 0;
    elseif mod(double(id), 16) == 3
        decoded.fields.inverterState = bitand(decoded.payload(1), uint8(3));
        decoded.fields.inverterReady = bitget(decoded.payload(1), 3) ~= 0;
        decoded.fields.torqueActualNm = typecast(uint16(decoded.payload(3)) + ...
            bitshift(uint16(decoded.payload(4)), 8), 'int16') / 32;
        decoded.fields.torqueSetpointNm = typecast(uint16(decoded.payload(5)) + ...
            bitshift(uint16(decoded.payload(6)), 8), 'int16') / 32;
    end
end
end
