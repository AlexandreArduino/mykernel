#include "modules.h"

LimineModulesParser limineModules;

void LimineModulesParser::init(struct stivale2_struct_tag_modules *modules)
{
    this->modules = modules;
    if(this->modules == NULL)
    {
        Exceptions::panic("Unable to locate bootloader modules!");
    }
    log.log("LimineModulesParser::init", "The limine modules are located at 0x");
    log.logln(String((uint64_t)this->modules, HEXADECIMAL));
}