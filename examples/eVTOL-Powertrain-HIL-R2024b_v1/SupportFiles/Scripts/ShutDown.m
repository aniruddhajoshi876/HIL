%   About this script:
%      -  Cleans up environemtn customizations of the demo environment 
%      -  Set to run at shutdown

% Reset the location where generated code and other temporary files are
% created (slprj) to the default:
Simulink.fileGenControl('reset');

% Use Simulink Project API to get the current project:
p = slproject.getCurrentProject;
projectRoot = p.RootFolder;

% Delete work folder contents
myCacheFolder = fullfile(slproject.getCurrentProject().RootFolder, 'SupportFiles', 'work');

if isfolder(myCacheFolder)
    try        
        rmdir('SupportFiles/work', 's');
    catch
        warning('Could not delete cache and codegen folder contents.');
    end
end

% Cleanup
clear p projectRoot myCacheFolder
clc;clear;
