function config = defaultStateConfig()
%DEFAULTSTATECONFIG Explicit configuration for the host state-machine core.
% Values are deterministic model defaults, not identified hardware data.

p = inverterhil.protocol();
config.sampleTimeS = 1e-3;
config.dcLinkMinimumV = 350;
config.configErrorScope = uint8(0); % 0 per-channel, 1 unit-wide
config.controlPinTorqueZeroS = p.timing.controlPinTorqueZeroS;
config.positionTimeoutS = p.timing.positionErrorS;
config.controlEnableErrorS = p.timing.controlEnableErrorS;
config.trackingErrorS = 0.050;
config.resetFloorS = p.timing.resetFloorS;
config.resetBackoffMaxS = 100;
config.recoveryS = p.timing.recoveryS;

channel = struct( ...
    'connected', true, ...
    'motorPolePairs', 4, ...
    'rotationDirection', 1, ...
    'encoderType', 'EnDat', ...
    'encoderReference', NaN, ...
    'motorShutdownC', 155, ...
    'ascThresholdRpm', 1000);
config.channels = repmat(channel, 1, 4);

inverterhil.validateStateConfig(config);
end
