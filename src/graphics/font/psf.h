#pragma once

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