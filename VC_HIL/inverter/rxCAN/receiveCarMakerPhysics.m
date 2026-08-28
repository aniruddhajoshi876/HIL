function [bank, accepted, reason] = receiveCarMakerPhysics(bank, frame, tickMs)
%RECEIVECARMAKERPHYSICS Retain only coherent, advancing physics groups.
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
if bank.hasPublished && counter == bank.publishedCounter
    accepted = false; reason = 'duplicate_counter';
    bank.rejectedCount = bank.rejectedCount + uint32(1);
    bank.lastRejectCode = uint8(3); return;
end
if bank.hasPending && counter ~= bank.pendingCounter
    % A frame that does not match the group currently being assembled is a
    % mismatch against the pending counter, checked before the
    % against-published out-of-order test below (which only classifies the
    % start of a fresh group).
    accepted = false; reason = 'counter_mismatch';
    bank.rejectedCount = bank.rejectedCount + uint32(1);
    bank.lastRejectCode = uint8(5); return;
end
if bank.hasPublished && ~bank.hasPending && ...
        counter ~= uint8(mod(double(bank.publishedCounter) + 1, 256))
    accepted = false; reason = 'out_of_order_counter';
    bank.rejectedCount = bank.rejectedCount + uint32(1);
    bank.lastRejectCode = uint8(4); return;
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
