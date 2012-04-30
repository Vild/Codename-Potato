#include <kstdlib.h>
struct multiboot;

int kmain(struct multiboot * mboot_ptr)
{
	int i;
	if (mboot_ptr) i++;
	cleanscr();
	kprintf("Hello WORLD:)\nINT: %i\nHEX:%X", 1337, 0x1A313337);
	return 0xDEADBABA;
}
