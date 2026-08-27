"""Strictly read-only MATLAB Engine -> SLRT target smoke test.

This script deliberately has no setparam/load/start/stop/reset calls.
"""

from pprint import pprint
from inverterhilgui.matlab_engine_backend import MatlabEngineBackend


def main():
    backend = MatlabEngineBackend("TargetPC1")
    backend.connect()
    print(f"isConnected={backend.isConnected()}")
    print(f"targetName={backend.targetName()}")
    print(f"applicationState={backend.applicationState()}")
    print(f"currentApplicationName={backend.currentApplicationName()}")
    print(f"executionTimeS={backend.executionTimeS()}")
    paths = backend.availableParameters()
    print(f"availableParameters.count={len(paths)}")
    round_trips = {path: backend.getparam(path) for path in paths}
    pprint(round_trips)


if __name__ == "__main__":
    main()
