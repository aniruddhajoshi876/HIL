function payloads = virtualVcuDeployStep(ai)
%#codegen
payloads = zeros(40,1,'uint8');
t = uint8(max(0,min(100,round(ai(1) * 20))));
payloads(1) = t;
payloads(2) = uint8(max(0,min(255,round(ai(3) * 130))));
payloads(9) = 1; payloads(11) = 80; payloads(12) = 70;
payloads(17) = 1; payloads(19) = 80; payloads(20) = 70;
payloads(25) = 1; payloads(27) = 80; payloads(28) = 70;
payloads(33) = 1; payloads(35) = 80; payloads(36) = 70;
end
