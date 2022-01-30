#pragma once

#include "../kernel.h"

class FrameAllocator
{
public:
    void init(uint64_t base, uint64_t size);
    void *alloc(uint64_t pages);
    void free(void *page, uint64_t count);
    uint8_t percent_memory_used();
private:
    uint64_t base;
    uint64_t size;
    uint8_t *bitmap;
    uint64_t bitmap_size;
    uint64_t last_free_page;
    uint64_t get_byte_bitmap(uint64_t page);
    uint8_t get_bit_in_byte(uint64_t page);
    void setBit(uint64_t page);
    void clearBit(uint64_t page);
    bool isBit(uint64_t page);
    uint8_t pages_used;
    uint64_t whole_pages;
    uint64_t find_pages(uint64_t pages);
};

extern FrameAllocator frameAllocator;