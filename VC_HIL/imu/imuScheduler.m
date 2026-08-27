function [next, due] = imuScheduler(previous, timeS, periodS)
%IMUSCHEDULER Advance IMU frame scheduling independently of any other sensor.
%   Split out of the former combined SENSORSCHEDULER: the IMU and LWS due
%   checks never referenced each other's state, so each sensor now has its
%   own scheduler called separately by the caller (e.g. TARGETSESSION or the
%   model build), which assembles any combined due-report itself.
if nargin < 1 || isempty(previous)
    previous = struct('lastImuS', -Inf, 'imuSequence', uint32(0));
end
if nargin < 3 || isempty(periodS)
    periodS = 0.005;
end
if ~isscalar(timeS) || ~isfinite(timeS) || timeS < 0
    error('inverterhil:InvalidSensorTime', 'Sensor time must be finite and nonnegative.');
end
if ~isscalar(periodS) || periodS <= 0
    error('inverterhil:InvalidSensorPeriod', 'Sensor periods must be positive.');
end
next = previous;
due = struct('imu', false, 'timestampS', timeS, ...
    'imuSequence', previous.imuSequence);
if timeS - previous.lastImuS + eps(timeS + 1) >= periodS
    due.imu = true;
    next.lastImuS = timeS;
    next.imuSequence = previous.imuSequence + uint32(1);
    due.imuSequence = next.imuSequence;
end
end
