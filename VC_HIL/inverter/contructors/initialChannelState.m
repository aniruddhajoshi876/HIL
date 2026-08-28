function state = initialChannelState(channelConfig, config, unitConfigurationValid)
%INITIALCHANNELSTATE Create deterministic state for one Ephorus channel.
% The optional unitConfigurationValid gate is used by the four-channel wrapper.

if nargin < 2
    config = defaultStateConfig();
end
if nargin < 1
    channelConfig = config.channels(1);
end
if nargin < 3
    unitConfigurationValid = true;
end
validateStateConfig(config);
validateBinary(unitConfigurationValid, 'unitConfigurationValid');
[localValid, configReason] = ...
    evaluateMandatoryConfiguration(channelConfig);
effectiveValid = localValid && logical(unitConfigurationValid);
if localValid && ~logical(unitConfigurationValid)
    configReason = 'unit_configuration_invalid';
end

p = protocol();
% These free-text diagnostic fields take strings of different lengths across
% branches below and in every function that later mutates this state (see
% STEPCHANNELSTATE); MATLAB Coder locks a struct field's array size at first
% assignment unless told otherwise, so each is declared variable-size here at
% the field's origin. 48 chars comfortably covers the longest literal used
% anywhere in the package (38 chars).
coder.varsize('state.modeName', [1, 48], [0, 1]);
coder.varsize('state.transitionReason', [1, 48], [0, 1]);
coder.varsize('state.activeFault', [1, 48], [0, 1]);
coder.varsize('state.latchedFaultCause', [1, 48], [0, 1]);
coder.varsize('state.configurationReason', [1, 48], [0, 1]);
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
