%Set Slider for Manual Control to Hover.
set_param([mdl '/Flight Controller/Guidance Test Bench/ControlType/Manual Control/Command Interface/FlightModeSlider'],'Value','0');
%Set Aircraft to Manual Control Mode
TestMode=0;
%Set Visualization on.
Visualization=1;
%No guidance mission
guidanceType=0;
disp("Enabled hover manual testbench mode.")
