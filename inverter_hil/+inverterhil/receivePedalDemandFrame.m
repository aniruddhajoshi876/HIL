function [bank, accepted, reason] = receivePedalDemandFrame(bank, frame, tickMs)
%RECEIVEPEDALDEMANDFRAME Retain valid payload and prove alive advancement.
required = {'id', 'dlc', 'payload', 'isExtended', 'isRemote', 'drop'};
for k = 1:numel(required)
    if ~isfield(frame, required{k}), error('inverterhil:MalformedFrame', ...
            'Frame is missing field %s.', required{k}); end
end
if ~isa(tickMs, 'uint32') || ~isscalar(tickMs), error('inverterhil:MalformedFrame', 'tickMs must be a uint32 scalar.'); end
if ~isscalar(frame.drop) || logical(frame.drop)
    accepted = false; reason = 'injected_drop'; bank.rejectedCount = bank.rejectedCount + uint32(1); bank.lastRejectCode = uint8(1); return;
end
[accepted, demand, reason] = inverterhil.decodePedalDemandFrame(frame.id, frame.dlc, frame.payload, frame.isExtended, frame.isRemote);
if ~accepted, bank.rejectedCount = bank.rejectedCount + uint32(1); bank.lastRejectCode = uint8(2); return; end
if bank.hasDemand
    bank.counterAdvanced = demand.aliveCounter == uint8(mod(double(bank.demand.aliveCounter) + 1, 16));
else
    bank.counterAdvanced = false; % Presence alone cannot prove a live sender.
end
bank.demand = demand; bank.hasDemand = true; bank.lastValidTickMs = tickMs;
bank.acceptedCount = bank.acceptedCount + uint32(1); bank.lastPayload = frame.payload;
end
