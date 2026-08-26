% speedgoat.showBitstreamContent - Show the content of FPGA bitstream mat file
%
%   Description
%   -----------
%   This Speedgoat API function shows the available information stored in the 'bitstream' mat-file.
%
%   Information displayed (if available) includes:
%       - CI number
%       - Revision number of bitstream
%       - A list of implemented code modules including version and channel count
%       - Required Speedgoat I/O Blockset version, if specified
%
%   Examples
%   --------
%   Show the content of FPGA bitstream mat file:
%       speedgoat.showBitstreamContent(bitstream)
%
%   Input Arguments
%   ---------------
%   bitstream - Bit stream mat-file
%       [mat-file].
%       The bit stream mat-file.

function showBitstreamContent(bitstream)
    sg.public.showBitstreamContent(bitstream);
end
