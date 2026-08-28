function [bank, accepted, reason] = receiveCarMakerSteering(bank, frame, tickMs)
%RECEIVECARMAKERSTEERING Retain the most recent valid 0x507 steering frame and
%   prove counter advancement. Modelled on RECEIVEPEDALDEMANDFRAME: presence
%   alone never proves a live sender; COUNTERADVANCED is set only when the
%   modulo-256 truth-group counter has moved FORWARD (see
%   COUNTERFORWARDDISTANCE).
%
%   Rejection policy, in order:
%     injected_drop         GUI fault injection, or an empty FIFO pop.
%     <decoder reason>      ID / DLC / RTR / extended / reserved / CRC / range.
%     duplicate_counter     forward distance 0 -- a frozen-but-repeating
%                           sender. The value is NOT refreshed, so the age
%                           keeps growing and the snapshot goes stale.
%     out_of_order_counter  forward distance in the backward half-window --
%                           a reordered or replayed frame.
%
%   A frame that is forward but has skipped counters IS accepted: the sender
%   is demonstrably alive and the newest value is the one worth having. What
%   must never happen is a duplicate or a rewind being mistaken for liveness.
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
    distance = counterForwardDistance(bank.groupCounter, decoded.groupCounter);
    if distance == uint8(0)
        % Frozen-but-repeating sender. Deliberately does NOT refresh
        % lastValidTickMs: a sender stuck on one counter must age out.
        accepted = false; reason = 'duplicate_counter';
        bank.counterAdvanced = false;
        bank.rejectedCount = bank.rejectedCount + uint32(1);
        bank.lastRejectCode = uint8(3); return;
    end
    if distance >= uint8(128)
        accepted = false; reason = 'out_of_order_counter';
        bank.counterAdvanced = false;
        bank.rejectedCount = bank.rejectedCount + uint32(1);
        bank.lastRejectCode = uint8(4); return;
    end
    bank.counterAdvanced = true;
else
    % First frame of a session: retained, but one frame is not liveness.
    bank.counterAdvanced = false;
end
bank.angleRad = decoded.angleRad;
bank.angleDeg = decoded.angleDeg;
bank.groupCounter = decoded.groupCounter;
bank.hasValue = true;
bank.lastValidTickMs = tickMs;
bank.acceptedCount = bank.acceptedCount + uint32(1);
bank.lastRejectCode = uint8(0);
end
