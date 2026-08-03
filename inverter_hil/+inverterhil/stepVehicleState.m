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

cfg = inverterhil.defaultVehicleStateConfig();
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
imu = [longitudinalAccelerationMps2, 0, 0, ...
    0, yawRateRadPerS, 0];
if ~isfinite(yawAccelerationRadPerS2) %#ok<NASGU>
    error('inverterhil:InvalidVehicleState', 'Vehicle state became non-finite.');
end
end
