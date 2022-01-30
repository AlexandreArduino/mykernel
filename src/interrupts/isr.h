#pragma once

#include "../kernel.h"

extern "C" void division_by_zero_interrupt();
extern "C" void page_fault_interrupt();
extern "C" void double_fault_interrupt();
extern "C" void general_protection_fault_interrupt();
extern "C" void keyboard_interrupt();
extern "C" void mouse_interrupt();
extern "C" void pit_interrupt();
extern "C" void default_interrupt();
extern "C" void invalid_opcode_interrupt();