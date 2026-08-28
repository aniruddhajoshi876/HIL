"""Golden vectors for the internal 0x507 CarMakerDriverSteering transport frame.

Hand-derived from the frame contract in
carmaker/config/MFE26_Inverter_CarMaker.dbc (BO_ 1287) and
VC_HIL/docs/carmaker_fanatec_lws_steering.md. NOT produced by running the
MATLAB decoder (decodeCarMakerSteeringFrame.m) or the CarMaker C sender
(IO.c MFE_SendSteeringFrame) -- those are cross-checked against this file.

Layout (standard 11-bit CAN data frame, DLC 8, Intel/little-endian):
  bytes 0-1  SteeringWheelAngleDeg        int16 LE, 0.1 deg/bit
  bytes 2-3  SteeringWheelSpeedDegPerSec  int16 LE, 0.5 (deg/s)/bit
  bytes 4-5  reserved, must be zero
  byte  6    alive counter, modulo 256 (NOT the physics group counter)
  byte  7    CRC-8/SAE-J1850 over bytes 0-6: poly 0x1D, init 0xFF,
             RefIn=false, RefOut=false, xorout 0xFF
"""
import json


def le16(value):
    value = int(value) & 0xFFFF
    return [value & 0xFF, (value >> 8) & 0xFF]


def crc8_j1850(data):
    crc = 0xFF
    for byte in data:
        crc ^= byte
        for _ in range(8):
            if crc & 0x80:
                crc = ((crc << 1) ^ 0x1D) & 0xFF
            else:
                crc = (crc << 1) & 0xFF
    return crc ^ 0xFF


def hx(data):
    return ' '.join('%02X' % b for b in data)


def frame(name, angle_deg, speed_dps, counter, note='',
          angle_raw=None, speed_raw=None, reserved=(0, 0)):
    if angle_raw is None:
        angle_raw = int(round(angle_deg / 0.1))
    if speed_raw is None:
        speed_raw = int(round(speed_dps / 0.5))
    body = le16(angle_raw) + le16(speed_raw) + [reserved[0], reserved[1],
                                                counter & 0xFF]
    payload = body + [crc8_j1850(body)]
    return dict(name=name, canId='0x507', dlc=8,
                angleDeg=angle_deg, angleCounts=angle_raw,
                speedDegPerSec=speed_dps, speedCounts=speed_raw,
                aliveCounter=counter & 0xFF,
                payloadHex=hx(payload), payloadBytes=payload, note=note)


accepted = [
    frame('cmsteer_centred', 0.0, 0.0, 0, 'straight-ahead, zero rate'),
    frame('cmsteer_one_lsb_angle', 0.1, 0.0, 1,
          'angle LSB = 0.1 deg, matching the Bosch LWS_ANGLE resolution'),
    frame('cmsteer_plus90_left', 90.0, 120.0, 7,
          '900 counts = 0x0384 LE; left-hand-positive (CarMaker / ISO 8855)'),
    frame('cmsteer_minus90_right', -90.0, -120.0, 8,
          'twos-complement -900 = 0xFC7C LE; speed -240 counts = 0xFF10 LE'),
    frame('cmsteer_full_left', 780.0, 0.0, 254,
          'Bosch LWS measuring range +780 deg; TorqueVect saturates here'),
    frame('cmsteer_full_right', -780.0, 0.0, 255,
          'Bosch LWS measuring range -780 deg; counter about to wrap 255->0'),
    frame('cmsteer_counter_wrap', 12.5, 30.0, 0,
          'counter wrapped 255->0; a decoder must treat this as advancing'),
    frame('cmsteer_fast_sweep', 45.0, 1500.0, 3,
          'a fast hand sweep; 3000 speed counts = 0x0BB8 LE. Well within the '
          '+/-3600 deg/s transport range; the LWS packer clamps to 1016.'),
]

rejected = [
    dict(name='cmsteer_reject_short_dlc', canId='0x507', dlc=7,
         payloadHex='00 00 00 00 00 00 00',
         expectation='REJECT wrong_dlc. The frame is always DLC 8.'),
    dict(name='cmsteer_reject_reserved_nonzero', canId='0x507', dlc=8,
         payloadHex=hx(le16(100) + le16(0) + [1, 0, 4]
                       + [crc8_j1850(le16(100) + le16(0) + [1, 0, 4])]),
         expectation='REJECT reserved_nonzero. Byte 4 must be zero; a '
                     'non-zero reserved byte flags a mis-scaled sender.'),
    dict(name='cmsteer_reject_bad_crc', canId='0x507', dlc=8,
         payloadHex=hx(le16(100) + le16(0) + [0, 0, 4, 0x00]),
         expectation='REJECT integrity_failure. Byte 7 is not the '
                     'CRC-8/SAE-J1850 of bytes 0-6.'),
    dict(name='cmsteer_reject_angle_over_range', canId='0x507', dlc=8,
         payloadHex=frame('x', None, 0.0, 1, angle_raw=9000)['payloadHex'],
         expectation='REJECT out_of_range. 9000 counts = 900.0 deg exceeds '
                     'the Bosch +/-780 deg range; the previous retained '
                     'value is kept.'),
    dict(name='cmsteer_reject_wrong_id', canId='0x508', dlc=8,
         payloadHex=frame('x', 0.0, 0.0, 0)['payloadHex'],
         expectation='REJECT wrong_id. Only 0x507 is CarMakerDriverSteering.'),
    dict(name='cmsteer_reject_extended', canId='0x507', dlc=8,
         payloadHex=frame('x', 0.0, 0.0, 0)['payloadHex'], extended=True,
         expectation='REJECT extended_frame. 0x507 is an 11-bit standard ID.'),
]

doc = dict(
    frame='0x507 CarMakerDriverSteering (internal HIL transport, CarMaker -> '
          'SpeedgoatHIL on the CarMaker bus / IO614 channel 1)',
    provisional='CAN ID 0x507 is PROVISIONAL -- no authoritative vehicle-wide '
                'CAN ID registry exists; team approval still required.',
    derivation='Hand-derived from BO_ 1287 in '
               'carmaker/config/MFE26_Inverter_CarMaker.dbc. NOT produced by '
               'running decodeCarMakerSteeringFrame.m or IO.c.',
    byteOrder='little-endian (Intel), matching the physics frames 0x503-0x506',
    scaling='angle 0.1 deg/bit, speed 0.5 (deg/s)/bit, both signed int16',
    integrity='byte 6 alive counter mod 256; byte 7 CRC-8/SAE-J1850 over '
              'bytes 0-6 (poly 0x1D, init 0xFF, non-reflected, xorout 0xFF)',
    signConvention='left-hand-positive (CarMaker / ISO 8855, matching the '
                   'Bosch LWS)',
    downstream='The SpeedgoatHIL LWS emulator, not CarMaker, turns this into '
               'the Bosch LWS 0x2B0 frame. 0x507 never reaches the VC bus.',
    vectors=dict(accepted=accepted, rejected=rejected))

if __name__ == '__main__':
    with open('golden_carmaker_steering.json', 'w') as handle:
        handle.write(json.dumps(doc, indent=2))
    for vector in accepted:
        print('%-26s %s' % (vector['name'], vector['payloadHex']))
