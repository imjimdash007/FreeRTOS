MEMORY
{
    FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 256K
    RAM (rwx)  : ORIGIN = 0x20000000, LENGTH = 64K
}

SECTIONS
{
    /* The program code goes into FLASH */
    .text :
    {
        KEEP(*(.isr_vector))
        *(.text)
    } > FLASH

    /* Initialized data goes into RAM */
    .data :
    {
        *(.data*)
    } > RAM

    /* Uninitialized data (and variables set to 0) goes into RAM */
    .bss :
    {
        *(.bss*)
        *(COMMON)
    } > RAM
}