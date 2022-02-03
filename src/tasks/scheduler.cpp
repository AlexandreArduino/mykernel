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
    uint8_t *ptr = (uint8_t*)frameAllocator.alloc(1);
    this->tasks[0]->init(this->number_of_tasks, ptr, default_task, this->tasks[0]);

    this->number_of_tasks++;

    screen.println("scheduler init");
}

bool Scheduler::create(void (*handler)())
{
    if(this->number_of_tasks > TASKS_NUMBER)
    {
        log.log("Scheduler::create", "Cannot create more than ");
        log.logln(String(TASKS_NUMBER, DECIMAL), " tasks!");
        return false;
    }
    uint8_t* ptr = (uint8_t*)frameAllocator.alloc(1);
    screen.println(String((uint64_t)ptr, HEXADECIMAL));
    this->tasks[this->number_of_tasks]->init(this->number_of_tasks, (uint8_t*)frameAllocator.alloc(1), handler, this->tasks[0]);
    this->tasks[this->number_of_tasks - 1]->next = this->tasks[this->number_of_tasks];
    this->number_of_tasks++;
    return true;
}