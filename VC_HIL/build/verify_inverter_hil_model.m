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
    'enforceHardwarePreflight'));

required = {'Ephorus System Status', 'Hardware I O - PRE-FLIGHT DISABLED', ...
    'GUI Command Parameters'};
for index = 1:numel(required)
    assert(getSimulinkBlockHandle([model '/' required{index}]) ~= -1, ...
        'inverterhil:MissingSubsystem', 'Missing subsystem %s.', required{index});
end
% The decorative MIL-architecture tree (Test Inputs, Fault Injection,
% Pedal Sensor Emulation, VCU Digital Interface, the fake IO614 CAN
% Interface, Ephorus Channel 1-4, Measurements and Logging) was removed:
% every one of those subsystems terminated its inputs immediately and
% emitted only constant zeros. Assert it stays gone.
removed = {'Test Inputs', 'Fault Injection', 'Pedal Sensor Emulation', ...
    'VCU Digital Interface', 'IO614 CAN Interface', ...
    'Ephorus Channel 1', 'Ephorus Channel 2', ...
    'Ephorus Channel 3', 'Ephorus Channel 4', ...
    'Measurements and Logging'};
for index = 1:numel(removed)
    assert(getSimulinkBlockHandle([model '/' removed{index}]) == -1, ...
        'inverterhil:DeadSubsystemResurrected', ...
        'Dead subsystem %s must not be reintroduced.', removed{index});
end

hardware = [model '/Hardware I O - PRE-FLIGHT DISABLED'];
assert(strcmp(get_param(hardware, 'Commented'), 'off'), ...
    'Hardware boundary must be live once preflight is attested.');
enforceHardwarePreflight(model);
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
% The CAN bus is split in two: channel 1 / Port B is the CarMaker bus,
% channel 2 / Port A is the VC bus. There is one CAN Read and one CAN Status
% per bus.
assert(sum(strcmp(references, 'speedgoatlib_IO614/CAN Read ')) == 2, ...
    'Expected two IO614 CAN Read blocks (one per bus).');
assert(sum(strcmp(references, 'speedgoatlib_IO614/CAN Status ')) == 2, ...
    'Expected two IO614 CAN Status blocks (one per bus).');
vcRead = [hardware '/IO614 CAN FIFO Read Raw'];
carMakerRead = [hardware '/IO614 CarMaker FIFO Read'];
vcStatus = [hardware '/IO614 CAN Diagnostics'];
carMakerStatus = [hardware '/IO614 CarMaker CAN Diagnostics'];
assert(getSimulinkBlockHandle(vcRead) ~= -1 && ...
    strcmp(get_param(vcRead, 'channel'), '2'), ...
    'VC bus read must be on IO614 channel 2.');
assert(getSimulinkBlockHandle(carMakerRead) ~= -1 && ...
    strcmp(get_param(carMakerRead, 'channel'), '1'), ...
    'CarMaker bus read must be on IO614 channel 1.');
assert(getSimulinkBlockHandle(vcStatus) ~= -1 && ...
    strcmp(get_param(vcStatus, 'channel'), '2'), ...
    'VC bus diagnostics must be on IO614 channel 2.');
assert(getSimulinkBlockHandle(carMakerStatus) ~= -1 && ...
    strcmp(get_param(carMakerStatus, 'channel'), '1'), ...
    'CarMaker bus diagnostics must be on IO614 channel 1.');

% Nine Ephorus status frames, the two CarMaker telemetry frames, the four
% synchronized sensor frames, and the separately sequenced Bosch config frame
% (MTi-680G acceleration 0x034, rate-of-turn 0x032 and velocity 0x076,
% Bosch LWS 0x2B0, config 0x7C0).
assert(sum(strcmp(references, 'speedgoatlib_IO614/CAN Write ')) == 16, ...
    'Expected sixteen linked IO614 CAN Write blocks.');
% Each CAN Write consumes a CAN_MESSAGE, which only a CAN Pack produces.
assert(sum(strcmp(references, 'canmsglib/CAN Pack')) == 16, ...
    'Expected sixteen linked CAN Pack blocks feeding the CAN Write blocks.');

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
    '501', '502', '032', '034', '076', '2B0', '7C0'}))), ...
    ['Expected the nine Ephorus status IDs, CarMaker 0x501/0x502, ' ...
    'MTi/LWS sensor IDs, and Bosch LWS config 0x7C0.']);
assert(all(cellfun(@(block) strcmp(get_param(block, 'enableStatusPort'), 'on'), writes)));

% Bus split: only the two CarMaker telemetry frames (0x501/0x502) transmit
% on channel 1; every other write -- the nine status frames and the sensor
% frames -- is VC-bus traffic on channel 2.
carMakerTxIds = hex2dec({'501', '502'});
for index = 1:numel(writes)
    id = double(get_param(writes{index}, 'UserData'));
    expectedChannel = '2';
    if any(carMakerTxIds == id)
        expectedChannel = '1';
    end
    assert(strcmp(get_param(writes{index}, 'channel'), expectedChannel), ...
        'inverterhil:WrongCanChannel', ...
        'CAN Write 0x%03X must transmit on channel %s.', id, expectedChannel);
end

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
