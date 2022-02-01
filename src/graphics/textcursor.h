#pragma once

#include "../kernel.h"

class TextCursor
{
public:
    void init(uint8_t inc_x, uint8_t inc_y);
    void incx();
    void incy();
    void check_coos();
private:
    size_t x;
    size_t y;
    uint8_t inc_x;
    uint8_t inc_y;
};