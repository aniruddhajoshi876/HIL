function [accepted, channel, command, reason] = decodeControlFrame( ...
        canId, dlc, payload, isExtended, isRemote)
%DECODECONTROLFRAME Decode one standard, data, DLC-8 Ephorus command.

if nargin < 4
    isExtended = false;
end
if nargin < 5
    isRemote = false;
end

accepted = false;
channel = uint8(0);
command = emptyCommand();

if ~isBinaryScalar(isExtended) || logical(isExtended)
    reason = 'extended_frame';
    return;
end
if ~isBinaryScalar(isRemote) || logical(isRemote)
    reason = 'remote_frame';
    return;
end
if ~isnumeric(dlc) || ~isscalar(dlc) || ~isreal(dlc) || ...
        ~isfinite(double(dlc)) || double(dlc) ~= 8
    reason = 'wrong_dlc';
    return;
end

if ~isa(payload, 'uint8') || ~isequal(size(payload), [1 8])
    reason = 'malformed_payload';
    return;
end
if ~(isnumeric(canId) || islogical(canId)) || ~isscalar(canId) || ...
        ~isreal(canId) || ~isfinite(double(canId)) || ...
        double(canId) ~= fix(double(canId)) || ...
        double(canId) < 0 || double(canId) > hex2dec('7FF')
    reason = 'wrong_id';
    return;
end

p = protocol();
index = find(p.controlIds == uint32(canId), 1);
if isempty(index)
    reason = 'wrong_id';
    return;
end

flags = payload(1);
command.enable = bitget(flags, 1) ~= 0;
command.resetError = bitget(flags, 2) ~= 0;
command.ascAllowed = bitget(flags, 3) ~= 0;
command.currentMode = bitget(flags, 4) ~= 0;
command.speedSetpointRpm = decodeI16(payload(3), payload(4));
command.rawTorquePosCounts = decodeI16(payload(5), payload(6));
command.rawTorqueNegCounts = decodeI16(payload(7), payload(8));
command.torquePosNm256 = double(command.rawTorquePosCounts) / 256;
command.torqueNegNm256 = double(command.rawTorqueNegCounts) / 256;
command.torquePosNm512 = double(command.rawTorquePosCounts) / 512;
command.torqueNegNm512 = double(command.rawTorqueNegCounts) / 512;
command.reservedRaw = uint16(payload(2)) + ...
    bitshift(uint16(bitand(payload(1), uint8(240))), 4);

accepted = true;
channel = uint8(index);
reason = 'accepted';
end

function command = emptyCommand()
command = struct( ...
    'enable', false, ...
    'resetError', false, ...
    'ascAllowed', false, ...
    'currentMode', false, ...
    'speedSetpointRpm', int16(0), ...
    'rawTorquePosCounts', int16(0), ...
    'rawTorqueNegCounts', int16(0), ...
    'torquePosNm256', 0, ...
    'torqueNegNm256', 0, ...
    'torquePosNm512', 0, ...
    'torqueNegNm512', 0, ...
    'reservedRaw', uint16(0));
end

function value = decodeI16(lowByte, highByte)
raw = uint16(lowByte) + bitshift(uint16(highByte), 8);
if raw >= uint16(32768)
    value = int16(int32(raw) - 65536);
else
    value = int16(raw);
end
end

function valid = isBinaryScalar(value)
valid = (islogical(value) || isnumeric(value)) && isscalar(value) && ...
    isreal(value) && isfinite(double(value)) && ...
    (double(value) == 0 || double(value) == 1);
end
