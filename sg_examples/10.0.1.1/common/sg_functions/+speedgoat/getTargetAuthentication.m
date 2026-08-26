% speedgoat.getTargetAuthentication - Get the target authentication info file
%
%   Description
%   -----------
%   This Speedgoat API function provides step-by-step instructions to obtain the target
%   authentication info file which may be required to obtain an authentication from Speedgoat.
%
%   The function must be used if you encounter the "failed target authentication" message. It
%   will give you the target authentication info file. You will then be asked to provide this file
%   directly to Speedgoat Support, along with a picture of the target machine's label, so that
%   Support can provide you with a "serial file".
%
%   Examples
%   --------
%   Get the file from the default target machine:
%       speedgoat.getTargetAuthentication
%
%   Get the file from a specific target machine using the target name (e.g. 'TargetPC1'):
%       speedgoat.getTargetAuthentication('TargetName', 'TargetPC1')
%
%   Get the file from a specific target machine using the target object (e.g. tg):
%       speedgoat.getTargetAuthentication('TargetObject', tg)
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
%   Notes
%   -----
%   This function requires an Ethernet connection to your Speedgoat real-time target machine.
%   If no 'TargetObject' or 'TargetName' argument is given to the function, the default target
%   is used. Moreover, the 'TargetObject' argument takes precedence: if both arguments
%   are supplied, 'TargetName' will therefore be ignored.

function getTargetAuthentication(varargin)
    sg.public.getTargetAuthentication(varargin{:});
end
