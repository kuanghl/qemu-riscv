 ### 编译.

```sh
riscv32-unknown-elf-gcc -ffreestanding -nostdlib -Wl,-Ttext=0x80000000 -O2 main.c
qemu-system-riscv32 -nographic -M virt -bios none -kernel a.out
```
