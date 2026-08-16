function p = imuProtocol()
%PROTOCOL Independent MTi-680G CAN output contract.
%   Contract source: Xsens MT CAN Protocol Documentation, MT1604P,
%   Revision A, 16 Sept 2019 (references/sensors/datasheets/
%   MTCANProtocolDocumentation.pdf). There is no 2020.A revision of this
%   document; the earlier citation was wrong. This file is deliberately
%   independent of VCU source.

p.source = 'Xsens MT CAN Protocol Documentation MT1604P Rev A, 16 Sept 2019';
p.acceleration = message(uint32(hex2dec('034')), uint8(6), 2^-8, 'm/s^2');
p.rateOfTurn = message(uint32(hex2dec('032')), uint8(6), 2^-9, 'rad/s');
p.eulerAngles = message(uint32(hex2dec('022')), uint8(6), 2^-7, 'deg');
p.groupCounter = struct('id', uint32(hex2dec('006')), 'dlc', uint8(2));
p.sampleTime = struct('id', uint32(hex2dec('005')), 'dlc', uint8(4));

% The MT CAN tables define signed integer fields and offsets. Keep byte order
% explicit at this boundary and cover it with independent golden vectors.
p.byteOrder = 'big';
end

function item = message(id, dlc, scale, unit)
item = struct('id', id, 'dlc', dlc, 'scale', scale, 'unit', unit, ...
    'signed', true, 'byteOrder', 'big');
end
