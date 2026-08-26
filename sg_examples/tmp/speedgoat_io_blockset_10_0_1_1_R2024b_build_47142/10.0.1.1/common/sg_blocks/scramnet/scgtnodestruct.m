function node=scgtnodestruct(node)
% SCGTNODESTRUCT   SCRAMNet GT node configuration utility
% SCGTNODESTRUCT(N) SCRAMNet GT nodes (boards) are configured
%  when the XPC target is started.  The Node structure (N) allows the user
%  to configure various modes of the board.  This utility can create a
%  default version of the node structure or it can accept a subset of
%  fields and produce a complete node structure by applying defaults
%  to undefined fields.
%
% See also SCGTPARTITIONSTRUCT

if isempty(node) || ~isfield(node,'Interface') || isempty(node.Interface)
    interface.NodeID          = '-1';
    interface.ActiveInterface = '-1';

    mode.ReceivePath          = 'nc';
    mode.TransmitPath         = 'nc';
    mode.RetransmitPath       = 'nc';
    mode.WriteLastPath        = 'nc';
    mode.ElectronicWrapPath   = 'nc';
    mode.ByteSwapGTMemory     = 'nc';
    mode.WordSwapGTMemory     = 'nc';
    mode.PCI64bitDataTransfer = 'nc';

    interrupts.ChangeBroadcastInterruptMask = 'no';
    interrupts.BroadcastInterruptMask       = '0x00000000';
    interrupts.SelfInterrupts               = 'nc';
    interrupts.UnicastInterrupts            = 'nc';
    interrupts.LinkErrorInterrupts          = 'nc';

    lasers.ActiveInterfaceLaser = 'nc';
    lasers.Interface0Laser      = 'nc';
    lasers.Interface1Laser      = 'nc';

    interface.Mode       = mode;
    interface.Lasers     = lasers;
    interface.Interrupts = interrupts;

    node.Interface       = interface;
end

if ~isfield(node,'Partitions') || isempty(node.Partitions)
    node.Partitions(1) = scgtpartitionstruct([]);
end

interface = node.Interface;

if ~isa(interface, 'struct')
    error('interface data must be of class ''struct''');
end

if ~isfield(interface, 'NodeID') || isempty(interface.NodeID)
    interface.NodeID = '-1';
end

if ~isfield(interface, 'ActiveInterface') || isempty(interface.ActiveInterface)
    interface.ActiveInterface = '-1';
end

if ~isa(interface.Mode, 'struct')
    error('Mode section of interface data must be of class ''struct''');
end

mode= interface.Mode;
if ~isfield(mode,'ReceivePath') || isempty(mode.ReceivePath)
    mode.ReceivePath = 'nc';
end
if ~isfield(mode,'TransmitPath') || isempty(mode.TransmitPath)
    mode.TransmitPath = 'nc';
end
if ~isfield(mode,'RetransmitPath') || isempty(mode.RetransmitPath)
    mode.RetransmitPath = 'nc';
end
if ~isfield(mode,'WriteLastPath') || isempty(mode.WriteLastPath)
    mode.WriteLastPath = 'nc';
end
if ~isfield(mode,'ElectronicWrapPath') || isempty(mode.ElectronicWrapPath)
    mode.ElectronicWrapPath = 'nc';
end
if ~isfield(mode,'ByteSwapGTMemory') || isempty(mode.ByteSwapGTMemory)
    mode.ByteSwapGTMemory = 'nc';
end
if ~isfield(mode,'WordSwapGTMemory') || isempty(mode.WordSwapGTMemory)
    mode.WordSwapGTMemory = 'nc';
end
if ~isfield(mode,'PCI64bitDataTransfer') || isempty(mode.PCI64bitDataTransfer)
    mode.PCI64bitDataTransfer = 'nc';
end
interface.Mode=mode;

if ~isfield(interface,'Lasers')
    interface.Lasers.ActiveInterfaceLaser = 'nc';
end

if ~isa(interface.Lasers, 'struct')
    error('Lasers section of interface data must be of class ''struct''');
end

interrupts= interface.Interrupts;
if ~isfield(interrupts,'ChangeBroadcastInterruptMask') || isempty(interrupts.ChangeBroadcastInterruptMask)
    interrupts.ChangeBroadcastInterruptMask = 'no';
end
if ~isfield(interrupts,'BroadcastInterruptMask') || isempty(interrupts.BroadcastInterruptMask)
    interrupts.BroadcastInterruptMask = '0x00000000';
end
if ~isfield(interrupts,'SelfInterrupts') || isempty(interrupts.SelfInterrupts)
    interrupts.SelfInterrupts = 'nc';
end
if ~isfield(interrupts,'UnicastInterrupts') || isempty(interrupts.UnicastInterrupts)
    interrupts.UnicastInterrupts = 'nc';
end
if ~isfield(interrupts,'LinkErrorInterrupts') || isempty(interrupts.LinkErrorInterrupts)
    interrupts.LinkErrorInterrupts = 'nc';
end
interface.Interrupts= interrupts;

lasers = interface.Lasers;
if ~isfield(lasers,'ActiveInterfaceLaser') || isempty(lasers.ActiveInterfaceLaser)
    lasers.ActiveInterfaceLaser = 'nc';
end
if ~isfield(lasers,'Interface0Laser') || isempty(lasers.Interface0Laser)
    lasers.Interface0Laser = 'nc';
end
if ~isfield(lasers,'Interface1Laser') || isempty(lasers.Interface1Laser)
    lasers.Interface1Laser = 'nc';
end
interface.Lasers = lasers;

if ~isa(interface.Interrupts, 'struct')
    error('Interrupts section of interface data must be of class ''struct''');
end

% calculate options
options = zeros(1, 15);

% Interface Options
nodeid = str2num(interface.NodeID);
if (nodeid < -1 || nodeid > 255)
   error('Invalid value for NodeID (Must be between -1 and 255)');
end

actint = str2num(interface.ActiveInterface);
if (actint < -1 || actint > 1)
   error('Invalid value for ActiveInterface (Must be -1, 0 or 1)');
end

% Mode Options
mode = interface.Mode;
if strcmpi(mode.ReceivePath,'off')
    options(1) = 0;
elseif strcmpi(mode.ReceivePath,'on')
    options(1) = 1;
elseif strcmpi(mode.ReceivePath,'nc')
    options(1) = -1;
else
    error('Invalid value for ReceivePath in section Mode (on, off, nc)');
end

if strcmpi(mode.TransmitPath,'off')
    options(2) = 0;
elseif strcmpi(mode.TransmitPath,'on')
    options(2) = 1;
elseif strcmpi(mode.TransmitPath,'nc')
    options(2) = -1;
else
    error('Invalid value for TransmitPath in section Mode (on, off, nc)');
end

if strcmpi(mode.RetransmitPath,'off')
    options(3) = 0;
elseif strcmpi(mode.RetransmitPath,'on')
    options(3) = 1;
elseif strcmpi(mode.RetransmitPath,'nc')
    options(3) = -1;
else
    error('Invalid value for RetransmitPath in section Mode (on, off, nc)');
end

if strcmpi(mode.WriteLastPath,'off')
    options(4) = 0;
elseif strcmpi(mode.WriteLastPath,'on')
    options(4) = 1;
elseif strcmpi(mode.WriteLastPath,'nc')
    options(4) = -1;
else
    error('Invalid value for WriteLastPath in section Mode (on, off, nc)');
end

if strcmpi(mode.ElectronicWrapPath,'off')
    options(5) = 0;
elseif strcmpi(mode.ElectronicWrapPath,'on')
    options(5) = 1;
elseif strcmpi(mode.ElectronicWrapPath,'nc')
    options(5) = -1;
else
    error('Invalid value for ElectronicWrapPath in section Mode (on, off, nc)');
end

if strcmpi(mode.ByteSwapGTMemory,'off')
    options(6) = 0;
elseif strcmpi(mode.ByteSwapGTMemory,'on')
    options(6) = 1;
elseif strcmpi(mode.ByteSwapGTMemory,'nc')
    options(6) = -1;
else
    error('Invalid value for ByteSwapGTMemory in section Mode (on, off, nc)');
end

if strcmpi(mode.WordSwapGTMemory,'off')
    options(7) = 0;
elseif strcmpi(mode.WordSwapGTMemory,'on')
    options(7) = 1;
elseif strcmpi(mode.WordSwapGTMemory,'nc')
    options(7) = -1;
else
    error('Invalid value for WordSwapGTMemory in section Mode (on, off, nc)');
end

if strcmpi(mode.PCI64bitDataTransfer,'off')
    options(8) = 1;
elseif strcmpi(mode.PCI64bitDataTransfer,'on')
    options(8) = 0;
elseif strcmpi(mode.PCI64bitDataTransfer,'nc')
    options(8) = -1;
else
    error('Invalid value for PCI64bitDataTransfer in section Mode (on, off, nc)');
end

% Interrupt Options
interrupts = interface.Interrupts;
if strcmpi(interrupts.ChangeBroadcastInterruptMask,'no')
    options(9) = 0;
elseif strcmpi(interrupts.ChangeBroadcastInterruptMask,'yes')
    options(9) = 1;
else
    error('Invalid value for ChangeBroadcastInterruptMask in section Interrupts (yes, no)');
end

if ischar(interrupts.BroadcastInterruptMask),
   mask = hex2dec(interrupts.BroadcastInterruptMask(3:end));
else
   error('Invalid value for BroadcastInterruptMask in section Interrupts');
end

if strcmpi(interrupts.SelfInterrupts,'off')
    options(10) = 0;
elseif strcmpi(interrupts.SelfInterrupts,'on')
    options(10) = 1;
elseif strcmpi(interrupts.SelfInterrupts,'nc')
    options(10) = -1;
else
    error('Invalid value for SelfInterrupts in section Interrupts (on, off, nc)');
end

if strcmpi(interrupts.UnicastInterrupts,'off')
    options(11) = 0;
elseif strcmpi(interrupts.UnicastInterrupts,'on')
    options(11) = 1;
elseif strcmpi(interrupts.UnicastInterrupts,'nc')
    options(11) = -1;
else
    error('Invalid value for UnicastInterrupts in section Interrupts (on, off, nc)');
end

if strcmpi(interrupts.LinkErrorInterrupts,'off')
    options(12) = 0;
elseif strcmpi(interrupts.LinkErrorInterrupts,'on')
    options(12) = 1;
elseif strcmpi(interrupts.LinkErrorInterrupts,'nc')
    options(12) = -1;
else
    error('Invalid value for LinkErrorInterrupts in section Interrupts (on, off, nc)');
end

% Laser Options
lasers = interface.Lasers;
if strcmpi(lasers.ActiveInterfaceLaser,'off')
    options(13) = 0;
elseif strcmpi(lasers.ActiveInterfaceLaser,'on')
    options(13) = 1;
elseif strcmpi(lasers.ActiveInterfaceLaser,'nc')
    options(13) = -1;
else
    error('Invalid value for ActiveInterfaceLaser in section Lasers (on, off, nc)');
end

if strcmpi(lasers.Interface0Laser,'off')
    options(14) = 0;
elseif strcmpi(lasers.Interface0Laser,'on')
    options(14) = 1;
elseif strcmpi(lasers.Interface0Laser,'nc')
    options(14) = -1;
else
    error('Invalid value for Interface0Laser in section Lasers (on, off, nc)');
end

if strcmpi(lasers.Interface1Laser,'off')
    options(15) = 0;
elseif strcmpi(lasers.Interface1Laser,'on')
    options(15) = 1;
elseif strcmpi(lasers.Interface1Laser,'nc')
    options(15) = -1;
else
    error('Invalid value for Interface1Laser in section Lasers (on, off, nc)');
end

node.Interface=interface;

% deal with associated partitions
partitions = node.Partitions;

poptions = length(partitions);
for i=1:length(partitions)
    partition = partitions(i);
    partition = scgtpartitionstruct(partition);
    poptions = [poptions, partition.Internal.NDwords, partition.Internal.Address];
    partitions1(i)=partition;
end
node.Partitions=partitions1;

node.Interface.Internal.NodeID          = nodeid;
node.Interface.Internal.ActiveInterface = actint;
node.Interface.Internal.Partitions      = poptions;
node.Interface.Internal.Options         = options;
node.Interface.Internal.Mask            = mask;
