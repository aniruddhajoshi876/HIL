function p = protocol()
%PROTOCOL Immutable Ephorus CAN contract used by the host-verifiable core.

p.controlIds = uint32([hex2dec('186'), hex2dec('196'), ...
    hex2dec('1A6'), hex2dec('1B6')]);
p.status3X3Ids = uint32([hex2dec('383'), hex2dec('393'), ...
    hex2dec('3A3'), hex2dec('3B3')]);
p.status3X5Ids = uint32([hex2dec('385'), hex2dec('395'), ...
    hex2dec('3A5'), hex2dec('3B5')]);
p.systemStatusId = uint32(hex2dec('400'));
p.pedalDemandId = uint32(hex2dec('500'));
p.statusCycleIds = uint32([hex2dec('383'), hex2dec('385'), ...
    hex2dec('393'), hex2dec('395'), hex2dec('3A3'), ...
    hex2dec('3A5'), hex2dec('3B3'), hex2dec('3B5'), ...
    hex2dec('400')]);

p.state.idle = uint8(0);
p.state.drive = uint8(1);
p.state.error = uint8(2);
p.state.configError = uint8(3);

% RESOLVED 2026-08-02. Real VCU firmware evidence (MFE26-VC clone, branch
% 'todo'), cross-checked in three independent places, conclusively resolves
% the control-frame torque-limit scale to 1/256 Nm/count, not 1/512:
%   - Drivers/Device_Drivers/Inc/ephorus_driver.hpp:55
%     `#define EPHORUS_TORQUE_CTRL_SCALE_NM (1.0f / 256.0f)`, labeled at
%     lines 38-39 "Torque limit positive/negative (int16, 1/256 Nm)" for
%     exactly the 0x186/0x196/0x1A6/0x1B6 fields this profile scales.
%   - sil/models/ephorus_model.cpp:37-38: "Datasheet control scale is
%     1/256 Nm and the inverter limits input to approximately
%     [-64,+64)."
%   - sil/tests/conformance/ephorus_conformance.cpp:252,440 and
%     sil/tests/gui/can_decode_test.cpp:25: golden-value conformance tests
%     built around 1/256 (e.g. "limit positive +12.5 Nm (3200 x 1/256)").
% PROVISIONAL512 (1/512 Nm/count) was never a torque scale in the firmware
% at all: it is EPHORUS_TORQUE_CTRL_SCALE_NM's near neighbour
% switchingFreq_khz's scale (ephorus_driver.hpp:119,187, "1/512 kHz"), and
% this profile appears to have originated from confusing that unrelated
% switching-frequency field's scale with the torque-limit scale. It is kept
% below, still marked verified = false, only because +INVERTERHIL/
% VALIDATECALIBRATION.M's profile whitelist and existing tests
% (TestVcuCommandLoop's torquePosNm512/torqueNegNm512 comparisons,
% TestPlant's explicit-profile-switch test) exercise it as a second,
% known-not-the-answer profile; it must never become the default again.
p.torqueProfiles.provisional512.id = ...
    'ephorus3-v1.03-provisional-1over512';
p.torqueProfiles.provisional512.scaleNmPerCount = 1 / 512;
p.torqueProfiles.provisional512.verified = false;
p.torqueProfiles.vcu256.id = 'ephorus3-v1.03-candidate-1over256';
p.torqueProfiles.vcu256.scaleNmPerCount = 1 / 256;
p.torqueProfiles.vcu256.verified = true;

p.timing.commandTorqueZeroMs = uint32(50);
p.timing.commandErrorMs = uint32(500);
% CarMakerPedalDemand is a 1-ms retained input. 100 ms tolerates ordinary
% host jitter but fails safely long before an operator can mistake a dead
% command link for a held pedal.
p.timing.pedalDemandTimeoutMs = uint32(100);
p.timing.controlPinTorqueZeroS = 100e-6;
p.timing.positionErrorS = 350e-6;
p.timing.resetFloorS = 500e-6;
p.timing.controlEnableErrorS = 0.200;
p.timing.recoveryS = 0.050;
end
