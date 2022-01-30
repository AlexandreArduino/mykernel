#pragma once

#include "../kernel.h"

#define PIC1_CMD 0x20
#define PIC1_DATA 0x21
#define PIC2_CMD 0xA0
#define PIC2_DATA 0xA1
#define PIC_EOI 0x20

#define ICW1_INIT 0x10
#define ICW1_ICW4 0x01
#define ICW4_8086 0x01

void RemapPIC();
void PIC_EndMaster();
void PIC_EndSlave();
void MaskAllInterrupts();