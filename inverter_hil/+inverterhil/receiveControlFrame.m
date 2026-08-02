function [bank, accepted, reason] = receiveControlFrame(bank, frame, tickMs)
%RECEIVECONTROLFRAME Retain only valid, non-dropped standard data frames.

required = {'id', 'dlc', 'payload', 'isExtended', 'isRemote', 'drop'};
for k = 1:numel(required)
    if ~isfield(frame, required{k})
        error('inverterhil:MalformedFrame', ...
            'Frame is missing field %s.', required{k});
    end
end
if ~isa(tickMs, 'uint32') || ~isscalar(tickMs)
    error('inverterhil:MalformedFrame', 'tickMs must be a uint32 scalar.');
end

if ~isscalar(frame.drop) || logical(frame.drop)
    accepted = false;
    reason = 'injected_drop';
    bank.rejectedCount = bank.rejectedCount + uint32(1);
    bank.lastRejectCode = uint8(1);
    return;
end

[accepted, channel, command, reason] = inverterhil.decodeControlFrame( ...
    frame.id, frame.dlc, frame.payload, frame.isExtended, frame.isRemote);
if accepted
    index = double(channel);
    bank.commands(index) = command;
    bank.hasCommand(index) = true;
    bank.lastValidTickMs(index) = tickMs;
    bank.acceptedCount(index) = bank.acceptedCount(index) + uint32(1);
else
    bank.rejectedCount = bank.rejectedCount + uint32(1);
    bank.lastRejectCode = uint8(2);
end
end
