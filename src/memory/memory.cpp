#include "memory.h"

Memory memory;

void Memory::init(struct stivale2_struct_tag_memmap *memorymap_tag)
{
    this->memorymap_tag = memorymap_tag;
    struct stivale2_mmap_entry entry;
    this->available.base = 0;
    this->available.size = 0;
    for(uint64_t i = 0; i < this->memorymap_tag->entries; i++)
    {
        entry = this->memorymap_tag->memmap[i];
        this->detect_memory_available(&entry);
    }
    log.log("Memory::init", "The base of the memory available is 0x");
    log.logln(String(this->available.base, HEXADECIMAL));
    log.log("Memory::init", "The size of the memory available is ");
    log.log(String(this->available.size, DECIMAL));
    log.logln(" bytes");
    this->base = this->available.base;
    this->size = this->available.size;
}

void Memory::show_mmap_type()
{
    log.logln("Memory::show_mmap_type", "Here is the memory map : ");
    struct stivale2_mmap_entry entry;
    for(uint64_t i = 0; i < this->memorymap_tag->entries; i++)
    {
        entry = this->memorymap_tag->memmap[i];
        log.logln(this->GetStringType(entry.type));
    }
}

void Memory::detect_memory_available(struct stivale2_mmap_entry *entry)
{
    if(entry->type == USABLE)
    {
        if(entry->length > this->available.size)
        {
            this->available.base = entry->base;
            this->available.size = entry->length;
        }
    }
}

const char *Memory::GetStringType(uint32_t type)
{
    switch(type)
    {
        case USABLE: return "USABLE";
        case RESERVED: return "RESERVED";
        case ACPI_RECLAIMABLE: return "ACPI_RECLAIMABLE";
        case ACPI_NVS: return "ACPI_NVS";
        case BAD_MEMORY: return "BAD_MEMORY";
        case BOOTLOADER_RECLAIMABLE: return "BOOTLOADER_RECLAIMABLE";
        case KERNEL_AND_MODULES: return "KERNEL_AND_MODULES";
        case FRAMEBUFFER: return "FRAMEBUFFER";
        default: return "UNDEFINED";
    }
}