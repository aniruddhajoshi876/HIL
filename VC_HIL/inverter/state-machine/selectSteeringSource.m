function [angleDeg, speedDegPerSec, source, carMakerFresh] = ...
        selectSteeringSource(guiAngleDeg, carMakerSnapshot, enabled)
%SELECTSTEERINGSOURCE Choose the steering-wheel angle fed to the Bosch LWS
%   emulator and the shared vehicle state: CarMaker's 0x507 transport value
%   when enabled and fresh, otherwise the GUI steering dial.
%
%   SOURCE  0  GUI steering dial (CarMaker steering disabled)
%           1  CarMaker / Fanatec via the 0x507 transport frame
%           2  GUI steering dial, fallback because CarMaker steering is
%              enabled but not fresh (never received, stale, or a
%              frozen-but-repeating sender)
%
%   Stale policy: fall back to the GUI dial, NOT to neutral steering or an
%   injected LWS fault. This is a development-bench policy chosen to match
%   the pedal-demand path (PEDALFALLBACKZEROHOLD / the pedal source switch
%   both fall back to GUI control on loss of CAN authority) and the existing
%   "GUI dial fallback" the LWS emulator already relies on. The GUI fault-
%   injection controls remain the way to force neutral / faulted steering.
%
%   The returned ANGLEDEG is always saturated to the Bosch LWS +/-780 deg
%   range so a downstream range check cannot fail regardless of source.
if ~isscalar(guiAngleDeg) || ~isreal(guiAngleDeg)
    error('inverterhil:InvalidSteeringSelect', 'guiAngleDeg must be a real scalar.');
end
config = defaultVehicleStateConfig();
if nargin < 3 || isempty(enabled)
    enabled = config.carMakerSteeringEnabled;
end
enabled = logical(enabled);

limitDeg = 780;
guiAngleDeg = double(guiAngleDeg);
if ~isfinite(guiAngleDeg)
    guiAngleDeg = 0;
end
guiAngleDeg = min(limitDeg, max(-limitDeg, guiAngleDeg));

carMakerUsable = enabled && ...
    logical(carMakerSnapshot.fresh) && ...
    logical(carMakerSnapshot.hasValue) && ...
    isfinite(double(carMakerSnapshot.angleDeg)) && ...
    isfinite(double(carMakerSnapshot.speedDegPerSec)) && ...
    abs(double(carMakerSnapshot.angleDeg)) <= limitDeg;
carMakerFresh = enabled && logical(carMakerSnapshot.fresh);

if carMakerUsable
    angleDeg = min(limitDeg, max(-limitDeg, double(carMakerSnapshot.angleDeg)));
    speedDegPerSec = double(carMakerSnapshot.speedDegPerSec);
    source = uint8(1);
elseif enabled
    angleDeg = guiAngleDeg;
    speedDegPerSec = 0;
    source = uint8(2);
else
    angleDeg = guiAngleDeg;
    speedDegPerSec = 0;
    source = uint8(0);
end
end
