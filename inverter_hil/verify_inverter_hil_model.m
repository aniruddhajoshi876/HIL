function result = verify_inverter_hil_model()
%VERIFY_INVERTER_HIL_MODEL Verify R2024b provenance, topology, and I/O safety.

root = inverter_hil_setup();
model = 'inverter_hil';
modelPath = fullfile(root, [model '.slx']);
dictionaryPath = fullfile(root, [model '.sldd']);
assert(isfile(modelPath), 'inverterhil:MissingModel', 'Missing %s.', modelPath);
assert(isfile(dictionaryPath), 'inverterhil:MissingDictionary', ...
    'Missing %s.', dictionaryPath);

load_system(modelPath);
cleanup = onCleanup(@() close_system(model, 0));
assert(strcmp(get_param(model, 'SolverType'), 'Fixed-step'));
assert(strcmp(get_param(model, 'Solver'), 'FixedStepDiscrete'));
assert(strcmp(get_param(model, 'FixedStep'), '0.001'));
assert(strcmp(get_param(model, 'SystemTargetFile'), 'speedgoat.tlc'));
assert(strcmp(get_param(model, 'DataDictionary'), 'inverter_hil.sldd'));
assert(contains(get_param(model, 'InitFcn'), ...
    'inverterhil.enforceHardwarePreflight'));

required = {'Test Inputs', 'Pedal Sensor Emulation', ...
    'VCU Digital Interface', 'IO614 CAN Interface', ...
    'Ephorus Channel 1', 'Ephorus Channel 2', ...
    'Ephorus Channel 3', 'Ephorus Channel 4', ...
    'Ephorus System Status', 'Fault Injection', ...
    'Measurements and Logging', 'Hardware I O - PRE-FLIGHT DISABLED', ...
    'GUI Command Parameters'};
for index = 1:numel(required)
    assert(getSimulinkBlockHandle([model '/' required{index}]) ~= -1, ...
        'inverterhil:MissingSubsystem', 'Missing subsystem %s.', required{index});
end

hardware = [model '/Hardware I O - PRE-FLIGHT DISABLED'];
assert(strcmp(get_param(hardware, 'Commented'), 'off'), ...
    'Hardware boundary must be live once preflight is attested.');
inverterhil.enforceHardwarePreflight(model);
blocks = find_system(hardware, 'LookUnderMasks', 'all', ...
    'FollowLinks', 'on', 'Type', 'Block');
references = cell(size(blocks));
for index = 1:numel(blocks)
    references{index} = get_param(blocks{index}, 'ReferenceBlock');
end
references = references(~cellfun(@isempty, references));
expected = {'speedgoatlib_IO183/Setup', ...
    'speedgoatlib_IO183/Analog Input', ...
    'speedgoatlib_IO183/Analog Output', ...
    'speedgoatlib_IO183/Digital Input', ...
    'speedgoatlib_IO183/Digital Output', ...
    'speedgoatlib_IO614/CAN and LIN Setup ', ...
    'speedgoatlib_IO614/CAN Read ', ...
    'speedgoatlib_IO614/CAN Status '};
for index = 1:numel(expected)
    assert(any(strcmp(references, expected{index})), ...
        'inverterhil:MissingLibraryLink', 'Missing link [%s].', expected{index});
end
% Nine Ephorus status frames plus the four synchronized sensor frames and
% the separately sequenced Bosch configuration frame
% (MTi-680G acceleration 0x034, rate-of-turn 0x032 and velocity 0x076,
% Bosch LWS 0x2B0, config 0x7C0).
assert(sum(strcmp(references, 'speedgoatlib_IO614/CAN Write ')) == 14, ...
    'Expected fourteen linked IO614 CAN Write blocks.');
% Each CAN Write consumes a CAN_MESSAGE, which only a CAN Pack produces.
assert(sum(strcmp(references, 'canmsglib/CAN Pack')) == 14, ...
    'Expected fourteen linked CAN Pack blocks feeding the CAN Write blocks.');

linked = blocks(~cellfun(@isempty, cellfun( ...
    @(block) get_param(block, 'ReferenceBlock'), blocks, ...
    'UniformOutput', false)));
for index = 1:numel(linked)
    assert(strcmp(get_param(linked{index}, 'LinkStatus'), 'resolved'), ...
        'inverterhil:UnresolvedLibraryLink', ...
        'Unresolved library link: %s', linked{index});
end

setup = [hardware '/IO183 Setup'];
ao = [hardware '/IO183 AO01-AO04 Safe Zero'];
dio = [hardware '/IO183 DIO01-DIO08 Safe Zero'];
assert(strcmp(get_param(setup, 'parDaInit'), '[0 0 0 0]'));
assert(strcmp(get_param(setup, 'parDaReset'), '[0 0 0 0]'));
assert(strcmp(get_param(setup, 'parDoInit'), '[0 0 0 0 0 0 0 0]'));
assert(strcmp(get_param(setup, 'parDoReset'), '[0 0 0 0 0 0 0 0]'));
assert(strcmp(get_param(setup, 'parIOPullReferenceFront'), 'Pull-down'));
assert(strcmp(get_param(ao, 'parDaInit'), '[0 0 0 0]'));
assert(strcmp(get_param(ao, 'parDaReset'), '[0 0 0 0]'));
assert(strcmp(get_param(dio, 'parDoInit'), '[0 0 0 0 0 0 0 0]'));
assert(strcmp(get_param(dio, 'parDoReset'), '[0 0 0 0 0 0 0 0]'));

writes = find_system(hardware, 'LookUnderMasks', 'all', ...
    'FollowLinks', 'on', 'ReferenceBlock', 'speedgoatlib_IO614/CAN Write ');
ids = cellfun(@(block) double(get_param(block, 'UserData')), writes);
assert(isequal(sort(ids), sort(hex2dec( ...
    {'383', '385', '393', '395', '3A3', '3A5', '3B3', '3B5', '400', ...
    '032', '034', '076', '2B0', '7C0'}))), ...
    ['Expected the nine Ephorus status IDs plus MTi/LWS sensor IDs and ' ...
    'Bosch LWS config 0x7C0.']);
assert(all(cellfun(@(block) strcmp(get_param(block, 'enableStatusPort'), 'on'), writes)));

set_param(model, 'SimulationCommand', 'update');

dictionary = Simulink.data.dictionary.open(dictionaryPath);
dictionaryCleanup = onCleanup(@() close(dictionary));
section = getSection(dictionary, 'Design Data');
hardwareGate = getEntry(section, 'hil_hardware_preflight_complete');
assert(getValue(hardwareGate), ...
    'Live hardware boundary requires an attested preflight gate.');
torqueGate = getEntry(section, 'hil_torque_results_provisional');
assert(getValue(torqueGate));

result.release = version('-release');
result.model = modelPath;
result.dictionary = dictionaryPath;
result.libraryLinkCount = numel(linked);
result.canWriteCount = numel(writes);
result.hardwareBoundaryCommented = false;
fprintf('R2024b model verification passed: %d links, %d CAN writes.\n', ...
    result.libraryLinkCount, result.canWriteCount);
end
