#pragma once

#include "../kernel.h"
#include "isr.h"

#define IDT_TA_InterruptGate 0b10001110
#define IDT_TA_CallGate 0b10001100
#define IDT_TA_TrapGate 0b10001111

void setEntry(void *isr, uint8_t interrupt_number, uint8_t attr, uint8_t code_segment);
void setupIDT();


struct IDTEntry
{
    uint16_t isr_low_base;
    uint16_t selector;
    uint8_t ist;
    uint8_t type_attr;
    uint16_t isr_middle_base;
    uint32_t isr_high_base;
    uint32_t ignore;

};

struct IDTR
{
    uint16_t Limit;
    uint64_t Offset;
}__attribute__((packed));

extern IDTR idtr;