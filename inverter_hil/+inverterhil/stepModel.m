function [nextState, nextPlantState, cycle, stateOutput, plantOutput, ...
    nextBank] = stepModel(state, plantState, tickMs, config, cal, bank, frames)
%STEPMODEL Advance one status tick and pack the real, correctly bit-packed
%Idle-state Ephorus status cycle -- not a hardcoded zero placeholder.
%
%   BANK and FRAMES carry received Ephorus control frames. FRAMES is a
%   struct array in RECEIVECONTROLFRAME's format; each is retained into BANK
%   before the snapshot is taken, and NEXTBANK is returned so the caller
%   holds retention across ticks. A channel's COMMANDENABLE comes from its
%   retained command, so a commanding VCU can drive it out of Idle.
%
%   With no BANK/FRAMES supplied the absence of a VCU is represented
%   directly rather than simulated: the snapshot reports HASCOMMAND false
%   and AGEMS at the never-received sentinel (INTMAX('UINT32')) for all four
%   channels. STEPCHANNELSTATE's EVALUATEOPERATIONALFAULT gate (see plan
%   decision on LV_ON) then correctly HOLDS every channel Idle on that
%   sentinel rather than latching a command-timeout Error, and STEPPLANT's
%   torque authority is separately blocked by MODE ~= DRIVE. The packed
%   status is therefore the genuine frame a fully-wired system transmits
%   with no VCU commanding it: real Idle state, real zero torque, real
%   ambient temperatures -- correctly bit-packed per
%   +INVERTERHIL/PACKSTATUS3X3, PACKSTATUS3X5, and PACKSYSTEMSTATUS.
%
%   Not yet wired (left at defaultCalibration()/defaultPlantInput() safe
%   defaults, honestly, rather than fabricated): live DC-link voltage
%   measurement (IO183 AI is read into the model but not yet fed to this
%   function), external load torque, and GUI torque/enable commands. Each of
%   those is a distinct future wiring task, not a limitation of this
%   function's packing correctness.
%
%   STATE, PLANTSTATE  - previous INITIALSYSTEMSTATE / INITIALPLANTSTATE.
%   TICKMS             - uint32 monotonic tick count in milliseconds.
%   CONFIG, CAL         - optional; default to
%                         INVERTERHIL.DEFAULTSTATECONFIG/DEFAULTCALIBRATION.
%
%   Returns the advanced STATE and PLANTSTATE, the nine-frame, 5 ms CYCLE
%   from INVERTERHIL.PACKSTATUSCYCLE, and both raw step outputs for
%   observability (GUI telemetry, logging).

if nargin < 4 || isempty(config)
    config = inverterhil.defaultStateConfig();
end
if nargin < 5 || isempty(cal)
    cal = inverterhil.defaultCalibration();
end
if nargin < 6 || isempty(bank)
    bank = inverterhil.initialDecoderBank();
end
if nargin < 7
    % A single DROPPED frame, not a 1x0 array: RECEIVECONTROLFRAME rejects a
    % dropped frame without touching the bank, so this is behaviourally
    % identical to "no frames" while keeping FRAMES a fixed 1x1 for code
    % generation. A 1x0 default conflicts with the 1x1 a caller passes, and
    % codegen requires one consistent size.
    frames = emptyFrame();
end
if ~isa(tickMs, 'uint32') || ~isscalar(tickMs)
    error('inverterhil:InvalidTick', 'tickMs must be a uint32 scalar.');
end

% Retain received control frames in the caller-owned decoder bank.
%
%   This previously discarded BANK and rebuilt INITIALDECODERBANK() on every
%   call, which pinned HASCOMMAND false and AGEMS at the never-received
%   sentinel forever. That was correct while nothing fed frames in, but it
%   also made the four channels permanently unable to leave Idle even if a
%   VCU were commanding, because STEPCHANNELSTATE gates on those very
%   values. BANK is now threaded through so retention actually persists
%   across ticks, and NEXTBANK is returned for the caller to hold.
%
%   Passing no BANK/FRAMES reproduces the old behaviour exactly, so every
%   existing caller and test keeps its meaning: with an empty bank and no
%   frames the snapshot still reports never-received and the channels still
%   hold Idle.
for index = 1:numel(frames)
    bank = inverterhil.receiveControlFrame(bank, frames(index), tickMs);
end
% NEXTBANK is assigned after the plant loop below, not here: that loop can
% still set COMMANDOUTOFDOMAIN, and returning the bank early would drop it.
snapshot = inverterhil.decoderSnapshot(bank, tickMs);

% Every decoded command bit is forwarded, not just ENABLE.
%
%   Forwarding ENABLE alone left three decoded fields stranded in the bank,
%   and each silently disabled a documented behaviour:
%     RESETERROR  - STEPCHANNELSTATE implements 'error_reset' correctly, but
%                   never saw the bit, so a latched Error could NEVER be
%                   cleared over CAN. A real VCU's reset frame (the one
%                   EPHORUSDRIVER::QUEUERESETENABLE emits) had no effect.
%     CURRENTMODE - the unsupported-current-mode refusal (plan 4.1.2) was
%                   unreachable, so the HIL accepted Drive on a frame it is
%                   specified to refuse.
%     ASCALLOWED  - never reached the state machine at all.
sysInput = inverterhil.defaultStateInput();
for channel = 1:4
    sysInput.channels(channel).commandAgeMs = snapshot.ageMs(channel);
    if bank.hasCommand(channel)
        command = bank.commands(channel);
        sysInput.channels(channel).commandEnable = command.enable;
        sysInput.channels(channel).resetError = command.resetError;
        sysInput.channels(channel).ascAllowed = command.ascAllowed;
        sysInput.channels(channel).currentMode = command.currentMode;
    else
        sysInput.channels(channel).commandEnable = false;
        sysInput.channels(channel).resetError = false;
        sysInput.channels(channel).ascAllowed = false;
        sysInput.channels(channel).currentMode = false;
    end
end

[nextState, stateOutput] = inverterhil.stepSystemState(state, sysInput, config);

plantInput = inverterhil.defaultPlantInput(cal);
for channel = 1:4
    channelOutput = stateOutput.channels(channel);
    plantInput.channels(channel).mode = channelOutput.mode;
    plantInput.channels(channel).ready = channelOutput.ready;
    plantInput.channels(channel).zeroTorque = channelOutput.zeroTorque;
    plantInput.channels(channel).activeFault = channelOutput.activeFault;
    plantInput.channels(channel).commandTorqueTimeout = ...
        channelOutput.commandTorqueTimeout;
    plantInput.channels(channel).commandErrorTimeout = ...
        channelOutput.commandErrorTimeout;

    % The commanded speed setpoint and torque limits reach the plant.
    %
    %   These were left at DEFAULTPLANTINPUT's zeros while the decoded values
    %   sat unused in the bank, so a commanding VCU could put a channel into
    %   Drive but never make it produce torque or turn: the transmitted 3X3
    %   torque setpoint and 3X5 speed stayed 0 forever, with no fault to
    %   explain why. That made the entire torque path untestable.
    %
    %   Counts are converted with CAL.TORQUESCALENMPERCOUNT rather than a
    %   literal, so this does NOT pick a side in the unresolved 1/512 vs
    %   1/256 question -- it follows whichever profile the calibration
    %   selects. The raw counts are forwarded UNSCALED alongside, so a
    %   consumer that must not depend on that choice still has the wire
    %   value.
    if ~bank.hasCommand(channel)
        continue;
    end
    command = bank.commands(channel);
    plantInput.channels(channel).speedSetpointRpm = ...
        double(command.speedSetpointRpm);
    plantInput.channels(channel).rawTorquePosCounts = ...
        command.rawTorquePosCounts;
    plantInput.channels(channel).rawTorqueNegCounts = ...
        command.rawTorqueNegCounts;

    % STEPPLANT REQUIRES an ordered pair: positive limit >= 0, negative
    % limit <= 0. A VCU is under test and may send neither -- a sign error
    % or a swapped pair is exactly the firmware defect this rig exists to
    % find. Passing such a pair through unchanged makes STEPPLANT THROW,
    % which on the real-time target is a hard fault: the HIL would die
    % instead of reporting the DUT's mistake. The pair is therefore clamped
    % into the plant's domain and the violation is recorded per channel, so
    % it surfaces as an observation about the VCU rather than as a crash or
    % as silence. Clamping each side independently also guarantees
    % negative <= positive, so the ordering check cannot fail afterwards.
    positiveNm = double(command.rawTorquePosCounts) * ...
        cal.torqueScaleNmPerCount;
    negativeNm = double(command.rawTorqueNegCounts) * ...
        cal.torqueScaleNmPerCount;
    if positiveNm < 0 || negativeNm > 0
        bank.commandOutOfDomain(channel) = true;
    end
    plantInput.channels(channel).torqueLimitPositiveNm = max(0, positiveNm);
    plantInput.channels(channel).torqueLimitNegativeNm = min(0, negativeNm);
end
nextBank = bank;

[nextPlantState, plantOutput] = inverterhil.stepPlant(plantState, plantInput, cal);

channelStatus = struct( ...
    'status3X3', {plantOutput.channels.status3X3}, ...
    'status3X5', {plantOutput.channels.status3X5});

dcLink12V = plantInput.channels(1).dcLinkV;
dcLink34V = plantInput.channels(3).dcLinkV;

systemStatus.dcLink12V = dcLink12V;
systemStatus.dcLink34V = dcLink34V;
systemStatus.switchingFrequencyKHz = cal.switchingFrequencyKHz;
systemStatus.dcLink12AboveMinimum = dcLink12V > cal.dcLinkMinimumV;
systemStatus.dcLink34AboveMinimum = dcLink34V > cal.dcLinkMinimumV;
systemStatus.controlEnable = sysInput.controlEnable;
systemStatus.controlDisable = sysInput.controlDisable;

cycle = inverterhil.packStatusCycle(channelStatus, systemStatus);
end

function frame = emptyFrame()
%EMPTYFRAME A single frame marked DROP, in RECEIVECONTROLFRAME's required
%   field order. DROP is true so the default retains nothing: "no frames
%   supplied" must never look like a received command.
frame = struct('id', uint32(0), 'dlc', uint8(0), ...
    'payload', zeros(1, 8, 'uint8'), 'isExtended', false, ...
    'isRemote', false, 'drop', true);
end
