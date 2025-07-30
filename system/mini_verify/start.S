.section .text.start
.global _start
_start:
    la   sp, _stack_top      # 设置栈指针
    call main
hang:
    j    hang