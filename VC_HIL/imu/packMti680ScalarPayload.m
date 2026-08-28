function payload = packMti680ScalarPayload(kind, value)
%PACKMTI680SCALARPAYLOAD Big-endian payload bytes for one MTi scalar frame.
%   PAYLOAD = PACKMTI680SCALARPAYLOAD(KIND, VALUE) returns just the packed
%   bytes for one of the scalar MTi messages -- groupCounter (0x006, 2
%   bytes), sampleTime (0x005, 4), statusWord (0x011, 4) or errorCode
%   (0x001, 1). KIND selects the message; VALUE is one non-negative integer.
%
%   Payload-only companion to PACKMTI680SCALARFRAME, shaped like
%   PACKMTI680PAYLOAD is to PACKMTI680FRAME: no id/dlc, no heterogeneous
%   struct, and no run-time INTMAX(format) call, so the deployed model's
%   "Scalar Sensor Payloads" MATLAB Function block can call it on its
%   codegen path. TESTSENSORPROTOCOL asserts byte-for-byte agreement with
%   PACKMTI680SCALARFRAME so the two encoders cannot silently diverge.

switch lower(char(kind))
    case 'groupcounter'
        nBytes = 2;
        maxValue = 65535;
    case 'sampletime'
        nBytes = 4;
        maxValue = 4294967295;
    case 'statusword'
        nBytes = 4;
        maxValue = 4294967295;
    case 'errorcode'
        nBytes = 1;
        maxValue = 255;
    otherwise
        error('mti680:UnsupportedPayload', ...
            'Unsupported MTi scalar payload kind.');
end

numericValue = double(value);
if ~isscalar(numericValue) || ~isfinite(numericValue) || ...
        numericValue < 0 || mod(numericValue, 1) ~= 0 || ...
        numericValue > maxValue
    error('mti680:PayloadRange', ...
        'MTi scalar payload requires one integer inside the message range.');
end

raw = uint64(numericValue);
payload = zeros(1, nBytes, 'uint8');
for index = 1:nBytes
    shift = 8 * (nBytes - index);
    payload(index) = uint8(bitand(bitshift(raw, -shift), uint64(255)));
end
end
