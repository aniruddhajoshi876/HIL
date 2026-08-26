% speedgoat.getMemoryInfo - Get information on the physical memory usage of your Speedgoat real-time target machine
%
%   Description
%   -----------
%   This Speedgoat API function retrieves information about the status of your Speedgoat real-time
%   target machine's physical memory.
%
%   Examples
%   --------
%   Get information on the available physical memory on the default target machine in bytes:
%       free = speedgoat.getMemoryInfo
%
%   Get information on the available as well as the total installed physical memory of the target
%       machine in bytes:
%       [free, total] = speedgoat.getMemoryInfo
%
%   Get information on the available and the installed physical memory of the target machine as well
%       as the percentage of physical memory in use:
%       [free, total, used] = speedgoat.getMemoryInfo
%
%   Display all available information about the default target machine's physical memory:
%       speedgoat.getMemoryInfo
%       >> 62.0GB of 63.0GB physical memory available (1.59% used)
%
%   Get memory usage information for a specific target using the target name
%       (for example, 'TargetPC1'):
%       [___] = speedgoat.getMemoryInfo('TargetName', 'TargetPC1')
%
%   Get memory usage information for a specific target using the target object (for example, tg):
%       [___] = speedgoat.getMemoryInfo('TargetObject', tg)
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
%   free - Available physical memory
%       [double].
%       Available physical memory in Bytes.
%
%   total - Total physical memory
%       [double].
%       Total installed physical memory in Bytes.
%
%   used - Used physical memory
%       [double].
%       Percentage of physical memory used.
%
%   Notes
%   -----
%   This function requires an Ethernet connection to your Speedgoat real-time target machine.
%   If no 'TargetObject' or 'TargetName' argument is given to the function, the default target
%   is used. Moreover, the 'TargetObject' argument takes precedence: if both arguments
%   are supplied, 'TargetName' will therefore be ignored.

function varargout = getMemoryInfo(varargin)
    [varargout{1:nargout}] = sg.public.getMemoryInfo(varargin{:});
end
