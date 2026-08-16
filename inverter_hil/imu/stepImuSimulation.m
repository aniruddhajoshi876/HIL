function [next, frame, velocityFrame, eulerFrame] = stepImuSimulation( ...
    previous, timeS, vehicleState, input)
%STEPIMUSIMULATION Sample shared vehicle state and produce MTi frames.
%   This function receives vehicle-state quantities from the independent HIL
%   plant; it does not call or mirror VCU control code.
%
%   FRAME is the acceleration frame (0x034). VELOCITYFRAME is VelocityXYZ
%   (0x076), which the MFE26-VC firmware actively decodes and gates its
%   use_imu_vel_x/y inputs on -- without it the VCU's velocity path receives
%   nothing at all. EULERFRAME (0x022) is encoded only when explicitly asked
%   for: the VCU has no Euler handler, so every such frame it receives just
%   increments its unknown-ID counter. See imuProtocol's defaultOutputRateHz,
%   where eulerAngles defaults to 0 Hz.
if nargin < 1 || isempty(previous)
    previous = struct('sequence', uint32(0));
end
if nargin < 4 || isempty(input)
    input = struct('enabled', true, 'dropout', false);
end
if ~isfield(input, 'enabled')
    input.enabled = true;
end
if ~isfield(input, 'dropout')
    input.dropout = false;
end
next = previous;
next.sequence = previous.sequence + uint32(1);
blank = struct('id', uint32(0), 'dlc', uint8(0), ...
    'payload', zeros(1, 8, 'uint8'), 'timestampS', timeS, ...
    'sequence', next.sequence, 'valid', false, 'kind', '');
frame = blank;
velocityFrame = blank;
eulerFrame = blank;
if ~input.enabled || input.dropout
    return;
end
required = {'accelerationMps2', 'rateOfTurnRadPerS'};
for index = 1:numel(required)
    if ~isfield(vehicleState, required{index})
        error('mti680:MissingVehicleState', ...
            'Vehicle state lacks %s.', required{index});
    end
end
frame = stamp(packMti680Frame('acceleration', ...
    vehicleState.accelerationMps2), timeS, next.sequence);

% VelocityXYZ is emitted whenever the shared state carries a velocity. It is
% not optional in practice: the VCU decodes 0x076 and its controls model
% consumes vy, so a simulator that never sends it leaves that input dead.
if isfield(vehicleState, 'velocityMps')
    velocityFrame = stamp(packMti680Frame('velocityXyz', ...
        vehicleState.velocityMps), timeS, next.sequence);
end

% Off unless the caller opts in, per imuProtocol.defaultOutputRateHz.
if isfield(input, 'eulerEnabled') && input.eulerEnabled && ...
        isfield(vehicleState, 'eulerAnglesDeg')
    eulerFrame = stamp(packMti680Frame('eulerAngles', ...
        vehicleState.eulerAnglesDeg), timeS, next.sequence);
end
end

function frame = stamp(frame, timeS, sequence)
frame.timestampS = timeS;
frame.sequence = sequence;
frame.valid = true;
end
