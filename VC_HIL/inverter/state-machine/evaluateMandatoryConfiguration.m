function [valid, reason] = evaluateMandatoryConfiguration(channelConfig)
%EVALUATEMANDATORYCONFIGURATION Check one virtual inverter configuration.
% NaN represents a deliberately missing numeric configuration value.

if ~isstruct(channelConfig) || ~isscalar(channelConfig)
    invalid('Channel configuration must be a scalar structure.');
end

requiredRuntime = {'connected', 'motorShutdownC', 'ascThresholdRpm'};
for index = 1:numel(requiredRuntime)
    if ~isfield(channelConfig, requiredRuntime{index})
        invalid('Channel configuration is missing field %s.', ...
            requiredRuntime{index});
    end
end
validateBinary(channelConfig.connected, 'connected');
validatePositive(channelConfig.motorShutdownC, 'motorShutdownC');
validatePositive(channelConfig.ascThresholdRpm, 'ascThresholdRpm');

valid = false;
reason = 'missing_motor_pole_pairs';
if ~isfield(channelConfig, 'motorPolePairs') || ...
        isMissingNumeric(channelConfig.motorPolePairs)
    return;
end
validateRealScalar(channelConfig.motorPolePairs, 'motorPolePairs');
if channelConfig.motorPolePairs <= 0 || ...
        channelConfig.motorPolePairs ~= fix(channelConfig.motorPolePairs)
    reason = 'invalid_motor_pole_pairs';
    return;
end

reason = 'missing_rotation_direction';
if ~isfield(channelConfig, 'rotationDirection') || ...
        isMissingNumeric(channelConfig.rotationDirection)
    return;
end
validateRealScalar(channelConfig.rotationDirection, 'rotationDirection');
if ~(channelConfig.rotationDirection == -1 || ...
        channelConfig.rotationDirection == 1)
    reason = 'invalid_rotation_direction';
    return;
end

reason = 'missing_encoder_type';
if ~isfield(channelConfig, 'encoderType')
    return;
end
encoderType = normalizeEncoderType(channelConfig.encoderType);
if isempty(encoderType)
    return;
end

if ~strcmpi(encoderType, 'EnDat')
    reason = 'missing_encoder_reference';
    if ~isfield(channelConfig, 'encoderReference') || ...
            isMissingNumeric(channelConfig.encoderReference)
        return;
    end
    validateRealScalar(channelConfig.encoderReference, 'encoderReference');
elseif isfield(channelConfig, 'encoderReference') && ...
        ~isMissingNumeric(channelConfig.encoderReference)
    validateRealScalar(channelConfig.encoderReference, 'encoderReference');
end

valid = true;
reason = 'valid';
end

function missing = isMissingNumeric(value)
missing = isnumeric(value) && isscalar(value) && isreal(value) && isnan(value);
end

function value = normalizeEncoderType(value)
if isstring(value)
    if ~isscalar(value) || ismissing(value)
        invalid('encoderType must be a character vector or string scalar.');
    end
    value = char(value);
end
if ~ischar(value) || ~isrow(value)
    invalid('encoderType must be a character vector or string scalar.');
end
value = strtrim(value);
end

function validateBinary(value, name)
if ~(islogical(value) || isnumeric(value)) || ~isscalar(value) || ...
        ~isreal(value) || ~isfinite(double(value)) || ...
        ~(double(value) == 0 || double(value) == 1)
    invalid('%s must be logical 0 or 1.', name);
end
end

function validatePositive(value, name)
validateRealScalar(value, name);
if value <= 0
    invalid('%s must be positive.', name);
end
end

function validateRealScalar(value, name)
if ~isnumeric(value) || ~isscalar(value) || ~isreal(value) || ~isfinite(value)
    invalid('%s must be a real finite numeric scalar.', name);
end
end

function invalid(message, varargin)
error('inverterhil:InvalidStateConfig', message, varargin{:});
end
