#include "modules.h"

LimineModulesParser limineModules;

void LimineModulesParser::init(struct stivale2_struct_tag_modules *modules)
{
    this->loaded = false;
    this->modules = modules;
    if(this->modules == NULL)
    {
        Exceptions::panic("Unable to locate bootloader modules!");
    }
    log.log("LimineModulesParser::init", "The limine modules are located at 0x");
    log.logln(String((uint64_t)this->modules, HEXADECIMAL));
    log.log("LimineModulesParser::init", "Number of modules detected : ");
    log.logln(String(this->modules->module_count, DECIMAL));
}

void LimineModulesParser::load_all_modules()
{
    log.logln("LimineModulesParser::load_all_modules", "Loading all the modules informations...");
    this->psf_font_start = this->modules->modules[0].begin;
    this->psf_font_end = this->modules->modules[0].end;
    this->loaded = true;
}

uint64_t LimineModulesParser::get_psf_font_start()
{
    if(!this->loaded) Exceptions::panic("You need to load the modules before reading them!");
    else return this->psf_font_start;
}

uint64_t LimineModulesParser::get_psf_font_end()
{
    if(!this->loaded) Exceptions::panic("You need to load the modules before reading them!");
    else return this->psf_font_end;
}