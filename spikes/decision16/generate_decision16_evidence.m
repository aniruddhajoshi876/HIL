function evidence = generate_decision16_evidence()
%GENERATE_DECISION16_EVIDENCE Answer plan decision 16 without a compiler.
%
%   Building a real-time application needs a supported C compiler and a
%   reachable target. Neither is required to learn what SETPARAM will be able
%   to address, because the addressable parameter set is decided at code
%   generation, not at link or download time: Simulink Real-Time's
%   GETPARAMLIST and SETPARAM are backed by the generated C API, whose
%   RTWCAPI_MODELPARAMETERS table is emitted into <model>_capi.c.
%
%   This function therefore generates code only, then reads that table. If a
%   bus-typed struct parameter appears there as one entry, SETPARAM addresses
%   the whole struct and a field-level write is a read-modify-write. If its
%   fields appear as separate entries, field-level writes are native.
%
%   The answer is read out of the generated artifact; nothing here is assumed.

model = 'decision16_spike';
root = fileparts(mfilename('fullpath'));
modelPath = fullfile(root, [model '.slx']);
assert(isfile(modelPath), 'decision16:MissingModel', ...
    'Run build_decision16_spike(true) first; missing %s.', modelPath);
assert(strcmp(version('-release'), '2024b'), 'decision16:WrongRelease', ...
    'This spike must run in R2024b, not R%s.', version('-release'));

previous = cd(root);
cleanupDirectory = onCleanup(@() cd(previous));
load_system(modelPath);
cleanupModel = onCleanup(@() close_system(model, 0));

set_param(model, 'GenCodeOnly', 'on', 'RTWCAPIParams', 'on');
slbuild(model);

% The speedgoat.tlc target emits into <model>_sg_rtw and writes C++ sources,
% so neither the folder suffix nor the extension can be assumed.
candidates = dir(fullfile(root, [model '_*_rtw']));
assert(~isempty(candidates), 'decision16:MissingCode', ...
    'No generated code directory under %s.', root);
codeDirectory = fullfile(root, candidates(1).name);

capiPath = '';
for extension = {'.cpp', '.c'}
    candidate = fullfile(codeDirectory, [model '_capi' extension{1}]);
    if isfile(candidate)
        capiPath = candidate;
        break;
    end
end
assert(~isempty(capiPath), 'decision16:MissingCapi', ...
    'No C API source in %s; SETPARAM addressing cannot be determined.', ...
    codeDirectory);

evidence.codeDirectory = codeDirectory;
evidence.parameters = readModelParameters(capiPath);
evidence.release = version('-release');

fprintf('\n=== Decision 16 evidence (%s) ===\n', evidence.release);
fprintf('C API model parameters exposed to setparam: %d\n\n', ...
    numel(evidence.parameters));
for index = 1:numel(evidence.parameters)
    fprintf('  %s\n', evidence.parameters{index});
end

report(evidence.parameters, 'spk_flat_ch1_torque', 'Group A flat scalar');
report(evidence.parameters, 'spk_struct_ch1', 'Group B scalar struct');
report(evidence.parameters, 'spk_array', 'Group C struct array');
fprintf('\n');
end

function names = readModelParameters(capiPath)
% The model-parameter table is the block that SETPARAM resolves names
% against. Only that block is read; the block for signals and block
% parameters uses the same TARGET_STRING macro and would otherwise pollute
% the answer.
text = fileread(capiPath);
start = regexp(text, 'rtwCAPI_ModelParameters\s+\w*\s*\[\s*\]\s*=\s*\{', ...
    'once', 'end');
names = {};
if isempty(start)
    return;
end
remainder = text(start:end);
stop = strfind(remainder, '};');
if ~isempty(stop)
    remainder = remainder(1:stop(1));
end
tokens = regexp(remainder, 'TARGET_STRING\(\s*"([^"]*)"\s*\)', 'tokens');
for index = 1:numel(tokens)
    name = tokens{index}{1};
    if ~isempty(name)
        names{end + 1, 1} = name; %#ok<AGROW>
    end
end
end

function report(names, stem, label)
exact = any(strcmp(names, stem));
fielded = ~isempty(names(~cellfun(@isempty, ...
    regexp(names, ['^' regexptranslate('escape', stem) '[.(\[]'], 'once'))));
fprintf('\n%s (%s):\n', label, stem);
fprintf('  whole parameter addressable : %d\n', exact);
fprintf('  fields separately addressable: %d\n', fielded);
end
