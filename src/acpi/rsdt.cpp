#include "rsdt.h"

struct RSDT rsdt;

const char *valids_signatures[] = {
    MADT,
    FADT,
    HPET,
    MCFG
};

void RSDT::init(struct SDTHeader *rsdt){
    this->rsdt = rsdt;
    if(!this->check_signature())
    {
        Exceptions::panic("Invalid RSDT signature!");
    }
    if(!StandardSDT::checksum(this->rsdt))
    {
        Exceptions::panic("RSDT checksum failed!");
    }
    this->table = (struct RSDTDescriptor*)this->rsdt;
    this->entries = (this->table->h.Length - sizeof(this->table)) / 4;
    this->list_all();
    apic.init((uint64_t*)this->find(MADT));
}

bool RSDT::check_signature(){
    return memcmp((void*)&this->rsdt->Signature, (void*)RSDT_SIGNATURE, 3);
}

void *RSDT::find(const char *signature)
{
    for(int i = 0; i < this->entries; i++)
    {
        struct SDTHeader *header = (struct SDTHeader*)this->table->next[i];
        if(memcmp((void*)&header->Signature, (void*)signature, 3)) return (void*)header;
    }
    return NULL;
}

void RSDT::list_all()
{
    log.logln("RSDT::list_all", "RSDT Tables available : ");
    for(int i = 0; i < this->entries; i++)
    {
        struct SDTHeader *header = (struct SDTHeader*)this->table->next[i];
        if(this->check_random_table_signature((char*)&header->Signature))
        {
            log.log("\t- ");
            com.writeln(&header->Signature[0], 4);
        }
    }
}

bool RSDT::check_random_table_signature(const char *signature)
{
    for(int i = 0; i < sizeof(valids_signatures) / 8; i++)
    {
        if(memcmp((void*)valids_signatures[i], (void*)signature, 3)) return true;
    }
    return false;
}