function boards = speedgoat_supported
% <name>_supported fills in a single instance or an array
% of structures with information about PCI boards that may
% be found in a system.  This information is used by getxpcpci.
%
%   VendorID is the number assigned to the vendor of the board
%   or bus adapter for this board.  This is given as a
%   hexadecimal number in string form.  This value is compared
%   with information returned from the target to decide if this
%   device is present.
%
%   DeviceID is the number chosen by the vendor for this specific
%   board or bus adapter.  This is given as a hexadecimal number
%   in string form.  This value is compared with information
%   returned from the target to decide if this device is present.
%
%   SubVendorID is the number assigned to the vendor of this
%   subsystem (the whole board).  Enter the number as a string
%   in hex.  If this is not needed to uniquely identify the board,
%   enter '-1'.
%
%   SubDeviceID is the vendor chosen number assigned to this
%   specific board in the vendor's catalog.  Enter the number as a
%   string in hex.  If this is not needed to uniquely identify the
%   board, enter '-1'.
%
%     NOTE: Some bus interface chips used on PCI boards, such
%     as the PLX-9080 always return a vendor ID of 0x10b5 (==PLX) and
%     a device ID of 9080 or 9050.  For these boards, it is necessary
%     to include SubVendorID and SubDeviceID.
%
%   DeviceName is a string that identifies the specific board.
%
%   VendorName is a string that identifies the vendor of the board.
%3
%   DeviceType is a string that indicates the functions that the
%   board performs.  Abbreviations like DI for digital input, etc.
%   are appropriate.  This is only used as a display string.

% An empty return indicates that there are no boards to be
% shown for this file.  Preset to empty and overwrite below.
boards = sg.db.getSupportedIoModules('RequireAccessToThisDataBase', '20Goats');
boards = rmfield(boards, {'FirstRelease', 'LastRelease'});

return
