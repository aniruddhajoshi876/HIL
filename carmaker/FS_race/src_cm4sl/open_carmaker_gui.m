function open_carmaker_gui()
%OPEN_CARMAKER_GUI Initialize the CM4SL/CarMaker environment for TorqueVect
%and launch the real CarMaker GUI. R2022a only.
%
%   This is the environment INITIALIZER for TorqueVect.mdl, not just a GUI
%   launcher. Opening TorqueVect.mdl directly, without running this first,
%   reliably fails to compile with errors like:
%
%     SLDD:sldd:VarDeletedBaseWithoutValueRecorded
%     Variable 'Kp' has been deleted from base workspace.
%
%   (and the same for Ki, Kd, kp, ki, kd, N, velocity_lookup) --
%   TorqueVect's pre-existing torque-vectoring PID controller blocks are
%   parameterized by base workspace variables. Current MFE25-Controls
%   initializes the newer gain-scheduled parameters but no longer creates
%   the lower-case legacy compatibility names, so those are restored below.
%   The lower-case values (kp/ki/kd, N, velocity_lookup) come from MFE25-
%   Controls' last tracked pre-removal behavior. The upper-case values
%   (Kp/Ki/Kd) are a provisional controls-development baseline recovered
%   from the older MFE23 full control loop; they still require vehicle
%   tuning. Nothing about this dependency is specific to the CarMaker-truth
%   / Speedgoat work.
%
%   Body is the user's own verbatim, previously-tested procedure:
%     1. Add MFE25-Controls' vehicle + controls model folders to path.
%     2. Run Control_FL_Combined_Run.m from "Model Parameters" through
%        "Other Controller and Optimization Parameters" ONLY -- never the
%        whole file, and never "Run Full Control Loop" onward.
%     3. `clear cd` -- that section defines `cd = 1.7` (a drag
%        coefficient), which shadows the builtin cd() function otherwise.
%     4. Add THIS repo's own src_cm4sl (the HIL copy -- resolved from this
%        script's own location, so it is correct on whichever branch is
%        checked out; never IPG-MFE or any other project) to path.
%     5. Run cmenv, then open TorqueVect.mdl and click its own
%        "Open CarMaker GUI" block, which launches the real CarMaker
%        engine process (window title "CarMaker for Simulink ... online",
%        process name HIL.exe, plus a companion Movie.exe) and links this
%        MATLAB session to it.
%
%   PRECONDITIONS THIS CHECKS, before touching anything above:
%     - Running in R2022a (CM4SL only ships up to R2022a/R2022b for this
%       CarMaker 12.0.1 install; this model is R2022a-authored).
%     - No stray HIL.exe / Movie.exe already running (an already-open
%       CarMaker link, re-triggered by opening the model or the GUI block
%       a second time, wedges: StartSim then fails with
%       pidpack.PIDConfig.utilSelectVariants: Invalid Simulink object name
%       and never recovers without killing both the engine process and
%       the backing MATLAB.exe). If you hit that anyway, the only known
%       fix is closing this MATLAB session and starting fresh -- there is
%       no in-session recovery.
%     - MFE25-Controls exists at the expected path.
%
%   DELIBERATELY NOT DONE HERE: driving/track setup (car selection,
%   cockpit device configuration, TestRun selection, Start). Those are
%   manual GUI steps once the CarMaker window is up, or a separate
%   cmguicmd('LoadTestRun "...")') call after this function returns.
%
%   Untracked by design (matches this file's own prior history in this
%   repo): a session-convenience script, not a build deliverable.

if ~strncmp(version('-release'), '2022', 4)
    error('open_carmaker_gui:wrongRelease', ...
        ['This model and CM4SL link require R2022a; running %s. ' ...
         'Open R2022a and rerun this from there.'], version('-release'));
end

if ispc
    [~, existing] = system('tasklist /FI "IMAGENAME eq HIL.exe" /FI "IMAGENAME eq Movie.exe" 2>NUL');
    if contains(existing, 'HIL.exe') || contains(existing, 'Movie.exe')
        error('open_carmaker_gui:staleEngine', ...
            ['A CarMaker engine (HIL.exe / Movie.exe) is already running. ' ...
             'Re-triggering the GUI block against an existing link wedges ' ...
             'StartSim. Close it (or kill the processes) before rerunning.']);
    end
end

mfeControlsRoot = 'C:\Users\MFE-HPC\Documents\GitHub\MFE25-Controls';
if ~isfolder(mfeControlsRoot)
    error('open_carmaker_gui:noMfe25Controls', ...
        'MFE25-Controls not found at %s.', mfeControlsRoot);
end

% 1. MFE25-Controls: vehicle + controls model on path
addpath(genpath(fullfile(mfeControlsRoot, '01 Vehicle Model')));
addpath(genpath(fullfile(mfeControlsRoot, '02 Controls Model')));

% 2. Run only "Model Parameters" through "Other Controller and Optimization
%    Parameters" from Control_FL_Combined_Run.m -- never the whole file.
combinedRunFile = fullfile(mfeControlsRoot, '02 Controls Model', 'Control_FL_Combined_Run.m');
fileText = fileread(combinedRunFile);
stopIdx = strfind(fileText, '%% Run Full Control Loop');
evalin('base', fileText(1:stopIdx(1) - 1));

% Compatibility for TorqueVect's legacy Full Control Loop PID paths
% (CarMaker/.../PTControl_TV_MFE25/Full Control Loop/TC 1..4). Those blocks
% read the un-suffixed base names kp/ki/kd, N and velocity_lookup. MFE25-
% Controls commit 2a61010 removed all of them from Control_FL_Combined_Run.m
% in the same edit that switched to pid_kp_*/pid_ki_*/pid_kd_* and the
% *_long/*_lat suffixes, so a clean session no longer defines them and the
% model fails to compile ("Variable 'N' has been deleted from base
% workspace", etc). Values below are that file's state at 2a61010^:
%   - kp/ki/kd: the longitudinal section set [3000 300 300]/[6000 600 600]/
%     [1 5 1.2], then the lateral section overwrote all three with [1 1 1];
%     running the documented sections in order leaves [1 1 1].
%   - velocity_lookup: [0 10 50], set once in the longitudinal section and
%     never overwritten (the lateral section uses velocity_lookup_lat).
%   - N: no un-suffixed N ever existed; the same section defined N_long = 100
%     (and N_lat = 1). The TC 1..4 loops are the per-wheel longitudinal
%     traction-control PIDs, so N_long's 100 is the match. Provisional --
%     retune with the rest of this legacy controller before relying on it.
assignin('base', 'kp', [1, 1, 1]);
assignin('base', 'ki', [1, 1, 1]);
assignin('base', 'kd', [1, 1, 1]);
assignin('base', 'N', 100);
assignin('base', 'velocity_lookup', [0, 10, 50]);

% Provisional scalar calibration for the older, upper-case PID masks.
% MFE23-Controllers/MFE_WIP_scripts/full_control_loop.slx contains the oldest
% numeric match found: Kp = 1500 and Ki/s = 6000/s. It has no numeric Kd, so
% use zero derivative until this legacy controller is retuned and validated.
assignin('base', 'Kp', 1500);
assignin('base', 'Ki', 6000);
assignin('base', 'Kd', 0);

% That script defines "cd = 1.7" (drag coefficient), which shadows the
% built-in cd() function -- clear it before using cd() again.
clear cd

% 3. HIL repo's src_cm4sl on path (source of truth, not IPG-MFE)
hilSrcCm4sl = fileparts(mfilename('fullpath'));
addpath(genpath(hilSrcCm4sl));
cd(hilSrcCm4sl);

% 4. Establish the real CarMaker link
cmenv;

% 5. Open the model and launch the CarMaker GUI
open_system('TorqueVect');
open_system('TorqueVect/Open CarMaker GUI');
end
