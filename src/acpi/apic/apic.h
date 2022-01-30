#pragma once

#include "../../kernel.h"

#define PROCESSOR_LOCAL_APIC 0

struct ProcessorLocalAPIC
{
    uint8_t ACPIProcessorID;
    uint8_t APIC_ID;
    uint32_t flags;
}__attribute__((packed));

class APIC
{
public:
    void init(uint64_t *apic_address);
private:
    struct MADTDescriptor *apic;
    void mask_all_interrupts();
};

extern APIC apic;