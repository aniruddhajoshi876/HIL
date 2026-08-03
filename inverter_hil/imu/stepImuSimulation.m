function [next, frame] = stepImuSimulation(previous, timeS, vehicleState, input)
%STEPIMUSIMULATION Sample shared vehicle state and produce MTi frames.
%   This function receives vehicle-state quantities from the independent HIL
%   plant; it does not call or mirror VCU control code.
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
frame = struct('id', uint32(0), 'dlc', uint8(0), ...
    'payload', zeros(1, 8, 'uint8'), 'timestampS', timeS, ...
    'sequence', next.sequence, 'valid', false, 'kind', '');
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
accel = packMti680Frame('acceleration', vehicleState.accelerationMps2);
frame = accel;
frame.timestampS = timeS;
frame.sequence = next.sequence;
frame.valid = true;
end
