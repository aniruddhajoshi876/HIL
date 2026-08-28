function switchMotorConfig(x)
    if x == "HIL" || x == "hil"
        set_param('eVTOL_System/Motor Drive/SimulationVariant', 'Value','3');
    elseif x == "RMIL" || x == "rmil"
        set_param('eVTOL_System/Motor Drive/SimulationVariant', 'Value','2');
    elseif x == "MIL" || x == "mil"
        set_param('eVTOL_System/Motor Drive/SimulationVariant', 'Value','1');
    else
        fprintf('Simulation Profile does not exist. Try "HIL" or "MIL" \n');
    end
end
