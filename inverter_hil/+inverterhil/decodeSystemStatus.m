function status = decodeSystemStatus(payload)
%DECODESYSTEMSTATUS Decode the general Ephorus status payload, ID 0x400.
%
%   STATUS = DECODESYSTEMSTATUS(PAYLOAD) reverses INVERTERHIL.PACKSYSTEMSTATUS
%   on a 1x8 uint8 CAN payload. Field offsets, widths and scales below mirror
%   that function line for line; the two must be changed together, and
%   TESTSTATUSPACKERS round-trips them to enforce that.
%
%   Voltages return in 1/64 V steps and the switching frequency in 1/512 kHz
%   steps, matching the frame's own resolution -- these are the quantised
%   values actually on the wire, not the pre-packing floats.
%
%   Bits 52-63 are not assigned by PACKSYSTEMSTATUS and are therefore not
%   reported here. Decoding them would invent a field the transmitter never
%   populates.

if ~isa(payload, 'uint8') || ~isequal(size(payload), [1 8])
    error('inverterhil:MalformedPayload', ...
        'payload must be a 1x8 uint8 row vector.');
end

raw = payloadToU64(payload);

status.dcLink12V = decodeUnsigned(getField(raw, 0, 16), 1 / 64, 16);
status.dcLink34V = decodeUnsigned(getField(raw, 16, 16), 1 / 64, 16);
status.switchingFrequencyKHz = ...
    decodeUnsigned(getField(raw, 32, 16), 1 / 512, 16);
status.dcLink12AboveMinimum = getField(raw, 48, 1) ~= 0;
status.dcLink34AboveMinimum = getField(raw, 49, 1) ~= 0;
status.controlEnable = getField(raw, 50, 1) ~= 0;
status.controlDisable = getField(raw, 51, 1) ~= 0;
end
