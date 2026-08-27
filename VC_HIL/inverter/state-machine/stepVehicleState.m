function [next, imu] = stepVehicleState(state, plantOutput, steeringAngleDeg, dt)
%STEPVEHICLESTATE Advance the shared state used by the virtual sensors.
%   The state is driven by the independent inverter plant output and the
%   steering stimulus.  No VCU implementation is called or duplicated.
%   State layout: [speedMps yawRateRadPerS distanceM yawAngleRad].

if ~isequal(size(state), [1 4])
    error('inverterhil:InvalidVehicleState', 'state must be a 1x4 row.');
end
if ~isscalar(dt) || ~isfinite(dt) || dt <= 0
    error('inverterhil:InvalidVehicleState', 'dt must be positive and finite.');
end

cfg = defaultVehicleStateConfig();
driveTorqueNm = sum(double(plantOutput.torqueActualNm));
longitudinalAccelerationMps2 = driveTorqueNm / ...
    max(cfg.massKg * cfg.wheelRadiusM, eps);
speedMps = state(1) + dt * longitudinalAccelerationMps2;
speedMps = max(speedMps, 0);
steeringRad = deg2rad(double(steeringAngleDeg)) * cfg.steeringGain;
wheelbaseM = cfg.frontAxleDistanceM + cfg.rearAxleDistanceM;
yawRateRadPerS = speedMps * tan(steeringRad) / max(wheelbaseM, eps);
yawAccelerationRadPerS2 = (yawRateRadPerS - state(2)) / dt;
next = [speedMps, yawRateRadPerS, ...
    state(3) + dt * speedMps, state(4) + dt * yawRateRadPerS];
% Observation vector handed to the sensor encoders, in the VEHICLE frame
% (X forward, Y left, Z up). mountingTransform / the model's payload encoder
% rotate it into the sensor frame at the CAN boundary.
%   1:3 acceleration [ax ay az]     -> MTi 0x034
%   4:6 rate of turn [wx wy wz]     -> MTi 0x032
%   7:9 velocity     [vx vy vz]     -> MTi 0x076
% Velocity is present because the MFE26-VC firmware decodes 0x076 and its
% controls model gates live inputs on it; without these fields that path
% receives nothing. Lateral and vertical velocity are a genuine zero here --
% this is a single-track longitudinal model with no sideslip state, not a
% measurement that was dropped.
%
% NOTE: yaw rate is published at index 6 (the vehicle Z axis). Resolved: the
% MTi mounting is now known (180 deg about the vehicle Z / yaw axis, see
% imuProtocol.mounting). Yaw is a rotation about vehicle vertical, so it
% belongs on Z, where a Z-rotation mount leaves it sign-invariant; the
% roll-rate and pitch-rate on X/Y negate. The earlier "yaw on index 5 (Y)"
% convention was non-physical and interacted with the mounting transform to
% invert the yaw-rate sign.
imu = [longitudinalAccelerationMps2, 0, 0, ...
    0, 0, yawRateRadPerS, ...
    speedMps, 0, 0];
if ~isfinite(yawAccelerationRadPerS2) %#ok<NASGU>
    error('inverterhil:InvalidVehicleState', 'Vehicle state became non-finite.');
end
end
