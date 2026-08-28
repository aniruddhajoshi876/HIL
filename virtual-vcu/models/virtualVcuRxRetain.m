function omInv = virtualVcuRxRetain(present, id, extended, remote, len, data)
%#codegen
% 1 ms multi-corner Ephorus wheel-speed retention, placed AHEAD of the
% "VCU 5 ms Rate Transition" so the virtual-VCU chart sees every 0x3X5 frame
% that arrived inside a 5 ms window instead of only the last one.
%
% Firmware drains its entire CAN RX FIFO on every comms cycle
% (vcComms.cpp:327-374 handleRxInterrupt while-loop), updating whichever of
% the four EphorusMotorStatus.wheel_speed slots arrived. The HIL base
% boundary (VC_HIL/build/build_inverter_hil_model.m) exposes only ONE FIFO
% item's fields per 1 ms base tick, and the chart samples through a 5 ms
% Rate Transition, so without this block a 5 ms chart tick updates at most
% one corner and drops any other 0x3X5 frames from the same window.
%
% This block runs at the 1 ms base rate: on every tick it latches the
% current frame (if it is one of the four actual-speed frames) into a
% persistent per-corner slot and outputs all four retained rad/s values.
% Persistence is the point -- retained speeds carry across chart executions.
%
% Inputs are the six globally published Port-A RX fields (EphorusRx* Goto
% tags). DATA is the 8-byte payload; bits 48-63 (payload bytes 7-8) are the
% int16 actual-speed RPM (ephorus_driver.cpp:285-289), converted to wheel
% rad/s via 2*pi/60 / GEAR_RATIO with GEAR_RATIO = 13.39
% (ephorus_driver.hpp:162).
%
% Output OMINV is [INV1 INV2 INV3 INV4] = [RL RR FR FL], matching the index
% order the chart's wheelSpeedRadS already used.
persistent omSlots
if isempty(omSlots)
    omSlots = zeros(4,1);
end

rxPresent = present > 0.5;
rxExtended = extended > 0.5;
rxRemote = remote > 0.5;
rxLength = round(len);
rxId = uint32(max(0, round(id)));
if rxPresent && ~rxExtended && ~rxRemote && rxLength == 8
    inv = uint8(0);
    if rxId == uint32(901), inv = uint8(1); end % 0x385 INV1 RL
    if rxId == uint32(917), inv = uint8(2); end % 0x395 INV2 RR
    if rxId == uint32(933), inv = uint8(3); end % 0x3A5 INV3 FR
    if rxId == uint32(949), inv = uint8(4); end % 0x3B5 INV4 FL
    if inv > 0
        d = double(data(:));
        lo = min(max(round(d(7)), 0), 255);
        hi = min(max(round(d(8)), 0), 255);
        speedCounts = lo + hi * 256;
        if speedCounts >= 32768
            speedCounts = speedCounts - 65536;
        end
        omSlots(inv) = speedCounts * (2*pi/60) / 13.39;
    end
end

omInv = omSlots;
end
