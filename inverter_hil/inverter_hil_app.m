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
        MainButtonSwitch          matlab.ui.control.CheckBox
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
        CanRxTable                matlab.ui.control.Table
        CanTxTable                matlab.ui.control.Table
        CanDiagnosticsLabel       matlab.ui.control.Label
        InstrumentStatusLabel     matlab.ui.control.Label
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
        ThrottleCoalescer
        BrakeCoalescer
        SteeringCoalescer
        Heartbeat
        PrechargeSequence = uint32(0)
        MainButtonSequence = uint32(0)
        InverterExpanded = false(1, 4)
        InverterStatusGrids
        InverterDisclosureButtons
        % Resolved at startup from inverterhilgui.hostHeartbeatTimeout so the
        % host can never report healthy longer than the target-side fallback.
        HeartbeatTimeoutS
        VcuStateNames = {'LV_ON', 'PRECHARGING', 'ENABLE', 'BUZZING', 'RTD'}
        PedalChannelNames = {'AO01 THR1', 'AO02 THR2', 'AO03 BRK1', ...
            'AO04 BRK2'}
        DigitalNames = {'main_button', 'cooling_switch', ...
            'shutdown_feedback'}
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
                {90, 130, 100, 100, 80, 90, 160, '1x'});
            strip.BackgroundColor = theme.color.panel;
            app.StateStripLabels = gobjects(1, numel(app.VcuStateNames));
            for index = 1:numel(app.VcuStateNames)
                app.StateStripLabels(index) = app.makeLabel(strip, ...
                    app.VcuStateNames{index}, theme.font.heading, ...
                    theme.color.disabledText);
                app.StateStripLabels(index).HorizontalAlignment = 'center';
            end
            app.StateErrorLabel = app.makeLabel(strip, 'ERROR', ...
                theme.font.heading, theme.color.disabledText);
            app.StateErrorLabel.HorizontalAlignment = 'center';
            app.TimeInStateLabel = app.makeLabel(strip, ...
                'TIME IN STATE --', theme.font.body, ...
                theme.color.secondaryText);

            columns = app.makeGrid(outer, {'1x'}, {'1x', '1x'});
            app.createDriverInputs(columns);
            app.createElectricalMimic(columns);
        end

        function createDriverInputs(app, parent)
            %CREATEDRIVERINPUTS Pedal, digital, and momentary operator area.
            theme = app.Theme;
            panel = app.makePanel(parent, 'DRIVER INPUTS');
            grid = app.makeGrid(panel, ...
                {26, 26, 26, 26, 26, 90, 26, 26, 26, 26, '1x'}, ...
                {150, '1x', 110, 150});

            app.makeLabel(grid, 'THROTTLE %', theme.font.body, ...
                theme.color.primaryText);
            app.ThrottleSlider = uislider(grid);
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
            app.ThrottleAppliedLabel = app.makeLabel(grid, ...
                'APPLIED --', theme.font.body, theme.color.secondaryText);

            app.makeLabel(grid, 'BRAKE %', theme.font.body, ...
                theme.color.primaryText);
            app.BrakeSlider = uislider(grid);
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
            app.BrakeAppliedLabel = app.makeLabel(grid, ...
                'APPLIED --', theme.font.body, theme.color.secondaryText);

            app.makeLabel(grid, 'STEERING ANGLE deg', theme.font.body, ...
                theme.color.primaryText);
            app.SteeringDial = uiknob(grid, 'continuous');
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
            app.SteeringAppliedLabel = app.makeLabel(grid, ...
                'APPLIED --', theme.font.body, theme.color.secondaryText);

            app.makeLabel(grid, 'APPLIED PEDAL V', theme.font.body, ...
                theme.color.primaryText);
            voltageGrid = app.makeGrid(grid, {'1x'}, {'1x', '1x', '1x', '1x'});
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
            app.PlausibilityCheckBox.Layout.Column = [1 4];
            app.ExpertModeCheckBox = app.makeCheckBox(grid, ...
                'INTERLOCK: expert mode (calibration, plant, faults)', ...
                @onExpertModeChanged);
            app.ExpertModeCheckBox.Layout.Column = [1 4];

            app.makeLabel(grid, 'DIGITAL STIMULI', theme.font.body, ...
                theme.color.primaryText);
            app.MainButtonSwitch = app.makeCheckBox(grid, 'MAIN_BTN_IN', ...
                @onMainButtonChanged);
            app.CoolingSwitch = app.makeCheckBox(grid, 'COOLING_SW_IN', ...
                @onCoolingSwitchChanged);
            app.ShutdownFeedbackSwitch = app.makeCheckBox(grid, ...
                'SD_FB_IN', @onShutdownFeedbackChanged);

            app.makeLabel(grid, 'APPLIED', theme.font.body, ...
                theme.color.primaryText);
            app.DigitalAppliedLabels = gobjects(1, 3);
            for index = 1:3
                app.DigitalAppliedLabels(index) = app.makeLabel(grid, ...
                    theme.text.noData, theme.font.small, ...
                    theme.color.secondaryText);
            end

            app.makeLabel(grid, 'MOMENTARY (uint32 seq)', theme.font.body, ...
                theme.color.primaryText);
            app.PrechargeButton = app.makeButton(grid, 'PRECHARGE', ...
                @onPrechargePushed);
            app.MainMomentaryButton = app.makeButton(grid, 'MAIN BUTTON', ...
                @onMainMomentaryPushed);
            app.MomentaryLabels = gobjects(1, 2);
            app.MomentaryLabels(1) = app.makeLabel(grid, ...
                'seq --', theme.font.small, theme.color.secondaryText);
            app.makeLabel(grid, '', theme.font.small, ...
                theme.color.secondaryText);
            app.MomentaryLabels(2) = app.makeLabel(grid, ...
                'seq --', theme.font.small, theme.color.secondaryText);
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
            outer = app.makeGrid(app.InvertersTab, {'1x', '1x'}, ...
                {'1x', '1x'});
            fieldCount = numel(app.InverterFieldNames);
            app.InverterTitleLabels = gobjects(1, 4);
            app.InverterCornerLabels = gobjects(1, 4);
            app.InverterFieldLabels = gobjects(4, fieldCount);
            app.InverterStatusGrids = [];
            app.InverterDisclosureButtons = [];
            for channel = 1:4
                panel = app.makePanel(outer, sprintf('INVERTER %d', channel));
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

        function onInverterDisclosurePushed(app, source, ~)
            %ONINVERTERDISCLOSUREPUSHED Toggle only the source inverter panel.
            channel = find(app.InverterDisclosureButtons == source, 1);
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
            outer = app.makeGrid(app.IoCanTab, {18, '1x', 30}, {'1x', '1x'});

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
                'VCU TX / HIL RX  0x186 0x196 0x1A6 0x1B6');
            rxPanel.Layout.Row = 2;
            rxPanel.Layout.Column = 1;
            rxGrid = app.makeGrid(rxPanel, {'1x'}, {'1x'});
            app.CanRxTable = app.makeCanTable(rxGrid);

            txPanel = app.makePanel(outer, ...
                ['HIL TX / VCU RX  0x383 0x385 0x393 0x395 0x3A3 0x3A5 ' ...
                '0x3B3 0x3B5 0x400']);
            txPanel.Layout.Row = 2;
            txPanel.Layout.Column = 2;
            txGrid = app.makeGrid(txPanel, {'1x'}, {'1x'});
            app.CanTxTable = app.makeCanTable(txGrid);

            app.CanDiagnosticsLabel = app.makeLabel(outer, ...
                app.canDiagnosticsText(inverterhilgui.blankTelemetry()), ...
                theme.font.small, theme.color.secondaryText);
            app.CanDiagnosticsLabel.Layout.Row = 3;
            app.CanDiagnosticsLabel.Layout.Column = [1 2];
            app.CanDiagnosticsLabel.BackgroundColor = theme.color.panel;
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
            try
                app.tickHeartbeat();
                app.pollCoalescers();
                app.refreshAll();
            catch err
                app.reportError('status_timer', err);
            end
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
            emission = app.ThrottleCoalescer.poll(app.hostTimeS());
            if emission.hasValue
                app.commitWrite('pedals.throttle', emission.value / 100, true);
            end
            emission = app.BrakeCoalescer.poll(app.hostTimeS());
            if emission.hasValue
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
                app.Telemetry.pedals.appliedV = live.pedalsAppliedV;
                % Fix 1: the IO183 Rail Monitor AI readback of the pedal
                % harness taps (5V_THROTTLE_1/2, 5V_BP_1/2), a genuine
                % hardware self-check measurement of the same lines AO01-04
                % command -- see TARGETSESSION.READLIVEIO. Shown alongside
                % the commanded throttle/brake percent (ThrottleField /
                % BrakeField, already live) in REFRESHELECTRICAL's rail
                % panel, honestly NaN when unread rather than fabricated.
                app.Telemetry.analogInV = live.analogInV;
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
                if live.rx.known
                    app.applyLiveRxFrames(live.rx);
                end
            else
                app.Telemetry.io.healthy = false;
                app.Telemetry.io.healthyKnown = false;
                for index = 1:numel(app.Telemetry.pins)
                    app.Telemetry.pins(index).state = [];
                end
                app.Telemetry.pedals.appliedV = nan(1, 4);
                app.Telemetry.analogInV = nan(1, 4);
                blankCan = inverterhilgui.blankTelemetry().can.diagnostics;
                app.Telemetry.can.diagnostics = blankCan;
            end
            app.Telemetry.pedals.throttleAppliedPercent = ...
                app.appliedPedalPercent(1, 'v1');
            app.Telemetry.pedals.brakeAppliedPercent = ...
                app.appliedPedalPercent(3, 'v3');
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
            %   TIMESTAMPSS empty makes the column read dashes, which is the
            %   honest statement that polling cannot measure this rate. A real
            %   rate needs frame-arrival instrumentation on the target.
            payloads = live.txPayloads;
            observations = app.Telemetry.can.tx;
            now = app.hostTimeS();
            for index = 1:numel(observations)
                if index > size(payloads, 1)
                    break;
                end
                bytes = payloads(index, :);
                value = sprintf('%02X ', bytes);
                previous = observations(index).value;
                observations(index).value = strtrim(value);
                observations(index).signal = ...
                    ['HIL-generated; bus ACK unverified | ' ...
                    app.txFrameSignalText(index, live)];
                if ~strcmp(previous, observations(index).value)
                    observations(index).lastChangeS = now;
                end
            end
            app.Telemetry.can.tx = observations;
        end

        function applyLiveRxFrames(app, rx)
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
            observations = app.Telemetry.can.rx;
            now = app.hostTimeS();
            for index = 1:numel(observations)
                if index > numel(rx.channels)
                    break;
                end
                channel = rx.channels(index);
                if isempty(channel.hasCommand) || ~channel.hasCommand
                    observations(index).signal = 'no frame received';
                    observations(index).value = '';
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
            end
            app.Telemetry.can.rx = observations;
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

        function text = txFrameSignalText(app, index, live)
            %#ok<INUSD>
            % TX bytes are model output. They are not decoded as inverter
            % state because no external acknowledgement or feedback is
            % implied by their presence in this table.
            text = 'HIL-generated output; ACK unverified';
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
                app.Telemetry.vcu.state, interlocks);
            app.applyEnable([app.ThrottleSlider app.ThrottleField ...
                app.BrakeSlider app.BrakeField], app.Policy.pedals);
            app.applyEnable([app.SteeringDial app.SteeringField], ...
                app.Policy.sensorStimulus);
            app.applyEnable([app.MainButtonSwitch app.CoolingSwitch ...
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
            %REFRESHSTATESTRIP Highlight the observed VCU state, if known.
            theme = app.Theme;
            current = app.Telemetry.vcu.state;
            for index = 1:numel(app.VcuStateNames)
                if strcmpi(current, app.VcuStateNames{index})
                    app.StateStripLabels(index).FontColor = ...
                        theme.color.healthy;
                    app.StateStripLabels(index).FontWeight = 'bold';
                else
                    app.StateStripLabels(index).FontColor = ...
                        theme.color.disabledText;
                    app.StateStripLabels(index).FontWeight = 'normal';
                end
            end
            if app.Telemetry.vcu.errorKnown && app.Telemetry.vcu.errorActive
                app.StateErrorLabel.FontColor = theme.color.fault;
                app.StateErrorLabel.FontWeight = 'bold';
            else
                app.StateErrorLabel.FontColor = theme.color.disabledText;
                app.StateErrorLabel.FontWeight = 'normal';
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
            app.ThrottleAppliedLabel.Text = sprintf('APPLIED %s', ...
                app.formatPercent(pedals.throttleAppliedPercent));
            app.BrakeAppliedLabel.Text = sprintf('APPLIED %s', ...
                app.formatPercent(pedals.brakeAppliedPercent));
            if isfield(app.Telemetry, 'steering') && ...
                    isfinite(app.Telemetry.steering.appliedAngleDeg)
                app.SteeringAppliedLabel.Text = sprintf('APPLIED %.1f deg', ...
                    app.Telemetry.steering.appliedAngleDeg);
            else
                app.SteeringAppliedLabel.Text = 'APPLIED --';
            end
            for index = 1:4
                measurement = inverterhilgui.formatMeasurement( ...
                    pedals.appliedV(index), NaN, 'V', false);
                app.PedalVoltageLabels(index).Text = sprintf('%s %s', ...
                    app.PedalChannelNames{index}, measurement.value);
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
            data = cell(numel(rows), 6);
            highlighted = false(1, numel(rows));
            for index = 1:numel(rows)
                data(index, :) = {rows(index).live, rows(index).id, ...
                    rows(index).name, rows(index).signal, ...
                    rows(index).value, rows(index).rate};
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
                writeText = sprintf('%d/9 OK', sum(diagnostics.writeSucceeded));
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
            if app.Session.describeState().isConnected
                app.recordLifecycle('disconnect', app.Session.disconnect());
            else
                app.recordLifecycle('connect', app.Session.connect());
            end
            app.refreshAll();
        end

        function onLoadPushed(app, ~)
            %ONLOADPUSHED Load the real-time application.
            app.recordLifecycle('load', app.Session.load('inverter_hil'));
            app.refreshAll();
        end

        function onStartPushed(app, ~)
            %ONSTARTPUSHED Start the real-time application.
            app.recordLifecycle('start', app.Session.start());
            app.refreshAll();
        end

        function onStopPushed(app, ~)
            %ONSTOPPUSHED Stop the application and fall back to safe outputs.
            app.recordLifecycle('stop', app.Session.stop());
            app.refreshAll();
        end

        function onResetPushed(app, ~)
            %ONRESETPUSHED Reset the target application.
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
            app.SteeringAppliedLabel.Text = sprintf('REQUESTED %.1f deg', ...
                angleDeg);
        end

        function submitPedal(app, coalescer, name, percent)
            %SUBMITPEDAL Offer a pedal percentage to its 30 ms coalescer.
            emission = coalescer.submit(percent, app.hostTimeS());
            if emission.hasValue
                app.commitWrite(name, emission.value / 100, true);
            end
            app.refreshDriverInputs();
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

        function onMainButtonChanged(app, ~)
            %ONMAINBUTTONCHANGED Drive MAIN_BTN_IN.
            app.commitWrite('digital.main_button', ...
                app.MainButtonSwitch.Value, true);
            app.refreshDriverInputs();
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
