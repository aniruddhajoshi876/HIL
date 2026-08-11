function payload = packPedalFrame(throttlePct, brakeFraction)
%PACKPEDALFRAME Pack the firmware's CAN 501 pedal broadcast (little-endian).
payload = zeros(1, 8, 'uint8');
payload(1) = uint8(round(min(max(double(throttlePct), 0), 100)));
% Firmware sends brake pressure directly in PSI: 650 PSI at 100 percent.
% The virtual VCU API carries brake as a normalized fraction, unlike the
% throttle byte which is already an integer percent.
brake = uint16(round(650 * min(max(double(brakeFraction), 0), 1)));
payload(2:3) = typecast(brake, 'uint8');
payload(4:5) = typecast(brake, 'uint8');
end
