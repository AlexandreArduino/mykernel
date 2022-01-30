#pragma once

#include "../kernel.h"

class CMOS
{
public:
	void init();
	void read();
	unsigned char *get_cmos_data_ptr();
private:
	unsigned char *data;
	int inUpdate();
};

extern CMOS cmos; 