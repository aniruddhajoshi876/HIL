function [next, output] = stepChannelState( ...
        state, input, channelConfig, config, unitConfigurationValid)
%STEPCHANNELSTATE Advance one Ephorus state machine by one deterministic tick.
% Input command age is supplied by the retained decoder. The optional fifth
% argument is the unit-wide configuration gate used by stepSystemState.

if nargin < 4
    config = inverterhil.defaultStateConfig();
end
if nargin < 3
    channelConfig = config.channels(1);
end
if nargin < 5
    unitConfigurationValid = true;
end
inverterhil.validateStateConfig(config);
validateChannelState(state);
validateChannelInput(input);
validateBinary(unitConfigurationValid, 'unitConfigurationValid', ...
    'inverterhil:InvalidStateConfig');
[localConfigValid, configReason] = ...
    inverterhil.evaluateMandatoryConfiguration(channelConfig);
effectiveConfigValid = localConfigValid && logical(unitConfigurationValid);
if localConfigValid && ~logical(unitConfigurationValid)
    configReason = 'unit_configuration_invalid';
end

p = inverterhil.protocol();
stepUs = secondsToUs(config.sampleTimeS);
% Sub-millisecond limits are observed on the first completed model tick.
next = state;
next.stepCount = addUs(state.stepCount, uint64(1));
next.unsupportedCurrentMode = logical(input.currentMode);
next.commandTorqueTimeout = double(input.commandAgeMs) > 50;
next.commandErrorTimeout = double(input.commandAgeMs) > 500;
next.positionTimeoutQuantized = input.positionAgeS > ...
    config.positionTimeoutS && config.sampleTimeS > config.positionTimeoutS;
next.unsupportedAscEntry = logical(input.ascAllowed) && ...
    abs(input.speedRpm) > channelConfig.ascThresholdRpm && ...
    ~logical(input.controlEnable) && logical(input.dischargeActive) && ...
    logical(channelConfig.connected);
next.configurationReason = configReason;

if logical(input.powerCycle)
    next = resetAfterPowerCycle(next, channelConfig, config, ...
        effectiveConfigValid, configReason);
    output = makeOutput(next);
    return;
end

if state.configErrorLatched || ~effectiveConfigValid
    next.mode = p.state.configError;
    next.modeName = 'Config Error';
    next.configErrorLatched = true;
    next.errorLatched = false;
    next.ready = false;
    next.zeroTorque = true;
    next.activeFault = 'none';
    if state.configErrorLatched
        next.transitionReason = 'hold_config_error_power_cycle_required';
    else
        next.transitionReason = ['config_error_' configReason];
    end
    output = makeOutput(next);
    return;
end

wasDrive = state.mode == p.state.drive;
enableLowContext = wasDrive || (state.errorLatched && ...
    strcmp(state.activeFault, 'control_enable_low'));
if enableLowContext && ~logical(input.controlEnable)
    next.controlEnableLowUs = addUs(state.controlEnableLowUs, stepUs);
else
    next.controlEnableLowUs = uint64(0);
end
trackingContext = wasDrive || (state.errorLatched && ...
    strcmp(state.activeFault, 'current_tracking'));
trackingExceeded = trackingContext && (abs(input.idTrackingErrorA) > 10 || ...
    abs(input.iqTrackingErrorA) > 10);
if trackingExceeded
    next.trackingErrorUs = addUs(state.trackingErrorUs, stepUs);
else
    next.trackingErrorUs = uint64(0);
end

[faultActive, faultCause] = evaluateOperationalFault( ...
    next, input, channelConfig, config, wasDrive);
if faultActive
    newOccurrence = ~state.errorLatched;
    next.errorLatched = true;
    next.mode = p.state.error;
    next.modeName = 'Error';
    next.ready = false;
    next.zeroTorque = true;
    next.activeFault = faultCause;
    next.faultClearUs = uint64(0);
    next.outsideErrorUs = uint64(0);
    if newOccurrence
        next.latchedFaultCause = faultCause;
        if state.errorOccurrences == 0
            next.resetWaitUs = secondsToUs(config.resetFloorS);
        else
            next.resetWaitUs = min( ...
                saturatingDouble(state.resetWaitUs), ...
                secondsToUs(config.resetBackoffMaxS));
        end
        next.errorOccurrences = state.errorOccurrences + uint32(1);
        next.transitionReason = ['error_' faultCause];
    else
        next.transitionReason = ['hold_error_' faultCause];
    end
    if logical(input.resetError)
        next.transitionReason = 'reset_refused_active_fault';
    end
    output = makeOutput(next);
    return;
end

if state.errorLatched
    next.mode = p.state.error;
    next.modeName = 'Error';
    next.ready = false;
    next.zeroTorque = true;
    next.activeFault = 'none';
    next.faultClearUs = addUs(state.faultClearUs, stepUs);
    next.outsideErrorUs = uint64(0);
    if logical(input.resetError)
        if next.faultClearUs >= next.resetWaitUs
            next.errorLatched = false;
            next.latchedFaultCause = 'none';
            next.mode = p.state.idle;
            next.modeName = 'Idle';
            next.transitionReason = 'error_reset';
            next.faultClearUs = uint64(0);
            next.ready = logical(channelConfig.connected);
        else
            next.transitionReason = 'reset_refused_backoff';
        end
    else
        next.transitionReason = 'hold_error_wait_reset';
    end
    output = makeOutput(next);
    return;
end

next.errorLatched = false;
next.configErrorLatched = false;
next.activeFault = 'none';

if logical(input.controlDisable)
    [next.mode, next.modeName] = modeValue('Idle', p);
    next.transitionReason = 'control_disable_provisional_idle';
elseif logical(input.currentMode)
    [next.mode, next.modeName] = modeValue('Idle', p);
    next.transitionReason = 'unsupported_current_mode';
elseif ~logical(channelConfig.connected)
    [next.mode, next.modeName] = modeValue('Idle', p);
    next.transitionReason = 'disconnected';
elseif wasDrive && ~logical(input.commandEnable)
    [next.mode, next.modeName] = modeValue('Idle', p);
    next.transitionReason = 'can_enable_cleared';
elseif wasDrive && ~logical(input.controlEnable)
    [next.mode, next.modeName] = modeValue('Drive', p);
    next.transitionReason = 'hold_drive_control_enable_low';
elseif wasDrive
    [next.mode, next.modeName] = modeValue('Drive', p);
    next.transitionReason = 'hold_drive';
elseif canEnterDrive(input, channelConfig, config, next)
    [next.mode, next.modeName] = modeValue('Drive', p);
    next.transitionReason = 'idle_to_drive';
else
    [next.mode, next.modeName] = modeValue('Idle', p);
    next.transitionReason = idleReason(input, channelConfig, config, next);
end

pinTorqueBlocked = logical(input.controlDisable) || ...
    (~logical(input.controlEnable) && ...
    next.controlEnableLowUs > secondsToUs(config.controlPinTorqueZeroS));
next.zeroTorque = next.mode ~= p.state.drive || ...
    next.commandTorqueTimeout || pinTorqueBlocked || ...
    next.unsupportedCurrentMode || next.unsupportedAscEntry;
if next.mode == p.state.drive && next.commandTorqueTimeout
    next.transitionReason = 'hold_drive_command_timeout_zero_torque';
elseif next.mode == p.state.drive && next.unsupportedAscEntry
    next.transitionReason = 'hold_drive_unsupported_asc_entry';
end
next.ready = logical(channelConfig.connected) && ...
    (next.mode == p.state.idle || next.mode == p.state.drive) && ...
    ~next.unsupportedCurrentMode && ~next.unsupportedAscEntry;

if state.mode == p.state.error
    next.outsideErrorUs = uint64(0);
else
    next.outsideErrorUs = addUs(state.outsideErrorUs, stepUs);
end
% Deterministic approximation for the unspecified datasheet reduction step:
% after strictly more than 50 ms healthy, restore the 500 us base wait.
if next.outsideErrorUs > secondsToUs(config.recoveryS) && ...
        abs(input.speedRpm) < 100 && ~logical(input.commandEnable)
    next.resetWaitUs = secondsToUs(config.resetFloorS);
    next.errorOccurrences = uint32(0);
end
output = makeOutput(next);
end

function [active, cause] = evaluateOperationalFault( ...
        state, input, channelConfig, config, wasDrive)
active = true;
% A never-received command reaches here as the INVERTERHIL.DECODERSNAPSHOT
% sentinel INTMAX('UINT32'), which must not be read as a 500 ms dropout. A
% silent bus before the VCU transmits holds Idle; only a gap after a valid
% command latches Error. CANENTERDRIVE still refuses Drive on the sentinel.
if state.commandErrorTimeout && ...
        double(input.commandAgeMs) < double(intmax('uint32'))
    cause = 'command_timeout';
elseif input.positionAgeS > config.positionTimeoutS
    cause = 'position_timeout';
elseif (wasDrive || (state.errorLatched && ...
        strcmp(state.activeFault, 'control_enable_low'))) && ...
        state.controlEnableLowUs > ...
        secondsToUs(config.controlEnableErrorS)
    cause = 'control_enable_low';
elseif input.dcLinkV > 700
    cause = 'dc_link_overvoltage';
elseif input.dcLinkV < -10
    cause = 'dc_link_invalid_low';
elseif (wasDrive || (logical(state.errorLatched) && ...
        strcmp(char(state.latchedFaultCause), ...
        'dc_link_undervoltage'))) && ...
        input.dcLinkV < config.dcLinkMinimumV
    cause = 'dc_link_undervoltage';
elseif any(abs(input.phaseCurrentsA) > 120)
    cause = 'phase_overcurrent';
elseif logical(input.desaturation)
    cause = 'desaturation';
elseif input.motorTemperatureC > channelConfig.motorShutdownC
    cause = 'motor_overtemperature';
elseif input.switchTemperatureC > 145
    cause = 'switch_overtemperature';
elseif state.trackingErrorUs > secondsToUs(config.trackingErrorS)
    cause = 'current_tracking';
elseif logical(input.phaseCurrentMeasurementFailure)
    cause = 'phase_current_measurement';
elseif logical(input.dcLinkMeasurementFailure)
    cause = 'dc_link_measurement';
elseif logical(input.switchTemperatureMeasurementFailure)
    cause = 'switch_temperature_measurement';
else
    active = false;
    cause = 'none';
end
end

function allowed = canEnterDrive(input, channelConfig, config, state)
allowed = logical(input.commandEnable) && logical(input.controlEnable) && ...
    ~logical(input.controlDisable) && ...
    input.dcLinkV > config.dcLinkMinimumV && ...
    logical(channelConfig.connected) && ...
    double(input.commandAgeMs) <= 50 && ...
    ~state.unsupportedCurrentMode && ~state.unsupportedAscEntry;
end

function reason = idleReason(input, channelConfig, config, state)
if ~logical(input.commandEnable)
    reason = 'hold_idle_can_disabled';
elseif ~logical(input.controlEnable)
    reason = 'hold_idle_control_enable_low';
elseif input.dcLinkV <= config.dcLinkMinimumV
    reason = 'hold_idle_dc_link_below_minimum';
elseif double(input.commandAgeMs) > 50
    reason = 'hold_idle_command_stale';
elseif state.unsupportedAscEntry
    reason = 'hold_idle_unsupported_asc_entry';
elseif ~logical(channelConfig.connected)
    reason = 'hold_idle_disconnected';
else
    reason = 'hold_idle';
end
end

function next = resetAfterPowerCycle(next, channelConfig, config, ...
        configurationValid, configReason)
p = inverterhil.protocol();
next.errorLatched = false;
next.configErrorLatched = ~configurationValid;
next.errorOccurrences = uint32(0);
next.resetWaitUs = secondsToUs(config.resetFloorS);
next.faultClearUs = uint64(0);
next.outsideErrorUs = uint64(0);
next.controlEnableLowUs = uint64(0);
next.trackingErrorUs = uint64(0);
next.unsupportedCurrentMode = false;
next.unsupportedAscEntry = false;
next.commandTorqueTimeout = false;
next.commandErrorTimeout = false;
next.positionTimeoutQuantized = false;
next.activeFault = 'none';
next.latchedFaultCause = 'none';
next.zeroTorque = true;
next.configurationReason = configReason;
if configurationValid
    next.mode = p.state.idle;
    next.modeName = 'Idle';
    next.transitionReason = 'power_cycle_valid_configuration';
    next.ready = logical(channelConfig.connected);
else
    next.mode = p.state.configError;
    next.modeName = 'Config Error';
    next.transitionReason = ['power_cycle_' configReason];
    next.ready = false;
end
end

function output = makeOutput(state)
output.mode = state.mode;
output.modeName = state.modeName;
output.transitionReason = state.transitionReason;
output.zeroTorque = state.zeroTorque;
output.ready = state.ready;
output.activeFault = state.activeFault;
output.unsupportedCurrentMode = state.unsupportedCurrentMode;
output.unsupportedAscEntry = state.unsupportedAscEntry;
output.commandTorqueTimeout = state.commandTorqueTimeout;
output.commandErrorTimeout = state.commandErrorTimeout;
output.positionTimeoutQuantized = state.positionTimeoutQuantized;
output.resetWaitS = double(state.resetWaitUs) / 1e6;
end

function [mode, name] = modeValue(name, protocol)
switch name
    case 'Idle'
        mode = protocol.state.idle;
    case 'Drive'
        mode = protocol.state.drive;
    otherwise
        error('inverterhil:InvalidChannelState', 'Unknown mode name.');
end
end

function validateChannelState(state)
required = {'mode', 'modeName', 'transitionReason', 'zeroTorque', ...
    'ready', 'configErrorLatched', 'errorLatched', ...
    'errorOccurrences', 'resetWaitUs', 'faultClearUs', ...
    'outsideErrorUs', 'controlEnableLowUs', 'trackingErrorUs', ...
    'unsupportedCurrentMode', 'unsupportedAscEntry', ...
    'commandTorqueTimeout', 'commandErrorTimeout', ...
    'positionTimeoutQuantized', 'activeFault', 'latchedFaultCause', ...
    'configurationReason', 'stepCount'};
requireFields(state, required, 'inverterhil:InvalidChannelState');
p = inverterhil.protocol();
if ~isa(state.mode, 'uint8') || ~isscalar(state.mode) || ...
        ~any(state.mode == [p.state.idle p.state.drive ...
        p.state.error p.state.configError])
    error('inverterhil:InvalidChannelState', 'mode is invalid.');
end
expectedModeNames = {'Idle', 'Drive', 'Error', 'Config Error'};
textFields = {'modeName', 'transitionReason', 'activeFault', ...
    'latchedFaultCause', 'configurationReason'};
for index = 1:numel(textFields)
    if ~isTextScalar(state.(textFields{index}))
        error('inverterhil:InvalidChannelState', ...
            '%s must be a nonempty character vector or string scalar.', ...
            textFields{index});
    end
end
if ~strcmp(char(state.modeName), expectedModeNames{double(state.mode) + 1})
    error('inverterhil:InvalidChannelState', ...
        'modeName is inconsistent with mode.');
end
knownFaults = {'none', 'command_timeout', 'position_timeout', ...
    'control_enable_low', 'dc_link_overvoltage', ...
    'dc_link_invalid_low', 'dc_link_undervoltage', ...
    'phase_overcurrent', 'desaturation', 'motor_overtemperature', ...
    'switch_overtemperature', 'current_tracking', ...
    'phase_current_measurement', 'dc_link_measurement', ...
    'switch_temperature_measurement'};
faultFields = {'activeFault', 'latchedFaultCause'};
for index = 1:numel(faultFields)
    if ~any(strcmp(char(state.(faultFields{index})), knownFaults))
        error('inverterhil:InvalidChannelState', ...
            '%s is not a known operational fault identifier.', ...
            faultFields{index});
    end
end
booleanFields = {'zeroTorque', 'ready', 'configErrorLatched', ...
    'errorLatched', 'unsupportedCurrentMode', 'unsupportedAscEntry', ...
    'commandTorqueTimeout', 'commandErrorTimeout', ...
    'positionTimeoutQuantized'};
for index = 1:numel(booleanFields)
    validateBinary(state.(booleanFields{index}), booleanFields{index}, ...
        'inverterhil:InvalidChannelState');
end
counters = {'resetWaitUs', 'faultClearUs', 'outsideErrorUs', ...
    'controlEnableLowUs', 'trackingErrorUs', 'stepCount'};
for index = 1:numel(counters)
    if ~isa(state.(counters{index}), 'uint64') || ...
            ~isscalar(state.(counters{index}))
        error('inverterhil:InvalidChannelState', ...
            '%s must be a uint64 scalar.', counters{index});
    end
end

if ~isa(state.errorOccurrences, 'uint32') || ...
        ~isscalar(state.errorOccurrences)
    error('inverterhil:InvalidChannelState', ...
        'errorOccurrences must be a uint32 scalar.');
end
end

function valid = isTextScalar(value)
if ischar(value)
    valid = isrow(value) && ~isempty(value);
elseif isstring(value)
    valid = isscalar(value) && ~ismissing(value) && strlength(value) > 0;
else
    valid = false;
end
end

function validateChannelInput(input)
required = {'commandAgeMs', 'commandEnable', 'resetError', ...
    'ascAllowed', 'currentMode', 'speedRpm', 'positionAgeS', ...
    'controlEnable', 'controlDisable', 'dcLinkV', 'phaseCurrentsA', ...
    'desaturation', 'motorTemperatureC', 'switchTemperatureC', ...
    'idTrackingErrorA', 'iqTrackingErrorA', ...
    'phaseCurrentMeasurementFailure', 'dcLinkMeasurementFailure', ...
    'switchTemperatureMeasurementFailure', 'dischargeActive', 'powerCycle'};
requireFields(input, required, 'inverterhil:InvalidStateInput');
if ~isnumeric(input.commandAgeMs) || ~isscalar(input.commandAgeMs) || ...
        ~isreal(input.commandAgeMs) || ~isfinite(double(input.commandAgeMs)) || ...
        double(input.commandAgeMs) < 0 || ...
        double(input.commandAgeMs) ~= fix(double(input.commandAgeMs)) || ...
        double(input.commandAgeMs) > double(intmax('uint32'))
    error('inverterhil:InvalidStateInput', ...
        'commandAgeMs must be an integer from 0 through uint32 maximum.');
end
binary = {'commandEnable', 'resetError', 'ascAllowed', 'currentMode', ...
    'controlEnable', 'controlDisable', 'desaturation', ...
    'phaseCurrentMeasurementFailure', 'dcLinkMeasurementFailure', ...
    'switchTemperatureMeasurementFailure', 'dischargeActive', 'powerCycle'};
for index = 1:numel(binary)
    validateBinary(input.(binary{index}), binary{index}, ...
        'inverterhil:InvalidStateInput');
end
finiteScalars = {'speedRpm', 'positionAgeS', 'dcLinkV', ...
    'motorTemperatureC', 'switchTemperatureC', ...
    'idTrackingErrorA', 'iqTrackingErrorA'};
for index = 1:numel(finiteScalars)
    value = input.(finiteScalars{index});
    if ~isnumeric(value) || ~isscalar(value) || ~isreal(value) || ...
            ~isfinite(value)
        error('inverterhil:InvalidStateInput', ...
            '%s must be a real finite numeric scalar.', finiteScalars{index});
    end
end
if input.positionAgeS < 0
    error('inverterhil:InvalidStateInput', ...
        'positionAgeS cannot be negative.');
end
if ~isnumeric(input.phaseCurrentsA) || ...
        ~isequal(size(input.phaseCurrentsA), [1 3]) || ...
        ~isreal(input.phaseCurrentsA) || ...
        any(~isfinite(input.phaseCurrentsA))
    error('inverterhil:InvalidStateInput', ...
        'phaseCurrentsA must be a real finite 1x3 vector.');
end
end

function requireFields(value, fields, identifier)
if ~isstruct(value) || ~isscalar(value)
    error(identifier, 'Value must be a scalar structure.');
end
for index = 1:numel(fields)
    if ~isfield(value, fields{index})
        error(identifier, 'Value is missing field %s.', fields{index});
    end
end
end

function validateBinary(value, name, identifier)
if ~(islogical(value) || isnumeric(value)) || ~isscalar(value) || ...
        ~isreal(value) || ~isfinite(double(value)) || ...
        ~(double(value) == 0 || double(value) == 1)
    error(identifier, '%s must be logical 0 or 1.', name);
end
end

function value = secondsToUs(seconds)
value = uint64(round(seconds * 1e6));
end

function result = saturatingDouble(value)
if value > bitshift(intmax('uint64'), -1)
    result = intmax('uint64');
else
    result = value * uint64(2);
end
end

function result = addUs(value, increment)
if value > intmax('uint64') - increment
    result = intmax('uint64');
else
    result = value + increment;
end
end
