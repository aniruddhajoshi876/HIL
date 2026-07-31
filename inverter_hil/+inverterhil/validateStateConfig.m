function validateStateConfig(config)
%VALIDATESTATECONFIG Validate deterministic state-machine configuration.

required = {'sampleTimeS', 'dcLinkMinimumV', 'configErrorScope', ...
    'controlPinTorqueZeroS', 'positionTimeoutS', ...
    'controlEnableErrorS', 'trackingErrorS', 'resetFloorS', ...
    'resetBackoffMaxS', 'recoveryS', 'channels'};
requireFields(config, required);

positive = {'sampleTimeS', 'controlPinTorqueZeroS', ...
    'positionTimeoutS', 'controlEnableErrorS', 'trackingErrorS', ...
    'resetFloorS', 'resetBackoffMaxS', 'recoveryS'};
for index = 1:numel(positive)
    value = config.(positive{index});
    if ~isnumeric(value) || ~isscalar(value) || ~isreal(value) || ...
            ~isfinite(value) || value <= 0
        invalid('%s must be a real finite positive scalar.', positive{index});
    end
end
if mod(config.sampleTimeS * 1e6, 1) ~= 0
    invalid('sampleTimeS must resolve to an integer number of microseconds.');
end
if ~isnumeric(config.dcLinkMinimumV) || ...
        ~isscalar(config.dcLinkMinimumV) || ...
        ~isreal(config.dcLinkMinimumV) || ...
        ~isfinite(config.dcLinkMinimumV) || ...
        config.dcLinkMinimumV <= -10 || config.dcLinkMinimumV >= 700
    invalid('dcLinkMinimumV must be a real scalar between -10 and 700 V.');
end
if ~(isequal(config.configErrorScope, uint8(0)) || ...
        isequal(config.configErrorScope, uint8(1)))
    invalid('configErrorScope must be uint8(0) or uint8(1).');
end
if config.resetFloorS > config.resetBackoffMaxS
    invalid('resetFloorS cannot exceed resetBackoffMaxS.');
end
if ~isstruct(config.channels) || ~isequal(size(config.channels), [1 4])
    invalid('channels must be a 1x4 structure array.');
end
for channel = 1:4
    inverterhil.evaluateMandatoryConfiguration(config.channels(channel));
end
end

function requireFields(value, fields)
if ~isstruct(value) || ~isscalar(value)
    invalid('State configuration must be a scalar structure.');
end
for index = 1:numel(fields)
    if ~isfield(value, fields{index})
        invalid('State configuration is missing field %s.', fields{index});
    end
end
end

function invalid(message, varargin)
error('inverterhil:InvalidStateConfig', message, varargin{:});
end
