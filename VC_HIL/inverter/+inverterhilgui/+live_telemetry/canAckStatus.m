function status = canAckStatus(diagnostics, transmitting)
%CANACKSTATUS Derive CAN acknowledgement state from controller error flags.
%
%   STATUS = CANACKSTATUS(DIAGNOSTICS, TRANSMITTING) reports whether frames
%   leaving this node are being acknowledged by another node on the bus.
%
%   WHY THIS IS A REAL MEASUREMENT, NOT A GUESS. On CAN, acknowledgement is
%   mandatory at the link layer: a transmitter releases the ACK slot
%   recessive and any node that received the frame correctly pulls it
%   dominant. If NO node acknowledges, the transmitter raises an ACK error,
%   adds 8 to its transmit error counter, and retries the same frame. So an
%   unacknowledged transmitter reaches error-warning (counter 96) after
%   about 12 frames and bus-off (counter 256) after about 32 -- a fraction
%   of a second at this rig's 5 ms status cycle. Sustained transmission
%   with the controller reporting no bus-off and no error-warning is
%   therefore positive evidence that the frames ARE being acknowledged.
%
%   This is the same inference every CAN analyser makes. A CAN controller
%   does not expose the per-frame ACK bit to the application layer, so
%   error-counter state is the only acknowledgement evidence available to
%   any tool, including this one.
%
%   WHAT IT DOES NOT CLAIM. ACK proves only that SOME node on the bus
%   received the frame at the link layer. It does not identify which node,
%   and it says nothing about that node decoding the payload, agreeing with
%   it, or acting on it. A frame can be faithfully acknowledged and then
%   discarded by the receiver.
%
%   TRANSMITTING must be true for a positive result. An error-free
%   controller proves nothing on a silent bus: a frame that is never sent
%   is never unacknowledged either, so "no errors" alone would report a
%   dead transmitter as healthy. The caller supplies this from a genuine
%   observation that the transmit count advanced (see
%   INVERTER_HIL_APP.APPLYLIVETXFRAMES).
%
%   DIAGNOSTICS is the CAN diagnostics block of a telemetry snapshot (see
%   INVERTERHILGUI.BLANKTELEMETRY), whose BUSOFF and ERRORWARNING fields
%   are empty when unread.
%
%   STATUS fields:
%     TEXT          - short display string, dashes when unknown.
%     ACKNOWLEDGED  - true, false, or empty when unknown. Never defaults to
%                     true: an unread controller reports unknown, so a
%                     failed read can never present as a healthy bus.
%     KNOWN         - whether ACKNOWLEDGED carries a decision.

noData = inverterhilgui.live_telemetry.guiTheme().text.noData;
status = struct('text', noData, 'acknowledged', [], 'known', false);

if nargin < 2
    transmitting = false;
end
if ~isstruct(diagnostics) || ~isscalar(diagnostics)
    return;
end

busOff = flagOr(diagnostics, 'busOff');
errorWarning = flagOr(diagnostics, 'errorWarning');
% Both flags must be readable before any verdict: they are the two states
% an unacknowledged transmitter reaches, so deciding on one alone could
% report an unacknowledged bus as acknowledged.
if isempty(busOff) || isempty(errorWarning)
    return;
end

if busOff
    % The terminal state of a transmitter nobody is acknowledging.
    status.known = true;
    status.acknowledged = false;
    status.text = 'NOT ACKED (bus-off)';
    return;
end
if errorWarning
    % Error counters are elevated: some frames are not getting through
    % cleanly, which on a transmit path is what missing ACKs look like
    % before they escalate to bus-off.
    status.known = true;
    status.acknowledged = false;
    status.text = 'ACK ERRORS (error-warning)';
    return;
end

isTransmitting = (islogical(transmitting) || isnumeric(transmitting)) && ...
    isscalar(transmitting) && isreal(transmitting) && ...
    isfinite(double(transmitting)) && logical(transmitting);
if ~isTransmitting
    % Silent bus: no evidence either way, so this stays unknown rather
    % than crediting a stopped transmitter with a healthy acknowledgement.
    return;
end

status.known = true;
status.acknowledged = true;
status.text = 'ACK OK (no bus errors)';
end

function value = flagOr(item, field)
%FLAGOR A strictly binary flag, or empty when unset or malformed.
value = [];
if ~isfield(item, field)
    return;
end
candidate = item.(field);
if ~(islogical(candidate) || isnumeric(candidate)) || ~isscalar(candidate) || ...
        ~isreal(candidate) || ~isfinite(double(candidate)) || ...
        ~(double(candidate) == 0 || double(candidate) == 1)
    return;
end
value = logical(candidate);
end
