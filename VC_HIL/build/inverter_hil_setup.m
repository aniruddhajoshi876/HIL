function root = inverter_hil_setup()
%INVERTER_HIL_SETUP Configure the R2024b inverter HIL workspace.

if ~strcmp(version('-release'), '2024b')
    error('inverterhil:WrongRelease', ...
        'Inverter HIL requires MATLAB/Simulink R2024b; running %s.', ...
        version('-release'));
end

root = fileparts(mfilename('fullpath'));
% ROOT is this file's own folder (VC_HIL/build); WORKSPACEROOT is VC_HIL
% itself, one level up, where the non-generated helper folders (imu/,
% steering-sensor/) and any local Speedgoat block checkout still live --
% only the generated model/app/GUI artifacts moved into ROOT.
workspaceRoot = fileparts(root);
speedgoatCandidates = { ...
    fullfile(workspaceRoot, '10.0.1.1', 'R2024B_SLX', 'sg_blocks'), ...
    fullfile(fileparts(workspaceRoot), '10.0.1.1', 'R2024B_SLX', 'sg_blocks'), ...
    fullfile(fileparts(workspaceRoot), 'examples', '10.0.1.1', ...
        'R2024B_SLX', 'sg_blocks')};
speedgoatBlocks = '';
for index = 1:numel(speedgoatCandidates)
    if isfolder(speedgoatCandidates{index})
        speedgoatBlocks = speedgoatCandidates{index};
        break
    end
end
if isempty(speedgoatBlocks)
    error('inverterhil:MissingSpeedgoatLibraries', ...
        'R2024b Speedgoat block libraries are missing near %s.', workspaceRoot);
end

% VC_HIL/inverter's own functions are split by role into subfolders
% (rxCAN, txCAN, bus_info, contructors, state-machine, sensorNormalizer,
% build); every caller reaches them by bare function name, so all seven
% must be on path alongside inverter/ itself. inverter/sensorNormalizer
% holds only the cross-sensor frame-ordering step that belongs to neither
% sensor individually (see SENSORFRAMEORDER); the IMU- and LWS-specific
% pieces that used to live alongside it (TX ID lists, schedulers, frame
% normalizers) now live in WORKSPACEROOT's own imu/ and steering-sensor/,
% added below.
inverterRoot = fullfile(workspaceRoot, 'inverter');
addpath(root, workspaceRoot, inverterRoot, ...
    fullfile(inverterRoot, 'rxCAN'), fullfile(inverterRoot, 'txCAN'), ...
    fullfile(inverterRoot, 'bus_info'), ...
    fullfile(inverterRoot, 'contructors'), ...
    fullfile(inverterRoot, 'state-machine'), ...
    fullfile(inverterRoot, 'sensorNormalizer'), fullfile(inverterRoot, 'build'), ...
    speedgoatBlocks, fullfile(workspaceRoot, 'imu'), ...
    fullfile(workspaceRoot, 'steering-sensor'));
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
