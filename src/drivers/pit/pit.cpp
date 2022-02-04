#include "pit.h"

PIT pit;

void PIT::init(uint16_t divisor)
{
    this->tick = 0;
    this->frequency = PIT_FREQUENCY / divisor;
    outb(0x40, this->frequency & 0xFF);
    outb(0x40, (this->frequency >> 8) & 0xFF);
    log.logln("PIT::init", "PIT setup!");
}

void PIT::handler()
{
    this->tick++;
    if(!(this->tick % frequency))
    {
        this->time.seconds++;
        if(this->time.seconds == 59)
        {
            this->time.minutes++;
            this->time.seconds = 0;
            if(this->time.minutes == 59)
            {
                this->time.hours++;
                this->time.minutes = 0;
                if(this->time.hours == 24)
                {
                    this->time.days++;
                    this->time.hours++;
                }
            }
        }
    }
    if(!(this->tick % 1000)) scheduler.switch_task();
}

void PIT::sleep(uint16_t n)
{
    uint64_t now = this->tick;
    while((this->tick - now) <= (n * this->frequency)) asm("hlt");
}

void PIT::sleep_ms(uint32_t n)
{
    uint64_t now = this->tick;
    while((this->tick - now) <= (n * this->frequency) / 1000) asm("hlt");
}

void PIT::show_time_since_boot()
{
    log.log("PIT::show_time_since_boot", "Time since boot: ");
    log.log((String(this->time.days, DECIMAL)));
    log.log(" d ");
    log.log((String(this->time.hours, DECIMAL)));
    log.log(" h ");
    log.log((String(this->time.minutes, DECIMAL)));
    log.log(" min ");
    log.log((String(this->time.seconds, DECIMAL)));
    log.logln(" sec");
}