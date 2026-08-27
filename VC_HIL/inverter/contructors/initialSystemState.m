function state = initialSystemState(config)
%INITIALSYSTEMSTATE Create four isolated channels with configured error scope.

if nargin < 1
    config = defaultStateConfig();
end
validateStateConfig(config);
localValid = false(1, 4);
for channel = 1:4
    localValid(channel) = evaluateMandatoryConfiguration( ...
        config.channels(channel));
end
if config.configErrorScope == uint8(1)
    unitValid = all(localValid);
else
    unitValid = true;
end
% CHANNELS is built via a full first assignment (channel 1), then
% preallocated with REPMAT: MATLAB Coder does not support growing a struct
% array by indexed assignment (CHANNELS(channel) = ... with CHANNELS not yet
% existing at that size).
channels = repmat(initialChannelState( ...
    config.channels(1), config, unitValid), 1, 4);
for channel = 2:4
    channels(channel) = initialChannelState( ...
        config.channels(channel), config, unitValid);
end
state.channels = channels;
state.stepCount = uint64(0);
state.configErrorScope = config.configErrorScope;
end
