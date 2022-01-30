#pragma once

#include "../kernel.h"

#define USABLE 1
#define RESERVED 2
#define ACPI_RECLAIMABLE 3
#define ACPI_NVS 4
#define BAD_MEMORY 5
#define BOOTLOADER_RECLAIMABLE 0x1000
#define KERNEL_AND_MODULES 0x1001
#define FRAMEBUFFER 0x1002

/*
enum stivale2_mmap_type : uint32_t {
    USABLE                 = 1,
    RESERVED               = 2,
    ACPI_RECLAIMABLE       = 3,
    ACPI_NVS               = 4,
    BAD_MEMORY             = 5,
    BOOTLOADER_RECLAIMABLE = 0x1000,
    KERNEL_AND_MODULES     = 0x1001,
    FRAMEBUFFER            = 0x1002
};
*/

struct MemoryAvailable
{
    uint64_t base;
    uint64_t size;
};

class Memory
{
public:
    void init(struct stivale2_struct_tag_memmap *memorymap_tag);
    void show_mmap_type();
    void detect_memory_available(struct stivale2_mmap_entry *entry);
    uint64_t base;
    uint64_t size;
private:    
    struct stivale2_struct_tag_memmap *memorymap_tag;
    const char *GetStringType(uint32_t type);
    struct MemoryAvailable available;
};

extern Memory memory;