#include "kernel.h"

#define STACK_SIZE 32768

char kernel_stack[STACK_SIZE];

static struct stivale2_struct_tag_memmap memorymap_tag
{
    .tag =
    {
        .identifier = STIVALE2_STRUCT_TAG_MEMMAP_ID,
        .next = (uintptr_t)&rsdp_tag
    }
};

static struct stivale2_header_tag_framebuffer framebuffer_header_tag = 
{
    .tag = 
    {
        .identifier = STIVALE2_HEADER_TAG_FRAMEBUFFER_ID,
        .next = (uintptr_t)&memorymap_tag
    },
    .framebuffer_width  = WIDTH,
    .framebuffer_height = HEIGHT,
    .framebuffer_bpp    = 32
};

__attribute__((section(".stivale2hdr"), used))
static struct stivale2_header stivale_hdr = {
    .entry_point = 0,
    .stack = (uintptr_t)kernel_stack + STACK_SIZE,
    .flags = 0,
    .tags = (uintptr_t)&framebuffer_header_tag
};


extern "C" void _start(struct stivale2_struct *bootloader_data)
{
    framebuffer.init(bootloader_data);
    framebuffer.clear();
    com.init(COM1);
    log.on();
    floader.init(0);
    gdt_init();
    struct stivale2_struct_tag_memmap *memorymap_tag = (struct stivale2_struct_tag_memmap*)stivale2_find_tag(bootloader_data, STIVALE2_STRUCT_TAG_MEMMAP_ID);
    memory.init(memorymap_tag);
    memory.show_mmap_type();
    frameAllocator.init(memory.base, memory.size);
    cpu.dump_registers();
    setupIDT();
    struct stivale2_struct_tag_rsdp *rsdp_tag = (struct stivale2_struct_tag_rsdp*)stivale2_find_tag(bootloader_data, STIVALE2_STRUCT_TAG_RSDP_ID);
    acpi.init((uint64_t*)rsdp_tag->rsdp);
    pit.init(1000);
    allocator.init(1000000);
    keyboard.init(QWERTY);
    keyboard.disable();
    cpu.show_vendor();
    cmos.init();
    cmos.read();
    rtc.init();
    rtc.show_date();
    #ifdef TEST
    log.logln("_start", "Running tests functions...");
    Tests::_framebuffer();
    Tests::primenumbers_examples();
    #endif
    keyboard.enable();
    framebuffer.clear();
    pci.show_all_periph();
    framebuffer.drawChar(0, {100, 100}, WHITE);
    pit.show_time_since_boot();
    while(1) asm("hlt");
}

void *stivale2_find_tag(struct stivale2_struct *bootloader_data, uint64_t tag_id)
{
    struct stivale2_tag *current = (stivale2_tag*)bootloader_data->tags;
    while(current != NULL)
    {    
        if (current->identifier == tag_id)
        {
            return current;
        }

        current = (stivale2_tag*)current->next;
    }
    return NULL;
}