function [accepted, decoded, reason] = decodeCarMakerSteeringFrame( ...
        canId, dlc, payload, isExtended, isRemote)
%DECODECARMAKERSTEERINGFRAME Validate and decode the 0x507 CarMakerSteeringTruth
%   transport frame (Fanatec / driver steering-wheel position, CarMaker ->
%   SpeedgoatHIL on the CarMaker bus / IO614 channel 1). Mirrors
%   DECODECARMAKERPHYSICSFRAME:
%
%     bytes 0-1  SteeringWheelAngleRad  signed Intel int16, 0.001 rad/bit
%     bytes 2-5  reserved, must be zero
%     byte  6    modulo-256 truth-group counter, THE SAME counter 0x503-0x506
%                carry: IO_Out() samples the physics group and this frame in
%                one 10 ms cycle and stamps them with one counter
%     byte  7    CRC-8/SAE-J1850 over bytes 0-6 (poly 0x1D, init 0xFF,
%                non-reflected, xorout 0xFF)
%
%   RADIANS is the wire unit, because radians is the unit of the CarMaker
%   source quantity Steer.WhlAng. Nothing on the CarMaker side scales it, so
%   nothing here has to unscale it. The degree conversion happens once,
%   downstream, immediately before Bosch LWS encoding -- DECODED carries both
%   so callers never re-derive the factor.
%
%   0.001 rad/count spans +/-32.767 rad in an int16, comfortably covering the
%   +/-105 deg active Fanatec Device.0 range, the +/-450 deg disabled
%   Device.1 range, and the Bosch LWS +/-780 deg measuring range.
%
%   The accepted physical range is the Bosch LWS limit expressed in whole
%   counts: 780 deg is 13.6135... rad, which rounds to 13614 counts, so the
%   limit checked here is 13.614 rad rather than the unrounded conversion. A
%   strict 780-deg test would reject the sender's own saturation value.
%   Anything beyond that is a sender fault and is rejected, leaving the
%   previously retained value in place -- the same policy
%   DECODECARMAKERPHYSICSFRAME uses for a physically impossible value.
%
%   No angular-speed field is decoded because none is transmitted: Bosch
%   LWS_SPEED is derived on this side from successive 10 ms samples of this
%   angle (see BUILD_INVERTER_HIL_MODEL's SENSORPAYLOADSCRIPT), so a
%   transported rate would be a second, redundant source of one quantity.
accepted = false;
decoded = struct('id', uint32(0), 'angleRad', 0, 'angleDeg', 0, ...
    'groupCounter', uint8(0));
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
if any(payload(3:6) ~= 0)
    reason = 'reserved_nonzero'; return;
end
if payload(8) ~= crc8(payload(1:7)), reason = 'integrity_failure'; return; end

angleWord = bitor(uint16(payload(1)), bitshift(uint16(payload(2)), 8));
angleRad = double(typecast(angleWord, 'int16')) * 0.001;
% 13.614 rad = 13614 counts = the count-quantised Bosch LWS +/-780 deg limit.
if ~isfinite(angleRad) || abs(angleRad) > 13.614
    reason = 'out_of_range'; return;
end

decoded.id = id;
decoded.angleRad = angleRad;
decoded.angleDeg = angleRad * (180 / pi);
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
