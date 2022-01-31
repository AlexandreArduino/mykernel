#pragma once

#include "kernel.h"

struct ModulesStartEnd
{
    uint64_t *start;
    uint64_t *end;
};

class LimineModulesParser
{
public:
    void init(struct stivale2_struct_tag_modules *modules);
    void load_all_modules();
    uint64_t get_psf_font_start();
    uint64_t get_psf_font_end();
private:
    struct stivale2_struct_tag_modules *modules;
    uint64_t psf_font_start;
    uint64_t psf_font_end;
    bool loaded;
};

extern LimineModulesParser limineModules;