function [ids, dlc] = lwsTxIds()
%LWSTXIDS The two Bosch LWS CAN IDs this HIL transmits, in model TX order.
%   [IDS, DLC] also returns each frame's declared data length: the standard
%   angle/speed frame (5 bytes) and the configuration command frame (2
%   bytes).
%
%   Split out of the former combined SENSORTXIDS so the LWS frame list lives
%   with the rest of the steering-sensor driver code. SENSORNORMALIZER's
%   callers concatenate this after IMUTXIDS ([IMUTXIDS(), LWSTXIDS()]) to
%   reconstruct the original five-ID transmit order; that concatenation
%   order is significant -- see IMUTXIDS/LWSTXIDS callers in TARGETSESSION
%   and BLANKTELEMETRY, which index TX rows and write-overrun flags
%   positionally against it.
%
%   The values are stated literally rather than read from LWSPROTOCOL, on
%   purpose: INVERTERHILGUI.BLANKTELEMETRY calls this on every GUI path,
%   including host tests that only put INVERTER_HIL itself on the path, and
%   this file being under VC_HIL/steering-sensor (added separately by
%   INVERTER_HIL_SETUP) must not create a circular or order-sensitive path
%   dependency.
%
%   TESTSENSORPROTOCOL asserts these agree with LWSPROTOCOL, so the
%   duplication cannot silently diverge.

ids = uint32([hex2dec('2B0'), ...   % Bosch LWS standard frame
              hex2dec('7C0')]);     % Bosch LWS configuration command
dlc = uint8([5, 2]);
end
