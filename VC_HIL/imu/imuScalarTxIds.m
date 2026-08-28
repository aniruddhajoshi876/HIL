function [ids, dlc] = imuScalarTxIds()
%IMUSCALARTXIDS The four MTi-680G scalar-group CAN IDs this HIL transmits.
%   [IDS, DLC] also returns each frame's declared data length.
%
%   The MTi appends these four single-integer messages to every inertial
%   group (see STEPIMUSIMULATION's SCALARFRAMES output and TESTSENSOR-
%   CONCURRENCY): groupCounter (0x006, uint16, 2 bytes), sampleTime
%   (0x005, uint32, 4 bytes), statusWord (0x011, uint32, 4 bytes) and
%   errorCode (0x001, uint8, 1 byte), in that transmit order.
%
%   Kept as a SEPARATE list from IMUTXIDS rather than folded into it: the
%   deployed model, BLANKTELEMETRY and TARGETSESSION concatenate the sensor
%   frames as [IMUTXIDS(), LWSTXIDS(), IMUSCALARTXIDS()], appending the
%   scalar frames AFTER the LWS frames so the combined indices 1-5
%   (MTi accel/rate/velocity, LWS standard, LWS config) that those callers
%   slice positionally do not shift. Folding the scalar IDs into IMUTXIDS
%   would move the LWS frames to indices 8-9 and break every positional
%   consumer.
%
%   Values are stated literally, matching IMUTXIDS/LWSTXIDS, so
%   INVERTERHILGUI.BLANKTELEMETRY does not have to put IMU/ on the path.
%   TESTSENSORPROTOCOL asserts these agree with IMUPROTOCOL.

ids = uint32([hex2dec('006'), ...   % MTi-680G group counter (uint16)
              hex2dec('005'), ...   % MTi-680G sample time, microseconds (uint32)
              hex2dec('011'), ...   % MTi-680G status word (uint32)
              hex2dec('001')]);     % MTi-680G error code (uint8)
dlc = uint8([2, 4, 4, 1]);
end
