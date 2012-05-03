GCC = i586-elf-gcc
LD = i586-elf-ld
NASM = nasm

OBJS = loader.o kmain.o io.o kstdlib.o interrupt.o descriptor_tables.o asm_misc.o  isr.o timer.o kheap.o paging.o
KERNEL = ../kernel.bin

all: $(KERNEL)

$(KERNEL): $(OBJS)
	$(LD) -Tlink.ld -o $@ $^

.c.o:
	$(GCC) -O -I./include -o $@ -c $< -Wall -Wextra -Werror -nostdlib -fno-builtin -nostartfiles -nodefaultlibs -nostdinc -nostdinc -fno-stack-protector

.s.o:
	$(NASM) -felf -o $@ $<

clean:
	@rm *.o | true

