function build_inverter_hil_model(force)
%BUILD_INVERTER_HIL_MODEL Generate the R2024b model and data dictionary.

if nargin < 1
    force = false;
end
if ~(islogical(force) && isscalar(force))
    error('inverterhil:InvalidBuildOption', 'force must be a logical scalar.');
end

root = inverter_hil_setup();
model = 'inverter_hil';
modelPath = fullfile(root, [model '.slx']);
dictionaryPath = fullfile(root, [model '.sldd']);

if bdIsLoaded(model)
    close_system(model, 0);
end
prepareOutput(modelPath, force);
prepareOutput(dictionaryPath, force);

createDictionary(dictionaryPath);
new_system(model);
cleanupModel = onCleanup(@() closeIfLoaded(model));
set_param(model, ...
    'DataDictionary', [model '.sldd'], ...
    'SolverType', 'Fixed-step', ...
    'Solver', 'FixedStepDiscrete', ...
    'FixedStep', '0.001', ...
    'StartTime', '0.0', ...
    'StopTime', 'inf', ...
    'SystemTargetFile', 'slrealtime.tlc', ...
    'DefaultParameterBehavior', 'Tunable', ...
    'SignalLogging', 'on', ...
    'InitFcn', 'inverterhil.enforceHardwarePreflight(bdroot);');

addArchitecture(model);
addHardwareBoundary(model);
addAnnotation(model, ...
    ['INVERTER HIL - R2024b SAFE SCAFFOLD\n' ...
     'Constant-zero MIL topology; functional core integration pending\n' ...
     'Target I/O is PRE-FLIGHT DISABLED and callback-gated\n' ...
     'Torque scale provisional (1/512 selected; 1/256 retained)'], ...
    [40 20 800 88], 'yellow');

save_system(model, modelPath, 'SaveModelWorkspace', false);
set_param(model, 'SimulationCommand', 'update');
save_system(model, modelPath);
fprintf('Created %s and %s with MATLAB %s.\n', ...
    modelPath, dictionaryPath, version('-release'));
end

function prepareOutput(path, force)
if isfile(path)
    if ~force
        error('inverterhil:ArtifactExists', ...
            'Artifact exists; call build_inverter_hil_model(true): %s', path);
    end
    delete(path);
end
end

function createDictionary(path)
dictionary = Simulink.data.dictionary.create(path);
cleanup = onCleanup(@() close(dictionary));
section = getSection(dictionary, 'Design Data');

addEntry(section, 'hil_model_release', 'R2024b');
addEntry(section, 'hil_base_sample_s', parameter(1e-3, 1e-3, 1e-3));
addEntry(section, 'hil_status_sample_s', parameter(5e-3, 5e-3, 5e-3));
addEntry(section, 'hil_cmd_pedals_throttle', parameter(0, 0, 1));
addEntry(section, 'hil_cmd_pedals_brake', parameter(0, 0, 1));
addEntry(section, 'hil_cmd_digital', parameter(false(1, 8), false, true));
addEntry(section, 'hil_cmd_dc_link_v', parameter([0 0], [0 0], [750 750]));
addEntry(section, 'hil_cmd_load_nm', parameter(zeros(1, 4), ...
    -200 * ones(1, 4), 200 * ones(1, 4)));
addEntry(section, 'hil_cmd_connected', parameter(true(1, 4), false, true));
addEntry(section, 'hil_cmd_fault_mask', parameter(zeros(1, 4, 'uint32'), ...
    uint32(0), intmax('uint32')));
addEntry(section, 'hil_cmd_gui_heartbeat', parameter(uint32(0), ...
    uint32(0), intmax('uint32')));

addEntry(section, 'hil_cal_pedal_released_v', parameter(NaN(1, 4), ...
    zeros(1, 4), 5 * ones(1, 4)));
addEntry(section, 'hil_cal_pedal_pressed_v', parameter(NaN(1, 4), ...
    zeros(1, 4), 5 * ones(1, 4)));
addEntry(section, 'hil_safe_analog_reset_v', parameter(zeros(1, 4), ...
    zeros(1, 4), zeros(1, 4)));
addEntry(section, 'hil_safe_digital_reset', parameter(false(1, 8), false, false));

addEntry(section, 'hil_control_can_ids', uint32(hex2dec( ...
    {'186', '196', '1A6', '1B6'})));
addEntry(section, 'hil_status_can_ids', uint32(hex2dec( ...
    {'383', '385', '393', '395', '3A3', '3A5', '3B3', '3B5', '400'})));
addEntry(section, 'hil_torque_profile_id', ...
    'ephorus3-v1.03-provisional-1over512');
addEntry(section, 'hil_torque_scale_nm_per_count', 1 / 512);
addEntry(section, 'hil_torque_scale_verified', false);
addEntry(section, 'hil_hardware_preflight_complete', false);
addEntry(section, 'hil_torque_results_provisional', true);

saveChanges(dictionary);
end

function value = parameter(initialValue, minimum, maximum)
value = Simulink.Parameter(initialValue);
value.Min = double(min(minimum(:)));
value.Max = double(max(maximum(:)));
value.CoderInfo.StorageClass = 'SimulinkGlobal';
end

function addArchitecture(model)
blocks = { ...
    'Test Inputs', [40 130 220 300]; ...
    'Fault Injection', [40 370 220 485]; ...
    'Pedal Sensor Emulation', [310 90 520 205]; ...
    'VCU Digital Interface', [310 235 520 350]; ...
    'IO614 CAN Interface', [310 390 520 545]; ...
    'Ephorus Channel 1', [630 80 850 185]; ...
    'Ephorus Channel 2', [630 220 850 325]; ...
    'Ephorus Channel 3', [630 360 850 465]; ...
    'Ephorus Channel 4', [630 500 850 605]; ...
    'Ephorus System Status', [960 210 1180 430]; ...
    'Measurements and Logging', [1280 200 1500 445]};
for index = 1:size(blocks, 1)
    add_block('simulink/Ports & Subsystems/Subsystem', ...
        [model '/' blocks{index, 1}], 'Position', blocks{index, 2});
end

buildTestInputs([model '/Test Inputs']);
buildFaultInputs([model '/Fault Injection']);
buildSafeInterface([model '/Pedal Sensor Emulation'], 2, 1, ...
    'zeros(1,4)', 'PedalVoltageV');
buildSafeInterface([model '/VCU Digital Interface'], 2, 1, ...
    'false(1,8)', 'DigitalStimulus');
buildCanInterface([model '/IO614 CAN Interface']);
for channel = 1:4
    buildChannel([model sprintf('/Ephorus Channel %d', channel)], channel);
end
buildSystemStatus([model '/Ephorus System Status']);
buildMeasurements([model '/Measurements and Logging']);

add_block('simulink/Signal Routing/Demux', [model '/Load Demux'], ...
    'Outputs', '4', 'Position', [260 276 265 344]);
add_block('simulink/Signal Routing/Demux', [model '/Fault Demux'], ...
    'Outputs', '4', 'Position', [560 520 565 588]);
add_block('simulink/Signal Routing/Demux', [model '/DC Link Demux'], ...
    'Outputs', '2', 'Position', [560 312 565 358]);

add_line(model, 'Test Inputs/1', 'Pedal Sensor Emulation/1', 'autorouting', 'on');
add_line(model, 'Fault Injection/1', 'Pedal Sensor Emulation/2', 'autorouting', 'on');
add_line(model, 'Test Inputs/2', 'VCU Digital Interface/1', 'autorouting', 'on');
add_line(model, 'Fault Injection/1', 'VCU Digital Interface/2', 'autorouting', 'on');
add_line(model, 'Test Inputs/3', 'IO614 CAN Interface/1', 'autorouting', 'on');
add_line(model, 'Ephorus System Status/1', 'IO614 CAN Interface/2', 'autorouting', 'on');
add_line(model, 'Test Inputs/4', 'Load Demux/1', 'autorouting', 'on');
add_line(model, 'Test Inputs/5', 'DC Link Demux/1', 'autorouting', 'on');
add_line(model, 'Fault Injection/2', 'Fault Demux/1', 'autorouting', 'on');

for channel = 1:4
    channelName = sprintf('Ephorus Channel %d', channel);
    add_line(model, 'IO614 CAN Interface/1', [channelName '/1'], 'autorouting', 'on');
    add_line(model, sprintf('Load Demux/%d', channel), ...
        [channelName '/2'], 'autorouting', 'on');
    dcPort = 1 + (channel > 2);
    add_line(model, sprintf('DC Link Demux/%d', dcPort), ...
        [channelName '/3'], 'autorouting', 'on');
    add_line(model, sprintf('Fault Demux/%d', channel), ...
        [channelName '/4'], 'autorouting', 'on');
    add_line(model, [channelName '/1'], ...
        sprintf('Ephorus System Status/%d', 2 * channel - 1), 'autorouting', 'on');
    add_line(model, [channelName '/2'], ...
        sprintf('Ephorus System Status/%d', 2 * channel), 'autorouting', 'on');
    add_line(model, [channelName '/3'], ...
        sprintf('Measurements and Logging/%d', channel + 1), 'autorouting', 'on');
end
add_line(model, 'IO614 CAN Interface/2', ...
    'Measurements and Logging/1', 'autorouting', 'on');
end

function buildTestInputs(path)
clearSubsystem(path);
values = {'[0 0]', 'false(1,8)', 'zeros(4,8,''uint8'')', ...
    'zeros(1,4)', '[0 0]'};
names = {'PedalCommand', 'DigitalCommand', 'ControlFrames', ...
    'LoadTorqueNm', 'DCLinkV'};
for index = 1:5
    y = 35 + 55 * (index - 1);
    add_block('simulink/Sources/Constant', [path '/Safe ' names{index}], ...
        'Value', values{index}, 'SampleTime', '0.001', ...
        'Position', [35 y 115 y + 25]);
    add_block('simulink/Sinks/Out1', [path '/' names{index}], ...
        'Port', num2str(index), 'Position', [150 y 180 y + 20]);
    add_line(path, ['Safe ' names{index} '/1'], [names{index} '/1']);
end
end

function buildFaultInputs(path)
clearSubsystem(path);
addConstantOut(path, 'PreflightSafe', 'false', 1, 40);
addConstantOut(path, 'FaultMask', 'zeros(1,4,''uint32'')', 2, 95);
end

function buildSafeInterface(path, inputCount, outputCount, value, outputName)
clearSubsystem(path);
for index = 1:inputCount
    add_block('simulink/Sources/In1', sprintf('%s/Input%d', path, index), ...
        'Port', num2str(index), 'Position', [25 35 + 55 * index 55 55 + 55 * index]);
    add_block('simulink/Sinks/Terminator', sprintf('%s/Input%d Terminator', path, index), ...
        'Position', [90 35 + 55 * index 110 55 + 55 * index]);
    add_line(path, sprintf('Input%d/1', index), sprintf('Input%d Terminator/1', index));
end
for index = 1:outputCount
    addConstantOut(path, outputName, value, index, 45);
end
end

function buildCanInterface(path)
clearSubsystem(path);
addTerminatedInput(path, 'ControlFramesRaw', 1, 45);
addTerminatedInput(path, 'StatusPayloads', 2, 100);
addConstantOut(path, 'DecodedCommands', 'zeros(4,8,''uint8'')', 1, 45);
addConstantOut(path, 'CANDiagnostics', 'zeros(1,8,''uint32'')', 2, 110);
end

function buildChannel(path, channel)
clearSubsystem(path);
inputNames = {'DecodedCommands', 'LoadTorqueNm', 'DCLinkV', 'FaultMask'};
for index = 1:4
    addTerminatedInput(path, inputNames{index}, index, 25 + 45 * index);
end
addConstantOut(path, sprintf('Status3X3_Ch%d', channel), ...
    'zeros(1,8,''uint8'')', 1, 45);
addConstantOut(path, sprintf('Status3X5_Ch%d', channel), ...
    'zeros(1,8,''uint8'')', 2, 100);
addConstantOut(path, sprintf('Observations_Ch%d', channel), ...
    'zeros(1,16)', 3, 155);
end

function buildSystemStatus(path)
clearSubsystem(path);
for index = 1:8
    addTerminatedInput(path, sprintf('StatusInput%d', index), index, 15 + 35 * index);
end
addConstantOut(path, 'OrderedStatusPayloads', ...
    'zeros(9,8,''uint8'')', 1, 55);
end

function buildMeasurements(path)
clearSubsystem(path);
for index = 1:5
    addTerminatedInput(path, sprintf('Observation%d', index), index, 25 + 50 * index);
end
end

function addTerminatedInput(path, name, port, y)
add_block('simulink/Sources/In1', [path '/' name], ...
    'Port', num2str(port), 'Position', [25 y 55 y + 20]);
add_block('simulink/Sinks/Terminator', [path '/' name ' Terminator'], ...
    'Position', [90 y 110 y + 20]);
add_line(path, [name '/1'], [name ' Terminator/1']);
end

function addConstantOut(path, name, value, port, y)
add_block('simulink/Sources/Constant', [path '/Safe ' name], ...
    'Value', value, 'SampleTime', '0.001', ...
    'Position', [35 y 125 y + 25]);
add_block('simulink/Sinks/Out1', [path '/' name], ...
    'Port', num2str(port), 'Position', [165 y 195 y + 20]);
add_line(path, ['Safe ' name '/1'], [name '/1']);
end

function clearSubsystem(path)
lineHandles = get_param(path, 'LineHandles');
fields = fieldnames(lineHandles);
for index = 1:numel(fields)
    handles = lineHandles.(fields{index});
    handles = handles(handles ~= -1);
    for handle = handles(:)'
        try %#ok<TRYNC>
            delete_line(handle);
        end
    end
end
blocks = find_system(path, 'SearchDepth', 1, 'Type', 'Block');
for index = 2:numel(blocks)
    delete_block(blocks{index});
end
end

function addHardwareBoundary(model)
path = [model '/Hardware I O - PRE-FLIGHT DISABLED'];
add_block('simulink/Ports & Subsystems/Subsystem', path, ...
    'Position', [960 505 1500 720], ...
    'BackgroundColor', 'red', ...
    'AttributesFormatString', ...
    'PRE-FLIGHT DISABLED\nElectrical/harness gates are open');
clearSubsystem(path);

io183 = add_block('speedgoatlib_IO183/Setup', [path '/IO183 Setup'], ...
    'Position', [25 30 160 100]);
set_param(io183, 'parModuleId', '1', 'parPciSlot', '-1', ...
    'parDaSimult', 'on', 'parAdCoupling', 'Single Ended', ...
    'parAdRange', '0..5V', 'parAdChannelLow', '1', ...
    'parAdChannelHigh', '4', 'parDaChannels', '[1 2 3 4]', ...
    'parDaRange', '0..5V', 'parDaInit', '[0 0 0 0]', ...
    'parDaReset', '[0 0 0 0]', 'parDoChannels', '[1 2 3 4 5 6 7 8]', ...
    'parDoInit', '[0 0 0 0 0 0 0 0]', ...
    'parDoReset', '[0 0 0 0 0 0 0 0]', ...
    'parDiChannels', '[9 10 11 12 13]', ...
    'parIOPullReferenceFront', 'Pull-down');

ao = add_block('speedgoatlib_IO183/Analog Output', ...
    [path '/IO183 AO01-AO04 Safe Zero'], 'Position', [25 130 170 185]);
set_param(ao, 'parModuleId', '1', 'parSampTime', '0.001', ...
    'parDaSimult', 'on', 'parDaChannels', '[1 2 3 4]', ...
    'parDaInit', '[0 0 0 0]', 'parDaReset', '[0 0 0 0]');
ai = add_block('speedgoatlib_IO183/Analog Input', ...
    [path '/IO183 AI01-AI04 Rail Monitor'], 'Position', [25 215 170 270]);
set_param(ai, 'parModuleId', '1', 'parSampTime', '0.001', ...
    'parAdChannelLow', '1', 'parAdChannelHigh', '4');
dio = add_block('speedgoatlib_IO183/Digital Output', ...
    [path '/IO183 DIO01-DIO08 Safe Zero'], 'Position', [25 300 170 355]);
set_param(dio, 'parModuleId', '1', 'parSampTime', '0.001', ...
    'parDoChannels', '[1 2 3 4 5 6 7 8]', ...
    'parDoInit', '[0 0 0 0 0 0 0 0]', ...
    'parDoReset', '[0 0 0 0 0 0 0 0]');
di = add_block('speedgoatlib_IO183/Digital Input', ...
    [path '/IO183 DIO09-DIO13 VCU Monitor'], 'Position', [25 385 170 440]);
set_param(di, 'parModuleId', '1', 'parSampTime', '0.001', ...
    'parDiChannels', '[9 10 11 12 13]');

setup = add_block('speedgoatlib_IO614/CAN and LIN Setup ', ...
    [path '/IO614 CAN Setup'], 'Position', [235 30 390 100]);
set_param(setup, 'moduleType', 'IO614', 'id', '1', ...
    'canChn1', 'CAN (HS)', 'canChn2', 'Disabled', ...
    'canChn3', 'Disabled', 'canChn4', 'Disabled', ...
    'arbBdrChn1', '1.0 MBaud');
read = add_block('speedgoatlib_IO614/CAN Read ', ...
    [path '/IO614 CAN FIFO Read Raw'], 'Position', [235 130 390 190]);
set_param(read, 'moduleType', 'IO614', 'id', '1', 'channel', '1', ...
    'canType', 'CAN (HS)', 'useBusOut', 'off', ...
    'HasMulRead', 'Single Read from Buffer (FIFO)', ...
    'LabelInHex', 'on', 'ts', '0.001');
status = add_block('speedgoatlib_IO614/CAN Status ', ...
    [path '/IO614 CAN Diagnostics'], 'Position', [235 220 390 280]);
set_param(status, 'moduleType', 'IO614', 'id', '1', 'channel', '1', ...
    'canType', 'CAN (HS)', 'autoRecovery', 'off', 'ts', '0.001');

ids = hex2dec({'383', '385', '393', '395', '3A3', ...
    '3A5', '3B3', '3B5', '400'});
for index = 1:numel(ids)
    row = mod(index - 1, 5);
    column = floor((index - 1) / 5);
    block = add_block('speedgoatlib_IO614/CAN Write ', ...
        sprintf('%s/CAN Write 0x%03X', path, ids(index)), ...
        'Position', [455 + 190 * column, 30 + 80 * row, ...
        610 + 190 * column, 85 + 80 * row]);
    set_param(block, 'moduleType', 'IO614', 'id', '1', ...
        'channel', '1', 'canType', 'CAN (HS)', 'useBusIn', 'off', ...
        'numOfMsg', '1', 'enableStatusPort', 'on', 'ts', '0.005', ...
        'UserData', uint32(ids(index)), 'UserDataPersistent', 'on', ...
        'Description', sprintf('Ordered Ephorus status ID 0x%03X', ids(index)));
end

set_param(path, 'Commented', 'on');
end

function addAnnotation(model, text, position, color)
annotation = Simulink.Annotation(model, text);
annotation.Position = position;
annotation.BackgroundColor = color;
annotation.FontWeight = 'bold';
end

function closeIfLoaded(model)
if bdIsLoaded(model)
    close_system(model, 0);
end
end
