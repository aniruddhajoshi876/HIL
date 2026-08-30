function open_carmaker_gui()
%OPEN_CARMAKER_GUI Initialize the CM4SL/CarMaker environment for the
%external-VC bridge model HIL_torquevectoring.mdl and launch the real
%CarMaker GUI. R2022a only.
%
%   ARCHITECTURE this launcher sets up
%     The vehicle controller runs on the real VC as code-generated controls.
%     CM4SL is only the simulated plant and the CAN bridge:
%
%       CarMaker sensors -> CM4SL truth CAN (0x503-0x507)
%                        -> VC runs the code-generated controls model
%                        -> VC CAN motor-torque commands
%                        -> Speedgoat republishes them as 0x501 / 0x502
%                        -> IO.c decodes -> MFE_CAN.Inverter*TorqueSetpointNm
%                        -> HIL_torquevectoring.mdl: validate / saturate /
%                           zero-torque fallback
%                        -> CarMaker motors / wheels
%
%     HIL_torquevectoring.mdl does NOT compute torque vectoring. The original
%     TorqueVect.mdl is kept unchanged next to it as the internal-controls
%     model and as the reference for the CarMaker interface blocks, actuator
%     mapping, wheel ordering, units and drivetrain conversions. This launcher
%     opens the bridge model; to work on the internal-controls model, open
%     TorqueVect.mdl and follow the older procedure.
%
%   This is the environment INITIALIZER, not just a GUI launcher. Opening
%   HIL_torquevectoring.mdl directly, without running this first, fails to
%   compile: T_i_max (the per-motor torque limit the bridge saturates to) is
%   a base-workspace variable that MFE25-Controls' Control_FL_Combined_Run.m
%   defines.
%
%   NOT NEEDED ANY MORE: the legacy torque-vectoring PID names
%   Kp/Ki/Kd/kp/ki/kd/N/velocity_lookup. Those parameterised TorqueVect.mdl's
%   Full Control Loop / TC 1..4 blocks, which HIL_torquevectoring.mdl does not
%   contain. Verified: with those names cleared from the base workspace and
%   only T_i_max present, HIL_torquevectoring.mdl compiles (model compile +
%   term) clean. If you ever hit "Variable 'Kp' has been deleted from base
%   workspace" here, you opened TorqueVect.mdl, not the bridge model.
%
%   Body is the user's own verbatim, previously-tested procedure:
%     1. Add MFE25-Controls' vehicle + controls model folders to path.
%     2. Run Control_FL_Combined_Run.m from "Model Parameters" through
%        "Other Controller and Optimization Parameters" ONLY -- never the
%        whole file, and never "Run Full Control Loop" onward. This is what
%        defines T_i_max.
%     3. `clear cd` -- that section defines `cd = 1.7` (a drag
%        coefficient), which shadows the builtin cd() function otherwise.
%     4. Add THIS repo's own src_cm4sl (the HIL copy -- resolved from this
%        script's own location, so it is correct on whichever branch is
%        checked out; never IPG-MFE or any other project) to path.
%     5. Run cmenv, then open HIL_torquevectoring.mdl and click its own
%        "Open CarMaker GUI" block, which launches the real CarMaker engine
%        process (window title "CarMaker for Simulink ... online", process
%        name HIL.exe, plus a companion Movie.exe) and links this MATLAB
%        session to it.
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
%    This is the sole source of T_i_max (the per-motor torque limit, 21 N*m,
%    that HIL_torquevectoring.mdl's bridge saturates the VC command to). It
%    also creates the *_long / *_lat / pid_* controller parameters; the
%    bridge model uses none of those, only T_i_max, but running the block
%    whole is the user's tested procedure so it stays as-is.
combinedRunFile = fullfile(mfeControlsRoot, '02 Controls Model', 'Control_FL_Combined_Run.m');
fileText = fileread(combinedRunFile);
stopIdx = strfind(fileText, '%% Run Full Control Loop');
evalin('base', fileText(1:stopIdx(1) - 1));

% That script defines "cd = 1.7" (drag coefficient), which shadows the
% built-in cd() function -- clear it before using cd() again.
clear cd

% 3. HIL repo's src_cm4sl on path (source of truth, not IPG-MFE)
hilSrcCm4sl = fileparts(mfilename('fullpath'));
addpath(genpath(hilSrcCm4sl));
cd(hilSrcCm4sl);

% 4. Establish the real CarMaker link
cmenv;

% 5. Open the external-VC bridge model and launch the CarMaker GUI.
%    (TorqueVect.mdl -- the internal-controls model -- is intentionally NOT
%    opened here; open it by hand when working on local controls.)
open_system('HIL_torquevectoring');
open_system('HIL_torquevectoring/Open CarMaker GUI');
end
