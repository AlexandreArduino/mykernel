#pragma once

#include "../kernel.h"

#define TASK_STACK_SIZE 4096

struct Task
{
    uint8_t id;
    uint8_t *stack[TASK_STACK_SIZE];
    void (*entry)();
    struct Task *next;
    struct SavedState *registers_state;
    void init(uint8_t id, uint8_t *stack_ptr, void (*entry)(), struct Task *next);
};

void show_task_info(struct Task *task);

void default_task();