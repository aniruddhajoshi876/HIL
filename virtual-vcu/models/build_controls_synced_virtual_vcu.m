function result = build_controls_synced_virtual_vcu(force)
%BUILD_CONTROLS_SYNCED_VIRTUAL_VCU Build base HIL then apply the VCU overlay.
if nargin < 1, force = true; end
repo = fileparts(fileparts(fileparts(mfilename('fullpath'))));
buildDir = fullfile(repo,'VC_HIL','build');
addpath(buildDir);
build_inverter_hil_model(force);
modelPath = fullfile(buildDir,'inverter_hil.slx');
add_virtual_vcu_to_model(modelPath);
patch_virtual_vcu_inputs(modelPath);
patch_virtual_vcu_chart(modelPath);
patch_virtual_vcu_state_outputs(modelPath);
result = verify_virtual_vcu_model(modelPath);
result.modelPath = modelPath;
end
