<#
.SYNOPSIS
    Deploy the canonical CarMaker-for-Simulink integration sources from this
    HIL repository into a local CarMaker / IPG-MFE project before an R2022a
    CM4SL build.

.DESCRIPTION
    The HIL repository is the single source of truth for the CM4SL integration
    (see carmaker/docs/cm4sl_integration.md). The CarMaker project is a build
    workspace only. This script copies a fixed manifest of files into
    <ProjectPath>\src_cm4sl and never touches anything else.

    Safety:
      * The destination structure is validated before any write.
      * The plan (which files, and their status) is always printed first.
      * A destination file whose contents differ from the canonical version is
        treated as an UNPRESERVED DIFFERENCE and is NOT overwritten unless you
        pass -Force or confirm interactively.
      * Nothing is ever deleted.
      * TorqueVect.mdl is excluded by default (the HIL and IPG copies have
        diverged and need a Simulink model comparison, not a blind copy).
        Pass -IncludeModel to sync it anyway.

.PARAMETER ProjectPath
    Path to the CarMaker project root that contains a 'src_cm4sl' folder,
    e.g.  C:\Users\<you>\Documents\GitHub\IPG-MFE\FCM_Projects\FS_race

.PARAMETER Verify
    Do not copy. Compare canonical vs deployed SHA-256 for every manifest file
    and print a table. Exit code 0 if all match, 1 otherwise.

.PARAMETER IncludeModel
    Also sync TorqueVect.mdl. Off by default - read the reconciliation note in
    carmaker/docs/cm4sl_integration.md first.

.PARAMETER Force
    Overwrite destination files that have unpreserved differences without
    prompting. Use only after you have confirmed the destination changes are
    disposable build-workspace edits.

.PARAMETER DryRun
    Print the plan and exit without writing anything.

.NOTES
    In a non-interactive shell (no console to prompt on) the script prints the
    plan, creates missing files, and REFUSES to overwrite conflicting ones
    unless -Force is given. Nothing is ever deleted.

.EXAMPLE
    .\apply_cm4sl.ps1 -ProjectPath C:\...\IPG-MFE\FCM_Projects\FS_race
        Dry-run plan, then copy the safe files, prompting for any conflicts.

.EXAMPLE
    .\apply_cm4sl.ps1 -ProjectPath C:\...\FS_race -Verify
        Report whether the deployed files match the canonical ones.
#>
[CmdletBinding()]
param(
    [Parameter(Mandatory = $true)]
    [string] $ProjectPath,

    [switch] $Verify,
    [switch] $IncludeModel,
    [switch] $Force,
    [switch] $DryRun
)

$ErrorActionPreference = 'Stop'

function Confirm-Overwrite([string] $FileName) {
    # Returns $true only on an explicit interactive 'y'. Any failure to prompt
    # (non-interactive shell, -NonInteractive, piped host) is treated as 'no'.
    try {
        $ans = Read-Host ("  Overwrite '{0}' in the project? Its current contents will be lost. [y/N]" -f $FileName)
        return ($ans -match '^[Yy]')
    } catch {
        return $false
    }
}

# --- Locate the canonical source directory (repo-relative, no absolute paths) -
$RepoRoot   = (Resolve-Path (Join-Path $PSScriptRoot '..\..')).Path
$CanonDir   = Join-Path $RepoRoot 'carmaker\FS_race\src_cm4sl'
$IntegDoc   = 'carmaker/docs/cm4sl_integration.md'

if (-not (Test-Path $CanonDir)) {
    throw "Canonical source directory not found: $CanonDir  (is this script still under carmaker/deploy/ in the HIL repo?)"
}

# --- Manifest ---------------------------------------------------------------
$Manifest = @(
    'src/IO.c'
    'src/User.c'
    'inc/User.h'
    'Makefile'
)
if ($IncludeModel) { $Manifest += 'vehicle_models/TorqueVect.mdl' }

# --- Validate the destination ---------------------------------------------------
try {
    $ProjectPath = (Resolve-Path $ProjectPath).Path
} catch {
    throw "ProjectPath does not exist: $ProjectPath"
}
$DestDir = Join-Path $ProjectPath 'src_cm4sl'
if (-not (Test-Path $DestDir)) {
    throw "Expected '$DestDir' to exist. Point -ProjectPath at the CarMaker project root that contains a 'src_cm4sl' folder (e.g. ...\IPG-MFE\FCM_Projects\FS_race)."
}
foreach ($sentinel in @('CM_Main.c', 'cmenv.m')) {
    if (-not (Test-Path (Join-Path $DestDir $sentinel))) {
        throw "'$DestDir' does not look like a CM4SL source directory (missing $sentinel). Refusing to write."
    }
}

# --- Helpers ----------------------------------------------------------------
function Get-NormHash([string] $Path) {
    # SHA-256 of the file with CRLF/CR collapsed to LF, so line-ending-only
    # differences are treated as identical.
    if (-not (Test-Path $Path)) { return $null }
    $text  = [System.IO.File]::ReadAllText($Path)
    $norm  = $text -replace "`r`n", "`n" -replace "`r", "`n"
    $bytes = [System.Text.Encoding]::UTF8.GetBytes($norm)
    $sha   = [System.Security.Cryptography.SHA256]::Create()
    try   { ($sha.ComputeHash($bytes) | ForEach-Object { $_.ToString('x2') }) -join '' }
    finally { $sha.Dispose() }
}

function Get-RawHash([string] $Path) {
    if (-not (Test-Path $Path)) { return $null }
    (Get-FileHash -Path $Path -Algorithm SHA256).Hash.ToLower()
}

# --- Build the plan -------------------------------------------------------------
$Plan = foreach ($name in $Manifest) {
    $src = Join-Path $CanonDir $name
    $dst = Join-Path $DestDir (Split-Path $name -Leaf)
    if (-not (Test-Path $src)) { throw "Canonical file missing from the repo: $src" }

    $srcHash = Get-NormHash $src
    $dstHash = Get-NormHash $dst
    $status =
        if     ($null -eq $dstHash)      { 'CREATE' }
        elseif ($srcHash -eq $dstHash)   { 'identical' }
        else                             { 'CONFLICT' }

    [pscustomobject]@{
        File       = (Split-Path $name -Leaf)
        Status     = $status
        Source     = $src
        Dest       = $dst
        SrcRawHash = (Get-RawHash $src)
        DstRawHash = (Get-RawHash $dst)
    }
}

# --- Verify mode --------------------------------------------------------------
if ($Verify) {
    Write-Host ""
    Write-Host "CM4SL deployment verification" -ForegroundColor Cyan
    Write-Host "  canonical : $CanonDir"
    Write-Host "  deployed  : $DestDir"
    Write-Host ""
    $allMatch = $true
    foreach ($row in $Plan) {
        $match = ($row.SrcRawHash -eq $row.DstRawHash)
        $normMatch = ($row.Status -eq 'identical')
        if ($match) {
            Write-Host ("  [ MATCH ] {0}" -f $row.File) -ForegroundColor Green
        } elseif ($normMatch) {
            Write-Host ("  [ ~EOL  ] {0}  (content identical, line endings differ)" -f $row.File) -ForegroundColor Yellow
        } else {
            $allMatch = $false
            $dstShown = if ($row.DstRawHash) { $row.DstRawHash.Substring(0,12) } else { '(absent)' }
            Write-Host ("  [ DIFF  ] {0}  canon {1}  dest {2}" -f $row.File, $row.SrcRawHash.Substring(0,12), $dstShown) -ForegroundColor Red
        }
    }
    Write-Host ""
    if ($allMatch) { Write-Host "All manifest files match." -ForegroundColor Green; exit 0 }
    else           { Write-Host "Deployed files are out of date - run this script without -Verify." -ForegroundColor Red; exit 1 }
}

# --- Print the plan --------------------------------------------------------------
Write-Host ""
Write-Host "CM4SL deployment plan" -ForegroundColor Cyan
Write-Host "  canonical : $CanonDir"
Write-Host "  project   : $DestDir"
Write-Host ""
$Plan | Format-Table File, Status -AutoSize | Out-String | Write-Host

if (-not $IncludeModel) {
    Write-Host "  TorqueVect.mdl is NOT in this sync (diverged - see $IntegDoc). Use -IncludeModel to force it." -ForegroundColor DarkYellow
    Write-Host ""
}

$conflicts = @($Plan | Where-Object Status -eq 'CONFLICT')
$toWrite   = @($Plan | Where-Object Status -eq 'CREATE')

if ($conflicts.Count -gt 0) {
    Write-Host "  $($conflicts.Count) destination file(s) differ from the canonical version (unpreserved differences):" -ForegroundColor Yellow
    foreach ($c in $conflicts) {
        $sl = (Get-Content $c.Source).Count
        $dl = (Get-Content $c.Dest).Count
        Write-Host ("     - {0}   canonical {1} lines / deployed {2} lines" -f $c.File, $sl, $dl)
    }
    Write-Host ""
    if ($DryRun) {
        Write-Host "  -DryRun: no files written. Re-run without -DryRun to apply." -ForegroundColor DarkGray
    } elseif ($Force) {
        Write-Host "  -Force given: overwriting all conflicts." -ForegroundColor Red
        $toWrite += $conflicts
    } else {
        $anySkipped = $false
        foreach ($c in $conflicts) {
            if (Confirm-Overwrite $c.File) {
                $toWrite += $c
            } else {
                Write-Host ("  skipped {0} (kept the project's copy)" -f $c.File) -ForegroundColor DarkGray
                $anySkipped = $true
            }
        }
        if ($anySkipped) {
            Write-Host "  To overwrite skipped files: re-run in an interactive shell, or pass -Force." -ForegroundColor Yellow
        }
    }
    Write-Host ""
}

if ($DryRun) {
    Write-Host "-DryRun: plan only, no files written." -ForegroundColor Cyan
    Write-Host ""
    exit 0
}

# --- Copy ----------------------------------------------------------------------
if ($toWrite.Count -eq 0) {
    Write-Host "Nothing to do - the project already matches the canonical sources." -ForegroundColor Green
} else {
    foreach ($row in $toWrite) {
        Copy-Item -LiteralPath $row.Source -Destination $row.Dest -Force
        Write-Host ("  wrote {0}" -f $row.File) -ForegroundColor Green
    }
}

# --- Next steps --------------------------------------------------------------
Write-Host ""
Write-Host "Next - R2022a CM4SL build" -ForegroundColor Cyan
Write-Host "  1. Open MATLAB R2022a."
Write-Host "  2. Add $ProjectPath\src_cm4sl to the path and run cmenv.m (choose 'change folder'; wait for 'Done.')."
Write-Host "  3. If TorqueVect.mdl was changed, open it and save through Simulink, then run the"
Write-Host "     ModelUpdate publish step if the CM4SL workflow requires it."
Write-Host "  4. Build:  the 'CarMaker for Simulink.sln' solution, OR  make -C $ProjectPath\src_cm4sl"
Write-Host "     (do NOT use the R2024b environment used for inverter_hil)."
Write-Host "  5. Re-run this script with -Verify to confirm the deployed files match."
Write-Host ""
Write-Host "  Full procedure, and the nine TorqueVect.mdl Read/Write CM Dict passthroughs:"
Write-Host "    $IntegDoc  and  carmaker/docs/carmaker_readcmdict_checklist.md"
Write-Host ""
