function plan = safeFallbackPlan(health)
%SAFEFALLBACKPLAN Decide the safe analog/digital fallback from host health.
%
%   PLAN = SAFEFALLBACKPLAN(HEALTH) implements plan 7.4: loss of the GUI
%   heartbeat, a target stop, or application unload returns the four analog
%   pedal outputs to 0 V and every digital stimulus to its verified inactive
%   level. Valid released-pedal voltages are only ever applied by a healthy,
%   running application.
%
%   HEALTH is a scalar structure with fields:
%     applicationRunning - true only while the real-time application runs
%     targetConnected    - true only while the host owns a connected target
%     applicationLoaded  - false once the application has been unloaded
%     ioHealthy          - target IO status
%     armed              - accepted but no longer gates the plan; see below
%     heartbeatAgeS      - age of the most recent heartbeat write
%     heartbeatTimeoutS  - configured heartbeat timeout
%
%   ARMED GATE REMOVED, matching INVERTERHILGUI.CONTROLPOLICY's 2026-08-02
%   "INTERLOCKS REMOVED" operator decision (full manual control, no software
%   protection beyond target/application/IO health). HEALTH.armed was always
%   read from APP.TELEMETRY.PEDALS.ARMED, which nothing in this codebase ever
%   set true -- CONTROLPOLICY's own interlock removal never reached this
%   file, so the fallback stayed permanently applied regardless of real
%   state. ARMED is still accepted (not required) for backward compatibility
%   with callers that pass it, but is no longer read.
%
%   This evaluator FAILS CLOSED: any missing field, malformed value, or
%   unhealthy input returns APPLYFALLBACK true with the safe outputs, exactly
%   as INVERTERHIL.SAFEIOOUTPUTS does on the target side.

plan = struct( ...
    'analogV', zeros(1, 4), ...
    'digital', false(1, 8), ...
    'applyFallback', true, ...
    'reason', 'malformed_health');

if ~isstruct(health) || ~isscalar(health)
    return;
end
required = {'applicationRunning', 'targetConnected', 'applicationLoaded', ...
    'ioHealthy', 'heartbeatAgeS', 'heartbeatTimeoutS'};
for index = 1:numel(required)
    if ~isfield(health, required{index})
        plan.reason = ['missing_' required{index}];
        return;
    end
end

flags = {'targetConnected', 'applicationLoaded', 'applicationRunning', ...
    'ioHealthy'};
reasons = {'target_disconnected', 'application_unloaded', ...
    'application_stopped', 'io_unhealthy'};
for index = 1:numel(flags)
    value = health.(flags{index});
    if ~(islogical(value) || isnumeric(value)) || ~isscalar(value) || ...
            ~isreal(value) || ~isfinite(double(value)) || ...
            ~(double(value) == 0 || double(value) == 1)
        plan.reason = 'malformed_health_flag';
        return;
    end
    if ~logical(value)
        plan.reason = reasons{index};
        return;
    end
end

ageS = health.heartbeatAgeS;
timeoutS = health.heartbeatTimeoutS;
if ~isnumeric(timeoutS) || ~isscalar(timeoutS) || ~isreal(timeoutS) || ...
        ~isfinite(timeoutS) || timeoutS <= 0
    plan.reason = 'malformed_heartbeat_timeout';
    return;
end
if ~isnumeric(ageS) || ~isscalar(ageS) || ~isreal(ageS) || ...
        ~isfinite(ageS) || ageS < 0 || ageS > timeoutS
    plan.reason = 'heartbeat_expired';
    return;
end

plan.applyFallback = false;
plan.reason = 'healthy';
end
