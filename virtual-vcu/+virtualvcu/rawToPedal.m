function [percent, valid] = rawToPedal(raw, kind, channel)
%RAWTOPEDAL Apply the pinned controls-branch calibration and range margin.
c = virtualvcu.config();
raw = double(raw);
if strcmpi(kind, 'throttle')
    rest = c.throttleRestRaw(channel);
    pressed = c.throttlePressedRaw(channel);
    percent = (rest - raw) / (rest - pressed);
    margin = abs(rest - pressed) * 0.15;
    valid = raw >= min(rest, pressed)-margin && raw <= max(rest, pressed)+margin;
else
    rest = c.brakeRestRaw(channel);
    pressed = c.brakePressedRaw(channel);
    percent = (raw - rest) / (pressed - rest);
    low = c.brakeRangeLowRaw(channel);
    margin = (pressed - low) * 0.25;
    valid = raw >= low-margin && raw <= pressed+margin;
end
percent = min(max(percent, 0), 1) * 100;
end
