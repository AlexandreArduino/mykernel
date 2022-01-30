#include "apic.h"

APIC apic;

void APIC::init(uint64_t *apic_address)
{
    if(apic_address == NULL) Exceptions::panic("No APIC table found!");
    else this->apic = (struct MADTDescriptor*)apic_address;
    log.log("APIC::init", "MADT table located at 0x");
    log.logln(String((uint64_t)this->apic, HEXADECIMAL));
    // this->mask_all_interrupts();
    log.log("APIC::init", "Local APIC address : 0x");
    log.logln(String((uint64_t)this->apic->lapic_address, HEXADECIMAL));
}

void APIC::mask_all_interrupts(){
    log.logln("APIC::mask_all_interrupts", "Masking all PIC Interrupts...");
    asm ("cli");
    outb(PIC1_DATA, 0b11111111);
    outb(PIC2_DATA, 0b11111111);
    asm ("sti");
}