function patch_virtual_vcu_state_outputs(modelPath)
%PATCH_VIRTUAL_VCU_STATE_OUTPUTS Add reviewable VCU state/control observers.
%
% R2024b-only model edit. The saved model is changed through Simulink and
% Stateflow APIs; the SLX archive is never edited directly. The existing
% five 8-byte CAN payloads remain elements 1:40. Elements 41:44 are state
% ID, MAIN_EN_OUT, PRECH_EN_OUT, and INV_CTRL_EN. This script deliberately
% does not rewire physical IO183 outputs.
%
% GETSIGNAL(target, blockPath, portIndex) reads port PORTINDEX of the
% SUBSYSTEM at blockPath -- i.e. it needs an Outport block placed INSIDE a
% subsystem, whose 'Port' parameter becomes that subsystem's numbered
% output port (see the existing, working 'Ephorus System Status'
% subsystem in build_inverter_hil_model.m for the same pattern). An
% earlier version of this script instead created standalone
% simulink/Sinks/Out1 blocks directly at the TOP model level, with no
% wrapping subsystem -- getsignal on those failed with "Port index 1
% exceeds number of ports of ... block", because a bare Outport doesn't
% "originate" a port the way a subsystem's boundary does. Fixed by
% wrapping all five observers in one 'Virtual VCU Observability'
% subsystem instead. If an earlier (broken) run of this script already
% created the old standalone blocks, they are removed first.

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
pedalTag = 'VirtualVcuPedalPayload';

% Publish each signal as a global Goto tag from inside "Virtual VCU" --
% this part was correct before and is unchanged.
if getSimulinkBlockHandle([root '/Virtual VCU Pedal Payload']) == -1
    add_block('simulink/Signal Routing/Goto', ...
        [root '/Virtual VCU Pedal Payload'], 'GotoTag', pedalTag, ...
        'TagVisibility', 'global', 'Position', [520 420 730 445]);
    add_line(root, 'VCU Payload Split/1', ...
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
end

% Remove the old, broken standalone top-level Out1 blocks and their From
% blocks, if a previous (incorrect) run of this script created them.
legacyNames = [{'Pedal Payload'}, names];
legacyTags = [{pedalTag}, tags];
for k = 1:numel(legacyNames)
    outPath = [model '/Virtual VCU ' legacyNames{k}];
    fromPath = [model '/From Virtual VCU ' legacyNames{k}];
    if getSimulinkBlockHandle(outPath) ~= -1
        delete_block(outPath);
    end
    if getSimulinkBlockHandle(fromPath) ~= -1
        delete_block(fromPath);
    end
end

% Wrap all five observers in one subsystem, matching the working
% "Ephorus System Status" pattern: From (global tag) -> Out1 (Port 'N')
% inside a subsystem, so the subsystem's own boundary exposes ports 1-5
% that GETSIGNAL(model/Virtual VCU Observability, N) can address.
obsPath = [model '/Virtual VCU Observability'];
if getSimulinkBlockHandle(obsPath) == -1
    add_block('simulink/Ports & Subsystems/Subsystem', obsPath, ...
        'Position', [1280 60 1420 300]);
end
% Default Subsystem blocks are created with one In1/Out1 pair (directly
% wired to each other); deleting either block removes its lines too, so
% every port here comes from a global Goto tag, not the subsystem's own
% default inport.
if getSimulinkBlockHandle([obsPath '/In1']) ~= -1
    delete_block([obsPath '/In1']);
end
if getSimulinkBlockHandle([obsPath '/Out1']) ~= -1
    delete_block([obsPath '/Out1']);
end

% A bare From->Outport passthrough is not enough: GETSIGNAL on these ports
% returned the SAME wrong (44-element, upstream chart-sized) data for
% every port. Root cause (see MathWorks "Troubleshoot Signals Not
% Accessible by Name", slrealtime doc set): Simulink's block-IO
% optimization eliminates a passthrough signal that nothing else in the
% model consumes -- these are observability-only dead ends -- and its
% compiled storage collapses onto its upstream signal, which is exactly
% why every port here read back the chart's raw 44-element output.
% Plain TestPoint marking on the From block's output was NOT sufficient
% (tried and confirmed still broken after a clean rebuild). The actual
% documented fix is an explicit Signal Copy, which in the Simulink API is
% NOT a block named "SignalCopy" (no such block type exists) but a
% "Signal Conversion" block (simulink/Signal Attributes/Signal
% Conversion) configured with ConversionOutput='Signal copy', which
% forces independent, non-optimizable storage. Contrast
% "Ephorus System Status" ports 1/2 (build_inverter_hil_model.m), which
% stay readable without this because their signals are genuinely
% consumed elsewhere in the model (the real CAN Write path), not just
% tapped for observability -- port 3 there is a bare passthrough like
% this one was, and correctly fails with the "Add a SignalCopy block"
% diagnostic rather than silently returning wrong data.
% Pedal TX Count (6th), Control Frame 1 (7th, carries torque at local
% bytes 5-6), and APPS Brake Fault (8th) are published directly as global
% Gotos inside "Virtual VCU" by ADD_VIRTUAL_VCU_TO_MODEL.M (not
% republished here like the first five, since Control Frame 1 already has
% its own Goto from VCU Payload Split port 2, and Pedal TX Count/APPS
% Brake Fault have no VCU Payload Split source at all -- APPS Brake Fault
% is VIRTUALVCUDEPLOYSTEP.M's own second output, a genuine typed logical,
% not a CAN payload byte) -- all reused via the same Signal Copy pattern
% as the rest, so the GUI can show a real fault indicator instead of the
% operator having to infer the interlock from a torque number going to
% zero.
% Torque Request Nm (9th): virtualVcuDeployStep.m's 4th output, published
% directly as a global Goto by ADD_VIRTUAL_VCU_TO_MODEL.M like APPS Brake
% Fault -- reused via the same Signal Copy pattern so it can be marked for
% XCP measurement without decoding a raw CAN payload byte pair. See
% virtual-vcu/docs/carmaker_speedgoat_interface.md section 7 items 4-6.
obsNames = [{'Pedal Payload'}, names, ...
    {'Pedal TX Count', 'Control Frame 1', 'APPS Brake Fault', ...
    'Torque Request Nm'}];
obsTags = [{pedalTag}, tags, {'VirtualVcuPedalTxCount', ...
    'VirtualVcuControlFrame1', 'VirtualVcuAppsBrakeFault', ...
    'VirtualVcuTorqueRequestNm'}];
measurementNames = { ...
    'hil_obs_virtual_vcu_pedal_payload'; ...
    'hil_obs_virtual_vcu_state_id'; ...
    'hil_obs_virtual_vcu_main_enable'; ...
    'hil_obs_virtual_vcu_precharge_enable'; ...
    'hil_obs_virtual_vcu_inverter_control_enable'; ...
    'hil_obs_virtual_vcu_pedal_tx_count'; ...
    'hil_obs_virtual_vcu_control_frame_1'; ...
    'hil_obs_virtual_vcu_apps_brake_fault'; ...
    'hil_obs_virtual_vcu_torque_request_nm'};
assert(numel(obsNames) == numel(measurementNames), ...
    'virtualvcu:MeasurementContract', ...
    'Every observability output must have one measurement Signal object.');
for k = 1:numel(obsNames)
    fromName = [obsPath '/From ' obsNames{k}];
    copyName = [obsPath '/Signal Copy ' obsNames{k}];
    outName = [obsPath '/' obsNames{k}];
    if getSimulinkBlockHandle(fromName) == -1
        add_block('simulink/Signal Routing/From', fromName, ...
            'GotoTag', obsTags{k}, ...
            'Position', [40 20 + 70*k 160 40 + 70*k]);
    end
    if getSimulinkBlockHandle(copyName) == -1
        add_block('simulink/Signal Attributes/Signal Conversion', ...
            copyName, 'ConversionOutput', 'Signal copy', ...
            'Position', [190 20 + 70*k 340 40 + 70*k]);
    else
        set_param(copyName, 'ConversionOutput', 'Signal copy');
    end
    if getSimulinkBlockHandle(outName) == -1
        add_block('simulink/Sinks/Out1', outName, 'Port', num2str(k), ...
            'Position', [380 20 + 70*k 410 40 + 70*k]);
    end
    deleteExistingLine(obsPath, ['From ' obsNames{k} '/1'], ...
        [obsNames{k} '/1']);
    deleteExistingLine(obsPath, ['From ' obsNames{k} '/1'], ...
        ['Signal Copy ' obsNames{k} '/1']);
    deleteExistingLine(obsPath, ['Signal Copy ' obsNames{k} '/1'], ...
        [obsNames{k} '/1']);
    add_line(obsPath, ['From ' obsNames{k} '/1'], ...
        ['Signal Copy ' obsNames{k} '/1'], 'autorouting', 'on');
    add_line(obsPath, ['Signal Copy ' obsNames{k} '/1'], ...
        [obsNames{k} '/1'], 'autorouting', 'on');
    copyPorts = get_param(copyName, 'PortHandles');
    set_param(copyPorts.Outport, 'TestPoint', 'on');
    % TestPoint alone does not cause SLRT's calibration-file generator to
    % emit an A2L measurement. Resolve this Signal Copy output to the
    % ExportedGlobal Simulink.Signal object created by the model builder.
    set_param(copyPorts.Outport, 'Name', measurementNames{k}, ...
        'MustResolveToSignalObject', 'on');
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
