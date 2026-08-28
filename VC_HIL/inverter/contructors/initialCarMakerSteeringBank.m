function bank = initialCarMakerSteeringBank()
%INITIALCARMAKERSTEERINGBANK Safe retained state for the 0x507
%   CarMakerDriverSteering transport frame. Single most-recent-valid retainer
%   with alive-counter advancement, modelled on INITIALPEDALDEMANDBANK rather
%   than the coherent-group INITIALCARMAKERPHYSICSBANK: this frame is a single
%   scalar pair, not a multi-frame atomic group.
bank.angleDeg = 0;
bank.speedDegPerSec = 0;
bank.aliveCounter = uint8(0);
bank.hasValue = false;
bank.counterAdvanced = false;
bank.lastValidTickMs = uint32(0);
bank.acceptedCount = uint32(0);
bank.rejectedCount = uint32(0);
bank.lastRejectCode = uint8(0);
end
