#pragma once

#include "../kernel.h"

struct framebuffer_pixel
{
    uint8_t blue;
    uint8_t green;
    uint8_t red;
    uint8_t __unused;
} __attribute__((packed));

struct RGB
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

struct Position
{
    size_t x;
    size_t y;
};

struct Dimension
{
    size_t width;
    size_t height;
};

#define WHITE (struct RGB){255, 255, 255}
#define BLACK (struct RGB){0, 0, 0}
#define RED (struct RGB){255, 0, 0}
#define GREEN (struct RGB){0, 255, 0}
#define BLUE (struct RGB){0, 0, 255}
#define MAGENTA (struct RGB){255, 0, 255}

class Framebuffer
{
public:
    void init(struct stivale2_struct *bootloader_data);
    size_t raw_position(struct Position position);
    struct Position coos_position(size_t raw_position);
    void set_pixel(struct Position position, struct RGB rgb);
    void set_pixel(size_t raw_position, struct RGB rgb);
    void fill_rect(struct Position position, struct Dimension dimension, struct RGB rgb);
    void clear();
    void clear(struct RGB rgb);
    void drawChar(char c, struct Position position, struct RGB rgb);
    struct RGB get_pixel(struct Position position);
    struct RGB get_pixel(size_t raw_position);
private:
    struct framebuffer_pixel *buffer;
    struct stivale2_struct_tag_framebuffer *tag;
    struct Position position;
};

extern Framebuffer framebuffer;