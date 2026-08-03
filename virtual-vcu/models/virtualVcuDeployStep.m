function payloads = virtualVcuDeployStep(u)
%#codegen
payloads = zeros(40,1,'uint8');
ai = u(1:4);
raw = min(max(double(ai(:)),0),5) / 5 * 65535;
t1 = min(max((30100-raw(1))/9200,0),1);
t2 = min(max((63600-raw(2))/17100,0),1);
b1 = min(max((raw(3)-9025)/22775,0),1);
b2 = min(max((raw(4)-8280)/23520,0),1);
appsOk = abs(t1-t2) <= 0.20;
brakeOk = (raw(3) >= 9025 && raw(3) <= 31800) && ...
    (raw(4) >= 8280 && raw(4) <= 31800);
precharge = u(5) > 0.5;
mainButton = u(6) > 0.5;
shutdownFeedback = u(9) > 0.5;
if ~isfinite(raw(1)) || ~isfinite(raw(2)) || ~isfinite(raw(3)) || ~isfinite(raw(4))
    appsOk = false; brakeOk = false;
end
persistent state ticks
if isempty(state), state = uint8(0); ticks = uint32(0); end
if shutdownFeedback
    state = uint8(5); ticks = uint32(0);
elseif state == 5
    state = uint8(0); ticks = uint32(0);
elseif state == 0 && precharge
    state = uint8(1); ticks = uint32(0);
elseif state == 1
    ticks = ticks + 1;
    if ticks >= 7500, state = uint8(2); ticks = uint32(0); end
elseif state == 2 && mainButton && brakeOk && mean([b1 b2]) >= 25
    state = uint8(3); ticks = uint32(0);
elseif state == 3
    ticks = ticks + 1;
    if ticks >= 1500, state = uint8(4); ticks = uint32(0); end
elseif state == 4 && precharge
    state = uint8(1); ticks = uint32(0);
end
active = state >= 2 && state <= 4;
drive = state == 4 && appsOk && brakeOk;
t = uint8(round(100*mean([t1 t2])));
brake = uint16(round(650*mean([b1 b2])));
payloads(1) = t;
payloads(2) = uint8(mod(brake,256));
payloads(3) = uint8(floor(double(brake)/256));
payloads(4) = payloads(2); payloads(5) = payloads(3);
torque = uint16(round(256*15*mean([t1 t2])));
payloads(9) = uint8(active); payloads(11) = 80; payloads(12) = 70;
payloads(17) = uint8(active); payloads(19) = 80; payloads(20) = 70;
payloads(25) = uint8(active); payloads(27) = 80; payloads(28) = 70;
payloads(33) = uint8(active); payloads(35) = 80; payloads(36) = 70;
if ~drive, torque = uint16(0); end
payloads(13) = uint8(mod(torque,256)); payloads(14) = uint8(floor(double(torque)/256));
payloads(21) = payloads(13); payloads(22) = payloads(14);
payloads(29) = payloads(13); payloads(30) = payloads(14);
payloads(37) = payloads(13); payloads(38) = payloads(14);
end
