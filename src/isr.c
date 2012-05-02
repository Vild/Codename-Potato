#include <isr.h>
#include <kstdlib.h>
#include <io.h>

isr_t interrupt_handlers[256];

void register_interrupt_handler(u8int n, isr_t handler)
{
	interrupt_handlers[n] = handler;
}

void isr_handler(registers_t regs)
{
	kprintf("recived interrupt: %i\n", regs.int_no);

	if (interrupt_handlers[regs.int_no] != 0)
	{
		isr_t handler = interrupt_handlers[regs.int_no];
		handler(regs);
	}
}

void irq_handler(registers_t regs)
{
	kprintf("recived IRQ: %i\n", regs.int_no);

	if (regs.int_no >= 40)
		outb(0xA0, 0x20);
	
	outb(0x20, 0x20);

	if (interrupt_handlers[regs.int_no] != 0)
	{
		isr_t handler = interrupt_handlers[regs.int_no];
		handler(regs);
	}
}
