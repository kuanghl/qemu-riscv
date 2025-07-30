CROSS  = riscv32-unknown-elf-
CFLAGS = -nostdlib -nostartfiles -ffreestanding -march=rv32imac -mabi=ilp32

OBJS = start.o main.o uart.o
hello.elf: $(OBJS)
	$(CROSS)ld -T link.ld -o $@ $^
	$(CROSS)objcopy -O binary hello.elf hello.bin

%.o: %.c
	$(CROSS)gcc $(CFLAGS) -c -o $@ $<
%.o: %.S
	$(CROSS)gcc $(CFLAGS) -c -o $@ $<

run: hello.elf
	qemu-system-riscv32 -machine virt -nographic -bios none -kernel hello.elf

clean:
	rm -f *.o *.elf *.bin

# 在终端按Ctrl-A再按X即可退出