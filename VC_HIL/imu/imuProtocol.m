function p = imuProtocol()
%PROTOCOL Independent MTi-680G CAN output contract.
%   Contract source: Xsens MT CAN Protocol Documentation, document MT1604P,
%   Revision A, 16 Sept 2019. This file is deliberately independent of VCU
%   source. Verified against the primary document and against the MFE26-VC
%   firmware decoder; see references/sensors/mti680_can_contract.md and
%   references/sensors/imu_contract_delta.md.

p.source = ['Xsens MT CAN Protocol Documentation, document MT1604P, ' ...
    'Revision A, 16 Sept 2019'];

% Vector messages: three int16 fields at byte offsets 0, 2, 4 (MT1604P
% section 6; the Offset column misprints the third field as 3 -- Total size 6
% makes 4 the only consistent value).
% rangeMax is the documented physical Range column, which is NARROWER than the
% int16 encoding limit. The MFE26 VCU drops any frame with an axis outside it,
% so a simulator that only saturates at int16 silently emits frames the VCU
% throws away. rangeMax is per axis: a scalar applies to all three, a 1x3
% vector bounds each axis independently. EulerAngles is the only per-axis
% case -- MT1604P section 6.3.2 specifies roll +/-180, PITCH +/-90, yaw +/-180.
p.acceleration = message(uint32(hex2dec('034')), uint8(6), 2^-8, 'm/s^2', 100);
p.rateOfTurn   = message(uint32(hex2dec('032')), uint8(6), 2^-9, 'rad/s', 35);
p.eulerAngles  = message(uint32(hex2dec('022')), uint8(6), 2^-7, 'deg', [180 90 180]);
% ASSUMPTION A3: MT1604P Table 4 lists 0x75 for VelocityXYZ while section
% 6.8.3 lists 0x076. 0x076 is adopted because that is what the MFE26-VC
% firmware decodes. Settle it against a real sensor before trusting it.
p.velocityXyz  = message(uint32(hex2dec('076')), uint8(6), 2^-6, 'm/s', 500);

% Scalar messages. Unsigned, unlike every vector message above.
p.groupCounter = scalarMessage(uint32(hex2dec('006')), uint8(2), 'uint16');
p.sampleTime   = scalarMessage(uint32(hex2dec('005')), uint8(4), 'uint32');
p.statusWord   = scalarMessage(uint32(hex2dec('011')), uint8(4), 'uint32');
p.errorCode    = scalarMessage(uint32(hex2dec('001')), uint8(1), 'uint8');

% Messages the MFE26-VC firmware actually decodes, as of branch `controls`.
% XCDI_EulerAngles (0x022) is a real MTi message but the VCU has no decoder
% for it; frames land in the unknown-ID counter. Keep it in the contract,
% default its scheduler rate to zero.
p.decodedByVcu = {'acceleration', 'rateOfTurn', 'velocityXyz'};

% MT1604P specifies NO per-message data-invalid sentinel for the MTi. Health
% is signalled out of band by statusWord (0x011) and errorCode (0x001). Do
% not carry Bosch LWS sentinel habits (0x7FFF / 0xFF) onto this bus.
p.hasDataInvalidSentinel = false;

% Nominal "all good" health values the simulator emits when no fault is
% injected. StatusWord bits per MT Low Level Communication Protocol
% Documentation Table 27: bit 0 Selftest passed, bit 1 Filter Valid. Bit 2
% (GNSS fix) and the filter-mode bits (23:25) are left 0 -- the HIL plant
% does not model GNSS reception, so a fix is not asserted. errorCode 0x00 is
% "no error" (MT1604P section 6.1.1 only defines 0x01 CEI_OutputBufferOverflow).
p.nominalStatusWord = uint32(3);   % bit 0 Selftest | bit 1 Filter Valid
p.nominalErrorCode  = uint8(0);

% MOUNTING ORIENTATION. The physical MTi-680G is mounted rotated 180 deg
% about the vehicle vertical (Z / yaw) axis: sensor +X points vehicle
% REARWARD, sensor +Y points vehicle RIGHTWARD, sensor +Z stays vehicle up.
% Vehicle frame is X forward, Y left, Z up. mountingTransform.m is the ONE
% place this is applied when shared vehicle state becomes sensor-frame CAN
% payloads, so the VCU sees what the real backwards sensor emits.
%   Vectors (acceleration, rate of turn, velocity XYZ): multiply each axis by
%   axisSign -- X and Y negate, Z keeps sign.
%   Euler angles: a 180 deg rotation about Z negates the two angles about the
%   axes perpendicular to Z (roll about X, pitch about Y) and offsets the
%   angle about Z (yaw) by 180 deg, then wraps to (-180, 180].
% If the mounting is ever corrected to align with the vehicle frame, set
% axisSign = [1 1 1], eulerRollSign = 1, eulerPitchSign = 1, and
% eulerYawOffsetDeg = 0 -- nothing else changes.
p.mounting = struct( ...
    'description', '180 deg about vehicle Z (yaw); sensor faces rearward', ...
    'axisSign', [-1 -1 1], ...
    'eulerRollSign', -1, 'eulerPitchSign', -1, 'eulerYawOffsetDeg', 180);

% Output rate is a SIMULATOR CHOICE. MT1604P gives an 11-bit per-message
% frequency field and no default. Mirror whatever the real MTi-680G is
% programmed to.
p.defaultOutputRateHz = struct('acceleration', 100, 'rateOfTurn', 100, ...
    'eulerAngles', 0, 'velocityXyz', 100);

% Bus configuration the MFE26 VCU expects (FDCAN1). The MTi's factory default
% is 250 kbit/s with CAN output DISABLED; the sensor must be reconfigured to
% baud code 10 (0x0A) before it will talk to this VCU.
p.bitrateBitsPerSecond = 500000;
p.identifierType = 'standard';   % 11-bit; MT1604P also supports 29-bit

% ASSUMPTION A1: MT1604P does NOT state the byte order of CAN output
% payloads. Big-endian is inherited from MT Low Level Communication Protocol
% Documentation section 5.1.1 ("All binary data communication is done in
% big-endian format") and is independently assumed by the MFE26-VC decoder.
% Because BOTH sides assume it, a passing HIL test proves nothing about
% which order the real sensor uses. It is UNPROVEN against hardware. Golden
% vector edge_little_endian_confusion_probe exists to settle it.
p.byteOrder = 'big';
p.byteOrderVerified = false;
end

function item = message(id, dlc, scale, unit, rangeMax)
item = struct('id', id, 'dlc', dlc, 'scale', scale, 'unit', unit, ...
    'signed', true, 'byteOrder', 'big', 'fieldCount', uint8(3), ...
    'fieldOffsets', uint8([0 2 4]), 'rangeMax', rangeMax);
end

function item = scalarMessage(id, dlc, format)
item = struct('id', id, 'dlc', dlc, 'format', format, 'signed', false, ...
    'byteOrder', 'big', 'fieldCount', uint8(1));
end
