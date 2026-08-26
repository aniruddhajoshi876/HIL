% speedgoat.restbus.IO723BlockAPI - Create an IO723 block configuration object
%
%   Description
%   -----------
%   speedgoat.restbus.IO723BlockAPI has been renamed to speedgoat.restbus.IO723BlockConfig and will be removed in a future release.
%
function configObj = IO723BlockAPI(blockPath)
    arguments
        blockPath{mustBeText}
    end

    sg.warning(['''speedgoat.restbus.IO723BlockAPI'' has been renamed to ' ...
        '''speedgoat.restbus.IO723BlockConfig'' and will be removed in a future release']);
    configObj = speedgoat.restbus.IO723BlockConfig(blockPath);
end
