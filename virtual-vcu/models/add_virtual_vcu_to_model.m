function add_virtual_vcu_to_model(modelPath)
%ADD_VIRTUAL_VCU_TO_MODEL Add the minimal Module 2 / Port B bench boundary.
if ~strcmp(version('-release'), '2024b')
    error('virtualvcu:WrongRelease', 'Build with MATLAB R2024b only.');
end
root = fileparts(fileparts(mfilename('fullpath')));
addpath(root);
if nargin < 1
    modelPath = fullfile(fileparts(root), 'inverter_hil', 'inverter_hil.slx');
end
model = 'inverter_hil';
load_system(modelPath);
cleanup = onCleanup(@() close_system(model, 0));
if getSimulinkBlockHandle([model '/Virtual VCU']) ~= -1
    return;
end
path = [model '/Virtual VCU'];
add_block('simulink/Ports & Subsystems/Subsystem', path, ...
    'Position', [960 80 1190 230], ...
    'Description', 'Virtual VCU: IO183 Module 2 and IO614 Port B (CAN channel 1).');
open_system(path);
add_block('speedgoatlib_IO183/Setup', [path '/IO183 Module 2 Setup'], ...
    'Position', [25 25 190 90]);
set_param([path '/IO183 Module 2 Setup'], 'parModuleId', '2', ...
    'parPciSlot', '-1', 'parDaSimult', 'on', ...
    'parAdCoupling', 'Single Ended', 'parAdRange', '0..5V', ...
    'parAdChannelLow', '1', 'parAdChannelHigh', '4', ...
    'parDaChannels', '[1 2 3 4]', 'parDaRange', '0..5V', ...
    'parDaInit', '[0 0 0 0]', 'parDaReset', '[0 0 0 0]', ...
    'parDoChannels', '[1 2 3 4 5 6 7 8]', ...
    'parDoInit', '[0 0 0 0 0 0 0 0]', ...
    'parDoReset', '[0 0 0 0 0 0 0 0]', ...
    'parDiChannels', '[1 2 3 4 5 6 7 8]', ...
    'parIOPullReferenceFront', 'Pull-down');
ai = add_block('speedgoatlib_IO183/Analog Input', [path '/Module 2 AI01-AI04'], ...
    'Position', [25 120 190 175]);
set_param(ai, 'parModuleId', '2', 'parSampTime', '0.001', ...
    'parAdChannelLow', '1', 'parAdChannelHigh', '4');
di = add_block('speedgoatlib_IO183/Digital Input', [path '/Module 2 DI01-DI08'], ...
    'Position', [25 205 190 260]);
set_param(di, 'parModuleId', '2', 'parSampTime', '0.001', ...
    'parDiChannels', '[1 2 3 4 5 6 7 8]');
add_block('simulink/Signal Routing/Mux', [path '/Module 2 Analog Mux'], ...
    'Inputs', '4', 'Position', [220 120 240 175]);
for k = 1:4
    add_line(path, sprintf('Module 2 AI01-AI04/%d', k), ...
        sprintf('Module 2 Analog Mux/%d', k));
end
add_block('simulink/Signal Routing/Mux', [path '/Module 2 Digital Mux'], ...
    'Inputs', '8', 'Position', [220 205 240 260]);
for k = 1:8
    add_line(path, sprintf('Module 2 DI01-DI08/%d', k), ...
        sprintf('Module 2 Digital Mux/%d', k));
end
% IO614 has one FIFO reader per channel. The inverter boundary owns the
% physical channel-1 reader and publishes its CAN message bus globally;
% Virtual VCU consumes that same stream rather than creating a second reader.
read = add_block('simulink/Signal Routing/From', ...
    [path '/Port B Shared CAN FIFO Read'], ...
    'Position', [270 120 440 180]);
set_param(read, 'GotoTag', 'VirtualVcuSharedCanMessage');
selector = add_block('simulink/Signal Routing/Bus Selector', ...
    [path '/Port B RX Selector'], 'Position', [475 115 490 250]);
set_param(selector, 'OutputSignals', 'ID,Extended,Remote,Length,Data');
add_line(path, 'Port B Shared CAN FIFO Read/1', 'Port B RX Selector/1');
fcn = add_block('simulink/User-Defined Functions/MATLAB Function', ...
    [path '/Virtual VCU LV_ON'], 'Position', [520 25 750 260]);
setMatlabFunctionScript(fcn, vcuScript());
% No immediate PortHandles assertion here (an earlier version checked for
% exactly 1 input/3 outputs right after SETMATLABFUNCTIONSCRIPT): a freshly
% created MATLAB Function block reports its ORIGINAL DEFAULT port count
% (1 input/1 output) until Simulink actually compiles/updates the diagram
% against the new script, so that check failed even on a correctly
% installed 3-output script -- confirmed by a from-scratch build. The
% ADD_LINE calls below on ports 2/3 are themselves a sufficient check:
% Simulink errors clearly if those ports genuinely do not exist once the
% diagram is compiled.
add_line(path, 'Module 2 Analog Mux/1', 'Virtual VCU LV_ON/1');
add_block('simulink/Signal Routing/Demux', [path '/VCU Payload Split'], ...
    'Outputs', '[8 8 8 8 8 1 1 1 1]', 'Position', [780 25 800 300]);
add_line(path, 'Virtual VCU LV_ON/1', 'VCU Payload Split/1');
% Outputs 2/3 (DCLINKV, APPSBRAKEFAULT) are genuine typed values (double
% volts, logical), not CAN payload bytes, so they bypass VCU PAYLOAD SPLIT
% entirely and go straight to their own global tags -- DCLINKV replaces
% the static hil_cmd_dc_link12_v/34_v GUI tunables in BUILDSYSTEMSTATUS
% (BUILD_INVERTER_HIL_MODEL.M) with this state-driven ramp, by REDIRECTING
% the two existing "GuiCmdDcLink12V From"/"GuiCmdDcLink34V From" blocks'
% GotoTag below rather than having BUILDSYSTEMSTATUS reference this tag
% directly. BUILD_INVERTER_HIL_MODEL.M calls ADDHARDWAREBOUNDARY (which
% builds "Ephorus System Status") BEFORE calling THIS function, and
% immediately compiles the diagram to save the base model -- a "From"
% block referencing a Goto tag that does not exist ANYWHERE in the model
% yet (VIRTUALVCUDCLINKV, only created here) failed that compile with a
% cryptic, seemingly-unrelated Stateflow data-size error elsewhere in the
% model ('Inferred size ... does not match back propagated size' on
% EPHORUSSTATUSCYCLEFRAMES's own output -- confirmed by a from-scratch
% build reproducing it, and by the ORIGINAL (unmodified) file's own
% GuiCmdDcLink12V/34V tags building cleanly in the same slot). Retargeting
% the ALREADY-COMPILED "From" blocks' tag here, after this tag genuinely
% exists, avoids the forward-reference entirely.
% APPSBRAKEFAULT is republished through VIRTUAL VCU OBSERVABILITY (see
% PATCH_VIRTUAL_VCU_STATE_OUTPUTS.M) for the GUI's fault banner.
add_block('simulink/Signal Routing/Goto', [path '/Virtual VCU DC Link V'], ...
    'GotoTag', 'VirtualVcuDcLinkV', 'TagVisibility', 'global', ...
    'Position', [780 340 950 360]);
add_line(path, 'Virtual VCU LV_ON/2', 'Virtual VCU DC Link V/1', 'autorouting', 'on');
add_block('simulink/Signal Routing/Goto', [path '/Virtual VCU APPS Brake Fault'], ...
    'GotoTag', 'VirtualVcuAppsBrakeFault', 'TagVisibility', 'global', ...
    'Position', [780 370 950 390]);
add_line(path, 'Virtual VCU LV_ON/3', 'Virtual VCU APPS Brake Fault/1', 'autorouting', 'on');
% TORQUEREQUESTNM (port 4): same physical Nm value already packed into the
% control-frame payload bytes, published here as its own typed double so
% it can be marked for XCP measurement directly -- see
% virtual-vcu/docs/carmaker_speedgoat_interface.md section 7 items 4-5.
% Republished through VIRTUAL VCU OBSERVABILITY like APPSBRAKEFAULT (see
% PATCH_VIRTUAL_VCU_STATE_OUTPUTS.M).
add_block('simulink/Signal Routing/Goto', [path '/Virtual VCU Torque Request Nm'], ...
    'GotoTag', 'VirtualVcuTorqueRequestNm', 'TagVisibility', 'global', ...
    'Position', [780 400 950 420]);
add_line(path, 'Virtual VCU LV_ON/4', 'Virtual VCU Torque Request Nm/1', 'autorouting', 'on');
statusPath = [model '/Ephorus System Status'];
for dcName = {'GuiCmdDcLink12V From', 'GuiCmdDcLink34V From'}
    dcFromPath = [statusPath '/' dcName{1}];
    assert(getSimulinkBlockHandle(dcFromPath) ~= -1, ...
        'virtualvcu:MissingDcLinkFrom', ...
        '%s is missing; BUILDSYSTEMSTATUS''s wiring may have changed.', dcFromPath);
    set_param(dcFromPath, 'GotoTag', 'VirtualVcuDcLinkV');
end
addVirtualVcuOutputTags(path);
% The CAN receive path remains physical and observable. No-data is preserved
% as false/unknown; it is not converted into a fabricated status frame.
for k = 1:5
    add_block('simulink/Signal Routing/Goto', ...
        [path sprintf('/Port B RX Field %d', k)], ...
        'GotoTag', sprintf('VirtualVcuRxField%d', k), 'TagVisibility', 'global', ...
        'Position', [520 285 + 25*k 680 305 + 25*k]);
    add_line(path, sprintf('Port B RX Selector/%d', k), ...
        sprintf('Port B RX Field %d/1', k));
end
add_block('simulink/Sinks/Terminator', [path '/Module 2 Digital Monitor'], ...
    'Position', [220 215 240 235]);
add_line(path, 'Module 2 Digital Mux/1', 'Module 2 Digital Monitor/1');
add_block('simulink/Signal Routing/Goto', [path '/Virtual VCU AI Telemetry'], ...
    'GotoTag', 'VirtualVcuMeasuredAI', 'TagVisibility', 'global', ...
    'Position', [520 270 680 290]);
add_line(path, 'Module 2 Analog Mux/1', 'Virtual VCU AI Telemetry/1');
ids = [uint32(hex2dec('1F5')) uint32(hex2dec('186')) ...
    uint32(hex2dec('196')) uint32(hex2dec('1A6')) uint32(hex2dec('1B6'))];
for k = 1:5
    transition = add_block('simulink/Signal Attributes/Rate Transition', ...
        [path sprintf('/Port B Payload Rate Transition %d', k)], ...
        'Position', [820 25 + 55*k 840 55 + 55*k]);
    pack = add_block('canlib/CAN Pack', [path sprintf('/Port B CAN Pack %d', k)], ...
        'Position', [920 25 + 55*k 1030 55 + 55*k]);
    set_param(pack, 'DataFormat', 'raw data', 'MsgIDType', ...
        'Standard (11-bit identifier)', 'MsgIdentifier', num2str(ids(k)), ...
        'CANIDInput', 'off', 'MsgLength', '8', 'Remote', 'off', ...
        'BusOutput', 'off');
    write = add_block('speedgoatlib_IO614/CAN Write ', ...
        [path sprintf('/Port B CAN Write %d', k)], ...
        'Position', [1060 25 + 55*k 1180 55 + 55*k]);
    set_param(write, 'moduleType', 'IO614', 'id', '1', 'channel', '1', ...
        'canType', 'CAN (HS)', 'useBusIn', 'off', 'numOfMsg', '1', ...
        'enableStatusPort', 'on', 'ts', '0.005', 'UserData', ids(k), ...
        'UserDataPersistent', 'on');
    add_line(path, sprintf('VCU Payload Split/%d', k), ...
        sprintf('Port B Payload Rate Transition %d/1', k));
    add_line(path, sprintf('Port B Payload Rate Transition %d/1', k), ...
        sprintf('Port B CAN Pack %d/1', k));
    add_line(path, sprintf('Port B CAN Pack %d/1', k), sprintf('Port B CAN Write %d/1', k));
end
% Genuine, target-measured transmit count for the pedal frame (0x1F5),
% mirroring EPHORUSSYSTEMSTATUSSTEP's TXCOUNT pattern
% (BUILD_INVERTER_HIL_MODEL.M): the CAN Write driver itself exposes no
% cumulative counter, so this counts how many times a pedal payload was
% actually emitted at the write path's own 5 ms rate. Tapped from the same
% rate-transitioned signal 'Port B CAN Pack 1' consumes (k==1 is 0x1F5, the
% first id in IDS), not the chart's 1 kHz base rate, so the count matches
% the frame's real transmit cadence.
counter = add_block('simulink/User-Defined Functions/MATLAB Function', ...
    [path '/Port B Pedal TX Counter'], 'Position', [920 900 1030 940]);
setCounterScript(counter, pedalTxCounterScript());
add_line(path, 'Port B Payload Rate Transition 1/1', ...
    'Port B Pedal TX Counter/1', 'autorouting', 'on');
add_block('simulink/Signal Routing/Goto', [path '/Virtual VCU Pedal TX Count'], ...
    'GotoTag', 'VirtualVcuPedalTxCount', 'TagVisibility', 'global', ...
    'Position', [1060 900 1230 920]);
add_line(path, 'Port B Pedal TX Counter/1', ...
    'Virtual VCU Pedal TX Count/1', 'autorouting', 'on');
set_param(path, 'Commented', 'off');
% Re-assert the chart source after all signal connections; R2024b may
% refresh a MATLAB Function block's default template when a downstream
% vector-width diagnostic is first evaluated. The same bug hit the pedal
% TX counter: its script was set right after creation but before its
% 8-wide input line was connected, so the vector-width diagnostic quietly
% reverted it to the default `function y=fcn(u)` passthrough template --
% compiled evidence: the counter's OUTPORT read back as uint8 width 8
% (identical to its input) instead of a scalar uint32, and getsignal on
% the observability port it feeds returned the pedal payload's own shape.
setMatlabFunctionScript(fcn, vcuScript());
setCounterScript(counter, pedalTxCounterScript());
save_system(model, modelPath);
% Persist the chart source once more after a close/reopen. This mirrors the
% R2024b App/Stateflow serialization behavior and prevents a stale default
% `function y=fcn(u)` template from shadowing the generated script.
%
% [PATH] (the "Virtual VCU" SUBSYSTEM's own path, not the CHART inside
% it) was passed here previously -- STATEFLOW's 'Path' find filter needs
% the chart's own path, [path '/Virtual VCU LV_ON'], so this call also
% silently found zero charts and left the script untouched, exactly like
% the handle issue SETMATLABFUNCTIONSCRIPT's own header now documents.
close_system(model, 0);
load_system(modelPath);
setMatlabFunctionScript([path '/Virtual VCU LV_ON'], vcuScript());
setCounterScript([path '/Port B Pedal TX Counter'], pedalTxCounterScript());
save_system(model, modelPath);
end

function addVirtualVcuOutputTags(path)
%ADDVIRTUALVCUOUTPUTTAGS Publish the state/control scalar outputs.
if getSimulinkBlockHandle([path '/Virtual VCU Pedal Payload']) == -1
    add_block('simulink/Signal Routing/Goto', ...
        [path '/Virtual VCU Pedal Payload'], ...
        'GotoTag', 'VirtualVcuPedalPayload', 'TagVisibility', 'global', ...
        'Position', [520 420 730 445]);
    add_line(path, 'VCU Payload Split/1', ...
        'Virtual VCU Pedal Payload/1', 'autorouting', 'on');
end
% VCU Payload Split port 2 is control frame 1 (bytes 9-16 of the 44-byte
% payload array), which carries torque at local bytes 5-6
% (VIRTUALVCUDEPLOYSTEP.M's payloads(13)/(14)) -- not observable from the
% pedal payload alone (port 1, bytes 1-8), which only carries throttle %
% and brake. Published the same way as the pedal payload so torque gating
% (RTD + valid pedals) can actually be verified instead of assumed.
if getSimulinkBlockHandle([path '/Virtual VCU Control Frame 1']) == -1
    add_block('simulink/Signal Routing/Goto', ...
        [path '/Virtual VCU Control Frame 1'], ...
        'GotoTag', 'VirtualVcuControlFrame1', 'TagVisibility', 'global', ...
        'Position', [520 450 730 475]);
    add_line(path, 'VCU Payload Split/2', ...
        'Virtual VCU Control Frame 1/1', 'autorouting', 'on');
end
names = {'State ID', 'Main Enable', 'Precharge Enable', ...
    'Inverter Control Enable'};
tags = {'VirtualVcuStateId', 'VirtualVcuMainEnable', ...
    'VirtualVcuPrechargeEnable', 'VirtualVcuInverterControlEnable'};
for k = 1:numel(names)
    blockName = ['Virtual VCU ' names{k}];
    block = [path '/' blockName];
    if getSimulinkBlockHandle(block) == -1
        add_block('simulink/Signal Routing/Goto', block, ...
            'GotoTag', tags{k}, 'TagVisibility', 'global', ...
            'Position', [520 470 + 30*k 730 490 + 30*k]);
        add_line(path, sprintf('VCU Payload Split/%d', 5+k), ...
            [blockName '/1'], 'autorouting', 'on');
    end
end
end

function script = vcuScript()
script = fileread(fullfile(fileparts(mfilename('fullpath')), ...
    'virtualVcuDeployStep.m'));
end

function setCounterScript(blockPath, script)
%SETCOUNTERSCRIPT Install a MATLAB Function block script without
%   SETMATLABFUNCTIONSCRIPT's hardcoded assertion, which checks for the
%   main chart's own function signature and does not apply here.
%   BLOCKPATH may be a handle or a path string -- see
%   SETMATLABFUNCTIONSCRIPT's header for why a raw handle needs resolving
%   to a path first.
if isnumeric(blockPath)
    blockPath = getfullname(blockPath);
end
rt = sfroot(); chart = rt.find('-isa', 'Stateflow.EMChart', '-and', 'Path', blockPath);
assert(~isempty(chart), 'virtualvcu:ChartNotFound', ...
    'No Stateflow chart found at %s.', blockPath);
chart(1).Script = script;
if ~contains(chart(1).Script, 'function count = pedalTxCountStep(payload)')
    error('virtualvcu:CounterScript', 'Pedal TX counter script was not installed.');
end
end

function script = pedalTxCounterScript()
script = sprintf(['function count = pedalTxCountStep(payload) %%#ok<INUSD>\n' ...
    '%%#codegen\n' ...
    'persistent n\n' ...
    'if isempty(n)\n' ...
    '    n = uint32(0);\n' ...
    'end\n' ...
    'n = n + 1;\n' ...
    'count = n;\n' ...
    'end\n']);
end

function setMatlabFunctionScript(blockPath, script)
%SETMATLABFUNCTIONSCRIPT Install SCRIPT on the MATLAB Function chart at
%   BLOCKPATH. BLOCKPATH may be a block handle (as ADD_BLOCK returns) or a
%   Simulink path string; STATEFLOW's own 'Path' find filter only matches
%   a string, so a raw handle here silently found zero charts and left
%   CHART(1).SCRIPT a no-op on an empty array -- confirmed by a
%   from-scratch build reproducing it (the chart quietly stayed on its
%   default 1-output template while every caller believed the 3-output
%   script had been installed).
if isnumeric(blockPath)
    blockPath = getfullname(blockPath);
end
rt = sfroot(); chart = rt.find('-isa', 'Stateflow.EMChart', '-and', 'Path', blockPath);
assert(~isempty(chart), 'virtualvcu:ChartNotFound', ...
    'No Stateflow chart found at %s.', blockPath);
chart(1).Script = script;
if ~contains(chart(1).Script, ...
        'function [payloads, dcLinkV, appsBrakeFault, torqueRequestNm] = virtualVcuDeployStep(u)')
    error('virtualvcu:ChartScript', 'Virtual VCU chart script was not installed.');
end
end
