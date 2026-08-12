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
for k = 1:8
    add_line(path, sprintf('Module 2 DI01-DI08/%d', k), ...
        sprintf('Module 2 Digital Mux/%d', k), 'autorouting', 'on');
end
add_line(path, 'Module 2 Digital Mux/1', 'VCU Input Double 2/1', 'autorouting', 'on');
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
