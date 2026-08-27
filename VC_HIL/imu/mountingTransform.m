function state = mountingTransform(state, contract)
%MOUNTINGTRANSFORM Map shared vehicle-frame quantities into the MTi sensor frame.
%   STATE = MOUNTINGTRANSFORM(STATE) applies the sensor<-vehicle transform for
%   the physical MTi-680G mounting (rotated 180 deg about the vehicle vertical
%   Z / yaw axis; see imuProtocol.mounting) to every field of STATE it
%   recognises, and returns STATE with those fields replaced by their
%   sensor-frame values. Unrecognised fields pass through untouched.
%
%   Recognised fields:
%     accelerationMps2, rateOfTurnRadPerS, velocityMps  -- 1x3 vectors, each
%         axis multiplied by imuProtocol.mounting.axisSign ([-1 -1 1]: X and Y
%         negate, Z keeps sign).
%     eulerAnglesDeg -- 1x3 [roll pitch yaw]. A 180 deg rotation about Z
%         negates roll and pitch (the angles about the axes perpendicular to
%         Z) and offsets yaw by 180 deg, wrapped to (-180, 180].
%
%   This is the single place the mounting is encoded. Change
%   imuProtocol.mounting to retune it; this function needs no edit.
if nargin < 2 || isempty(contract)
    contract = imuProtocol();
end
m = contract.mounting;
axisSign = double(m.axisSign(:).');

vectorFields = {'accelerationMps2', 'rateOfTurnRadPerS', 'velocityMps'};
for index = 1:numel(vectorFields)
    name = vectorFields{index};
    if isfield(state, name)
        v = double(state.(name)(:).');
        if numel(v) == 3
            state.(name) = v .* axisSign;
        end
    end
end

if isfield(state, 'eulerAnglesDeg')
    e = double(state.eulerAnglesDeg(:).');
    if numel(e) == 3
        roll = m.eulerRollSign * e(1);
        pitch = m.eulerPitchSign * e(2);
        yaw = wrapDeg(e(3) + m.eulerYawOffsetDeg);
        state.eulerAnglesDeg = [roll, pitch, yaw];
    end
end
end

function angle = wrapDeg(angle)
%WRAPDEG Wrap an angle in degrees to the half-open interval (-180, 180].
angle = angle - 360 * floor((angle + 180) / 360);
if angle == -180
    angle = 180;
end
end
