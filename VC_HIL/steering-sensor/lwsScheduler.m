function [next, due] = lwsScheduler(previous, timeS, periodS)
%LWSSCHEDULER Advance LWS frame scheduling independently of any other sensor.
%   Split out of the former combined SENSORSCHEDULER: the IMU and LWS due
%   checks never referenced each other's state, so each sensor now has its
%   own scheduler called separately by the caller (e.g. TARGETSESSION or the
%   model build), which assembles any combined due-report itself.
if nargin < 1 || isempty(previous)
    previous = struct('lastLwsS', -Inf, 'lwsSequence', uint32(0));
end
if nargin < 3 || isempty(periodS)
    periodS = 0.010;
end
if ~isscalar(timeS) || ~isfinite(timeS) || timeS < 0
    error('inverterhil:InvalidSensorTime', 'Sensor time must be finite and nonnegative.');
end
if ~isscalar(periodS) || periodS <= 0
    error('inverterhil:InvalidSensorPeriod', 'Sensor periods must be positive.');
end
next = previous;
due = struct('lws', false, 'timestampS', timeS, ...
    'lwsSequence', previous.lwsSequence);
if timeS - previous.lastLwsS + eps(timeS + 1) >= periodS
    due.lws = true;
    next.lastLwsS = timeS;
    next.lwsSequence = previous.lwsSequence + uint32(1);
    due.lwsSequence = next.lwsSequence;
end
end
