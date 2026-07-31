function bank = initialDecoderBank()
%INITIALDECODERBANK Four independent retained command decoders.

[~, ~, empty, ~] = inverterhil.decodeControlFrame( ...
    uint32(0), uint8(0), zeros(1, 8, 'uint8'), false, false);
bank.commands = repmat(empty, 1, 4);
bank.hasCommand = false(1, 4);
bank.lastValidTickMs = zeros(1, 4, 'uint32');
bank.acceptedCount = zeros(1, 4, 'uint32');
bank.rejectedCount = uint32(0);
bank.lastRejectReason = 'none';
end
