CC = arm-none-eabi-gcc
CFLAGS = -mcpu=cortex-a7 -fpic -ffreestanding -std=gnu99 -O2 -Wall -Wextra
ASFLAGS = -mcpu=cortex-a7 -fpic -ffreestanding
LDFLAGS = -T linker.ld -ffreestanding -O2 -nostdlib -lgcc

OBJS = boot.o kernel.o
EXEC = kernel.elf
IMAGE = kernel7.img

# Targets
all: $(IMAGE)

boot.o: boot.S
	$(CC) $(ASFLAGS) -c boot.S -o boot.o

kernel.o: kernel.c
	$(CC) $(CFLAGS) -c kernel.c -o kernel.o

$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) -o $(EXEC) $(OBJS)

$(IMAGE): $(EXEC)
	arm-none-eabi-objcopy $(EXEC) -O binary $(IMAGE)

clean:
	rm -f $(OBJS) $(EXEC) $(IMAGE)

run: $(IMAGE)
	qemu-system-arm -M raspi2b -serial stdio -kernel $(IMAGE)
