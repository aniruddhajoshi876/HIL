function payload = packMti680Payload(kind, values)
%PACKMTI680PAYLOAD Return the eight-byte payload for a CAN sensor frame.
protocol = imuProtocol();
switch lower(char(kind))
    case 'acceleration'
        scale = protocol.acceleration.scale;
    case 'rateofturn'
        scale = protocol.rateOfTurn.scale;
    otherwise
        error('mti680:UnsupportedPayload', 'Unsupported MTi payload kind.');
end
rawCounts = round(double(values(:)) ./ scale);
if numel(rawCounts) ~= 3 || any(rawCounts < double(intmin('int16'))) || ...
        any(rawCounts > double(intmax('int16')))
    error('mti680:PayloadRange', 'MTi payload requires three int16 values.');
end
counts = int16(rawCounts);
payload = zeros(1, 8, 'uint8');
for index = 1:3
    raw = typecast(counts(index), 'uint8');
    payload(2 * index - 1:2 * index) = raw([2 1]);
end
end
