ENTRY(loader)

SECTIONS {
    . = 1M;

    .boot :
    {
        /* ensure that the multiboot header is at the beginning */
        *(.mbheader)
    }

    .text :
    {
        *(.text)
    }
}
