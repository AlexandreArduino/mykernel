#include "primenumber.h"

bool Mathematics::isPrimeNumber(size_t n)
{
    n = Mathematics::abs(n);
    if(n > 1)
    {
        for(size_t i = 2; i < n; i++)
        {
            if(!(n % i)) return false;
        }
        return true;
    }
    return true;
}