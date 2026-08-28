function outputPath = build_controls_model_mex(force)
%BUILD_CONTROLS_MODEL_MEX Build the host adapter for the pinned generated C.
if nargin < 1, force = false; end
if ~strcmp(version('-release'), '2024b')
    error('virtualvcu:WrongRelease', 'Build with MATLAB R2024b only.');
end
root = fileparts(fileparts(mfilename('fullpath')));
vendor = fullfile(root,'vendor','controls_model');
buildDir = fullfile(tempdir,'virtualvcu_controls_r2024b');
if ~isfolder(buildDir), mkdir(buildDir); end
outputPath = fullfile(buildDir, ['vvcu_controls_mex.' mexext]);
if force && isfile(outputPath), delete(outputPath); end
if ~isfile(outputPath)
    sources = controlsModelSources(vendor, true);
    args = [{'-R2018a',['-I' vendor]}, sources, ...
        {'-outdir',buildDir,'-output','vvcu_controls_mex'}];
    mex(args{:});
end
addpath(buildDir);
end

function sources = controlsModelSources(vendor, includeMexGateway)
names = {'ControlsMFE25.c','ControlsMFE25_data.c','coder_posix_time.c', ...
    'rt_nonfinite.c','rtGetInf.c','rtGetNaN.c','vvcu_controls_wrapper.c'};
if includeMexGateway, names{end+1} = 'vvcu_controls_mex.c'; end
sources = cellfun(@(name) fullfile(vendor,name),names,'UniformOutput',false);
end
