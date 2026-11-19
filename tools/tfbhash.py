import zlib
def name_hash(s: bytes | None) -> int:
    if s is None:
        return 0
    s = bytes(c + 0x20 if 0x41 <= c <= 0x5A else c for c in s)
    return zlib.crc32(s) ^ 0xFFFFFFFF

print(hex(name_hash(b"a")))
print(hex(name_hash(b"PRESCRIPT")))
print(hex(name_hash(b"prescript")))
print(hex(name_hash(b"actor")))
print(hex(name_hash(b"")))
print(hex(name_hash(None)))