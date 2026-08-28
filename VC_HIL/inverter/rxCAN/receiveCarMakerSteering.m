function [bank, accepted, reason] = receiveCarMakerSteering(bank, frame, tickMs)
%RECEIVECARMAKERSTEERING Retain the most recent valid 0x507 steering frame and
%   prove alive-counter advancement. Modelled on RECEIVEPEDALDEMANDFRAME:
%   presence alone never proves a live sender; COUNTERADVANCED is set only
%   when the modulo-256 alive counter is exactly the previous value plus one.
%   A structurally valid frame always replaces the retained value and
%   refreshes its timestamp (including a non-advancing counter), so a sender
%   that restarts is picked up again; SELECTSTEERINGSOURCE / the snapshot are
%   what gate on COUNTERADVANCED so a frozen-but-repeating sender is treated
%   as stale.
required = {'id', 'dlc', 'payload', 'isExtended', 'isRemote', 'drop'};
for k = 1:numel(required)
    if ~isfield(frame, required{k}), error('inverterhil:MalformedFrame', ...
            'Frame is missing field %s.', required{k}); end
end
if ~isa(tickMs, 'uint32') || ~isscalar(tickMs)
    error('inverterhil:MalformedFrame', 'tickMs must be a uint32 scalar.');
end
if ~isscalar(frame.drop) || logical(frame.drop)
    accepted = false; reason = 'injected_drop';
    bank.rejectedCount = bank.rejectedCount + uint32(1);
    bank.lastRejectCode = uint8(1); return;
end
[accepted, decoded, reason] = decodeCarMakerSteeringFrame(frame.id, frame.dlc, ...
    frame.payload, frame.isExtended, frame.isRemote);
if ~accepted
    bank.rejectedCount = bank.rejectedCount + uint32(1);
    bank.lastRejectCode = uint8(2); return;
end
if bank.hasValue
    bank.counterAdvanced = decoded.aliveCounter == ...
        uint8(mod(double(bank.aliveCounter) + 1, 256));
else
    bank.counterAdvanced = false;
end
bank.angleDeg = decoded.angleDeg;
bank.speedDegPerSec = decoded.speedDegPerSec;
bank.aliveCounter = decoded.aliveCounter;
bank.hasValue = true;
bank.lastValidTickMs = tickMs;
bank.acceptedCount = bank.acceptedCount + uint32(1);
bank.lastRejectCode = uint8(0);
end
