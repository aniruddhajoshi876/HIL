function field = getField(raw, shift, width)
%GETFIELD Extract one bit field from a uint64 payload.
%   Exact inverse of PUTFIELD.

field = bitand(bitshift(raw, -shift), uint64(2^width - 1));
end
