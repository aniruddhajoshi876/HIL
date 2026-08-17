function [accepted, demand, reason] = decodePedalDemandFrame( ...
        canId, dlc, payload, isExtended, isRemote)
%DECODEPEDALDEMANDFRAME Decode the isolated CarMakerPedalDemand CAN frame.
% Wire: 0x500/DLC8; B1/B2 percent, B3 active+counter, B4 CRC-8/J1850,
% B5:B8 reserved zero. Counter is B3 bits 2:5, active is B3 bit 1.
accepted = false;
demand = emptyDemand();
if nargin < 4, isExtended = false; end
if nargin < 5, isRemote = false; end
if ~isBinaryScalar(isExtended) || logical(isExtended), reason = 'extended_frame'; return; end
if ~isBinaryScalar(isRemote) || logical(isRemote), reason = 'remote_frame'; return; end
if ~isnumeric(dlc) || ~isscalar(dlc) || ~isreal(dlc) || ~isfinite(double(dlc)) || double(dlc) ~= 8
    reason = 'wrong_dlc'; return;
end
if ~isa(payload, 'uint8') || ~isequal(size(payload), [1 8])
    reason = 'malformed_payload'; return;
end
if ~(isnumeric(canId) || islogical(canId)) || ~isscalar(canId) || ~isreal(canId) || ...
        ~isfinite(double(canId)) || double(canId) ~= fix(double(canId)) || ...
        double(canId) ~= double(inverterhil.protocol().pedalDemandId)
    reason = 'wrong_id'; return;
end
if payload(1) > uint8(100) || payload(2) > uint8(100), reason = 'out_of_range'; return; end
if bitand(payload(3), uint8(224)) ~= 0 || any(payload(5:8) ~= 0)
    reason = 'reserved_nonzero'; return;
end
if payload(4) ~= crc8(payload(1:3)), reason = 'integrity_failure'; return; end
demand.throttlePercent = double(payload(1));
demand.brakePercent = double(payload(2));
demand.active = bitget(payload(3), 1) ~= 0;
demand.aliveCounter = bitshift(bitand(payload(3), uint8(30)), -1);
accepted = true; reason = 'accepted';
end

function demand = emptyDemand()
demand = struct('throttlePercent', 0, 'brakePercent', 0, 'active', false, ...
    'aliveCounter', uint8(0));
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
    isreal(value) && isfinite(double(value)) && (double(value) == 0 || double(value) == 1);
end
