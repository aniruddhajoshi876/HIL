function deploy_inverter_hil(targetName)
%DEPLOY_INVERTER_HIL Build INVERTER_HIL and run it on the Speedgoat target.
%
%   DEPLOY_INVERTER_HIL() builds the real-time application, stops whatever
%   the target is currently running, loads and starts the new application,
%   and leaves it installed as the startup application so a power cycle
%   brings it back. DEPLOY_INVERTER_HIL(NAME) targets another machine.
%
%   Written down because this sequence had been performed by hand from the
%   command window each time, which is how a step gets skipped. In
%   particular STOP-BEFORE-LOAD is not optional: LOAD on a running target
%   fails, and the failure reads like a connection problem.
%
%   PATH NOTE: RTWBUILD spawns its generated batch file without searching the
%   working directory, so the build directory is prepended to PATH for the
%   duration of the build. Without it the build fails with
%   "'...bat' is not recognized", which looks like a toolchain fault and is
%   not one. The original PATH is restored on the way out, including on
%   error.

if nargin < 1 || isempty(targetName)
    targetName = 'TargetPC1';
end

root = inverter_hil_setup();
model = 'inverter_hil';

if bdIsLoaded(model)
    close_system(model, 0);
end
load_system(fullfile(root, [model '.slx']));
cleanupModel = onCleanup(@() closeIfLoaded(model)); %#ok<NASGU>

fprintf('Building %s...\n', model);
% Folder name comes from the SPEEDGOAT system target file: '<model>_sg_rtw',
% not the '_slrealtime_rtw' the generic Simulink Real-Time flow would use.
buildFolder = fullfile(root, '.simulink', 'codegen', ...
    [model '_sg_rtw'], 'instrumented');
originalPath = getenv('PATH');
restorePath = onCleanup(@() setenv('PATH', originalPath)); %#ok<NASGU>
setenv('PATH', [buildFolder pathsep originalPath]);
slbuild(model);
fprintf('Build complete.\n');

target = slrealtime(targetName);
if ~isConnected(target)
    connect(target);
end

% A running application must be stopped before another can be loaded. This
% is checked rather than assumed because the target is normally left running
% its startup application.
status = target.status();
% R2024b returns the execution state as a character vector; newer releases
% return a status structure with EXECSTATUS. Normalize both forms so the
% deployment helper remains usable with the project-supported release.
if isstruct(status)
    isRunning = strcmp(status.execStatus, 'running');
else
    isRunning = strcmp(char(status), 'running');
end
if isRunning
    fprintf('Stopping the running application...\n');
    stop(target);
end

fprintf('Loading %s onto %s...\n', model, targetName);
load(target, model);
start(target);

% Survive a power cycle. Done AFTER a successful start so a broken
% application is never made the thing the target boots into.
setStartupApp(target, model);
fprintf('%s is running on %s and set as the startup application.\n', ...
    model, targetName);
end

function closeIfLoaded(model)
if bdIsLoaded(model)
    close_system(model, 0);
end
end
