# Speedgoat / IPG CarMaker status

## Relationship to `inverter_hil`

These are two separate systems that happen to share this PC (and, for the
Speedgoat, its physical hardware):

- `inverter_hil` (this repo) runs on the Speedgoat target `TargetPC1`
  (10.10.10.5, R2024b Simulink Real-Time) and replaces the physical
  Electrophorus Ephorus3 inverter unit, driving the real VCU over IO183/IO614.
- IPG CarMaker (`Documents/GitHub/IPG-MFE`, project `FS_race`) runs on this
  PC directly via `ipg-control.exe` and a CM4SL link into
  `Documents/GitHub/MFE25-Controls`. It does not use the Speedgoat at all.

They are not integrated with each other today. `TargetPC1` was reflashed
between R2022a and R2024b Simulink Real-Time multiple times while setting up
`inverter_hil`; this had no effect on the CarMaker side, since CarMaker never
talks to the Speedgoat. `inverter_hil` is currently loaded and running on
`TargetPC1` as its startup application (survives a target power cycle) --
relevant only if the Speedgoat is ever repurposed for CarMaker-side real-time
work later, since the two would then contend for the same target machine.

## HOW TO USE IPG

The user-confirmed, working procedure for connecting MATLAB/Simulink to the
FS_race CarMaker rig:

```text
1) Open MATLAB R2022a
2) Navigate to Documents/GitHub/MFE25-Controls
3) Select "01 Vehicle Model" and "02 Controls Model" folders, right-click and
   "Add To Path"->"Selected folders and subfolders"
3.1) Open 02 Controls Model/Control_FL_Combined_Run.m
3.2) Run script sections "Model Parameters", "", "", up until "Other
     Controller and Optimization Parameters". By clicking "Run Section" in
     each section.
4) Navigate to Documents/GitHub/IPG-MFE/FCM_Projects/FS_race
5) Select "src_cm4sl", right-click and "Add To Path"->"Selected folders and
   subfolders"
6) Open "src_cm4sl" and right-click on "cmenv.m" and select "Run". If
   prompted, select "change folders". Wait until the command window says
   "Done."
7) Open TorqueVect.mdl
8) Go up all levels by clicking the up arrow in top left
8.1) On the first tab, click "Open CarMaker GUI"
9) In car tab, Select the Examples_FS/MFE24_V3 car
10) Under Application/Cockpit Configuration, select the 2nd FANATEC option
    under the device dropdown and click "enable", ensure Profile is on
    "mfe_setup" and status is "Configured", do not close this window:
    minimize it.
11) Under Parameters/Maneuver, click the car on the top left then the blue
    folder icon
12) Choose your desired track
14) GREEN START MEANS GO ; RED STOP MEANS YOU CRASHED
```

Known non-obvious failure points in this procedure (`cd` variable shadowing,
launching `ipg-control.exe` specifically rather than `CarMaker.win64.exe`,
re-linking CM4SL after any CarMaker restart, `TorqueVect.mdl`'s `PreLoadFcn`
relative-path dependency on `pwd`, missing `kp`/`ki`/`kd`/`N`/
`velocity_lookup`/`ka` workspace variables, stale Simulink diagnostics) are
recorded in this machine's Claude Code memory
(`ipg_carmaker_hil_setup.md`), not duplicated here.

## Open items on the IPG side

1. **`TorqueVect.mdl` has an uncommitted diff** in `IPG-MFE`
   (`FCM_Projects/FS_race/src_cm4sl/TorqueVect.mdl`): 148,220 insertions /
   44,957 deletions, driven by Simulink's re-serialization on save. It
   contains the `fmincon` constraint-shape fix below, plus whatever else the
   re-save touched. Never reviewed or committed.
2. **`PTControl_TV_MFE3` duplicate subsystem is unchecked.** The fix applied
   to `PTControl_TV_MFE25/Full Control Loop/MATLAB Function` --
   `A_ineq = omega*13.39;` to `A_ineq = omega' * 13.39;`, correcting a
   `[4x1]` vs `fmincon`-required `[1x4]` constraint-matrix shape mismatch --
   was only applied to `PTControl_TV_MFE25`. A second, near-duplicate
   subsystem, `PTControl_TV_MFE3`, still has the old unfixed line. Whether
   `PTControl_TV_MFE3` is actually wired into anything active in the current
   car/config has not been checked.
3. **Memory file needs a correction.** `ipg_carmaker_hil_setup.md` point #6
   currently says the fmincon fix "was not yet saved back to the .mdl file on
   disk" -- this is stale; `git status` confirms it was saved (as the
   uncommitted diff in item 1). The memory file also doesn't mention the
   `PTControl_TV_MFE3` duplicate finding from item 2.
