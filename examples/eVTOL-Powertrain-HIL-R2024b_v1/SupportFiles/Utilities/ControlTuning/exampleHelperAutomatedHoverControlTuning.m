%exampleHelperAutomatedHoverControlTuning tune all control gains for hover
%mode.

% Copyright 2023 The MathWorks, Inc.
%Disable linearization warning
state = warning('off', 'Simulink:blocks:BmathSqrtOfNegativeNumber');
cleanup = onCleanup(@()warning(state));


options = linearizeOptions('SampleTime',0.005);
ctrloptions= pidtuneOptions;
ctrloptions.PhaseMargin=60;
ctrloptions.DesignFocus = 'balanced';

%% Enable/Disable Tuning of Loops
TuneXY = true;
TuneVxVy = true;
TunePR = true;
TunePrRr = true;
%% Roll rate
if TunePrRr
    io(1) = linio([mdl '/Autopilot/Multicopter Controller/Attitude Control/Derivative Gain/Roll Rate Controller'],1,'openinput');
    io(2) = linio([mdl '/Autopilot/Multicopter Controller/Attitude Control/Derivative Gain/Demux2'],1,'openoutput');
    rollRateSys=linearize(mdl,io,options);
    [C,~]=pidtune(rollRateSys,'PDF',50,ctrloptions);
    controlParams.P_ROLL_RATE=C.Kp;
    controlParams.I_ROLL_RATE=C.Ki; % NO I Gain because of 1/s plant
    controlParams.D_ROLL_RATE=C.Kd;
    if C.Tf<eps
        C.Tf = 0.01;
    end
    controlParams.N_ROLL_RATE=1/C.Tf;
end

%% Pitch rate
if TunePrRr
    io(1) = linio([mdl '/Autopilot/Multicopter Controller/Attitude Control/Derivative Gain/Pitch Rate Controller'],1,'openinput');
    io(2) = linio([mdl '/Autopilot/Multicopter Controller/Attitude Control/Derivative Gain/Demux2'],2,'openoutput');
    pitchRateSys=linearize(mdl,io,options);
    [C,~]=pidtune(pitchRateSys,'PDF',50,ctrloptions);
    controlParams.P_PITCH_RATE=C.Kp;
    controlParams.I_PITCH_RATE=C.Ki; % NO I Gain because of 1/s plant
    controlParams.D_PITCH_RATE=C.Kd;
    if C.Tf<eps
        C.Tf = 0.01;
    end
    controlParams.N_PITCH_RATE=1/C.Tf;
end

%% Yaw rate
if TunePrRr
    io(1) = linio([mdl '/Autopilot/Multicopter Controller/Attitude Control/Derivative Gain/Yaw rate controller'],1,'openinput');
    io(2) = linio([mdl '/Autopilot/Multicopter Controller/Attitude Control/Derivative Gain/Demux2'],3,'openoutput');
    yawRateSys=linearize(mdl,io,options);
    [C,~]=pidtune(yawRateSys,'PDF',50,ctrloptions);
    controlParams.P_YAW_RATE=C.Kp;
    controlParams.I_YAW_RATE=C.Ki;  % NO I Gain because of 1/s plant
    controlParams.D_YAW_RATE=C.Kd;
    if C.Tf<eps
        C.Tf = 0.01;
    end
    controlParams.N_YAW_RATE=1/C.Tf;
end

%% Design outer loop after designing inner loop.
%% Roll
if TunePR
    io(1) = linio([mdl '/Autopilot/Multicopter Controller/Attitude Control/Derivative Gain/Roll Controller'],1,'openinput');
    io(2) = linio([mdl '/Autopilot/Multicopter Controller/Attitude Control/Derivative Gain/Demux3'],1,'openoutput');
    rollSys=linearize(mdl,io,options);
    [C,~]=pidtune(rollSys,'PDF',10,ctrloptions);
    controlParams.P_ROLL=C.Kp;
    controlParams.I_ROLL=C.Ki; % NO I Gain because of 1/s plant
    controlParams.D_ROLL=C.Kd;
    if C.Tf<eps
        C.Tf = 0.01;
    end
    controlParams.N_ROLL=1/C.Tf;
end

%% Pitch
if TunePR
    io(1) = linio([mdl '/Autopilot/Multicopter Controller/Attitude Control/Derivative Gain/Pitch Controller'],1,'openinput');
    io(2) = linio([mdl '/Autopilot/Multicopter Controller/Attitude Control/Derivative Gain/Demux3'],2,'openoutput');
    pitchSys=linearize(mdl,io,options);
    [C,~]=pidtune(pitchSys,'PDF',10,ctrloptions);
    controlParams.P_PITCH=C.Kp;
    controlParams.I_PITCH=C.Ki; % NO I Gain because of 1/s plant
    controlParams.D_PITCH=C.Kd;
    if C.Tf<eps
        C.Tf = 0.01;
    end
    controlParams.N_PITCH=1/C.Tf;
end

%% Yaw
if TunePR
    io(1) = linio([mdl '/Autopilot/Multicopter Controller/Attitude Control/Derivative Gain/Yaw Controller'],1,'openinput');
    io(2) = linio([mdl '/Autopilot/Multicopter Controller/Attitude Control/Derivative Gain/Demux3'],3,'openoutput');
    yawSys=linearize(mdl,io,options);
    [C,~]=pidtune(yawSys,'PDF',10,ctrloptions);
    controlParams.P_YAW=C.Kp;
    controlParams.I_YAW=C.Ki; % NO I Gain because of 1/s plant
    controlParams.D_YAW=C.Kd;
    if C.Tf<eps
        C.Tf = 0.01;
    end
   controlParams.N_YAW=1/C.Tf;
end

%% X Rate Controller
% NEEDS TO BE "SNAPSHOT" LINEARIZED
% SYSTEM IS VERY HIGH ORDER WITH NUMEROUS MODES
if TuneVxVy
    io(1) = linio([mdl '/Autopilot/Multicopter Controller/Horizontal Position Control/XY Controller/Vx Controller'],1,'openinput');
    io(2) = linio([mdl '/Autopilot/Multicopter Controller/Horizontal Position Control/XY Controller/Demux1'],1,'openoutput');
    try % System doesn't always linearize at t=0
        XRateSys=linearize(mdl,io,options);
    catch % Snapshot at t=10 seconds
        XRateSys=linearize(mdl,io,options,10);
    end
    [C,~]=pidtune(XRateSys,'P',5,ctrloptions);
    controlParams.P_VX=C.Kp;
end

%% Y Rate Controller
if TuneVxVy
    io(1) = linio([mdl '/Autopilot/Multicopter Controller/Horizontal Position Control/XY Controller/Vy Controller'],1,'openinput');
    io(2) = linio([mdl '/Autopilot/Multicopter Controller/Horizontal Position Control/XY Controller/Demux1'],2,'openoutput');
    YRateSys=linearize(mdl,io,options);
    [C,~]=pidtune(YRateSys,'P',5,ctrloptions);
    controlParams.P_VY=C.Kp;
end

%% Z Rate Controller
if TuneVxVy
    io(1) = linio([mdl '/Autopilot/Multicopter Controller/Altitude Control/PID Controller1'],1,'openinput');
    io(2) = linio([mdl '/Autopilot/Multicopter Controller/Altitude Control/Selector1'],1,'openoutput');
    ZRateSys=linearize(mdl,io,options);
    [C,~]=pidtune(ZRateSys,'PIDF',5,ctrloptions);
    controlParams.P_VZ=-C.Kp;
    controlParams.I_VZ=-C.Ki;
    controlParams.D_VZ=C.Kd;
    if C.Tf<eps
        C.Tf = 0.01;
    end
    controlParams.N_VZ=1/C.Tf;
end

%% X Controller
% NEEDS TO BE "SNAPSHOT" LINEARIZED
% SYSTEM IS VERY HIGH ORDER WITH NUMEROUS MODES
if TuneXY
    io(1) = linio([mdl '/Autopilot/Multicopter Controller/Horizontal Position Control/XY Controller/X Controller'],1,'openinput');
    io(2) = linio([mdl '/Autopilot/Multicopter Controller/Horizontal Position Control/XY Controller/Demux'],1,'openoutput');
    try % System doesn't always linearize at t=0
        XSys=linearize(mdl,io,options);
    catch % Snapshot at t=10 seconds
        XSys=linearize(mdl,io,options,10);
    end
    [C,~]=pidtune(XSys,'PDF',2,ctrloptions);
    controlParams.P_X=C.Kp;
    controlParams.I_X=C.Ki;
    controlParams.D_X=C.Kd;
    if C.Tf<eps
        C.Tf = 0.01;
    end
    controlParams.N_X=1/C.Tf;
end

%% Y Controller
if TuneXY
    io(1) = linio([mdl '/Autopilot/Multicopter Controller/Horizontal Position Control/XY Controller/Y Controller'],1,'openinput');
    io(2) = linio([mdl '/Autopilot/Multicopter Controller/Horizontal Position Control/XY Controller/Demux'],2,'openoutput');
    YSys=linearize(mdl,io,options);
    [C,~]=pidtune(YSys,'PDF',2,ctrloptions);
    controlParams.P_Y=C.Kp;
    controlParams.I_Y=C.Ki;
    controlParams.D_Y=C.Kd;
    if C.Tf<eps
        C.Tf = 0.01;
    end
    controlParams.N_Y=1/C.Tf;
end

%% Z Controller
if TuneXY && false
    % Disable VZ Controller for linearization
    UseVZControl = false;
    io(1) = linio([mdl '/Autopilot/Multicopter Controller/Altitude Control/PID Controller'],1,'openinput');
    io(2) = linio([mdl '/Autopilot/Multicopter Controller/Altitude Control/Selector'],1,'openoutput');
    ZSys=linearize(mdl,io,options);
    UseVZControl = true;
    [C,~]=pidtune(ZSys,'PDF',1,ctrloptions);
    controlParams.P_Z=C.Kp;
    controlParams.I_Z=C.Ki;
    controlParams.D_Z=C.Kd;
    if C.Tf<eps
        C.Tf = 0.01;
    end
    controlParams.N_Z=1/C.Tf;
end

%% Discard IO points
setlinio(mdl,[]);