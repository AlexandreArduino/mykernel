#pragma once

#include "../kernel.h"

#define COM_INIT_ERROR RED
#define SIGNATURE_ERROR GREEN
#define PANIC_SCREEN BLUE
#define MEMORY_ERROR MAGENTA

namespace Exceptions {
    void panic(const char *error);
};