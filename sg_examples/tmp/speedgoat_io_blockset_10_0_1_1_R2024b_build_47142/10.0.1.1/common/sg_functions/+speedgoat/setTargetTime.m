% speedgoat.setTargetTime - Set the date and time on your Speedgoat real-time target machine
%
%   Description
%   -----------
%   This Speedgoat API function sets the date and time on your Speedgoat real-time target machine.
%
%   You can run this function without input arguments and use the current host system
%   time, or you can specify the desired date and time in an input argument.
%   This function writes the new date and time to the target machine's real-time clock. The date
%   and time will therefore remain correct in the event of a reboot or loss of power.
%
%   Examples
%   --------
%   Set the time on the default target machine according to the current time of the host computer:
%       speedgoat.setTargetTime
%       >> Target time set to: Mon Nov 30 14:38:08 GMT 2020
%
%   Set a specific time on the default target machine:
%       speedgoat.setTargetTime(newTime)
%       >> Target time set to: Mon Nov 30 14:38:08 GMT 2020
%
%   Set the time on a specified target machine using the target name (e.g. 'TargetPC1'):
%       speedgoat.setTargetTime(___, 'TargetName', 'TargetPC1')
%       >> Target time set to: Mon Nov 30 14:38:08 GMT 2020
%
%   Set the time on a specified target machine using the target object (e.g. tg):
%       speedgoat.setTargetTime(___, 'TargetObject', tg)
%       >> Target time set to: Mon Nov 30 14:38:08 GMT 2020
%
%   Obtain the updated result in a variable when setting the time on the target machine:
%       targetTime = speedgoat.setTargetTime(___)
%
%   Input Arguments
%   ---------------
%   newTime - New date and time
%       [datenum].
%       New date and time to set on the target machine, specified as MATLAB datenum, e.g. now().
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
%       [character vector].
%       Updated date and time on the target.
%
%   Notes
%   -----
%   This function requires an Ethernet connection to your Speedgoat real-time target machine.
%   If no 'TargetObject' or 'TargetName' argument is given to the function, the default target
%   is used. Moreover, the 'TargetObject' argument takes precedence: if both arguments
%   are supplied, 'TargetName' will therefore be ignored.

function varargout = setTargetTime(varargin)
    [varargout{1:nargout}] = sg.public.setTargetTime(varargin{:});
end
