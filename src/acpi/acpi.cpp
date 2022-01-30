#include "rsdp.h"

ACPI acpi;

void ACPI::init(uint64_t *rsdp)
{
    this->rsdp = (struct RSDPDescriptor*)rsdp;
    log.log("ACPI::init", "RSDP located at 0x");
    log.logln(String((uint64_t)this->rsdp, HEXADECIMAL));
    if(!this->check_rsdp_signature())
    {
        log.logln("ACPI::init", "Invalid RSDP signature!");
        log.log("ACPI::init", "Signature detected : ");
        com.writeln(this->rsdp->base.Signature, 8);
        framebuffer.clear(SIGNATURE_ERROR);
        while(1);
    }
    this->version = this->rsdp->base.Revision;
    if(!this->version) log.logln("ACPI::init", "ACPI version 1.0");
    else log.logln("ACPI::init", "New ACPI version");
    if(!this->rsdp_checksum())
    {
        log.logln("ACPI::init", "RSDP checksum failed!");
        framebuffer.clear(SIGNATURE_ERROR);
        while(1);
    }
    log.log("ACPI::init", "OEM ID : ");
    com.writeln(this->rsdp->base.OEMID, 6);
    if(!this->version)
    {
        log.log("ACPI::init", "RSDT located at 0x");
        log.logln(String((uint64_t)this->rsdp->base.RsdtAddress, HEXADECIMAL));
        rsdt.init((struct SDTHeader*)this->rsdp->base.RsdtAddress);
    }
}

bool ACPI::check_rsdp_signature()
{
    return memcmp((void*)this->rsdp->base.Signature, (void*)RSDP_SIGNATURE, 7);
}

bool ACPI::rsdp_checksum()
{
    uint64_t checksum = 0;
    uint8_t *ptr = (uint8_t*)this->rsdp;
    if(!this->version)
    {
        for(uint8_t i = 0; i < sizeof(BaseRSDPDescriptor); i++)
        {
            checksum += ptr[i];
        }
    }
    return ~(!(checksum & 0b11111111));
}

bool StandardSDT::checksum(SDTHeader *table)
{
    unsigned char sum = 0;
    for(int i = 0; i < table->Length; i++)
    {
        sum += ((char*)table)[i];
    }
    return sum == 0;
}