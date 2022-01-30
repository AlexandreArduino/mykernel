#include "cmos.h"

CMOS cmos;

void CMOS::init()
{
	this->data = (unsigned char*)allocator.alloc(128);
	if(this->data == NULL) Exceptions::panic("CMOS data can't be store because memory allocation failed!");
	else
	{
		log.log("CMOS::init", "CMOS data will be store at 0x");
		log.logln(String((uint64_t)this->data, HEXADECIMAL));
	}
}

void CMOS::read()
{
	log.logln("CMOS::read", "Reading CMOS informations...");
	cli();
	for(unsigned char index = 0; index < 128; index++)
	{
		while(this->inUpdate());
		outb(0x70, index);
		this->data[index] = inb(0x71);
	}
	sti();
}

int CMOS::inUpdate()
{
	outb(0x70, 0x0A);
	return (inb(0x71) & 0x80);
}

unsigned char *CMOS::get_cmos_data_ptr()
{
	return this->data;
}