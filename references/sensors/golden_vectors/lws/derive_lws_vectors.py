import json

def le16(v):
    v = int(v) & 0xFFFF
    return [v & 0xFF, (v >> 8) & 0xFF]

def hx(b):
    return ' '.join('%02X' % x for x in b)

def std(name, angle_deg, speed_dps, trim, cal, ok, note='', angle_raw=None, speed_raw=None):
    if angle_raw is None:
        angle_raw = int(round(angle_deg / 0.1))
    if speed_raw is None:
        speed_raw = int(round(speed_dps / 4.0))
    status = (0x04 if trim else 0) | (0x02 if cal else 0) | (0x01 if ok else 0)
    payload = le16(angle_raw) + [speed_raw & 0xFF, status, 0x00]
    return dict(name=name, canId='0x2B0', dlc=5,
                angleDeg=angle_deg, angleCounts=angle_raw,
                speedDegPerS=speed_dps, speedCounts=speed_raw,
                status=dict(TRIM=trim, CAL=cal, OK=ok, byte3='0x%02X' % status),
                payloadHex=hx(payload), payloadBytes=payload, note=note)

vec = [
 std('lws_centred_still', 0.0, 0.0, 1, 1, 1, 'nominal calibrated zero'),
 std('lws_one_lsb_angle', 0.1, 0.0, 1, 1, 1, 'angle LSB = 0.1 deg (datasheet "Absolute physical resolution")'),
 std('lws_plus90_100dps', 90.0, 100.0, 1, 1, 1, '900 counts = 0x0384, little-endian on the wire'),
 std('lws_minus90_100dps', -90.0, 100.0, 1, 1, 1, 'twos-complement -900 = 0xFC7C, little-endian'),
 std('lws_full_left', 780.0, 0.0, 1, 1, 1, 'datasheet measuring range +780 deg'),
 std('lws_full_right', -780.0, 0.0, 1, 1, 1, 'datasheet measuring range -780 deg'),
 std('lws_speed_508dps', 0.0, 508.0, 1, 1, 1, 'speed count 127 = 0x7F, the last value that survives an int8 cast'),
 std('lws_speed_512dps', 0.0, 512.0, 1, 1, 1, 'speed count 128 = 0x80. LWS_SPEED is UNSIGNED; an int8 receiver reads -128 here. First value that breaks a signed receiver.'),
 std('lws_speed_max_1016dps', 0.0, 1016.0, 1, 1, 1, 'speed count 254 = 0xFE, top of the documented 0..1016 deg/s range. An int8 receiver reads -2.'),
 std('lws_uncalibrated', None, 200.0, 1, 0, 1,
     'Truth table row TRIM=1 OK=1 CAL=0: LWS_ANGLE is forced to the 0x7FFF sentinel, LWS_SPEED stays valid.',
     angle_raw=0x7FFF),
 std('lws_failure_trim_only', None, None, 1, 0, 0,
     'Truth table row TRIM=1 OK=0 CAL=0: angle 0x7FFF, speed 0xFF, sensor in failure mode.',
     angle_raw=0x7FFF, speed_raw=0xFF),
 std('lws_failure_all_clear', None, None, 0, 0, 0,
     'Truth table row TRIM=0 OK=0 CAL=0: angle 0x7FFF, speed 0xFF, sensor in failure mode.',
     angle_raw=0x7FFF, speed_raw=0xFF),
]

invalid = [
 dict(name='lws_invalid_short_dlc', canId='0x2B0', dlc=4, payloadHex='00 00 00 07',
      expectation='REJECT. LWS_Standard is a 5-byte message (Bosch F02U.V02.894-01, CAN Message table).'),
 dict(name='lws_invalid_long_dlc', canId='0x2B0', dlc=8, payloadHex='84 03 19 07 00 00 00 00',
      expectation='REJECT or accept-first-5 - the datasheet fixes the length at 5 and says nothing about padding. The MFE26-VC driver requires length == 5 exactly, so a simulator MUST emit DLC 5.'),
 dict(name='lws_invalid_status_combo_010', canId='0x2B0', dlc=5, payloadHex='84 03 19 02 00',
      expectation='REJECT. TRIM=0 CAL=1 OK=0 is listed under "Other combinations for TRIM, OK and CAL are not valid".'),
 dict(name='lws_invalid_status_combo_011', canId='0x2B0', dlc=5, payloadHex='84 03 19 03 00',
      expectation='REJECT. TRIM=0 CAL=1 OK=1 is not a valid combination.'),
 dict(name='lws_unknown_id', canId='0x2B1', dlc=5, payloadHex='84 03 19 07 00',
      expectation='IGNORE. Only 0x2B0 (LWS_Standard) and 0x7C0 (LWS_Config) are defined.'),
 dict(name='lws_endianness_probe', canId='0x2B0', dlc=5, payloadHex='03 84 19 07 00',
      expectation='A correct little-endian receiver decodes 0x8403 = -31741 counts = -3174.1 deg, far outside the +/-780 deg range. A wrongly big-endian receiver decodes 900 counts = +90.0 deg.',
      note='Byte-swapped twin of lws_plus90_100dps. Use it to prove byte order on real hardware.'),
 dict(name='lws_config_zero_angle', canId='0x7C0', dlc=2, payloadHex='03 00',
      expectation='LWS_Config, CCW = 3h, sets LWS_Angle to 0 deg. VCU-to-sensor direction.'),
 dict(name='lws_config_reset_calibration', canId='0x7C0', dlc=2, payloadHex='05 00',
      expectation='LWS_Config, CCW = 5h, resets the calibration status of the angle. VCU-to-sensor direction.'),
]

doc = dict(
  contract='Bosch Motorsport Steering Wheel Angle Sensor LWS, order number F02U.V02.894-01',
  sourceDocument='Bosch Motorsport datasheet "Steering Wheel Angle Sensor LWS", document 54425995, en, 26 Aug 2025',
  derivation='Hand-derived from the Bosch datasheet tables only. NOT produced by running or transcribing the MFE26-VC LWSSteering decoder or the inverter_hil packLws encoder.',
  byteOrder='little-endian ("Byte order LSB (Intel)", CAN Parameters table). Explicitly stated by the datasheet, unlike the MTi.',
  bitrate='500 kbaud (stated twice: Electrical Data and CAN Parameters)',
  updateRate='100 Hz / 10 ms (CAN Parameters table)',
  layout='byte 0-1 LWS_ANGLE int16 LE, byte 2 LWS_SPEED uint8, byte 3 bit2 TRIM / bit1 CAL / bit0 OK with bits 7:3 reserved, byte 4 reserved',
  scaling='LWS_ANGLE 0.1 deg/count, LWS_SPEED 4 deg/s per count. See mti680_can_contract.md ASSUMPTION A7: the datasheet gives these as "Absolute physical resolution", not as an explicit LSB scaling.',
  invalidSentinels='LWS_ANGLE = 0x7FFF and LWS_SPEED = 0xFF whenever the truth table says the value is not valid',
  vectors=dict(standardFrames=vec, invalidAndEdge=invalid))

open('golden_lws.json', 'w').write(json.dumps(doc, indent=2))
for v in vec:
    print('%-28s %s' % (v['name'], v['payloadHex']))
