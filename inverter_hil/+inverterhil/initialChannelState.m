function state = initialChannelState(channelConfig, config, unitConfigurationValid)
%INITIALCHANNELSTATE Create deterministic state for one Ephorus channel.
% The optional unitConfigurationValid gate is used by the four-channel wrapper.

if nargin < 2
    config = inverterhil.defaultStateConfig();
end
if nargin < 1
    channelConfig = config.channels(1);
end
if nargin < 3
    unitConfigurationValid = true;
end
inverterhil.validateStateConfig(config);
validateBinary(unitConfigurationValid, 'unitConfigurationValid');
[localValid, configReason] = ...
    inverterhil.evaluateMandatoryConfiguration(channelConfig);
effectiveValid = localValid && logical(unitConfigurationValid);
if localValid && ~logical(unitConfigurationValid)
    configReason = 'unit_configuration_invalid';
end

p = inverterhil.protocol();
state.mode = p.state.idle;
state.modeName = 'Idle';
state.transitionReason = 'initial_idle';
state.zeroTorque = true;
state.ready = effectiveValid && logical(channelConfig.connected);
state.configErrorLatched = false;
state.errorLatched = false;
state.errorOccurrences = uint32(0);
state.resetWaitUs = secondsToUs(config.resetFloorS);
state.faultClearUs = uint64(0);
state.outsideErrorUs = uint64(0);
state.controlEnableLowUs = uint64(0);
state.trackingErrorUs = uint64(0);
state.unsupportedCurrentMode = false;
state.unsupportedAscEntry = false;
state.commandTorqueTimeout = false;
state.commandErrorTimeout = false;
state.positionTimeoutQuantized = false;
state.activeFault = 'none';
state.latchedFaultCause = 'none';
state.configurationReason = configReason;
state.stepCount = uint64(0);

if ~effectiveValid
    state.mode = p.state.configError;
    state.modeName = 'Config Error';
    state.transitionReason = ['initial_' configReason];
    state.configErrorLatched = true;
    state.ready = false;
end
end

function validateBinary(value, name)
if ~(islogical(value) || isnumeric(value)) || ~isscalar(value) || ...
        ~isreal(value) || ~isfinite(double(value)) || ...
        ~(double(value) == 0 || double(value) == 1)
    error('inverterhil:InvalidStateConfig', ...
        '%s must be logical 0 or 1.', name);
end
end

function value = secondsToUs(seconds)
value = uint64(round(seconds * 1e6));
end
