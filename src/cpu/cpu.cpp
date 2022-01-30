#include "cpu.h"

struct CPU cpu;

const char *string_registers[] = {
    "RAX",
    "RBX",
    "RCX",
    "RDX",
    "RSI",
    "RDI",
    "R8",
    "R9",
    "R10",
    "R11",
    "R12",
    "R13",
    "R14",
    "R15"
};

void CPU::dump_registers()
{
    log.logln("CPU::dump_registers", "Here is the dump of the common registers : ");
    dump_registers_asm();
    uint64_t *register_ptr = &registers_saved.rax;
    for(uint8_t i = 0; i < number_registers; i++)
    {
        log.log(string_registers[i]);
        log.log(" = 0x");
        log.logln(String(*register_ptr, HEXADECIMAL));
        register_ptr++;
    }
}

void CPU::show_vendor()
{
    memcpy((void*)this->vendor_string, (void*)(char*)cpuid_command(0), 12);
    this->vendor_string[12] = (char*)'\0';
    log.log("CPU::show_vendor", "CPUID Vendor : ");
    log.logln((char*)this->vendor_string);
}