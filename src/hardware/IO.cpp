#include "IO.h"

void outb(uint16_t port, uint8_t value)
{
    asm volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

void out32(uint16_t port, uint32_t value)
{
    asm volatile ("outl %0, %1" : : "a"(value), "Nd"(port));
}

void out16(uint16_t port, uint16_t value)
{
    asm volatile ("outw %0, %1" : : "a"(value), "Nd"(port));
}

uint8_t inb(uint16_t port)
{
    uint8_t returnValue;
    asm volatile ("inb %1, %0"
    : "=a"(returnValue)
    : "Nd"(port));
    return returnValue;
}

uint32_t in32(uint16_t port)
{
    uint32_t returnValue;
    asm volatile("inl %1, %0"
    : "=a"(returnValue)
    : "Nd"(port));
    return returnValue;
}

uint16_t in16(uint16_t port)
{
    uint16_t returnValue;
    asm volatile("inw %1, %0"
    : "=a"(returnValue)
    : "Nd"(port));
    return returnValue;
}

void io_wait()
{
    asm volatile ("outb %%al, $0x80" : : "a"(0)); // Wait an IO cycle
}