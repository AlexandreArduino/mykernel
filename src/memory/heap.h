#pragma once

#include "../kernel.h"

class MemoryAllocator
{
public:
    void init(uint64_t memory_size);
    void *alloc(uint64_t size);
    void free(void *base);
private:
    uint64_t *base;
    uint64_t pages;
    uint64_t size;
    struct chunk *first;
};

struct chunk
{
    struct chunk *next;
    struct chunk *previous;
    bool allocated;
    uint64_t size;
}__attribute__((packed));

extern MemoryAllocator allocator;