MEMORY {
    FLASH(rx) : ORIGIN = 0x00000000, LENGTH = 10K
    RAM(rwx)  : ORIGIN = 0x20000000, LENGTH = 156K
}

SECTIONS {
    .text : {
        *(.isrVector)
        *(.text*)
        *(.rodata*)
    } >FLASH

    .data : {
        *(.data*)
    } >RAM

    .bss : {
        _sbss = .;
        *(.bss*)
        *(COMMON)
        _ebss = .;
    } >RAM
}

_stack_top = ORIGIN(RAM) + LENGTH(RAM);