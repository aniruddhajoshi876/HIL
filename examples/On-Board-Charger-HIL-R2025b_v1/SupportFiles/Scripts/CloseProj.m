%   About this script:
%      -  Cleans up environemtn customizations of the demo environment 
%      -  Set to run at shutdown

% Reset the location where generated code and other temporary files are
% created (slprj) to the default:
Simulink.fileGenControl('reset');

% Close all data dictionaries.  Discard unsaved changes
Simulink.data.dictionary.closeAll('-discard')

% Use Simulink Project API to get the current project:
p = slproject.getCurrentProject;
projectRoot = p.RootFolder;

% Delete work folder contents
myCacheFolder = fullfile(projectRoot, 'SupportFiles', 'Work');
if exist(myCacheFolder, 'dir')
    try
        cd(projectRoot);
        rmdir(myCacheFolder,"s");
    catch
    end
end

% Cleanup
clear p projectRoot myCacheFolder
clc;clear;
