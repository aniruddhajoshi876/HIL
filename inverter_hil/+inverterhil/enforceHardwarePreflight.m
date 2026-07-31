function enforceHardwarePreflight(model)
%ENFORCEHARDWAREPREFLIGHT Block target I/O while electrical gates are open.

if ~strcmp(version('-release'), '2024b')
    error('inverterhil:WrongRelease', ...
        'Inverter HIL hardware requires MATLAB/Simulink R2024b.');
end
if nargin < 1 || isempty(model)
    model = bdroot;
end
if isnumeric(model) && isscalar(model)
    model = getfullname(model);
end
if ~(ischar(model) && isrow(model)) || ~bdIsLoaded(model)
    error('inverterhil:InvalidModel', 'model must name a loaded model.');
end

hardware = [model '/Hardware I O - PRE-FLIGHT DISABLED'];
if getSimulinkBlockHandle(hardware) == -1
    error('inverterhil:MissingHardwareBoundary', ...
        'Missing preflight-gated hardware boundary: %s', hardware);
end
if strcmp(get_param(hardware, 'Commented'), 'on')
    return;
end

dictionaryName = get_param(model, 'DataDictionary');
dictionaryPath = which(dictionaryName);
if isempty(dictionaryPath)
    modelPath = get_param(model, 'FileName');
    dictionaryPath = fullfile(fileparts(modelPath), dictionaryName);
end
if ~isfile(dictionaryPath)
    error('inverterhil:MissingDictionary', ...
        'Cannot enforce hardware preflight without %s.', dictionaryPath);
end

dictionary = Simulink.data.dictionary.open(dictionaryPath);
cleanup = onCleanup(@() close(dictionary)); %#ok<NASGU>
section = getSection(dictionary, 'Design Data');
entry = getEntry(section, 'hil_hardware_preflight_complete');
gate = getValue(entry);
if isa(gate, 'Simulink.Parameter')
    gate = gate.Value;
end
if ~(islogical(gate) || isnumeric(gate)) || ~isscalar(gate) || ...
        ~isreal(gate) || ~isfinite(double(gate)) || ...
        ~(double(gate) == 0 || double(gate) == 1)
    error('inverterhil:InvalidHardwarePreflightGate', ...
        'hil_hardware_preflight_complete must be logical 0 or 1.');
end
if ~logical(gate)
    error('inverterhil:HardwarePreflightOpen', ...
        ['Hardware I/O cannot be enabled: electrical levels, grounds, J3 ' ...
         'isolation, polarity, CAN termination, and harness gates are open.']);
end
end
