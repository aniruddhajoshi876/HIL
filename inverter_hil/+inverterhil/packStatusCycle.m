function cycle = packStatusCycle(channelStatus, systemStatus)
%PACKSTATUSCYCLE Pack the ordered nine-frame, 5 ms Ephorus status burst.

if ~isstruct(channelStatus) || numel(channelStatus) ~= 4
    error('inverterhil:MalformedStatus', ...
        'channelStatus must contain exactly four channel structs.');
end
p = inverterhil.protocol();
cycle.ids = p.statusCycleIds;
cycle.dlc = repmat(uint8(8), 1, 9);
cycle.payloads = zeros(9, 8, 'uint8');
for channel = 1:4
    row3X3 = 2 * channel - 1;
    row3X5 = row3X3 + 1;
    cycle.payloads(row3X3, :) = ...
        inverterhil.packStatus3X3(channelStatus(channel).status3X3);
    cycle.payloads(row3X5, :) = ...
        inverterhil.packStatus3X5(channelStatus(channel).status3X5);
end
cycle.payloads(9, :) = inverterhil.packSystemStatus(systemStatus);
end
