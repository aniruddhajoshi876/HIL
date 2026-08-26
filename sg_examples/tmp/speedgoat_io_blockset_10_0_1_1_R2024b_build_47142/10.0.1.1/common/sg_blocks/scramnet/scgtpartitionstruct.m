function [partition]=scgtpartitionstruct(partition)
% SCGTPARTITIONSTRUCT   SCRAMNet GT memory partition utility
% SCGTPARTITIONSTRUCT(P) Shared memory is allocated using
%  hetergenenous bundles of data that are packed into memory partitions.
%  To provide flexible control over the ordering and alignment of data, a
%  partition structure is required.  This utility function provides a 
%  default version of the partition structure or accepts a user-supplied
%  partition structure.  
%
% Common Partition fields
%
%   P(1).Address - Offset into shared memory of first element
%   P(n).Type - Data type (ex. 'int32','double', etc)
%   p(n).Size - Array dimensions supplied as a vector of dimensions
%   p(n).Alignment - Byte alignment for this element
%
% See also SCGTNODESTRUCT

if isempty(partition)
    partition.Address   = '0x0';
    partition.Type      = 'uint32';
    partition.Size      = '1';
    partition.Alignment = '4';
elseif ~isa(partition, 'struct')
    error('Data partition must be of class ''struct''');
end

for i=1:length(partition)
    if ~isfield(partition(i),'Address') || isempty(partition(i).Address)
        partition(i).Address = '0x0';
    end
    if ~isfield(partition(i),'Type') || isempty(partition(i).Type)
        partition(i).Type = 'uint32';
    end
    if ~isfield(partition(i),'Size') || isempty(partition(i).Size)
        partition(i).Size = '1';
    end
    if ~isfield(partition(i),'Alignment') || isempty(partition(i).Alignment)
        partition(i).Alignment = '4';
    end
end

dtypes     = zeros(1, length(partition), 1);
sizes      = zeros(1, length(partition) * 2, 1);
alignments = zeros(1, length(partition), 1);
widths     = zeros(1, length(partition), 1);

for i=1:length(partition)
    [dtID, dtSize, ACsize] = getDataType(partition(i).Type);
    dtypes(i) = dtID;
    try
        if ischar(partition(i).Size),
            eval(['tsize=', partition(i).Size, ';']);
        elseif isnumeric(partition(i).Size),
            tsize = round(partition(i).Size);
            partition(i).Size = ['[' num2str(tsize) ']'];
            eval(['tsize=', partition(i).Size, ';']);
        else
            error('Size information is invalid type');
        end
    catch
        error('Size information is invalid');
    end
    if length(tsize) == 1 % vector
        sizes(i * 2 - 1) = tsize;
        dlength = tsize;
    else % matrix
        sizes(i * 2 - 1) = tsize(1);
        sizes(i * 2) = tsize(2);
        dlength = tsize(1) * tsize(2);
    end
    try
        if ischar(partition(i).Alignment),
            eval(['alignment=', partition(i).Alignment, ';']);
        elseif isnumeric(partition(i).Alignment),
            tsize = round(partition(i).Alignment);
            partition(i).Size = ['[' num2str(Alignment) ']'];
            eval(['alignment=', partition(i).Alignment, ';']);
        else
            error('Alignment information is invalid type');
        end
    catch
        error('Alignment information is invalid');
    end
    alignments(i) = alignment;    
    nBytes = dlength * dtSize;
    alignRem = rem(nBytes, alignment);
    if alignRem == 0
        widths(i) = nBytes;
    else
        widths(i) = nBytes+alignment-alignRem;
    end  
end

% Compute address
baseAddress = partition(1).Address;
if ischar(baseAddress), 
    baseAddress = hex2dec(baseAddress(3:end));
elseif isnumeric(baseAddress),
    baseAddress = round(baseAddress);
    partition(1).Address = ['0x' dec2hex(baseAddress)];
end
address= baseAddress;
if rem(baseAddress, 4) ~= 0
    error(['the Specified address = '  partition(1).Address ' is not aligned on 32 bit boundaries, Try = 0x' dec2hex(bitshift(bitshift(baseAddress,-2)+1,2)) ]);
end

for i=2:length(partition)
    baseAddress = baseAddress + widths(i-1);
    partition(i).Address = ['0x',dec2hex(baseAddress)];
end
ndwords = ceil(sum(widths)/4);

partition(1).Internal.DTypes     = dtypes;
partition(1).Internal.Sizes      = sizes;
partition(1).Internal.Alignments = alignments;
partition(1).Internal.Widths     = widths;
partition(1).Internal.NDwords    = ndwords;
partition(1).Internal.Address    = address;



function [dtID, dtSize, ACsize]= getDataType(typeStr)

if strcmp(typeStr,'double')
     dtID=0;
     dtSize=8;
     ACsize=4;
elseif strcmp(typeStr,'single')
    dtID=1;
    dtSize=4;
    ACsize=4;
elseif strcmp(typeStr,'int8')
    dtID=2;
    dtSize=1;
    ACsize=1;
elseif strcmp(typeStr,'uint8')
    dtID=3;
    dtSize=1;
    ACsize=1;
elseif strcmp(typeStr,'int16')
    dtID=4;
    dtSize=2;
    ACsize=2;
elseif strcmp(typeStr,'uint16')
    dtID=5;
    dtSize=2;
    ACsize=2;
elseif strcmp(typeStr,'int32')
    dtID=6;
    dtSize=4;
    ACsize=4;
elseif strcmp(typeStr,'uint32')
    dtID=7;
    dtSize=4;
    ACsize=4;
elseif strcmp(typeStr,'boolean')
    dtID=8;
    dtSize=1;
    ACsize=1;
else
    error('the supported data types are: double, single, int8, uint8, int16, uint16, int32, uint32, boolean'); 
end
