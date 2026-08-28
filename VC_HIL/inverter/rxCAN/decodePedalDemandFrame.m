function [accepted, demand, reason] = decodePedalDemandFrame( ...
        canId, dlc, payload, isExtended, isRemote)
%DECODEPEDALDEMANDFRAME Decode the isolated CarMakerPedalDemand CAN frame.
% Wire contract: see inverter_hil/docs/can_pedal_demand_frame_spec.m~2.
% 0x500/DLC8, Intel/little-endian. B1:B2 throttle uint16 raw 0..10000 at
% 0.01 %/bit; B3:B4 brake likewise; B5 bit0 active, bits1..4 alive counter,
% bits5..7 reserved zero; B6 CRC-8/SAE-J1850 over B1..B5; B7:B8 reserved zero.
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
        double(canId) ~= double(protocol().pedalDemandId)
    reason = 'wrong_id'; return;
end

% Least-significant byte first, per the Intel/little-endian wire convention.
throttleRaw = double(payload(1)) + 256 * double(payload(2));
brakeRaw = double(payload(3)) + 256 * double(payload(4));
if throttleRaw > 10000 || brakeRaw > 10000, reason = 'out_of_range'; return; end

% Both reserved regions must be zero: B5 bits 5..7 and the whole of B7:B8.
if bitand(payload(5), uint8(224)) ~= 0 || any(payload(7:8) ~= 0)
    reason = 'reserved_nonzero'; return;
end
if payload(6) ~= crc8(payload(1:5)), reason = 'integrity_failure'; return; end

demand.throttlePercent = throttleRaw * 0.01;
demand.brakePercent = brakeRaw * 0.01;
demand.active = bitget(payload(5), 1) ~= 0;
demand.aliveCounter = bitshift(bitand(payload(5), uint8(30)), -1);
accepted = true; reason = 'accepted';
end

function demand = emptyDemand()
demand = struct('throttlePercent', 0, 'brakePercent', 0, 'active', false, ...
    'aliveCounter', uint8(0));
end

function value = crc8(bytes)
% CRC-8/SAE-J1850: width 8, poly 0x1D, init 0xFF, no reflection, final XOR 0xFF.
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
