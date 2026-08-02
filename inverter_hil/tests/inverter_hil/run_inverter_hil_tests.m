function results = run_inverter_hil_tests()
%RUN_INVERTER_HIL_TESTS Run the independent host-verifiable R2024b suite.

testFolder = fileparts(mfilename('fullpath'));
% fileparts(fileparts(testFolder)) already resolves to .../HIL/inverter_hil
% (testFolder is .../HIL/inverter_hil/tests/inverter_hil), so this IS the
% package root already -- appending 'inverter_hil' again produced a
% nonexistent path (a silent MATLAB warning; harmless only because the
% +inverterhil/+inverterhilgui packages happened to already be reachable
% from elsewhere on the path).
repoRoot = fileparts(fileparts(testFolder));
addpath(repoRoot);

release = version('-release');
if ~strcmp(release, '2024b')
    error('inverterhil:test:WrongMatlabRelease', ...
        'Authoritative tests require R2024b; running %s.', release);
end

suite = matlab.unittest.TestSuite.fromFolder(testFolder, ...
    'IncludingSubfolders', true);
results = run(suite);
disp(results);

if ~all([results.Passed])
    error('inverterhil:test:Failure', ...
        '%d of %d inverter HIL tests did not pass.', ...
        sum(~[results.Passed]), numel(results));
end
end
