% speedgoat.model.highlight - Highlight objects in a Simulink model
%
%   Description
%   -----------
%   This function allows you to temporarily highlight blocks, block parameters, subsystems and
%   annotations in a Simulink model.
%
%   Using name-value pair arguments, you can in addition open the block mask or subsystem.
%
%   Examples
%   --------
%   Highlight the "CAN FD Pack_standard" block of the CAN_FDLoopback product example:
%       speedgoat.model.highlight('sgMdl_CAN_FDLoopback/CAN FD Pack_standard')
%
%   Highlight the "CAN_(FD)_MESSAGE_BUS" subsystem and open it:
%       speedgoat.model.highlight('sgMdl_CAN_FDLoopback/CAN_(FD)_MESSAGE_BUS - Datatypes', 'Open', true)
%
%   Highlight the "moduleType" mask parameter of the "CAN_Setup" block:
%       speedgoat.model.highlight('sgMdl_CAN_FDLoopback/CAN_Setup', 'Parameter', 'moduleType')
%
%   Highlight the signal output port N°1 of the "BusSelector_CANFD" block:
%       speedgoat.model.highlight('sgMdl_CAN_FDLoopback/CAN_(FD)_MESSAGE_BUS - Datatypes/BusSelector_CANFD', 'Signal', 1)
%
%   Input Arguments
%   ---------------
%   Path-object path in Simulink
%       [character vector | string].
%       Path of the block, subsystem or annotation that should be highlighted. The model must
%       already be open when this API is executed.
%
%   Name-Value Pair Arguments:
%       'Open' - open block mask or subsystem
%           [boolean].
%           When set to true, the object specified in 'path' will not only be highlighted but also
%           opened.
%           If the path specifies a block, it will open the block mask.
%           If the path specifies a subsystem, it will open that subsystem.
%
%       'Parameter' - Mask parameter
%           [character vector | string].
%           The mask parameter name that you want to highlight in the specified block. The block
%           mask will be opened in any case, and the 'Open' argument does not need to be set to
%           true.
%
%       'Signal' - Signal port
%           [double].
%           The output port of the source block of the signal you want to highlight.

function highlight(varargin)
    sg.public.highlight(varargin{:});
end
