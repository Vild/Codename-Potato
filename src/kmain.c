#include <kstdlib.h>
#include <descriptor_tables.h>
#include <multiboot.h>
#include <timer.h>

int kmain(multiboot_info_t * mboot_ptr)
{
	init_descriptor_tables();
	setcol(0x02);
	cleanscr();
	
	kprintf("Hello! I see you use the %s bootloader :)\n", mboot_ptr->boot_loader_name);

	asm volatile("int $0x3");
	asm volatile("int $0x4");

	asm volatile("sti");

	init_timer(50);
	return 0xDEADBABA;
}
