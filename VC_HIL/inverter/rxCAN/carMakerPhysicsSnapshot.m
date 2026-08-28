function snapshot = carMakerPhysicsSnapshot(bank, tickMs)
%CARMAKERPHYSICSSNAPSHOT Return the last complete atomic physics group.
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
    'rejectedCount', bank.rejectedCount, 'lastRejectCode', bank.lastRejectCode);
end
