#pragma once

#include "../kernel.h"

struct GDTR
{
    uint16_t size;
    uint64_t address;
}__attribute__((packed));

struct segment
{
    uint16_t low_limit;
    uint16_t low_base;
    uint8_t middle_base;
    uint8_t flag;
    uint8_t high_limit_and_granularity;
    uint8_t high_base;
}__attribute__((packed));

struct GDT
{
    struct segment knull;
    struct segment kcode;
    struct segment kdata;
    struct segment unull;
    struct segment ucode;
    struct segment udata;
}__attribute__((packed));
__attribute__((aligned(0x1000)))

void gdt_init();

extern GDT gdt;
extern "C" void load(GDTR *gdtr);