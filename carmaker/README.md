# carmaker/

CarMaker-side assets for the CarMaker ↔ Speedgoat HIL bench. **This repository
is the source of truth** for the CarMaker-for-Simulink (CM4SL) integration; the
local `IPG-MFE/FCM_Projects/FS_race` project is a build/deploy workspace only —
never commit the integration there.

| Path | What |
|---|---|
| `FS_race/src_cm4sl/` | Canonical CM4SL workspace. C sources are in `src/`, headers in `inc/`, and vehicle models/parameters in `vehicle_models/`; build and model-update files remain at the root. |
| `config/MFE26_Inverter_CarMaker.dbc` | The two-bus CAN contract (`0x500`-`0x506`, sensor and inverter frames). |
| `deploy/apply_cm4sl.ps1` | Copies the canonical CM4SL sources from `src/` and `inc/` into a CarMaker project before a CM4SL build. Safe: shows a plan, refuses to clobber unpreserved changes, never deletes. `-Verify` checks a deployed project. |
| `docs/cm4sl_integration.md` | **Start here.** How it fits together, how to deploy, rebuild in R2022a, wire the CarMaker physics passthroughs, enable/disable CarMaker-as-truth. |
| `docs/carmaker_readcmdict_checklist.md` | R2022a step-by-step for the nine `Read CM Dict → Write CM Dict` passthroughs. |
| `docs/can_setup_walkthrough.md`, `docs/ipg_hil_bringup.md` | Bus topology and PCAN/RBS bring-up. |

Design plan for the CarMaker-as-IMU-truth feature:
`VC_HIL/docs/carmaker_imu_truth_source_plan.md`.

## Deploy in one line

```powershell
carmaker\deploy\apply_cm4sl.ps1 -ProjectPath C:\path\to\IPG-MFE\FCM_Projects\FS_race
```
