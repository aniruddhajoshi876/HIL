classdef targetSession < handle
    %TARGETSESSION Seam wrapping the Simulink Real-Time target object.
    %
    %   s = INVERTERHILGUI.TARGETSESSION(targetName) uses the real Simulink
    %   Real-Time backend, which is only constructed when a target is actually
    %   addressed. s = INVERTERHILGUI.TARGETSESSION(targetName, backend)
    %   injects a backend so tests can substitute
    %   INVERTERHILGUI.FAKETARGETBACKEND. Plan assumption M4: the Simulink
    %   Real-Time target and instrument APIs cannot be exercised without
    %   hardware, so every target interaction goes through this seam.
    %
    %   Safety behavior (plan 7.2, 7.4):
    %     * CONNECT discovers the parameter contract and reads target values
    %       with GETPARAM. It NEVER pushes host defaults to the target.
    %     * WRITE validates and clamps through
    %       INVERTERHILGUI.VALIDATECOMMANDVALUE, writes with SETPARAM, reads
    %       the applied value back, and reports requested versus applied.
    %     * SETPARAM is never called with Force=true.

    properties (SetAccess = private)
        % Configured target name.
        TargetName = ''
        % Injected or lazily created backend.
        Backend = []
        % True when the backend was injected by a test.
        BackendInjected = false
        % Lifecycle state from INVERTERHILGUI.CONNECTIONSTATE.
        State = 'disconnected'
        % Resolved parameter contract, empty until CONNECT succeeds.
        Contract = []
        % Values read from the target on connect, keyed by logical name.
        TargetValues
        % Most recent failure reason.
        LastError = ''
    end

    methods
        function obj = targetSession(targetName, backend)
            %TARGETSESSION Construct a session, optionally with a fake backend.
            if nargin < 1 || isempty(targetName)
                targetName = 'TargetPC1';
            end
            if isstring(targetName) && isscalar(targetName)
                targetName = char(targetName);
            end
            if ~ischar(targetName) || isempty(targetName)
                error('inverterhilgui:InvalidTargetName', ...
                    'Target name must be a nonempty character vector.');
            end
            obj.TargetName = targetName;
            obj.TargetValues = containers.Map('KeyType', 'char', ...
                'ValueType', 'any');
            if nargin >= 2 && ~isempty(backend)
                obj.Backend = backend;
                obj.BackendInjected = true;
            end
        end

        function result = connect(obj)
            %CONNECT Connect, replace the target application, and synchronize.
            %   CONNECT stops whatever is running, loads the current
            %   INVERTER_HIL build (which contains inverter HIL and virtual
            %   VCU together), then reads the target contract and values. The
            %   separate Start button controls when the loaded application
            %   begins driving I/O.
            %
            %   The hardware boundary is now live, so starting the application
            %   does drive the IO183 outputs and transmits the Ephorus status
            %   frames on CAN. It starts in the safe state the dictionary
            %   ships: pedal calibration is NaN so both analog pedal pairs
            %   hold 0 V, every digital stimulus is false, and the precharge
            %   counter is 0 so no pulse is generated. Physical levels change
            %   only when the operator moves a control.
            result = struct('success', false, 'state', obj.State, ...
                'reason', '', 'contract', []);
            obj.applyEvent('connect');
            try
                obj.ensureBackend();
                obj.Backend.connect();
                obj.applyEvent('connectSucceeded');
                obj.ensureApplicationRunning();
                obj.Contract = inverterhilgui.discoverContract( ...
                    obj.Backend.availableParameters());
                obj.readAllTargetValues();
                obj.syncStateFromBackend();
                result.success = true;
                result.reason = 'connected';
                result.contract = obj.Contract;
            catch err
                % A failed connect or a version-mismatched application must
                % never leave the session looking connected, so drop the
                % target and the partially resolved contract.
                obj.LastError = err.message;
                obj.Contract = [];
                obj.TargetValues = containers.Map('KeyType', 'char', ...
                    'ValueType', 'any');
                try
                    if ~isempty(obj.Backend)
                        obj.Backend.disconnect();
                    end
                catch
                    % The backend may already be gone; nothing to release.
                end
                obj.applyEvent('disconnect');
                result.reason = err.message;
            end
            result.state = obj.State;
        end

        function result = disconnect(obj)
            %DISCONNECT Drop the target and clear the resolved contract.
            result = struct('success', true, 'state', '', 'reason', '');
            try
                if ~isempty(obj.Backend)
                    obj.Backend.removeInstruments();
                    obj.Backend.disconnect();
                end
            catch err
                obj.LastError = err.message;
                result.success = false;
                result.reason = err.message;
            end
            obj.Contract = [];
            obj.TargetValues = containers.Map('KeyType', 'char', ...
                'ValueType', 'any');
            obj.applyEvent('disconnect');
            result.state = obj.State;
        end

        function result = load(obj, applicationName)
            %LOAD Load a real-time application onto the target.
            if nargin < 2
                applicationName = '';
            end
            result = obj.lifecycleCall(@() obj.Backend.load(applicationName), ...
                'load', 'loadSucceeded');
        end

        function result = start(obj)
            %START Start the loaded real-time application.
            result = obj.lifecycleCall(@() obj.Backend.start(), ...
                'start', 'startSucceeded');
        end

        function result = stop(obj)
            %STOP Stop the running real-time application.
            result = obj.lifecycleCall(@() obj.Backend.stop(), ...
                'stop', 'stopSucceeded');
        end

        function result = reset(obj)
            %RESET Reset the target application.
            result = obj.lifecycleCall(@() obj.Backend.reset(), ...
                'reset', 'reset');
        end

        function result = write(obj, name, value)
            %WRITE Validate, clamp, write, and read back one logical command.
            result = struct( ...
                'name', name, ...
                'path', '', ...
                'requested', value, ...
                'applied', [], ...
                'success', false, ...
                'clamped', false, ...
                'mismatch', false, ...
                'reason', 'not_connected');
            if isempty(obj.Contract)
                result.reason = 'contract_unresolved';
                return;
            end
            validation = inverterhilgui.validateCommandValue( ...
                obj.Contract, name, value);
            if ~validation.accepted
                result.reason = validation.reason;
                return;
            end
            entry = inverterhilgui.contractEntry(obj.Contract, name);
            result.path = entry.path;
            result.requested = validation.value;
            result.clamped = validation.clamped;
            try
                obj.Backend.setparam(entry.path, validation.value);
                applied = obj.Backend.getparam(entry.path);
            catch err
                obj.LastError = err.message;
                result.reason = 'write_failed';
                return;
            end
            result.applied = applied;
            obj.TargetValues(name) = applied;
            result.success = true;
            result.mismatch = ~valuesMatch(validation.value, applied);
            if result.mismatch
                result.reason = 'mismatch';
            elseif result.clamped
                result.reason = 'clamped';
            else
                result.reason = 'applied';
            end
        end

        function [value, known] = readCached(obj, name)
            %READCACHED Value read from the target, without re-reading it.
            value = [];
            known = false;
            if isKey(obj.TargetValues, name)
                value = obj.TargetValues(name);
                known = true;
            end
        end

        function value = executionTimeS(obj)
            %EXECUTIONTIMES Elapsed target execution time, NaN when unknown.
            value = NaN;
            try
                if ~isempty(obj.Backend) && obj.Backend.isConnected()
                    value = double(obj.Backend.executionTimeS());
                end
            catch err
                obj.LastError = err.message;
            end
        end

        function value = describeState(obj)
            %DESCRIBESTATE Lifecycle description including allowed actions.
            value = inverterhilgui.connectionState(obj.State);
        end

        function success = addInstrument(obj, instrument)
            %ADDINSTRUMENT Register a Simulink Real-Time instrument.
            success = false;
            try
                obj.Backend.addInstrument(instrument);
                success = true;
            catch err
                obj.LastError = err.message;
            end
        end

        function snapshot = readLiveIo(obj)
            %READLIVEIO Read the small set of genuinely live signals this
            %   session can read today: the five IO183 VCU-monitor digital
            %   inputs, the four commanded pedal output voltages, and CAN
            %   health (bus-off / bus-warning) from IO614 CAN Diagnostics.
            %
            %   Block paths are hardcoded to INVERTER_HIL's Hardware I O
            %   boundary, the same way ENSUREAPPLICATIONRUNNING hardcodes the
            %   application name -- this session is specific to that model.
            %
            %   io.healthy = ~busOff && ~busWarning. This is a narrower
            %   definition than "everything is fine": it says nothing about
            %   IO183 analog health, CAN write success, or the still-missing
            %   part 28 observability contract. It fails closed (KNOWN=false,
            %   HEALTHY=false) on any read error rather than throw, because a
            %   snapshot miss must never look like "no target" to the caller.
            %
            %   GUI pin order (VC_SD_OUT, MAIN_EN_OUT, PRECH_EN_OUT,
            %   INV_CTRL_EN, INV_CTRL_DIS) is NOT the same order as the IO183
            %   Digital Input block's channel vector [9 10 11 12 13]
            %   (..., INV_CTRL_DIS=DIO12, INV_CTRL_EN=DIO13) -- see
            %   PINOUTS.MD section 4.3. The mapping below corrects that
            %   transposition explicitly rather than copying by index.
            snapshot = struct('known', false, 'pins', [], ...
                'pedalsAppliedV', nan(1, 4), 'analogInV', nan(1, 4), 'io', ...
                struct('healthy', false, 'healthyKnown', false), ...
                'can', blankLiveCan(), ...
                'inverter', blankLiveInverters(), ...
                'inverterKnown', false, ...
                'systemStatus', blankLiveSystemStatus(), ...
                'rx', blankLiveRx(), ...
                'txPayloads', zeros(9, 8, 'uint8'), ...
                'txPayloadsKnown', false, ...
                'txMessageCount', NaN, ...
                'sensorTxCounts', nan(1, 5), ...
                'sensorAgesS', nan(1, 5), ...
                'lwsCalibrationState', NaN, ...
                'canPedals', [NaN NaN], 'canPedalsKnown', false, ...
                'canPedalsDriving', false);
            % Sensor blocks start from the same honest no-data snapshot the
            % dashboard uses, so an unread sensor is dashes here too rather
            % than a zero that looks like a real measurement.
            blank = inverterhilgui.blankTelemetry();
            [~, sensorDlcInit] = sensorTxIds();
            snapshot.steering = blank.steering;
            snapshot.imu = blank.imu;
            snapshot.sensorPayloads = ...
                zeros(numel(sensorDlcInit), 8, 'uint8');
            snapshot.sensorPayloadLengths = double(sensorDlcInit);
            snapshot.sensorPayloadsKnown = false;
            if isempty(obj.Backend) || ~obj.Backend.isConnected()
                return;
            end
            hw = 'inverter_hil/Hardware I O - PRE-FLIGHT DISABLED';
            diBlock = [hw '/IO183 DIO09-DIO13 VCU Monitor'];
            diagBlock = [hw '/IO614 CAN Diagnostics'];
            try
                di = nan(1, 5);
                for port = 1:5
                    di(port) = double(obj.Backend.getsignal(diBlock, port));
                end
                % di(4) = DIO12 = INV_CTRL_DIS, di(5) = DIO13 = INV_CTRL_EN.
                snapshot.pins = logical([di(1) di(2) di(3) di(5) di(4)]);

                % The pedal-calibration signal is the model's command into
                % the IO183 analog-output block, not a measured pin voltage.
                % There is no loopback of the AO command signal itself in
                % this model, so report it as unavailable instead of
                % presenting the commanded value as physical output
                % telemetry. (A separate, genuine hardware loopback of the
                % physical pedal lines DOES exist -- see the IO183 Rail
                % Monitor AI read below, which populates ANALOGINV, not this
                % field.)
                snapshot.pedalsAppliedV = nan(1, 4);

                % IO614 CAN Status port order, from the block's own mask:
                % 1 Bus Load, 2 Bus-Off, 3 Recovery Count,
                % 4 Transmit Buffer Overrun, 5 Receive Buffer Overrun,
                % 6 Bus-Warning Limit.
                busLoad = double(obj.Backend.getsignal(diagBlock, 1));
                busOff = logical(obj.Backend.getsignal(diagBlock, 2));
                recoveryCount = double(obj.Backend.getsignal(diagBlock, 3));
                txOverrun = logical(obj.Backend.getsignal(diagBlock, 4));
                rxOverrun = logical(obj.Backend.getsignal(diagBlock, 5));
                busWarning = logical(obj.Backend.getsignal(diagBlock, 6));

                % Each CAN Write block exposes one status output, enabled at
                % build time via enableStatusPort -- whose mask prompt is
                % "Show Overrun Output". The port is therefore an OVERRUN
                % flag: TRUE means the tx buffer overran, i.e. the frame did
                % NOT get away cleanly. It is inverted here so the field
                % reads as "no overrun" rather than being reported backwards.
                writeIds = {'383', '385', '393', '395', '3A3', '3A5', ...
                    '3B3', '3B5', '400'};
                % The four sensor frames and LWS config frame are transmitted
                % by CAN Write blocks too --
                % so an overrunning sensor write reported as healthy. Their
                % blocks are named "CAN Write Sensor 0x..." (see
                % BUILD_INVERTER_HIL_MODEL), hence the separate loop rather
                % than one combined ID list.
                sensorIds = sensorTxIds();
                writeNoOverrun = false(1, numel(writeIds) + numel(sensorIds));
                for k = 1:numel(writeIds)
                    writeBlock = sprintf('%s/CAN Write 0x%s', hw, ...
                        writeIds{k});
                    writeNoOverrun(k) = ...
                        ~logical(obj.Backend.getsignal(writeBlock, 1));
                end
                for k = 1:numel(sensorIds)
                    writeBlock = sprintf('%s/CAN Write Sensor 0x%03X', hw, ...
                        double(sensorIds(k)));
                    writeNoOverrun(numel(writeIds) + k) = ...
                        ~logical(obj.Backend.getsignal(writeBlock, 1));
                end

                snapshot.can.diagnostics.busLoadPercent = busLoad;
                snapshot.can.diagnostics.busOff = busOff;
                snapshot.can.diagnostics.recoveryCount = recoveryCount;
                snapshot.can.diagnostics.transmitOverrun = txOverrun;
                snapshot.can.diagnostics.receiveOverrun = rxOverrun;
                snapshot.can.diagnostics.errorWarning = busWarning;
                snapshot.can.diagnostics.writeSucceeded = writeNoOverrun;
                snapshot.can.diagnostics.writeKnown = true;
                snapshot.can.known = true;

                snapshot.io.healthy = ~busOff && ~busWarning;
                snapshot.io.healthyKnown = true;
                snapshot.known = true;
            catch err
                obj.LastError = err.message;
                return;
            end

            % IO183 Rail Monitor AI01-AI04 readback (Fix 1). Despite the
            % block's "Rail Monitor" name this is NOT a DC electrical rail
            % measurement -- per PINOUTS.MD S4.2 it is a genuine hardware
            % self-check loopback of the four pedal harness taps
            % (5V_THROTTLE_1/2, 5V_BP_1/2), the same physical lines
            % IO183 AO01-AO04 command. Exposed on port 3 of the same
            % subsystem as the payload/observation ports read below.
            %
            % Deliberately its own try, and deliberately does not RETURN on
            % failure or size mismatch: this port only exists in
            % applications built after Fix 1, so an older build on the
            % target must leave the pin/CAN data above intact and simply
            % report the measured pedal voltages unknown, without blocking
            % the payload/observation reads that follow.
            try
                analogRaw = obj.Backend.getsignal( ...
                    'inverter_hil/Ephorus System Status', 3);
                if numel(analogRaw) == 4
                    snapshot.analogInV = reshape(double(analogRaw), 1, 4);
                end
            catch err
                obj.LastError = err.message;
                % ANALOGINV stays at its NaN default.
            end

            % The status cycle below is generated by this HIL model and sent
            % toward the external CAN bus. It is not inverter feedback. Keep
            % the raw model-generated payloads for the TX table, but leave
            % measured inverter/system status unknown until a real feedback
            % path exists.
            %
            % Deliberately a separate try: the payload signal is the newest
            % and least certain of these reads, so a failure here must leave
            % the pin, pedal and CAN data above intact rather than blanking a
            % whole snapshot that was otherwise good. INVERTERKNOWN stays
            % false in that case and the panels honestly show dashes.
            try
                payloads = obj.Backend.getsignal( ...
                    'inverter_hil/Ephorus System Status', 1);
                if ~isequal(size(payloads), [9 8])
                    return;
                end
                payloads = uint8(payloads);
                % PROTOCOL.STATUSCYCLEIDS order: 3X3/3X5 interleaved per
                % channel (383,385, 393,395, 3A3,3A5, 3B3,3B5) then 0x400.
                for channel = 1:4
                    threeX3 = decodeStatus3X3( ...
                        payloads(2 * channel - 1, :));
                    threeX5 = decodeStatus3X5( ...
                        payloads(2 * channel, :));
                    snapshot.inverter(channel).state = threeX3.state;
                    snapshot.inverter(channel).ready = threeX3.ready;
                    snapshot.inverter(channel).derating = threeX3.derating;
                    snapshot.inverter(channel).torqueActualNm = ...
                        threeX3.actualTorqueNm;
                    snapshot.inverter(channel).torqueCommandNm = ...
                        threeX3.torqueSetpointNm;
                    snapshot.inverter(channel).motorTemperatureC = ...
                        threeX3.motorTemperatureC;
                    snapshot.inverter(channel).switchTemperatureC = ...
                        threeX3.switchTemperatureC;
                    snapshot.inverter(channel).idSetpointA = ...
                        threeX5.idSetpointA;
                    snapshot.inverter(channel).idActualA = threeX5.idActualA;
                    snapshot.inverter(channel).iqSetpointA = ...
                        threeX5.iqSetpointA;
                    snapshot.inverter(channel).iqActualA = threeX5.iqActualA;
                    snapshot.inverter(channel).speedRpm = threeX5.speedRpm;
                end
                % Row 9 is the 0x400 general status, decoded from the same
                % transmitted bytes as the eight per-channel rows above.
                snapshot.systemStatus = ...
                    decodeSystemStatus(payloads(9, :));
                % Raw bytes retained so the TX table can show exactly what the
                % model generated. These bytes alone are not proof of
                % successful transmission; acknowledgement is reported
                % separately and for real by INVERTERHILGUI.CANACKSTATUS,
                % from the CAN controller's own bus-off/error-warning
                % counters read below.
                snapshot.txPayloads = payloads;
                snapshot.txPayloadsKnown = true;
                % Port 5 of the same subsystem is the shared vehicle state
                % INVERTERHIL.STEPVEHICLESTATE advances -- the exact vector
                % the MTi encoders sample, laid out
                % [ax ay az | wx wy wz | vx vy vz]. Reading it here is what
                % makes the IMU panel show measured values instead of
                % permanent dashes. Guarded separately so a failure leaves
                % the inverter and CAN data above intact.
                try
                    vehicleState = obj.Backend.getsignal( ...
                        'inverter_hil/Ephorus System Status', 5);
                    vehicleState = double(vehicleState(:))';
                    if numel(vehicleState) == 9 && all(isfinite(vehicleState))
                        snapshot.imu.accelerationMps2 = vehicleState(1:3);
                        snapshot.imu.rateOfTurnRadPerS = vehicleState(4:6);
                        snapshot.imu.velocityMps = vehicleState(7:9);
                        % VALID states that this snapshot carries a genuine
                        % reading, not that the frame was acknowledged on the
                        % bus -- acknowledgement is CANACKSTATUS's job.
                        snapshot.imu.valid = true;
                    end
                catch
                    % Leave the blank IMU block: dashes, never zeros.
                end
                % Four encoded sensor payloads and the most recent LWS
                % config payload leave SYNCHRONIZED SENSOR PAYLOADS on
                % ports 1-5, in INVERTERHIL.SENSORTXIDS order. These are the
                % exact bytes handed to the CAN Pack /
                % CAN Write pairs, so the TX table shows what is genuinely
                % on the wire rather than a host-side re-encode.
                try
                    [~, sensorDlc] = sensorTxIds();
                    sensorDlc = double(sensorDlc);
                    % Ports 14-18 are the target-selected wire DLCs. These
                    % differ from the nominal contract only during malformed
                    % injection; reading them is what makes the GUI report
                    % the actual short frame rather than the nominal length.
                    for k = 1:numel(sensorDlc)
                        runtimeDlc = obj.Backend.getsignal( ...
                            [hw '/Synchronized Sensor Payloads'], 13 + k);
                        if isnumeric(runtimeDlc) && isscalar(runtimeDlc) && ...
                                isfinite(double(runtimeDlc)) && ...
                                runtimeDlc >= 0 && runtimeDlc <= 8
                            sensorDlc(k) = double(runtimeDlc);
                        end
                    end
                    rows = zeros(numel(sensorDlc), 8, 'uint8');
                    for k = 1:numel(sensorDlc)
                        raw = obj.Backend.getsignal( ...
                            [hw '/Synchronized Sensor Payloads'], k);
                        raw = uint8(raw(:))';
                        take = min(numel(raw), sensorDlc(k));
                        rows(k, 1:take) = raw(1:take);
                    end
                    snapshot.sensorPayloads = rows;
                    snapshot.sensorPayloadLengths = sensorDlc;
                    snapshot.sensorPayloadsKnown = true;
                    % Ports 11 and 12 are target-maintained counters and
                    % target-clock ages. They are never reconstructed from
                    % this host's poll cadence. Port 13 is the enforced LWS
                    % reset/wait/zero/result-check sequencer state.
                    counts = double(obj.Backend.getsignal( ...
                        [hw '/Synchronized Sensor Payloads'], 11));
                    ages = double(obj.Backend.getsignal( ...
                        [hw '/Synchronized Sensor Payloads'], 12));
                    if numel(counts) == numel(sensorDlc)
                        snapshot.sensorTxCounts = reshape(counts, 1, []);
                    end
                    if numel(ages) == numel(sensorDlc)
                        snapshot.sensorAgesS = reshape(ages, 1, []);
                        if all(isfinite(snapshot.sensorAgesS(1:3)))
                            snapshot.imu.ageS = max(snapshot.sensorAgesS(1:3));
                        end
                        if isfinite(snapshot.sensorAgesS(4))
                            snapshot.steering.ageS = snapshot.sensorAgesS(4);
                        end
                    end
                    calibrationState = obj.Backend.getsignal( ...
                        [hw '/Synchronized Sensor Payloads'], 13);
                    if isnumeric(calibrationState) && ...
                            isscalar(calibrationState) && ...
                            isfinite(double(calibrationState))
                        snapshot.lwsCalibrationState = ...
                            double(calibrationState);
                        snapshot.steering.calibrationState = ...
                            double(calibrationState);
                    end
                    % Decode the LWS frame we actually transmitted, using
                    % the simulator's own decoder. The layout is
                    % deliberately NOT restated here: a second copy in the
                    % GUI is exactly how the byte-3/byte-4 status bug went
                    % unnoticed once already.
                    measurement = decodeTransmittedLws( ...
                        rows(4, 1:sensorDlc(4)));
                    if ~isempty(measurement)
                        snapshot.steering.observedAngleDeg = ...
                            measurement.angleDeg;
                        snapshot.steering.speedDegPerS = ...
                            measurement.speedDegPerS;
                        snapshot.steering.valid = measurement.valid;
                        snapshot.steering.known = true;
                    end
                catch
                    % Leave the blank steering/sensor block.
                end
                % APPLIED is the steering angle the TARGET actually holds,
                % read back with GETPARAM. It is a different quantity from
                % REQUESTED (the app's local dial value, which has not
                % necessarily been emitted by the 30 ms coalescer yet, and
                % may have been clamped or rejected on write) and from
                % OBSERVED (the LWS frame value above, quantised to the
                % encoder's 0.1 deg and absent entirely during a dropout).
                % SYNCHRONIZEDSENSORPAYLOADS applies no rate limit, so
                % APPLIED is what drove the shared vehicle state this tick.
                try
                    applied = obj.Backend.getparam( ...
                        'hil_cmd_steering_angle_deg');
                    if isnumeric(applied) && isscalar(applied) && ...
                            isfinite(double(applied))
                        snapshot.steering.appliedAngleDeg = double(applied);
                    end
                catch
                    % Unknown stays NaN; the panel shows a dash.
                end
                faultFields = { ...
                    'steering', 'dropout'; ...
                    'steering', 'stale'; ...
                    'steering', 'malformed'; ...
                    'steering', 'invalid_status'; ...
                    'steering', 'angle_sentinel'; ...
                    'steering', 'speed_sentinel'; ...
                    'imu', 'dropout'; ...
                    'imu', 'stale'; ...
                    'imu', 'malformed'};
                for faultIndex = 1:size(faultFields, 1)
                    sensorName = faultFields{faultIndex, 1};
                    parameterName = faultFields{faultIndex, 2};
                    try
                        flag = obj.Backend.getparam( ...
                            sprintf('hil_cmd_%s_%s', sensorName, parameterName));
                        if (islogical(flag) || isnumeric(flag)) && ...
                                isscalar(flag) && isfinite(double(flag))
                            telemetryName = strrep(parameterName, ...
                                '_status', 'Status');
                            telemetryName = strrep(telemetryName, ...
                                '_sentinel', 'Sentinel');
                            snapshot.(sensorName).(telemetryName) = logical(flag);
                        end
                    catch
                        % Leave false: an unread flag must not read as an
                        % injected dropout the operator never commanded.
                    end
                end
                % The decoded values above are this rig's own generated
                % inverter-side output (STEPMODEL/STEPPLANT), not an
                % independently confirmed measurement -- there is no
                % cross-channel CAN receipt signal wired up to verify it
                % (see INVERTER_HIL_APP's CREATEINVERTERSTAB, which carries a
                % permanent disclosure label for exactly this reason).
                % INVERTERKNOWN is true because there genuinely is decoded
                % data to show; the "genuinely received" branch below still
                % overwrites individual channels with independently verified
                % values if a real CAN round-trip observation is ever wired
                % up, so this is a floor, not a ceiling, on data quality.
                snapshot.inverterKnown = true;
                % SNAPSHOT.SYSTEMSTATUS is NOT blanked here (an earlier
                % version of this fix did, matching the "not independently
                % confirmed" caveat above). dcLink12V/34V/switchingFrequency
                % are not an inverter feedback claim at all -- they are this
                % rig's own GUI-commanded values (HIL_CMD_DC_LINK12_V/34_V),
                % packed into the same frame purely to be broadcast, with no
                % ambiguity about their truthfulness the way channel state/
                % torque/ready genuinely have. Blanking them meant the NEXT
                % TRANSITION and TWIN DC-LINK panels could never show
                % anything but dashes on a bench with no second node to
                % produce a "genuinely received" 0x400 frame (the FRESH(9)
                % branch below). The "genuinely received" branch still
                % overwrites this with independently verified data first if
                % that path is ever wired up, so this remains a floor, not a
                % ceiling.
            catch err
                obj.LastError = err.message;
                % INVERTERKNOWN stays false: a partial or failed read must present as
                % "no live data", never as a partially-populated snapshot.
            end

            % Port 4: a genuine, target-measured count of status-cycle
            % payloads emitted (see BUILD_INVERTER_HIL_MODEL's
            % STATUSCYCLESCRIPT). Its own try, matching port 3 above: this
            % port only exists in applications built after this fix, so an
            % older running application must leave everything read above
            % intact and simply report the count unknown (NaN), not blank a
            % good snapshot.
            try
                txCount = obj.Backend.getsignal( ...
                    'inverter_hil/Ephorus System Status', 4);
                snapshot.txMessageCount = double(txCount);
            catch err
                obj.LastError = err.message;
                % TXMESSAGECOUNT stays NaN; the GUI shows dashes.
            end

            % Port 6 is the target's retained CarMakerPedalDemand state:
            % percent throttle, percent brake, and the exact atomic ownership
            % flag used by the model-side selectors. A failed optional lookup
            % remains unknown; it is never interpreted as a healthy dead link.
            try
                canPedals = obj.Backend.getsignal( ...
                    'inverter_hil/Ephorus System Status', 6);
                if isnumeric(canPedals) && numel(canPedals) == 3 && ...
                        all(isfinite(double(canPedals(1:2)))) && ...
                        (double(canPedals(3)) == 0 || double(canPedals(3)) == 1)
                    snapshot.canPedals = reshape(double(canPedals(1:2)), 1, 2);
                    snapshot.canPedalsDriving = logical(canPedals(3));
                    snapshot.canPedalsKnown = true;
                end
            catch err
                obj.LastError = err.message;
            end

            % What the target actually RECEIVED from the VCU, published on
            % output port 2 of the same subsystem (see
            % INVERTERHIL.RXOBSERVATION for the column layout).
            %
            % Separate try again, for the same reason as the block above: this
            % port only exists in applications built after the RX observation
            % was added, so an older application still running on the target
            % makes this read fail. That must leave everything above intact
            % and simply report RX as unknown, not blank a good snapshot.
            try
                observation = obj.Backend.getsignal( ...
                    'inverter_hil/Ephorus System Status', 2);
                if ~isequal(size(observation), [13 14])
                    return;
                end
                observation = double(observation);
                controlObservation = observation(1:4, :);
                for channel = 1:4
                    hasCommand = controlObservation(channel, 9) ~= 0;
                    snapshot.rx.channels(channel).hasCommand = hasCommand;
                    snapshot.rx.channels(channel).acceptedCount = ...
                        controlObservation(channel, 10);
                    snapshot.rx.channels(channel).outOfDomain = ...
                        controlObservation(channel, 12) ~= 0;
                    % PAYLOAD and AGEMS stay at their blank values unless a
                    % frame was genuinely accepted. Copying the zero row for a
                    % never-received channel would render as eight 00 bytes,
                    % which is a real frame a VCU can send -- the table would
                    % then show fabricated traffic on a silent channel.
                    if ~hasCommand
                        continue;
                    end
                    snapshot.rx.channels(channel).payload = ...
                        uint8(controlObservation(channel, 1:8));
                    snapshot.rx.channels(channel).ageMs = ...
                        controlObservation(channel, 11);
                end
                snapshot.rx.rejectedCount = controlObservation(1, 13);
                snapshot.rx.lastRejectCode = controlObservation(1, 14);
                snapshot.rx.known = true;
            catch err
                obj.LastError = err.message;
                % RX.KNOWN stays false; the table shows dashes.
            end

            % Rows 5:13 of the same physical RX observation are inverter
            % status IDs 0x383..0x400. Decode only fresh, genuinely received
            % pairs; no TX payload is used as a fallback.
            try
                statusRows = observation(5:13, 1:11);
                fresh = statusRows(:, 9) ~= 0 & statusRows(:, 11) <= 100;
                for channel = 1:4
                    row3X3 = 2 * channel - 1;
                    row3X5 = 2 * channel;
                    if ~(fresh(row3X3) && fresh(row3X5))
                        continue;
                    end
                    threeX3 = decodeStatus3X3( ...
                        uint8(statusRows(row3X3, 1:8)));
                    threeX5 = decodeStatus3X5( ...
                        uint8(statusRows(row3X5, 1:8)));
                    snapshot.inverter(channel).state = threeX3.state;
                    snapshot.inverter(channel).ready = threeX3.ready;
                    snapshot.inverter(channel).derating = threeX3.derating;
                    snapshot.inverter(channel).torqueActualNm = ...
                        threeX3.actualTorqueNm;
                    snapshot.inverter(channel).torqueCommandNm = ...
                        threeX3.torqueSetpointNm;
                    snapshot.inverter(channel).motorTemperatureC = ...
                        threeX3.motorTemperatureC;
                    snapshot.inverter(channel).switchTemperatureC = ...
                        threeX3.switchTemperatureC;
                    snapshot.inverter(channel).idSetpointA = threeX5.idSetpointA;
                    snapshot.inverter(channel).idActualA = threeX5.idActualA;
                    snapshot.inverter(channel).iqSetpointA = threeX5.iqSetpointA;
                    snapshot.inverter(channel).iqActualA = threeX5.iqActualA;
                    snapshot.inverter(channel).speedRpm = threeX5.speedRpm;
                    snapshot.inverterKnown = true;
                end
                if fresh(9)
                    snapshot.systemStatus = decodeSystemStatus( ...
                        uint8(statusRows(9, 1:8)));
                end
            catch err
                obj.LastError = err.message;
                % Feedback remains unknown if status rows are unavailable.
            end
        end
    end

    methods (Access = private)
        function ensureBackend(obj)
            if ~isempty(obj.Backend)
                return;
            end
            if exist('slrealtime.Target', 'class') ~= 8
                error('inverterhilgui:RealTimeToolboxMissing', ...
                    ['Simulink Real-Time is required to address target ' ...
                    '%s and no backend was injected.'], obj.TargetName);
            end
            obj.Backend = inverterhilgui.slrealtimeBackend(obj.TargetName);
        end

        function result = lifecycleCall(obj, action, requestEvent, doneEvent)
            result = struct('success', false, 'state', obj.State, ...
                'reason', '');
            if isempty(obj.Backend)
                result.reason = 'not_connected';
                return;
            end
            allowed = inverterhilgui.connectionState(obj.State).allowed;
            actionName = strrep(requestEvent, 'Succeeded', '');
            if isfield(allowed, actionName) && ~allowed.(actionName)
                result.reason = 'action_not_allowed';
                result.state = obj.State;
                return;
            end
            obj.applyEvent(requestEvent);
            try
                action();
                obj.applyEvent(doneEvent);
                result.success = true;
                result.reason = doneEvent;
            catch err
                obj.LastError = err.message;
                obj.applyEvent('fail');
                result.reason = err.message;
            end
            result.state = obj.State;
        end

        function applyEvent(obj, event)
            transition = inverterhilgui.connectionState(obj.State, event);
            obj.State = transition.state;
        end

        function ensureApplicationRunning(obj)
            %ENSUREAPPLICATIONRUNNING Stop only another app, then run ours.
            %   A running INVERTER_HIL is preserved. If another model owns
            %   the target, it is stopped before the inverter HIL
            %   application is loaded and started.
            state = obj.Backend.applicationState();
            if strcmp(state, 'running')
                current = obj.Backend.currentApplicationName();
                if ~strcmpi(current, 'inverter_hil')
                    obj.Backend.stop();
                    state = 'stopped';
                else
                    return;
                end
            end
            if ~strcmp(state, 'loaded')
                obj.Backend.load('inverter_hil');
            end
            obj.Backend.start();
        end

        function syncStateFromBackend(obj)
            try
                reported = obj.Backend.applicationState();
            catch err
                obj.LastError = err.message;
                return;
            end
            if any(strcmp(reported, {'connected', 'loaded', 'running', ...
                    'stopped'}))
                obj.State = reported;
            end
        end

        function readAllTargetValues(obj)
            % Plan 7.4: read target values before enabling controls and never
            % push host defaults on connect. This method only reads.
            obj.TargetValues = containers.Map('KeyType', 'char', ...
                'ValueType', 'any');
            for index = 1:numel(obj.Contract.entries)
                entry = obj.Contract.entries(index);
                try
                    obj.TargetValues(entry.name) = ...
                        obj.Backend.getparam(entry.path);
                catch err
                    obj.LastError = err.message;
                end
            end
        end
    end
end

function inverters = blankLiveInverters()
%BLANKLIVEINVERTERS Unknown per-inverter block, NaN/empty per BLANKTELEMETRY's
%   contract that an unread field is never a zero.
inverters = repmat(struct( ...
    'state', NaN, 'ready', [], 'derating', [], ...
    'torqueActualNm', NaN, 'torqueCommandNm', NaN, ...
    'motorTemperatureC', NaN, 'switchTemperatureC', NaN, ...
    'idSetpointA', NaN, 'idActualA', NaN, ...
    'iqSetpointA', NaN, 'iqActualA', NaN, 'speedRpm', NaN), 1, 4);
end

function rx = blankLiveRx()
%BLANKLIVERX The unknown received-control block.
%   PAYLOAD is empty, not zeros: an all-zero payload is a frame a VCU can
%   legitimately send, so it must never be how "nothing received" presents.
channel = struct( ...
    'payload', zeros(1, 0, 'uint8'), ...
    'hasCommand', [], ...
    'acceptedCount', NaN, ...
    'ageMs', NaN, ...
    'outOfDomain', []);
rx = struct('known', false, 'channels', repmat(channel, 1, 4), ...
    'rejectedCount', NaN, 'lastRejectCode', NaN);
end

function status = blankLiveSystemStatus()
%BLANKLIVESYSTEMSTATUS The unknown 0x400 block. NaN/empty rather than zero,
%   because a 0 V DC link is a meaningful reading and must never be how "not
%   read yet" presents.
status = struct( ...
    'dcLink12V', NaN, ...
    'dcLink34V', NaN, ...
    'switchingFrequencyKHz', NaN, ...
    'dcLink12AboveMinimum', [], ...
    'dcLink34AboveMinimum', [], ...
    'controlEnable', [], ...
    'controlDisable', []);
end

function measurement = decodeTransmittedLws(payload)
%DECODETRANSMITTEDLWS Decode a transmitted LWS payload, or return empty.
%   Calls the simulator's own DECODELWSFRAME rather than restating the
%   Bosch layout here. That folder is a sibling of INVERTER_HIL and is put
%   on the path by INVERTER_HIL_SETUP -- but the app does not call that
%   function, so the decoder may genuinely be unavailable at runtime. It is
%   located relative to this file and added once rather than assumed,
%   because falling back to a local copy of the byte layout is precisely
%   how the status byte ended up written to the wrong byte once already.
%
%   Returns [] when the decoder cannot be reached or the frame is
%   unreadable, so every caller renders dashes instead of a guess.

measurement = [];
if isempty(which('decodeLwsFrame'))
    here = fileparts(fileparts(mfilename('fullpath')));
    candidate = fullfile(here, 'steering-sensor');
    if isfolder(candidate)
        addpath(candidate);
    end
end
if isempty(which('decodeLwsFrame')) || isempty(which('lwsProtocol'))
    return;
end
try
    contract = lwsProtocol();
    measurement = decodeLwsFrame(struct( ...
        'id', contract.standardId, 'payload', uint8(payload)), contract);
catch
    measurement = [];
end
end

function can = blankLiveCan()
%BLANKLIVECAN The unknown live-CAN block, matching BLANKTELEMETRY's contract
%   that an unread field is NaN/empty with a KNOWN flag, never a zero.
can = struct('known', false, 'diagnostics', struct( ...
    'busLoadPercent', NaN, ...
    'busOff', [], ...
    'recoveryCount', NaN, ...
    'transmitOverrun', [], ...
    'receiveOverrun', [], ...
    'errorWarning', [], ...
    'writeSucceeded', false(1, 9 + numel(sensorTxIds())), ...
    'writeKnown', false));
end

function match = valuesMatch(requested, applied)
match = false;
if ~(isnumeric(applied) || islogical(applied)) || ~isscalar(applied)
    return;
end
requestedValue = double(requested);
appliedValue = double(applied);
if ~isfinite(requestedValue) || ~isfinite(appliedValue)
    return;
end
tolerance = max(1e-9, 1e-6 * abs(requestedValue));
match = abs(requestedValue - appliedValue) <= tolerance;
end
