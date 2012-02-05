GCC = i586-elf-gcc
LD = i586-elf-ld
NASM = nasm

OBJS = loader.o main.o
KERNEL = ../kernel.bin

all: clean $(KERNEL)

$(KERNEL): $(OBJS)
	$(LD) -Tlink.ld -o $@ $^

.c.o:
	$(GCC) -O -I./include -o $@ -c $< -Wall -Wextra -Werror -nostdlib -fno-builtin -nostartfiles -nodefaultlibs -nostdlib -nostdinc -fno-stack-protector

.s.o:
	$(NASM) -felf -o $@ $<

clean:
	@rm *.o | true

