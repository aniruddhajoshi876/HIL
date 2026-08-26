% speedgoat.version - Show (or get) the Speedgoat I/O Blockset version and other information
%
%   Description
%   -----------
%   This Speedgoat API function provides information about the version of the Speedgoat I/O Blockset
%   currently installed on your MATLAB host.
%
%   Examples
%   --------
%   Show the Speedgoat I/O Blockset version:
%       speedgoat.version
%       >> Speedgoat I/O Blockset Version 9.1.0 (R2020b)
%       >> Build number: 20576-002
%       >> Build date: 02-Sep-2020 08:46:53
%
%   Get the Speedgoat I/O Blockset version number:
%       sgLibVer = speedgoat.version
%
%   Get the Speedgoat I/O Blockset version and the build number:
%       [sgLibVer, sgLibBuildNum] = speedgoat.version
%
%   Get the Speedgoat I/O Blockset version number, the build number and the build date:
%       [sgLibVer, sgLibBuildNum, sgLibBuildDate] = speedgoat.version
%
%   Output Arguments
%   ----------------
%   sgLibVer - Speedgoat I/O Blockset version
%       [character vector].
%       The version, e.g. '9.1.0'.
%
%   sgLibBuildNum - Speedgoat I/O Blockset build number (code revision)
%       [character vector].
%       The build number, e.g. '20576'.
%
%   sgLibBuildDate - Speedgoat I/O Blockset build date
%       [character vector].
%       The build date, e.g. '02-Sep-2020 08:46:53'.
%

function varargout = version
    [varargout{1:nargout}] = sg.public.version;
end
