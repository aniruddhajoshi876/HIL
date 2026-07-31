function results = run_inverter_hil_tests()
%RUN_INVERTER_HIL_TESTS Run the independent host-verifiable R2024b suite.

testFolder = fileparts(mfilename('fullpath'));
repoRoot = fileparts(fileparts(testFolder));
addpath(fullfile(repoRoot, 'inverter_hil'));

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
