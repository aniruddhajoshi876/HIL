function [payloads, dcLinkV, appsBrakeFault] = virtualVcuDeployStep(u)
%#codegen
% Elements 1:40 are the five CAN payloads. Elements 41:44 expose the
% virtual VCU state and its three control outputs to the model observer.
payloads = zeros(44,1,'uint8');
ai = u(1:4);
% Raw-count thresholds below (30100/23100 etc.) are firmware ADC counts
% derived on the 3.3 V reference the firmware's own ADS7066 uses (see
% PINOUTS.md S4.2: sil/registry/params.hpp ADS_VREF_V = 3.3), the same
% basis pedalCalibrationConstants.m/apply_pedal_calibration.m use elsewhere
% in this repo. This conversion previously used 5 V (the IO183 AI range),
% which put every voltage this bench can physically produce below the
% pressed-side threshold no matter what was commanded, always reading
% 100% throttle -- 5 V was the IO183 channel's own full-scale range,
% not the firmware's ADC reference; the two happen to share units (V)
% but are unrelated scales.
rawRead = min(max(double(ai(:)),0),3.3) / 3.3 * 65535;
persistent state ticks rawFilt
if isempty(state)
    state = uint8(0); ticks = uint32(0); rawFilt = rawRead;
end
% First-order low-pass on the raw ADC counts, matching how real VCU
% firmware filters pedal sensors before computing torque. This bench's
% physical throttle/brake self-loop jumpers pick up genuine electrical
% noise; an unfiltered pass-through (the original behavior) reflected
% every count of that noise straight into the torque number every tick.
% alpha = 1 - exp(-dt/tau) with dt = 1 ms (the chart's own tick rate, per
% the 7500-tick/7.5 s precharge timeout below) and tau = 20 ms.
filterAlpha = 0.05;
rawFilt = rawFilt + filterAlpha * (rawRead - rawFilt);
raw = rawFilt;
t1 = min(max((30100-raw(1))/9200,0),1);
t2 = min(max((63600-raw(2))/17100,0),1);
b1 = min(max((raw(3)-9025)/22775,0),1);
b2 = min(max((raw(4)-8280)/23520,0),1);
appsOk = abs(t1-t2) <= 0.20;
brakeOk = (raw(3) >= 9025 && raw(3) <= 31800) && ...
    (raw(4) >= 8280 && raw(4) <= 31800);
% APPS+brake plausibility (UN R13-H / FMVSS 124 brake-override style rule):
% throttle and brake pressed together beyond a nominal deadband/threshold
% must cut torque authority immediately, independent of appsOk/brakeOk.
% 0.25 matches the existing ENABLE->BUZZING brake-applied threshold so one
% number governs "brake is meaningfully applied" everywhere in this chart.
% Exposed as a genuine second output (not packed into PAYLOADS, which is
% only the five real CAN frames) so the GUI can show a real fault
% indicator instead of the operator having to infer it from a torque
% number silently going to zero.
appsBrakeFault = mean([t1 t2]) > 0.05 && mean([b1 b2]) >= 0.25;
precharge = u(5) > 0.5;
mainButton = u(6) > 0.5;
shutdownFeedback = u(9) > 0.5;
if ~isfinite(raw(1)) || ~isfinite(raw(2)) || ~isfinite(raw(3)) || ~isfinite(raw(4))
    appsOk = false; brakeOk = false;
end
rxId = uint32(max(u(13),0));
rxLength = uint32(max(u(16),0));
rxStatus3x3 = rxLength == 8 && (rxId == 899 || rxId == 915 || ...
    rxId == 931 || rxId == 947);
if rxStatus3x3 && bitand(uint8(max(u(17),0)),uint8(3)) >= 2 && ...
        state >= 2 && state <= 4
    state = uint8(5); ticks = uint32(0);
end
if shutdownFeedback
    state = uint8(5); ticks = uint32(0);
elseif state == 5
    state = uint8(0); ticks = uint32(0);
elseif state == 0 && precharge
    state = uint8(1); ticks = uint32(0);
elseif state == 1
    ticks = ticks + 1;
    if ticks >= 7500, state = uint8(2); ticks = uint32(0); end
elseif state == 2 && mainButton && brakeOk && mean([b1 b2]) >= 0.25
    state = uint8(3); ticks = uint32(0);
elseif state == 3
    ticks = ticks + 1;
    if ticks >= 1500, state = uint8(4); ticks = uint32(0); end
elseif state == 4 && precharge
    state = uint8(1); ticks = uint32(0);
end
active = state >= 2 && state <= 4;
drive = state == 4 && appsOk && brakeOk && ~appsBrakeFault;
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
payloads(41) = state;
payloads(42) = uint8(state >= 2 && state <= 4); % MAIN_EN_OUT
payloads(43) = uint8(state == 1);              % PRECH_EN_OUT
payloads(44) = uint8(state >= 1 && state <= 4); % INV_CTRL_EN
% DCLINKV simulates the DC bus capacitance charging through the precharge
% resistor: 0 V at LV_ON, ramping linearly to NOMINALDCLINKV over the same
% 7500-tick PRECHARGING window the state machine itself times against (so
% the two are always consistent by construction, not by a second,
% independently-tuned timer), then held at NOMINALDCLINKV through
% ENABLE/BUZZING/RTD. Drops back to 0 once precharge is re-armed (state
% re-enters PRECHARGING from RTD) or on ERROR_SHUTDOWN/LV_ON, matching a
% real bus discharging once the main contactor opens.
nominalDcLinkV = 400;
if state == 1
    dcLinkV = nominalDcLinkV * min(double(ticks) / 7500, 1);
elseif state >= 2 && state <= 4
    dcLinkV = nominalDcLinkV;
else
    dcLinkV = 0;
end
end
