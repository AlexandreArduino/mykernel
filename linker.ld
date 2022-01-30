ENTRY(_start)

SECTIONS
{
    kernel_phys_offset = 0xffffffff80100000;
    . = kernel_phys_offset;
    
    .stivale2hdr ALIGN(4K):
    {
        KEEP(*(.stivale2hdr))
    }
    
    .text ALIGN(4K):
    {
        *(.text*)
    }
    
    .rodata ALIGN(4K):
    {
        *(.rodata*)
    }
    
    .data  ALIGN(4K):
    {
        *(.data*)
    }
    
    .bss  ALIGN(4K) :
    {
        *(COMMON)
        *(.bss*)
    }
}