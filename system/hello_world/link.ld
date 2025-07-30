ENTRY(_start)
SECTIONS
{
    . = 0x80000000;
    .text : { *(.text.start) *(.text*) }
    .rodata : { *(.rodata*) }
    .data : { *(.data*) }
    .bss : { *(.bss*) }
    _stack_top = . + 0x8000;
}