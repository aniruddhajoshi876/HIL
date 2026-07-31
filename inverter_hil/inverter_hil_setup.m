function root = inverter_hil_setup()
%INVERTER_HIL_SETUP Configure the R2024b inverter HIL workspace.

if ~strcmp(version('-release'), '2024b')
    error('inverterhil:WrongRelease', ...
        'Inverter HIL requires MATLAB/Simulink R2024b; running %s.', ...
        version('-release'));
end

root = fileparts(mfilename('fullpath'));
workspaceRoot = fileparts(root);
speedgoatCandidates = { ...
    fullfile(root, '10.0.1.1', 'R2024B_SLX', 'sg_blocks'), ...
    fullfile(workspaceRoot, '10.0.1.1', 'R2024B_SLX', 'sg_blocks')};
speedgoatBlocks = '';
for index = 1:numel(speedgoatCandidates)
    if isfolder(speedgoatCandidates{index})
        speedgoatBlocks = speedgoatCandidates{index};
        break
    end
end
if isempty(speedgoatBlocks)
    error('inverterhil:MissingSpeedgoatLibraries', ...
        'R2024b Speedgoat block libraries are missing near %s.', root);
end

addpath(root, speedgoatBlocks);
cacheFolder = fullfile(root, '.simulink', 'cache');
codegenFolder = fullfile(root, '.simulink', 'codegen');
if ~isfolder(cacheFolder)
    mkdir(cacheFolder);
end
if ~isfolder(codegenFolder)
    mkdir(codegenFolder);
end
Simulink.fileGenControl('set', 'CacheFolder', cacheFolder, ...
    'CodeGenFolder', codegenFolder, 'createDir', true);
end
