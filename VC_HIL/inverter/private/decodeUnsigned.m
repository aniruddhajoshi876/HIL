function value = decodeUnsigned(bits, scale, width)
%DECODEUNSIGNED Unsigned field to engineering units.
%   Inverse of ENCODEUNSIGNED, with the same quantisation and saturation
%   caveats noted in DECODESIGNED.

counts = double(bitand(uint64(bits), uint64(2^width - 1)));
value = counts * scale;
end
