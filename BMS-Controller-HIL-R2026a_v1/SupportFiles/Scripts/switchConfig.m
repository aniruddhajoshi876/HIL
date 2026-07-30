function switchConfig(x)
    if x == "HIL" || x == "hil"
        set_param([bdroot '/Instrumentation/Simulation_Profile_Value'], 'Value','1');
    elseif x == "MIL" || x == "mil"
        set_param([bdroot '/Instrumentation/Simulation_Profile_Value'], 'Value','0');
    else
        fprintf('Simulation Profile does not exist. Try "HIL" or "MIL" \n');
    end
