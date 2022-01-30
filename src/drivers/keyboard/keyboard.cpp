#include "keyboard.h"

KeyboardDriver keyboard;

void KeyboardDriver::init(uint8_t keyboard_disposition)
{
    this->isInit = true;
    this->shifted = false;
    switch(keyboard_disposition)
    {
        case QWERTY:
            this->disposition = &KeyboardDisposition::qwerty[0];
            log.logln("KeyboardDriver::init", "Keyboard disposition set to qwerty");
            break;
        default:
            log.logln("KeyboardDriver::init", "Keyboard disposition set to unknown");
            this->isInit = false;
            break;

    }
    this->state = true;
}

void KeyboardDriver::handle(uint8_t code)
{
    if(!this->isInit)
    {
        log.logln("KeyboardDisposition::handle", "You must choice a keyboard disposition before using it!");
        while(1);
    }
    if(this->state)
    {
        com.write(this->disposition[code]);
    }
}

void KeyboardDriver::disable()
{
    this->state = false;
}

void KeyboardDriver::enable()
{
    this->state = true;
}
