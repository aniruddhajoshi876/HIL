function values = decodeMti680Frame(frame, contract)
%DECODEMTI680FRAME Decode an MTi three-axis signed-int16 output frame.
if nargin < 2 || isempty(contract)
    contract = imuProtocol();
end
if ~isstruct(frame) || ~isfield(frame, 'id') || ~isfield(frame, 'payload')
    error('mti680:InvalidFrame', 'Frame must contain id and payload.');
end
names = {'acceleration', 'rateOfTurn', 'eulerAngles', 'velocityXyz'};
kind = '';
for index = 1:numel(names)
    if uint32(frame.id) == contract.(names{index}).id
        kind = names{index};
        break;
    end
end
if isempty(kind)
    error('mti680:UnknownId', 'Unknown MTi CAN ID 0x%03X.', uint32(frame.id));
end
item = contract.(kind);
payload = uint8(frame.payload(:).');
if numel(payload) < double(item.dlc)
    error('mti680:InvalidDlc', 'MTi payload is shorter than its contract DLC.');
end
values = zeros(1, 3);
for index = 1:3
    offset = 2 * index - 1;
    raw = bitor(bitshift(uint16(payload(offset)), 8), ...
        uint16(payload(offset + 1)));
    signed = double(raw);
    if signed >= 32768
        signed = signed - 65536;
    end
    values(index) = signed * item.scale;
end
end
