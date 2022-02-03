#include "task.h"

void default_task()
{
    while(1) asm("hlt");
}

void Task::init(uint8_t id, char *stack_ptr, void (*entry)(), struct Task *next)
{
    log.log("Task::init", "Creating task number ");
    log.logln((String(id, DECIMAL)), "...");
    this->id = id;
    if(stack_ptr == NULL)
    {
        log.log("Task::init", "NULL stack ptr! Task creation cancelled!");
        return;
    }
    this->stack[0] = stack_ptr;
    this->entry = entry;
    this->next = next;

    log.logln("Task::init", "Task created : ");
    log.logln("ID :", String(this->id, DECIMAL));
    log.logln("Stack : 0x", String((uint64_t)(uint64_t*)this->stack, HEXADECIMAL));
    log.logln("Handle function 0x", String((uint64_t)(uint64_t*)this->entry, HEXADECIMAL));
    log.logln("Next task : 0x", String((uint64_t)this->next, HEXADECIMAL));
}