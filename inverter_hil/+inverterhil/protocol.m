function p = protocol()
%PROTOCOL Immutable Ephorus CAN contract used by the host-verifiable core.

p.controlIds = uint32([hex2dec('186'), hex2dec('196'), ...
    hex2dec('1A6'), hex2dec('1B6')]);
p.status3X3Ids = uint32([hex2dec('383'), hex2dec('393'), ...
    hex2dec('3A3'), hex2dec('3B3')]);
p.status3X5Ids = uint32([hex2dec('385'), hex2dec('395'), ...
    hex2dec('3A5'), hex2dec('3B5')]);
p.systemStatusId = uint32(hex2dec('400'));
p.statusCycleIds = uint32([hex2dec('383'), hex2dec('385'), ...
    hex2dec('393'), hex2dec('395'), hex2dec('3A3'), ...
    hex2dec('3A5'), hex2dec('3B3'), hex2dec('3B5'), ...
    hex2dec('400')]);

p.state.idle = uint8(0);
p.state.drive = uint8(1);
p.state.error = uint8(2);
p.state.configError = uint8(3);

p.torqueProfiles.provisional512.id = ...
    'ephorus3-v1.03-provisional-1over512';
p.torqueProfiles.provisional512.scaleNmPerCount = 1 / 512;
p.torqueProfiles.provisional512.verified = false;
p.torqueProfiles.vcu256.id = 'ephorus3-v1.03-candidate-1over256';
p.torqueProfiles.vcu256.scaleNmPerCount = 1 / 256;
p.torqueProfiles.vcu256.verified = false;

p.timing.commandTorqueZeroMs = uint32(50);
p.timing.commandErrorMs = uint32(500);
p.timing.controlPinTorqueZeroS = 100e-6;
p.timing.positionErrorS = 350e-6;
p.timing.resetFloorS = 500e-6;
p.timing.controlEnableErrorS = 0.200;
p.timing.recoveryS = 0.050;
end
