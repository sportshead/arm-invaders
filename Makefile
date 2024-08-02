SRCS = $(wildcard *.c */*.c)
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib -mcpu=cortex-a53+nosimd -Iinclude

.PHONY: all
all: clean kernel8.img

start.o: start.S
	clang --target=aarch64-elf $(CFLAGS) -c start.S -o start.o

%.o: %.c
	clang --target=aarch64-elf $(CFLAGS) -c $< -o $@

kernel8.img: start.o $(OBJS)
	ld.lld -m aarch64elf -nostdlib start.o $(OBJS) -T link.ld -o kernel8.elf
	llvm-objcopy -O binary kernel8.elf kernel8.img

.PHONY: clean
clean:
	rm kernel8.elf *.o **/*.o >/dev/null 2>/dev/null || true

.PHONY: run
run: kernel8.img
	qemu-system-aarch64 -M raspi3b -kernel kernel8.img -serial null -serial stdio -display cocoa,zoom-to-fit=on

.PHONY: install
install: kernel8.img config.txt
	@test -d "$(PREFIX)" || (echo "PREFIX is not set or not a directory" && exit 1)
	cp kernel8.img $(PREFIX)/kernel8.img
	cp config.txt $(PREFIX)/config.txt
