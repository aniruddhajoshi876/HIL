%exampleHelperSetupFixedWingControlTuning_Attitude Setup fixed wing linearization of attitude loops
%for control tuning.

% Copyright 2023 The MathWorks, Inc.

%Set Slider for Manual Control to Fixed Wing.
set_param([mdl '/Guidance Test Bench/ControlType/Manual Control/Command Interface/FlightModeSlider'],'Value','2');

TestMode = 0;
TuningMode = 1;

controllerBlock = [mdl,'/Autopilot/Fixed Wing Controller/Fixed Wing Controller Tuning'];

% Define blocks to tune
tunedBlocks = {[controllerBlock,'/Attitude Controller/Pitch Roll Controller/Roll Angle Controller']; ...
               [controllerBlock,'/Attitude Controller/Pitch Roll Controller/Roll Rate Controller']; ...
               [controllerBlock,'/Attitude Controller/Pitch Roll Controller/Pitch Angle Controller']; ...
               [controllerBlock,'/Attitude Controller/Pitch Roll Controller/Pitch Rate Controller']};

% Define analysis points based on design goals for the loops to tune
rollOpenLoopLocation = [controllerBlock,'/Attitude Controller/Pitch Roll Controller/Roll Rate Controller/1'];
pitchOpenLoopLocation = [controllerBlock,'/Attitude Controller/Pitch Roll Controller/Pitch Rate Controller/1'];
rollAngleInput = [controllerBlock,'/Roll SP Switch/1'];
rollAngleOutput = [controllerBlock,'/Demux1/3'];
pitchAngleInput = [controllerBlock,'/Pitch SP Switch/1'];
pitchAngleOutput = [controllerBlock,'/Demux1/2'];

analysisPoints = {rollOpenLoopLocation,pitchOpenLoopLocation,rollAngleInput,rollAngleOutput,pitchAngleInput,pitchAngleOutput}';