function patch_virtual_vcu_inputs(modelPath)
%PATCH_VIRTUAL_VCU_INPUTS Connect AI, DI and physical CAN RX to the VCU.
if ~strcmp(version('-release'), '2024b')
    error('virtualvcu:WrongRelease', 'Build with MATLAB R2024b only.');
end
model = 'inverter_hil';
load_system(modelPath);
cleanup = onCleanup(@() close_system(model, 0));
path = [model '/Virtual VCU'];
if getSimulinkBlockHandle([path '/VCU Input Mux']) == -1
add_block('simulink/Signal Routing/Mux', [path '/VCU Input Mux'], ...
        'Inputs', '7', 'Position', [430 25 450 180]);
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
for k = 2:7
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
for k = 1:5
    deleteExistingLine(path, sprintf('Port A RX Selector/%d', k), ...
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
for k = 1:5
    add_line(path, sprintf('Port A RX Selector/%d', k), ...
        sprintf('VCU Input Double %d/1', k+2), 'autorouting', 'on');
    add_line(path, sprintf('VCU Input Double %d/1', k+2), ...
        sprintf('VCU Input Mux/%d', k+2), 'autorouting', 'on');
end
add_line(path, 'VCU Input Mux/1', 'Virtual VCU LV_ON/1', 'autorouting', 'on');
chart = sfroot().find('-isa', 'Stateflow.EMChart', '-and', ...
    'Path', [path '/Virtual VCU LV_ON']);
chart(1).Script = fileread(fullfile(fileparts(mfilename('fullpath')), ...
    'virtualVcuDeployStep.m'));
save_system(model, modelPath);
end

function deleteExistingLine(path, src, dst)
try
    delete_line(path, src, dst);
catch
    % Idempotent patch: no line is fine when rebuilding or repairing a model.
end
end
