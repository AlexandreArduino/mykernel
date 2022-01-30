#pragma once

#include "../../kernel.h"

#define PIT_FREQUENCY 1193182

struct Time
{
    uint8_t days;
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
};

class PIT
{
public:
    void init(uint16_t divisor);
    void handler();
    void sleep(uint16_t n);
    void sleep_ms(uint32_t n);
    void show_time_since_boot();
    uint64_t tick;
private:
    uint16_t frequency;
    struct Time time;
};

extern PIT pit;