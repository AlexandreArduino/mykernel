#include "loop.h"

void Tests::sample_loop(int value)
{
    log.log("Tests::sample_loop", "Sample looping to ");
    log.logln(String(value, DECIMAL), "...");
    int output = 0;
    for(int i = 0; i < value; i++) { output = i; }
    log.log("Tests::sample_loop", "Result : ");
    log.logln(String(output, DECIMAL));
}