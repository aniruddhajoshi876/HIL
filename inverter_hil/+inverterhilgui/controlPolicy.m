function policy = controlPolicy(applicationState, vcuState, interlocks)
%CONTROLPOLICY Single authority for which GUI control groups are enabled.
%
%   POLICY = CONTROLPOLICY(APPLICATIONSTATE, VCUSTATE, INTERLOCKS) returns one
%   logical enable per control group. No callback may re-derive enable state;
%   every widget takes its Enable value from this function.
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
    'momentary', false, ...
    'electrical', false, ...
    'plantParameters', false, ...
    'calibration', false, ...
    'faultInjection', false, ...
    'canFaults', false, ...
    'logExport', true, ...
    'expertGroupsUnlocked', false, ...
    'reason', 'malformed_input');

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
if ~values.contractResolved
    policy.reason = 'contract_unresolved';
    return;
end
if ~values.targetHealthy
    policy.reason = 'target_unhealthy';
    return;
end
if ~values.heartbeatOk
    policy.reason = 'heartbeat_lost';
    return;
end

running = lifecycle.isRunning;
inDrive = any(strcmp(vcuState, {'ENABLE', 'BUZZING', 'RTD'}));
quiescent = ~running || strcmp(vcuState, 'LV_ON') || isempty(vcuState);

% Runtime stimuli require a running application; they are the only groups
% permitted while the VCU is in Drive.
policy.pedals = running;
policy.digitalStimuli = running;
policy.momentary = running;
policy.armPedals = running;
policy.plausibilityViolation = running && values.plausibilityOverride;

% Everything else needs the application stopped or the VCU quiet, plus the
% explicit expert interlock.
unlocked = values.expertMode && quiescent && ~inDrive;
policy.expertGroupsUnlocked = unlocked;
policy.electrical = unlocked;
policy.plantParameters = unlocked;
policy.calibration = unlocked && ~running;
policy.faultInjection = unlocked;
policy.canFaults = unlocked;

if inDrive
    policy.reason = 'drive_restricted';
elseif unlocked
    policy.reason = 'expert_unlocked';
elseif running
    policy.reason = 'running_stimuli_only';
else
    policy.reason = 'idle_locked';
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
