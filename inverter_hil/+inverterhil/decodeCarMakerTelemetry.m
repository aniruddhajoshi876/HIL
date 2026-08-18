function telemetry = decodeCarMakerTelemetry(torquePayload, readyPayload)
%DECODECARMAKERTELEMETRY Decode CarMaker telemetry IDs 0x501 and 0x502.

validatePayload(torquePayload, 'torquePayload');
validatePayload(readyPayload, 'readyPayload');
torqueRaw = payloadToU64(torquePayload);
readyRaw = payloadToU64(readyPayload);

if bitand(readyPayload(1), uint8(240)) ~= 0 || any(readyPayload(2:8) ~= 0)
    error('inverterhil:ReservedBits', ...
        '0x502 reserved bits 4..63 must be zero.');
end

telemetry.torqueSetpointNm = zeros(1, 4);
telemetry.ready = false(1, 4);
for channel = 1:4
    telemetry.torqueSetpointNm(channel) = decodeSigned( ...
        getField(torqueRaw, 16 * (channel - 1), 16), 1 / 32, 16);
    telemetry.ready(channel) = logical(getField(readyRaw, channel - 1, 1));
end
end

function validatePayload(payload, name)
if ~isa(payload, 'uint8') || ~isequal(size(payload), [1 8])
    error('inverterhil:MalformedPayload', ...
        '%s must be a 1x8 uint8 row vector.', name);
end
end
