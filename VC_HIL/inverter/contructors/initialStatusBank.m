function bank = initialStatusBank()
%INITIALSTATUSBANK Fixed-size retention for genuinely received inverter status.
p = protocol();
bank.lastPayload = zeros(9, 8, 'uint8');
bank.hasFrame = false(1, 9);
bank.lastValidTickMs = zeros(1, 9, 'uint32');
bank.acceptedCount = zeros(1, 9, 'uint32');
bank.ids = p.statusCycleIds;
end
