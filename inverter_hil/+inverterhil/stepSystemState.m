function [next, output] = stepSystemState(state, input, config)
%STEPSYSTEMSTATE Advance four channels with pairwise DC and shared pin inputs.

if nargin < 3
    config = inverterhil.defaultStateConfig();
end
inverterhil.validateStateConfig(config);
validateSystemState(state, config);
validateSystemInput(input);

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

next = state;
for channel = 1:4
    channelInput = input.channels(channel);
    channelInput.controlEnable = input.controlEnable;
    channelInput.controlDisable = input.controlDisable;
    channelInput.powerCycle = input.powerCycle;
    if channel <= 2
        channelInput.dcLinkV = input.dcLinkV(1);
    else
        channelInput.dcLinkV = input.dcLinkV(2);
    end
    [next.channels(channel), channelOutput(channel)] = ...
        inverterhil.stepChannelState(state.channels(channel), ...
        channelInput, config.channels(channel), config, unitValid); %#ok<AGROW>
end
next.stepCount = addOne(state.stepCount);
next.configErrorScope = config.configErrorScope;

output.channels = channelOutput;
output.mode = [channelOutput.mode];
output.zeroTorque = [channelOutput.zeroTorque];
output.ready = [channelOutput.ready];
output.transitionReason = {channelOutput.transitionReason};
output.controlEnable = logical(input.controlEnable);
output.controlDisable = logical(input.controlDisable);
output.dcLinkV = input.dcLinkV;
end

function validateSystemState(state, config)
if ~isstruct(state) || ~isscalar(state) || ...
        ~isfield(state, 'channels') || ...
        ~isstruct(state.channels) || ...
        ~isequal(size(state.channels), [1 4]) || ...
        ~isfield(state, 'stepCount') || ...
        ~isa(state.stepCount, 'uint64') || ~isscalar(state.stepCount) || ...
        ~isfield(state, 'configErrorScope')
    error('inverterhil:InvalidSystemState', ...
        ['System state must contain four channels, a uint64 stepCount, ' ...
        'and configErrorScope.']);
end
if ~isa(state.configErrorScope, 'uint8') || ...
        ~isscalar(state.configErrorScope) || ...
        ~(state.configErrorScope == uint8(0) || ...
        state.configErrorScope == uint8(1)) || ...
        state.configErrorScope ~= config.configErrorScope
    error('inverterhil:InvalidSystemState', ...
        'System configErrorScope is invalid or inconsistent with config.');
end
end

function validateSystemInput(input)
required = {'controlEnable', 'controlDisable', 'powerCycle', ...
    'dcLinkV', 'channels'};
if ~isstruct(input) || ~isscalar(input)
    error('inverterhil:InvalidStateInput', ...
        'System input must be a scalar structure.');
end
for index = 1:numel(required)
    if ~isfield(input, required{index})
        error('inverterhil:InvalidStateInput', ...
            'System input is missing field %s.', required{index});
    end
end
binary = {'controlEnable', 'controlDisable', 'powerCycle'};
for index = 1:numel(binary)
    value = input.(binary{index});
    if ~(islogical(value) || isnumeric(value)) || ~isscalar(value) || ...
            ~isreal(value) || ~isfinite(double(value)) || ...
            ~(double(value) == 0 || double(value) == 1)
        error('inverterhil:InvalidStateInput', ...
            '%s must be logical 0 or 1.', binary{index});
    end
end
if ~isnumeric(input.dcLinkV) || ~isequal(size(input.dcLinkV), [1 2]) || ...
        ~isreal(input.dcLinkV) || any(~isfinite(input.dcLinkV))
    error('inverterhil:InvalidStateInput', ...
        'dcLinkV must be a real finite 1x2 vector.');
end
if ~isstruct(input.channels) || ~isequal(size(input.channels), [1 4])
    error('inverterhil:InvalidStateInput', ...
        'channels must be a 1x4 structure array.');
end
end

function value = addOne(value)
if value == intmax('uint64')
    error('inverterhil:InvalidSystemState', 'System step counter overflow.');
end
value = value + uint64(1);
end
