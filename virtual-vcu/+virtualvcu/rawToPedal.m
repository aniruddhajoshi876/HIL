function [percent, valid] = rawToPedal(raw, kind, channel)
%RAWTOPEDAL Apply the MFE26-VC todo-branch pedal calibration.
c = virtualvcu.config();
raw = double(raw);
if strcmpi(kind, 'throttle')
    rest = c.throttleRestRaw(channel);
    pressed = c.throttlePressedRaw(channel);
    percent = (rest - raw) / (rest - pressed);
    valid = raw >= min(rest, pressed) && raw <= max(rest, pressed);
else
    rest = c.brakeRestRaw(channel);
    pressed = c.brakePressedRaw(channel);
    percent = (raw - rest) / (pressed - rest);
    valid = raw >= min(rest, pressed) && raw <= max(rest, pressed);
end
percent = min(max(percent, 0), 1) * 100;
end
