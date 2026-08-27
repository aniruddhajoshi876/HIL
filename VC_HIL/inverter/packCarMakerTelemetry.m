function [torquePayload, readyPayload] = packCarMakerTelemetry(telemetry)
%PACKCARMAKERTELEMETRY Pack the two CarMaker-facing inverter telemetry frames.
%
%   0x501 carries all four torque setpoints at the existing 1/32 Nm status
%   resolution.  0x502 carries the corresponding four inverter-ready bits.

required = {'torqueSetpointNm', 'ready'};
for k = 1:numel(required)
    if ~isfield(telemetry, required{k})
        error('inverterhil:MalformedTelemetry', ...
            'Telemetry is missing field %s.', required{k});
    end
end

torqueSetpointNm = telemetry.torqueSetpointNm;
if ~(isnumeric(torqueSetpointNm) || islogical(torqueSetpointNm)) || ...
        ~isequal(size(torqueSetpointNm), [1 4])
    error('inverterhil:MalformedTelemetry', ...
        'torqueSetpointNm must be a 1x4 numeric row vector.');
end
ready = telemetry.ready;
if ~(isnumeric(ready) || islogical(ready)) || ~isequal(size(ready), [1 4])
    error('inverterhil:MalformedTelemetry', ...
        'ready must be a 1x4 logical/numeric row vector.');
end

torqueRaw = uint64(0);
readyRaw = uint64(0);
for channel = 1:4
    torqueRaw = putField(torqueRaw, encodeSigned(torqueSetpointNm(channel), ...
        1 / 32, 16, 'torqueSetpointNm'), ...
        16 * (channel - 1), 16);
    readyRaw = putField(readyRaw, uint64(logicalScalar(ready(channel), ...
        'ready')), channel - 1, 1);
end
torquePayload = u64ToPayload(torqueRaw);
readyPayload = u64ToPayload(readyRaw);
end

function value = logicalScalar(value, name)
if ~(islogical(value) || isnumeric(value)) || ~isscalar(value) || ...
        ~isfinite(double(value)) || ~(double(value) == 0 || double(value) == 1)
    error('inverterhil:InvalidEnum', '%s must be logical 0 or 1.', name);
end
value = logical(value);
end
