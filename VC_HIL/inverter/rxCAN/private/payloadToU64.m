function raw = payloadToU64(payload)
%PAYLOADTOU64 Explicit little-endian eight CAN bytes to uint64.
%   Exact inverse of U64TOPAYLOAD.

raw = uint64(0);
for k = 1:8
    raw = bitor(raw, bitshift(uint64(payload(k)), 8 * (k - 1)));
end
end
