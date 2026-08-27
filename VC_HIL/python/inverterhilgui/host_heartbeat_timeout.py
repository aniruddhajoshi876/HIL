def hostHeartbeatTimeout():
    # MATLAB defaultCalibration currently declares 3.0 s; host cap is 3.0 s.
    return min(3.0, 3.0)
