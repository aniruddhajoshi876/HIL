function c = config()
%CONFIG R2024b virtual-VCU bench contract.
%   The virtual VCU is deliberately separated from the inverter boundary:
%   IO183 module 3 and IO614 connector A (CAN channel 2).
c.moduleId = 3;
c.canChannel = 2;
c.canPort = 'A';
c.canBitrate = 1e6;
c.canDlc = uint8(8);
c.controlIds = uint32(hex2dec({'186','196','1A6','1B6'}));
c.statusIds = uint32(hex2dec({'383','385','393','395','3A3','3A5','3B3','3B5','400'}));
c.analogChannels = uint8(1:4);
c.digitalChannels = uint8(1:8);
c.adcFullScale = 65535;
c.io183FullScaleV = 5.0;
c.throttleRestRaw = [30100 63600];
c.throttlePressedRaw = [20900 46500];
c.brakeRestRaw = [9025 8280];
c.brakePressedRaw = [31800 31800];
c.pedalCanId = uint32(501);
end
