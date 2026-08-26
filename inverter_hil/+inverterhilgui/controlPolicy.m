function policy = controlPolicy(applicationState, vcuState, interlocks, canDriving)
%CONTROLPOLICY Single authority for which GUI control groups are enabled.
%
%   POLICY = CONTROLPOLICY(APPLICATIONSTATE, VCUSTATE, INTERLOCKS) returns one
%   logical enable per control group. No callback may re-derive enable state;
%   every widget takes its Enable value from this function.
%
%   POLICY = CONTROLPOLICY(..., CANDRIVING) additionally takes a scalar
%   logical, default false when omitted, true while CarMaker is driving pedal
%   demand over CAN. This is NOT part of the INTERLOCKS REMOVED 2026-08-02
%   decision below -- it is write-ownership arbitration between two
%   legitimate writers of the same two dictionary entries
%   (hil_cmd_pedals_throttle/brake), not a safety gate, and only ever affects
%   POLICY.PEDALS.
%
%   UNRESOLVED PLAN OPEN DECISION 18 - "Which GUI controls are allowed during
%   Drive versus Idle/stopped operation" is not answered by the plan. The
%   conservative default implemented here, pending that decision, is:
%
%     * While the VCU is in Drive, permit ONLY pedal commands and digital
%       stimuli. Everything else is locked.
%     * Calibration edits, plant parameters, unsafe DC-link voltage commands,
%       and fault injection require the real-time application to be stopped OR
%       the VCU to be in Idle, AND an explicit expert-mode interlock
%       (plan 7.4).
%     * Calibration is held one notch tighter than the other expert groups:
%       plan 7.1 states that HIL_CAL.PEDALS.* may "change only while stopped
%       until validated", so calibration additionally requires the
%       application not to be running. This is a deliberate tightening of
%       plan 7.4, not an oversight.
%     * The pedal interface cannot be armed against an unhealthy target: an
%       unresolved parameter contract, unhealthy target IO, or an expired GUI
%       heartbeat disables every command group.
%
%   Change this default only when open decision 18 is closed in the plan.
%
%   APPLICATIONSTATE is a lifecycle state from INVERTERHILGUI.CONNECTIONSTATE.
%   VCUSTATE is the observed VCU state text ('LV_ON', 'PRECHARGING', 'ENABLE',
%   'BUZZING', 'RTD', 'ERROR' or '' when unknown).
%   INTERLOCKS is a scalar structure with logical fields EXPERTMODE,
%   PLAUSIBILITYOVERRIDE, TARGETHEALTHY, HEARTBEATOK and CONTRACTRESOLVED.
%
%   The evaluator FAILS CLOSED: malformed input disables every command group.

policy = struct( ...
    'connectionControls', false, ...
    'pedals', false, ...
    'armPedals', false, ...
    'plausibilityViolation', false, ...
    'digitalStimuli', false, ...
    'sensorStimulus', false, ...
    'momentary', false, ...
    'electrical', false, ...
    'plantParameters', false, ...
    'calibration', false, ...
    'faultInjection', false, ...
    'canFaults', false, ...
    'logExport', true, ...
    'canDriving', false, ...
    'expertGroupsUnlocked', false, ...
    'reason', 'malformed_input');

if nargin < 4 || isempty(canDriving)
    canDriving = false;
end
if ~(islogical(canDriving) || isnumeric(canDriving)) || ~isscalar(canDriving) || ...
        ~isreal(canDriving) || ~isfinite(double(canDriving)) || ...
        ~(double(canDriving) == 0 || double(canDriving) == 1)
    policy.reason = 'malformed_canDriving';
    return;
end
canDriving = logical(canDriving);

applicationState = normalizeText(applicationState);
vcuState = upper(normalizeText(vcuState));
if isempty(applicationState)
    return;
end

lifecycle = inverterhilgui.connectionState(applicationState);
if ~lifecycle.valid
    policy.reason = 'unknown_application_state';
    return;
end
policy.connectionControls = true;

flags = {'expertMode', 'plausibilityOverride', 'targetHealthy', ...
    'heartbeatOk', 'contractResolved'};
values = struct();
if ~isstruct(interlocks) || ~isscalar(interlocks)
    policy.reason = 'malformed_interlocks';
    return;
end
for index = 1:numel(flags)
    name = flags{index};
    if ~isfield(interlocks, name)
        policy.reason = ['missing_' name];
        return;
    end
    value = interlocks.(name);
    if ~(islogical(value) || isnumeric(value)) || ~isscalar(value) || ...
            ~isreal(value) || ~isfinite(double(value)) || ...
            ~(double(value) == 0 || double(value) == 1)
        policy.reason = ['malformed_' name];
        return;
    end
    values.(name) = logical(value);
end

if ~lifecycle.isConnected
    policy.reason = 'not_connected';
    return;
end

% INTERLOCKS REMOVED 2026-08-02 by explicit operator decision.
%
%   The contract-resolved, target-healthy, heartbeat-alive, expert-mode,
%   Drive-restriction and application-stopped gates documented in the help
%   above are all bypassed below. The operator asked for full manual control
%   and was shown what that means: there is now NO software protection
%   against commanding this rig in an unverified or unhealthy state.
%
%   What that costs, concretely, so a future reader can restore it knowingly:
%     * targetHealthy/heartbeatOk no longer gate anything, so pedal and
%       digital commands stay enabled against a bus-off CAN link or a GUI
%       whose heartbeat the target has already declared stale.
%     * The expert interlock no longer guards calibration, plant parameters,
%       fault injection or DC-link commands, so a mis-click edits them
%       directly.
%     * Plan 7.1's "calibration may change only while stopped until
%       validated" is no longer enforced.
%     * INDROVE/Drive restriction is gone: every group stays live while the
%       VCU is in ENABLE/BUZZING/RTD.
%   INTERLOCKS is still validated above, and the values are still reported
%   through the returned struct, so restoring any individual gate is a
%   matter of reinstating its condition here.
%
%   RUNNING is still required for the runtime stimulus groups. That is not a
%   safety interlock: SETPARAM against a stopped application simply fails, so
%   enabling those widgets would only produce write errors.
running = lifecycle.isRunning;

% Pedals are writable from the GUI only while the external command source
% does not own them. CAN ownership is a writer-arbitration fact, not a
% safety interlock; every other control group is unaffected.
policy.pedals = running && ~canDriving;
policy.canDriving = canDriving;
policy.digitalStimuli = running;
policy.sensorStimulus = running;
policy.momentary = running;
policy.armPedals = running;
policy.plausibilityViolation = running;

policy.expertGroupsUnlocked = true;
policy.electrical = true;
policy.plantParameters = true;
policy.calibration = true;
policy.faultInjection = true;
policy.canFaults = true;

if running
    policy.reason = 'interlocks_removed_running';
else
    policy.reason = 'interlocks_removed_stopped';
end
end

function text = normalizeText(text)
if isstring(text) && isscalar(text)
    text = char(text);
end
if ~ischar(text)
    text = '';
end
text = strtrim(text);
end
