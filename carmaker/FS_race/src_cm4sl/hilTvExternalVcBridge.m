function [motorLoad, appliedNm, limitedNm, commandAgeS, fresh, readyAll, ...
        enable, timedOut] = hilTvExternalVcBridge( ...
        setpointNm, ready, rxTimeS, simTimeS, tIMaxNm, timeoutS)
%#codegen
%HILTVEXTERNALVCBRIDGE  Validate the external-VC motor-torque command for
%   HIL_torquevectoring.mdl and turn it into the four CarMaker motor demands.
%
%   This is the whole decision logic of the external-VC bridge model. The
%   model does NOT compute torque vectoring -- the vehicle controller runs on
%   the VC as code-generated controls, sends four per-inverter torque commands
%   over CAN, the Speedgoat republishes them as 0x501
%   CarMakerInverterTorqueSetpoint, and IO.c decodes them into the
%   MFE_CAN.Inverter{1..4}TorqueSetpointNm dictionary quantities. This function
%   only checks that command and applies it (or a zero-torque fallback) to the
%   CarMaker plant.
%
%   INPUTS
%     setpointNm (1x4) MFE_CAN.Inverter{1..4}TorqueSetpointNm, N*m, already
%                      descaled by IO.c (raw int16 LE / 32). Each element is
%                      the VC's *positive torque limit* for that inverter
%                      (command.torquePosNm256, decoded from control frame
%                      0x186/0x196/0x1A6/0x1B6). Regen / negative-limit torque
%                      is NOT carried on 0x501, so this path only ever drives
%                      the motors forward.
%                      Order [FL FR RL RR] = inverter 1..4 = MotorOut0..3.
%     ready      (1x4) MFE_CAN.Inverter{1..4}Ready bits from 0x502.
%     rxTimeS          MFE_CAN.InverterTorque.RxTimeS -- SimCore.Time (s) of
%                      the last accepted 0x501 frame; -1000 until the first.
%     simTimeS         model clock, same SimCore.Time base.
%     tIMaxNm          per-motor torque limit T_i_max (N*m). Established
%                      vehicle limit from MFE25-Controls (21 N*m).
%     timeoutS         command-freshness window (s). 0.050 for this bench.
%
%   OUTPUTS
%     motorLoad  (1x4) normalised motor demand for MotorOut{0..3}.Load,
%                      = appliedNm / tIMaxNm, matching TorqueVect.mdl's own
%                      1/T_i_max output gain. MotorOut.Trq_trg / .rotv_trg
%                      stay at CarMaker's -99999 "not set" sentinel.
%     appliedNm  (1x4) torque actually applied, for diagnostics.
%     limitedNm  (1x4) command after saturation, before the enable gate.
%     commandAgeS      simTimeS - rxTimeS.
%     fresh            1 if a frame has been seen AND it is within timeoutS.
%     readyAll         1 if all four inverter-ready bits are set.
%     enable           1 if non-zero torque is allowed through to the motors.
%     timedOut         1 if the command age exceeds timeoutS.
%   fresh / readyAll / enable / timedOut are returned as double 0/1 so they
%   map straight onto Write CM Dict diagnostic quantities.

sp  = double(reshape(setpointNm, 1, 4));
rdy = double(reshape(ready, 1, 4)) ~= 0;

% --- command freshness -------------------------------------------------------
commandAgeS = simTimeS - rxTimeS;
seenAFrame  = rxTimeS > 0;
timedOut    = commandAgeS > timeoutS;
fresh       = seenAFrame && ~timedOut;

% --- ready / interlock -----------------------------------------------------
readyAll = all(rdy);

% --- per-motor saturation to the established vehicle limit ----------------
limitedNm = max(min(sp, tIMaxNm), -tIMaxNm);

% TODO(human): produce the enable gate and the applied torque.
%   Set:
%     enable    -- scalar logical: may non-zero torque reach the CarMaker
%                  motors this step?
%     appliedNm -- 1x4 double: the per-motor torque actually applied.
%   Weigh:
%     * Zero is the safe fallback. If any precondition is not met, appliedNm
%       must be [0 0 0 0] and enable false.
%     * The interlock chosen in the handoff is GROUP level: "all four
%       InverterReady = 1 AND the command is fresh" -- one not-ready inverter
%       or one late frame zeros ALL four motors, not just the offender.
%       (readyAll and fresh above already carry those two facts.)
%     * limitedNm is the saturated command; appliedNm is normally limitedNm
%       when enabled and zeros otherwise -- no extra shaping is expected here.
%     * A hard step from full torque to zero on a dropout is acceptable for a
%       HIL plant; do not add a ramp unless you have a specific reason.
enable    = false;
appliedNm = zeros(1, 4);

if fresh && readyAll && commandAgeS >= 0
    enable = true;
    appliedNm = limitedNm;
end
% END TODO(human)

% --- normalise to the CarMaker motor "Load" input -------------------------
motorLoad = appliedNm ./ tIMaxNm;

% --- flags out as double 0/1 for the diagnostic dictionary quantities ----
fresh    = double(fresh ~= 0);
readyAll = double(readyAll ~= 0);
enable   = double(enable ~= 0);
timedOut = double(timedOut ~= 0);
end
