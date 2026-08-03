function frame = packMti680Frame(kind, values, contract)
%PACKMTI680FRAME Encode one independent MTi CAN output frame.
%   FRAME = PACKMTI680FRAME(KIND, VALUES, CONTRACT) returns ID, DLC, and
%   payload fields. KIND is acceleration, rateOfTurn, or eulerAngles.

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
values = double(values(:).');
if numel(values) ~= 3 || any(~isfinite(values))
    error('mti680:InvalidValues', 'MTi vector must contain three finite values.');
end
counts = round(values ./ item.scale);
if any(counts < -32768 | counts > 32767)
    error('mti680:Range', 'MTi value exceeds signed int16 range.');
end

payload = zeros(1, double(item.dlc), 'uint8');
for index = 1:3
    raw = uint16(mod(int32(counts(index)), 65536));
    offset = 2 * index - 1;
    payload(offset) = uint8(bitshift(raw, -8));
    payload(offset + 1) = uint8(bitand(raw, 255));
end
frame = struct('id', item.id, 'dlc', item.dlc, 'payload', payload, ...
    'kind', kind, 'values', values, 'timestampS', NaN);
end
