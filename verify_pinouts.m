function verify_pinouts()
%VERIFY_PINOUTS Check PINOUTS.MD section 4 against the real inverter_hil model.
%
%   Loads INVERTER_HIL.SLX and compares every IO183 block parameter and every
%   digital-output port source against the tables documented in PINOUTS.MD.
%   Prints PASS/FAIL per check and raises an error if anything mismatches, so
%   this is safe to call from a test harness.
%
%   Only the "as configured" claims (PINOUTS.MD section 4) are checkable here.
%   Sections 2, 3, 5.2 and 6 are vendor hardware facts verified by citation.

modelDir = fileparts(mfilename('fullpath'));
projectDir = fullfile(modelDir, 'inverter_hil');
model = 'inverter_hil';

fprintf('\n=== verify_pinouts: PINOUTS.MD section 4 vs %s.slx ===\n\n', model);

previousDir = pwd;
restoreDir = onCleanup(@() cd(previousDir));
cd(projectDir);

alreadyLoaded = bdIsLoaded(model);
if ~alreadyLoaded
    load_system([model '.slx']);
end

results = struct('label', {}, 'pass', {}, 'detail', {});

% The hardware boundary carries a deliberately alarming standing name. It is a
% permanent warning label, NOT a state flag: the real gates are this block's
% Commented parameter and hil_hardware_preflight_complete, both checked below.
hw = [model '/Hardware I O - PRE-FLIGHT DISABLED'];

results = check(results, 'Hardware boundary is live (Commented off)', ...
    get_param(hw, 'Commented'), 'off');

% ---------------------------------------------------------------- Setup block
setup = [hw '/IO183 Setup'];
results = check(results, 'Setup parModuleId', ...
    get_param(setup, 'parModuleId'), '1');
results = check(results, 'Setup parPciSlot (autosearch)', ...
    get_param(setup, 'parPciSlot'), '-1');
results = check(results, 'Setup parAdCoupling', ...
    get_param(setup, 'parAdCoupling'), 'Single Ended');
results = check(results, 'Setup parAdRange', ...
    get_param(setup, 'parAdRange'), '0..5V');
results = check(results, 'Setup parAdChannelLow', ...
    get_param(setup, 'parAdChannelLow'), '1');
results = check(results, 'Setup parAdChannelHigh', ...
    get_param(setup, 'parAdChannelHigh'), '4');
results = check(results, 'Setup parDaChannels', ...
    normalizeVector(get_param(setup, 'parDaChannels')), '[1 2 3 4]');
results = check(results, 'Setup parDaRange', ...
    get_param(setup, 'parDaRange'), '0..5V');
results = check(results, 'Setup parDaInit (0 V)', ...
    normalizeVector(get_param(setup, 'parDaInit')), '[0 0 0 0]');
results = check(results, 'Setup parDaSimult', ...
    get_param(setup, 'parDaSimult'), 'on');
results = check(results, 'Setup parDoReset', ...
    normalizeVector(get_param(setup, 'parDoReset')), '[0 0 0 0 0 0 0 0]');
results = check(results, 'Setup parDiChannels', ...
    normalizeVector(get_param(setup, 'parDiChannels')), '[9 10 11 12 13]');
results = check(results, 'Setup parIOPullReferenceFront', ...
    get_param(setup, 'parIOPullReferenceFront'), 'Pull-down');

% ------------------------------------------------------------- Analog output
ao = [hw '/IO183 AO01-AO04 Safe Zero'];
results = check(results, 'AO parDaChannels (AO01-AO04)', ...
    normalizeVector(get_param(ao, 'parDaChannels')), '[1 2 3 4]');
results = check(results, 'AO parDaInit (0 V initial)', ...
    normalizeVector(get_param(ao, 'parDaInit')), '[0 0 0 0]');
results = check(results, 'AO parDaReset (0 V on stop)', ...
    normalizeVector(get_param(ao, 'parDaReset')), '[0 0 0 0]');
results = check(results, 'AO parSampTime (1 kHz)', ...
    get_param(ao, 'parSampTime'), '0.001');

% -------------------------------------------------------------- Analog input
ai = [hw '/IO183 AI01-AI04 Rail Monitor'];
results = check(results, 'AI parAdChannelLow', ...
    get_param(ai, 'parAdChannelLow'), '1');
results = check(results, 'AI parAdChannelHigh', ...
    get_param(ai, 'parAdChannelHigh'), '4');
results = check(results, 'AI parSampTime (1 kHz)', ...
    get_param(ai, 'parSampTime'), '0.001');

% ------------------------------------------------------------ Digital output
do = [hw '/IO183 DIO01-DIO08 Safe Zero'];
results = check(results, 'DO parDoChannels (DIO01-DIO08)', ...
    normalizeVector(get_param(do, 'parDoChannels')), '[1 2 3 4 5 6 7 8]');
results = check(results, 'DO parDoInit (0 initial)', ...
    normalizeVector(get_param(do, 'parDoInit')), '[0 0 0 0 0 0 0 0]');
results = check(results, 'DO parDoReset (0 on stop)', ...
    normalizeVector(get_param(do, 'parDoReset')), '[0 0 0 0 0 0 0 0]');
results = check(results, 'DO parSampTime (1 kHz)', ...
    get_param(do, 'parSampTime'), '0.001');

% ------------------------------------------------------------- Digital input
di = [hw '/IO183 DIO09-DIO13 VCU Monitor'];
results = check(results, 'DI parDiChannels (DIO09-DIO13)', ...
    normalizeVector(get_param(di, 'parDiChannels')), '[9 10 11 12 13]');
results = check(results, 'DI parSampTime (1 kHz)', ...
    get_param(di, 'parSampTime'), '0.001');

% ------------------------------- Digital output port sources (section 4.3)
% PINOUTS.MD claims: port1 precharge pulse, port2 main button pulse (mirrors
% port1's pulse-on-counter-change pattern; hil_cmd_digital_main_button itself
% has no hardware effect), port3 cooling switch, port4 shutdown feedback,
% ports 5-8 unused SW_IN constants.
expectedSources = { ...
    1, 'Precharge Pulse Generator'; ...
    2, 'Main Button Pulse Generator'; ...
    3, 'hil_cmd_digital_cooling_switch'; ...
    4, 'hil_cmd_digital_shutdown_feedback'; ...
    5, 'Unused SW_IN_1'; ...
    6, 'Unused SW_IN_2'; ...
    7, 'Unused SW_IN_3'; ...
    8, 'Unused SW_IN_4'};

for index = 1:size(expectedSources, 1)
    port = expectedSources{index, 1};
    expectedFragment = expectedSources{index, 2};
    actual = sourceBlockForInport(do, port);
    label = sprintf('DO port %d (DIO%02d) source', port, port);
    passed = contains(actual, expectedFragment);
    results(end + 1) = struct('label', label, 'pass', passed, ...
        'detail', sprintf('expected to contain "%s", got "%s"', ...
        expectedFragment, actual)); %#ok<AGROW>
end

% ------------------- Throttle / brake routing to AO01-AO04 (section 4.2)
% PINOUTS.MD claims throttle -> AO01, AO02 and brake -> AO03, AO04, produced by
% the Pedal Voltage Calibration block. Verify the four AO ports come from that
% block on the matching source port, so a transposed line would be caught.
for port = 1:4
    [srcName, srcPort] = sourceBlockForInport(ao, port);
    label = sprintf('AO port %d (AO%02d) source', port, port);
    passed = contains(srcName, 'Pedal Voltage Calibration') && srcPort == port;
    results(end + 1) = struct('label', label, 'pass', passed, ...
        'detail', sprintf(['expected "Pedal Voltage Calibration" port %d, ' ...
        'got "%s" port %d'], port, srcName, srcPort)); %#ok<AGROW>
end

% pedalVoltageCalibration(throttle, brake, released1, pressed1, ... pressed4)
% assigns ao1/ao2 from throttle and ao3/ao4 from brake, so the input order below
% is what makes "throttle -> AO01/AO02, brake -> AO03/AO04" true. Inputs 1/2
% arrive through Throttle/Brake Source Switch, not directly from the GUI
% dictionary entries -- see the "Pedal voltage generation" prose above.
expectedPedalInputs = { ...
    1,  'Throttle Source Switch'; ...
    2,  'Brake Source Switch'; ...
    3,  'hil_cal_pedals_released_v1'; ...
    4,  'hil_cal_pedals_pressed_v1'; ...
    5,  'hil_cal_pedals_released_v2'; ...
    6,  'hil_cal_pedals_pressed_v2'; ...
    7,  'hil_cal_pedals_released_v3'; ...
    8,  'hil_cal_pedals_pressed_v3'; ...
    9,  'hil_cal_pedals_released_v4'; ...
    10, 'hil_cal_pedals_pressed_v4'};

pedal = [hw '/Pedal Voltage Calibration'];
for index = 1:size(expectedPedalInputs, 1)
    port = expectedPedalInputs{index, 1};
    expectedFragment = expectedPedalInputs{index, 2};
    srcName = sourceBlockForInport(pedal, port);
    label = sprintf('Pedal calib input %d', port);
    passed = contains(srcName, expectedFragment);
    results(end + 1) = struct('label', label, 'pass', passed, ...
        'detail', sprintf('expected to contain "%s", got "%s"', ...
        expectedFragment, srcName)); %#ok<AGROW>
end

% ------------------------- GUI pins array vs DI channel order (section 4.3 warning)
% PINOUTS.MD warns that blankTelemetry orders the last two pins as
% INV_CTRL_EN (DIO13) then INV_CTRL_DIS (DIO12), i.e. transposed relative to
% the DI block's numeric [9 10 11 12 13]. Verify that warning is still true.
addpath(projectDir);
snapshot = inverterhilgui.blankTelemetry();
guiNames = {snapshot.pins.name};
guiTestPoints = {snapshot.pins.testPoint};

results = check(results, 'GUI pins(4).name is INV_CTRL_EN', ...
    guiNames{4}, 'INV_CTRL_EN');
results = check(results, 'GUI pins(5).name is INV_CTRL_DIS', ...
    guiNames{5}, 'INV_CTRL_DIS');
results = check(results, 'GUI pins(4).testPoint is TP9', ...
    guiTestPoints{4}, 'TP9');
results = check(results, 'GUI pins(5).testPoint is TP10', ...
    guiTestPoints{5}, 'TP10');

% ------------------------------------------- Pedal calibration state (report)
% Routing being correct does NOT mean the pedals produce voltage: an endpoint
% left at NaN makes pedalVoltageCalibration drive 0 V by design. Report this
% loudly, but do not fail -- shipping NaN is the intended uncalibrated state.
calibrationNames = { ...
    'hil_cal_pedals_released_v1', 'hil_cal_pedals_pressed_v1', ...
    'hil_cal_pedals_released_v2', 'hil_cal_pedals_pressed_v2', ...
    'hil_cal_pedals_released_v3', 'hil_cal_pedals_pressed_v3', ...
    'hil_cal_pedals_released_v4', 'hil_cal_pedals_pressed_v4'};
uncalibrated = {};
dictionaryPath = fullfile(projectDir, 'inverter_hil.sldd');
dictionary = Simulink.data.dictionary.open(dictionaryPath);
section = getSection(dictionary, 'Design Data');
for index = 1:numel(calibrationNames)
    value = getValue(getEntry(section, calibrationNames{index}));
    if isa(value, 'Simulink.Parameter')
        value = value.Value;
    end
    if ~isfinite(double(value))
        uncalibrated{end + 1} = calibrationNames{index}; %#ok<AGROW>
    end
end
close(dictionary);

% ------------------------------------------------------------------- Report
fprintf('%-46s %s\n', 'CHECK', 'RESULT');
fprintf('%s\n', repmat('-', 1, 62));
failures = 0;
for index = 1:numel(results)
    if results(index).pass
        verdict = 'PASS';
    else
        verdict = 'FAIL';
        failures = failures + 1;
    end
    fprintf('%-46s %s\n', results(index).label, verdict);
    if ~results(index).pass
        fprintf('    -> %s\n', results(index).detail);
    end
end

fprintf('%s\n', repmat('-', 1, 62));
fprintf('%d checks, %d passed, %d failed\n\n', ...
    numel(results), numel(results) - failures, failures);

if isempty(uncalibrated)
    fprintf('Pedal calibration: all 8 endpoints set.\n\n');
else
    fprintf(['*** PEDAL CALIBRATION INCOMPLETE ***\n' ...
        '%d of 8 endpoints are NaN:\n'], numel(uncalibrated));
    fprintf('    %s\n', uncalibrated{:});
    fprintf(['Routing is correct, but every affected channel drives 0 V by\n' ...
        'design until its endpoints are measured at the connected VCU pin\n' ...
        'under load. Moving the GUI throttle/brake will NOT sweep voltage.\n\n']);
end

if ~alreadyLoaded
    bdclose(model);
end

if failures > 0
    error('verify_pinouts:mismatch', ...
        '%d PINOUTS.MD claim(s) do not match the model.', failures);
end
fprintf('All machine-checkable PINOUTS.MD claims match the model.\n\n');
end

% -------------------------------------------------------------------- helpers

function results = check(results, label, actual, expected)
%CHECK Record one string-equality check.
passed = strcmp(strtrim(actual), expected);
results(end + 1) = struct('label', label, 'pass', passed, ...
    'detail', sprintf('expected "%s", got "%s"', expected, strtrim(actual)));
end

function text = normalizeVector(text)
%NORMALIZEVECTOR Collapse whitespace so '[1  2]' compares equal to '[1 2]'.
text = strtrim(text);
text = regexprep(text, '\s+', ' ');
text = regexprep(text, '\[\s+', '[');
text = regexprep(text, '\s+\]', ']');
end

function [name, sourcePortNumber] = sourceBlockForInport(block, port)
%SOURCEBLOCKFORINPORT Name and source-port number driving one inport of BLOCK.
name = '<unconnected>';
sourcePortNumber = -1;
handles = get_param(block, 'PortHandles');
if port > numel(handles.Inport)
    name = sprintf('<no port %d>', port);
    return
end
line = get_param(handles.Inport(port), 'Line');
if line == -1
    return
end
sourcePort = get_param(line, 'SrcPortHandle');
if sourcePort == -1
    return
end
name = get_param(sourcePort, 'Parent');
sourcePortNumber = get_param(sourcePort, 'PortNumber');
end
