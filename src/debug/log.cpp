#include "log.h"

LOG log;

void LOG::on(){ this->state = true; }
void LOG::off(){ this->state = false; }
void LOG::log(const char *fct, const char *msg)
{
    if(this->state)
    {
        com.write(fct);
        com.write(" ");
        com.write(msg);
    }
}

void LOG::logln(const char *fct, const char *msg)
{
    this->log(fct, msg);
    if(this->state) com.write('\n');
}

void LOG::log(const char *message)
{
    if(this->state)
    {
        com.write(message);
    }
}

void LOG::logln(const char *message)
{
    this->log(message);
    if(this->state) com.write('\n');
}