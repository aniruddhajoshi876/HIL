% speedgoat.uninstall - Uninstall your current Speedgoat I/O Blockset
%
%   Description
%   -----------
%   This Speedgoat API function removes the installed Speedgoat I/O Blockset from your host
%   computer.
%
%   Examples
%   --------
%   Uninstall the Speedgoat I/O Blockset:
%       speedgoat.uninstall
%
%   Uninstall the Speedgoat I/O Blockset without any further interaction required:
%       speedgoat.uninstall('Force', true)
%
%   Input Arguments
%   ---------------
%   Name-Value Pair Arguments:
%       'Force' - Forces an automatic uninstall
%           [boolean].
%           When set to 'true', this option starts the uninstallation without any further
%           interaction required.
%
%   Notes
%   -----
%   When you install a new version of the Speedgoat I/O Blockset, the current blockset
%   is uninstalled automatically.

function uninstall(varargin)
    sg.public.uninstall(varargin{:});
end
