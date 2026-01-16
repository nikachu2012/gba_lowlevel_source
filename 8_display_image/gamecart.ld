OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")
OUTPUT_ARCH(arm)

MEMORY {
    ewram : ORIGIN = 0x2000000, LENGTH = 256K
    iwram : ORIGIN = 0x3000000, LENGTH = 32K
    rom   : ORIGIN = 0x8000000, LENGTH = 32M
}

SECTIONS {
    .text : {
        *(.header)
        *(.text)
        . = ALIGN(4);
    } > rom

    .rodata : {
        *(.rodata)
    } > rom
    
    .data : {
        __data_start__ = .;
        *(.data)
        __data_end__ = .;
    } > ewram AT > rom

    .bss : {
        __bss_start__ = .;
        *(.bss)
        __bss_end__ = .;
    } > ewram AT > rom

    /* dataセクションのLMAを取得 */    
    __data_rom_start__ = LOADADDR(.data);
}
