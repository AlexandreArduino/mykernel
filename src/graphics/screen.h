#pragma once

#include "../kernel.h"

class Screen
{
public:
    void init();
    void print(const char *str, struct Position position, struct RGB rgb);
};

extern Screen screen;