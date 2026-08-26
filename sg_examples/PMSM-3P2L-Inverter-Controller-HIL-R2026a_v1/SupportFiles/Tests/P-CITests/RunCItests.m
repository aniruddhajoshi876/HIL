import matlab.unittest.TestRunner;
import matlab.unittest.TestSuite;
import matlab.unittest.Verbosity;
import matlab.unittest.plugins.XMLPlugin;
import matlab.unittest.plugins.TestReportPlugin;
import matlab.unittest.plugins.TAPPlugin;
import matlab.unittest.plugins.ToFile;
import matlab.unittest.parameters.Parameter;
import matlab.unittest.plugins.CodeCoveragePlugin;
import matlab.unittest.plugins.codecoverage.CoberturaFormat;
import matlab.unittest.Verbosity;

%Configure the environement (create a Config.m file in the project if needed)
try
    Config;
catch
    fprintf('No configuration script \n')
end
% Command to remove promts for CI implementation
sg.host.setUserPref('ShowHelpPrefMessage', false);

% Get current project   
projObj = currentProject;

% Create testresults folder in the test folder
mkdir(fullfile(projObj.RootFolder,'/SupportFiles/Tests/Results'))

% Creates a suite of tests from current projcet
% from the files marked as test
suite = TestSuite.fromProject(projObj);

% Create TestRunner object
runner = TestRunner.withTextOutput('OutputDetail', Verbosity.Detailed);

% Plugin that produces Test Anything Protocol stream
runner.addPlugin(TAPPlugin.producingOriginalFormat(ToFile(fullfile(projObj.RootFolder,'/SupportFiles/Tests/Results/results.tap'))));

% Construct plugin to write test results in XML format
runner.addPlugin(XMLPlugin.producingJUnitFormat(fullfile(projObj.RootFolder,'/SupportFiles/Tests/Results/junit.xml')));

% Construct plugin to write test results in XML format
runner.addPlugin(XMLPlugin.producingJUnitFormat(fullfile(projObj.RootFolder,'/SupportFiles/Tests/Results/results.xml')));

% Enable pushing test results to Simulink Test Manager
try
    runner.addSimulinkTestResults("ExportToFile",fullfile(projObj.RootFolder,'/SupportFiles/Tests/Results/stmresults.mldatx'));
catch
    fprintf('No results to push to simulink test manager')
end
% Run all tests in TestSuite array
results = runner.run(suite);

% Display test results
disp(results.table);

% Import Test Manager results file
try
    results = sltest.testmanager.importResults(fullfile(projObj.RootFolder,'/SupportFiles/Tests/Results/stmresults.mldatx'));
    filePath = fullfile(projObj.RootFolder,'/SupportFiles/Tests/Results/testreport.pdf');
    sltest.testmanager.report(results,filePath,...
        'Author','Jenkins',...
        'Title','Testsuite',...
        'IncludeMLVersion',true,...
        'IncludeTestResults',false,...
        'IncludeSimulationSignalPlots',false,...
        'IncludeComparisonSignalPlots',true,...
        'IncludeErrorMessage',false,...
        'NumPlotColumnsPerPage',1, ...
        'LaunchReport',false);
catch
    fprintf('No results from simulink test manager \n')
end
% gets the default config to the models again to avoid publishing the CI
% configuration
try
    Default_Config
catch
    fprintf('No default configuration script \n')
end

%clear results to avoid test manager hanging on to prompt when CI server (jenkins) will
%try to close matlab
try
    sltest.testmanager.clearResults;
    sltest.testmanager.clear;
catch 
    fprintf('no results in test manager : consider removing these lines from the script')
end
