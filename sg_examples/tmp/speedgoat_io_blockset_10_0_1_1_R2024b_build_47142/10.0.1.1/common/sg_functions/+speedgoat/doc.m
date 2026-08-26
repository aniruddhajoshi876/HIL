% speedgoat.doc - Open the Speedgoat documentation
%
%   Description
%   -----------
%   This Speedgoat API function opens the Speedgoat help documentation where you can find
%   information such as help pages for all Speedgoat driver blocks, release notes, Speedgoat Tools
%   and details on getting started.
%
%   You can also open a specific documentation page by specifying it as an input argument.
%
%   Examples
%   --------
%   Open the Speedgoat help documentation:
%   	speedgoat.doc
%
%   Open the doc page for the IO131 I/O module:
%       speedgoat.doc('IO131')
%
%   Open the doc page for the EtherCAT protocol:
%       speedgoat.doc('EtherCAT')
%
%   Input Arguments
%   ---------------
%   pageName - Documentation page name
%       [character vector].
%       Specify the doc page name by using the auto-suggestion feature (see notes).
%
%   Notes
%   -----
%   The function either opens the doc page in the integrated doc (from your local Speedgoat
%   I/O Blockset installation) or on the online doc (from the Speedgoat website with the latest
%   Speedgoat I/O Blockset), depending on your MATLAB settings. To change your preferences go to:
%   MATLAB Preferences -> Help -> Documentation Location.
%
%   The list of documentation pages is available when using the auto-suggestion feature: open the
%   first left bracket of the function then press the <strong>Tab</strong> key.

function doc(varargin)
    sg.public.doc(varargin{:});
end
