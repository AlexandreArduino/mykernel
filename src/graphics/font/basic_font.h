#pragma once

#include "../../kernel.h"

class fontLoader
{
public:
	void init(void *font_tab);
private:
	void *font;
};

extern fontLoader floader;