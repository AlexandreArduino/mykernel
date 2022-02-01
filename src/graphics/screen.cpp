#include "screen.h"

Screen screen;

void Screen::init()
{
    log.logln("Screen::init", "The screen method is ready!");
}

void Screen::print(const char *str, struct Position position, struct RGB rgb)
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
        framebuffer.drawChar(*str, position, rgb);
        position.x += DEFAULT_PSF_WIDTH;
        str++;
    }
}