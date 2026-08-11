function patch_virtual_vcu_state_outputs(modelPath)
%PATCH_VIRTUAL_VCU_STATE_OUTPUTS Add reviewable VCU state/control observers.
%
% R2024b-only model edit. The saved model is changed through Simulink and
% Stateflow APIs; the SLX archive is never edited directly. The existing
% five 8-byte CAN payloads remain elements 1:40. Elements 41:44 are state
% ID, MAIN_EN_OUT, PRECH_EN_OUT, and INV_CTRL_EN. Stable root Outport paths
% make those simulated outputs readable by the GUI. This script deliberately
% does not rewire physical IO183 outputs.

if nargin < 1
    modelPath = fullfile(fileparts(fileparts(fileparts(mfilename('fullpath')))), ...
        'inverter_hil', 'inverter_hil.slx');
end
if ~strcmp(version('-release'), '2024b')
    error('virtualvcu:WrongRelease', 'Build with MATLAB R2024b only.');
end

model = 'inverter_hil';
load_system(modelPath);
cleanup = onCleanup(@() close_system(model, 0));
root = [model '/Virtual VCU'];
chartPath = [root '/Virtual VCU LV_ON'];
assert(getSimulinkBlockHandle(root) ~= -1, ...
    'virtualvcu:MissingBoundary', 'Virtual VCU boundary is missing.');
assert(getSimulinkBlockHandle(chartPath) ~= -1, ...
    'virtualvcu:MissingChart', 'Virtual VCU LV_ON chart is missing.');

chart = sfroot().find('-isa', 'Stateflow.EMChart', '-and', ...
    'Path', chartPath);
assert(~isempty(chart), 'virtualvcu:MissingChart', ...
    'Virtual VCU MATLAB Function chart is missing.');
chart(1).Script = fileread(fullfile(fileparts(mfilename('fullpath')), ...
    'virtualVcuDeployStep.m'));

split = [root '/VCU Payload Split'];
assert(getSimulinkBlockHandle(split) ~= -1, ...
    'virtualvcu:MissingPayloadSplit', 'VCU payload split is missing.');
set_param(split, 'Outputs', '[8 8 8 8 8 1 1 1 1]');

names = {'State ID', 'Main Enable', 'Precharge Enable', ...
    'Inverter Control Enable'};
tags = {'VirtualVcuStateId', 'VirtualVcuMainEnable', ...
    'VirtualVcuPrechargeEnable', 'VirtualVcuInverterControlEnable'};
% The pedal payload is already the first CAN output; expose a copy for
% honest model-generated observation in the GUI.
pedalTag = 'VirtualVcuPedalPayload';
if getSimulinkBlockHandle([root '/Virtual VCU Pedal Payload']) == -1
    add_block('simulink/Signal Routing/Goto', ...
        [root '/Virtual VCU Pedal Payload'], 'GotoTag', pedalTag, ...
        'TagVisibility', 'global', 'Position', [520 420 730 445]);
    add_line(root, 'VCU Payload Split/1', ...
        'Virtual VCU Pedal Payload/1', 'autorouting', 'on');
end
if getSimulinkBlockHandle([model '/Virtual VCU Pedal Payload']) == -1
    add_block('simulink/Signal Routing/From', [model '/From Virtual VCU Pedal Payload'], ...
        'GotoTag', pedalTag, 'Position', [1280 85 1350 105]);
    add_block('simulink/Sinks/Out1', [model '/Virtual VCU Pedal Payload'], ...
        'Port', '5', 'Position', [1390 85 1420 105]);
    add_line(model, 'From Virtual VCU Pedal Payload/1', ...
        'Virtual VCU Pedal Payload/1', 'autorouting', 'on');
end
for k = 1:numel(names)
    blockName = ['Virtual VCU ' names{k}];
    block = [root '/' blockName];
    if getSimulinkBlockHandle(block) == -1
        add_block('simulink/Signal Routing/Goto', block, ...
            'GotoTag', tags{k}, 'TagVisibility', 'global', ...
            'Position', [520 470 + 30*k 730 490 + 30*k]);
    end
    deleteExistingLine(root, sprintf('VCU Payload Split/%d', 5+k), ...
        [blockName '/1']);
    add_line(root, sprintf('VCU Payload Split/%d', 5+k), ...
        [blockName '/1'], 'autorouting', 'on');

    outName = ['Virtual VCU ' names{k}];
    outPath = [model '/' outName];
    if getSimulinkBlockHandle(outPath) == -1
        fromName = ['From ' outName];
        add_block('simulink/Signal Routing/From', [model '/' fromName], ...
            'GotoTag', tags{k}, ...
            'Position', [1280 100 + 55*k 1350 120 + 55*k]);
        add_block('simulink/Sinks/Out1', outPath, 'Port', num2str(k), ...
            'Position', [1390 100 + 55*k 1420 120 + 55*k]);
        add_line(model, [fromName '/1'], [outName '/1'], ...
            'autorouting', 'on');
    end
end

save_system(model, modelPath);
end

function deleteExistingLine(path, src, dst)
try
    delete_line(path, src, dst);
catch
    % Idempotent patch: a missing line is expected on first application.
end
end
