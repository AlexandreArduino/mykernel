#pragma once

#include "../kernel.h"

class LOG
{
public:
    void on();
    void off();
    void log(const char *fct, const char *message);
    void log(const char *message);
    void logln(const char *fct, const char *message);
    void logln(const char *message);
private:
    bool state;
};

extern LOG log;