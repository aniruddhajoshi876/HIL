function configure_controls_model(model)
%CONFIGURE_CONTROLS_MODEL Link the vendored ControlsMFE25 allocator C for RTW.
%   The virtual-VCU chart (virtualVcuDeployStep) reaches the allocator two ways:
%
%     * Simulation (interpreted MATLAB, the accelerator MEX, and the Stateflow
%       chart S-function that slbuild builds first) -> the already-built host
%       MEX vvcu_controls_mex. The chart carries NO custom code on that path, so
%       the S-function build is not subject to Stateflow's custom-code pre-parse.
%
%     * Code generation (RTW / Speedgoat) -> coder.ceval on
%       vvcu_controls_wrapper.c, with the four vendored .c files below attached
%       here as model-level CustomSource (full paths, so the generated makefile
%       gets a real compile rule -- addSourceFiles with bare names does not).
%
%   rt_nonfinite.c / rtGetInf.c / rtGetNaN.c are NOT attached: Simulink Coder
%   generates its own for every model; the vendored copies would produce
%   "multiple definition of rtIsNaN" at link. Their headers stay on the include
%   path so ControlsMFE25.c compiles, and it links against Simulink's copies.
if nargin < 1, model = bdroot; end
root = fileparts(fileparts(mfilename('fullpath')));
vendor = fullfile(root,'vendor','controls_model');
if exist(vendor,'dir') == 7
    addpath(vendor);
end
names = {'ControlsMFE25.c','ControlsMFE25_data.c','coder_posix_time.c', ...
    'vvcu_controls_wrapper.c'};
quoted = cellfun(@(n) ['"' fullfile(vendor,n) '"'], names, 'UniformOutput', false);
set_param(model, ...
    'CustomInclude',['"' vendor '"'], ...
    'CustomSource',strjoin(quoted,sprintf('\n')));
end
