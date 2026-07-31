function next = sequenceCommand(current)
%SEQUENCECOMMAND Wrap-safe uint32 increment for a momentary target command.
%
%   Plan 7.4 requires momentary commands (precharge, main button) to be
%   generated on target from a sequence counter rather than from a host-timed
%   pulse. The host only ever increments the counter; the model turns each
%   change into a deterministic pulse. The counter is monotonic modulo 2^32
%   and wraps from 4294967295 back to 0 without saturating.

if ~(isnumeric(current) || islogical(current)) || ~isscalar(current) || ...
        ~isreal(current) || ~isfinite(double(current))
    error('inverterhilgui:InvalidSequenceCounter', ...
        'Sequence counter must be a real finite numeric scalar.');
end
value = double(current);
if value < 0 || value > 4294967295 || value ~= floor(value)
    error('inverterhilgui:InvalidSequenceCounter', ...
        'Sequence counter must be a whole number within uint32 range.');
end
if value == 4294967295
    next = uint32(0);
else
    next = uint32(value + 1);
end
end
