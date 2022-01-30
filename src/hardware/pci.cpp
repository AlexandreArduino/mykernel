#include "pci.h"

PCI pci;

const char *PCITEXT::ClassCode[] = {
        "Unclassified", 
        "Mass Storage Controller", 
        "Network Controller", 
        "Display Controller", 
        "Multimedia Controller", 
        "Memory Controller", 
        "Bridge", 
        "Simple Communication Controller", 
        "Base System Peripheral", 
        "Input Device Controller", 
        "Docking Station", 
        "Processor", 
        "Serial Bus Controller", 
        "Wireless Controller", 
        "Intelligent Controller", 
        "Satellite Communication Controller", 
        "Encryption Controller", 
        "Signal Processing Controller",
        "Processing Accelerator", 
        "Non-Essential Instrumentation", 
        "0x3F (Reserved)", 
        "Co-Processor", 
        "0xFE (Reserved)", 
        "Unassigned Class (Vendor specific)"
};

uint16_t PCI::ReadConfiguration(uint8_t _bus, uint8_t _device, uint8_t _function, uint8_t offset)
{
    uint32_t bus = (uint32_t)_bus;
    uint32_t device = (uint32_t)_device;
    uint32_t function = (uint32_t)_function;

    uint32_t address = (uint32_t)((bus << 16) | (device << 11) | (function << 8) | (offset & 0xFC) | ((uint32_t)0x80000000));

    out32(ConfigAddress, address);
    io_wait();
    //result will contain the first word of the 32 bits register
    uint16_t result = (uint16_t)((in32(ConfigData) >> ((offset & 2) * 8)) & 0xFFFF);
    return result;
}

uint16_t PCI::GetVendor(uint8_t bus, uint8_t device)
{
    return PCI::ReadConfiguration(bus, device, 0, 0x0);
}

uint16_t PCI::GetDevice(uint8_t bus, uint8_t device)
{
    return PCI::ReadConfiguration(bus, device, 0, 0x2);
}

uint16_t PCI::GetVendor(uint8_t bus, uint8_t device, uint8_t function)
{
    return PCI::ReadConfiguration(bus, device, function, 0x0);
}

uint16_t PCI::GetDevice(uint8_t bus, uint8_t device, uint8_t function)
{
    return PCI::ReadConfiguration(bus, device, function, 0x2);
}

uint8_t PCI::GetClass(uint8_t bus, uint8_t device, uint8_t function)
{
    return (uint8_t)(PCI::ReadConfiguration(bus, device, function, 10) >> 8);
}

uint8_t PCI::GetSubClass(uint8_t bus, uint8_t device, uint8_t function)
{
    return (uint8_t)(PCI::ReadConfiguration(bus, device, function, 10));
}

uint8_t PCI::GetProgrammingInterfaceByte(uint8_t bus, uint8_t device, uint8_t function)
{
    return (uint8_t)(PCI::ReadConfiguration(bus, device, function, 8) >> 8);
}

const char *PCI::GetVendorName(uint16_t vendor)
{
    switch(vendor)
    {
        case 0x8086: return "Intel Corporation";
        case 0x1234: return "Qemu";
        default: return String((uint16_t)vendor, HEXADECIMAL);
    }
}

const char *PCI::GetDeviceName(uint16_t vendor, uint16_t device)
{
    switch(vendor)
    {
        case 0x8086:
            switch(device)
            {
                case 0x29C0: return "82G33/G31/P35/P31 Express DRAM Controller";
                case 0x2918: return "82801IB (ICH9) LPC Interface Controller";
                case 0x2922: return "82801IR/IO/IH (ICH9R/DO/DH) 6 port SATA Controller [AHCI mode]";
                case 0x2930: return "82801I (ICH9 Family) SMBus Controller";
                default: return String((uint16_t)device, HEXADECIMAL);
            }
        case 0x1234:
            switch(device)
            {
                case 0x1111: return "Virtual Video Controller";
                default: return String((uint16_t)device, HEXADECIMAL);
            }
        default: return String((uint16_t)device, HEXADECIMAL);
    }
}

const char *PCI::GetClassName(uint8_t classcode)
{
    return PCITEXT::ClassCode[classcode];
}

const char *PCI::GetSubClassName(uint8_t classcode, uint8_t subclasscode)
{
    switch(classcode)
    {
        case 0x00:
            switch(subclasscode)
            {
                case 0x00: return "Non-VGA-Compatible Unclassified Device";
                case 0x01: return "VGA-Compatible Unclassified Device";
                default: return String((uint8_t)subclasscode, HEXADECIMAL);
            }
        case 0x01:
            switch(subclasscode)
            {
                case 0x00: return "SCSI Bus Controller";
                case 0x01: return "IDE Controller";
                case 0x02: return "Floppy Disk Controller";
                case 0x03: return "IPI Bus Controller";
                case 0x04: return "RAID Controller";
                case 0x05: return "ATA Controller";
                case 0x06: return "Serial ATA Controller";
                case 0x07: return "Serial Attached SCSI Controller";
                case 0x08: return "Non-Volatile Memory Controller";
                case 0x80: return "Other";
                default: return String((uint8_t)subclasscode, HEXADECIMAL);
            }
        case 0x02:
            switch(subclasscode)
            {
                case 0x00: return "Ethernet Controller";
                case 0x01: return "Token Ring Controller";
                case 0x02: return "FDDI Controller";
                case 0x03: return "ATM Controller";
                case 0x04: return "ISDN Controller";
                case 0x05: return "WorldFip Controller";
                case 0x06: return "PICMG 2.14 Multi Computing Controller";
                case 0x07: return "Infiniband Controller";
                case 0x08: return "Fabric Controller";
                case 0x80: return "Other";
                default: return String((uint8_t)subclasscode, HEXADECIMAL);
            }
        case 0x03:
            switch(subclasscode)
            {
                case 0x00: return "VGA Compatible Controller";
                case 0x01: return "XGA Controller";
                case 0x02: return "3D Controller (Not VGA-Compatible) ";
                case 0x80: return "Other";
                default: return String((uint8_t)subclasscode, HEXADECIMAL);
            }
        case 0x04:
            switch(subclasscode)
            {
                case 0x00: return "Multimedia Video Controller";
                case 0x01: return "Multimedia Audio Controller";
                case 0x02: return "Computer Telephony Device";
                case 0x03: return "Audio Device";
                case 0x08: return "Other";
                default: return String((uint8_t)subclasscode, HEXADECIMAL);
            }
        case 0x05:
            switch(subclasscode)
            {
                case 0x00: return "RAM Controller";
                case 0x01: return "Flash Controller";
                case 0x80: return "Other";
                default: return String((uint8_t)subclasscode, HEXADECIMAL);
            }
        case 0x06:
            switch(subclasscode)
            {
                case 0x00: return "Host Bridge";
                case 0x01: return "ISA Bridge";
                case 0x02: return "EISA Bridge";
                case 0x03: return "MCA Bridge";
                case 0x04: return "PCI-to-PCI Bridge";
                case 0x05: return "PCMCIA Bridge";
                case 0x06: return "NuBus Bridge";
                case 0x07: return "CardBus Bridge";
                case 0x08: return "RACEway Bridge";
                case 0x09: return "PCI-to-PCI Bridge";
                case 0x0A: return "InfiniBand-to-PCI Host Bridge";
                case 0x80: return "Other";
                default: return String((uint8_t)subclasscode, HEXADECIMAL);
            }
        case 0x07:
            switch(subclasscode)
            {
                case 0x00: return "Serial Controller";
                case 0x01: return "Parallel Controller";
                case 0x02: return "Multiport Serial Controller";
                case 0x03: return "Modem";
                case 0x04: return "IEEE 488.1/2 (GPIB) Controller";
                case 0x05: return "Smart Card Controller";
                case 0x80: return "Other";
                default: return String((uint8_t)subclasscode, HEXADECIMAL);
            }
        case 0x08:
            switch(subclasscode)
            {
                case 0x00: return "PIC";
                case 0x01: return "DMA Controller";
                case 0x02: return "Timer";
                case 0x03: return "RTC Controller";
                case 0x04: return "PCI Hot-Plug Controller";
                case 0x05: return "SD Host controller";
                case 0x06: return "IOMMU";
                case 0x80: return "Other";
                default: return String((uint8_t)subclasscode, HEXADECIMAL);
            }
        case 0x09:
            switch(subclasscode)
            {
                case 0x00: return "Keyboard Controller";
                case 0x01: return "Digitizer Pen";
                case 0x02: return "Mouse Controller";
                case 0x03: return "Scanner Controller";
                case 0x04: return "Gameport Controller";
                case 0x80: return "Other";
                default: return String((uint8_t)subclasscode, HEXADECIMAL);
            }
        case 0x0A:
            switch(subclasscode)
            {
                case 0x00: return "Generic";
                case 0x80: return "Other";
                default: return String((uint8_t)subclasscode, HEXADECIMAL);
            }
        case 0x0B:
            switch(subclasscode)
            {
                case 0x00: return "386";
                case 0x01: return "486";
                case 0x02: return "Pentium";
                case 0x03: return "Pentium Pro";
                case 0x10: return "Alpha";
                case 0x20: return "PowerPC";
                case 0x30: return "MIPS";
                case 0x40: return "Co-Processor";
                case 0x80: return "Other";
                default: return String((uint8_t)subclasscode, HEXADECIMAL);
            }
        case 0x0C:
            switch(subclasscode)
            {
                case 0x00: return "FireWire (IEEE 1394) Controller";
                case 0x01: return "ACCESS Bus Controller";
                case 0x02: return "SSA";
                case 0x03: return "USB Controller";
                case 0x04: return "Fibre Channel";
                case 0x05: return "SMBus Controller";
                case 0x06: return "InfiniBand Controller";
                case 0x07: return "IPMI Interface";
                case 0x08: return "SERCOS Interface (IEC 61491)";
                case 0x09: return "CANbus Controller";
                case 0x80: return "Other";
                default: return String((uint8_t)subclasscode, HEXADECIMAL);
            }
        case 0x0D:
            switch(subclasscode)
            {
                case 0x00: return "iRDA Compatible Controller";
                case 0x01: return "Consumer IR Controller";
                case 0x10: return "RF Controller";
                case 0x11: return "Bluetooth Controller";
                case 0x12: return "Broadband Controller";
                case 0x20: return "Ethernet Controller (802.1a)";
                case 0x21: return "Ethernet Controller (802.1b)";
                case 0x80: return "Other";
                default: return String((uint8_t)subclasscode, HEXADECIMAL);
            }
        case 0x0E:
            switch(subclasscode)
            {
                case 0x00: return "I20";
                default: return String((uint8_t)subclasscode, HEXADECIMAL);
            }
        case 0x0F:
            switch(subclasscode)
            {
                case 0x01: return "Satellite TV Controller";
                case 0x02: return "Satellite Audio Controller";
                case 0x03: return "Satellite Voice Controller";
                case 0x04: return "Satellite Data Controller";
                default: return String((uint8_t)subclasscode, HEXADECIMAL);
            }
        case 0x10:
            switch(subclasscode)
            {
                case 0x00: return "Network and Computing Encrpytion/Decryption";
                case 0x01: return "Entertainment Encryption/Decryption";
                case 0x80: return "Other";
                default: return String((uint8_t)subclasscode, HEXADECIMAL);
            }
        case 0x11:
            switch(subclasscode)
            {
                case 0x00: return "DPIO Modules";
                case 0x01: return "Performance Counters";
                case 0x10: return "Communication Synchronizer";
                case 0x20: return "Signal Processing Management";
                case 0x80: return "Other";
                default: return String((uint8_t)subclasscode, HEXADECIMAL);
            }
        default: return String((uint8_t)classcode, HEXADECIMAL);
    }
}

uint8_t PCI::CheckHeaderType(uint8_t bus, uint8_t device, uint8_t function)
{
    return (uint8_t)(uint16_t)(this->ReadConfiguration(bus, device, function, 14) & 0x7F);
}

uint32_t PCI::get_bar(uint8_t bus, uint8_t device, uint8_t function, uint8_t bar_number)
{
    uint16_t base_address_high_part = this->ReadConfiguration(bus, device, function, 0x12 + bar_number * sizeof(uint32_t));
    uint16_t base_address_low_part = this->ReadConfiguration(bus, device, function, 0x10 + bar_number * sizeof(uint32_t));
    uint32_t base_address =  ((uint32_t)base_address_high_part << 16) +  base_address_low_part;

    return base_address;
}

void PCI::show_all_periph()
{
    log.logln("PCI::show_all_periph", "Here are the devices detected : ");
    for(uint8_t bus = 0; bus < 8; bus++)
    {
        for(uint8_t device = 0; device < 32; device++)
        {
            for(uint8_t function = 0; function < 8; function++)
            {
                uint16_t tmp = pci.GetVendor(bus, device, function);
                if(tmp != 0xFFFF)
                {
                    uint16_t Vendor = tmp;
                    uint16_t Device = pci.GetDevice(bus, device, function);
                    uint8_t Class = pci.GetClass(bus, device, function);
                    uint8_t SubClass = pci.GetSubClass(bus, device, function);
                    log.log(pci.GetVendorName(tmp));
                    log.log("/");
                    log.log(pci.GetDeviceName(Vendor, Device));
                    log.log("/");
                    log.log(pci.GetClassName(Class));
                    log.log("/");
                    log.log(pci.GetSubClassName(Class, SubClass));
                    uint8_t type = pci.CheckHeaderType(bus, device, function);
                    if(type == PCI_GENERAL_DEVICE) log.log(" => General Device");
                    else if(type == PCI_TO_PCI_BRIDGE) log.log(" => PCI to PCI bridge");
                    else if(type == PCI_CARDBUS) log.log(" => PCI Cardbus");
                    else log.log(" => Unknown type");
                    log.log(" 0x");
                    uint32_t bar = pci.get_bar(bus, device, function, 0);
                    log.logln(String((uint32_t)bar, HEXADECIMAL));
                }
            }
        }
    }
}