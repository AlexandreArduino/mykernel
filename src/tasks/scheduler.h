#pragma once

#include "../kernel.h"
#include "task.h"

#define TASKS_NUMBER 5

class Scheduler
{
public:
    void init();
private:
    struct Task *tasks[TASKS_NUMBER];
    uint8_t number_of_tasks;
};

extern Scheduler scheduler;