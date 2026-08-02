function decoded = decodeStatusFrame(id, payload)
%DECODESTATUSFRAME Decode inverter status using the shared HIL definitions.
decoded = struct('known', false, 'id', uint32(id), 'payload', uint8(payload(:)'), ...
    'name', '', 'fields', struct());
if numel(decoded.payload) ~= 8
    return;
end
if any(uint32(id) == virtualvcu.config().statusIds)
    decoded.known = true;
    decoded.name = sprintf('Ephorus status 0x%03X', uint32(id));
    if mod(uint32(id), 16) == 3
        decoded.fields.rawTorqueCounts = double(decoded.payload(3)) + ...
            256 * double(decoded.payload(4));
    end
end
end
