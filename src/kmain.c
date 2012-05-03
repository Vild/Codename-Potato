#include <kstdlib.h>
#include <descriptor_tables.h>
#include <multiboot.h>
//#include <timer.h>
#include <paging.h>

extern u32int end;
extern u32int placement_address;

int kmain(multiboot_info_t * mboot_ptr)
{
	init_descriptor_tables();
	setcol(0x02);
	cleanscr();

    kprintf("END = %X, PLACEMENT_ADDR = %X\n", end, placement_address);

	initialise_paging();
	kprintf("Hello! I see you use the %s bootloader :) testing PAGEING :S\n", mboot_ptr->boot_loader_name);

	u32int *ptr = (u32int*)0xA0000000;
    u32int do_page_fault = *ptr;
    kprintf("Ptr = %X", do_page_fault);

	//init_timer(50);
	return 0xDEADBABA;
}
