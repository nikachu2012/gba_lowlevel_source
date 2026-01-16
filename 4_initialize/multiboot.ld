OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")
OUTPUT_ARCH(arm)

MEMORY {
    ewram : ORIGIN = 0x2000000, LENGTH = 256K
}

SECTIONS {
    .text : {
        *(.header)
        *(.text)
        . = ALIGN(4);
    } > ewram
}
