% Open the project file. This also opens the System model
matlab.project.loadProject("BMS-Controller-HIL.prj");

% Load the test file that already has a test case defined with the right input.
sltest.testmanager.load('BMS_MIL_Test.mldatx');

% Run the test cases
autoTestObj = sltest.testmanager.run;

% Generate a .zip file with test results
sltest.testmanager.report(autoTestObj,'BatteryManagementSystem_MIL_TestResult.zip',...
    'IncludeTestResults',0,'IncludeComparisonSignalPlots',true,...
    'IncludeSimulationSignalPlots',true,'NumPlotRowsPerPage',3);
