function bank = receiveStatusFrame(bank, frame, tickMs)
%RECEIVESTATUSFRAME Retain one genuine inverter status CAN frame.
if logical(frame.drop) || logical(frame.isExtended) || logical(frame.isRemote) || ...
        uint8(frame.dlc) ~= uint8(8)
    return;
end
index = find(bank.ids == uint32(frame.id), 1);
if isempty(index)
    return;
end
bank.lastPayload(index, :) = frame.payload;
bank.hasFrame(index) = true;
bank.lastValidTickMs(index) = uint32(tickMs);
bank.acceptedCount(index) = bank.acceptedCount(index) + uint32(1);
end
