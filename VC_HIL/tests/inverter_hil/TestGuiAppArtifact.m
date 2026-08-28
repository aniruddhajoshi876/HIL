classdef TestGuiAppArtifact < matlab.unittest.TestCase
    %TESTGUIAPPARTIFACT Guard the generated .mlapp against source drift.
    %
    %   In the workspace root the generated INVERTER_HIL_APP.MLAPP shadows its
    %   own source INVERTER_HIL_APP.M, so an edit to the .m that is not
    %   followed by BUILD_INVERTER_HIL_APP silently keeps the old app running
    %   and leaves no readable git diff. These tests make that drift a test
    %   failure instead of a review escape.

    methods (TestClassSetup)
        function addWorkspaceToPath(testCase)
            testCase.applyFixture(matlab.unittest.fixtures.PathFixture( ...
                TestGuiAppArtifact.workspaceRoot()));
        end
    end

    methods (Test)
        function generatedAppMatchesItsClassdefSource(testCase)
            appFile = TestGuiAppArtifact.appFile();
            if exist(appFile, 'file') ~= 2
                % A fresh clone without the binary must still pass the suite.
                testCase.log(1, ['inverter_hil_app.mlapp is absent; ' ...
                    'skipping the generated-app freshness check.']);
                return;
            end

            % The .mlapp is a plain zip. Unpack it under tempdir - never into
            % the workspace - and confirm the code part is present.
            folder = TestGuiAppArtifact.temporaryFolder(testCase);
            unzip(appFile, folder);
            documentFile = fullfile(folder, 'matlab', 'document.xml');
            testCase.verifyEqual(exist(documentFile, 'file'), 2, ...
                'The .mlapp must contain matlab/document.xml.');

            embedded = appdesigner.internal.serialization.FileReader( ...
                appFile).readMATLABCodeText();
            source = fileread(fullfile( ...
                TestGuiAppArtifact.workspaceRoot(), 'inverter_hil_app.m'));

            testCase.verifyEqual( ...
                TestGuiAppArtifact.normalize(embedded), ...
                TestGuiAppArtifact.normalize(source), ...
                ['inverter_hil_app.mlapp is stale. Re-run ' ...
                'build_inverter_hil_app in R2024b and commit both files.']);
        end

        function generatedAppIsStampedR2024b(testCase)
            appFile = TestGuiAppArtifact.appFile();
            if exist(appFile, 'file') ~= 2
                testCase.log(1, ['inverter_hil_app.mlapp is absent; ' ...
                    'skipping the release-stamp check.']);
                return;
            end

            metadata = appdesigner.internal.serialization.FileReader( ...
                appFile).readAppMetadata();

            testCase.verifyEqual(metadata.MATLABRelease, 'R2024b');
        end

        function hostHeartbeatTimeoutIsNeverLooserThanTheTarget(testCase)
            host = inverterhilgui.writes.hostHeartbeatTimeout();
            calibrated = defaultCalibration().guiHeartbeatTimeoutS;

            testCase.verifyTrue(isnumeric(host) && isscalar(host) && ...
                isreal(host) && isfinite(host) && host > 0);
            testCase.verifyLessThanOrEqual(host, calibrated, ...
                ['The GUI must never report the pedal interface healthy ' ...
                'for longer than the target-side fallback tolerates.']);
        end

        function theAppUsesTheDerivedHeartbeatTimeout(testCase)
            source = fileread(fullfile( ...
                TestGuiAppArtifact.workspaceRoot(), 'inverter_hil_app.m'));

            testCase.verifySubstring(source, ...
                'inverterhilgui.writes.hostHeartbeatTimeout()');
            testCase.verifyEmpty(regexp(source, ...
                'HeartbeatTimeoutS\s*=\s*[0-9]', 'once'), ...
                'The heartbeat timeout must not be hard-coded in the app.');
        end

        function highRateStreamingIsLabelledInactive(testCase)
            source = fileread(fullfile( ...
                TestGuiAppArtifact.workspaceRoot(), 'inverter_hil_app.m'));

            testCase.verifySubstring(source, 'InstrumentStatusLabel');
            testCase.verifySubstring(source, ...
                'HIGH-RATE INSTRUMENT STREAMING NOT REGISTERED');
        end
    end

    methods (Static, Access = private)
        function root = workspaceRoot()
            here = fileparts(mfilename('fullpath'));
            root = fileparts(fileparts(here));
        end

        function file = appFile()
            file = fullfile(TestGuiAppArtifact.workspaceRoot(), ...
                'inverter_hil_app.mlapp');
        end

        function text = normalize(text)
            text = strrep(text, char(13), '');
            text = strrep(text, newline, '');
        end

        function folder = temporaryFolder(testCase)
            fixture = testCase.applyFixture( ...
                matlab.unittest.fixtures.TemporaryFolderFixture);
            folder = fixture.Folder;
        end
    end
end
