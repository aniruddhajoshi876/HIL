%Prject tests for simulink projects: it also gives an example of script to
%define tests.
classdef Prjtest < matlab.unittest.TestCase
    %% Prerequisites
    % List any prerequisites of this test, e.g. a connected target

    %% Parameters

    properties
        %Constant properties you use during your test

        checkResults;
    end

    %% Initialisation

    methods(TestClassSetup)
        %Methods in here are executed when the test object is created
        function ClassSetup(obj)
            proj = currentProject;
            obj.checkResults = proj.runChecks;
        end
    end

    methods(TestClassTeardown)
        %Methods in here are executed when the test object is destroyed
        function ClassTeardown(obj)
            fprintf('TestClassTeardown\n');
        end
    end

    methods(TestMethodSetup)
        %Methods in here are executed before every test method is ran
        function MethodSetup(obj)
            fprintf('TestMethodSetup\n');
        end
    end

    methods(TestMethodTeardown)
        %Methods in here are executed after every test method is ran
        function MethodTeardown(obj)
            fprintf('TestMethodTeardown\n');
        end
    end

    %% Tests

    methods (Test)
      
        % All project definition files are under source control.
        function ProjectDefinitionFilesUnderSourceControl(obj)
            obj.verifyEqual(obj.checkResults(1).Passed, true);
        end

        % All files in the project are under source control.
        function AllProjectFilesUnderSourceControl(obj)
            obj.verifyEqual(obj.checkResults(2).Passed, true);
        end

        % Not used due to Unreleased folder in the template
        % All files under source control are in the project.
        %function AllFilesUnderSourceControlInProject(obj)
        %   obj.verifyEqual(obj.checkResults(3).Passed, true);
        %end

        % All project folders on the MATLAB search path are on the project path.
        function ProjectFoldersExist(obj)
            obj.verifyEqual(obj.checkResults(4).Passed, true);
        end

        % All projects in sub-folders are referenced by this project
        function ProjectFilesExist(obj)
            obj.verifyEqual(obj.checkResults(5).Passed, true);
        end

        % All project folders on the MATLAB search path are on the project path.
        function ProjectPath(obj)
            obj.verifyEqual(obj.checkResults(6).Passed, true);
        end

        % All projects in sub-folders are referenced by this project.
        function ReferencedSubprojects(obj)
            obj.verifyEqual(obj.checkResults(7).Passed, true);
        end

        % Check for project files with unsaved changes.
        function UnsavedProjectFiles(obj)
            obj.verifyEqual(obj.checkResults(8).Passed, true);
        end

        % Not used due to inconsistent results depending on releases
        % All derived files in the project are up-to-date
        %function OutOfDateDerivedFiles(obj)
        %    obj.verifyEqual(obj.checkResults(9).Passed, true);
        %end

        % There are no slprj or sfprj folders in the project.
        function SLPRJ(obj)
            obj.verifyEqual(obj.checkResults(10).Passed, true);
        end

        % Model files saved in a different format (MDL or SLX) are added to the project.
        % The original files are not currently in the project.
        function MDLToSLX(obj)
            obj.verifyEqual(obj.checkResults(11).Passed, true);
        end


    end

    %% Helper functions
    %Utils you use in your test
    methods(Access = private)
        function str = getCorrectTeststring(obj)
            str = obj.testStringTarget;
        end

        function str = getInvalidTestString(obj)
            str ='InvalidTestSTring';
        end
    end

end
