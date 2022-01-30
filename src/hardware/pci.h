#pragma once

#include "../kernel.h"

#define ConfigAddress 0xCF8
#define ConfigData 0xCFC

#define PCI_GENERAL_DEVICE 0x0
#define PCI_TO_PCI_BRIDGE 0x1
#define PCI_CARDBUS 0x2

struct StandardPCIHeader
{
    uint16_t vendor_id;
    uint16_t device_id;
    uint16_t command;
    uint16_t status;
    uint8_t revision_id;
    uint8_t prog_if;
    uint8_t header_type;
    uint8_t bist;
}__attribute__((packed));

struct BAR
{
    uint64_t base;
    uint64_t io_base;
    uint32_t size;
    uint32_t type;
}__attribute__((packed));

class PCI
{
public:
    uint16_t ReadConfiguration(uint8_t _bus, uint8_t _device, uint8_t _function, uint8_t offset);
    uint16_t GetVendor(uint8_t bus, uint8_t device);
    uint16_t GetVendor(uint8_t bus, uint8_t device, uint8_t function);
    uint16_t GetDevice(uint8_t bus, uint8_t device);
    uint16_t GetDevice(uint8_t bus, uint8_t device, uint8_t function);
    uint8_t GetClass(uint8_t bus, uint8_t device, uint8_t function);
    uint8_t GetSubClass(uint8_t bus, uint8_t device, uint8_t function);
    uint8_t GetProgrammingInterfaceByte(uint8_t bus, uint8_t device, uint8_t function);
    const char *GetVendorName(uint16_t vendor);
    const char *GetDeviceName(uint16_t vendor, uint16_t device);
    const char *GetClassName(uint8_t classcode);
    const char *GetSubClassName(uint8_t classcode, uint8_t subclasscode);
    uint8_t CheckHeaderType(uint8_t bus, uint8_t device, uint8_t function);
    uint32_t get_bar(uint8_t bus, uint8_t device, uint8_t function, uint8_t bar_number);
    void show_all_periph();
};

namespace PCITEXT
{
    extern const char *ClassCode[];
};

extern PCI pci;