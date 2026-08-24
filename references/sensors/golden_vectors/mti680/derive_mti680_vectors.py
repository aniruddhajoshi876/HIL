import json, math

def be16(v):
    v = int(v) & 0xFFFF
    return [(v >> 8) & 0xFF, v & 0xFF]

def rnd(q):
    return int(math.floor(q + 0.5)) if q >= 0 else int(math.ceil(q - 0.5))

def vec6(vals, scale):
    out = []
    counts = []
    for x in vals:
        c = rnd(x / scale)
        assert -32768 <= c <= 32767, (x, c)
        counts.append(c)
        out += be16(c)
    return counts, out

def hx(b):
    return ' '.join('%02X' % v for v in b)

def mk(name, kind, canid, dlc, scale, unit, fields, vals, note=''):
    counts, payload = vec6(vals, scale)
    return dict(name=name, message=kind, canId=canid, dlc=dlc,
                fields=fields, unit=unit, scale=scale,
                physicalIn=vals,
                rawCounts=counts,
                decodedBack=[c * scale for c in counts],
                payloadHex=hx(payload), payloadBytes=payload, note=note)

ACC = '0x034'; ROT = '0x032'; EUL = '0x022'; VEL = '0x076'
Sa = 2 ** -8; Sg = 2 ** -9; Se = 2 ** -7; Sv = 2 ** -6
FA = ['accX', 'accY', 'accZ']; FG = ['gyrX', 'gyrY', 'gyrZ']
FE = ['roll', 'pitch', 'yaw']; FV = ['velX', 'velY', 'velZ']

acc = [
 mk('acc_zero', 'XCDI_Acceleration', ACC, 6, Sa, 'm/s^2', FA, [0.0, 0.0, 0.0]),
 mk('acc_one_lsb_x', 'XCDI_Acceleration', ACC, 6, Sa, 'm/s^2', FA, [2 ** -8, 0.0, 0.0], 'one LSB = 0.00390625 m/s^2'),
 mk('acc_static_gravity_z', 'XCDI_Acceleration', ACC, 6, Sa, 'm/s^2', FA, [0.0, 0.0, 9.81], '9.81 is not representable; nearest count 2511 decodes to 9.80859375'),
 mk('acc_neg_unit_x', 'XCDI_Acceleration', ACC, 6, Sa, 'm/s^2', FA, [-1.0, 0.0, 0.0], 'twos-complement negative'),
 mk('acc_mixed', 'XCDI_Acceleration', ACC, 6, Sa, 'm/s^2', FA, [1.5, -2.25, 9.80859375], 'all three axes, exactly representable counts'),
 mk('acc_doc_range_max', 'XCDI_Acceleration', ACC, 6, Sa, 'm/s^2', FA, [100.0, 100.0, 100.0], 'doc Range column +/-100 m/s^2 (MT1604P section 6.4.4)'),
 mk('acc_doc_range_min', 'XCDI_Acceleration', ACC, 6, Sa, 'm/s^2', FA, [-100.0, -100.0, -100.0], 'doc Range column +/-100 m/s^2'),
 mk('acc_int16_max', 'XCDI_Acceleration', ACC, 6, Sa, 'm/s^2', FA, [32767 * Sa] * 3, 'int16 saturation 0x7FFF = 127.99609375 m/s^2, ABOVE the documented +/-100 range'),
 mk('acc_int16_min', 'XCDI_Acceleration', ACC, 6, Sa, 'm/s^2', FA, [-32768 * Sa] * 3, 'int16 saturation 0x8000 = -128.0 m/s^2, BELOW the documented -100 range'),
 mk('acc_rounding', 'XCDI_Acceleration', ACC, 6, Sa, 'm/s^2', FA, [0.006, -0.006, 0.0], '0.006/2^-8 = 1.536, rounds to 2 counts; sign symmetric'),
]
rot = [
 mk('rot_zero', 'XCDI_RateOfTurn', ROT, 6, Sg, 'rad/s', FG, [0.0, 0.0, 0.0]),
 mk('rot_one_lsb_z', 'XCDI_RateOfTurn', ROT, 6, Sg, 'rad/s', FG, [0.0, 0.0, 2 ** -9], 'one LSB = 0.001953125 rad/s'),
 mk('rot_yaw_1radps', 'XCDI_RateOfTurn', ROT, 6, Sg, 'rad/s', FG, [0.0, 0.0, 1.0]),
 mk('rot_yaw_neg1radps', 'XCDI_RateOfTurn', ROT, 6, Sg, 'rad/s', FG, [0.0, 0.0, -1.0]),
 mk('rot_mixed', 'XCDI_RateOfTurn', ROT, 6, Sg, 'rad/s', FG, [0.1, -0.25, 2.5], '0.1 rad/s is not representable; 51.2 rounds to 51 counts'),
 mk('rot_doc_range_max', 'XCDI_RateOfTurn', ROT, 6, Sg, 'rad/s', FG, [35.0, 35.0, 35.0], 'doc Range column +/-35 rad/s (MT1604P section 6.4.2)'),
 mk('rot_doc_range_min', 'XCDI_RateOfTurn', ROT, 6, Sg, 'rad/s', FG, [-35.0, -35.0, -35.0]),
 mk('rot_int16_max', 'XCDI_RateOfTurn', ROT, 6, Sg, 'rad/s', FG, [32767 * Sg] * 3, '0x7FFF = 63.998046875 rad/s, ABOVE documented +/-35'),
 mk('rot_int16_min', 'XCDI_RateOfTurn', ROT, 6, Sg, 'rad/s', FG, [-32768 * Sg] * 3, '0x8000 = -64.0 rad/s'),
]
eul = [
 mk('euler_zero', 'XCDI_EulerAngles', EUL, 6, Se, 'deg', FE, [0.0, 0.0, 0.0]),
 mk('euler_one_lsb_roll', 'XCDI_EulerAngles', EUL, 6, Se, 'deg', FE, [2 ** -7, 0.0, 0.0], 'one LSB = 0.0078125 deg'),
 mk('euler_roll90', 'XCDI_EulerAngles', EUL, 6, Se, 'deg', FE, [90.0, 0.0, 0.0]),
 mk('euler_pitch_neg45', 'XCDI_EulerAngles', EUL, 6, Se, 'deg', FE, [0.0, -45.0, 0.0]),
 mk('euler_yaw180', 'XCDI_EulerAngles', EUL, 6, Se, 'deg', FE, [0.0, 0.0, 180.0], 'doc Range +/-180 deg for roll and yaw, +/-90 for pitch'),
 mk('euler_yaw_neg180', 'XCDI_EulerAngles', EUL, 6, Se, 'deg', FE, [0.0, 0.0, -180.0]),
 mk('euler_mixed', 'XCDI_EulerAngles', EUL, 6, Se, 'deg', FE, [12.5, -3.25, -90.0]),
 mk('euler_int16_max', 'XCDI_EulerAngles', EUL, 6, Se, 'deg', FE, [32767 * Se] * 3, '0x7FFF = 255.9921875 deg, outside every documented Euler range'),
 mk('euler_int16_min', 'XCDI_EulerAngles', EUL, 6, Se, 'deg', FE, [-32768 * Se] * 3, '0x8000 = -256.0 deg'),
]
VU = 'm/s (unit ASSUMED, see ASSUMPTION A4; MT1604P Unit column is a dash)'
vel = [
 mk('vel_zero', 'XCDI_VelocityXYZ', VEL, 6, Sv, VU, FV, [0.0, 0.0, 0.0]),
 mk('vel_one_lsb_x', 'XCDI_VelocityXYZ', VEL, 6, Sv, VU, FV, [2 ** -6, 0.0, 0.0], 'one LSB = 0.015625'),
 mk('vel_20_x', 'XCDI_VelocityXYZ', VEL, 6, Sv, VU, FV, [20.0, 0.0, 0.0]),
 mk('vel_neg20_x', 'XCDI_VelocityXYZ', VEL, 6, Sv, VU, FV, [-20.0, 0.0, 0.0]),
 mk('vel_mixed', 'XCDI_VelocityXYZ', VEL, 6, Sv, VU, FV, [27.5, -1.25, 0.0625]),
 mk('vel_doc_range_max', 'XCDI_VelocityXYZ', VEL, 6, Sv, VU, FV, [500.0, 500.0, 500.0], 'doc Range +/-500 (MT1604P section 6.8.3); 32000 counts, still inside int16'),
 mk('vel_doc_range_min', 'XCDI_VelocityXYZ', VEL, 6, Sv, VU, FV, [-500.0, -500.0, -500.0]),
 mk('vel_int16_max', 'XCDI_VelocityXYZ', VEL, 6, Sv, VU, FV, [32767 * Sv] * 3, '0x7FFF = 511.984375, ABOVE documented +/-500'),
]

def scalar(name, msg, canid, dlc, fmt, val, nbytes, note=''):
    b = [(int(val) >> (8 * (nbytes - 1 - i))) & 0xFF for i in range(nbytes)]
    return dict(name=name, message=msg, canId=canid, dlc=dlc, format=fmt,
                valueIn=int(val), payloadHex=hx(b), payloadBytes=b, note=note)

scal = [
 scalar('groupcounter_zero', 'XCID_GroupCounter', '0x006', 2, 'uint16', 0, 2),
 scalar('groupcounter_one', 'XCID_GroupCounter', '0x006', 2, 'uint16', 1, 2),
 scalar('groupcounter_0x1234', 'XCID_GroupCounter', '0x006', 2, 'uint16', 0x1234, 2),
 scalar('groupcounter_wrap', 'XCID_GroupCounter', '0x006', 2, 'uint16', 65535, 2, 'next frame wraps to 0'),
 scalar('sampletime_zero', 'XCID_SampleTime', '0x005', 4, 'uint32 microseconds', 0, 4),
 scalar('sampletime_1s', 'XCID_SampleTime', '0x005', 4, 'uint32 microseconds', 1000000, 4, '1 s = 1e6 us'),
 scalar('sampletime_max', 'XCID_SampleTime', '0x005', 4, 'uint32 microseconds', 0xFFFFFFFF, 4, 'wraps after ~4295 s'),
 scalar('statusword_zero', 'XCDI_StatusWord', '0x011', 4, 'uint32', 0, 4),
 scalar('statusword_bit0', 'XCDI_StatusWord', '0x011', 4, 'uint32', 1, 4, 'bit meanings are defined in the MT Low Level doc, not in MT1604P'),
 scalar('error_buffer_overflow', 'XCID_Error', '0x001', 1, 'uint8', 0x01, 1, 'CEI_OutputBufferOverflow, MT1604P section 6.1.1'),
]

q = []
def quat(name, vals, note=''):
    cs = []; pl = []
    for x in vals:
        c = rnd(x * 32767)
        cs.append(c); pl += be16(c)
    q.append(dict(name=name, message='XCDI_Quaternion', canId='0x021', dlc=8,
        fields=['q0', 'q1', 'q2', 'q3'], scale='1/(2^15-1) = 1/32767',
        physicalIn=vals, rawCounts=cs, decodedBack=[c / 32767 for c in cs],
        payloadHex=hx(pl), payloadBytes=pl, note=note))
quat('quat_identity', [1.0, 0.0, 0.0, 0.0], 'doc note "Be careful when converting the value 1"; 1.0*32767 = 0x7FFF exactly')
quat('quat_45deg_yaw', [0.9238795325112867, 0.0, 0.0, 0.3826834323650898])
quat('quat_neg_identity', [-1.0, 0.0, 0.0, 0.0], '-1.0*32767 = -32767 = 0x8001, NOT 0x8000')

invalid = [
 dict(name='invalid_short_dlc_accel', canId='0x034', dlc=4, payloadHex='00 00 09 CF',
      expectation='REJECT. XCDI_Acceleration Total size is 6 (MT1604P section 6.4.4). A 4-byte frame cannot carry three int16 fields.',
      note='The simulator must never emit this; a receiver must not update state from it.'),
 dict(name='invalid_short_dlc_rot', canId='0x032', dlc=2, payloadHex='02 00',
      expectation='REJECT. XCDI_RateOfTurn Total size is 6 (MT1604P section 6.4.2).'),
 dict(name='invalid_zero_dlc_accel', canId='0x034', dlc=0, payloadHex='',
      expectation='REJECT. Zero-length data frame on an XCDI id carries no fields.'),
 dict(name='edge_overlong_dlc_accel', canId='0x034', dlc=8, payloadHex='00 00 00 00 09 CF DE AD',
      expectation='ACCEPT the first 6 bytes, IGNORE bytes 6 and 7. MT1604P fixes Total size 6; trailing bytes are outside the contract.',
      note='Not something a real MTi emits. Included to pin receiver behaviour when a HIL simulator pads to DLC 8.'),
 dict(name='invalid_unknown_id', canId='0x100', dlc=6, payloadHex='00 00 00 00 00 00',
      expectation='IGNORE. 0x100 is not an XCDI message id in MT1604P section 6.'),
 dict(name='invalid_unknown_id_near_miss', canId='0x033', dlc=6, payloadHex='00 00 00 00 00 00',
      expectation='IGNORE as an acceleration frame. 0x033 is XCDI_DeltaQ (Total size 8), not Acceleration.',
      note='0x033 sits between RateOfTurn 0x032 and Acceleration 0x034; a range-based CAN filter must not conflate them.'),
 dict(name='edge_accel_beyond_doc_range', canId='0x034', dlc=6, payloadHex='7F FF 7F FF 7F FF',
      expectation='DECODES to 127.99609375 m/s^2 per axis. The encoding is a legal int16; the value lies outside the documented +/-100 m/s^2 Range. A receiver that range-guards will discard the whole frame.',
      note='This case separates "decodable" from "acceptable".'),
 dict(name='edge_rot_beyond_doc_range', canId='0x032', dlc=6, payloadHex='7F FF 7F FF 7F FF',
      expectation='DECODES to 63.998046875 rad/s per axis, outside the documented +/-35 rad/s Range.'),
 dict(name='edge_all_ones', canId='0x034', dlc=6, payloadHex='FF FF FF FF FF FF',
      expectation='DECODES to -0.00390625 m/s^2 on all axes (int16 -1). MT1604P defines NO all-ones invalid sentinel for CAN output messages.',
      note='Explicitly NOT an invalid marker. Unlike the Bosch LWS, the MTi CAN protocol has no per-message data-invalid sentinel; invalidity is signalled out of band by XCDI_StatusWord (0x011) and XCID_Error (0x001).'),
 dict(name='edge_bosch_style_sentinel_is_not_special', canId='0x034', dlc=6, payloadHex='7F FF 00 00 00 00',
      expectation='DECODES accX = 127.99609375 m/s^2. 0x7FFF is the Bosch LWS invalid-angle sentinel; it carries no such meaning on the MTi bus.'),
 dict(name='edge_little_endian_confusion_probe', canId='0x034', dlc=6, payloadHex='CF 09 00 00 00 00',
      expectation='A big-endian receiver decodes accX = -12543 counts = -48.99609375 m/s^2. A little-endian receiver decodes +2511 counts = +9.80859375 m/s^2.',
      note='Diagnostic frame: byte-swapped twin of acc_static_gravity_z on the X axis. Use it to prove endianness end to end on real hardware rather than assuming it.'),
]

doc = dict(
  contract='Xsens MTi 600-series MT CAN output messages',
  sourceDocument='Xsens MT CAN Protocol Documentation, document MT1604P, Revision A, 16 Sept 2019 (page footers read "Document MT0101P.2019.A")',
  derivation='Hand-derived from the MT1604P tables only. NOT produced by running, importing or transcribing the MFE26-VC MTi680G_driver decoder or the inverter_hil imuProtocol/packMti680 encoder. Both of those are units under test.',
  byteOrder='big-endian (MSB first) within each multi-byte field. NOTE: MT1604P does not state this for CAN output payloads; it is carried over from MT Low Level Communication Protocol Documentation section 5.1.1, "All binary data communication is done in big-endian format". See mti680_can_contract.md ASSUMPTION A1.',
  fieldOrder='fields are laid out at the byte offsets given in the MT1604P tables, first field at offset 0',
  roundingRule='round half away from zero, then twos complement',
  idFormat='11-bit standard identifiers as listed in MT1604P section 6. Both the identifier value and the 11-vs-29-bit format are user-configurable via SetCanOutputConfig (MID 0xE8).',
  vectors=dict(acceleration=acc, rateOfTurn=rot, eulerAngles=eul, velocityXYZ=vel,
               scalarMessages=scal, quaternion=q, invalidAndEdge=invalid))

open('golden.json', 'w').write(json.dumps(doc, indent=2))
for grp in (acc, rot, eul, vel):
    for v in grp:
        print('%-32s %-20s counts=%s' % (v['name'], v['payloadHex'], v['rawCounts']))
for v in scal + q:
    print('%-32s %s' % (v['name'], v['payloadHex']))
