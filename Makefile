# makefile from an old project of mine, modified
CC=i686-elf-g++
CCFLAGS=-ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -I./include
AS=nasm
ASFLAGS=-felf32
SOURCES=$(shell find src/ -name "*.cpp")
SOURCES_ASM=$(shell find . -name "*.asm")
LDFLAGS=-T linker.ld -ffreestanding -O2 -nostdlib -lgcc

%.o: %.cpp
	$(CC) -c $(CCFLAGS) $< -o $@

%.o: %.asm
	$(AS) $(ASFLAGS) $< -o $@

all: $(SOURCES:%.cpp=%.o) $(SOURCES_ASM:%.asm=%.o)
	$(CC) $^ $(LDFLAGS) -o kernel.bin

iso: all
	mkdir -p iso/boot/grub
	cp kernel.bin iso/boot/
	cp grub.cfg iso/boot/grub
	grub-mkrescue -o os.iso iso

clean: all
	rm $(SOURCES:%.cpp=%.o) $(SOURCES_ASM:%.asm=%.o)
