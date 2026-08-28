function patch_virtual_vcu_chart(modelPath)
%PATCH_VIRTUAL_VCU_CHART Persist the R2024b chart source after model build.
if nargin < 1
    modelPath = default_virtual_vcu_model_path();
end
load_system(modelPath);
cleanup = onCleanup(@() close_system('inverter_hil', 0));
configure_controls_model('inverter_hil');
rt = sfroot();
block = 'inverter_hil/Virtual VCU/Virtual VCU LV_ON';
chart = rt.find('-isa', 'Stateflow.EMChart', '-and', 'Path', block);
assert(~isempty(chart), 'virtualvcu:MissingChart', 'Missing virtual VCU chart.');
chart(1).Script = fileread(fullfile(fileparts(mfilename('fullpath')), ...
    'virtualVcuDeployStep.m'));
save_system('inverter_hil', modelPath);
end
