#include <stdarg.h>
#include <kstdlib.h>
#include <io.h>

int cur = 0;
char ccol = 0x07;

volatile char * videoram = (char *)0xb8000;

static void update_cursor()
{
	outb(0x3D4, 14);                  // Tell the VGA board we are setting the high cursor byte.
	outb(0x3D5, cur >> 8); // Send the high cursor byte.
	outb(0x3D4, 15);                  // Tell the VGA board we are setting the low cursor byte.
	outb(0x3D5, cur);      // Send the low cursor byte.
}

void setcol(char col)
{
	ccol = col;
}

void cleanscr()
{
	int i;
	for(i = 0; i < (25 * 80) * 2; i += 2)
	{
		videoram[i] = ' ';
		videoram[i + 1] = ccol;
	}
}

void * memcpy(void * destination, const void * source, int num)
{
	int i;
	for(i = 0; i < num; i++)
		*((int *)destination + i) = *((int *)source + i);
	return destination;
}

void * memmove(void * destination, const void * source, int num)
{
	if(source == destination)
		return 0;
	
	int e = (source < destination);
	
	int i;
	for(i = e ? num - 1 : 0; e ? (i >= 0) : (i < num); i += e ? -1 : 1)
		*((int *)destination + i) = *((int *)source + i);
	return destination;
}

void * memset(void * ptr, int value, int num)
{
	int i;
	for(i = 0; i < num; i++)
		*((int *)ptr + i) = value;
	return ptr;
}

void scroll()
{
	memmove((void *)videoram, (void *)(videoram + 160), 48 * 40);
	memset((void *)(videoram + ((24 * 2) * 80)), ccol, 40);
	cur -= 80;
}

void kputc(char chr, char col)
{
	if(chr == '\n')
		cur = ((cur / 80) * 80) + 80;
	else if(chr == '\t')
		cur = ((cur / 4) * 4) + 4;
	else if(chr == '\b')
		cur -= (cur != 0) ? 1 : 0;
	else if(chr == '\r')
		cur -= ((cur / 80) * 80);
	else
	{
		videoram[cur * 2] = chr;
		videoram[cur * 2 + 1] = col;
		cur++;
	}
	if(cur > 80 * 20)
		scroll();
}

void sprint(char * str)
{
	for(; *str != 0; str++)
	{
		kputc(*str, ccol);
		update_cursor();
	}
}

int strlen(char * str)
{
	int l = 0;
	while(*str != 0)
	{
		str++;
		l++;
	}
	return l;
}

char * invertstr(char * str)
{
	int len = strlen(str);
	int i;
	char t;
	for(i = 0; i < len / 2; i++)
	{
		t = *(str + i);
		*(str + i) = *(str + (len - (i + 1)));
		*(str + (len - (i + 1))) = t;
	}
	return str;
}

char * itoa(int val, char * buffer, int base)
{
	int i = 0;
	int n = val < 0;
	if(n) val = -val;
	do
	{
		int n = val % base;
		if(n < 10)
			buffer[i] = 48 + n;
		else
			buffer[i] = ('A' - 10) + n;
		val /= base;
		i++;
	}
	while(val != 0);
	if(n)
	{
		buffer[i] = '-';
		i++;
	}
	buffer[i] = 0;

	invertstr(buffer);
	return buffer;
}

void kprintf(char * format, ...)
{
	va_list vl;
	va_start(vl, format);
	while(*format != 0)
	{
		if(*format == '%')
		{
			format++;
			switch(*format)
			{
				case 's':
				{
					char *s  = va_arg(vl, char *);
					sprint(s);
				}
				break;
				
				case 'i':
				case 'd':
				{
					char s[50];
					itoa(va_arg(vl, int), s, 10);
					sprint(s);
				}
				break;
				
				case 'X':
				{
					char s[50];
					itoa(va_arg(vl, int), s, 16);
					sprint(s);
				}
				break;
			}
		}
		else
			kputc(*format, ccol);
		
		format++;
	}
	va_end(vl);
}

