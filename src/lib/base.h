#pragma once

#include "../kernel.h"

#define DECIMAL 10
#define HEXADECIMAL 16
#define BINARY 2
#define FLOAT 255

const char *String(uint64_t value, uint8_t base);
const char *DecimalString(uint64_t value);
const char *HexadecimalString(uint64_t value);
const char *BinaryString(uint64_t value);
const char *FloatString(float value);

namespace Library
{
    extern char conversion_output[256];
}