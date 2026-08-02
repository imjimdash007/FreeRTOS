MEMORY
{
    FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 256K
    RAM (rwx)  : ORIGIN = 0x20000000, LENGTH = 64K
}

SECTIONS
{
    .text :
    {
        KEEP(*(.isr_vector))
        *(.text*)
        *(.rodata*) /* Good practice to include read-only data here too */
    } > FLASH

    .data :
    {
        *(.data*)
    } > RAM

    .bss :
    {
        /* Tell the C library exactly where BSS starts */
        __bss_start__ = .; 
        
        *(.bss*)
        *(COMMON)
        
        /* Tell the C library exactly where BSS ends */
        __bss_end__ = .;   
    } > RAM

    /* Tell the C library where the heap can start (immediately after BSS) */
    PROVIDE(end = .);
}