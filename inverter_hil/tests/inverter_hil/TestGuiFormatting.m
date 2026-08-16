classdef TestGuiFormatting < matlab.unittest.TestCase
    methods (TestClassSetup)
        function addWorkspaceToPath(testCase)
            testCase.applyFixture(matlab.unittest.fixtures.PathFixture( ...
                TestGuiFormatting.workspaceRoot()));
        end
    end

    methods (Test)
        function torqueCountsShowBothCandidateScales(testCase)
            text = inverterhilgui.formatTorqueCandidates(8192);

            testCase.verifyTrue(text.hasData);
            testCase.verifyEqual(text.raw, '8192');
            testCase.verifyEqual(text.nm256, '32.000');
            testCase.verifyEqual(text.nm512, '16.000');
            testCase.verifySubstring(text.summary, '1/256');
            testCase.verifySubstring(text.summary, '1/512');
            testCase.verifySubstring(text.summary, '8192');

            negative = inverterhilgui.formatTorqueCandidates(-8192);
            testCase.verifyEqual(negative.nm256, '-32.000');
            testCase.verifyEqual(negative.nm512, '-16.000');

            endpoints = inverterhilgui.formatTorqueCandidates(32767);
            testCase.verifyEqual(endpoints.nm512, '63.998');
            testCase.verifyEqual(endpoints.nm256, '127.996');
        end

        function torqueFormattingShowsDashesWithoutData(testCase)
            invalid = {NaN, Inf, [], 0.5, 40000, -40000, 'x', complex(1, 1)};
            for index = 1:numel(invalid)
                text = inverterhilgui.formatTorqueCandidates(invalid{index});
                testCase.verifyFalse(text.hasData, sprintf('%d', index));
                testCase.verifyEqual(text.raw, '--');
                testCase.verifyEqual(text.nm256, '--');
                testCase.verifyEqual(text.nm512, '--');
                testCase.verifyEqual(text.summary, '--');
            end
        end

        function measurementsCarryRawCountsAndCaptureStatus(testCase)
            text = inverterhilgui.formatMeasurement(400.5, 25632, 'V', true);

            testCase.verifyTrue(text.hasData);
            testCase.verifyEqual(text.value, '400.500 V');
            testCase.verifyEqual(text.raw, '25632');
            testCase.verifyEqual(text.status, 'CAPTURE PENDING');
            testCase.verifySubstring(text.combined, '25632');
            testCase.verifySubstring(text.combined, 'CAPTURE PENDING');

            quiet = inverterhilgui.formatMeasurement(37.25, 298, 'C', false);
            testCase.verifyEmpty(quiet.status);
            testCase.verifyEqual(quiet.combined, '37.250 C (298 cnt)');

            blank = inverterhilgui.formatMeasurement(NaN, NaN, 'V', true);
            testCase.verifyFalse(blank.hasData);
            testCase.verifyEqual(blank.combined, '--');
            testCase.verifyEqual(blank.value, '--');
        end

        function pinStateIsTextPlusColourNeverColourAlone(testCase)
            theme = inverterhilgui.guiTheme();

            on = inverterhilgui.formatPinState(true);
            testCase.verifyEqual(on.text, 'ON');
            testCase.verifyTrue(on.known);
            testCase.verifyEqual(on.color, theme.color.healthy);

            off = inverterhilgui.formatPinState(false);
            testCase.verifyEqual(off.text, 'OFF');
            testCase.verifyTrue(off.known);
            testCase.verifyNotEqual(off.color, on.color);

            unknown = {[], NaN, 2, -1, 'on', [true true], complex(1, 1)};
            for index = 1:numel(unknown)
                display = inverterhilgui.formatPinState(unknown{index});
                testCase.verifyFalse(display.known, sprintf('%d', index));
                testCase.verifyEqual(display.text, '--');
            end

            % Text alone must distinguish every state.
            texts = {on.text, off.text, '--'};
            testCase.verifyEqual(numel(unique(texts)), 3);
        end

        function transitionGuardsCoverEveryRequiredCondition(testCase)
            snapshot = struct( ...
                'mainButton', true, ...
                'brakePercent', 35, ...
                'dcLink12V', 400, ...
                'dcLink34V', 120, ...
                'plausibilityOk', false);
            guards = inverterhilgui.evaluateTransitionGuards(snapshot, ...
                struct('brakePercent', 20, 'dcLinkMinimumV', 350));

            testCase.verifyEqual(numel(guards), 5);
            names = {guards.name};
            testCase.verifyEqual(names, {'Main button', 'Brake threshold', ...
                'DC-link pair 1/2', 'DC-link pair 3/4', ...
                'Driver-input plausibility'});
            testCase.verifyTrue(guards(1).pass);
            testCase.verifyTrue(guards(2).pass);
            testCase.verifyEqual(guards(2).actual, '35.0 %');
            testCase.verifyEqual(guards(2).required, '>= 20.0 %');
            testCase.verifyTrue(guards(3).pass);
            testCase.verifyFalse(guards(4).pass);
            testCase.verifyEqual(guards(4).actual, '120.0 V');
            testCase.verifyFalse(guards(5).pass);
            testCase.verifyTrue(all([guards.known]));
        end

        function unknownGuardsAreNeverShownAsPassing(testCase)
            guards = inverterhilgui.evaluateTransitionGuards( ...
                inverterhilgui.blankTelemetry().guards, struct());

            testCase.verifyEqual(numel(guards), 5);
            testCase.verifyFalse(any([guards.pass]));
            testCase.verifyFalse(any([guards.known]));
            for index = 1:numel(guards)
                testCase.verifyEqual(guards(index).actual, '--');
            end

            malformed = inverterhilgui.evaluateTransitionGuards(42, struct());
            testCase.verifyEqual(numel(malformed), 5);
            testCase.verifyFalse(any([malformed.pass]));
        end

        function inverterPanelsDoNotLeakBetweenChannels(testCase)
            snapshot = inverterhilgui.blankTelemetry();
            snapshot.inverter(2).state = 'DRIVE';
            snapshot.inverter(2).ready = true;
            snapshot.inverter(2).commandAgeS = 0.004;
            snapshot.inverter(2).torqueCommandRaw = 8192;
            snapshot.inverter(2).torqueActualRaw = -4096;
            snapshot.inverter(2).speedRpm = 2500;
            snapshot.inverter(2).idSetpointA = 10;
            snapshot.inverter(2).idActualA = 9.5;
            snapshot.inverter(2).motorTemperatureC = 55.5;
            snapshot.inverter(2).motorTemperatureRaw = 444;
            snapshot.inverter(2).derating = true;
            snapshot.inverter(2).activeFault = 'OVERTEMP';

            populated = inverterhilgui.formatInverterPanel(snapshot, 2);
            testCase.verifyEqual(populated.title, 'INV2');
            testCase.verifyEqual(populated.corner, 'FR');
            testCase.verifyEqual(populated.state, 'DRIVE');
            testCase.verifyEqual(populated.ready, 'READY');
            testCase.verifyEqual(populated.commandAge, '0.004 s');
            testCase.verifySubstring(populated.torqueCommand, '32.000');
            testCase.verifySubstring(populated.torqueCommand, '16.000');
            testCase.verifySubstring(populated.torqueActual, '-8.000');
            testCase.verifyEqual(populated.speed, '2500 rpm');
            testCase.verifyEqual(populated.idCurrent, '10.0 / 9.5 A');
            testCase.verifySubstring(populated.motorTemperature, '444');
            testCase.verifySubstring(populated.motorTemperature, ...
                'CAPTURE PENDING');
            testCase.verifyEqual(populated.derating, 'ACTIVE');
            testCase.verifyEqual(populated.activeFault, 'OVERTEMP');

            expectedCorners = struct('c1', 'FL', 'c3', 'RR', 'c4', 'RL');
            for channel = [1 3 4]
                other = inverterhilgui.formatInverterPanel(snapshot, channel);
                testCase.verifyEqual(other.title, sprintf('INV%d', channel));
                testCase.verifyEqual(other.corner, ...
                    expectedCorners.(sprintf('c%d', channel)));
                testCase.verifyEqual(other.state, '--');
                testCase.verifyEqual(other.torqueCommand, '--');
                testCase.verifyEqual(other.speed, '--');
                testCase.verifyEqual(other.motorTemperature, '--');
                testCase.verifyEqual(other.activeFault, 'NONE');
                testCase.verifyFalse(other.hasData);
            end

            bad = inverterhilgui.formatInverterPanel(snapshot, 5);
            testCase.verifyEqual(bad.title, '--');
            testCase.verifyFalse(bad.hasData);
        end

        function cornerLabelsUseConfirmedMapping(testCase)
            % Operator-confirmed 2026-08-01: 1=FL, 2=FR, 3=RR, 4=RL. Pins the
            % mapping so a silent reordering is caught. Note this guards the
            % recorded mapping only -- no test can confirm which physical
            % wheel an Ephorus index actually drives.
            expected = {'FL', 'FR', 'RR', 'RL'};
            snapshot = inverterhilgui.blankTelemetry();
            for channel = 1:4
                panel = inverterhilgui.formatInverterPanel(snapshot, channel);
                testCase.verifyEqual(panel.corner, expected{channel});
                testCase.verifyTrue(panel.cornerVerified);
                testCase.verifyEqual(panel.title, sprintf('INV%d', channel));
            end
        end

        function invalidIndexKeepsUnverifiedPlaceholder(testCase)
            % An out-of-range index must not index into the corner list; it
            % keeps the placeholder and reports the mapping as unconfirmed.
            snapshot = inverterhilgui.blankTelemetry();
            for badIndex = [0 5 2.5 NaN]
                panel = inverterhilgui.formatInverterPanel(snapshot, badIndex);
                testCase.verifyEqual(panel.corner, 'UNVERIFIED');
                testCase.verifyFalse(panel.cornerVerified);
                testCase.verifyEqual(panel.title, '--');
            end
        end

        function stateCardsClassifySequence(testCase)
            testCase.verifyEqual(inverterhilgui.stateCardStyle( ...
                'PRECHARGING', 'LV_ON'), 'passed');
            testCase.verifyEqual(inverterhilgui.stateCardStyle( ...
                'PRECHARGING', 'PRECHARGING'), 'active');
            testCase.verifyEqual(inverterhilgui.stateCardStyle( ...
                'PRECHARGING', 'ENABLE'), 'upcoming');
            testCase.verifyEqual(inverterhilgui.stateCardStyle('', ...
                'ENABLE'), 'unknown');
        end

        function vcuStateEntryResetsOnChangeAndAdvancesWhileHeld(testCase)
            % Regression test: TIME IN STATE previously never moved because
            % nothing ever updated app.Telemetry.vcu.timeInStateS -- it was
            % initialized to NaN in blankTelemetry.m and left there forever.
            [entered, elapsed] = inverterhilgui.trackVcuStateEntry( ...
                'LV_ON', '', NaN, 100.0);
            testCase.verifyEqual(entered, 100.0);
            testCase.verifyEqual(elapsed, 0.0);

            % Same state on a later tick: entry timestamp is held, elapsed
            % time keeps advancing -- this is the live-incrementing timer.
            [entered2, elapsed2] = inverterhilgui.trackVcuStateEntry( ...
                'LV_ON', 'LV_ON', entered, 102.5);
            testCase.verifyEqual(entered2, 100.0);
            testCase.verifyEqual(elapsed2, 2.5);

            % A real state change resets the clock to 0 s elapsed.
            [entered3, elapsed3] = inverterhilgui.trackVcuStateEntry( ...
                'PRECHARGING', 'LV_ON', entered2, 102.5);
            testCase.verifyEqual(entered3, 102.5);
            testCase.verifyEqual(elapsed3, 0.0);

            % Reconnecting with a stale/unknown previous timestamp (NaN)
            % also resets, even if the state string happens to match --
            % guards against a fabricated elapsed time across a disconnect.
            [entered4, elapsed4] = inverterhilgui.trackVcuStateEntry( ...
                'PRECHARGING', 'PRECHARGING', NaN, 200.0);
            testCase.verifyEqual(entered4, 200.0);
            testCase.verifyEqual(elapsed4, 0.0);
        end

        function canRatesAreMeasuredNotAssumed(testCase)
            observation = struct( ...
                'id', uint32(hex2dec('186')), ...
                'name', 'CTRL INV1', ...
                'signal', 'torque limit +', ...
                'value', '8192 cnt', ...
                'timestampsS', 0:0.005:0.05, ...
                'lastChangeS', 0.05);
            rows = inverterhilgui.canRowModel(observation, 0.052);

            testCase.verifyEqual(numel(rows), 1);
            testCase.verifyEqual(rows(1).id, '0x186');
            testCase.verifyEqual(rows(1).rateHz, 200, 'RelTol', 1e-9);
            testCase.verifyEqual(rows(1).rate, '200.0 Hz');
            testCase.verifyEqual(rows(1).live, 'LIVE');
            testCase.verifyTrue(rows(1).highlight);

            slow = observation;
            slow.timestampsS = 0:0.02:0.1;
            slowRows = inverterhilgui.canRowModel(slow, 0.101);
            testCase.verifyEqual(slowRows(1).rateHz, 50, 'RelTol', 1e-9);

            single = observation;
            single.timestampsS = 0.05;
            singleRows = inverterhilgui.canRowModel(single, 0.052);
            testCase.verifyEqual(singleRows(1).rate, '--', ...
                'A single timestamp cannot imply the 5 ms nominal rate.');
            testCase.verifyEqual(singleRows(1).rateHz, NaN);
        end

        function canRowsMarkStaleAndUnchangedTraffic(testCase)
            observation = struct( ...
                'id', uint32(hex2dec('400')), 'name', 'GENERAL', ...
                'signal', 'dc link 1/2', 'value', '400.0 V', ...
                'timestampsS', 10:0.005:10.05, 'lastChangeS', 9.0);

            fresh = inverterhilgui.canRowModel(observation, 10.052);
            testCase.verifyEqual(fresh(1).live, 'LIVE');
            testCase.verifyFalse(fresh(1).highlight, ...
                'An old payload change must not stay highlighted.');

            recent = observation;
            recent.lastChangeS = 10.05;
            testCase.verifyTrue( ...
                inverterhilgui.canRowModel(recent, 10.052).highlight);

            stale = inverterhilgui.canRowModel(observation, 15.0);
            testCase.verifyEqual(stale(1).live, 'STALE');
            testCase.verifyFalse(stale(1).highlight);
        end

        function blankCanObservationsRenderAsNoData(testCase)
            snapshot = inverterhilgui.blankTelemetry();
            rows = inverterhilgui.canRowModel(snapshot.can.rx, 1.0);

            testCase.verifyEqual(numel(rows), 5);
            expectedIds = {'0x1F5', '0x186', '0x196', '0x1A6', '0x1B6'};
            for index = 1:numel(rows)
                testCase.verifyEqual(rows(index).id, expectedIds{index});
                testCase.verifyEqual(rows(index).live, 'NO DATA');
                testCase.verifyEqual(rows(index).rate, '--');
                testCase.verifyEqual(rows(index).value, '--');
                testCase.verifyFalse(rows(index).highlight);
            end

            % Nine Ephorus status frames THEN the four synchronized sensor
            % frames, in the order BUILD_INVERTER_HIL_MODEL writes them.
            % Order is load-bearing, not cosmetic: APPLYLIVETXFRAMES matches
            % payload rows to these observations positionally, so a
            % re-ordering here would silently label every sensor row with
            % another frame's bytes.
            txRows = inverterhilgui.canRowModel(snapshot.can.tx, 1.0);
            testCase.verifyEqual(numel(txRows), 13);
            testCase.verifyEqual({txRows.id}, {'0x383', '0x385', '0x393', ...
                '0x395', '0x3A3', '0x3A5', '0x3B3', '0x3B5', '0x400', ...
                '0x034', '0x032', '0x076', '0x2B0'});
            testCase.verifyEqual({txRows(10:13).name}, ...
                {'MTI ACCEL', 'MTI RATE', 'MTI VELOCITY', 'LWS STEERING'});
            % Sensor rows obey the same no-invented-values rule as the rest.
            for index = 10:13
                testCase.verifyEqual(txRows(index).live, 'NO DATA');
                testCase.verifyEqual(txRows(index).value, '--');
            end

            testCase.verifyEmpty(inverterhilgui.canRowModel([], 1.0));

            % COUNT is shown verbatim from the target, never fabricated: an
            % unread count stays dashes rather than rendering as 0, which is
            % a real count a silent-but-alive transmitter could report.
            for index = 1:numel(rows)
                testCase.verifyEqual(rows(index).count, '--');
            end
        end

        function canMessageCountsAreShownVerbatimOrNotAtAll(testCase)
            base = struct('id', uint32(hex2dec('186')), 'name', 'CTRL INV1', ...
                'signal', 'x', 'value', 'y', 'timestampsS', 1.0, ...
                'lastChangeS', 1.0, 'count', 8135);
            testCase.verifyEqual( ...
                inverterhilgui.canRowModel(base, 1.0).count, '8135');

            % A genuinely zero count is real data and must render as 0, not
            % as dashes: a transmitter that has sent nothing yet is a
            % meaningful, reportable state.
            zeroCount = base;
            zeroCount.count = 0;
            testCase.verifyEqual( ...
                inverterhilgui.canRowModel(zeroCount, 1.0).count, '0');

            % Anything that is not a whole, non-negative count is refused
            % rather than rounded or clamped into looking real.
            for bad = {NaN, -1, 2.5, [], [1 2], 'x'}
                item = base;
                item.count = bad{1};
                testCase.verifyEqual( ...
                    inverterhilgui.canRowModel(item, 1.0).count, '--', ...
                    sprintf('A malformed count must not render as a number.'));
            end
        end

        function canAckIsReportedFromControllerErrorCountersOnly(testCase)
            healthy = struct('busOff', false, 'errorWarning', false);

            % Transmitting with clean error counters is real evidence of
            % acknowledgement: an unacknowledged transmitter cannot stay out
            % of error-warning and bus-off (see INVERTERHILGUI.CANACKSTATUS).
            acked = inverterhilgui.canAckStatus(healthy, true);
            testCase.verifyTrue(acked.known);
            testCase.verifyTrue(acked.acknowledged);
            testCase.verifySubstring(acked.text, 'ACK OK');

            % A silent bus proves nothing either way, so a stopped
            % transmitter must never be credited with acknowledgement.
            silent = inverterhilgui.canAckStatus(healthy, false);
            testCase.verifyFalse(silent.known);
            testCase.verifyEmpty(silent.acknowledged);
            testCase.verifyEqual(silent.text, '--');

            busOff = inverterhilgui.canAckStatus( ...
                struct('busOff', true, 'errorWarning', false), true);
            testCase.verifyTrue(busOff.known);
            testCase.verifyFalse(busOff.acknowledged);
            testCase.verifySubstring(busOff.text, 'NOT ACKED');

            warned = inverterhilgui.canAckStatus( ...
                struct('busOff', false, 'errorWarning', true), true);
            testCase.verifyTrue(warned.known);
            testCase.verifyFalse(warned.acknowledged);
            testCase.verifySubstring(warned.text, 'ACK ERRORS');

            % Bus-off outranks a clear error-warning flag: it is the
            % terminal state of a transmitter nobody is acknowledging.
            both = inverterhilgui.canAckStatus( ...
                struct('busOff', true, 'errorWarning', true), true);
            testCase.verifyFalse(both.acknowledged);

            % An unread controller reports unknown, never a healthy bus, so
            % a failed telemetry read can never look like a working one.
            blank = inverterhilgui.blankTelemetry().can.diagnostics;
            unread = inverterhilgui.canAckStatus(blank, true);
            testCase.verifyFalse(unread.known);
            testCase.verifyEmpty(unread.acknowledged);
            testCase.verifyEqual(unread.text, '--');

            for bad = {struct('busOff', false), struct('errorWarning', false), ...
                    struct(), [], 'x'}
                result = inverterhilgui.canAckStatus(bad{1}, true);
                testCase.verifyFalse(result.known, ...
                    'A partial or malformed diagnostics block must not decide.');
                testCase.verifyEmpty(result.acknowledged);
            end
        end

        function blankTelemetryContainsNoFabricatedValues(testCase)
            snapshot = inverterhilgui.blankTelemetry();

            testCase.verifyFalse(snapshot.valid);
            testCase.verifyEqual(snapshot.targetTimeS, NaN);
            testCase.verifyEmpty(snapshot.vcu.state);
            testCase.verifyEqual(snapshot.vcu.timeInStateS, NaN);
            testCase.verifyFalse(snapshot.vcu.errorKnown);
            testCase.verifyEqual(snapshot.analogInV, nan(1, 4));
            testCase.verifyEqual(snapshot.pedals.appliedV, nan(1, 4));
            testCase.verifyFalse(snapshot.pedals.armed);
            testCase.verifyFalse(snapshot.io.healthy);
            testCase.verifyEqual(numel(snapshot.pins), 5);
            testCase.verifyEqual({snapshot.pins.name}, {'VC_SD_OUT', ...
                'MAIN_EN_OUT', 'PRECH_EN_OUT', 'INV_CTRL_EN', ...
                'INV_CTRL_DIS'});
            testCase.verifyEqual({snapshot.pins.testPoint}, {'TP6', 'TP7', ...
                'TP8', 'TP9', 'TP10'});
            for index = 1:numel(snapshot.pins)
                testCase.verifyEmpty(snapshot.pins(index).state);
            end
            testCase.verifyEqual(numel(snapshot.dcLink), 2);
            for index = 1:2
                testCase.verifyEqual(snapshot.dcLink(index).voltageV, NaN);
                testCase.verifyEqual(snapshot.dcLink(index).rawCount, NaN);
                testCase.verifyTrue(snapshot.dcLink(index).capturePending);
            end
            testCase.verifyEqual(snapshot.switchingFrequencyKHz, NaN);
            testCase.verifyEqual(numel(snapshot.inverter), 4);
            testCase.verifyEqual([snapshot.inverter.index], 1:4);
        end

        function themeUsesTheSpecifiedConsolePalette(testCase)
            % VS Code 2017-style dark console: near-black background with
            % white primary text and readable secondary text on panels.
            theme = inverterhilgui.guiTheme();

            background = theme.color.background;
            primary = theme.color.primaryText;
            testCase.verifyLessThan(mean(background), 0.2, ...
                'Background must be near-black.');
            testCase.verifyGreaterThan(mean(primary), 0.8, ...
                'Primary text must be light.');
            testCase.verifyGreaterThan( ...
                TestGuiFormatting.contrastRatio(primary, background), 4.5, ...
                'Primary text on background must meet WCAG AA (4.5:1).');
            testCase.verifyGreaterThan( ...
                TestGuiFormatting.contrastRatio(theme.color.secondaryText, ...
                theme.color.panel), 4.5, ...
                'Secondary text on panel must meet WCAG AA (4.5:1).');
            % The tab header bar covers MATLAB's unstyleable white native
            % strip, so it must be BLACK with WHITE text -- not merely dark.
            % Asserted as exact endpoints because "near-black" was what let
            % the strip drift to 252526/F0F0F0 and read as washed out.
            testCase.verifyEqual(theme.color.tabBar, [0 0 0], ...
                'Tab header background must be pure black.');
            testCase.verifyEqual(theme.color.tabBarText, [1 1 1], ...
                'Tab header text must be pure white.');
            % An unselected tab is dimmer, but must still be comfortably
            % readable rather than merely present.
            testCase.verifyGreaterThan( ...
                TestGuiFormatting.contrastRatio( ...
                theme.color.tabBarInactiveText, theme.color.tabBar), 7, ...
                'Unselected tab text must meet WCAG AAA (7:1) on black.');
            % Regression test for a real bug: the active ERROR state-strip
            % card set FontColor and BackgroundColor to the SAME
            % theme.color.fault, so the word "ERROR" rendered invisible
            % against its own highlight. REFRESHSTATESTRIP now pairs the
            % fault background with theme.color.background as the font
            % color; assert that pairing actually stays legible rather
            % than just non-identical.
            testCase.verifyGreaterThan( ...
                TestGuiFormatting.contrastRatio( ...
                theme.color.background, theme.color.fault), 4.5, ...
                'ERROR card text on its fault-red highlight must meet WCAG AA (4.5:1).');
            testCase.verifySubstring(theme.text.torqueBanner, ...
                'TORQUE SCALE UNVERIFIED');
            testCase.verifySubstring(theme.text.torqueBanner, '1/512');
            testCase.verifySubstring(theme.text.torqueBanner, ...
                'ephorus3-v1.03-provisional-1over512');
            % Still the placeholder for an out-of-range index; the confirmed
            % 1=FL/2=FR/3=RR/4=RL mapping is asserted by
            % CORNERLABELSUSECONFIRMEDMAPPING.
            testCase.verifyEqual(theme.text.cornerLabel, 'UNVERIFIED');
            testCase.verifyEqual(theme.text.noData, '--');
        end
    end

    methods (Static, Access = private)
        function ratio = contrastRatio(foreground, background)
            %CONTRASTRATIO WCAG 2.1 relative-luminance contrast ratio.
            lumA = TestGuiFormatting.relativeLuminance(foreground);
            lumB = TestGuiFormatting.relativeLuminance(background);
            ratio = (max(lumA, lumB) + 0.05) / (min(lumA, lumB) + 0.05);
        end

        function lum = relativeLuminance(rgb)
            %RELATIVELUMINANCE WCAG 2.1 relative luminance of a 0-1 RGB row.
            channel = rgb;
            low = channel <= 0.03928;
            channel(low) = channel(low) / 12.92;
            channel(~low) = ((channel(~low) + 0.055) / 1.055) .^ 2.4;
            lum = 0.2126 * channel(1) + 0.7152 * channel(2) + ...
                0.0722 * channel(3);
        end
    end

    methods (Static, Access = private)
        function root = workspaceRoot()
            here = fileparts(mfilename('fullpath'));
            root = fileparts(fileparts(here));
        end
    end
end
