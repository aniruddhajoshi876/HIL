function ids = sensorTxIds()
%SENSORTXIDS The synchronized sensor CAN IDs, in model transmit order.
%   Single source of truth for the four sensor frames this HIL transmits, so
%   the model builder, the GUI TX table and the CAN write diagnostics cannot
%   drift apart. The ORDER is significant: INVERTERHILGUI.APPLYLIVETXFRAMES
%   indexes payload rows positionally, and TARGETSESSION reads one overrun
%   flag per CAN Write block in this same sequence.
%
%   The values are stated literally rather than read from IMUPROTOCOL and
%   LWSPROTOCOL on purpose. INVERTERHILGUI.BLANKTELEMETRY calls this on every
%   GUI path, including host tests that only put INVERTER_HIL itself on the
%   path -- IMU and STEERING-SENSOR are separate folders added by
%   INVERTER_HIL_SETUP, so reaching into them here would make the whole GUI
%   depend on a path those tests never set up.
%
%   TESTSENSORPROTOCOL asserts these agree with IMUPROTOCOL/LWSPROTOCOL, so
%   the duplication cannot silently diverge.

ids = uint32([hex2dec('034'), ...   % MTi-680G acceleration
              hex2dec('032'), ...   % MTi-680G rate of turn
              hex2dec('076'), ...   % MTi-680G velocity XYZ (assumption A3)
              hex2dec('2B0')]);     % Bosch LWS standard frame
end
