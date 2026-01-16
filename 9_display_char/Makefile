
OUT = out.gba
OBJS = header.o main.o

BASEPATH = /opt/devkitpro/devkitARM/bin/

CC = $(BASEPATH)arm-none-eabi-gcc
LD = $(BASEPATH)arm-none-eabi-ld
AS = $(BASEPATH)arm-none-eabi-as
OBJCOPY = $(BASEPATH)arm-none-eabi-objcopy

$(OUT): $(OBJS)
	$(LD) -T gamecart.ld -o out.elf $^
	$(OBJCOPY) -O binary out.elf $@

%.o: %.c
	$(CC) -c -mcpu=arm7tdmi -o $@ $<

%.o: %.s
	$(AS) -mcpu=arm7tdmi -o $@ $<

.PHONY: clean
clean:
	rm *.o *.elf *.gba
