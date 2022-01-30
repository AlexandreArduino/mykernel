#pragma once

#include "../kernel.h"

class RTC
{
public:
	void init();
	void refresh();
	void show_date();
	unsigned char century;
	unsigned char second;
    unsigned char minute;
    unsigned char hour;
    unsigned char day;
    unsigned char month;
	unsigned char year;
    unsigned char registerB;
private:
	unsigned char *cmos_data_ptr;
};

extern RTC rtc;