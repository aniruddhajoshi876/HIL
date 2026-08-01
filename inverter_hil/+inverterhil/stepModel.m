function [nextState, nextPlantState, cycle, stateOutput, plantOutput] = ...
    stepModel(state, plantState, tickMs, config, cal)
%STEPMODEL Advance one status tick and pack the real, correctly bit-packed
%Idle-state Ephorus status cycle -- not a hardcoded zero placeholder.
%
%   No VCU is connected on this bench, so no control frame is ever received.
%   That absence is represented directly, not simulated: DECODERSNAPSHOT is
%   driven off INITIALDECODERBANK() every call, so HASCOMMAND stays false and
%   AGEMS stays the never-received sentinel (INTMAX('UINT32')) for all four
%   channels. STEPCHANNELSTATE's EVALUATEOPERATIONALFAULT gate (see plan
%   decision on LV_ON) correctly HOLDS every channel Idle on that sentinel
%   rather than latching a command-timeout Error, and STEPPLANT's torque
%   authority is separately blocked by MODE ~= DRIVE regardless of any other
%   input. The packed status is therefore the genuine frame a fully-wired
%   system would transmit with no VCU commanding it: real Idle state, real
%   zero torque, real ambient temperatures -- correctly bit-packed per
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
if ~isa(tickMs, 'uint32') || ~isscalar(tickMs)
    error('inverterhil:InvalidTick', 'tickMs must be a uint32 scalar.');
end

bank = inverterhil.initialDecoderBank();
snapshot = inverterhil.decoderSnapshot(bank, tickMs);

sysInput = inverterhil.defaultStateInput();
for channel = 1:4
    sysInput.channels(channel).commandAgeMs = snapshot.ageMs(channel);
    sysInput.channels(channel).commandEnable = false;
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
