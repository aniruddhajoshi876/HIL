function status = decodeStatus3X3(payload)
%DECODESTATUS3X3 Decode one Ephorus 3X3 status payload.
%
%   STATUS = DECODESTATUS3X3(PAYLOAD) reverses INVERTERHIL.PACKSTATUS3X3 on
%   a 1x8 uint8 CAN payload. Field offsets, widths and scales below mirror
%   that function line for line; the two must be changed together, and
%   TESTSTATUSPACKERS round-trips them to enforce that.
%
%   This exists so the GUI can display what the HIL is ACTUALLY transmitting,
%   decoded from the bytes on the wire, rather than a parallel copy of the
%   model's internal state that could silently diverge from the frame the VCU
%   receives.
%
%   Decoding is quantised, not lossless: torque returns in 1/32 Nm steps and
%   temperatures in 1/8 and 1/16 C steps, because that is the resolution the
%   frame carries. See DECODESIGNED for the saturation caveat.

if ~isa(payload, 'uint8') || ~isequal(size(payload), [1 8])
    error('inverterhil:MalformedPayload', ...
        'payload must be a 1x8 uint8 row vector.');
end

raw = payloadToU64(payload);

status.state = double(getField(raw, 0, 2));
status.ready = logical(getField(raw, 2, 1));
status.derating = logical(getField(raw, 3, 1));
status.maxAllowedCurrentA = decodeUnsigned(getField(raw, 4, 12), 1 / 32, 12);
status.actualTorqueNm = decodeSigned(getField(raw, 16, 12), 1 / 32, 12);
status.torqueSetpointNm = decodeSigned(getField(raw, 28, 12), 1 / 32, 12);
status.motorTemperatureC = decodeSigned(getField(raw, 40, 12), 1 / 8, 12);
status.switchTemperatureC = decodeSigned(getField(raw, 52, 12), 1 / 16, 12);
end
