#include "gdt.h"

__attribute__((aligned(0x1000)))
struct GDT gdt;
struct TSS tss;

GDTR gdtr;
void gdt_init()
{
    gdt.knull = (struct segment){0, 0, 0, 0, 0, 0};
    gdt.kcode = (struct segment){0, 0, 0, 0x9A, 0xA0, 0};
    gdt.kdata = (struct segment){0, 0, 0, 0x92, 0xA0, 0};
    gdt.unull = (struct segment){0, 0, 0, 0, 0, 0};
    gdt.ucode = (struct segment){0, 0, 0, 0x9A, 0xA0, 0};
    gdt.udata = (struct segment){0, 0, 0, 0x92, 0xA0, 0};
    gdtr.size = sizeof(gdt) - 1;
    gdtr.address = (uint64_t)&gdt;
    load(&gdtr);
}