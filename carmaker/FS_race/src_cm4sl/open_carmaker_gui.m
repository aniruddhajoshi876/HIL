%OPEN_CARMAKER_HIL_GUI Launch the real CarMaker GUI for FS_race/HIL.
%   Run this file directly as a SCRIPT in MATLAB R2022a (the CM4SL-
%   compatible release for this repo -- do not confuse with the R2024b
%   session used for MFE25-Controls' .slx / Speedgoat work). It must run
%   as a script, not be called as a function, so the workspace variables
%   TorqueVect.mdl needs land in the base workspace where Simulink looks
%   for them.
%
%   Steps, matching the user's verbatim manual procedure:
%     1. Add MFE25-Controls' vehicle + controls model folders to path.
%     2. Run ONLY "Model Parameters" through "Other Controller and
%        Optimization Parameters" from Archive/Control_Full_Loop_Run.m --
%        never the whole file. Running further sections ("Run Full
%        Control Loop" onward) is what previously produced a
%        cd-shadowing bug. This is the Archive script, not
%        Control_FL_Combined_Run.m: TorqueVect.mdl's PID Controller
%        blocks (PTControl_TV_MFE25/Full Control Loop/TC 1-4) read their
%        gains as literal base-workspace vars named kp/ki/kd, and
%        Control_Full_Loop_Run.m is the only script anywhere in HIL,
%        MFE25-Controls, or IPG-MFE that defines those exact names
%        (Control_FL_Combined_Run.m only defines pid_kp_long/pid_ki_lat/
%        etc., which nothing in TorqueVect.mdl reads) -- confirmed by
%        scanning every block/parameter in the model for undefined
%        workspace refs. Without this section, update/StartSim fails
%        with "Variable 'kp' has been deleted from base workspace."
%     3. Add the HIL repo's src_cm4sl to path (this repo is the source of
%        truth; IPG-MFE is a scratch build target, never used here).
%     4. Run cmenv, which establishes the real CarMaker link (wraps
%        cminit).
%     5. Open TorqueVect.mdl and try to launch the CarMaker GUI via its
%        "Open CarMaker GUI" block. If that block's own OpenFcn can't be
%        triggered programmatically, double-click it by hand at the
%        model's top level.

%% 1. MFE25-Controls: vehicle + controls model on path
mfeControlsRoot = 'C:\Users\MFE-HPC\Documents\GitHub\MFE25-Controls';
addpath(genpath(fullfile(mfeControlsRoot, '01 Vehicle Model')));
addpath(genpath(fullfile(mfeControlsRoot, '02 Controls Model')));

%% 2. Run only the required sections of Archive/Control_Full_Loop_Run.m
combinedRunFile = fullfile(mfeControlsRoot, '02 Controls Model', ...
    'Archive', 'Control_Full_Loop_Run.m');
fileText = fileread(combinedRunFile);
stopMarker = '%% Run Full Control Loop';
stopIdx = strfind(fileText, stopMarker);
if isempty(stopIdx)
    error('open_carmaker_hil_gui:MarkerNotFound', ...
        ['Could not find the "%s" section marker in %s -- the file may ' ...
        'have changed. Update this script''s stopMarker to match before ' ...
        'rerunning.'], stopMarker, combinedRunFile);
end
evalin('base', fileText(1:stopIdx(1) - 1));

% Control_Full_Loop_Run.m defines "cd = 1.7" (drag coefficient) in the
% base workspace, which shadows the built-in cd() directory-change
% function for the rest of the session -- every cd() call below would
% otherwise throw "Index exceeds the number of array elements."
evalin('base', 'clear cd');

% TorqueVect.mdl also wires in an orphaned, never-selected sibling
% controller subsystem left over from last year's car
% (PTControl_ALL_CTRL_VC_MFE24, under PowerTrain/PTControl Example). Its
% Switch selector is hardcoded to always pick this year's controller
% (PTControl_TV_MFE25), so ALL_CTRL_VC_MFE24's output is structurally
% discarded every run -- but Simulink still compiles that dead branch on
% every update/start, and its 6 PID Controller blocks reference base
% workspace variables Kp/Ki/Kd that no script in HIL, MFE25-Controls, or
% IPG-MFE defines (confirmed by repo-wide search). Nothing feeds them, so
% without this line every update/StartSim fails with
% SLDD:sldd:VarDeletedBaseWithoutValueRecorded. Since the branch's output
% is provably unused, the exact numbers don't matter -- these are inert
% placeholders, not real tuned gains.
evalin('base', 'Kp = 1; Ki = 0; Kd = 0;');

%% 3. HIL repo's src_cm4sl on path (source of truth, not IPG-MFE)
hilSrcCm4sl = ...
    'C:\Users\MFE-HPC\Documents\GitHub\HIL\carmaker\FS_race\src_cm4sl';
addpath(genpath(hilSrcCm4sl));
cd(hilSrcCm4sl);

%% 4. Establish the real CarMaker link (wraps cminit)
cmenv;

%% 5. Open the model and try to launch the CarMaker GUI
open_system('TorqueVect');
try
    open_system('TorqueVect/Open CarMaker GUI');
catch openErr
    warning('open_carmaker_hil_gui:GuiBlockOpenFailed', ...
        ['Could not open the CarMaker GUI programmatically (%s). In the ' ...
        'TorqueVect window, go to the model''s top level and ' ...
        'double-click the "Open CarMaker GUI" block by hand.'], ...
        openErr.message);
end
