#include "string.h"

uint8_t string::length(const char *str)
{
    uint8_t count = 0;
    while(*str != '\0')
    {
        count++;
        str++;
    }
    return count;
}