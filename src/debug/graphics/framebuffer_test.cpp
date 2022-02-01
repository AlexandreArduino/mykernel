#include "framebuffer_test.h"

void Tests::_framebuffer()
{
    log.logln("Tests::_framebuffer", "Testing framebuffer...");
    for(size_t x = 0; x < WIDTH; x++)
    {
        for(size_t y = 0; y < HEIGHT; y++)
        {
            framebuffer.set_pixel({x, y}, WHITE);
        }
    }
}

void Tests::drawChar()
{
    for(int i = 0; i < 16; i++)
    {
        log.logln("Tests::drawChar", String(floader.font->glyph[i], BINARY));
        for(int x = 0; x < 8; x++)
        {
            if((floader.font->glyph[i] & (0b10000000 >> x)) > 0) framebuffer.set_pixel({x, i}, WHITE);
        }
    }
}