% speedgoat.getDiskSpace - Get information about disk usage of your Speedgoat real-time target machine
%
%   Description
%   -----------
%   This Speedgoat API function retrieves information about the status of your Speedgoat real-time
%   target machine's disk.
%
%   Examples
%   --------
%   Get the available space on the default target machine's disk in bytes:
%       free = speedgoat.getDiskSpace
%
%   Get the available space as well as the total capacity of the target machine's disk in bytes:
%       [free, total] = speedgoat.getDiskSpace
%
%   Get the available space, the total capacity, and the percentage of disk space used:
%       [free, total, used] = speedgoat.getDiskSpace
%
%   Display disk information for the default target machine:
%       speedgoat.getDiskSpace
%       >> Disk space: 102.3 GB of 128.0 GB available (20.1% used)
%
%   Get disk usage information for a specific target using the target name (e.g., 'TargetPC1'):
%       [___] = speedgoat.getDiskSpace('TargetName', 'TargetPC1')
%
%   Get disk usage information for a specific target using the target object (e.g., tg):
%       [___] = speedgoat.getDiskSpace('TargetObject', tg)
%
%   Input Arguments
%   ---------------
%   Name-Value Pair Arguments:
%       'TargetName' - Target machine name
%           [character vector].
%           The name of the target machine you want to use.
%
%       'TargetObject' - Target object
%           [target object].
%           The target object of the target machine you want to use.
%
%   Output Arguments
%   ----------------
%   free - Free disk space
%       [double].
%       Free disk space in bytes.
%
%   total - Total disk space
%       [double].
%       Total disk space in bytes.
%
%   used - Used disk space
%       [double].
%       Percentage of disk space used.
%
%   Notes
%   -----
%   This function requires an Ethernet connection to your Speedgoat real-time target machine.
%   If no 'TargetObject' or 'TargetName' argument is given to the function, the default target
%   is used. The 'TargetObject' argument takes precedence if both arguments are supplied and
%   'TargetName' is ignored.
%
%   For dual-boot systems, the output varies depending on the running MATLAB release.
%   The total disk space shown on MATLAB R2020b up to R2025b is the space allocated to the 
%   currently active operating system. In MATLAB R2026a and later, it is the size of the entire 
%   disk. The free disk space is the space available for logging, excluding the 16 GB reserved 
%   for Antelope RTOS.

function varargout = getDiskSpace(varargin)
    [varargout{1:nargout}] = sg.public.getDiskSpace(varargin{:});
end
