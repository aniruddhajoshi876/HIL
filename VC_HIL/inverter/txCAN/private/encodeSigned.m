function bits = encodeSigned(value, scale, width, name)
%ENCODESIGNED Saturating engineering-unit to two's-complement conversion.

value = finiteScalar(value, name);
counts = round(value / scale);
minimum = -(2^(width - 1));
maximum = 2^(width - 1) - 1;
counts = min(max(counts, minimum), maximum);
bits = uint64(mod(counts, 2^width));
end
