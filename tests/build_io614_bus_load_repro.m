function build_io614_bus_load_repro(force)
%BUILD_IO614_BUS_LOAD_REPRO Reproduce Speedgoat support ticket 241678.
%
% Builds the exact repro described to Speedgoat support: IO614 module 1,
% CAN channel 1 (connector B), CAN HS, 1 Mbit/s classical CAN, two
% standard 11-bit DLC-8 CAN Write blocks each sending unconditionally
% every 1 ms (no Tx Control gating), plus an IO614 CAN Status block with
% all 6 outputs wired to root Outports in mask order (Bus Load,
% Bus-Off Status, Recovery Count, Transmit Buffer Overrun, Receive
% Buffer Overrun, Bus-Warning Limit).

if nargin < 1
    force = false;
end
if ~strcmp(version('-release'), '2024b')
    error('io614busload:WrongRelease', ...
        'This test must be built with MATLAB/Simulink R2024b, not %s.', ...
        version('-release'));
end

root = fileparts(mfilename('fullpath'));
model = 'io614_bus_load_repro_R2024b';
modelPath = fullfile(root, [model '.slx']);

if bdIsLoaded(model)
    close_system(model, 0);
end
if isfile(modelPath)
    if ~force
        error('io614busload:ArtifactExists', ...
            'Artifact exists; call build_io614_bus_load_repro(true): %s', modelPath);
    end
    delete(modelPath);
end

load_system('speedgoatlib_IO614');

new_system(model);
cleanupModel = onCleanup(@() closeIfLoaded(model));
set_param(model, ...
    'SolverType', 'Fixed-step', ...
    'Solver', 'FixedStepDiscrete', ...
    'FixedStep', '0.001', ...
    'StartTime', '0.0', ...
    'StopTime', 'inf', ...
    'SystemTargetFile', 'speedgoat.tlc');

setup = add_block('speedgoatlib_IO614/CAN and LIN Setup ', ...
    [model '/IO614 CAN Setup'], 'Position', [40 30 220 100]);
set_param(setup, 'moduleType', 'IO614', 'id', '1', ...
    'canChn1', 'CAN (HS)', 'canChn2', 'Disabled', ...
    'canChn3', 'Disabled', 'canChn4', 'Disabled', ...
    'arbBdrChn1', '1.0 MBaud');

addTxFrame(model, 1, hex2dec('300'), [1 2 3 4 5 6 7 8], [40 150 240 260]);
addTxFrame(model, 2, hex2dec('301'), [8 7 6 5 4 3 2 1], [40 300 240 410]);

status = add_block('speedgoatlib_IO614/CAN Status ', [model '/IO614 CAN Status'], ...
    'Position', [400 150 600 260]);
set_param(status, 'moduleType', 'IO614', 'id', '1', 'channel', '1', ...
    'canType', 'CAN (HS)', 'autoRecovery', 'off', 'ts', '0.001');

diagNames = {'bus_load', 'bus_off_status', 'recovery_count', ...
    'transmit_buffer_overrun', 'receive_buffer_overrun', 'bus_warning_limit'};
for index = 1:numel(diagNames)
    addNamedOutport(model, diagNames{index}, 660, ...
        150 + 30 * (index - 1), 'IO614 CAN Status', index);
end

addAnnotation(model, ...
    ['IO614 BUS LOAD REPRO - Speedgoat ticket 241678\n' ...
     'Two standard 11-bit DLC-8 frames, unconditional Tx every 1 ms.\n' ...
     'Compare bus_load output against PCAN-View on the same wire.'], ...
    [40 470 700 540], 'yellow');

save_system(model, modelPath, 'SaveModelWorkspace', false);
set_param(model, 'SimulationCommand', 'update');
save_system(model, modelPath);
fprintf('Created %s with MATLAB %s.\n', modelPath, version('-release'));
end

function addTxFrame(model, frameNum, id, payload, position)
prefix = sprintf('%s/Tx%d ', model, frameNum);

add_block('simulink/Sources/Constant', [prefix 'Control (always send)'], ...
    'Value', 'uint32(1)', 'Position', position + [0 0 -140 -220]);

add_block('simulink/Sources/Constant', [prefix 'Extended (0)'], ...
    'Value', 'uint8(0)', 'Position', position + [40 0 -100 -220]);
add_block('simulink/Sources/Constant', [prefix 'Length (8)'], ...
    'Value', 'uint8(8)', 'Position', position + [40 30 -100 -190]);
add_block('simulink/Sources/Constant', [prefix 'Remote (0)'], ...
    'Value', 'uint8(0)', 'Position', position + [40 60 -100 -160]);
add_block('simulink/Sources/Constant', [prefix 'Error (0)'], ...
    'Value', 'uint8(0)', 'Position', position + [40 90 -100 -130]);
add_block('simulink/Sources/Constant', [prefix 'ID'], ...
    'Value', sprintf('uint32(%d)', id), 'Position', position + [40 120 -100 -100]);
add_block('simulink/Sources/Constant', [prefix 'Timestamp (0)'], ...
    'Value', 'double(0)', 'Position', position + [40 150 -100 -70]);
add_block('simulink/Sources/Constant', [prefix 'Payload'], ...
    'Value', sprintf('uint8([%s])', num2str(payload)), ...
    'Position', position + [40 180 -100 -40]);

busCreator = add_block('simulink/Signal Routing/Bus Creator', [prefix 'Bus Creator'], ...
    'Inputs', '7', 'Position', position + [180 0 220 220]);

fields = {'Extended', 'Length', 'Remote', 'Error', 'ID', 'Timestamp', 'Data'};
srcSuffix = {'Extended (0)', 'Length (8)', 'Remote (0)', 'Error (0)', ...
    'ID', 'Timestamp (0)', 'Payload'};
for k = 1:numel(fields)
    line = add_line(model, sprintf('%s%s/1', prefix, srcSuffix{k}), ...
        sprintf('%s/%d', get_param(busCreator, 'Name'), k), 'autorouting', 'on');
    set_param(line, 'Name', fields{k});
end

write = add_block('speedgoatlib_IO614/CAN Write ', [prefix 'Write'], ...
    'Position', position + [260 0 460 60]);
set_param(write, 'moduleType', 'IO614', 'id', '1', 'channel', '1', ...
    'canType', 'CAN (HS)', 'useBusIn', 'on', 'numOfMsg', '1', ...
    'enableInput', 'on', 'enableStatusPort', 'off', 'ts', '0.001');

add_line(model, sprintf('%sControl (always send)/1', prefix), ...
    sprintf('%s/1', get_param(write, 'Name')), 'autorouting', 'on');
add_line(model, sprintf('%s/1', get_param(busCreator, 'Name')), ...
    sprintf('%s/2', get_param(write, 'Name')), 'autorouting', 'on');
end

function addNamedOutport(model, name, x, y, srcBlock, srcPort)
outBlock = add_block('simulink/Sinks/Out1', [model '/' name], ...
    'Position', [x y x + 40 y + 20]);
portNumber = str2double(get_param(outBlock, 'Port'));
set_param(outBlock, 'Port', num2str(portNumber));
add_line(model, sprintf('%s/%d', srcBlock, srcPort), [name '/1'], ...
    'autorouting', 'on');
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
