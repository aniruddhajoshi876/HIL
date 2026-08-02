function raw = voltageToRaw(voltageV)
%VOLTAGETORAW Convert measured Module 3 0-5 V input to firmware-style raw.
c = virtualvcu.config();
raw = uint16(round(min(max(double(voltageV), 0), c.io183FullScaleV) ./ ...
    c.io183FullScaleV .* c.adcFullScale));
end
