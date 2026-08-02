function out = step(measuredVoltageV, enabled)
%STEP Compute LV_ON virtual-VCU pedal telemetry and minimum CAN traffic.
%   MEASURED_VOLTAGE_V must be the four physical Module 3 AI readings. No
%   GUI command or Module 1 signal is accepted by this function.
if nargin < 2, enabled = true; end
v = double(measuredVoltageV(:)');
if numel(v) ~= 4, error('virtualvcu:InvalidAnalogVector', 'Expected 4 AI values.'); end
raw = double(virtualvcu.voltageToRaw(v));
[t1, tv1] = virtualvcu.rawToPedal(raw(1), 'throttle', 1);
[t2, tv2] = virtualvcu.rawToPedal(raw(2), 'throttle', 2);
[b1, bv1] = virtualvcu.rawToPedal(raw(3), 'brake', 1);
[b2, bv2] = virtualvcu.rawToPedal(raw(4), 'brake', 2);
out = struct('state', 'LV_ON', 'enabled', logical(enabled), 'raw', raw, ...
    'pedalPct', [t1 t2 b1 b2], 'valid', [tv1 tv2 bv1 bv2], ...
    'pedalPayload', virtualvcu.packPedalFrame(mean([t1 t2]), mean([b1 b2])), ...
    'controlPayloads', zeros(4, 8, 'uint8'));
for i = 1:4
    out.controlPayloads(i,:) = virtualvcu.packControlFrame(i, enabled, 18000, ...
        15 * mean([t1 t2]) / 100);
end
if ~enabled
    out.pedalPayload(:) = 0;
    out.controlPayloads(:) = 0;
end
end
