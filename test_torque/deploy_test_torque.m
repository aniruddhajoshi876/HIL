function deploy_test_torque(targetName)
%DEPLOY_TEST_TORQUE Build TEST_TORQUE and run it on the Speedgoat target.
%
%   DEPLOY_TEST_TORQUE() builds the real-time application, stops whatever
%   the target is currently running, loads and starts the new application,
%   and leaves it installed as the startup application so a power cycle
%   brings it back. DEPLOY_TEST_TORQUE(NAME) targets another machine.
%
%   Identical stop-before-load / PATH-prepending sequence to
%   inverter_hil/deploy_inverter_hil.m -- see that file's header comment
%   for why both steps are load-bearing, not optional. Deploying this
%   model WILL stop whatever inverter_hil (or anything else) is currently
%   running on the target; that is expected.

if nargin < 1 || isempty(targetName)
    targetName = 'TargetPC1';
end

root = test_torque_setup();
model = 'test_torque';

if bdIsLoaded(model)
    close_system(model, 0);
end
load_system(fullfile(root, [model '.slx']));
cleanupModel = onCleanup(@() closeIfLoaded(model)); %#ok<NASGU>

fprintf('Building %s...\n', model);
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

status = target.status();
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

setStartupApp(target, model);
fprintf('%s is running on %s and set as the startup application.\n', ...
    model, targetName);
end

function closeIfLoaded(model)
if bdIsLoaded(model)
    close_system(model, 0);
end
end
