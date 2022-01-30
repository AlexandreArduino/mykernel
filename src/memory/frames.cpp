#include "frames.h"

FrameAllocator frameAllocator;

void FrameAllocator::init(uint64_t base, uint64_t size)
{
    this->base = base;
    this->size = size;
    this->bitmap = (uint8_t*)this->base;
    uint64_t end_memory = this->base + this->size;
    uint64_t bitmap_size = end_memory / 32768;
    this->bitmap_size = bitmap_size;
    this->last_free_page = 0;
    for(uint64_t i = 0; i < this->bitmap_size; i++)
    {
        *this->bitmap = 0;
        this->bitmap++;
    }
    log.log("FramAllocator::init", "Size of the bitmap : ");
    log.logln("Frameallocator::init", String(this->bitmap_size, DECIMAL));
    uint8_t pages_used_by_bitmap = (this->bitmap_size / 4096) + 1;
    log.log("Frameallocator::init", "Pages used so : ");
    log.logln(String(pages_used_by_bitmap, DECIMAL));

    uint8_t bytes = pages_used_by_bitmap / 8;

    for(uint8_t i = 0; i <= bytes; i++) this->bitmap[i] = 255;
    log.logln("Frameallocator::init", "Bitmap ok");
    this->pages_used = 0;
    this->whole_pages = this->size / 4096;
}

void *FrameAllocator::alloc(uint64_t pages)
{
    log.log("Framealloctor::alloc", "Allocating ");
    log.log(String(pages, DECIMAL));
    log.logln(" pages...");
    int64_t bit_number = this->find_pages(pages);
    if(bit_number == -1)
    {
        log.logln("Frameallocator::alloc", "Failed to allocate pages!");
        framebuffer.clear(MEMORY_ERROR);
        while(1);
    }
    for(uint64_t i = bit_number; i < bit_number + pages; i++)
    {
        this->setBit(i);
    }
    return (void*)(this->bitmap + 4096 * bit_number);
}

void FrameAllocator::free(void *page, uint64_t count)
{
    log.log("FrameAllocator::free", "Freeing ");
    log.log(String(count, DECIMAL));
    log.logln(" pages...");
    uint64_t bit_number = ((uint64_t)(uint64_t*)page - (uint64_t)this->bitmap) / 4096;
    for(uint64_t i = bit_number; i < bit_number + count; i++)
    {
        this->clearBit(i);
    }
    if(bit_number < this->last_free_page) this->last_free_page = bit_number;
}

uint64_t FrameAllocator::get_byte_bitmap(uint64_t page)
{
    return page / 8;
}

uint8_t FrameAllocator::get_bit_in_byte(uint64_t page)
{
    return page % 8;
}

void FrameAllocator::setBit(uint64_t page)
{
    this->bitmap[this->get_byte_bitmap(page)] |= (1 << this->get_bit_in_byte(page));
    this->pages_used++;
}

void FrameAllocator::clearBit(uint64_t page)
{
    this->bitmap[this->get_byte_bitmap(page)] &= ~(1 << this->get_bit_in_byte(page));
    this->pages_used--;
}

bool FrameAllocator::isBit(uint64_t page)
{
    return this->bitmap[this->get_byte_bitmap(page)] & (1 << this->get_bit_in_byte(page));
}

uint64_t FrameAllocator::find_pages(uint64_t pages)
{
    uint64_t free_pages_count = 0;
    for(uint64_t i = this->last_free_page; i < this->bitmap_size * 8; i++)
    {
        if(!this->isBit(i))
        {
            free_pages_count++;
            if(free_pages_count == pages)
            {
                this->last_free_page = i;
                return i - pages + 1; // The bit number in the bitmap
            }
        } else free_pages_count = 0;
    }
    return -1;
}

uint8_t FrameAllocator::percent_memory_used()
{
    return this->pages_used / this->whole_pages;
}