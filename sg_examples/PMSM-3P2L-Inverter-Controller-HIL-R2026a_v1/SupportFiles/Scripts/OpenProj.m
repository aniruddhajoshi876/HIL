%   About this script:
%      -  Sets up the environment for a flawless exercise of the reference
%      application
%      -  Set to run at startup

% Use Simulink Project API to get the current project:
p = slproject.getCurrentProject;
projectRoot = p.RootFolder;

% Create work folder and sets it as cache and codegen folder 
myCacheFolder = fullfile(projectRoot, 'SupportFiles', 'Work');
Simulink.fileGenControl('set',...
    'CacheFolder', myCacheFolder,...
    'CodeGenFolder', myCacheFolder,...
    'createDir', true)
clearvars project projectRoot myCacheFolder

% Open reference application system model 
open_system('PMSM3P2LInverterCHILsystem')

% Open reference application getting started doc file 
edit('GettingStarted')

% Cleanup
clear p projectRoot myCacheFolder
