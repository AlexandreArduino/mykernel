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

struct TSS
{
    uint8_t reserved1 : 4;
    uint8_t rsp0_low : 4;
    uint8_t rsp0_high : 4;
    uint8_t rsp1_low : 4;
    uint8_t rsp1_high : 4;
    uint8_t rsp2_low : 4;
    uint8_t rsp2_high : 4;
    uint8_t reserved2;
    uint8_t ist1_low : 4;
    uint8_t ist1_high : 4;
    uint8_t ist2_low : 4;
    uint8_t ist2_high : 4;
    uint8_t ist3_low : 4;
    uint8_t ist3_high : 4;
    uint8_t ist4_low : 4;
    uint8_t ist4_high : 4;
    uint8_t ist5_low : 4;
    uint8_t ist5_high : 4;
    uint8_t ist6_low : 4;
    uint8_t ist6_high : 4;
    uint8_t ist7_low : 4;
    uint8_t ist7_high : 4;
    uint8_t reserved3;
    uint8_t reserved4 : 4;
    uint8_t iopb_offset : 4;
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
extern struct TSS tss;
extern "C" void load(GDTR *gdtr);