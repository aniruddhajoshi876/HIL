function payload = packLwsConfigPayload(command)
%PACKLWSCONFIGPAYLOAD Encode one Bosch LWS_Config command (0x7C0, DLC 2).
%   Each call encodes exactly one command. The ordered reset/zero procedure
%   is owned by the target-side sequencer in BUILD_INVERTER_HIL_MODEL; this
%   helper deliberately cannot queue two commands into one payload.
p = lwsProtocol();
if ~(isnumeric(command) || islogical(command)) || ~isscalar(command) || ...
        ~isreal(command) || ~isfinite(double(command))
    error('lws:InvalidConfigCommand', ...
        'LWS config command must be reset (0x05) or zero (0x03).');
end
command = uint8(command);
if ~(command == p.ccwResetCalibration || command == p.ccwZeroAngle)
    error('lws:InvalidConfigCommand', ...
        'LWS config command must be reset (0x05) or zero (0x03).');
end
payload = zeros(1, double(p.configDlc), 'uint8');
payload(1) = command;
end
