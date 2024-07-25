SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib -mcpu=cortex-a53+nosimd

USPI_DIR = uspi
CFLAGS += -I$(USPI_DIR)/include
USPI_SRCS = $(wildcard $(USPI_DIR)/*/*.c)
USPI_OBJS = $(USPI_SRCS:.c=.o)

.PHONY: all
all: clean $(USPI_DIR) kernel8.img

start.o: start.S
	clang --target=aarch64-elf $(CFLAGS) -c start.S -o start.o

%.o: %.c $(USPI_DIR)
	clang --target=aarch64-elf $(CFLAGS) -c $< -o $@

kernel8.img: $(USPI_DIR)/lib/libuspi.a start.o $(OBJS)
	ld.lld -m aarch64elf -nostdlib start.o $(OBJS) $(USPI_DIR)/lib/libuspi.a -T link.ld -o kernel8.elf
	llvm-objcopy -O binary kernel8.elf kernel8.img

.PHONY: clean
clean:
	rm kernel8.elf *.o $(USPI_DIR)/lib/*.a $(USPI_DIR)/**/*.o >/dev/null 2>/dev/null || true

$(USPI_DIR):
	git submodule update --init --recursive

$(USPI_DIR)/%.o: $(USPI_DIR)/%/*.c
	clang --target=aarch64-elf $(CFLAGS) -c $< -o $@

$(USPI_DIR)/lib/libuspi.a: $(USPI_OBJS)
	ar rcs $@ $^


.PHONY: run
run: kernel8.img
	qemu-system-aarch64 -M raspi3b -kernel kernel8.img -serial stdio -display cocoa,zoom-to-fit=on
