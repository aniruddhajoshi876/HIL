function raw = putField(raw, field, shift, width)
%PUTFIELD Insert an already-narrowed field into a uint64 payload.

mask = bitshift(uint64(2^width - 1), shift);
raw = bitor(bitand(raw, bitcmp(mask, 'uint64')), ...
    bitshift(bitand(uint64(field), uint64(2^width - 1)), shift));
end
