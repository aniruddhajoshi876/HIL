function [angleDeg, source, steeringValid, carMakerFresh] = ...
        selectSteeringSource(guiAngleDeg, carMakerSnapshot, mode)
%SELECTSTEERINGSOURCE Choose the steering-wheel angle fed to the Bosch LWS
%   emulator and the shared vehicle state. There is no implicit source: the
%   caller states which one it wants, and the answer carries a validity flag.
%
%   MODE (DEFAULTVEHICLESTATECONFIG.STEERINGSOURCEMODE when omitted)
%     0  MANUAL   the GUI steering dial. Must be selected deliberately. This
%                 is the shipping default and the documented rollback.
%     1  CARMAKER the Fanatec wheel, via CarMaker Steer.WhlAng and the 0x507
%                 CarMakerSteeringTruth transport frame.
%
%   SOURCE (what the frame on the wire actually came from)
%     0  MANUAL      GUI dial, manual mode. STEERINGVALID true.
%     1  CARMAKER    CarMaker / Fanatec truth, fresh. STEERINGVALID true.
%     2  UNAVAILABLE CarMaker mode selected but the truth is not usable --
%                    never received, stale, frozen-but-repeating counter, or
%                    non-finite. STEERINGVALID FALSE. ANGLEDEG is zero and
%                    carries no meaning; the caller must not encode it as a
%                    measurement.
%
%   STALE POLICY -- deliberate, and different from the pedal path.
%   When CarMaker mode is selected and the truth goes stale, this does NOT
%   fall back to the GUI dial. Silently swapping in a different physical
%   source would make the VCU see a plausible, well-formed steering angle
%   that no longer corresponds to the wheel the driver is holding, and
%   nothing on the wire would say so. That is the one failure a HIL bench
%   must not be able to produce.
%
%   Instead the selector reports STEERINGVALID false and the LWS emulator
%   encodes the Bosch failure state -- LWS_ANGLE 0x7FFF, LWS_SPEED 0xFF,
%   status TRIM=1 OK=0 CAL=0 -- at the normal 100 Hz. The frame keeps
%   flowing, so the VCU distinguishes "sensor reports itself broken" from
%   "bus went quiet", and the VCU's existing plausibility handling sees a
%   state the datasheet defines. Suppressing 0x2B0 entirely was the
%   alternative; it stays available as the existing GUI dropout injection,
%   which is the right tool for testing bus silence specifically.
%
%   Getting the GUI dial back is a mode change to MANUAL, which is explicit,
%   visible in the telemetry, and auditable.
if ~isscalar(guiAngleDeg) || ~isreal(guiAngleDeg)
    error('inverterhil:InvalidSteeringSelect', 'guiAngleDeg must be a real scalar.');
end
config = defaultVehicleStateConfig();
if nargin < 3 || isempty(mode)
    mode = config.steeringSourceMode;
end
mode = uint8(mode);

limitDeg = 780;
guiAngleDeg = double(guiAngleDeg);
if ~isfinite(guiAngleDeg)
    guiAngleDeg = 0;
end
guiAngleDeg = min(limitDeg, max(-limitDeg, guiAngleDeg));

carMakerUsable = logical(carMakerSnapshot.fresh) && ...
    logical(carMakerSnapshot.hasValue) && ...
    isfinite(double(carMakerSnapshot.angleDeg)) && ...
    abs(double(carMakerSnapshot.angleDeg)) <= limitDeg;
carMakerFresh = mode == uint8(1) && logical(carMakerSnapshot.fresh);

if mode == uint8(1)
    if carMakerUsable
        % Radians on the wire, degrees from here on: this is the single
        % rad -> deg boundary, applied once at decode and carried through
        % the retainer, so no consumer re-derives 180/pi.
        angleDeg = min(limitDeg, max(-limitDeg, double(carMakerSnapshot.angleDeg)));
        source = uint8(1);
        steeringValid = true;
    else
        angleDeg = 0;
        source = uint8(2);
        steeringValid = false;
    end
else
    angleDeg = guiAngleDeg;
    source = uint8(0);
    steeringValid = true;
end
end
