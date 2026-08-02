function value = decodeSigned(bits, scale, width)
%DECODESIGNED Two's-complement field to engineering units.
%   Inverse of ENCODESIGNED. Note the inverse is exact only for values that
%   ENCODESIGNED did not saturate or round: it quantises to SCALE, so a
%   round trip returns the nearest representable value, not the original
%   double. Saturation is not recoverable at all -- an out-of-range input
%   was clamped at pack time and the clamped value is what the wire carries.

counts = double(bitand(uint64(bits), uint64(2^width - 1)));
if counts >= 2^(width - 1)
    counts = counts - 2^width;
end
value = counts * scale;
end
