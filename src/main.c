int kmain(void *mboot_ptr) //struct multiboot
{
	int i;
	if (mboot_ptr) i++;
	return 0xDEADBABA;
}
