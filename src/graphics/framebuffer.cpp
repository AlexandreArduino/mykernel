#include "framebuffer.h"
#include "../kernel.h"

Framebuffer framebuffer;

void Framebuffer::init(struct stivale2_struct *bootloader_data)
{
    struct stivale2_struct_tag_framebuffer *framebuffer_tag = (struct stivale2_struct_tag_framebuffer*)stivale2_find_tag(bootloader_data, STIVALE2_STRUCT_TAG_FRAMEBUFFER_ID);
    struct framebuffer_pixel* framebuffer = (struct framebuffer_pixel*)framebuffer_tag->framebuffer_addr;
    if(framebuffer_tag == NULL) Exceptions::panic("No framebuffer found!");
    else this->buffer = framebuffer;
    this->position.x = 0;
    this->position.y = 0;
    this->tag = framebuffer_tag;
    // log.logln("Framebuffer::init", "The framebuffer is ready!");
}

size_t Framebuffer::raw_position(struct Position position)
{
    return position.x + position.y * this->tag->framebuffer_width;
}

struct Position Framebuffer::coos_position(size_t raw_position)
{
    struct Position to_return;
    to_return.y = raw_position / this->tag->framebuffer_width;
    to_return.x = raw_position % this->tag->framebuffer_width;
    return to_return;
}

void Framebuffer::set_pixel(struct Position position, struct RGB rgb)
{
    this->buffer[this->raw_position(position)].red = rgb.red;
    this->buffer[this->raw_position(position)].green = rgb.green;
    this->buffer[this->raw_position(position)].blue = rgb.blue;

}

void Framebuffer::set_pixel(size_t raw_position, struct RGB rgb)
{
    this->buffer[raw_position].red = rgb.red;
    this->buffer[raw_position].green = rgb.green;
    this->buffer[raw_position].blue = rgb.blue;

}

struct RGB Framebuffer::get_pixel(struct Position position)
{
    struct RGB to_return;
    to_return.red = this->buffer[this->raw_position(position)].red;
    to_return.green = this->buffer[this->raw_position(position)].green;
    to_return.blue = this->buffer[this->raw_position(position)].blue;
    return to_return;
}

struct RGB Framebuffer::get_pixel(size_t raw_position)
{
    return this->get_pixel(this->coos_position(raw_position));
}

void Framebuffer::fill_rect(struct Position position, struct Dimension dimension, struct RGB rgb)
{
    for(size_t x = position.x; x < position.x + dimension.width; x++)
    {
        for(size_t y = position.y; y < position.y + dimension.height; y++)
        {
            this->set_pixel((struct Position){x, y}, rgb);
        }
    }
}

void Framebuffer::clear()
{
    this->clear(BLACK);
}

void Framebuffer::clear(struct RGB rgb)
{
    this->fill_rect({0, 0}, {this->tag->framebuffer_width, this->tag->framebuffer_height}, rgb);
}

void Framebuffer::drawChar(char c, struct Position position, struct RGB rgb)
{
    char* fontPtr = floader.get_font(c);
    for (unsigned long y = position.y; y < position.y + 16; y++)
    {
        for (unsigned long x = position.x; x < position.x + 8; x++)
        {
            if ((*fontPtr & (0b10000000 >> (x - position.x))) > 0)
            {
                this->set_pixel(this->raw_position({x, y}), rgb);
            }

        }
        fontPtr++;
    }
}