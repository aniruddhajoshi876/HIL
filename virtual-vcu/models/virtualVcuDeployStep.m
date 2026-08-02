function payloads = virtualVcuDeployStep(ai)
%#codegen
payloads = zeros(40,1,'uint8');
raw = min(max(double(ai(:)),0),5) / 5 * 65535;
t1 = min(max((30100-raw(1))/9200,0),1);
t2 = min(max((63600-raw(2))/17100,0),1);
b1 = min(max((raw(3)-9025)/22775,0),1);
b2 = min(max((raw(4)-8280)/23520,0),1);
t = uint8(round(100*mean([t1 t2])));
brake = uint16(round(650*mean([b1 b2])));
payloads(1) = t;
payloads(2) = uint8(mod(brake,256));
payloads(3) = uint8(floor(double(brake)/256));
payloads(4) = payloads(2); payloads(5) = payloads(3);
torque = uint16(round(256*15*mean([t1 t2])));
payloads(9) = 1; payloads(11) = 80; payloads(12) = 70;
payloads(17) = 1; payloads(19) = 80; payloads(20) = 70;
payloads(25) = 1; payloads(27) = 80; payloads(28) = 70;
payloads(33) = 1; payloads(35) = 80; payloads(36) = 70;
payloads(13) = uint8(mod(torque,256)); payloads(14) = uint8(floor(double(torque)/256));
payloads(21) = payloads(13); payloads(22) = payloads(14);
payloads(29) = payloads(13); payloads(30) = payloads(14);
payloads(37) = payloads(13); payloads(38) = payloads(14);
end
