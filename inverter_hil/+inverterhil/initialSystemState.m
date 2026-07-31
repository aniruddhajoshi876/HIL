function state = initialSystemState(config)
%INITIALSYSTEMSTATE Create four isolated channels with configured error scope.

if nargin < 1
    config = inverterhil.defaultStateConfig();
end
inverterhil.validateStateConfig(config);
localValid = false(1, 4);
for channel = 1:4
    localValid(channel) = inverterhil.evaluateMandatoryConfiguration( ...
        config.channels(channel));
end
if config.configErrorScope == uint8(1)
    unitValid = all(localValid);
else
    unitValid = true;
end
for channel = 1:4
    channels(channel) = inverterhil.initialChannelState( ...
        config.channels(channel), config, unitValid); %#ok<AGROW>
end
state.channels = channels;
state.stepCount = uint64(0);
state.configErrorScope = config.configErrorScope;
end
