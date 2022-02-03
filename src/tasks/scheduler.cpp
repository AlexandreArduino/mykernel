#include "scheduler.h"

Scheduler scheduler;

void Scheduler::init()
{
    log.logln("Scheduler::init", "Initializing the kernel scheduler...");
    this->number_of_tasks = 0;

    this->tasks[0] = (struct Task*)allocator.alloc(sizeof(struct Task) * TASKS_NUMBER);
    if(this->tasks[0] == NULL)
    {
        log.logln("Scheduler::init", "Unable to allocate memory space for the tasks!");
        screen.println("Unable to allocate memory space for the tasks!");
        while(1) asm("hlt");
    }
    else
    {
        log.log("Scheduler::init", "The tasks will be located at 0x");
        log.logln(String((uint64_t)this->tasks[0], HEXADECIMAL));
    }

    // Create the first void task

    this->tasks[0]->init(0, (char*)frameAllocator.alloc(1), default_task, this->tasks[0]);

    screen.println("scheduler init");
}