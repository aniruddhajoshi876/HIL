classdef inverter_hil_app < matlab.apps.AppBase
    %INVERTER_HIL_APP MFE26 VC inverter HIL operator dashboard.
    %
    %   This class is the reviewable source of truth for the operator GUI.
    %   BUILD_INVERTER_HIL_APP regenerates INVERTER_HIL_APP.MLAPP from it, so
    %   the binary app file never carries behavior that is not in this file.
    %
    %   The class is a thin shell: it constructs layout and delegates every
    %   decision to +INVERTERHILGUI. In particular
    %     * INVERTERHILGUI.CONTROLPOLICY is the single enable/disable
    %       authority; no callback below re-derives enable state.
    %     * INVERTERHILGUI.BLANKTELEMETRY supplies the honest no-data snapshot
    %       used whenever no target is connected. Nothing here invents,
    %       simulates, or animates telemetry, and there is no demo mode.
    %     * INVERTERHILGUI.TARGETSESSION is the only path to a Speedgoat, and
    %       it is always constructed without an injected backend here.
    %
    %   Plan open decisions 16 and 18 are UNRESOLVED; see
    %   INVERTERHILGUI.PARAMETERCONTRACT and INVERTERHILGUI.CONTROLPOLICY.

    properties (Access = public)
        UIFigure                  matlab.ui.Figure
        RootLayout                matlab.ui.container.GridLayout
        ToolbarLayout             matlab.ui.container.GridLayout
        TitleLabel                matlab.ui.control.Label
        TargetNameLabel           matlab.ui.control.Label
        ConnectionStateLabel      matlab.ui.control.Label
        ApplicationStateLabel     matlab.ui.control.Label
        ElapsedTimeLabel          matlab.ui.control.Label
        ConnectButton             matlab.ui.control.Button
        LoadButton                matlab.ui.control.Button
        StartButton               matlab.ui.control.Button
        StopButton                matlab.ui.control.Button
        ResetButton               matlab.ui.control.Button
        TorqueBannerLabel         matlab.ui.control.Label
        TabGroup                  matlab.ui.container.TabGroup
        TabBarPanel               matlab.ui.container.Panel
        TabButtons                matlab.ui.control.Button
        OverviewTab               matlab.ui.container.Tab
        InvertersTab              matlab.ui.container.Tab
        IoCanTab                  matlab.ui.container.Tab
        FaultsTab                 matlab.ui.container.Tab
        LoggingTab                matlab.ui.container.Tab
        StateStripLabels
        StateStripSeparators
        StateErrorLabel           matlab.ui.control.Label
        TimeInStateLabel          matlab.ui.control.Label
        GuardTable                matlab.ui.control.Table
        ThrottleSlider            matlab.ui.control.Slider
        ThrottleField             matlab.ui.control.NumericEditField
        ThrottleAppliedLabel      matlab.ui.control.Label
        BrakeSlider               matlab.ui.control.Slider
        BrakeField                matlab.ui.control.NumericEditField
        BrakeAppliedLabel         matlab.ui.control.Label
        SteeringDial              matlab.ui.control.Knob
        SteeringField             matlab.ui.control.NumericEditField
        SteeringAppliedLabel      matlab.ui.control.Label
        PedalVoltageLabels
        PlausibilityCheckBox      matlab.ui.control.CheckBox
        ExpertModeCheckBox        matlab.ui.control.CheckBox
        CoolingSwitch             matlab.ui.control.CheckBox
        ShutdownFeedbackSwitch    matlab.ui.control.CheckBox
        DigitalAppliedLabels
        PrechargeButton           matlab.ui.control.Button
        MainMomentaryButton       matlab.ui.control.Button
        MomentaryLabels
        DcLinkValueLabels
        DcLinkFlagLabels
        SwitchingFrequencyLabel   matlab.ui.control.Label
        PinNameLabels
        PinStateLabels
        AnalogInputLabels
        InverterFieldLabels
        InverterTitleLabels
        InverterCornerLabels
        InverterSourceLabel       matlab.ui.control.Label
        CanRxTable                matlab.ui.control.Table
        CanTxTable                matlab.ui.control.Table
        CanDiagnosticsLabel       matlab.ui.control.Label
        InstrumentStatusLabel     matlab.ui.control.Label
        SensorSteeringLabel       matlab.ui.control.Label
        SensorImuAccelLabel       matlab.ui.control.Label
        SensorImuRateLabel        matlab.ui.control.Label
        SensorImuVelocityLabel    matlab.ui.control.Label
        SensorCalibrationLabel    matlab.ui.control.Label
        SteeringDropoutCheckBox   matlab.ui.control.CheckBox
        SteeringStaleCheckBox     matlab.ui.control.CheckBox
        SteeringMalformedCheckBox matlab.ui.control.CheckBox
        SteeringInvalidStatusCheckBox matlab.ui.control.CheckBox
        SteeringAngleSentinelCheckBox matlab.ui.control.CheckBox
        SteeringSpeedSentinelCheckBox matlab.ui.control.CheckBox
        ImuDropoutCheckBox        matlab.ui.control.CheckBox
        ImuStaleCheckBox          matlab.ui.control.CheckBox
        ImuMalformedCheckBox      matlab.ui.control.CheckBox
        LwsCalibrationButton      matlab.ui.control.Button
        FaultMaskFields
        LoadTorqueFields
        ConnectedCheckBoxes
        DropControlField          matlab.ui.control.NumericEditField
        DropStatusField           matlab.ui.control.NumericEditField
        HeartbeatLabel            matlab.ui.control.Label
        FallbackLabel             matlab.ui.control.Label
        LogTable                  matlab.ui.control.Table
        ExportLogButton           matlab.ui.control.Button
        LogSummaryLabel           matlab.ui.control.Label
    end

    properties (Access = private)
        Theme
        Session
        Log
        Telemetry
        Policy
        StatusTimer
        % True while a CONNECT/LOAD/START/STOP/RESET call is in flight on
        % the Simulink Real-Time target. See ENTERTARGETSECTION.
        TargetBusy = false
        ThrottleCoalescer
        BrakeCoalescer
        % True only while the target's 1-ms CarMakerPedalDemand retainer owns
        % both pedals. This is the model selector's own liveness decision.
        CanPedalsDriving = false
        SteeringCoalescer
        % Last steering angle the operator REQUESTED via the dial or the
        % numeric field. Held here rather than read back off the widget so
        % REFRESHDRIVERINPUTS can show requested and applied side by side;
        % NaN until the operator actually moves the dial, so a never-touched
        % control shows dashes instead of a fabricated 0 deg.
        RequestedSteeringDeg = NaN
        % True while an XCP master (e.g. CarMaker over Ethernet) is
        % actively driving pedal demand, in which case it owns
        % hil_cmd_pedals_throttle/brake and the GUI becomes
        % diagnostic/read-only for that group (see
        % inverterhilgui.controlPolicy and POLLCOALESCERS). Set each poll
        % cycle by REFRESHLIVEIO from the live hil_cmd_xcp_pedals_active
        % target parameter (see TargetSession.readLiveIo) -- the same
        % model-side source-select flag the AO01-04 Switch blocks in
        % build_inverter_hil_model.m already read directly, so the GUI and
        % the model can no longer disagree about which source is live. Not
        % yet exercised against a real target (this codebase cannot reach
        % one -- see virtual-vcu/docs/carmaker_speedgoat_interface.md,
        % section 7's "Items not confirmed locally"), but the read path is
        % real and fails closed to false (GUI keeps/regains pedal write
        % ownership) on any read failure or disconnect. Reverts to GUI
        % write control the instant this goes false, with no separate
        % re-arm step.
        XcpDriving = false
        Heartbeat
        PrechargeSequence = uint32(0)
        MainButtonSequence = uint32(0)
        LwsCalibrationSequence = uint32(0)
        % Host timestamp of the last MAIN BUTTON momentary press, used to
        % show the NEXT TRANSITION guard's "Main button" row as PRESSED for
        % a short window after each push. MAIN_BTN_IN is now driven purely
        % by a ~200 ms edge pulse (see build_inverter_hil_model.m's Main
        % Button Pulse Generator), not a held level, so there is no
        % steady-state pin value worth polling -- a 200 ms pulse is also
        % shorter than this app's 250 ms poll period and could otherwise be
        % missed entirely between polls.
        MainButtonLastPressedS = -Inf
        % Previous poll's target transmit count, and whether it advanced
        % between the last two polls. INVERTERHILGUI.CANACKSTATUS requires
        % that genuine observation before it will report frames as
        % acknowledged -- see APPLYLIVETXFRAMES.
        LastTxMessageCount = NaN
        TxTransmitting = false
        InverterExpanded = false(1, 4)
        InverterStatusGrids
        InverterDisclosureButtons
        % Host time the VCU was last observed entering its current state.
        % NaN whenever state is not currently known, so time-in-state never
        % holds a stale value across a disconnect. See REFRESHLIVEIO.
        VcuStateEnteredS = NaN
        VcuStateLast = ''
        % Resolved at startup from inverterhilgui.hostHeartbeatTimeout so the
        % host can never report healthy longer than the target-side fallback.
        HeartbeatTimeoutS
        VcuStateNames = {'LV_ON', 'PRECHARGING', 'ENABLE', 'BUZZING', 'RTD'}
        PedalChannelNames = {'AO01 THR1', 'AO02 THR2', 'AO03 BRK1', ...
            'AO04 BRK2'}
        DigitalNames = {'cooling_switch', 'shutdown_feedback'}
        InverterFieldNames = {'STATE', 'READY', 'CMD AGE', 'TORQUE CMD', ...
            'TORQUE ACT', 'SPEED', 'Id set/act', 'Iq set/act', ...
            'MOTOR TEMP', 'SWITCH TEMP', 'DERATING', 'ACTIVE FAULT'}
    end

    methods (Access = private)

        function createComponents(app)
            %CREATECOMPONENTS Build the dense dark operator console.
            app.Theme = inverterhilgui.guiTheme();
            theme = app.Theme;

            app.UIFigure = uifigure('Visible', 'off');
            app.UIFigure.Name = 'MFE26 VC INVERTER HIL';
            app.UIFigure.Position = [40 40 1680 980];
            app.UIFigure.Color = theme.color.background;
            app.UIFigure.CloseRequestFcn = ...
                createCallbackFcn(app, @onCloseRequest, true);

            app.RootLayout = uigridlayout(app.UIFigure, [3 1]);
            app.RootLayout.RowHeight = {theme.spacing.toolbarHeight, 22, '1x'};
            app.RootLayout.ColumnWidth = {'1x'};
            app.RootLayout.BackgroundColor = theme.color.background;
            app.RootLayout.Padding = theme.spacing.padding;
            app.RootLayout.RowSpacing = theme.spacing.rowSpacing;

            app.createToolbar();
            app.createBanner();

            app.TabGroup = uitabgroup(app.RootLayout);
            app.TabGroup.Layout.Row = 3;
            app.TabGroup.TabLocation = 'top';
            % The native tab headers are intentionally blank: MATLAB does
            % not expose a supported dark header style in R2024b. The
            % readable custom bar below is the only visible tab navigation.
            app.OverviewTab = uitab(app.TabGroup, 'Title', '');
            app.InvertersTab = uitab(app.TabGroup, 'Title', '');
            app.IoCanTab = uitab(app.TabGroup, 'Title', '');
            app.FaultsTab = uitab(app.TabGroup, 'Title', '');
            app.LoggingTab = uitab(app.TabGroup, 'Title', '');
            tabs = [app.OverviewTab app.InvertersTab app.IoCanTab ...
                app.FaultsTab app.LoggingTab];
            set(tabs, 'BackgroundColor', theme.color.panel, ...
                'ForegroundColor', theme.color.primaryText);
            app.createTabBar();

            app.createOverviewTab();
            app.createInvertersTab();
            app.createIoCanTab();
            app.createFaultsTab();
            app.createLoggingTab();

            app.UIFigure.Visible = 'on';
        end

        function createTabBar(app)
            %CREATETABBAR Cover MATLAB's unstyleable native tab headers with
            %   a dark, keyboard/mouse-friendly navigation bar. The native
            %   tab pages remain the content model; these buttons only select
            %   those pages and supply the readable dark appearance.
            theme = app.Theme;
            app.TabBarPanel = uipanel(app.UIFigure, ...
                'Units', 'pixels', ...
                'Position', [0 0 1 1], ...
                'BackgroundColor', theme.color.tabBar, ...
                'BorderType', 'none');
            grid = uigridlayout(app.TabBarPanel, [1 5]);
            grid.Padding = [0 0 0 0];
            grid.ColumnSpacing = 1;
            titles = {'Overview', 'Inverters', 'I/O & CAN', ...
                'Faults & Scenarios', 'Logging'};
            pages = [app.OverviewTab app.InvertersTab app.IoCanTab ...
                app.FaultsTab app.LoggingTab];
            buttonArray = uibutton(grid);
            for index = 2:numel(titles)
                buttonArray(index) = uibutton(grid);
            end
            app.TabButtons = buttonArray;
            for index = 1:numel(titles)
                button = app.TabButtons(index);
                button.Text = titles{index};
                button.FontName = theme.font.name;
                button.FontSize = theme.font.body;
                button.FontWeight = 'bold';
                button.FontColor = theme.color.tabBarText;
                button.BackgroundColor = theme.color.tabBar;
                button.ButtonPushedFcn = ...
                    @(~, ~) app.selectTab(pages(index));
            end
            app.TabGroup.SelectionChangedFcn = ...
                @(~, ~) app.syncTabButtons();
            % No UIFIGURE.SIZECHANGEDFCN here. Assigning one warned at every
            % construction ('will not execute while AutoResizeChildren is set
            % to on') and then never ran, so it advertised a resize response
            % this app did not actually have. REFRESHALL re-derives the
            % overlay geometry on the status tick instead; see POSITIONTABBAR.
            drawnow;
            app.positionTabBar();
            uistack(app.TabBarPanel, 'top');
            app.syncTabButtons();
        end

        function positionTabBar(app)
            %POSITIONTABBAR Place the custom bar over the native white header.
            %   MATLAB uitabgroup has no supported header color property in
            %   R2024b, so the readable black strip is an overlay and its
            %   geometry has to match the native header exactly.
            %
            %   The header is derived from the tab group's own live bounds:
            %   POSITION covers the whole control, INNERPOSITION covers only
            %   the page area, so the band between the two tops IS the header.
            %   That holds at any window size and needs no magic numbers.
            %
            %   It previously used a fixed 42 px height and a +98 y offset,
            %   which only matched one particular window size. Worse, it ran
            %   once during construction, before the grid layout had settled,
            %   so it captured the tab group's pre-layout bounds and left the
            %   bar 250 px wide at mid-screen -- covering dashboard content
            %   while most of the white native strip stayed exposed.
            if isempty(app.TabBarPanel) || ~isvalid(app.TabBarPanel) || ...
                    isempty(app.TabGroup) || ~isvalid(app.TabGroup)
                return;
            end
            outer = app.TabGroup.Position;
            inner = app.TabGroup.InnerPosition;
            headerBottom = inner(2) + inner(4);
            headerHeight = (outer(2) + outer(4)) - headerBottom;
            if ~(headerHeight > 0) || ~(outer(3) > 0)
                return;
            end
            target = [outer(1), headerBottom, outer(3), headerHeight];
            if isequal(app.TabBarPanel.Position, target)
                return;
            end
            app.TabBarPanel.Position = target;
            uistack(app.TabBarPanel, 'top');
        end

        function selectTab(app, page)
            app.TabGroup.SelectedTab = page;
            app.syncTabButtons();
        end

        function syncTabButtons(app)
            %SYNCTABBUTTONS Show which tab is selected without leaving black.
            %   Every button keeps THEME.COLOR.TABBAR as its background, so
            %   the header strip stays uniformly black; selection is carried
            %   by pure-white bold text against the dimmer, lighter-weight
            %   label of an unselected tab. Swapping the background instead
            %   (as this did previously) put a blue block behind the selected
            %   tab and broke the black header.
            if isempty(app.TabButtons) || ~isvalid(app.TabButtons(1))
                return;
            end
            theme = app.Theme;
            pages = [app.OverviewTab app.InvertersTab app.IoCanTab ...
                app.FaultsTab app.LoggingTab];
            for index = 1:numel(pages)
                button = app.TabButtons(index);
                button.BackgroundColor = theme.color.tabBar;
                if app.TabGroup.SelectedTab == pages(index)
                    button.FontColor = theme.color.tabBarText;
                    button.FontWeight = 'bold';
                else
                    button.FontColor = theme.color.tabBarInactiveText;
                    button.FontWeight = 'normal';
                end
            end
        end

        function createToolbar(app)
            %CREATETOOLBAR Title, target identity, states, lifecycle buttons.
            theme = app.Theme;
            app.ToolbarLayout = uigridlayout(app.RootLayout, [1 11]);
            app.ToolbarLayout.Layout.Row = 1;
            app.ToolbarLayout.ColumnWidth = {230, 150, 150, 150, 150, '1x', ...
                90, 90, 90, 90, 90};
            app.ToolbarLayout.RowHeight = {'1x'};
            app.ToolbarLayout.Padding = [2 2 2 2];
            app.ToolbarLayout.ColumnSpacing = theme.spacing.columnSpacing;
            app.ToolbarLayout.BackgroundColor = theme.color.panel;

            app.TitleLabel = app.makeLabel(app.ToolbarLayout, ...
                'MFE26 VC INVERTER HIL', theme.font.title, ...
                theme.color.primaryText);
            app.TitleLabel.FontWeight = 'bold';
            app.TargetNameLabel = app.makeLabel(app.ToolbarLayout, ...
                'TARGET --', theme.font.body, theme.color.secondaryText);
            app.ConnectionStateLabel = app.makeLabel(app.ToolbarLayout, ...
                'DISCONNECTED', theme.font.heading, theme.color.fault);
            app.ApplicationStateLabel = app.makeLabel(app.ToolbarLayout, ...
                'APP --', theme.font.heading, theme.color.secondaryText);
            app.ElapsedTimeLabel = app.makeLabel(app.ToolbarLayout, ...
                'TARGET T --', theme.font.body, theme.color.secondaryText);
            app.makeLabel(app.ToolbarLayout, '', theme.font.body, ...
                theme.color.secondaryText);

            app.ConnectButton = app.makeButton(app.ToolbarLayout, ...
                'Connect', @onConnectPushed);
            app.LoadButton = app.makeButton(app.ToolbarLayout, ...
                'Load', @onLoadPushed);
            app.StartButton = app.makeButton(app.ToolbarLayout, ...
                'Start', @onStartPushed);
            app.StopButton = app.makeButton(app.ToolbarLayout, ...
                'Stop', @onStopPushed);
            app.ResetButton = app.makeButton(app.ToolbarLayout, ...
                'Reset', @onResetPushed);
        end

        function createBanner(app)
            %CREATEBANNER Persistent red unresolved-torque-scale banner.
            theme = app.Theme;
            app.TorqueBannerLabel = uilabel(app.RootLayout);
            app.TorqueBannerLabel.Layout.Row = 2;
            app.TorqueBannerLabel.Text = theme.text.torqueBanner;
            app.TorqueBannerLabel.FontName = theme.font.name;
            app.TorqueBannerLabel.FontSize = theme.font.heading;
            app.TorqueBannerLabel.FontWeight = 'bold';
            app.TorqueBannerLabel.FontColor = [1 1 1];
            app.TorqueBannerLabel.BackgroundColor = theme.color.fault;
            app.TorqueBannerLabel.HorizontalAlignment = 'center';
        end

        function createOverviewTab(app)
            %CREATEOVERVIEWTAB State strip, guards, driver inputs, mimic.
            theme = app.Theme;
            outer = app.makeGrid(app.OverviewTab, ...
                {theme.spacing.stripHeight, '1x'}, {'1x'});

            strip = app.makeGrid(outer, {'1x'}, ...
                {90, 18, 130, 18, 100, 18, 100, 18, 80, 18, 90, 160, '1x'});
            strip.BackgroundColor = theme.color.panel;
            app.StateStripLabels = gobjects(1, numel(app.VcuStateNames));
            app.StateStripSeparators = gobjects(1, numel(app.VcuStateNames)-1);
            for index = 1:numel(app.VcuStateNames)
                app.StateStripLabels(index) = app.makeLabel(strip, ...
                    app.VcuStateNames{index}, theme.font.heading, ...
                    theme.color.disabledText);
                app.StateStripLabels(index).Layout.Column = 2 * index - 1;
                app.StateStripLabels(index).HorizontalAlignment = 'center';
                app.StateStripLabels(index).BackgroundColor = theme.color.background;
                if index < numel(app.VcuStateNames)
                    app.StateStripSeparators(index) = app.makeLabel(strip, '>', ...
                        theme.font.heading, theme.color.secondaryText);
                    app.StateStripSeparators(index).Layout.Column = 2 * index;
                    app.StateStripSeparators(index).HorizontalAlignment = 'center';
                end
            end
            app.StateErrorLabel = app.makeLabel(strip, 'ERROR', ...
                theme.font.heading, theme.color.disabledText);
            app.StateErrorLabel.Layout.Column = 11;
            app.StateErrorLabel.HorizontalAlignment = 'center';
            app.StateErrorLabel.BackgroundColor = theme.color.background;
            app.TimeInStateLabel = app.makeLabel(strip, ...
                'TIME IN STATE --', theme.font.body, ...
                theme.color.secondaryText);
            app.TimeInStateLabel.Layout.Column = 12;

            columns = app.makeGrid(outer, {'1x'}, {'1x', '1x'});
            app.createDriverInputs(columns);
            app.createElectricalMimic(columns);
        end

        function createDriverInputs(app, parent)
            %CREATEDRIVERINPUTS Pedal, digital, and momentary operator area.
            theme = app.Theme;
            panel = app.makePanel(parent, 'DRIVER INPUTS');
            % Row 3 (STEERING ANGLE) is the tall row: a uiknob needs real
            % height to render as a legible circle with its major-tick
            % labels, unlike the plain sliders/checkboxes in every other
            % row. Row heights are (parent, rowHeight, columnWidth) per
            % MAKEGRID's signature -- the 90px entry must line up with the
            % steering row, not row 6 (ExpertModeCheckBox), which is a
            % plain checkbox with no need for extra height.
            grid = app.makeGrid(panel, ...
                {26, 26, 90, 26, 26, 26, 26, 26, 26, '1x'}, ...
                {150, '1x', 110, 150});

            throttleLabel = app.makeLabel(grid, 'THROTTLE %', ...
                theme.font.body, theme.color.primaryText);
            throttleLabel.Layout.Row = 1;
            throttleLabel.Layout.Column = 1;
            app.ThrottleSlider = uislider(grid);
            app.ThrottleSlider.Layout.Row = 1;
            app.ThrottleSlider.Layout.Column = 2;
            app.ThrottleSlider.Limits = [0 100];
            app.ThrottleSlider.MajorTicks = 0:25:100;
            app.ThrottleSlider.FontName = theme.font.name;
            app.ThrottleSlider.FontColor = theme.color.secondaryText;
            app.ThrottleSlider.ValueChangingFcn = ...
                createCallbackFcn(app, @onThrottleChanging, true);
            app.ThrottleSlider.ValueChangedFcn = ...
                createCallbackFcn(app, @onThrottleChanged, true);
            app.ThrottleField = app.makeNumericField(grid, ...
                [0 100], @onThrottleFieldChanged);
            app.ThrottleField.Layout.Row = 1;
            app.ThrottleField.Layout.Column = 3;
            app.ThrottleAppliedLabel = app.makeLabel(grid, ...
                'APPLIED --', theme.font.body, theme.color.secondaryText);
            app.ThrottleAppliedLabel.Layout.Row = 1;
            app.ThrottleAppliedLabel.Layout.Column = 4;

            brakeLabel = app.makeLabel(grid, 'BRAKE %', theme.font.body, ...
                theme.color.primaryText);
            brakeLabel.Layout.Row = 2;
            brakeLabel.Layout.Column = 1;
            app.BrakeSlider = uislider(grid);
            app.BrakeSlider.Layout.Row = 2;
            app.BrakeSlider.Layout.Column = 2;
            app.BrakeSlider.Limits = [0 100];
            app.BrakeSlider.MajorTicks = 0:25:100;
            app.BrakeSlider.FontName = theme.font.name;
            app.BrakeSlider.FontColor = theme.color.secondaryText;
            app.BrakeSlider.ValueChangingFcn = ...
                createCallbackFcn(app, @onBrakeChanging, true);
            app.BrakeSlider.ValueChangedFcn = ...
                createCallbackFcn(app, @onBrakeChanged, true);
            app.BrakeField = app.makeNumericField(grid, ...
                [0 100], @onBrakeFieldChanged);
            app.BrakeField.Layout.Row = 2;
            app.BrakeField.Layout.Column = 3;
            app.BrakeAppliedLabel = app.makeLabel(grid, ...
                'APPLIED --', theme.font.body, theme.color.secondaryText);
            app.BrakeAppliedLabel.Layout.Row = 2;
            app.BrakeAppliedLabel.Layout.Column = 4;

            steeringLabel = app.makeLabel(grid, 'STEERING ANGLE deg', ...
                theme.font.body, theme.color.primaryText);
            steeringLabel.Layout.Row = 3;
            steeringLabel.Layout.Column = 1;
            app.SteeringDial = uiknob(grid, 'continuous');
            app.SteeringDial.Layout.Row = 3;
            app.SteeringDial.Layout.Column = 2;
            app.SteeringDial.Limits = [-780 780];
            app.SteeringDial.MajorTicks = -780:195:780;
            app.SteeringDial.Value = 0;
            app.SteeringDial.FontName = theme.font.name;
            app.SteeringDial.FontColor = theme.color.secondaryText;
            app.SteeringDial.ValueChangingFcn = ...
                createCallbackFcn(app, @onSteeringChanging, true);
            app.SteeringDial.ValueChangedFcn = ...
                createCallbackFcn(app, @onSteeringChanged, true);
            app.SteeringField = app.makeNumericField(grid, ...
                [-780 780], @onSteeringFieldChanged);
            app.SteeringField.Layout.Row = 3;
            app.SteeringField.Layout.Column = 3;
            app.SteeringAppliedLabel = app.makeLabel(grid, ...
                'APPLIED --', theme.font.body, theme.color.secondaryText);
            app.SteeringAppliedLabel.Layout.Row = 3;
            app.SteeringAppliedLabel.Layout.Column = 4;

            % Every control in this grid, starting with THROTTLE % above,
            % gets an explicit Layout.Row / Layout.Column instead of
            % relying on uigridlayout auto-flow. Auto-flow assigns (row,
            % column) purely by each child's add order divided by the
            % 10-column width -- it does NOT look at which cells are
            % actually occupied, so with only 4 controls per logical row
            % (label, control, field, applied-label) it packs 2.5 logical
            % rows' worth of controls into physical row 1 before wrapping.
            % That is what pushed the steering knob into a slim, wrong
            % column (garbling its major-tick labels into overlapping
            % text) and wrapped its field/applied-label onto stray rows.
            % voltageGrid, PlausibilityCheckBox and ExpertModeCheckBox
            % below compound the same bug: they span multiple columns
            % (Layout.Column = [1 4] / [2 4]) but still only ever counted
            % as "one slot" toward the auto-flow arithmetic, so every
            % auto-placed control after them drifted onto rows that were
            % already occupied and rendered on top of each other (this is
            % what also produced the overlapping/ghosted AO02 THR2 text).
            % Pinning every row removes that drift.
            pedalVLabel = app.makeLabel(grid, 'APPLIED PEDAL V', ...
                theme.font.body, theme.color.primaryText);
            pedalVLabel.Layout.Row = 4;
            pedalVLabel.Layout.Column = 1;
            voltageGrid = app.makeGrid(grid, {'1x'}, {'1x', '1x', '1x', '1x'});
            voltageGrid.Layout.Row = 4;
            voltageGrid.Layout.Column = [2 4];
            app.PedalVoltageLabels = gobjects(1, 4);
            for index = 1:4
                app.PedalVoltageLabels(index) = app.makeLabel(voltageGrid, ...
                    sprintf('%s %s', app.PedalChannelNames{index}, ...
                    theme.text.noData), theme.font.small, ...
                    theme.color.electrical);
            end

            app.PlausibilityCheckBox = app.makeCheckBox(grid, ...
                'INTERLOCK: allow pedal-plausibility violation', ...
                @onPlausibilityChanged);
            app.PlausibilityCheckBox.Layout.Row = 5;
            app.PlausibilityCheckBox.Layout.Column = [1 4];
            app.ExpertModeCheckBox = app.makeCheckBox(grid, ...
                'INTERLOCK: expert mode (calibration, plant, faults)', ...
                @onExpertModeChanged);
            app.ExpertModeCheckBox.Layout.Row = 6;
            app.ExpertModeCheckBox.Layout.Column = [1 4];

            digitalStimuliLabel = app.makeLabel(grid, 'DIGITAL STIMULI', ...
                theme.font.body, theme.color.primaryText);
            digitalStimuliLabel.Layout.Row = 7;
            digitalStimuliLabel.Layout.Column = 1;
            % MAIN_BTN_IN has no checkbox here: a held-level control was
            % inert on hardware (the chart only reacts to the momentary
            % MAIN BUTTON pulse below), so it was removed rather than kept
            % as a control that visibly does nothing when clicked.
            app.CoolingSwitch = app.makeCheckBox(grid, 'COOLING_SW_IN', ...
                @onCoolingSwitchChanged);
            app.CoolingSwitch.Layout.Row = 7;
            app.CoolingSwitch.Layout.Column = 2;
            app.ShutdownFeedbackSwitch = app.makeCheckBox(grid, ...
                'SD_FB_IN', @onShutdownFeedbackChanged);
            app.ShutdownFeedbackSwitch.Layout.Row = 7;
            app.ShutdownFeedbackSwitch.Layout.Column = 3;

            digitalAppliedLabel = app.makeLabel(grid, 'APPLIED', ...
                theme.font.body, theme.color.primaryText);
            digitalAppliedLabel.Layout.Row = 8;
            digitalAppliedLabel.Layout.Column = 1;
            app.DigitalAppliedLabels = gobjects(1, 2);
            for index = 1:2
                app.DigitalAppliedLabels(index) = app.makeLabel(grid, ...
                    theme.text.noData, theme.font.small, ...
                    theme.color.secondaryText);
                app.DigitalAppliedLabels(index).Layout.Row = 8;
                app.DigitalAppliedLabels(index).Layout.Column = index + 1;
            end

            momentaryLabel = app.makeLabel(grid, 'MOMENTARY (uint32 seq)', ...
                theme.font.body, theme.color.primaryText);
            momentaryLabel.Layout.Row = 9;
            momentaryLabel.Layout.Column = 1;
            app.PrechargeButton = app.makeButton(grid, 'PRECHARGE', ...
                @onPrechargePushed);
            app.PrechargeButton.Layout.Row = 9;
            app.PrechargeButton.Layout.Column = 2;
            app.MainMomentaryButton = app.makeButton(grid, 'MAIN BUTTON', ...
                @onMainMomentaryPushed);
            app.MainMomentaryButton.Layout.Row = 9;
            app.MainMomentaryButton.Layout.Column = 3;
            app.MomentaryLabels = gobjects(1, 2);
            app.MomentaryLabels(1) = app.makeLabel(grid, ...
                'seq --', theme.font.small, theme.color.secondaryText);
            app.MomentaryLabels(1).Layout.Row = 9;
            app.MomentaryLabels(1).Layout.Column = 4;
            blankMomentaryLabel = app.makeLabel(grid, '', theme.font.small, ...
                theme.color.secondaryText);
            blankMomentaryLabel.Layout.Row = 10;
            blankMomentaryLabel.Layout.Column = 1;
            app.MomentaryLabels(2) = app.makeLabel(grid, ...
                'seq --', theme.font.small, theme.color.secondaryText);
            app.MomentaryLabels(2).Layout.Row = 10;
            app.MomentaryLabels(2).Layout.Column = 2;
        end

        function createElectricalMimic(app, parent)
            %CREATEELECTRICALMIMIC Guards, twin DC-link, pin cards, rails.
            theme = app.Theme;
            column = app.makeGrid(parent, {180, 120, 110, 90}, {'1x'});

            guardPanel = app.makePanel(column, 'NEXT TRANSITION');
            guardGrid = app.makeGrid(guardPanel, {'1x'}, {'1x'});
            app.GuardTable = uitable(guardGrid);
            % Native uitable headers remain white in R2024b and cannot be
            % themed reliably. The surrounding section and row labels carry
            % the meaning, so hide this nonessential header strip.
            app.GuardTable.ColumnName = {};
            app.GuardTable.ColumnWidth = {200, 130, 130, 90};
            app.GuardTable.RowName = {};
            app.GuardTable.Data = cell(0, 4);
            app.GuardTable.FontName = theme.font.name;
            app.GuardTable.FontSize = theme.font.small;
            app.GuardTable.BackgroundColor = theme.color.panel;
            app.GuardTable.ForegroundColor = theme.color.primaryText;

            dcPanel = app.makePanel(column, 'TWIN DC-LINK MIMIC');
            dcGrid = app.makeGrid(dcPanel, {22, 22, 22}, {110, '1x', 200});
            app.DcLinkValueLabels = gobjects(1, 2);
            app.DcLinkFlagLabels = gobjects(1, 2);
            labels = {'PAIR 1/2', 'PAIR 3/4'};
            for index = 1:2
                app.makeLabel(dcGrid, labels{index}, theme.font.body, ...
                    theme.color.primaryText);
                app.DcLinkValueLabels(index) = app.makeLabel(dcGrid, ...
                    theme.text.noData, theme.font.body, ...
                    theme.color.electrical);
                app.DcLinkFlagLabels(index) = app.makeLabel(dcGrid, ...
                    ['ABOVE MIN ' theme.text.noData], theme.font.small, ...
                    theme.color.secondaryText);
            end
            app.makeLabel(dcGrid, 'SWITCHING', theme.font.body, ...
                theme.color.primaryText);
            app.SwitchingFrequencyLabel = app.makeLabel(dcGrid, ...
                theme.text.noData, theme.font.body, theme.color.electrical);
            app.makeLabel(dcGrid, '', theme.font.small, ...
                theme.color.secondaryText);

            pinPanel = app.makePanel(column, 'VCU OUTPUT PINS');
            pinGrid = app.makeGrid(pinPanel, {26, 26}, ...
                {'1x', '1x', '1x', '1x', '1x'});
            blank = inverterhilgui.blankTelemetry();
            app.PinNameLabels = gobjects(1, numel(blank.pins));
            app.PinStateLabels = gobjects(1, numel(blank.pins));
            for index = 1:numel(blank.pins)
                app.PinNameLabels(index) = app.makeLabel(pinGrid, ...
                    sprintf('%s (%s)', blank.pins(index).name, ...
                    blank.pins(index).testPoint), theme.font.small, ...
                    theme.color.primaryText);
                app.PinNameLabels(index).HorizontalAlignment = 'center';
            end
            for index = 1:numel(blank.pins)
                app.PinStateLabels(index) = app.makeLabel(pinGrid, ...
                    theme.text.noData, theme.font.heading, ...
                    theme.color.secondaryText);
                app.PinStateLabels(index).HorizontalAlignment = 'center';
                app.PinStateLabels(index).FontWeight = 'bold';
            end

            railPanel = app.makePanel(column, 'VCU SENSOR RAILS');
            railGrid = app.makeGrid(railPanel, {'1x'}, ...
                {'1x', '1x', '1x', '1x'});
            app.AnalogInputLabels = gobjects(1, 4);
            railNames = {'AI01 5V_THR1', 'AI02 5V_THR2', 'AI03 5V_BP1', ...
                'AI04 5V_BP2'};
            for index = 1:4
                app.AnalogInputLabels(index) = app.makeLabel(railGrid, ...
                    sprintf('%s %s', railNames{index}, theme.text.noData), ...
                    theme.font.small, theme.color.electrical);
            end
        end

        function createInvertersTab(app)
            %CREATEINVERTERSTAB Four compact INV1-INV4 status panels.
            theme = app.Theme;
            outer = app.makeGrid(app.InvertersTab, {18, '1x'}, {'1x'});
            % Permanent disclosure, the same pattern as the CAN TX table's
            % "HIL-generated; bus ACK unverified" text: these fields are
            % this rig's own simulated inverter output (STEPMODEL/
            % STEPPLANT), not a measurement confirmed by another node. See
            % TARGETSESSION.READLIVEIO for why -- there is no cross-channel
            % CAN receipt signal wired up to verify it.
            app.InverterSourceLabel = app.makeLabel(outer, ...
                ['SIMULATED INVERTER OUTPUT (this rig''s own STEPMODEL/' ...
                'STEPPLANT state) - not independently confirmed by a ' ...
                'cross-channel CAN receipt; no such signal is wired up yet.'], ...
                theme.font.small, theme.color.secondaryText);
            app.InverterSourceLabel.Layout.Row = 1;
            app.InverterSourceLabel.Layout.Column = 1;
            panels = app.makeGrid(outer, {'1x', '1x'}, {'1x', '1x'});
            panels.Layout.Row = 2;
            panels.Layout.Column = 1;
            fieldCount = numel(app.InverterFieldNames);
            app.InverterTitleLabels = gobjects(1, 4);
            app.InverterCornerLabels = gobjects(1, 4);
            app.InverterFieldLabels = gobjects(4, fieldCount);
            app.InverterStatusGrids = [];
            app.InverterDisclosureButtons = [];
            for channel = 1:4
                panel = app.makePanel(panels, sprintf('INVERTER %d', channel));
                [~, collapsedRows] = ...
                    inverterhilgui.inverterPanelVisibility(false);
                grid = app.makeGrid(panel, [{20} collapsedRows], ...
                    {170, '1x', 120});
                app.InverterTitleLabels(channel) = app.makeLabel(grid, ...
                    sprintf('INV%d', channel), theme.font.heading, ...
                    theme.color.primaryText);
                app.InverterTitleLabels(channel).FontWeight = 'bold';
                app.InverterTitleLabels(channel).Layout.Row = 1;
                app.InverterTitleLabels(channel).Layout.Column = 1;
                app.InverterCornerLabels(channel) = app.makeLabel(grid, ...
                    theme.text.cornerLabel, theme.font.small, ...
                    theme.color.fault);
                app.InverterCornerLabels(channel).Layout.Row = 1;
                app.InverterCornerLabels(channel).Layout.Column = 2;
                button = app.makeButton(grid, '> DETAILS', ...
                    @onInverterDisclosurePushed);
                button.Layout.Row = 1;
                button.Layout.Column = 3;
                if channel == 1
                    app.InverterStatusGrids = grid;
                    app.InverterDisclosureButtons = button;
                else
                    app.InverterStatusGrids(channel) = grid;
                    app.InverterDisclosureButtons(channel) = button;
                end
                for field = 1:fieldCount
                    name = app.makeLabel(grid, app.InverterFieldNames{field}, ...
                        theme.font.small, theme.color.secondaryText);
                    name.Layout.Row = field + 1;
                    name.Layout.Column = 1;
                    app.InverterFieldLabels(channel, field) = ...
                        app.makeLabel(grid, theme.text.noData, ...
                        theme.font.small, theme.color.primaryText);
                    app.InverterFieldLabels(channel, field).Layout.Row = ...
                        field + 1;
                    app.InverterFieldLabels(channel, field).Layout.Column = 2;
                end
                app.setInverterExpanded(channel, false);
            end
        end

        function onInverterDisclosurePushed(app, event)
            %ONINVERTERDISCLOSUREPUSHED Toggle only the source inverter panel.
            %   This app's CREATECALLBACKFCN wrapper invokes callbacks as
            %   CALLBACK(APP, EVENT) -- not (APP, SOURCE, EVENT) -- so which
            %   button fired must come from EVENT.SOURCE, matching every
            %   other callback in this file (e.g. ONCONNECTPUSHED(APP, ~)).
            channel = find(app.InverterDisclosureButtons == event.Source, 1);
            if isempty(channel)
                return;
            end
            app.setInverterExpanded(channel, ~app.InverterExpanded(channel));
        end

        function setInverterExpanded(app, channel, expanded)
            %SETINVERTEREXPANDED Apply layout-only visibility for one panel.
            if ~isnumeric(channel) || ~isscalar(channel) || ...
                    ~isreal(channel) || ~isfinite(channel) || ...
                    channel < 1 || channel > 4 || channel ~= floor(channel)
                error('inverterhilgui:InvalidInverterChannel', ...
                    'Inverter channel must be an integer from 1 through 4.');
            end
            if ~islogical(expanded) || ~isscalar(expanded)
                error('inverterhilgui:InvalidExpandedState', ...
                    'Expanded state must be a logical scalar.');
            end

            [~, fieldRows] = ...
                inverterhilgui.inverterPanelVisibility(expanded);
            app.InverterExpanded(channel) = expanded;
            app.InverterStatusGrids(channel).RowHeight = [{20} fieldRows];
            if expanded
                app.InverterDisclosureButtons(channel).Text = 'v DETAILS';
                app.InverterDisclosureButtons(channel).Tooltip = ...
                    'Collapse inverter details';
            else
                app.InverterDisclosureButtons(channel).Text = '> DETAILS';
                app.InverterDisclosureButtons(channel).Tooltip = ...
                    'Expand inverter details';
            end
        end

        function createIoCanTab(app)
            %CREATEIOCANTAB Split CAN tables and the diagnostics strip.
            theme = app.Theme;
            outer = app.makeGrid(app.IoCanTab, {18, '1x', 150, 30}, ...
                {'1x', '1x'});

            % Same honesty standard as the torque banner: state plainly that
            % no high-rate feed is registered, so the empty tables below are
            % never mistaken for a live-but-idle bus.
            app.InstrumentStatusLabel = app.makeLabel(outer, ...
                ['HIGH-RATE INSTRUMENT STREAMING NOT REGISTERED - the ' ...
                'part 28 target observability signal contract does not ' ...
                'exist yet, so every high-rate field below is inactive.'], ...
                theme.font.small, theme.color.secondaryText);
            app.InstrumentStatusLabel.Layout.Row = 1;
            app.InstrumentStatusLabel.Layout.Column = [1 2];

            rxPanel = app.makePanel(outer, ...
                'VCU TX / HIL RX  0x1F5 0x186 0x196 0x1A6 0x1B6');
            rxPanel.Layout.Row = 2;
            rxPanel.Layout.Column = 1;
            rxGrid = app.makeGrid(rxPanel, {'1x'}, {'1x'});
            app.CanRxTable = app.makeCanTable(rxGrid);

            txPanel = app.makePanel(outer, ...
                ['HIL TX / VCU RX  0x383 0x385 0x393 0x395 0x3A3 0x3A5 ' ...
                '0x3B3 0x3B5 0x400  |  SENSORS 0x034 0x032 0x076 0x2B0 0x7C0']);
            txPanel.Layout.Row = 2;
            txPanel.Layout.Column = 2;
            txGrid = app.makeGrid(txPanel, {'1x'}, {'1x'});
            app.CanTxTable = app.makeCanTable(txGrid);

            app.createSensorHealthPanel(outer);

            app.CanDiagnosticsLabel = app.makeLabel(outer, ...
                app.canDiagnosticsText(inverterhilgui.blankTelemetry()), ...
                theme.font.small, theme.color.secondaryText);
            app.CanDiagnosticsLabel.Layout.Row = 4;
            app.CanDiagnosticsLabel.Layout.Column = [1 2];
            app.CanDiagnosticsLabel.BackgroundColor = theme.color.panel;
        end

        function createSensorHealthPanel(app, outer)
            %CREATESENSORHEALTHPANEL Synchronized MTi/LWS readout and dropout.
            %
            %   The four readouts are deliberately separate quantities, not
            %   one summary line: REQUESTED is the dial, APPLIED is what the
            %   virtual car actually steered to, SPEED is derived, and LWS is
            %   what the encoded 0x2B0 frame carries. Every one renders as
            %   dashes until genuinely read -- see INVERTERHILGUI.
            %   BLANKTELEMETRY's no-invented-values rule.
            theme = app.Theme;
            panel = app.makePanel(outer, ...
                'SENSOR SIMULATION - MTi-680G / BOSCH LWS');
            panel.Layout.Row = 3;
            panel.Layout.Column = [1 2];
            grid = app.makeGrid(panel, {20, 20, 20, 20, 24}, ...
                {'1x', 220, 260});

            app.SensorSteeringLabel = app.makeLabel(grid, ...
                'STEERING --', theme.font.small, theme.color.primaryText);
            app.SensorSteeringLabel.Layout.Row = 1;
            app.SensorSteeringLabel.Layout.Column = 1;
            app.SteeringDropoutCheckBox = app.makeCheckBox(grid, ...
                'INJECT: LWS 0x2B0 dropout', @onSteeringDropoutChanged);
            app.SteeringDropoutCheckBox.Layout.Row = 1;
            app.SteeringDropoutCheckBox.Layout.Column = 2;
            app.SteeringStaleCheckBox = app.makeCheckBox(grid, ...
                'INJECT: LWS stale payload', @onSteeringStaleChanged);
            app.SteeringStaleCheckBox.Layout.Row = 1;
            app.SteeringStaleCheckBox.Layout.Column = 3;

            app.SensorImuAccelLabel = app.makeLabel(grid, ...
                'MTi ACCEL --', theme.font.small, theme.color.electrical);
            app.SensorImuAccelLabel.Layout.Row = 2;
            app.SensorImuAccelLabel.Layout.Column = 1;
            app.SteeringMalformedCheckBox = app.makeCheckBox(grid, ...
                'INJECT: LWS wrong DLC', @onSteeringMalformedChanged);
            app.SteeringMalformedCheckBox.Layout.Row = 2;
            app.SteeringMalformedCheckBox.Layout.Column = 2;
            app.SteeringInvalidStatusCheckBox = app.makeCheckBox(grid, ...
                'INJECT: illegal TRIM/CAL/OK', @onSteeringInvalidStatusChanged);
            app.SteeringInvalidStatusCheckBox.Layout.Row = 2;
            app.SteeringInvalidStatusCheckBox.Layout.Column = 3;

            app.SensorImuRateLabel = app.makeLabel(grid, ...
                'MTi RATE --', theme.font.small, theme.color.electrical);
            app.SensorImuRateLabel.Layout.Row = 3;
            app.SensorImuRateLabel.Layout.Column = 1;
            app.SteeringAngleSentinelCheckBox = app.makeCheckBox(grid, ...
                'INJECT: LWS angle 0x7FFF', @onSteeringAngleSentinelChanged);
            app.SteeringAngleSentinelCheckBox.Layout.Row = 3;
            app.SteeringAngleSentinelCheckBox.Layout.Column = 2;
            app.SteeringSpeedSentinelCheckBox = app.makeCheckBox(grid, ...
                'INJECT: LWS speed 0xFF', @onSteeringSpeedSentinelChanged);
            app.SteeringSpeedSentinelCheckBox.Layout.Row = 3;
            app.SteeringSpeedSentinelCheckBox.Layout.Column = 3;

            app.SensorImuVelocityLabel = app.makeLabel(grid, ...
                'MTi VELOCITY --', theme.font.small, theme.color.electrical);
            app.SensorImuVelocityLabel.Layout.Row = 4;
            app.SensorImuVelocityLabel.Layout.Column = 1;
            app.ImuDropoutCheckBox = app.makeCheckBox(grid, ...
                'INJECT: MTi all-frame dropout', @onImuDropoutChanged);
            app.ImuDropoutCheckBox.Layout.Row = 4;
            app.ImuDropoutCheckBox.Layout.Column = 2;
            app.ImuStaleCheckBox = app.makeCheckBox(grid, ...
                'INJECT: MTi stale payloads', @onImuStaleChanged);
            app.ImuStaleCheckBox.Layout.Row = 4;
            app.ImuStaleCheckBox.Layout.Column = 3;

            app.SensorCalibrationLabel = app.makeLabel(grid, ...
                'LWS CALIBRATION --', theme.font.small, theme.color.secondaryText);
            app.SensorCalibrationLabel.Layout.Row = 5;
            app.SensorCalibrationLabel.Layout.Column = 1;
            app.ImuMalformedCheckBox = app.makeCheckBox(grid, ...
                'INJECT: MTi wrong DLC', @onImuMalformedChanged);
            app.ImuMalformedCheckBox.Layout.Row = 5;
            app.ImuMalformedCheckBox.Layout.Column = 2;
            app.LwsCalibrationButton = app.makeButton(grid, ...
                'RESET 0x05 -> CHECK -> ZERO 0x03', @onLwsCalibrationPushed);
            app.LwsCalibrationButton.Layout.Row = 5;
            app.LwsCalibrationButton.Layout.Column = 3;
        end

        function createFaultsTab(app)
            %CREATEFAULTSTAB Per-inverter and CAN fault-injection controls.
            theme = app.Theme;
            outer = app.makeGrid(app.FaultsTab, {'1x', 120, 60}, {'1x'});

            invPanel = app.makePanel(outer, 'PER-INVERTER SCENARIO');
            rows = num2cell(repmat(26, 1, 5));
            invGrid = app.makeGrid(invPanel, [rows {'1x'}], ...
                {120, 160, 160, 160, '1x'});
            headers = {'CHANNEL', 'fault_mask (uint32)', 'load_nm', ...
                'connected', ''};
            for index = 1:numel(headers)
                app.makeLabel(invGrid, headers{index}, theme.font.small, ...
                    theme.color.secondaryText);
            end
            app.FaultMaskFields = gobjects(1, 4);
            app.LoadTorqueFields = gobjects(1, 4);
            app.ConnectedCheckBoxes = gobjects(1, 4);
            for channel = 1:4
                app.makeLabel(invGrid, sprintf('INV%d', channel), ...
                    theme.font.body, theme.color.primaryText);
                app.FaultMaskFields(channel) = app.makeNumericField( ...
                    invGrid, [0 4294967295], @onFaultMaskChanged);
                app.FaultMaskFields(channel).UserData = channel;
                app.LoadTorqueFields(channel) = app.makeNumericField( ...
                    invGrid, [-200 200], @onLoadTorqueChanged);
                app.LoadTorqueFields(channel).UserData = channel;
                app.ConnectedCheckBoxes(channel) = app.makeCheckBox( ...
                    invGrid, 'connected', @onConnectedChanged);
                app.ConnectedCheckBoxes(channel).UserData = channel;
                app.makeLabel(invGrid, '', theme.font.small, ...
                    theme.color.secondaryText);
            end

            canPanel = app.makePanel(outer, 'CAN FAULT INJECTION');
            canGrid = app.makeGrid(canPanel, {26, 26, '1x'}, ...
                {200, 160, '1x'});
            app.makeLabel(canGrid, 'drop_control_mask (uint8)', ...
                theme.font.body, theme.color.primaryText);
            app.DropControlField = app.makeNumericField(canGrid, [0 255], ...
                @onDropControlChanged);
            app.makeLabel(canGrid, '0x186 0x196 0x1A6 0x1B6', ...
                theme.font.small, theme.color.secondaryText);
            app.makeLabel(canGrid, 'drop_status_mask (uint16)', ...
                theme.font.body, theme.color.primaryText);
            app.DropStatusField = app.makeNumericField(canGrid, [0 65535], ...
                @onDropStatusChanged);
            app.makeLabel(canGrid, 'nine-frame status cycle', ...
                theme.font.small, theme.color.secondaryText);

            healthGrid = app.makeGrid(outer, {'1x'}, {'1x', '1x'});
            app.HeartbeatLabel = app.makeLabel(healthGrid, ...
                'GUI HEARTBEAT --', theme.font.body, ...
                theme.color.secondaryText);
            app.FallbackLabel = app.makeLabel(healthGrid, ...
                'FALLBACK --', theme.font.body, theme.color.secondaryText);
        end

        function createLoggingTab(app)
            %CREATELOGGINGTAB Append-only session log view and export.
            theme = app.Theme;
            outer = app.makeGrid(app.LoggingTab, {'1x', 30}, {'1x'});
            app.LogTable = uitable(outer);
            % Hide MATLAB's unstyleable white column-header strip.
            app.LogTable.ColumnName = {};
            app.LogTable.ColumnWidth = {170, 90, 200, 220, 110, 110, 90, 240};
            app.LogTable.RowName = {};
            app.LogTable.Data = cell(0, 8);
            app.LogTable.FontName = theme.font.name;
            app.LogTable.FontSize = theme.font.small;
            app.LogTable.BackgroundColor = theme.color.panel;
            app.LogTable.ForegroundColor = theme.color.primaryText;

            footer = app.makeGrid(outer, {'1x'}, {160, '1x'});
            footer.Layout.Row = 2;
            app.ExportLogButton = app.makeButton(footer, 'Export log...', ...
                @onExportLogPushed);
            app.LogSummaryLabel = app.makeLabel(footer, ...
                '0 records (append-only)', theme.font.small, ...
                theme.color.secondaryText);
        end

        function startupFcn(app)
            %STARTUPFCN Start disconnected with blank telemetry and no target.
            app.HeartbeatTimeoutS = inverterhilgui.hostHeartbeatTimeout();
            app.Session = inverterhilgui.targetSession('TargetPC1');
            app.Log = inverterhilgui.sessionLog();
            app.Telemetry = inverterhilgui.blankTelemetry();
            app.ThrottleCoalescer = inverterhilgui.sliderCoalescer(0.030);
            app.BrakeCoalescer = inverterhilgui.sliderCoalescer(0.030);
            app.SteeringCoalescer = inverterhilgui.sliderCoalescer(0.030);
            app.Heartbeat = struct('counter', uint32(0), ...
                'lastUpdateS', NaN);
            app.refreshAll();
            app.StatusTimer = timer( ...
                'Name', 'inverterHilStatusTimer', ...
                'ExecutionMode', 'fixedSpacing', ...
                'Period', 0.25, ...
                'BusyMode', 'drop', ...
                'TimerFcn', @(~, ~) app.onStatusTimer());
            start(app.StatusTimer);
        end

        function onStatusTimer(app)
            %ONSTATUSTIMER Low-rate status, heartbeat, and reconciliation.
            %
            %   Skipped outright while TARGETBUSY (see ENTERTARGETSECTION):
            %   this tick's TICKHEARTBEAT/REFRESHALL reach the target through
            %   GETSIGNAL/GETPARAM exactly like CONNECT/LOAD/START/STOP/
            %   RESET do, and a timer tick landing mid-lifecycle-call reaches
            %   Simulink Real-Time's async streaming queue from two call
            %   stacks at once. That is not a MATLAB error to catch -- it is
            %   an access violation in slrealtime::xcp::AsyncQueue::write
            %   that takes MATLAB down with it (confirmed from crash dumps
            %   captured on this machine on the STOP path). Skipping, not
            %   deferring, is what keeps this timer from ever reaching the
            %   target while a lifecycle call is on it.
            if app.TargetBusy
                return;
            end
            try
                app.tickHeartbeat();
                app.pollCoalescers();
                app.refreshAll();
            catch err
                app.reportError('status_timer', err);
            end
        end

        function cleanupObj = enterTargetSection(app)
            %ENTERTARGETSECTION Lock ONSTATUSTIMER out of the target for the
            %   life of the returned cleanup object. Every callback that
            %   calls CONNECT/LOAD/START/STOP/RESET on APP.SESSION must hold
            %   this for its full body (the action and the REFRESHALL that
            %   follows it), since REFRESHALL reaches the target too.
            app.TargetBusy = true;
            cleanupObj = onCleanup(@() app.leaveTargetSection());
        end

        function leaveTargetSection(app)
            app.TargetBusy = false;
        end

        function tickHeartbeat(app)
            %TICKHEARTBEAT Advance and write the uint32 GUI heartbeat.
            beat = inverterhilgui.heartbeatState(app.Heartbeat, ...
                app.hostTimeS(), app.HeartbeatTimeoutS);
            app.Heartbeat = struct('counter', beat.counter, ...
                'lastUpdateS', beat.lastUpdateS);
            if app.Session.describeState().isRunning
                app.commitWrite('gui_heartbeat', beat.counter, false);
            end
            plan = inverterhilgui.safeFallbackPlan(app.fallbackHealth(beat));
            app.HeartbeatLabel.Text = sprintf( ...
                'GUI HEARTBEAT %u  age %s', beat.counter, ...
                app.formatSeconds(beat.ageS));
            app.FallbackLabel.Text = sprintf('FALLBACK %s : AO %s / DIO %s', ...
                upper(plan.reason), mat2str(plan.analogV), ...
                mat2str(double(plan.digital)));
            if plan.applyFallback
                app.FallbackLabel.FontColor = app.Theme.color.waiting;
            else
                app.FallbackLabel.FontColor = app.Theme.color.healthy;
            end
        end

        function health = fallbackHealth(app, beat)
            %FALLBACKHEALTH Assemble the health inputs for the fallback plan.
            lifecycle = app.Session.describeState();
            health = struct( ...
                'applicationRunning', lifecycle.isRunning, ...
                'targetConnected', lifecycle.isConnected, ...
                'applicationLoaded', lifecycle.isConnected, ...
                'ioHealthy', app.Telemetry.io.healthy, ...
                'armed', app.Telemetry.pedals.armed, ...
                'heartbeatAgeS', beat.ageS, ...
                'heartbeatTimeoutS', app.HeartbeatTimeoutS);
        end

        function pollCoalescers(app)
            %POLLCOALESCERS Emit any pedal value held by the 30 ms window.
            %
            %   Both POLL calls always run, draining each coalescer's queued
            %   window regardless of XCPDRIVING, so a value queued while the
            %   GUI still owned pedals never leaks a stale COMMITWRITE the
            %   moment XCPDRIVING clears. Only the COMMITWRITE itself is
            %   gated: while an XCP master owns hil_cmd_pedals_throttle/
            %   brake, GUI slider movement must not reach SESSION.WRITE at
            %   all, matching inverterhilgui.controlPolicy's POLICY.PEDALS
            %   (which independently disables the slider widgets) -- this is
            %   the actual enforcement point, not merely the widget Enable
            %   state.
            emission = app.ThrottleCoalescer.poll(app.hostTimeS());
            if emission.hasValue && ~app.XcpDriving && ~app.CanPedalsDriving
                app.commitWrite('pedals.throttle', emission.value / 100, true);
            end
            emission = app.BrakeCoalescer.poll(app.hostTimeS());
            if emission.hasValue && ~app.XcpDriving && ~app.CanPedalsDriving
                app.commitWrite('pedals.brake', emission.value / 100, true);
            end
            emission = app.SteeringCoalescer.poll(app.hostTimeS());
            if emission.hasValue
                app.commitWrite('steering.angle_deg', emission.value, true);
            end
        end

        function result = commitWrite(app, name, value, logResult)
            %COMMITWRITE Write one logical command and audit the outcome.
            result = app.Session.write(name, value);
            if logResult || ~result.success || result.mismatch
                app.Log.append(struct( ...
                    'targetTimeS', app.Session.executionTimeS(), ...
                    'logicalName', name, ...
                    'targetPath', result.path, ...
                    'requested', result.requested, ...
                    'applied', result.applied, ...
                    'result', app.auditResultCode(result), ...
                    'detail', result.reason));
            end
        end

        function code = auditResultCode(~, result)
            %AUDITRESULTCODE Map a write outcome to an audit result code.
            if ~result.success
                code = 'failed';
            elseif result.mismatch
                code = 'mismatch';
            elseif result.clamped
                code = 'clamped';
            else
                code = 'applied';
            end
        end

        function refreshAll(app)
            %REFRESHALL Repaint every readout from the current snapshot.
            %
            %   POSITIONTABBAR is driven from here rather than only from
            %   UIFIGURE.SIZECHANGEDFCN because that callback NEVER FIRES:
            %   the figure keeps AUTORESIZECHILDREN on, which suppresses it,
            %   and MATLAB says so at construction ('SizeChangedFcn callback
            %   will not execute while AutoResizeChildren is set to on'). An
            %   addlistener on SizeChanged is suppressed identically -- both
            %   were measured firing zero times across a resize. Turning
            %   AutoResizeChildren off would hand back the callback but also
            %   hand this class responsibility for resizing every child.
            %
            %   Re-deriving the overlay geometry on the existing status tick
            %   is what keeps the bar aligned after a resize. It is two
            %   property reads and an early return when nothing moved, so the
            %   cost is negligible, and correctness no longer depends on a
            %   callback this figure configuration cannot deliver.
            app.positionTabBar();
            app.refreshLiveIo();
            app.refreshPolicy();
            app.refreshToolbar();
            app.refreshStateStrip();
            app.refreshGuards();
            app.refreshDriverInputs();
            app.refreshElectrical();
            app.refreshInverters();
            app.refreshSensors();
            app.refreshCan();
            app.refreshLog();
        end

        function refreshLiveIo(app)
            %REFRESHLIVEIO Pull the genuinely live target signals -- IO
            %   health, the five VCU-monitor digital inputs, and the four
            %   commanded pedal output voltages -- via
            %   TARGETSESSION.READLIVEIO. This is the ONLY source that
            %   updates APP.TELEMETRY after STARTUPFCN's initial BLANKTELEMETRY
            %   assignment; nothing else in this class re-reads the target.
            %   On any read failure the affected fields revert to the honest
            %   unknown state rather than holding a stale value.
            live = app.Session.readLiveIo();
            if live.known
                app.Telemetry.io.healthy = live.io.healthy;
                app.Telemetry.io.healthyKnown = live.io.healthyKnown;
                for index = 1:numel(app.Telemetry.pins)
                    app.Telemetry.pins(index).state = live.pins(index);
                end
                if live.vcuStateKnown
                    names = [app.VcuStateNames {'ERROR_SHUTDOWN'}];
                    stateIndex = round(live.vcuStateId) + 1;
                    if stateIndex >= 1 && stateIndex <= numel(names)
                        newState = names{stateIndex};
                        [app.VcuStateEnteredS, timeInStateS] = ...
                            inverterhilgui.trackVcuStateEntry(newState, ...
                            app.VcuStateLast, app.VcuStateEnteredS, ...
                            app.hostTimeS());
                        app.VcuStateLast = newState;
                        app.Telemetry.vcu.state = newState;
                        app.Telemetry.vcu.timeInStateS = timeInStateS;
                        app.Telemetry.vcu.errorKnown = stateIndex == 6;
                        app.Telemetry.vcu.errorActive = stateIndex == 6;
                    end
                else
                    app.VcuStateEnteredS = NaN;
                    app.VcuStateLast = '';
                    app.Telemetry.vcu.timeInStateS = NaN;
                end
                if live.appsBrakeFaultKnown
                    app.Telemetry.appsBrakeFault = live.appsBrakeFault;
                else
                    app.Telemetry.appsBrakeFault = [];
                end
                % XcpDriving now reflects the live hil_cmd_xcp_pedals_active
                % target parameter (see TargetSession.readLiveIo) instead of
                % being a permanent placeholder. Unknown (read failed, or an
                % application built before this parameter existed) fails
                % closed to false -- GUI keeps/regains pedal write
                % ownership, matching the resolved policy's default-to-GUI
                % behavior in controlPolicy.m.
                if live.xcpPedalsActiveKnown
                    app.XcpDriving = live.xcpPedalsActive;
                else
                    app.XcpDriving = false;
                end
                wasCanDriving = app.CanPedalsDriving;
                if live.canPedalsKnown
                    app.CanPedalsDriving = live.canPedalsDriving;
                    if app.CanPedalsDriving
                        % Sliders are diagnostic/read-only during CAN
                        % ownership, so display the live target values.
                        app.ThrottleSlider.Value = live.canPedals(1);
                        app.ThrottleField.Value = live.canPedals(1);
                        app.BrakeSlider.Value = live.canPedals(2);
                        app.BrakeField.Value = live.canPedals(2);
                    elseif wasCanDriving
                        % A dead CAN link must never pick up an old GUI slider
                        % position. Reset the GUI-owned fallback at handover.
                        app.commitWrite('pedals.throttle', 0, true);
                        app.commitWrite('pedals.brake', 0, true);
                    end
                else
                    app.CanPedalsDriving = false;
                end
                % Fix 1: the IO183 Rail Monitor AI readback of the pedal
                % harness taps (5V_THROTTLE_1/2, 5V_BP_1/2), a genuine
                % hardware self-check measurement of the same lines AO01-04
                % command -- see TARGETSESSION.READLIVEIO. Shown alongside
                % the commanded throttle/brake percent (ThrottleField /
                % BrakeField, already live) in REFRESHELECTRICAL's rail
                % panel, honestly NaN when unread rather than fabricated.
                %
                % PEDALS.APPLIEDV is sourced from this same ANALOGINV, not
                % LIVE.PEDALSAPPLIEDV: that field is a permanent NaN
                % placeholder for a genuinely different, unwired signal (the
                % AO command's own echo -- see TARGETSESSION.READLIVEIO's
                % comment on PEDALSAPPLIEDV), so every consumer of
                % PEDALS.APPLIEDV (PedalVoltageLabels, per-sensor
                % percentages, the plausibility guard) was reading a value
                % that could never be anything but NaN on this bench, even
                % though the genuinely self-looped pedal voltage was already
                % being measured and shown two lines below in the rail
                % panel.
                app.Telemetry.pedals.appliedV = live.analogInV;
                app.Telemetry.analogInV = live.analogInV;
                % Synchronized sensor state. REQUESTEDANGLEDEG is owned by
                % the app (the dial), so it is deliberately not overwritten
                % from the target -- everything else here is measured.
                if isfield(live, 'imu')
                    app.Telemetry.imu = live.imu;
                end
                if isfield(live, 'steering')
                    requested = app.Telemetry.steering.requestedAngleDeg;
                    app.Telemetry.steering = live.steering;
                    app.Telemetry.steering.requestedAngleDeg = requested;
                end
                if live.can.known
                    d = live.can.diagnostics;
                    app.Telemetry.can.diagnostics.busLoadPercent = ...
                        d.busLoadPercent;
                    app.Telemetry.can.diagnostics.busOff = d.busOff;
                    app.Telemetry.can.diagnostics.recoveryCount = ...
                        d.recoveryCount;
                    app.Telemetry.can.diagnostics.transmitOverrun = ...
                        d.transmitOverrun;
                    app.Telemetry.can.diagnostics.receiveOverrun = ...
                        d.receiveOverrun;
                    app.Telemetry.can.diagnostics.errorWarning = ...
                        d.errorWarning;
                    app.Telemetry.can.diagnostics.writeSucceeded = ...
                        d.writeSucceeded;
                    app.Telemetry.can.diagnostics.writeKnown = d.writeKnown;
                end
                if live.txPayloadsKnown
                    app.applyLiveTxFrames(live);
                end
                % No inverter feedback path exists in this model. Do not
                % populate inverter panels from the HIL's own transmitted
                % status frames; those bytes are output, not measured state.
                if live.inverterKnown
                    app.applyLiveInverters(live.inverter);
                end
                if live.rx.known || live.pedalPayloadKnown
                    app.applyLiveRxFrames(live.rx, live);
                end
            else
                app.VcuStateEnteredS = NaN;
                app.VcuStateLast = '';
                app.Telemetry.vcu.timeInStateS = NaN;
                app.Telemetry.io.healthy = false;
                app.Telemetry.io.healthyKnown = false;
                for index = 1:numel(app.Telemetry.pins)
                    app.Telemetry.pins(index).state = [];
                end
                app.Telemetry.pedals.appliedV = nan(1, 4);
                app.Telemetry.analogInV = nan(1, 4);
                app.Telemetry.appsBrakeFault = [];
                blankCan = inverterhilgui.blankTelemetry().can.diagnostics;
                app.Telemetry.can.diagnostics = blankCan;
                % Read failed or not connected: fail closed to GUI-owned
                % pedals only when neither external source reports ownership.
                app.XcpDriving = false;
                app.CanPedalsDriving = false;
            end
            app.Telemetry.pedals.throttleAppliedPercent = ...
                app.appliedPedalPercent(1, 'v1');
            app.Telemetry.pedals.brakeAppliedPercent = ...
                app.appliedPedalPercent(3, 'v3');
            app.Telemetry.dcLink = inverterhilgui.blankTelemetry().dcLink;
            status = struct('dcLink12V', NaN, 'dcLink34V', NaN, ...
                'dcLink12AboveMinimum', [], 'dcLink34AboveMinimum', []);
            if live.known && isstruct(live.systemStatus)
                status = live.systemStatus;
            end
            voltageFields = {'dcLink12V', 'dcLink34V'};
            flagFields = {'dcLink12AboveMinimum', ...
                'dcLink34AboveMinimum'};
            for index = 1:2
                voltage = status.(voltageFields{index});
                aboveMinimum = status.(flagFields{index});
                if isnumeric(voltage) && isscalar(voltage) && ...
                        isfinite(voltage)
                    app.Telemetry.dcLink(index).voltageV = double(voltage);
                    app.Telemetry.dcLink(index).rawCount = round( ...
                        double(voltage) * 64);
                    app.Telemetry.dcLink(index).capturePending = false;
                end
                if (islogical(aboveMinimum) || isnumeric(aboveMinimum)) && ...
                        isscalar(aboveMinimum) && isfinite(double(aboveMinimum))
                    app.Telemetry.dcLink(index).aboveMinimum = ...
                        logical(aboveMinimum);
                end
            end
            [~, plausibilityOk] = app.pedalSensorPercentages();
            % MAIN_BTN_IN is edge-pulsed (see MainButtonLastPressedS above),
            % so "pressed" here means "pressed recently enough to still be
            % the operator's most recent action" rather than a live pin
            % level. 1 s comfortably covers several 250 ms poll cycles so a
            % press is never silently missed between polls.
            mainButtonPressWindowS = 1.0;
            app.Telemetry.guards.mainButton = ...
                (app.hostTimeS() - app.MainButtonLastPressedS) <= ...
                mainButtonPressWindowS;
            app.Telemetry.guards.brakePercent = ...
                app.Telemetry.pedals.brakeAppliedPercent;
            app.Telemetry.guards.dcLink12V = status.dcLink12V;
            app.Telemetry.guards.dcLink34V = status.dcLink34V;
            app.Telemetry.guards.plausibilityOk = plausibilityOk;
        end

        function applyLiveTxFrames(app, live)
            %APPLYLIVETXFRAMES Fill the HIL TX table from the frames actually
            %   being transmitted, decoded plus their raw bytes.
            %
            %   MEASURED RATE IS DELIBERATELY LEFT UNKNOWN. CANROWMODEL
            %   derives the rate from consecutive observed timestamps and its
            %   help is explicit that the 5 ms nominal cycle must never be
            %   assumed. This app polls at the 250 ms status tick, so feeding
            %   it poll times would report about 4 Hz for frames the model
            %   emits at 200 Hz -- a plausible-looking, wrong number. Leaving
            %   TIMESTAMPSS holds exactly ONE entry, this poll's host time --
            %   never accumulated -- so CANROWMODEL's rate calculation (which
            %   needs at least 2 samples) stays off and the column keeps
            %   reading dashes, the honest statement that polling cannot
            %   measure this rate. A single timestamp is enough for
            %   CANROWMODEL's LIVE/STALE check, though, which only asks
            %   whether the most recent sample is still fresh; leaving
            %   TIMESTAMPSS empty (as before) starved that check too, so
            %   every row read NO DATA forever regardless of whether the
            %   target was actually transmitting. A real rate still needs
            %   frame-arrival instrumentation on the target.
            %
            %   COUNT is different: LIVE.TXMESSAGECOUNT is a genuine,
            %   target-measured cumulative count (EPHORUSSYSTEMSTATUSSTEP's
            %   TXCOUNT), not derived from poll times, so it is shown
            %   verbatim -- the same "number of messages sent" a CAN
            %   analyzer like PCAN-View shows, in place of a rate this app
            %   cannot honestly measure.
            payloads = live.txPayloads;
            observations = app.Telemetry.can.tx;
            now = app.hostTimeS();

            % Whether the target's own transmit count advanced since the
            % last poll -- a genuine observation that frames are actually
            % leaving, which INVERTERHILGUI.CANACKSTATUS requires before it
            % will credit an error-free controller with acknowledgement.
            count = live.txMessageCount;
            if isnumeric(count) && isscalar(count) && isfinite(count)
                if isfinite(app.LastTxMessageCount)
                    app.TxTransmitting = count > app.LastTxMessageCount;
                end
                app.LastTxMessageCount = count;
            else
                app.TxTransmitting = false;
            end
            ack = inverterhilgui.canAckStatus( ...
                app.Telemetry.can.diagnostics, app.TxTransmitting);

            % Rows past the Ephorus block are the sensor frames, whose
            % payloads arrive separately and are SHORTER than eight bytes.
            % They are appended here rather than padded into LIVE.TXPAYLOADS
            % so the table never shows padding as though it were on the wire.
            lengths = repmat(8, 1, size(payloads, 1));
            if isfield(live, 'sensorPayloadsKnown') && live.sensorPayloadsKnown
                payloads = [payloads; live.sensorPayloads];
                lengths = [lengths, live.sensorPayloadLengths(:)'];
            end

            for index = 1:numel(observations)
                if index > size(payloads, 1)
                    break;
                end
                if index > 9 && isfield(live, 'sensorTxCounts')
                    sensorIndex = index - 9;
                    if numel(live.sensorTxCounts) >= sensorIndex && ...
                            live.sensorTxCounts(sensorIndex) == 0
                        % A cached payload exists from model initialization,
                        % but count zero proves it has never been offered to
                        % this CAN Write. Show the genuine zero count while
                        % leaving bytes/live state as NO DATA.
                        observations(index).count = 0;
                        observations(index).timestampsS = [];
                        continue;
                    end
                end
                bytes = payloads(index, 1:lengths(index));
                value = sprintf('%02X ', bytes);
                previous = observations(index).value;
                observations(index).value = strtrim(value);
                observations(index).signal = ...
                    ['HIL-generated | ' ack.text];
                if ~strcmp(previous, observations(index).value)
                    observations(index).lastChangeS = now;
                end
                if index <= 9
                    observations(index).timestampsS = now;
                    observations(index).count = live.txMessageCount;
                else
                    sensorIndex = index - 9;
                    % SENSORCOUNTS and SENSORAGESS are maintained by the
                    % target's 5 ms sensor producer. Host poll timestamps
                    % are never counted, differenced, or treated as sensor
                    % time. NOW merely anchors the target-measured age for
                    % CANROWMODEL's LIVE/STALE presentation; the single
                    % timestamp cannot produce a fabricated rate.
                    observations(index).count = NaN;
                    observations(index).timestampsS = [];
                    if isfield(live, 'sensorTxCounts') && ...
                            numel(live.sensorTxCounts) >= sensorIndex
                        observations(index).count = ...
                            live.sensorTxCounts(sensorIndex);
                    end
                    if isfield(live, 'sensorAgesS') && ...
                            numel(live.sensorAgesS) >= sensorIndex
                        targetAgeS = live.sensorAgesS(sensorIndex);
                        if isnumeric(targetAgeS) && isscalar(targetAgeS) && ...
                                isfinite(targetAgeS) && targetAgeS >= 0
                            observations(index).timestampsS = now - targetAgeS;
                        end
                    end
                end
            end
            app.Telemetry.can.tx = observations;
        end

        function applyLiveRxFrames(app, rx, live)
            %APPLYLIVERXFRAMES Fill the VCU TX / HIL RX table from the frames
            %   the target genuinely retained.
            %
            %   A channel that has received nothing keeps its blank row and
            %   renders as dashes. It is NOT filled with the zero payload the
            %   observation carries, because eight 00 bytes is a frame a VCU
            %   can legitimately send -- showing it for a silent channel would
            %   be indistinguishable from real traffic.
            %
            %   Rate is left unmeasured for the same reason as the TX table:
            %   this app polls far slower than frames arrive, so any rate it
            %   derived from poll times would be plausible and wrong.
            %   ACCEPTEDCOUNT is shown instead, which is a real number the
            %   target counted.
            %
            %   TIMESTAMPSS gets exactly ONE entry per channel, computed as
            %   NOW minus the target's own AGEMS -- a real, target-measured
            %   per-frame age (from EPHORUS RX RETENTION's 1 ms clock), not
            %   a poll-time guess -- so CANROWMODEL's LIVE/STALE check
            %   reflects whether the CHANNEL is actually current, not just
            %   whether this poll happened to succeed. A single entry never
            %   feeds CANROWMODEL's rate calculation (which needs 2+), so
            %   the RATE column still correctly stays dashes.
            observations = app.Telemetry.can.rx;
            now = app.hostTimeS();
            if live.pedalPayloadKnown && numel(observations) >= 1
                payload = live.pedalPayload;
                previous = observations(1).value;
                observations(1).value = strtrim(sprintf('%02X ', payload));
                observations(1).signal = app.pedalFrameSignalText(payload);
                observations(1).timestampsS = now;
                % Genuine, target-measured transmit count (Port A Pedal TX
                % Counter, read via PEDALTXCOUNT) when available; NaN/dashes
                % on an older build that predates that counter, never a
                % fabricated estimate.
                if live.pedalTxCountKnown
                    observations(1).count = live.pedalTxCount;
                else
                    observations(1).count = NaN;
                end
                if ~strcmp(previous, observations(1).value)
                    observations(1).lastChangeS = now;
                end
            end
            for index = 2:numel(observations)
                channelIndex = index - 1;
                if channelIndex < 1 || channelIndex > numel(rx.channels)
                    break;
                end
                channel = rx.channels(channelIndex);
                if isempty(channel.hasCommand) || ~channel.hasCommand
                    observations(index).signal = 'no frame received';
                    observations(index).value = '';
                    observations(index).timestampsS = [];
                    continue;
                end
                previous = observations(index).value;
                observations(index).value = ...
                    strtrim(sprintf('%02X ', channel.payload));
                observations(index).signal = ...
                    app.rxFrameSignalText(observations(index).id, channel);
                if ~strcmp(previous, observations(index).value)
                    observations(index).lastChangeS = now;
                end
                if isnumeric(channel.ageMs) && isscalar(channel.ageMs) && ...
                        isfinite(channel.ageMs) && ...
                        channel.ageMs < double(intmax('uint32'))
                    observations(index).timestampsS = now - double(channel.ageMs) / 1000;
                end
                observations(index).count = double(channel.acceptedCount);
            end
            app.Telemetry.can.rx = observations;
        end

        function text = pedalFrameSignalText(~, payload)
            %PEDALFRAMESIGNALTEXT Decode only the explicit VCU 0x1F5 contract.
            if numel(payload) ~= 8
                text = 'invalid pedal payload';
                return;
            end
            front = double(payload(2)) + 256 * double(payload(3));
            rear = double(payload(4)) + 256 * double(payload(5));
            text = sprintf('throttle %d %% | front %d PSI | rear %d PSI | steering 0', ...
                payload(1), front, rear);
        end

        function text = rxFrameSignalText(app, id, channel)
            %RXFRAMESIGNALTEXT Decoded summary of one retained control frame.
            %   Decoded here from the retained bytes with the SAME decoder the
            %   model uses, so this column can never disagree with the raw
            %   payload beside it. ID is the row's own control ID.
            [accepted, ~, command] = inverterhil.decodeControlFrame( ...
                uint32(id), uint8(8), channel.payload, false, false);
            if ~accepted
                text = 'retained bytes no longer decode';
                return;
            end
            % Torque limits are reported as RAW COUNTS, not Nm. Converting
            % would require choosing between the 1/512 and 1/256 scales, and
            % that question is unresolved (INVERTERHIL.PROTOCOL marks both
            % profiles verified = false). Counts are what is on the wire and
            % are correct under either answer.
            text = sprintf(['en=%d rst=%d asc=%d imode=%d | %d rpm | ' ...
                'trq %+d/%+d counts | %d rx, age %s'], ...
                command.enable, command.resetError, command.ascAllowed, ...
                command.currentMode, command.speedSetpointRpm, ...
                command.rawTorquePosCounts, command.rawTorqueNegCounts, ...
                channel.acceptedCount, app.formatAgeMs(channel.ageMs));
            if ~isempty(channel.outOfDomain) && channel.outOfDomain
                text = [text ' | TORQUE LIMITS CLAMPED'];
            end
        end

        function text = formatAgeMs(app, value)
            %FORMATAGEMS Command age, dashes when unknown or never-received.
            if ~isnumeric(value) || ~isscalar(value) || ~isfinite(value) || ...
                    value >= double(intmax('uint32'))
                text = app.Theme.text.noData;
            else
                text = sprintf('%d ms', round(value));
            end
        end

        function applyLiveInverters(app, decoded)
            %APPLYLIVEINVERTERS Copy decoded status-frame values into the
            %   telemetry snapshot the inverter panels render.
            %
            %   FORMATINVERTERPANEL renders torque through
            %   FORMATTORQUECANDIDATES, which expects a RAW COUNT and applies
            %   both candidate scales itself. The decoded values are already
            %   in Nm at the frame's own 1/32 scale, so they are converted
            %   back to counts here rather than passed as engineering units,
            %   which would be rescaled a second time and displayed wrong.
            stateNames = {'Idle', 'Drive', 'Error', 'ConfigError'};
            for channel = 1:4
                item = decoded(channel);

                stateIndex = item.state + 1;
                if isfinite(item.state) && stateIndex >= 1 && ...
                        stateIndex <= numel(stateNames)
                    app.Telemetry.inverter(channel).state = ...
                        stateNames{stateIndex};
                else
                    app.Telemetry.inverter(channel).state = '';
                end

                app.Telemetry.inverter(channel).ready = item.ready;
                app.Telemetry.inverter(channel).derating = item.derating;
                app.Telemetry.inverter(channel).torqueActualRaw = ...
                    item.torqueActualNm * 32;
                app.Telemetry.inverter(channel).torqueCommandRaw = ...
                    item.torqueCommandNm * 32;
                app.Telemetry.inverter(channel).motorTemperatureC = ...
                    item.motorTemperatureC;
                app.Telemetry.inverter(channel).switchTemperatureC = ...
                    item.switchTemperatureC;
                app.Telemetry.inverter(channel).idSetpointA = ...
                    item.idSetpointA;
                app.Telemetry.inverter(channel).idActualA = item.idActualA;
                app.Telemetry.inverter(channel).iqSetpointA = ...
                    item.iqSetpointA;
                app.Telemetry.inverter(channel).iqActualA = item.iqActualA;
                app.Telemetry.inverter(channel).speedRpm = item.speedRpm;
                % commandAgeS and activeFault are NOT carried by the status
                % frames, so they stay at their blankTelemetry unknowns
                % rather than being invented from the decode.
            end
        end

        function percent = appliedPedalPercent(app, aoChannel, calSuffix)
            %APPLIEDPEDALPERCENT Invert PEDALVOLTAGECALIBRATION's own mapping
            %   to show what percent the measured AO voltage corresponds to.
            %   Uses only values already read from the target (measured
            %   voltage, and the calibration endpoints the target itself
            %   reports back), not invented telemetry.
            percent = NaN;
            appliedV = app.Telemetry.pedals.appliedV(aoChannel);
            if ~isfinite(appliedV)
                return;
            end
            [releasedV, releasedKnown] = app.Session.readCached( ...
                ['cal.pedals.released_' calSuffix]);
            [pressedV, pressedKnown] = app.Session.readCached( ...
                ['cal.pedals.pressed_' calSuffix]);
            if ~releasedKnown || ~pressedKnown || ...
                    ~isfinite(releasedV) || ~isfinite(pressedV) || ...
                    releasedV == pressedV
                return;
            end
            fraction = (appliedV - releasedV) / (pressedV - releasedV);
            percent = min(max(fraction, 0), 1) * 100;
        end

        function [percentages, plausibilityOk] = pedalSensorPercentages(app)
            %PEDALSENSORPERCENTAGES Mirror the VCU pedal plausibility math
            %   for display only, using the already-read pedal voltages.
            percentages = nan(1, 4);
            plausibilityOk = [];
            voltages = app.Telemetry.pedals.appliedV;
            if ~isnumeric(voltages) || numel(voltages) < 4
                return;
            end
            raw = double(voltages(1:4)) / 3.3 * 65535;
            valid = isfinite(raw);
            if valid(1)
                percentages(1) = 100 * min(max((30100 - raw(1)) / 9200, 0), 1);
            end
            if valid(2)
                percentages(2) = 100 * min(max((63600 - raw(2)) / 17100, 0), 1);
            end
            if valid(3)
                percentages(3) = 100 * min(max((raw(3) - 9025) / 22775, 0), 1);
            end
            if valid(4)
                percentages(4) = 100 * min(max((raw(4) - 8280) / 23520, 0), 1);
            end
            if valid(1) && valid(2)
                plausibilityOk = logical(abs(percentages(1) - percentages(2)) <= 20);
            end
        end

        function refreshPolicy(app)
            %REFRESHPOLICY Apply the single control-enable authority.
            lifecycle = app.Session.describeState();
            interlocks = struct( ...
                'expertMode', app.ExpertModeCheckBox.Value, ...
                'plausibilityOverride', app.PlausibilityCheckBox.Value, ...
                'targetHealthy', app.Telemetry.io.healthy, ...
                'heartbeatOk', lifecycle.isConnected, ...
                'contractResolved', ~isempty(app.Session.Contract));
            app.Policy = inverterhilgui.controlPolicy(lifecycle.state, ...
                app.Telemetry.vcu.state, interlocks, app.XcpDriving, ...
                app.CanPedalsDriving);
            app.applyEnable([app.ThrottleSlider app.ThrottleField ...
                app.BrakeSlider app.BrakeField], app.Policy.pedals);
            app.applyEnable([app.SteeringDial app.SteeringField], ...
                app.Policy.sensorStimulus);
            % Sensor-local dropout, stale payload, wrong DLC, illegal status,
            % and sentinel injection all follow the sensorStimulus policy.
            app.applyEnable([app.SteeringDropoutCheckBox ...
                app.SteeringStaleCheckBox app.SteeringMalformedCheckBox ...
                app.SteeringInvalidStatusCheckBox ...
                app.SteeringAngleSentinelCheckBox ...
                app.SteeringSpeedSentinelCheckBox app.ImuDropoutCheckBox ...
                app.ImuStaleCheckBox app.ImuMalformedCheckBox], ...
                app.Policy.sensorStimulus);
            app.applyEnable(app.LwsCalibrationButton, app.Policy.calibration);
            app.applyEnable([app.CoolingSwitch ...
                app.ShutdownFeedbackSwitch], app.Policy.digitalStimuli);
            app.applyEnable([app.PrechargeButton app.MainMomentaryButton], ...
                app.Policy.momentary);
            app.applyEnable(app.FaultMaskFields, app.Policy.faultInjection);
            app.applyEnable(app.LoadTorqueFields, app.Policy.plantParameters);
            app.applyEnable(app.ConnectedCheckBoxes, ...
                app.Policy.plantParameters);
            app.applyEnable([app.DropControlField app.DropStatusField], ...
                app.Policy.canFaults);
            app.applyEnable(app.ExportLogButton, app.Policy.logExport);
            allowed = app.Session.describeState().allowed;
            app.applyEnable(app.ConnectButton, ...
                allowed.connect || allowed.disconnect);
            app.applyEnable(app.LoadButton, allowed.load);
            app.applyEnable(app.StartButton, allowed.start);
            app.applyEnable(app.StopButton, allowed.stop);
            app.applyEnable(app.ResetButton, allowed.reset);
        end

        function refreshToolbar(app)
            %REFRESHTOOLBAR Repaint identity, states, and elapsed target time.
            theme = app.Theme;
            lifecycle = app.Session.describeState();
            app.TargetNameLabel.Text = ['TARGET ' app.Session.TargetName];
            app.ConnectionStateLabel.Text = upper(lifecycle.state);
            if lifecycle.isConnected
                app.ConnectionStateLabel.FontColor = theme.color.healthy;
            elseif strcmp(lifecycle.state, 'connecting')
                app.ConnectionStateLabel.FontColor = theme.color.waiting;
            else
                app.ConnectionStateLabel.FontColor = theme.color.fault;
            end
            if lifecycle.isRunning
                app.ApplicationStateLabel.Text = 'APP RUNNING';
                app.ApplicationStateLabel.FontColor = theme.color.healthy;
            else
                app.ApplicationStateLabel.Text = ['APP ' ...
                    upper(lifecycle.state)];
                app.ApplicationStateLabel.FontColor = ...
                    theme.color.secondaryText;
            end
            app.ElapsedTimeLabel.Text = ['TARGET T ' ...
                app.formatSeconds(app.Session.executionTimeS())];
            app.ConnectButton.Text = 'Connect';
            if lifecycle.isConnected
                app.ConnectButton.Text = 'Disconnect';
            end
        end

        function refreshStateStrip(app)
            %REFRESHSTATESTRIP Paint graphical active/passed/upcoming cards.
            theme = app.Theme;
            current = app.Telemetry.vcu.state;
            for index = 1:numel(app.VcuStateNames)
                status = inverterhilgui.stateCardStyle(current, ...
                    app.VcuStateNames{index}, ...
                    app.Telemetry.vcu.errorKnown && app.Telemetry.vcu.errorActive);
                switch status
                    case 'active'
                        color = theme.color.healthy;
                        background = theme.color.highlight;
                        weight = 'bold';
                    case 'passed'
                        color = theme.color.electrical;
                        background = theme.color.panel;
                        weight = 'normal';
                    case 'upcoming'
                        color = theme.color.disabledText;
                        background = theme.color.background;
                        weight = 'normal';
                    otherwise
                        color = theme.color.secondaryText;
                        background = theme.color.background;
                        weight = 'normal';
                end
                app.StateStripLabels(index).FontColor = color;
                app.StateStripLabels(index).BackgroundColor = background;
                app.StateStripLabels(index).FontWeight = weight;
            end
            if app.Telemetry.vcu.errorKnown && app.Telemetry.vcu.errorActive
                % FontColor and BackgroundColor must differ, or "ERROR"
                % renders invisible against its own highlight -- exactly
                % what a same-color pair does. Dark text on the fault-red
                % background reads clearly, matching how every other card
                % state (active/passed/upcoming) already uses two
                % distinct colors.
                app.StateErrorLabel.FontColor = theme.color.background;
                app.StateErrorLabel.FontWeight = 'bold';
                app.StateErrorLabel.BackgroundColor = theme.color.fault;
            else
                app.StateErrorLabel.FontColor = theme.color.disabledText;
                app.StateErrorLabel.FontWeight = 'normal';
                app.StateErrorLabel.BackgroundColor = theme.color.background;
            end
            app.TimeInStateLabel.Text = ['TIME IN STATE ' ...
                app.formatSeconds(app.Telemetry.vcu.timeInStateS)];
        end

        function refreshGuards(app)
            %REFRESHGUARDS Repaint the NEXT TRANSITION pass/fail rows.
            guards = inverterhilgui.evaluateTransitionGuards( ...
                app.Telemetry.guards, struct());
            data = cell(numel(guards), 4);
            for index = 1:numel(guards)
                data(index, :) = {guards(index).name, ...
                    guards(index).actual, guards(index).required, ...
                    app.guardResultText(guards(index))};
            end
            app.GuardTable.Data = data;
        end

        function text = guardResultText(app, guard)
            %GUARDRESULTTEXT Pass/fail text; unknown is never shown as pass.
            if ~guard.known
                text = app.Theme.text.noData;
            elseif guard.pass
                text = 'PASS';
            else
                text = 'FAIL';
            end
        end

        function refreshDriverInputs(app)
            %REFRESHDRIVERINPUTS Repaint requested and applied pedal values.
            theme = app.Theme;
            pedals = app.Telemetry.pedals;
            % Throttle+brake plausibility interlock (VIRTUALVCUDEPLOYSTEP.M's
            % APPSBRAKEFAULT): shown directly on the two labels the operator
            % is already looking at while pressing pedals, rather than a new
            % banner elsewhere that could go unnoticed. Only ever appended
            % when the chart itself reports the fault (islogical/true), never
            % inferred here from a torque number happening to read zero.
            faultActive = islogical(app.Telemetry.appsBrakeFault) && ...
                app.Telemetry.appsBrakeFault;
            if faultActive
                app.ThrottleAppliedLabel.Text = sprintf( ...
                    'APPLIED %s | APPS+BRAKE FAULT: TORQUE SUPPRESSED', ...
                    app.formatPercent(pedals.throttleAppliedPercent));
                app.BrakeAppliedLabel.Text = sprintf( ...
                    'APPLIED %s | APPS+BRAKE FAULT: TORQUE SUPPRESSED', ...
                    app.formatPercent(pedals.brakeAppliedPercent));
                app.ThrottleAppliedLabel.FontColor = theme.color.fault;
                app.BrakeAppliedLabel.FontColor = theme.color.fault;
            else
                app.ThrottleAppliedLabel.Text = sprintf('APPLIED %s', ...
                    app.formatPercent(pedals.throttleAppliedPercent));
                app.BrakeAppliedLabel.Text = sprintf('APPLIED %s', ...
                    app.formatPercent(pedals.brakeAppliedPercent));
                app.ThrottleAppliedLabel.FontColor = theme.color.secondaryText;
                app.BrakeAppliedLabel.FontColor = theme.color.secondaryText;
            end
            [sensorPercentages, ~] = app.pedalSensorPercentages();
            throttleMismatch = isfinite(sensorPercentages(1)) && ...
                isfinite(sensorPercentages(2)) && ...
                abs(sensorPercentages(1) - sensorPercentages(2)) > 20;
            % REQUESTED (dial), APPLIED (virtual car), SPEED (derived), and
            % LWS (independently decoded frame value) are four DIFFERENT
            % quantities, so they get four separate fields rather than one
            % label that flips between them. The dial is not a display-only
            % LWS override: it feeds the shared vehicle state through a
            % bounded steering rate, so REQUESTED and APPLIED genuinely
            % differ while the car is still slewing, and LWS is what the
            % encoded CAN frame actually carries. Unknown values render as
            % dashes -- never a fabricated zero.
            if isfield(app.Telemetry, 'steering')
                steering = app.Telemetry.steering;
            else
                steering = inverterhilgui.blankTelemetry().steering;
            end
            app.SteeringAppliedLabel.Text = sprintf( ...
                'REQUESTED %s | APPLIED %s | SPEED %s | LWS %s', ...
                app.formatSteeringValue(app.RequestedSteeringDeg, 'deg'), ...
                app.formatSteeringValue(steering.appliedAngleDeg, 'deg'), ...
                app.formatSteeringValue(steering.speedDegPerS, 'deg/s'), ...
                app.formatSteeringValue(steering.observedAngleDeg, 'deg'));
            for index = 1:4
                measurement = inverterhilgui.formatMeasurement( ...
                    pedals.appliedV(index), NaN, 'V', false);
                app.PedalVoltageLabels(index).Text = sprintf('%s %s | %s', ...
                    app.PedalChannelNames{index}, measurement.value, ...
                    app.formatPercent(sensorPercentages(index)));
                if throttleMismatch && index <= 2
                    app.PedalVoltageLabels(index).FontColor = theme.color.fault;
                else
                    app.PedalVoltageLabels(index).FontColor = ...
                        theme.color.electrical;
                end
            end
            for index = 1:numel(app.DigitalNames)
                [value, known] = app.Session.readCached( ...
                    ['digital.' app.DigitalNames{index}]);
                if known
                    display = inverterhilgui.formatPinState(value);
                    app.DigitalAppliedLabels(index).Text = display.text;
                    app.DigitalAppliedLabels(index).FontColor = display.color;
                else
                    app.DigitalAppliedLabels(index).Text = theme.text.noData;
                    app.DigitalAppliedLabels(index).FontColor = ...
                        theme.color.secondaryText;
                end
            end
            app.MomentaryLabels(1).Text = sprintf('seq %u', ...
                app.PrechargeSequence);
            app.MomentaryLabels(2).Text = sprintf('seq %u', ...
                app.MainButtonSequence);
        end

        function refreshElectrical(app)
            %REFRESHELECTRICAL Repaint DC-link mimic, pins, and rails.
            theme = app.Theme;
            for index = 1:2
                link = app.Telemetry.dcLink(index);
                measurement = inverterhilgui.formatMeasurement( ...
                    link.voltageV, link.rawCount, 'V', link.capturePending);
                app.DcLinkValueLabels(index).Text = measurement.combined;
                display = inverterhilgui.formatPinState(link.aboveMinimum);
                app.DcLinkFlagLabels(index).Text = ['ABOVE MIN ' display.text];
                app.DcLinkFlagLabels(index).FontColor = display.color;
            end
            frequency = inverterhilgui.formatMeasurement( ...
                app.Telemetry.switchingFrequencyKHz, ...
                app.Telemetry.switchingFrequencyRaw, 'kHz', true);
            app.SwitchingFrequencyLabel.Text = frequency.combined;
            for index = 1:numel(app.Telemetry.pins)
                display = inverterhilgui.formatPinState( ...
                    app.Telemetry.pins(index).state);
                app.PinStateLabels(index).Text = display.text;
                app.PinStateLabels(index).FontColor = display.color;
            end
            railNames = {'AI01 5V_THR1', 'AI02 5V_THR2', 'AI03 5V_BP1', ...
                'AI04 5V_BP2'};
            for index = 1:4
                measurement = inverterhilgui.formatMeasurement( ...
                    app.Telemetry.analogInV(index), NaN, 'V', false);
                app.AnalogInputLabels(index).Text = sprintf('%s %s', ...
                    railNames{index}, measurement.value);
            end
            app.TorqueBannerLabel.BackgroundColor = theme.color.fault;
        end

        function refreshInverters(app)
            %REFRESHINVERTERS Repaint the four inverter panels.
            for channel = 1:4
                panel = inverterhilgui.formatInverterPanel(app.Telemetry, ...
                    channel);
                values = {panel.state, panel.ready, panel.commandAge, ...
                    panel.torqueCommand, panel.torqueActual, panel.speed, ...
                    panel.idCurrent, panel.iqCurrent, ...
                    panel.motorTemperature, panel.switchTemperature, ...
                    panel.derating, panel.activeFault};
                for field = 1:numel(values)
                    app.InverterFieldLabels(channel, field).Text = ...
                        values{field};
                end
                app.InverterTitleLabels(channel).Text = panel.title;
                app.InverterCornerLabels(channel).Text = panel.corner;
                % A confirmed corner is ordinary identification, not an alarm;
                % only the UNVERIFIED placeholder stays fault-coloured.
                if panel.cornerVerified
                    app.InverterCornerLabels(channel).FontColor = ...
                        app.Theme.color.secondaryText;
                else
                    app.InverterCornerLabels(channel).FontColor = ...
                        app.Theme.color.fault;
                end
            end
        end

        function refreshSensors(app)
            %REFRESHSENSORS Repaint the synchronized MTi/LWS health readout.
            theme = app.Theme;
            blank = inverterhilgui.blankTelemetry();
            if isfield(app.Telemetry, 'steering')
                steering = app.Telemetry.steering;
            else
                steering = blank.steering;
            end
            if isfield(app.Telemetry, 'imu')
                imu = app.Telemetry.imu;
            else
                imu = blank.imu;
            end

            app.SensorSteeringLabel.Text = sprintf( ...
                ['STEERING  REQUESTED %s | APPLIED %s | SPEED %s | ' ...
                'LWS %s | VALID %s | AGE %s'], ...
                app.formatSteeringValue(app.RequestedSteeringDeg, 'deg'), ...
                app.formatSteeringValue(steering.appliedAngleDeg, 'deg'), ...
                app.formatSteeringValue(steering.speedDegPerS, 'deg/s'), ...
                app.formatSteeringValue(steering.observedAngleDeg, 'deg'), ...
                app.sensorValidityText(steering.valid), ...
                app.formatSeconds(steering.ageS));

            app.SensorImuAccelLabel.Text = sprintf( ...
                'MTi ACCEL 0x034  %s | VALID %s | AGE %s', ...
                app.formatVector(imu.accelerationMps2, 'm/s^2'), ...
                app.sensorValidityText(imu.valid), ...
                app.formatSeconds(imu.ageS));
            app.SensorImuRateLabel.Text = sprintf('MTi RATE 0x032   %s', ...
                app.formatVector(imu.rateOfTurnRadPerS, 'rad/s'));
            app.SensorImuVelocityLabel.Text = sprintf( ...
                'MTi VELOCITY 0x076  %s', ...
                app.formatVector(imu.velocityMps, 'm/s'));
            app.SensorCalibrationLabel.Text = sprintf( ...
                'LWS CALIBRATION  %s', ...
                app.lwsCalibrationStateText(steering.calibrationState));

            % A dropout the operator injected is a commanded state, not a
            % fault, so it is called out plainly rather than coloured as an
            % error the rig discovered by itself.
            if isfield(steering, 'dropout') && islogical(steering.dropout) ...
                    && steering.dropout
                app.SensorSteeringLabel.FontColor = theme.color.fault;
            else
                app.SensorSteeringLabel.FontColor = theme.color.primaryText;
            end
        end

        function text = formatVector(app, values, unit)
            %FORMATVECTOR One XYZ sensor readout, dashes when unknown.
            if ~isnumeric(values) || numel(values) ~= 3 || ...
                    ~all(isfinite(values))
                text = app.Theme.text.noData;
                return;
            end
            text = sprintf('X %.2f  Y %.2f  Z %.2f %s', ...
                values(1), values(2), values(3), unit);
        end

        function text = lwsCalibrationStateText(app, value)
            %LWSCALIBRATIONSTATETEXT Decode target sequencer state only.
            labels = {'IDLE', 'RESET 0x05 PENDING', ...
                'WAITING 100 ms + RESET CHECK', 'ZERO 0x03 PENDING', ...
                'WAITING ZERO RESULT CHECK', 'PASSED (TARGET-SIDE)', ...
                'FAILED RESULT CHECK'};
            if isnumeric(value) && isscalar(value) && isfinite(value) && ...
                    value >= 0 && value <= 6 && value == floor(value)
                text = labels{value + 1};
            else
                text = app.Theme.text.noData;
            end
        end

        function text = sensorValidityText(app, value)
            %SENSORVALIDITYTEXT Preserve unknown instead of assuming false.
            if (islogical(value) || isnumeric(value)) && isscalar(value) && ...
                    isfinite(double(value)) && ...
                    (double(value) == 0 || double(value) == 1)
                if logical(value)
                    text = 'YES';
                else
                    text = 'NO';
                end
            else
                text = app.Theme.text.noData;
            end
        end

        function refreshCan(app)
            %REFRESHCAN Repaint both CAN tables and the diagnostics strip.
            now = app.hostTimeS();
            app.paintCanTable(app.CanRxTable, ...
                inverterhilgui.canRowModel(app.Telemetry.can.rx, now));
            app.paintCanTable(app.CanTxTable, ...
                inverterhilgui.canRowModel(app.Telemetry.can.tx, now));
            app.CanDiagnosticsLabel.Text = ...
                app.canDiagnosticsText(app.Telemetry);
        end

        function paintCanTable(app, table, rows)
            %PAINTCANTABLE Render CAN rows and highlight recent payload changes.
            %   The last column shows ROWS.COUNT -- a genuine, target-
            %   measured cumulative message count (PCAN-View style), not
            %   ROWS.RATE: RATE stays dashed by design (see CANROWMODEL),
            %   since nothing here measures real frame-arrival timing, and a
            %   climbing count is a more honest, unambiguous sign of live
            %   traffic than a rate this app cannot actually derive.
            data = cell(numel(rows), 6);
            highlighted = false(1, numel(rows));
            for index = 1:numel(rows)
                data(index, :) = {rows(index).live, rows(index).id, ...
                    rows(index).name, rows(index).signal, ...
                    rows(index).value, rows(index).count};
                highlighted(index) = rows(index).highlight;
            end
            if isempty(rows)
                data = cell(0, 6);
            end
            table.Data = data;
            removeStyle(table);
            if any(highlighted)
                addStyle(table, uistyle('BackgroundColor', ...
                    app.Theme.color.highlight), 'row', find(highlighted));
            end
        end

        function text = canDiagnosticsText(~, snapshot)
            %CANDIAGNOSTICSTEXT One-line CAN diagnostics strip.
            diagnostics = snapshot.can.diagnostics;
            if diagnostics.writeKnown
                % Denominator comes from the flag vector itself, not a
                % literal 9: the model now has fourteen CAN Write blocks
                % (nine Ephorus, four sensor, one LWS config) and a
                % hard-coded 9 under-reported every one of them.
                writeText = sprintf('%d/%d OK', ...
                    sum(diagnostics.writeSucceeded), ...
                    numel(diagnostics.writeSucceeded));
            else
                writeText = '--';
            end
            text = sprintf(['CAN WRITE %s | BUS LOAD %s | TX OVERRUN %s | ' ...
                'RX OVERRUN %s | ERROR WARNING %s | BUS-OFF %s | ' ...
                'RECOVERIES %s | QUEUE %s | BURST %s'], writeText, ...
                inverterhilgui.formatMeasurement( ...
                diagnostics.busLoadPercent, NaN, '%', false).value, ...
                inverterhilgui.formatPinState( ...
                diagnostics.transmitOverrun).text, ...
                inverterhilgui.formatPinState( ...
                diagnostics.receiveOverrun).text, ...
                inverterhilgui.formatPinState( ...
                diagnostics.errorWarning).text, ...
                inverterhilgui.formatPinState(diagnostics.busOff).text, ...
                inverterhilgui.formatMeasurement( ...
                diagnostics.recoveryCount, NaN, '', false).value, ...
                inverterhilgui.formatMeasurement(diagnostics.queueDepth, ...
                NaN, '', false).value, ...
                inverterhilgui.formatMeasurement( ...
                diagnostics.burstDurationS, NaN, 's', false).value);
        end

        function refreshLog(app)
            %REFRESHLOG Repaint the append-only session log view.
            app.LogTable.Data = app.Log.toCell();
            app.LogSummaryLabel.Text = sprintf( ...
                '%d records (append-only)', app.Log.Count);
        end

        function reportError(app, context, err)
            %REPORTERROR Record a failure without inventing a success.
            app.Log.append(struct( ...
                'targetTimeS', NaN, ...
                'logicalName', context, ...
                'targetPath', '', ...
                'requested', '--', ...
                'applied', '--', ...
                'result', 'failed', ...
                'detail', err.message));
        end

        function value = hostTimeS(~)
            %HOSTTIMES Monotonic host clock used by every timing decision.
            value = seconds(datetime('now') - datetime(2026, 1, 1));
        end

        function text = formatSeconds(app, value)
            %FORMATSECONDS Seconds text, dashes when the value is unknown.
            if ~isnumeric(value) || ~isscalar(value) || ~isfinite(value)
                text = app.Theme.text.noData;
            else
                text = sprintf('%.3f s', double(value));
            end
        end

        function text = flagText(~, state)
            %FLAGTEXT ON/OFF text for a decoded boolean status bit.
            %   Delegates to FORMATPINSTATE so a single implementation decides
            %   what an unknown flag looks like, and an unset one can never
            %   render as OFF by accident.
            text = inverterhilgui.formatPinState(state).text;
        end

        function text = formatPercent(app, value)
            %FORMATPERCENT Percent text, dashes when the value is unknown.
            if ~isnumeric(value) || ~isscalar(value) || ~isfinite(value)
                text = app.Theme.text.noData;
            else
                text = sprintf('%.1f %%', double(value));
            end
        end

        function applyEnable(~, components, enabled)
            %APPLYENABLE Apply one policy decision to a set of controls.
            if enabled
                set(components, 'Enable', 'on');
            else
                set(components, 'Enable', 'off');
            end
        end

        function label = makeLabel(app, parent, text, fontSize, color)
            %MAKELABEL Create one themed label.
            label = uilabel(parent);
            label.Text = text;
            label.FontName = app.Theme.font.name;
            label.FontSize = fontSize;
            label.FontColor = color;
        end

        function button = makeButton(app, parent, text, callback)
            %MAKEBUTTON Create one themed button bound to a callback.
            button = uibutton(parent, 'push');
            button.Text = text;
            button.FontName = app.Theme.font.name;
            button.FontSize = app.Theme.font.body;
            button.BackgroundColor = app.Theme.color.panel;
            button.FontColor = app.Theme.color.primaryText;
            button.ButtonPushedFcn = createCallbackFcn(app, callback, true);
        end

        function box = makeCheckBox(app, parent, text, callback)
            %MAKECHECKBOX Create one themed check box bound to a callback.
            box = uicheckbox(parent);
            box.Text = text;
            box.FontName = app.Theme.font.name;
            box.FontSize = app.Theme.font.small;
            box.FontColor = app.Theme.color.primaryText;
            box.ValueChangedFcn = createCallbackFcn(app, callback, true);
        end

        function field = makeNumericField(app, parent, limits, callback)
            %MAKENUMERICFIELD Create one themed numeric field.
            field = uieditfield(parent, 'numeric');
            field.Limits = limits;
            field.Value = limits(1);
            field.FontName = app.Theme.font.name;
            field.FontSize = app.Theme.font.body;
            field.BackgroundColor = app.Theme.color.panel;
            field.FontColor = app.Theme.color.primaryText;
            field.ValueChangedFcn = createCallbackFcn(app, callback, true);
        end

        function grid = makeGrid(app, parent, rowHeight, columnWidth)
            %MAKEGRID Create one dense themed grid layout.
            grid = uigridlayout(parent, ...
                [numel(rowHeight) numel(columnWidth)]);
            grid.RowHeight = rowHeight;
            grid.ColumnWidth = columnWidth;
            grid.Padding = app.Theme.spacing.padding;
            grid.RowSpacing = app.Theme.spacing.rowSpacing;
            grid.ColumnSpacing = app.Theme.spacing.columnSpacing;
            grid.BackgroundColor = app.Theme.color.background;
        end

        function panel = makePanel(app, parent, title)
            %MAKEPANEL Create one small-radius themed panel.
            panel = uipanel(parent);
            panel.Title = title;
            panel.FontName = app.Theme.font.name;
            panel.FontSize = app.Theme.font.small;
            panel.FontWeight = 'bold';
            panel.ForegroundColor = app.Theme.color.secondaryText;
            panel.BackgroundColor = app.Theme.color.panel;
            panel.BorderColor = app.Theme.color.panelEdge;
        end

        function table = makeCanTable(app, parent)
            %MAKECANTABLE Create one themed CAN traffic table.
            table = uitable(parent);
            % Hide MATLAB's unstyleable white column-header strip.
            table.ColumnName = {};
            table.ColumnWidth = {70, 70, 110, 200, 160, 130};
            table.RowName = {};
            table.Data = cell(0, 6);
            table.FontName = app.Theme.font.name;
            table.FontSize = app.Theme.font.small;
            table.BackgroundColor = app.Theme.color.panel;
            table.ForegroundColor = app.Theme.color.primaryText;
        end
    end

    methods (Access = private)

        function onConnectPushed(app, ~)
            %ONCONNECTPUSHED Connect or disconnect the target.
            cleanupObj = app.enterTargetSection(); %#ok<NASGU>
            if app.Session.describeState().isConnected
                app.recordLifecycle('disconnect', app.Session.disconnect());
            else
                app.recordLifecycle('connect', app.Session.connect());
            end
            app.refreshAll();
        end

        function onLoadPushed(app, ~)
            %ONLOADPUSHED Load the real-time application.
            cleanupObj = app.enterTargetSection(); %#ok<NASGU>
            app.recordLifecycle('load', app.Session.load('inverter_hil'));
            app.refreshAll();
        end

        function onStartPushed(app, ~)
            %ONSTARTPUSHED Start the real-time application.
            cleanupObj = app.enterTargetSection(); %#ok<NASGU>
            app.recordLifecycle('start', app.Session.start());
            app.refreshAll();
        end

        function onStopPushed(app, ~)
            %ONSTOPPUSHED Stop the application and fall back to safe outputs.
            cleanupObj = app.enterTargetSection(); %#ok<NASGU>
            app.recordLifecycle('stop', app.Session.stop());
            app.refreshAll();
        end

        function onResetPushed(app, ~)
            %ONRESETPUSHED Reset the target application.
            cleanupObj = app.enterTargetSection(); %#ok<NASGU>
            app.recordLifecycle('reset', app.Session.reset());
            app.refreshAll();
        end

        function recordLifecycle(app, name, result)
            %RECORDLIFECYCLE Audit one lifecycle action and its outcome.
            code = 'failed';
            if result.success
                code = 'lifecycle';
            end
            app.Log.append(struct( ...
                'targetTimeS', app.Session.executionTimeS(), ...
                'logicalName', ['lifecycle.' name], ...
                'targetPath', app.Session.TargetName, ...
                'requested', name, ...
                'applied', result.state, ...
                'result', code, ...
                'detail', result.reason));
        end

        function onThrottleChanging(app, event)
            %ONTHROTTLECHANGING Coalesce rapid throttle motion.
            app.submitPedal(app.ThrottleCoalescer, 'pedals.throttle', ...
                event.Value);
        end

        function onThrottleChanged(app, ~)
            %ONTHROTTLECHANGED Commit the final throttle value.
            app.ThrottleField.Value = app.ThrottleSlider.Value;
            app.submitPedal(app.ThrottleCoalescer, 'pedals.throttle', ...
                app.ThrottleSlider.Value);
        end

        function onThrottleFieldChanged(app, ~)
            %ONTHROTTLEFIELDCHANGED Commit a typed throttle percentage.
            app.ThrottleSlider.Value = app.ThrottleField.Value;
            app.submitPedal(app.ThrottleCoalescer, 'pedals.throttle', ...
                app.ThrottleField.Value);
        end

        function onBrakeChanging(app, event)
            %ONBRAKECHANGING Coalesce rapid brake motion.
            app.submitPedal(app.BrakeCoalescer, 'pedals.brake', event.Value);
        end

        function onBrakeChanged(app, ~)
            %ONBRAKECHANGED Commit the final brake value.
            app.BrakeField.Value = app.BrakeSlider.Value;
            app.submitPedal(app.BrakeCoalescer, 'pedals.brake', ...
                app.BrakeSlider.Value);
        end

        function onBrakeFieldChanged(app, ~)
            %ONBRAKEFIELDCHANGED Commit a typed brake percentage.
            app.BrakeSlider.Value = app.BrakeField.Value;
            app.submitPedal(app.BrakeCoalescer, 'pedals.brake', ...
                app.BrakeField.Value);
        end

        function onSteeringChanging(app, event)
            %ONSTEERINGCHANGING Coalesce rapid virtual-car steering motion.
            app.submitSteering(event.Value);
        end

        function onSteeringChanged(app, ~)
            %ONSTEERINGCHANGED Commit the final steering-dial value.
            app.SteeringField.Value = app.SteeringDial.Value;
            app.submitSteering(app.SteeringDial.Value);
        end

        function onSteeringFieldChanged(app, ~)
            %ONSTEERINGFIELDCHANGED Commit a typed steering angle.
            app.SteeringDial.Value = app.SteeringField.Value;
            app.submitSteering(app.SteeringField.Value);
        end

        function submitSteering(app, angleDeg)
            %SUBMITSTEERING Offer a steering angle to the 30 ms coalescer.
            emission = app.SteeringCoalescer.submit(angleDeg, ...
                app.hostTimeS());
            if emission.hasValue
                app.commitWrite('steering.angle_deg', emission.value, true);
            end
            % Record what was REQUESTED and let REFRESHDRIVERINPUTS repaint
            % the combined readback. The label is not written here: doing so
            % would overwrite the applied/speed/observed fields with a
            % requested-only string until the next refresh, which is exactly
            % the requested-vs-applied conflation the separate fields exist
            % to prevent.
            app.RequestedSteeringDeg = angleDeg;
        end

        function text = formatSteeringValue(app, value, unit)
            %FORMATSTEERINGVALUE One steering readback field.
            %   Dashes for anything not a finite scalar, so a disconnected or
            %   stale sensor is never rendered as a real measurement.
            if isnumeric(value) && isscalar(value) && isfinite(value)
                text = sprintf('%.1f %s', value, unit);
            else
                text = app.Theme.text.noData;
            end
        end

        function submitPedal(app, coalescer, name, percent)
            %SUBMITPEDAL Offer a pedal percentage to its 30 ms coalescer.
            emission = coalescer.submit(percent, app.hostTimeS());
            if emission.hasValue
                app.commitWrite(name, emission.value / 100, true);
            end
            app.refreshDriverInputs();
        end

        function onSteeringDropoutChanged(app, ~)
            %ONSTEERINGDROPOUTCHANGED Stop or resume the LWS 0x2B0 frame.
            %   Writes the dictionary parameter the model's Tx Control gate
            %   already reads: with the flag set, that CAN Write genuinely
            %   does not transmit, so this is a real bus dropout rather than
            %   a display effect.
            app.commitWrite('steering.dropout', ...
                app.SteeringDropoutCheckBox.Value, true);
            app.refreshAll();
        end

        function onSteeringStaleChanged(app, ~)
            %ONSTEERINGSTALECHANGED Keep transmitting the last LWS payload.
            app.commitWrite('steering.stale', ...
                app.SteeringStaleCheckBox.Value, true);
            app.refreshAll();
        end

        function onSteeringMalformedChanged(app, ~)
            %ONSTEERINGMALFORMEDCHANGED Transmit 0x2B0 with DLC 4, not 5.
            app.commitWrite('steering.malformed', ...
                app.SteeringMalformedCheckBox.Value, true);
            app.refreshAll();
        end

        function onSteeringInvalidStatusChanged(app, ~)
            %ONSTEERINGINVALIDSTATUSCHANGED Emit illegal status byte 0x02.
            app.commitWrite('steering.invalid_status', ...
                app.SteeringInvalidStatusCheckBox.Value, true);
            app.refreshAll();
        end

        function onSteeringAngleSentinelChanged(app, ~)
            %ONSTEERINGANGLESENTINELCHANGED Force documented 0x7FFF.
            app.commitWrite('steering.angle_sentinel', ...
                app.SteeringAngleSentinelCheckBox.Value, true);
            app.refreshAll();
        end

        function onSteeringSpeedSentinelChanged(app, ~)
            %ONSTEERINGSPEEDSENTINELCHANGED Force documented 0xFF.
            app.commitWrite('steering.speed_sentinel', ...
                app.SteeringSpeedSentinelCheckBox.Value, true);
            app.refreshAll();
        end

        function onImuDropoutChanged(app, ~)
            %ONIMUDROPOUTCHANGED Stop or resume all three MTi frames.
            %   One flag gates 0x034, 0x032 and 0x076 together, matching
            %   SYNCHRONIZEDSENSORPAYLOADS. The LWS is unaffected: one
            %   sensor's dropout must never stop the other's frames.
            app.commitWrite('imu.dropout', ...
                app.ImuDropoutCheckBox.Value, true);
            app.refreshAll();
        end

        function onImuStaleChanged(app, ~)
            %ONIMUSTALECHANGED Keep transmitting all three cached MTi frames.
            app.commitWrite('imu.stale', app.ImuStaleCheckBox.Value, true);
            app.refreshAll();
        end

        function onImuMalformedChanged(app, ~)
            %ONIMUMALFORMEDCHANGED Transmit each MTi frame with DLC 5, not 6.
            app.commitWrite('imu.malformed', ...
                app.ImuMalformedCheckBox.Value, true);
            app.refreshAll();
        end

        function onLwsCalibrationPushed(app, ~)
            %ONLWSCALIBRATIONPUSHED Request the enforced target sequence.
            %   One token starts reset 0x05, a target-clock 100 ms hold and
            %   uncalibrated-frame result check, then a separate zero 0x03
            %   transmit and zero-frame result check. This callback never
            %   sends command bytes and cannot collapse the pair into one
            %   backend call.
            app.LwsCalibrationSequence = inverterhilgui.sequenceCommand( ...
                app.LwsCalibrationSequence);
            app.commitWrite('steering.calibration_sequence', ...
                app.LwsCalibrationSequence, true);
            app.refreshAll();
        end

        function onPlausibilityChanged(app, ~)
            %ONPLAUSIBILITYCHANGED Update the pedal-plausibility interlock.
            app.commitWrite('pedals.plausibility_override', ...
                app.PlausibilityCheckBox.Value, true);
            app.refreshAll();
        end

        function onExpertModeChanged(app, ~)
            %ONEXPERTMODECHANGED Update the expert-mode interlock.
            app.refreshAll();
        end

        function onCoolingSwitchChanged(app, ~)
            %ONCOOLINGSWITCHCHANGED Drive COOLING_SW_IN.
            app.commitWrite('digital.cooling_switch', ...
                app.CoolingSwitch.Value, true);
            app.refreshDriverInputs();
        end

        function onShutdownFeedbackChanged(app, ~)
            %ONSHUTDOWNFEEDBACKCHANGED Drive SD_FB_IN.
            app.commitWrite('digital.shutdown_feedback', ...
                app.ShutdownFeedbackSwitch.Value, true);
            app.refreshDriverInputs();
        end

        function onPrechargePushed(app, ~)
            %ONPRECHARGEPUSHED Increment the precharge sequence counter.
            app.PrechargeSequence = ...
                inverterhilgui.sequenceCommand(app.PrechargeSequence);
            app.commitWrite('digital.precharge_sequence', ...
                app.PrechargeSequence, true);
            app.refreshDriverInputs();
        end

        function onMainMomentaryPushed(app, ~)
            %ONMAINMOMENTARYPUSHED Increment the main-button sequence counter.
            app.MainButtonSequence = ...
                inverterhilgui.sequenceCommand(app.MainButtonSequence);
            app.MainButtonLastPressedS = app.hostTimeS();
            app.commitWrite('digital.main_button_sequence', ...
                app.MainButtonSequence, true);
            app.refreshDriverInputs();
        end

        function onFaultMaskChanged(app, event)
            %ONFAULTMASKCHANGED Inject a per-inverter fault mask.
            channel = event.Source.UserData;
            app.commitWrite(sprintf('inverter%d.fault_mask', channel), ...
                event.Source.Value, true);
            app.refreshLog();
        end

        function onLoadTorqueChanged(app, event)
            %ONLOADTORQUECHANGED Set a per-inverter load torque.
            channel = event.Source.UserData;
            app.commitWrite(sprintf('inverter%d.load_nm', channel), ...
                event.Source.Value, true);
            app.refreshLog();
        end

        function onConnectedChanged(app, event)
            %ONCONNECTEDCHANGED Set a per-inverter connected flag.
            channel = event.Source.UserData;
            app.commitWrite(sprintf('inverter%d.connected', channel), ...
                event.Source.Value, true);
            app.refreshLog();
        end

        function onDropControlChanged(app, ~)
            %ONDROPCONTROLCHANGED Set the CAN control-drop mask.
            app.commitWrite('can.drop_control_mask', ...
                app.DropControlField.Value, true);
            app.refreshLog();
        end

        function onDropStatusChanged(app, ~)
            %ONDROPSTATUSCHANGED Set the CAN status-drop mask.
            app.commitWrite('can.drop_status_mask', ...
                app.DropStatusField.Value, true);
            app.refreshLog();
        end

        function onExportLogPushed(app, ~)
            %ONEXPORTLOGPUSHED Export the append-only log without mutating it.
            [name, folder] = uiputfile('*.csv', 'Export session log', ...
                'inverter_hil_session_log.csv');
            if isequal(name, 0)
                return;
            end
            app.Log.export(fullfile(folder, name));
            app.refreshLog();
        end

        function onCloseRequest(app, ~)
            %ONCLOSEREQUEST Treat app unload as a safe-fallback condition.
            delete(app);
        end
    end

    methods (Access = public)

        function app = inverter_hil_app()
            %INVERTER_HIL_APP Construct and register the operator dashboard.
            createComponents(app);
            registerApp(app, app.UIFigure);
            runStartupFcn(app, @startupFcn);
            if nargout == 0
                clear app;
            end
        end

        function delete(app)
            %DELETE Stop the status timer and release the figure.
            if ~isempty(app.StatusTimer) && isvalid(app.StatusTimer)
                stop(app.StatusTimer);
                delete(app.StatusTimer);
            end
            if ~isempty(app.Session)
                app.Session.disconnect();
            end
            delete(app.UIFigure);
        end
    end
end
