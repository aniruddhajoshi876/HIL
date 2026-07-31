function evidence = confirm_decision16_on_target(targetName)
%CONFIRM_DECISION16_ON_TARGET Confirm the decision-16 finding against hardware.
%
%   GENERATE_DECISION16_EVIDENCE already answered decision 16 from the
%   generated artifacts. This function re-checks that answer against a real
%   Speedgoat, which is the only way to observe what GETPARAMLIST actually
%   returns and whether a field-addressed SETPARAM is accepted or rejected.
%
%   It needs a target computer and a compiler-built application; it does NOT
%   need a VCU, because nothing here transmits or expects CAN traffic.
%
%   Run BUILD_DECISION16_SPIKE(TRUE) and build the application first, then
%   CONFIRM_DECISION16_ON_TARGET('TargetName').
%
%   Nothing in this function fabricates a result. Each probe records what the
%   target did, including a thrown error, and the caller decides.

assert(nargin >= 1 && (ischar(targetName) || isstring(targetName)), ...
    'decision16:MissingTargetName', ...
    'Supply the target computer name (plan open decision 17).');
targetName = char(targetName);

target = slrealtime.Target(targetName);
connect(target);
load(target, 'decision16_spike');
start(target);
cleanup = onCleanup(@() stopQuietly(target));

evidence.targetName = targetName;
evidence.paramList = target.getparamlist();

% Probe 1: does the registry name struct fields, or only whole parameters?
evidence.namesWholeStruct = probeName(evidence.paramList, 'spk_struct_ch1');
evidence.namesStructField = probeName(evidence.paramList, ...
    'spk_struct_ch1.torque');
evidence.namesArrayElement = probeName(evidence.paramList, 'spk_array(1)');

% Probe 2: is a field-addressed write accepted? A thrown error here is the
% expected outcome and is recorded rather than propagated.
evidence.fieldWrite = attempt(@() setparam(target, '', ...
    'spk_struct_ch1.torque', 12.5));

% Probe 3: does a whole-struct write land, and does it leave siblings and
% other channels alone? This is the read-modify-write path the GUI would be
% forced onto if probe 2 fails.
before2 = attempt(@() getparam(target, '', 'spk_struct_ch2'));
evidence.structWrite = attempt(@() setparam(target, '', 'spk_struct_ch1', ...
    struct('torque', 7.5, 'enable', true)));
evidence.readBack1 = attempt(@() getparam(target, '', 'spk_struct_ch1'));
after2 = attempt(@() getparam(target, '', 'spk_struct_ch2'));
evidence.channel2Undisturbed = before2.ok && after2.ok && ...
    isequal(before2.value, after2.value);

% Probe 4: the flat fallback, which is the control case.
evidence.flatWrite = attempt(@() setparam(target, '', ...
    'spk_flat_ch1_torque', 3.25));
evidence.flatReadBack = attempt(@() getparam(target, '', ...
    'spk_flat_ch1_torque'));

describe(evidence);
end

function present = probeName(paramList, name)
present = false;
if isempty(paramList)
    return;
end
if istable(paramList)
    if any(strcmp('ParameterName', paramList.Properties.VariableNames))
        present = any(strcmp(name, string(paramList.ParameterName)));
    end
    return;
end
if iscell(paramList)
    present = any(strcmp(name, paramList));
end
end

function outcome = attempt(operation)
outcome.ok = false;
outcome.value = [];
outcome.error = '';
try
    outcome.value = operation();
    outcome.ok = true;
catch failure
    outcome.error = sprintf('%s: %s', failure.identifier, failure.message);
end
end

function describe(evidence)
fprintf('\n=== Decision 16 on-target confirmation (%s) ===\n', ...
    evidence.targetName);
fprintf('registry names whole struct   : %d\n', evidence.namesWholeStruct);
fprintf('registry names struct field   : %d\n', evidence.namesStructField);
fprintf('registry names array element  : %d\n', evidence.namesArrayElement);
fprintf('field-addressed setparam ok   : %d  %s\n', ...
    evidence.fieldWrite.ok, evidence.fieldWrite.error);
fprintf('whole-struct setparam ok      : %d  %s\n', ...
    evidence.structWrite.ok, evidence.structWrite.error);
fprintf('channel 2 undisturbed         : %d\n', evidence.channel2Undisturbed);
fprintf('flat scalar setparam ok       : %d  %s\n', ...
    evidence.flatWrite.ok, evidence.flatWrite.error);
fprintf('\n');
end

function stopQuietly(target)
try %#ok<TRYNC>
    stop(target);
end
end
