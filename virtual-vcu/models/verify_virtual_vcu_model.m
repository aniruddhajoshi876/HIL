function result = verify_virtual_vcu_model(modelPath)
%VERIFY_VIRTUAL_VCU_MODEL Verify actual Module 2 / Port A block parameters.
if nargin < 1
    modelPath = default_virtual_vcu_model_path();
end
load_system(modelPath);
cleanup = onCleanup(@() close_system('inverter_hil', 0));
root = 'inverter_hil/Virtual VCU';
assert(getSimulinkBlockHandle(root) ~= -1, 'virtualvcu:MissingBoundary', ...
    'Virtual VCU boundary is missing.');
ai = [root '/Module 2 AI01-AI04'];
di = [root '/Module 2 DI01-DI08'];
assert(strcmp(get_param(ai, 'parModuleId'), '2'));
assert(strcmp(get_param(ai, 'parAdChannelLow'), '1'));
assert(strcmp(get_param(ai, 'parAdChannelHigh'), '4'));
assert(strcmp(get_param(di, 'parModuleId'), '2'));
assert(strcmp(get_param(di, 'parDiChannels'), '[1 2 3 4 5 6 7 8]'));
assert(strcmp(get_param([root '/VCU 5 ms Rate Transition'], ...
    'OutPortSampleTime'),'0.005'));
% RTW / Speedgoat: the four vendored allocator .c files are model-level
% CustomSource (full paths) and the vendor dir is on CustomInclude. Simulation
% (incl. the chart S-function slbuild builds first) uses the host MEX and
% carries no custom code -- see configure_controls_model.m.
customSrc = get_param('inverter_hil','CustomSource');
assert(contains(get_param('inverter_hil','CustomInclude'),'controls_model'), ...
    'Pinned ControlsMFE25 include directory is not on the model include path.');
assert(contains(customSrc,'ControlsMFE25.c') && ...
    contains(customSrc,'vvcu_controls_wrapper.c') && ...
    ~contains(customSrc,'rt_nonfinite.c'), ...
    'CustomSource must carry the 4 vendored allocator .c files and not rt_nonfinite.c.');
chartScript = fileread(fullfile(fileparts(mfilename('fullpath')), ...
    'virtualVcuDeployStep.m'));
assert(contains(chartScript, "coder.ceval('vvcu_controls_step'") && ...
    contains(chartScript, "coder.extrinsic('vvcu_controls_mex')"), ...
    'Chart must ceval the allocator for codegen and use the MEX for simulation.');
assert(getSimulinkBlockHandle([root '/Port A CAN FIFO Read']) == -1, ...
    'Virtual VCU must reuse the base boundary''s sole physical FIFO reader.');
assert(strcmp(get_param([root '/Port A RX Present From'],'GotoTag'), ...
    'EphorusRxDataPresent'));
writes = find_system(root, 'LookUnderMasks', 'all', 'FollowLinks', 'on', ...
    'ReferenceBlock', 'speedgoatlib_IO614/CAN Write ');
assert(numel(writes) == 5, 'Expected five Port A CAN writes.');
assert(all(cellfun(@(b) strcmp(get_param(b, 'channel'), '2'), writes)));
% Items 8/9: every Port A CAN write is transmission-gated (enableInput on)
% so control frames transmit only in RTD and 0x1F5 stops in ERROR_SHUTDOWN.
assert(all(cellfun(@(b) strcmp(get_param(b, 'enableInput'), 'on'), writes)), ...
    'Every Port A CAN write must expose its transmission-control input.');
assert(getSimulinkBlockHandle([root '/Port A TX Gate']) ~= -1, ...
    'Port A TX Gate (control/pedal transmission enable) is missing.');
% enableInput moves the Tx-control input to PORT 1 and the CAN Pack data
% input to PORT 2 (build_inverter_hil_model.m:769-776,1047-1052). Walk each
% Port A CAN Write's connections and confirm the sources, not just presence.
% k == 1 is 0x1F5, gated by the pedal-frame enable (TX Gate output 2 ->
% "Port A TX Gate Rate Transition 2"); k = 2..5 are the control frames,
% gated by the control-frame enable (output 1).
expectedGate = {'Port A TX Gate Rate Transition 2', ...
    'Port A TX Gate Rate Transition 1', 'Port A TX Gate Rate Transition 1', ...
    'Port A TX Gate Rate Transition 1', 'Port A TX Gate Rate Transition 1'};
for k = 1:5
    write = [root '/Port A CAN Write ' num2str(k)];
    assert(getSimulinkBlockHandle(write) ~= -1, ...
        'virtualvcu:MissingCanWrite', '%s is missing.', write);
    ph = get_param(write, 'PortHandles');
    assert(numel(ph.Inport) == 2, 'virtualvcu:CanWritePorts', ...
        '%s must have 2 inports (Tx control + CAN data).', write);
    src1 = canWriteInportSource(write, ph.Inport(1));
    src2 = canWriteInportSource(write, ph.Inport(2));
    assert(strcmp(src1, expectedGate{k}), 'virtualvcu:CanWriteTxControl', ...
        '%s port 1 must be driven by "%s" (got "%s").', ...
        write, expectedGate{k}, src1);
    assert(strcmp(src2, ['Port A CAN Pack ' num2str(k)]), ...
        'virtualvcu:CanWriteData', ...
        '%s port 2 must be driven by Port A CAN Pack %d (got "%s").', ...
        write, k, src2);
end
ids = cellfun(@(b) double(get_param(b, 'UserData')), writes);
expected = double([hex2dec('1F5') hex2dec('186') hex2dec('196') ...
    hex2dec('1A6') hex2dec('1B6')]);
assert(isequal(sort(ids(:)), sort(expected(:))));
packs = find_system(root, 'LookUnderMasks', 'all', 'FollowLinks', 'on', ...
    'RegExp', 'on', 'ReferenceBlock', '.*CAN Pack');
assert(numel(packs) == 5, 'Expected five Port A CAN packs.');
packIds = cellfun(@(b) str2double(get_param(b, 'MsgIdentifier')), packs);
assert(any(packIds == double(hex2dec('1F5'))), ...
    'Expected a standard CAN Pack for pedal ID 0x1F5 (501).');
result.moduleId = 2;
result.canChannel = 2;
result.canWriteCount = numel(writes);
fprintf(['R2024b virtual VCU verification passed: Module 2, ' ...
    'Port A/channel 2, %d CAN writes.\n'], numel(writes));
end

function name = canWriteInportSource(write, inportHandle)
%CANWRITEINPORTSOURCE Name of the block driving one CAN Write inport.
line = get_param(inportHandle, 'Line');
assert(line ~= -1, 'virtualvcu:CanWriteUnconnected', ...
    'A %s inport is unconnected.', write);
src = get_param(line, 'SrcBlockHandle');
assert(src ~= -1, 'virtualvcu:CanWriteNoSource', ...
    'A %s inport line has no source block.', write);
name = get_param(src, 'Name');
end
