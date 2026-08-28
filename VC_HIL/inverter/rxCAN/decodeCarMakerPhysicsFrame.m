function [accepted, decoded, reason] = decodeCarMakerPhysicsFrame( ...
        canId, dlc, payload, isExtended, isRemote)
%DECODECARMAKERPHYSICSFRAME Validate and decode one CarMaker physics frame.
accepted = false;
decoded = struct('id', uint32(0), 'kind', uint8(0), ...
    'values', zeros(1, 3), 'groupCounter', uint8(0));
if nargin < 4, isExtended = false; end
if nargin < 5, isRemote = false; end
if ~isBinaryScalar(isExtended) || logical(isExtended), reason = 'extended_frame'; return; end
if ~isBinaryScalar(isRemote) || logical(isRemote), reason = 'remote_frame'; return; end
if ~isnumeric(dlc) || ~isscalar(dlc) || ~isreal(dlc) || ...
        ~isfinite(double(dlc)) || double(dlc) ~= 8
    reason = 'wrong_dlc'; return;
end
if ~isa(payload, 'uint8') || ~isequal(size(payload), [1 8])
    reason = 'malformed_payload'; return;
end
if ~(isnumeric(canId) || islogical(canId)) || ~isscalar(canId) || ...
        ~isreal(canId) || ~isfinite(double(canId)) || ...
        double(canId) ~= fix(double(canId))
    reason = 'wrong_id'; return;
end
id = uint32(canId);
if id < uint32(hex2dec('503')) || id > uint32(hex2dec('506'))
    reason = 'wrong_id'; return;
end
if payload(8) ~= crc8(payload(1:7)), reason = 'integrity_failure'; return; end

raw = zeros(1, 3, 'int16');
for k = 1:3
    word = bitor(uint16(payload(2*k-1)), bitshift(uint16(payload(2*k)), 8));
    raw(k) = typecast(word, 'int16');
end
kind = uint8(double(id) - hex2dec('502'));
scales = [0.01 0.002 0.01 0.0001];
limits = [100 100 100; 35 35 35; 200 200 200; pi pi/2 pi];
values = double(raw) * scales(kind);
if any(~isfinite(values)) || any(abs(values) > limits(kind, :))
    reason = 'out_of_range'; return;
end
decoded.id = id;
decoded.kind = kind;
decoded.values = values;
decoded.groupCounter = payload(7);
accepted = true;
reason = 'accepted';
end

function value = crc8(bytes)
value = uint8(255);
for index = 1:numel(bytes)
    value = bitxor(value, bytes(index));
    for bit = 1:8
        if bitand(value, uint8(128)) ~= 0
            value = bitxor(bitshift(value, 1), uint8(29));
        else
            value = bitshift(value, 1);
        end
    end
end
value = bitxor(value, uint8(255));
end

function valid = isBinaryScalar(value)
valid = (islogical(value) || isnumeric(value)) && isscalar(value) && ...
    isreal(value) && isfinite(double(value)) && ...
    (double(value) == 0 || double(value) == 1);
end
