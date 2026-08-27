function [frame, dropped] = applyControlDropMask(frame, dropControlMask)
%APPLYCONTROLDROPMASK Force-drop a received control frame whose channel is
%masked, before it ever reaches INVERTERHIL.RECEIVECONTROLFRAME.
%
%   [FRAME, DROPPED] = APPLYCONTROLDROPMASK(FRAME, DROPCONTROLMASK) looks up
%   FRAME.ID against INVERTERHIL.PROTOCOL's four control identifiers
%   (0x186/0x196/0x1A6/0x1B6, channels 1-4) and, when it matches channel N
%   and bit (N-1) of DROPCONTROLMASK is set, forces FRAME.DROP = true.
%   RECEIVECONTROLFRAME rejects a dropped frame outright (reason
%   'injected_drop') without touching the decoder bank, so a masked frame
%   is genuinely absent from the retained command -- not decoded and then
%   zeroed.
%
%   A frame whose ID does not match any control channel, or whose channel
%   bit is clear, is returned with FRAME unchanged (an already-dropped
%   FRAME.DROP stays dropped either way). DROPPED reports whether THIS call
%   is what forced the drop, so a caller can distinguish "no CAN data this
%   tick" from "injected by the drop mask" if it needs to.
%
%   DROPCONTROLMASK is the GUI-owned hil_cmd_can_drop_control_mask tunable:
%   a uint8 per-channel bitmask, bit (channel-1) gating that channel's
%   control identifier (0x186 = ch1 = bit0, 0x196 = ch2 = bit1,
%   0x1A6 = ch3 = bit2, 0x1B6 = ch4 = bit3). Bits 4-7 are unused.

required = {'id', 'dlc', 'payload', 'isExtended', 'isRemote', 'drop'};
for k = 1:numel(required)
    if ~isfield(frame, required{k})
        error('inverterhil:MalformedFrame', ...
            'Frame is missing field %s.', required{k});
    end
end
if ~isnumeric(dropControlMask) || ~isscalar(dropControlMask) || ...
        ~isreal(dropControlMask) || ~isfinite(double(dropControlMask)) || ...
        double(dropControlMask) < 0 || double(dropControlMask) > 255
    error('inverterhil:InvalidDropMask', ...
        'dropControlMask must be a uint8-range scalar.');
end

dropped = false;
mask = uint8(dropControlMask);
p = protocol();
channel = find(p.controlIds == uint32(frame.id), 1);
if isempty(channel)
    return;
end
if bitget(mask, channel) ~= 0
    frame.drop = true;
    dropped = true;
end
end
