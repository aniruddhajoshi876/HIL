function frame = packMti680ScalarFrame(kind, value, contract)
%PACKMTI680SCALARFRAME Encode one MTi scalar (uintN) CAN output frame.
%   FRAME = PACKMTI680SCALARFRAME(KIND, VALUE, CONTRACT) returns id, dlc and
%   payload for one of the scalar MTi messages -- groupCounter (0x006),
%   sampleTime (0x005), statusWord (0x011) or errorCode (0x001). These carry
%   a single big-endian UNSIGNED integer, not the three int16 fields
%   packMti680Frame handles, so they get their own packer. Formats and DLCs
%   follow MT1604P sections 6.1.1-6.1.3 and 6.2.1.
%
%   The returned struct has the same shape packMti680Frame returns
%   (id, dlc, payload, kind, values, timestampS), so stepImuSimulation's
%   stamp helper and imuNormalizeFrame accept it unchanged.
if nargin < 3 || isempty(contract)
    contract = imuProtocol();
end
if ~(ischar(kind) || isstring(kind)) || ~isscalar(string(kind))
    error('mti680:InvalidKind', 'kind must name one MTi message.');
end
kind = char(kind);
if ~isfield(contract, kind)
    error('mti680:UnknownKind', 'Unsupported MTi message kind: %s.', kind);
end
item = contract.(kind);
% Reject the vector messages here the same way packMti680Frame rejects the
% scalar ones: a scalar message is the one with fieldCount 1 and a format.
if ~isstruct(item) || ~isfield(item, 'fieldCount') || item.fieldCount ~= 1 ...
        || ~isfield(item, 'format')
    error('mti680:UnknownKind', ...
        'MTi message %s is not a scalar message.', kind);
end
value = double(value);
if ~isscalar(value) || ~isfinite(value) || value < 0 || mod(value, 1) ~= 0
    error('mti680:InvalidValues', ...
        'MTi scalar %s requires one non-negative integer value.', kind);
end
format = char(item.format);   % 'uint8' | 'uint16' | 'uint32'
if value > double(intmax(format))
    error('mti680:Range', ...
        'MTi scalar %s value exceeds the %s range.', kind, format);
end
nBytes = double(item.dlc);
raw = uint64(value);
payload = zeros(1, nBytes, 'uint8');
for index = 1:nBytes
    shift = 8 * (nBytes - index);
    payload(index) = uint8(bitand(bitshift(raw, -shift), uint64(255)));
end
frame = struct('id', item.id, 'dlc', item.dlc, 'payload', payload, ...
    'kind', kind, 'values', value, 'timestampS', NaN);
end
