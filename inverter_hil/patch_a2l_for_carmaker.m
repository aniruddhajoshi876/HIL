function patch_a2l_for_carmaker(a2lPath)
%PATCH_A2L_FOR_CARMAKER Post-process a coder.asap2.export A2L so IPG CarMaker
%can import it and stimulate the pedal commands.
%
% coder.asap2.export output is not directly usable by CarMaker 12.0.1. Two
% edits are required every time the A2L is regenerated; doing them by hand is
% how they get forgotten.
%
%   1. Remove the HOST_NAME line from /begin XCP_ON_UDP_IP.
%      CarMaker's importer double-quotes whatever value it finds into '""""',
%      producing a Tcl parse error in XCP::Setup::GenASAP2Parameters
%      ("list element in quotes followed by ..."). Deleting the line entirely
%      is the only form that imports cleanly.
%
%   2. Re-declare the DAQ event channels as DAQ_STIM instead of DAQ.
%      A STIM sample group can only use an event channel that permits STIM.
%      coder.asap2.export emits every EVENT as DAQ-only, so CarMaker offers no
%      STIM direction and the pedal commands can never be stimulated.
%
%      CAVEAT: this declares a capability on the master side. It is only
%      honoured if the Simulink Real-Time XCP server actually implements STIM.
%      No evidence of STIM support was found in the R2024b slrealtime
%      installation (no STIM tokens in slrealtime_xcp.tlc, none across 648
%      scanned binaries). If the slave does not support it, expect a
%      master/slave mismatch warning at SIM_START, in the same family as the
%      timestamp mismatch documented in carmaker/docs/ipg_hil_bringup.md.
%
% Idempotent: safe to run twice on the same file.

if nargin < 1 || isempty(a2lPath)
    a2lPath = fullfile(fileparts(mfilename('fullpath')), 'inverter_hil.a2l');
end
assert(isfile(a2lPath), 'A2L not found: %s', a2lPath);

txt = fileread(a2lPath);
original = txt;

% --- 1. drop HOST_NAME, but ONLY inside the transport IF_DATA blocks -----
% The A2ML schema section legitimately contains '"HOST_NAME" char[256];' as
% part of a taggedunion type declaration. Removing that would corrupt the
% grammar, so scope the edit to /begin XCP_ON_*_IP blocks and match only a
% line that STARTS with the bare token (the schema line starts with a quote).
% Note coder.asap2.export emits 'ADDRESS "10.10.10.5"' rather than HOST_NAME
% when the target address is configured, in which case there is nothing to
% remove and nHost is 0 -- that is the healthy case, not a failure.
nHost = 0;
for tag = ["XCP_ON_UDP_IP", "XCP_ON_TCP_IP"]
    pat = "(/begin " + tag + ".*?/end " + tag + ")";
    blocks = regexp(txt, pat, 'match');
    for k = 1:numel(blocks)
        blk = blocks{k};
        stripped = regexprep(blk, '^[ \t]*HOST_NAME[^\r\n]*\r?\n', '', 'lineanchors');
        if ~strcmp(stripped, blk)
            txt = strrep(txt, blk, stripped);
            nHost = nHost + 1;
        end
    end
end

% --- 2. DAQ -> DAQ_STIM on event channels --------------------------------
% Only inside /begin EVENT blocks; the DAQ direction token there is the 4th
% field. Leave the top-level /begin DAQ section alone.
nEvent = 0;
pattern = '(/begin EVENT.*?/end EVENT)';
blocks = regexp(txt, pattern, 'match');
for k = 1:numel(blocks)
    blk = blocks{k};
    if contains(blk, 'DAQ_STIM')
        continue    % already patched
    end
    patched = regexprep(blk, '(\n\s*)DAQ(\s*\n)', '$1DAQ_STIM$2', 'once');
    if ~strcmp(patched, blk)
        txt = strrep(txt, blk, patched);
        nEvent = nEvent + 1;
    end
end

if strcmp(txt, original)
    fprintf('patch_a2l_for_carmaker: no changes needed (%s)\n', a2lPath);
else
    fid = fopen(a2lPath, 'w');
    fwrite(fid, txt);
    fclose(fid);
end
fprintf('patch_a2l_for_carmaker: removed %d HOST_NAME line(s), set %d EVENT(s) to DAQ_STIM\n', ...
    nHost, nEvent);
end
