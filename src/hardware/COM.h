#pragma once

#include "../lib/defs.h"
#include "../kernel.h"

#define COM1 0x3F8
#define COM2 0x2F8
#define COM3 0x3E8
#define COM4 0x2E8

#define COM1_IRQ 4
#define COM2_IRQ 3
#define COM3_IRQ 4
#define COM4_IRQ 3

class COM
{
public:
    void init(uint16_t port);
    int received();
    char read();
    int isTransmitEmpty();
    void write(char c);
    void write(const char *str);
    void writeln(const char *str);
    void writeln(const char *str, size_t length);
private:
    uint16_t port;
};

extern COM com;