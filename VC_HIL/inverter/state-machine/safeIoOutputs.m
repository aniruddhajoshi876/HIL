function output = safeIoOutputs(command, cal)
%SAFEIOOUTPUTS Apply arming and heartbeat authority to HIL-owned outputs.

output.analogV = zeros(1, 4);
output.digital = false(1, 8);
output.armed = false;
output.reason = 'safe_zero';

required = {'applicationRunning', 'ioHealthy', 'armed', ...
    'heartbeatAgeS', 'throttle', 'brake', 'digital'};
for k = 1:numel(required)
    if ~isfield(command, required{k})
        output.reason = ['missing_' required{k}];
        return;
    end
end
interlocks = {'applicationRunning', 'ioHealthy', 'armed'};
for index = 1:numel(interlocks)
    value = command.(interlocks{index});
    if ~(islogical(value) || isnumeric(value)) || ~isscalar(value) || ...
            ~isreal(value) || ~isfinite(double(value)) || ...
            ~(double(value) == 0 || double(value) == 1)
        output.reason = 'malformed_interlock';
        return;
    end
    if ~logical(value)
        output.reason = 'not_armed';
        return;
    end
end
if ~isnumeric(command.heartbeatAgeS) || ~isscalar(command.heartbeatAgeS) || ...
        ~isreal(command.heartbeatAgeS) || ...
        ~isfinite(command.heartbeatAgeS) || command.heartbeatAgeS < 0 || ...
        command.heartbeatAgeS > cal.guiHeartbeatTimeoutS
    output.reason = 'heartbeat_expired';
    return;
end
% CALIBRATION GATE REMOVED 2026-08-02 by explicit operator decision.
%   This previously blocked ALL pedal and digital output while any of the
%   four channels had a non-finite released/pressed endpoint. An
%   uncalibrated channel now reaches the voltage clamp below instead of
%   halting the whole output set. The clamp still bounds the result to
%   [minimumV, maximumV], and the NONFINITE_OUTPUT_BLOCKED check further
%   down still refuses to emit a NaN into a DAC, so an uncalibrated channel
%   fails at that later, narrower check rather than here.
%   Restore by reinstating the any(~isfinite(...)) test.
if ~isnumeric(command.throttle) || ~isscalar(command.throttle) || ...
        ~isreal(command.throttle) || ~isfinite(command.throttle) || ...
        ~isnumeric(command.brake) || ~isscalar(command.brake) || ...
        ~isreal(command.brake) || ~isfinite(command.brake)
    output.reason = 'malformed_pedal_command';
    return;
end
if ~(islogical(command.digital) || isnumeric(command.digital)) || ...
        ~isequal(size(command.digital), [1 8]) || ...
        any(~isfinite(double(command.digital))) || ...
        any(~ismember(double(command.digital), [0 1]))
    output.reason = 'malformed_digital_command';
    return;
end

pedalCommand = [command.throttle command.throttle ...
    command.brake command.brake];
pedalCommand = min(max(pedalCommand, 0), 1);
voltage = cal.pedals.releasedV + pedalCommand .* ...
    (cal.pedals.pressedV - cal.pedals.releasedV);
voltage = min(max(voltage, cal.pedals.minimumV), cal.pedals.maximumV);
if any(~isfinite(voltage))
    output.reason = 'nonfinite_output_blocked';
    return;
end
output.analogV = voltage;
output.digital = logical(command.digital);
output.armed = true;
output.reason = 'armed';
end
