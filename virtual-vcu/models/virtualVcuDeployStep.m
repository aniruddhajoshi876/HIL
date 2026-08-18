function [payloads, dcLinkV, appsBrakeFault, torqueRequestNm] = virtualVcuDeployStep(u)
%#codegen
% Elements 1:40 are the five CAN payloads. Elements 41:44 expose the
% virtual VCU state and its three control outputs to the model observer.
% TORQUEREQUESTNM is a 4th, later addition: the same physical Nm value
% packed into byte pairs 13-14/21-22/29-30/37-38 below, now also exposed
% as its own typed double so it can be marked for XCP measurement without
% requiring a downstream consumer to decode raw CAN bytes. See
% virtual-vcu/docs/carmaker_speedgoat_interface.md section 7 items 4-5.
%
% Pedal thresholds, plausibility rules, the APPS+brake interlock, and the
% ERROR_SHUTDOWN fault causes below are read directly from the real VCU
% firmware (git@github.com:McGillFormulaElectric/MFE26-VC.git, main branch
% at commit 47a1f50): Core/Src/DriverInputs.cpp for pedals/plausibility/
% interlock, Core/Src/vcStateMachine.cpp for the state machine and
% shouldFault()/prechargeComplete(). Verified against real firmware
% source, not re-derived, since this chart's whole purpose is standing in
% for that firmware on a bench with no real VCU.
payloads = zeros(44,1,'uint8');
ai = u(1:4);
% Raw ADC counts on the firmware's own 3.3 V ADS7066 reference (PINOUTS.md
% S4.2: ADS_VREF_V = 3.3).
rawRead = min(max(double(ai(:)),0),3.3) / 3.3 * 65535;
persistent state ticks rawFilt dcLinkAccum appsErrorLatch
if isempty(state)
    state = uint8(0); ticks = uint32(0); rawFilt = rawRead;
    dcLinkAccum = 0; appsErrorLatch = false;
end
% First-order low-pass on the raw ADC counts, matching how real VCU
% firmware filters pedal sensors before computing torque. This bench's
% physical throttle/brake self-loop jumpers pick up genuine electrical
% noise; an unfiltered pass-through reflected every count of that noise
% straight into the torque number every tick. alpha = 1 - exp(-dt/tau)
% with dt = 1 ms (this chart's own tick rate) and tau = 20 ms.
filterAlpha = 0.05;
rawFilt = rawFilt + filterAlpha * (rawRead - rawFilt);
raw = rawFilt;

% Percent conversions: DriverInputs.cpp's convertThrottle1ToPercent
% (throttle1Min=23100, throttle1Max=30100 -- span 7000, NOT the 9200 this
% chart previously used, which put the full-press point at raw=20900
% instead of firmware's real 23100), convertThrottle2ToPercent
% (throttle2Min=46500, throttle2Max=63600), convertBrakeToPercent
% (brakeMin=9025, brakeMax=31800, brake channel 1 only -- see BRAKEOK
% below for why the shared channel-1 boundary is used).
t1 = min(max((30100-raw(1))/7000,0),1);
t2 = min(max((63600-raw(2))/17100,0),1);
b1 = min(max((raw(3)-9025)/22775,0),1);

% Range plausibility: DriverInputs.cpp's isThrottle1InRange/
% isThrottle2InRange/isBrake1InRange. A WIDER band around the nominal span
% (15% margin for throttle, 25% for brake) that fails a sensor reading
% clearly out of range (disconnected/shorted) even before checking
% dual-sensor agreement -- this chart previously had no equivalent, only
% the percent-conversion clamp to [0,1], which cannot distinguish "at
% rest" from "sensor railed/disconnected".
throttle1Margin = (30100 - 23100) * 0.15;
throttle1InRange = raw(1) >= (23100 - throttle1Margin) && raw(1) <= (30100 + throttle1Margin);
throttle2Margin = (63600 - 46500) * 0.15;
throttle2InRange = raw(2) >= (46500 - throttle2Margin) && raw(2) <= (63600 + throttle2Margin);
brake1Margin = (31800 - 9025) * 0.25;
brake1InRange = raw(3) >= (9025 - brake1Margin) && raw(3) <= (31800 + brake1Margin);

% isThrottlePlausible(): both channels in range AND agree within 20%
% (FSAE T11.8 dual-sensor rule).
appsOk = throttle1InRange && throttle2InRange && abs(t1 - t2) <= 0.20;
% isBrakePlausible(): "Brake2 sensor is inactive (hardware fault). Only
% brake1 range is checked." -- real firmware's own comment. Only brake1
% gates plausibility; brake2 is not read into BRAKEVALIDPCT at all, which
% is why this chart no longer averages b1/b2 anywhere below.
brakeOk = brake1InRange;
if ~isfinite(raw(1)) || ~isfinite(raw(2)) || ~isfinite(raw(3))
    appsOk = false; brakeOk = false;
end

% checkPlausibility(): an implausible channel is zeroed at the source, not
% just excluded from downstream gating -- THROTTLEVALIDPCT/BRAKEVALIDPCT
% are 0 whenever their own plausibility check fails, matching
% DriverInputs.cpp exactly (both the APPS+brake interlock below and the
% transmitted pedal percentages read these, not the raw t1/t2/b1).
if appsOk
    throttleValidPct = mean([t1 t2]);
else
    throttleValidPct = 0;
end
if brakeOk
    brakeValidPct = b1;
else
    brakeValidPct = 0;
end

% APPS+brake interlock (FSAE T11.9, DriverInputs.cpp run()): triggers at
% throttle>=25% AND brake>=25% together -- not the 5%/25% this chart
% previously used -- and LATCHES via APPSERRORLATCH (mirroring firmware's
% own persistent SHARED.APPSERROR): once tripped, torque stays cut until
% throttle drops to <=5%, not merely until the pedals are no longer both
% pressed past threshold simultaneously.
if throttleValidPct >= 0.25 && brakeValidPct >= 0.25
    appsErrorLatch = true;
end
if appsErrorLatch && throttleValidPct <= 0.05
    appsErrorLatch = false;
end
appsBrakeFault = appsErrorLatch;

precharge = u(5) > 0.5;
mainButton = u(6) > 0.5;
shutdownFeedback = u(9) > 0.5;

% shouldFault() (vcStateMachine.cpp): DC-link<=350V faults ENABLE/
% BUZZING/RTD (PRECHARGECOMPLETE()'s health check); SDERROR only faults
% RTD specifically -- real firmware's shouldFault() reads shared.sdError
% only in the RTD case, not universally, presumably because the physical
% shutdown loop is hardware-enforced independent of software state in
% every other state, and software only needs to react to it once actually
% driving. PRECHARGING never faults. The previous version of this chart
% used a CAN-status-bit trigger (rxStatus3x3/bitand(...)>=2) modeled on
% real firmware's ALLINVERTERSREADY(), but that check is CURRENTLY
% COMMENTED OUT OF SHOULDFAULT() in real firmware ("unused ... while
% inverter bring-up is in progress") -- removed here to match; re-add if
% real firmware re-enables it.
%
% DCLINKACCUM (this tick's value, before it is updated further down)
% stands in for EPHORUSDRIVER's measured dcLink12_v/34_v: this bench has
% no real DC bus, so this chart's own simulated ramp (below) is what
% PRECHARGECOMPLETE() would be reading on real hardware.
dcLinkFault = dcLinkAccum <= 350;
enterFault = (state == 2 || state == 3) && dcLinkFault;
enterFaultFromRtd = state == 4 && (dcLinkFault || shutdownFeedback);
% Real firmware's ENTERSTATE(ERROR_SHUTDOWN) is followed, in the SAME
% RUN() CALL, by FORCELVON() -- an immediate, same-cycle fall-through back
% to LV_ON, which would make ERROR_SHUTDOWN invisible to a human operator
% or even this bench's 250 ms-polling GUI. This chart deliberately HOLDS
% in ERROR_SHUTDOWN (state 5) until the underlying cause clears, rather
% than replicating that same-cycle auto-recovery: the bench's value is in
% being able to observe and manually clear a fault, and there's no
% indication the instant-recovery is an intentional competition-rules
% behavior rather than an artifact of how ENTERSTATE/FORCELVON happen to
% be sequenced. HOLDFAULT re-checks SHUTDOWNFEEDBACK every tick regardless
% of current state (state is already 5 by the tick after entry, so
% checking only STATE==2/3/4 as above would let it clear itself the very
% next tick, silently reproducing the same instant-recovery this is meant
% to avoid).
%
% HOLDFAULT deliberately does NOT also re-check DCLINKFAULT: entering
% ERROR_SHUTDOWN zeroes DCLINKACCUM below (state no longer in [1,4]), so
% DCLINKFAULT is trivially true for as long as ERROR_SHUTDOWN lasts --
% including it here would make a DC-link-triggered fault permanently
% unrecoverable regardless of SHUTDOWNFEEDBACK, a real deadlock confirmed
% live on hardware (state never left ERROR_SHUTDOWN after clearing
% shutdown feedback, because DCLINKFAULT alone kept HOLDFAULT true
% forever). DC-link health is what PRECHARGING re-establishes on the way
% back to RTD, not a condition LV_ON itself needs to satisfy.
holdFault = state == 5 && shutdownFeedback;

if enterFault || enterFaultFromRtd || holdFault
    state = uint8(5); ticks = uint32(0);
elseif state == 5
    state = uint8(0); ticks = uint32(0);
elseif state == 0 && precharge
    state = uint8(1); ticks = uint32(0);
elseif state == 1
    ticks = ticks + 1;
    if ticks >= 7500, state = uint8(2); ticks = uint32(0); end
elseif state == 2 && mainButton && brakeValidPct >= 0.25
    state = uint8(3); ticks = uint32(0);
elseif state == 3
    ticks = ticks + 1;
    if ticks >= 1500, state = uint8(4); ticks = uint32(0); end
elseif state == 4 && precharge
    state = uint8(1); ticks = uint32(0);
end
active = state >= 2 && state <= 4;
% torqueRequestPct (DriverInputs.cpp run()): appsPlausible && !appsError,
% full stop -- real firmware does NOT also require brakePlausible/
% brakeOk to authorize torque. STATE==4 (RTD) is kept as an additional
% gate here, standing in for whatever ultimately gates the real inverter
% accepting a torque command outside RTD (VC firmware itself computes
% TORQUEREQUESTPCT every cycle regardless of state; this repo does not
% contain the Ephorus inverter's own enable logic to confirm it refuses
% torque before RTD, so RTD-only is the conservative choice here).
drive = state == 4 && appsOk && ~appsBrakeFault;
t = uint8(round(100*throttleValidPct));
brake = uint16(round(650*brakeValidPct));
payloads(1) = t;
payloads(2) = uint8(mod(brake,256));
payloads(3) = uint8(floor(double(brake)/256));
payloads(4) = payloads(2); payloads(5) = payloads(3);
torque = uint16(round(256*15*throttleValidPct));
% Named double alongside the uint16 CAN-count encoding above: same
% underlying physical quantity (15 Nm full scale times throttleValidPct),
% zeroed by the same DRIVE gate below, computed directly rather than by
% dividing TORQUE back out of its quantized counts.
torqueRequestNm = 15*throttleValidPct;
payloads(9) = uint8(active); payloads(11) = 80; payloads(12) = 70;
payloads(17) = uint8(active); payloads(19) = 80; payloads(20) = 70;
payloads(25) = uint8(active); payloads(27) = 80; payloads(28) = 70;
payloads(33) = uint8(active); payloads(35) = 80; payloads(36) = 70;
if ~drive, torque = uint16(0); torqueRequestNm = 0; end
payloads(13) = uint8(mod(torque,256)); payloads(14) = uint8(floor(double(torque)/256));
payloads(21) = payloads(13); payloads(22) = payloads(14);
payloads(29) = payloads(13); payloads(30) = payloads(14);
payloads(37) = payloads(13); payloads(38) = payloads(14);
payloads(41) = state;
payloads(42) = uint8(state >= 2 && state <= 4); % MAIN_EN_OUT
payloads(43) = uint8(state == 1);              % PRECH_EN_OUT
payloads(44) = uint8(state >= 1 && state <= 4); % INV_CTRL_EN
% DCLINKV simulates the DC bus capacitance charging through the precharge
% resistor: 0 V at LV_ON, ramping at a FIXED rate (RAMPVOLTSPERTICK, volts
% per 1 ms tick) while PRECHARGING through RTD, capping at NOMINALDCLINKV
% once reached. The ramp rate is deliberately independent of the
% PRECHARGING timeout (the ELSEIF STATE==1 branch above, currently 7500
% ticks). NOMINALDCLINKV=400 is a placeholder, not read from real
% firmware: MFE26-VC only encodes a 350 V FLOOR (PRECHARGECOMPLETE()'s
% health check, used as DCLINKFAULT above), not this car's actual nominal
% pack voltage, which is not in firmware source -- replace 400 with the
% real value once known.
%
% DCLINKACCUM, not DCLINKV itself, is the persistent state: a variable
% that is both persistent and a direct MATLAB Function output breaks
% Simulink's code generation size inference (the same pitfall TXCOUNTER/
% TXCOUNT already works around elsewhere in this file).
nominalDcLinkV = 400;
rampVoltsPerTick = 400 / 7500;
if state >= 1 && state <= 4
    dcLinkAccum = min(dcLinkAccum + rampVoltsPerTick, nominalDcLinkV);
else
    dcLinkAccum = 0;
end
dcLinkV = dcLinkAccum;
end
