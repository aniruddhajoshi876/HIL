function build_decision16_spike(force)
%BUILD_DECISION16_SPIKE Generate the throwaway model for plan decision 16.
%
%   Decision 16 asks whether Simulink Real-Time R2024b supports independent
%   field-level SETPARAM updates, and if not, whether separately tunable flat
%   scalars must be used instead.
%
%   This model exists only to answer that question. It is NOT part of the
%   inverter HIL deliverable and must never be deployed alongside it. It
%   declares the same logical quantity three ways, each referenced by a real
%   block so that none of them is pruned during code generation:
%
%     Group A  spk_flat_chN_torque / spk_flat_chN_enable
%              Eight independent flat scalars. This is the plan's stated
%              fallback and is assumed to work; it is included as the control.
%     Group B  spk_struct_chN
%              Four scalar bus-typed structs, one per channel, each with a
%              torque and an enable field. Answers the sibling-field question.
%     Group C  spk_array
%              One 1x4 bus-typed struct array, which is the shape
%              INVERTERHILGUI.PARAMETERCONTRACT actually proposes. Answers the
%              cross-channel question. Group C is built inside a try block
%              because an array of buses driven from a CONSTANT block is the
%              part most likely to be rejected outright; a rejection is itself
%              a decision-16 answer and must be reported, not thrown away.
%
%   BUILD_DECISION16_SPIKE(TRUE) overwrites existing artifacts.

if nargin < 1
    force = false;
end
if ~(islogical(force) && isscalar(force))
    error('decision16:InvalidBuildOption', 'force must be a logical scalar.');
end
assert(strcmp(version('-release'), '2024b'), 'decision16:WrongRelease', ...
    'This spike must be built in R2024b, not R%s.', version('-release'));

root = fileparts(mfilename('fullpath'));
model = 'decision16_spike';
modelPath = fullfile(root, [model '.slx']);
dictionaryPath = fullfile(root, [model '.sldd']);

if bdIsLoaded(model)
    close_system(model, 0);
end
prepareOutput(modelPath, force);
prepareOutput(dictionaryPath, force);

createDictionary(dictionaryPath);
new_system(model);
cleanup = onCleanup(@() closeIfLoaded(model));
set_param(model, ...
    'DataDictionary', [model '.sldd'], ...
    'SolverType', 'Fixed-step', ...
    'Solver', 'FixedStepDiscrete', ...
    'FixedStep', '0.001', ...
    'StartTime', '0.0', ...
    'StopTime', 'inf', ...
    'SystemTargetFile', 'speedgoat.tlc', ...
    'DefaultParameterBehavior', 'Tunable');

port = 0;
port = addFlatGroup(model, port);
port = addStructGroup(model, port);
[port, arrayStatus] = addArrayGroup(model, port);

addAnnotation(model, sprintf(['DECISION 16 SPIKE - THROWAWAY\n' ...
    'Not part of the inverter HIL deliverable; never deploy with it\n' ...
    'Group C (struct array) status: %s'], arrayStatus), [40 20 760 90]);

save_system(model, modelPath, 'SaveModelWorkspace', false);
set_param(model, 'SimulationCommand', 'update');
save_system(model, modelPath);
fprintf('Created %s with %d root outports (group C: %s).\n', ...
    modelPath, port, arrayStatus);
end

function port = addFlatGroup(model, port)
for channel = 1:4
    y = 40 + 60 * (channel - 1);
    port = addConstantOutport(model, ...
        sprintf('Flat Ch%d Torque', channel), ...
        sprintf('spk_flat_ch%d_torque', channel), '', 40, y, port);
    port = addConstantOutport(model, ...
        sprintf('Flat Ch%d Enable', channel), ...
        sprintf('spk_flat_ch%d_enable', channel), '', 40, y + 28, port);
end
end

function port = addStructGroup(model, port)
for channel = 1:4
    y = 40 + 60 * (channel - 1);
    name = sprintf('Struct Ch%d', channel);
    add_block('simulink/Sources/Constant', [model '/' name], ...
        'Value', sprintf('spk_struct_ch%d', channel), ...
        'OutDataTypeStr', 'Bus: SpkChannelBus', ...
        'SampleTime', '0.001', 'Position', [340 y 450 y + 24]);
    selector = sprintf('%s Fields', name);
    add_block('simulink/Signal Routing/Bus Selector', [model '/' selector], ...
        'OutputSignals', 'torque,enable', 'Position', [490 y 495 y + 40]);
    add_line(model, [name '/1'], [selector '/1'], 'autorouting', 'on');
    port = addOutport(model, sprintf('%s Torque', name), selector, 1, ...
        560, y, port);
    port = addOutport(model, sprintf('%s Enable', name), selector, 2, ...
        560, y + 26, port);
end
end

function [port, status] = addArrayGroup(model, port)
% An array of buses sourced from a CONSTANT block is the shape the parameter
% contract proposes and the shape most likely to be rejected. A rejection is a
% decision-16 finding, so it is captured and reported rather than raised.
status = 'built';
try
    add_block('simulink/Sources/Constant', [model '/Array Channels'], ...
        'Value', 'spk_array', 'OutDataTypeStr', 'Bus: SpkChannelBus', ...
        'SampleTime', '0.001', 'Position', [340 300 450 330]);
    for element = 1:2
        y = 300 + 70 * (element - 1);
        picker = sprintf('Array Element %d', element);
        add_block('simulink/Signal Routing/Selector', [model '/' picker], ...
            'NumberOfDimensions', '1', 'IndexOptions', 'Index vector (dialog)', ...
            'Indices', sprintf('%d', element), 'InputPortWidth', '4', ...
            'Position', [490 y 540 y + 30]);
        add_line(model, 'Array Channels/1', [picker '/1'], 'autorouting', 'on');
        selector = sprintf('%s Fields', picker);
        add_block('simulink/Signal Routing/Bus Selector', ...
            [model '/' selector], 'OutputSignals', 'torque,enable', ...
            'Position', [590 y 595 y + 40]);
        add_line(model, [picker '/1'], [selector '/1'], 'autorouting', 'on');
        port = addOutport(model, sprintf('%s Torque', picker), selector, 1, ...
            660, y, port);
        port = addOutport(model, sprintf('%s Enable', picker), selector, 2, ...
            660, y + 26, port);
    end
catch buildError
    status = buildError.identifier;
    if isempty(status)
        status = 'rejected';
    end
    warning('decision16:ArrayGroupRejected', ...
        'Group C could not be built: %s', buildError.message);
end
end

function port = addConstantOutport(model, name, value, dataType, x, y, port)
% NAME-VALUE pairs are accumulated in OPTIONS; ARGUMENTS is a reserved word.
options = {'Value', value, 'SampleTime', '0.001', ...
    'Position', [x y x + 110 y + 24]};
if ~isempty(dataType)
    options = [options, {'OutDataTypeStr', dataType}];
end
add_block('simulink/Sources/Constant', [model '/' name], options{:});
port = addOutport(model, [name ' Out'], name, 1, x + 160, y, port);
end

function port = addOutport(model, name, sourceBlock, sourcePort, x, y, port)
port = port + 1;
add_block('simulink/Sinks/Out1', [model '/' name], ...
    'Port', num2str(port), 'Position', [x y x + 30 y + 20]);
add_line(model, sprintf('%s/%d', sourceBlock, sourcePort), ...
    [name '/1'], 'autorouting', 'on');
end

function createDictionary(path)
dictionary = Simulink.data.dictionary.create(path);
cleanup = onCleanup(@() close(dictionary));
section = getSection(dictionary, 'Design Data');

addEntry(section, 'SpkChannelBus', channelBus());

for channel = 1:4
    addEntry(section, sprintf('spk_flat_ch%d_torque', channel), ...
        scalarParameter(0, -200, 200));
    addEntry(section, sprintf('spk_flat_ch%d_enable', channel), ...
        scalarParameter(false, false, true));
    addEntry(section, sprintf('spk_struct_ch%d', channel), ...
        busParameter(channelValue()));
end
addEntry(section, 'spk_array', busParameter(repmat(channelValue(), 1, 4)));

saveChanges(dictionary);
end

function bus = channelBus()
torque = Simulink.BusElement;
torque.Name = 'torque';
torque.DataType = 'double';
enable = Simulink.BusElement;
enable.Name = 'enable';
enable.DataType = 'boolean';
bus = Simulink.Bus;
bus.Elements = [torque enable];
bus.Description = 'Decision 16 spike channel parameter.';
end

function value = channelValue()
value = struct('torque', 0, 'enable', false);
end

function value = scalarParameter(initialValue, minimum, maximum)
value = Simulink.Parameter(initialValue);
value.Min = double(minimum);
value.Max = double(maximum);
value.CoderInfo.StorageClass = 'SimulinkGlobal';
end

function value = busParameter(initialValue)
value = Simulink.Parameter(initialValue);
value.DataType = 'Bus: SpkChannelBus';
value.CoderInfo.StorageClass = 'SimulinkGlobal';
end

function prepareOutput(path, force)
if isfile(path)
    if ~force
        error('decision16:ArtifactExists', ...
            'Artifact exists; call build_decision16_spike(true): %s', path);
    end
    delete(path);
end
end

function addAnnotation(model, text, position)
annotation = Simulink.Annotation(model, text);
annotation.Position = position;
annotation.BackgroundColor = 'orange';
annotation.FontWeight = 'bold';
end

function closeIfLoaded(model)
if bdIsLoaded(model)
    close_system(model, 0);
end
end
