function payload = packPedalFrame(throttlePct, brakeFrontFraction, brakeRearFraction)
%PACKPEDALFRAME Pack the firmware's CAN 501 pedal broadcast (little-endian).
if nargin < 3
    brakeRearFraction = brakeFrontFraction;
end
payload = zeros(1, 8, 'uint8');
payload(1) = uint8(round(min(max(double(throttlePct), 0), 100)));
% Firmware sends brake pressure directly in PSI: 650 PSI at 100 percent.
% The virtual VCU API carries brake as a normalized fraction, unlike the
% throttle byte which is already an integer percent.
front = uint16(round(650 * min(max(double(brakeFrontFraction), 0), 1)));
rear = uint16(round(650 * min(max(double(brakeRearFraction), 0), 1)));
payload(2:3) = typecast(front, 'uint8');
payload(4:5) = typecast(rear, 'uint8');
end
