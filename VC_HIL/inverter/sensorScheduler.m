function [next, due] = sensorScheduler(previous, timeS, input)
%SENSORSCHEDULER Advance synchronized IMU/LWS frame scheduling.
%   Both producers observe the same input state and simulation timestamp.
if nargin < 1 || isempty(previous)
    previous = struct('lastImuS', -Inf, 'lastLwsS', -Inf, ...
        'imuSequence', uint32(0), 'lwsSequence', uint32(0));
end
if nargin < 3 || isempty(input)
    input = struct('imuPeriodS', 0.005, 'lwsPeriodS', 0.010);
end
if ~isscalar(timeS) || ~isfinite(timeS) || timeS < 0
    error('inverterhil:InvalidSensorTime', 'Sensor time must be finite and nonnegative.');
end
required = {'imuPeriodS', 'lwsPeriodS'};
for index = 1:numel(required)
    if ~isfield(input, required{index}) || input.(required{index}) <= 0
        error('inverterhil:InvalidSensorPeriod', 'Sensor periods must be positive.');
    end
end
next = previous;
due = struct('imu', false, 'lws', false, 'timestampS', timeS, ...
    'imuSequence', previous.imuSequence, 'lwsSequence', previous.lwsSequence);
if timeS - previous.lastImuS + eps(timeS + 1) >= input.imuPeriodS
    due.imu = true;
    next.lastImuS = timeS;
    next.imuSequence = previous.imuSequence + uint32(1);
    due.imuSequence = next.imuSequence;
end
if timeS - previous.lastLwsS + eps(timeS + 1) >= input.lwsPeriodS
    due.lws = true;
    next.lastLwsS = timeS;
    next.lwsSequence = previous.lwsSequence + uint32(1);
    due.lwsSequence = next.lwsSequence;
end
end
