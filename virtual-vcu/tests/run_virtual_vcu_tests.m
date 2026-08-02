function results = run_virtual_vcu_tests()
%RUN_VIRTUAL_VCU_TESTS Run the R2024b host-only virtual-VCU tests.
root = fileparts(fileparts(mfilename('fullpath')));
addpath(root);
suite = testsuite(fileparts(mfilename('fullpath')));
results = run(suite);
disp(table(results));
assert(all([results.Passed]), 'virtualvcu:TestsFailed', ...
    'Virtual-VCU tests failed.');
end
