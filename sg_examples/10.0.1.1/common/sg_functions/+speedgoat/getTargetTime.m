% speedgoat.getTargetTime - Get the date and time of your Speedgoat real-time target machine
%
%   Description
%   -----------
%   This Speedgoat API function gets the current date and time of your Speedgoat real-time target
%   machine. The target time is by default in [ddd mmm dd HH:MM:SS yyyy] format, but can also be
%   returned as a serial date number [double].
%
%   Examples
%   --------
%   Get the time of the default target machine:
%       targetTime = speedgoat.getTargetTime
%
%   Get the time of the default target machine in serial date number format:
%       targetTime = speedgoat.getTargetTime('NumberFormat', true)
%
%   Get the time of a specified target machine using the target name (for example, 'TargetPC1'):
%       targetTime = speedgoat.getTargetTime(___, 'TargetName', 'TargetPC1')
%
%   Get the time of a specified target machine using the target object (for example, tg):
%       targetTime = speedgoat.getTargetTime(___, 'TargetObject', tg)
%
%   Display the time of the target machine:
%       speedgoat.getTargetTime(___)
%       >> Target time is: Tue Dec 07 08:54:17 GMT 2021
%
%   Display the time of the target machine as a serial date number:
%       speedgoat.getTargetTime('NumberFormat', true)
%       >> Target time is: 7.3850e+05
%
%   Input Arguments
%   ---------------
%   NumberFormat - Serial date number format
%       [boolean].
%       When set to true, the input argument converts the output of the function to the serial
%       date number format [double], similar to the MATLAB datenum, for example, now().
%
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
%   targetTime - Target time
%       [character vector | double].
%       The current date and time of the target machine.
%
%   Notes
%   -----
%   This function requires an Ethernet connection to your Speedgoat real-time target machine.
%   If no 'TargetObject' or 'TargetName' argument is given to the function, the default target
%   is used. Moreover, the 'TargetObject' argument takes precedence: if both arguments
%   are supplied, 'TargetName' will therefore be ignored.

function varargout = getTargetTime(varargin)
    [varargout{1:nargout}] = sg.public.getTargetTime(varargin{:});
end
