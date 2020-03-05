CROSS_COMPILE ?= arm-none-eabi-

.PHONY: all

all: blink.bin

blink.o: blink.c
	$(CROSS_COMPILE)gcc -mcpu=cortex-m3 -mthumb -nostartfiles -c blink.c -o blink.o

blink.out: blink.o stm32_flash.ld
	$(CROSS_COMPILE)ld -T stm32_flash.ld -o blink.out blink.o

blink.bin: blink.out
	$(CROSS_COMPILE)objcopy -O binary blink.out blink.bin

clean:
	rm -f *.o *.out *.bin
