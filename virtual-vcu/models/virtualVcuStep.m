function [pedal,c1,c2,c3,c4,telemetry,rxSeen,rxId] = virtualVcuStep(ai,rxPresent,rxIdIn,rxExtended,rxRemote,rxLength,rxData)
%#codegen
% Fixed-size deployable wrapper. Physical Module 3 AI is the only pedal source.
x = double(ai);
t = uint8(max(0,min(100,round(x(1) * 20))));
b = uint16(max(0,min(650,round(x(3) * 130))));
pedal = zeros(1,8,'uint8');
pedal(1) = t; pedal(2) = uint8(mod(b,256));
pedal(3) = uint8(floor(double(b) / 256));
pedal(4) = pedal(2); pedal(5) = pedal(3);
q = uint16(max(0,min(32767,round(double(t) * 38.4))));
c1 = zeros(1,8,'uint8'); c2 = c1; c3 = c1; c4 = c1;
c1(1) = 1; c2(1) = 1; c3(1) = 1; c4(1) = 1;
c1(3) = 80; c1(4) = 70; c2(3) = 80; c2(4) = 70;
c3(3) = 80; c3(4) = 70; c4(3) = 80; c4(4) = 70;
c1(5) = uint8(mod(q,256)); c1(6) = uint8(floor(double(q)/256));
c2(5:6) = c1(5:6); c3(5:6) = c1(5:6); c4(5:6) = c1(5:6);
telemetry = [x(1),x(2),x(3),x(4),double(rxPresent),double(rxIdIn), ...
    double(rxExtended),double(rxLength)];
rxSeen = logical(rxPresent); rxId = uint32(rxIdIn);
end
