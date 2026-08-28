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
                'function setInverterExpanded(app, channel, expanded)');
        end

        function clickingOneDisclosureButtonTogglesOnlyThatPanel(testCase)
            % Regression test for a real bug: ONINVERTERDISCLOSUREPUSHED
            % previously declared (app, source, ~), but this app's
            % CREATECALLBACKFCN wrapper invokes callbacks as
            % CALLBACK(APP, EVENT) -- two arguments, not three -- so SOURCE
            % silently received the event data (or []) instead of the
            % clicked button. The resulting APP.INVERTERDISCLOSUREBUTTONS
            % == SOURCE comparison threw "Matrix dimensions must agree",
            % which App Designer swallows into the console rather than a
            % visible dialog: from the operator's seat, clicking the button
            % did nothing. A source-substring check could not catch this --
            % only actually invoking the callback can. See git history for
            % the incident this regression test was written from.
            app = inverter_hil_app();
            closeApp = onCleanup(@() delete(app));

            buttons = TestInverterDisclosure.disclosureButtons();
            testCase.verifyEqual(numel(buttons), 4);
            [button1, grid1] = deal(buttons(1), buttons(1).Parent);
            [button2, grid2] = deal(buttons(2), buttons(2).Parent);

            testCase.verifyEqual(button1.Text, '> DETAILS');
            collapsedHeight1 = grid1.RowHeight;
            collapsedHeight2 = grid2.RowHeight;

            button1.ButtonPushedFcn(button1, struct('Source', button1));

            testCase.verifyEqual(button1.Text, 'v DETAILS');
            testCase.verifyNotEqual(grid1.RowHeight, collapsedHeight1);
            % Channel 2 must be untouched by channel 1's click.
            testCase.verifyEqual(button2.Text, '> DETAILS');
            testCase.verifyEqual(grid2.RowHeight, collapsedHeight2);

            button1.ButtonPushedFcn(button1, struct('Source', button1));

            testCase.verifyEqual(button1.Text, '> DETAILS');
            testCase.verifyEqual(grid1.RowHeight, collapsedHeight1);
        end

        function appKeepsAllFormatterFieldsAndMovesOnlyFieldRows(testCase)
            source = TestInverterDisclosure.appSource();

            testCase.verifySubstring(source, ...
                'inverterhilgui.live_telemetry.formatInverterPanel(app.Telemetry, ...');
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

        function buttons = disclosureButtons()
            %DISCLOSUREBUTTONS Find the four DETAILS buttons in open figures.
            %   Located through the figure's own object tree rather than the
            %   app's (private) properties, matching how a real click
            %   reaches the button regardless of MATLAB access control.
            figures = findall(groot, 'Type', 'figure');
            candidates = findall(figures, 'Type', 'uibutton');
            buttons = candidates(contains({candidates.Text}, 'DETAILS'));
        end
    end
end
