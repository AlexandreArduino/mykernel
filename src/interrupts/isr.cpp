#include "isr.h"

extern "C" void DivisionByZero()
{
    log.logln("WARNING : You tried to divide by zero!");
}

extern "C" void PageFaultHandler()
{
    Exceptions::panic("Page Fault detected!");
}

extern "C" void DoubleFaultHandler()
{
    Exceptions::panic("Double Page Fault detected!");
}
extern "C" void GeneralProtectionHandler()
{
    Exceptions::panic("General Protection Fault detected!");
}

extern "C" void KeyboardInterruptHandler()
{
    uint8_t scanCode = inb(0x60);
	keyboard.handle(scanCode);
    PIC_EndMaster();
}

extern "C" void MouseInterruptHandler()
{
    uint8_t mouseData = inb(0x60);
    // mouse.handle(mouseData);
    log.logln("Mouse interrupt!");
    PIC_EndSlave();
}

extern "C" void PITHandler()
{
    pit.handler();
    PIC_EndMaster();
}


extern "C" void InvalidOpCode()
{
    Exceptions::panic("Invalid OpCode interrupt!");
}