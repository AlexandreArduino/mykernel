#pragma once

#include "../kernel.h"
#include "task.h"

#define TASKS_NUMBER 5

class Scheduler
{
public:
    void init();
    bool create(void (*handler)());
    struct Task *tasks[TASKS_NUMBER];
    void switch_task();
private:
    uint8_t number_of_tasks;
    struct Task *current_task;
};

extern Scheduler scheduler;