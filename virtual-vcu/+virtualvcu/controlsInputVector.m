function inputs = controlsInputVector(throttleFraction, wheelSpeedRadS)
%CONTROLSINPUTVECTOR Build the exact 32-element generated-model input order.
if nargin < 1, throttleFraction = 0; end
if nargin < 2, wheelSpeedRadS = zeros(1,4); end
wheelSpeedRadS = double(wheelSpeedRadS(:)');
if numel(wheelSpeedRadS) ~= 4
    error('virtualvcu:WheelSpeedVector', 'Expected [FL FR RL RR] wheel speeds.');
end
inputs = zeros(32,1);
inputs(1) = 0;                 % ResetSignal
inputs(2) = 0;                 % vehicle_speed: no physical IMU sample
inputs(3) = 0.5;               % min_speed
inputs(4) = 80000;             % P_max
inputs(5:6) = 1;               % lamda1, lamda2
inputs(7) = 0.1;               % lamda3
inputs(8:11) = wheelSpeedRadS; % om_fl, om_fr, om_rl, om_rr
inputs(12) = 0.99;             % efficiency
inputs(13) = 100;              % N_long
inputs(14:17) = 0;             % ax, SWA, vy, yaw_rate
inputs(18) = double(throttleFraction);
inputs(19) = 0;                % BRegenEnabledButton
inputs(20) = 15;               % T_i_max
inputs(21) = 0;                % R_max
inputs(22:23) = 1;             % yrr_scaling, Fz_gain
inputs(24) = 0;                % ay
inputs(25:26) = 1;             % use_imu_vel_x/y, per update_ctrls_inputs
inputs(27:31) = 0;             % load-cell selector and fz_fl..rr
inputs(32) = 1;                % slip_ref_scaling
end
