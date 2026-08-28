function [payloads, dcLinkV, appsBrakeFault, torqueRequestNm] = virtualVcuDeployStep(u)
%#codegen
% Deployed 5 ms virtual-VCU step, synchronized to MFE26-VC controls branch
% bcd6352e1674ef4b999391f345f675f386718d32.
%
% U is fixed-size: AI01..04 (1:4), DI01..08 (5:12), physical CAN Present,
% ID, Extended, Remote, Length (13:17), and physical CAN payload (18:25).
% No CAN status is synthesized. Only received Ephorus 3x5 frames update the
% four retained wheel speeds. IMU, steering, and load-cell inputs stay zero
% because this Port-A bench does not physically supply those messages.
%
% The generated ControlsMFE25 model is called exactly once per RTD comms
% cycle through vvcu_controls_wrapper.c. Its output order is
% TORQUEREQUESTNM=[tau1 tau2 tau3 tau4]=[FL FR RL RR]. Persistent state is
% never output-aliased; all outputs are fixed-size local copies.
coder.cinclude('vvcu_controls_wrapper.h');

payloads = zeros(48,1,'uint8');
torqueRequestNm = zeros(4,1);
ai = u(1:4);
% IO183 Module 2 analog range is 0..5 V (config.m io183FullScaleV and the AI
% block parAdRange). Convert to the ADS7066-style 16-bit count the firmware
% pedal calibration expects. Firmware reads the ADC directly with no pedal
% filter (Core/Src/driverInputs.cpp convertInputs), so no smoothing is
% applied here either.
% Round to integer ADC counts, matching the host +virtualvcu/voltageToRaw.m.
raw = round(min(max(double(ai(:)),0),5) / 5 * 65535);

persistent state ticks dcLinkAccum12 dcLinkAccum34 appsErrorLatch resetSent wheelSpeedRadS
if isempty(state)
    state = uint8(0);
    ticks = uint32(0);
    dcLinkAccum12 = 0;
    dcLinkAccum34 = 0;
    appsErrorLatch = false;
    resetSent = false;
    wheelSpeedRadS = zeros(4,1);
    if coder.target('MATLAB')
        vvcu_controls_mex('reset');
    else
        coder.ceval('vvcu_controls_reset');
    end
end

% Controls-branch conversions. Brake 2 uses the same 9025 conversion zero
% as brake 1; 8280 exists only as brake-2's unused range-check low bound.
t1 = min(max((30100-raw(1))/7000,0),1);
t2 = min(max((63600-raw(2))/17100,0),1);
b1 = min(max((raw(3)-9025)/22775,0),1);
b2 = min(max((raw(4)-9025)/22775,0),1);

t1Margin = 7000 * 0.15;
t2Margin = 17100 * 0.15;
b1Margin = 22775 * 0.25;
t1InRange = raw(1) >= 23100-t1Margin && raw(1) <= 30100+t1Margin;
t2InRange = raw(2) >= 46500-t2Margin && raw(2) <= 63600+t2Margin;
b1InRange = raw(3) >= 9025-b1Margin && raw(3) <= 31800+b1Margin;
appsOk = t1InRange && t2InRange && abs(t1-t2) <= 0.20;
brakeOk = b1InRange;
if appsOk
    throttleValidPct = (t1+t2)/2;
else
    % Firmware also zeroes throttle1Pct/throttle2Pct here; only the combined
    % throttleValidPct is consumed downstream in this bench step.
    throttleValidPct = 0;
end
if brakeOk
    brakeValidPct = b1;
else
    b1 = 0; b2 = 0; brakeValidPct = 0; % b1/b2 feed the 0x1F5 pressure bytes
end

if throttleValidPct >= 0.25 && brakeValidPct >= 0.25
    appsErrorLatch = true;
end
if appsErrorLatch && throttleValidPct <= 0.05
    appsErrorLatch = false;
end
appsBrakeFault = appsErrorLatch;
if appsOk && ~appsErrorLatch
    torqueRequestPct = throttleValidPct;
else
    torqueRequestPct = 0;
end

precharge = u(5) > 0.5;
mainButton = u(6) > 0.5;
shutdownFeedback = u(9) > 0.5;

% Preserve the last physically received 3x5 speed for each inverter. CAN
% input layout is the flattened Bus Selector output documented above.
rxPresent = u(13) > 0.5;
rxId = uint32(max(0,round(u(14))));
rxExtended = u(15) > 0.5;
rxRemote = u(16) > 0.5;
rxLength = round(u(17));
if rxPresent && ~rxExtended && ~rxRemote && rxLength == 8
    inv = uint8(0);
    if rxId == uint32(901), inv = uint8(1); end % 0x385 INV1 RL
    if rxId == uint32(917), inv = uint8(2); end % 0x395 INV2 RR
    if rxId == uint32(933), inv = uint8(3); end % 0x3A5 INV3 FR
    if rxId == uint32(949), inv = uint8(4); end % 0x3B5 INV4 FL
    if inv > 0
        lo = uint16(min(max(round(u(24)),0),255));
        hi = uint16(min(max(round(u(25)),0),255));
        speedCounts = double(lo + bitshift(hi,8));
        if speedCounts >= 32768, speedCounts = speedCounts-65536; end
        wheelSpeedRadS(inv) = speedCounts * (2*pi/60) / 13.39;
    end
end

% Two independent pair accumulators stand in for the DC-link 12 V and 34 V
% pair voltages. The bench drives them identically, but the fault structure
% matches firmware prechargeComplete(), which requires BOTH pairs above 350 V
% (vcStateMachine.cpp:131-145). This bench has no received 0x400
% system-status frame, so it cannot assert sys.valid; the host reference
% (+virtualvcu/step.m) is stricter and also requires a decoded 0x400.
dcLinkFault = dcLinkAccum12 <= 350 || dcLinkAccum34 <= 350;
enterFault = (state == 2 || state == 3) && dcLinkFault;
enterFaultFromRtd = state == 4 && (dcLinkFault || shutdownFeedback);
% Deviation: this fault-entry branch runs before the "elseif state == 5"
% recovery, so ANY fault entry (DC-link-only included) parks state 5 for one
% full 5 ms cycle before recovery is evaluated; firmware falls through
% state 5 to LV_ON within a single call. shutdownFeedback additionally
% latches the hold until it clears.
holdFault = state == 5 && shutdownFeedback;
if enterFault || enterFaultFromRtd || holdFault
    state = uint8(5); ticks = uint32(0);
elseif state == 5
    state = uint8(0); ticks = uint32(0);
elseif state == 0 && precharge
    state = uint8(1); ticks = uint32(0);
elseif state == 1
    ticks = ticks + 1;
    if ticks >= 1500, state = uint8(2); ticks = uint32(0); end
elseif state == 2 && mainButton && brakeValidPct >= 0.25
    state = uint8(3); ticks = uint32(0);
elseif state == 3
    ticks = ticks + 1;
    if ticks >= 300, state = uint8(4); ticks = uint32(0); end
elseif state == 4 && precharge
    state = uint8(1); ticks = uint32(0);
end

% Pedal broadcast: front=b1, rear=b2 (brake 2 is still converted and sent as
% rear pressure even though it is excluded from plausibility). In RTD the
% throttle byte uses the interlock-gated torqueRequestPct; other states use
% throttleValidPct.
% DEVIATION: firmware skips 0x1F5 entirely on the first RTD (reset) cycle and
% in ERROR_SHUTDOWN (vcComms.cpp run()). This fixed-rate bench re-packs the
% pedal payload every 5 ms because the CAN Write path is not gated per cycle;
% see docs/controls_branch_sync.md.
pedalThrottle = throttleValidPct;
if state == 4, pedalThrottle = torqueRequestPct; end
frontBrake = uint16(round(650*b1));
rearBrake = uint16(round(650*b2));
payloads(1) = uint8(round(100*pedalThrottle));
payloads(2) = uint8(mod(frontBrake,256));
payloads(3) = uint8(floor(double(frontBrake)/256));
payloads(4) = uint8(mod(rearBrake,256));
payloads(5) = uint8(floor(double(rearBrake)/256));

if state ~= 4
    resetSent = false;
elseif ~resetSent
    % First RTD comms cycle: reset+enable, zero speed and torque, no model step.
    payloads(9) = uint8(3);
    payloads(17) = uint8(3);
    payloads(25) = uint8(3);
    payloads(33) = uint8(3);
    resetSent = true;
else
    controlsInputs = zeros(32,1);
    controlsInputs(1) = 0;
    controlsInputs(2) = 0;      % vehicle_speed; no received IMU velocity
    controlsInputs(3) = 0.5;
    controlsInputs(4) = 80000;
    controlsInputs(5) = 1;
    controlsInputs(6) = 1;
    controlsInputs(7) = 0.1;
    % Model order FL,FR,RL,RR from physical inverter order RL,RR,FR,FL.
    controlsInputs(8) = wheelSpeedRadS(4);
    controlsInputs(9) = wheelSpeedRadS(3);
    controlsInputs(10) = wheelSpeedRadS(1);
    controlsInputs(11) = wheelSpeedRadS(2);
    controlsInputs(12) = 0.99;
    controlsInputs(13) = 100;
    controlsInputs(14) = 0;     % ax; no received IMU acceleration
    controlsInputs(15) = 0;     % SWA; no received steering frame
    controlsInputs(16) = 0;     % vy; no received IMU velocity
    controlsInputs(17) = 0;     % yaw_rate; no received IMU gyro
    controlsInputs(18) = throttleValidPct;
    controlsInputs(19) = 0;
    controlsInputs(20) = 15;
    controlsInputs(21) = 0;
    controlsInputs(22) = 1;
    controlsInputs(23) = 1;
    controlsInputs(24) = 0;     % ay
    controlsInputs(25) = 1;     % firmware runtime override
    controlsInputs(26) = 1;     % firmware runtime override
    controlsInputs(27) = 0;
    controlsInputs(28:31) = 0;
    controlsInputs(32) = 1;
    rawTau = zeros(4,1);
    if coder.target('MATLAB')
        rawTau = reshape(vvcu_controls_mex(controlsInputs),4,1);
    else
        coder.ceval('vvcu_controls_step',coder.rref(controlsInputs),coder.wref(rawTau));
    end
    % Firmware caps only the upper positive limit. tau order remains FL/FR/RL/RR.
    for k = 1:4
        if rawTau(k) > 15
            torqueRequestNm(k) = 15;
        else
            torqueRequestNm(k) = rawTau(k);
        end
    end
    inverterTau = [torqueRequestNm(3); torqueRequestNm(4); ...
        torqueRequestNm(2); torqueRequestNm(1)];
    for inverter = 1:4
        base = 1 + 8*inverter;
        payloads(base) = uint8(1);
        payloads(base+2) = uint8(80); % 18000 RPM little-endian
        payloads(base+3) = uint8(70);
        % ephorus_driver.cpp buildControlFrame truncates nm/(1/256) toward
        % zero, then clampToI16 before the little-endian split.
        signedCounts = int32(fix(256*inverterTau(inverter)));
        if signedCounts > 32767, signedCounts = int32(32767); end
        if signedCounts < -32768, signedCounts = int32(-32768); end
        if signedCounts < 0, signedCounts = signedCounts + 65536; end
        payloads(base+4) = uint8(mod(signedCounts,256));
        payloads(base+5) = uint8(floor(double(signedCounts)/256));
    end
end

payloads(41) = state;
payloads(42) = uint8(state >= 2 && state <= 4); % MAIN_EN_OUT (ENABLE/BUZZING/RTD)
payloads(43) = uint8(state == 1 || state == 2); % PRECH_EN_OUT (PRECHARGING + ENABLE, vcStateMachine.cpp:307,325)
payloads(44) = uint8(state >= 1 && state <= 4); % INV_CTRL_EN
payloads(45) = uint8(u(7) > 0.5); % GRI_RELAY_1, cooling DI03
payloads(46) = payloads(45);       % GRI_RELAY_2
payloads(47) = payloads(45);       % COMET_RELAY
payloads(48) = uint8(u(8) > 0.5); % FAN_RELAY, fan DI04

% Existing bench plant: a deterministic 400 V ramp per pair. It is an internal
% plant signal, never a fabricated received CAN frame.
nominalDcLinkV = 400;
rampVoltsPerTick = nominalDcLinkV/1500;
if state >= 1 && state <= 4
    dcLinkAccum12 = min(dcLinkAccum12+rampVoltsPerTick,nominalDcLinkV);
    dcLinkAccum34 = min(dcLinkAccum34+rampVoltsPerTick,nominalDcLinkV);
else
    dcLinkAccum12 = 0;
    dcLinkAccum34 = 0;
end
dcLinkV = min(dcLinkAccum12,dcLinkAccum34);
end
