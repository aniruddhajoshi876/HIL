function input = defaultStateInput()
%DEFAULTSTATEINPUT Quiescent system input with shared pins and pair DC links.

input.controlEnable = true;
input.controlDisable = false;
input.powerCycle = false;
input.dcLinkV = [400 400];
input.channels = repmat(inverterhil.defaultChannelStateInput(), 1, 4);
end
