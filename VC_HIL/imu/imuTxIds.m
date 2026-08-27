function [ids, dlc] = imuTxIds()
%IMUTXIDS The three MTi-680G CAN IDs this HIL transmits, in model TX order.
%   [IDS, DLC] also returns each frame's declared data length.
%
%   Split out of the former combined SENSORTXIDS so the MTi/IMU frame list
%   lives with the rest of the IMU driver code. SENSORNORMALIZER's callers
%   concatenate this with LWSTXIDS ([IMUTXIDS(), LWSTXIDS()]) to reconstruct
%   the original five-ID transmit order; that concatenation order is
%   significant -- see IMUTXIDS/LWSTXIDS callers in TARGETSESSION and
%   BLANKTELEMETRY, which index TX rows and write-overrun flags positionally
%   against it.
%
%   The values are stated literally rather than read from IMUPROTOCOL, on
%   purpose: INVERTERHILGUI.BLANKTELEMETRY calls this on every GUI path,
%   including host tests that only put INVERTER_HIL itself on the path, and
%   this file being under VC_HIL/imu (added separately by INVERTER_HIL_SETUP)
%   must not create a circular or order-sensitive path dependency.
%
%   TESTSENSORPROTOCOL asserts these agree with IMUPROTOCOL, so the
%   duplication cannot silently diverge.

ids = uint32([hex2dec('034'), ...   % MTi-680G acceleration
              hex2dec('032'), ...   % MTi-680G rate of turn
              hex2dec('076')]);     % MTi-680G velocity XYZ (assumption A3)
dlc = uint8([6, 6, 6]);
end
