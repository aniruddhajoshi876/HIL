function bits = encodeUnsigned(value, scale, width, name)
%ENCODEUNSIGNED Saturating engineering-unit to unsigned field conversion.

value = finiteScalar(value, name);
counts = round(value / scale);
counts = min(max(counts, 0), 2^width - 1);
bits = uint64(counts);
end
