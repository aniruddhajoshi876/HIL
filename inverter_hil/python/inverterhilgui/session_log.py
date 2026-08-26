import csv
import math
import os
from .audit_record import auditRecord


class SessionLog:
    MaxRecords = 5000
    def __init__(self):
        self.Records = []; self.Count = 0; self.TotalDropped = 0

    def append(self, info):
        record = auditRecord(info); self.Records.append(record)
        if len(self.Records) > self.MaxRecords:
            excess = len(self.Records) - self.MaxRecords
            del self.Records[:excess]; self.TotalDropped += excess
        self.Count += 1
        return record

    def retainedCount(self): return len(self.Records)
    def snapshot(self): return [dict(item) for item in self.Records]
    @staticmethod
    def columnNames(): return ("hostTime", "targetTimeS", "logicalName", "targetPath", "requested", "applied", "result", "detail")
    @staticmethod
    def _target(value): return f"{value:.3f}" if isinstance(value, (int, float)) and not isinstance(value, bool) and math.isfinite(value) else "--"
    def toLines(self):
        return [f'{r["hostTime"]}  t={self._target(r["targetTimeS"])}  {r["logicalName"]:<28}  req={r["requested"]:<12} app={r["applied"]:<12}  {r["result"]:<9} {r["detail"]}' for r in self.Records]
    def toCell(self):
        return [[r["hostTime"], self._target(r["targetTimeS"]), r["logicalName"], r["targetPath"], r["requested"], r["applied"], r["result"], r["detail"]] for r in self.Records]
    def export(self, fileName):
        try:
            fileName = os.fspath(fileName)
        except TypeError as exc:
            raise ValueError("An export file name is required.") from exc
        if not isinstance(fileName, (str, bytes)) or not fileName: raise ValueError("An export file name is required.")
        with open(fileName, "w", newline="", encoding="utf-8") as stream:
            writer = csv.writer(stream, quoting=csv.QUOTE_ALL, lineterminator="\n")
            writer.writerow(self.columnNames()); writer.writerows(self.toCell())
        return fileName


sessionLog = SessionLog
