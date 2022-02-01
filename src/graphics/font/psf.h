#pragma once

#define DEFAULT_PSF_WIDTH 8
#define DEFAULT_PSF_HEIGHT 16

namespace PSF
{
    struct header
    {
        unsigned char magic[2];
        unsigned char mode;
        unsigned char charsize;
    }__attribute__((packed));
    
    struct font
    {
        unsigned char magic[2];
        unsigned char mode;
        unsigned char charsize;
        char glyph[];
    }__attribute__((packed));
}