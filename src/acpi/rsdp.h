#pragma once

#include "../kernel.h"

#define RSDP_SIGNATURE "RSD PTR "

static struct stivale2_struct_tag_rsdp rsdp_tag {
    .tag = 
    {
        .identifier = STIVALE2_STRUCT_TAG_RSDP_ID,
        .next = 0
    }
};

struct BaseRSDPDescriptor
{
    char Signature[8];
    uint8_t Checksum;
    char OEMID[6];
    uint8_t Revision;
    uint32_t RsdtAddress;
}__attribute__((packed));

struct RSDPDescriptor
{
    BaseRSDPDescriptor base;
    uint32_t Length;
    uint64_t XsdtAddress;
    uint8_t ExtendedChecksum;
    uint8_t reserved[3];
}__attribute__((packed));

struct SDTHeader {
    char Signature[4];
    uint32_t Length;
    uint8_t Revision;
    uint8_t Checksum;
    char OEMID[6];
    char OEMTableID[8];
    uint32_t OEMRevision;
    uint32_t CreatorID;
    uint32_t CreatorRevision;
}__attribute__((packed));

struct RSDTDescriptor {
    struct SDTHeader h;
    uint32_t next[];
}__attribute__((packed));

struct XSDT
{
    struct SDTHeader h;
    uint64_t next[];
}__attribute__((packed));

struct APICHeader
{
    uint8_t type;
    uint8_t record_length;
}__attribute__((packed));

struct MADTDescriptor
{
    struct SDTHeader header;
    uint32_t lapic_address;
    uint32_t flags;
    struct APICHeader first_header;
}__attribute__((packed));

class ACPI
{
public:
    void init(uint64_t *rsdp);
private:
    struct RSDPDescriptor *rsdp;
    bool check_rsdp_signature();
    bool rsdp_checksum();
    bool version;
    struct XSDT *xsdt;
};

namespace StandardSDT
{
    bool checksum(SDTHeader *table);
};

extern ACPI acpi;