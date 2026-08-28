function snapshot = carMakerPhysicsSnapshot(bank, tickMs)
%CARMAKERPHYSICSSNAPSHOT Return the last complete atomic physics group.
%   COMPLETE means a full equal-counter 0x503+0x504+0x505 group has been
%   published at least once; a partial group is never visible here. FRESH
%   additionally requires that group to be within the 30 ms window, which is
%   three missed 10 ms cycles of the CarMaker producer.
if ~isa(tickMs, 'uint32') || ~isscalar(tickMs)
    error('inverterhil:InvalidTick', 'tickMs must be a uint32 scalar.');
end
ageMs = intmax('uint32');
if bank.hasPublished
    ageMs = uint32(mod(double(tickMs) - double(bank.lastCompleteTickMs), 2^32));
end
fresh = bank.hasPublished && ageMs <= uint32(30);
snapshot = struct('values', reshape(bank.publishedValues.', 1, 12), ...
    'ageMs', ageMs, 'fresh', fresh, 'complete', bank.hasPublished, ...
    'counter', bank.publishedCounter, 'acceptedCount', bank.acceptedCount, ...
    'rejectedCount', bank.rejectedCount, ...
    'abandonedGroupCount', bank.abandonedGroupCount, ...
    'lastRejectCode', bank.lastRejectCode);
end
