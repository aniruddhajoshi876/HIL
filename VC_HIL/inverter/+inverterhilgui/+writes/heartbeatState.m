function result = heartbeatState(previous, nowS, timeoutS)
%HEARTBEATSTATE Advance the GUI heartbeat counter and evaluate its age.
%
%   RESULT = HEARTBEATSTATE(PREVIOUS, NOWS, TIMEOUTS) is called once per app
%   timer tick. PREVIOUS is a scalar structure with fields COUNTER (uint32)
%   and LASTUPDATES (host seconds). RESULT.COUNTER is the wrap-safe uint32
%   value to write to HIL_CMD.GUI_HEARTBEAT and RESULT.AGES is the interval
%   since the previous beat, so a stalled host timer is visible to the
%   operator as well as to the target.
%
%   This evaluator FAILS CLOSED: malformed input or a missing previous state
%   reports EXPIRED true and holds the counter at its last known good value,
%   because an unknown heartbeat must be treated as a lost heartbeat.

result = struct( ...
    'counter', uint32(0), ...
    'lastUpdateS', NaN, ...
    'ageS', Inf, ...
    'expired', true, ...
    'reason', 'malformed_previous_state');

if ~isstruct(previous) || ~isscalar(previous) || ...
        ~isfield(previous, 'counter') || ~isfield(previous, 'lastUpdateS')
    return;
end
counterValue = previous.counter;
if ~(isnumeric(counterValue) || islogical(counterValue)) || ...
        ~isscalar(counterValue) || ~isreal(counterValue) || ...
        ~isfinite(double(counterValue)) || double(counterValue) < 0 || ...
        double(counterValue) > 4294967295 || ...
        double(counterValue) ~= floor(double(counterValue))
    result.reason = 'malformed_counter';
    return;
end
result.counter = uint32(counterValue);

if ~isnumeric(nowS) || ~isscalar(nowS) || ~isreal(nowS) || ~isfinite(nowS)
    result.reason = 'malformed_now';
    return;
end
if ~isnumeric(timeoutS) || ~isscalar(timeoutS) || ~isreal(timeoutS) || ...
        ~isfinite(timeoutS) || timeoutS <= 0
    result.reason = 'malformed_timeout';
    return;
end

lastUpdateS = previous.lastUpdateS;
if ~isnumeric(lastUpdateS) || ~isscalar(lastUpdateS) || ...
        ~isreal(lastUpdateS) || ~isfinite(lastUpdateS)
    result.counter = inverterhilgui.writes.sequenceCommand(result.counter);
    result.lastUpdateS = double(nowS);
    result.ageS = Inf;
    result.expired = true;
    result.reason = 'no_previous_beat';
    return;
end

ageS = double(nowS) - double(lastUpdateS);
if ageS < 0
    result.ageS = Inf;
    result.expired = true;
    result.reason = 'host_clock_went_backwards';
    return;
end

result.counter = inverterhilgui.writes.sequenceCommand(result.counter);
result.lastUpdateS = double(nowS);
result.ageS = ageS;
result.expired = ageS > double(timeoutS);
if result.expired
    result.reason = 'heartbeat_expired';
else
    result.reason = 'healthy';
end
end
