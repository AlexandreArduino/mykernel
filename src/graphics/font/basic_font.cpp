#include "basic_font.h"

fontLoader floader;

void fontLoader::init(void *font_tab)
{
	this->font = font_tab;
	log.log("fontLoader::init", "Loading font tab at 0x");
	log.logln(String((uint64_t)this->font, HEXADECIMAL));
}