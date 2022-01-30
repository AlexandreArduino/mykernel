#include "mem.h"

bool memcmp(void *arg1, void *arg2, size_t size)
{
    char *ptr1 = (char*)arg1;
    char *ptr2 = (char*)arg2;
    for(size_t i = 0; i <= size; i++)
    {
        if(ptr1[i] != ptr2[i]) return false;
    }
    return true;
}

void memcpy(void *dst, void *src, size_t size)
{
    for(size_t i = 0; i < size; i++)
    {
        *(char*)((char*)dst + i) = *(char*)((char*)src + i);
    }
}

