#pragma once

#include "kernel.h"

class LimineModulesParser
{
public:
    void init(struct stivale2_struct_tag_modules *modules);
private:
    struct stivale2_struct_tag_modules *modules;
};

extern LimineModulesParser limineModules;