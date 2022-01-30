#pragma once

#include "../kernel.h"

#define RSDT_SIGNATURE "RSDT"
#define MADT "APIC"
#define FADT "FACP"
#define HPET "HPET"
#define MCFG "MCFG"

struct RSDT
{
    void init(struct SDTHeader *rsdt);
    bool check_signature();
    void *find(const char *signature);
    void list_all();
    bool check_random_table_signature(const char *signature);
    struct SDTHeader *rsdt;
    struct RSDTDescriptor *table;
    int entries;
};

extern struct RSDT rsdt;