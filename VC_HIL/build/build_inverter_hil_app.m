function fileName = build_inverter_hil_app(overwrite)
%BUILD_INVERTER_HIL_APP Generate inverter_hil_app.mlapp from the classdef.
%
%   INVERTER_HIL_APP.M is the reviewable source of truth. This script builds
%   the app headlessly, serializes the resulting component tree together with
%   the unmodified class source, and writes INVERTER_HIL_APP.MLAPP beside it.
%   The binary file therefore never carries behavior that is not in the .m.
%
%   The generator refuses to run outside R2024b: the .mlapp format is release
%   stamped, and saving from a later release would silently upgrade an
%   authoritative artifact.
%
%   SHADOWING HAZARD - READ BEFORE EDITING INVERTER_HIL_APP.M
%   In this folder `which -all inverter_hil_app` returns the .MLAPP FIRST and
%   the .M second, so the generated binary SHADOWS its own source. Editing
%   inverter_hil_app.m and running the app without re-running this script
%   silently executes the OLD app, and because a .mlapp is a binary zip the
%   stale copy produces no readable git diff for a reviewer to catch.
%   Therefore: re-run BUILD_INVERTER_HIL_APP after every edit to
%   inverter_hil_app.m, and commit the two together.
%   TESTGUIAPPARTIFACT enforces this by comparing the code embedded in the
%   .mlapp against inverter_hil_app.m on every test run.

if nargin < 1 || isempty(overwrite)
    overwrite = true;
end

release = version('-release');
if ~strcmp(release, '2024b')
    error('inverterhilgui:WrongMatlabRelease', ...
        ['The operator app must be generated with R2024b; this session ' ...
        'is %s.'], release);
end

appRoot = fileparts(mfilename('fullpath'));
sourceFile = fullfile(appRoot, 'inverter_hil_app.m');
fileName = fullfile(appRoot, 'inverter_hil_app.mlapp');
if exist(sourceFile, 'file') ~= 2
    error('inverterhilgui:MissingAppSource', ...
        'The app source %s does not exist.', sourceFile);
end
if exist('appdesigner.internal.serialization.MLAPPSerializer', 'class') ~= 8
    error('inverterhilgui:MissingSerializer', ...
        'appdesigner.internal.serialization.MLAPPSerializer is not available.');
end

previousPath = addpath(appRoot);
restorePath = onCleanup(@() path(previousPath));

% The existing .mlapp shadows inverter_hil_app.m (see the header note), so
% constructing the app while it is still on disk would serialize the OLD
% component tree alongside the NEW source text. Remove it first so the
% classdef is unambiguously the thing being built.
if exist(fileName, 'file') == 2
    delete(fileName);
end
rehash path;
resolved = which('inverter_hil_app');
if ~strcmp(resolved, sourceFile)
    error('inverterhilgui:AppSourceShadowed', ...
        ['inverter_hil_app resolves to %s instead of the classdef %s; ' ...
        'refusing to generate from a shadowed source.'], resolved, ...
        sourceFile);
end

app = inverter_hil_app;
closeApp = onCleanup(@() delete(app));
drawnow;

serializer = appdesigner.internal.serialization.MLAPPSerializer( ...
    fileName, app.UIFigure);
serializer.ClassName = 'inverter_hil_app';
serializer.MatlabCodeText = fileread(sourceFile);
serializer.OverwriteTargetFile = logical(overwrite);
serializer.save();

clear closeApp;
clear restorePath;

if exist(fileName, 'file') ~= 2
    error('inverterhilgui:AppGenerationFailed', ...
        'The serializer did not produce %s.', fileName);
end
info = dir(fileName);
fprintf('Wrote %s (%d bytes) with R2024b.\n', fileName, info.bytes);
end
