#pragma once

#include <stdint.h>
#include "stivale2.h"
#include "config.h"
#include "modules.h"
#include "hardware/IO.h"
#include "hardware/COM.h"
#include "hardware/pic.h"
#include "hardware/pci.h"
#include "hardware/cmos.h"
#include "hardware/rtc.h"
#include "gdt/gdt.h"
#include "lib/base.h"
#include "lib/string.h"
#include "lib/mem.h"
#include "lib/math/math.h"
#include "lib/defs.h"
#include "lib/arithmetic/cnvrt.h"
#include "memory/memory.h"
#include "memory/frames.h"
#include "memory/heap.h"
#include "cpu/cpu.h"
#include "interrupts/idt.h"
#include "acpi/rsdp.h"
#include "acpi/rsdt.h"
#include "acpi/apic/apic.h"
#include "drivers/pit/pit.h"
#include "drivers/keyboard/keyboard.h"
#include "drivers/keyboard/dispositions.h"
#include "drivers/sound/beep.h"
#include "exceptions/panic.h"
#include "graphics/font/basic_font.h"
#include "graphics/framebuffer.h"
#include "graphics/screen.h"
#include "graphics/textcursor.h"
#include "debug/log.h"
#include "debug/maths/primenumbers_test.h"
#include "debug/memory/loop.h"
#include "tasks/scheduler.h"

#ifdef TEST
#include "debug/graphics/framebuffer_test.h"
#endif

#define cli() __asm__("cli");
#define sti() __asm__("sti");

extern "C" void _start(struct stivale2_struct *bootloader_data);
void *stivale2_find_tag(struct stivale2_struct *bootloader_data, uint64_t tag_id);