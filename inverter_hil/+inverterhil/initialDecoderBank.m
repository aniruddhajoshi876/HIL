function bank = initialDecoderBank()
%INITIALDECODERBANK Four independent retained command decoders.

[~, ~, empty, ~] = inverterhil.decodeControlFrame( ...
    uint32(0), uint8(0), zeros(1, 8, 'uint8'), false, false);
bank.commands = repmat(empty, 1, 4);
bank.hasCommand = false(1, 4);
bank.lastValidTickMs = zeros(1, 4, 'uint32');
bank.acceptedCount = zeros(1, 4, 'uint32');
bank.rejectedCount = uint32(0);
% Fixed-size code, NOT the human-readable reason. The reason strings differ
% in length ('none', 'injected_drop', 'extended_frame', ...) and a
% variable-length char in a struct field cannot be code generated, which
% blocked STEPMODEL from calling RECEIVECONTROLFRAME inside the Simulink
% model. RECEIVECONTROLFRAME still RETURNS the readable reason for host use.
%   0 none | 1 injected drop | 2 rejected by decodeControlFrame
bank.lastRejectCode = uint8(0);
end
