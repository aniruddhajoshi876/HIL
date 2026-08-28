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
assert(contains(get_param('inverter_hil','CustomSource'),'ControlsMFE25.c'), ...
    'Pinned ControlsMFE25 source is not linked into the model.');
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
