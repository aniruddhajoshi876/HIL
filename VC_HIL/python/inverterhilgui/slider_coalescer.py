import math


class SliderCoalescer:
    def __init__(self, rateS=0.030):
        if not isinstance(rateS, (int, float)) or isinstance(rateS, bool) or not math.isfinite(rateS) or not 0.020 <= rateS <= 0.050:
            raise ValueError("Host update rate must be within 0.020-0.050 s.")
        self.RateS = float(rateS); self.HasPending = False; self.PendingValue = None
        self.LastEmitS = -math.inf; self.EmittedCount = 0; self.DroppedCount = 0

    @staticmethod
    def _time(now):
        if not isinstance(now, (int, float)) or isinstance(now, bool) or not math.isfinite(now): raise ValueError("Host time must be finite.")
        return float(now)

    def _emit(self, now):
        out = {"hasValue": False, "value": None, "timeS": math.nan}
        if self.HasPending and now - self.LastEmitS >= self.RateS:
            out.update(hasValue=True, value=self.PendingValue, timeS=now)
            self.HasPending = False; self.PendingValue = None; self.LastEmitS = now; self.EmittedCount += 1
        return out

    def submit(self, value, nowS):
        now = self._time(nowS)
        if not isinstance(value, (int, float, bool)) or isinstance(value, complex) or not math.isfinite(float(value)):
            raise ValueError("Coalesced values must be finite scalars.")
        if self.HasPending: self.DroppedCount += 1
        self.PendingValue = value; self.HasPending = True
        return self._emit(now)

    def poll(self, nowS): return self._emit(self._time(nowS))

    def reset(self):
        if self.HasPending: self.DroppedCount += 1
        self.HasPending = False; self.PendingValue = None


sliderCoalescer = SliderCoalescer
