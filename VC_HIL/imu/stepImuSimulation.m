function [next, frame, velocityFrame, eulerFrame, rateOfTurnFrame, ...
    scalarFrames] = stepImuSimulation(previous, timeS, vehicleState, input)
%STEPIMUSIMULATION Sample shared vehicle state and produce MTi frames.
%   This function receives vehicle-state quantities from the independent HIL
%   plant; it does not call or mirror VCU control code.
%
%   Every quantity is first passed through mountingTransform: the physical
%   MTi-680G is mounted rotated 180 deg about the vehicle Z (yaw) axis, so
%   the frames produced here are what the real backwards sensor would emit,
%   not the raw vehicle-frame values.
%
%   Outputs:
%     FRAME           acceleration (0x034).
%     VELOCITYFRAME   VelocityXYZ (0x076) -- the MFE26-VC firmware decodes
%                     this and gates use_imu_vel_x/y on it. Emitted only when
%                     the shared state carries velocityMps.
%     EULERFRAME      EulerAngles (0x022) -- the VCU has no Euler handler, so
%                     every such frame just increments its unknown-ID
%                     counter. Encoded only when input.eulerEnabled is set;
%                     imuProtocol.defaultOutputRateHz.eulerAngles is 0 Hz.
%     RATEOFTURNFRAME rate of turn (0x032) -- decoded by the VCU, in
%                     imuProtocol.decodedByVcu, so it is always emitted.
%     SCALARFRAMES    1x4 struct array of the scalar messages the MTi groups
%                     with every inertial sample: groupCounter (0x006,
%                     increments once per group), sampleTime (0x005,
%                     microsecond uint32 timestamp), statusWord (0x011,
%                     nominal "all good"), errorCode (0x001, nominal 0x00).
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
contract = imuProtocol();
next = previous;
next.sequence = previous.sequence + uint32(1);
blank = struct('id', uint32(0), 'dlc', uint8(0), ...
    'payload', zeros(1, 8, 'uint8'), 'timestampS', timeS, ...
    'sequence', next.sequence, 'valid', false, 'kind', '');
frame = blank;
velocityFrame = blank;
eulerFrame = blank;
rateOfTurnFrame = blank;
scalarFrames = repmat(blank, 1, 4);
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

% One place applies the 180-deg-Z sensor<-vehicle mounting transform.
sensorState = mountingTransform(vehicleState, contract);

frame = stamp(packMti680Frame('acceleration', ...
    sensorState.accelerationMps2, contract), timeS, next.sequence);

% Rate of turn is decoded by the VCU (imuProtocol.decodedByVcu) and its
% input is already required above, so it is emitted on every group exactly
% like acceleration.
rateOfTurnFrame = stamp(packMti680Frame('rateOfTurn', ...
    sensorState.rateOfTurnRadPerS, contract), timeS, next.sequence);

% VelocityXYZ is emitted whenever the shared state carries a velocity. It is
% not optional in practice: the VCU decodes 0x076 and its controls model
% consumes vy, so a simulator that never sends it leaves that input dead.
if isfield(sensorState, 'velocityMps')
    velocityFrame = stamp(packMti680Frame('velocityXyz', ...
        sensorState.velocityMps, contract), timeS, next.sequence);
end

% Off unless the caller opts in, per imuProtocol.defaultOutputRateHz.
if isfield(input, 'eulerEnabled') && input.eulerEnabled && ...
        isfield(sensorState, 'eulerAnglesDeg')
    eulerFrame = stamp(packMti680Frame('eulerAngles', ...
        sensorState.eulerAnglesDeg, contract), timeS, next.sequence);
end

% Scalar group messages. The MTi appends these to every inertial group;
% GroupCounter increments once per group and wraps at 2^16, SampleTime is a
% free-running microsecond clock (uint32, wraps after ~4295 s). StatusWord
% and ErrorCode carry the nominal healthy values until a fault is injected.
groupCounter = mod(double(next.sequence) - 1, 65536);
sampleTimeUs = mod(round(double(timeS) * 1e6), 2^32);
groupCounterFrame = stamp(packMti680ScalarFrame('groupCounter', ...
    groupCounter, contract), timeS, next.sequence);
sampleTimeFrame = stamp(packMti680ScalarFrame('sampleTime', ...
    sampleTimeUs, contract), timeS, next.sequence);
statusWordFrame = stamp(packMti680ScalarFrame('statusWord', ...
    double(contract.nominalStatusWord), contract), timeS, next.sequence);
errorCodeFrame = stamp(packMti680ScalarFrame('errorCode', ...
    double(contract.nominalErrorCode), contract), timeS, next.sequence);
scalarFrames = [groupCounterFrame, sampleTimeFrame, statusWordFrame, ...
    errorCodeFrame];
end

function frame = stamp(raw, timeS, sequence)
%STAMP Project a packed frame onto the canonical frame shape and mark it live.
frame = struct('id', uint32(raw.id), 'dlc', uint8(raw.dlc), ...
    'payload', uint8(raw.payload(:).'), 'timestampS', timeS, ...
    'sequence', uint32(sequence), 'valid', true, 'kind', char(raw.kind));
end
