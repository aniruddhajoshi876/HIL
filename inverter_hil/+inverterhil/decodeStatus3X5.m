function status = decodeStatus3X5(payload)
%DECODESTATUS3X5 Decode one Ephorus 3X5 status payload.
%
%   STATUS = DECODESTATUS3X5(PAYLOAD) reverses INVERTERHIL.PACKSTATUS3X5 on
%   a 1x8 uint8 CAN payload. Field offsets, widths and scales below mirror
%   that function line for line; the two must be changed together, and
%   TESTSTATUSPACKERS round-trips them to enforce that.
%
%   Currents return in 1/16 A steps and speed in whole rpm, matching the
%   frame's own resolution. See DECODESIGNED for the saturation caveat.

if ~isa(payload, 'uint8') || ~isequal(size(payload), [1 8])
    error('inverterhil:MalformedPayload', ...
        'payload must be a 1x8 uint8 row vector.');
end

raw = payloadToU64(payload);

status.idSetpointA = decodeSigned(getField(raw, 0, 12), 1 / 16, 12);
status.idActualA = decodeSigned(getField(raw, 12, 12), 1 / 16, 12);
status.iqSetpointA = decodeSigned(getField(raw, 24, 12), 1 / 16, 12);
status.iqActualA = decodeSigned(getField(raw, 36, 12), 1 / 16, 12);
status.speedRpm = decodeSigned(getField(raw, 48, 16), 1, 16);
end
