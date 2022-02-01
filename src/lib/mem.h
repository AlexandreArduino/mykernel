#pragma once

#include "defs.h"
#include "../lib/mem.h"
#include "../kernel.h"

bool memcmp(void *arg1, void *arg2, size_t size);
void memcpy(void *dst, void *src, size_t size);