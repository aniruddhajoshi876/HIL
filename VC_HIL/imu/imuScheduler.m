function [next, due] = imuScheduler(previous, timeS, periodS, contract)
%IMUSCHEDULER Advance IMU frame scheduling independently of any other sensor.
%   Split out of the former combined SENSORSCHEDULER: the IMU and LWS due
%   checks never referenced each other's state, so each sensor now has its
%   own scheduler called separately by the caller (e.g. TARGETSESSION or the
%   model build), which assembles any combined due-report itself.
%
%   [NEXT, DUE] = IMUSCHEDULER(PREVIOUS, TIMES) derives the base group tick
%   from imuProtocol.defaultOutputRateHz -- the contract is the single source
%   of truth for output rates -- rather than assuming a fixed rate. The base
%   tick is 1 / (fastest non-zero message rate), i.e. 0.01 s (100 Hz) for the
%   shipped contract.
%
%   [NEXT, DUE] = IMUSCHEDULER(PREVIOUS, TIMES, PERIODS) overrides the base
%   tick with an explicit period (used by tests and by any caller that wants
%   a different group rate).
%
%   DUE fields:
%     imu           the base group is due this tick.
%     timestampS    TIMES.
%     imuSequence   group counter after this tick.
%     acceleration / rateOfTurn / velocityXyz / eulerAngles
%                   per-message due flags derived from the contract rates
%                   relative to the base tick. A message at 0 Hz
%                   (eulerAngles) is never due -- "not transmitted".
%     groupCounter / sampleTime / statusWord / errorCode
%                   the scalar group messages, due on every base tick.
if nargin < 1 || isempty(previous)
    previous = struct('lastImuS', -Inf, 'imuSequence', uint32(0));
end
if nargin < 4 || isempty(contract)
    contract = imuProtocol();
end
rates = contract.defaultOutputRateHz;
messageNames = fieldnames(rates);
% Base tick: the fastest non-zero per-message rate the contract declares.
baseRateHz = 0;
for index = 1:numel(messageNames)
    baseRateHz = max(baseRateHz, double(rates.(messageNames{index})));
end
if baseRateHz <= 0
    baseRateHz = 100;
end
if nargin < 3 || isempty(periodS)
    periodS = 1 / baseRateHz;
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
% Per-message due flags, relative to the base group tick. A rate at or above
% the base rate rides every group; a lower rate is decimated; 0 Hz never
% fires.
for index = 1:numel(messageNames)
    name = messageNames{index};
    rateHz = double(rates.(name));
    if rateHz <= 0
        due.(name) = false;
    elseif rateHz >= baseRateHz
        due.(name) = due.imu;
    else
        decimation = max(1, round(baseRateHz / rateHz));
        due.(name) = due.imu && ...
            mod(double(next.imuSequence) - 1, decimation) == 0;
    end
end
% The scalar group messages accompany every inertial group (MT Low Level
% doc: "if enabled, this data will accompany every message").
due.groupCounter = due.imu;
due.sampleTime = due.imu;
due.statusWord = due.imu;
due.errorCode = due.imu;
end
