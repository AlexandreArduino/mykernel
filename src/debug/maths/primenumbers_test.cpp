#include "primenumbers_test.h"

void Tests::primenumbers_examples()
{
    log.log("Tests::primenumbers_examples", "Prime numbers between 0 and 20 : ");
    for(uint8_t i = 1; i < 20; i++)
    {
        if(Mathematics::isPrimeNumber(i))
        {
            log.log(String(i, DECIMAL));
            log.log(", ");
        }
    }
    log.logln("done");
}