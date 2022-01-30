#include "idt.h"

IDTR idtr;

void setEntry(void *isr, uint8_t interrupt_number, uint8_t attr, uint8_t code_segment)
{
    // log.log("setEntry", "Setting interrupt number ");
    // log.logln(String(interrupt_number, DECIMAL));
    IDTEntry *interrupt =(IDTEntry*)(idtr.Offset + interrupt_number * sizeof(IDTEntry));
    interrupt->isr_low_base = (uint16_t)((uint64_t)isr & 0x000000000000FFFF);
    interrupt->isr_middle_base = (uint16_t)(((uint64_t)isr & 0x00000000FFFF0000) >> 16);
    interrupt->isr_high_base = (uint32_t)(((uint64_t)isr & 0xFFFFFFFF00000000) >> 32);
    interrupt->type_attr = attr;
    interrupt->selector = code_segment;

}

void setupIDT()
{
    idtr.Limit = 0x0FFF;
    idtr.Offset = (uint64_t)frameAllocator.alloc(1);
    for(int i = 0; i <= 255; i++) setEntry((void*)default_interrupt, i, IDT_TA_InterruptGate, 0x08);
    setEntry((void*)division_by_zero_interrupt, 0x0, IDT_TA_InterruptGate, 0x08);
    setEntry((void*)page_fault_interrupt, 0xE, IDT_TA_InterruptGate, 0x08);
    setEntry((void*)double_fault_interrupt, 0x8, IDT_TA_InterruptGate, 0x08);
    setEntry((void*)general_protection_fault_interrupt, 0xD, IDT_TA_InterruptGate, 0x08);
    setEntry((void*)keyboard_interrupt, 0x21, IDT_TA_InterruptGate, 0x08);
    setEntry((void*)mouse_interrupt, 0x2C, IDT_TA_InterruptGate, 0x08);
    setEntry((void*)pit_interrupt, 0x20, IDT_TA_InterruptGate, 0x08);
    asm ("lidt %0" : : "m" (idtr));
    asm ("sti");
    RemapPIC();
    outb(PIC1_DATA, 0b11111000);
    outb(PIC2_DATA, 0b11111111);
    asm("sti");
    log.logln("setupIDT", "If you see this message and there is no GPF, interrupts are set up!");
}
