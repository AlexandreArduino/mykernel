#pragma once

#include "../../kernel.h"

#define QWERTY 0
#define AZERTY 1

#define LEFT_SHIFT 0x2A
#define RIGHT_SHIFT 0x36
#define ENTER 0x1C
#define BACKSPACE 0x0E
#define SPACEBAR 0x39
#define SHIFT_RELEASE 0x80
 

class KeyboardDriver
{
public:
    void init(uint8_t keyboard_disposition);
    void handle(uint8_t code);
    void disable();
    void enable();
private:
    char *disposition;
    bool isInit;
    bool state;
    bool shifted;
};

extern KeyboardDriver keyboard;
