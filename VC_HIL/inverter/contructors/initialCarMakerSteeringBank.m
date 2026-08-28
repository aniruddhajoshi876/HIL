function bank = initialCarMakerSteeringBank()
%INITIALCARMAKERSTEERINGBANK Safe retained state for the 0x507
%   CarMakerSteeringTruth transport frame. Single most-recent-valid retainer
%   with counter-advance proof, modelled on INITIALPEDALDEMANDBANK rather
%   than the coherent-group INITIALCARMAKERPHYSICSBANK: this frame is a
%   single scalar, not a multi-frame atomic group.
%
%   Angle is retained in BOTH units on purpose. Radians is the wire and
%   CarMaker unit; degrees is what the Bosch LWS encoder needs. Converting
%   once here, at decode, means no consumer re-derives 180/pi and the two can
%   never drift apart.
bank.angleRad = 0;
bank.angleDeg = 0;
bank.groupCounter = uint8(0);
bank.hasValue = false;
bank.counterAdvanced = false;
bank.lastValidTickMs = uint32(0);
bank.acceptedCount = uint32(0);
bank.rejectedCount = uint32(0);
bank.lastRejectCode = uint8(0);
end
