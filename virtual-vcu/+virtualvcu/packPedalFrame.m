function payload = packPedalFrame(throttlePct, brakePct)
%PACKPEDALFRAME Pack the firmware's CAN 501 pedal broadcast (little-endian).
payload = zeros(1, 8, 'uint8');
payload(1) = uint8(round(min(max(double(throttlePct), 0), 100)));
brake = uint16(round(min(max(double(brakePct), 0), 650)));
payload(2:3) = typecast(brake, 'uint8');
payload(4:5) = typecast(brake, 'uint8');
end
