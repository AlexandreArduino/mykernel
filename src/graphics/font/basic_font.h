#pragma once

#include "../../kernel.h"

#define ZAP_LIGHT_FILE_SIZE 5312

class fontLoader
{
public:
	void init();
private:
	bool isFileSizeCorrect(uint16_t size);
	uint16_t get_file_size();
};

extern fontLoader floader;