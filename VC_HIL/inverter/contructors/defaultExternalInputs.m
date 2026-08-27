function inputs = defaultExternalInputs()
%DEFAULTEXTERNALINPUTS Safe, quiescent per-channel external plant inputs.
%
%   Backs INVERTERHIL.STEPMODEL's optional EXTERNALINPUTS argument. Every
%   field here matches what STEPMODEL produced before that argument existed:
%   INVERTERHIL.DEFAULTPLANTINPUT's implicit loadTorqueNm (0 Nm) and dcLinkV
%   (400 V), and INVERTERHIL.DEFAULTSTATECONFIG's channel default
%   (connected = true). A caller that omits EXTERNALINPUTS therefore gets
%   STEPMODEL's original behavior bit-for-bit.
%
%   FAULTMASK is carried for contract completeness (the GUI-owned
%   hil_cmd_inverter*_fault_mask tunable) but has no consumer anywhere in the
%   host-verifiable core today -- no function in +INVERTERHIL/ reads a
%   per-channel fault-injection bitmask. STEPMODEL accepts and ignores it
%   rather than silently dropping the field, so a future consumer can be
%   wired without another signature change.

channel = struct( ...
    'loadTorqueNm', 0, ...
    'dcLinkV', 400, ...
    'connected', true, ...
    'faultMask', uint32(0));
inputs.channels = repmat(channel, 1, 4);
end
