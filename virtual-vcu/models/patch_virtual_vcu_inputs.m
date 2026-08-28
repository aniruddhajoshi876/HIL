function patch_virtual_vcu_inputs(modelPath)
%PATCH_VIRTUAL_VCU_INPUTS Connect AI, DI and physical CAN RX to the VCU.
if ~strcmp(version('-release'), '2024b')
    error('virtualvcu:WrongRelease', 'Build with MATLAB R2024b only.');
end
model = 'inverter_hil';
load_system(modelPath);
cleanup = onCleanup(@() close_system(model, 0));
configure_controls_model(model);
path = [model '/Virtual VCU'];
if getSimulinkBlockHandle([path '/VCU Input Mux']) == -1
add_block('simulink/Signal Routing/Mux', [path '/VCU Input Mux'], ...
        'Inputs', '9', 'Position', [430 25 450 220]);
else
    set_param([path '/VCU Input Mux'],'Inputs','9');
end
if getSimulinkBlockHandle([path '/Module 2 Digital Mux']) == -1
    add_block('simulink/Signal Routing/Mux', [path '/Module 2 Digital Mux'], ...
        'Inputs', '8', 'Position', [220 205 240 260]);
end
% This bench has one physical IO183 (Module 1); Module 2's own AI01-04 are
% unwired hardware and read a floating 0 V, which the falling throttle
% calibration decodes as fully pressed (100%) regardless of the pedal
% command. Per the operator, Module 1's own connector A self-loop
% (AO01/AO02 -> AI01/AI02, already jumpered) is the genuine, physically
% measured throttle/brake path -- so the virtual VCU reads that same
% voltage via the AnalogInputsV global tag the Hardware I/O boundary
% already publishes (see BUILD_INVERTER_HIL_MODEL's ADDHARDWAREBOUNDARY),
% instead of owning a separate, disconnected Module 2 AI reading.
if getSimulinkBlockHandle([path '/Module 1 Analog Inputs From']) == -1
    add_block('simulink/Signal Routing/From', ...
        [path '/Module 1 Analog Inputs From'], ...
        'GotoTag', 'AnalogInputsV', 'Position', [40 250 160 270]);
end
deleteExistingLine(path, 'Module 2 Analog Mux/1', 'Virtual VCU LV_ON/1');
deleteExistingLine(path, 'VCU Input Mux/1', 'Virtual VCU LV_ON/1');
deleteExistingLine(path, 'Module 2 Analog Mux/1', 'VCU Input Mux/1');
deleteExistingLine(path, 'Module 1 Analog Inputs From/1', 'VCU Input Mux/1');
for k = 2:8
    name = sprintf('VCU Input Double %d', k);
    if getSimulinkBlockHandle([path '/' name]) == -1
        add_block('simulink/Signal Attributes/Data Type Conversion', ...
            [path '/' name], 'OutDataTypeStr', 'double', ...
            'Position', [350 50 + 28*k 405 75 + 28*k]);
    end
end
for k = 1:8
    deleteExistingLine(path, sprintf('Module 2 DI01-DI08/%d', k), ...
        sprintf('Module 2 Digital Mux/%d', k));
end
deleteExistingLine(path, 'Module 2 DI01-DI08/1', 'VCU Input Double 2/1');
deleteExistingLine(path, 'Module 2 Digital Mux/1', 'VCU Input Double 2/1');
deleteExistingLine(path, 'Module 2 Digital Mux/1', 'VCU Input Mux/2');
rxNames = {'Present','ID','Extended','Remote','Length','Data'};
for k = 1:6
    deleteExistingLine(path, ['Port A RX ' rxNames{k} ' From/1'], ...
        sprintf('VCU Input Mux/%d', k+2));
end
add_line(path, 'Module 1 Analog Inputs From/1', 'VCU Input Mux/1', 'autorouting', 'on');
% Module 2's own DI01-DI08 are unwired hardware on this bench (confirmed
% floating, same category of bug as the analog Module 2 AI reading fixed
% above), so this branch is kept wired but unused, matching the analog
% case's precedent of leaving Module 2 blocks in place rather than
% removing them.
for k = 1:8
    add_line(path, sprintf('Module 2 DI01-DI08/%d', k), ...
        sprintf('Module 2 Digital Mux/%d', k), 'autorouting', 'on');
end

% Module 1's own DIO01-04 stimulus outputs are self-looped back into
% Module 1's own DIO09-13 ("IO183 DIO09-DIO13 VCU Monitor" -- repurposed
% here since there is no real VCU on this bench), exactly like the analog
% self-loop above. Confirmed empirically on real hardware (not assumed):
% precharge (DIO01/PRECH_BTN_IN) lands on DIO11 (VcuMonitorPins element 3,
% the "PRECH_EN_OUT" slot); main button (DIO02/MAIN_BTN_IN) lands on DIO10
% (element 2, "MAIN_EN_OUT" slot); shutdown feedback (DIO04/SD_FB_IN) lands
% on DIO09 (element 1, "VC_SD_OUT" slot) -- confirmed by toggling
% hil_cmd_digital_shutdown_feedback and observing DIO09 flip, with
% hil_cmd_digital_cooling_switch toggled separately and confirmed to NOT
% affect any of the 5 pins (the first physical wiring attempt actually
% landed cooling's output on DIO09; re-wired and re-confirmed before this
% mapping was written). This is NOT a simple sequential DIOnn->DIO(nn+8)
% offset, so the mapping below is by confirmed physical pairing, not by
% the VCU-Monitor block's own (irrelevant here) labels. Cooling switch is
% not yet physically jumpered on this bench, so DI03 (cooling) and DI04
% (unused fourth stimulus slot) are held at a constant 0 rather than
% guessed -- update once cooling is jumpered and confirmed the same way.
if getSimulinkBlockHandle([path '/Module 1 VCU Monitor Pins From']) == -1
    add_block('simulink/Signal Routing/From', ...
        [path '/Module 1 VCU Monitor Pins From'], ...
        'GotoTag', 'VcuMonitorPins', 'Position', [40 300 160 320]);
end
if getSimulinkBlockHandle([path '/Module 1 VCU Monitor Pins Demux']) == -1
    add_block('simulink/Signal Routing/Demux', ...
        [path '/Module 1 VCU Monitor Pins Demux'], ...
        'Outputs', '5', 'Position', [190 300 210 360]);
end
if getSimulinkBlockHandle([path '/Module 1 Digital Mux']) == -1
    add_block('simulink/Signal Routing/Mux', [path '/Module 1 Digital Mux'], ...
        'Inputs', '8', 'Position', [280 300 300 420]);
end
deleteExistingLine(path, 'Module 1 VCU Monitor Pins From/1', ...
    'Module 1 VCU Monitor Pins Demux/1');
add_line(path, 'Module 1 VCU Monitor Pins From/1', ...
    'Module 1 VCU Monitor Pins Demux/1', 'autorouting', 'on');
deleteExistingLine(path, 'Module 1 VCU Monitor Pins Demux/3', 'Module 1 Digital Mux/1');
add_line(path, 'Module 1 VCU Monitor Pins Demux/3', 'Module 1 Digital Mux/1', ...
    'autorouting', 'on');
deleteExistingLine(path, 'Module 1 VCU Monitor Pins Demux/2', 'Module 1 Digital Mux/2');
add_line(path, 'Module 1 VCU Monitor Pins Demux/2', 'Module 1 Digital Mux/2', ...
    'autorouting', 'on');
% DI05 = shutdownFeedback (VIRTUALVCUDEPLOYSTEP.M's u(9)) <- DIO09
% (VcuMonitorPins element 1), confirmed physical pairing per the note above.
deleteExistingLine(path, 'Module 1 VCU Monitor Pins Demux/1', 'Module 1 Digital Mux/5');
add_line(path, 'Module 1 VCU Monitor Pins Demux/1', 'Module 1 Digital Mux/5', ...
    'autorouting', 'on');
for k = [3 4 6 7 8]
    cname = sprintf('Module 1 Digital Unwired %d', k);
    if getSimulinkBlockHandle([path '/' cname]) == -1
        add_block('simulink/Sources/Constant', [path '/' cname], ...
            'Value', '0', 'OutDataTypeStr', 'double', 'SampleTime', '0.001', ...
            'Position', [190 400 + 20 * k, 260, 415 + 20 * k]);
    end
    deleteExistingLine(path, cname, sprintf('Module 1 Digital Mux/%d', k));
    add_line(path, [cname '/1'], sprintf('Module 1 Digital Mux/%d', k), ...
        'autorouting', 'on');
end
deleteExistingLine(path, 'Module 1 Digital Mux/1', 'VCU Input Double 2/1');
add_line(path, 'Module 1 Digital Mux/1', 'VCU Input Double 2/1', 'autorouting', 'on');
add_line(path, 'VCU Input Double 2/1', 'VCU Input Mux/2', 'autorouting', 'on');
for k = 1:6
    deleteExistingLine(path, ['Port A RX ' rxNames{k} ' From/1'], ...
        sprintf('VCU Input Double %d/1', k+2));
    deleteExistingLine(path, sprintf('VCU Input Double %d/1', k+2), ...
        sprintf('VCU Input Mux/%d', k+2));
    add_line(path, ['Port A RX ' rxNames{k} ' From/1'], ...
        sprintf('VCU Input Double %d/1', k+2), 'autorouting', 'on');
    add_line(path, sprintf('VCU Input Double %d/1', k+2), ...
        sprintf('VCU Input Mux/%d', k+2), 'autorouting', 'on');
end
% Item 2: 1 ms multi-corner wheel-speed retention ahead of the 5 ms rate
% transition. Firmware drains its whole RX FIFO each comms cycle
% (vcComms.cpp:327-374); the base boundary publishes one FIFO item per 1 ms
% base tick, so without retention a 5 ms chart tick sees only the last
% 0x3X5 frame in the window. This block latches all four Ephorus
% actual-speed frames at the base rate and feeds the chart a coherent
% 4-vector as VCU Input Mux input 9 -> chart u(26:29).
retain = [path '/Virtual VCU RX Retain'];
if getSimulinkBlockHandle(retain) == -1
    add_block('simulink/User-Defined Functions/MATLAB Function', retain, ...
        'Position', [270 250 400 340]);
end
setRxRetainScript(retain, fileread(fullfile(fileparts(mfilename('fullpath')), ...
    'virtualVcuRxRetain.m')));
for k = 1:6
    deleteExistingLine(path, ['Port A RX ' rxNames{k} ' From/1'], ...
        sprintf('Virtual VCU RX Retain/%d', k));
    add_line(path, ['Port A RX ' rxNames{k} ' From/1'], ...
        sprintf('Virtual VCU RX Retain/%d', k), 'autorouting', 'on');
end
deleteExistingLine(path, 'Virtual VCU RX Retain/1', 'VCU Input Mux/9');
add_line(path, 'Virtual VCU RX Retain/1', 'VCU Input Mux/9', 'autorouting', 'on');

deleteExistingLine(path, 'VCU Input Mux/1', 'Virtual VCU LV_ON/1');
rate = [path '/VCU 5 ms Rate Transition'];
if getSimulinkBlockHandle(rate) == -1
    add_block('simulink/Signal Attributes/Rate Transition', rate, ...
        'OutPortSampleTime','0.005','Position',[465 25 500 180]);
else
    set_param(rate,'OutPortSampleTime','0.005');
end
deleteExistingLine(path,'VCU Input Mux/1','VCU 5 ms Rate Transition/1');
deleteExistingLine(path,'VCU 5 ms Rate Transition/1','Virtual VCU LV_ON/1');
add_line(path,'VCU Input Mux/1','VCU 5 ms Rate Transition/1','autorouting','on');
add_line(path,'VCU 5 ms Rate Transition/1','Virtual VCU LV_ON/1','autorouting','on');
% Re-assert both MATLAB Function scripts AFTER every signal connection.
% R2024b silently reverts a MATLAB Function block to its default passthrough
% template when a downstream vector-width diagnostic is first evaluated
% against a script installed before the block's inputs/outputs were wired
% (see the same reassert pattern in add_virtual_vcu_to_model.m for the
% chart / pedal TX counter). virtualVcuRxRetain's script was installed
% above before its 6 inputs and its VCU Input Mux/9 output existed.
reassertInputScripts(path);
save_system(model, modelPath);
% Persist once more after a close/reopen, mirroring add_virtual_vcu_to_model.
close_system(model, 0);
load_system(modelPath);
reassertInputScripts(path);
save_system(model, modelPath);
end

function reassertInputScripts(path)
deployChart = sfroot().find('-isa', 'Stateflow.EMChart', '-and', ...
    'Path', [path '/Virtual VCU LV_ON']);
assert(~isempty(deployChart), 'virtualvcu:MissingChart', ...
    'Virtual VCU LV_ON chart is missing.');
deployChart(1).Script = fileread(fullfile(fileparts(mfilename('fullpath')), ...
    'virtualVcuDeployStep.m'));
setRxRetainScript([path '/Virtual VCU RX Retain'], ...
    fileread(fullfile(fileparts(mfilename('fullpath')), 'virtualVcuRxRetain.m')));
end

function deleteExistingLine(path, src, dst)
try
    delete_line(path, src, dst);
catch
    % Idempotent patch: no line is fine when rebuilding or repairing a model.
end
end

function setRxRetainScript(blockPath, script)
%SETRXRETAINSCRIPT Install the wheel-speed retention script on its MATLAB
%   Function block. Mirrors ADD_VIRTUAL_VCU_TO_MODEL's SETMATLABFUNCTIONSCRIPT
%   (a raw handle must be resolved to a path before Stateflow's 'Path' find
%   filter matches it).
if isnumeric(blockPath)
    blockPath = getfullname(blockPath);
end
chart = sfroot().find('-isa', 'Stateflow.EMChart', '-and', 'Path', blockPath);
assert(~isempty(chart), 'virtualvcu:ChartNotFound', ...
    'No Stateflow chart found at %s.', blockPath);
chart(1).Script = script;
if ~contains(chart(1).Script, ...
        'function omInv = virtualVcuRxRetain(present, id, extended, remote, len, data)')
    error('virtualvcu:RxRetainScript', ...
        'Virtual VCU RX Retain script was not installed.');
end
end
