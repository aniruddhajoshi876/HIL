function [bank, accepted, reason] = receiveCarMakerPhysics(bank, frame, tickMs)
%RECEIVECARMAKERPHYSICS Retain only coherent, forward-advancing physics groups.
%   A group is 0x503 acceleration + 0x504 angular rate + 0x505 velocity
%   carrying one equal truth-group counter; 0x506 Euler shares the counter but
%   is optional. Nothing is published until all three required members of one
%   counter have arrived, so a partial group can never reach the observation
%   selector.
%
%   COUNTER POLICY. Acceptance is by FORWARD PROGRESS (COUNTERFORWARDDISTANCE),
%   not by an exact +1. The exact-+1 rule this replaced was strictly worse:
%   after a single lost frame -- one dropped member, one missed group, one
%   CarMaker pause -- no future counter could ever equal published+1 again, so
%   the physics path latched off for the rest of the run and never recovered
%   when CarMaker came back. Duplicates (distance 0) and reordered or replayed
%   frames (distance in the backward half-window) are still rejected; only the
%   "must be the very next one" part is relaxed.
%
%   A frame belonging to a NEWER group than the one being assembled abandons
%   that partial group rather than rejecting the frame. The partial group is
%   discarded unpublished -- which is the required behaviour -- and assembly
%   restarts on the new counter instead of wedging.
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
[accepted, decoded, reason] = decodeCarMakerPhysicsFrame(frame.id, frame.dlc, ...
    frame.payload, frame.isExtended, frame.isRemote);
if ~accepted
    bank.rejectedCount = bank.rejectedCount + uint32(1);
    bank.lastRejectCode = uint8(2); return;
end
counter = decoded.groupCounter;

% Against the last PUBLISHED group: a repeat of it is a duplicate, and
% anything in the backward half-window is a reorder or a replay.
if bank.hasPublished
    publishedDistance = counterForwardDistance(bank.publishedCounter, counter);
    if publishedDistance == uint8(0)
        accepted = false; reason = 'duplicate_counter';
        bank.rejectedCount = bank.rejectedCount + uint32(1);
        bank.lastRejectCode = uint8(3); return;
    end
    if publishedDistance >= uint8(128)
        accepted = false; reason = 'out_of_order_counter';
        bank.rejectedCount = bank.rejectedCount + uint32(1);
        bank.lastRejectCode = uint8(4); return;
    end
end

% Against the group currently being assembled.
if bank.hasPending && counter ~= bank.pendingCounter
    pendingDistance = counterForwardDistance(bank.pendingCounter, counter);
    if pendingDistance >= uint8(128)
        % Older than the group in progress: a reordered straggler.
        accepted = false; reason = 'counter_mismatch';
        bank.rejectedCount = bank.rejectedCount + uint32(1);
        bank.lastRejectCode = uint8(5); return;
    end
    % Newer: the group in progress will never complete because its remaining
    % members are already behind us on the wire. Drop it unpublished and
    % start assembling the new one. Counted separately from rejections --
    % nothing was wrong with THIS frame.
    bank.abandonedGroupCount = bank.abandonedGroupCount + uint32(1);
    bank.hasPending = false;
end

if ~bank.hasPending
    bank.pendingValues(:) = 0;
    bank.pendingSeen(:) = false;
    bank.pendingCounter = counter;
    bank.hasPending = true;
end
kind = double(decoded.kind);
bank.pendingValues(kind, :) = decoded.values;
bank.pendingSeen(kind) = true;
bank.acceptedCount = bank.acceptedCount + uint32(1);
bank.lastRejectCode = uint8(0);
if all(bank.pendingSeen(1:3))
    bank.publishedValues = bank.pendingValues;
    bank.publishedCounter = counter;
    bank.hasPublished = true;
    bank.lastCompleteTickMs = tickMs;
    bank.hasPending = false;
end
end
