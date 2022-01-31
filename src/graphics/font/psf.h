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
        struct header* psf1_Header;
        void* glyphBuffer;
    }__attribute__((packed));
}