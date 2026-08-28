function payload = packControlFrame(inverter, enable, speedRpm, torquePosNm, resetError)
%PACKCONTROLFRAME Pack one golden Ephorus control frame from firmware fields.
if nargin < 5, resetError = false; end
c = virtualvcu.config();
if inverter < 1 || inverter > 4
    error('virtualvcu:InvalidInverter', 'Inverter must be 1..4.');
end
payload = zeros(1, 8, 'uint8');
payload(1) = uint8(logical(enable)) + bitshift(uint8(logical(resetError)), 1);
speed = int16(max(min(round(double(speedRpm)), 32767), -32768));
torquePosNm = min(double(torquePosNm), c.maxTorqueNm);
% ephorus_driver.cpp buildControlFrame truncates nm/(1/256) toward zero
% (no rounding) before clampToI16.
counts = int16(max(min(fix(torquePosNm * 256), 32767), -32768));
payload(3:4) = typecast(speed, 'uint8');
payload(5:6) = typecast(counts, 'uint8');
payload(7:8) = uint8([0 0]);
assert(c.canDlc == 8);
end
