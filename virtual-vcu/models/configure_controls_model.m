function configure_controls_model(model)
%CONFIGURE_CONTROLS_MODEL Link pinned generated C into simulation and target.
if nargin < 1, model = bdroot; end
root = fileparts(fileparts(mfilename('fullpath')));
vendor = fullfile(root,'vendor','controls_model');
names = {'ControlsMFE25.c','ControlsMFE25_data.c','coder_posix_time.c', ...
    'rt_nonfinite.c','rtGetInf.c','rtGetNaN.c','vvcu_controls_wrapper.c'};
sources = cellfun(@(name) ['"' fullfile(vendor,name) '"'],names, ...
    'UniformOutput',false);
set_param(model,'CustomInclude',['"' vendor '"'], ...
    'CustomSource',strjoin(sources,sprintf('\n')));
end
