#pragma once

#include "../../kernel.h"

struct float_number
{
    uint32_t before_coma;
    uint32_t after_coma;
}__attribute__((packed));

namespace Mathematics
{
    struct float_number convert_to_float(float number); 
};