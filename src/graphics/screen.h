#pragma once

#include "../kernel.h"

#define DEFAULT_COLOR WHITE

struct TextCursor
{
    size_t x;
    size_t y;
};

class Screen
{
public:
    void init();
    void print(const char *str, struct TextCursor position, struct RGB rgb);
    void println(const char *str, struct TextCursor position, struct RGB rgb);
    void print(const char *str, struct TextCursor position);
    void println(const char *str, struct TextCursor position);
    void print(const char *str);
    void println(const char *str);
private:
    struct TextCursor position;
};

extern Screen screen;