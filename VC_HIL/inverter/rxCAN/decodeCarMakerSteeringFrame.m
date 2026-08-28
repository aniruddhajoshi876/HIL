function [accepted, decoded, reason] = decodeCarMakerSteeringFrame( ...
        canId, dlc, payload, isExtended, isRemote)
%DECODECARMAKERSTEERINGFRAME Validate and decode the 0x507 CarMakerDriverSteering
%   transport frame (Fanatec / driver steering-wheel position, CarMaker ->
%   SpeedgoatHIL on the CarMaker bus). Mirrors DECODECARMAKERPHYSICSFRAME:
%
%     bytes 0-1  SteeringWheelAngleDeg       signed Intel int16, 0.1 deg/bit
%     bytes 2-3  SteeringWheelSpeedDegPerSec signed Intel int16, 0.5 (deg/s)/bit
%     bytes 4-5  reserved, must be zero
%     byte  6    own modulo-256 alive counter (NOT the physics group counter)
%     byte  7    CRC-8/SAE-J1850 over bytes 0-6 (poly 0x1D, init 0xFF,
%                non-reflected, xorout 0xFF)
%
%   The angle is saturated to the Bosch LWS +/-780 deg range by TorqueVect.mdl
%   before transmission; an angle outside that range here is a sender fault
%   and is rejected (previous retained value kept), the same policy
%   DECODECARMAKERPHYSICSFRAME uses for a physically impossible value.
accepted = false;
decoded = struct('id', uint32(0), 'angleDeg', 0, 'speedDegPerSec', 0, ...
    'aliveCounter', uint8(0));
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
if id ~= uint32(hex2dec('507'))
    reason = 'wrong_id'; return;
end
if any(payload(5:6) ~= 0)
    reason = 'reserved_nonzero'; return;
end
if payload(8) ~= crc8(payload(1:7)), reason = 'integrity_failure'; return; end

angleWord = bitor(uint16(payload(1)), bitshift(uint16(payload(2)), 8));
speedWord = bitor(uint16(payload(3)), bitshift(uint16(payload(4)), 8));
angleDeg = double(typecast(angleWord, 'int16')) * 0.1;
speedDegPerSec = double(typecast(speedWord, 'int16')) * 0.5;
if ~isfinite(angleDeg) || abs(angleDeg) > 780
    reason = 'out_of_range'; return;
end
if ~isfinite(speedDegPerSec) || abs(speedDegPerSec) > 3600
    reason = 'out_of_range'; return;
end

decoded.id = id;
decoded.angleDeg = angleDeg;
decoded.speedDegPerSec = speedDegPerSec;
decoded.aliveCounter = payload(7);
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
