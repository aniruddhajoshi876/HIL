classdef TestInverterDisclosure < matlab.unittest.TestCase
    methods (TestClassSetup)
        function addWorkspaceToPath(testCase)
            testCase.applyFixture(matlab.unittest.fixtures.PathFixture( ...
                TestInverterDisclosure.workspaceRoot()));
        end
    end

    methods (Test)
        function appDeclaresIndependentDisclosureStateAndHandles(testCase)
            source = TestInverterDisclosure.appSource();

            testCase.verifySubstring(source, ...
                'InverterExpanded = false(1, 4)');
            testCase.verifySubstring(source, 'InverterStatusGrids');
            testCase.verifySubstring(source, 'InverterDisclosureButtons');
            testCase.verifySubstring(source, ...
                'function onInverterDisclosurePushed(app, source, ~)');
            testCase.verifySubstring(source, ...
                'function setInverterExpanded(app, channel, expanded)');
            testCase.verifySubstring(source, ...
                'find(app.InverterDisclosureButtons == source, 1)');
        end

        function appKeepsAllFormatterFieldsAndMovesOnlyFieldRows(testCase)
            source = TestInverterDisclosure.appSource();

            testCase.verifySubstring(source, ...
                'inverterhilgui.formatInverterPanel(app.Telemetry, ...');
            testCase.verifySubstring(source, ...
                'app.InverterFieldLabels(channel, field).Text = ...');
            testCase.verifySubstring(source, ...
                'app.InverterStatusGrids(channel).RowHeight');
            testCase.verifySubstring(source, ...
                'app.InverterFieldLabels(channel, field).Layout.Row');
            testCase.verifySubstring(source, ...
                'app.InverterFieldLabels(channel, field).Layout.Column = 2');
        end

        function appUsesTheSpecifiedDisclosureTexts(testCase)
            source = TestInverterDisclosure.appSource();

            testCase.verifySubstring(source, '''> DETAILS''');
            testCase.verifySubstring(source, '''v DETAILS''');
            testCase.verifySubstring(source, 'Expand inverter details');
            testCase.verifySubstring(source, 'Collapse inverter details');
        end
    end

    methods (Static, Access = private)
        function source = appSource()
            source = fileread(fullfile( ...
                TestInverterDisclosure.workspaceRoot(), 'inverter_hil_app.m'));
        end

        function root = workspaceRoot()
            here = fileparts(mfilename('fullpath'));
            root = fileparts(fileparts(here));
        end
    end
end
