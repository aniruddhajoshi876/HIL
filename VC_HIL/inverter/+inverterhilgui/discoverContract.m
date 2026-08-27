function resolved = discoverContract(availablePaths, contract)
%DISCOVERCONTRACT Resolve logical names to concrete target parameter paths.
%
%   RESOLVED = DISCOVERCONTRACT(AVAILABLEPATHS) takes the parameter listing
%   read from the connected real-time application and resolves every logical
%   name in INVERTERHILGUI.PARAMETERCONTRACT to the concrete path the
%   application actually exposes. The nested-structure backing is preferred
%   and the flat-scalar backing is used when it is the only one present, so
%   plan open decision 16 can be answered later without touching callbacks.
%
%   A required logical name with neither backing present is a version
%   mismatch: this function throws INVERTERHILGUI:VERSIONMISMATCH naming every
%   missing path rather than silently falling back to a host default.

if nargin < 2
    contract = inverterhilgui.parameterContract();
end
if ~isstruct(contract) || isempty(contract)
    invalid('Contract must be a nonempty structure array.');
end
availablePaths = normalizePaths(availablePaths);

resolved.entries = repmat(emptyEntry(), 0, 1);
resolved.names = cell(0, 1);
resolved.missing = cell(0, 1);
resolved.structCount = 0;
resolved.flatCount = 0;

missingRequired = cell(0, 1);
for index = 1:numel(contract)
    item = contract(index);
    path = '';
    backing = 'none';
    if any(strcmp(item.structPath, availablePaths))
        path = item.structPath;
        backing = 'struct';
    elseif any(strcmp(item.flatPath, availablePaths))
        path = item.flatPath;
        backing = 'flat';
    end
    if strcmp(backing, 'none')
        resolved.missing{end + 1, 1} = item.name;
        if item.required
            missingRequired{end + 1, 1} = sprintf('%s (%s | %s)', ...
                item.name, item.structPath, item.flatPath); %#ok<AGROW>
        end
        continue;
    end
    entry = emptyEntry();
    entry.name = item.name;
    entry.type = item.type;
    entry.minimum = item.minimum;
    entry.maximum = item.maximum;
    entry.group = item.group;
    entry.required = item.required;
    entry.path = path;
    entry.backing = backing;
    resolved.entries(end + 1, 1) = entry;
    resolved.names{end + 1, 1} = item.name;
    if strcmp(backing, 'struct')
        resolved.structCount = resolved.structCount + 1;
    else
        resolved.flatCount = resolved.flatCount + 1;
    end
end

if ~isempty(missingRequired)
    error('inverterhilgui:VersionMismatch', ...
        ['The connected application does not expose %d required ' ...
        'parameter(s):\n  %s'], numel(missingRequired), ...
        strjoin(missingRequired, sprintf('\n  ')));
end

if resolved.structCount > 0 && resolved.flatCount > 0
    resolved.backing = 'mixed';
elseif resolved.flatCount > 0
    resolved.backing = 'flat';
elseif resolved.structCount > 0
    resolved.backing = 'struct';
else
    resolved.backing = 'none';
end
resolved.resolvedCount = numel(resolved.entries);
end

function paths = normalizePaths(paths)
if ischar(paths)
    paths = {paths};
end
if isstring(paths)
    paths = cellstr(paths);
end
if ~iscell(paths)
    invalid('Available parameter paths must be a cell array of names.');
end
paths = paths(:)';
for index = 1:numel(paths)
    value = paths{index};
    if isstring(value) && isscalar(value)
        value = char(value);
    end
    if ~ischar(value) || isempty(value)
        invalid('Every available parameter path must be a nonempty name.');
    end
    paths{index} = value;
end
end

function entry = emptyEntry()
entry = struct( ...
    'name', '', ...
    'type', '', ...
    'minimum', 0, ...
    'maximum', 0, ...
    'group', '', ...
    'required', false, ...
    'path', '', ...
    'backing', 'none');
end

function invalid(message, varargin)
error('inverterhilgui:InvalidContract', message, varargin{:});
end
