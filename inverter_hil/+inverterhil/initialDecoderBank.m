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
% Set by STEPMODEL when a channel's retained command carries a torque-limit
% pair outside the plant's domain (positive limit negative, or negative limit
% positive) -- a device-under-test defect the rig must report rather than
% crash on.
%
% LATCHED, deliberately. The model steps every 5 ms while the GUI polls at
% 250 ms, so a per-tick flag would be invisible 49 times out of 50 and the
% operator would never see a fault that really occurred. The cost is that
% recovery is not observable: once set it stays set until the application
% restarts. Clearing it would need an explicit acknowledge path, which does
% not exist yet.
bank.commandOutOfDomain = false(1, 4);
% Raw bytes of the last ACCEPTED frame per channel, retained so the GUI can
% show the wire content rather than only the decode. Zeros until a frame is
% accepted; HASCOMMAND is what distinguishes "never received" from "received
% a genuinely all-zero payload", so a reader must consult it and never treat
% all-zero bytes as absence.
bank.lastPayload = zeros(4, 8, 'uint8');
end
