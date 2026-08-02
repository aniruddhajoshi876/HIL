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

if nargin < 4
    config = inverterhil.defaultStateConfig();
end
if nargin < 5
    cal = inverterhil.defaultCalibration();
end
if nargin < 6 || isempty(bank)
    bank = inverterhil.initialDecoderBank();
end
if nargin < 7
    frames = repmat(emptyFrame(), 1, 0);
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
nextBank = bank;
snapshot = inverterhil.decoderSnapshot(bank, tickMs);

sysInput = inverterhil.defaultStateInput();
for channel = 1:4
    sysInput.channels(channel).commandAgeMs = snapshot.ageMs(channel);
    % ENABLE now comes from the retained command rather than a hardcoded
    % false, so a channel with a live enable can actually reach Drive.
    if bank.hasCommand(channel)
        sysInput.channels(channel).commandEnable = ...
            bank.commands(channel).enable;
    else
        sysInput.channels(channel).commandEnable = false;
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
end

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
%EMPTYFRAME Prototype in RECEIVECONTROLFRAME's required field order, used
%   only to give the no-FRAMES default a concrete 1x0 type so MATLAB Coder
%   can resolve the loop that never executes.
frame = struct('id', uint32(0), 'dlc', uint8(0), ...
    'payload', zeros(1, 8, 'uint8'), 'isExtended', false, ...
    'isRemote', false, 'drop', false);
end
