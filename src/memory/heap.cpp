#include "heap.h"

MemoryAllocator allocator;

void MemoryAllocator::init(uint64_t memory_size)
{
    this->pages = memory_size / 4096;
    this->base = (uint64_t*)frameAllocator.alloc(this->pages);
    this->size = memory_size;
    log.log("MemoryAllocator::init", "Memory allocation will start at 0x");
    log.logln(String((uint64_t)this->base, HEXADECIMAL));
    this->first = (struct chunk*)this->base;
    this->first->size = this->size - sizeof(struct chunk);
    this->first->allocated = false;
    this->first->previous = 0;
    this->first->next = 0;
    if(this->size <= sizeof(struct chunk))
    {
        log.logln("MemoryAllocator::init", "Too few memory detected for memory allocator!");
        framebuffer.clear(MEMORY_ERROR);
        while(1);
    }
}

void *MemoryAllocator::alloc(uint64_t size)
{
    struct chunk *result = NULL;
    for(struct chunk *current_chunck = this->first; current_chunck != 0; current_chunck = current_chunck->next)
    {
        if(current_chunck->size >= size + sizeof(struct chunk) + 1 && !current_chunck->allocated)
        {
            result = current_chunck;
            break;
        }
    }
    if(!result) return NULL;
    else
    {
        result->allocated = true;
        struct chunk *next_chunck =  (struct chunk*)((uint64_t)result + sizeof(struct chunk) + size);
        next_chunck->allocated = false;
        next_chunck->previous = result;
        next_chunck->next = next_chunck;
        next_chunck->size = result->size - size - sizeof(struct chunk);
        result->size = size;
        result->next = next_chunck;
        return (void*)((uint64_t)result + sizeof(struct chunk));
    }
}

void MemoryAllocator::free(void *base)
{
    struct chunk *to_remove = (struct chunk*)((uint64_t)base - sizeof(struct chunk));
    to_remove->allocated = false;

    // In the case where the previous chunk is free
    if(to_remove->previous && !to_remove->previous->allocated)
    {
        to_remove->previous->next = to_remove->next;
        to_remove->previous->size += sizeof(struct chunk) + to_remove->size;
    }

    // In the case where the next chunk is free
    if(to_remove->next && !to_remove->next->allocated)
    {
        to_remove->next->previous = to_remove->previous;
        to_remove->size += sizeof(struct chunk) + to_remove->size;
    }
}