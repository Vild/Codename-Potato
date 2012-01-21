GCC = i586-elf-gcc
LD = i586-elf-ld
NASM = nasm

OBJS = main.o
KERNEL = kernel.bin

$(KERNEL): $(OBJS)
	$(LD) -Tlink.ld -o $@ $^

.c.o:
	$(GCC) -O -I./src/include -o $@ -c $< -Wall -Wextra -Werror -nostdlib -fno-builtin -nostartfiles -nodefaultlibs

.s.o:
	$(NASM) -felf -o $@ $<

