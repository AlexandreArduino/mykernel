#include "rtc.h"

RTC rtc;

void RTC::init()
{
	log.logln("RTC::init", "Initializing RTC class...");
	this->cmos_data_ptr = cmos.get_cmos_data_ptr();
	this->refresh();
}

void RTC::refresh()
{
	log.logln("RTC::refresh", "Refreshing RTC data in memory...");
	cmos.read();
	this->second = this->cmos_data_ptr[0x00];
	this->minute = this->cmos_data_ptr[0x02];
	this->hour = this->cmos_data_ptr[0x04];
	this->day = this->cmos_data_ptr[0x07];
	this->month = this->cmos_data_ptr[0x08];
	this->year = this->cmos_data_ptr[0x09];
	this->registerB = this->cmos_data_ptr[0x0B];
	if (!(this->registerB & 0x04))
	{
		this->second = (this->second & 0x0F) + ((this->second / 16) * 10);
		this->minute = (this->minute & 0x0F) + ((this->minute / 16) * 10);
		this->hour = ((this->hour & 0x0F) + (((this->hour & 0x70) / 16) * 10) ) | (this->hour & 0x80);
		this->day = (this->day & 0x0F) + ((this->day / 16) * 10);
		this->month = (this->month & 0x0F) + ((this->month / 16) * 10);
		this->year = (this->year & 0x0F) + ((this->year / 16) * 10);
		this->century = (this->century & 0x0F) + ((this->century / 16) * 10);
	}
	if (!(this->registerB & 0x02) && (this->hour & 0x80))
	{
		this->hour = ((this->hour & 0x7F) + 12) % 24;
	}
}

void RTC::show_date()
{
	this->refresh();
	log.log("RTC::show_date", "RTC date => ");
	log.log(String(this->hour, DECIMAL));
	log.log(":");
	log.log(String(this->minute, DECIMAL));
	log.log(":");
	log.log(String(this->second, DECIMAL));
	log.log(" ");
	log.log(String(this->day, DECIMAL));
	log.log("/");
	log.log(String(this->month, DECIMAL));
	log.log("/");
	log.logln(String(this->year, DECIMAL));
}