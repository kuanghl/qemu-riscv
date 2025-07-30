ENTRY(_start)
SECTIONS
{
    . = 0x80000000;

    .text : { *(.text.start) *(.text*) }
    .rodata : { *(.rodata*) }
    .data : { *(.data*) }
    .bss : { *(.bss*) }

    /* 64 KiB 0x10000 栈空间 */
    /* Dilithium 3/5 需要栈空间较大, 否则halt fault */
    /* _stack_top = . + 0x100000; */
    _stack_top = . + 0x1b000;
}