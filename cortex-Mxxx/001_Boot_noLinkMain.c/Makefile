.SILENT:

obj_bin = start.o
all: main.elf

main.elf: ${obj_bin}
	mkdir -p build
	arm-none-eabi-gcc $^ -nostdlib -T linker.ld -o build/$@
	
%.o : %.s
	arm-none-eabi-gcc -c $< -o $@

clean:
	rm -rf build/* *.o

start: main.elf
	qemu-system-arm -M lm3s6965evb -kernel build/main.elf -S -gdb tcp::1234 -nographic

gdb:
	gdb-multiarch build/main.elf	