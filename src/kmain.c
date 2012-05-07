#include <kstdlib.h>
#include <descriptor_tables.h>
#include <multiboot.h>
//#include <timer.h>
#include <paging.h>

int kmain(multiboot_info_t * mboot_ptr)
{
	init_descriptor_tables();
	setcol(0x02);
	cleanscr();

	initialise_paging();
	kprintf("Hello! I see you use the %s bootloader :)\n", mboot_ptr->boot_loader_name);
    kprintf("Hello, pagin world!\n");

	u32int *ptr = (u32int*)0xA0000000;
    u32int do_page_fault = *ptr;
	//init_timer(50);
	kprintf("DO NOT COME HERE!\n", do_page_fault);
	return 0xDEADBABA;
}
