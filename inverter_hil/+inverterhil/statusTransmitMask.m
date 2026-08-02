function keep = statusTransmitMask(dropStatusMask)
%STATUSTRANSMITMASK Per-frame transmit gate for the nine-frame status cycle.
%
%   KEEP = STATUSTRANSMITMASK(DROPSTATUSMASK) returns a 1x9 logical vector,
%   one entry per INVERTERHIL.PROTOCOL().STATUSCYCLEIDS entry in that same
%   order (0x383, 0x385, 0x393, 0x395, 0x3A3, 0x3A5, 0x3B3, 0x3B5, 0x400).
%   KEEP(K) is false exactly when bit (K-1) of DROPSTATUSMASK is set, i.e.
%   the operator has masked that frame for CAN fault injection.
%
%   DROPSTATUSMASK is the GUI-owned hil_cmd_can_drop_status_mask tunable: a
%   uint16 covering all nine frames one bit each; the remaining seven bits
%   are unused.
%
%   This function only computes the gate. Genuine wire-level absence (not a
%   zeroed payload) requires the caller to route KEEP into something that
%   stops transmission outright -- in the Simulink model, each IO614 CAN
%   Write block's own "Tx Control" input (its enableInput mask parameter,
%   "Show Transmission Control Input"), one per frame; see
%   BUILD_INVERTER_HIL_MODEL's ADDHARDWAREBOUNDARY. A false Tx Control input
%   means that CAN Write block does not transmit that tick at all, which is
%   genuinely absent traffic rather than an all-zero payload (an all-zero
%   payload is itself a status frame a healthy Idle channel can legitimately
%   send, so zeroing would be indistinguishable from real content).

if ~isnumeric(dropStatusMask) || ~isscalar(dropStatusMask) || ...
        ~isreal(dropStatusMask) || ~isfinite(double(dropStatusMask)) || ...
        double(dropStatusMask) < 0 || double(dropStatusMask) > 65535
    error('inverterhil:InvalidDropMask', ...
        'dropStatusMask must be a uint16-range scalar.');
end
mask = uint16(dropStatusMask);
keep = true(1, 9);
for index = 1:9
    keep(index) = bitget(mask, index) == 0;
end
end
