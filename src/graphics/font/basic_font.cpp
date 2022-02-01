#include "basic_font.h"

fontLoader floader;

void fontLoader::init()
{
	log.logln("fontLoader::init", "Loading the font file...");
	log.logln("fontLoader::init", "Checking size file...");
	log.log("fontLoader::init", "Size in bytes : ");
	log.logln(String(this->get_file_size(), DECIMAL));
	if(!this->isFileSizeCorrect(ZAP_LIGHT_FILE_SIZE))
	{
		Exceptions::panic("The zap light file size is not correct!");
		log.logln("The file size detected in bytes is ", String(this->get_file_size(), DECIMAL));
	}
	this->font = (PSF::font*)limineModules.get_psf_font_start();
	log.logln("fontLoader::init", "Copying file in usable memory...");
	uint8_t pages = (this->get_file_size() / 4096) + 1;
	uint64_t *space_allocated = (uint64_t*)frameAllocator.alloc(pages);
	memcpy((void*)space_allocated, (void*)(uint64_t*)limineModules.get_psf_font_start(), ZAP_LIGHT_FILE_SIZE);
	log.log("fontLoader::init", "The file is now at 0x");
	this->font = (PSF::font*)space_allocated;
	log.logln(String((uint64_t)this->font, HEXADECIMAL));
}

bool fontLoader::isFileSizeCorrect(uint16_t size)
{
	if(this->get_file_size() != size) return false;
	else return true;
}

uint16_t fontLoader::get_file_size()
{
	return limineModules.get_psf_font_end() - limineModules.get_psf_font_start();
}