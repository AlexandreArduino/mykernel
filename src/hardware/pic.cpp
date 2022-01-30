#include "pic.h"

void RemapPIC()
{
    uint8_t a1, a2;
    a1 = inb(PIC1_DATA);
    io_wait();
    a2 = inb(PIC2_DATA);
    io_wait();
    outb(PIC1_CMD, ICW1_INIT | ICW1_ICW4);
    io_wait();
    outb(PIC2_CMD, ICW1_INIT | ICW1_ICW4);
    io_wait();
    outb(PIC1_DATA, 0x20);
    io_wait();
    outb(PIC2_DATA, 0x28);
    io_wait();
    outb(PIC1_DATA, 4);
    io_wait();
    outb(PIC2_DATA, 2);
    io_wait();
    outb(PIC1_DATA, ICW4_8086);
    io_wait();
    outb(PIC2_DATA, ICW4_8086);
    io_wait();
    outb(PIC1_DATA, a1);
    io_wait();
    outb(PIC2_DATA, a2);
    io_wait();
}

void PIC_EndMaster()
{
    outb(PIC1_CMD, PIC_EOI);
}

void PIC_EndSlave()
{
    outb(PIC2_CMD, PIC_EOI);
    outb(PIC1_CMD, PIC_EOI);
}

void MaskAllInterrupts()
{
    outb(PIC1_DATA, 0b11111111);
    outb(PIC2_DATA, 0b11111111);
}