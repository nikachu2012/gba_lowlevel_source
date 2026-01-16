# game title must be 12 bytes (not use bytes fill 00h)
game_title = ('\x00' * 12).encode()

# game code must be 4 bytes 
game_code = ('\x00' * 4).encode()

maker_code = ('\x00' * 2).encode()

unit_code = bytes([0x00])

device_type = bytes([0x00])

software_version = bytes([0x00])

header = game_title + game_code + maker_code + bytes([0x96]) + unit_code + device_type + bytes([0x00] * 7) + software_version

assert len(header) == 29

chk = 0
for i in header:
    chk = chk - i
chk = (chk-0x19) & 0xff

print(hex(chk))
