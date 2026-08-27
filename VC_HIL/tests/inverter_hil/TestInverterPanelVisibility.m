classdef TestInverterPanelVisibility < matlab.unittest.TestCase
    methods (TestClassSetup)
        function addWorkspaceToPath(testCase)
            testCase.applyFixture(matlab.unittest.fixtures.PathFixture( ...
                TestInverterPanelVisibility.workspaceRoot()));
        end
    end

    methods (Test)
        function collapsedStateShowsOnlyTheThreeSummaryFields(testCase)
            [visible, rowHeights, names] = ...
                inverterhilgui.inverterPanelVisibility(false);

            testCase.verifyEqual(names, {'STATE', 'READY', 'CMD AGE', ...
                'TORQUE CMD', 'TORQUE ACT', 'SPEED', 'Id set/act', ...
                'Iq set/act', 'MOTOR TEMP', 'SWITCH TEMP', 'DERATING', ...
                'ACTIVE FAULT'});
            testCase.verifyEqual(visible, ...
                [false false false true true false false false true ...
                false false false]);
            testCase.verifyEqual(rowHeights, ...
                {0 0 0 20 20 0 0 0 20 0 0 0});
            testCase.verifyEqual(nnz(visible), 3);
        end

        function expandedStateShowsAllRemainingFields(testCase)
            [visible, rowHeights] = ...
                inverterhilgui.inverterPanelVisibility(true);

            testCase.verifyTrue(all(visible));
            testCase.verifyEqual(rowHeights, ...
                {20 20 20 20 20 20 20 20 20 20 20 20});
            testCase.verifyEqual(nnz(visible), 12);
            testCase.verifyEqual(12 - nnz( ...
                inverterhilgui.inverterPanelVisibility(false)), 9);
        end

        function malformedExpandedStateIsRejected(testCase)
            invalid = {1, 0, true(1, 2), [], 'false'};
            for index = 1:numel(invalid)
                testCase.verifyError(@() ...
                    inverterhilgui.inverterPanelVisibility(invalid{index}), ...
                    'inverterhilgui:InvalidExpandedState');
            end
        end

        function onePanelStateDoesNotAffectAnother(testCase)
            collapsed = inverterhilgui.inverterPanelVisibility(false);
            expanded = inverterhilgui.inverterPanelVisibility(true);

            testCase.verifyEqual(nnz(collapsed), 3);
            testCase.verifyEqual(nnz(expanded), 12);
            testCase.verifyEqual(nnz( ...
                inverterhilgui.inverterPanelVisibility(false)), 3);
        end
    end

    methods (Static, Access = private)
        function root = workspaceRoot()
            here = fileparts(mfilename('fullpath'));
            root = fileparts(fileparts(here));
        end
    end
end
