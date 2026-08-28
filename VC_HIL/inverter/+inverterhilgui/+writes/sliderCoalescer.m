classdef sliderCoalescer < handle
    %SLIDERCOALESCER Coalesce rapid slider motion to the newest value.
    %
    %   Plan 7.2 requires rapid slider movement to be coalesced to the newest
    %   value at a 20-50 ms host update rate so the GUI stays responsive
    %   without flooding target traffic. Intermediate values are dropped; the
    %   newest value always replaces an older pending value, so emissions can
    %   never be reordered.
    %
    %   c = INVERTERHILGUI.SLIDERCOALESCER(0.030);
    %   out = c.submit(value, nowS);   % emits immediately when the rate allows
    %   out = c.poll(nowS);            % emits a pending value once due

    properties (SetAccess = private)
        % Minimum spacing between emissions, seconds, within 0.020-0.050.
        RateS = 0.030
        % True when a newer value is waiting for the rate window.
        HasPending = false
        % The newest value waiting to be emitted.
        PendingValue = []
        % Host time of the most recent emission, seconds.
        LastEmitS = -Inf
        % Number of values actually emitted.
        EmittedCount = 0
        % Number of intermediate values discarded without being emitted.
        DroppedCount = 0
    end

    methods
        function obj = sliderCoalescer(rateS)
            %SLIDERCOALESCER Construct a coalescer at a validated host rate.
            if nargin < 1 || isempty(rateS)
                rateS = 0.030;
            end
            if ~isnumeric(rateS) || ~isscalar(rateS) || ~isreal(rateS) || ...
                    ~isfinite(rateS) || rateS < 0.020 || rateS > 0.050
                error('inverterhilgui:InvalidCoalescerRate', ...
                    'Host update rate must be a scalar within 0.020-0.050 s.');
            end
            obj.RateS = double(rateS);
        end

        function out = submit(obj, value, nowS)
            %SUBMIT Offer a new value; emit it now or hold it as pending.
            out = emptyEmission();
            nowS = obj.checkTime(nowS);
            if ~(isnumeric(value) || islogical(value)) || ~isscalar(value) ...
                    || ~isreal(value) || ~isfinite(double(value))
                error('inverterhilgui:InvalidCoalescerValue', ...
                    'Coalesced values must be real finite numeric scalars.');
            end
            if obj.HasPending
                obj.DroppedCount = obj.DroppedCount + 1;
            end
            obj.PendingValue = value;
            obj.HasPending = true;
            out = obj.emitIfDue(nowS, out);
        end

        function out = poll(obj, nowS)
            %POLL Emit the pending value once the host rate window has passed.
            out = emptyEmission();
            nowS = obj.checkTime(nowS);
            out = obj.emitIfDue(nowS, out);
        end

        function reset(obj)
            %RESET Discard any pending value without emitting it.
            if obj.HasPending
                obj.DroppedCount = obj.DroppedCount + 1;
            end
            obj.HasPending = false;
            obj.PendingValue = [];
        end
    end

    methods (Access = private)
        function out = emitIfDue(obj, nowS, out)
            if ~obj.HasPending
                return;
            end
            if nowS - obj.LastEmitS < obj.RateS
                return;
            end
            out.hasValue = true;
            out.value = obj.PendingValue;
            out.timeS = nowS;
            obj.HasPending = false;
            obj.PendingValue = [];
            obj.LastEmitS = nowS;
            obj.EmittedCount = obj.EmittedCount + 1;
        end

        function nowS = checkTime(~, nowS)
            if ~isnumeric(nowS) || ~isscalar(nowS) || ~isreal(nowS) || ...
                    ~isfinite(nowS)
                error('inverterhilgui:InvalidCoalescerTime', ...
                    'Host time must be a real finite numeric scalar.');
            end
            nowS = double(nowS);
        end
    end
end

function out = emptyEmission()
out = struct('hasValue', false, 'value', [], 'timeS', NaN);
end
