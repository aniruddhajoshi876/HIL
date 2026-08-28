function modelPath = default_virtual_vcu_model_path()
%DEFAULT_VIRTUAL_VCU_MODEL_PATH Locate the current or legacy HIL model path.
repo = fileparts(fileparts(fileparts(mfilename('fullpath'))));
candidates = {fullfile(repo,'VC_HIL','build','inverter_hil.slx'), ...
    fullfile(repo,'inverter_hil','inverter_hil.slx')};
modelPath = candidates{1};
for k = 1:numel(candidates)
    if isfile(candidates{k}), modelPath = candidates{k}; return; end
end
end
