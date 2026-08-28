function snapshot = pedalDemandSnapshot(bank, tickMs)
%PEDALDEMANDSNAPSHOT Produce the atomic CAN ownership decision.
if ~isa(tickMs, 'uint32') || ~isscalar(tickMs), error('inverterhil:InvalidTick', 'tickMs must be a uint32 scalar.'); end
ageMs = intmax('uint32');
if bank.hasDemand, ageMs = uint32(mod(double(tickMs) - double(bank.lastValidTickMs), 2^32)); end
p = protocol();
fresh = bank.hasDemand && ageMs <= p.timing.pedalDemandTimeoutMs;
snapshot = struct('throttlePercent', bank.demand.throttlePercent, 'brakePercent', bank.demand.brakePercent, ...
    'active', bank.demand.active, 'counterAdvanced', bank.counterAdvanced, 'ageMs', ageMs, 'fresh', fresh, ...
    'ownsPedals', fresh && bank.counterAdvanced && bank.demand.active);
end
