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