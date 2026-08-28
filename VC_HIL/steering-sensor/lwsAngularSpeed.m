function speedDegPerS = lwsAngularSpeed(angleDeg, previousAngleDeg, samplePeriodS)
%LWSANGULARSPEED Bosch LWS_SPEED from two successive steering-angle samples.
%   LWS_SPEED is the STEERING WHEEL angular speed: the Bosch F02U.V02.894-01
%   datasheet defines it as "Angular speed", 0 to 1016 deg/s at 4 deg/s
%   resolution -- the rate of change of LWS_ANGLE, measured by the same
%   column-mounted sensor.
%
%   It is NOT the vehicle yaw rate. Yaw rate is a different physical quantity,
%   measured by a different sensor, and already on the bus as the MTi
%   rate-of-turn frame 0x032. They are numerically unrelated: a stationary car
%   with the wheel being spun has large LWS_SPEED and zero yaw rate, and a car
%   in a steady-state skidpad circle has zero LWS_SPEED and large yaw rate.
%   Feeding yaw rate into this field would make the VCU's steering-rate
%   plausibility checks pass on a signal that never moves with the wheel.
%   This function exists so that rule is expressed once, in a host-testable
%   place, rather than inline in a generated Stateflow chart.
%
%   The field is UNSIGNED, so the MAGNITUDE of the rate is what goes on the
%   wire; direction is recoverable from successive LWS_ANGLE values.
%
%   The result is clamped to the encoder's live range. 0xFF is reserved as the
%   invalid sentinel and must never be produced by a live reading, so a fast
%   hand sweep clamps rather than range-erroring PACKLWSPAYLOAD.
if nargin < 3 || isempty(samplePeriodS)
    contractPeriod = lwsProtocol();
    samplePeriodS = contractPeriod.updatePeriodS;
end
if ~isscalar(samplePeriodS) || ~isfinite(double(samplePeriodS)) || ...
        double(samplePeriodS) <= 0
    error('lws:InvalidSamplePeriod', ...
        'samplePeriodS must be a positive finite scalar.');
end
contract = lwsProtocol();
delta = double(angleDeg) - double(previousAngleDeg);
if ~isfinite(delta)
    speedDegPerS = 0;
    return;
end
speedDegPerS = min(contract.maximumSpeedDegPerS, ...
    abs(delta) / double(samplePeriodS));
end
