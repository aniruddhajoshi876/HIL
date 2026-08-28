# ControlsMFE25 provenance

The generated model files in this directory were copied from
`MFE26-VC/Drivers/Controls_model` at controls commit
`bcd6352e1674ef4b999391f345f675f386718d32`.

Exact pinned-file SHA-256 values:

| File | SHA-256 |
|---|---|
| `ControlsMFE25.c` | `58D19A1E7C54D72066FFDD12EE0C35774C6AD2AC960855A83DBCC53DEBDB6B41` |
| `ControlsMFE25.h` | `A29B3B16D6B6048AD869A85C37592CC041CD65FD91CE5D32A7704A8B94DA3BED` |
| `ControlsMFE25_data.c` | `E9F57B6D8AA332D389A820E6418AB94682A203BDEB6E80272D23913AB5A3C1ED` |
| `ControlsMFE25_private.h` | `227902CA7E1595F874B253741B03467FD165D004D763EC935E051AD49AD52A1C` |
| `ControlsMFE25_types.h` | `0BFA583FDD6E404FFF00D59726809F284683AD84C23639B51C4B049FC7900F21` |
| `rtwtypes.h` | `6260BD368CB7327DE07D737D6F2088FD49EFE77881F839ACF261B1E795FD9F8C` |

`coder_posix_time.c/.h` are the sole platform-adapter substitutions. The
firmware copy depends on STM32 TIM2/HAL and cannot compile for Windows MEX or
Speedgoat. The replacement is a **deliberate no-op stub**: `coderInitTimeFunctions`
sets `freq = 1.0` and `coderTimeClockGettimeMonotonic` returns constant zeros,
with no syscall. `ControlsMFE25.c` calls `ControlsMFE25_toc` once per step
(line 6806 at commit `bcd6352`) and discards the return; the timekeeper's only
state (`savedTime`, `DW->freq*`) is read solely by the timing functions
themselves, so constant zeros cannot change allocator outputs or state
evolution. Restore a real `clock_gettime`/`clock()` body (preserved in git
history) only if a future allocator revision starts consuming the `toc` value.
`vvcu_controls_wrapper.*` and `vvcu_controls_mex.c` are HIL integration files,
not generated model files.
