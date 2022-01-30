#include "panic.h"

void Exceptions::panic(const char *error){
    log.logln("################################");
    log.logln("A kernel panic has been detected!");
    log.log("The error message is : ");
    log.logln(error);
    cpu.dump_registers();
    log.logln("################################");
    framebuffer.clear(PANIC_SCREEN);
    while(1) asm("hlt");
}