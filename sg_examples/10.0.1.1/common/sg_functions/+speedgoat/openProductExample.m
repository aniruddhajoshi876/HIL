% speedgoat.openProductExample - Open the Speedgoat Product Example
%
%   Description
%   -----------
%   This Speedgoat API function opens either a specific Speedgoat product example or the webpage
%   listing all the available Speedgoat product examples.
%
%   Syntax
%   ------
%   Open the webpage listing all Speedgoat product examples:
%       speedgoat.openProductExample()
%
%   Open a specific Speedgoat product example using the example name:
%       speedgoat.openProductExample(exampleName)
%
%   Examples
%   --------
%   Open the webpage listing all Speedgoat product examples:
%       speedgoat.openProductExample
%
%   Open the Speedgoat product example for the Real-Time UDP communication protocol:
%       speedgoat.openProductExample('UDP_Loopback')
%
%   Open the Speedgoat product example for the IO750 (the I/O module is required in order to run
%       the example):
%       speedgoat.openProductExample('IO750_EtherCATDriveControl')
%
%   Input Arguments
%   ---------------
%   exampleName - Example's name
%       [character vector | string].
%       The name of the example you want to open, e.g. "UDP_Loopback" for the Real-Time UDP
%       communication protocol. Otherwise use the auto-suggestion feature to find the example
%       that matches your Speedgoat I/O module (see Notes).
%
%   Notes
%   -----
%   The list of all the product examples is available when using the auto-suggestion feature:
%   open the first left bracket of the function then press the <strong>Tab</strong> key.

function openProductExample(varargin)
    sg.public.openProductExample(varargin{:});
end
