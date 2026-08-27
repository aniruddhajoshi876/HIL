function entry = contractEntry(source, name)
%CONTRACTENTRY Look up one logical name in a contract or resolved contract.
%
%   ENTRY = CONTRACTENTRY(SOURCE, NAME) accepts either the declarative
%   contract from INVERTERHILGUI.PARAMETERCONTRACT or the resolved contract
%   from INVERTERHILGUI.DISCOVERCONTRACT. ENTRY is empty when NAME is not
%   present, so callers fail closed instead of guessing a target path.

entry = [];
if isstruct(source) && isscalar(source) && isfield(source, 'entries')
    source = source.entries;
end
if ~isstruct(source) || isempty(source) || ~isfield(source, 'name')
    return;
end
if isstring(name) && isscalar(name)
    name = char(name);
end
if ~ischar(name) || isempty(name)
    return;
end
for index = 1:numel(source)
    if strcmp(source(index).name, name)
        entry = source(index);
        return;
    end
end
end
