function snapshot = blankTelemetry()
%BLANKTELEMETRY The honest no-data telemetry snapshot used when disconnected.
%
%   Every numeric field is NaN and every discrete field is empty or false with
%   a matching KNOWN flag, so the dashboard shows dashes rather than zeros
%   when there is no target. Nothing in this snapshot may ever be filled with
%   an invented, simulated, or animated value.

snapshot.valid = false;
snapshot.sourceTimeS = NaN;
snapshot.targetTimeS = NaN;

snapshot.vcu.state = '';
snapshot.vcu.timeInStateS = NaN;
snapshot.vcu.errorActive = false;
snapshot.vcu.errorKnown = false;

% Whether VIRTUALVCUDEPLOYSTEP.M's own APPS+brake plausibility interlock
% is actively suppressing torque -- a genuine chart-computed value (see
% TARGETSESSION.READLIVEIO port 8), not inferred here from a torque number
% happening to read zero. Empty (unknown) rather than false when unread,
% so a failed read never presents as "interlock not active".
snapshot.appsBrakeFault = [];

snapshot.guards.mainButton = [];
snapshot.guards.brakePercent = NaN;
snapshot.guards.dcLink12V = NaN;
snapshot.guards.dcLink34V = NaN;
snapshot.guards.plausibilityOk = [];

snapshot.pedals.throttleRequestedPercent = NaN;
snapshot.pedals.throttleAppliedPercent = NaN;
snapshot.pedals.brakeRequestedPercent = NaN;
snapshot.pedals.brakeAppliedPercent = NaN;
snapshot.pedals.appliedV = nan(1, 4);
snapshot.pedals.armed = false;

snapshot.steering.requestedAngleDeg = NaN;
snapshot.steering.appliedAngleDeg = NaN;
snapshot.steering.observedAngleDeg = NaN;
snapshot.steering.speedDegPerS = NaN;
snapshot.steering.valid = [];
snapshot.steering.ageS = NaN;
snapshot.steering.dropout = false;
snapshot.steering.stale = false;
snapshot.steering.malformed = false;
snapshot.steering.invalidStatus = false;
snapshot.steering.angleSentinel = false;
snapshot.steering.speedSentinel = false;
snapshot.steering.calibrationState = NaN;
% Whether the transmitted LWS frame was genuinely read and decoded this
% poll, as opposed to the fields above still being their no-data defaults.
snapshot.steering.known = false;

snapshot.imu.accelerationMps2 = nan(1, 3);
snapshot.imu.rateOfTurnRadPerS = nan(1, 3);
% VelocityXYZ (MTi 0x076). Present because the model genuinely transmits it
% and the MFE26-VC firmware decodes it -- leaving it out of the snapshot made
% a frame that is actually on the wire invisible to the operator.
snapshot.imu.velocityMps = nan(1, 3);
snapshot.imu.valid = [];
snapshot.imu.ageS = NaN;
snapshot.imu.dropout = false;
snapshot.imu.stale = false;
snapshot.imu.malformed = false;

snapshot.analogInV = nan(1, 4);

pinNames = {'VC_SD_OUT', 'MAIN_EN_OUT', 'PRECH_EN_OUT', ...
    'INV_CTRL_EN', 'INV_CTRL_DIS'};
testPoints = {'TP6', 'TP7', 'TP8', 'TP9', 'TP10'};
snapshot.pins = repmat(struct('name', '', 'testPoint', '', 'state', []), ...
    1, numel(pinNames));
for index = 1:numel(pinNames)
    snapshot.pins(index).name = pinNames{index};
    snapshot.pins(index).testPoint = testPoints{index};
    snapshot.pins(index).state = [];
end

snapshot.dcLink = repmat(struct( ...
    'label', '', 'voltageV', NaN, 'rawCount', NaN, ...
    'aboveMinimum', [], 'capturePending', true), 1, 2);
snapshot.dcLink(1).label = 'PAIR 1/2';
snapshot.dcLink(2).label = 'PAIR 3/4';
snapshot.switchingFrequencyKHz = NaN;
snapshot.switchingFrequencyRaw = NaN;

snapshot.inverter = repmat(blankInverter(), 1, 4);
for index = 1:4
    snapshot.inverter(index).index = index;
end

snapshot.can.rx = blankCanObservations( ...
    [uint32(hex2dec('1F5')) inverterhil.protocol().controlIds], ...
    {'VCU PEDALS', 'CTRL INV1', 'CTRL INV2', 'CTRL INV3', 'CTRL INV4'});
statusIds = inverterhil.protocol().statusCycleIds;
statusNames = {'3X3 INV1', '3X5 INV1', '3X3 INV2', '3X5 INV2', ...
    '3X3 INV3', '3X5 INV3', '3X3 INV4', '3X5 INV4', 'GENERAL'};
% The four synchronized sensor frames and Bosch config frame use the same CAN
% interface and must appear in the TX table too, in the SAME order the model
% writes them (BUILD_INVERTER_HIL_MODEL's SENSORIDS), because
% APPLYLIVETXFRAMES indexes payload rows positionally against this list.
sensorIds = inverterhil.sensorTxIds();
sensorNames = {'MTI ACCEL', 'MTI RATE', 'MTI VELOCITY', ...
    'LWS STEERING', 'LWS CONFIG'};
snapshot.can.tx = blankCanObservations( ...
    [uint32(statusIds(:)); uint32(sensorIds(:))]', ...
    [statusNames, sensorNames]);

% One flag per CAN Write block in the model: the nine Ephorus status frames
% plus the four sensor frames and one config frame. Sized from the shared
% ID lists rather than a
% literal so it cannot drift out of step with the model again.
snapshot.can.diagnostics.writeSucceeded = ...
    false(1, numel(statusIds) + numel(sensorIds));
snapshot.can.diagnostics.writeKnown = false;
snapshot.can.diagnostics.receiveOverrun = [];
snapshot.can.diagnostics.errorWarning = [];
snapshot.can.diagnostics.busOff = [];
snapshot.can.diagnostics.queueDepth = NaN;
snapshot.can.diagnostics.burstDurationS = NaN;
% Read live from the IO614 CAN Status block by TARGETSESSION.READLIVEIO.
snapshot.can.diagnostics.busLoadPercent = NaN;
snapshot.can.diagnostics.recoveryCount = NaN;
snapshot.can.diagnostics.transmitOverrun = [];

snapshot.io.healthy = false;
snapshot.io.healthyKnown = false;
end

function item = blankInverter()
item = struct( ...
    'index', 0, ...
    'state', '', ...
    'ready', [], ...
    'commandAgeS', NaN, ...
    'torqueCommandRaw', NaN, ...
    'torqueActualRaw', NaN, ...
    'speedRpm', NaN, ...
    'idSetpointA', NaN, ...
    'idActualA', NaN, ...
    'iqSetpointA', NaN, ...
    'iqActualA', NaN, ...
    'motorTemperatureC', NaN, ...
    'motorTemperatureRaw', NaN, ...
    'switchTemperatureC', NaN, ...
    'switchTemperatureRaw', NaN, ...
    'derating', [], ...
    'activeFault', '');
end

function items = blankCanObservations(ids, names)
count = numel(ids);
items = repmat(struct( ...
    'id', uint32(0), 'name', '', 'signal', '', 'value', '', ...
    'timestampsS', [], 'lastChangeS', NaN, 'count', NaN), 1, count);
for index = 1:count
    items(index).id = ids(index);
    items(index).name = names{index};
    items(index).signal = '';
    items(index).value = '';
    items(index).timestampsS = [];
    items(index).lastChangeS = NaN;
    items(index).count = NaN;
end
end
