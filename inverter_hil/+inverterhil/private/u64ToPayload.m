function payload = u64ToPayload(raw)
%U64TOPAYLOAD Explicit little-endian uint64 to eight CAN bytes.

payload = zeros(1, 8, 'uint8');
for k = 1:8
    payload(k) = uint8(bitand(bitshift(raw, -8 * (k - 1)), uint64(255)));
end
end
