% Open the project file. This also opens the System model
matlab.project.loadProject("eVTOL-Powertrain-HIL.prj");

% Load the test file that already has a test case defined with the right input.
sltest.testmanager.load('eVTOL_System_Test.mldatx');

% Run the test cases
autoTestObj = sltest.testmanager.run;

% Generate a .zip file with test results
sltest.testmanager.report(autoTestObj,'eVTOL_TestResult.zip',...
    'IncludeTestResults',0,'IncludeComparisonSignalPlots',true,...
    'IncludeSimulationSignalPlots',true,'NumPlotRowsPerPage',3);
