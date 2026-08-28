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
% Only the three-axis vector messages are packed here. Without this gate the
% scalar entries (groupCounter, sampleTime, statusWord, errorCode) would pass
% the isfield check above and then fail the "three finite values" test with a
% confusing message.
if ~isstruct(item) || ~isfield(item, 'fieldCount') || item.fieldCount ~= 3
    error('mti680:UnknownKind', ...
        'MTi message %s is not a three-axis vector message.', kind);
end
values = double(values(:).');
if numel(values) ~= 3 || any(~isfinite(values))
    error('mti680:InvalidValues', 'MTi vector must contain three finite values.');
end
% The DOCUMENTED physical range is narrower than the int16 encoding limit,
% and the MFE26 VCU rejects the whole frame if any axis exceeds it. Checking
% only the int16 limit would let the simulator emit frames the VCU silently
% drops, which looks like a dead sensor rather than an out-of-range stimulus.
% rangeMax is per axis: a scalar bounds all three, a 1x3 vector bounds each
% axis independently (eulerAngles: roll +/-180, pitch +/-90, yaw +/-180).
if isfield(item, 'rangeMax')
    rangeMax = double(item.rangeMax(:).');
    if isscalar(rangeMax)
        rangeMax = repmat(rangeMax, 1, 3);
    end
    if any(abs(values) > rangeMax)
        error('mti680:DocRange', ...
            ['MTi %s value exceeds the documented per-axis range ' ...
            '[%g %g %g] %s; the VCU discards the entire frame.'], ...
            kind, rangeMax(1), rangeMax(2), rangeMax(3), item.unit);
    end
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
