.global _ProggyClean_start
.global _ProggyClean_end
.global _ProggyClean_size

_ProggyClean_start:
    .incbin "ProggyClean.bin"
_ProggyClean_end:
    .set _ProggyClean_size, _ProggyClean_end - _ProggyClean_start
