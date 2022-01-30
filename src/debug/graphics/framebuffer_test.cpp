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