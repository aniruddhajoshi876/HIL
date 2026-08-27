function bank = initialPedalDemandBank()
%INITIALPEDALDEMANDBANK Safe retained state for CarMaker pedal demand.
[~, empty] = inverterhil.decodePedalDemandFrame(uint32(0), uint8(0), ...
    zeros(1, 8, 'uint8'), false, false);
bank.demand = empty;
bank.hasDemand = false;
bank.lastValidTickMs = uint32(0);
bank.acceptedCount = uint32(0);
bank.rejectedCount = uint32(0);
bank.lastRejectCode = uint8(0);
bank.counterAdvanced = false;
bank.lastPayload = zeros(1, 8, 'uint8');
end
