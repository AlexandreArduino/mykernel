#include "screen.h"

Screen screen;

void Screen::init()
{
    this->position.x = 0;
    this->position.y = 0;
    log.logln("Screen::init", "The screen method is ready!");
}

void Screen::print(const char *str, struct TextCursor position, struct RGB rgb)
{
    while(*str)
    {
        if(position.x > framebuffer.width())
        {
            position.x = 0;
            position.y += DEFAULT_PSF_HEIGHT;
        }
        if(position.y > framebuffer.height())
        {
            position.y = 0;
            position.x = 0;
        }
        if(*str == '\n')
        {
            position.y += DEFAULT_PSF_HEIGHT;
            position.x = 0;
        }
        else
        {
            framebuffer.drawChar(*str, {position.x, position.y}, rgb);
            position.x += DEFAULT_PSF_WIDTH;
        }
        str++;
    }
    this->position = position;
}

void Screen::println(const char *str, struct TextCursor position, struct RGB rgb)
{
    this->print(str, position, rgb);
    this->println("\n", this->position, rgb);
}

void Screen::print(const char *str, struct TextCursor position)
{
    this->print(str, position, DEFAULT_COLOR);
}

void Screen::println(const char *str, struct TextCursor position)
{
    this->print(str, position);
    this->print("\n", this->position);
}

void Screen::print(const char *str)
{
    this->print(str, this->position);
}

void Screen::println(const char *str)
{
    this->print(str, this->position);
    this->print("\n", this->position);
}