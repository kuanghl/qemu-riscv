CROSS  = riscv32-unknown-elf-
CFLAGS = -nostdlib -nostartfiles -ffreestanding -march=rv32imac -mabi=ilp32 -g

OBJS = start.o uart.o main.o fips202.o ntt.o packing.o poly.o polyvec.o reduce.o rounding.o sign.o symmetric-shake.o 
main.elf: $(OBJS)
	$(CROSS)ld -T link.ld -o $@ $^
	$(CROSS)objcopy -O binary main.elf main.bin

%.o: %.c
	$(CROSS)gcc $(CFLAGS) -c -o $@ $<
%.o: %.S
	$(CROSS)gcc $(CFLAGS) -c -o $@ $<

run: main.elf
	qemu-system-riscv32 -machine virt -nographic -bios none -kernel main.elf

clean:
	rm -f *.o *.elf *.bin

# 在终端按Ctrl-A再按X即可退出