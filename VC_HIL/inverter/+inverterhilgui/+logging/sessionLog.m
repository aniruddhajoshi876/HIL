classdef sessionLog < handle
    %SESSIONLOG Append-only in-memory operator command log with export.
    %
    %   Plan 7.4 requires every operator command to be recorded. This log is
    %   append-only in the sense that matters for audit: there is no edit or
    %   clear method, EXPORT does not mutate the stored records, and the log
    %   survives disconnect and reconnect because it is owned by the app
    %   session, not by the target.
    %
    %   BOUNDED RETENTION (2026-08-02): RECORDS is a ring buffer capped at
    %   MAXRECORDS. A continuous pedal drag appends at roughly the 30 ms
    %   coalescer rate, so an unbounded list grew without limit for as long as
    %   the app stayed open, and REFRESHLOG rebuilt the whole table from it on
    %   every 250 ms tick -- O(n) work four times a second against an
    %   ever-growing n. Oldest records are therefore discarded once the cap is
    %   reached. COUNT remains the TOTAL ever appended, so it still reveals
    %   that earlier records existed; TOTALDROPPED reports how many were aged
    %   out. Export a session before it exceeds the cap if a complete trail is
    %   required.

    properties (SetAccess = private)
        % Audit records in append order, built by INVERTERHILGUI.AUDITRECORD.
        % Holds at most MAXRECORDS; oldest are dropped first.
        Records
        % Number of records ever appended, including any since dropped.
        Count = 0
        % Records discarded to stay within MAXRECORDS.
        TotalDropped = 0
    end

    properties (Constant)
        % Retained-record cap. Chosen so a long session stays responsive
        % while keeping a substantial recent command trail.
        MaxRecords = 5000
    end

    methods
        function obj = sessionLog()
            %SESSIONLOG Construct an empty append-only session log.
            obj.Records = inverterhilgui.logging.auditRecord(struct());
            obj.Records(:) = [];
            obj.Count = 0;
        end

        function record = append(obj, info)
            %APPEND Build and store one audit record; returns the record.
            %   Drops the oldest retained record once MAXRECORDS is reached.
            record = inverterhilgui.logging.auditRecord(info);
            obj.Records(end + 1, 1) = record;
            if numel(obj.Records) > obj.MaxRecords
                excess = numel(obj.Records) - obj.MaxRecords;
                obj.Records(1:excess) = [];
                obj.TotalDropped = obj.TotalDropped + excess;
            end
            obj.Count = obj.Count + 1;
        end

        function value = retainedCount(obj)
            %RETAINEDCOUNT Records currently held, after any ring-buffer drop.
            value = numel(obj.Records);
        end

        function records = snapshot(obj)
            %SNAPSHOT Return a copy of every stored record, in order.
            records = obj.Records;
        end

        function text = toLines(obj)
            %TOLINES Render the log as one display line per record.
            text = cell(obj.Count, 1);
            for index = 1:obj.Count
                item = obj.Records(index);
                text{index} = sprintf( ...
                    '%s  t=%s  %-28s  req=%-12s app=%-12s  %-9s %s', ...
                    item.hostTime, targetTimeText(item.targetTimeS), ...
                    item.logicalName, item.requested, item.applied, ...
                    item.result, item.detail);
            end
        end

        function data = toCell(obj)
            %TOCELL Return the log as a cell matrix for a UI table.
            names = obj.columnNames();
            data = cell(obj.Count, numel(names));
            for index = 1:obj.Count
                item = obj.Records(index);
                data(index, :) = { ...
                    item.hostTime, targetTimeText(item.targetTimeS), ...
                    item.logicalName, item.targetPath, item.requested, ...
                    item.applied, item.result, item.detail};
            end
        end

        function fileName = export(obj, fileName)
            %EXPORT Write the log to a CSV file without mutating the log.
            if nargin < 2 || isempty(fileName)
                error('inverterhilgui:InvalidExportTarget', ...
                    'An export file name is required.');
            end
            if isstring(fileName) && isscalar(fileName)
                fileName = char(fileName);
            end
            if ~ischar(fileName) || isempty(fileName)
                error('inverterhilgui:InvalidExportTarget', ...
                    'Export file name must be a nonempty character vector.');
            end
            fid = fopen(fileName, 'w');
            if fid < 0
                error('inverterhilgui:ExportFailed', ...
                    'Could not open %s for writing.', fileName);
            end
            closer = onCleanup(@() fclose(fid));
            names = obj.columnNames();
            fprintf(fid, '%s\n', strjoin(names, ','));
            data = obj.toCell();
            for index = 1:size(data, 1)
                row = data(index, :);
                for column = 1:numel(row)
                    row{column} = csvField(row{column});
                end
                fprintf(fid, '%s\n', strjoin(row, ','));
            end
            clear closer;
        end
    end

    methods (Static)
        function names = columnNames()
            %COLUMNNAMES Fixed export and table column order.
            names = {'hostTime', 'targetTimeS', 'logicalName', ...
                'targetPath', 'requested', 'applied', 'result', 'detail'};
        end
    end
end

function text = targetTimeText(value)
if ~isnumeric(value) || ~isscalar(value) || ~isreal(value) || ~isfinite(value)
    text = '--';
    return;
end
text = sprintf('%.3f', double(value));
end

function text = csvField(value)
if ~ischar(value)
    value = '';
end
text = ['"' strrep(value, '"', '""') '"'];
end
