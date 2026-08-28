function distance = counterForwardDistance(previous, current)
%COUNTERFORWARDDISTANCE Modulo-256 forward distance between two alive counters.
%   Returns how many increments it takes to get from PREVIOUS to CURRENT
%   going forwards, i.e. MOD(CURRENT - PREVIOUS, 256). Wrap is therefore free:
%   255 -> 0 is distance 1, exactly like 40 -> 41.
%
%   Callers classify the result:
%     0          duplicate -- the sender is repeating itself, or the frame is
%                a bus-level retransmission. Never treat as liveness.
%     1..127     forward. 1 is the nominal step; 2..127 means frames were
%                lost, which is still forward progress.
%     128..255   backward / reordered. Read as a NEGATIVE distance of
%                256 - DISTANCE; reject.
%
%   The 127/128 split is the standard half-window convention: with a
%   modulo-256 counter there is no way to distinguish "254 frames lost" from
%   "2 frames late", so the receiver has to pick a boundary. Half the range
%   is the only choice that treats the two directions symmetrically.
%
%   Requiring EXACTLY +1 instead -- which is what the retainers did before --
%   looks stricter but is not safer: after a single lost frame the retained
%   counter can never line up again, so the path latches off permanently and
%   never recovers when CarMaker comes back. Phase-17 acceptance explicitly
%   requires controlled recovery after a CarMaker pause, so forward progress
%   is the correct rule and duplicates/reordering are still rejected.
if ~isa(previous, 'uint8') || ~isscalar(previous)
    error('inverterhil:InvalidCounter', 'previous must be a uint8 scalar.');
end
if ~isa(current, 'uint8') || ~isscalar(current)
    error('inverterhil:InvalidCounter', 'current must be a uint8 scalar.');
end
distance = uint8(mod(double(current) - double(previous), 256));
end
